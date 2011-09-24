/*
        modified by lo sauer, 2001
    --------------------------------

    SDL_image:  An example image loading library for use with SDL
    Copyright (C) 1999, 2000, 2001  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/

 /*
 * A RAW Image loader for the SDL library
 * Supports: Reading 8, 16, 24 and 32bpp images, with alpha or colourkey,
 *
 * RAW Info: Image Stream only contains the pure pixel-data, without any header, 
 * therefore width, height and bpp must be provided, else they're estimated.
 *
 * Header Format: (if available) Magic_Bytes_Num = 4
 *				  #define MAGIC_BYTES 0x524157
 *				  char raw_spec = 
 *
 *
 * RAW Creation: Photoshop, others....
 * 
 * If you need a special format not provided in this lib, then you should take a 
 * look at the ImageMagick project: http://www.imagemagick.org/www/formats.html
 *
 * 2001-21-12 Lorenz Sauer <lorenz_sauer@gmx.at>: initial version
 * Todo: Rewrite code, to speed up loading process
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <math.h>
#include "string.h"

#include "SDL_endian.h"
#include "SDL_image.h"

#define BOOL    int
#define FALSE   0
#define TRUE    1

#ifdef LOAD_RAW

typedef struct IMG_Raw
{
	int width;													// Width Of Image In Pixels
	int height;													// Height Of Image In Pixels
	int numcmpts;												// Number Of Components
	unsigned char *data;										// Raw Pixel Data (RGBA)
} IMG_Raw;

typedef struct RAW_Header {
	Uint16 x;
	Uint16 y;
	Uint8 bpp;
	Uint8 alpha;
} RAW_Header;


/* See if an image is contained in a data source, Set as pre-last Element in
   Function LUT. Last should be the dummy type. Due lack of a header, it's 
   always assumed as true */
int IMG_isRAW(SDL_RWops *src)
{
	return(TRUE);
}

/* little endian 2 big endian order */
void le2be(Uint16 *num) {
	Uint16 Lby = *num & 0x00FF;
	Lby <<= 8;
	*num >>= 8;
	*num |= Lby;

	//return num;
}

/* Load a PCX type image from an SDL datasource */
SDL_Surface *IMG_LoadRAW_RW(SDL_RWops *src)
{
	int w=256, h=256, numcmpts=3, i, j, k, done=0, scanline, raw_spec=0, flen,len,bpp=1;
	Uint32 Rmask, Gmask, Bmask, Amask;
	IMG_Raw *image;
	SDL_Surface *surface;
	unsigned char *p = NULL, buf[4]={0};
	RAW_Header header={0};

	if ( ! src ) {
		return FALSE;
	}

	/* Check for header ELSE estimate {ratio 1:1, (w=h %8) == 0} */
	if (SDL_RWread(src, buf, 1, 3) == 3	&& strcmp( buf , "RAW") == 0 ) {
		SDL_RWread(src, &header, 1, 8);
		le2be(&header.x);
		le2be(&header.y);
		raw_spec = TRUE;
	} else {
		//SDL_RWseek(src, 0, SEEK_SET);
		flen = SDL_RWseek(src, 0, SEEK_END);
		SDL_RWseek(src, 0, SEEK_SET);
		if( ! (flen %2) ){
			while( (bpp != 4) && (( len = (int) sqrt(flen/bpp)) %8) ){	bpp++; }
			header.x = len;
			header.y = len;
			header.bpp = bpp*8;
			raw_spec = TRUE;
		} else {
			fprintf(stderr, "RAW file is either corrupted or couldn't be estimated properly! %i",bpp);
		}
	}

    image = (IMG_Raw *) malloc(sizeof(IMG_Raw));

	/* Set image width, height & format*/
    if( image ) {
        image->width  = raw_spec ? header.x : w;
        image->height = raw_spec ? header.y : h;
        image->numcmpts = raw_spec ? (header.bpp/8)+1 : numcmpts+1;
        
		image->data = (void *) malloc( image->width * image->height * image->numcmpts);
        if ( ! image->data ) {
			fprintf(stderr, "Could Not Allocate Memory For A Texture Buffer\n");
            return FALSE;
        }
    } else {
		fprintf(stderr, "Could Not Allocate An Image Structure\n");
		return FALSE;
    }

	/* Read raw bitmap */
	scanline = image->width * image->numcmpts;			// Size Of A Row (Width * Bytes Per Pixel)
	for( i = 0; i < image->height-1; i++ )				// Loop Through Height (Bottoms Up - Flip Image)
	{
		p = image->data + (i * scanline );				// 
		for ( j = 0; j < image->width ; j++ )			// Loop Through Width
		{
			for ( k = 0 ; k < image->numcmpts-1 ; k++, p++, done++ )
			{
				*p = fgetc(src->hidden.stdio.fp);				// Read Value From File And Store In Memory
			}
			*p = raw_spec ? header.alpha : 255; p++;		// Store 255 In Alpha Channel And Increase Pointer
		}
	}
	
	/* Set Bit masks */
	Rmask = 0x000000FF;
	Gmask = 0x0000FF00;
	Bmask = 0x00FF0000;
	Amask = (raw_spec && header.alpha) ? 0xFF000000 : 0;

	/* Create Surface */
	surface = (SDL_Surface *) SDL_CreateRGBSurfaceFrom((void *) image->data,
			(int) image->width, (int) image->height, (int) image->numcmpts * 8, (int) scanline,
			(Uint32) Rmask, (Uint32) Gmask, (Uint32) Bmask, (Uint32) Amask);
	
	if (image) {
		free(image);												// Free Itself
	}

	return surface;	
}

#else

/* See if an image is contained in a data source */
int IMG_isRAW(SDL_RWops *src)
{
	return TRUE;
}

/* Load a PCX type image from an SDL datasource */
SDL_Surface *IMG_LoadRAW_RW(SDL_RWops *src)
{
	return(NULL);
}

#endif /* LOAD_RAW */

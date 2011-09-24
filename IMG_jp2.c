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
 * A JPEG2000 loader for the SDL library
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
 * Todo: Rewrite code, to speed up loading process, fully implementation of JP2, 
 * extend JP2 core functions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <io.h>

#include "SDL_endian.h"
#include "SDL_image.h"

#define TRUE 1
#define FALSE 0


/******************************************************************************\
* Includes.
\******************************************************************************/

#ifdef LOAD_JP2

typedef struct IMG_Raw
{
	int width;													// Width Of Image In Pixels
	int height;													// Height Of Image In Pixels
	int numcmpts;												// Number Of Components
	unsigned char *data;										// Raw Pixel Data (RGBA)
} IMG_Raw;

#include <jasper/jasper.h>

#include "jasper/jas_types.h"
#include "jasper/jas_stream.h"
#include "jasper/jas_image.h"

#define JP2_BYTES_TO_CHECK	12

#include "jp2_cod.h"
#include "jp2_dec.h"

/* Protoypes */
int IMG_isJP2(SDL_RWops *src);
SDL_Surface *IMG_LoadJP2_RW(const char *file);
SDL_Surface *raw_encode(jas_image_t *image);
jas_image_t *jp2_decode(jas_stream_t *in, char *inopts);

/******************************************************************************\
* Functions.
\******************************************************************************/

/* See if an image is contained in a data source */
int IMG_isJP2(SDL_RWops *src)
{
	char magic[JP2_BYTES_TO_CHECK];

	if ( SDL_RWread(src, magic, 1, JP2_BYTES_TO_CHECK) == JP2_BYTES_TO_CHECK
		 && memcmp(magic, "\0x0000006a5020200d0a870a00",JP2_BYTES_TO_CHECK) == 0
	   ) {
			return TRUE;
	}
	return FALSE;
}

/* Load a JP2 type image from an SDL datasource */
SDL_Surface *IMG_LoadJP2_RW(const char *file)
{
	jas_stream_t *in;
	jas_image_t *image;
	char *inopts="";
	SDL_Surface *surface;
	
	if ( !(in = jas_stream_fopen(file, "rb")) ) {
		fprintf(stderr, "error: cannot open input image file %s\n",
		  file);
		return FALSE;
	}

	if ( !(image = (jas_image_t *) jp2_decode((jas_stream_t*) in, (char*) inopts)) ) {
		fprintf(stderr, "error: cannot load image data\n");
		return FALSE;
	}
	
	if ( !(surface = (SDL_Surface *) raw_encode((jas_image_t *) image)) ) {
		fprintf(stderr, "error: cannot encode image\n");
		return FALSE;
	}
	//jas_stream_flush(out);

	/* If this fails, we don't care. */
	//(void) jas_stream_close(in);

	//jas_image_destroy(image);
	//jas_image_clearfmts();

	return surface;
}


/******************************************************************************\
* Interface functions.
\******************************************************************************/

SDL_Surface *raw_encode(jas_image_t *image)
{
	IMG_Raw *rawimage;
	SDL_Surface *surface;
	jas_matrix_t *cmpts[3];
	unsigned char red, grn, blu, aph, *p;
	Uint32 Rmask, Gmask, Bmask, Amask, datalen;
	Uint16 depth, cmptno;
	int i, j , numpad, scanline, v, stop;
//	bmp_hdr_t hdr;
//	bmp_info_t *info;
	
	rawimage = (IMG_Raw *) malloc(sizeof(IMG_Raw));

	rawimage->numcmpts = jas_image_numcmpts(image); 
	rawimage->width = jas_image_cmptwidth(image, 0);
	rawimage->height = jas_image_cmptheight(image, 0);
	depth = jas_image_cmptprec(image, 0);
	scanline = rawimage->width * (rawimage->numcmpts + 1);

	/* Check to ensure that the image to be saved can actually be represented
	  using the BMP format. */
	for (cmptno = 0; cmptno < rawimage->numcmpts; ++cmptno) {
		if (jas_image_cmptwidth(image, cmptno) != (unsigned) rawimage->width ||
		  jas_image_cmptheight(image, cmptno) != (unsigned) rawimage->height ||
		  jas_image_cmptprec(image, cmptno) != depth ||
		  jas_image_cmptsgnd(image, cmptno) != false ||
		  jas_image_cmpttlx(image, cmptno) != 0 ||
		  jas_image_cmpttly(image, cmptno) != 0) {
			fprintf(stderr, "The BMP format cannot be used to represent an image with this geometry.\n");
			return FALSE;
		}
	}

	/* The component depths must be 1, 4, or 8. */
	if (depth != 1 && depth != 4 && depth != 8) {
		return FALSE;
	}

	numpad = (rawimage->width * rawimage->numcmpts) % 4;
	if (numpad) {
		numpad = 4 - numpad;
	}
	//datalen = (rawimage->numcmpts * rawimage->width + numpad) * rawimage->height;
	datalen = (rawimage->numcmpts + 1) * rawimage->width  * rawimage->height;

	rawimage->data = (void *) malloc(datalen);
/*
	if (!(info = bmp_info_create())) {
		return -1;
	}
	info->len = BMP_INFOLEN;
	info->width = width;
	info->height = height;
	info->numplanes = 1;
	info->depth = numcmpts * depth;
	info->enctype = BMP_ENC_RGB;
	info->siz = datalen;
	info->hres = 0;
	info->vres = 0;
	info->numcolors = (numcmpts == 1) ? 256 : 0;
	info->mincolors = 0;

*/

	/* Write the bitmap data. */
	//if (bmp_putdata(out, info, image)) {
	//	return -1;
	//}

	//numcmpts = (info->depth == 24) ? 3 : 1;

	/* We do not support palettized images. */
	//if (BMP_HASPAL(info) && numcmpts == 3) {
	//	fprintf(stderr, "no palettized image support for BMP format\n");
	//	return FALSE;
	//}

	for (i = 0; i < rawimage->numcmpts; ++i) {
		cmpts[i] = 0;
	}

	/* Create temporary matrices to hold component data. */
	for (i = 0; i < rawimage->numcmpts; ++i) {
		if (!(cmpts[i] = jas_matrix_create(1, rawimage->width))) {
			stop = TRUE;
		}
	}

	/* Calculate number of padding bytes per row of image data. */
	numpad = (rawimage->numcmpts * rawimage->width) % 4;
	if (numpad) {
		numpad = 4 - numpad;
	}

	/* Put the image data. */
	for (i = rawimage->height - 1 ; i >= 0; --i) {
		p = rawimage->data + (i * scanline);
		for (cmptno = 0; cmptno < rawimage->numcmpts; ++cmptno) {
			if (jas_image_readcmpt(image, cmptno, 0, i, rawimage->width,
			  1, cmpts[cmptno])) {
				stop = TRUE;
			}
		}
		for (j = 0; j < rawimage->width - 1; ++j) {
			if (rawimage->numcmpts == 3) {
				red = (jas_matrix_getv(cmpts[0], j));
				grn = (jas_matrix_getv(cmpts[1], j));
				blu = (jas_matrix_getv(cmpts[2], j));
				aph = 255;
				*p = red; p++;
				*p = grn; p++;
				*p = blu; p++;
				*p = 255; p++;

			} else if (rawimage->numcmpts == 1) {
				v = (jas_matrix_getv(cmpts[0], j));
				p+=4; *p = v;
			} else {
				stop = TRUE;
			}
		}
		for (j = numpad; j > 0; --j, p++) {
			*p = 0;
		}
	}

	/* Destroy the temporary matrices. */
	for (i = 0; i < rawimage->numcmpts; ++i) {
		if (cmpts[i]) {
			jas_matrix_destroy(cmpts[i]);
		}
	}

	/* Set Bit masks */
	Rmask = 0x000000FF;
	Gmask = 0x0000FF00;
	Bmask = 0x00FF0000;
	Amask = 0xFF000000;

	/* Create Surface */
	surface = (SDL_Surface *) SDL_CreateRGBSurfaceFrom((void *) rawimage->data,
			(int) rawimage->width-1, (int) rawimage->height-1, (int) (rawimage->numcmpts+1) * 8, (int) scanline,
			(Uint32) Rmask, (Uint32) Gmask, (Uint32) Bmask, (Uint32) Amask);

	return surface;
}

#else

/* See if an image is contained in a data source */
int IMG_isJP2(SDL_RWops *src)
{
	return(FALSE);
}

/* Load a JP2 type image from an SDL datasource */
SDL_Surface *IMG_LoadJP2_RW(SDL_RWops *src)
{
	return(NULL);
}

#endif /* LOAD_JP2 */

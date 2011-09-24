 /*
 * A RAS loader for the SDL library
 * Supports: Reading 8, 15, 16, 24 and 32bpp images, with alpha or colourkey,
 *           uncompressed or RLE encoded.
 *
 * 2001- Lorenz Sauer <lorenz_sauer@gmx.at>: initial version
 */
/*
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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL_endian.h"
#include "SDL_image.h"



/******************************************************************************\
* Includes.
\******************************************************************************/

#ifdef LOAD_RAS

#include "jasper/jas_image.h"
#include "jasper/jas_stream.h"
#include "jasper/jas_math.h"
#include "jasper/jas_debug.h"
#include "jasper/jas_malloc.h"
#include "jasper/jas_version.h"

#include "jp2_cod.h"
#include "jp2_dec.h"

#define	JP2_VALIDATELEN	(JAS_MIN(JP2_JP_LEN + 16, JAS_STREAM_MAXPUTBACK))

static jp2_dec_t *jp2_dec_create(void);
static void jp2_dec_destroy(jp2_dec_t *dec);

/******************************************************************************\
* Functions.
\******************************************************************************/

#define JP2_BYTES_TO_CHECK	12
#define JP2_BYTES_MAGIC		0x0000006a5020200d0a870a00

/* See if an image is contained in a data source */
int IMG_isJP2(SDL_RWops *src)
{
	int is_JP2;
	char magic[JP2_BYTES_TO_CHECK];

	is_JP2 = 0;
	if ( SDL_RWread(src, magic, JP2_BYTES_TO_CHECK, 1) ) {
		if ( (memcmp(magic, JP2_BYTES_MAGIC, JP2_BYTES_TO_CHECK) == 0) {
			is_JP2 = 1;
		}
	}
	return(is_JP2);
}

/* Load a JP2 type image from an SDL datasource */
SDL_Surface *IMG_LoadJP2_RW(SDL_RWops *src)
{
	fclose(src);
	char *optstr = "";
	//jas_image_t *jp2_decode(jas_stream_t *in, char *optstr){
	SDL_Surface *img;
	jp2_box_t *box;
	int found;
	jas_image_t *image;
	jp2_dec_t *dec;

	dec = 0;
	box = 0;

	if (!(dec = jp2_dec_create())) {
		goto error;
	}

	//fprintf(stderr, "%s", JAS_JP2DISCLAIMER);

	/* Get the first box.  This should be a JP box. */

	if (!(box = jp2_box_get(in))) {
		goto error;
	}
	if (box->type != JP2_BOX_JP) {
		fprintf(stderr, "expecting signature box\n");
		goto error;
	}
	if (box->data.jp.magic != JP2_JP_MAGIC) {
		fprintf(stderr, "incorrect magic number\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	/* Get the second box.  This should be a FTYP box. */
	if (!(box = jp2_box_get(in))) {
		goto error;
	}
	if (box->type != JP2_BOX_FTYP) {
		fprintf(stderr, "expecting file type box\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	found = 0;
	while ((box = jp2_box_get(in))) {
		if (jas_getdbglevel() >= 1) {
			fprintf(stderr, "box type %s\n", box->info->name);
		}
		switch (box->type) {
		case JP2_BOX_JP2C:
			found = 1;
			break;
		case JP2_BOX_IHDR:
			if (!dec->ihdr) {
				dec->ihdr = box;
				box = 0;
			}
			break;
		case JP2_BOX_BPCC:
			if (!dec->bpcc) {
				dec->bpcc = box;
				box = 0;
			}
			break;
		case JP2_BOX_CDEF:
			if (!dec->cdef) {
				dec->cdef = box;
				box = 0;
			}
			break;
		case JP2_BOX_PCLR:
			if (!dec->pclr) {
				dec->pclr = box;
				box = 0;
			}
			break;
		}
		if (box) {
			jp2_box_destroy(box);
			box = 0;
		}
		if (found) {
			break;
		}
	}

	if (!found) {
		fprintf(stderr, "no code stream\n");
		goto error;
	}

	if (!(image = jpc_decode(in, optstr))) {
		goto error;
	}

	if (dec->cdef) {
		jas_eprintf("warning: CDEF box has been ignored\n");
		if (jas_image_numcmpts(image) > 1) {
			jas_eprintf("The components may be incorrectly permuted.\n");
		}
	}
	if (dec->pclr) {
		jas_eprintf("warning: PCLR box has been ignored\n");
	}

	jp2_dec_destroy(dec);

	return image;

error:
	if (box) {
		jp2_box_destroy(box);
	}
	if (dec) {
		jp2_dec_destroy(dec);
	}
    //IMG_SetError("Error reading TGA data");
    return NULL;
}

static jp2_dec_t *jp2_dec_create(void)
{
	jp2_dec_t *dec;

	if (!(dec = malloc(sizeof(jp2_dec_t)))) {
		return 0;
	}
	dec->ihdr = 0;
	dec->bpcc = 0;
	dec->cdef = 0;
	dec->pclr = 0;
	return dec;
}

static void jp2_dec_destroy(jp2_dec_t *dec)
{
	if (dec->ihdr) {
		jp2_box_destroy(dec->ihdr);
	}
	if (dec->bpcc) {
		jp2_box_destroy(dec->bpcc);
	}
	if (dec->cdef) {
		jp2_box_destroy(dec->cdef);
	}
	if (dec->cdef) {
		jp2_box_destroy(dec->pclr);
	}
	jas_free(dec);
}
#else

/* See if an image is contained in a data source */
int IMG_isRAS(SDL_RWops *src)
{
	return(0);
}

/* Load a JP2 type image from an SDL datasource */
SDL_Surface *IMG_LoadRAS_RW(SDL_RWops *src)
{
	return(NULL);
}

#endif /* LOAD_JP2 */






author: lo sauer, 2001
based on SDL_image code written by Sam Lantinga, and the Jasper Jpeg2000 library.

Description: the program displays images which are rendered on an SDL surface.
The library supports, JK2, JP2, RAW, EPS, MIF and
BMP, PNM (PPM/PGM/PBM), XPM, LBM, PCX, GIF, JPEG, PNG, TGA, and TIFF formats.

=== Getting Started ===
  * compile the program
  * Windows-users can use the windows executable in the showimage folder
  * start showimage and pass as argument the name of the image file showimage <image_file>
  e.g. showimage "examplePics/7sisters.jp2"
  * clicking on the SDL surface will close it and exit the program

  * copyrights of the included pictures: Ericsson

=== Notes ===
  Implementing motion picture support is quite straightforward. To do so add the corresponding container-format decoder library
  and update the SDL canvas according to the movie's native framerate.

=== TODO:: ===
  * update the codebase
  * implement WebP

showimage

See here for more information on SDL:
http://www.libsdl.org/



---------
SDL-IMAGE:

API:
#include "SDL_image.h"

	SDL_Surface *IMG_Load(const char *file);
or
	SDL_Surface *IMG_Load_RW(SDL_RWops *src, int freesrc);
or
	SDL_Surface *IMG_LoadTyped_RW(SDL_RWops *src, int freesrc, char *type);

where type is a string specifying the format (i.e. "PNG" or "pcx").
Note that IMG_Load_RW cannot load TGA images.

To create a surface from an XPM image included in C source, use:

	SDL_Surface *IMG_ReadXPMFromArray(char **xpm);

An example program 'showimage' is included, with source in showimage.c

JPEG support requires the JPEG library: http://www.ijg.org/
PNG support requires the PNG library: http://www.libpng.org/pub/png/libpng.html
    and the Zlib library: http://www.gzip.org/zlib/
TIFF support requires the TIFF library: ftp://ftp.sgi.com/graphics/tiff/

This library is under the GNU Library General Public License, see the file
"COPYING" for details.  Certain image loaders may be under a different
license, see the individual image loader source files for details.  
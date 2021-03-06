### JPEG2000 SDL-IMAGE Viewer 
**author**: lo sauer, 2001 - lsauer.com
based on SDL_image code written by Sam Lantinga, and the Jasper Jpeg2000 library.
<img src="https://lh6.googleusercontent.com/-X8gF5OiNkCQ/UpBlxKMIukI/AAAAAAAACzQ/0z0LD5rrbSg/w100-h50-no/product_sm_sdl_logo.gif">  

Description: the program displays images which are rendered on an SDL surface.
The library supports, JK2, JP2, RAW, EPS, MIF and
BMP, PNM (PPM/PGM/PBM), XPM, LBM, PCX, GIF, JPEG, PNG, TGA, and TIFF formats.

### Getting Started 
 * compile the program
 
 * Windows-users can use the windows executable in the showimage folder
 
 * start showimage and pass as argument the name of the image file showimage <image_file>
  e.g. showimage "examplePics/7sisters.jp2"
  
 * clicking on the SDL surface will close it and exit the program

 * copyrights of the included pictures: Ericsson

### Examples

<img src="https://lh5.googleusercontent.com/-BiySKZnaEwI/UpBlo07cyPI/AAAAAAAACy8/SU_Sczu6XSY/w668-h329-no/sdl_jpeg2000_jp2_lsauer-lorenz-lo-sauer-techshot_3.jpg">

##### Encoding  
<table><tr><td><b>before</b></td><td><b>after</b></td></tr>
<tr><tr><td>
<img src="https://lh5.googleusercontent.com/-ufDbmhwNn70/UpBlozW2Y6I/AAAAAAAACzE/Y4wyz8BtfG4/w350-no/sdl_jpeg2000_jp2_lsauer-lorenz-lo-sauer-techshot_1.jpg">
</td><td>
<img src="https://lh5.googleusercontent.com/-5rzt-tF4_Go/UpBlo5ohypI/AAAAAAAACzI/yCGEQ45tZRA/w350-no/sdl_jpeg2000_jp2_lsauer-lorenz-lo-sauer-techshot_2.jpg">
</td></tr></table>
### Installing as an image viewer
 * In windows, right click on the image file to be opened and select 'open with'
 * In the file association windows click Browse at the bottom right
 * Select the showimage application
 * Now for instance each time you double click/enter an associated image file type showimage will
   render it (e.g. *.jp2, *.raw...)

### Notes
 * Implementing motion picture support is quite straightforward. To do so add the corresponding container-format decoder library
  and update the SDL canvas according to the movie's native framerate.

### TODO
 * update the codebase
 
 * implement Google's WebP


### OTHER
See here for more information on SDL:
http://www.libsdl.org/

-----

###SDL-IMAGE:

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

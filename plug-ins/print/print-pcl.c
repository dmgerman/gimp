begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * "$Id$"  *  *   Print plug-in HP PCL driver for the GIMP.  *  *   Copyright 1997-1998 Michael Sweet (mike@easysw.com)  *  *   This program is free software; you can redistribute it and/or modify it  *   under the terms of the GNU General Public License as published by the Free  *   Software Foundation; either version 2 of the License, or (at your option)  *   any later version.  *  *   This program is distributed in the hope that it will be useful, but  *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  *   for more details.  *  *   You should have received a copy of the GNU General Public License  *   along with this program; if not, write to the Free Software  *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  * Contents:  *  *   pcl_print() - Print an image to an HP printer.  *   pcl_mode0() - Send PCL graphics using mode 0 (no) compression.  *   pcl_mode2() - Send PCL graphics using mode 2 (TIFF) compression.  *  * Revision History:  *  *   $Log$  *   Revision 1.3  1998/03/19 02:11:41  adrian  *    *AlienMap/AlienMap.c CEL/CEL.c CML_explorer/CML_explorer.c  *           align_layers/align_layers.c animationplay/animationplay.c  *           bmp/bmpwrite.c dbbrowser/dbbrowser.c emboss/emboss.c  *           exchange/exchange.c faxg3/faxg3.c faxg3/g3.c gbr/gbr.c  *           gif/gif.c gqbist/gqbist.c hot/hot.c ifscompose/ifscompose.c  *           iwarp/iwarp.c max_rgb/max_rgb.c maze/maze_face.c  *           megawidget/megawidget.c mpeg/mpeg.c nlfilt/nlfilt.c pcx/pcx.c  *           plasma/plasma.c pnm/pnm.c print/print-escp2.c  *           print/print-pcl.c print/print.c scatter_hsv/scatter_hsv.c  *           script-fu/script-fu-scripts.c script-fu/script-fu.c  *           sinus/sinus.c tga/tga.c tileit/tileit.c  *           vpropagate/vpropagate.c xpm/xpm.c:  More picky picky ansi type  *           stuff from gimp-hpux-980316.patch.  *  *   	isnt big patches fun?  *  *   -adrian  *  *   Revision 1.2  1998/01/25 09:29:26  yosh  *   Plugin updates  *   Properly generated aa Makefile (still not built by default)  *   Sven's no args script patch  *  *   -Yosh  *  *   Revision 1.8  1998/01/21  21:33:47  mike  *   Updated copyright.  *  *   Revision 1.7  1997/11/12  15:57:48  mike  *   Minor changes for clean compiles under Digital UNIX.  *  *   Revision 1.7  1997/11/12  15:57:48  mike  *   Minor changes for clean compiles under Digital UNIX.  *  *   Revision 1.6  1997/10/02  17:57:26  mike  *   Updated positioning code to use "decipoint" commands.  *  *   Revision 1.5  1997/07/30  20:33:05  mike  *   Final changes for 1.1 release.  *  *   Revision 1.4  1997/07/30  18:47:39  mike  *   Added scaling, orientation, and offset options.  *  *   Revision 1.3  1997/07/03  13:24:12  mike  *   Updated documentation for 1.0 release.  *  *   Revision 1.2  1997/07/02  18:48:14  mike  *   Added mode 2 compression code.  *   Fixed bug in pcl_mode0 and pcl_mode2 - wasn't sending 'V' or 'W' at  *   the right times.  *  *   Revision 1.2  1997/07/02  18:48:14  mike  *   Added mode 2 compression code.  *   Fixed bug in pcl_mode0 and pcl_mode2 - wasn't sending 'V' or 'W' at  *   the right times.  *  *   Revision 1.1  1997/07/02  13:51:53  mike  *   Initial revision  */
end_comment

begin_include
include|#
directive|include
file|"print.h"
end_include

begin_comment
comment|/*  * Local functions...  */
end_comment

begin_function_decl
specifier|static
name|void
name|pcl_mode0
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pcl_mode2
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * 'pcl_print()' - Print an image to an HP printer.  */
end_comment

begin_function
name|void
DECL|function|pcl_print (FILE * prn,GDrawable * drawable,int media_size,int xdpi,int ydpi,int output_type,int model,guchar * lut,guchar * cmap,int orientation,int scaling,int left,int top)
name|pcl_print
parameter_list|(
name|FILE
modifier|*
name|prn
parameter_list|,
comment|/* I - Print file or command */
name|GDrawable
modifier|*
name|drawable
parameter_list|,
comment|/* I - Image to print */
name|int
name|media_size
parameter_list|,
comment|/* I - Output size */
name|int
name|xdpi
parameter_list|,
comment|/* I - Horizontal resolution */
name|int
name|ydpi
parameter_list|,
comment|/* I - Vertical resolution */
name|int
name|output_type
parameter_list|,
comment|/* I - Color or grayscale? */
name|int
name|model
parameter_list|,
comment|/* I - Model of printer */
name|guchar
modifier|*
name|lut
parameter_list|,
comment|/* I - Brightness lookup table */
name|guchar
modifier|*
name|cmap
parameter_list|,
comment|/* I - Colormap (for indexed images) */
name|int
name|orientation
parameter_list|,
comment|/* I - Orientation of image */
name|int
name|scaling
parameter_list|,
comment|/* I - Scaling of image */
name|int
name|left
parameter_list|,
comment|/* I - Left offset of image (10ths) */
name|int
name|top
parameter_list|)
comment|/* I - Top offset of image (10ths) */
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/* Looping vars */
name|GPixelRgn
name|rgn
decl_stmt|;
comment|/* Image region */
name|unsigned
name|char
modifier|*
name|in
decl_stmt|,
comment|/* Input pixels */
modifier|*
name|out
decl_stmt|,
comment|/* Output pixels */
modifier|*
name|black
decl_stmt|,
comment|/* Black bitmap data */
modifier|*
name|cyan
decl_stmt|,
comment|/* Cyan bitmap data */
modifier|*
name|magenta
decl_stmt|,
comment|/* Magenta bitmap data */
modifier|*
name|yellow
decl_stmt|;
comment|/* Yellow bitmap data */
name|int
name|page_width
decl_stmt|,
comment|/* Width of page */
name|page_height
decl_stmt|,
comment|/* Height of page */
name|out_width
decl_stmt|,
comment|/* Width of image on page */
name|out_height
decl_stmt|,
comment|/* Height of image on page */
name|out_bpp
decl_stmt|,
comment|/* Output bytes per pixel */
name|temp_width
decl_stmt|,
comment|/* Temporary width of image on page */
name|temp_height
decl_stmt|,
comment|/* Temporary height of image on page */
name|landscape
decl_stmt|,
comment|/* True if we rotate the output 90 degrees */
name|length
decl_stmt|,
comment|/* Length of raster data */
name|errdiv
decl_stmt|,
comment|/* Error dividend */
name|errmod
decl_stmt|,
comment|/* Error modulus */
name|errval
decl_stmt|,
comment|/* Current error value */
name|errline
decl_stmt|,
comment|/* Current raster line */
name|errlast
decl_stmt|;
comment|/* Last raster line loaded */
name|convert_t
name|colorfunc
decl_stmt|;
comment|/* Color conversion function... */
name|void
function_decl|(
modifier|*
name|writefunc
function_decl|)
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
comment|/* PCL output function */
comment|/*   * Setup a read-only pixel region for the entire image...   */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*   * Choose the correct color conversion function...   */
if|if
condition|(
operator|(
name|drawable
operator|->
name|bpp
operator|<
literal|3
operator|&&
name|cmap
operator|==
name|NULL
operator|)
operator|||
name|model
operator|<=
literal|500
condition|)
name|output_type
operator|=
name|OUTPUT_GRAY
expr_stmt|;
comment|/* Force grayscale output */
if|if
condition|(
name|output_type
operator|==
name|OUTPUT_COLOR
condition|)
block|{
name|out_bpp
operator|=
literal|3
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|bpp
operator|>=
literal|3
condition|)
name|colorfunc
operator|=
name|rgb_to_rgb
expr_stmt|;
else|else
name|colorfunc
operator|=
name|indexed_to_rgb
expr_stmt|;
if|if
condition|(
name|model
operator|==
literal|800
condition|)
name|xdpi
operator|=
name|ydpi
operator|=
literal|300
expr_stmt|;
block|}
else|else
block|{
name|out_bpp
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|bpp
operator|>=
literal|3
condition|)
name|colorfunc
operator|=
name|rgb_to_gray
expr_stmt|;
elseif|else
if|if
condition|(
name|cmap
operator|==
name|NULL
condition|)
name|colorfunc
operator|=
name|gray_to_gray
expr_stmt|;
else|else
name|colorfunc
operator|=
name|indexed_to_gray
expr_stmt|;
block|}
empty_stmt|;
comment|/*   * Compute the output size...   */
name|landscape
operator|=
literal|0
expr_stmt|;
name|page_width
operator|=
name|media_width
argument_list|(
name|media_size
argument_list|,
name|xdpi
argument_list|)
expr_stmt|;
name|page_height
operator|=
name|media_height
argument_list|(
name|media_size
argument_list|,
name|ydpi
argument_list|)
expr_stmt|;
comment|/*   * Portrait width/height...   */
name|out_width
operator|=
name|page_width
operator|*
name|scaling
operator|/
literal|100
expr_stmt|;
name|out_height
operator|=
name|out_width
operator|*
name|ydpi
operator|/
name|xdpi
operator|*
name|drawable
operator|->
name|height
operator|/
name|drawable
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|out_height
operator|>
name|page_height
condition|)
block|{
name|out_height
operator|=
name|page_height
expr_stmt|;
name|out_width
operator|=
name|out_height
operator|*
name|xdpi
operator|/
name|ydpi
operator|*
name|drawable
operator|->
name|width
operator|/
name|drawable
operator|->
name|height
expr_stmt|;
block|}
empty_stmt|;
comment|/*   * Landscape width/height...   */
name|temp_width
operator|=
name|page_width
operator|*
name|scaling
operator|/
literal|100
expr_stmt|;
name|temp_height
operator|=
name|temp_width
operator|*
name|ydpi
operator|/
name|xdpi
operator|*
name|drawable
operator|->
name|width
operator|/
name|drawable
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|temp_height
operator|>
name|page_height
condition|)
block|{
name|temp_height
operator|=
name|page_height
expr_stmt|;
name|temp_width
operator|=
name|temp_height
operator|*
name|xdpi
operator|/
name|ydpi
operator|*
name|drawable
operator|->
name|height
operator|/
name|drawable
operator|->
name|width
expr_stmt|;
block|}
empty_stmt|;
comment|/*   * See which orientation has the greatest area...   */
if|if
condition|(
operator|(
name|temp_width
operator|*
name|temp_height
operator|)
operator|>
operator|(
name|out_width
operator|*
name|out_height
operator|)
operator|&&
name|orientation
operator|!=
name|ORIENT_PORTRAIT
condition|)
block|{
name|out_width
operator|=
name|temp_width
expr_stmt|;
name|out_height
operator|=
name|temp_height
expr_stmt|;
name|landscape
operator|=
literal|1
expr_stmt|;
comment|/*     * Swap left/top offsets...     */
name|x
operator|=
name|top
expr_stmt|;
name|top
operator|=
name|left
expr_stmt|;
name|left
operator|=
name|x
expr_stmt|;
block|}
empty_stmt|;
comment|/*   * Let the user know what we're doing...   */
name|gimp_progress_init
argument_list|(
literal|"Printing..."
argument_list|)
expr_stmt|;
comment|/*   * Send PCL initialization commands...   */
name|fputs
argument_list|(
literal|"\033E"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* PCL reset */
switch|switch
condition|(
name|media_size
condition|)
comment|/* Set media size... */
block|{
case|case
name|MEDIA_LETTER
case|:
name|fputs
argument_list|(
literal|"\033&l2A"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
break|break;
case|case
name|MEDIA_LEGAL
case|:
name|fputs
argument_list|(
literal|"\033&l3A"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
break|break;
case|case
name|MEDIA_TABLOID
case|:
name|fputs
argument_list|(
literal|"\033&l6A"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
break|break;
case|case
name|MEDIA_A4
case|:
name|fputs
argument_list|(
literal|"\033&l26A"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
break|break;
case|case
name|MEDIA_A3
case|:
name|fputs
argument_list|(
literal|"\033&l27A"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
break|break;
block|}
empty_stmt|;
if|if
condition|(
name|xdpi
operator|!=
name|ydpi
condition|)
comment|/* Set resolution */
block|{
comment|/*     * Send 26-byte configure image data command with horizontal and     * vertical resolutions as well as a color count...     */
name|fputs
argument_list|(
literal|"\033*g26W"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|2
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Format 2 */
if|if
condition|(
name|output_type
operator|==
name|OUTPUT_COLOR
condition|)
name|putc
argument_list|(
literal|4
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* # output planes */
else|else
name|putc
argument_list|(
literal|1
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* # output planes */
name|putc
argument_list|(
name|xdpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Black resolution */
name|putc
argument_list|(
name|xdpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|0
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|2
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* # of black levels */
name|putc
argument_list|(
name|xdpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Cyan resolution */
name|putc
argument_list|(
name|xdpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|0
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|2
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* # of cyan levels */
name|putc
argument_list|(
name|xdpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Magenta resolution */
name|putc
argument_list|(
name|xdpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|0
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|2
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* # of magenta levels */
name|putc
argument_list|(
name|xdpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Yellow resolution */
name|putc
argument_list|(
name|xdpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
operator|>>
literal|8
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
name|ydpi
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|0
argument_list|,
name|prn
argument_list|)
expr_stmt|;
name|putc
argument_list|(
literal|2
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* # of yellow levels */
block|}
else|else
block|{
name|fprintf
argument_list|(
name|prn
argument_list|,
literal|"\033*t%dR"
argument_list|,
name|xdpi
argument_list|)
expr_stmt|;
comment|/* Simple resolution */
if|if
condition|(
name|output_type
operator|==
name|OUTPUT_COLOR
condition|)
block|{
if|if
condition|(
name|model
operator|==
literal|501
operator|||
name|model
operator|==
literal|1200
condition|)
name|fputs
argument_list|(
literal|"\033*r-3U"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Simple CMY color */
else|else
name|fputs
argument_list|(
literal|"\033*r-4U"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Simple KCMY color */
block|}
empty_stmt|;
block|}
empty_stmt|;
if|if
condition|(
name|model
operator|<
literal|3
operator|||
name|model
operator|==
literal|500
condition|)
name|fputs
argument_list|(
literal|"\033*b0M"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Mode 0 (no compression) */
else|else
name|fputs
argument_list|(
literal|"\033*b2M"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Mode 2 (TIFF) */
if|if
condition|(
name|left
operator|<
literal|0
operator|||
name|top
operator|<
literal|0
condition|)
block|{
name|left
operator|=
operator|(
name|page_width
operator|-
name|out_width
operator|)
operator|/
literal|2
expr_stmt|;
name|top
operator|=
operator|(
name|page_height
operator|-
name|out_height
operator|)
operator|/
literal|2
expr_stmt|;
block|}
else|else
block|{
name|left
operator|*=
literal|30
expr_stmt|;
name|top
operator|*=
literal|30
expr_stmt|;
block|}
empty_stmt|;
name|fprintf
argument_list|(
name|prn
argument_list|,
literal|"\033&a%dH"
argument_list|,
literal|720
operator|*
name|left
operator|/
name|xdpi
argument_list|)
expr_stmt|;
comment|/* Set left raster position */
name|fprintf
argument_list|(
name|prn
argument_list|,
literal|"\033&a%dV"
argument_list|,
literal|720
operator|*
name|top
operator|/
name|ydpi
argument_list|)
expr_stmt|;
comment|/* Set top raster position */
name|fprintf
argument_list|(
name|prn
argument_list|,
literal|"\033*r%dS"
argument_list|,
name|out_width
argument_list|)
expr_stmt|;
comment|/* Set raster width */
name|fprintf
argument_list|(
name|prn
argument_list|,
literal|"\033*r%dT"
argument_list|,
name|out_height
argument_list|)
expr_stmt|;
comment|/* Set raster height */
name|fputs
argument_list|(
literal|"\033*r1A"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Start GFX */
comment|/*   * Allocate memory for the raster data...   */
name|length
operator|=
operator|(
name|out_width
operator|+
literal|7
operator|)
operator|/
literal|8
expr_stmt|;
if|if
condition|(
name|output_type
operator|==
name|OUTPUT_GRAY
condition|)
block|{
name|black
operator|=
name|g_malloc
argument_list|(
name|length
argument_list|)
expr_stmt|;
name|cyan
operator|=
name|NULL
expr_stmt|;
name|magenta
operator|=
name|NULL
expr_stmt|;
name|yellow
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|cyan
operator|=
name|g_malloc
argument_list|(
name|length
argument_list|)
expr_stmt|;
name|magenta
operator|=
name|g_malloc
argument_list|(
name|length
argument_list|)
expr_stmt|;
name|yellow
operator|=
name|g_malloc
argument_list|(
name|length
argument_list|)
expr_stmt|;
if|if
condition|(
name|model
operator|!=
literal|501
operator|&&
name|model
operator|!=
literal|1200
condition|)
name|black
operator|=
name|g_malloc
argument_list|(
name|length
argument_list|)
expr_stmt|;
else|else
name|black
operator|=
name|NULL
expr_stmt|;
block|}
empty_stmt|;
comment|/*   * Output the page, rotating as necessary...   */
if|if
condition|(
name|model
operator|<
literal|3
operator|||
name|model
operator|==
literal|500
condition|)
name|writefunc
operator|=
name|pcl_mode0
expr_stmt|;
else|else
name|writefunc
operator|=
name|pcl_mode2
expr_stmt|;
if|if
condition|(
name|landscape
condition|)
block|{
name|in
operator|=
name|g_malloc
argument_list|(
name|drawable
operator|->
name|height
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|out
operator|=
name|g_malloc
argument_list|(
name|drawable
operator|->
name|height
operator|*
name|out_bpp
argument_list|)
expr_stmt|;
name|errdiv
operator|=
name|drawable
operator|->
name|width
operator|/
name|out_height
expr_stmt|;
name|errmod
operator|=
name|drawable
operator|->
name|width
operator|%
name|out_height
expr_stmt|;
name|errval
operator|=
literal|0
expr_stmt|;
name|errlast
operator|=
operator|-
literal|1
expr_stmt|;
name|errline
operator|=
name|drawable
operator|->
name|width
operator|-
literal|1
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|out_height
condition|;
name|x
operator|++
control|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"pcl_print: x = %d, line = %d, val = %d, mod = %d, height = %d\n"
argument_list|,
name|x
argument_list|,
name|errline
argument_list|,
name|errval
argument_list|,
name|errmod
argument_list|,
name|out_height
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
if|if
condition|(
operator|(
name|x
operator|&
literal|255
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|x
operator|/
operator|(
name|double
operator|)
name|out_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|errline
operator|!=
name|errlast
condition|)
block|{
name|errlast
operator|=
name|errline
expr_stmt|;
name|gimp_pixel_rgn_get_col
argument_list|(
operator|&
name|rgn
argument_list|,
name|in
argument_list|,
name|errline
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
call|(
modifier|*
name|colorfunc
call|)
argument_list|(
name|in
argument_list|,
name|out
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|drawable
operator|->
name|bpp
argument_list|,
name|lut
argument_list|,
name|cmap
argument_list|)
expr_stmt|;
if|if
condition|(
name|output_type
operator|==
name|OUTPUT_GRAY
condition|)
block|{
name|dither_black
argument_list|(
name|out
argument_list|,
name|x
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|out_width
argument_list|,
name|black
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|black
argument_list|,
name|length
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dither_cmyk
argument_list|(
name|out
argument_list|,
name|x
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|out_width
argument_list|,
name|cyan
argument_list|,
name|magenta
argument_list|,
name|yellow
argument_list|,
name|black
argument_list|)
expr_stmt|;
if|if
condition|(
name|black
operator|!=
name|NULL
condition|)
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|black
argument_list|,
name|length
argument_list|,
literal|0
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|cyan
argument_list|,
name|length
argument_list|,
literal|0
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|magenta
argument_list|,
name|length
argument_list|,
literal|0
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|yellow
argument_list|,
name|length
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
name|errval
operator|+=
name|errmod
expr_stmt|;
name|errline
operator|-=
name|errdiv
expr_stmt|;
if|if
condition|(
name|errval
operator|>=
name|out_height
condition|)
block|{
name|errval
operator|-=
name|out_height
expr_stmt|;
name|errline
operator|--
expr_stmt|;
block|}
empty_stmt|;
block|}
empty_stmt|;
block|}
else|else
block|{
name|in
operator|=
name|g_malloc
argument_list|(
name|drawable
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|out
operator|=
name|g_malloc
argument_list|(
name|drawable
operator|->
name|width
operator|*
name|out_bpp
argument_list|)
expr_stmt|;
name|errdiv
operator|=
name|drawable
operator|->
name|height
operator|/
name|out_height
expr_stmt|;
name|errmod
operator|=
name|drawable
operator|->
name|height
operator|%
name|out_height
expr_stmt|;
name|errval
operator|=
literal|0
expr_stmt|;
name|errlast
operator|=
operator|-
literal|1
expr_stmt|;
name|errline
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|out_height
condition|;
name|y
operator|++
control|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"pcl_print: y = %d, line = %d, val = %d, mod = %d, height = %d\n"
argument_list|,
name|y
argument_list|,
name|errline
argument_list|,
name|errval
argument_list|,
name|errmod
argument_list|,
name|out_height
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
if|if
condition|(
operator|(
name|y
operator|&
literal|255
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
operator|(
name|double
operator|)
name|out_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|errline
operator|!=
name|errlast
condition|)
block|{
name|errlast
operator|=
name|errline
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|rgn
argument_list|,
name|in
argument_list|,
literal|0
argument_list|,
name|errline
argument_list|,
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
call|(
modifier|*
name|colorfunc
call|)
argument_list|(
name|in
argument_list|,
name|out
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|bpp
argument_list|,
name|lut
argument_list|,
name|cmap
argument_list|)
expr_stmt|;
if|if
condition|(
name|output_type
operator|==
name|OUTPUT_GRAY
condition|)
block|{
name|dither_black
argument_list|(
name|out
argument_list|,
name|y
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|out_width
argument_list|,
name|black
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|black
argument_list|,
name|length
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dither_cmyk
argument_list|(
name|out
argument_list|,
name|y
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|out_width
argument_list|,
name|cyan
argument_list|,
name|magenta
argument_list|,
name|yellow
argument_list|,
name|black
argument_list|)
expr_stmt|;
if|if
condition|(
name|black
operator|!=
name|NULL
condition|)
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|black
argument_list|,
name|length
argument_list|,
literal|0
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|cyan
argument_list|,
name|length
argument_list|,
literal|0
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|magenta
argument_list|,
name|length
argument_list|,
literal|0
argument_list|)
expr_stmt|;
call|(
modifier|*
name|writefunc
call|)
argument_list|(
name|prn
argument_list|,
name|yellow
argument_list|,
name|length
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
name|errval
operator|+=
name|errmod
expr_stmt|;
name|errline
operator|+=
name|errdiv
expr_stmt|;
if|if
condition|(
name|errval
operator|>=
name|out_height
condition|)
block|{
name|errval
operator|-=
name|out_height
expr_stmt|;
name|errline
operator|++
expr_stmt|;
block|}
empty_stmt|;
block|}
empty_stmt|;
block|}
empty_stmt|;
comment|/*   * Cleanup...   */
name|g_free
argument_list|(
name|in
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|out
argument_list|)
expr_stmt|;
if|if
condition|(
name|black
operator|!=
name|NULL
condition|)
name|g_free
argument_list|(
name|black
argument_list|)
expr_stmt|;
if|if
condition|(
name|cyan
operator|!=
name|NULL
condition|)
block|{
name|g_free
argument_list|(
name|cyan
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|magenta
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|yellow
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
switch|switch
condition|(
name|model
condition|)
comment|/* End raster graphics */
block|{
case|case
literal|1
case|:
case|case
literal|2
case|:
case|case
literal|3
case|:
case|case
literal|500
case|:
name|fputs
argument_list|(
literal|"\033*rB"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
break|break;
default|default :
name|fputs
argument_list|(
literal|"\033*rbC"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
break|break;
block|}
empty_stmt|;
name|fputs
argument_list|(
literal|"\033&l0H"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* Eject page */
name|fputs
argument_list|(
literal|"\033E"
argument_list|,
name|prn
argument_list|)
expr_stmt|;
comment|/* PCL reset */
block|}
end_function

begin_comment
comment|/*  * 'pcl_mode0()' - Send PCL graphics using mode 0 (no) compression.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pcl_mode0 (FILE * prn,unsigned char * line,int length,int last_plane)
name|pcl_mode0
parameter_list|(
name|FILE
modifier|*
name|prn
parameter_list|,
comment|/* I - Print file or command */
name|unsigned
name|char
modifier|*
name|line
parameter_list|,
comment|/* I - Output bitmap data */
name|int
name|length
parameter_list|,
comment|/* I - Length of bitmap data */
name|int
name|last_plane
parameter_list|)
comment|/* I - True if this is the last plane */
block|{
name|fprintf
argument_list|(
name|prn
argument_list|,
literal|"\033*b%d%c"
argument_list|,
name|length
argument_list|,
name|last_plane
condition|?
literal|'W'
else|:
literal|'V'
argument_list|)
expr_stmt|;
name|fwrite
argument_list|(
name|line
argument_list|,
name|length
argument_list|,
literal|1
argument_list|,
name|prn
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * 'pcl_mode2()' - Send PCL graphics using mode 2 (TIFF) compression.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pcl_mode2 (FILE * prn,unsigned char * line,int length,int last_plane)
name|pcl_mode2
parameter_list|(
name|FILE
modifier|*
name|prn
parameter_list|,
comment|/* I - Print file or command */
name|unsigned
name|char
modifier|*
name|line
parameter_list|,
comment|/* I - Output bitmap data */
name|int
name|length
parameter_list|,
comment|/* I - Length of bitmap data */
name|int
name|last_plane
parameter_list|)
comment|/* I - True if this is the last plane */
block|{
name|unsigned
name|char
name|comp_buf
index|[
literal|1536
index|]
decl_stmt|,
comment|/* Compression buffer */
modifier|*
name|comp_ptr
decl_stmt|,
comment|/* Current slot in buffer */
modifier|*
name|start
decl_stmt|,
comment|/* Start of compressed data */
name|repeat
decl_stmt|;
comment|/* Repeating char */
name|int
name|count
decl_stmt|,
comment|/* Count of compressed bytes */
name|tcount
decl_stmt|;
comment|/* Temporary count< 128 */
comment|/*   * Compress using TIFF "packbits" run-length encoding...   */
name|comp_ptr
operator|=
name|comp_buf
expr_stmt|;
while|while
condition|(
name|length
operator|>
literal|0
condition|)
block|{
comment|/*     * Get a run of non-repeated chars...     */
name|start
operator|=
name|line
expr_stmt|;
name|line
operator|+=
literal|2
expr_stmt|;
name|length
operator|-=
literal|2
expr_stmt|;
while|while
condition|(
name|length
operator|>
literal|0
operator|&&
operator|(
name|line
index|[
operator|-
literal|2
index|]
operator|!=
name|line
index|[
operator|-
literal|1
index|]
operator|||
name|line
index|[
operator|-
literal|1
index|]
operator|!=
name|line
index|[
literal|0
index|]
operator|)
condition|)
block|{
name|line
operator|++
expr_stmt|;
name|length
operator|--
expr_stmt|;
block|}
empty_stmt|;
name|line
operator|-=
literal|2
expr_stmt|;
name|length
operator|+=
literal|2
expr_stmt|;
comment|/*     * Output the non-repeated sequences (max 128 at a time).     */
name|count
operator|=
name|line
operator|-
name|start
expr_stmt|;
while|while
condition|(
name|count
operator|>
literal|0
condition|)
block|{
name|tcount
operator|=
name|count
operator|>
literal|128
condition|?
literal|128
else|:
name|count
expr_stmt|;
name|comp_ptr
index|[
literal|0
index|]
operator|=
name|tcount
operator|-
literal|1
expr_stmt|;
name|memcpy
argument_list|(
name|comp_ptr
operator|+
literal|1
argument_list|,
name|start
argument_list|,
name|tcount
argument_list|)
expr_stmt|;
name|comp_ptr
operator|+=
name|tcount
operator|+
literal|1
expr_stmt|;
name|start
operator|+=
name|tcount
expr_stmt|;
name|count
operator|-=
name|tcount
expr_stmt|;
block|}
empty_stmt|;
if|if
condition|(
name|length
operator|<=
literal|0
condition|)
break|break;
comment|/*     * Find the repeated sequences...     */
name|start
operator|=
name|line
expr_stmt|;
name|repeat
operator|=
name|line
index|[
literal|0
index|]
expr_stmt|;
name|line
operator|++
expr_stmt|;
name|length
operator|--
expr_stmt|;
while|while
condition|(
name|length
operator|>
literal|0
operator|&&
operator|*
name|line
operator|==
name|repeat
condition|)
block|{
name|line
operator|++
expr_stmt|;
name|length
operator|--
expr_stmt|;
block|}
empty_stmt|;
comment|/*     * Output the repeated sequences (max 128 at a time).     */
name|count
operator|=
name|line
operator|-
name|start
expr_stmt|;
while|while
condition|(
name|count
operator|>
literal|0
condition|)
block|{
name|tcount
operator|=
name|count
operator|>
literal|128
condition|?
literal|128
else|:
name|count
expr_stmt|;
name|comp_ptr
index|[
literal|0
index|]
operator|=
literal|1
operator|-
name|tcount
expr_stmt|;
name|comp_ptr
index|[
literal|1
index|]
operator|=
name|repeat
expr_stmt|;
name|comp_ptr
operator|+=
literal|2
expr_stmt|;
name|count
operator|-=
name|tcount
expr_stmt|;
block|}
empty_stmt|;
block|}
empty_stmt|;
comment|/*   * Send a line of raster graphics...   */
name|fprintf
argument_list|(
name|prn
argument_list|,
literal|"\033*b%d%c"
argument_list|,
call|(
name|int
call|)
argument_list|(
name|comp_ptr
operator|-
name|comp_buf
argument_list|)
argument_list|,
name|last_plane
condition|?
literal|'W'
else|:
literal|'V'
argument_list|)
expr_stmt|;
name|fwrite
argument_list|(
name|comp_buf
argument_list|,
name|comp_ptr
operator|-
name|comp_buf
argument_list|,
literal|1
argument_list|,
name|prn
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * End of "$Id$".  */
end_comment

end_unit


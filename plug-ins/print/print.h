begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * "$Id$"  *  *   Print plug-in header file for the GIMP.  *  *   Copyright 1997 Michael Sweet (mike@easysw.com)  *  *   This program is free software; you can redistribute it and/or modify it  *   under the terms of the GNU General Public License as published by the Free  *   Software Foundation; either version 2 of the License, or (at your option)  *   any later version.  *  *   This program is distributed in the hope that it will be useful, but  *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  *   for more details.  *  *   You should have received a copy of the GNU General Public License  *   along with this program; if not, write to the Free Software  *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  * Revision History:  *  *   $Log$  *   Revision 1.1.1.1  1997/11/24 22:04:34  sopwith  *   Let's try this import one last time.  *  *   Revision 1.3  1997/11/18 03:04:27  nobody  *   fixed ugly comment-bugs introduced by evil darkwing  *   keep out configuration empty dirs  *   	--darkwing  *  *   Revision 1.2  1997/11/17 05:43:57  nobody  *   updated ChangeLog  *   dropped non-working doc/Makefile entries  *   applied many fixes from the registry as well as the devel ML  *   applied missing patches by Art Haas  *  *   	--darkwing  *  *   Revision 1.8  1997/11/14  17:17:59  mike  *   Updated to dynamically allocate return params in the run() function.  *  *   Revision 1.7  1997/10/02  17:57:26  mike  *   Added gamma/dot gain correction values for all printers.  *  *   Revision 1.7  1997/10/02  17:57:26  mike  *   Added gamma/dot gain correction values for all printers.  *  *   Revision 1.6  1997/07/30  20:33:05  mike  *   Final changes for 1.1 release.  *  *   Revision 1.5  1997/07/30  18:47:39  mike  *   Added scaling, orientation, and offset options.  *  *   Revision 1.4  1997/07/26  18:43:04  mike  *   Updated version number to 1.1.  *  *   Revision 1.3  1997/07/03  13:26:46  mike  *   Updated documentation for 1.0 release.  *  *   Revision 1.2  1997/07/02  13:51:53  mike  *   Added rgb_to_rgb and gray_to_gray conversion functions.  *   Standardized calling args to conversion functions.  *  *   Revision 1.2  1997/07/02  13:51:53  mike  *   Added rgb_to_rgb and gray_to_gray conversion functions.  *   Standardized calling args to conversion functions.  *  *   Revision 1.1  1997/06/19  02:18:15  mike  *   Initial revision  */
end_comment

begin_comment
comment|/*  * Include necessary header files...  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_comment
comment|/*  * Constants...  */
end_comment

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"1.2.2 - 14 November 1997"
end_define

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"Print"
end_define

begin_define
DECL|macro|MEDIA_LETTER
define|#
directive|define
name|MEDIA_LETTER
value|0
end_define

begin_comment
DECL|macro|MEDIA_LETTER
comment|/* 8.5x11" a.k.a. "A" size */
end_comment

begin_define
DECL|macro|MEDIA_LEGAL
define|#
directive|define
name|MEDIA_LEGAL
value|1
end_define

begin_comment
DECL|macro|MEDIA_LEGAL
comment|/* 8.5x14" */
end_comment

begin_define
DECL|macro|MEDIA_TABLOID
define|#
directive|define
name|MEDIA_TABLOID
value|2
end_define

begin_comment
DECL|macro|MEDIA_TABLOID
comment|/* 11x17" a.k.a. "B" size */
end_comment

begin_define
DECL|macro|MEDIA_A4
define|#
directive|define
name|MEDIA_A4
value|3
end_define

begin_comment
DECL|macro|MEDIA_A4
comment|/* 8.27x11.69" (210x297mm) */
end_comment

begin_define
DECL|macro|MEDIA_A3
define|#
directive|define
name|MEDIA_A3
value|4
end_define

begin_comment
DECL|macro|MEDIA_A3
comment|/* 11.69x16.54" (297x420mm) */
end_comment

begin_define
DECL|macro|OUTPUT_GRAY
define|#
directive|define
name|OUTPUT_GRAY
value|0
end_define

begin_comment
DECL|macro|OUTPUT_GRAY
comment|/* Grayscale output */
end_comment

begin_define
DECL|macro|OUTPUT_COLOR
define|#
directive|define
name|OUTPUT_COLOR
value|1
end_define

begin_comment
DECL|macro|OUTPUT_COLOR
comment|/* Color output */
end_comment

begin_define
DECL|macro|ORIENT_AUTO
define|#
directive|define
name|ORIENT_AUTO
value|-1
end_define

begin_comment
DECL|macro|ORIENT_AUTO
comment|/* Best orientation */
end_comment

begin_define
DECL|macro|ORIENT_PORTRAIT
define|#
directive|define
name|ORIENT_PORTRAIT
value|0
end_define

begin_comment
DECL|macro|ORIENT_PORTRAIT
comment|/* Portrait orientation */
end_comment

begin_define
DECL|macro|ORIENT_LANDSCAPE
define|#
directive|define
name|ORIENT_LANDSCAPE
value|1
end_define

begin_comment
DECL|macro|ORIENT_LANDSCAPE
comment|/* Landscape orientation */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|MIN
end_ifndef

begin_define
DECL|macro|MIN (a,b)
define|#
directive|define
name|MIN
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)< (b) ? (a) : (b))
end_define

begin_define
DECL|macro|MAX (a,b)
define|#
directive|define
name|MAX
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)> (b) ? (a) : (b))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !MIN */
end_comment

begin_comment
comment|/*  * Printer driver control structure.  See "print.c" for the actual list...  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c15697d0108
block|{
DECL|member|long_name
name|char
modifier|*
name|long_name
decl_stmt|,
comment|/* Long name for UI */
DECL|member|short_name
modifier|*
name|short_name
decl_stmt|;
comment|/* Short name for printrc file */
DECL|member|xdpi
name|int
name|xdpi
decl_stmt|,
comment|/* X resolution */
DECL|member|ydpi
name|ydpi
decl_stmt|,
comment|/* Y resolution */
DECL|member|large_sizes
name|large_sizes
decl_stmt|,
comment|/* TRUE if supports large sizes */
DECL|member|color
name|color
decl_stmt|,
comment|/* TRUE if supports color */
DECL|member|model
name|model
decl_stmt|;
comment|/* Model number */
DECL|member|gamma
name|float
name|gamma
decl_stmt|,
comment|/* Gamma correction */
DECL|member|density
name|density
decl_stmt|;
comment|/* Ink "density" or black level */
DECL|member|print
name|void
function_decl|(
modifier|*
name|print
function_decl|)
parameter_list|(
name|FILE
modifier|*
name|prn
parameter_list|,
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|media_size
parameter_list|,
name|int
name|xdpi
parameter_list|,
name|int
name|ydpi
parameter_list|,
name|int
name|output_type
parameter_list|,
name|int
name|model
parameter_list|,
name|guchar
modifier|*
name|lut
parameter_list|,
name|guchar
modifier|*
name|cmap
parameter_list|,
name|int
name|orientation
parameter_list|,
name|int
name|scaling
parameter_list|,
name|int
name|left
parameter_list|,
name|int
name|top
parameter_list|)
function_decl|;
comment|/* Print function */
DECL|typedef|printer_t
block|}
name|printer_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|convert_t
typedef|typedef
name|void
function_decl|(
modifier|*
name|convert_t
function_decl|)
parameter_list|(
name|guchar
modifier|*
name|in
parameter_list|,
name|guchar
modifier|*
name|out
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|bpp
parameter_list|,
name|guchar
modifier|*
name|lut
parameter_list|,
name|guchar
modifier|*
name|cmap
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  * Prototypes...  */
end_comment

begin_function_decl
specifier|extern
name|void
name|dither_black
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|dither_cmyk
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gray_to_gray
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|indexed_to_gray
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|indexed_to_rgb
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|media_width
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|media_height
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|rgb_to_gray
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|rgb_to_rgb
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|escp2_print
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|GDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|pcl_print
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|GDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|ps_print
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|GDrawable
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * End of "$Id$".  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * "$Id$"  *  *   Print plug-in for the GIMP.  *  *   Copyright 1997-2000 Michael Sweet (mike@easysw.com),  *	Robert Krawitz (rlk@alum.mit.edu). and Steve Miller (smiller@rni.net  *  *   This program is free software; you can redistribute it and/or modify it  *   under the terms of the GNU General Public License as published by the Free  *   Software Foundation; either version 2 of the License, or (at your option)  *   any later version.  *  *   This program is distributed in the hope that it will be useful, but  *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  *   for more details.  *  *   You should have received a copy of the GNU General Public License  *   along with this program; if not, write to the Free Software  *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Revision History:  *  *   See ChangeLog  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PRINT_GIMP_H__
end_ifndef

begin_define
DECL|macro|__PRINT_GIMP_H__
define|#
directive|define
name|__PRINT_GIMP_H__
end_define

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

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"print.h"
end_include

begin_comment
comment|/*  * All Gimp-specific code is in this file.  */
end_comment

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|VERSION " - " RELEASE_DATE
end_define

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"Print"
end_define

begin_comment
comment|/*  * Constants for GUI...  */
end_comment

begin_define
DECL|macro|PREVIEW_SIZE_VERT
define|#
directive|define
name|PREVIEW_SIZE_VERT
value|240
end_define

begin_comment
DECL|macro|PREVIEW_SIZE_VERT
comment|/* Assuming max media size of 24" A2 */
end_comment

begin_define
DECL|macro|PREVIEW_SIZE_HORIZ
define|#
directive|define
name|PREVIEW_SIZE_HORIZ
value|240
end_define

begin_comment
DECL|macro|PREVIEW_SIZE_HORIZ
comment|/* Assuming max media size of 24" A2 */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|GIMP_MINOR_VERSION
argument_list|)
operator|||
operator|(
name|GIMP_MAJOR_VERSION
operator|==
literal|1
operator|&&
name|GIMP_MINOR_VERSION
operator|==
literal|0
operator|)
operator|||
operator|(
name|GIMP_MAJOR_VERSION
operator|==
literal|1
operator|&&
name|GIMP_MINOR_VERSION
operator|==
literal|1
operator|&&
name|GIMP_MICRO_VERSION
operator|<
literal|21
operator|)
end_if

begin_define
DECL|macro|GIMP_1_0
define|#
directive|define
name|GIMP_1_0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * Function prototypes  */
end_comment

begin_comment
comment|/* How to create an Image wrapping a Gimp drawable */
end_comment

begin_function_decl
specifier|extern
name|Image
name|Image_GDrawable_new
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PRINT_GIMP_H__ */
end_comment

end_unit


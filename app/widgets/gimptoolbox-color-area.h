begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_AREA_H__
end_ifndef

begin_define
DECL|macro|__COLOR_AREA_H__
define|#
directive|define
name|__COLOR_AREA_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_define
DECL|macro|FOREGROUND
define|#
directive|define
name|FOREGROUND
value|0
end_define

begin_define
DECL|macro|BACKGROUND
define|#
directive|define
name|BACKGROUND
value|1
end_define

begin_comment
comment|/*  *  Global variables  */
end_comment

begin_decl_stmt
specifier|extern
name|gint
name|active_color
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* foreground (= 0) or background (= 1) */
end_comment

begin_decl_stmt
specifier|extern
name|GDisplay
name|color_area_gdisp
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* hack for color displays */
end_comment

begin_comment
comment|/*  *  Functions  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|color_area_create
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GdkPixmap
modifier|*
name|default_pixmap
parameter_list|,
name|GdkPixmap
modifier|*
name|swap_pixmap
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Exported for use by color_select */
end_comment

begin_function_decl
name|void
name|color_area_draw_rect
parameter_list|(
name|GdkDrawable
modifier|*
name|drawable
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __COLOR_AREA_H__  */
end_comment

end_unit


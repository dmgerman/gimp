begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_PANEL_H__
end_ifndef

begin_define
DECL|macro|__COLOR_PANEL_H__
define|#
directive|define
name|__COLOR_PANEL_H__
end_define

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpcolorbutton.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_PANEL
define|#
directive|define
name|GIMP_TYPE_COLOR_PANEL
value|(gimp_color_panel_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_PANEL (obj)
define|#
directive|define
name|GIMP_COLOR_PANEL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_COLOR_PANEL, GimpColorPanel))
end_define

begin_define
DECL|macro|GIMP_COLOR_PANEL_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_PANEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_PANEL, GimpColorPanelClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PANEL (obj)
define|#
directive|define
name|GIMP_IS_COLOR_PANEL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_COLOR_PANEL))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PANEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_PANEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_PANEL))
end_define

begin_typedef
DECL|typedef|GimpColorPanel
typedef|typedef
name|struct
name|_GimpColorPanel
name|GimpColorPanel
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorPanelClass
typedef|typedef
name|struct
name|_GimpColorPanelClass
name|GimpColorPanelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorPanelClass
struct|struct
name|_GimpColorPanelClass
block|{
DECL|member|parent_class
name|GimpColorButtonClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_color_panel_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_panel_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __COLOR_PANEL_H__  */
end_comment

end_unit


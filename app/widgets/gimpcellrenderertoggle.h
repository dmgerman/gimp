begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcellrenderertoggle.h  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CELL_RENDERER_TOGGLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CELL_RENDERER_TOGGLE_H__
define|#
directive|define
name|__GIMP_CELL_RENDERER_TOGGLE_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkcellrenderertoggle.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_CELL_RENDERER_TOGGLE
define|#
directive|define
name|GIMP_TYPE_CELL_RENDERER_TOGGLE
value|(gimp_cell_renderer_toggle_get_type ())
end_define

begin_define
DECL|macro|GIMP_CELL_RENDERER_TOGGLE (obj)
define|#
directive|define
name|GIMP_CELL_RENDERER_TOGGLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CELL_RENDERER_TOGGLE, GimpCellRendererToggle))
end_define

begin_define
DECL|macro|GIMP_CELL_RENDERER_TOGGLE_CLASS (klass)
define|#
directive|define
name|GIMP_CELL_RENDERER_TOGGLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CELL_RENDERER_TOGGLE, GimpCellRendererToggleClass))
end_define

begin_define
DECL|macro|GIMP_IS_CELL_RENDERER_TOGGLE (obj)
define|#
directive|define
name|GIMP_IS_CELL_RENDERER_TOGGLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CELL_RENDERER_TOGGLE))
end_define

begin_define
DECL|macro|GIMP_IS_CELL_RENDERER_TOGGLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CELL_RENDERER_TOGGLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CELL_RENDERER_TOGGLE))
end_define

begin_define
DECL|macro|GIMP_CELL_RENDERER_TOGGLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CELL_RENDERER_TOGGLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CELL_RENDERER_TOGGLE, GimpCellRendererToggleClass))
end_define

begin_typedef
DECL|typedef|GimpCellRendererToggleClass
typedef|typedef
name|struct
name|_GimpCellRendererToggleClass
name|GimpCellRendererToggleClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCellRendererToggle
struct|struct
name|_GimpCellRendererToggle
block|{
DECL|member|parent_instance
name|GtkCellRendererToggle
name|parent_instance
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|stock_size
name|GtkIconSize
name|stock_size
decl_stmt|;
DECL|member|pixbuf
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCellRendererToggleClass
struct|struct
name|_GimpCellRendererToggleClass
block|{
DECL|member|parent_class
name|GtkCellRendererToggleClass
name|parent_class
decl_stmt|;
DECL|member|clicked
name|void
function_decl|(
modifier|*
name|clicked
function_decl|)
parameter_list|(
name|GimpCellRendererViewable
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_cell_renderer_toggle_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkCellRenderer
modifier|*
name|gimp_cell_renderer_toggle_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CELL_RENDERER_TOGGLE_H__ */
end_comment

end_unit


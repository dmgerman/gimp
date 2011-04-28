begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcellrenderertoggle.h  * Copyright (C) 2003-2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_macro
name|G_BEGIN_DECLS
end_macro

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
name|GimpCellRendererToggle
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
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
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

begin_function_decl
name|void
name|gimp_cell_renderer_toggle_clicked
parameter_list|(
name|GimpCellRendererToggle
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
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CELL_RENDERER_TOGGLE_H__ */
end_comment

end_unit


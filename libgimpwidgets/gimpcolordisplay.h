begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU Lesser General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_DISPLAY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_DISPLAY_H__
define|#
directive|define
name|__GIMP_COLOR_DISPLAY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look at the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLOR_DISPLAY
define|#
directive|define
name|GIMP_TYPE_COLOR_DISPLAY
value|(gimp_color_display_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY (obj)
define|#
directive|define
name|GIMP_COLOR_DISPLAY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_DISPLAY, GimpColorDisplay))
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_DISPLAY, GimpColorDisplayClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DISPLAY (obj)
define|#
directive|define
name|GIMP_IS_COLOR_DISPLAY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_DISPLAY))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DISPLAY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_DISPLAY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_DISPLAY))
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_DISPLAY, GimpColorDisplayClass))
end_define

begin_typedef
DECL|typedef|GimpColorDisplayClass
typedef|typedef
name|struct
name|_GimpColorDisplayClass
name|GimpColorDisplayClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorDisplay
struct|struct
name|_GimpColorDisplay
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorDisplayClass
struct|struct
name|_GimpColorDisplayClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|help_page
specifier|const
name|gchar
modifier|*
name|help_page
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|clone
name|GimpColorDisplay
modifier|*
function_decl|(
modifier|*
name|clone
function_decl|)
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|convert
name|void
function_decl|(
modifier|*
name|convert
function_decl|)
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
function_decl|;
DECL|member|load_state
name|void
function_decl|(
modifier|*
name|load_state
function_decl|)
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
function_decl|;
DECL|member|save_state
name|GimpParasite
modifier|*
function_decl|(
modifier|*
name|save_state
function_decl|)
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|configure
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|configure
function_decl|)
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|configure_reset
name|void
function_decl|(
modifier|*
name|configure_reset
function_decl|)
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_display_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpColorDisplay
modifier|*
name|gimp_color_display_new
parameter_list|(
name|GType
name|display_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorDisplay
modifier|*
name|gimp_color_display_clone
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_convert
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_load_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_color_display_save_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_display_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_configure_reset
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
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
comment|/* __GIMP_COLOR_DISPLAY_H__ */
end_comment

end_unit


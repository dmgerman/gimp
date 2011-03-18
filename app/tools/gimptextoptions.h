begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_OPTIONS_H__
define|#
directive|define
name|__GIMP_TEXT_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TEXT_OPTIONS
define|#
directive|define
name|GIMP_TYPE_TEXT_OPTIONS
value|(gimp_text_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_OPTIONS (obj)
define|#
directive|define
name|GIMP_TEXT_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_OPTIONS, GimpTextOptions))
end_define

begin_define
DECL|macro|GIMP_TEXT_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT_OPTIONS, GimpTextOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_TEXT_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_TEXT_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TEXT_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TEXT_OPTIONS, GimpTextOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpTextOptions
typedef|typedef
name|struct
name|_GimpTextOptions
name|GimpTextOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpTextOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextOptions
struct|struct
name|_GimpTextOptions
block|{
DECL|member|tool_options
name|GimpToolOptions
name|tool_options
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|font_size
name|gdouble
name|font_size
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|hint_style
name|GimpTextHintStyle
name|hint_style
decl_stmt|;
DECL|member|language
name|gchar
modifier|*
name|language
decl_stmt|;
DECL|member|base_dir
name|GimpTextDirection
name|base_dir
decl_stmt|;
DECL|member|justify
name|GimpTextJustification
name|justify
decl_stmt|;
DECL|member|indent
name|gdouble
name|indent
decl_stmt|;
DECL|member|line_spacing
name|gdouble
name|line_spacing
decl_stmt|;
DECL|member|letter_spacing
name|gdouble
name|letter_spacing
decl_stmt|;
DECL|member|box_mode
name|GimpTextBoxMode
name|box_mode
decl_stmt|;
DECL|member|font_view_type
name|GimpViewType
name|font_view_type
decl_stmt|;
DECL|member|font_view_size
name|GimpViewSize
name|font_view_size
decl_stmt|;
DECL|member|use_editor
name|gboolean
name|use_editor
decl_stmt|;
comment|/*  options gui  */
DECL|member|size_entry
name|GtkWidget
modifier|*
name|size_entry
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_text_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_text_options_connect_text
parameter_list|(
name|GimpTextOptions
modifier|*
name|options
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_text_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_text_options_editor_new
parameter_list|(
name|GtkWindow
modifier|*
name|parent
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTextOptions
modifier|*
name|options
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|,
name|GimpTextBuffer
modifier|*
name|text_buffer
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_OPTIONS_H__ */
end_comment

end_unit


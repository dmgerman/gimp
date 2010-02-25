begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_H__
define|#
directive|define
name|__GIMP_TEXT_H__
end_define

begin_include
include|#
directive|include
file|"libgimpmath/gimpmatrix.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TEXT
define|#
directive|define
name|GIMP_TYPE_TEXT
value|(gimp_text_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT (obj)
define|#
directive|define
name|GIMP_TEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT, GimpText))
end_define

begin_define
DECL|macro|GIMP_TEXT_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT, GimpTextClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT (obj)
define|#
directive|define
name|GIMP_IS_TEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT))
end_define

begin_define
DECL|macro|GIMP_TEXT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TEXT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TEXT, GimpTextClass))
end_define

begin_typedef
DECL|typedef|GimpTextClass
typedef|typedef
name|struct
name|_GimpTextClass
name|GimpTextClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpText
struct|struct
name|_GimpText
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|text
name|gchar
modifier|*
name|text
decl_stmt|;
DECL|member|markup
name|gchar
modifier|*
name|markup
decl_stmt|;
DECL|member|font
name|gchar
modifier|*
name|font
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
DECL|member|kerning
name|gboolean
name|kerning
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
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|outline
name|GimpTextOutline
name|outline
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
DECL|member|box_width
name|gdouble
name|box_width
decl_stmt|;
DECL|member|box_height
name|gdouble
name|box_height
decl_stmt|;
DECL|member|box_unit
name|GimpUnit
name|box_unit
decl_stmt|;
DECL|member|transformation
name|GimpMatrix2
name|transformation
decl_stmt|;
DECL|member|offset_x
name|gdouble
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gdouble
name|offset_y
decl_stmt|;
DECL|member|border
name|gdouble
name|border
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextClass
struct|struct
name|_GimpTextClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_text_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_text_get_transformation
parameter_list|(
name|GimpText
modifier|*
name|text
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_H__ */
end_comment

end_unit


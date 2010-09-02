begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextTag  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_TAG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_TAG_H__
define|#
directive|define
name|__GIMP_TEXT_TAG_H__
end_define

begin_comment
comment|/*  GtkTextTag property names  */
end_comment

begin_define
DECL|macro|GIMP_TEXT_PROP_NAME_SIZE
define|#
directive|define
name|GIMP_TEXT_PROP_NAME_SIZE
value|"size"
end_define

begin_define
DECL|macro|GIMP_TEXT_PROP_NAME_BASELINE
define|#
directive|define
name|GIMP_TEXT_PROP_NAME_BASELINE
value|"rise"
end_define

begin_define
DECL|macro|GIMP_TEXT_PROP_NAME_KERNING
define|#
directive|define
name|GIMP_TEXT_PROP_NAME_KERNING
value|"rise"
end_define

begin_comment
DECL|macro|GIMP_TEXT_PROP_NAME_KERNING
comment|/* FIXME */
end_comment

begin_define
DECL|macro|GIMP_TEXT_PROP_NAME_FONT
define|#
directive|define
name|GIMP_TEXT_PROP_NAME_FONT
value|"font"
end_define

begin_define
DECL|macro|GIMP_TEXT_PROP_NAME_COLOR
define|#
directive|define
name|GIMP_TEXT_PROP_NAME_COLOR
value|"foreground-gdk"
end_define

begin_function_decl
name|gint
name|gimp_text_tag_get_size
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_text_tag_get_baseline
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_text_tag_get_kerning
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_text_tag_get_font
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tag_get_color
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_TAG_H__ */
end_comment

end_unit


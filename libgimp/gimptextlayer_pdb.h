begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimptextlayer_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_LAYER_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_LAYER_PDB_H__
define|#
directive|define
name|__GIMP_TEXT_LAYER_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gint32
name|gimp_text_layer_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_text
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_font
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_fontsize
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gdouble
name|font_size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_hinting
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|hinting
parameter_list|,
name|gboolean
name|autohint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_antialias
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_kerning
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
name|kerning
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_language
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|language
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_base_direction
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpTextDirection
name|direction
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_justification
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpTextJustification
name|justify
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_color
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_indent
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gdouble
name|indent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_line_spacing
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gdouble
name|line_spacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_set_letter_spacing
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gdouble
name|letter_spacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_text_layer_get_text
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_text_layer_get_font
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_text_layer_get_fontsize
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpUnit
modifier|*
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_get_hinting
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gboolean
modifier|*
name|autohint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_get_antialias
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_get_kerning
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_text_layer_get_language
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTextDirection
name|gimp_text_layer_get_base_direction
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTextJustification
name|gimp_text_layer_get_justification
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_layer_get_color
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_text_layer_get_indent
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_text_layer_get_line_spacing
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_text_layer_get_letter_spacing
parameter_list|(
name|gint32
name|layer_ID
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
comment|/* __GIMP_TEXT_LAYER_PDB_H__ */
end_comment

end_unit


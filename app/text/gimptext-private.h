begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_LAYOUT_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_LAYOUT_PRIVATE_H__
define|#
directive|define
name|__GIMP_TEXT_LAYOUT_PRIVATE_H__
end_define

begin_comment
comment|/*  The purpose of this extra header file is to hide any Pango or  *  FreeType types from the rest of the gimp core.  */
end_comment

begin_struct
DECL|struct|_GimpTextLayout
struct|struct
name|_GimpTextLayout
block|{
DECL|member|object
name|GObject
name|object
decl_stmt|;
DECL|member|text
name|GimpText
modifier|*
name|text
decl_stmt|;
DECL|member|layout
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
DECL|member|extents
name|PangoRectangle
name|extents
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextLayoutClass
struct|struct
name|_GimpTextLayoutClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpTextRenderFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpTextRenderFunc
function_decl|)
parameter_list|(
name|PangoFont
modifier|*
name|font
parameter_list|,
name|PangoGlyph
name|glyph
parameter_list|,
name|FT_Int32
name|load_flags
parameter_list|,
name|FT_Matrix
modifier|*
name|tranform
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gpointer
name|render_data
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_LAYOUT_PRIVATE_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999,2000 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GDYNTEXT_H_
end_ifndef

begin_define
DECL|macro|_GDYNTEXT_H_
define|#
directive|define
name|_GDYNTEXT_H_
end_define

begin_define
DECL|macro|GDYNTEXT_VERSION
define|#
directive|define
name|GDYNTEXT_VERSION
value|"1.5.4"
end_define

begin_define
DECL|macro|GDYNTEXT_MAGIC
define|#
directive|define
name|GDYNTEXT_MAGIC
value|"GDT10"
end_define

begin_define
DECL|macro|GDYNTEXT_WEB_PAGE
define|#
directive|define
name|GDYNTEXT_WEB_PAGE
value|"http://www.geocities.com/Tokyo/1474/gimp/"
end_define

begin_define
DECL|macro|MAX_TEXT_SIZE
define|#
directive|define
name|MAX_TEXT_SIZE
value|(1024<< 6)
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE
define|#
directive|define
name|GDYNTEXT_PARASITE
value|"plug_in_gdyntext/data"
end_define

begin_comment
comment|/* version detection macros */
end_comment

begin_define
DECL|macro|GDT_MAGIC_REV (lname)
define|#
directive|define
name|GDT_MAGIC_REV
parameter_list|(
name|lname
parameter_list|)
value|(atoi(lname + 3))
end_define

begin_define
DECL|macro|GDT_REV ()
define|#
directive|define
name|GDT_REV
parameter_list|()
value|((int)(atof(GDYNTEXT_VERSION) * 10))
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c8437540103
block|{
DECL|enumerator|LEFT
name|LEFT
init|=
literal|0
block|,
DECL|enumerator|CENTER
name|CENTER
init|=
literal|1
block|,
DECL|enumerator|RIGHT
name|RIGHT
init|=
literal|2
DECL|typedef|GdtAlign
block|}
name|GdtAlign
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c8437540203
block|{
DECL|enumerator|TEXT
name|TEXT
init|=
literal|0
block|,
DECL|enumerator|ANTIALIAS
name|ANTIALIAS
init|=
literal|1
block|,
DECL|enumerator|ALIGNMENT
name|ALIGNMENT
init|=
literal|2
block|,
DECL|enumerator|ROTATION
name|ROTATION
init|=
literal|3
block|,
DECL|enumerator|LINE_SPACING
name|LINE_SPACING
init|=
literal|4
block|,
DECL|enumerator|COLOR
name|COLOR
init|=
literal|5
block|,
DECL|enumerator|LAYER_ALIGNMENT
name|LAYER_ALIGNMENT
init|=
literal|6
block|,
DECL|enumerator|XLFD
name|XLFD
init|=
literal|7
DECL|typedef|GDTBlock
block|}
name|GDTBlock
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c8437540303
block|{
DECL|enumerator|XLFD_NONE
name|XLFD_NONE
init|=
literal|0
block|,
DECL|enumerator|XLFD_FOUNDRY
name|XLFD_FOUNDRY
init|=
literal|1
block|,
DECL|enumerator|XLFD_FAMILY
name|XLFD_FAMILY
init|=
literal|2
block|,
DECL|enumerator|XLFD_WEIGHT
name|XLFD_WEIGHT
init|=
literal|3
block|,
DECL|enumerator|XLFD_SLANT
name|XLFD_SLANT
init|=
literal|4
block|,
DECL|enumerator|XLFD_SET_WIDTH
name|XLFD_SET_WIDTH
init|=
literal|5
block|,
DECL|enumerator|XLFD_ADD_STYLE
name|XLFD_ADD_STYLE
init|=
literal|6
block|,
DECL|enumerator|XLFD_PIXEL_SIZE
name|XLFD_PIXEL_SIZE
init|=
literal|7
block|,
DECL|enumerator|XLFD_POINT_SIZE
name|XLFD_POINT_SIZE
init|=
literal|8
block|,
DECL|enumerator|XLFD_RES_X
name|XLFD_RES_X
init|=
literal|9
block|,
DECL|enumerator|XLFD_RES_Y
name|XLFD_RES_Y
init|=
literal|10
block|,
DECL|enumerator|XLFD_SPACING
name|XLFD_SPACING
init|=
literal|11
block|,
DECL|enumerator|XLFD_AVERAGE_WIDTH
name|XLFD_AVERAGE_WIDTH
init|=
literal|12
block|,
DECL|enumerator|XLFD_REGISTRY
name|XLFD_REGISTRY
init|=
literal|13
block|,
DECL|enumerator|XLFD_ENCODING
name|XLFD_ENCODING
init|=
literal|14
DECL|typedef|XLFDBlock
block|}
name|XLFDBlock
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c8437540403
block|{
DECL|enumerator|LA_NONE
name|LA_NONE
init|=
literal|0
block|,
DECL|enumerator|LA_BOTTOM_LEFT
name|LA_BOTTOM_LEFT
init|=
literal|1
block|,
DECL|enumerator|LA_BOTTOM_CENTER
name|LA_BOTTOM_CENTER
init|=
literal|2
block|,
DECL|enumerator|LA_BOTTOM_RIGHT
name|LA_BOTTOM_RIGHT
init|=
literal|3
block|,
DECL|enumerator|LA_MIDDLE_LEFT
name|LA_MIDDLE_LEFT
init|=
literal|4
block|,
DECL|enumerator|LA_CENTER
name|LA_CENTER
init|=
literal|5
block|,
DECL|enumerator|LA_MIDDLE_RIGHT
name|LA_MIDDLE_RIGHT
init|=
literal|6
block|,
DECL|enumerator|LA_TOP_LEFT
name|LA_TOP_LEFT
init|=
literal|7
block|,
DECL|enumerator|LA_TOP_CENTER
name|LA_TOP_CENTER
init|=
literal|8
block|,
DECL|enumerator|LA_TOP_RIGHT
name|LA_TOP_RIGHT
init|=
literal|9
DECL|typedef|LayerAlignments
block|}
name|LayerAlignments
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c8437540508
typedef|typedef
struct|struct
block|{
comment|/* TRUE if the structure is correctly loaded throught gimp_get_data */
DECL|member|valid
name|gboolean
name|valid
decl_stmt|;
comment|/* Plug-in values */
DECL|member|new_layer
name|gboolean
name|new_layer
decl_stmt|;
DECL|member|image_id
name|gint32
name|image_id
decl_stmt|;
DECL|member|layer_id
name|gint32
name|layer_id
decl_stmt|;
DECL|member|drawable_id
name|gint32
name|drawable_id
decl_stmt|;
DECL|member|text
name|gchar
name|text
index|[
name|MAX_TEXT_SIZE
index|]
decl_stmt|;
DECL|member|xlfd
name|gchar
name|xlfd
index|[
literal|1024
index|]
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|alignment
name|GdtAlign
name|alignment
decl_stmt|;
DECL|member|rotation
name|gint
name|rotation
decl_stmt|;
DECL|member|line_spacing
name|gint
name|line_spacing
decl_stmt|;
DECL|member|layer_alignment
name|gint
name|layer_alignment
decl_stmt|;
DECL|member|change_layer_name
name|gboolean
name|change_layer_name
decl_stmt|;
comment|/* if TRUE force parasites use + label change */
comment|/* GUI stuff */
DECL|member|messages
name|GList
modifier|*
name|messages
decl_stmt|;
comment|/* FIXME: replace this stuff through a status bar */
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|GdtVals
block|}
name|GdtVals
typedef|;
end_typedef

begin_include
include|#
directive|include
file|"gdyntext_ui.h"
end_include

begin_include
include|#
directive|include
file|"gdyntextcompat.h"
end_include

begin_function_decl
name|void
name|gdt_load
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdt_save
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdt_render_text
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdt_render_text_p
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|,
name|gboolean
name|show_progress
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _GDYNTEXT_H_ */
end_comment

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit


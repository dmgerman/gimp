begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
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

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|GDYNTEXT_VERSION
define|#
directive|define
name|GDYNTEXT_VERSION
value|"1.4.1"
end_define

begin_define
DECL|macro|GDYNTEXT_MAGIC
define|#
directive|define
name|GDYNTEXT_MAGIC
value|"GDT09"
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
value|(64 * 1024)
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE
define|#
directive|define
name|GDYNTEXT_PARASITE
value|"gdyntext-parasite"
end_define

begin_comment
comment|/* parasites for compatibility with GDynText 1.3.0 */
end_comment

begin_define
DECL|macro|GDYNTEXT_PARASITE_PFX
define|#
directive|define
name|GDYNTEXT_PARASITE_PFX
value|"gdyntext_parasite"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_MAGIC
define|#
directive|define
name|GDYNTEXT_PARASITE_MAGIC
value|GDYNTEXT_PARASITE_PFX"_magic"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_TEXT
define|#
directive|define
name|GDYNTEXT_PARASITE_TEXT
value|GDYNTEXT_PARASITE_PFX"_text"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_FONT_FAMILY
define|#
directive|define
name|GDYNTEXT_PARASITE_FONT_FAMILY
value|GDYNTEXT_PARASITE_PFX"_font_family"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_FONT_STYLE
define|#
directive|define
name|GDYNTEXT_PARASITE_FONT_STYLE
value|GDYNTEXT_PARASITE_PFX"_font_style"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_FONT_SIZE
define|#
directive|define
name|GDYNTEXT_PARASITE_FONT_SIZE
value|GDYNTEXT_PARASITE_PFX"_font_size"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_FONT_METRIC
define|#
directive|define
name|GDYNTEXT_PARASITE_FONT_METRIC
value|GDYNTEXT_PARASITE_PFX"_font_metric"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_FONT_COLOR
define|#
directive|define
name|GDYNTEXT_PARASITE_FONT_COLOR
value|GDYNTEXT_PARASITE_PFX"_font_color"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_ANTIALIAS
define|#
directive|define
name|GDYNTEXT_PARASITE_ANTIALIAS
value|GDYNTEXT_PARASITE_PFX"_antialias"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_ALIGNMENT
define|#
directive|define
name|GDYNTEXT_PARASITE_ALIGNMENT
value|GDYNTEXT_PARASITE_PFX"_alignment"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_ROTATION
define|#
directive|define
name|GDYNTEXT_PARASITE_ROTATION
value|GDYNTEXT_PARASITE_PFX"_rotation"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_PREVIEW
define|#
directive|define
name|GDYNTEXT_PARASITE_PREVIEW
value|GDYNTEXT_PARASITE_PFX"_preview"
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29300bcd0103
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
DECL|struct|__anon29300bcd0208
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
name|char
name|text
index|[
name|MAX_TEXT_SIZE
index|]
decl_stmt|;
DECL|member|font_family
name|char
name|font_family
index|[
literal|1024
index|]
decl_stmt|;
DECL|member|font_style
name|char
name|font_style
index|[
literal|1024
index|]
decl_stmt|;
DECL|member|font_size
name|gint32
name|font_size
decl_stmt|;
DECL|member|font_metric
name|gint
name|font_metric
decl_stmt|;
DECL|member|font_color
name|gint32
name|font_color
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
DECL|member|spacing
name|gint
name|spacing
decl_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HAVE_PARASITES
DECL|member|change_layer_name
name|gboolean
name|change_layer_name
decl_stmt|;
comment|/* if TRUE force parasites use + label change */
endif|#
directive|endif
comment|/* GUI stuff */
DECL|member|messages
name|GList
modifier|*
name|messages
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|GdtVals
block|}
name|GdtVals
typedef|;
end_typedef

begin_function_decl
name|void
name|gdt_get_values
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdt_set_values
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
name|GArray
modifier|*
name|strsplit
parameter_list|(
specifier|const
name|char
modifier|*
name|text
parameter_list|,
specifier|const
name|char
name|sep
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


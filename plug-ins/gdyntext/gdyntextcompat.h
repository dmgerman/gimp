begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999,2000 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GDYNTEXTCOMPAT_H_
end_ifndef

begin_define
DECL|macro|_GDYNTEXTCOMPAT_H_
define|#
directive|define
name|_GDYNTEXTCOMPAT_H_
end_define

begin_include
include|#
directive|include
file|"gdyntext.h"
end_include

begin_comment
comment|/* parasites for compatibility with GDynText 1.4.4 and later versions */
end_comment

begin_define
DECL|macro|GDYNTEXT_PARASITE_144
define|#
directive|define
name|GDYNTEXT_PARASITE_144
value|"plug_in_gdyntext/data"
end_define

begin_comment
comment|/* parasites for compatibility with GDynText 1.3.1 - 1.4.3 */
end_comment

begin_define
DECL|macro|GDYNTEXT_PARASITE_131
define|#
directive|define
name|GDYNTEXT_PARASITE_131
value|"gdyntext-parasite"
end_define

begin_comment
comment|/* parasites for compatibility with GDynText 1.3.0 */
end_comment

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_PFX
define|#
directive|define
name|GDYNTEXT_PARASITE_130_PFX
value|"gdyntext_parasite"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_MAGIC
define|#
directive|define
name|GDYNTEXT_PARASITE_130_MAGIC
value|GDYNTEXT_PARASITE_130_PFX"_magic"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_TEXT
define|#
directive|define
name|GDYNTEXT_PARASITE_130_TEXT
value|GDYNTEXT_PARASITE_130_PFX"_text"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_FONT_FAMILY
define|#
directive|define
name|GDYNTEXT_PARASITE_130_FONT_FAMILY
value|GDYNTEXT_PARASITE_130_PFX"_font_family"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_FONT_STYLE
define|#
directive|define
name|GDYNTEXT_PARASITE_130_FONT_STYLE
value|GDYNTEXT_PARASITE_130_PFX"_font_style"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_FONT_SIZE
define|#
directive|define
name|GDYNTEXT_PARASITE_130_FONT_SIZE
value|GDYNTEXT_PARASITE_130_PFX"_font_size"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_FONT_METRIC
define|#
directive|define
name|GDYNTEXT_PARASITE_130_FONT_METRIC
value|GDYNTEXT_PARASITE_130_PFX"_font_metric"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_FONT_COLOR
define|#
directive|define
name|GDYNTEXT_PARASITE_130_FONT_COLOR
value|GDYNTEXT_PARASITE_130_PFX"_font_color"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_ANTIALIAS
define|#
directive|define
name|GDYNTEXT_PARASITE_130_ANTIALIAS
value|GDYNTEXT_PARASITE_130_PFX"_antialias"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_ALIGNMENT
define|#
directive|define
name|GDYNTEXT_PARASITE_130_ALIGNMENT
value|GDYNTEXT_PARASITE_130_PFX"_alignment"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_ROTATION
define|#
directive|define
name|GDYNTEXT_PARASITE_130_ROTATION
value|GDYNTEXT_PARASITE_130_PFX"_rotation"
end_define

begin_define
DECL|macro|GDYNTEXT_PARASITE_130_PREVIEW
define|#
directive|define
name|GDYNTEXT_PARASITE_130_PREVIEW
value|GDYNTEXT_PARASITE_130_PFX"_preview"
end_define

begin_comment
comment|/* parasite blocks */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29b381150103
block|{
DECL|enumerator|C_TEXT
name|C_TEXT
init|=
literal|0
block|,
DECL|enumerator|C_FONT_FAMILY
name|C_FONT_FAMILY
init|=
literal|1
block|,
DECL|enumerator|C_FONT_SIZE
name|C_FONT_SIZE
init|=
literal|2
block|,
DECL|enumerator|C_FONT_SIZE_T
name|C_FONT_SIZE_T
init|=
literal|3
block|,
DECL|enumerator|C_FONT_COLOR
name|C_FONT_COLOR
init|=
literal|4
block|,
DECL|enumerator|C_ANTIALIAS
name|C_ANTIALIAS
init|=
literal|5
block|,
DECL|enumerator|C_ALIGNMENT
name|C_ALIGNMENT
init|=
literal|6
block|,
DECL|enumerator|C_ROTATION
name|C_ROTATION
init|=
literal|7
block|,
DECL|enumerator|C_FONT_STYLE
name|C_FONT_STYLE
init|=
literal|8
block|,
DECL|enumerator|C_SPACING
name|C_SPACING
init|=
literal|9
DECL|typedef|GDTCompatBlock
block|}
name|GDTCompatBlock
typedef|;
end_typedef

begin_comment
comment|/* gimp-1.1.14+ function names reorganization forgotten something */
end_comment

begin_if
if|#
directive|if
name|defined
argument_list|(
name|GIMP_HAVE_PARASITES
argument_list|)
operator|&&
name|GIMP_MICRO_VERSION
operator|<
literal|14
end_if

begin_warning
warning|#
directive|warning
warning|Replacing missing function 'gimp_drawable_parasite_find'
end_warning

begin_define
DECL|macro|gimp_drawable_parasite_find
define|#
directive|define
name|gimp_drawable_parasite_find
value|gimp_drawable_parasite_find
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|gboolean
name|gdt_compat_load
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _GDYNTEXTCOMPAT_H_ */
end_comment

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit


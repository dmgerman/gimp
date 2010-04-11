begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PALETTE_LOAD_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PALETTE_LOAD_H__
define|#
directive|define
name|__GIMP_PALETTE_LOAD_H__
end_define

begin_define
DECL|macro|GIMP_PALETTE_FILE_EXTENSION
define|#
directive|define
name|GIMP_PALETTE_FILE_EXTENSION
value|".gpl"
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon289146b50103
block|{
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_UNKNOWN
name|GIMP_PALETTE_FILE_FORMAT_UNKNOWN
block|,
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_GPL
name|GIMP_PALETTE_FILE_FORMAT_GPL
block|,
comment|/* GIMP palette                        */
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_RIFF_PAL
name|GIMP_PALETTE_FILE_FORMAT_RIFF_PAL
block|,
comment|/* RIFF palette                        */
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_ACT
name|GIMP_PALETTE_FILE_FORMAT_ACT
block|,
comment|/* Photoshop binary color palette      */
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_PSP_PAL
name|GIMP_PALETTE_FILE_FORMAT_PSP_PAL
block|,
comment|/* JASC's Paint Shop Pro color palette */
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_ACO
name|GIMP_PALETTE_FILE_FORMAT_ACO
block|,
comment|/* Photoshop ACO color file            */
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_CSS
name|GIMP_PALETTE_FILE_FORMAT_CSS
comment|/* Cascaded Stylesheet file (CSS)      */
DECL|typedef|GimpPaletteFileFormat
block|}
name|GimpPaletteFileFormat
typedef|;
end_typedef

begin_function_decl
name|GList
modifier|*
name|gimp_palette_load
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_palette_load_act
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_palette_load_riff
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_palette_load_psp
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_palette_load_aco
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_palette_load_css
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPaletteFileFormat
name|gimp_palette_load_detect_format
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PALETTE_H__ */
end_comment

end_unit


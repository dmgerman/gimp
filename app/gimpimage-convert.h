begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CONVERT_H__
end_ifndef

begin_define
DECL|macro|__CONVERT_H__
define|#
directive|define
name|__CONVERT_H__
end_define

begin_comment
comment|/* adam's extra palette stuff */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c2d5bc50103
block|{
DECL|enumerator|MAKE_PALETTE
name|MAKE_PALETTE
init|=
literal|0
block|,
DECL|enumerator|REUSE_PALETTE
name|REUSE_PALETTE
init|=
literal|1
block|,
DECL|enumerator|WEB_PALETTE
name|WEB_PALETTE
init|=
literal|2
block|,
DECL|enumerator|MONO_PALETTE
name|MONO_PALETTE
init|=
literal|3
block|,
DECL|enumerator|CUSTOM_PALETTE
name|CUSTOM_PALETTE
init|=
literal|4
DECL|typedef|ConvertPaletteType
block|}
name|ConvertPaletteType
typedef|;
end_typedef

begin_comment
comment|/* adam's extra dither stuff */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c2d5bc50203
block|{
DECL|enumerator|NO_DITHER
name|NO_DITHER
init|=
literal|0
block|,
DECL|enumerator|FS_DITHER
name|FS_DITHER
init|=
literal|1
block|,
DECL|enumerator|FSLOWBLEED_DITHER
name|FSLOWBLEED_DITHER
init|=
literal|2
block|,
DECL|enumerator|FIXED_DITHER
name|FIXED_DITHER
init|=
literal|3
block|,
DECL|enumerator|NODESTRUCT_DITHER
name|NODESTRUCT_DITHER
init|=
literal|4
comment|/* NEVER USE NODESTRUCT_DITHER EXPLICITLY */
DECL|typedef|ConvertDitherType
block|}
name|ConvertDitherType
typedef|;
end_typedef

begin_define
DECL|macro|MAXNUMCOLORS
define|#
directive|define
name|MAXNUMCOLORS
value|256
end_define

begin_comment
comment|/*  convert functions  */
end_comment

begin_function_decl
name|void
name|convert_to_rgb
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|convert_to_grayscale
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|convert_to_indexed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|convert_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpImageBaseType
parameter_list|,
name|gint
name|num_cols
parameter_list|,
name|ConvertDitherType
parameter_list|,
name|gint
name|alpha_dither
parameter_list|,
name|gint
name|remdups
parameter_list|,
name|ConvertPaletteType
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|GimpPalette
modifier|*
name|theCustomPalette
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __CONVERT_H__  */
end_comment

end_unit


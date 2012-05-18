begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BASE_TYPES_H__
end_ifndef

begin_define
DECL|macro|__BASE_TYPES_H__
define|#
directive|define
name|__BASE_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_comment
comment|/* screw include policy in base/ */
end_comment

begin_comment
comment|/* convenient defines */
end_comment

begin_define
DECL|macro|MAX_CHANNELS
define|#
directive|define
name|MAX_CHANNELS
value|4
end_define

begin_define
DECL|macro|RED
define|#
directive|define
name|RED
value|0
end_define

begin_define
DECL|macro|GREEN
define|#
directive|define
name|GREEN
value|1
end_define

begin_define
DECL|macro|BLUE
define|#
directive|define
name|BLUE
value|2
end_define

begin_define
DECL|macro|ALPHA
define|#
directive|define
name|ALPHA
value|3
end_define

begin_define
DECL|macro|GRAY
define|#
directive|define
name|GRAY
value|0
end_define

begin_define
DECL|macro|ALPHA_G
define|#
directive|define
name|ALPHA_G
value|1
end_define

begin_define
DECL|macro|INDEXED
define|#
directive|define
name|INDEXED
value|0
end_define

begin_define
DECL|macro|ALPHA_I
define|#
directive|define
name|ALPHA_I
value|1
end_define

begin_comment
comment|/* types */
end_comment

begin_typedef
DECL|typedef|PixelRegion
typedef|typedef
name|struct
name|_PixelRegion
name|PixelRegion
typedef|;
end_typedef

begin_typedef
DECL|typedef|SioxState
typedef|typedef
name|struct
name|_SioxState
name|SioxState
typedef|;
end_typedef

begin_typedef
DECL|typedef|Tile
typedef|typedef
name|struct
name|_Tile
name|Tile
typedef|;
end_typedef

begin_typedef
DECL|typedef|TileManager
typedef|typedef
name|struct
name|_TileManager
name|TileManager
typedef|;
end_typedef

begin_typedef
DECL|typedef|TilePyramid
typedef|typedef
name|struct
name|_TilePyramid
name|TilePyramid
typedef|;
end_typedef

begin_comment
comment|/*  enums  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28bffd990103
block|{
DECL|enumerator|SIOX_REFINEMENT_NO_CHANGE
name|SIOX_REFINEMENT_NO_CHANGE
init|=
literal|0
block|,
DECL|enumerator|SIOX_REFINEMENT_ADD_FOREGROUND
name|SIOX_REFINEMENT_ADD_FOREGROUND
init|=
operator|(
literal|1
operator|<<
literal|0
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_ADD_BACKGROUND
name|SIOX_REFINEMENT_ADD_BACKGROUND
init|=
operator|(
literal|1
operator|<<
literal|1
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_CHANGE_SENSITIVITY
name|SIOX_REFINEMENT_CHANGE_SENSITIVITY
init|=
operator|(
literal|1
operator|<<
literal|2
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_CHANGE_SMOOTHNESS
name|SIOX_REFINEMENT_CHANGE_SMOOTHNESS
init|=
operator|(
literal|1
operator|<<
literal|3
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_CHANGE_MULTIBLOB
name|SIOX_REFINEMENT_CHANGE_MULTIBLOB
init|=
operator|(
literal|1
operator|<<
literal|4
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_RECALCULATE
name|SIOX_REFINEMENT_RECALCULATE
init|=
literal|0xFF
DECL|typedef|SioxRefinementType
block|}
name|SioxRefinementType
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __BASE_TYPES_H__ */
end_comment

end_unit


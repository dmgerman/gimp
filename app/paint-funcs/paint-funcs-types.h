begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_FUNCS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__PAINT_FUNCS_TYPES_H__
define|#
directive|define
name|__PAINT_FUNCS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_comment
comment|/* Opacities */
end_comment

begin_define
DECL|macro|TRANSPARENT_OPACITY
define|#
directive|define
name|TRANSPARENT_OPACITY
value|0
end_define

begin_define
DECL|macro|OPAQUE_OPACITY
define|#
directive|define
name|OPAQUE_OPACITY
value|255
end_define

begin_comment
comment|/*  Lay down the groundwork for layer construction...  *  This includes background images for indexed or non-alpha  *  images, floating selections, selective display of intensity  *  channels, and display of arbitrary mask channels  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bc173370103
block|{
DECL|enumerator|INITIAL_CHANNEL_MASK
name|INITIAL_CHANNEL_MASK
init|=
literal|0
block|,
DECL|enumerator|INITIAL_CHANNEL_SELECTION
name|INITIAL_CHANNEL_SELECTION
block|,
DECL|enumerator|INITIAL_INDEXED
name|INITIAL_INDEXED
block|,
DECL|enumerator|INITIAL_INDEXED_ALPHA
name|INITIAL_INDEXED_ALPHA
block|,
DECL|enumerator|INITIAL_INTENSITY
name|INITIAL_INTENSITY
block|,
DECL|enumerator|INITIAL_INTENSITY_ALPHA
name|INITIAL_INTENSITY_ALPHA
DECL|typedef|InitialMode
block|}
name|InitialMode
typedef|;
end_typedef

begin_comment
comment|/*  Combine two source regions with the help of an optional mask  *  region into a destination region.  This is used for constructing  *  layer projections, and for applying image patches to an image  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bc173370203
block|{
DECL|enumerator|NO_COMBINATION
name|NO_COMBINATION
init|=
literal|0
block|,
DECL|enumerator|COMBINE_INDEXED_INDEXED
name|COMBINE_INDEXED_INDEXED
block|,
DECL|enumerator|COMBINE_INDEXED_INDEXED_A
name|COMBINE_INDEXED_INDEXED_A
block|,
DECL|enumerator|COMBINE_INDEXED_A_INDEXED_A
name|COMBINE_INDEXED_A_INDEXED_A
block|,
DECL|enumerator|COMBINE_INTEN_A_INDEXED
name|COMBINE_INTEN_A_INDEXED
block|,
DECL|enumerator|COMBINE_INTEN_A_INDEXED_A
name|COMBINE_INTEN_A_INDEXED_A
block|,
DECL|enumerator|COMBINE_INTEN_A_CHANNEL_MASK
name|COMBINE_INTEN_A_CHANNEL_MASK
block|,
DECL|enumerator|COMBINE_INTEN_A_CHANNEL_SELECTION
name|COMBINE_INTEN_A_CHANNEL_SELECTION
block|,
DECL|enumerator|COMBINE_INTEN_INTEN
name|COMBINE_INTEN_INTEN
block|,
DECL|enumerator|COMBINE_INTEN_INTEN_A
name|COMBINE_INTEN_INTEN_A
block|,
DECL|enumerator|COMBINE_INTEN_A_INTEN
name|COMBINE_INTEN_A_INTEN
block|,
DECL|enumerator|COMBINE_INTEN_A_INTEN_A
name|COMBINE_INTEN_A_INTEN_A
block|,
comment|/*  Non-conventional combination modes  */
DECL|enumerator|BEHIND_INTEN
name|BEHIND_INTEN
block|,
DECL|enumerator|BEHIND_INDEXED
name|BEHIND_INDEXED
block|,
DECL|enumerator|REPLACE_INTEN
name|REPLACE_INTEN
block|,
DECL|enumerator|REPLACE_INDEXED
name|REPLACE_INDEXED
block|,
DECL|enumerator|ERASE_INTEN
name|ERASE_INTEN
block|,
DECL|enumerator|ERASE_INDEXED
name|ERASE_INDEXED
block|,
DECL|enumerator|ANTI_ERASE_INTEN
name|ANTI_ERASE_INTEN
block|,
DECL|enumerator|ANTI_ERASE_INDEXED
name|ANTI_ERASE_INDEXED
block|,
DECL|enumerator|COLOR_ERASE_INTEN
name|COLOR_ERASE_INTEN
DECL|typedef|CombinationMode
block|}
name|CombinationMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_FUNCS_TYPES_H__  */
end_comment

end_unit


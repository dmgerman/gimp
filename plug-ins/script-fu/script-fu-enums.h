begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCRIPT_FU_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__SCRIPT_FU_ENUMS_H__
define|#
directive|define
name|__SCRIPT_FU_ENUMS_H__
end_define

begin_comment
comment|/*  Typedefs for script-fu argument types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon279430a70103
block|{
DECL|enumerator|SF_IMAGE
name|SF_IMAGE
init|=
literal|0
block|,
DECL|enumerator|SF_DRAWABLE
name|SF_DRAWABLE
block|,
DECL|enumerator|SF_LAYER
name|SF_LAYER
block|,
DECL|enumerator|SF_CHANNEL
name|SF_CHANNEL
block|,
DECL|enumerator|SF_COLOR
name|SF_COLOR
block|,
DECL|enumerator|SF_TOGGLE
name|SF_TOGGLE
block|,
DECL|enumerator|SF_VALUE
name|SF_VALUE
block|,
DECL|enumerator|SF_STRING
name|SF_STRING
block|,
DECL|enumerator|SF_ADJUSTMENT
name|SF_ADJUSTMENT
block|,
DECL|enumerator|SF_FONT
name|SF_FONT
block|,
DECL|enumerator|SF_PATTERN
name|SF_PATTERN
DECL|typedef|SFArgType
block|}
name|SFArgType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon279430a70203
block|{
DECL|enumerator|SF_SLIDER
name|SF_SLIDER
init|=
literal|0
block|,
DECL|enumerator|SF_SPINNER
name|SF_SPINNER
DECL|typedef|SFAdjustmentType
block|}
name|SFAdjustmentType
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCRIPT_FU_ENUMS__  */
end_comment

end_unit


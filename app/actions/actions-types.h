begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ACTIONS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__ACTIONS_TYPES_H__
define|#
directive|define
name|__ACTIONS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"dialogs/dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"tools/tools-types.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b3f7e710103
block|{
DECL|enumerator|GIMP_ACTION_SELECT_SET
name|GIMP_ACTION_SELECT_SET
init|=
literal|0
block|,
DECL|enumerator|GIMP_ACTION_SELECT_SET_TO_DEFAULT
name|GIMP_ACTION_SELECT_SET_TO_DEFAULT
init|=
operator|-
literal|1
block|,
DECL|enumerator|GIMP_ACTION_SELECT_FIRST
name|GIMP_ACTION_SELECT_FIRST
init|=
operator|-
literal|2
block|,
DECL|enumerator|GIMP_ACTION_SELECT_LAST
name|GIMP_ACTION_SELECT_LAST
init|=
operator|-
literal|3
block|,
DECL|enumerator|GIMP_ACTION_SELECT_SMALL_PREVIOUS
name|GIMP_ACTION_SELECT_SMALL_PREVIOUS
init|=
operator|-
literal|4
block|,
DECL|enumerator|GIMP_ACTION_SELECT_SMALL_NEXT
name|GIMP_ACTION_SELECT_SMALL_NEXT
init|=
operator|-
literal|5
block|,
DECL|enumerator|GIMP_ACTION_SELECT_PREVIOUS
name|GIMP_ACTION_SELECT_PREVIOUS
init|=
operator|-
literal|6
block|,
DECL|enumerator|GIMP_ACTION_SELECT_NEXT
name|GIMP_ACTION_SELECT_NEXT
init|=
operator|-
literal|7
block|,
DECL|enumerator|GIMP_ACTION_SELECT_SKIP_PREVIOUS
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
init|=
operator|-
literal|8
block|,
DECL|enumerator|GIMP_ACTION_SELECT_SKIP_NEXT
name|GIMP_ACTION_SELECT_SKIP_NEXT
init|=
operator|-
literal|9
block|,
DECL|enumerator|GIMP_ACTION_SELECT_PERCENT_PREVIOUS
name|GIMP_ACTION_SELECT_PERCENT_PREVIOUS
init|=
operator|-
literal|10
block|,
DECL|enumerator|GIMP_ACTION_SELECT_PERCENT_NEXT
name|GIMP_ACTION_SELECT_PERCENT_NEXT
init|=
operator|-
literal|11
DECL|typedef|GimpActionSelectType
block|}
name|GimpActionSelectType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b3f7e710203
block|{
DECL|enumerator|GIMP_SAVE_MODE_SAVE
name|GIMP_SAVE_MODE_SAVE
block|,
DECL|enumerator|GIMP_SAVE_MODE_SAVE_AS
name|GIMP_SAVE_MODE_SAVE_AS
block|,
DECL|enumerator|GIMP_SAVE_MODE_SAVE_A_COPY
name|GIMP_SAVE_MODE_SAVE_A_COPY
block|,
DECL|enumerator|GIMP_SAVE_MODE_SAVE_AND_CLOSE
name|GIMP_SAVE_MODE_SAVE_AND_CLOSE
block|,
DECL|enumerator|GIMP_SAVE_MODE_EXPORT
name|GIMP_SAVE_MODE_EXPORT
block|,
DECL|enumerator|GIMP_SAVE_MODE_EXPORT_TO
name|GIMP_SAVE_MODE_EXPORT_TO
block|,
DECL|enumerator|GIMP_SAVE_MODE_OVERWRITE
name|GIMP_SAVE_MODE_OVERWRITE
DECL|typedef|GimpSaveMode
block|}
name|GimpSaveMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ACTIONS_TYPES_H__ */
end_comment

end_unit


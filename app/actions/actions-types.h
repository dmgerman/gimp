begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gui/gui-types.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297e6e820103
block|{
DECL|enumerator|GIMP_ACTION_SELECT_SET
name|GIMP_ACTION_SELECT_SET
init|=
literal|0
block|,
DECL|enumerator|GIMP_ACTION_SELECT_FIRST
name|GIMP_ACTION_SELECT_FIRST
init|=
operator|-
literal|1
block|,
DECL|enumerator|GIMP_ACTION_SELECT_LAST
name|GIMP_ACTION_SELECT_LAST
init|=
operator|-
literal|2
block|,
DECL|enumerator|GIMP_ACTION_SELECT_PREVIOUS
name|GIMP_ACTION_SELECT_PREVIOUS
init|=
operator|-
literal|3
block|,
DECL|enumerator|GIMP_ACTION_SELECT_NEXT
name|GIMP_ACTION_SELECT_NEXT
init|=
operator|-
literal|4
block|,
DECL|enumerator|GIMP_ACTION_SELECT_SKIP_PREVIOUS
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
init|=
operator|-
literal|5
block|,
DECL|enumerator|GIMP_ACTION_SELECT_SKIP_NEXT
name|GIMP_ACTION_SELECT_SKIP_NEXT
init|=
operator|-
literal|6
DECL|typedef|GimpActionSelectType
block|}
name|GimpActionSelectType
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


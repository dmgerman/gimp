begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHECKS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHECKS_H__
define|#
directive|define
name|__GIMP_CHECKS_H__
end_define

begin_comment
comment|/*  Transparency representation  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2883cfcc0103
block|{
DECL|enumerator|LIGHT_CHECKS
name|LIGHT_CHECKS
init|=
literal|0
block|,
DECL|enumerator|GRAY_CHECKS
name|GRAY_CHECKS
init|=
literal|1
block|,
DECL|enumerator|DARK_CHECKS
name|DARK_CHECKS
init|=
literal|2
block|,
DECL|enumerator|WHITE_ONLY
name|WHITE_ONLY
init|=
literal|3
block|,
DECL|enumerator|GRAY_ONLY
name|GRAY_ONLY
init|=
literal|4
block|,
DECL|enumerator|BLACK_ONLY
name|BLACK_ONLY
init|=
literal|5
DECL|typedef|GimpCheckType
block|}
name|GimpCheckType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2883cfcc0203
block|{
DECL|enumerator|SMALL_CHECKS
name|SMALL_CHECKS
init|=
literal|0
block|,
DECL|enumerator|MEDIUM_CHECKS
name|MEDIUM_CHECKS
init|=
literal|1
block|,
DECL|enumerator|LARGE_CHECKS
name|LARGE_CHECKS
init|=
literal|2
DECL|typedef|GimpCheckSize
block|}
name|GimpCheckSize
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CHECKS_H__  */
end_comment

end_unit


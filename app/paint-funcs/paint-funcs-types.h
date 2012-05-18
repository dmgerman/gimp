begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_FUNCS_TYPES_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmathtypes.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MATH_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MATH_TYPES_H__
define|#
directive|define
name|__GIMP_MATH_TYPES_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpMatrix2
typedef|typedef
name|struct
name|_GimpMatrix2
name|GimpMatrix2
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMatrix3
typedef|typedef
name|struct
name|_GimpMatrix3
name|GimpMatrix3
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMatrix4
typedef|typedef
name|struct
name|_GimpMatrix4
name|GimpMatrix4
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVector2
typedef|typedef
name|struct
name|_GimpVector2
name|GimpVector2
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVector3
typedef|typedef
name|struct
name|_GimpVector3
name|GimpVector3
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVector4
typedef|typedef
name|struct
name|_GimpVector4
name|GimpVector4
typedef|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MATH_TYPES_H__ */
end_comment

end_unit


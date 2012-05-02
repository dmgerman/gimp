begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MODULE_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MODULE_TYPES_H__
define|#
directive|define
name|__GIMP_MODULE_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<libgimpbase/gimpbasetypes.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_comment
comment|/*  * GIMP_MODULE_PARAM_SERIALIZE is deprecated, use  * GIMP_CONFIG_PARAM_SERIALIZE instead.  */
end_comment

begin_define
DECL|macro|GIMP_MODULE_PARAM_SERIALIZE
define|#
directive|define
name|GIMP_MODULE_PARAM_SERIALIZE
value|(1<< (0 + G_PARAM_USER_SHIFT))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|GimpModule
typedef|typedef
name|struct
name|_GimpModule
name|GimpModule
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpModuleInfo
typedef|typedef
name|struct
name|_GimpModuleInfo
name|GimpModuleInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpModuleDB
typedef|typedef
name|struct
name|_GimpModuleDB
name|GimpModuleDB
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
comment|/* __GIMP_MODULE_TYPES_H__ */
end_comment

end_unit


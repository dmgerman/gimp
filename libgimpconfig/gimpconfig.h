begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_H__
define|#
directive|define
name|__GIMP_CONFIG_H__
end_define

begin_define
DECL|macro|__GIMP_CONFIG_H_INSIDE__
define|#
directive|define
name|__GIMP_CONFIG_H_INSIDE__
end_define

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfigtypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfigwriter.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig-iface.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig-error.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig-serialize.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig-deserialize.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig-utils.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig-params.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig-path.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpscanner.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpcolorconfig.h>
end_include

begin_undef
undef|#
directive|undef
name|__GIMP_CONFIG_H_INSIDE__
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_H__ */
end_comment

end_unit


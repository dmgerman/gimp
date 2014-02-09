begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_H__
define|#
directive|define
name|__GIMP_COLOR_H__
end_define

begin_define
DECL|macro|__GIMP_COLOR_H_INSIDE__
define|#
directive|define
name|__GIMP_COLOR_H_INSIDE__
end_define

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolortypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpadaptivesupersample.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpbilinear.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcairo.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolormanaged.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolorspace.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcmyk.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimphsl.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimphsv.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimplcms.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimppixbuf.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimprgb.h>
end_include

begin_undef
undef|#
directive|undef
name|__GIMP_COLOR_H_INSIDE__
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_H__ */
end_comment

end_unit


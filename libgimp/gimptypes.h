begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimptypes.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TYPES_H__
define|#
directive|define
name|__GIMP_TYPES_H__
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
comment|/* For information look into the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpPDB
typedef|typedef
name|struct
name|_GimpPDB
name|GimpPDB
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugIn
typedef|typedef
name|struct
name|_GimpPlugIn
name|GimpPlugIn
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpProcedure
typedef|typedef
name|struct
name|_GimpProcedure
name|GimpProcedure
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInInfo
typedef|typedef
name|struct
name|_GimpPlugInInfo
name|GimpPlugInInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParamDef
typedef|typedef
name|struct
name|_GimpParamDef
name|GimpParamDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParamData
typedef|typedef
name|union
name|_GimpParamData
name|GimpParamData
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParam
typedef|typedef
name|struct
name|_GimpParam
name|GimpParam
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImage
typedef|typedef
name|struct
name|_GimpImage
name|GimpImage
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItem
typedef|typedef
name|struct
name|_GimpItem
name|GimpItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawable
typedef|typedef
name|struct
name|_GimpDrawable
name|GimpDrawable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayer
typedef|typedef
name|struct
name|_GimpLayer
name|GimpLayer
typedef|;
end_typedef

begin_comment
comment|/* FIXME move somewhere else */
end_comment

begin_comment
comment|/**  * GimpPixbufTransparency:  * @GIMP_PIXBUF_KEEP_ALPHA:   Create a pixbuf with alpha  * @GIMP_PIXBUF_SMALL_CHECKS: Show transparency as small checks  * @GIMP_PIXBUF_LARGE_CHECKS: Show transparency as large checks  *  * How to deal with transparency when creating thubnail pixbufs from  * images and drawables.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28af3f580103
block|{
DECL|enumerator|GIMP_PIXBUF_KEEP_ALPHA
name|GIMP_PIXBUF_KEEP_ALPHA
block|,
DECL|enumerator|GIMP_PIXBUF_SMALL_CHECKS
name|GIMP_PIXBUF_SMALL_CHECKS
block|,
DECL|enumerator|GIMP_PIXBUF_LARGE_CHECKS
name|GIMP_PIXBUF_LARGE_CHECKS
DECL|typedef|GimpPixbufTransparency
block|}
name|GimpPixbufTransparency
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
comment|/* __GIMP_TYPES_H__ */
end_comment

end_unit


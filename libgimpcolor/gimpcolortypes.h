begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_TYPES_H__
define|#
directive|define
name|__GIMP_COLOR_TYPES_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/*  usually we don't keep the structure definitions in the types file  *  but GimpRGB appears in too many header files...  */
end_comment

begin_typedef
DECL|typedef|GimpRGB
typedef|typedef
name|struct
name|_GimpRGB
name|GimpRGB
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHSV
typedef|typedef
name|struct
name|_GimpHSV
name|GimpHSV
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHSL
typedef|typedef
name|struct
name|_GimpHSL
name|GimpHSL
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRGB
struct|struct
name|_GimpRGB
block|{
DECL|member|r
DECL|member|g
DECL|member|b
DECL|member|a
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHSV
struct|struct
name|_GimpHSV
block|{
DECL|member|h
DECL|member|s
DECL|member|v
DECL|member|a
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHSL
struct|struct
name|_GimpHSL
block|{
DECL|member|h
DECL|member|s
DECL|member|l
DECL|member|a
name|gdouble
name|h
decl_stmt|,
name|s
decl_stmt|,
name|l
decl_stmt|,
name|a
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpRenderFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRenderFunc
function_decl|)
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpPutPixelFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpPutPixelFunc
function_decl|)
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpProgressFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProgressFunc
function_decl|)
parameter_list|(
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gint
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_TYPES_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ADAPTIVE_SUPERSAMPLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ADAPTIVE_SUPERSAMPLE_H__
define|#
directive|define
name|__GIMP_ADAPTIVE_SUPERSAMPLE_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
comment|/*  adaptive supersampling function taken from LibGCK  */
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
name|gulong
name|gimp_adaptive_supersample_area
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|max_depth
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|GimpRenderFunc
name|render_func
parameter_list|,
name|gpointer
name|render_data
parameter_list|,
name|GimpPutPixelFunc
name|put_pixel_func
parameter_list|,
name|gpointer
name|put_pixel_data
parameter_list|,
name|GimpProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ADAPTIVE_SUPERSAMPLE_H__ */
end_comment

end_unit


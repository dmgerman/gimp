begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrushcache.h  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_CACHE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_CACHE_H__
define|#
directive|define
name|__GIMP_BRUSH_CACHE_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BRUSH_CACHE
define|#
directive|define
name|GIMP_TYPE_BRUSH_CACHE
value|(gimp_brush_cache_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_CACHE (obj)
define|#
directive|define
name|GIMP_BRUSH_CACHE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BRUSH_CACHE, GimpBrushCache))
end_define

begin_define
DECL|macro|GIMP_BRUSH_CACHE_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_CACHE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH_CACHE, GimpBrushCacheClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_CACHE (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_CACHE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BRUSH_CACHE))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_CACHE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_CACHE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH_CACHE))
end_define

begin_define
DECL|macro|GIMP_BRUSH_CACHE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BRUSH_CACHE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BRUSH_CACHE, GimpBrushCacheClass))
end_define

begin_typedef
DECL|typedef|GimpBrushCacheClass
typedef|typedef
name|struct
name|_GimpBrushCacheClass
name|GimpBrushCacheClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushCache
struct|struct
name|_GimpBrushCache
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|data_destroy
name|GDestroyNotify
name|data_destroy
decl_stmt|;
DECL|member|last_data
name|gpointer
name|last_data
decl_stmt|;
DECL|member|last_width
name|gint
name|last_width
decl_stmt|;
DECL|member|last_height
name|gint
name|last_height
decl_stmt|;
DECL|member|last_scale
name|gdouble
name|last_scale
decl_stmt|;
DECL|member|last_aspect_ratio
name|gdouble
name|last_aspect_ratio
decl_stmt|;
DECL|member|last_angle
name|gdouble
name|last_angle
decl_stmt|;
DECL|member|last_hardness
name|gdouble
name|last_hardness
decl_stmt|;
DECL|member|debug_hit
name|gchar
name|debug_hit
decl_stmt|;
DECL|member|debug_miss
name|gchar
name|debug_miss
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushCacheClass
struct|struct
name|_GimpBrushCacheClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_brush_cache_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpBrushCache
modifier|*
name|gimp_brush_cache_new
parameter_list|(
name|GDestroyNotify
name|data_destory
parameter_list|,
name|gchar
name|debug_hit
parameter_list|,
name|gchar
name|debug_miss
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_cache_clear
parameter_list|(
name|GimpBrushCache
modifier|*
name|cache
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gconstpointer
name|gimp_brush_cache_get
parameter_list|(
name|GimpBrushCache
modifier|*
name|cache
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_cache_add
parameter_list|(
name|GimpBrushCache
modifier|*
name|cache
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|aspect_ratio
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BRUSH_CACHE_H__  */
end_comment

end_unit


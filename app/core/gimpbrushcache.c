begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrushcache.c  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushcache.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MAX_CACHED_DATA
define|#
directive|define
name|MAX_CACHED_DATA
value|20
end_define

begin_enum
enum|enum
DECL|enum|__anon294809460103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DATA_DESTROY
name|PROP_DATA_DESTROY
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpBrushCacheUnit
typedef|typedef
name|struct
name|_GimpBrushCacheUnit
name|GimpBrushCacheUnit
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushCacheUnit
struct|struct
name|_GimpBrushCacheUnit
block|{
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
DECL|member|aspect_ratio
name|gdouble
name|aspect_ratio
decl_stmt|;
DECL|member|angle
name|gdouble
name|angle
decl_stmt|;
DECL|member|reflect
name|gboolean
name|reflect
decl_stmt|;
DECL|member|hardness
name|gdouble
name|hardness
decl_stmt|;
DECL|member|op
name|GeglNode
modifier|*
name|op
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_brush_cache_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_cache_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_cache_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_cache_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBrushCache,gimp_brush_cache,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrushCache
argument_list|,
argument|gimp_brush_cache
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brush_cache_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_brush_cache_class_init
parameter_list|(
name|GimpBrushCacheClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_brush_cache_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_brush_cache_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_brush_cache_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_brush_cache_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DATA_DESTROY
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"data-destroy"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_cache_init (GimpBrushCache * brush)
name|gimp_brush_cache_init
parameter_list|(
name|GimpBrushCache
modifier|*
name|brush
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_cache_constructed (GObject * object)
name|gimp_brush_cache_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrushCache
modifier|*
name|cache
init|=
name|GIMP_BRUSH_CACHE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cache
operator|->
name|data_destroy
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_cache_finalize (GObject * object)
name|gimp_brush_cache_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrushCache
modifier|*
name|cache
init|=
name|GIMP_BRUSH_CACHE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_brush_cache_clear
argument_list|(
name|cache
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_cache_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_brush_cache_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpBrushCache
modifier|*
name|cache
init|=
name|GIMP_BRUSH_CACHE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_DATA_DESTROY
case|:
name|cache
operator|->
name|data_destroy
operator|=
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_cache_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_brush_cache_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpBrushCache
modifier|*
name|cache
init|=
name|GIMP_BRUSH_CACHE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_DATA_DESTROY
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|cache
operator|->
name|data_destroy
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpBrushCache
modifier|*
DECL|function|gimp_brush_cache_new (GDestroyNotify data_destroy,gchar debug_hit,gchar debug_miss)
name|gimp_brush_cache_new
parameter_list|(
name|GDestroyNotify
name|data_destroy
parameter_list|,
name|gchar
name|debug_hit
parameter_list|,
name|gchar
name|debug_miss
parameter_list|)
block|{
name|GimpBrushCache
modifier|*
name|cache
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|data_destroy
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cache
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH_CACHE
argument_list|,
literal|"data-destroy"
argument_list|,
name|data_destroy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cache
operator|->
name|debug_hit
operator|=
name|debug_hit
expr_stmt|;
name|cache
operator|->
name|debug_miss
operator|=
name|debug_miss
expr_stmt|;
return|return
name|cache
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_cache_clear (GimpBrushCache * cache)
name|gimp_brush_cache_clear
parameter_list|(
name|GimpBrushCache
modifier|*
name|cache
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_CACHE
argument_list|(
name|cache
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
operator|->
name|cached_units
condition|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
for|for
control|(
name|iter
operator|=
name|cache
operator|->
name|cached_units
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|GimpBrushCacheUnit
modifier|*
name|unit
init|=
name|iter
operator|->
name|data
decl_stmt|;
name|cache
operator|->
name|data_destroy
argument_list|(
name|unit
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free_full
argument_list|(
name|cache
operator|->
name|cached_units
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|cache
operator|->
name|cached_units
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gconstpointer
DECL|function|gimp_brush_cache_get (GimpBrushCache * cache,GeglNode * op,gint width,gint height,gdouble scale,gdouble aspect_ratio,gdouble angle,gboolean reflect,gdouble hardness)
name|gimp_brush_cache_get
parameter_list|(
name|GimpBrushCache
modifier|*
name|cache
parameter_list|,
name|GeglNode
modifier|*
name|op
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
name|gboolean
name|reflect
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_CACHE
argument_list|(
name|cache
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|cache
operator|->
name|cached_units
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|GimpBrushCacheUnit
modifier|*
name|unit
init|=
name|iter
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|unit
operator|->
name|data
operator|&&
name|unit
operator|->
name|width
operator|==
name|width
operator|&&
name|unit
operator|->
name|height
operator|==
name|height
operator|&&
name|unit
operator|->
name|scale
operator|==
name|scale
operator|&&
name|unit
operator|->
name|aspect_ratio
operator|==
name|aspect_ratio
operator|&&
name|unit
operator|->
name|angle
operator|==
name|angle
operator|&&
name|unit
operator|->
name|reflect
operator|==
name|reflect
operator|&&
name|unit
operator|->
name|hardness
operator|==
name|hardness
operator|&&
name|unit
operator|->
name|op
operator|==
name|op
condition|)
block|{
if|if
condition|(
name|gimp_log_flags
operator|&
name|GIMP_LOG_BRUSH_CACHE
condition|)
name|g_printerr
argument_list|(
literal|"%c"
argument_list|,
name|cache
operator|->
name|debug_hit
argument_list|)
expr_stmt|;
comment|/* Make the returned cached brush first in the list. */
name|cache
operator|->
name|cached_units
operator|=
name|g_list_remove_link
argument_list|(
name|cache
operator|->
name|cached_units
argument_list|,
name|iter
argument_list|)
expr_stmt|;
name|iter
operator|->
name|next
operator|=
name|cache
operator|->
name|cached_units
expr_stmt|;
if|if
condition|(
name|cache
operator|->
name|cached_units
condition|)
name|cache
operator|->
name|cached_units
operator|->
name|prev
operator|=
name|iter
expr_stmt|;
name|cache
operator|->
name|cached_units
operator|=
name|iter
expr_stmt|;
return|return
operator|(
name|gconstpointer
operator|)
name|unit
operator|->
name|data
return|;
block|}
block|}
if|if
condition|(
name|gimp_log_flags
operator|&
name|GIMP_LOG_BRUSH_CACHE
condition|)
name|g_printerr
argument_list|(
literal|"%c"
argument_list|,
name|cache
operator|->
name|debug_miss
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_cache_add (GimpBrushCache * cache,gpointer data,GeglNode * op,gint width,gint height,gdouble scale,gdouble aspect_ratio,gdouble angle,gboolean reflect,gdouble hardness)
name|gimp_brush_cache_add
parameter_list|(
name|GimpBrushCache
modifier|*
name|cache
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GeglNode
modifier|*
name|op
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
name|gboolean
name|reflect
parameter_list|,
name|gdouble
name|hardness
parameter_list|)
block|{
name|GList
modifier|*
name|iter
decl_stmt|;
name|GimpBrushCacheUnit
modifier|*
name|unit
decl_stmt|;
name|GList
modifier|*
name|last
init|=
name|NULL
decl_stmt|;
name|gint
name|length
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_CACHE
argument_list|(
name|cache
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|cache
operator|->
name|cached_units
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|unit
operator|=
name|iter
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|data
operator|==
name|unit
operator|->
name|data
condition|)
return|return;
name|length
operator|++
expr_stmt|;
name|last
operator|=
name|iter
expr_stmt|;
block|}
if|if
condition|(
name|length
operator|>
name|MAX_CACHED_DATA
condition|)
block|{
name|unit
operator|=
name|last
operator|->
name|data
expr_stmt|;
name|cache
operator|->
name|data_destroy
argument_list|(
name|unit
operator|->
name|data
argument_list|)
expr_stmt|;
name|cache
operator|->
name|cached_units
operator|=
name|g_list_delete_link
argument_list|(
name|cache
operator|->
name|cached_units
argument_list|,
name|last
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|unit
argument_list|)
expr_stmt|;
block|}
name|unit
operator|=
name|g_new0
argument_list|(
name|GimpBrushCacheUnit
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|unit
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|unit
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|unit
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|unit
operator|->
name|scale
operator|=
name|scale
expr_stmt|;
name|unit
operator|->
name|aspect_ratio
operator|=
name|aspect_ratio
expr_stmt|;
name|unit
operator|->
name|angle
operator|=
name|angle
expr_stmt|;
name|unit
operator|->
name|reflect
operator|=
name|reflect
expr_stmt|;
name|unit
operator|->
name|hardness
operator|=
name|hardness
expr_stmt|;
name|unit
operator|->
name|op
operator|=
name|op
expr_stmt|;
name|cache
operator|->
name|cached_units
operator|=
name|g_list_prepend
argument_list|(
name|cache
operator|->
name|cached_units
argument_list|,
name|unit
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


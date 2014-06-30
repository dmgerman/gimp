begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* This file contains the code necessary for generating on canvas  * previews, by connecting a specified GEGL operation to do the  * processing. It uses drawable filters that allow for non-destructive  * manupulation of drawable data, with live preview on screen.  *  * To create a tool that uses this, see /tools/gimpimagemaptool.c for  * the interface and /tools/gimpcolorbalancetool.c for an example of  * using that interface.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimpapplicator.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemap.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b3044860103
block|{
DECL|enumerator|FLUSH
name|FLUSH
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpImageMap
struct|struct
name|_GimpImageMap
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|undo_desc
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
DECL|member|operation
name|GeglNode
modifier|*
name|operation
decl_stmt|;
DECL|member|icon_name
name|gchar
modifier|*
name|icon_name
decl_stmt|;
DECL|member|region
name|GimpImageMapRegion
name|region
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|paint_mode
name|GimpLayerModeEffects
name|paint_mode
decl_stmt|;
DECL|member|gamma_hack
name|gboolean
name|gamma_hack
decl_stmt|;
DECL|member|filter_area
name|GeglRectangle
name|filter_area
decl_stmt|;
DECL|member|filter
name|GimpFilter
modifier|*
name|filter
decl_stmt|;
DECL|member|translate
name|GeglNode
modifier|*
name|translate
decl_stmt|;
DECL|member|crop
name|GeglNode
modifier|*
name|crop
decl_stmt|;
DECL|member|cast_before
name|GeglNode
modifier|*
name|cast_before
decl_stmt|;
DECL|member|cast_after
name|GeglNode
modifier|*
name|cast_after
decl_stmt|;
DECL|member|applicator
name|GimpApplicator
modifier|*
name|applicator
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_image_map_dispose
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
name|gimp_image_map_finalize
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
name|gimp_image_map_sync_region
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_sync_mode
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_sync_gamma_hack
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_map_is_filtering
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_map_add_filter
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_map_remove_filter
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_update_drawable
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageMap
argument_list|,
argument|gimp_image_map
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_map_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|image_map_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_class_init (GimpImageMapClass * klass)
name|gimp_image_map_class_init
parameter_list|(
name|GimpImageMapClass
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
name|image_map_signals
index|[
name|FLUSH
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"flush"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpImageMapClass
argument_list|,
name|flush
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_image_map_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_image_map_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_init (GimpImageMap * image_map)
name|gimp_image_map_init
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
name|image_map
operator|->
name|region
operator|=
name|GIMP_IMAGE_MAP_REGION_SELECTION
expr_stmt|;
name|image_map
operator|->
name|opacity
operator|=
name|GIMP_OPACITY_OPAQUE
expr_stmt|;
name|image_map
operator|->
name|paint_mode
operator|=
name|GIMP_REPLACE_MODE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_dispose (GObject * object)
name|gimp_image_map_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_map
operator|->
name|drawable
condition|)
name|gimp_viewable_preview_thaw
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_finalize (GObject * object)
name|gimp_image_map_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_map
operator|->
name|undo_desc
condition|)
block|{
name|g_free
argument_list|(
name|image_map
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|undo_desc
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_map
operator|->
name|operation
condition|)
block|{
name|g_object_unref
argument_list|(
name|image_map
operator|->
name|operation
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|operation
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_map
operator|->
name|icon_name
condition|)
block|{
name|g_free
argument_list|(
name|image_map
operator|->
name|icon_name
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|icon_name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_map
operator|->
name|filter
condition|)
block|{
name|g_object_unref
argument_list|(
name|image_map
operator|->
name|filter
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|filter
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_map
operator|->
name|applicator
condition|)
block|{
name|g_object_unref
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|applicator
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|image_map
operator|->
name|drawable
condition|)
block|{
name|g_object_unref
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
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
name|GimpImageMap
modifier|*
DECL|function|gimp_image_map_new (GimpDrawable * drawable,const gchar * undo_desc,GeglNode * operation,const gchar * icon_name)
name|gimp_image_map_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglNode
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|operation
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gegl_node_has_pad
argument_list|(
name|operation
argument_list|,
literal|"output"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_MAP
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|drawable
operator|=
name|g_object_ref
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|undo_desc
operator|=
name|g_strdup
argument_list|(
name|undo_desc
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|operation
operator|=
name|g_object_ref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|icon_name
operator|=
name|g_strdup
argument_list|(
name|icon_name
argument_list|)
expr_stmt|;
name|gimp_viewable_preview_freeze
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|image_map
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_set_region (GimpImageMap * image_map,GimpImageMapRegion region)
name|gimp_image_map_set_region
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpImageMapRegion
name|region
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|region
operator|!=
name|image_map
operator|->
name|region
condition|)
block|{
name|image_map
operator|->
name|region
operator|=
name|region
expr_stmt|;
name|gimp_image_map_sync_region
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_set_mode (GimpImageMap * image_map,gdouble opacity,GimpLayerModeEffects paint_mode)
name|gimp_image_map_set_mode
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|!=
name|image_map
operator|->
name|opacity
operator|||
name|paint_mode
operator|!=
name|image_map
operator|->
name|paint_mode
condition|)
block|{
name|image_map
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|image_map
operator|->
name|paint_mode
operator|=
name|paint_mode
expr_stmt|;
name|gimp_image_map_sync_mode
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_set_gamma_hack (GimpImageMap * image_map,gboolean gamma_hack)
name|gimp_image_map_set_gamma_hack
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|gboolean
name|gamma_hack
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gamma_hack
operator|!=
name|image_map
operator|->
name|gamma_hack
condition|)
block|{
name|image_map
operator|->
name|gamma_hack
operator|=
name|gamma_hack
expr_stmt|;
name|gimp_image_map_sync_gamma_hack
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_apply (GimpImageMap * image_map,const GeglRectangle * area)
name|gimp_image_map_apply
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|area
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|GeglRectangle
name|update_area
decl_stmt|;
name|GimpComponentMask
name|active_mask
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Make sure the drawable is still valid  */
if|if
condition|(
operator|!
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_image_map_remove_filter
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  The application should occur only within selection bounds  */
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
operator|&
name|image_map
operator|->
name|filter_area
operator|.
name|x
argument_list|,
operator|&
name|image_map
operator|->
name|filter_area
operator|.
name|y
argument_list|,
operator|&
name|image_map
operator|->
name|filter_area
operator|.
name|width
argument_list|,
operator|&
name|image_map
operator|->
name|filter_area
operator|.
name|height
argument_list|)
condition|)
block|{
name|gimp_image_map_remove_filter
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* Only update "area" because only that has changed */
if|if
condition|(
operator|!
name|area
condition|)
block|{
name|update_area
operator|=
name|image_map
operator|->
name|filter_area
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|gimp_rectangle_intersect
argument_list|(
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|,
name|image_map
operator|->
name|filter_area
operator|.
name|x
argument_list|,
name|image_map
operator|->
name|filter_area
operator|.
name|y
argument_list|,
name|image_map
operator|->
name|filter_area
operator|.
name|width
argument_list|,
name|image_map
operator|->
name|filter_area
operator|.
name|height
argument_list|,
operator|&
name|update_area
operator|.
name|x
argument_list|,
operator|&
name|update_area
operator|.
name|y
argument_list|,
operator|&
name|update_area
operator|.
name|width
argument_list|,
operator|&
name|update_area
operator|.
name|height
argument_list|)
condition|)
block|{
comment|/* Bail out, but don't remove the filter */
return|return;
block|}
if|if
condition|(
operator|!
name|image_map
operator|->
name|filter
condition|)
block|{
name|GeglNode
modifier|*
name|filter_node
decl_stmt|;
name|image_map
operator|->
name|filter
operator|=
name|gimp_filter_new
argument_list|(
name|image_map
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
name|gimp_viewable_set_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_map
operator|->
name|filter
argument_list|)
argument_list|,
name|image_map
operator|->
name|icon_name
argument_list|)
expr_stmt|;
name|filter_node
operator|=
name|gimp_filter_get_node
argument_list|(
name|image_map
operator|->
name|filter
argument_list|)
expr_stmt|;
name|gegl_node_add_child
argument_list|(
name|filter_node
argument_list|,
name|image_map
operator|->
name|operation
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|applicator
operator|=
name|gimp_applicator_new
argument_list|(
name|filter_node
argument_list|,
name|gimp_drawable_get_linear
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_filter_set_applicator
argument_list|(
name|image_map
operator|->
name|filter
argument_list|,
name|image_map
operator|->
name|applicator
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|translate
operator|=
name|gegl_node_new_child
argument_list|(
name|filter_node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:translate"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|crop
operator|=
name|gegl_node_new_child
argument_list|(
name|filter_node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:crop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|cast_before
operator|=
name|gegl_node_new_child
argument_list|(
name|filter_node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:nop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|cast_after
operator|=
name|gegl_node_new_child
argument_list|(
name|filter_node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:nop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_map_sync_region
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
name|gimp_image_map_sync_mode
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
name|gimp_image_map_sync_gamma_hack
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
if|if
condition|(
name|gegl_node_has_pad
argument_list|(
name|image_map
operator|->
name|operation
argument_list|,
literal|"input"
argument_list|)
condition|)
block|{
name|GeglNode
modifier|*
name|input
init|=
name|gegl_node_get_input_proxy
argument_list|(
name|filter_node
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
name|gegl_node_link_many
argument_list|(
name|input
argument_list|,
name|image_map
operator|->
name|translate
argument_list|,
name|image_map
operator|->
name|crop
argument_list|,
name|image_map
operator|->
name|cast_before
argument_list|,
name|image_map
operator|->
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gegl_node_link_many
argument_list|(
name|image_map
operator|->
name|operation
argument_list|,
name|image_map
operator|->
name|cast_after
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|image_map
operator|->
name|cast_after
argument_list|,
literal|"output"
argument_list|,
name|filter_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
block|}
name|active_mask
operator|=
name|gimp_drawable_get_active_mask
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
expr_stmt|;
comment|/*  don't let the filter affect the drawable projection's alpha,    *  because it can't affect the drawable buffer's alpha either    *  when finally merged (see bug #699279)    */
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
condition|)
name|active_mask
operator|&=
operator|~
name|GIMP_COMPONENT_ALPHA
expr_stmt|;
name|gimp_applicator_set_affect
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
name|active_mask
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_channel_is_empty
argument_list|(
name|mask
argument_list|)
condition|)
block|{
name|gimp_applicator_set_mask_buffer
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
name|mask_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_applicator_set_mask_buffer
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
name|mask_buffer
argument_list|)
expr_stmt|;
name|gimp_applicator_set_mask_offset
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
name|offset_y
argument_list|)
expr_stmt|;
block|}
name|gimp_image_map_add_filter
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
name|gimp_image_map_update_drawable
argument_list|(
name|image_map
argument_list|,
operator|&
name|update_area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_map_commit (GimpImageMap * image_map,GimpProgress * progress,gboolean cancelable)
name|gimp_image_map_commit
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_map_is_filtering
argument_list|(
name|image_map
argument_list|)
condition|)
block|{
name|success
operator|=
name|gimp_drawable_merge_filter
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|image_map
operator|->
name|filter
argument_list|,
name|progress
argument_list|,
name|image_map
operator|->
name|undo_desc
argument_list|,
name|cancelable
argument_list|)
expr_stmt|;
name|gimp_image_map_remove_filter
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|image_map
argument_list|,
name|image_map_signals
index|[
name|FLUSH
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_abort (GimpImageMap * image_map)
name|gimp_image_map_abort
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP
argument_list|(
name|image_map
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_map_remove_filter
argument_list|(
name|image_map
argument_list|)
condition|)
block|{
name|gimp_image_map_update_drawable
argument_list|(
name|image_map
argument_list|,
operator|&
name|image_map
operator|->
name|filter_area
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_sync_region (GimpImageMap * image_map)
name|gimp_image_map_sync_region
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
if|if
condition|(
name|image_map
operator|->
name|applicator
condition|)
block|{
if|if
condition|(
name|image_map
operator|->
name|region
operator|==
name|GIMP_IMAGE_MAP_REGION_SELECTION
condition|)
block|{
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|translate
argument_list|,
literal|"x"
argument_list|,
operator|(
name|gdouble
operator|)
operator|-
name|image_map
operator|->
name|filter_area
operator|.
name|x
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
operator|-
name|image_map
operator|->
name|filter_area
operator|.
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|crop
argument_list|,
literal|"width"
argument_list|,
operator|(
name|gdouble
operator|)
name|image_map
operator|->
name|filter_area
operator|.
name|width
argument_list|,
literal|"height"
argument_list|,
operator|(
name|gdouble
operator|)
name|image_map
operator|->
name|filter_area
operator|.
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_applicator_set_apply_offset
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
name|image_map
operator|->
name|filter_area
operator|.
name|x
argument_list|,
name|image_map
operator|->
name|filter_area
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
decl_stmt|;
name|gdouble
name|width
init|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gdouble
name|height
init|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|translate
argument_list|,
literal|"x"
argument_list|,
operator|(
name|gdouble
operator|)
literal|0.0
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
literal|0.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|crop
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_applicator_set_apply_offset
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_sync_mode (GimpImageMap * image_map)
name|gimp_image_map_sync_mode
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
if|if
condition|(
name|image_map
operator|->
name|applicator
condition|)
name|gimp_applicator_set_mode
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
name|image_map
operator|->
name|opacity
argument_list|,
name|image_map
operator|->
name|paint_mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_sync_gamma_hack (GimpImageMap * image_map)
name|gimp_image_map_sync_gamma_hack
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
if|if
condition|(
name|image_map
operator|->
name|applicator
condition|)
block|{
if|if
condition|(
name|image_map
operator|->
name|gamma_hack
condition|)
block|{
specifier|const
name|Babl
modifier|*
name|drawable_format
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|cast_format
decl_stmt|;
name|drawable_format
operator|=
name|gimp_drawable_get_format_with_alpha
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|cast_format
operator|=
name|gimp_babl_format
argument_list|(
name|gimp_babl_format_get_base_type
argument_list|(
name|drawable_format
argument_list|)
argument_list|,
name|gimp_babl_precision
argument_list|(
name|gimp_babl_format_get_component_type
argument_list|(
name|drawable_format
argument_list|)
argument_list|,
operator|!
name|gimp_babl_format_get_linear
argument_list|(
name|drawable_format
argument_list|)
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|cast_before
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:cast-format"
argument_list|,
literal|"input-format"
argument_list|,
name|drawable_format
argument_list|,
literal|"output-format"
argument_list|,
name|cast_format
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|cast_after
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:cast-format"
argument_list|,
literal|"input-format"
argument_list|,
name|cast_format
argument_list|,
literal|"output-format"
argument_list|,
name|drawable_format
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|cast_before
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:nop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|image_map
operator|->
name|cast_after
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:nop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_is_filtering (GimpImageMap * image_map)
name|gimp_image_map_is_filtering
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
if|if
condition|(
name|image_map
operator|->
name|filter
operator|&&
name|gimp_drawable_has_filter
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|image_map
operator|->
name|filter
argument_list|)
condition|)
block|{
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_add_filter (GimpImageMap * image_map)
name|gimp_image_map_add_filter
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_image_map_is_filtering
argument_list|(
name|image_map
argument_list|)
condition|)
block|{
if|if
condition|(
name|image_map
operator|->
name|filter
condition|)
block|{
name|gimp_drawable_add_filter
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|image_map
operator|->
name|filter
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_remove_filter (GimpImageMap * image_map)
name|gimp_image_map_remove_filter
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
block|{
if|if
condition|(
name|gimp_image_map_is_filtering
argument_list|(
name|image_map
argument_list|)
condition|)
block|{
name|gimp_drawable_remove_filter
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|image_map
operator|->
name|filter
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_update_drawable (GimpImageMap * image_map,const GeglRectangle * area)
name|gimp_image_map_update_drawable
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|area
parameter_list|)
block|{
name|gimp_drawable_update
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|image_map
argument_list|,
name|image_map_signals
index|[
name|FLUSH
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


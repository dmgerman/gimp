begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* This file contains the code necessary for generating on canvas  * previews, either by connecting a function to process the pixels or  * by connecting a specified GEGL operation to do the processing. It  * keeps an undo buffer to allow direct modification of the pixel data  * (so that it will show up in the projection) and it will restore the  * source in case the mapping procedure was cancelled.  *  * To create a tool that uses this, see /tools/gimpimagemaptool.c for  * the interface and /tools/gimpcolorbalancetool.c for an example of  * using that interface.  *  * Note that when talking about on canvas preview, we are speaking  * about non destructive image editing where the operation is previewd  * before being applied.  */
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
file|"gegl/gimpapplicator.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilter.h"
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
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2949b88b0103
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
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
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
name|gimp_image_map_pickable_iface_init
parameter_list|(
name|GimpPickableInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

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
name|GimpImage
modifier|*
name|gimp_image_map_get_image
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|Babl
modifier|*
name|gimp_image_map_get_format
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|Babl
modifier|*
name|gimp_image_map_get_format_with_alpha
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglBuffer
modifier|*
name|gimp_image_map_get_buffer
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_map_get_pixel_at
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpImageMap
argument_list|,
argument|gimp_image_map
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_PICKABLE,                                                 gimp_image_map_pickable_iface_init)
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
block|}
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
DECL|function|gimp_image_map_pickable_iface_init (GimpPickableInterface * iface)
name|gimp_image_map_pickable_iface_init
parameter_list|(
name|GimpPickableInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_image
operator|=
name|gimp_image_map_get_image
expr_stmt|;
name|iface
operator|->
name|get_format
operator|=
name|gimp_image_map_get_format
expr_stmt|;
name|iface
operator|->
name|get_format_with_alpha
operator|=
name|gimp_image_map_get_format_with_alpha
expr_stmt|;
name|iface
operator|->
name|get_buffer
operator|=
name|gimp_image_map_get_buffer
expr_stmt|;
name|iface
operator|->
name|get_pixel_at
operator|=
name|gimp_image_map_get_pixel_at
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
block|{ }
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
name|stock_id
condition|)
block|{
name|g_free
argument_list|(
name|image_map
operator|->
name|stock_id
argument_list|)
expr_stmt|;
name|image_map
operator|->
name|stock_id
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
specifier|static
name|GimpImage
modifier|*
DECL|function|gimp_image_map_get_image (GimpPickable * pickable)
name|gimp_image_map_get_image
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
return|return
name|gimp_pickable_get_image
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|Babl
modifier|*
DECL|function|gimp_image_map_get_format (GimpPickable * pickable)
name|gimp_image_map_get_format
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
return|return
name|gimp_pickable_get_format
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|Babl
modifier|*
DECL|function|gimp_image_map_get_format_with_alpha (GimpPickable * pickable)
name|gimp_image_map_get_format_with_alpha
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
return|return
name|gimp_pickable_get_format_with_alpha
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GeglBuffer
modifier|*
DECL|function|gimp_image_map_get_buffer (GimpPickable * pickable)
name|gimp_image_map_get_buffer
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
return|return
name|gimp_pickable_get_buffer
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_map_get_pixel_at (GimpPickable * pickable,gint x,gint y,const Babl * format,gpointer pixel)
name|gimp_image_map_get_pixel_at
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|pixel
parameter_list|)
block|{
name|GimpImageMap
modifier|*
name|image_map
init|=
name|GIMP_IMAGE_MAP
argument_list|(
name|pickable
argument_list|)
decl_stmt|;
return|return
name|gimp_pickable_get_pixel_at
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|format
argument_list|,
name|pixel
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpImageMap
modifier|*
DECL|function|gimp_image_map_new (GimpDrawable * drawable,const gchar * undo_desc,GeglNode * operation,const gchar * stock_id)
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
name|stock_id
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
name|stock_id
operator|=
name|g_strdup
argument_list|(
name|stock_id
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
DECL|function|gimp_image_map_apply (GimpImageMap * image_map)
name|gimp_image_map_apply
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
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
name|rect
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
return|return;
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
name|rect
operator|.
name|x
argument_list|,
operator|&
name|rect
operator|.
name|y
argument_list|,
operator|&
name|rect
operator|.
name|width
argument_list|,
operator|&
name|rect
operator|.
name|height
argument_list|)
condition|)
return|return;
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
name|GeglNode
modifier|*
name|filter_output
decl_stmt|;
name|GeglNode
modifier|*
name|input
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
name|gimp_viewable_set_stock_id
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
name|stock_id
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
name|input
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|filter_node
argument_list|,
literal|"input"
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
operator|&&
name|gegl_node_has_pad
argument_list|(
name|image_map
operator|->
name|operation
argument_list|,
literal|"output"
argument_list|)
condition|)
block|{
comment|/*  if there are input and output pads we probably have a            *  filter OP, connect it on both ends.            */
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
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filter_output
operator|=
name|image_map
operator|->
name|operation
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gegl_node_has_pad
argument_list|(
name|image_map
operator|->
name|operation
argument_list|,
literal|"output"
argument_list|)
condition|)
block|{
comment|/*  if there is only an output pad we probably have a            *  source OP, blend its result on top of the original            *  pixels.            */
name|GeglNode
modifier|*
name|over
init|=
name|gegl_node_new_child
argument_list|(
name|filter_node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:over"
argument_list|,
name|NULL
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
name|over
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|image_map
operator|->
name|operation
argument_list|,
literal|"output"
argument_list|,
name|over
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|filter_output
operator|=
name|over
expr_stmt|;
block|}
else|else
block|{
comment|/* otherwise we just construct a silly nop pipleline            */
name|gegl_node_link_many
argument_list|(
name|input
argument_list|,
name|image_map
operator|->
name|translate
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filter_output
operator|=
name|image_map
operator|->
name|translate
expr_stmt|;
block|}
name|gegl_node_connect_to
argument_list|(
name|filter_output
argument_list|,
literal|"output"
argument_list|,
name|filter_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gimp_applicator_set_mode
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_REPLACE_MODE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
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
name|rect
operator|.
name|x
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
operator|-
name|rect
operator|.
name|y
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
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|)
expr_stmt|;
name|gimp_applicator_set_affect
argument_list|(
name|image_map
operator|->
name|applicator
argument_list|,
name|gimp_drawable_get_active_mask
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
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
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_update
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
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

begin_function
name|void
DECL|function|gimp_image_map_commit (GimpImageMap * image_map,GimpProgress * progress)
name|gimp_image_map_commit
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpProgress
modifier|*
name|progress
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
name|g_return_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
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
name|GeglRectangle
name|rect
decl_stmt|;
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
if|if
condition|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|)
argument_list|)
operator|&&
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
name|rect
operator|.
name|x
argument_list|,
operator|&
name|rect
operator|.
name|y
argument_list|,
operator|&
name|rect
operator|.
name|width
argument_list|,
operator|&
name|rect
operator|.
name|height
argument_list|)
condition|)
block|{
name|gimp_drawable_update
argument_list|(
name|image_map
operator|->
name|drawable
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
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
block|}
block|}
end_function

end_unit


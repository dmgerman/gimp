begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gimpdrawable-floating-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-filters.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_drawable_remove_fs_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_sync_fs_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_fs_notify
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_fs_format_changed
parameter_list|(
name|GimpDrawable
modifier|*
name|signal_drawable
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_fs_affect_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_fs_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_fs_visibility_changed
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_fs_excludes_backdrop_changed
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_fs_update
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_drawable_get_floating_sel (GimpDrawable * drawable)
name|gimp_drawable_get_floating_sel
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
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
return|return
name|drawable
operator|->
name|private
operator|->
name|floating_selection
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_attach_floating_sel (GimpDrawable * drawable,GimpLayer * fs)
name|gimp_drawable_attach_floating_sel
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpLayer
modifier|*
name|fs
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|FLOATING_SELECTION
argument_list|,
literal|"%s"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|private
operator|->
name|floating_selection
operator|=
name|fs
expr_stmt|;
name|gimp_image_set_floating_selection
argument_list|(
name|image
argument_list|,
name|fs
argument_list|)
expr_stmt|;
comment|/*  clear the selection  */
name|gimp_drawable_invalidate_boundary
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_bind_visible_to_active
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_filter_set_active
argument_list|(
name|GIMP_FILTER
argument_list|(
name|fs
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|_gimp_drawable_add_floating_sel_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|fs
argument_list|,
literal|"visibility-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_fs_visibility_changed
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|fs
argument_list|,
literal|"excludes-backdrop-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_fs_excludes_backdrop_changed
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|fs
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_fs_update
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_fs_update
argument_list|(
name|fs
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_detach_floating_sel (GimpDrawable * drawable)
name|gimp_drawable_detach_floating_sel
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|fs
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_LOG
argument_list|(
name|FLOATING_SELECTION
argument_list|,
literal|"%s"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|fs
operator|=
name|drawable
operator|->
name|private
operator|->
name|floating_selection
expr_stmt|;
name|gimp_drawable_remove_fs_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|fs
argument_list|,
name|gimp_drawable_fs_visibility_changed
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|fs
argument_list|,
name|gimp_drawable_fs_excludes_backdrop_changed
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|fs
argument_list|,
name|gimp_drawable_fs_update
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_fs_update
argument_list|(
name|fs
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_item_bind_visible_to_active
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  clear the selection  */
name|gimp_drawable_invalidate_boundary
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_set_floating_selection
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|drawable
operator|->
name|private
operator|->
name|floating_selection
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GimpFilter
modifier|*
DECL|function|gimp_drawable_get_floating_sel_filter (GimpDrawable * drawable)
name|gimp_drawable_get_floating_sel_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
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
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Ensure that the graph is construced before the filter is used.    * Otherwise, we rely on the projection to cause the graph to be    * constructed, which fails for images that aren't displayed.    */
name|gimp_filter_get_node
argument_list|(
name|GIMP_FILTER
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|drawable
operator|->
name|private
operator|->
name|fs_filter
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
name|void
DECL|function|_gimp_drawable_add_floating_sel_filter (GimpDrawable * drawable)
name|_gimp_drawable_add_floating_sel_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpDrawablePrivate
modifier|*
name|private
init|=
name|drawable
operator|->
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|fs
init|=
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|fs_source
decl_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|source_node
condition|)
return|return;
name|private
operator|->
name|fs_filter
operator|=
name|gimp_filter_new
argument_list|(
name|_
argument_list|(
literal|"Floating Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_viewable_set_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|private
operator|->
name|fs_filter
argument_list|)
argument_list|,
literal|"gimp-floating-selection"
argument_list|)
expr_stmt|;
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|private
operator|->
name|fs_filter
argument_list|)
expr_stmt|;
name|fs_source
operator|=
name|gimp_drawable_get_source_node
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
comment|/* rip the fs' source node out of its graph */
if|if
condition|(
name|fs
operator|->
name|layer_offset_node
condition|)
block|{
name|gegl_node_disconnect
argument_list|(
name|fs
operator|->
name|layer_offset_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_remove_child
argument_list|(
name|gimp_filter_get_node
argument_list|(
name|GIMP_FILTER
argument_list|(
name|fs
argument_list|)
argument_list|)
argument_list|,
name|fs_source
argument_list|)
expr_stmt|;
block|}
name|gegl_node_add_child
argument_list|(
name|node
argument_list|,
name|fs_source
argument_list|)
expr_stmt|;
name|private
operator|->
name|fs_applicator
operator|=
name|gimp_applicator_new
argument_list|(
name|node
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_filter_set_applicator
argument_list|(
name|private
operator|->
name|fs_filter
argument_list|,
name|private
operator|->
name|fs_applicator
argument_list|)
expr_stmt|;
name|private
operator|->
name|fs_crop_node
operator|=
name|gegl_node_new_child
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:crop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|fs_source
argument_list|,
literal|"output"
argument_list|,
name|private
operator|->
name|fs_crop_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|private
operator|->
name|fs_crop_node
argument_list|,
literal|"output"
argument_list|,
name|node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gimp_drawable_add_filter
argument_list|(
name|drawable
argument_list|,
name|private
operator|->
name|fs_filter
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|fs
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_fs_notify
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|drawable
argument_list|,
literal|"format-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_fs_format_changed
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"component-active-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_fs_affect_changed
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"mask-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_fs_mask_changed
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_sync_fs_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_remove_fs_filter (GimpDrawable * drawable)
name|gimp_drawable_remove_fs_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpDrawablePrivate
modifier|*
name|private
init|=
name|drawable
operator|->
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|fs
init|=
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|fs_filter
condition|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|fs_source
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|fs
argument_list|,
name|gimp_drawable_fs_notify
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|drawable
argument_list|,
name|gimp_drawable_fs_format_changed
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image
argument_list|,
name|gimp_drawable_fs_affect_changed
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image
argument_list|,
name|gimp_drawable_fs_mask_changed
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_remove_filter
argument_list|(
name|drawable
argument_list|,
name|private
operator|->
name|fs_filter
argument_list|)
expr_stmt|;
name|node
operator|=
name|gimp_filter_get_node
argument_list|(
name|private
operator|->
name|fs_filter
argument_list|)
expr_stmt|;
name|fs_source
operator|=
name|gimp_drawable_get_source_node
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_node_remove_child
argument_list|(
name|node
argument_list|,
name|fs_source
argument_list|)
expr_stmt|;
comment|/* plug the fs' source node back into its graph */
if|if
condition|(
name|fs
operator|->
name|layer_offset_node
condition|)
block|{
name|gegl_node_add_child
argument_list|(
name|gimp_filter_get_node
argument_list|(
name|GIMP_FILTER
argument_list|(
name|fs
argument_list|)
argument_list|)
argument_list|,
name|fs_source
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|fs_source
argument_list|,
literal|"output"
argument_list|,
name|fs
operator|->
name|layer_offset_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|fs_filter
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|fs_applicator
argument_list|)
expr_stmt|;
name|private
operator|->
name|fs_crop_node
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_sync_fs_filter (GimpDrawable * drawable)
name|gimp_drawable_sync_fs_filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpDrawablePrivate
modifier|*
name|private
init|=
name|drawable
operator|->
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
init|=
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpLayer
modifier|*
name|fs
init|=
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|fs_off_x
decl_stmt|,
name|fs_off_y
decl_stmt|;
name|gimp_filter_set_active
argument_list|(
name|private
operator|->
name|fs_filter
argument_list|,
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|,
operator|&
name|fs_off_x
argument_list|,
operator|&
name|fs_off_y
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|private
operator|->
name|fs_crop_node
argument_list|,
literal|"x"
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|off_x
operator|-
name|fs_off_x
argument_list|)
argument_list|,
literal|"y"
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|off_y
operator|-
name|fs_off_y
argument_list|)
argument_list|,
literal|"width"
argument_list|,
operator|(
name|gdouble
operator|)
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
literal|"height"
argument_list|,
operator|(
name|gdouble
operator|)
name|gimp_item_get_height
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
name|gimp_applicator_set_apply_offset
argument_list|(
name|private
operator|->
name|fs_applicator
argument_list|,
name|fs_off_x
operator|-
name|off_x
argument_list|,
name|fs_off_y
operator|-
name|off_y
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
name|private
operator|->
name|fs_applicator
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GeglBuffer
modifier|*
name|buffer
init|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_applicator_set_mask_buffer
argument_list|(
name|private
operator|->
name|fs_applicator
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gimp_applicator_set_mask_offset
argument_list|(
name|private
operator|->
name|fs_applicator
argument_list|,
operator|-
name|off_x
argument_list|,
operator|-
name|off_y
argument_list|)
expr_stmt|;
block|}
name|gimp_applicator_set_opacity
argument_list|(
name|private
operator|->
name|fs_applicator
argument_list|,
name|gimp_layer_get_opacity
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_applicator_set_mode
argument_list|(
name|private
operator|->
name|fs_applicator
argument_list|,
name|gimp_layer_get_mode
argument_list|(
name|fs
argument_list|)
argument_list|,
name|gimp_layer_get_blend_space
argument_list|(
name|fs
argument_list|)
argument_list|,
name|gimp_layer_get_composite_space
argument_list|(
name|fs
argument_list|)
argument_list|,
name|gimp_layer_get_composite_mode
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_applicator_set_affect
argument_list|(
name|private
operator|->
name|fs_applicator
argument_list|,
name|gimp_drawable_get_active_mask
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_applicator_set_output_format
argument_list|(
name|private
operator|->
name|fs_applicator
argument_list|,
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_fs_notify (GimpLayer * fs,const GParamSpec * pspec,GimpDrawable * drawable)
name|gimp_drawable_fs_notify
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"offset-x"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"offset-y"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"visible"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"mode"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"blend-space"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"composite-space"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"composite-mode"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"opacity"
argument_list|)
condition|)
block|{
name|gimp_drawable_sync_fs_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_fs_format_changed (GimpDrawable * signal_drawable,GimpDrawable * drawable)
name|gimp_drawable_fs_format_changed
parameter_list|(
name|GimpDrawable
modifier|*
name|signal_drawable
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|fs
init|=
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gimp_drawable_sync_fs_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_fs_affect_changed (GimpImage * image,GimpChannelType channel,GimpDrawable * drawable)
name|gimp_drawable_fs_affect_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|fs
init|=
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gimp_drawable_sync_fs_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_fs_mask_changed (GimpImage * image,GimpDrawable * drawable)
name|gimp_drawable_fs_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|fs
init|=
name|gimp_drawable_get_floating_sel
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gimp_drawable_sync_fs_filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_fs_visibility_changed (GimpLayer * fs,GimpDrawable * drawable)
name|gimp_drawable_fs_visibility_changed
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|gimp_layer_get_excludes_backdrop
argument_list|(
name|fs
argument_list|)
condition|)
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
else|else
name|gimp_drawable_update
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|fs
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_fs_excludes_backdrop_changed (GimpLayer * fs,GimpDrawable * drawable)
name|gimp_drawable_fs_excludes_backdrop_changed
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|)
condition|)
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_fs_update (GimpLayer * fs,gint x,gint y,gint width,gint height,GimpDrawable * drawable)
name|gimp_drawable_fs_update
parameter_list|(
name|GimpLayer
modifier|*
name|fs
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gint
name|fs_off_x
decl_stmt|,
name|fs_off_y
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|dr_x
decl_stmt|,
name|dr_y
decl_stmt|,
name|dr_width
decl_stmt|,
name|dr_height
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|fs
argument_list|)
argument_list|,
operator|&
name|fs_off_x
argument_list|,
operator|&
name|fs_off_y
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_rectangle_intersect
argument_list|(
name|x
operator|+
name|fs_off_x
argument_list|,
name|y
operator|+
name|fs_off_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
operator|&
name|dr_x
argument_list|,
operator|&
name|dr_y
argument_list|,
operator|&
name|dr_width
argument_list|,
operator|&
name|dr_height
argument_list|)
condition|)
block|{
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|dr_x
operator|-
name|off_x
argument_list|,
name|dr_y
operator|-
name|off_y
argument_list|,
name|dr_width
argument_list|,
name|dr_height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


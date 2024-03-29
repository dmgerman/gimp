begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererdrawable.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpasync.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcancelable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-preview.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererdrawable.h"
end_include

begin_struct
DECL|struct|_GimpViewRendererDrawablePrivate
struct|struct
name|_GimpViewRendererDrawablePrivate
block|{
DECL|member|render_async
name|GimpAsync
modifier|*
name|render_async
decl_stmt|;
DECL|member|render_widget
name|GtkWidget
modifier|*
name|render_widget
decl_stmt|;
DECL|member|render_buf_x
name|gint
name|render_buf_x
decl_stmt|;
DECL|member|render_buf_y
name|gint
name|render_buf_y
decl_stmt|;
DECL|member|render_update
name|gboolean
name|render_update
decl_stmt|;
DECL|member|prev_width
name|gint
name|prev_width
decl_stmt|;
DECL|member|prev_height
name|gint
name|prev_height
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_drawable_dispose
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
name|gimp_view_renderer_drawable_invalidate
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_drawable_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_drawable_cancel_render
parameter_list|(
name|GimpViewRendererDrawable
modifier|*
name|renderdrawable
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpViewRendererDrawable,gimp_view_renderer_drawable,GIMP_TYPE_VIEW_RENDERER)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpViewRendererDrawable
argument_list|,
argument|gimp_view_renderer_drawable
argument_list|,
argument|GIMP_TYPE_VIEW_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_drawable_parent_class
end_define

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_view_renderer_drawable_class_init
parameter_list|(
name|GimpViewRendererDrawableClass
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
name|GimpViewRendererClass
modifier|*
name|renderer_class
init|=
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_view_renderer_drawable_dispose
expr_stmt|;
name|renderer_class
operator|->
name|invalidate
operator|=
name|gimp_view_renderer_drawable_invalidate
expr_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_view_renderer_drawable_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_init (GimpViewRendererDrawable * renderdrawable)
name|gimp_view_renderer_drawable_init
parameter_list|(
name|GimpViewRendererDrawable
modifier|*
name|renderdrawable
parameter_list|)
block|{
name|renderdrawable
operator|->
name|priv
operator|=
name|gimp_view_renderer_drawable_get_instance_private
argument_list|(
name|renderdrawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_dispose (GObject * object)
name|gimp_view_renderer_drawable_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpViewRendererDrawable
modifier|*
name|renderdrawable
init|=
name|GIMP_VIEW_RENDERER_DRAWABLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_view_renderer_drawable_cancel_render
argument_list|(
name|renderdrawable
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
DECL|function|gimp_view_renderer_drawable_invalidate (GimpViewRenderer * renderer)
name|gimp_view_renderer_drawable_invalidate
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
block|{
name|GimpViewRendererDrawable
modifier|*
name|renderdrawable
init|=
name|GIMP_VIEW_RENDERER_DRAWABLE
argument_list|(
name|renderer
argument_list|)
decl_stmt|;
name|gimp_view_renderer_drawable_cancel_render
argument_list|(
name|renderdrawable
argument_list|)
expr_stmt|;
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|invalidate
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_render_async_callback (GimpAsync * async,GimpViewRendererDrawable * renderdrawable)
name|gimp_view_renderer_drawable_render_async_callback
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|GimpViewRendererDrawable
modifier|*
name|renderdrawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
comment|/* rendering was canceled, and the view renderer is potentially dead (see    * gimp_view_renderer_drawable_cancel_render()).  bail.    */
if|if
condition|(
name|gimp_async_is_canceled
argument_list|(
name|async
argument_list|)
condition|)
return|return;
name|widget
operator|=
name|renderdrawable
operator|->
name|priv
operator|->
name|render_widget
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|render_async
operator|=
name|NULL
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|render_widget
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|gimp_async_is_finished
argument_list|(
name|async
argument_list|)
condition|)
block|{
name|GimpViewRenderer
modifier|*
name|renderer
init|=
name|GIMP_VIEW_RENDERER
argument_list|(
name|renderdrawable
argument_list|)
decl_stmt|;
name|GimpTempBuf
modifier|*
name|render_buf
init|=
name|gimp_async_get_result
argument_list|(
name|async
argument_list|)
decl_stmt|;
name|gimp_view_renderer_render_temp_buf
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|render_buf
argument_list|,
name|renderdrawable
operator|->
name|priv
operator|->
name|render_buf_x
argument_list|,
name|renderdrawable
operator|->
name|priv
operator|->
name|render_buf_y
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_VIEW_BG_CHECKS
argument_list|,
name|GIMP_VIEW_BG_CHECKS
argument_list|)
expr_stmt|;
if|if
condition|(
name|renderdrawable
operator|->
name|priv
operator|->
name|render_update
condition|)
name|gimp_view_renderer_update
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_drawable_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpViewRendererDrawable
modifier|*
name|renderdrawable
init|=
name|GIMP_VIEW_RENDERER_DRAWABLE
argument_list|(
name|renderer
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|icon_name
decl_stmt|;
name|GimpAsync
modifier|*
name|async
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gint
name|view_width
decl_stmt|;
name|gint
name|view_height
decl_stmt|;
name|gint
name|src_x
decl_stmt|;
name|gint
name|src_y
decl_stmt|;
name|gint
name|src_width
decl_stmt|;
name|gint
name|src_height
decl_stmt|;
name|gint
name|dst_x
decl_stmt|;
name|gint
name|dst_y
decl_stmt|;
name|gint
name|dst_width
decl_stmt|;
name|gint
name|dst_height
decl_stmt|;
name|gdouble
name|xres
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|yres
init|=
literal|1.0
decl_stmt|;
name|gboolean
name|empty
init|=
name|FALSE
decl_stmt|;
comment|/* render is already in progress */
if|if
condition|(
name|renderdrawable
operator|->
name|priv
operator|->
name|render_async
condition|)
return|return;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|icon_name
operator|=
name|gimp_viewable_get_icon_name
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|&&
operator|!
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|layer_previews
condition|)
block|{
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_width
operator|=
literal|0
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_height
operator|=
literal|0
expr_stmt|;
name|gimp_view_renderer_render_icon
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|icon_name
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|image
condition|)
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
if|if
condition|(
name|renderer
operator|->
name|is_popup
condition|)
name|image
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|image_width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|image_width
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
name|gimp_viewable_calc_preview_size
argument_list|(
name|image_width
argument_list|,
name|image_height
argument_list|,
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|,
name|renderer
operator|->
name|dot_for_dot
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|,
operator|&
name|view_width
argument_list|,
operator|&
name|view_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|src_x
operator|=
literal|0
expr_stmt|;
name|src_y
operator|=
literal|0
expr_stmt|;
name|src_width
operator|=
name|gimp_item_get_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|src_height
operator|=
name|gimp_item_get_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_rectangle_intersect
argument_list|(
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
operator|-
name|offset_x
argument_list|,
operator|-
name|offset_y
argument_list|,
name|image_width
argument_list|,
name|image_height
argument_list|,
operator|&
name|src_x
argument_list|,
operator|&
name|src_y
argument_list|,
operator|&
name|src_width
argument_list|,
operator|&
name|src_height
argument_list|)
condition|)
block|{
name|offset_x
operator|+=
name|src_x
expr_stmt|;
name|offset_y
operator|+=
name|src_y
expr_stmt|;
name|dst_x
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|view_width
operator|/
name|image_width
operator|)
operator|*
name|offset_x
argument_list|)
expr_stmt|;
name|dst_y
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|view_height
operator|/
name|image_height
operator|)
operator|*
name|offset_y
argument_list|)
expr_stmt|;
name|dst_width
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|view_width
operator|/
name|image_width
operator|)
operator|*
name|src_width
argument_list|)
expr_stmt|;
name|dst_height
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|view_height
operator|/
name|image_height
operator|)
operator|*
name|src_height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dst_x
operator|=
literal|0
expr_stmt|;
name|dst_y
operator|=
literal|0
expr_stmt|;
name|dst_width
operator|=
literal|1
expr_stmt|;
name|dst_height
operator|=
literal|1
expr_stmt|;
name|empty
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
else|else
block|{
name|dst_x
operator|=
operator|(
name|renderer
operator|->
name|width
operator|-
name|view_width
operator|)
operator|/
literal|2
expr_stmt|;
name|dst_y
operator|=
operator|(
name|renderer
operator|->
name|height
operator|-
name|view_height
operator|)
operator|/
literal|2
expr_stmt|;
name|dst_width
operator|=
name|view_width
expr_stmt|;
name|dst_height
operator|=
name|view_height
expr_stmt|;
block|}
name|dst_width
operator|=
name|MAX
argument_list|(
name|dst_width
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|dst_height
operator|=
name|MAX
argument_list|(
name|dst_height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|empty
condition|)
block|{
name|async
operator|=
name|gimp_drawable_get_sub_preview_async
argument_list|(
name|drawable
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
name|dst_width
argument_list|,
name|dst_height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|gimp_drawable_get_preview_format
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|GimpTempBuf
modifier|*
name|render_buf
decl_stmt|;
name|async
operator|=
name|gimp_async_new
argument_list|()
expr_stmt|;
name|render_buf
operator|=
name|gimp_temp_buf_new
argument_list|(
name|dst_width
argument_list|,
name|dst_height
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gimp_temp_buf_data_clear
argument_list|(
name|render_buf
argument_list|)
expr_stmt|;
name|gimp_async_finish_full
argument_list|(
name|async
argument_list|,
name|render_buf
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_temp_buf_unref
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|async
condition|)
block|{
name|renderdrawable
operator|->
name|priv
operator|->
name|render_async
operator|=
name|async
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|render_widget
operator|=
name|g_object_ref
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|render_buf_x
operator|=
name|dst_x
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|render_buf_y
operator|=
name|dst_y
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|render_update
operator|=
name|FALSE
expr_stmt|;
name|gimp_async_add_callback_for_object
argument_list|(
name|async
argument_list|,
operator|(
name|GimpAsyncCallback
operator|)
name|gimp_view_renderer_drawable_render_async_callback
argument_list|,
name|renderdrawable
argument_list|,
name|renderdrawable
argument_list|)
expr_stmt|;
comment|/* if rendering isn't done yet, update the render-view once it is, and        * either keep the old drawable preview for now, or, if size changed (or        * there's no old preview,) render an icon in the meantime.        */
if|if
condition|(
name|renderdrawable
operator|->
name|priv
operator|->
name|render_async
condition|)
block|{
name|renderdrawable
operator|->
name|priv
operator|->
name|render_update
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|renderer
operator|->
name|width
operator|!=
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_width
operator|||
name|renderer
operator|->
name|height
operator|!=
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_height
condition|)
block|{
name|gimp_view_renderer_render_icon
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|icon_name
argument_list|)
expr_stmt|;
block|}
block|}
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_width
operator|=
name|renderer
operator|->
name|width
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_height
operator|=
name|renderer
operator|->
name|height
expr_stmt|;
name|g_object_unref
argument_list|(
name|async
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_width
operator|=
literal|0
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|prev_height
operator|=
literal|0
expr_stmt|;
name|gimp_view_renderer_render_icon
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|icon_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_cancel_render (GimpViewRendererDrawable * renderdrawable)
name|gimp_view_renderer_drawable_cancel_render
parameter_list|(
name|GimpViewRendererDrawable
modifier|*
name|renderdrawable
parameter_list|)
block|{
comment|/* cancel the async render operation (if one is ongoing) without actually    * waiting for it.  if the actual rendering hasn't started yet, it will be    * immediately aborted; otherwise, it can't really be interrupted, so we just    * let it go on without blocking the main thread.    * gimp_drawable_get_sub_preview_async() can continue rendering safely even    * after the drawable had died, and our completion callback is prepared to    * handle cancellation.    */
if|if
condition|(
name|renderdrawable
operator|->
name|priv
operator|->
name|render_async
condition|)
block|{
name|gimp_cancelable_cancel
argument_list|(
name|GIMP_CANCELABLE
argument_list|(
name|renderdrawable
operator|->
name|priv
operator|->
name|render_async
argument_list|)
argument_list|)
expr_stmt|;
name|renderdrawable
operator|->
name|priv
operator|->
name|render_async
operator|=
name|NULL
expr_stmt|;
block|}
name|g_clear_object
argument_list|(
operator|&
name|renderdrawable
operator|->
name|priv
operator|->
name|render_widget
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


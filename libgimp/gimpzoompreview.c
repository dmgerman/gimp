begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpzoompreview.c  * Copyright (C) 2005  David Odin<dindinx@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"gimpzoompreview.h"
end_include

begin_define
DECL|macro|SELECTION_BORDER
define|#
directive|define
name|SELECTION_BORDER
value|2
end_define

begin_typedef
DECL|typedef|GimpZoomPreviewPrivate
typedef|typedef
name|struct
name|_GimpZoomPreviewPrivate
name|GimpZoomPreviewPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpZoomPreviewPrivate
struct|struct
name|_GimpZoomPreviewPrivate
block|{
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|zoom
name|GimpZoomModel
modifier|*
name|zoom
decl_stmt|;
DECL|member|extents
name|GdkRectangle
name|extents
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_ZOOM_PREVIEW_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_PRIVATE ((obj), GIMP_TYPE_ZOOM_PREVIEW, GimpZoomPreviewPrivate))
end_define

begin_function_decl
specifier|static
name|void
name|gimp_zoom_preview_set_adjustments
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_zoom_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_zoom_preview_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_zoom_preview_draw
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_zoom_preview_draw_buffer
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|rowstride
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_zoom_preview_draw_thumb
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_zoom_preview_get_bounds
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
modifier|*
name|xmin
parameter_list|,
name|gint
modifier|*
name|ymin
parameter_list|,
name|gint
modifier|*
name|xmax
parameter_list|,
name|gint
modifier|*
name|ymax
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpZoomPreview,gimp_zoom_preview,GIMP_TYPE_SCROLLED_PREVIEW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpZoomPreview
argument_list|,
argument|gimp_zoom_preview
argument_list|,
argument|GIMP_TYPE_SCROLLED_PREVIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_zoom_preview_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_zoom_preview_class_init
parameter_list|(
name|GimpZoomPreviewClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpPreviewClass
modifier|*
name|preview_class
init|=
name|GIMP_PREVIEW_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_zoom_preview_style_set
expr_stmt|;
name|preview_class
operator|->
name|draw
operator|=
name|gimp_zoom_preview_draw
expr_stmt|;
name|preview_class
operator|->
name|draw_buffer
operator|=
name|gimp_zoom_preview_draw_buffer
expr_stmt|;
name|preview_class
operator|->
name|draw_thumb
operator|=
name|gimp_zoom_preview_draw_thumb
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpZoomPreviewPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_preview_init (GimpZoomPreview * preview)
name|gimp_zoom_preview_init
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button_bar
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|priv
operator|->
name|zoom
operator|=
name|gimp_zoom_model_new
argument_list|()
expr_stmt|;
name|gimp_zoom_model_set_range
argument_list|(
name|GIMP_ZOOM_MODEL
argument_list|(
name|priv
operator|->
name|zoom
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|256.0
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|priv
operator|->
name|zoom
argument_list|,
literal|"notify::value"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_zoom_preview_set_adjustments
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|button_bar
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|preview
argument_list|)
argument_list|,
name|button_bar
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button_bar
argument_list|)
expr_stmt|;
comment|/* zoom out */
name|button
operator|=
name|gimp_zoom_button_new
argument_list|(
name|priv
operator|->
name|zoom
argument_list|,
name|GIMP_ZOOM_OUT
argument_list|,
name|GTK_ICON_SIZE_SMALL_TOOLBAR
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_bar
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
comment|/* zoom in */
name|button
operator|=
name|gimp_zoom_button_new
argument_list|(
name|priv
operator|->
name|zoom
argument_list|,
name|GIMP_ZOOM_IN
argument_list|,
name|GTK_ICON_SIZE_SMALL_TOOLBAR
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_bar
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
comment|/* label */
name|label
operator|=
name|gimp_prop_label_new
argument_list|(
name|G_OBJECT
argument_list|(
name|priv
operator|->
name|zoom
argument_list|)
argument_list|,
literal|"fraction"
argument_list|)
expr_stmt|;
name|gtk_misc_set_padding
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|6
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|button_bar
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|area
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_zoom_preview_size_allocate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|area
argument_list|,
literal|"check-size"
argument_list|,
name|gimp_check_size
argument_list|()
argument_list|,
literal|"check-type"
argument_list|,
name|gimp_check_type
argument_list|()
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_preview_set_adjustments (GimpZoomPreview * preview)
name|gimp_zoom_preview_set_adjustments
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpScrolledPreview
modifier|*
name|scrolled_preview
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gdouble
name|zoom_factor
decl_stmt|;
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|scrolled_preview
operator|=
name|GIMP_SCROLLED_PREVIEW
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|zoom_factor
operator|=
name|gimp_zoom_model_get_factor
argument_list|(
name|priv
operator|->
name|zoom
argument_list|)
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|zoom_factor
operator|-
literal|1.0
argument_list|)
operator|<
literal|0.05
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|scrolled_preview
operator|->
name|vscr
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|scrolled_preview
operator|->
name|hscr
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|scrolled_preview
operator|->
name|nav_icon
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|adj
operator|=
name|gtk_range_get_adjustment
argument_list|(
name|GTK_RANGE
argument_list|(
name|scrolled_preview
operator|->
name|hscr
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|->
name|lower
operator|=
literal|0
expr_stmt|;
name|adj
operator|->
name|page_size
operator|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|width
expr_stmt|;
name|adj
operator|->
name|upper
operator|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|width
operator|*
name|zoom_factor
expr_stmt|;
name|adj
operator|->
name|step_increment
operator|=
literal|1.0
expr_stmt|;
name|adj
operator|->
name|page_increment
operator|=
name|MAX
argument_list|(
name|adj
operator|->
name|page_size
operator|/
literal|2.0
argument_list|,
name|adj
operator|->
name|step_increment
argument_list|)
expr_stmt|;
name|adj
operator|->
name|value
operator|=
name|CLAMP
argument_list|(
name|adj
operator|->
name|value
argument_list|,
name|adj
operator|->
name|lower
argument_list|,
name|adj
operator|->
name|upper
operator|-
name|adj
operator|->
name|page_size
argument_list|)
expr_stmt|;
name|gtk_adjustment_changed
argument_list|(
name|adj
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gtk_range_get_adjustment
argument_list|(
name|GTK_RANGE
argument_list|(
name|scrolled_preview
operator|->
name|vscr
argument_list|)
argument_list|)
expr_stmt|;
name|adj
operator|->
name|lower
operator|=
literal|0
expr_stmt|;
name|adj
operator|->
name|page_size
operator|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|height
expr_stmt|;
name|adj
operator|->
name|upper
operator|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|height
operator|*
name|zoom_factor
expr_stmt|;
name|adj
operator|->
name|step_increment
operator|=
literal|1.0
expr_stmt|;
name|adj
operator|->
name|page_increment
operator|=
name|MAX
argument_list|(
name|adj
operator|->
name|page_size
operator|/
literal|2.0
argument_list|,
name|adj
operator|->
name|step_increment
argument_list|)
expr_stmt|;
name|adj
operator|->
name|value
operator|=
name|CLAMP
argument_list|(
name|adj
operator|->
name|value
argument_list|,
name|adj
operator|->
name|lower
argument_list|,
name|adj
operator|->
name|upper
operator|-
name|adj
operator|->
name|page_size
argument_list|)
expr_stmt|;
name|gtk_adjustment_changed
argument_list|(
name|adj
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_preview
operator|->
name|vscr
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_preview
operator|->
name|hscr
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_preview
operator|->
name|nav_icon
argument_list|)
expr_stmt|;
block|}
name|gimp_preview_invalidate
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_preview_size_allocate (GtkWidget * widget,GtkAllocation * allocation,GimpZoomPreview * preview)
name|gimp_zoom_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
block|{
name|gint
name|width
init|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|xmax
operator|-
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|xmin
decl_stmt|;
name|gint
name|height
init|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|ymax
operator|-
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|ymin
decl_stmt|;
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|width
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
name|allocation
operator|->
name|width
argument_list|)
expr_stmt|;
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|height
operator|=
name|MIN
argument_list|(
name|height
argument_list|,
name|allocation
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_zoom_preview_set_adjustments
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_preview_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_zoom_preview_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
init|=
name|GIMP_PREVIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|priv
operator|->
name|drawable
decl_stmt|;
name|gint
name|size
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"size"
argument_list|,
operator|&
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|>
name|height
condition|)
block|{
name|preview
operator|->
name|width
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|preview
operator|->
name|height
operator|=
operator|(
name|height
operator|*
name|preview
operator|->
name|width
operator|)
operator|/
name|width
expr_stmt|;
block|}
else|else
block|{
name|preview
operator|->
name|height
operator|=
name|MIN
argument_list|(
name|height
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|preview
operator|->
name|width
operator|=
operator|(
name|width
operator|*
name|preview
operator|->
name|height
operator|)
operator|/
name|height
expr_stmt|;
block|}
name|gtk_widget_set_size_request
argument_list|(
name|preview
operator|->
name|area
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|preview
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|gimp_zoom_preview_get_source (GimpZoomPreview * preview,gint * width,gint * height,gint * bpp)
name|gimp_zoom_preview_get_source
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
block|{
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|priv
operator|->
name|drawable
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
name|gdouble
name|zoom_factor
decl_stmt|;
name|GimpPreview
modifier|*
name|gimp_preview
init|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|zoom_factor
operator|=
name|gimp_zoom_model_get_factor
argument_list|(
name|priv
operator|->
name|zoom
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
name|gimp_preview
operator|->
name|width
expr_stmt|;
operator|*
name|height
operator|=
name|gimp_preview
operator|->
name|height
expr_stmt|;
name|src_x
operator|=
name|priv
operator|->
name|extents
operator|.
name|x
operator|+
name|gimp_preview
operator|->
name|xoff
operator|*
name|priv
operator|->
name|extents
operator|.
name|width
operator|/
operator|*
name|width
operator|/
name|zoom_factor
expr_stmt|;
name|src_y
operator|=
name|priv
operator|->
name|extents
operator|.
name|y
operator|+
name|gimp_preview
operator|->
name|yoff
operator|*
name|priv
operator|->
name|extents
operator|.
name|height
operator|/
operator|*
name|height
operator|/
name|zoom_factor
expr_stmt|;
name|src_width
operator|=
name|priv
operator|->
name|extents
operator|.
name|width
operator|/
name|zoom_factor
expr_stmt|;
name|src_height
operator|=
name|priv
operator|->
name|extents
operator|.
name|height
operator|/
name|zoom_factor
expr_stmt|;
name|data
operator|=
name|gimp_drawable_get_sub_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_preview_draw (GimpPreview * preview)
name|gimp_zoom_preview_draw
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|bpp
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gdouble
name|zoom_factor
decl_stmt|;
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ZOOM_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|priv
operator|->
name|drawable
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|zoom_factor
operator|=
name|gimp_zoom_model_get_factor
argument_list|(
name|priv
operator|->
name|zoom
argument_list|)
expr_stmt|;
name|width
operator|=
name|preview
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|preview
operator|->
name|height
expr_stmt|;
name|src_x
operator|=
name|priv
operator|->
name|extents
operator|.
name|x
operator|+
name|preview
operator|->
name|xoff
operator|*
name|priv
operator|->
name|extents
operator|.
name|width
operator|/
name|width
operator|/
name|zoom_factor
expr_stmt|;
name|src_y
operator|=
name|priv
operator|->
name|extents
operator|.
name|y
operator|+
name|preview
operator|->
name|yoff
operator|*
name|priv
operator|->
name|extents
operator|.
name|height
operator|/
name|height
operator|/
name|zoom_factor
expr_stmt|;
name|src_width
operator|=
name|priv
operator|->
name|extents
operator|.
name|width
operator|/
name|zoom_factor
expr_stmt|;
name|src_height
operator|=
name|priv
operator|->
name|extents
operator|.
name|height
operator|/
name|zoom_factor
expr_stmt|;
name|data
operator|=
name|gimp_drawable_get_sub_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
name|data
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_preview_draw_buffer (GimpPreview * preview,const guchar * buffer,gint rowstride)
name|gimp_zoom_preview_draw_buffer
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|rowstride
parameter_list|)
block|{
name|gint32
name|image_id
decl_stmt|;
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|priv
operator|->
name|drawable
decl_stmt|;
name|image_id
operator|=
name|gimp_drawable_get_image
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_selection_is_empty
argument_list|(
name|image_id
argument_list|)
condition|)
block|{
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|preview
operator|->
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|guchar
modifier|*
name|sel
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|gint
name|selection_id
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|selection_id
operator|=
name|gimp_image_get_selection
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|width
operator|=
name|preview
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|preview
operator|->
name|height
expr_stmt|;
name|src
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
name|sel
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|selection_id
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
name|gimp_preview_area_mask
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|preview
operator|->
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
name|src
argument_list|,
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|,
name|buffer
argument_list|,
name|rowstride
argument_list|,
name|sel
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|sel
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_zoom_preview_draw_thumb (GimpPreview * preview,GimpPreviewArea * area,gint width,gint height)
name|gimp_zoom_preview_draw_thumb
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|priv
operator|->
name|drawable
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
if|if
condition|(
name|gimp_zoom_preview_get_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
condition|)
block|{
name|buffer
operator|=
name|gimp_drawable_get_sub_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|buffer
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|buffer
condition|)
block|{
name|GimpImageType
name|type
decl_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
name|type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
break|break;
default|default:
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_preview_area_draw
argument_list|(
name|area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|buffer
argument_list|,
name|bpp
operator|*
name|width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|MAX3 (a,b,c)
define|#
directive|define
name|MAX3
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|)
value|(MAX (MAX ((a), (b)), (c)))
end_define

begin_define
DECL|macro|MIN3 (a,b,c)
define|#
directive|define
name|MIN3
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|)
value|(MIN (MIN ((a), (b)), (c)))
end_define

begin_function
specifier|static
name|gboolean
DECL|function|gimp_zoom_preview_get_bounds (GimpDrawable * drawable,gint * xmin,gint * ymin,gint * xmax,gint * ymax)
name|gimp_zoom_preview_get_bounds
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
modifier|*
name|xmin
parameter_list|,
name|gint
modifier|*
name|ymin
parameter_list|,
name|gint
modifier|*
name|xmax
parameter_list|,
name|gint
modifier|*
name|ymax
parameter_list|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
operator|*
name|xmin
operator|=
name|MAX3
argument_list|(
name|x1
operator|-
name|SELECTION_BORDER
argument_list|,
literal|0
argument_list|,
operator|-
name|offset_x
argument_list|)
expr_stmt|;
operator|*
name|ymin
operator|=
name|MAX3
argument_list|(
name|y1
operator|-
name|SELECTION_BORDER
argument_list|,
literal|0
argument_list|,
operator|-
name|offset_y
argument_list|)
expr_stmt|;
operator|*
name|xmax
operator|=
name|MIN3
argument_list|(
name|x2
operator|+
name|SELECTION_BORDER
argument_list|,
name|width
argument_list|,
name|width
operator|+
name|offset_x
argument_list|)
expr_stmt|;
operator|*
name|ymax
operator|=
name|MIN3
argument_list|(
name|y2
operator|+
name|SELECTION_BORDER
argument_list|,
name|height
argument_list|,
name|height
operator|+
name|offset_y
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_zoom_preview_new (GimpDrawable * drawable)
name|gimp_zoom_preview_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpZoomPreview
modifier|*
name|preview
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|max_width
decl_stmt|,
name|max_height
decl_stmt|;
name|GimpZoomPreviewPrivate
modifier|*
name|priv
decl_stmt|;
name|preview
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ZOOM_PREVIEW
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|priv
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|priv
operator|->
name|extents
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|priv
operator|->
name|extents
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|priv
operator|->
name|extents
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|priv
operator|->
name|extents
operator|.
name|height
operator|=
name|height
expr_stmt|;
if|if
condition|(
name|width
operator|>
name|height
condition|)
block|{
name|max_width
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
literal|512
argument_list|)
expr_stmt|;
name|max_height
operator|=
operator|(
name|height
operator|*
name|max_width
operator|)
operator|/
name|width
expr_stmt|;
block|}
else|else
block|{
name|max_height
operator|=
name|MIN
argument_list|(
name|height
argument_list|,
literal|512
argument_list|)
expr_stmt|;
name|max_width
operator|=
operator|(
name|width
operator|*
name|max_height
operator|)
operator|/
name|height
expr_stmt|;
block|}
name|gimp_preview_set_bounds
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|max_width
argument_list|,
name|max_height
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|frame
argument_list|,
literal|"ratio"
argument_list|,
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_zoom_preview_set_adjustments
argument_list|(
name|preview
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpDrawable
modifier|*
DECL|function|gimp_zoom_preview_get_drawable (GimpZoomPreview * preview)
name|gimp_zoom_preview_get_drawable
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpZoomPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ZOOM_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
return|return
name|priv
operator|->
name|drawable
return|;
block|}
end_function

end_unit


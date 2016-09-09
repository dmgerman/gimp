begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpframe.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimp3migration.h"
end_include

begin_include
include|#
directive|include
file|"gimpframe.h"
end_include

begin_comment
comment|/**  * SECTION: gimpframe  * @title: GimpFrame  * @short_description: A widget providing a HIG-compliant subclass  *                     of #GtkFrame.  *  * A widget providing a HIG-compliant subclass of #GtkFrame.  **/
end_comment

begin_define
DECL|macro|DEFAULT_LABEL_SPACING
define|#
directive|define
name|DEFAULT_LABEL_SPACING
value|6
end_define

begin_define
DECL|macro|DEFAULT_LABEL_BOLD
define|#
directive|define
name|DEFAULT_LABEL_BOLD
value|TRUE
end_define

begin_define
DECL|macro|GIMP_FRAME_INDENT_KEY
define|#
directive|define
name|GIMP_FRAME_INDENT_KEY
value|"gimp-frame-indent"
end_define

begin_define
DECL|macro|GIMP_FRAME_IN_EXPANDER_KEY
define|#
directive|define
name|GIMP_FRAME_IN_EXPANDER_KEY
value|"gimp-frame-in-expander"
end_define

begin_function_decl
specifier|static
name|void
name|gimp_frame_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_frame_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_frame_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|previous
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_frame_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_frame_child_allocate
parameter_list|(
name|GtkFrame
modifier|*
name|frame
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_frame_label_widget_notify
parameter_list|(
name|GtkFrame
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_frame_get_indent
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_frame_get_label_spacing
parameter_list|(
name|GtkFrame
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFrame,gimp_frame,GTK_TYPE_FRAME)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFrame
argument_list|,
argument|gimp_frame
argument_list|,
argument|GTK_TYPE_FRAME
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_frame_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_frame_class_init
parameter_list|(
name|GimpFrameClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|size_request
operator|=
name|gimp_frame_size_request
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_frame_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_frame_style_set
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_frame_expose_event
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"label-bold"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_LABEL_BOLD
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"label-spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_LABEL_SPACING
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_frame_init (GimpFrame * frame)
name|gimp_frame_init
parameter_list|(
name|GimpFrame
modifier|*
name|frame
parameter_list|)
block|{
name|g_signal_connect
argument_list|(
name|frame
argument_list|,
literal|"notify::label-widget"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_frame_label_widget_notify
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_frame_size_request (GtkWidget * widget,GtkRequisition * requisition)
name|gimp_frame_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
block|{
name|GtkFrame
modifier|*
name|frame
init|=
name|GTK_FRAME
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|label_widget
init|=
name|gtk_frame_get_label_widget
argument_list|(
name|frame
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
if|if
condition|(
name|label_widget
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|label_widget
argument_list|)
condition|)
block|{
name|gtk_widget_size_request
argument_list|(
name|label_widget
argument_list|,
name|requisition
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|requisition
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
literal|0
expr_stmt|;
block|}
name|requisition
operator|->
name|height
operator|+=
name|gimp_frame_get_label_spacing
argument_list|(
name|frame
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|child
argument_list|)
condition|)
block|{
name|gint
name|indent
init|=
name|gimp_frame_get_indent
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gtk_widget_size_request
argument_list|(
name|child
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|width
operator|=
name|MAX
argument_list|(
name|requisition
operator|->
name|width
argument_list|,
name|child_requisition
operator|.
name|width
operator|+
name|indent
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|height
operator|+=
name|child_requisition
operator|.
name|height
expr_stmt|;
block|}
name|border_width
operator|=
name|gtk_container_get_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|width
operator|+=
literal|2
operator|*
name|border_width
expr_stmt|;
name|requisition
operator|->
name|height
operator|+=
literal|2
operator|*
name|border_width
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_frame_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_frame_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GtkFrame
modifier|*
name|frame
init|=
name|GTK_FRAME
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|label_widget
init|=
name|gtk_frame_get_label_widget
argument_list|(
name|frame
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|GtkAllocation
name|child_allocation
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
name|gimp_frame_child_allocate
argument_list|(
name|frame
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|child
argument_list|)
condition|)
name|gtk_widget_size_allocate
argument_list|(
name|child
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|label_widget
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|label_widget
argument_list|)
condition|)
block|{
name|GtkAllocation
name|label_allocation
decl_stmt|;
name|GtkRequisition
name|label_requisition
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|border_width
operator|=
name|gtk_container_get_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_get_child_requisition
argument_list|(
name|label_widget
argument_list|,
operator|&
name|label_requisition
argument_list|)
expr_stmt|;
name|label_allocation
operator|.
name|x
operator|=
name|allocation
operator|->
name|x
operator|+
name|border_width
expr_stmt|;
name|label_allocation
operator|.
name|y
operator|=
name|allocation
operator|->
name|y
operator|+
name|border_width
expr_stmt|;
name|label_allocation
operator|.
name|width
operator|=
name|MAX
argument_list|(
name|label_requisition
operator|.
name|width
argument_list|,
name|allocation
operator|->
name|width
operator|-
literal|2
operator|*
name|border_width
argument_list|)
expr_stmt|;
name|label_allocation
operator|.
name|height
operator|=
name|label_requisition
operator|.
name|height
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|label_widget
argument_list|,
operator|&
name|label_allocation
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_frame_child_allocate (GtkFrame * frame,GtkAllocation * child_allocation)
name|gimp_frame_child_allocate
parameter_list|(
name|GtkFrame
modifier|*
name|frame
parameter_list|,
name|GtkAllocation
modifier|*
name|child_allocation
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|frame
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|label_widget
init|=
name|gtk_frame_get_label_widget
argument_list|(
name|frame
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|border_width
decl_stmt|;
name|gint
name|spacing
init|=
literal|0
decl_stmt|;
name|gint
name|indent
init|=
name|gimp_frame_get_indent
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|border_width
operator|=
name|gtk_container_get_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|label_widget
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|label_widget
argument_list|)
condition|)
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|gtk_widget_get_child_requisition
argument_list|(
name|label_widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|spacing
operator|+=
name|child_requisition
operator|.
name|height
expr_stmt|;
block|}
name|spacing
operator|+=
name|gimp_frame_get_label_spacing
argument_list|(
name|frame
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_get_direction
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_TEXT_DIR_LTR
condition|)
name|child_allocation
operator|->
name|x
operator|=
name|border_width
operator|+
name|indent
expr_stmt|;
else|else
name|child_allocation
operator|->
name|x
operator|=
name|border_width
expr_stmt|;
name|child_allocation
operator|->
name|y
operator|=
name|border_width
operator|+
name|spacing
expr_stmt|;
name|child_allocation
operator|->
name|width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|border_width
operator|-
name|indent
argument_list|)
expr_stmt|;
name|child_allocation
operator|->
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|allocation
operator|.
name|height
operator|-
name|child_allocation
operator|->
name|y
operator|-
name|border_width
argument_list|)
expr_stmt|;
name|child_allocation
operator|->
name|x
operator|+=
name|allocation
operator|.
name|x
expr_stmt|;
name|child_allocation
operator|->
name|y
operator|+=
name|allocation
operator|.
name|y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_frame_style_set (GtkWidget * widget,GtkStyle * previous)
name|gimp_frame_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|previous
parameter_list|)
block|{
comment|/*  font changes invalidate the indentation  */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_FRAME_INDENT_KEY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  for "label_bold"  */
name|gimp_frame_label_widget_notify
argument_list|(
name|GTK_FRAME
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_frame_expose_event (GtkWidget * widget,GdkEventExpose * event)
name|gimp_frame_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
if|if
condition|(
name|gtk_widget_is_drawable
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|g_type_class_peek_parent
argument_list|(
name|parent_class
argument_list|)
decl_stmt|;
return|return
name|widget_class
operator|->
name|expose_event
argument_list|(
name|widget
argument_list|,
name|event
argument_list|)
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
DECL|function|gimp_frame_label_widget_notify (GtkFrame * frame)
name|gimp_frame_label_widget_notify
parameter_list|(
name|GtkFrame
modifier|*
name|frame
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label_widget
init|=
name|gtk_frame_get_label_widget
argument_list|(
name|frame
argument_list|)
decl_stmt|;
if|if
condition|(
name|label_widget
condition|)
block|{
name|GtkLabel
modifier|*
name|label
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|label_widget
argument_list|)
condition|)
block|{
name|gfloat
name|xalign
decl_stmt|,
name|yalign
decl_stmt|;
name|label
operator|=
name|GTK_LABEL
argument_list|(
name|label_widget
argument_list|)
expr_stmt|;
name|gtk_frame_get_label_align
argument_list|(
name|frame
argument_list|,
operator|&
name|xalign
argument_list|,
operator|&
name|yalign
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|xalign
argument_list|)
expr_stmt|;
name|gtk_label_set_yalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|yalign
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GTK_IS_BIN
argument_list|(
name|label_widget
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|child
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|label_widget
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|child
argument_list|)
condition|)
name|label
operator|=
name|GTK_LABEL
argument_list|(
name|child
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|label
condition|)
block|{
name|PangoAttrList
modifier|*
name|attrs
init|=
name|pango_attr_list_new
argument_list|()
decl_stmt|;
name|PangoAttribute
modifier|*
name|attr
decl_stmt|;
name|gboolean
name|bold
decl_stmt|;
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|"label_bold"
argument_list|,
operator|&
name|bold
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|attr
operator|=
name|pango_attr_weight_new
argument_list|(
name|bold
condition|?
name|PANGO_WEIGHT_BOLD
else|:
name|PANGO_WEIGHT_NORMAL
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
operator|-
literal|1
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|gtk_label_set_attributes
argument_list|(
name|label
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_frame_get_indent (GtkWidget * widget)
name|gimp_frame_get_indent
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gint
name|width
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_FRAME_INDENT_KEY
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|width
condition|)
block|{
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
comment|/*  the HIG suggests to use four spaces so do just that  */
name|layout
operator|=
name|gtk_widget_create_pango_layout
argument_list|(
name|widget
argument_list|,
literal|"    "
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_size
argument_list|(
name|layout
argument_list|,
operator|&
name|width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_FRAME_INDENT_KEY
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|width
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|width
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_frame_get_label_spacing (GtkFrame * frame)
name|gimp_frame_get_label_spacing
parameter_list|(
name|GtkFrame
modifier|*
name|frame
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label_widget
init|=
name|gtk_frame_get_label_widget
argument_list|(
name|frame
argument_list|)
decl_stmt|;
name|gint
name|spacing
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|(
name|label_widget
operator|&&
name|gtk_widget_get_visible
argument_list|(
name|label_widget
argument_list|)
operator|)
operator|||
operator|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GIMP_FRAME_IN_EXPANDER_KEY
argument_list|)
operator|)
condition|)
block|{
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|"label_spacing"
argument_list|,
operator|&
name|spacing
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|spacing
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_frame_new:  * @label: text to set as the frame's title label (or %NULL for no title)  *  * Creates a #GimpFrame widget. A #GimpFrame is a HIG-compliant  * variant of #GtkFrame. It doesn't render a frame at all but  * otherwise behaves like a frame. The frame's title is rendered in  * bold and the frame content is indented four spaces as suggested by  * the GNOME HIG (see http://developer.gnome.org/projects/gup/hig/).  *  * Return value: a new #GimpFrame widget  *  * Since: 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_frame_new (const gchar * label)
name|gimp_frame_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gboolean
name|expander
init|=
name|FALSE
decl_stmt|;
comment|/*  somewhat hackish, should perhaps be an object property of GimpFrame  */
if|if
condition|(
name|label
operator|&&
name|strcmp
argument_list|(
name|label
argument_list|,
literal|"<expander>"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|expander
operator|=
name|TRUE
expr_stmt|;
name|label
operator|=
name|NULL
expr_stmt|;
block|}
name|frame
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FRAME
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|expander
condition|)
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GIMP_FRAME_IN_EXPANDER_KEY
argument_list|,
operator|(
name|gpointer
operator|)
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

end_unit


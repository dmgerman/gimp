begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * GtkVWrapBox: Vertical wrapping box widget  * Copyright (C) 1999 Tim Janik  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gtkvwrapbox.h"
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_comment
comment|/* --- prototypes --- */
end_comment

begin_function_decl
specifier|static
name|void
name|gtk_vwrap_box_class_init
parameter_list|(
name|GtkVWrapBoxClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gtk_vwrap_box_init
parameter_list|(
name|GtkVWrapBox
modifier|*
name|vwbox
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gtk_vwrap_box_size_request
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
name|gtk_vwrap_box_size_allocate
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
name|GSList
modifier|*
name|reverse_list_col_children
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWrapBoxChild
modifier|*
modifier|*
name|child_p
parameter_list|,
name|GtkAllocation
modifier|*
name|area
parameter_list|,
name|guint
modifier|*
name|max_width
parameter_list|,
name|gboolean
modifier|*
name|can_hexpand
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* --- variables --- */
end_comment

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|gpointer
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* --- functions --- */
end_comment

begin_function
name|GtkType
DECL|function|gtk_vwrap_box_get_type (void)
name|gtk_vwrap_box_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|vwrap_box_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|vwrap_box_type
condition|)
block|{
specifier|static
specifier|const
name|GtkTypeInfo
name|vwrap_box_info
init|=
block|{
literal|"GtkVWrapBox"
block|,
sizeof|sizeof
argument_list|(
name|GtkVWrapBox
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GtkVWrapBoxClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gtk_vwrap_box_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gtk_vwrap_box_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|vwrap_box_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_WRAP_BOX
argument_list|,
operator|&
name|vwrap_box_info
argument_list|)
expr_stmt|;
block|}
return|return
name|vwrap_box_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtk_vwrap_box_class_init (GtkVWrapBoxClass * class)
name|gtk_vwrap_box_class_init
parameter_list|(
name|GtkVWrapBoxClass
modifier|*
name|class
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|GtkContainerClass
modifier|*
name|container_class
decl_stmt|;
name|GtkWrapBoxClass
modifier|*
name|wrap_box_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|class
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|class
argument_list|)
expr_stmt|;
name|container_class
operator|=
name|GTK_CONTAINER_CLASS
argument_list|(
name|class
argument_list|)
expr_stmt|;
name|wrap_box_class
operator|=
name|GTK_WRAP_BOX_CLASS
argument_list|(
name|class
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GTK_TYPE_WRAP_BOX
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|size_request
operator|=
name|gtk_vwrap_box_size_request
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gtk_vwrap_box_size_allocate
expr_stmt|;
name|wrap_box_class
operator|->
name|rlist_line_children
operator|=
name|reverse_list_col_children
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtk_vwrap_box_init (GtkVWrapBox * vwbox)
name|gtk_vwrap_box_init
parameter_list|(
name|GtkVWrapBox
modifier|*
name|vwbox
parameter_list|)
block|{
name|vwbox
operator|->
name|max_child_height
operator|=
literal|0
expr_stmt|;
name|vwbox
operator|->
name|max_child_width
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gtk_vwrap_box_new (gboolean homogeneous)
name|gtk_vwrap_box_new
parameter_list|(
name|gboolean
name|homogeneous
parameter_list|)
block|{
name|GtkVWrapBox
modifier|*
name|vwbox
decl_stmt|;
name|vwbox
operator|=
name|GTK_VWRAP_BOX
argument_list|(
name|gtk_widget_new
argument_list|(
name|GTK_TYPE_VWRAP_BOX
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WRAP_BOX
argument_list|(
name|vwbox
argument_list|)
operator|->
name|homogeneous
operator|=
name|homogeneous
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|vwbox
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|get_child_requisition (GtkWrapBox * wbox,GtkWidget * child,GtkRequisition * child_requisition)
name|get_child_requisition
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|GtkRequisition
modifier|*
name|child_requisition
parameter_list|)
block|{
if|if
condition|(
name|wbox
operator|->
name|homogeneous
condition|)
block|{
name|GtkVWrapBox
modifier|*
name|vwbox
init|=
name|GTK_VWRAP_BOX
argument_list|(
name|wbox
argument_list|)
decl_stmt|;
name|child_requisition
operator|->
name|height
operator|=
name|vwbox
operator|->
name|max_child_height
expr_stmt|;
name|child_requisition
operator|->
name|width
operator|=
name|vwbox
operator|->
name|max_child_width
expr_stmt|;
block|}
else|else
name|gtk_widget_get_child_requisition
argument_list|(
name|child
argument_list|,
name|child_requisition
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|_gtk_vwrap_box_size_request (GtkWidget * widget,GtkRequisition * requisition)
name|_gtk_vwrap_box_size_request
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
name|GtkVWrapBox
modifier|*
name|this
init|=
name|GTK_VWRAP_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWrapBox
modifier|*
name|wbox
init|=
name|GTK_WRAP_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWrapBoxChild
modifier|*
name|child
decl_stmt|;
name|guint
name|area
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|requisition
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*<h2v-off>*/
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
name|this
operator|->
name|max_child_width
operator|=
literal|0
expr_stmt|;
name|this
operator|->
name|max_child_height
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|child
operator|=
name|wbox
operator|->
name|children
init|;
name|child
condition|;
name|child
operator|=
name|child
operator|->
name|next
control|)
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|gtk_widget_size_request
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|area
operator|+=
name|child_requisition
operator|.
name|width
operator|*
name|child_requisition
operator|.
name|height
expr_stmt|;
name|this
operator|->
name|max_child_width
operator|=
name|MAX
argument_list|(
name|this
operator|->
name|max_child_width
argument_list|,
name|child_requisition
operator|.
name|width
argument_list|)
expr_stmt|;
name|this
operator|->
name|max_child_height
operator|=
name|MAX
argument_list|(
name|this
operator|->
name|max_child_height
argument_list|,
name|child_requisition
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|wbox
operator|->
name|homogeneous
condition|)
name|area
operator|=
name|this
operator|->
name|max_child_width
operator|*
name|this
operator|->
name|max_child_height
operator|*
name|wbox
operator|->
name|n_children
expr_stmt|;
if|if
condition|(
name|area
condition|)
block|{
name|requisition
operator|->
name|width
operator|=
name|sqrt
argument_list|(
name|area
operator|*
name|wbox
operator|->
name|aspect_ratio
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
name|area
operator|/
name|requisition
operator|->
name|width
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
name|width
operator|+=
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
operator|->
name|border_width
operator|*
literal|2
expr_stmt|;
name|requisition
operator|->
name|height
operator|+=
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
operator|->
name|border_width
operator|*
literal|2
expr_stmt|;
comment|/*<h2v-on>*/
block|}
end_function

begin_function
specifier|static
name|gfloat
DECL|function|get_layout_size (GtkVWrapBox * this,guint max_height,guint * height_inc)
name|get_layout_size
parameter_list|(
name|GtkVWrapBox
modifier|*
name|this
parameter_list|,
name|guint
name|max_height
parameter_list|,
name|guint
modifier|*
name|height_inc
parameter_list|)
block|{
name|GtkWrapBox
modifier|*
name|wbox
init|=
name|GTK_WRAP_BOX
argument_list|(
name|this
argument_list|)
decl_stmt|;
name|GtkWrapBoxChild
modifier|*
name|child
decl_stmt|;
name|guint
name|n_cols
decl_stmt|,
name|left_over
init|=
literal|0
decl_stmt|,
name|total_width
init|=
literal|0
decl_stmt|;
name|gboolean
name|last_col_filled
init|=
name|TRUE
decl_stmt|;
operator|*
name|height_inc
operator|=
name|this
operator|->
name|max_child_height
operator|+
literal|1
expr_stmt|;
name|n_cols
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|child
operator|=
name|wbox
operator|->
name|children
init|;
name|child
condition|;
name|child
operator|=
name|child
operator|->
name|next
control|)
block|{
name|GtkWrapBoxChild
modifier|*
name|col_child
decl_stmt|;
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|guint
name|col_height
decl_stmt|,
name|col_width
decl_stmt|,
name|n
init|=
literal|1
decl_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
continue|continue;
name|get_child_requisition
argument_list|(
name|wbox
argument_list|,
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|last_col_filled
condition|)
operator|*
name|height_inc
operator|=
name|MIN
argument_list|(
operator|*
name|height_inc
argument_list|,
name|child_requisition
operator|.
name|height
operator|-
name|left_over
argument_list|)
expr_stmt|;
name|col_height
operator|=
name|child_requisition
operator|.
name|height
expr_stmt|;
name|col_width
operator|=
name|child_requisition
operator|.
name|width
expr_stmt|;
for|for
control|(
name|col_child
operator|=
name|child
operator|->
name|next
init|;
name|col_child
operator|&&
name|n
operator|<
name|wbox
operator|->
name|child_limit
condition|;
name|col_child
operator|=
name|col_child
operator|->
name|next
control|)
block|{
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|col_child
operator|->
name|widget
argument_list|)
condition|)
block|{
name|get_child_requisition
argument_list|(
name|wbox
argument_list|,
name|col_child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
if|if
condition|(
name|col_height
operator|+
name|wbox
operator|->
name|vspacing
operator|+
name|child_requisition
operator|.
name|height
operator|>
name|max_height
condition|)
break|break;
name|col_height
operator|+=
name|wbox
operator|->
name|vspacing
operator|+
name|child_requisition
operator|.
name|height
expr_stmt|;
name|col_width
operator|=
name|MAX
argument_list|(
name|col_width
argument_list|,
name|child_requisition
operator|.
name|width
argument_list|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
name|child
operator|=
name|col_child
expr_stmt|;
block|}
name|last_col_filled
operator|=
name|n
operator|>=
name|wbox
operator|->
name|child_limit
expr_stmt|;
name|left_over
operator|=
name|last_col_filled
condition|?
literal|0
else|:
name|max_height
operator|-
operator|(
name|col_height
operator|+
name|wbox
operator|->
name|vspacing
operator|)
expr_stmt|;
name|total_width
operator|+=
operator|(
name|n_cols
condition|?
name|wbox
operator|->
name|hspacing
else|:
literal|0
operator|)
operator|+
name|col_width
expr_stmt|;
name|n_cols
operator|++
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|height_inc
operator|>
name|this
operator|->
name|max_child_height
condition|)
operator|*
name|height_inc
operator|=
literal|0
expr_stmt|;
return|return
name|MAX
argument_list|(
name|total_width
argument_list|,
literal|1
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtk_vwrap_box_size_request (GtkWidget * widget,GtkRequisition * requisition)
name|gtk_vwrap_box_size_request
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
name|GtkVWrapBox
modifier|*
name|this
init|=
name|GTK_VWRAP_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWrapBox
modifier|*
name|wbox
init|=
name|GTK_WRAP_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWrapBoxChild
modifier|*
name|child
decl_stmt|;
name|gfloat
name|ratio_dist
decl_stmt|,
name|layout_height
init|=
literal|0
decl_stmt|;
name|guint
name|col_inc
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|requisition
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|requisition
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|this
operator|->
name|max_child_height
operator|=
literal|0
expr_stmt|;
name|this
operator|->
name|max_child_width
operator|=
literal|0
expr_stmt|;
comment|/* size_request all children */
for|for
control|(
name|child
operator|=
name|wbox
operator|->
name|children
init|;
name|child
condition|;
name|child
operator|=
name|child
operator|->
name|next
control|)
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|gtk_widget_size_request
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|this
operator|->
name|max_child_height
operator|=
name|MAX
argument_list|(
name|this
operator|->
name|max_child_height
argument_list|,
name|child_requisition
operator|.
name|height
argument_list|)
expr_stmt|;
name|this
operator|->
name|max_child_width
operator|=
name|MAX
argument_list|(
name|this
operator|->
name|max_child_width
argument_list|,
name|child_requisition
operator|.
name|width
argument_list|)
expr_stmt|;
block|}
comment|/* figure all possible layouts */
name|ratio_dist
operator|=
literal|32768
expr_stmt|;
name|layout_height
operator|=
name|this
operator|->
name|max_child_height
expr_stmt|;
do|do
block|{
name|gfloat
name|layout_width
decl_stmt|;
name|gfloat
name|ratio
decl_stmt|,
name|dist
decl_stmt|;
name|layout_height
operator|+=
name|col_inc
expr_stmt|;
name|layout_width
operator|=
name|get_layout_size
argument_list|(
name|this
argument_list|,
name|layout_height
argument_list|,
operator|&
name|col_inc
argument_list|)
expr_stmt|;
name|ratio
operator|=
name|layout_width
operator|/
name|layout_height
expr_stmt|;
comment|/*<h2v-skip>*/
name|dist
operator|=
name|MAX
argument_list|(
name|ratio
argument_list|,
name|wbox
operator|->
name|aspect_ratio
argument_list|)
operator|-
name|MIN
argument_list|(
name|ratio
argument_list|,
name|wbox
operator|->
name|aspect_ratio
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|ratio_dist
condition|)
block|{
name|ratio_dist
operator|=
name|dist
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
name|layout_height
expr_stmt|;
name|requisition
operator|->
name|width
operator|=
name|layout_width
expr_stmt|;
block|}
comment|/* g_print ("ratio for height %d width %d = %f\n", 	 (gint) layout_height, 	 (gint) layout_width, 	 ratio);       */
block|}
do|while
condition|(
name|col_inc
condition|)
do|;
name|requisition
operator|->
name|width
operator|+=
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
operator|->
name|border_width
operator|*
literal|2
expr_stmt|;
comment|/*<h2v-skip>*/
name|requisition
operator|->
name|height
operator|+=
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
operator|->
name|border_width
operator|*
literal|2
expr_stmt|;
comment|/*<h2v-skip>*/
comment|/* g_print ("choosen: height %d, width %d\n",      requisition->height,      requisition->width);   */
block|}
end_function

begin_function
specifier|static
name|GSList
modifier|*
DECL|function|reverse_list_col_children (GtkWrapBox * wbox,GtkWrapBoxChild ** child_p,GtkAllocation * area,guint * max_child_size,gboolean * expand_line)
name|reverse_list_col_children
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWrapBoxChild
modifier|*
modifier|*
name|child_p
parameter_list|,
name|GtkAllocation
modifier|*
name|area
parameter_list|,
name|guint
modifier|*
name|max_child_size
parameter_list|,
name|gboolean
modifier|*
name|expand_line
parameter_list|)
block|{
name|GSList
modifier|*
name|slist
init|=
name|NULL
decl_stmt|;
name|guint
name|height
init|=
literal|0
decl_stmt|,
name|col_height
init|=
name|area
operator|->
name|height
decl_stmt|;
name|GtkWrapBoxChild
modifier|*
name|child
init|=
operator|*
name|child_p
decl_stmt|;
operator|*
name|max_child_size
operator|=
literal|0
expr_stmt|;
operator|*
name|expand_line
operator|=
name|FALSE
expr_stmt|;
while|while
condition|(
name|child
operator|&&
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
block|{
operator|*
name|child_p
operator|=
name|child
operator|->
name|next
expr_stmt|;
name|child
operator|=
operator|*
name|child_p
expr_stmt|;
block|}
if|if
condition|(
name|child
condition|)
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|guint
name|n
init|=
literal|1
decl_stmt|;
name|get_child_requisition
argument_list|(
name|wbox
argument_list|,
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|height
operator|+=
name|child_requisition
operator|.
name|height
expr_stmt|;
operator|*
name|max_child_size
operator|=
name|MAX
argument_list|(
operator|*
name|max_child_size
argument_list|,
name|child_requisition
operator|.
name|width
argument_list|)
expr_stmt|;
operator|*
name|expand_line
operator||=
name|child
operator|->
name|hexpand
expr_stmt|;
name|slist
operator|=
name|g_slist_prepend
argument_list|(
name|slist
argument_list|,
name|child
argument_list|)
expr_stmt|;
operator|*
name|child_p
operator|=
name|child
operator|->
name|next
expr_stmt|;
name|child
operator|=
operator|*
name|child_p
expr_stmt|;
while|while
condition|(
name|child
operator|&&
name|n
operator|<
name|wbox
operator|->
name|child_limit
condition|)
block|{
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
block|{
name|get_child_requisition
argument_list|(
name|wbox
argument_list|,
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
if|if
condition|(
name|height
operator|+
name|wbox
operator|->
name|vspacing
operator|+
name|child_requisition
operator|.
name|height
operator|>
name|col_height
condition|)
break|break;
name|height
operator|+=
name|wbox
operator|->
name|vspacing
operator|+
name|child_requisition
operator|.
name|height
expr_stmt|;
operator|*
name|max_child_size
operator|=
name|MAX
argument_list|(
operator|*
name|max_child_size
argument_list|,
name|child_requisition
operator|.
name|width
argument_list|)
expr_stmt|;
operator|*
name|expand_line
operator||=
name|child
operator|->
name|hexpand
expr_stmt|;
name|slist
operator|=
name|g_slist_prepend
argument_list|(
name|slist
argument_list|,
name|child
argument_list|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
operator|*
name|child_p
operator|=
name|child
operator|->
name|next
expr_stmt|;
name|child
operator|=
operator|*
name|child_p
expr_stmt|;
block|}
block|}
return|return
name|slist
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layout_col (GtkWrapBox * wbox,GtkAllocation * area,GSList * children,guint children_per_line,gboolean hexpand)
name|layout_col
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkAllocation
modifier|*
name|area
parameter_list|,
name|GSList
modifier|*
name|children
parameter_list|,
name|guint
name|children_per_line
parameter_list|,
name|gboolean
name|hexpand
parameter_list|)
block|{
name|GSList
modifier|*
name|slist
decl_stmt|;
name|guint
name|n_children
init|=
literal|0
decl_stmt|,
name|n_expand_children
init|=
literal|0
decl_stmt|,
name|have_expand_children
init|=
literal|0
decl_stmt|,
name|total_height
init|=
literal|0
decl_stmt|;
name|gfloat
name|y
decl_stmt|,
name|height
decl_stmt|,
name|extra
decl_stmt|;
name|GtkAllocation
name|child_allocation
decl_stmt|;
for|for
control|(
name|slist
operator|=
name|children
init|;
name|slist
condition|;
name|slist
operator|=
name|slist
operator|->
name|next
control|)
block|{
name|GtkWrapBoxChild
modifier|*
name|child
init|=
name|slist
operator|->
name|data
decl_stmt|;
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|n_children
operator|++
expr_stmt|;
if|if
condition|(
name|child
operator|->
name|vexpand
condition|)
name|n_expand_children
operator|++
expr_stmt|;
name|get_child_requisition
argument_list|(
name|wbox
argument_list|,
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
name|total_height
operator|+=
name|child_requisition
operator|.
name|height
expr_stmt|;
block|}
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|area
operator|->
name|height
operator|-
operator|(
name|n_children
operator|-
literal|1
operator|)
operator|*
name|wbox
operator|->
name|vspacing
argument_list|)
expr_stmt|;
if|if
condition|(
name|height
operator|>
name|total_height
condition|)
name|extra
operator|=
name|height
operator|-
name|total_height
expr_stmt|;
else|else
name|extra
operator|=
literal|0
expr_stmt|;
name|have_expand_children
operator|=
name|n_expand_children
operator|&&
name|extra
expr_stmt|;
name|y
operator|=
name|area
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|wbox
operator|->
name|homogeneous
condition|)
block|{
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|area
operator|->
name|height
operator|-
operator|(
name|children_per_line
operator|-
literal|1
operator|)
operator|*
name|wbox
operator|->
name|vspacing
argument_list|)
expr_stmt|;
name|height
operator|/=
operator|(
operator|(
name|gdouble
operator|)
name|children_per_line
operator|)
expr_stmt|;
name|extra
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|have_expand_children
condition|)
block|{
name|height
operator|=
name|extra
expr_stmt|;
name|extra
operator|/=
operator|(
operator|(
name|gdouble
operator|)
name|n_expand_children
operator|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|wbox
operator|->
name|justify
operator|==
name|GTK_JUSTIFY_FILL
condition|)
block|{
name|height
operator|=
name|extra
expr_stmt|;
name|have_expand_children
operator|=
name|TRUE
expr_stmt|;
name|n_expand_children
operator|=
name|n_children
expr_stmt|;
name|extra
operator|/=
operator|(
operator|(
name|gdouble
operator|)
name|n_expand_children
operator|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|wbox
operator|->
name|justify
operator|==
name|GTK_JUSTIFY_CENTER
condition|)
block|{
name|y
operator|+=
name|extra
operator|/
literal|2
expr_stmt|;
name|height
operator|=
literal|0
expr_stmt|;
name|extra
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|wbox
operator|->
name|justify
operator|==
name|GTK_JUSTIFY_LEFT
condition|)
block|{
name|height
operator|=
literal|0
expr_stmt|;
name|extra
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|wbox
operator|->
name|justify
operator|==
name|GTK_JUSTIFY_RIGHT
condition|)
block|{
name|y
operator|+=
name|extra
expr_stmt|;
name|height
operator|=
literal|0
expr_stmt|;
name|extra
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|n_children
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|slist
operator|=
name|children
init|;
name|slist
condition|;
name|slist
operator|=
name|slist
operator|->
name|next
control|)
block|{
name|GtkWrapBoxChild
modifier|*
name|child
init|=
name|slist
operator|->
name|data
decl_stmt|;
name|child_allocation
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|child_allocation
operator|.
name|x
operator|=
name|area
operator|->
name|x
expr_stmt|;
if|if
condition|(
name|wbox
operator|->
name|homogeneous
condition|)
block|{
name|child_allocation
operator|.
name|width
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|child_allocation
operator|.
name|height
operator|=
name|height
expr_stmt|;
name|y
operator|+=
name|child_allocation
operator|.
name|height
operator|+
name|wbox
operator|->
name|vspacing
expr_stmt|;
block|}
else|else
block|{
name|GtkRequisition
name|child_requisition
decl_stmt|;
name|get_child_requisition
argument_list|(
name|wbox
argument_list|,
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_requisition
argument_list|)
expr_stmt|;
if|if
condition|(
name|child_requisition
operator|.
name|width
operator|>=
name|area
operator|->
name|width
condition|)
name|child_allocation
operator|.
name|width
operator|=
name|area
operator|->
name|width
expr_stmt|;
else|else
block|{
name|child_allocation
operator|.
name|width
operator|=
name|child_requisition
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|wbox
operator|->
name|line_justify
operator|==
name|GTK_JUSTIFY_FILL
operator|||
name|child
operator|->
name|hfill
condition|)
name|child_allocation
operator|.
name|width
operator|=
name|area
operator|->
name|width
expr_stmt|;
elseif|else
if|if
condition|(
name|child
operator|->
name|hexpand
operator|||
name|wbox
operator|->
name|line_justify
operator|==
name|GTK_JUSTIFY_CENTER
condition|)
name|child_allocation
operator|.
name|x
operator|+=
operator|(
name|area
operator|->
name|width
operator|-
name|child_requisition
operator|.
name|width
operator|)
operator|/
literal|2
expr_stmt|;
elseif|else
if|if
condition|(
name|wbox
operator|->
name|line_justify
operator|==
name|GTK_JUSTIFY_BOTTOM
condition|)
name|child_allocation
operator|.
name|x
operator|+=
name|area
operator|->
name|width
operator|-
name|child_requisition
operator|.
name|width
expr_stmt|;
block|}
if|if
condition|(
name|have_expand_children
condition|)
block|{
name|child_allocation
operator|.
name|height
operator|=
name|child_requisition
operator|.
name|height
expr_stmt|;
if|if
condition|(
name|child
operator|->
name|vexpand
operator|||
name|wbox
operator|->
name|justify
operator|==
name|GTK_JUSTIFY_FILL
condition|)
block|{
name|guint
name|space
decl_stmt|;
name|n_expand_children
operator|--
expr_stmt|;
name|space
operator|=
name|extra
operator|*
name|n_expand_children
expr_stmt|;
name|space
operator|=
name|height
operator|-
name|space
expr_stmt|;
name|height
operator|-=
name|space
expr_stmt|;
if|if
condition|(
name|child
operator|->
name|vfill
condition|)
name|child_allocation
operator|.
name|height
operator|+=
name|space
expr_stmt|;
else|else
block|{
name|child_allocation
operator|.
name|y
operator|+=
name|space
operator|/
literal|2
expr_stmt|;
name|y
operator|+=
name|space
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
comment|/* g_print ("child_allocation.y %d += %d * %f ", 		       child_allocation.y, n_children, extra); */
name|child_allocation
operator|.
name|y
operator|+=
name|n_children
operator|*
name|extra
expr_stmt|;
comment|/* g_print ("= %d\n", 		       child_allocation.y); */
name|child_allocation
operator|.
name|height
operator|=
name|MIN
argument_list|(
name|child_requisition
operator|.
name|height
argument_list|,
name|area
operator|->
name|height
operator|-
name|child_allocation
operator|.
name|y
operator|+
name|area
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
block|}
name|y
operator|+=
name|child_allocation
operator|.
name|height
operator|+
name|wbox
operator|->
name|vspacing
expr_stmt|;
name|gtk_widget_size_allocate
argument_list|(
name|child
operator|->
name|widget
argument_list|,
operator|&
name|child_allocation
argument_list|)
expr_stmt|;
name|n_children
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_typedef
DECL|typedef|Line
typedef|typedef
name|struct
name|_Line
name|Line
typedef|;
end_typedef

begin_struct
DECL|struct|_Line
struct|struct
name|_Line
block|{
DECL|member|children
name|GSList
modifier|*
name|children
decl_stmt|;
DECL|member|min_size
name|guint16
name|min_size
decl_stmt|;
DECL|member|expand
name|guint
name|expand
range|:
literal|1
decl_stmt|;
DECL|member|next
name|Line
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|layout_cols (GtkWrapBox * wbox,GtkAllocation * area)
name|layout_cols
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkAllocation
modifier|*
name|area
parameter_list|)
block|{
name|GtkWrapBoxChild
modifier|*
name|next_child
decl_stmt|;
name|guint
name|min_width
decl_stmt|;
name|gboolean
name|hexpand
decl_stmt|;
name|GSList
modifier|*
name|slist
decl_stmt|;
name|Line
modifier|*
name|line_list
init|=
name|NULL
decl_stmt|;
name|guint
name|total_width
init|=
literal|0
decl_stmt|,
name|n_expand_lines
init|=
literal|0
decl_stmt|,
name|n_lines
init|=
literal|0
decl_stmt|;
name|gfloat
name|shrink_width
decl_stmt|;
name|guint
name|children_per_line
decl_stmt|;
name|next_child
operator|=
name|wbox
operator|->
name|children
expr_stmt|;
name|slist
operator|=
name|GTK_WRAP_BOX_GET_CLASS
argument_list|(
name|wbox
argument_list|)
operator|->
name|rlist_line_children
argument_list|(
name|wbox
argument_list|,
operator|&
name|next_child
argument_list|,
name|area
argument_list|,
operator|&
name|min_width
argument_list|,
operator|&
name|hexpand
argument_list|)
expr_stmt|;
name|slist
operator|=
name|g_slist_reverse
argument_list|(
name|slist
argument_list|)
expr_stmt|;
name|children_per_line
operator|=
name|g_slist_length
argument_list|(
name|slist
argument_list|)
expr_stmt|;
while|while
condition|(
name|slist
condition|)
block|{
name|Line
modifier|*
name|line
init|=
name|g_new
argument_list|(
name|Line
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|line
operator|->
name|children
operator|=
name|slist
expr_stmt|;
name|line
operator|->
name|min_size
operator|=
name|min_width
expr_stmt|;
name|total_width
operator|+=
name|min_width
expr_stmt|;
name|line
operator|->
name|expand
operator|=
name|hexpand
expr_stmt|;
if|if
condition|(
name|hexpand
condition|)
name|n_expand_lines
operator|++
expr_stmt|;
name|line
operator|->
name|next
operator|=
name|line_list
expr_stmt|;
name|line_list
operator|=
name|line
expr_stmt|;
name|n_lines
operator|++
expr_stmt|;
name|slist
operator|=
name|GTK_WRAP_BOX_GET_CLASS
argument_list|(
name|wbox
argument_list|)
operator|->
name|rlist_line_children
argument_list|(
name|wbox
argument_list|,
operator|&
name|next_child
argument_list|,
name|area
argument_list|,
operator|&
name|min_width
argument_list|,
operator|&
name|hexpand
argument_list|)
expr_stmt|;
name|slist
operator|=
name|g_slist_reverse
argument_list|(
name|slist
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|total_width
operator|>
name|area
operator|->
name|width
condition|)
name|shrink_width
operator|=
name|total_width
operator|-
name|area
operator|->
name|width
expr_stmt|;
else|else
name|shrink_width
operator|=
literal|0
expr_stmt|;
if|if
condition|(
literal|1
condition|)
comment|/* reverse lines and shrink */
block|{
name|Line
modifier|*
name|prev
init|=
name|NULL
decl_stmt|,
modifier|*
name|last
init|=
name|NULL
decl_stmt|;
name|gfloat
name|n_shrink_lines
init|=
name|n_lines
decl_stmt|;
while|while
condition|(
name|line_list
condition|)
block|{
name|Line
modifier|*
name|tmp
init|=
name|line_list
operator|->
name|next
decl_stmt|;
if|if
condition|(
name|shrink_width
condition|)
block|{
name|Line
modifier|*
name|line
init|=
name|line_list
decl_stmt|;
name|guint
name|shrink_fract
init|=
name|shrink_width
operator|/
name|n_shrink_lines
operator|+
literal|0.5
decl_stmt|;
if|if
condition|(
name|line
operator|->
name|min_size
operator|>
name|shrink_fract
condition|)
block|{
name|shrink_width
operator|-=
name|shrink_fract
expr_stmt|;
name|line
operator|->
name|min_size
operator|-=
name|shrink_fract
expr_stmt|;
block|}
else|else
block|{
name|shrink_width
operator|-=
name|line
operator|->
name|min_size
operator|-
literal|1
expr_stmt|;
name|line
operator|->
name|min_size
operator|=
literal|1
expr_stmt|;
block|}
block|}
name|n_shrink_lines
operator|--
expr_stmt|;
name|last
operator|=
name|line_list
expr_stmt|;
name|line_list
operator|->
name|next
operator|=
name|prev
expr_stmt|;
name|prev
operator|=
name|line_list
expr_stmt|;
name|line_list
operator|=
name|tmp
expr_stmt|;
block|}
name|line_list
operator|=
name|last
expr_stmt|;
block|}
if|if
condition|(
name|n_lines
condition|)
block|{
name|Line
modifier|*
name|line
decl_stmt|;
name|gfloat
name|x
decl_stmt|,
name|width
decl_stmt|,
name|extra
init|=
literal|0
decl_stmt|;
name|width
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|width
operator|=
name|MAX
argument_list|(
name|n_lines
argument_list|,
name|width
operator|-
operator|(
name|n_lines
operator|-
literal|1
operator|)
operator|*
name|wbox
operator|->
name|hspacing
argument_list|)
expr_stmt|;
if|if
condition|(
name|wbox
operator|->
name|homogeneous
condition|)
name|width
operator|/=
operator|(
operator|(
name|gdouble
operator|)
name|n_lines
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|n_expand_lines
condition|)
block|{
name|width
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|width
operator|-
name|total_width
argument_list|)
expr_stmt|;
name|extra
operator|=
name|width
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|n_expand_lines
operator|)
expr_stmt|;
block|}
else|else
name|width
operator|=
literal|0
expr_stmt|;
name|x
operator|=
name|area
operator|->
name|x
expr_stmt|;
name|line
operator|=
name|line_list
expr_stmt|;
while|while
condition|(
name|line
condition|)
block|{
name|GtkAllocation
name|col_allocation
decl_stmt|;
name|Line
modifier|*
name|next_line
init|=
name|line
operator|->
name|next
decl_stmt|;
name|col_allocation
operator|.
name|y
operator|=
name|area
operator|->
name|y
expr_stmt|;
name|col_allocation
operator|.
name|height
operator|=
name|area
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|wbox
operator|->
name|homogeneous
condition|)
name|col_allocation
operator|.
name|width
operator|=
name|width
expr_stmt|;
else|else
block|{
name|col_allocation
operator|.
name|width
operator|=
name|line
operator|->
name|min_size
expr_stmt|;
if|if
condition|(
name|line
operator|->
name|expand
condition|)
name|col_allocation
operator|.
name|width
operator|+=
name|extra
expr_stmt|;
block|}
name|col_allocation
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|x
operator|+=
name|col_allocation
operator|.
name|width
operator|+
name|wbox
operator|->
name|hspacing
expr_stmt|;
name|layout_col
argument_list|(
name|wbox
argument_list|,
operator|&
name|col_allocation
argument_list|,
name|line
operator|->
name|children
argument_list|,
name|children_per_line
argument_list|,
name|line
operator|->
name|expand
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|line
operator|->
name|children
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|line
argument_list|)
expr_stmt|;
name|line
operator|=
name|next_line
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtk_vwrap_box_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gtk_vwrap_box_size_allocate
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
name|GtkWrapBox
modifier|*
name|wbox
init|=
name|GTK_WRAP_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|area
decl_stmt|;
name|guint
name|border
init|=
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
operator|->
name|border_width
decl_stmt|;
comment|/*<h2v-skip>*/
name|widget
operator|->
name|allocation
operator|=
operator|*
name|allocation
expr_stmt|;
name|area
operator|.
name|y
operator|=
name|allocation
operator|->
name|y
operator|+
name|border
expr_stmt|;
name|area
operator|.
name|x
operator|=
name|allocation
operator|->
name|x
operator|+
name|border
expr_stmt|;
name|area
operator|.
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
operator|(
name|gint
operator|)
name|allocation
operator|->
name|height
operator|-
name|border
operator|*
literal|2
argument_list|)
expr_stmt|;
name|area
operator|.
name|width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
operator|(
name|gint
operator|)
name|allocation
operator|->
name|width
operator|-
name|border
operator|*
literal|2
argument_list|)
expr_stmt|;
comment|/*<h2v-off>*/
comment|/* g_print ("got: width %d, height %d\n",      allocation->width,      allocation->height);   */
comment|/*<h2v-on>*/
name|layout_cols
argument_list|(
name|wbox
argument_list|,
operator|&
name|area
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


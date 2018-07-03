begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayxfer.h"
end_include

begin_define
DECL|macro|NUM_PAGES
define|#
directive|define
name|NUM_PAGES
value|2
end_define

begin_typedef
DECL|typedef|RTree
typedef|typedef
name|struct
name|_RTree
name|RTree
typedef|;
end_typedef

begin_typedef
DECL|typedef|RTreeNode
typedef|typedef
name|struct
name|_RTreeNode
name|RTreeNode
typedef|;
end_typedef

begin_struct
DECL|struct|_RTreeNode
struct|struct
name|_RTreeNode
block|{
DECL|member|children
name|RTreeNode
modifier|*
name|children
index|[
literal|2
index|]
decl_stmt|;
DECL|member|next
name|RTreeNode
modifier|*
name|next
decl_stmt|;
DECL|member|x
DECL|member|y
DECL|member|w
DECL|member|h
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_RTree
struct|struct
name|_RTree
block|{
DECL|member|root
name|RTreeNode
name|root
decl_stmt|;
DECL|member|available
name|RTreeNode
modifier|*
name|available
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDisplayXfer
struct|struct
name|_GimpDisplayXfer
block|{
comment|/* track subregions of render_surface for efficient uploads */
DECL|member|rtree
name|RTree
name|rtree
decl_stmt|;
DECL|member|render_surface
name|cairo_surface_t
modifier|*
name|render_surface
index|[
name|NUM_PAGES
index|]
decl_stmt|;
DECL|member|page
name|gint
name|page
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|GIMP_DISPLAY_RENDER_BUF_WIDTH
name|gint
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
init|=
literal|256
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|GIMP_DISPLAY_RENDER_BUF_HEIGHT
name|gint
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
init|=
literal|256
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|RTreeNode
modifier|*
DECL|function|rtree_node_create (RTree * rtree,RTreeNode ** prev,gint x,gint y,gint w,gint h)
name|rtree_node_create
parameter_list|(
name|RTree
modifier|*
name|rtree
parameter_list|,
name|RTreeNode
modifier|*
modifier|*
name|prev
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|RTreeNode
modifier|*
name|node
decl_stmt|;
name|gimp_assert
argument_list|(
name|x
operator|>=
literal|0
operator|&&
name|x
operator|+
name|w
operator|<=
name|rtree
operator|->
name|root
operator|.
name|w
argument_list|)
expr_stmt|;
name|gimp_assert
argument_list|(
name|y
operator|>=
literal|0
operator|&&
name|y
operator|+
name|h
operator|<=
name|rtree
operator|->
name|root
operator|.
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|w
operator|<=
literal|0
operator|||
name|h
operator|<=
literal|0
condition|)
return|return
name|NULL
return|;
name|node
operator|=
name|g_slice_alloc
argument_list|(
sizeof|sizeof
argument_list|(
operator|*
name|node
argument_list|)
argument_list|)
expr_stmt|;
name|node
operator|->
name|children
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|children
index|[
literal|1
index|]
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|node
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|node
operator|->
name|w
operator|=
name|w
expr_stmt|;
name|node
operator|->
name|h
operator|=
name|h
expr_stmt|;
name|node
operator|->
name|next
operator|=
operator|*
name|prev
expr_stmt|;
operator|*
name|prev
operator|=
name|node
expr_stmt|;
return|return
name|node
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rtree_node_destroy (RTree * rtree,RTreeNode * node)
name|rtree_node_destroy
parameter_list|(
name|RTree
modifier|*
name|rtree
parameter_list|,
name|RTreeNode
modifier|*
name|node
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|node
operator|->
name|children
index|[
name|i
index|]
condition|)
name|rtree_node_destroy
argument_list|(
name|rtree
argument_list|,
name|node
operator|->
name|children
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|RTreeNode
argument_list|,
name|node
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|RTreeNode
modifier|*
DECL|function|rtree_node_insert (RTree * rtree,RTreeNode ** prev,RTreeNode * node,gint w,gint h)
name|rtree_node_insert
parameter_list|(
name|RTree
modifier|*
name|rtree
parameter_list|,
name|RTreeNode
modifier|*
modifier|*
name|prev
parameter_list|,
name|RTreeNode
modifier|*
name|node
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
operator|*
name|prev
operator|=
name|node
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|node
operator|->
name|w
operator|-
name|w
operator|)
operator||
operator|(
name|node
operator|->
name|h
operator|-
name|h
operator|)
operator|)
operator|>
literal|1
condition|)
block|{
name|gint
name|ww
init|=
name|node
operator|->
name|w
operator|-
name|w
decl_stmt|;
name|gint
name|hh
init|=
name|node
operator|->
name|h
operator|-
name|h
decl_stmt|;
if|if
condition|(
name|ww
operator|>=
name|hh
condition|)
block|{
name|node
operator|->
name|children
index|[
literal|0
index|]
operator|=
name|rtree_node_create
argument_list|(
name|rtree
argument_list|,
name|prev
argument_list|,
name|node
operator|->
name|x
operator|+
name|w
argument_list|,
name|node
operator|->
name|y
argument_list|,
name|ww
argument_list|,
name|node
operator|->
name|h
argument_list|)
expr_stmt|;
name|node
operator|->
name|children
index|[
literal|1
index|]
operator|=
name|rtree_node_create
argument_list|(
name|rtree
argument_list|,
name|prev
argument_list|,
name|node
operator|->
name|x
argument_list|,
name|node
operator|->
name|y
operator|+
name|h
argument_list|,
name|w
argument_list|,
name|hh
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|node
operator|->
name|children
index|[
literal|0
index|]
operator|=
name|rtree_node_create
argument_list|(
name|rtree
argument_list|,
name|prev
argument_list|,
name|node
operator|->
name|x
argument_list|,
name|node
operator|->
name|y
operator|+
name|h
argument_list|,
name|node
operator|->
name|w
argument_list|,
name|hh
argument_list|)
expr_stmt|;
name|node
operator|->
name|children
index|[
literal|1
index|]
operator|=
name|rtree_node_create
argument_list|(
name|rtree
argument_list|,
name|prev
argument_list|,
name|node
operator|->
name|x
operator|+
name|w
argument_list|,
name|node
operator|->
name|y
argument_list|,
name|ww
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|node
return|;
block|}
end_function

begin_function
specifier|static
name|RTreeNode
modifier|*
DECL|function|rtree_insert (RTree * rtree,gint w,gint h)
name|rtree_insert
parameter_list|(
name|RTree
modifier|*
name|rtree
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|RTreeNode
modifier|*
name|node
decl_stmt|,
modifier|*
modifier|*
name|prev
decl_stmt|;
for|for
control|(
name|prev
operator|=
operator|&
name|rtree
operator|->
name|available
init|;
operator|(
name|node
operator|=
operator|*
name|prev
operator|)
condition|;
name|prev
operator|=
operator|&
name|node
operator|->
name|next
control|)
if|if
condition|(
name|node
operator|->
name|w
operator|>=
name|w
operator|&&
name|node
operator|->
name|h
operator|>=
name|h
condition|)
return|return
name|rtree_node_insert
argument_list|(
name|rtree
argument_list|,
name|prev
argument_list|,
name|node
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rtree_init (RTree * rtree,gint w,gint h)
name|rtree_init
parameter_list|(
name|RTree
modifier|*
name|rtree
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|rtree
operator|->
name|root
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|rtree
operator|->
name|root
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|rtree
operator|->
name|root
operator|.
name|w
operator|=
name|w
expr_stmt|;
name|rtree
operator|->
name|root
operator|.
name|h
operator|=
name|h
expr_stmt|;
name|rtree
operator|->
name|root
operator|.
name|children
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
name|rtree
operator|->
name|root
operator|.
name|children
index|[
literal|1
index|]
operator|=
name|NULL
expr_stmt|;
name|rtree
operator|->
name|root
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
name|rtree
operator|->
name|available
operator|=
operator|&
name|rtree
operator|->
name|root
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rtree_reset (RTree * rtree)
name|rtree_reset
parameter_list|(
name|RTree
modifier|*
name|rtree
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|rtree
operator|->
name|root
operator|.
name|children
index|[
name|i
index|]
operator|==
name|NULL
condition|)
continue|continue;
name|rtree_node_destroy
argument_list|(
name|rtree
argument_list|,
name|rtree
operator|->
name|root
operator|.
name|children
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|rtree
operator|->
name|root
operator|.
name|children
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
name|rtree
operator|->
name|root
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
name|rtree
operator|->
name|available
operator|=
operator|&
name|rtree
operator|->
name|root
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|xfer_destroy (void * data)
name|xfer_destroy
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
block|{
name|GimpDisplayXfer
modifier|*
name|xfer
init|=
name|data
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|NUM_PAGES
condition|;
name|i
operator|++
control|)
name|cairo_surface_destroy
argument_list|(
name|xfer
operator|->
name|render_surface
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|rtree_reset
argument_list|(
operator|&
name|xfer
operator|->
name|rtree
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|xfer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpDisplayXfer
modifier|*
DECL|function|gimp_display_xfer_realize (GtkWidget * widget)
name|gimp_display_xfer_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GimpDisplayXfer
modifier|*
name|xfer
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|env
decl_stmt|;
name|env
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_DISPLAY_RENDER_BUF_SIZE"
argument_list|)
expr_stmt|;
if|if
condition|(
name|env
condition|)
block|{
name|gint
name|width
init|=
name|atoi
argument_list|(
name|env
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|width
decl_stmt|;
name|env
operator|=
name|strchr
argument_list|(
name|env
argument_list|,
literal|'x'
argument_list|)
expr_stmt|;
if|if
condition|(
name|env
condition|)
name|height
operator|=
name|atoi
argument_list|(
name|env
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|>
literal|0
operator|&&
name|width
operator|<=
literal|8192
operator|&&
name|height
operator|>
literal|0
operator|&&
name|height
operator|<=
literal|8192
condition|)
block|{
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
operator|=
name|width
expr_stmt|;
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
operator|=
name|height
expr_stmt|;
block|}
block|}
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|xfer
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|screen
argument_list|)
argument_list|,
literal|"gimp-display-xfer"
argument_list|)
expr_stmt|;
if|if
condition|(
name|xfer
operator|==
name|NULL
condition|)
block|{
name|GdkDrawingContext
modifier|*
name|context
decl_stmt|;
name|cairo_region_t
modifier|*
name|region
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gint
name|w
init|=
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
decl_stmt|;
name|gint
name|h
init|=
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
decl_stmt|;
name|int
name|n
decl_stmt|;
name|xfer
operator|=
name|g_new
argument_list|(
name|GimpDisplayXfer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|rtree_init
argument_list|(
operator|&
name|xfer
operator|->
name|rtree
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|region
operator|=
name|cairo_region_create
argument_list|()
expr_stmt|;
name|context
operator|=
name|gdk_window_begin_draw_frame
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|region
argument_list|)
expr_stmt|;
name|cr
operator|=
name|gdk_drawing_context_get_cairo_context
argument_list|(
name|context
argument_list|)
expr_stmt|;
for|for
control|(
name|n
operator|=
literal|0
init|;
name|n
operator|<
name|NUM_PAGES
condition|;
name|n
operator|++
control|)
block|{
name|xfer
operator|->
name|render_surface
index|[
name|n
index|]
operator|=
name|cairo_surface_create_similar_image
argument_list|(
name|cairo_get_target
argument_list|(
name|cr
argument_list|)
argument_list|,
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|cairo_surface_mark_dirty
argument_list|(
name|xfer
operator|->
name|render_surface
index|[
name|n
index|]
argument_list|)
expr_stmt|;
block|}
name|gdk_window_end_draw_frame
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|xfer
operator|->
name|page
operator|=
literal|0
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|screen
argument_list|)
argument_list|,
literal|"gimp-display-xfer"
argument_list|,
name|xfer
argument_list|,
name|xfer_destroy
argument_list|)
expr_stmt|;
block|}
return|return
name|xfer
return|;
block|}
end_function

begin_function
name|cairo_surface_t
modifier|*
DECL|function|gimp_display_xfer_get_surface (GimpDisplayXfer * xfer,gint w,gint h,gint * src_x,gint * src_y)
name|gimp_display_xfer_get_surface
parameter_list|(
name|GimpDisplayXfer
modifier|*
name|xfer
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
modifier|*
name|src_x
parameter_list|,
name|gint
modifier|*
name|src_y
parameter_list|)
block|{
name|RTreeNode
modifier|*
name|node
decl_stmt|;
name|gimp_assert
argument_list|(
name|w
operator|<=
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
operator|&&
name|h
operator|<=
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
argument_list|)
expr_stmt|;
name|node
operator|=
name|rtree_insert
argument_list|(
operator|&
name|xfer
operator|->
name|rtree
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|node
operator|==
name|NULL
condition|)
block|{
name|xfer
operator|->
name|page
operator|=
operator|(
name|xfer
operator|->
name|page
operator|+
literal|1
operator|)
operator|%
name|NUM_PAGES
expr_stmt|;
name|cairo_surface_flush
argument_list|(
name|xfer
operator|->
name|render_surface
index|[
name|xfer
operator|->
name|page
index|]
argument_list|)
expr_stmt|;
name|rtree_reset
argument_list|(
operator|&
name|xfer
operator|->
name|rtree
argument_list|)
expr_stmt|;
name|cairo_surface_mark_dirty
argument_list|(
name|xfer
operator|->
name|render_surface
index|[
name|xfer
operator|->
name|page
index|]
argument_list|)
expr_stmt|;
comment|/* XXX */
name|node
operator|=
name|rtree_insert
argument_list|(
operator|&
name|xfer
operator|->
name|rtree
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|gimp_assert
argument_list|(
name|node
operator|!=
name|NULL
argument_list|)
expr_stmt|;
block|}
operator|*
name|src_x
operator|=
name|node
operator|->
name|x
expr_stmt|;
operator|*
name|src_y
operator|=
name|node
operator|->
name|y
expr_stmt|;
return|return
name|xfer
operator|->
name|render_surface
index|[
name|xfer
operator|->
name|page
index|]
return|;
block|}
end_function

end_unit


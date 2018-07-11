begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas<alt@picnic.demon.co.uk>  *               2003 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gfig-stock.h"
end_include

begin_include
include|#
directive|include
file|"images/gfig-stock-pixbufs.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|gfig_icon_factory
specifier|static
name|GtkIconFactory
modifier|*
name|gfig_icon_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gfig_stock_items
specifier|static
name|GtkStockItem
name|gfig_stock_items
index|[]
init|=
block|{
block|{
name|GFIG_STOCK_BEZIER
block|,
name|N_
argument_list|(
literal|"Create bezier curve"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_CIRCLE
block|,
name|N_
argument_list|(
literal|"Create circle"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_COPY_OBJECT
block|,
name|N_
argument_list|(
literal|"Copy an object"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_CURVE
block|,
name|N_
argument_list|(
literal|"Create arc"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_DELETE_OBJECT
block|,
name|N_
argument_list|(
literal|"Delete an object"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_ELLIPSE
block|,
name|N_
argument_list|(
literal|"Create ellipse"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_LINE
block|,
name|N_
argument_list|(
literal|"Create line"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_MOVE_OBJECT
block|,
name|N_
argument_list|(
literal|"Move an object"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_MOVE_POINT
block|,
name|N_
argument_list|(
literal|"Move a single point"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_POLYGON
block|,
name|N_
argument_list|(
literal|"Create reg polygon"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_RECTANGLE
block|,
name|N_
argument_list|(
literal|"Create rectangle"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_SELECT_OBJECT
block|,
name|N_
argument_list|(
literal|"Select an object"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_SHOW_ALL
block|,
name|N_
argument_list|(
literal|"Show all objects"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_SPIRAL
block|,
name|N_
argument_list|(
literal|"Create spiral"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|GFIG_STOCK_STAR
block|,
name|N_
argument_list|(
literal|"Create star"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|add_stock_icon (const gchar * stock_id,GtkIconSize size,const guint8 * inline_data)
name|add_stock_icon
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|GtkIconSize
name|size
parameter_list|,
specifier|const
name|guint8
modifier|*
name|inline_data
parameter_list|)
block|{
name|GtkIconSource
modifier|*
name|source
decl_stmt|;
name|GtkIconSet
modifier|*
name|set
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|source
operator|=
name|gtk_icon_source_new
argument_list|()
expr_stmt|;
name|gtk_icon_source_set_size
argument_list|(
name|source
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|gtk_icon_source_set_size_wildcarded
argument_list|(
name|source
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_inline
argument_list|(
operator|-
literal|1
argument_list|,
name|inline_data
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_icon_source_set_pixbuf
argument_list|(
name|source
argument_list|,
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|set
operator|=
name|gtk_icon_set_new
argument_list|()
expr_stmt|;
name|gtk_icon_set_add_source
argument_list|(
name|set
argument_list|,
name|source
argument_list|)
expr_stmt|;
name|gtk_icon_source_free
argument_list|(
name|source
argument_list|)
expr_stmt|;
name|gtk_icon_factory_add
argument_list|(
name|gfig_icon_factory
argument_list|,
name|stock_id
argument_list|,
name|set
argument_list|)
expr_stmt|;
name|gtk_icon_set_unref
argument_list|(
name|set
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gfig_stock_init (void)
name|gfig_stock_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|initialized
condition|)
return|return;
name|gfig_icon_factory
operator|=
name|gtk_icon_factory_new
argument_list|()
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_BEZIER
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_bezier
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_CIRCLE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_circle
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_COPY_OBJECT
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_copy_object
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_CURVE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_curve
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_DELETE_OBJECT
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_delete_object
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_ELLIPSE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_ellipse
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_LINE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_line
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_MOVE_OBJECT
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_move_object
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_MOVE_POINT
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_move_point
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_POLYGON
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_polygon
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_RECTANGLE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_rectangle
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_SELECT_OBJECT
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_select_object
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_SHOW_ALL
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_show_all
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_SPIRAL
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_spiral
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|GFIG_STOCK_STAR
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_star
argument_list|)
expr_stmt|;
name|gtk_icon_factory_add_default
argument_list|(
name|gfig_icon_factory
argument_list|)
expr_stmt|;
name|gtk_stock_add_static
argument_list|(
name|gfig_stock_items
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|gfig_stock_items
argument_list|)
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

end_unit


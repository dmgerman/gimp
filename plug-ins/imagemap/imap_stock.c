begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|"imap_stock.h"
end_include

begin_include
include|#
directive|include
file|"images/imap-stock-pixbufs.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|imap_icon_factory
specifier|static
name|GtkIconFactory
modifier|*
name|imap_icon_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|imap_stock_items
specifier|static
name|GtkStockItem
name|imap_stock_items
index|[]
init|=
block|{
block|{
name|IMAP_STOCK_CIRCLE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|IMAP_STOCK_COORD
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|IMAP_STOCK_DIMENSION
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|IMAP_STOCK_JAVA
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|IMAP_STOCK_MAP_INFO
block|,
name|N_
argument_list|(
literal|"Edit Map Info..."
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|GETTEXT_PACKAGE
literal|"-std-plug-ins"
block|}
block|,
block|{
name|IMAP_STOCK_POLYGON
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|IMAP_STOCK_RECTANGLE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|IMAP_STOCK_TO_BACK
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|IMAP_STOCK_TO_FRONT
block|,
name|NULL
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
DECL|function|add_stock_icon (const gchar * stock_id,const guint8 * inline_data)
name|add_stock_icon
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
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
name|GTK_ICON_SIZE_SMALL_TOOLBAR
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
name|imap_icon_factory
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
DECL|function|init_stock_icons (void)
name|init_stock_icons
parameter_list|(
name|void
parameter_list|)
block|{
name|imap_icon_factory
operator|=
name|gtk_icon_factory_new
argument_list|()
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_CIRCLE
argument_list|,
name|stock_circle
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_COORD
argument_list|,
name|stock_coord
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_DIMENSION
argument_list|,
name|stock_dimension
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_JAVA
argument_list|,
name|stock_java
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_MAP_INFO
argument_list|,
name|stock_map_info
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_POLYGON
argument_list|,
name|stock_polygon
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_RECTANGLE
argument_list|,
name|stock_rectangle
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_TO_BACK
argument_list|,
name|stock_to_back
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|IMAP_STOCK_TO_FRONT
argument_list|,
name|stock_to_front
argument_list|)
expr_stmt|;
name|gtk_icon_factory_add_default
argument_list|(
name|imap_icon_factory
argument_list|)
expr_stmt|;
name|gtk_stock_add_static
argument_list|(
name|imap_stock_items
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|imap_stock_items
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


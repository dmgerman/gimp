begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2003 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|"arrow.xpm"
end_include

begin_include
include|#
directive|include
file|"circle.xpm"
end_include

begin_include
include|#
directive|include
file|"coord.xpm"
end_include

begin_include
include|#
directive|include
file|"dimension.xpm"
end_include

begin_include
include|#
directive|include
file|"grid.xpm"
end_include

begin_include
include|#
directive|include
file|"java.xpm"
end_include

begin_include
include|#
directive|include
file|"link.xpm"
end_include

begin_include
include|#
directive|include
file|"map_info.xpm"
end_include

begin_include
include|#
directive|include
file|"polygon.xpm"
end_include

begin_include
include|#
directive|include
file|"rectangle.xpm"
end_include

begin_include
include|#
directive|include
file|"to_back.xpm"
end_include

begin_include
include|#
directive|include
file|"to_front.xpm"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|imap_stock_items
specifier|static
name|GtkStockItem
name|imap_stock_items
index|[]
init|=
block|{
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
literal|"imap"
block|}
block|,
block|{
name|IMAP_STOCK_GRID
block|,
name|N_
argument_list|(
literal|"Grid"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"imap"
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|add_stock_icon (GtkIconFactory * factory,const gchar * stock_id,const char ** xpm_data)
name|add_stock_icon
parameter_list|(
name|GtkIconFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|char
modifier|*
modifier|*
name|xpm_data
parameter_list|)
block|{
name|GtkIconSet
modifier|*
name|icon_set
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_xpm_data
argument_list|(
name|xpm_data
argument_list|)
expr_stmt|;
name|icon_set
operator|=
name|gtk_icon_set_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gtk_icon_factory_add
argument_list|(
name|factory
argument_list|,
name|stock_id
argument_list|,
name|icon_set
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gtk_icon_set_unref
argument_list|(
name|icon_set
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
name|GtkIconFactory
modifier|*
name|factory
init|=
name|gtk_icon_factory_new
argument_list|()
decl_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_ARROW
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|arrow_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_CIRCLE
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|circle_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_COORD
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|coord_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_DIMENSION
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|dimension_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_GRID
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|grid_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_JAVA
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|java_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_LINK
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|link_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_MAP_INFO
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|map_info_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_POLYGON
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|polygon_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_RECTANGLE
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|rectangle_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_TO_BACK
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|to_back_xpm
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|factory
argument_list|,
name|IMAP_STOCK_TO_FRONT
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|*
operator|)
name|to_front_xpm
argument_list|)
expr_stmt|;
name|gtk_icon_factory_add_default
argument_list|(
name|factory
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


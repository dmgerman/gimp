begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"map-object-stock.h"
end_include

begin_include
include|#
directive|include
file|"../lighting/images/stock-pixbufs.h"
end_include

begin_decl_stmt
DECL|variable|mapobject_icon_factory
specifier|static
name|GtkIconFactory
modifier|*
name|mapobject_icon_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|mapobject_stock_items
specifier|static
name|GtkStockItem
name|mapobject_stock_items
index|[]
init|=
block|{
block|{
name|STOCK_INTENSITY_AMBIENT_LOW
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
name|STOCK_INTENSITY_AMBIENT_HIGH
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
name|STOCK_INTENSITY_DIFFUSE_LOW
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
name|STOCK_INTENSITY_DIFFUSE_HIGH
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
name|STOCK_REFLECTIVITY_DIFFUSE_LOW
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
name|STOCK_REFLECTIVITY_DIFFUSE_HIGH
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
name|STOCK_REFLECTIVITY_SPECULAR_LOW
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
name|STOCK_REFLECTIVITY_SPECULAR_HIGH
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
name|STOCK_REFLECTIVITY_HIGHLIGHT_LOW
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
name|STOCK_REFLECTIVITY_HIGHLIGHT_HIGH
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
name|FALSE
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
name|mapobject_icon_factory
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
DECL|function|mapobject_stock_init (void)
name|mapobject_stock_init
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
name|mapobject_icon_factory
operator|=
name|gtk_icon_factory_new
argument_list|()
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_INTENSITY_AMBIENT_LOW
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_intensity_ambient_low
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_INTENSITY_AMBIENT_HIGH
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_intensity_ambient_high
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_INTENSITY_DIFFUSE_LOW
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_intensity_diffuse_low
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_INTENSITY_DIFFUSE_HIGH
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_intensity_diffuse_high
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_REFLECTIVITY_DIFFUSE_LOW
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_reflectivity_diffuse_low
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_REFLECTIVITY_DIFFUSE_HIGH
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_reflectivity_diffuse_high
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_REFLECTIVITY_SPECULAR_LOW
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_reflectivity_specular_low
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_REFLECTIVITY_SPECULAR_HIGH
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_reflectivity_specular_high
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_REFLECTIVITY_HIGHLIGHT_LOW
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_reflectivity_highlight_low
argument_list|)
expr_stmt|;
name|add_stock_icon
argument_list|(
name|STOCK_REFLECTIVITY_HIGHLIGHT_HIGH
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|stock_reflectivity_highlight_high
argument_list|)
expr_stmt|;
name|gtk_icon_factory_add_default
argument_list|(
name|mapobject_icon_factory
argument_list|)
expr_stmt|;
name|gtk_stock_add_static
argument_list|(
name|mapobject_stock_items
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|mapobject_stock_items
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


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpstock.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtkiconfactory.h>
end_include

begin_include
include|#
directive|include
file|"gimpstock.h"
end_include

begin_include
include|#
directive|include
file|"themes/Default/images/gimp-stock-pixbufs.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|LIBGIMP_DOMAIN
define|#
directive|define
name|LIBGIMP_DOMAIN
value|GETTEXT_PACKAGE "-libgimp"
end_define

begin_decl_stmt
DECL|variable|gimp_stock_factory
specifier|static
name|GtkIconFactory
modifier|*
name|gimp_stock_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|icon_set_from_inline (GtkIconSet * set,const guchar * inline_data,GtkIconSize size,gboolean fallback)
name|icon_set_from_inline
parameter_list|(
name|GtkIconSet
modifier|*
name|set
parameter_list|,
specifier|const
name|guchar
modifier|*
name|inline_data
parameter_list|,
name|GtkIconSize
name|size
parameter_list|,
name|gboolean
name|fallback
parameter_list|)
block|{
name|GtkIconSource
modifier|*
name|source
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
name|g_assert
argument_list|(
name|pixbuf
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
name|gtk_icon_set_add_source
argument_list|(
name|set
argument_list|,
name|source
argument_list|)
expr_stmt|;
if|if
condition|(
name|fallback
condition|)
block|{
name|gtk_icon_source_set_size_wildcarded
argument_list|(
name|source
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_icon_set_add_source
argument_list|(
name|set
argument_list|,
name|source
argument_list|)
expr_stmt|;
block|}
name|gtk_icon_source_free
argument_list|(
name|source
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_sized_with_same_fallback (GtkIconFactory * factory,const guchar * inline_data,GtkIconSize size,const gchar * stock_id)
name|add_sized_with_same_fallback
parameter_list|(
name|GtkIconFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|guchar
modifier|*
name|inline_data
parameter_list|,
name|GtkIconSize
name|size
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|GtkIconSet
modifier|*
name|set
decl_stmt|;
name|gboolean
name|fallback
init|=
name|FALSE
decl_stmt|;
name|set
operator|=
name|gtk_icon_factory_lookup
argument_list|(
name|factory
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|set
condition|)
block|{
name|set
operator|=
name|gtk_icon_set_new
argument_list|()
expr_stmt|;
name|gtk_icon_factory_add
argument_list|(
name|factory
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
name|fallback
operator|=
name|TRUE
expr_stmt|;
block|}
name|icon_set_from_inline
argument_list|(
name|set
argument_list|,
name|inline_data
argument_list|,
name|size
argument_list|,
name|fallback
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_stock_items
specifier|static
name|GtkStockItem
name|gimp_stock_items
index|[]
init|=
block|{
block|{
name|GIMP_STOCK_ANCHOR
block|,
name|N_
argument_list|(
literal|"Anchor"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_DUPLICATE
block|,
name|N_
argument_list|(
literal|"_Duplicate"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"_Edit"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_LINKED
block|,
name|N_
argument_list|(
literal|"Linked"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_PASTE_AS_NEW
block|,
name|N_
argument_list|(
literal|"Paste as New"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_PASTE_INTO
block|,
name|N_
argument_list|(
literal|"Paste Into"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_RESET
block|,
name|N_
argument_list|(
literal|"_Reset"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_VISIBLE
block|,
name|N_
argument_list|(
literal|"Visible"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_EAST
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_NORTH
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_NORTH_EAST
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_NORTH_WEST
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_SOUTH
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_SOUTH_EAST
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_SOUTH_WEST
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_WEST
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_HCHAIN
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_HCHAIN_BROKEN
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_VCHAIN
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_VCHAIN_BROKEN
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_REPLACE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_ADD
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_SUBTRACT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_INTERSECT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_STROKE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_TO_CHANNEL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_TO_PATH
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_PATH_STROKE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CURVE_FREE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CURVE_SMOOTH
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_PICKER_BLACK
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_PICKER_GRAY
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_PICKER_WHITE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_TRIANGLE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHAR_PICKER
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_LETTER_SPACING
block|,
name|N_
argument_list|(
literal|"L_etter Spacing"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_LINE_SPACING
block|,
name|N_
argument_list|(
literal|"L_ine Spacing"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CONVERT_RGB
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CONVERT_GRAYSCALE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CONVERT_INDEXED
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_INVERT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_MERGE_DOWN
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_LAYER_TO_IMAGESIZE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_PLUGIN
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_RESHOW_FILTER
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_ROTATE_90
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_ROTATE_180
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_ROTATE_270
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_RESIZE
block|,
name|N_
argument_list|(
literal|"_Resize"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SCALE
block|,
name|N_
argument_list|(
literal|"_Scale"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_OPTIONS
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_DEVICE_STATUS
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_IMAGES
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_LAYERS
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHANNELS
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_PATHS
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_IMAGE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_LAYER
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_RED
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_GREEN
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_BLUE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_GRAY
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_ALPHA
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_ALL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_NONE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_GROW
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_SHRINK
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_NAVIGATION
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_QMASK_OFF
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_QMASK_ON
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_ERROR
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_INFO
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_QUESTION
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_WARNING
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_WILBER
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_WILBER_EEK
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_AIRBRUSH
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BEZIER_SELECT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BLEND
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BLUR
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BUCKET_FILL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BY_COLOR_SELECT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CLONE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_COLOR_BALANCE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_COLOR_PICKER
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CROP
block|,
name|N_
argument_list|(
literal|"Crop"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CURVES
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_DODGE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ELLIPSE_SELECT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ERASER
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FLIP
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FREE_SELECT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FUZZY_SELECT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_HISTOGRAM
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_HUE_SATURATION
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_INK
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ISCISSORS
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_LEVELS
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_MEASURE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_MOVE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PAINTBRUSH
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PATH
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PENCIL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PERSPECTIVE
block|,
name|N_
argument_list|(
literal|"_Transform"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_POSTERIZE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_RECT_SELECT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ROTATE
block|,
name|N_
argument_list|(
literal|"_Rotate"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SCALE
block|,
name|N_
argument_list|(
literal|"_Scale"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SHEAR
block|,
name|N_
argument_list|(
literal|"_Shear"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SMUDGE
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_TEXT
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_THRESHOLD
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ZOOM
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|LIBGIMP_DOMAIN
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_struct
specifier|static
struct|struct
DECL|struct|__anon289c06b50108
block|{
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|inline_data
name|gconstpointer
name|inline_data
decl_stmt|;
block|}
DECL|variable|gimp_stock_button_pixbufs
name|gimp_stock_button_pixbufs
index|[]
init|=
block|{
block|{
name|GIMP_STOCK_ANCHOR
block|,
name|stock_anchor_16
block|}
block|,
block|{
name|GIMP_STOCK_DUPLICATE
block|,
name|stock_duplicate_16
block|}
block|,
block|{
name|GIMP_STOCK_EDIT
block|,
name|stock_edit_16
block|}
block|,
block|{
name|GIMP_STOCK_PASTE_AS_NEW
block|,
name|stock_paste_as_new_16
block|}
block|,
block|{
name|GIMP_STOCK_PASTE_INTO
block|,
name|stock_paste_into_16
block|}
block|,
block|{
name|GIMP_STOCK_RESET
block|,
name|stock_reset_16
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_EAST
block|,
name|stock_gravity_east_24
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_NORTH
block|,
name|stock_gravity_north_24
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_NORTH_EAST
block|,
name|stock_gravity_north_east_24
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_NORTH_WEST
block|,
name|stock_gravity_north_west_24
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_SOUTH
block|,
name|stock_gravity_south_24
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_SOUTH_EAST
block|,
name|stock_gravity_south_east_24
block|}
block|,
block|{
name|GIMP_STOCK_GRAVITY_SOUTH_WEST
block|,
name|stock_gravity_south_west_24
block|}
block|,
block|{
name|GIMP_STOCK_HCHAIN
block|,
name|stock_hchain_24
block|}
block|,
block|{
name|GIMP_STOCK_HCHAIN_BROKEN
block|,
name|stock_hchain_broken_24
block|}
block|,
block|{
name|GIMP_STOCK_VCHAIN
block|,
name|stock_vchain_24
block|}
block|,
block|{
name|GIMP_STOCK_VCHAIN_BROKEN
block|,
name|stock_vchain_broken_24
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_REPLACE
block|,
name|stock_selection_replace_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_ADD
block|,
name|stock_selection_add_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_SUBTRACT
block|,
name|stock_selection_subtract_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_INTERSECT
block|,
name|stock_selection_intersect_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_STROKE
block|,
name|stock_selection_stroke_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_TO_CHANNEL
block|,
name|stock_selection_to_channel_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_TO_PATH
block|,
name|stock_selection_to_path_16
block|}
block|,
block|{
name|GIMP_STOCK_PATH_STROKE
block|,
name|stock_path_stroke_16
block|}
block|,
block|{
name|GIMP_STOCK_CURVE_FREE
block|,
name|stock_curve_free_16
block|}
block|,
block|{
name|GIMP_STOCK_CURVE_SMOOTH
block|,
name|stock_curve_smooth_16
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_PICKER_BLACK
block|,
name|stock_color_picker_black_18
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_PICKER_GRAY
block|,
name|stock_color_picker_gray_18
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_PICKER_WHITE
block|,
name|stock_color_picker_white_18
block|}
block|,
block|{
name|GIMP_STOCK_COLOR_TRIANGLE
block|,
name|stock_color_triangle_16
block|}
block|,
block|{
name|GIMP_STOCK_CHAR_PICKER
block|,
name|stock_char_picker_22
block|}
block|,
block|{
name|GIMP_STOCK_LETTER_SPACING
block|,
name|stock_letter_spacing_22
block|}
block|,
block|{
name|GIMP_STOCK_LINE_SPACING
block|,
name|stock_line_spacing_22
block|}
block|,
block|{
name|GIMP_STOCK_IMAGES
block|,
name|stock_images_24
block|}
block|,
block|{
name|GIMP_STOCK_LAYERS
block|,
name|stock_layers_24
block|}
block|,
block|{
name|GIMP_STOCK_CHANNELS
block|,
name|stock_channels_24
block|}
block|,
block|{
name|GIMP_STOCK_PATHS
block|,
name|stock_paths_22
block|}
block|,
block|{
name|GIMP_STOCK_IMAGE
block|,
name|stock_image_24
block|}
block|,
block|{
name|GIMP_STOCK_LAYER
block|,
name|stock_layer_24
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL
block|,
name|stock_channel_24
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_RED
block|,
name|stock_channel_red_24
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_GREEN
block|,
name|stock_channel_green_24
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_BLUE
block|,
name|stock_channel_blue_24
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_GRAY
block|,
name|stock_channel_gray_24
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_ALPHA
block|,
name|stock_channel_alpha_24
block|}
block|,
block|{
name|GIMP_STOCK_LINKED
block|,
name|stock_linked_20
block|}
block|,
block|{
name|GIMP_STOCK_VISIBLE
block|,
name|stock_eye_20
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_AIRBRUSH
block|,
name|stock_tool_airbrush_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BEZIER_SELECT
block|,
name|stock_tool_bezier_select_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BLEND
block|,
name|stock_tool_blend_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BLUR
block|,
name|stock_tool_blur_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
block|,
name|stock_tool_brightness_contrast_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BUCKET_FILL
block|,
name|stock_tool_bucket_fill_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BY_COLOR_SELECT
block|,
name|stock_tool_by_color_select_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CLONE
block|,
name|stock_tool_clone_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_COLOR_BALANCE
block|,
name|stock_tool_color_balance_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_COLOR_PICKER
block|,
name|stock_tool_color_picker_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CROP
block|,
name|stock_tool_crop_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CURVES
block|,
name|stock_tool_curves_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_DODGE
block|,
name|stock_tool_dodge_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ELLIPSE_SELECT
block|,
name|stock_tool_ellipse_select_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ERASER
block|,
name|stock_tool_eraser_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FLIP
block|,
name|stock_tool_flip_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FREE_SELECT
block|,
name|stock_tool_free_select_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FUZZY_SELECT
block|,
name|stock_tool_fuzzy_select_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_HISTOGRAM
block|,
name|stock_tool_histogram_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_HUE_SATURATION
block|,
name|stock_tool_hue_saturation_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_INK
block|,
name|stock_tool_ink_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ISCISSORS
block|,
name|stock_tool_iscissors_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_LEVELS
block|,
name|stock_tool_levels_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_MEASURE
block|,
name|stock_tool_measure_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_MOVE
block|,
name|stock_tool_move_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PAINTBRUSH
block|,
name|stock_tool_paintbrush_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PATH
block|,
name|stock_tool_path_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PENCIL
block|,
name|stock_tool_pencil_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PERSPECTIVE
block|,
name|stock_tool_perspective_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_POSTERIZE
block|,
name|stock_tool_posterize_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_RECT_SELECT
block|,
name|stock_tool_rect_select_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ROTATE
block|,
name|stock_tool_rotate_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SCALE
block|,
name|stock_tool_scale_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SHEAR
block|,
name|stock_tool_shear_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SMUDGE
block|,
name|stock_tool_smudge_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_TEXT
block|,
name|stock_tool_text_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_THRESHOLD
block|,
name|stock_tool_threshold_22
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ZOOM
block|,
name|stock_tool_zoom_22
block|}
block|,
block|{
name|GIMP_STOCK_INFO
block|,
name|stock_info_24
block|}
block|,
block|{
name|GIMP_STOCK_WARNING
block|,
name|stock_warning_24
block|}
block|}
struct|;
end_struct

begin_struct
specifier|static
struct|struct
DECL|struct|__anon289c06b50208
block|{
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|inline_data
name|gconstpointer
name|inline_data
decl_stmt|;
block|}
DECL|variable|gimp_stock_menu_pixbufs
name|gimp_stock_menu_pixbufs
index|[]
init|=
block|{
block|{
name|GIMP_STOCK_CONVERT_RGB
block|,
name|stock_convert_rgb_16
block|}
block|,
block|{
name|GIMP_STOCK_CONVERT_GRAYSCALE
block|,
name|stock_convert_grayscale_16
block|}
block|,
block|{
name|GIMP_STOCK_CONVERT_INDEXED
block|,
name|stock_convert_indexed_16
block|}
block|,
block|{
name|GIMP_STOCK_INVERT
block|,
name|stock_invert_16
block|}
block|,
block|{
name|GIMP_STOCK_MERGE_DOWN
block|,
name|stock_merge_down_16
block|}
block|,
block|{
name|GIMP_STOCK_LAYER_TO_IMAGESIZE
block|,
name|stock_layer_to_imagesize_16
block|}
block|,
block|{
name|GIMP_STOCK_PLUGIN
block|,
name|stock_plugin_16
block|}
block|,
block|{
name|GIMP_STOCK_RESHOW_FILTER
block|,
name|stock_reshow_filter_16
block|}
block|,
block|{
name|GIMP_STOCK_ROTATE_90
block|,
name|stock_rotate_90_16
block|}
block|,
block|{
name|GIMP_STOCK_ROTATE_180
block|,
name|stock_rotate_180_16
block|}
block|,
block|{
name|GIMP_STOCK_ROTATE_270
block|,
name|stock_rotate_270_16
block|}
block|,
block|{
name|GIMP_STOCK_RESIZE
block|,
name|stock_resize_16
block|}
block|,
block|{
name|GIMP_STOCK_SCALE
block|,
name|stock_scale_16
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_OPTIONS
block|,
name|stock_tool_options_16
block|}
block|,
block|{
name|GIMP_STOCK_DEVICE_STATUS
block|,
name|stock_device_status_16
block|}
block|,
block|{
name|GIMP_STOCK_IMAGES
block|,
name|stock_images_16
block|}
block|,
block|{
name|GIMP_STOCK_LAYERS
block|,
name|stock_layers_16
block|}
block|,
block|{
name|GIMP_STOCK_CHANNELS
block|,
name|stock_channels_16
block|}
block|,
block|{
name|GIMP_STOCK_PATHS
block|,
name|stock_paths_16
block|}
block|,
block|{
name|GIMP_STOCK_IMAGE
block|,
name|stock_image_16
block|}
block|,
block|{
name|GIMP_STOCK_LAYER
block|,
name|stock_layer_16
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL
block|,
name|stock_channel_16
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_RED
block|,
name|stock_channel_red_16
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_GREEN
block|,
name|stock_channel_green_16
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_BLUE
block|,
name|stock_channel_blue_16
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_GRAY
block|,
name|stock_channel_gray_16
block|}
block|,
block|{
name|GIMP_STOCK_CHANNEL_ALPHA
block|,
name|stock_channel_alpha_16
block|}
block|,
block|{
name|GIMP_STOCK_LINKED
block|,
name|stock_linked_12
block|}
block|,
block|{
name|GIMP_STOCK_VISIBLE
block|,
name|stock_eye_12
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_ALL
block|,
name|stock_selection_all_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_NONE
block|,
name|stock_selection_none_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_GROW
block|,
name|stock_selection_grow_16
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_SHRINK
block|,
name|stock_selection_shrink_16
block|}
block|,
block|{
name|GIMP_STOCK_NAVIGATION
block|,
name|stock_navigation_16
block|}
block|,
block|{
name|GIMP_STOCK_QMASK_OFF
block|,
name|stock_qmask_off_16
block|}
block|,
block|{
name|GIMP_STOCK_QMASK_ON
block|,
name|stock_qmask_on_16
block|}
block|,
block|{
name|GIMP_STOCK_DEFAULT_COLORS
block|,
name|stock_default_colors_12
block|}
block|,
block|{
name|GIMP_STOCK_SWAP_COLORS
block|,
name|stock_swap_colors_12
block|}
block|,
block|{
name|GIMP_STOCK_INFO
block|,
name|stock_info_16
block|}
block|,
block|{
name|GIMP_STOCK_WARNING
block|,
name|stock_warning_16
block|}
block|,
block|{
name|GIMP_STOCK_WILBER
block|,
name|stock_wilber_16
block|}
block|}
struct|;
end_struct

begin_struct
specifier|static
struct|struct
DECL|struct|__anon289c06b50308
block|{
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|inline_data
name|gconstpointer
name|inline_data
decl_stmt|;
block|}
DECL|variable|gimp_stock_dialog_pixbufs
name|gimp_stock_dialog_pixbufs
index|[]
init|=
block|{
block|{
name|GIMP_STOCK_ERROR
block|,
name|stock_error_64
block|}
block|,
block|{
name|GIMP_STOCK_INFO
block|,
name|stock_info_64
block|}
block|,
block|{
name|GIMP_STOCK_QUESTION
block|,
name|stock_question_64
block|}
block|,
block|{
name|GIMP_STOCK_WARNING
block|,
name|stock_warning_64
block|}
block|,
block|{
name|GIMP_STOCK_WILBER
block|,
name|stock_wilber_64
block|}
block|,
block|{
name|GIMP_STOCK_WILBER_EEK
block|,
name|stock_wilber_eek_64
block|}
block|}
struct|;
end_struct

begin_function
name|void
DECL|function|gimp_stock_init (void)
name|gimp_stock_init
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
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|initialized
condition|)
return|return;
name|gimp_stock_factory
operator|=
name|gtk_icon_factory_new
argument_list|()
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|gimp_stock_dialog_pixbufs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|add_sized_with_same_fallback
argument_list|(
name|gimp_stock_factory
argument_list|,
name|gimp_stock_dialog_pixbufs
index|[
name|i
index|]
operator|.
name|inline_data
argument_list|,
name|GTK_ICON_SIZE_DIALOG
argument_list|,
name|gimp_stock_dialog_pixbufs
index|[
name|i
index|]
operator|.
name|stock_id
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|gimp_stock_button_pixbufs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|add_sized_with_same_fallback
argument_list|(
name|gimp_stock_factory
argument_list|,
name|gimp_stock_button_pixbufs
index|[
name|i
index|]
operator|.
name|inline_data
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|gimp_stock_button_pixbufs
index|[
name|i
index|]
operator|.
name|stock_id
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|gimp_stock_menu_pixbufs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|add_sized_with_same_fallback
argument_list|(
name|gimp_stock_factory
argument_list|,
name|gimp_stock_menu_pixbufs
index|[
name|i
index|]
operator|.
name|inline_data
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|,
name|gimp_stock_menu_pixbufs
index|[
name|i
index|]
operator|.
name|stock_id
argument_list|)
expr_stmt|;
block|}
name|gtk_icon_factory_add_default
argument_list|(
name|gimp_stock_factory
argument_list|)
expr_stmt|;
name|gtk_stock_add_static
argument_list|(
name|gimp_stock_items
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|gimp_stock_items
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


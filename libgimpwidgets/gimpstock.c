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
file|"themes/Default/gimp-stock-pixbufs.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

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
name|GtkIconSet
modifier|*
DECL|function|sized_with_same_fallback_icon_set_from_inline (const guchar * inline_data,GtkIconSize size)
name|sized_with_same_fallback_icon_set_from_inline
parameter_list|(
specifier|const
name|guchar
modifier|*
name|inline_data
parameter_list|,
name|GtkIconSize
name|size
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
name|G_OBJECT
argument_list|(
name|pixbuf
argument_list|)
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
name|gtk_icon_source_free
argument_list|(
name|source
argument_list|)
expr_stmt|;
return|return
name|set
return|;
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
name|set
operator|=
name|sized_with_same_fallback_icon_set_from_inline
argument_list|(
name|inline_data
argument_list|,
name|size
argument_list|)
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
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_DUPLICATE
block|,
name|N_
argument_list|(
literal|"Duplicate"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_EDIT
block|,
name|N_
argument_list|(
literal|"Edit"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_PASTE
block|,
name|N_
argument_list|(
literal|"Paste"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_STROKE
block|,
name|N_
argument_list|(
literal|"_Stroke"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_TO_PATH
block|,
name|N_
argument_list|(
literal|"Selection To Path"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_TO_SELECTION
block|,
name|N_
argument_list|(
literal|"To Sleection"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CROP
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PERSPECTIVE
block|,
name|N_
argument_list|(
literal|"Transform"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ROTATE
block|,
name|N_
argument_list|(
literal|"Rotate"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SCALE
block|,
name|N_
argument_list|(
literal|"Scale"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SHEAR
block|,
name|N_
argument_list|(
literal|"Shear"
argument_list|)
block|,
literal|0
block|,
literal|0
block|,
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
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
literal|"gimp-libgimp"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_struct
specifier|static
struct|struct
DECL|struct|__anon2a2282b60108
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
name|stock_button_anchor
block|}
block|,
block|{
name|GIMP_STOCK_DUPLICATE
block|,
name|stock_button_duplicate
block|}
block|,
block|{
name|GIMP_STOCK_EDIT
block|,
name|stock_button_edit
block|}
block|,
block|{
name|GIMP_STOCK_LINKED
block|,
name|stock_button_linked
block|}
block|,
block|{
name|GIMP_STOCK_PASTE
block|,
name|stock_button_paste
block|}
block|,
block|{
name|GIMP_STOCK_PASTE_AS_NEW
block|,
name|stock_button_paste_as_new
block|}
block|,
block|{
name|GIMP_STOCK_PASTE_INTO
block|,
name|stock_button_paste_into
block|}
block|,
block|{
name|GIMP_STOCK_RESET
block|,
name|stock_button_refresh
block|}
block|,
block|{
name|GIMP_STOCK_STROKE
block|,
name|stock_button_stroke
block|}
block|,
block|{
name|GIMP_STOCK_TO_PATH
block|,
name|stock_button_to_path
block|}
block|,
block|{
name|GIMP_STOCK_TO_SELECTION
block|,
name|stock_button_to_selection
block|}
block|,
block|{
name|GIMP_STOCK_VISIBLE
block|,
name|stock_button_eye
block|}
block|,
block|{
name|GIMP_STOCK_HCHAIN
block|,
name|stock_button_hchain
block|}
block|,
block|{
name|GIMP_STOCK_HCHAIN_BROKEN
block|,
name|stock_button_hchain_broken
block|}
block|,
block|{
name|GIMP_STOCK_VCHAIN
block|,
name|stock_button_vchain
block|}
block|,
block|{
name|GIMP_STOCK_VCHAIN_BROKEN
block|,
name|stock_button_vchain_broken
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_REPLACE
block|,
name|stock_button_selection_replace
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_ADD
block|,
name|stock_button_selection_add
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_SUBTRACT
block|,
name|stock_button_selection_subtract
block|}
block|,
block|{
name|GIMP_STOCK_SELECTION_INTERSECT
block|,
name|stock_button_selection_intersect
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_AIRBRUSH
block|,
name|stock_tool_button_airbrush
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BEZIER_SELECT
block|,
name|stock_tool_button_bezier_select
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BLEND
block|,
name|stock_tool_button_blend
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BLUR
block|,
name|stock_tool_button_blur
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
block|,
name|stock_tool_button_brightness_contrast
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BUCKET_FILL
block|,
name|stock_tool_button_bucket_fill
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_BY_COLOR_SELECT
block|,
name|stock_tool_button_by_color_select
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CLONE
block|,
name|stock_tool_button_clone
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_COLOR_BALANCE
block|,
name|stock_tool_button_color_balance
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_COLOR_PICKER
block|,
name|stock_tool_button_color_picker
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CROP
block|,
name|stock_tool_button_crop
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_CURVES
block|,
name|stock_tool_button_curves
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_DODGE
block|,
name|stock_tool_button_dodge
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ELLIPSE_SELECT
block|,
name|stock_tool_button_ellipse_select
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ERASER
block|,
name|stock_tool_button_eraser
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FLIP
block|,
name|stock_tool_button_flip
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FREE_SELECT
block|,
name|stock_tool_button_free_select
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_FUZZY_SELECT
block|,
name|stock_tool_button_fuzzy_select
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_HISTOGRAM
block|,
name|stock_tool_button_histogram
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_HUE_SATURATION
block|,
name|stock_tool_button_hue_saturation
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_INK
block|,
name|stock_tool_button_ink
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ISCISSORS
block|,
name|stock_tool_button_iscissors
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_LEVELS
block|,
name|stock_tool_button_levels
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_MEASURE
block|,
name|stock_tool_button_measure
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_MOVE
block|,
name|stock_tool_button_move
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PAINTBRUSH
block|,
name|stock_tool_button_paintbrush
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PATH
block|,
name|stock_tool_button_path
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PENCIL
block|,
name|stock_tool_button_pencil
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_PERSPECTIVE
block|,
name|stock_tool_button_perspective
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_POSTERIZE
block|,
name|stock_tool_button_posterize
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_RECT_SELECT
block|,
name|stock_tool_button_rect_select
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ROTATE
block|,
name|stock_tool_button_rotate
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SCALE
block|,
name|stock_tool_button_scale
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SHEAR
block|,
name|stock_tool_button_shear
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_SMUDGE
block|,
name|stock_tool_button_smudge
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_TEXT
block|,
name|stock_tool_button_text
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_THRESHOLD
block|,
name|stock_tool_button_threshold
block|}
block|,
block|{
name|GIMP_STOCK_TOOL_ZOOM
block|,
name|stock_tool_button_zoom
block|}
block|}
struct|;
end_struct

begin_struct
specifier|static
struct|struct
DECL|struct|__anon2a2282b60208
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
name|GIMP_STOCK_NAVIGATION
block|,
name|stock_menu_navigation
block|}
block|,
block|{
name|GIMP_STOCK_QMASK_OFF
block|,
name|stock_menu_qmask_off
block|}
block|,
block|{
name|GIMP_STOCK_QMASK_ON
block|,
name|stock_menu_qmask_on
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


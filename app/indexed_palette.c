begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"gdk/gdkkeysyms.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"actionarea.h"
end_include

begin_include
include|#
directive|include
file|"buildmenu.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"color_select.h"
end_include

begin_include
include|#
directive|include
file|"color_area.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"image_render.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"indexed_palette.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_define
DECL|macro|EVENT_MASK
define|#
directive|define
name|EVENT_MASK
value|GDK_BUTTON_PRESS_MASK | GDK_ENTER_NOTIFY_MASK
end_define

begin_define
DECL|macro|CELL_WIDTH
define|#
directive|define
name|CELL_WIDTH
value|20
end_define

begin_define
DECL|macro|CELL_HEIGHT
define|#
directive|define
name|CELL_HEIGHT
value|20
end_define

begin_define
DECL|macro|P_AREA_WIDTH
define|#
directive|define
name|P_AREA_WIDTH
value|(CELL_WIDTH * 16)
end_define

begin_define
DECL|macro|P_AREA_HEIGHT
define|#
directive|define
name|P_AREA_HEIGHT
value|(CELL_HEIGHT * 16)
end_define

begin_comment
comment|/*  Add these features:  *  *  load/save colormaps  *  requantize  *  add color--by clicking in the checked region  *  all changes need to flush colormap lookup cache  */
end_comment

begin_typedef
DECL|typedef|IndexedPalette
typedef|typedef
name|struct
name|_IndexedPalette
name|IndexedPalette
typedef|;
end_typedef

begin_struct
DECL|struct|_IndexedPalette
struct|struct
name|_IndexedPalette
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|palette
name|GtkWidget
modifier|*
name|palette
decl_stmt|;
DECL|member|image_menu
name|GtkWidget
modifier|*
name|image_menu
decl_stmt|;
DECL|member|image_option_menu
name|GtkWidget
modifier|*
name|image_option_menu
decl_stmt|;
comment|/*  state information  */
DECL|member|gimage_id
name|int
name|gimage_id
decl_stmt|;
DECL|member|col_index
name|int
name|col_index
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  indexed palette routines  */
end_comment

begin_function_decl
specifier|static
name|void
name|indexed_palette_draw
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|indexed_palette_clear
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|indexed_palette_update
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  indexed palette menu callbacks  */
end_comment

begin_function_decl
specifier|static
name|void
name|indexed_palette_close_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|indexed_palette_select_callback
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|ColorSelectState
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  event callback  */
end_comment

begin_function_decl
specifier|static
name|gint
name|indexed_palette_area_events
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  create image menu  */
end_comment

begin_function_decl
specifier|static
name|void
name|image_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|create_image_menu
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|MenuItemCallback
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Only one indexed palette  */
end_comment

begin_decl_stmt
DECL|variable|indexedP
specifier|static
name|IndexedPalette
modifier|*
name|indexedP
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Color select dialog  */
end_comment

begin_decl_stmt
DECL|variable|color_select
specifier|static
name|ColorSelectP
name|color_select
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_select_active
specifier|static
name|int
name|color_select_active
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the action area structure  */
end_comment

begin_decl_stmt
DECL|variable|action_items
specifier|static
name|ActionAreaItem
name|action_items
index|[]
init|=
block|{
block|{
literal|"Close"
block|,
name|indexed_palette_close_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|indexed_color_ops
specifier|static
name|MenuItem
name|indexed_color_ops
index|[]
init|=
block|{
block|{
literal|"Close"
block|,
literal|'W'
block|,
name|GDK_CONTROL_MASK
block|,
name|indexed_palette_close_callback
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************************************/
end_comment

begin_comment
comment|/*  Public indexed palette functions  */
end_comment

begin_comment
comment|/**************************************/
end_comment

begin_function
name|void
DECL|function|indexed_palette_create (int gimage_id)
name|indexed_palette_create
parameter_list|(
name|int
name|gimage_id
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|util_box
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|arrow_hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|arrow
decl_stmt|;
name|GtkWidget
modifier|*
name|ops_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_bar
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_bar_item
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkAcceleratorTable
modifier|*
name|table
decl_stmt|;
name|int
name|default_index
decl_stmt|;
if|if
condition|(
operator|!
name|indexedP
condition|)
block|{
name|indexedP
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|IndexedPalette
argument_list|)
argument_list|)
expr_stmt|;
name|indexedP
operator|->
name|gimage_id
operator|=
operator|-
literal|1
expr_stmt|;
name|table
operator|=
name|gtk_accelerator_table_new
argument_list|()
expr_stmt|;
comment|/*  The shell and main vbox  */
name|indexedP
operator|->
name|shell
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
argument_list|,
literal|"indexed_color_palette"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
argument_list|,
literal|"Indexed Color Palette"
argument_list|)
expr_stmt|;
name|gtk_window_add_accelerator_table
argument_list|(
name|GTK_WINDOW
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_hide_on_delete
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_quit_add
argument_list|(
literal|1
argument_list|,
operator|(
name|GtkFunction
operator|)
name|gtk_widget_destroy
argument_list|,
name|indexedP
operator|->
name|shell
argument_list|)
expr_stmt|;
name|indexedP
operator|->
name|vbox
operator|=
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  The hbox to hold the command menu and image option menu box  */
name|util_box
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|util_box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  The GIMP image option menu  */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Image:"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|util_box
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|indexedP
operator|->
name|image_option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|util_box
argument_list|)
argument_list|,
name|indexedP
operator|->
name|image_option_menu
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|indexedP
operator|->
name|image_option_menu
argument_list|)
expr_stmt|;
name|indexedP
operator|->
name|image_menu
operator|=
name|create_image_menu
argument_list|(
operator|&
name|gimage_id
argument_list|,
operator|&
name|default_index
argument_list|,
name|image_menu_callback
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|indexedP
operator|->
name|image_option_menu
argument_list|)
argument_list|,
name|indexedP
operator|->
name|image_menu
argument_list|)
expr_stmt|;
if|if
condition|(
name|default_index
operator|!=
operator|-
literal|1
condition|)
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|indexedP
operator|->
name|image_option_menu
argument_list|)
argument_list|,
name|default_index
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/*  The indexed palette commands pulldown menu  */
name|ops_menu
operator|=
name|build_menu
argument_list|(
name|indexed_color_ops
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|menu_bar
operator|=
name|gtk_menu_bar_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|util_box
argument_list|)
argument_list|,
name|menu_bar
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|menu_bar_item
operator|=
name|gtk_menu_item_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|menu_bar
argument_list|)
argument_list|,
name|menu_bar_item
argument_list|)
expr_stmt|;
name|gtk_menu_item_set_submenu
argument_list|(
name|GTK_MENU_ITEM
argument_list|(
name|menu_bar_item
argument_list|)
argument_list|,
name|ops_menu
argument_list|)
expr_stmt|;
name|arrow_hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|menu_bar_item
argument_list|)
argument_list|,
name|arrow_hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Ops"
argument_list|)
expr_stmt|;
name|arrow
operator|=
name|gtk_arrow_new
argument_list|(
name|GTK_ARROW_DOWN
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|arrow_hbox
argument_list|)
argument_list|,
name|arrow
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|arrow_hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|arrow
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|arrow
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|arrow_hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_bar_item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_bar
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|util_box
argument_list|)
expr_stmt|;
comment|/*  The palette frame  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|indexedP
operator|->
name|palette
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|)
argument_list|,
name|P_AREA_WIDTH
argument_list|,
name|P_AREA_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|,
name|EVENT_MASK
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|)
argument_list|,
literal|"event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|indexed_palette_area_events
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|indexedP
operator|->
name|palette
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
comment|/* some helpful hints */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|" Click to select color.  Right-click to edit color"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/*  The action area  */
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|indexedP
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
argument_list|,
name|action_items
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
expr_stmt|;
name|indexed_palette_update
argument_list|(
name|gimage_id
argument_list|)
expr_stmt|;
name|indexed_palette_update_image_list
argument_list|()
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
expr_stmt|;
name|indexed_palette_update
argument_list|(
name|gimage_id
argument_list|)
expr_stmt|;
name|indexed_palette_update_image_list
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|indexed_palette_update_image_list ()
name|indexed_palette_update_image_list
parameter_list|()
block|{
name|int
name|default_index
decl_stmt|;
name|int
name|default_id
decl_stmt|;
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return;
name|default_id
operator|=
name|indexedP
operator|->
name|gimage_id
expr_stmt|;
name|indexedP
operator|->
name|image_menu
operator|=
name|create_image_menu
argument_list|(
operator|&
name|default_id
argument_list|,
operator|&
name|default_index
argument_list|,
name|image_menu_callback
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|indexedP
operator|->
name|image_option_menu
argument_list|)
argument_list|,
name|indexedP
operator|->
name|image_menu
argument_list|)
expr_stmt|;
if|if
condition|(
name|default_index
operator|!=
operator|-
literal|1
condition|)
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_IS_SENSITIVE
argument_list|(
name|indexedP
operator|->
name|vbox
argument_list|)
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|indexedP
operator|->
name|vbox
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|indexedP
operator|->
name|image_option_menu
argument_list|)
argument_list|,
name|default_index
argument_list|)
expr_stmt|;
name|indexed_palette_update
argument_list|(
name|default_id
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|GTK_WIDGET_IS_SENSITIVE
argument_list|(
name|indexedP
operator|->
name|vbox
argument_list|)
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|indexedP
operator|->
name|vbox
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|indexed_palette_clear
argument_list|()
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_palette_draw ()
name|indexed_palette_draw
parameter_list|()
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|,
name|l
decl_stmt|,
name|b
decl_stmt|;
name|int
name|col
decl_stmt|;
name|guchar
name|row
index|[
name|P_AREA_WIDTH
operator|*
literal|3
index|]
decl_stmt|;
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return;
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|indexedP
operator|->
name|gimage_id
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return;
name|col
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|16
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|16
operator|&&
name|col
operator|<
name|gimage
operator|->
name|num_cols
condition|;
name|j
operator|++
operator|,
name|col
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|CELL_WIDTH
condition|;
name|k
operator|++
control|)
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|3
condition|;
name|b
operator|++
control|)
name|row
index|[
operator|(
name|j
operator|*
name|CELL_WIDTH
operator|+
name|k
operator|)
operator|*
literal|3
operator|+
name|b
index|]
operator|=
name|gimage
operator|->
name|cmap
index|[
name|col
operator|*
literal|3
operator|+
name|b
index|]
expr_stmt|;
block|}
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|CELL_HEIGHT
condition|;
name|k
operator|++
control|)
block|{
for|for
control|(
name|l
operator|=
name|j
operator|*
name|CELL_WIDTH
init|;
name|l
operator|<
literal|16
operator|*
name|CELL_WIDTH
condition|;
name|l
operator|++
control|)
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
literal|3
condition|;
name|b
operator|++
control|)
name|row
index|[
name|l
operator|*
literal|3
operator|+
name|b
index|]
operator|=
operator|(
operator|(
operator|(
operator|(
name|i
operator|*
name|CELL_HEIGHT
operator|+
name|k
operator|)
operator|&
literal|0x4
operator|)
condition|?
operator|(
name|l
operator|)
else|:
operator|(
name|l
operator|+
literal|0x4
operator|)
operator|)
operator|&
literal|0x4
operator|)
condition|?
name|blend_light_check
index|[
literal|0
index|]
else|:
name|blend_dark_check
index|[
literal|0
index|]
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|)
argument_list|,
name|row
argument_list|,
literal|0
argument_list|,
name|i
operator|*
name|CELL_HEIGHT
operator|+
name|k
argument_list|,
name|P_AREA_WIDTH
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_draw
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_palette_clear ()
name|indexed_palette_clear
parameter_list|()
block|{
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|int
name|offset
decl_stmt|;
name|guchar
name|row
index|[
name|P_AREA_WIDTH
operator|*
literal|3
index|]
decl_stmt|;
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|P_AREA_HEIGHT
condition|;
name|i
operator|+=
literal|4
control|)
block|{
name|offset
operator|=
operator|(
name|i
operator|&
literal|0x4
operator|)
condition|?
literal|0x4
else|:
literal|0x0
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|P_AREA_WIDTH
condition|;
name|j
operator|++
control|)
block|{
name|row
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|row
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|row
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
operator|(
operator|(
name|j
operator|+
name|offset
operator|)
operator|&
literal|0x4
operator|)
condition|?
name|blend_light_check
index|[
literal|0
index|]
else|:
name|blend_dark_check
index|[
literal|0
index|]
expr_stmt|;
block|}
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|4
condition|;
name|j
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|)
argument_list|,
name|row
argument_list|,
literal|0
argument_list|,
name|i
operator|+
name|j
argument_list|,
name|P_AREA_WIDTH
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|indexedP
operator|->
name|palette
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_palette_update (int gimage_id)
name|indexed_palette_update
parameter_list|(
name|int
name|gimage_id
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return;
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|gimage_id
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return;
if|if
condition|(
name|gimage_base_type
argument_list|(
name|gimage
argument_list|)
operator|==
name|INDEXED
condition|)
block|{
name|indexedP
operator|->
name|gimage_id
operator|=
name|gimage_id
expr_stmt|;
name|indexed_palette_draw
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_palette_close_callback (GtkWidget * w,gpointer client_data)
name|indexed_palette_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return;
name|gtk_widget_hide
argument_list|(
name|indexedP
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_palette_select_callback (int r,int g,int b,ColorSelectState state,void * client_data)
name|indexed_palette_select_callback
parameter_list|(
name|int
name|r
parameter_list|,
name|int
name|g
parameter_list|,
name|int
name|b
parameter_list|,
name|ColorSelectState
name|state
parameter_list|,
name|void
modifier|*
name|client_data
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return;
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|indexedP
operator|->
name|gimage_id
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return;
if|if
condition|(
name|color_select
condition|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|COLOR_SELECT_UPDATE
case|:
break|break;
case|case
name|COLOR_SELECT_OK
case|:
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|r
expr_stmt|;
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|g
expr_stmt|;
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|b
expr_stmt|;
name|gdisplays_update_full
argument_list|(
name|gimage
operator|->
name|ID
argument_list|)
expr_stmt|;
name|indexed_palette_draw
argument_list|()
expr_stmt|;
comment|/* Fallthrough */
case|case
name|COLOR_SELECT_CANCEL
case|:
name|color_select_hide
argument_list|(
name|color_select
argument_list|)
expr_stmt|;
name|color_select_active
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|indexed_palette_area_events (GtkWidget * widget,GdkEvent * event)
name|indexed_palette_area_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|indexedP
operator|->
name|gimage_id
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_BUTTON_PRESS
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|indexedP
operator|->
name|col_index
operator|=
literal|16
operator|*
operator|(
operator|(
name|int
operator|)
name|bevent
operator|->
name|y
operator|/
name|CELL_HEIGHT
operator|)
operator|+
operator|(
operator|(
name|int
operator|)
name|bevent
operator|->
name|x
operator|/
name|CELL_WIDTH
operator|)
expr_stmt|;
name|r
operator|=
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|g
operator|=
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|palette_set_foreground
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|active_color
operator|==
name|BACKGROUND
condition|)
name|palette_set_background
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|3
condition|)
block|{
name|indexedP
operator|->
name|col_index
operator|=
literal|16
operator|*
operator|(
operator|(
name|int
operator|)
name|bevent
operator|->
name|y
operator|/
name|CELL_HEIGHT
operator|)
operator|+
operator|(
operator|(
name|int
operator|)
name|bevent
operator|->
name|x
operator|/
name|CELL_WIDTH
operator|)
expr_stmt|;
name|r
operator|=
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|g
operator|=
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|gimage
operator|->
name|cmap
index|[
name|indexedP
operator|->
name|col_index
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
operator|!
name|color_select
condition|)
block|{
name|color_select
operator|=
name|color_select_new
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|indexed_palette_select_callback
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|color_select_active
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|color_select_active
condition|)
name|color_select_show
argument_list|(
name|color_select
argument_list|)
expr_stmt|;
name|color_select_set_color
argument_list|(
name|color_select
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_menu_callback (GtkWidget * w,gpointer client_data)
name|image_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|indexedP
condition|)
return|return;
if|if
condition|(
name|gimage_get_ID
argument_list|(
operator|(
name|long
operator|)
name|client_data
argument_list|)
operator|!=
name|NULL
condition|)
block|{
name|indexed_palette_update
argument_list|(
operator|(
name|long
operator|)
name|client_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|create_image_menu (int * default_id,int * default_index,MenuItemCallback callback)
name|create_image_menu
parameter_list|(
name|int
modifier|*
name|default_id
parameter_list|,
name|int
modifier|*
name|default_index
parameter_list|,
name|MenuItemCallback
name|callback
parameter_list|)
block|{
specifier|extern
name|GSList
modifier|*
name|image_list
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|char
modifier|*
name|menu_item_label
decl_stmt|;
name|char
modifier|*
name|image_name
decl_stmt|;
name|GSList
modifier|*
name|tmp
decl_stmt|;
name|int
name|num_items
init|=
literal|0
decl_stmt|;
name|int
name|id
decl_stmt|;
name|id
operator|=
operator|-
literal|1
expr_stmt|;
operator|*
name|default_index
operator|=
operator|-
literal|1
expr_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
name|tmp
operator|=
name|image_list
expr_stmt|;
while|while
condition|(
name|tmp
condition|)
block|{
name|gimage
operator|=
name|tmp
operator|->
name|data
expr_stmt|;
name|tmp
operator|=
name|g_slist_next
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage_base_type
argument_list|(
name|gimage
argument_list|)
operator|==
name|INDEXED
condition|)
block|{
name|id
operator|=
operator|-
literal|1
expr_stmt|;
comment|/*  make sure the default index gets set to _something_, if possible  */
if|if
condition|(
operator|*
name|default_index
operator|==
operator|-
literal|1
condition|)
block|{
name|id
operator|=
name|gimage
operator|->
name|ID
expr_stmt|;
operator|*
name|default_index
operator|=
name|num_items
expr_stmt|;
block|}
if|if
condition|(
name|gimage
operator|->
name|ID
operator|==
operator|*
name|default_id
condition|)
block|{
name|id
operator|=
operator|*
name|default_id
expr_stmt|;
operator|*
name|default_index
operator|=
name|num_items
expr_stmt|;
block|}
name|image_name
operator|=
name|prune_filename
argument_list|(
name|gimage_filename
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|menu_item_label
operator|=
operator|(
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|image_name
argument_list|)
operator|+
literal|15
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|menu_item_label
argument_list|,
literal|"%s-%d"
argument_list|,
name|image_name
argument_list|,
name|gimage
operator|->
name|ID
argument_list|)
expr_stmt|;
name|menu_item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|menu_item_label
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|menu_item
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|callback
argument_list|,
call|(
name|gpointer
call|)
argument_list|(
operator|(
name|long
operator|)
name|gimage
operator|->
name|ID
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu_item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|menu_item_label
argument_list|)
expr_stmt|;
name|num_items
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|num_items
condition|)
block|{
name|menu_item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
literal|"none"
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|menu
argument_list|)
argument_list|,
name|menu_item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu_item
argument_list|)
expr_stmt|;
block|}
operator|*
name|default_id
operator|=
name|id
expr_stmt|;
return|return
name|menu
return|;
block|}
end_function

end_unit


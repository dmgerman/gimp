begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpedit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gtkhwrapbox.h"
end_include

begin_include
include|#
directive|include
file|"color-area.h"
end_include

begin_include
include|#
directive|include
file|"devices.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"indicator-area.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/default.xpm"
end_include

begin_include
include|#
directive|include
file|"pixmaps/swap.xpm"
end_include

begin_comment
comment|/*  local functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|toolbox_tool_button_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|toolbox_tool_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toolbox_destroy
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|toolbox_delete
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|toolbox_check_device
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toolbox_style_set_callback
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|GtkStyle
modifier|*
name|previous_style
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toolbox_drop_drawable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toolbox_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toolbox_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|toolbox_drop_buffer
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|COLUMNS
define|#
directive|define
name|COLUMNS
value|3
end_define

begin_define
DECL|macro|ROWS
define|#
directive|define
name|ROWS
value|8
end_define

begin_define
DECL|macro|MARGIN
define|#
directive|define
name|MARGIN
value|2
end_define

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|toolbox_shell
specifier|static
name|GtkWidget
modifier|*
name|toolbox_shell
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|toolbox_target_table
specifier|static
name|GtkTargetEntry
name|toolbox_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_URI_LIST
block|,
name|GIMP_TARGET_TEXT_PLAIN
block|,
name|GIMP_TARGET_NETSCAPE_URL
block|,
name|GIMP_TARGET_LAYER
block|,
name|GIMP_TARGET_CHANNEL
block|,
name|GIMP_TARGET_LAYER_MASK
block|,
name|GIMP_TARGET_TOOL
block|,
name|GIMP_TARGET_BUFFER
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|toolbox_n_targets
specifier|static
name|guint
name|toolbox_n_targets
init|=
operator|(
sizeof|sizeof
argument_list|(
name|toolbox_target_table
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|toolbox_target_table
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|toolbox_tool_button_toggled (GtkWidget * widget,gpointer data)
name|toolbox_tool_button_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|tool_info
operator|=
name|GIMP_TOOL_INFO
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|tool_info
operator|)
operator|&&
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
name|gimp_context_set_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|toolbox_tool_button_press (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|toolbox_tool_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
operator|(
name|event
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
operator|)
operator|&&
operator|(
name|event
operator|->
name|button
operator|==
literal|1
operator|)
condition|)
block|{
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp:tool-options-dialog"
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|toolbox_delete (GtkWidget * widget,GdkEvent * event,gpointer data)
name|toolbox_delete
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|app_exit
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toolbox_destroy (void)
name|toolbox_destroy
parameter_list|(
name|void
parameter_list|)
block|{
name|app_exit_finish
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|toolbox_check_device (GtkWidget * widget,GdkEvent * event,gpointer data)
name|toolbox_check_device
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|devices_check_change
argument_list|(
name|event
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_indicator_area (GtkWidget * parent,GimpContext * context)
name|create_indicator_area
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|ind_area
decl_stmt|;
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
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_wrap_box_pack
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|alignment
argument_list|,
name|NULL
argument_list|,
literal|"#indicator_area"
argument_list|)
expr_stmt|;
name|ind_area
operator|=
name|indicator_area_create
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|ind_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ind_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|alignment
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_color_area (GtkWidget * parent)
name|create_color_area
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|col_area
decl_stmt|;
name|GdkPixmap
modifier|*
name|default_pixmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|default_mask
decl_stmt|;
name|GdkPixmap
modifier|*
name|swap_pixmap
decl_stmt|;
name|GdkBitmap
modifier|*
name|swap_mask
decl_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_REALIZED
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_widget_realize
argument_list|(
name|parent
argument_list|)
expr_stmt|;
name|default_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|parent
operator|->
name|window
argument_list|,
operator|&
name|default_mask
argument_list|,
operator|&
name|parent
operator|->
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|default_xpm
argument_list|)
expr_stmt|;
name|swap_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|parent
operator|->
name|window
argument_list|,
operator|&
name|swap_mask
argument_list|,
operator|&
name|parent
operator|->
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|swap_xpm
argument_list|)
expr_stmt|;
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
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_wrap_box_pack
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_wrap_box_set_child_forced_break
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|alignment
argument_list|,
name|NULL
argument_list|,
literal|"#color_area"
argument_list|)
expr_stmt|;
name|col_area
operator|=
name|color_area_create
argument_list|(
literal|54
argument_list|,
literal|42
argument_list|,
name|default_pixmap
argument_list|,
name|default_mask
argument_list|,
name|swap_pixmap
argument_list|,
name|swap_mask
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|col_area
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|col_area
argument_list|,
name|_
argument_list|(
literal|"Foreground& background colors.  The black "
literal|"and white squares reset colors.  The arrows swap colors. Double "
literal|"click to select a color from a colorrequester."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|col_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|alignment
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toolbox_tool_changed (GimpContext * context,GimpToolInfo * tool_info,gpointer data)
name|toolbox_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|tool_info
condition|)
block|{
name|GtkWidget
modifier|*
name|toolbox_button
decl_stmt|;
name|toolbox_button
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|"toolbox_button"
argument_list|)
expr_stmt|;
if|if
condition|(
name|toolbox_button
operator|&&
operator|!
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toolbox_button
argument_list|)
operator|->
name|active
condition|)
block|{
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toolbox_button
argument_list|)
argument_list|,
name|toolbox_tool_button_toggled
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|gtk_widget_activate
argument_list|(
name|toolbox_button
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toolbox_button
argument_list|)
argument_list|,
name|toolbox_tool_button_toggled
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_tools (GtkWidget * wbox,GimpContext * context)
name|create_tools
parameter_list|(
name|GtkWidget
modifier|*
name|wbox
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|tool_info_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|button
operator|=
name|gtk_radio_button_new
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|"toolbox_button"
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_mode
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_wrap_box_pack
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|22
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|toolbox_tool_button_toggled
argument_list|)
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|toolbox_tool_button_press
argument_list|)
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|tool_info
operator|->
name|help
argument_list|,
name|tool_info
operator|->
name|help_data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|alignment
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|wbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|toolbox_create (void)
name|toolbox_create
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|toolbox_factory
decl_stmt|;
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|wbox
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|window
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_TOPLEVEL
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"toolbox"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"The GIMP"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Register dialog */
name|dialog_register_toolbox
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|toolbox_delete
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|toolbox_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"style_set"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|toolbox_style_set_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* We need to know when the current device changes, so we can update    * the correct tool - to do this we connect to motion events.    * We can't just use EXTENSION_EVENTS_CURSOR though, since that    * would get us extension events for the mouse pointer, and our    * device would change to that and not change back. So we check    * manually that all devices have a cursor, before establishing the check.    */
for|for
control|(
name|list
operator|=
name|gdk_input_list_devices
argument_list|()
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
if|if
condition|(
operator|!
operator|(
operator|(
name|GdkDeviceInfo
operator|*
operator|)
operator|(
name|list
operator|->
name|data
operator|)
operator|)
operator|->
name|has_cursor
condition|)
break|break;
block|}
if|if
condition|(
operator|!
name|list
condition|)
comment|/* all devices have cursor */
block|{
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|toolbox_check_device
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|window
argument_list|,
name|GDK_POINTER_MOTION_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_extension_events
argument_list|(
name|window
argument_list|,
name|GDK_EXTENSION_EVENTS_CURSOR
argument_list|)
expr_stmt|;
block|}
name|toolbox_factory
operator|=
name|menus_get_toolbox_factory
argument_list|()
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|window
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|toolbox_factory
operator|->
name|widget
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toolbox_factory
operator|->
name|widget
argument_list|)
expr_stmt|;
name|gtk_window_add_accel_group
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|toolbox_factory
operator|->
name|accel_group
argument_list|)
expr_stmt|;
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect_help_accel
argument_list|(
name|window
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"toolbox/toolbox.html"
argument_list|)
expr_stmt|;
name|wbox
operator|=
name|gtk_hwrap_box_new
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_wrap_box_set_justify
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|GTK_JUSTIFY_TOP
argument_list|)
expr_stmt|;
name|gtk_wrap_box_set_line_justify
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
comment|/*  magic number to set a default 5x5 layout  */
name|gtk_wrap_box_set_aspect_ratio
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|wbox
argument_list|)
argument_list|,
literal|5.0
operator|/
literal|5.9
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|wbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|wbox
argument_list|)
expr_stmt|;
name|create_tools
argument_list|(
name|wbox
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_signal_connect_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
argument_list|,
literal|"tool_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|toolbox_tool_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GTK_OBJECT
argument_list|(
name|wbox
argument_list|)
argument_list|)
expr_stmt|;
name|create_color_area
argument_list|(
name|wbox
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimprc
operator|.
name|show_indicators
condition|)
name|create_indicator_area
argument_list|(
name|wbox
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|window
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|toolbox_target_table
argument_list|,
name|toolbox_n_targets
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_file_dest_set
argument_list|(
name|window
argument_list|,
name|gimp_dnd_open_files
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|window
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|,
name|toolbox_drop_drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|window
argument_list|,
name|GIMP_TYPE_LAYER_MASK
argument_list|,
name|toolbox_drop_drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|window
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|,
name|toolbox_drop_drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|window
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|toolbox_drop_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|window
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|,
name|toolbox_drop_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|toolbox_shell
operator|=
name|window
expr_stmt|;
return|return
name|toolbox_shell
return|;
block|}
end_function

begin_function
name|void
DECL|function|toolbox_free (void)
name|toolbox_free
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|toolbox_shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toolbox_style_set_callback (GtkWidget * window,GtkStyle * previous_style,gpointer data)
name|toolbox_style_set_callback
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|GtkStyle
modifier|*
name|previous_style
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GdkGeometry
name|geometry
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|gint
name|xthickness
decl_stmt|;
name|gint
name|ythickness
decl_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|xthickness
operator|=
operator|(
operator|(
name|GtkStyleClass
operator|*
operator|)
name|style
operator|->
name|klass
operator|)
operator|->
name|xthickness
expr_stmt|;
name|ythickness
operator|=
operator|(
operator|(
name|GtkStyleClass
operator|*
operator|)
name|style
operator|->
name|klass
operator|)
operator|->
name|ythickness
expr_stmt|;
name|geometry
operator|.
name|min_width
operator|=
literal|2
operator|+
literal|24
operator|+
literal|2
operator|*
name|xthickness
expr_stmt|;
name|geometry
operator|.
name|min_height
operator|=
literal|80
operator|+
literal|24
operator|+
literal|2
operator|*
name|ythickness
expr_stmt|;
name|geometry
operator|.
name|width_inc
operator|=
literal|24
operator|+
literal|2
operator|*
name|xthickness
expr_stmt|;
name|geometry
operator|.
name|height_inc
operator|=
literal|24
operator|+
literal|2
operator|*
name|ythickness
expr_stmt|;
name|gtk_window_set_geometry_hints
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|geometry
argument_list|,
name|GDK_HINT_MIN_SIZE
operator||
name|GDK_HINT_RESIZE_INC
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toolbox_drop_drawable (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|toolbox_drop_drawable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpImage
modifier|*
name|new_gimage
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|GimpImageBaseType
name|type
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
case|case
name|RGBA_GIMAGE
case|:
name|type
operator|=
name|RGB
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
case|case
name|GRAYA_GIMAGE
case|:
name|type
operator|=
name|GRAY
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
case|case
name|INDEXEDA_GIMAGE
case|:
name|type
operator|=
name|INDEXED
expr_stmt|;
break|break;
default|default:
name|type
operator|=
name|RGB
expr_stmt|;
break|break;
block|}
name|new_gimage
operator|=
name|gimp_create_image
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|INDEXED
condition|)
comment|/* copy the colormap */
block|{
name|new_gimage
operator|->
name|num_cols
operator|=
name|gimage
operator|->
name|num_cols
expr_stmt|;
name|memcpy
argument_list|(
name|new_gimage
operator|->
name|cmap
argument_list|,
name|gimage
operator|->
name|cmap
argument_list|,
name|COLORMAP_SIZE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_set_resolution
argument_list|(
name|new_gimage
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|new_gimage
argument_list|,
name|gimage
operator|->
name|unit
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|new_layer
operator|=
name|gimp_layer_copy
argument_list|(
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  a non-layer drawable can't have an alpha channel,        *  so add one        */
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|TileManager
modifier|*
name|tiles
decl_stmt|;
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bytes
operator|+
literal|1
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|add_alpha_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|new_layer
operator|=
name|gimp_layer_new_from_tiles
argument_list|(
name|new_gimage
argument_list|,
name|gimp_image_base_type_with_alpha
argument_list|(
name|new_gimage
argument_list|)
argument_list|,
name|tiles
argument_list|,
literal|""
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|tile_manager_destroy
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_set_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|new_gimage
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_layer_translate
argument_list|(
name|new_layer
argument_list|,
operator|-
name|off_x
argument_list|,
operator|-
name|off_y
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_gimage
argument_list|,
name|new_layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|new_gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toolbox_drop_tool (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|toolbox_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_context_set_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|toolbox_drop_buffer (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|toolbox_drop_buffer
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|gimp_busy
condition|)
return|return;
name|gimp_edit_paste_as_new
argument_list|(
name|the_gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_BUFFER
argument_list|(
name|viewable
argument_list|)
operator|->
name|tiles
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


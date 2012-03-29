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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolordialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpanel.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_panel_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GType
name|gimp_color_panel_get_action_type
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_panel_dialog_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpColorPanel
modifier|*
name|panel
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpColorPanel,gimp_color_panel,GIMP_TYPE_COLOR_BUTTON)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorPanel
argument_list|,
argument|gimp_color_panel
argument_list|,
argument|GIMP_TYPE_COLOR_BUTTON
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_panel_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_color_panel_class_init
parameter_list|(
name|GimpColorPanelClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkButtonClass
modifier|*
name|button_class
init|=
name|GTK_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpColorButtonClass
modifier|*
name|color_button_class
init|=
name|GIMP_COLOR_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_color_panel_dispose
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_color_panel_button_press
expr_stmt|;
name|button_class
operator|->
name|clicked
operator|=
name|gimp_color_panel_clicked
expr_stmt|;
name|color_button_class
operator|->
name|color_changed
operator|=
name|gimp_color_panel_color_changed
expr_stmt|;
name|color_button_class
operator|->
name|get_action_type
operator|=
name|gimp_color_panel_get_action_type
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_init (GimpColorPanel * panel)
name|gimp_color_panel_init
parameter_list|(
name|GimpColorPanel
modifier|*
name|panel
parameter_list|)
block|{
name|panel
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|panel
operator|->
name|color_dialog
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_dispose (GObject * object)
name|gimp_color_panel_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
init|=
name|GIMP_COLOR_PANEL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|panel
operator|->
name|color_dialog
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|panel
operator|->
name|color_dialog
argument_list|)
expr_stmt|;
name|panel
operator|->
name|color_dialog
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_panel_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_color_panel_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
if|if
condition|(
name|gdk_event_triggers_context_menu
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|bevent
argument_list|)
condition|)
block|{
name|GimpColorButton
modifier|*
name|color_button
decl_stmt|;
name|GimpColorPanel
modifier|*
name|color_panel
decl_stmt|;
name|GtkUIManager
modifier|*
name|ui_manager
decl_stmt|;
name|GtkActionGroup
modifier|*
name|group
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|color_button
operator|=
name|GIMP_COLOR_BUTTON
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|color_panel
operator|=
name|GIMP_COLOR_PANEL
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|ui_manager
operator|=
name|GTK_UI_MANAGER
argument_list|(
name|color_button
operator|->
name|popup_menu
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_ui_manager_get_action_groups
argument_list|(
name|ui_manager
argument_list|)
operator|->
name|data
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|group
argument_list|,
literal|"color-button-use-foreground"
argument_list|)
expr_stmt|;
name|gtk_action_set_visible
argument_list|(
name|action
argument_list|,
name|color_panel
operator|->
name|context
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|group
argument_list|,
literal|"color-button-use-background"
argument_list|)
expr_stmt|;
name|gtk_action_set_visible
argument_list|(
name|action
argument_list|,
name|color_panel
operator|->
name|context
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_panel
operator|->
name|context
condition|)
block|{
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|group
argument_list|,
literal|"color-button-use-foreground"
argument_list|)
expr_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|color_panel
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|group
argument_list|,
literal|"color-button-use-background"
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|color_panel
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|group
argument_list|,
literal|"color-button-use-black"
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|group
argument_list|,
literal|"color-button-use-white"
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|action
argument_list|,
literal|"color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press_event
condition|)
return|return
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press_event
argument_list|(
name|widget
argument_list|,
name|bevent
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_clicked (GtkButton * button)
name|gimp_color_panel_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
init|=
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|panel
operator|->
name|color_dialog
condition|)
block|{
name|panel
operator|->
name|color_dialog
operator|=
name|gimp_color_dialog_new
argument_list|(
name|NULL
argument_list|,
name|panel
operator|->
name|context
argument_list|,
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
operator|->
name|title
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|(
specifier|const
name|GimpRGB
operator|*
operator|)
operator|&
name|color
argument_list|,
name|FALSE
argument_list|,
name|gimp_color_button_has_alpha
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|panel
operator|->
name|color_dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|panel
operator|->
name|color_dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|panel
operator|->
name|color_dialog
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_panel_dialog_update
argument_list|)
argument_list|,
name|panel
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|panel
operator|->
name|color_dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|gimp_color_panel_get_action_type (GimpColorButton * button)
name|gimp_color_panel_get_action_type
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
block|{
return|return
name|GIMP_TYPE_ACTION
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_panel_new (const gchar * title,const GimpRGB * color,GimpColorAreaType type,gint width,gint height)
name|gimp_color_panel_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_PANEL
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"type"
argument_list|,
name|type
argument_list|,
literal|"color"
argument_list|,
name|color
argument_list|,
literal|"area-width"
argument_list|,
name|width
argument_list|,
literal|"area-height"
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_color_changed (GimpColorButton * button)
name|gimp_color_panel_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|)
block|{
name|GimpColorPanel
modifier|*
name|panel
init|=
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
name|panel
operator|->
name|color_dialog
condition|)
block|{
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_color_dialog_set_color
argument_list|(
name|GIMP_COLOR_DIALOG
argument_list|(
name|panel
operator|->
name|color_dialog
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_panel_set_context (GimpColorPanel * panel,GimpContext * context)
name|gimp_color_panel_set_context
parameter_list|(
name|GimpColorPanel
modifier|*
name|panel
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_PANEL
argument_list|(
name|panel
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|panel
operator|->
name|context
operator|=
name|context
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_panel_dialog_update (GimpColorDialog * dialog,const GimpRGB * color,GimpColorDialogState state,GimpColorPanel * panel)
name|gimp_color_panel_dialog_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpColorPanel
modifier|*
name|panel
parameter_list|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|GIMP_COLOR_DIALOG_UPDATE
case|:
break|break;
case|case
name|GIMP_COLOR_DIALOG_OK
case|:
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|panel
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
comment|/* Fallthrough */
case|case
name|GIMP_COLOR_DIALOG_CANCEL
case|:
name|gtk_widget_hide
argument_list|(
name|panel
operator|->
name|color_dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * color_dialog module (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-palettes.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalettemru.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolordialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorhistory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_define
DECL|macro|COLOR_AREA_SIZE
define|#
directive|define
name|COLOR_AREA_SIZE
value|20
end_define

begin_enum
enum|enum
DECL|enum|__anon2c4c58400103
block|{
DECL|enumerator|UPDATE
name|UPDATE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_dialog_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_dialog_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_dialog_color_changed
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_history_add_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_dialog_history_selected
parameter_list|(
name|GimpColorHistory
modifier|*
name|history
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorDialog
argument_list|,
argument|gimp_color_dialog
argument_list|,
argument|GIMP_TYPE_VIEWABLE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_dialog_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|color_dialog_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_class_init (GimpColorDialogClass * klass)
name|gimp_color_dialog_class_init
parameter_list|(
name|GimpColorDialogClass
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
name|GtkDialogClass
modifier|*
name|dialog_class
init|=
name|GTK_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_color_dialog_constructed
expr_stmt|;
name|dialog_class
operator|->
name|response
operator|=
name|gimp_color_dialog_response
expr_stmt|;
name|color_dialog_signals
index|[
name|UPDATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"update"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpColorDialogClass
argument_list|,
name|update
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__BOXED_ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_RGB
argument_list|,
name|GIMP_TYPE_COLOR_DIALOG_STATE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_init (GimpColorDialog * dialog)
name|gimp_color_dialog_init
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Reset"
argument_list|)
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_OK"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|selection
operator|=
name|gimp_color_selection_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|dialog
operator|->
name|selection
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
name|dialog
operator|->
name|selection
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|selection
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_dialog_color_changed
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_constructed (GObject * object)
name|gimp_color_dialog_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorDialog
modifier|*
name|dialog
init|=
name|GIMP_COLOR_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpViewableDialog
modifier|*
name|viewable_dialog
init|=
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|history
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
comment|/* Color history box. */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_color_selection_get_right_vbox
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/* Button for adding to color history. */
name|button
operator|=
name|gimp_icon_button_new
argument_list|(
name|GIMP_ICON_LIST_ADD
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|_
argument_list|(
literal|"Add the current color to the color history"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_history_add_clicked
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
comment|/* Color history table. */
name|history
operator|=
name|gimp_color_history_new
argument_list|(
name|viewable_dialog
operator|->
name|context
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|history
argument_list|)
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
name|GTK_WIDGET
argument_list|(
name|history
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|history
argument_list|,
literal|"color-selected"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_dialog_history_selected
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_response (GtkDialog * gtk_dialog,gint response_id)
name|gimp_color_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|gtk_dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|GimpColorDialog
modifier|*
name|dialog
init|=
name|GIMP_COLOR_DIALOG
argument_list|(
name|gtk_dialog
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
name|gimp_color_selection_reset
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
name|gimp_color_selection_get_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dialog
argument_list|,
name|color_dialog_signals
index|[
name|UPDATE
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|color
argument_list|,
name|GIMP_COLOR_DIALOG_OK
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_color_selection_get_old_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dialog
argument_list|,
name|color_dialog_signals
index|[
name|UPDATE
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|color
argument_list|,
name|GIMP_COLOR_DIALOG_CANCEL
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_dialog_new (GimpViewable * viewable,GimpContext * context,const gchar * title,const gchar * icon_name,const gchar * desc,GtkWidget * parent,GimpDialogFactory * dialog_factory,const gchar * dialog_identifier,const GimpRGB * color,gboolean wants_updates,gboolean show_alpha)
name|gimp_color_dialog_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_identifier
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|wants_updates
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
block|{
name|GimpColorDialog
modifier|*
name|dialog
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|role
decl_stmt|;
name|gboolean
name|use_header_bar
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|viewable
operator|==
name|NULL
operator|||
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dialog_factory
operator|==
name|NULL
operator|||
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|dialog_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dialog_factory
operator|==
name|NULL
operator|||
name|dialog_identifier
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
name|role
operator|=
name|dialog_identifier
condition|?
name|dialog_identifier
else|:
literal|"gimp-color-selector"
expr_stmt|;
name|g_object_get
argument_list|(
name|gtk_settings_get_default
argument_list|()
argument_list|,
literal|"gtk-dialogs-use-header"
argument_list|,
operator|&
name|use_header_bar
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"role"
argument_list|,
name|role
argument_list|,
literal|"help-func"
argument_list|,
name|gimp_color_dialog_help_func
argument_list|,
literal|"help-id"
argument_list|,
name|GIMP_HELP_COLOR_DIALOG
argument_list|,
literal|"icon-name"
argument_list|,
name|icon_name
argument_list|,
literal|"description"
argument_list|,
name|desc
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"parent"
argument_list|,
name|parent
argument_list|,
literal|"use-header-bar"
argument_list|,
name|use_header_bar
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
block|{
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|viewable
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|parent
decl_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|icon
argument_list|)
expr_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|parent
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|parent
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|->
name|wants_updates
operator|=
name|wants_updates
expr_stmt|;
if|if
condition|(
name|dialog_factory
condition|)
block|{
name|gimp_dialog_factory_add_foreign
argument_list|(
name|dialog_factory
argument_list|,
name|dialog_identifier
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|gimp_widget_get_monitor
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_color_selection_set_show_alpha
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|show_alpha
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
argument_list|)
argument_list|,
literal|"gimp-context"
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_color_selection_set_config
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|context
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
argument_list|)
argument_list|,
literal|"gimp-context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_color_selection_set_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|gimp_color_selection_set_old_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_dialog_set_color (GimpColorDialog * dialog,const GimpRGB * color)
name|gimp_color_dialog_set_color
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|dialog
operator|->
name|selection
argument_list|,
name|gimp_color_dialog_color_changed
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gimp_color_selection_set_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|gimp_color_selection_set_old_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dialog
operator|->
name|selection
argument_list|,
name|gimp_color_dialog_color_changed
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_dialog_get_color (GimpColorDialog * dialog,GimpRGB * color)
name|gimp_color_dialog_get_color
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_color_selection_get_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_help_func (const gchar * help_id,gpointer help_data)
name|gimp_color_dialog_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{
name|GimpColorDialog
modifier|*
name|dialog
init|=
name|GIMP_COLOR_DIALOG
argument_list|(
name|help_data
argument_list|)
decl_stmt|;
name|GimpColorNotebook
modifier|*
name|notebook
decl_stmt|;
name|GimpColorSelector
modifier|*
name|current
decl_stmt|;
name|notebook
operator|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|gimp_color_selection_get_notebook
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|current
operator|=
name|gimp_color_notebook_get_current_selector
argument_list|(
name|notebook
argument_list|)
expr_stmt|;
name|help_id
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|current
argument_list|)
operator|->
name|help_id
expr_stmt|;
name|gimp_standard_help_func
argument_list|(
name|help_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_color_changed (GimpColorSelection * selection,GimpColorDialog * dialog)
name|gimp_color_dialog_color_changed
parameter_list|(
name|GimpColorSelection
modifier|*
name|selection
parameter_list|,
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|dialog
operator|->
name|wants_updates
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_color_selection_get_color
argument_list|(
name|selection
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|dialog
argument_list|,
name|color_dialog_signals
index|[
name|UPDATE
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|color
argument_list|,
name|GIMP_COLOR_DIALOG_UPDATE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* History-adding button callback */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_add_clicked (GtkWidget * widget,GimpColorDialog * dialog)
name|gimp_color_history_add_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpViewableDialog
modifier|*
name|viewable_dialog
init|=
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|GimpPalette
modifier|*
name|history
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|history
operator|=
name|gimp_palettes_get_color_history
argument_list|(
name|viewable_dialog
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gimp_color_selection_get_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_palette_mru_add
argument_list|(
name|GIMP_PALETTE_MRU
argument_list|(
name|history
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Color history callback  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_history_selected (GimpColorHistory * history,const GimpRGB * rgb,GimpColorDialog * dialog)
name|gimp_color_dialog_history_selected
parameter_list|(
name|GimpColorHistory
modifier|*
name|history
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gimp_color_selection_set_color
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


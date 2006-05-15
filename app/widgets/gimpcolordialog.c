begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * color_dialog module (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolordialog.h"
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
DECL|enum|__anon2bf5f3530103
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
name|gimp_color_dialog_dispose
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
name|gimp_color_history_color_clicked
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
name|gimp_color_history_color_changed
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

begin_decl_stmt
DECL|variable|color_dialogs
specifier|static
name|GList
modifier|*
name|color_dialogs
init|=
name|NULL
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
name|dispose
operator|=
name|gimp_color_dialog_dispose
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
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|arrow
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|color_dialogs
operator|=
name|g_list_prepend
argument_list|(
name|color_dialogs
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|selection
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
comment|/* The color history */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|1
operator|+
name|COLOR_HISTORY_SIZE
operator|/
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
operator|->
name|right_vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
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
name|arrow
operator|=
name|gtk_arrow_new
argument_list|(
name|GTK_ARROW_RIGHT
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|arrow
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|arrow
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|COLOR_HISTORY_SIZE
condition|;
name|i
operator|++
control|)
block|{
name|GimpRGB
name|history_color
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|column
decl_stmt|;
name|column
operator|=
name|i
operator|%
operator|(
name|COLOR_HISTORY_SIZE
operator|/
literal|2
operator|)
expr_stmt|;
name|row
operator|=
name|i
operator|/
operator|(
name|COLOR_HISTORY_SIZE
operator|/
literal|2
operator|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|button
argument_list|,
name|COLOR_AREA_SIZE
argument_list|,
name|COLOR_AREA_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
name|column
operator|+
literal|1
argument_list|,
name|column
operator|+
literal|2
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|color_history_get
argument_list|(
name|i
argument_list|,
operator|&
name|history_color
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|history
index|[
name|i
index|]
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|history_color
argument_list|,
name|GIMP_COLOR_AREA_SMALL_CHECKS
argument_list|,
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|dialog
operator|->
name|history
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|history
index|[
name|i
index|]
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
name|gimp_color_history_color_clicked
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|history
index|[
name|i
index|]
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_history_color_changed
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|i
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_dialog_dispose (GObject * object)
name|gimp_color_dialog_dispose
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
name|color_dialogs
operator|=
name|g_list_remove
argument_list|(
name|color_dialogs
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
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
name|gimp_color_history_add_clicked
argument_list|(
name|NULL
argument_list|,
name|dialog
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
DECL|function|gimp_color_dialog_new (GimpViewable * viewable,const gchar * title,const gchar * stock_id,const gchar * desc,GtkWidget * parent,GimpDialogFactory * dialog_factory,const gchar * dialog_identifier,const GimpRGB * color,gboolean wants_updates,gboolean show_alpha)
name|gimp_color_dialog_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
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
literal|"stock-id"
argument_list|,
name|stock_id
argument_list|,
literal|"description"
argument_list|,
name|desc
argument_list|,
literal|"parent"
argument_list|,
name|parent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
condition|)
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_hide
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|icon
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
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
argument_list|)
expr_stmt|;
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
name|notebook
operator|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|GIMP_COLOR_SELECTION
argument_list|(
name|dialog
operator|->
name|selection
argument_list|)
operator|->
name|notebook
argument_list|)
expr_stmt|;
name|help_id
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|notebook
operator|->
name|cur_page
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
comment|/*  color history callbacks  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_color_clicked (GtkWidget * widget,GimpColorDialog * dialog)
name|gimp_color_history_color_clicked
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
name|GimpColorArea
modifier|*
name|color_area
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|color_area
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
name|gimp_color_area_get_color
argument_list|(
name|color_area
argument_list|,
operator|&
name|color
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
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_history_color_changed (GtkWidget * widget,gpointer data)
name|gimp_color_history_color_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpRGB
name|changed_color
decl_stmt|;
name|gint
name|color_index
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gimp_color_area_get_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|changed_color
argument_list|)
expr_stmt|;
name|color_index
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|color_history_set
argument_list|(
name|color_index
argument_list|,
operator|&
name|changed_color
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|color_dialogs
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
name|GimpColorDialog
modifier|*
name|dialog
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|history
index|[
name|color_index
index|]
operator|!=
name|widget
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|dialog
operator|->
name|history
index|[
name|color_index
index|]
argument_list|,
name|gimp_color_history_color_changed
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|dialog
operator|->
name|history
index|[
name|color_index
index|]
argument_list|)
argument_list|,
operator|&
name|changed_color
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dialog
operator|->
name|history
index|[
name|color_index
index|]
argument_list|,
name|gimp_color_history_color_changed
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

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
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|shift_begin
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
name|shift_begin
operator|=
name|color_history_add
argument_list|(
operator|&
name|color
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|shift_begin
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
block|{
name|color_history_get
argument_list|(
name|i
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|dialog
operator|->
name|history
index|[
name|i
index|]
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


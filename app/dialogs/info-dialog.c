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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"info-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SB_WIDTH
define|#
directive|define
name|SB_WIDTH
value|10
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|InfoDialog
modifier|*
name|info_dialog_new_extended
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
name|wmclass_name
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
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gpointer
name|help_data
parameter_list|,
name|gboolean
name|in_notebook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|info_dialog_field_new
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|InfoFieldType
name|field_type
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|value_ptr
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|info_dialog_update_field
parameter_list|(
name|InfoField
modifier|*
name|info_field
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|InfoDialog
modifier|*
DECL|function|info_dialog_new (GimpViewable * viewable,const gchar * title,const gchar * wmclass_name,const gchar * stock_id,const gchar * desc,GimpHelpFunc help_func,gpointer help_data)
name|info_dialog_new
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
name|wmclass_name
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
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{
return|return
name|info_dialog_new_extended
argument_list|(
name|viewable
argument_list|,
name|title
argument_list|,
name|wmclass_name
argument_list|,
name|stock_id
argument_list|,
name|desc
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|InfoDialog
modifier|*
DECL|function|info_dialog_notebook_new (GimpViewable * viewable,const gchar * title,const gchar * wmclass_name,const gchar * stock_id,const gchar * desc,GimpHelpFunc help_func,gpointer help_data)
name|info_dialog_notebook_new
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
name|wmclass_name
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
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{
return|return
name|info_dialog_new_extended
argument_list|(
name|viewable
argument_list|,
name|title
argument_list|,
name|wmclass_name
argument_list|,
name|stock_id
argument_list|,
name|desc
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_free (InfoDialog * idialog)
name|info_dialog_free
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
name|idialog
operator|->
name|field_list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|idialog
operator|->
name|field_list
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_popup (InfoDialog * idialog)
name|info_dialog_popup
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_popdown (InfoDialog * idialog)
name|info_dialog_popdown
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|idialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|info_dialog_update (InfoDialog * idialog)
name|info_dialog_update
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|idialog
operator|->
name|field_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
name|info_dialog_update_field
argument_list|(
operator|(
name|InfoField
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|info_dialog_add_label (InfoDialog * idialog,gchar * title,gchar * text_ptr)
name|info_dialog_add_label
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|text_ptr
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|text_ptr
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|info_dialog_field_new
argument_list|(
name|idialog
argument_list|,
name|INFO_LABEL
argument_list|,
name|title
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|,
name|text_ptr
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|label
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|info_dialog_add_entry (InfoDialog * idialog,gchar * title,gchar * text_ptr,GCallback callback,gpointer callback_data)
name|info_dialog_add_entry
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|text_ptr
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|entry
argument_list|,
literal|50
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|text_ptr
condition|?
name|text_ptr
else|:
literal|""
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"changed"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|info_dialog_field_new
argument_list|(
name|idialog
argument_list|,
name|INFO_ENTRY
argument_list|,
name|title
argument_list|,
name|entry
argument_list|,
name|NULL
argument_list|,
name|text_ptr
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
return|return
name|entry
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|info_dialog_add_scale (InfoDialog * idialog,gchar * title,gdouble * value_ptr,gfloat lower,gfloat upper,gfloat step_increment,gfloat page_increment,gfloat page_size,gint digits,GCallback callback,gpointer callback_data)
name|info_dialog_add_scale
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
modifier|*
name|value_ptr
parameter_list|,
name|gfloat
name|lower
parameter_list|,
name|gfloat
name|upper
parameter_list|,
name|gfloat
name|step_increment
parameter_list|,
name|gfloat
name|page_increment
parameter_list|,
name|gfloat
name|page_size
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|value_ptr
condition|?
operator|*
name|value_ptr
else|:
literal|0
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
name|page_size
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|digits
operator|>=
literal|0
condition|)
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|MAX
argument_list|(
name|digits
argument_list|,
literal|6
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|adjustment
argument_list|,
literal|"value_changed"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|info_dialog_field_new
argument_list|(
name|idialog
argument_list|,
name|INFO_SCALE
argument_list|,
name|title
argument_list|,
name|scale
argument_list|,
name|adjustment
argument_list|,
name|value_ptr
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
return|return
name|scale
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|info_dialog_add_spinbutton (InfoDialog * idialog,gchar * title,gdouble * value_ptr,gfloat lower,gfloat upper,gfloat step_increment,gfloat page_increment,gfloat page_size,gfloat climb_rate,gint digits,GCallback callback,gpointer callback_data)
name|info_dialog_add_spinbutton
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
modifier|*
name|value_ptr
parameter_list|,
name|gfloat
name|lower
parameter_list|,
name|gfloat
name|upper
parameter_list|,
name|gfloat
name|step_increment
parameter_list|,
name|gfloat
name|page_increment
parameter_list|,
name|gfloat
name|page_size
parameter_list|,
name|gfloat
name|climb_rate
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.0
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
name|value_ptr
condition|?
operator|*
name|value_ptr
else|:
literal|0
argument_list|,
name|lower
argument_list|,
name|upper
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
name|page_size
argument_list|,
name|climb_rate
argument_list|,
name|MAX
argument_list|(
name|MIN
argument_list|(
name|digits
argument_list|,
literal|6
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|SB_WIDTH
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|adjustment
argument_list|,
literal|"value_changed"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|info_dialog_field_new
argument_list|(
name|idialog
argument_list|,
name|INFO_SPINBUTTON
argument_list|,
name|title
argument_list|,
name|alignment
argument_list|,
name|adjustment
argument_list|,
name|value_ptr
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
return|return
name|spinbutton
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|info_dialog_add_sizeentry (InfoDialog * idialog,gchar * title,gdouble * value_ptr,gint nfields,GimpUnit unit,gchar * unit_format,gboolean menu_show_pixels,gboolean menu_show_percent,gboolean show_refval,GimpSizeEntryUpdatePolicy update_policy,GCallback callback,gpointer callback_data)
name|info_dialog_add_sizeentry
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
modifier|*
name|value_ptr
parameter_list|,
name|gint
name|nfields
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gchar
modifier|*
name|unit_format
parameter_list|,
name|gboolean
name|menu_show_pixels
parameter_list|,
name|gboolean
name|menu_show_percent
parameter_list|,
name|gboolean
name|show_refval
parameter_list|,
name|GimpSizeEntryUpdatePolicy
name|update_policy
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|idialog
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.0
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|gimp_size_entry_new
argument_list|(
name|nfields
argument_list|,
name|unit
argument_list|,
name|unit_format
argument_list|,
name|menu_show_pixels
argument_list|,
name|menu_show_percent
argument_list|,
name|show_refval
argument_list|,
name|SB_WIDTH
argument_list|,
name|update_policy
argument_list|)
expr_stmt|;
if|if
condition|(
name|value_ptr
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nfields
condition|;
name|i
operator|++
control|)
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|i
argument_list|,
name|value_ptr
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|g_signal_connect
argument_list|(
name|sizeentry
argument_list|,
literal|"value_changed"
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|sizeentry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|sizeentry
argument_list|)
expr_stmt|;
name|info_dialog_field_new
argument_list|(
name|idialog
argument_list|,
name|INFO_SIZEENTRY
argument_list|,
name|title
argument_list|,
name|alignment
argument_list|,
name|GTK_OBJECT
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|value_ptr
argument_list|,
name|callback
argument_list|,
name|callback_data
argument_list|)
expr_stmt|;
return|return
name|sizeentry
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|InfoDialog
modifier|*
DECL|function|info_dialog_new_extended (GimpViewable * viewable,const gchar * title,const gchar * wmclass_name,const gchar * stock_id,const gchar * desc,GimpHelpFunc help_func,gpointer help_data,gboolean in_notebook)
name|info_dialog_new_extended
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
name|wmclass_name
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
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gpointer
name|help_data
parameter_list|,
name|gboolean
name|in_notebook
parameter_list|)
block|{
name|InfoDialog
modifier|*
name|idialog
decl_stmt|;
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|info_table
decl_stmt|;
name|GtkWidget
modifier|*
name|info_notebook
decl_stmt|;
name|idialog
operator|=
name|g_new
argument_list|(
name|InfoDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|idialog
operator|->
name|field_list
operator|=
name|NULL
expr_stmt|;
name|idialog
operator|->
name|nfields
operator|=
literal|0
expr_stmt|;
name|shell
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|viewable
argument_list|,
name|title
argument_list|,
name|wmclass_name
argument_list|,
name|stock_id
argument_list|,
name|desc
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_type_hint
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GDK_WINDOW_TYPE_HINT_UTILITY
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|info_table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|in_notebook
condition|)
block|{
name|info_notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|info_table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|info_notebook
argument_list|)
argument_list|,
name|info_table
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"General"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|info_notebook
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|info_notebook
operator|=
name|NULL
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|info_table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|idialog
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
name|idialog
operator|->
name|vbox
operator|=
name|vbox
expr_stmt|;
name|idialog
operator|->
name|info_table
operator|=
name|info_table
expr_stmt|;
name|idialog
operator|->
name|info_notebook
operator|=
name|info_notebook
expr_stmt|;
if|if
condition|(
name|in_notebook
condition|)
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|info_notebook
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|info_table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|idialog
operator|->
name|vbox
argument_list|)
expr_stmt|;
return|return
name|idialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|info_dialog_field_new (InfoDialog * idialog,InfoFieldType field_type,gchar * title,GtkWidget * widget,GtkObject * obj,gpointer value_ptr,GCallback callback,gpointer callback_data)
name|info_dialog_field_new
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|InfoFieldType
name|field_type
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkObject
modifier|*
name|obj
parameter_list|,
name|gpointer
name|value_ptr
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|InfoField
modifier|*
name|field
decl_stmt|;
name|gint
name|row
decl_stmt|;
name|field
operator|=
name|g_new
argument_list|(
name|InfoField
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|row
operator|=
name|idialog
operator|->
name|nfields
operator|+
literal|1
expr_stmt|;
name|gtk_table_resize
argument_list|(
name|GTK_TABLE
argument_list|(
name|idialog
operator|->
name|info_table
argument_list|)
argument_list|,
literal|2
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|idialog
operator|->
name|info_table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|row
operator|-
literal|1
argument_list|,
name|row
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|idialog
operator|->
name|info_table
argument_list|)
argument_list|,
name|widget
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|row
operator|-
literal|1
argument_list|,
name|row
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|idialog
operator|->
name|info_table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|idialog
operator|->
name|info_table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|field
operator|->
name|field_type
operator|=
name|field_type
expr_stmt|;
if|if
condition|(
name|obj
operator|==
name|NULL
condition|)
name|field
operator|->
name|obj
operator|=
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
expr_stmt|;
else|else
name|field
operator|->
name|obj
operator|=
name|obj
expr_stmt|;
name|field
operator|->
name|value_ptr
operator|=
name|value_ptr
expr_stmt|;
name|field
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|field
operator|->
name|callback_data
operator|=
name|callback_data
expr_stmt|;
name|idialog
operator|->
name|field_list
operator|=
name|g_slist_prepend
argument_list|(
name|idialog
operator|->
name|field_list
argument_list|,
name|field
argument_list|)
expr_stmt|;
name|idialog
operator|->
name|nfields
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|info_dialog_update_field (InfoField * field)
name|info_dialog_update_field
parameter_list|(
name|InfoField
modifier|*
name|field
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|old_text
decl_stmt|;
name|gint
name|num
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|field
operator|->
name|value_ptr
operator|==
name|NULL
condition|)
return|return;
if|if
condition|(
name|field
operator|->
name|field_type
operator|!=
name|INFO_LABEL
condition|)
name|g_signal_handlers_block_by_func
argument_list|(
name|field
operator|->
name|obj
argument_list|,
name|field
operator|->
name|callback
argument_list|,
name|field
operator|->
name|callback_data
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|field
operator|->
name|field_type
condition|)
block|{
case|case
name|INFO_LABEL
case|:
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|field
operator|->
name|obj
argument_list|)
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|field
operator|->
name|value_ptr
argument_list|)
expr_stmt|;
break|break;
case|case
name|INFO_ENTRY
case|:
name|old_text
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|field
operator|->
name|obj
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|old_text
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|field
operator|->
name|value_ptr
argument_list|)
condition|)
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|field
operator|->
name|obj
argument_list|)
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|field
operator|->
name|value_ptr
argument_list|)
expr_stmt|;
break|break;
case|case
name|INFO_SCALE
case|:
case|case
name|INFO_SPINBUTTON
case|:
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|field
operator|->
name|obj
argument_list|)
argument_list|,
operator|*
operator|(
operator|(
name|gdouble
operator|*
operator|)
name|field
operator|->
name|value_ptr
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|INFO_SIZEENTRY
case|:
name|num
operator|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|field
operator|->
name|obj
argument_list|)
operator|->
name|number_of_fields
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num
condition|;
name|i
operator|++
control|)
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|field
operator|->
name|obj
argument_list|)
argument_list|,
name|i
argument_list|,
operator|(
operator|(
name|gdouble
operator|*
operator|)
name|field
operator|->
name|value_ptr
operator|)
index|[
name|i
index|]
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s: Unknown info_dialog field type."
argument_list|,
name|G_STRLOC
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|field
operator|->
name|field_type
operator|!=
name|INFO_LABEL
condition|)
name|g_signal_handlers_unblock_by_func
argument_list|(
name|field
operator|->
name|obj
argument_list|,
name|field
operator|->
name|callback
argument_list|,
name|field
operator|->
name|callback_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


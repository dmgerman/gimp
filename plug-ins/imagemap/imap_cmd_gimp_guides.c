begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2004 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"imap_commands.h"
end_include

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_rectangle.h"
end_include

begin_include
include|#
directive|include
file|"imap_ui_grid.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
DECL|struct|__anon2c2126c30108
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|list
name|ObjectList_t
modifier|*
name|list
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|alternate
name|GtkWidget
modifier|*
name|alternate
decl_stmt|;
DECL|member|all
name|GtkWidget
modifier|*
name|all
decl_stmt|;
DECL|member|left_border
name|GtkWidget
modifier|*
name|left_border
decl_stmt|;
DECL|member|right_border
name|GtkWidget
modifier|*
name|right_border
decl_stmt|;
DECL|member|upper_border
name|GtkWidget
modifier|*
name|upper_border
decl_stmt|;
DECL|member|lower_border
name|GtkWidget
modifier|*
name|lower_border
decl_stmt|;
DECL|member|url
name|GtkWidget
modifier|*
name|url
decl_stmt|;
DECL|typedef|GimpGuidesDialog_t
block|}
name|GimpGuidesDialog_t
typedef|;
end_typedef

begin_function
specifier|static
name|gint
DECL|function|guide_sort_func (gconstpointer a,gconstpointer b)
name|guide_sort_func
parameter_list|(
name|gconstpointer
name|a
parameter_list|,
name|gconstpointer
name|b
parameter_list|)
block|{
return|return
name|GPOINTER_TO_INT
argument_list|(
name|a
argument_list|)
operator|-
name|GPOINTER_TO_INT
argument_list|(
name|b
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_guides_ok_cb (gpointer data)
name|gimp_guides_ok_cb
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpGuidesDialog_t
modifier|*
name|param
init|=
operator|(
name|GimpGuidesDialog_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|guide_num
decl_stmt|;
name|GSList
modifier|*
name|hguides
decl_stmt|,
modifier|*
name|hg
decl_stmt|;
name|GSList
modifier|*
name|vguides
decl_stmt|,
modifier|*
name|vg
decl_stmt|;
name|gboolean
name|all
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|url
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|param
operator|->
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
comment|/* First get some dialog values */
name|all
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|param
operator|->
name|all
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|param
operator|->
name|left_border
argument_list|)
argument_list|)
condition|)
name|vguides
operator|=
name|g_slist_append
argument_list|(
name|NULL
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|vguides
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|param
operator|->
name|right_border
argument_list|)
argument_list|)
condition|)
name|vguides
operator|=
name|g_slist_append
argument_list|(
name|vguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|gimp_image_width
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|param
operator|->
name|upper_border
argument_list|)
argument_list|)
condition|)
name|hguides
operator|=
name|g_slist_append
argument_list|(
name|NULL
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|hguides
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|param
operator|->
name|lower_border
argument_list|)
argument_list|)
condition|)
name|hguides
operator|=
name|g_slist_append
argument_list|(
name|hguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|gimp_image_height
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|url
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|param
operator|->
name|url
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Next get all the GIMP guides */
name|guide_num
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image
argument_list|,
literal|0
argument_list|)
expr_stmt|;
while|while
condition|(
name|guide_num
operator|>
literal|0
condition|)
block|{
name|gint
name|position
init|=
name|gimp_image_get_guide_position
argument_list|(
name|image
argument_list|,
name|guide_num
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_image_get_guide_orientation
argument_list|(
name|image
argument_list|,
name|guide_num
argument_list|)
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
block|{
name|hguides
operator|=
name|g_slist_insert_sorted
argument_list|(
name|hguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|position
argument_list|)
argument_list|,
name|guide_sort_func
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* GIMP_ORIENTATION_VERTICAL */
name|vguides
operator|=
name|g_slist_insert_sorted
argument_list|(
name|vguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|position
argument_list|)
argument_list|,
name|guide_sort_func
argument_list|)
expr_stmt|;
block|}
name|guide_num
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image
argument_list|,
name|guide_num
argument_list|)
expr_stmt|;
block|}
comment|/* Create the areas */
name|subcommand_start
argument_list|(
name|_
argument_list|(
literal|"Use Gimp Guides"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|hg
operator|=
name|hguides
init|;
name|hg
operator|&&
name|hg
operator|->
name|next
condition|;
name|hg
operator|=
operator|(
name|all
operator|)
condition|?
name|hg
operator|->
name|next
else|:
name|hg
operator|->
name|next
operator|->
name|next
control|)
block|{
name|gint
name|y
init|=
name|GPOINTER_TO_INT
argument_list|(
name|hg
operator|->
name|data
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|GPOINTER_TO_INT
argument_list|(
name|hg
operator|->
name|next
operator|->
name|data
argument_list|)
operator|-
name|y
decl_stmt|;
for|for
control|(
name|vg
operator|=
name|vguides
init|;
name|vg
operator|&&
name|vg
operator|->
name|next
condition|;
name|vg
operator|=
operator|(
name|all
operator|)
condition|?
name|vg
operator|->
name|next
else|:
name|vg
operator|->
name|next
operator|->
name|next
control|)
block|{
name|gint
name|x
init|=
name|GPOINTER_TO_INT
argument_list|(
name|vg
operator|->
name|data
argument_list|)
decl_stmt|;
name|gint
name|width
init|=
name|GPOINTER_TO_INT
argument_list|(
name|vg
operator|->
name|next
operator|->
name|data
argument_list|)
operator|-
name|x
decl_stmt|;
name|Object_t
modifier|*
name|obj
init|=
name|create_rectangle
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
decl_stmt|;
name|Command_t
modifier|*
name|command
init|=
name|create_command_new
argument_list|(
name|param
operator|->
name|list
argument_list|,
name|obj
argument_list|)
decl_stmt|;
name|object_set_url
argument_list|(
name|obj
argument_list|,
name|url
argument_list|)
expr_stmt|;
name|command_execute
argument_list|(
name|command
argument_list|)
expr_stmt|;
block|}
block|}
name|subcommand_end
argument_list|()
expr_stmt|;
name|preview_redraw
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpGuidesDialog_t
modifier|*
DECL|function|make_gimp_guides_dialog (void)
name|make_gimp_guides_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpGuidesDialog_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|GimpGuidesDialog_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|grid
decl_stmt|,
modifier|*
name|frame
decl_stmt|,
modifier|*
name|hbox
decl_stmt|,
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|dialog
operator|=
name|data
operator|->
name|dialog
operator|=
name|make_default_dialog
argument_list|(
name|_
argument_list|(
literal|"Use Gimp Guides"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_set_ok_cb
argument_list|(
name|dialog
argument_list|,
name|gimp_guides_ok_cb
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|grid
operator|=
name|default_dialog_add_grid
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Create"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|frame
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|data
operator|->
name|alternate
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Al_ternate"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|data
operator|->
name|alternate
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
name|data
operator|->
name|alternate
argument_list|)
expr_stmt|;
name|data
operator|->
name|all
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|data
operator|->
name|alternate
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"A_ll"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|data
operator|->
name|all
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
name|data
operator|->
name|all
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Add Additional Guides"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|frame
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|data
operator|->
name|left_border
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"L_eft border"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|data
operator|->
name|left_border
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|left_border
argument_list|)
expr_stmt|;
name|data
operator|->
name|right_border
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Right border"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|data
operator|->
name|right_border
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|right_border
argument_list|)
expr_stmt|;
name|data
operator|->
name|upper_border
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Upper border"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|data
operator|->
name|upper_border
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|upper_border
argument_list|)
expr_stmt|;
name|data
operator|->
name|lower_border
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Lo_wer border"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|data
operator|->
name|lower_border
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|lower_border
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|hbox
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Base URL:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
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
literal|0
argument_list|)
expr_stmt|;
name|data
operator|->
name|url
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|data
operator|->
name|url
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|data
operator|->
name|url
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|data
operator|->
name|url
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|init_gimp_guides_dialog (GimpGuidesDialog_t * dialog,ObjectList_t * list,GimpDrawable * drawable)
name|init_gimp_guides_dialog
parameter_list|(
name|GimpGuidesDialog_t
modifier|*
name|dialog
parameter_list|,
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|dialog
operator|->
name|list
operator|=
name|list
expr_stmt|;
name|dialog
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|do_create_gimp_guides_dialog (ObjectList_t * list,GimpDrawable * drawable)
name|do_create_gimp_guides_dialog
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
specifier|static
name|GimpGuidesDialog_t
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
name|dialog
operator|=
name|make_gimp_guides_dialog
argument_list|()
expr_stmt|;
name|init_gimp_guides_dialog
argument_list|(
name|dialog
argument_list|,
name|list
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|default_dialog_show
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function_decl
specifier|static
name|CmdExecuteValue_t
name|gimp_guides_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_guides_command_class
specifier|static
name|CommandClass_t
name|gimp_guides_command_class
init|=
block|{
name|NULL
block|,
comment|/* guides_command_destruct */
name|gimp_guides_command_execute
block|,
name|NULL
block|,
comment|/* guides_command_undo */
name|NULL
comment|/* guides_command_redo */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon2c2126c30208
typedef|typedef
struct|struct
block|{
DECL|member|parent
name|Command_t
name|parent
decl_stmt|;
DECL|member|list
name|ObjectList_t
modifier|*
name|list
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|typedef|GimpGuidesCommand_t
block|}
name|GimpGuidesCommand_t
typedef|;
end_typedef

begin_function
name|Command_t
modifier|*
DECL|function|gimp_guides_command_new (ObjectList_t * list,GimpDrawable * drawable)
name|gimp_guides_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpGuidesCommand_t
modifier|*
name|command
init|=
name|g_new
argument_list|(
name|GimpGuidesCommand_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|command
operator|->
name|list
operator|=
name|list
expr_stmt|;
name|command
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
return|return
name|command_init
argument_list|(
operator|&
name|command
operator|->
name|parent
argument_list|,
name|_
argument_list|(
literal|"Use Gimp Guides"
argument_list|)
argument_list|,
operator|&
name|gimp_guides_command_class
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|CmdExecuteValue_t
DECL|function|gimp_guides_command_execute (Command_t * parent)
name|gimp_guides_command_execute
parameter_list|(
name|Command_t
modifier|*
name|parent
parameter_list|)
block|{
name|GimpGuidesCommand_t
modifier|*
name|command
init|=
operator|(
name|GimpGuidesCommand_t
operator|*
operator|)
name|parent
decl_stmt|;
name|do_create_gimp_guides_dialog
argument_list|(
name|command
operator|->
name|list
argument_list|,
name|command
operator|->
name|drawable
argument_list|)
expr_stmt|;
return|return
name|CMD_DESTRUCT
return|;
block|}
end_function

end_unit


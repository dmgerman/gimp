begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * color_notebook module (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"color_notebook.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/color_selector.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|color_notebook_ok_callback
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
name|color_notebook_cancel_callback
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
name|gint
name|color_notebook_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_notebook_update_callback
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_notebook_page_switch
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GtkNotebookPage
modifier|*
parameter_list|,
name|guint
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|action_items
specifier|static
name|ActionAreaItem
name|action_items
index|[
literal|2
index|]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"OK"
argument_list|)
block|,
name|color_notebook_ok_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Cancel"
argument_list|)
block|,
name|color_notebook_cancel_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* information we keep on each registered colour selector */
end_comment

begin_typedef
DECL|struct|_ColorSelectorInfo
typedef|typedef
struct|struct
name|_ColorSelectorInfo
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
comment|/* label used in notebook tab */
DECL|member|m
name|GimpColorSelectorMethods
name|m
decl_stmt|;
DECL|member|refs
name|int
name|refs
decl_stmt|;
comment|/* number of instances around */
DECL|member|active
name|gboolean
name|active
decl_stmt|;
DECL|member|death_callback
name|void
function_decl|(
modifier|*
name|death_callback
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|death_data
name|void
modifier|*
name|death_data
decl_stmt|;
DECL|member|next
name|struct
name|_ColorSelectorInfo
modifier|*
name|next
decl_stmt|;
DECL|typedef|ColorSelectorInfo
block|}
name|ColorSelectorInfo
typedef|;
end_typedef

begin_typedef
DECL|struct|_ColorSelectorInstance
typedef|typedef
struct|struct
name|_ColorSelectorInstance
block|{
DECL|member|color_notebook
name|_ColorNotebook
modifier|*
name|color_notebook
decl_stmt|;
DECL|member|info
name|ColorSelectorInfo
modifier|*
name|info
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
comment|/* main widget */
DECL|member|selector_data
name|gpointer
name|selector_data
decl_stmt|;
DECL|member|next
name|struct
name|_ColorSelectorInstance
modifier|*
name|next
decl_stmt|;
DECL|typedef|ColorSelectorInstance
block|}
name|ColorSelectorInstance
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|selector_death
parameter_list|(
name|ColorSelectorInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* master list of all registered colour selectors */
end_comment

begin_decl_stmt
DECL|variable|selector_info
specifier|static
name|ColorSelectorInfo
modifier|*
name|selector_info
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|RED
define|#
directive|define
name|RED
value|0
end_define

begin_define
DECL|macro|GREEN
define|#
directive|define
name|GREEN
value|1
end_define

begin_define
DECL|macro|BLUE
define|#
directive|define
name|BLUE
value|2
end_define

begin_define
DECL|macro|NUM_COLORS
define|#
directive|define
name|NUM_COLORS
value|3
end_define

begin_function
name|ColorNotebookP
DECL|function|color_notebook_new (int r,int g,int b,ColorNotebookCallback callback,void * client_data,int wants_updates)
name|color_notebook_new
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
name|ColorNotebookCallback
name|callback
parameter_list|,
name|void
modifier|*
name|client_data
parameter_list|,
name|int
name|wants_updates
parameter_list|)
block|{
name|ColorNotebookP
name|cnp
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|ColorSelectorInfo
modifier|*
name|info
decl_stmt|;
name|ColorSelectorInstance
modifier|*
name|csel
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|selector_info
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cnp
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|_ColorNotebook
argument_list|)
argument_list|)
expr_stmt|;
name|cnp
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|cnp
operator|->
name|client_data
operator|=
name|client_data
expr_stmt|;
name|cnp
operator|->
name|wants_updates
operator|=
name|wants_updates
expr_stmt|;
name|cnp
operator|->
name|selectors
operator|=
name|NULL
expr_stmt|;
name|cnp
operator|->
name|cur_page
operator|=
name|NULL
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|RED
index|]
operator|=
name|cnp
operator|->
name|orig_values
index|[
name|RED
index|]
operator|=
name|r
operator|&
literal|0xff
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|GREEN
index|]
operator|=
name|cnp
operator|->
name|orig_values
index|[
name|GREEN
index|]
operator|=
name|g
operator|&
literal|0xff
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|BLUE
index|]
operator|=
name|cnp
operator|->
name|orig_values
index|[
name|BLUE
index|]
operator|=
name|b
operator|&
literal|0xff
expr_stmt|;
comment|/* window hints need to stay the same, so people's window manager    * setups still work */
name|cnp
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
name|cnp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"color_selection"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Color Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  handle the wm close signal */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|color_notebook_delete_callback
argument_list|,
name|cnp
argument_list|)
expr_stmt|;
comment|/* do we actually need a notebook? */
if|if
condition|(
name|selector_info
operator|->
name|next
condition|)
block|{
name|cnp
operator|->
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|cnp
operator|->
name|notebook
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|cnp
operator|->
name|notebook
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* only one selector */
block|{
name|cnp
operator|->
name|notebook
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* create each registered colour selector */
name|info
operator|=
name|selector_info
expr_stmt|;
while|while
condition|(
name|info
condition|)
block|{
if|if
condition|(
name|info
operator|->
name|active
condition|)
block|{
name|csel
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ColorSelectorInstance
argument_list|)
argument_list|)
expr_stmt|;
name|csel
operator|->
name|color_notebook
operator|=
name|cnp
expr_stmt|;
name|csel
operator|->
name|info
operator|=
name|info
expr_stmt|;
name|info
operator|->
name|refs
operator|++
expr_stmt|;
name|csel
operator|->
name|frame
operator|=
name|info
operator|->
name|m
operator|.
name|new
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|color_notebook_update_callback
argument_list|,
name|csel
argument_list|,
operator|&
name|csel
operator|->
name|selector_data
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|csel
operator|->
name|frame
argument_list|)
argument_list|,
literal|"gimp_color_notebook"
argument_list|,
name|csel
argument_list|)
expr_stmt|;
if|if
condition|(
name|cnp
operator|->
name|notebook
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|info
operator|->
name|name
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/* hide the frame, so it doesn't get selected by mistake */
name|gtk_widget_hide
argument_list|(
name|csel
operator|->
name|frame
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|cnp
operator|->
name|notebook
argument_list|)
argument_list|,
name|csel
operator|->
name|frame
argument_list|,
name|label
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|csel
operator|->
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|csel
operator|->
name|frame
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cnp
operator|->
name|cur_page
condition|)
name|cnp
operator|->
name|cur_page
operator|=
name|csel
expr_stmt|;
comment|/* link into list of all selectors hanging off the new notebook */
name|csel
operator|->
name|next
operator|=
name|cnp
operator|->
name|selectors
expr_stmt|;
name|cnp
operator|->
name|selectors
operator|=
name|csel
expr_stmt|;
block|}
name|info
operator|=
name|info
operator|->
name|next
expr_stmt|;
block|}
comment|/*  The action area  */
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|cnp
expr_stmt|;
name|action_items
index|[
literal|1
index|]
operator|.
name|user_data
operator|=
name|cnp
expr_stmt|;
if|if
condition|(
name|cnp
operator|->
name|wants_updates
condition|)
block|{
name|action_items
index|[
literal|0
index|]
operator|.
name|label
operator|=
name|_
argument_list|(
literal|"Close"
argument_list|)
expr_stmt|;
name|action_items
index|[
literal|1
index|]
operator|.
name|label
operator|=
name|_
argument_list|(
literal|"Revert to Old Color"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|action_items
index|[
literal|0
index|]
operator|.
name|label
operator|=
name|_
argument_list|(
literal|"OK"
argument_list|)
expr_stmt|;
name|action_items
index|[
literal|1
index|]
operator|.
name|label
operator|=
name|_
argument_list|(
literal|"Cancel"
argument_list|)
expr_stmt|;
block|}
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
argument_list|,
name|action_items
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/* this must come after showing the widget, otherwise we get a    * switch_page signal for a non-visible color selector, which is bad    * news. */
if|if
condition|(
name|cnp
operator|->
name|notebook
condition|)
block|{
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|cnp
operator|->
name|notebook
argument_list|)
argument_list|,
name|cnp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|cnp
operator|->
name|notebook
argument_list|)
argument_list|,
literal|"switch_page"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|color_notebook_page_switch
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|cnp
return|;
block|}
end_function

begin_function
name|void
DECL|function|color_notebook_show (ColorNotebookP cnp)
name|color_notebook_show
parameter_list|(
name|ColorNotebookP
name|cnp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|cnp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_notebook_hide (ColorNotebookP cnp)
name|color_notebook_hide
parameter_list|(
name|ColorNotebookP
name|cnp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|cnp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_notebook_free (ColorNotebookP cnp)
name|color_notebook_free
parameter_list|(
name|ColorNotebookP
name|cnp
parameter_list|)
block|{
name|ColorSelectorInstance
modifier|*
name|csel
decl_stmt|,
modifier|*
name|next
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|cnp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|cnp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/* call the free functions for all the colour selectors */
name|csel
operator|=
name|cnp
operator|->
name|selectors
expr_stmt|;
while|while
condition|(
name|csel
condition|)
block|{
name|next
operator|=
name|csel
operator|->
name|next
expr_stmt|;
name|csel
operator|->
name|info
operator|->
name|m
operator|.
name|free
argument_list|(
name|csel
operator|->
name|selector_data
argument_list|)
expr_stmt|;
name|csel
operator|->
name|info
operator|->
name|refs
operator|--
expr_stmt|;
if|if
condition|(
name|csel
operator|->
name|info
operator|->
name|refs
operator|==
literal|0
operator|&&
operator|!
name|csel
operator|->
name|info
operator|->
name|active
condition|)
name|selector_death
argument_list|(
name|csel
operator|->
name|info
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|csel
argument_list|)
expr_stmt|;
name|csel
operator|=
name|next
expr_stmt|;
block|}
name|g_free
argument_list|(
name|cnp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_notebook_set_color (ColorNotebookP cnp,int r,int g,int b,int set_current)
name|color_notebook_set_color
parameter_list|(
name|ColorNotebookP
name|cnp
parameter_list|,
name|int
name|r
parameter_list|,
name|int
name|g
parameter_list|,
name|int
name|b
parameter_list|,
name|int
name|set_current
parameter_list|)
block|{
name|ColorSelectorInstance
modifier|*
name|csel
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|cnp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cnp
operator|->
name|orig_values
index|[
name|RED
index|]
operator|=
name|r
expr_stmt|;
name|cnp
operator|->
name|orig_values
index|[
name|GREEN
index|]
operator|=
name|g
expr_stmt|;
name|cnp
operator|->
name|orig_values
index|[
name|BLUE
index|]
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|set_current
condition|)
block|{
name|cnp
operator|->
name|values
index|[
name|RED
index|]
operator|=
name|r
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|GREEN
index|]
operator|=
name|g
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|BLUE
index|]
operator|=
name|b
expr_stmt|;
block|}
name|csel
operator|=
name|cnp
operator|->
name|cur_page
expr_stmt|;
name|csel
operator|->
name|info
operator|->
name|m
operator|.
name|setcolor
argument_list|(
name|csel
operator|->
name|selector_data
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|set_current
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Called by a colour selector on user selection of a colour */
end_comment

begin_function
specifier|static
name|void
DECL|function|color_notebook_update_callback (void * data,int r,int g,int b)
name|color_notebook_update_callback
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|int
name|r
parameter_list|,
name|int
name|g
parameter_list|,
name|int
name|b
parameter_list|)
block|{
name|ColorSelectorInstance
modifier|*
name|csel
decl_stmt|;
name|ColorNotebookP
name|cnp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|csel
operator|=
operator|(
name|ColorSelectorInstance
operator|*
operator|)
name|data
expr_stmt|;
name|cnp
operator|=
name|csel
operator|->
name|color_notebook
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|RED
index|]
operator|=
name|r
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|GREEN
index|]
operator|=
name|g
expr_stmt|;
name|cnp
operator|->
name|values
index|[
name|BLUE
index|]
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|cnp
operator|->
name|wants_updates
operator|&&
name|cnp
operator|->
name|callback
condition|)
block|{
call|(
modifier|*
name|cnp
operator|->
name|callback
call|)
argument_list|(
name|cnp
operator|->
name|values
index|[
name|RED
index|]
argument_list|,
name|cnp
operator|->
name|values
index|[
name|GREEN
index|]
argument_list|,
name|cnp
operator|->
name|values
index|[
name|BLUE
index|]
argument_list|,
name|COLOR_NOTEBOOK_UPDATE
argument_list|,
name|cnp
operator|->
name|client_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_notebook_ok_callback (GtkWidget * w,gpointer client_data)
name|color_notebook_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|ColorNotebookP
name|cnp
decl_stmt|;
name|cnp
operator|=
operator|(
name|ColorNotebookP
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|cnp
operator|->
name|callback
condition|)
call|(
modifier|*
name|cnp
operator|->
name|callback
call|)
argument_list|(
name|cnp
operator|->
name|values
index|[
name|RED
index|]
argument_list|,
name|cnp
operator|->
name|values
index|[
name|GREEN
index|]
argument_list|,
name|cnp
operator|->
name|values
index|[
name|BLUE
index|]
argument_list|,
name|COLOR_NOTEBOOK_OK
argument_list|,
name|cnp
operator|->
name|client_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|color_notebook_delete_callback (GtkWidget * w,GdkEvent * e,gpointer client_data)
name|color_notebook_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GdkEvent
modifier|*
name|e
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|color_notebook_cancel_callback
argument_list|(
name|w
argument_list|,
name|client_data
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
DECL|function|color_notebook_cancel_callback (GtkWidget * w,gpointer client_data)
name|color_notebook_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|ColorNotebookP
name|cnp
decl_stmt|;
name|cnp
operator|=
operator|(
name|ColorNotebookP
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|cnp
operator|->
name|callback
condition|)
call|(
modifier|*
name|cnp
operator|->
name|callback
call|)
argument_list|(
name|cnp
operator|->
name|orig_values
index|[
name|RED
index|]
argument_list|,
name|cnp
operator|->
name|orig_values
index|[
name|GREEN
index|]
argument_list|,
name|cnp
operator|->
name|orig_values
index|[
name|BLUE
index|]
argument_list|,
name|COLOR_NOTEBOOK_CANCEL
argument_list|,
name|cnp
operator|->
name|client_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_notebook_page_switch (GtkWidget * w,GtkNotebookPage * page,guint page_num)
name|color_notebook_page_switch
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GtkNotebookPage
modifier|*
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|)
block|{
name|ColorNotebookP
name|cnp
decl_stmt|;
name|ColorSelectorInstance
modifier|*
name|csel
decl_stmt|;
name|cnp
operator|=
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|w
argument_list|)
argument_list|)
expr_stmt|;
name|csel
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|page
operator|->
name|child
argument_list|)
argument_list|,
literal|"gimp_color_notebook"
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cnp
operator|!=
name|NULL
operator|&&
name|csel
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cnp
operator|->
name|cur_page
operator|=
name|csel
expr_stmt|;
name|csel
operator|->
name|info
operator|->
name|m
operator|.
name|setcolor
argument_list|(
name|csel
operator|->
name|selector_data
argument_list|,
name|cnp
operator|->
name|values
index|[
name|RED
index|]
argument_list|,
name|cnp
operator|->
name|values
index|[
name|GREEN
index|]
argument_list|,
name|cnp
operator|->
name|values
index|[
name|BLUE
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**************************************************************/
end_comment

begin_comment
comment|/* Registration functions */
end_comment

begin_function
name|GimpColorSelectorID
DECL|function|gimp_color_selector_register (const char * name,GimpColorSelectorMethods * methods)
name|gimp_color_selector_register
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
name|GimpColorSelectorMethods
modifier|*
name|methods
parameter_list|)
block|{
name|ColorSelectorInfo
modifier|*
name|info
decl_stmt|;
comment|/* check the name is unique */
name|info
operator|=
name|selector_info
expr_stmt|;
while|while
condition|(
name|info
condition|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|info
operator|->
name|name
argument_list|,
name|name
argument_list|)
condition|)
return|return
name|NULL
return|;
name|info
operator|=
name|info
operator|->
name|next
expr_stmt|;
block|}
name|info
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ColorSelectorInfo
argument_list|)
argument_list|)
expr_stmt|;
name|info
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|info
operator|->
name|m
operator|=
operator|*
name|methods
expr_stmt|;
name|info
operator|->
name|refs
operator|=
literal|0
expr_stmt|;
name|info
operator|->
name|active
operator|=
name|TRUE
expr_stmt|;
name|info
operator|->
name|next
operator|=
name|selector_info
expr_stmt|;
name|selector_info
operator|=
name|info
expr_stmt|;
return|return
name|info
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_color_selector_unregister (GimpColorSelectorID id,void (* callback)(void * data),void * data)
name|gimp_color_selector_unregister
parameter_list|(
name|GimpColorSelectorID
name|id
parameter_list|,
name|void
function_decl|(
modifier|*
name|callback
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|ColorSelectorInfo
modifier|*
name|info
decl_stmt|;
name|info
operator|=
name|selector_info
expr_stmt|;
while|while
condition|(
name|info
condition|)
block|{
if|if
condition|(
name|info
operator|==
name|id
condition|)
block|{
name|info
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
name|info
operator|->
name|death_callback
operator|=
name|callback
expr_stmt|;
name|info
operator|->
name|death_data
operator|=
name|data
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|refs
operator|==
literal|0
condition|)
name|selector_death
argument_list|(
name|info
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|info
operator|=
name|info
operator|->
name|next
expr_stmt|;
block|}
name|g_warning
argument_list|(
literal|"unknown color selector id %p"
argument_list|,
name|id
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
DECL|function|selector_death (ColorSelectorInfo * info)
name|selector_death
parameter_list|(
name|ColorSelectorInfo
modifier|*
name|info
parameter_list|)
block|{
name|ColorSelectorInfo
modifier|*
name|here
decl_stmt|,
modifier|*
name|prev
decl_stmt|;
name|here
operator|=
name|selector_info
expr_stmt|;
name|prev
operator|=
name|NULL
expr_stmt|;
while|while
condition|(
name|here
condition|)
block|{
if|if
condition|(
name|here
operator|==
name|info
condition|)
block|{
if|if
condition|(
name|prev
condition|)
name|prev
operator|->
name|next
operator|=
name|info
operator|->
name|next
expr_stmt|;
else|else
name|selector_info
operator|=
name|info
operator|->
name|next
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|death_callback
condition|)
call|(
modifier|*
name|info
operator|->
name|death_callback
call|)
argument_list|(
name|info
operator|->
name|death_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|info
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
return|return;
block|}
name|prev
operator|=
name|here
expr_stmt|;
name|here
operator|=
name|here
operator|->
name|next
expr_stmt|;
block|}
name|g_warning
argument_list|(
literal|"color selector %p not found, can't happen!"
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* End of color_notebook.c */
end_comment

end_unit


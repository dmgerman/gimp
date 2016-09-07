begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbrowser.c  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsmarshal.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpbrowser  * @title: GimpBrowser  * @short_description: A base class for a documentation browser.  *  * A base class for a documentation browser.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2c006e820103
block|{
DECL|enumerator|SEARCH
name|SEARCH
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_browser_dispose
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
name|gimp_browser_combo_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|combo
parameter_list|,
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_browser_entry_changed
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_browser_entry_icon_press
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GtkEntryIconPosition
name|icon_pos
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_browser_search_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrowser
argument_list|,
argument|gimp_browser
argument_list|,
argument|GTK_TYPE_HPANED
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_browser_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|browser_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_browser_class_init (GimpBrowserClass * klass)
name|gimp_browser_class_init
parameter_list|(
name|GimpBrowserClass
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
name|browser_signals
index|[
name|SEARCH
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"search"
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
name|GimpBrowserClass
argument_list|,
name|search
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__STRING_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_browser_dispose
expr_stmt|;
name|klass
operator|->
name|search
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_browser_init (GimpBrowser * browser)
name|gimp_browser_init
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkWidget
modifier|*
name|viewport
decl_stmt|;
name|browser
operator|->
name|search_type
operator|=
operator|-
literal|1
expr_stmt|;
name|browser
operator|->
name|left_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_paned_pack1
argument_list|(
name|GTK_PANED
argument_list|(
name|browser
argument_list|)
argument_list|,
name|browser
operator|->
name|left_vbox
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|browser
operator|->
name|left_vbox
argument_list|)
expr_stmt|;
comment|/* search entry */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|browser
operator|->
name|left_vbox
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
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Search:"
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
name|label
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
name|label
argument_list|)
expr_stmt|;
name|browser
operator|->
name|search_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|browser
operator|->
name|search_entry
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
name|browser
operator|->
name|search_entry
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|browser
operator|->
name|search_entry
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_browser_entry_changed
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_from_icon_name
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
literal|"edit-clear"
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_activatable
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_sensitive
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|,
literal|"icon-press"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_browser_entry_icon_press
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
comment|/* count label */
name|browser
operator|->
name|count_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"No matches"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|browser
operator|->
name|count_label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
operator|->
name|count_label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|browser
operator|->
name|left_vbox
argument_list|)
argument_list|,
name|browser
operator|->
name|count_label
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
name|browser
operator|->
name|count_label
argument_list|)
expr_stmt|;
comment|/* scrolled window */
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_ALWAYS
argument_list|)
expr_stmt|;
name|gtk_paned_pack2
argument_list|(
name|GTK_PANED
argument_list|(
name|browser
argument_list|)
argument_list|,
name|scrolled_window
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_window
argument_list|)
expr_stmt|;
name|viewport
operator|=
name|gtk_viewport_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|viewport
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|viewport
argument_list|)
expr_stmt|;
name|browser
operator|->
name|right_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|browser
operator|->
name|right_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|viewport
argument_list|)
argument_list|,
name|browser
operator|->
name|right_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|browser
operator|->
name|right_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_browser_dispose (GObject * object)
name|gimp_browser_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrowser
modifier|*
name|browser
init|=
name|GIMP_BROWSER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|browser
operator|->
name|search_timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|browser
operator|->
name|search_timeout_id
argument_list|)
expr_stmt|;
name|browser
operator|->
name|search_timeout_id
operator|=
literal|0
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

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_browser_new:  *  * Create a new #GimpBrowser widget.  *  * Return Value: a newly created #GimpBrowser.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_browser_new (void)
name|gimp_browser_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_BROWSER
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_browser_add_search_types:  * @browser:          a #GimpBrowser widget  * @first_type_label: the label of the first search type  * @first_type_id:    an integer that identifies the first search type  * @...:              a %NULL-terminated list of more labels and ids.  *  * Populates the #GtkComboBox with search types.  *  * Since: 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_browser_add_search_types (GimpBrowser * browser,const gchar * first_type_label,gint first_type_id,...)
name|gimp_browser_add_search_types
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|first_type_label
parameter_list|,
name|gint
name|first_type_id
parameter_list|,
modifier|...
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BROWSER
argument_list|(
name|browser
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|first_type_label
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|browser
operator|->
name|search_type_combo
condition|)
block|{
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_type_id
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new_valist
argument_list|(
name|first_type_label
argument_list|,
name|first_type_id
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|gtk_combo_box_set_focus_on_click
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|browser
operator|->
name|search_type_combo
operator|=
name|combo
expr_stmt|;
name|browser
operator|->
name|search_type
operator|=
name|first_type_id
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_widget_get_parent
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_connect
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|browser
operator|->
name|search_type
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|browser
operator|->
name|search_type
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_browser_combo_changed
argument_list|)
argument_list|,
name|browser
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_int_combo_box_append
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|browser
operator|->
name|search_type_combo
argument_list|)
argument_list|,
name|first_type_label
argument_list|,
name|first_type_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_browser_set_widget:  * @browser: a #GimpBrowser widget  * @widget:  a #GtkWidget  *  * Sets the widget to appear on the right side of the @browser.  *  * Since: 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_browser_set_widget (GimpBrowser * browser,GtkWidget * widget)
name|gimp_browser_set_widget
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BROWSER
argument_list|(
name|browser
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|widget
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
operator|==
name|browser
operator|->
name|right_widget
condition|)
return|return;
if|if
condition|(
name|browser
operator|->
name|right_widget
condition|)
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|browser
operator|->
name|right_vbox
argument_list|)
argument_list|,
name|browser
operator|->
name|right_widget
argument_list|)
expr_stmt|;
name|browser
operator|->
name|right_widget
operator|=
name|widget
expr_stmt|;
if|if
condition|(
name|widget
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|browser
operator|->
name|right_vbox
argument_list|)
argument_list|,
name|widget
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
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_browser_show_message:  * @browser: a #GimpBrowser widget  * @message: text message  *  * Displays @message in the right side of the @browser. Unless the right  * side already contains a #GtkLabel, the widget previously added with  * gimp_browser_set_widget() is removed and replaced by a #GtkLabel.  *  * Since: 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_browser_show_message (GimpBrowser * browser,const gchar * message)
name|gimp_browser_show_message
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BROWSER
argument_list|(
name|browser
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|browser
operator|->
name|right_widget
argument_list|)
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|browser
operator|->
name|right_widget
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|gtk_label_new
argument_list|(
name|message
argument_list|)
decl_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_browser_set_widget
argument_list|(
name|browser
argument_list|,
name|label
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
name|gtk_main_iteration
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_browser_queue_search (GimpBrowser * browser)
name|gimp_browser_queue_search
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
block|{
if|if
condition|(
name|browser
operator|->
name|search_timeout_id
condition|)
name|g_source_remove
argument_list|(
name|browser
operator|->
name|search_timeout_id
argument_list|)
expr_stmt|;
name|browser
operator|->
name|search_timeout_id
operator|=
name|g_timeout_add
argument_list|(
literal|100
argument_list|,
name|gimp_browser_search_timeout
argument_list|,
name|browser
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_browser_combo_changed (GtkComboBox * combo,GimpBrowser * browser)
name|gimp_browser_combo_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|combo
parameter_list|,
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|gimp_browser_queue_search
argument_list|(
name|browser
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_browser_entry_changed (GtkEntry * entry,GimpBrowser * browser)
name|gimp_browser_entry_changed
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|gimp_browser_queue_search
argument_list|(
name|browser
argument_list|)
expr_stmt|;
name|gtk_entry_set_icon_sensitive
argument_list|(
name|entry
argument_list|,
name|GTK_ENTRY_ICON_SECONDARY
argument_list|,
name|gtk_entry_get_text_length
argument_list|(
name|entry
argument_list|)
operator|>
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_browser_entry_icon_press (GtkEntry * entry,GtkEntryIconPosition icon_pos,GdkEvent * event,GimpBrowser * browser)
name|gimp_browser_entry_icon_press
parameter_list|(
name|GtkEntry
modifier|*
name|entry
parameter_list|,
name|GtkEntryIconPosition
name|icon_pos
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpBrowser
modifier|*
name|browser
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
init|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
decl_stmt|;
if|if
condition|(
name|icon_pos
operator|==
name|GTK_ENTRY_ICON_SECONDARY
operator|&&
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gtk_entry_set_text
argument_list|(
name|entry
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_browser_search_timeout (gpointer data)
name|gimp_browser_search_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBrowser
modifier|*
name|browser
init|=
name|GIMP_BROWSER
argument_list|(
name|data
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|search_string
decl_stmt|;
name|GDK_THREADS_ENTER
argument_list|()
expr_stmt|;
name|search_string
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|browser
operator|->
name|search_entry
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|search_string
condition|)
name|search_string
operator|=
literal|""
expr_stmt|;
name|g_signal_emit
argument_list|(
name|browser
argument_list|,
name|browser_signals
index|[
name|SEARCH
index|]
argument_list|,
literal|0
argument_list|,
name|search_string
argument_list|,
name|browser
operator|->
name|search_type
argument_list|)
expr_stmt|;
name|browser
operator|->
name|search_timeout_id
operator|=
literal|0
expr_stmt|;
name|GDK_THREADS_LEAVE
argument_list|()
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit


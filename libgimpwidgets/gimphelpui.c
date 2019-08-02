begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelpui.c  * Copyright (C) 2000-2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-private.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimphelpui  * @title: GimpHelpUI  * @short_description: Functions for setting tooltip and help identifier  *                     used by the GIMP help system.  *  * Functions for setting tooltip and help identifier used by the GIMP  * help system.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ffad100103
block|{
DECL|enumerator|GIMP_WIDGET_HELP_TOOLTIP
name|GIMP_WIDGET_HELP_TOOLTIP
init|=
name|GTK_WIDGET_HELP_TOOLTIP
block|,
DECL|enumerator|GIMP_WIDGET_HELP_WHATS_THIS
name|GIMP_WIDGET_HELP_WHATS_THIS
init|=
name|GTK_WIDGET_HELP_WHATS_THIS
block|,
DECL|enumerator|GIMP_WIDGET_HELP_TYPE_HELP
name|GIMP_WIDGET_HELP_TYPE_HELP
init|=
literal|0xff
DECL|typedef|GimpWidgetHelpType
block|}
name|GimpWidgetHelpType
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_help_get_help_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|help_widget
parameter_list|,
name|gpointer
modifier|*
name|ret_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_help_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpWidgetHelpType
name|help_type
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_help_menu_item_set_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_help_menu_item_query_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|keyboard_mode
parameter_list|,
name|GtkTooltip
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_context_help_idle_start
parameter_list|(
name|gpointer
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_context_help_button_press
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
name|gboolean
name|gimp_context_help_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_context_help_idle_show_help
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_standard_help_func:  * @help_id:   A unique help identifier.  * @help_data: The @help_data passed to gimp_help_connect().  *  * This is the standard GIMP help function which does nothing but calling  * gimp_help(). It is the right function to use in almost all cases.  **/
end_comment

begin_function
name|void
DECL|function|gimp_standard_help_func (const gchar * help_id,gpointer help_data)
name|gimp_standard_help_func
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
if|if
condition|(
operator|!
name|_gimp_standard_help_func
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: you must call gimp_widgets_init() before using "
literal|"the help system"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
call|(
modifier|*
name|_gimp_standard_help_func
call|)
argument_list|(
name|help_id
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_help_connect:  * @widget: The widget you want to connect the help accelerator for. Will  *          be a #GtkWindow in most cases.  * @help_func: The function which will be called if the user presses "F1".  * @help_id:   The @help_id which will be passed to @help_func.  * @help_data: The @help_data pointer which will be passed to @help_func.  *  * Note that this function is automatically called by all libgimp dialog  * constructors. You only have to call it for windows/dialogs you created  * "manually".  **/
end_comment

begin_function
name|void
DECL|function|gimp_help_connect (GtkWidget * widget,GimpHelpFunc help_func,const gchar * help_id,gpointer help_data)
name|gimp_help_connect
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|help_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*  set up the help signals    */
if|if
condition|(
operator|!
name|initialized
condition|)
block|{
name|GtkBindingSet
modifier|*
name|binding_set
decl_stmt|;
name|binding_set
operator|=
name|gtk_binding_set_by_class
argument_list|(
name|g_type_class_peek
argument_list|(
name|GTK_TYPE_WIDGET
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_F1
argument_list|,
literal|0
argument_list|,
literal|"show-help"
argument_list|,
literal|1
argument_list|,
name|GTK_TYPE_WIDGET_HELP_TYPE
argument_list|,
name|GIMP_WIDGET_HELP_TYPE_HELP
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_KP_F1
argument_list|,
literal|0
argument_list|,
literal|"show-help"
argument_list|,
literal|1
argument_list|,
name|GTK_TYPE_WIDGET_HELP_TYPE
argument_list|,
name|GIMP_WIDGET_HELP_TYPE_HELP
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
name|gimp_help_set_help_data
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-help-data"
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"show-help"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_help_callback
argument_list|)
argument_list|,
name|help_func
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|widget
argument_list|,
name|GDK_BUTTON_PRESS_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_help_set_help_data:  * @widget:  The #GtkWidget you want to set a @tooltip and/or @help_id for.  * @tooltip: The text for this widget's tooltip (or %NULL).  * @help_id: The @help_id for the #GtkTipsQuery tooltips inspector.  *  * The reason why we don't use gtk_widget_set_tooltip_text() is that  * elements in the GIMP user interface should, if possible, also have  * a @help_id set for context-sensitive help.  *  * This function can be called with %NULL for @tooltip. Use this feature  * if you want to set a help link for a widget which shouldn't have  * a visible tooltip.  **/
end_comment

begin_function
name|void
DECL|function|gimp_help_set_help_data (GtkWidget * widget,const gchar * tooltip,const gchar * help_id)
name|gimp_help_set_help_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_tooltip_text
argument_list|(
name|widget
argument_list|,
name|tooltip
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_MENU_ITEM
argument_list|(
name|widget
argument_list|)
condition|)
name|gimp_help_menu_item_set_tooltip
argument_list|(
name|widget
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|g_object_set_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_HELP_ID
argument_list|,
operator|(
name|gpointer
operator|)
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_help_set_help_data_with_markup:  * @widget:  The #GtkWidget you want to set a @tooltip and/or @help_id for.  * @tooltip: The markup for this widget's tooltip (or %NULL).  * @help_id: The @help_id for the #GtkTipsQuery tooltips inspector.  *  * Just like gimp_help_set_help_data(), but supports to pass text  * which is marked up with<link linkend="PangoMarkupFormat">Pango  * text markup language</link>.  *  * Since: 2.6  **/
end_comment

begin_function
name|void
DECL|function|gimp_help_set_help_data_with_markup (GtkWidget * widget,const gchar * tooltip,const gchar * help_id)
name|gimp_help_set_help_data_with_markup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_tooltip_markup
argument_list|(
name|widget
argument_list|,
name|tooltip
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_MENU_ITEM
argument_list|(
name|widget
argument_list|)
condition|)
name|gimp_help_menu_item_set_tooltip
argument_list|(
name|widget
argument_list|,
name|tooltip
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|g_object_set_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_HELP_ID
argument_list|,
operator|(
name|gpointer
operator|)
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_help:  * @widget: Any #GtkWidget on the screen.  *  * This function invokes the context help inspector.  *  * The mouse cursor will turn turn into a question mark and the user can  * click on any widget of the application which started the inspector.  *  * If the widget the user clicked on has a @help_id string attached  * (see gimp_help_set_help_data()), the corresponding help page will  * be displayed. Otherwise the help system will ascend the widget hierarchy  * until it finds an attached @help_id string (which should be the  * case at least for every window/dialog).  **/
end_comment

begin_function
name|void
DECL|function|gimp_context_help (GtkWidget * widget)
name|gimp_context_help
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_callback
argument_list|(
name|widget
argument_list|,
name|GIMP_WIDGET_HELP_WHATS_THIS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_help_id_quark:  *  * This function returns the #GQuark which should be used as key when  * attaching help IDs to widgets and objects.  *  * Returns: The #GQuark.  *  * Since: 2.2  **/
end_comment

begin_function
name|GQuark
DECL|function|gimp_help_id_quark (void)
name|gimp_help_id_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|quark
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|quark
condition|)
name|quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-help-id"
argument_list|)
expr_stmt|;
return|return
name|quark
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_help_get_help_data (GtkWidget * widget,GtkWidget ** help_widget,gpointer * ret_data)
name|gimp_help_get_help_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|help_widget
parameter_list|,
name|gpointer
modifier|*
name|ret_data
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|help_id
init|=
name|NULL
decl_stmt|;
name|gpointer
name|help_data
init|=
name|NULL
decl_stmt|;
for|for
control|(
init|;
name|widget
condition|;
name|widget
operator|=
name|gtk_widget_get_parent
argument_list|(
name|widget
argument_list|)
control|)
block|{
name|help_id
operator|=
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_HELP_ID
argument_list|)
expr_stmt|;
name|help_data
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-help-data"
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_id
condition|)
block|{
if|if
condition|(
name|help_widget
condition|)
operator|*
name|help_widget
operator|=
name|widget
expr_stmt|;
if|if
condition|(
name|ret_data
condition|)
operator|*
name|ret_data
operator|=
name|help_data
expr_stmt|;
return|return
name|help_id
return|;
block|}
block|}
if|if
condition|(
name|help_widget
condition|)
operator|*
name|help_widget
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_data
condition|)
operator|*
name|ret_data
operator|=
name|NULL
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_help_callback (GtkWidget * widget,GimpWidgetHelpType help_type,GimpHelpFunc help_func)
name|gimp_help_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpWidgetHelpType
name|help_type
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|)
block|{
switch|switch
condition|(
name|help_type
condition|)
block|{
case|case
name|GIMP_WIDGET_HELP_TYPE_HELP
case|:
if|if
condition|(
name|help_func
condition|)
block|{
name|help_func
argument_list|(
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_HELP_ID
argument_list|)
argument_list|,
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-help-data"
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
case|case
name|GIMP_WIDGET_HELP_WHATS_THIS
case|:
name|g_idle_add
argument_list|(
name|gimp_context_help_idle_start
argument_list|,
name|widget
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
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
DECL|function|gimp_help_menu_item_set_tooltip (GtkWidget * widget,const gchar * tooltip,const gchar * help_id)
name|gimp_help_menu_item_set_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GTK_IS_MENU_ITEM
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tooltip
operator|&&
name|help_id
condition|)
block|{
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"has-tooltip"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"query-tooltip"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_help_menu_item_query_tooltip
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|tooltip
condition|)
block|{
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"has-tooltip"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|widget
argument_list|,
name|gimp_help_menu_item_query_tooltip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_help_menu_item_query_tooltip (GtkWidget * widget,gint x,gint y,gboolean keyboard_mode,GtkTooltip * tooltip)
name|gimp_help_menu_item_query_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|keyboard_mode
parameter_list|,
name|GtkTooltip
modifier|*
name|tooltip
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gboolean
name|use_markup
init|=
name|TRUE
decl_stmt|;
name|text
operator|=
name|gtk_widget_get_tooltip_markup
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|text
condition|)
block|{
name|text
operator|=
name|gtk_widget_get_tooltip_text
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|use_markup
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|text
condition|)
return|return
name|FALSE
return|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_label_set_use_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|use_markup
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Press F1 for more help"
argument_list|)
argument_list|)
expr_stmt|;
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
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_SMALL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_tooltip_set_custom
argument_list|(
name|tooltip
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  Do all the actual context help calls in idle functions and check for  *  some widget holding a grab before starting the query because strange  *  things happen if (1) the help browser pops up while the query has  *  grabbed the pointer or (2) the query grabs the pointer while some  *  other part of GIMP has grabbed it (e.g. a tool, eek)  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_context_help_idle_start (gpointer widget)
name|gimp_context_help_idle_start
parameter_list|(
name|gpointer
name|widget
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gtk_grab_get_current
argument_list|()
condition|)
block|{
name|GtkWidget
modifier|*
name|invisible
decl_stmt|;
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|GdkGrabStatus
name|status
decl_stmt|;
name|invisible
operator|=
name|gtk_invisible_new_for_screen
argument_list|(
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|invisible
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|invisible
argument_list|)
argument_list|,
name|GDK_QUESTION_ARROW
argument_list|)
expr_stmt|;
name|status
operator|=
name|gdk_pointer_grab
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|invisible
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|,
name|NULL
argument_list|,
name|cursor
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|!=
name|GDK_GRAB_SUCCESS
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|invisible
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gdk_keyboard_grab
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|invisible
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
operator|!=
name|GDK_GRAB_SUCCESS
condition|)
block|{
name|gdk_display_pointer_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|invisible
argument_list|)
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|invisible
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gtk_grab_add
argument_list|(
name|invisible
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|invisible
argument_list|,
literal|"button-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_context_help_button_press
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|invisible
argument_list|,
literal|"key-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_context_help_key_press
argument_list|)
argument_list|,
name|NULL
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
name|gboolean
DECL|function|gimp_context_help_button_press (GtkWidget * widget,GdkEventButton * bevent,gpointer data)
name|gimp_context_help_button_press
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
block|{
name|GtkWidget
modifier|*
name|event_widget
init|=
name|gtk_get_event_widget
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|bevent
argument_list|)
decl_stmt|;
if|if
condition|(
name|event_widget
operator|&&
name|bevent
operator|->
name|button
operator|==
literal|1
operator|&&
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gdk_display_keyboard_ungrab
argument_list|(
name|display
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gdk_display_pointer_ungrab
argument_list|(
name|display
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|event_widget
operator|!=
name|widget
condition|)
name|g_idle_add
argument_list|(
name|gimp_context_help_idle_show_help
argument_list|,
name|event_widget
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_context_help_key_press (GtkWidget * widget,GdkEventKey * kevent,gpointer data)
name|gimp_context_help_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_Escape
condition|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gdk_display_keyboard_ungrab
argument_list|(
name|display
argument_list|,
name|kevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gdk_display_pointer_ungrab
argument_list|(
name|display
argument_list|,
name|kevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_context_help_idle_show_help (gpointer data)
name|gimp_context_help_idle_show_help
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|help_widget
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_id
init|=
name|NULL
decl_stmt|;
name|gpointer
name|help_data
init|=
name|NULL
decl_stmt|;
name|help_id
operator|=
name|gimp_help_get_help_data
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|,
operator|&
name|help_widget
argument_list|,
operator|&
name|help_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_id
condition|)
name|gimp_standard_help_func
argument_list|(
name|help_id
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit


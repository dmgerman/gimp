begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelpui.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *               * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtktipsquery.h>
end_include

begin_define
DECL|macro|GTK_DISABLE_DEPRECATED
define|#
directive|define
name|GTK_DISABLE_DEPRECATED
end_define

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28fb60df0103
block|{
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
name|GtkWidgetHelpType
name|help_type
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_help_tips_query_idle_show_help
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_help_tips_query_widget_selected
parameter_list|(
name|GtkWidget
modifier|*
name|tips_query
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_private
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|func_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_help_tips_query_idle_start
parameter_list|(
name|gpointer
name|tips_query
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|tool_tips
specifier|static
name|GtkTooltips
modifier|*
name|tool_tips
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tips_query
specifier|static
name|GtkWidget
modifier|*
name|tips_query
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * _gimp_help_init:  *  * This function initializes GIMP's help system.  *  * Currently it only creates a #GtkTooltips object with gtk_tooltips_new()  * which will be used by gimp_help_set_help_data().  *  * Nota that this function is called automatically by gimp_widgets_init().  **/
end_comment

begin_function
name|void
DECL|function|_gimp_help_init (void)
name|_gimp_help_init
parameter_list|(
name|void
parameter_list|)
block|{
name|tool_tips
operator|=
name|gtk_tooltips_new
argument_list|()
expr_stmt|;
comment|/* take ownership of the tooltips */
name|g_object_ref
argument_list|(
name|tool_tips
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool_tips
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_help_enable_tooltips:  *  * This function calls gtk_tooltips_enable().  **/
end_comment

begin_function
name|void
DECL|function|gimp_help_enable_tooltips (void)
name|gimp_help_enable_tooltips
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_tooltips_enable
argument_list|(
name|tool_tips
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_help_disable_tooltips:  *  * This function calls gtk_tooltips_disable().  **/
end_comment

begin_function
name|void
DECL|function|gimp_help_disable_tooltips (void)
name|gimp_help_disable_tooltips
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_tooltips_disable
argument_list|(
name|tool_tips
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_help_connect:  * @widget: The widget you want to connect the help accelerator for. Will  *          be a #GtkWindow in most cases.  * @help_func: The function which will be called if the user presses "F1".  * @help_data: The data pointer which will be passed to @help_func.  *  * Note that this function is automatically called by all libgimp dialog  * constructors. You only have to call it for windows/dialogs you created  * "manually".  **/
end_comment

begin_function
name|void
DECL|function|gimp_help_connect (GtkWidget * widget,GimpHelpFunc help_func,const gchar * help_data)
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
name|help_data
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
name|g_return_if_fail
argument_list|(
name|help_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*  set up the help signals and tips query widget    */
if|if
condition|(
operator|!
name|tips_query
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
name|GDK_F1
argument_list|,
literal|0
argument_list|,
literal|"show_help"
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
name|GDK_KP_F1
argument_list|,
literal|0
argument_list|,
literal|"show_help"
argument_list|,
literal|1
argument_list|,
name|GTK_TYPE_WIDGET_HELP_TYPE
argument_list|,
name|GIMP_WIDGET_HELP_TYPE_HELP
argument_list|)
expr_stmt|;
name|tips_query
operator|=
name|gtk_tips_query_new
argument_list|()
expr_stmt|;
name|g_object_set
argument_list|(
name|tips_query
argument_list|,
literal|"emit_always"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|tips_query
argument_list|,
literal|"widget_selected"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_help_tips_query_widget_selected
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  FIXME: EEEEEEEEEEEEEEEEEEEEK, this is very ugly and forbidden...        *  does anyone know a way to do this tips query stuff without        *  having to attach to some parent widget???        */
name|tips_query
operator|->
name|parent
operator|=
name|widget
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|tips_query
argument_list|)
expr_stmt|;
block|}
name|gimp_help_set_help_data
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"show_help"
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
comment|/**  * gimp_help_set_help_data:  * @widget: The #GtkWidget you want to set a @tooltip and/or @help_data for.  * @tooltip: The text for this widget's tooltip (or %NULL).  * @help_data: The @help_data for the #GtkTipsQuery tooltips inspector.  *  * The reason why we don't use gtk_tooltips_set_tip() is that it's  * impossible to set a @private_tip (aka @help_data) without a visible  * @tooltip.  *  * This function can be called with %NULL for @tooltip. Use this feature  * if you want to set a HTML help link for a widget which shouldn't have  * a visible tooltip.  *  * You can e.g. set a @help_data string to a complete HTML page for a  * container widget (e.g. a #GtkBox). For the widgets inside the box  * you can set HTML anchors which point inside the container widget's  * help page by setting @help_data strings starting with "#".  *  * If the tooltips inspector (Shift + "F1") is invoked and the user  * clicks on one of the widgets which only contain a "#" link, the  * help system will automatically ascend the widget hierarchy until it  * finds another widget with @help_data attached and concatenates both  * to a complete help path.  **/
end_comment

begin_function
name|void
DECL|function|gimp_help_set_help_data (GtkWidget * widget,const gchar * tooltip,const gchar * help_data)
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
name|help_data
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
if|if
condition|(
name|tooltip
condition|)
block|{
name|gtk_tooltips_set_tip
argument_list|(
name|tool_tips
argument_list|,
name|widget
argument_list|,
name|tooltip
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|help_data
condition|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_help_data"
argument_list|,
operator|(
name|gpointer
operator|)
name|help_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_context_help:  *  * This function invokes the #GtkTipsQuery tooltips inspector.  *  * The mouse cursor will turn turn into a question mark and the user can  * click on any widget of the application which started the inspector.  *  * If the widget the user clicked on has a @help_data string attached  * (see gimp_help_set_help_data()), the corresponding HTML page will  * be displayed. Otherwise the help system will ascend the widget hierarchy  * until it finds an attached @help_data string (which should be the  * case at least for every window/dialog).  **/
end_comment

begin_function
name|void
DECL|function|gimp_context_help (void)
name|gimp_context_help
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|tips_query
condition|)
name|gimp_help_callback
argument_list|(
name|NULL
argument_list|,
name|GTK_WIDGET_HELP_WHATS_THIS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
DECL|function|gimp_help_get_help_data (GtkWidget * widget,GtkWidget ** help_widget)
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
parameter_list|)
block|{
name|GtkTooltipsData
modifier|*
name|tooltips_data
decl_stmt|;
name|gchar
modifier|*
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
name|widget
operator|->
name|parent
control|)
block|{
if|if
condition|(
operator|(
name|tooltips_data
operator|=
name|gtk_tooltips_data_get
argument_list|(
name|widget
argument_list|)
operator|)
operator|&&
name|tooltips_data
operator|->
name|tip_private
condition|)
block|{
name|help_data
operator|=
name|tooltips_data
operator|->
name|tip_private
expr_stmt|;
block|}
else|else
block|{
name|help_data
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_help_data"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|help_data
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
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|help_data
return|;
block|}
block|}
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
name|gchar
modifier|*
name|help_data
decl_stmt|;
name|help_data
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_help_data"
argument_list|)
expr_stmt|;
call|(
modifier|*
name|help_func
call|)
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
case|case
name|GTK_WIDGET_HELP_WHATS_THIS
case|:
if|if
condition|(
operator|!
name|GTK_TIPS_QUERY
argument_list|(
name|tips_query
argument_list|)
operator|->
name|in_query
condition|)
name|g_idle_add
argument_list|(
name|gimp_help_tips_query_idle_start
argument_list|,
name|tips_query
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

begin_comment
comment|/*  Do all the actual GtkTipsQuery calls in idle functions and check for  *  some widget holding a grab before starting the query because strange  *  things happen if (1) the help browser pops up while the query has  *  grabbed the pointer or (2) the query grabs the pointer while some  *  other part of the gimp has grabbed it (e.g. a tool, eek)  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_help_tips_query_idle_show_help (gpointer data)
name|gimp_help_tips_query_idle_show_help
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
name|help_data
init|=
name|NULL
decl_stmt|;
name|help_data
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
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_data
condition|)
block|{
if|if
condition|(
name|help_data
index|[
literal|0
index|]
operator|==
literal|'#'
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|help_index
decl_stmt|;
name|help_index
operator|=
name|help_data
expr_stmt|;
name|help_data
operator|=
name|gimp_help_get_help_data
argument_list|(
name|help_widget
operator|->
name|parent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_data
condition|)
block|{
name|gchar
modifier|*
name|help_text
decl_stmt|;
name|help_text
operator|=
name|g_strconcat
argument_list|(
name|help_data
argument_list|,
name|help_index
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_standard_help_func
argument_list|(
name|help_text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_text
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_standard_help_func
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_help_tips_query_widget_selected (GtkWidget * tips_query,GtkWidget * widget,const gchar * tip_text,const gchar * tip_private,GdkEventButton * event,gpointer func_data)
name|gimp_help_tips_query_widget_selected
parameter_list|(
name|GtkWidget
modifier|*
name|tips_query
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip_private
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|func_data
parameter_list|)
block|{
if|if
condition|(
name|widget
condition|)
name|g_idle_add
argument_list|(
name|gimp_help_tips_query_idle_show_help
argument_list|,
name|widget
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_help_tips_query_idle_start (gpointer tips_query)
name|gimp_help_tips_query_idle_start
parameter_list|(
name|gpointer
name|tips_query
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gtk_grab_get_current
argument_list|()
condition|)
name|gtk_tips_query_start_query
argument_list|(
name|GTK_TIPS_QUERY
argument_list|(
name|tips_query
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit


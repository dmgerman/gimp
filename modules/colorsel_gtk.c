begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * colorsel_gtk module (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpmodregister.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpcolorselector.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/* prototypes */
end_comment

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|colorsel_gtk_new
parameter_list|(
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|gint
name|a
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|,
name|GimpColorSelectorCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gpointer
modifier|*
name|selector_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_gtk_free
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_gtk_setcolor
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|gint
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_gtk_update
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

begin_comment
comment|/* EEK */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|colorsel_gtk_widget_idle_hide
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_gtk_widget_hide
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

begin_comment
comment|/* local methods */
end_comment

begin_decl_stmt
DECL|variable|methods
specifier|static
name|GimpColorSelectorMethods
name|methods
init|=
block|{
name|colorsel_gtk_new
block|,
name|colorsel_gtk_free
block|,
name|colorsel_gtk_setcolor
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|info
specifier|static
name|GimpModuleInfo
name|info
init|=
block|{
name|NULL
block|,
name|N_
argument_list|(
literal|"GTK color selector as a pluggable color selector"
argument_list|)
block|,
literal|"Austin Donnelly<austin@gimp.org>"
block|,
literal|"v0.02"
block|,
literal|"(c) 1999, released under the GPL"
block|,
literal|"17 Jan 1999"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* globaly exported init function */
end_comment

begin_function
name|G_MODULE_EXPORT
name|GimpModuleStatus
DECL|function|module_init (GimpModuleInfo ** inforet)
name|module_init
parameter_list|(
name|GimpModuleInfo
modifier|*
modifier|*
name|inforet
parameter_list|)
block|{
name|GimpColorSelectorID
name|id
decl_stmt|;
ifndef|#
directive|ifndef
name|__EMX__
name|id
operator|=
name|gimp_color_selector_register
argument_list|(
literal|"GTK"
argument_list|,
literal|"gtk.html"
argument_list|,
operator|&
name|methods
argument_list|)
expr_stmt|;
else|#
directive|else
name|id
operator|=
name|mod_color_selector_register
argument_list|(
literal|"GTK"
argument_list|,
literal|"gtk.html"
argument_list|,
operator|&
name|methods
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|id
condition|)
block|{
name|info
operator|.
name|shutdown_data
operator|=
name|id
expr_stmt|;
operator|*
name|inforet
operator|=
operator|&
name|info
expr_stmt|;
return|return
name|GIMP_MODULE_OK
return|;
block|}
else|else
block|{
return|return
name|GIMP_MODULE_UNLOAD
return|;
block|}
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|void
DECL|function|module_unload (gpointer shutdown_data,GimpColorSelectorFinishedCB completed_cb,gpointer completed_data)
name|module_unload
parameter_list|(
name|gpointer
name|shutdown_data
parameter_list|,
name|GimpColorSelectorFinishedCB
name|completed_cb
parameter_list|,
name|gpointer
name|completed_data
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|__EMX__
name|gimp_color_selector_unregister
argument_list|(
name|shutdown_data
argument_list|,
name|completed_cb
argument_list|,
name|completed_data
argument_list|)
expr_stmt|;
else|#
directive|else
name|mod_color_selector_unregister
argument_list|(
name|shutdown_data
argument_list|,
name|completed_cb
argument_list|,
name|completed_data
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/******************************/
end_comment

begin_comment
comment|/* GTK color selector methods */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bac0f300108
block|{
DECL|member|selector
name|GtkWidget
modifier|*
name|selector
decl_stmt|;
DECL|member|callback
name|GimpColorSelectorCallback
name|callback
decl_stmt|;
DECL|member|client_data
name|void
modifier|*
name|client_data
decl_stmt|;
DECL|typedef|ColorselGtk
block|}
name|ColorselGtk
typedef|;
end_typedef

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|colorsel_gtk_new (gint r,gint g,gint b,gint a,gboolean show_alpha,GimpColorSelectorCallback callback,gpointer data,gpointer * selector_data)
name|colorsel_gtk_new
parameter_list|(
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|gint
name|a
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|,
name|GimpColorSelectorCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
comment|/* RETURNS: */
name|gpointer
modifier|*
name|selector_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|ColorselGtk
modifier|*
name|p
decl_stmt|;
name|p
operator|=
name|g_new
argument_list|(
name|ColorselGtk
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|p
operator|->
name|selector
operator|=
name|gtk_color_selection_new
argument_list|()
expr_stmt|;
name|p
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|p
operator|->
name|client_data
operator|=
name|data
expr_stmt|;
name|gtk_color_selection_set_opacity
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|p
operator|->
name|selector
argument_list|)
argument_list|,
name|show_alpha
argument_list|)
expr_stmt|;
comment|/*   gtk_widget_hide (GTK_COLOR_SELECTION (p->selector)->sample_area->parent);   */
name|colorsel_gtk_setcolor
argument_list|(
name|p
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
comment|/* EEK: to be removed */
name|gtk_signal_connect_object_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|p
operator|->
name|selector
argument_list|)
operator|->
name|sample_area
argument_list|)
argument_list|,
literal|"realize"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|colorsel_gtk_widget_hide
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|p
operator|->
name|selector
argument_list|)
operator|->
name|sample_area
operator|->
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|p
operator|->
name|selector
argument_list|)
argument_list|,
literal|"color_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|colorsel_gtk_update
argument_list|)
argument_list|,
name|p
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|p
operator|->
name|selector
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
name|p
operator|->
name|selector
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
operator|*
name|selector_data
operator|=
name|p
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_gtk_free (gpointer data)
name|colorsel_gtk_free
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|ColorselGtk
modifier|*
name|p
init|=
name|data
decl_stmt|;
comment|/* don't need to gtk_widget_destroy() the selector, since that's    * done for us.    */
name|g_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_gtk_setcolor (gpointer data,gint r,gint g,gint b,gint a)
name|colorsel_gtk_setcolor
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|gint
name|a
parameter_list|)
block|{
name|ColorselGtk
modifier|*
name|p
init|=
name|data
decl_stmt|;
name|gdouble
name|color
index|[
literal|4
index|]
decl_stmt|;
name|color
index|[
literal|0
index|]
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|r
operator|)
operator|/
literal|255.999
expr_stmt|;
name|color
index|[
literal|1
index|]
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|g
operator|)
operator|/
literal|255.999
expr_stmt|;
name|color
index|[
literal|2
index|]
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|b
operator|)
operator|/
literal|255.999
expr_stmt|;
name|color
index|[
literal|3
index|]
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|a
operator|)
operator|/
literal|255.999
expr_stmt|;
name|gtk_color_selection_set_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|p
operator|->
name|selector
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_gtk_update (GtkWidget * widget,gpointer data)
name|colorsel_gtk_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorselGtk
modifier|*
name|p
init|=
name|data
decl_stmt|;
name|gint
name|r
decl_stmt|;
name|gint
name|g
decl_stmt|;
name|gint
name|b
decl_stmt|;
name|gint
name|a
decl_stmt|;
name|gdouble
name|color
index|[
literal|4
index|]
decl_stmt|;
name|gtk_color_selection_get_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|p
operator|->
name|selector
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|r
operator|=
call|(
name|gint
call|)
argument_list|(
name|color
index|[
literal|0
index|]
operator|*
literal|255.999
argument_list|)
expr_stmt|;
name|g
operator|=
call|(
name|gint
call|)
argument_list|(
name|color
index|[
literal|1
index|]
operator|*
literal|255.999
argument_list|)
expr_stmt|;
name|b
operator|=
call|(
name|gint
call|)
argument_list|(
name|color
index|[
literal|2
index|]
operator|*
literal|255.999
argument_list|)
expr_stmt|;
name|a
operator|=
call|(
name|gint
call|)
argument_list|(
name|color
index|[
literal|3
index|]
operator|*
literal|255.999
argument_list|)
expr_stmt|;
name|p
operator|->
name|callback
argument_list|(
name|p
operator|->
name|client_data
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* EEK */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|colorsel_gtk_widget_idle_hide (gpointer data)
name|colorsel_gtk_widget_idle_hide
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
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
DECL|function|colorsel_gtk_widget_hide (GtkWidget * widget,gpointer data)
name|colorsel_gtk_widget_hide
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_idle_add
argument_list|(
name|colorsel_gtk_widget_idle_hide
argument_list|,
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


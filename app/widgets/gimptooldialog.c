begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooldialog.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimptooldialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewabledialog.h"
end_include

begin_comment
comment|/**  * gimp_tool_dialog_new:  * @tool_info: a #GimpToolInfo  * @parent: the parent widget of this dialog  * @desc: a string to use in the dialog header or %NULL to use the help  *        field from #GimpToolInfo  * @...: a %NULL-terminated valist of button parameters as described in  *       gimp_dialog_create_action_areav().  *  * This function conveniently creates a #GimpViewableDialog using the  * information stored in @tool_info. It also registers the tool with  * the "toplevel" dialog factory.  *  * Return value: a new #GimpViewableDialog  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_dialog_new (GimpToolInfo * tool_info,GtkWidget * parent,const gchar * desc,...)
name|gimp_tool_dialog_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
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
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|NULL
argument_list|,
name|tool_info
operator|->
name|blurb
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
operator|->
name|name
argument_list|,
name|stock_id
argument_list|,
name|desc
condition|?
name|desc
else|:
name|tool_info
operator|->
name|help
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|tool_info
operator|->
name|help_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_type_hint
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GDK_WINDOW_TYPE_HINT_UTILITY
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|gimp_dialog_add_buttons_valist
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|identifier
operator|=
name|g_strconcat
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
operator|->
name|name
argument_list|,
literal|"-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_add_foreign
argument_list|(
name|gimp_dialog_factory_from_name
argument_list|(
literal|"toplevel"
argument_list|)
argument_list|,
name|identifier
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

end_unit


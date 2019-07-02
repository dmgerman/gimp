begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpradioaction.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  * Copyright (C) 2008 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpaction.h"
end_include

begin_include
include|#
directive|include
file|"gimpradioaction.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_radio_action_connect_proxy
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|proxy
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpRadioAction,gimp_radio_action,GTK_TYPE_RADIO_ACTION,G_IMPLEMENT_INTERFACE (GIMP_TYPE_ACTION,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpRadioAction
argument_list|,
argument|gimp_radio_action
argument_list|,
argument|GTK_TYPE_RADIO_ACTION
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_ACTION, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_radio_action_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_radio_action_class_init
parameter_list|(
name|GimpRadioActionClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkActionClass
modifier|*
name|action_class
init|=
name|GTK_ACTION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|action_class
operator|->
name|connect_proxy
operator|=
name|gimp_radio_action_connect_proxy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_radio_action_init (GimpRadioAction * action)
name|gimp_radio_action_init
parameter_list|(
name|GimpRadioAction
modifier|*
name|action
parameter_list|)
block|{
name|gimp_action_init
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_radio_action_connect_proxy (GtkAction * action,GtkWidget * proxy)
name|gimp_radio_action_connect_proxy
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkWidget
modifier|*
name|proxy
parameter_list|)
block|{
name|GTK_ACTION_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|connect_proxy
argument_list|(
name|action
argument_list|,
name|proxy
argument_list|)
expr_stmt|;
name|gimp_action_set_proxy
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|proxy
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkRadioAction
modifier|*
DECL|function|gimp_radio_action_new (const gchar * name,const gchar * label,const gchar * tooltip,const gchar * icon_name,const gchar * help_id,gint value)
name|gimp_radio_action_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|GtkRadioAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RADIO_ACTION
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"label"
argument_list|,
name|label
argument_list|,
literal|"tooltip"
argument_list|,
name|tooltip
argument_list|,
literal|"icon-name"
argument_list|,
name|icon_name
argument_list|,
literal|"value"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_action_set_help_id
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
return|return
name|action
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_radio_action_set_current_value (GimpRadioAction * action,gint value)
name|gimp_radio_action_set_current_value
parameter_list|(
name|GimpRadioAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|gtk_radio_action_set_current_value
argument_list|(
operator|(
name|GtkRadioAction
operator|*
operator|)
name|action
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_radio_action_get_current_value (GimpRadioAction * action)
name|gimp_radio_action_get_current_value
parameter_list|(
name|GimpRadioAction
modifier|*
name|action
parameter_list|)
block|{
return|return
name|gtk_radio_action_get_current_value
argument_list|(
operator|(
name|GtkRadioAction
operator|*
operator|)
name|action
argument_list|)
return|;
block|}
end_function

end_unit


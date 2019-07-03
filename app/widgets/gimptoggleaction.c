begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoggleaction.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  * Copyright (C) 2008 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimptoggleaction.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_toggle_action_connect_proxy
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

begin_function_decl
specifier|static
name|void
name|gimp_toggle_action_toggled
parameter_list|(
name|GtkToggleAction
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpToggleAction,gimp_toggle_action,GTK_TYPE_TOGGLE_ACTION,G_IMPLEMENT_INTERFACE (GIMP_TYPE_ACTION,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpToggleAction
argument_list|,
argument|gimp_toggle_action
argument_list|,
argument|GTK_TYPE_TOGGLE_ACTION
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_ACTION, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_toggle_action_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_toggle_action_class_init
parameter_list|(
name|GimpToggleActionClass
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
name|GtkToggleActionClass
modifier|*
name|toggle_class
init|=
name|GTK_TOGGLE_ACTION_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|action_class
operator|->
name|connect_proxy
operator|=
name|gimp_toggle_action_connect_proxy
expr_stmt|;
name|toggle_class
operator|->
name|toggled
operator|=
name|gimp_toggle_action_toggled
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_toggle_action_init (GimpToggleAction * action)
name|gimp_toggle_action_init
parameter_list|(
name|GimpToggleAction
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
DECL|function|gimp_toggle_action_connect_proxy (GtkAction * action,GtkWidget * proxy)
name|gimp_toggle_action_connect_proxy
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

begin_function
specifier|static
name|void
DECL|function|gimp_toggle_action_toggled (GtkToggleAction * action)
name|gimp_toggle_action_toggled
parameter_list|(
name|GtkToggleAction
modifier|*
name|action
parameter_list|)
block|{
name|gboolean
name|value
decl_stmt|;
name|value
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_emit_change_state
argument_list|(
name|GIMP_ACTION
argument_list|(
name|action
argument_list|)
argument_list|,
name|g_variant_new_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkToggleAction
modifier|*
DECL|function|gimp_toggle_action_new (const gchar * name,const gchar * label,const gchar * tooltip,const gchar * icon_name,const gchar * help_id)
name|gimp_toggle_action_new
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
parameter_list|)
block|{
name|GtkToggleAction
modifier|*
name|action
decl_stmt|;
name|action
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOGGLE_ACTION
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
DECL|function|gimp_toggle_action_set_active (GimpToggleAction * action,gboolean active)
name|gimp_toggle_action_set_active
parameter_list|(
name|GimpToggleAction
modifier|*
name|action
parameter_list|,
name|gboolean
name|active
parameter_list|)
block|{
return|return
name|gtk_toggle_action_set_active
argument_list|(
operator|(
name|GtkToggleAction
operator|*
operator|)
name|action
argument_list|,
name|active
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_toggle_action_get_active (GimpToggleAction * action)
name|gimp_toggle_action_get_active
parameter_list|(
name|GimpToggleAction
modifier|*
name|action
parameter_list|)
block|{
return|return
name|gtk_toggle_action_get_active
argument_list|(
operator|(
name|GtkToggleAction
operator|*
operator|)
name|action
argument_list|)
return|;
block|}
end_function

end_unit


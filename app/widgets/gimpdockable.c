begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockable.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockbook.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_dockable_class_init
parameter_list|(
name|GimpDockableClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_init
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dockable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkBinClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_dockable_get_type (void)
name|gimp_dockable_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|dockable_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dockable_type
condition|)
block|{
specifier|static
specifier|const
name|GtkTypeInfo
name|dockable_info
init|=
block|{
literal|"GimpDockable"
block|,
sizeof|sizeof
argument_list|(
name|GimpDockable
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpDockableClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_dockable_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_dockable_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|dockable_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_VBOX
argument_list|,
operator|&
name|dockable_info
argument_list|)
expr_stmt|;
block|}
return|return
name|dockable_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_class_init (GimpDockableClass * klass)
name|gimp_dockable_class_init
parameter_list|(
name|GimpDockableClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_dockable_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_init (GimpDockable * dockable)
name|gimp_dockable_init
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|dockable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|short_name
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|dockbook
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|get_tab_func
operator|=
name|NULL
expr_stmt|;
name|dockable
operator|->
name|set_context_func
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dockable_destroy (GtkObject * object)
name|gimp_dockable_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"gimp_dockable_destroy()\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|context
condition|)
name|gimp_dockable_set_context
argument_list|(
name|dockable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|name
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|dockable
operator|->
name|short_name
condition|)
block|{
name|g_free
argument_list|(
name|dockable
operator|->
name|short_name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|short_name
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_new (const gchar * name,const gchar * short_name,GimpDockableGetTabFunc get_tab_func,GimpDockableSetContextFunc set_context_func)
name|gimp_dockable_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|short_name
parameter_list|,
name|GimpDockableGetTabFunc
name|get_tab_func
parameter_list|,
name|GimpDockableSetContextFunc
name|set_context_func
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|short_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_DOCKABLE
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|short_name
operator|=
name|g_strdup
argument_list|(
name|short_name
argument_list|)
expr_stmt|;
name|dockable
operator|->
name|get_tab_func
operator|=
name|get_tab_func
expr_stmt|;
name|dockable
operator|->
name|set_context_func
operator|=
name|set_context_func
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dockable_get_tab_widget (GimpDockable * dockable,GimpDockbook * dockbook,gint size)
name|gimp_dockable_get_tab_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|>=
operator|-
literal|1
operator|&&
name|size
operator|<
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
operator|->
name|get_tab_func
condition|)
block|{
return|return
name|dockable
operator|->
name|get_tab_func
argument_list|(
name|dockable
argument_list|,
name|dockbook
argument_list|,
name|size
argument_list|)
return|;
block|}
return|return
name|gtk_label_new
argument_list|(
name|dockable
operator|->
name|short_name
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dockable_set_context (GimpDockable * dockable,GimpContext * context)
name|gimp_dockable_set_context
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|context
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
operator|!=
name|dockable
operator|->
name|context
condition|)
block|{
if|if
condition|(
name|dockable
operator|->
name|set_context_func
condition|)
block|{
name|dockable
operator|->
name|set_context_func
argument_list|(
name|dockable
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
name|dockable
operator|->
name|context
operator|=
name|context
expr_stmt|;
block|}
block|}
end_function

end_unit


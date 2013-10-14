begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTreeHandler  * Copyright (C) 2009  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimptreehandler.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_dispose
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
name|gimp_tree_handler_freeze
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_thaw
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_add_container
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_add_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_add
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_remove_container
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_remove_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tree_handler_remove
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTreeHandler,gimp_tree_handler,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTreeHandler
argument_list|,
argument|gimp_tree_handler
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tree_handler_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tree_handler_class_init
parameter_list|(
name|GimpTreeHandlerClass
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
name|object_class
operator|->
name|dispose
operator|=
name|gimp_tree_handler_dispose
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_init (GimpTreeHandler * handler)
name|gimp_tree_handler_init
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_dispose (GObject * object)
name|gimp_tree_handler_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTreeHandler
modifier|*
name|handler
init|=
name|GIMP_TREE_HANDLER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|handler
operator|->
name|container
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|handler
operator|->
name|container
argument_list|,
name|gimp_tree_handler_freeze
argument_list|,
name|handler
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|handler
operator|->
name|container
argument_list|,
name|gimp_tree_handler_thaw
argument_list|,
name|handler
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_container_frozen
argument_list|(
name|handler
operator|->
name|container
argument_list|)
condition|)
name|gimp_tree_handler_remove_container
argument_list|(
name|handler
argument_list|,
name|handler
operator|->
name|container
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|handler
operator|->
name|container
argument_list|)
expr_stmt|;
name|handler
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
name|g_free
argument_list|(
name|handler
operator|->
name|signal_name
argument_list|)
expr_stmt|;
name|handler
operator|->
name|signal_name
operator|=
name|NULL
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

begin_function
name|GimpTreeHandler
modifier|*
DECL|function|gimp_tree_handler_connect (GimpContainer * container,const gchar * signal_name,GCallback callback,gpointer user_data)
name|gimp_tree_handler_connect
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal_name
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpTreeHandler
modifier|*
name|handler
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|signal_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|handler
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TREE_HANDLER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|handler
operator|->
name|container
operator|=
name|g_object_ref
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|handler
operator|->
name|signal_name
operator|=
name|g_strdup
argument_list|(
name|signal_name
argument_list|)
expr_stmt|;
name|handler
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|handler
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_container_frozen
argument_list|(
name|container
argument_list|)
condition|)
name|gimp_tree_handler_add_container
argument_list|(
name|handler
argument_list|,
name|container
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|container
argument_list|,
literal|"freeze"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tree_handler_freeze
argument_list|)
argument_list|,
name|handler
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|container
argument_list|,
literal|"thaw"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tree_handler_thaw
argument_list|)
argument_list|,
name|handler
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
return|return
name|handler
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tree_handler_disconnect (GimpTreeHandler * handler)
name|gimp_tree_handler_disconnect
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TREE_HANDLER
argument_list|(
name|handler
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_run_dispose
argument_list|(
name|G_OBJECT
argument_list|(
name|handler
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|handler
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_freeze (GimpTreeHandler * handler,GimpContainer * container)
name|gimp_tree_handler_freeze
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|gimp_tree_handler_remove_container
argument_list|(
name|handler
argument_list|,
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_thaw (GimpTreeHandler * handler,GimpContainer * container)
name|gimp_tree_handler_thaw
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|gimp_tree_handler_add_container
argument_list|(
name|handler
argument_list|,
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_add_container (GimpTreeHandler * handler,GimpContainer * container)
name|gimp_tree_handler_add_container
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|gimp_container_foreach
argument_list|(
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_tree_handler_add_foreach
argument_list|,
name|handler
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|container
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tree_handler_add
argument_list|)
argument_list|,
name|handler
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|container
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tree_handler_remove
argument_list|)
argument_list|,
name|handler
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_add_foreach (GimpViewable * viewable,GimpTreeHandler * handler)
name|gimp_tree_handler_add_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|)
block|{
name|gimp_tree_handler_add
argument_list|(
name|handler
argument_list|,
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_add (GimpTreeHandler * handler,GimpViewable * viewable,GimpContainer * unused)
name|gimp_tree_handler_add
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|unused
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|children
init|=
name|gimp_viewable_get_children
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|g_signal_connect
argument_list|(
name|viewable
argument_list|,
name|handler
operator|->
name|signal_name
argument_list|,
name|handler
operator|->
name|callback
argument_list|,
name|handler
operator|->
name|user_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|children
condition|)
name|gimp_tree_handler_add_container
argument_list|(
name|handler
argument_list|,
name|children
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_remove_container (GimpTreeHandler * handler,GimpContainer * container)
name|gimp_tree_handler_remove_container
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|container
argument_list|,
name|gimp_tree_handler_add
argument_list|,
name|handler
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|container
argument_list|,
name|gimp_tree_handler_remove
argument_list|,
name|handler
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_tree_handler_remove_foreach
argument_list|,
name|handler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_remove_foreach (GimpViewable * viewable,GimpTreeHandler * handler)
name|gimp_tree_handler_remove_foreach
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|)
block|{
name|gimp_tree_handler_remove
argument_list|(
name|handler
argument_list|,
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tree_handler_remove (GimpTreeHandler * handler,GimpViewable * viewable,GimpContainer * unused)
name|gimp_tree_handler_remove
parameter_list|(
name|GimpTreeHandler
modifier|*
name|handler
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContainer
modifier|*
name|unused
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|children
init|=
name|gimp_viewable_get_children
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|children
condition|)
name|gimp_tree_handler_remove_container
argument_list|(
name|handler
argument_list|,
name|children
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|viewable
argument_list|,
name|handler
operator|->
name|callback
argument_list|,
name|handler
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


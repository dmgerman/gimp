begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolordisplaystack.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU Lesser General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolordisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolordisplaystack.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29d6a9b40103
block|{
DECL|enumerator|CHANGED
name|CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_display_stack_class_init
parameter_list|(
name|GimpColorDisplayStackClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_display_stack_init
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_display_stack_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|stack_signals
specifier|static
name|guint
name|stack_signals
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
name|GType
DECL|function|gimp_color_display_stack_get_type (void)
name|gimp_color_display_stack_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|display_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|display_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|display_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorDisplayStackClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_color_display_stack_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorDisplayStack
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_display_stack_init
block|,       }
decl_stmt|;
name|display_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_OBJECT
argument_list|,
literal|"GimpColorDisplayStack"
argument_list|,
operator|&
name|display_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|display_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_class_init (GimpColorDisplayStackClass * klass)
name|gimp_color_display_stack_class_init
parameter_list|(
name|GimpColorDisplayStackClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|stack_signals
index|[
name|CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpColorDisplayStackClass
argument_list|,
name|changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_display_stack_finalize
expr_stmt|;
name|klass
operator|->
name|changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_init (GimpColorDisplayStack * stack)
name|gimp_color_display_stack_init
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|stack
operator|->
name|filters
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_display_stack_finalize (GObject * object)
name|gimp_color_display_stack_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorDisplayStack
modifier|*
name|stack
init|=
name|GIMP_COLOR_DISPLAY_STACK
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|stack
operator|->
name|filters
condition|)
block|{
name|g_list_foreach
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_unref
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|stack
operator|->
name|filters
argument_list|)
expr_stmt|;
name|stack
operator|->
name|filters
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpColorDisplayStack
modifier|*
DECL|function|gimp_color_display_stack_new (void)
name|gimp_color_display_stack_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpColorDisplayStack
modifier|*
name|stack
decl_stmt|;
name|stack
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_DISPLAY_STACK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|stack
return|;
block|}
end_function

begin_function
name|GimpColorDisplayStack
modifier|*
DECL|function|gimp_color_display_stack_clone (GimpColorDisplayStack * stack)
name|gimp_color_display_stack_clone
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|GimpColorDisplayStack
modifier|*
name|clone
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|clone
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_DISPLAY_STACK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|stack
operator|->
name|filters
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorDisplay
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gimp_color_display_clone
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_add
argument_list|(
name|clone
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
return|return
name|clone
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_changed (GimpColorDisplayStack * stack)
name|gimp_color_display_stack_changed
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|stack
argument_list|,
name|stack_signals
index|[
name|CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_add (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_add
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|stack
operator|->
name|filters
operator|=
name|g_list_append
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|g_object_ref
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|display
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_display_stack_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|stack
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_remove (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_remove
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|display
argument_list|,
name|gimp_color_display_stack_changed
argument_list|,
name|stack
argument_list|)
expr_stmt|;
name|stack
operator|->
name|filters
operator|=
name|g_list_remove
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_reorder_up (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_reorder_up
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|prev
condition|)
block|{
name|list
operator|->
name|data
operator|=
name|list
operator|->
name|prev
operator|->
name|data
expr_stmt|;
name|list
operator|->
name|prev
operator|->
name|data
operator|=
name|display
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_reorder_down (GimpColorDisplayStack * stack,GimpColorDisplay * display)
name|gimp_color_display_stack_reorder_down
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|stack
operator|->
name|filters
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|next
condition|)
block|{
name|list
operator|->
name|data
operator|=
name|list
operator|->
name|next
operator|->
name|data
expr_stmt|;
name|list
operator|->
name|next
operator|->
name|data
operator|=
name|display
expr_stmt|;
name|gimp_color_display_stack_changed
argument_list|(
name|stack
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_display_stack_convert (GimpColorDisplayStack * stack,guchar * buf,gint width,gint height,gint bpp,gint bpl)
name|gimp_color_display_stack_convert
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_DISPLAY_STACK
argument_list|(
name|stack
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|stack
operator|->
name|filters
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_color_display_convert
argument_list|(
name|display
argument_list|,
name|buf
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bpp
argument_list|,
name|bpl
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_define
DECL|macro|CONTEXT_CHECK_CURRENT (context)
define|#
directive|define
name|CONTEXT_CHECK_CURRENT
parameter_list|(
name|context
parameter_list|)
define|\
value|((context) = (context) ? (context) : current_context)
end_define

begin_enum
DECL|enum|__anon2b3ae5460103
enum|enum
block|{
DECL|enumerator|OPACITY_CHANGED
name|OPACITY_CHANGED
block|,
DECL|enumerator|PAINT_MODE_CHANGED
name|PAINT_MODE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_decl_stmt
DECL|variable|gimp_context_signals
specifier|static
name|guint
name|gimp_context_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the currently active context  */
end_comment

begin_decl_stmt
DECL|variable|current_context
specifier|static
name|GimpContext
modifier|*
name|current_context
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  for later use static void gimp_context_destroy (GtkObject *object) {   GimpContext *context;    g_return_if_fail (object != NULL);   g_return_if_fail (GIMP_IS_CONTEXT (object));    context = GIMP_CONTEXT (object);    if (GTK_OBJECT_CLASS (parent_class)->destroy)     (* GTK_OBJECT_CLASS (parent_class)->destroy) (object); } */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_context_class_init (GimpContextClass * klass)
name|gimp_context_class_init
parameter_list|(
name|GimpContextClass
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
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gimp_object_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_context_signals
index|[
name|OPACITY_CHANGED
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"opacity_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContextClass
argument_list|,
name|opacity_changed
argument_list|)
argument_list|,
name|gimp_sigtype_void
argument_list|)
expr_stmt|;
name|gimp_context_signals
index|[
name|PAINT_MODE_CHANGED
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"paint_mode_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpContextClass
argument_list|,
name|paint_mode_changed
argument_list|)
argument_list|,
name|gimp_sigtype_void
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_context_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|klass
operator|->
name|opacity_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|paint_mode_changed
operator|=
name|NULL
expr_stmt|;
comment|/* object_class->destroy = gimp_context_destroy; */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_context_init (GimpContext * context)
name|gimp_context_init
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|context
operator|->
name|opacity
operator|=
literal|1.0
expr_stmt|;
name|context
operator|->
name|paint_mode
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_context_get_type (void)
name|gimp_context_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpContext"
block|,
sizeof|sizeof
argument_list|(
name|GimpContext
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpContextClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_context_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_context_init
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
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|gimp_object_get_type
argument_list|()
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GimpContext
modifier|*
DECL|function|gimp_context_new (void)
name|gimp_context_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|gtk_type_new
argument_list|(
name|gimp_context_get_type
argument_list|()
argument_list|)
expr_stmt|;
return|return
name|context
return|;
block|}
end_function

begin_function
name|GimpContext
modifier|*
DECL|function|gimp_context_get_current (void)
name|gimp_context_get_current
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|current_context
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_context_set_current (GimpContext * context)
name|gimp_context_set_current
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|current_context
operator|=
name|context
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_context_get_opacity (GimpContext * context)
name|gimp_context_get_opacity
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|CONTEXT_CHECK_CURRENT
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|context
operator|!=
name|NULL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|context
operator|->
name|opacity
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_context_set_opacity (GimpContext * context,gdouble opacity)
name|gimp_context_set_opacity
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|CONTEXT_CHECK_CURRENT
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_signals
index|[
name|OPACITY_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_context_get_paint_mode (GimpContext * context)
name|gimp_context_get_paint_mode
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|CONTEXT_CHECK_CURRENT
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|context
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|context
operator|->
name|paint_mode
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_context_set_paint_mode (GimpContext * context,gint paint_mode)
name|gimp_context_set_paint_mode
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|paint_mode
parameter_list|)
block|{
name|CONTEXT_CHECK_CURRENT
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|->
name|paint_mode
operator|=
name|paint_mode
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_signals
index|[
name|PAINT_MODE_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpmarshal.h"
end_include

begin_typedef
DECL|typedef|GimpSignal_NONE__INT_INT_INT_INT
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSignal_NONE__INT_INT_INT_INT
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gint
name|arg1
parameter_list|,
name|gint
name|arg2
parameter_list|,
name|gint
name|arg3
parameter_list|,
name|gint
name|arg4
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function
name|void
DECL|function|gimp_marshal_NONE__INT_INT_INT_INT (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshal_NONE__INT_INT_INT_INT
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|(
operator|*
operator|(
name|GimpSignal_NONE__INT_INT_INT_INT
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|1
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|2
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|3
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|typedef|GimpSignal_NONE__INT_INT_INT
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSignal_NONE__INT_INT_INT
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gint
name|arg1
parameter_list|,
name|gint
name|arg2
parameter_list|,
name|gint
name|arg3
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function
name|void
DECL|function|gimp_marshal_NONE__INT_INT_INT (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshal_NONE__INT_INT_INT
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|(
operator|*
operator|(
name|GimpSignal_NONE__INT_INT_INT
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|1
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|2
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|typedef|GimpSignal_NONE__DOUBLE
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSignal_NONE__DOUBLE
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gdouble
name|arg1
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function
name|void
DECL|function|gimp_marshal_NONE__DOUBLE (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshal_NONE__DOUBLE
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|(
operator|*
operator|(
name|GimpSignal_NONE__DOUBLE
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_DOUBLE
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|typedef|GimpSignal_POINTER__INT_INT
typedef|typedef
name|gpointer
function_decl|(
modifier|*
name|GimpSignal_POINTER__INT_INT
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gint
name|arg1
parameter_list|,
name|gint
name|arg2
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function
name|void
DECL|function|gimp_marshal_POINTER__INT_INT (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshal_POINTER__INT_INT
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|*
name|GTK_RETLOC_POINTER
argument_list|(
name|args
index|[
literal|2
index|]
argument_list|)
operator|=
operator|(
operator|*
operator|(
name|GimpSignal_POINTER__INT_INT
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|1
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|typedef|GimpSignal_POINTER__POINTER_INT_INT
typedef|typedef
name|gpointer
function_decl|(
modifier|*
name|GimpSignal_POINTER__POINTER_INT_INT
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|arg1
parameter_list|,
name|gint
name|arg2
parameter_list|,
name|gint
name|arg3
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function
name|void
DECL|function|gimp_marshal_POINTER__POINTER_INT_INT (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshal_POINTER__POINTER_INT_INT
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|*
name|GTK_RETLOC_POINTER
argument_list|(
name|args
index|[
literal|3
index|]
argument_list|)
operator|=
operator|(
operator|*
operator|(
name|GimpSignal_POINTER__POINTER_INT_INT
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_POINTER
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|1
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|2
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Test suite for GimpConfig.  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"stdlib.h"
end_include

begin_include
include|#
directive|include
file|"string.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
end_include

begin_function_decl
specifier|static
name|void
name|notify_callback
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|output_unknown_token
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|int
DECL|function|main (int argc,char * argv[])
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|GimpConfig
modifier|*
name|grid
decl_stmt|;
name|GimpConfig
modifier|*
name|grid2
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
init|=
literal|"foorc"
decl_stmt|;
name|gchar
modifier|*
name|header
decl_stmt|;
name|gchar
modifier|*
name|result
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|argc
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--g-fatal-warnings"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|GLogLevelFlags
name|fatal_mask
decl_stmt|;
name|fatal_mask
operator|=
name|g_log_set_always_fatal
argument_list|(
name|G_LOG_FATAL_MASK
argument_list|)
expr_stmt|;
name|fatal_mask
operator||=
name|G_LOG_LEVEL_WARNING
operator||
name|G_LOG_LEVEL_CRITICAL
expr_stmt|;
name|g_log_set_always_fatal
argument_list|(
name|fatal_mask
argument_list|)
expr_stmt|;
block|}
block|}
name|g_type_init
argument_list|()
expr_stmt|;
name|g_print
argument_list|(
literal|"\nTesting GimpConfig ...\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Creating a new Grid object ..."
argument_list|)
expr_stmt|;
name|grid
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" done.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Adding the unknown token (foobar \"hadjaha\") ..."
argument_list|)
expr_stmt|;
name|gimp_config_add_unknown_token
argument_list|(
name|grid
argument_list|,
literal|"foobar"
argument_list|,
literal|"hadjaha"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" done.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Serializing %s to '%s' ..."
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|grid
argument_list|)
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_file
argument_list|(
name|grid
argument_list|,
name|filename
argument_list|,
literal|"foorc"
argument_list|,
literal|"end of foorc"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
name|g_print
argument_list|(
literal|" done.\n"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|grid
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|notify_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Deserializing from '%s' ...\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|grid
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
name|header
operator|=
literal|" Unknown string tokens:\n"
expr_stmt|;
name|gimp_config_foreach_unknown_token
argument_list|(
name|grid
argument_list|,
name|output_unknown_token
argument_list|,
operator|&
name|header
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" done.\n\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Changing a property ..."
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|grid
argument_list|,
literal|"style"
argument_list|,
name|GIMP_GRID_DOTS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Testing gimp_config_duplicate() ..."
argument_list|)
expr_stmt|;
name|grid2
operator|=
name|gimp_config_duplicate
argument_list|(
name|grid
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" done.\n"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|grid2
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|notify_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Changing a property in the duplicate ..."
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|grid2
argument_list|,
literal|"xspacing"
argument_list|,
literal|20.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Creating a diff between the two ..."
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_config_diff
argument_list|(
name|grid
argument_list|,
name|grid2
argument_list|,
literal|0
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_print
argument_list|(
literal|"%c%s"
argument_list|,
operator|(
name|list
operator|->
name|prev
condition|?
literal|','
else|:
literal|' '
operator|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
name|g_print
argument_list|(
literal|"\n\n"
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|grid2
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|" Deserializing from gimpconfig.c (should fail) ..."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|grid
argument_list|,
literal|"gimpconfig.c"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_print
argument_list|(
literal|" OK, failed. The error was:\n %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|error
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"This test should have failed :-(\n"
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
name|g_print
argument_list|(
literal|" Serializing to a string and back ... "
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_config_serialize_to_string
argument_list|(
name|grid
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|grid2
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRID
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_string
argument_list|(
name|grid2
argument_list|,
name|result
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_print
argument_list|(
literal|"failed!\nThe error was:\n %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
else|else
block|{
name|GList
modifier|*
name|diff
init|=
name|gimp_config_diff
argument_list|(
name|grid
argument_list|,
name|grid2
argument_list|,
literal|0
argument_list|)
decl_stmt|;
if|if
condition|(
name|diff
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_print
argument_list|(
literal|"succeeded but properties differ:\n"
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|diff
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GParamSpec
modifier|*
name|pspec
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_print
argument_list|(
literal|"   %s\n"
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|EXIT_FAILURE
return|;
block|}
name|g_print
argument_list|(
literal|"OK (%u bytes)\n"
argument_list|,
name|result
condition|?
operator|(
name|guint
operator|)
name|strlen
argument_list|(
name|result
argument_list|)
else|:
literal|0
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|result
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|grid2
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|grid
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\nFinished test of GimpConfig.\n\n"
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|notify_callback (GObject * object,GParamSpec * pspec)
name|notify_callback
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GString
modifier|*
name|str
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|object
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_config_serialize_value
argument_list|(
operator|&
name|value
argument_list|,
name|str
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|g_print
argument_list|(
literal|"  %s -> %s\n"
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|str
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"  %s changed but we failed to serialize its value!\n"
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|output_unknown_token (const gchar * key,const gchar * value,gpointer data)
name|output_unknown_token
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|header
init|=
operator|(
name|gchar
operator|*
operator|*
operator|)
name|data
decl_stmt|;
name|gchar
modifier|*
name|escaped
init|=
name|g_strescape
argument_list|(
name|value
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
operator|*
name|header
condition|)
block|{
name|g_print
argument_list|(
operator|*
name|header
argument_list|)
expr_stmt|;
operator|*
name|header
operator|=
name|NULL
expr_stmt|;
block|}
name|g_print
argument_list|(
literal|"   %s \"%s\"\n"
argument_list|,
name|key
argument_list|,
name|escaped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|escaped
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* some dummy funcs so we can properly link this beast */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_unit_get_identifier (GimpUnit unit)
name|gimp_unit_get_identifier
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
switch|switch
condition|(
name|unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
return|return
literal|"pixels"
return|;
case|case
name|GIMP_UNIT_INCH
case|:
return|return
literal|"inches"
return|;
case|case
name|GIMP_UNIT_MM
case|:
return|return
literal|"millimeters"
return|;
case|case
name|GIMP_UNIT_POINT
case|:
return|return
literal|"points"
return|;
case|case
name|GIMP_UNIT_PICA
case|:
return|return
literal|"picas"
return|;
default|default:
return|return
name|NULL
return|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_unit_get_number_of_units (void)
name|gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|GIMP_UNIT_END
return|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfig object property dumper.   * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpversion.h"
end_include

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_function_decl
specifier|static
name|gint
name|dump_man_page
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|dump_system_gimprc
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|dump_get_comment
parameter_list|(
name|GParamSpec
modifier|*
name|param_spec
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
name|GObject
modifier|*
name|rc
decl_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
if|if
condition|(
name|argc
operator|>
literal|1
condition|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
literal|1
index|]
argument_list|,
literal|"--system-gimprc"
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|dump_system_gimprc
argument_list|()
return|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
literal|1
index|]
argument_list|,
literal|"--man-page"
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|dump_man_page
argument_list|()
return|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
literal|1
index|]
argument_list|,
literal|"--version"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_printerr
argument_list|(
literal|"gimpconfig-dump version %s\n"
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"gimpconfig-dump version %s\n\n"
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"Usage: %s [option ... ]\n\n"
argument_list|,
name|argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"Options:\n"
literal|"  --man-page        create a gimprc manual page\n"
literal|"  --system-gimprc   create a commented system gimprc\n"
literal|"  --help            output usage information\n"
literal|"  --version         output version information\n"
literal|"\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
literal|1
index|]
argument_list|,
literal|"--help"
argument_list|)
operator|==
literal|0
condition|)
return|return
name|EXIT_SUCCESS
return|;
else|else
return|return
name|EXIT_FAILURE
return|;
block|}
block|}
name|rc
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"# Dump of the GIMP default configuration\n\n"
argument_list|)
expr_stmt|;
name|gimp_config_serialize_properties
argument_list|(
name|rc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|rc
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|dump_man_page (void)
name|dump_man_page
parameter_list|(
name|void
parameter_list|)
block|{
name|g_warning
argument_list|(
literal|"dump_man_page() is not yet implemented."
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|dump_system_gimprc (void)
name|dump_system_gimprc
parameter_list|(
name|void
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|klass
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|property_specs
decl_stmt|;
name|GObject
modifier|*
name|rc
decl_stmt|;
name|GString
modifier|*
name|str
decl_stmt|;
name|guint
name|n_property_specs
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|str
operator|=
name|g_string_new
argument_list|(
literal|"# This is the system-wide gimprc file.  Any change made in this file\n"
literal|"# will affect all users of this system, provided that they are not\n"
literal|"# overriding the default values in their personal gimprc file.\n"
literal|"#\n"
literal|"# Lines that start with a '#' are comments.\n"
literal|"# Blank lines are ignored.\n"
literal|"\n"
literal|"# The variable gimp_dir is set to either the interned value\n"
literal|"# @gimpdir@ or the environment variable GIMP_DIRECTORY.  If\n"
literal|"# the path in GIMP_DIRECTORY is relative, it is considered\n"
literal|"# relative to your home directory.\n"
literal|"\n"
literal|"(prefix \"@prefix@\"\n"
literal|"(exec_prefix \"@exec_prefix@\")\n"
literal|"(gimp_data_dir \"@gimpdatadir@\")\n"
literal|"(gimp_plugin_dir \"@gimpplugindir@\")\n"
literal|"\n"
argument_list|)
expr_stmt|;
name|write
argument_list|(
literal|1
argument_list|,
name|str
operator|->
name|str
argument_list|,
name|str
operator|->
name|len
argument_list|)
expr_stmt|;
name|rc
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|rc
argument_list|)
expr_stmt|;
name|property_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|klass
argument_list|,
operator|&
name|n_property_specs
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_property_specs
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|prop_spec
init|=
name|property_specs
index|[
name|i
index|]
decl_stmt|;
name|gchar
modifier|*
name|comment
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
name|g_string_assign
argument_list|(
name|str
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|comment
operator|=
name|dump_get_comment
argument_list|(
name|prop_spec
argument_list|)
expr_stmt|;
if|if
condition|(
name|comment
condition|)
block|{
name|gimp_config_serialize_comment
argument_list|(
name|str
argument_list|,
name|comment
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|comment
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"#\n"
argument_list|)
expr_stmt|;
block|}
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"# "
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_config_serialize_property
argument_list|(
name|rc
argument_list|,
name|prop_spec
argument_list|,
name|str
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
name|write
argument_list|(
literal|1
argument_list|,
name|str
operator|->
name|str
argument_list|,
name|str
operator|->
name|len
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|rc
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|dump_get_comment (GParamSpec * param_spec)
name|dump_get_comment
parameter_list|(
name|GParamSpec
modifier|*
name|param_spec
parameter_list|)
block|{
name|GType
name|type
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|blurb
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|values
init|=
name|NULL
decl_stmt|;
name|blurb
operator|=
name|g_param_spec_get_blurb
argument_list|(
name|param_spec
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|blurb
condition|)
block|{
name|g_warning
argument_list|(
literal|"FIXME: Property '%s' has no blurb."
argument_list|,
name|param_spec
operator|->
name|name
argument_list|)
expr_stmt|;
name|blurb
operator|=
name|param_spec
operator|->
name|name
expr_stmt|;
block|}
name|type
operator|=
name|param_spec
operator|->
name|value_type
expr_stmt|;
if|if
condition|(
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_COLOR
argument_list|)
condition|)
block|{
name|values
operator|=
literal|"The color is specified in the form (color-rgba red green blue alpha) "
literal|"with channel values as floats between 0.0 and 1.0."
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_MEMSIZE
argument_list|)
condition|)
block|{
name|values
operator|=
literal|"The integer size can contain a suffix of 'B', 'K', 'M' or 'G' which "
literal|"makes GIMP interpret the size as being specified in bytes, kilobytes, "
literal|"megabytes or gigabytes. If no suffix is specified the size defaults "
literal|"to being specified in kilobytes."
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_PATH
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|G_SEARCHPATH_SEPARATOR
condition|)
block|{
case|case
literal|':'
case|:
name|values
operator|=
literal|"This is a colon-separated list of directories to search."
expr_stmt|;
break|break;
case|case
literal|';'
case|:
name|values
operator|=
literal|"This is a semicolon-separated list of directories to search."
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_UNIT
argument_list|)
condition|)
block|{
name|values
operator|=
literal|"The unit can be one inches, millimeters, points or picas plus "
literal|"those in your user units database."
expr_stmt|;
block|}
else|else
block|{
switch|switch
condition|(
name|G_TYPE_FUNDAMENTAL
argument_list|(
name|type
argument_list|)
condition|)
block|{
case|case
name|G_TYPE_BOOLEAN
case|:
name|values
operator|=
literal|"Possible values are yes and no."
expr_stmt|;
break|break;
case|case
name|G_TYPE_INT
case|:
case|case
name|G_TYPE_UINT
case|:
case|case
name|G_TYPE_LONG
case|:
case|case
name|G_TYPE_ULONG
case|:
name|values
operator|=
literal|"This is an integer value."
expr_stmt|;
break|break;
case|case
name|G_TYPE_FLOAT
case|:
case|case
name|G_TYPE_DOUBLE
case|:
name|values
operator|=
literal|"This is a float value."
expr_stmt|;
break|break;
case|case
name|G_TYPE_STRING
case|:
name|values
operator|=
literal|"This is a string value."
expr_stmt|;
break|break;
case|case
name|G_TYPE_ENUM
case|:
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|GString
modifier|*
name|str
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_string_new
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|"  Possible values are "
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|enum_value
operator|=
name|enum_class
operator|->
name|values
init|;
name|i
operator|<
name|enum_class
operator|->
name|n_values
condition|;
name|i
operator|++
operator|,
name|enum_value
operator|++
control|)
block|{
name|g_string_append
argument_list|(
name|str
argument_list|,
name|enum_value
operator|->
name|value_nick
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|enum_class
operator|->
name|n_values
operator|-
name|i
condition|)
block|{
case|case
literal|1
case|:
name|g_string_append_c
argument_list|(
name|str
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|" and "
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_string_append
argument_list|(
name|str
argument_list|,
literal|", "
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
return|return
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|values
condition|)
name|g_warning
argument_list|(
literal|"FIXME: Can't tell anything about a %s."
argument_list|,
name|g_type_name
argument_list|(
name|type
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s  %s"
argument_list|,
name|blurb
argument_list|,
name|values
argument_list|)
return|;
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


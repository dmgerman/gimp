begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfig object property dumper.  * Copyright (C) 2001-2006  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|<cairo.h>
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-dump.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_function_decl
specifier|static
name|void
name|dump_gimprc_system
parameter_list|(
name|GimpConfig
modifier|*
name|rc
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gint
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dump_gimprc_manpage
parameter_list|(
name|GimpConfig
modifier|*
name|rc
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gint
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|dump_describe_param
parameter_list|(
name|GParamSpec
modifier|*
name|param_spec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dump_with_linebreaks
parameter_list|(
name|gint
name|fd
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|gimp_config_dump (GimpConfigDumpFormat format)
name|gimp_config_dump
parameter_list|(
name|GimpConfigDumpFormat
name|format
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|GimpConfig
modifier|*
name|rc
decl_stmt|;
name|rc
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_fd
argument_list|(
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|format
condition|)
block|{
case|case
name|GIMP_CONFIG_DUMP_NONE
case|:
break|break;
case|case
name|GIMP_CONFIG_DUMP_GIMPRC
case|:
name|gimp_config_writer_comment
argument_list|(
name|writer
argument_list|,
literal|"Dump of the GIMP default configuration"
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_serialize_properties
argument_list|(
name|rc
argument_list|,
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CONFIG_DUMP_GIMPRC_SYSTEM
case|:
name|dump_gimprc_system
argument_list|(
name|rc
argument_list|,
name|writer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CONFIG_DUMP_GIMPRC_MANPAGE
case|:
name|dump_gimprc_manpage
argument_list|(
name|rc
argument_list|,
name|writer
argument_list|,
literal|1
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|rc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|system_gimprc_header
specifier|static
specifier|const
name|gchar
name|system_gimprc_header
index|[]
init|=
literal|"This is the system-wide gimprc file.  Any change made in this file "
literal|"will affect all users of this system, provided that they are not "
literal|"overriding the default values in their personal gimprc file.\n"
literal|"\n"
literal|"Lines that start with a '#' are comments. Blank lines are ignored.\n"
literal|"\n"
literal|"By default everything in this file is commented out.  The file then "
literal|"documents the default values and shows what changes are possible.\n"
literal|"\n"
literal|"The variable ${gimp_dir} is set to the value of the environment "
literal|"variable GIMP2_DIRECTORY or, if that is not set, the compiled-in "
literal|"default value is used.  If GIMP2_DIRECTORY is not an absolute path, "
literal|"it is interpreted relative to your home directory."
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|dump_gimprc_system (GimpConfig * rc,GimpConfigWriter * writer,gint fd)
name|dump_gimprc_system
parameter_list|(
name|GimpConfig
modifier|*
name|rc
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gint
name|fd
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
name|guint
name|n_property_specs
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|gimp_config_writer_comment
argument_list|(
name|writer
argument_list|,
name|system_gimprc_header
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
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
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
if|if
condition|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_IGNORE
condition|)
continue|continue;
name|comment
operator|=
name|dump_describe_param
argument_list|(
name|prop_spec
argument_list|)
expr_stmt|;
if|if
condition|(
name|comment
condition|)
block|{
name|gimp_config_writer_comment
argument_list|(
name|writer
argument_list|,
name|comment
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|comment
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_comment_mode
argument_list|(
name|writer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_serialize_property
argument_list|(
name|rc
argument_list|,
name|prop_spec
argument_list|,
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_comment_mode
argument_list|(
name|writer
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|man_page_header
specifier|static
specifier|const
name|gchar
name|man_page_header
index|[]
init|=
literal|".\\\" This man-page is auto-generated by gimp --dump-gimprc-manpage.\n"
literal|"\n"
literal|".TH GIMPRC 5 \"Version @GIMP_VERSION@\" \"GIMP Manual Pages\"\n"
literal|".SH NAME\n"
literal|"gimprc \\- gimp configuration file\n"
literal|".SH DESCRIPTION\n"
literal|"The\n"
literal|".B gimprc\n"
literal|"file is a configuration file read by GIMP when it starts up.  There\n"
literal|"are two of these: one system-wide one stored in\n"
literal|"@gimpsysconfdir@/gimprc and a per-user \\fB$HOME\\fP/@gimpdir@/gimprc\n"
literal|"which may override system settings.\n"
literal|"\n"
literal|"Comments are introduced by a hash sign (#), and continue until the end\n"
literal|"of the line.  Blank lines are ignored.\n"
literal|"\n"
literal|"The\n"
literal|".B gimprc\n"
literal|"file associates values with properties.  These properties may be set\n"
literal|"by lisp-like assignments of the form:\n"
literal|".IP\n"
literal|"\\f3(\\f2property\\-name\\ value\\f3)\\f1\n"
literal|".TP\n"
literal|"where:\n"
literal|".TP 10\n"
literal|".I property\\-name\n"
literal|"is one of the property names described below.\n"
literal|".TP\n"
literal|".I value\n"
literal|"is the value the property is to be set to.\n"
literal|".PP\n"
literal|"\n"
literal|"Either spaces or tabs may be used to separate the name from the value.\n"
literal|".PP\n"
literal|".SH PROPERTIES\n"
literal|"Valid properties and their default values are:\n"
literal|"\n"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|man_page_path
specifier|static
specifier|const
name|gchar
modifier|*
name|man_page_path
init|=
literal|".PP\n"
literal|".SH PATH EXPANSION\n"
literal|"Strings of type PATH are expanded in a manner similar to\n"
literal|".BR bash (1).\n"
literal|"Specifically: tilde (~) is expanded to the user's home directory. Note that\n"
literal|"the bash feature of being able to refer to other user's home directories\n"
literal|"by writing ~userid/ is not valid in this file.\n"
literal|"\n"
literal|"${variable} is expanded to the current value of an environment variable.\n"
literal|"There are a few variables that are pre-defined:\n"
literal|".TP\n"
literal|".I gimp_dir\n"
literal|"The personal gimp directory which is set to the value of the environment\n"
literal|"variable GIMP2_DIRECTORY or to ~/@gimpdir@.\n"
literal|".TP\n"
literal|".I gimp_data_dir\n"
literal|"Base for paths to shareable data, which is set to the value of the\n"
literal|"environment variable GIMP2_DATADIR or to the compiled-in default value\n"
literal|"@gimpdatadir@.\n"
literal|".TP\n"
literal|".I gimp_plug_in_dir\n"
literal|"Base to paths for architecture-specific plugins and modules, which is set\n"
literal|"to the value of the environment variable GIMP2_PLUGINDIR or to the\n"
literal|"compiled-in default value @gimpplugindir@.\n"
literal|".TP\n"
literal|".I gimp_sysconf_dir\n"
literal|"Path to configuration files, which is set to the value of the environment\n"
literal|"variable GIMP2_SYSCONFDIR or to the compiled-in default value \n"
literal|"@gimpsysconfdir@.\n"
literal|"\n"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|man_page_footer
specifier|static
specifier|const
name|gchar
name|man_page_footer
index|[]
init|=
literal|".SH FILES\n"
literal|".TP\n"
literal|".I @gimpsysconfdir@/gimprc\n"
literal|"System-wide configuration file\n"
literal|".TP\n"
literal|".I \\fB$HOME\\fP/@gimpdir@/gimprc\n"
literal|"Per-user configuration file\n"
literal|"\n"
literal|".SH \"SEE ALSO\"\n"
literal|".BR gimp (1)\n"
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|dump_gimprc_manpage (GimpConfig * rc,GimpConfigWriter * writer,gint fd)
name|dump_gimprc_manpage
parameter_list|(
name|GimpConfig
modifier|*
name|rc
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gint
name|fd
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
name|guint
name|n_property_specs
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|man_page_header
argument_list|,
name|strlen
argument_list|(
name|man_page_header
argument_list|)
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
name|desc
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
if|if
condition|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_IGNORE
condition|)
continue|continue;
name|write
argument_list|(
name|fd
argument_list|,
literal|".TP\n"
argument_list|,
name|strlen
argument_list|(
literal|".TP\n"
argument_list|)
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
name|writer
argument_list|)
condition|)
block|{
name|write
argument_list|(
name|fd
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|desc
operator|=
name|dump_describe_param
argument_list|(
name|prop_spec
argument_list|)
expr_stmt|;
name|dump_with_linebreaks
argument_list|(
name|fd
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|man_page_path
argument_list|,
name|strlen
argument_list|(
name|man_page_path
argument_list|)
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|man_page_footer
argument_list|,
name|strlen
argument_list|(
name|man_page_footer
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|display_format_description
specifier|static
specifier|const
name|gchar
name|display_format_description
index|[]
init|=
literal|"This is a format string; certain % character sequences are recognised and "
literal|"expanded as follows:\n"
literal|"\n"
literal|"%%  literal percent sign\n"
literal|"%f  bare filename, or \"Untitled\"\n"
literal|"%F  full path to file, or \"Untitled\"\n"
literal|"%p  PDB image id\n"
literal|"%i  view instance number\n"
literal|"%t  image type (RGB, grayscale, indexed)\n"
literal|"%z  zoom factor as a percentage\n"
literal|"%s  source scale factor\n"
literal|"%d  destination scale factor\n"
literal|"%Dx expands to x if the image is dirty, the empty string otherwise\n"
literal|"%Cx expands to x if the image is clean, the empty string otherwise\n"
literal|"%B  expands to (modified) if the image is dirty, the empty string otherwise\n"
literal|"%A  expands to (clean) if the image is clean, the empty string otherwise\n"
literal|"%l  the number of layers\n"
literal|"%L  the number of layers (long form)\n"
literal|"%m  memory used by the image\n"
literal|"%n  the name of the active layer/channel\n"
literal|"%P  the PDB id of the active layer/channel\n"
literal|"%w  image width in pixels\n"
literal|"%W  image width in real-world units\n"
literal|"%h  image height in pixels\n"
literal|"%H  image height in real-world units\n"
literal|"%M  the image size expressed in megapixels\n"
literal|"%u  unit symbol\n"
literal|"%U  unit abbreviation\n\n"
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|dump_describe_param (GParamSpec * param_spec)
name|dump_describe_param
parameter_list|(
name|GParamSpec
modifier|*
name|param_spec
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|blurb
init|=
name|g_param_spec_get_blurb
argument_list|(
name|param_spec
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|values
init|=
name|NULL
decl_stmt|;
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
name|g_strdup_printf
argument_list|(
literal|"The %s property has no description."
argument_list|,
name|param_spec
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_RGB
argument_list|(
name|param_spec
argument_list|)
condition|)
block|{
if|if
condition|(
name|gimp_param_spec_rgb_has_alpha
argument_list|(
name|param_spec
argument_list|)
condition|)
name|values
operator|=
literal|"The color is specified in the form (color-rgba red green blue "
literal|"alpha) with channel values as floats in the range of 0.0 to 1.0."
expr_stmt|;
else|else
name|values
operator|=
literal|"The color is specified in the form (color-rgb red green blue) "
literal|"with channel values as floats in the range of 0.0 to 1.0."
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_MEMSIZE
argument_list|(
name|param_spec
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
name|GIMP_IS_PARAM_SPEC_CONFIG_PATH
argument_list|(
name|param_spec
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|gimp_param_spec_config_path_type
argument_list|(
name|param_spec
argument_list|)
condition|)
block|{
case|case
name|GIMP_CONFIG_PATH_FILE
case|:
name|values
operator|=
literal|"This is a single filename."
expr_stmt|;
break|break;
case|case
name|GIMP_CONFIG_PATH_FILE_LIST
case|:
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
literal|"This is a colon-separated list of files."
expr_stmt|;
break|break;
case|case
literal|';'
case|:
name|values
operator|=
literal|"This is a semicolon-separated list of files."
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"unhandled G_SEARCHPATH_SEPARATOR value"
argument_list|)
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|GIMP_CONFIG_PATH_DIR
case|:
name|values
operator|=
literal|"This is a single folder."
expr_stmt|;
break|break;
case|case
name|GIMP_CONFIG_PATH_DIR_LIST
case|:
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
literal|"This is a colon-separated list of folders to search."
expr_stmt|;
break|break;
case|case
literal|';'
case|:
name|values
operator|=
literal|"This is a semicolon-separated list of folders to search."
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"unhandled G_SEARCHPATH_SEPARATOR value"
argument_list|)
expr_stmt|;
break|break;
block|}
break|break;
block|}
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_PARAM_SPEC_UNIT
argument_list|(
name|param_spec
argument_list|)
condition|)
block|{
name|values
operator|=
literal|"The unit can be one inches, millimeters, points or picas plus "
literal|"those in your user units database."
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|param_spec
operator|->
name|value_type
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|)
condition|)
block|{
name|values
operator|=
literal|"This is a parameter list."
expr_stmt|;
block|}
else|else
block|{
switch|switch
condition|(
name|G_TYPE_FUNDAMENTAL
argument_list|(
name|param_spec
operator|->
name|value_type
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
comment|/* eek */
if|if
condition|(
name|strcmp
argument_list|(
name|g_param_spec_get_name
argument_list|(
name|param_spec
argument_list|)
argument_list|,
literal|"image-title-format"
argument_list|)
operator|&&
name|strcmp
argument_list|(
name|g_param_spec_get_name
argument_list|(
name|param_spec
argument_list|)
argument_list|,
literal|"image-status-format"
argument_list|)
condition|)
block|{
name|values
operator|=
literal|"This is a string value."
expr_stmt|;
block|}
else|else
block|{
name|values
operator|=
name|display_format_description
expr_stmt|;
block|}
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
name|param_spec
operator|->
name|value_type
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
name|param_spec
operator|->
name|value_type
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|blurb
argument_list|,
literal|""
argument_list|)
operator|==
literal|0
condition|)
return|return
name|g_strdup_printf
argument_list|(
literal|"%s"
argument_list|,
name|values
argument_list|)
return|;
else|else
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

begin_define
DECL|macro|LINE_LENGTH
define|#
directive|define
name|LINE_LENGTH
value|78
end_define

begin_function
specifier|static
name|void
DECL|function|dump_with_linebreaks (gint fd,const gchar * text)
name|dump_with_linebreaks
parameter_list|(
name|gint
name|fd
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|gint
name|len
init|=
name|strlen
argument_list|(
name|text
argument_list|)
decl_stmt|;
while|while
condition|(
name|len
operator|>
literal|0
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|t
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|space
decl_stmt|;
comment|/*  groff doesn't like lines to start with a single quote  */
if|if
condition|(
operator|*
name|text
operator|==
literal|'\''
condition|)
name|write
argument_list|(
name|fd
argument_list|,
literal|"\\&"
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  this represents a zero width space  */
for|for
control|(
name|t
operator|=
name|text
operator|,
name|i
operator|=
literal|0
operator|,
name|space
operator|=
literal|0
init|;
operator|*
name|t
operator|!=
literal|'\n'
operator|&&
operator|(
name|i
operator|<=
name|LINE_LENGTH
operator|||
name|space
operator|==
literal|0
operator|)
operator|&&
name|i
operator|<
name|len
condition|;
name|t
operator|++
operator|,
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_ascii_isspace
argument_list|(
operator|*
name|t
argument_list|)
condition|)
name|space
operator|=
name|i
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|>
name|LINE_LENGTH
operator|&&
name|space
operator|&&
operator|*
name|t
operator|!=
literal|'\n'
condition|)
name|i
operator|=
name|space
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|text
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|t
operator|==
literal|'\n'
condition|)
name|write
argument_list|(
name|fd
argument_list|,
literal|".br\n"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
name|text
operator|+=
name|i
expr_stmt|;
name|len
operator|-=
name|i
expr_stmt|;
block|}
block|}
end_function

end_unit


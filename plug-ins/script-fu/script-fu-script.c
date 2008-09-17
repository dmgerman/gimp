begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"script-fu-types.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-script.h"
end_include

begin_comment
comment|/*  *  Function definitions  */
end_comment

begin_function
name|SFScript
modifier|*
DECL|function|script_fu_script_new (const gchar * name,const gchar * menu_path,const gchar * blurb,const gchar * author,const gchar * copyright,const gchar * date,const gchar * image_types,gint n_args)
name|script_fu_script_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|,
name|gint
name|n_args
parameter_list|)
block|{
name|SFScript
modifier|*
name|script
decl_stmt|;
name|script
operator|=
name|g_slice_new0
argument_list|(
name|SFScript
argument_list|)
expr_stmt|;
name|script
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|script
operator|->
name|menu_path
operator|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|script
operator|->
name|blurb
operator|=
name|g_strdup
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|script
operator|->
name|author
operator|=
name|g_strdup
argument_list|(
name|author
argument_list|)
expr_stmt|;
name|script
operator|->
name|copyright
operator|=
name|g_strdup
argument_list|(
name|copyright
argument_list|)
expr_stmt|;
name|script
operator|->
name|date
operator|=
name|g_strdup
argument_list|(
name|date
argument_list|)
expr_stmt|;
name|script
operator|->
name|image_types
operator|=
name|g_strdup
argument_list|(
name|image_types
argument_list|)
expr_stmt|;
name|script
operator|->
name|n_args
operator|=
name|n_args
expr_stmt|;
name|script
operator|->
name|args
operator|=
name|g_new0
argument_list|(
name|SFArg
argument_list|,
name|script
operator|->
name|n_args
argument_list|)
expr_stmt|;
return|return
name|script
return|;
block|}
end_function

begin_function
name|void
DECL|function|script_fu_script_free (SFScript * script)
name|script_fu_script_free
parameter_list|(
name|SFScript
modifier|*
name|script
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|script
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|script
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|script
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|script
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|script
operator|->
name|author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|script
operator|->
name|copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|script
operator|->
name|date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|script
operator|->
name|image_types
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
name|script
operator|->
name|n_args
condition|;
name|i
operator|++
control|)
block|{
name|SFArg
modifier|*
name|arg
init|=
operator|&
name|script
operator|->
name|args
index|[
name|i
index|]
decl_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|label
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|arg
operator|->
name|type
condition|)
block|{
case|case
name|SF_IMAGE
case|:
case|case
name|SF_DRAWABLE
case|:
case|case
name|SF_LAYER
case|:
case|case
name|SF_CHANNEL
case|:
case|case
name|SF_VECTORS
case|:
case|case
name|SF_DISPLAY
case|:
case|case
name|SF_COLOR
case|:
case|case
name|SF_TOGGLE
case|:
break|break;
case|case
name|SF_VALUE
case|:
case|case
name|SF_STRING
case|:
case|case
name|SF_TEXT
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|value
operator|.
name|sfa_value
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_ADJUSTMENT
case|:
break|break;
case|case
name|SF_FILENAME
case|:
case|case
name|SF_DIRNAME
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_file
operator|.
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|value
operator|.
name|sfa_file
operator|.
name|filename
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_FONT
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_font
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|value
operator|.
name|sfa_font
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_PALETTE
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_palette
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|value
operator|.
name|sfa_palette
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_PATTERN
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_pattern
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|value
operator|.
name|sfa_pattern
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_GRADIENT
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_gradient
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|value
operator|.
name|sfa_gradient
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_BRUSH
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_brush
operator|.
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|arg
operator|->
name|value
operator|.
name|sfa_brush
operator|.
name|name
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_OPTION
case|:
name|g_slist_foreach
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_option
operator|.
name|list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_option
operator|.
name|list
argument_list|)
expr_stmt|;
break|break;
case|case
name|SF_ENUM
case|:
name|g_free
argument_list|(
name|arg
operator|->
name|default_value
operator|.
name|sfa_enum
operator|.
name|type_name
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_free
argument_list|(
name|script
operator|->
name|args
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|SFScript
argument_list|,
name|script
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|script_fu_script_install_proc (SFScript * script,GimpRunProc run_proc)
name|script_fu_script_install_proc
parameter_list|(
name|SFScript
modifier|*
name|script
parameter_list|,
name|GimpRunProc
name|run_proc
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|menu_path
init|=
name|NULL
decl_stmt|;
name|GimpParamDef
modifier|*
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|script
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|run_proc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* Allow scripts with no menus */
if|if
condition|(
name|strncmp
argument_list|(
name|script
operator|->
name|menu_path
argument_list|,
literal|"<None>"
argument_list|,
literal|6
argument_list|)
operator|!=
literal|0
condition|)
name|menu_path
operator|=
name|script
operator|->
name|menu_path
expr_stmt|;
name|args
operator|=
name|g_new0
argument_list|(
name|GimpParamDef
argument_list|,
name|script
operator|->
name|n_args
operator|+
literal|1
argument_list|)
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|name
operator|=
literal|"run-mode"
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|description
operator|=
literal|"Interactive, non-interactive"
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|script
operator|->
name|n_args
condition|;
name|i
operator|++
control|)
block|{
name|GimpPDBArgType
name|type
init|=
literal|0
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|script
operator|->
name|args
index|[
name|i
index|]
operator|.
name|type
condition|)
block|{
case|case
name|SF_IMAGE
case|:
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|name
operator|=
literal|"image"
expr_stmt|;
break|break;
case|case
name|SF_DRAWABLE
case|:
name|type
operator|=
name|GIMP_PDB_DRAWABLE
expr_stmt|;
name|name
operator|=
literal|"drawable"
expr_stmt|;
break|break;
case|case
name|SF_LAYER
case|:
name|type
operator|=
name|GIMP_PDB_LAYER
expr_stmt|;
name|name
operator|=
literal|"layer"
expr_stmt|;
break|break;
case|case
name|SF_CHANNEL
case|:
name|type
operator|=
name|GIMP_PDB_CHANNEL
expr_stmt|;
name|name
operator|=
literal|"channel"
expr_stmt|;
break|break;
case|case
name|SF_VECTORS
case|:
name|type
operator|=
name|GIMP_PDB_VECTORS
expr_stmt|;
name|name
operator|=
literal|"vectors"
expr_stmt|;
break|break;
case|case
name|SF_DISPLAY
case|:
name|type
operator|=
name|GIMP_PDB_DISPLAY
expr_stmt|;
name|name
operator|=
literal|"display"
expr_stmt|;
break|break;
case|case
name|SF_COLOR
case|:
name|type
operator|=
name|GIMP_PDB_COLOR
expr_stmt|;
name|name
operator|=
literal|"color"
expr_stmt|;
break|break;
case|case
name|SF_TOGGLE
case|:
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|name
operator|=
literal|"toggle"
expr_stmt|;
break|break;
case|case
name|SF_VALUE
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"value"
expr_stmt|;
break|break;
case|case
name|SF_STRING
case|:
case|case
name|SF_TEXT
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"string"
expr_stmt|;
break|break;
case|case
name|SF_ADJUSTMENT
case|:
name|type
operator|=
name|GIMP_PDB_FLOAT
expr_stmt|;
name|name
operator|=
literal|"value"
expr_stmt|;
break|break;
case|case
name|SF_FILENAME
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"filename"
expr_stmt|;
break|break;
case|case
name|SF_DIRNAME
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"dirname"
expr_stmt|;
break|break;
case|case
name|SF_FONT
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"font"
expr_stmt|;
break|break;
case|case
name|SF_PALETTE
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"palette"
expr_stmt|;
break|break;
case|case
name|SF_PATTERN
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"pattern"
expr_stmt|;
break|break;
case|case
name|SF_BRUSH
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"brush"
expr_stmt|;
break|break;
case|case
name|SF_GRADIENT
case|:
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|name
operator|=
literal|"gradient"
expr_stmt|;
break|break;
case|case
name|SF_OPTION
case|:
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|name
operator|=
literal|"option"
expr_stmt|;
break|break;
case|case
name|SF_ENUM
case|:
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|name
operator|=
literal|"enum"
expr_stmt|;
break|break;
block|}
name|args
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|type
operator|=
name|type
expr_stmt|;
name|args
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|name
expr_stmt|;
name|args
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|description
operator|=
name|script
operator|->
name|args
index|[
name|i
index|]
operator|.
name|label
expr_stmt|;
block|}
name|gimp_install_temp_proc
argument_list|(
name|script
operator|->
name|name
argument_list|,
name|script
operator|->
name|blurb
argument_list|,
literal|""
argument_list|,
name|script
operator|->
name|author
argument_list|,
name|script
operator|->
name|copyright
argument_list|,
name|script
operator|->
name|date
argument_list|,
name|menu_path
argument_list|,
name|script
operator|->
name|image_types
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|script
operator|->
name|n_args
operator|+
literal|1
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|,
name|run_proc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|script_fu_script_uninstall_proc (SFScript * script)
name|script_fu_script_uninstall_proc
parameter_list|(
name|SFScript
modifier|*
name|script
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|script
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_uninstall_temp_proc
argument_list|(
name|script
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


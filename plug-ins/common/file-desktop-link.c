begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * Desktop Entry Specification  * http://standards.freedesktop.org/desktop-entry-spec/latest/  */
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
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-desktop-link-load"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-desktop-link"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-desktop-link"
end_define

begin_typedef
DECL|typedef|Desktop
typedef|typedef
name|struct
name|_Desktop
name|Desktop
typedef|;
end_typedef

begin_typedef
DECL|typedef|DesktopClass
typedef|typedef
name|struct
name|_DesktopClass
name|DesktopClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Desktop
struct|struct
name|_Desktop
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_DesktopClass
struct|struct
name|_DesktopClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|DESKTOP_TYPE
define|#
directive|define
name|DESKTOP_TYPE
value|(desktop_get_type ())
end_define

begin_define
DECL|macro|DESKTOP
define|#
directive|define
name|DESKTOP
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), DESKTOP_TYPE, Desktop))
end_define

begin_decl_stmt
name|GType
name|desktop_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GList
modifier|*
name|desktop_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|desktop_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|desktop_load
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (Desktop,desktop,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Desktop
argument_list|,
argument|desktop
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|DESKTOP_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|desktop_class_init
parameter_list|(
name|DesktopClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|query_procedures
operator|=
name|desktop_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|desktop_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|desktop_init (Desktop * desktop)
name|desktop_init
parameter_list|(
name|Desktop
modifier|*
name|desktop
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|desktop_query_procedures (GimpPlugIn * plug_in)
name|desktop_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
return|return
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|g_strdup
argument_list|(
name|LOAD_PROC
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|desktop_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|desktop_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_load_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|desktop_load
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Desktop Link"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Follows a link to an image in a "
literal|".desktop file"
argument_list|,
literal|"Opens a .desktop file and if it is "
literal|"a link, it asks GIMP to open the "
literal|"file the link points to."
argument_list|,
name|LOAD_PROC
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2006"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"desktop"
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|desktop_load (GimpProcedure * procedure,GimpRunMode run_mode,GFile * file,const GimpValueArray * args,gpointer run_data)
name|desktop_load
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_values
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|image_ID
operator|=
name|load_image
argument_list|(
name|file
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
name|return_values
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_values
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|return_values
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|return_values
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (GFile * file,GimpRunMode run_mode,GError ** load_error)
name|load_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|load_error
parameter_list|)
block|{
name|GKeyFile
modifier|*
name|key_file
init|=
name|g_key_file_new
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|value
init|=
name|NULL
decl_stmt|;
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|filename
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_key_file_load_from_file
argument_list|(
name|key_file
argument_list|,
name|filename
argument_list|,
name|G_KEY_FILE_NONE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
goto|goto
name|out
goto|;
name|group
operator|=
name|g_key_file_get_start_group
argument_list|(
name|key_file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|group
operator|||
name|strcmp
argument_list|(
name|group
argument_list|,
name|G_KEY_FILE_DESKTOP_GROUP
argument_list|)
operator|!=
literal|0
condition|)
goto|goto
name|out
goto|;
name|value
operator|=
name|g_key_file_get_value
argument_list|(
name|key_file
argument_list|,
name|group
argument_list|,
name|G_KEY_FILE_DESKTOP_KEY_TYPE
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|value
operator|||
name|strcmp
argument_list|(
name|value
argument_list|,
name|G_KEY_FILE_DESKTOP_TYPE_LINK
argument_list|)
operator|!=
literal|0
condition|)
goto|goto
name|out
goto|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|value
operator|=
name|g_key_file_get_value
argument_list|(
name|key_file
argument_list|,
name|group
argument_list|,
name|G_KEY_FILE_DESKTOP_KEY_URL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|run_mode
argument_list|,
name|value
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|out
label|:
if|if
condition|(
name|error
condition|)
block|{
name|g_set_error
argument_list|(
name|load_error
argument_list|,
name|error
operator|->
name|domain
argument_list|,
name|error
operator|->
name|code
argument_list|,
name|_
argument_list|(
literal|"Error loading desktop file '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
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
block|}
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_key_file_free
argument_list|(
name|key_file
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

end_unit


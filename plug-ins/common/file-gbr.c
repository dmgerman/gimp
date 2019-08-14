begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * gbr plug-in version 1.00  * Loads/exports version 2 GIMP .gbr files, by Tim Newsome<drz@frody.bloke.com>  * Some bits stolen from the .99.7 source tree.  *  * Added in GBR version 1 support after learning that there wasn't a  * tool to read them.  * July 6, 1998 by Seth Burgess<sjburges@gimp.org>  *  * Dec 17, 2000  * Load and save GIMP brushes in GRAY or RGBA.  jtl + neo  *  *  * TODO: Give some better error reporting on not opening files/bad headers  *       etc.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-gbr-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-gbr"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-gbr"
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b4ef4fa0108
block|{
DECL|member|description
name|gchar
name|description
index|[
literal|256
index|]
decl_stmt|;
DECL|member|spacing
name|gint
name|spacing
decl_stmt|;
DECL|typedef|BrushInfo
block|}
name|BrushInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|Gbr
typedef|typedef
name|struct
name|_Gbr
name|Gbr
typedef|;
end_typedef

begin_typedef
DECL|typedef|GbrClass
typedef|typedef
name|struct
name|_GbrClass
name|GbrClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Gbr
struct|struct
name|_Gbr
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GbrClass
struct|struct
name|_GbrClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GBR_TYPE
define|#
directive|define
name|GBR_TYPE
value|(gbr_get_type ())
end_define

begin_define
DECL|macro|GBR
define|#
directive|define
name|GBR
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GBR_TYPE, Gbr))
end_define

begin_decl_stmt
name|GType
name|gbr_get_type
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
name|gbr_query_procedures
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
name|gbr_create_procedure
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
name|gbr_save
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|gboolean
name|save_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|entry_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|Gbr
argument_list|,
argument|gbr
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|GBR_TYPE
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|BrushInfo
name|info
init|=
block|{
literal|"GIMP Brush"
block|,
literal|10
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gbr_class_init (GbrClass * klass)
name|gbr_class_init
parameter_list|(
name|GbrClass
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
name|gbr_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|gbr_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gbr_init (Gbr * gbr)
name|gbr_init
parameter_list|(
name|Gbr
modifier|*
name|gbr
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gbr_query_procedures (GimpPlugIn * plug_in)
name|gbr_query_procedures
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
name|SAVE_PROC
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|gbr_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|gbr_create_procedure
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
name|SAVE_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_save_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|gbr_save
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_image_types
argument_list|(
name|procedure
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"GIMP brush"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_icon_name
argument_list|(
name|procedure
argument_list|,
name|GIMP_ICON_BRUSH
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Exports files in the GIMP brush "
literal|"file format"
argument_list|,
literal|"Exports files in the GIMP brush "
literal|"file format"
argument_list|,
name|SAVE_PROC
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, "
literal|"Sven Neumann"
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, "
literal|"Sven Neumann"
argument_list|,
literal|"1997-2000"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/x-gimp-gbr"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gbr"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_handles_remote
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"spacing"
argument_list|,
literal|"Spacing"
argument_list|,
literal|"Spacing of the brush"
argument_list|,
literal|1
argument_list|,
literal|1000
argument_list|,
literal|10
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_STRING
argument_list|(
name|procedure
argument_list|,
literal|"description"
argument_list|,
literal|"Description"
argument_list|,
literal|"Short description of the brush"
argument_list|,
literal|"GIMP Brush"
argument_list|,
name|GIMP_PARAM_READWRITE
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
DECL|function|gbr_save (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,GFile * file,const GimpValueArray * args,gpointer run_data)
name|gbr_save
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|GimpImage
modifier|*
name|orig_image
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|orig_image
operator|=
name|image
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|image
argument_list|,
operator|&
name|drawable
argument_list|,
literal|"GBR"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_CANCEL
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_CANCEL
argument_list|,
name|NULL
argument_list|)
return|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_image_get_parasite
argument_list|(
name|orig_image
argument_list|,
literal|"gimp-brush-name"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|g_strlcpy
argument_list|(
name|info
operator|.
name|description
argument_list|,
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|MIN
argument_list|(
sizeof|sizeof
argument_list|(
name|info
operator|.
name|description
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|name
init|=
name|g_path_get_basename
argument_list|(
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_str_has_suffix
argument_list|(
name|name
argument_list|,
literal|".gbr"
argument_list|)
condition|)
name|name
index|[
name|strlen
argument_list|(
name|name
argument_list|)
operator|-
literal|4
index|]
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
name|g_strlcpy
argument_list|(
name|info
operator|.
name|description
argument_list|,
name|name
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|.
name|description
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
if|if
condition|(
operator|!
name|save_dialog
argument_list|()
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
goto|goto
name|out
goto|;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|info
operator|.
name|spacing
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_strlcpy
argument_list|(
name|info
operator|.
name|description
argument_list|,
name|GIMP_VALUES_GET_STRING
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|.
name|description
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|GimpValueArray
modifier|*
name|save_retvals
decl_stmt|;
name|gchar
modifier|*
name|uri
init|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
decl_stmt|;
name|save_retvals
operator|=
name|gimp_pdb_run_procedure
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"file-gbr-save-internal"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|gimp_item_get_id
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|uri
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|uri
argument_list|,
name|G_TYPE_INT
argument_list|,
name|info
operator|.
name|spacing
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|info
operator|.
name|description
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|save_retvals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|info
argument_list|,
sizeof|sizeof
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
operator|&
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Running procedure 'file-gbr-save-internal' "
literal|"failed: %s"
argument_list|,
name|gimp_pdb_get_last_error
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|save_retvals
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|strlen
argument_list|(
name|info
operator|.
name|description
argument_list|)
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-brush-name"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|info
operator|.
name|description
argument_list|)
operator|+
literal|1
argument_list|,
name|info
operator|.
name|description
argument_list|)
expr_stmt|;
name|gimp_image_attach_parasite
argument_list|(
name|orig_image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_detach_parasite
argument_list|(
name|orig_image
argument_list|,
literal|"gimp-brush-name"
argument_list|)
expr_stmt|;
block|}
name|out
label|:
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_EXPORT
condition|)
name|gimp_image_delete
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|status
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|save_dialog (void)
name|save_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|dialog
operator|=
name|gimp_export_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Brush"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|SAVE_PROC
argument_list|)
expr_stmt|;
comment|/* The main grid */
name|grid
operator|=
name|gtk_grid_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_grid_set_row_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_export_dialog_get_content_area
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|grid
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|grid
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|info
operator|.
name|description
argument_list|)
expr_stmt|;
name|gimp_grid_attach_aligned
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Description:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|entry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|entry_callback
argument_list|)
argument_list|,
name|info
operator|.
name|description
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gtk_adjustment_new
argument_list|(
name|info
operator|.
name|spacing
argument_list|,
literal|1
argument_list|,
literal|1000
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_grid_attach_aligned
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Spacing:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|info
operator|.
name|spacing
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|entry_callback (GtkWidget * widget,gpointer data)
name|entry_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_strlcpy
argument_list|(
name|info
operator|.
name|description
argument_list|,
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|info
operator|.
name|description
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


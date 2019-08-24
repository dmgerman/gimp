begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* bmp.c                                          */
end_comment

begin_comment
comment|/* Version 0.52                                   */
end_comment

begin_comment
comment|/* This is a File input and output filter for the */
end_comment

begin_comment
comment|/* Gimp. It loads and saves images in windows(TM) */
end_comment

begin_comment
comment|/* bitmap format.                                 */
end_comment

begin_comment
comment|/* Some Parts that deal with the interaction with */
end_comment

begin_comment
comment|/* GIMP are taken from the GIF plugin by          */
end_comment

begin_comment
comment|/* Peter Mattis& Spencer Kimball and from the    */
end_comment

begin_comment
comment|/* PCX plugin by Francisco Bustamante.            */
end_comment

begin_comment
comment|/*                                                */
end_comment

begin_comment
comment|/* Alexander.Schulz@stud.uni-karlsruhe.de         */
end_comment

begin_comment
comment|/* Changes:   28.11.1997 Noninteractive operation */
end_comment

begin_comment
comment|/*            16.03.1998 Endian-independent!!     */
end_comment

begin_comment
comment|/*            21.03.1998 Little Bug-fix           */
end_comment

begin_comment
comment|/*            06.04.1998 Bugfix in Padding        */
end_comment

begin_comment
comment|/*            11.04.1998 Arch. cleanup (-Wall)    */
end_comment

begin_comment
comment|/*                       Parses gtkrc             */
end_comment

begin_comment
comment|/*            14.04.1998 Another Bug in Padding   */
end_comment

begin_comment
comment|/*            28.04.1998 RLE-Encoding rewritten   */
end_comment

begin_comment
comment|/*            29.10.1998 Changes by Tor Lillqvist */
end_comment

begin_comment
comment|/*<tml@iki.fi> to support  */
end_comment

begin_comment
comment|/*                       16 and 32 bit images     */
end_comment

begin_comment
comment|/*            28.11.1998 Bug in RLE-read-padding  */
end_comment

begin_comment
comment|/*                       fixed.                   */
end_comment

begin_comment
comment|/*            19.12.1999 Resolution support added */
end_comment

begin_comment
comment|/*            06.05.2000 Overhaul for 16&24-bit   */
end_comment

begin_comment
comment|/*                       plus better OS/2 code    */
end_comment

begin_comment
comment|/*                       by njl195@zepler.org.uk  */
end_comment

begin_comment
comment|/*            29.06.2006 Full support for 16/32   */
end_comment

begin_comment
comment|/*                       bits bitmaps and support */
end_comment

begin_comment
comment|/*                       for alpha channel        */
end_comment

begin_comment
comment|/*                       by p.filiciak@zax.pl     */
end_comment

begin_comment
comment|/*  * GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  * ----------------------------------------------------------------------------  */
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
file|"bmp.h"
end_include

begin_include
include|#
directive|include
file|"bmp-load.h"
end_include

begin_include
include|#
directive|include
file|"bmp-save.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
DECL|typedef|Bmp
typedef|typedef
name|struct
name|_Bmp
name|Bmp
typedef|;
end_typedef

begin_typedef
DECL|typedef|BmpClass
typedef|typedef
name|struct
name|_BmpClass
name|BmpClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Bmp
struct|struct
name|_Bmp
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_BmpClass
struct|struct
name|_BmpClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|BMP_TYPE
define|#
directive|define
name|BMP_TYPE
value|(bmp_get_type ())
end_define

begin_define
DECL|macro|BMP
define|#
directive|define
name|BMP
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), BMP_TYPE, Bmp))
end_define

begin_decl_stmt
name|GType
name|bmp_get_type
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
name|bmp_query_procedures
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
name|bmp_create_procedure
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
name|bmp_load
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
name|GimpValueArray
modifier|*
name|bmp_save
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

begin_macro
DECL|function|G_DEFINE_TYPE (Bmp,bmp,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Bmp
argument_list|,
argument|bmp
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|BMP_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|bmp_class_init
parameter_list|(
name|BmpClass
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
name|bmp_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|bmp_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|bmp_init (Bmp * bmp)
name|bmp_init
parameter_list|(
name|Bmp
modifier|*
name|bmp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|bmp_query_procedures (GimpPlugIn * plug_in)
name|bmp_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|LOAD_PROC
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|SAVE_PROC
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|bmp_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|bmp_create_procedure
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
name|bmp_load
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
literal|"Windows BMP image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Loads files of Windows BMP file format"
argument_list|,
literal|"Loads files of Windows BMP file format"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/bmp"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"bmp"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_magics
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"0,string,BM"
argument_list|)
expr_stmt|;
block|}
elseif|else
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
name|bmp_save
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
literal|"INDEXED, GRAY, RGB*"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Windows BMP image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Saves files in Windows BMP file format"
argument_list|,
literal|"Saves files in Windows BMP file format"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"Alexander Schulz"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/bmp"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"bmp"
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
DECL|function|bmp_load (GimpProcedure * procedure,GimpRunMode run_mode,GFile * file,const GimpValueArray * args,gpointer run_data)
name|bmp_load
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
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|filename
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
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|image
operator|=
name|load_image
argument_list|(
name|filename
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|error
argument_list|)
return|;
name|return_vals
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
name|GIMP_VALUES_SET_IMAGE
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|,
name|image
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|bmp_save (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,GFile * file,const GimpValueArray * args,gpointer run_data)
name|bmp_save
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
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
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
literal|"BMP"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
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
break|break;
default|default:
break|break;
block|}
name|status
operator|=
name|save_image
argument_list|(
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
name|image
argument_list|,
name|drawable
argument_list|,
name|run_mode
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
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

end_unit


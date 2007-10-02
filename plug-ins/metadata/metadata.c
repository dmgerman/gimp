begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* metadata.c - main() for the metadata editor  *  * Copyright (C) 2004-2005, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<stdio.h>
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

begin_include
include|#
directive|include
file|"metadata.h"
end_include

begin_include
include|#
directive|include
file|"xmp-encode.h"
end_include

begin_comment
comment|/* FIXME: uncomment when these are working #include "interface.h" #include "exif-decode.h" #include "exif-encode.h" #include "iptc-decode.h" */
end_comment

begin_define
DECL|macro|METADATA_PARASITE
define|#
directive|define
name|METADATA_PARASITE
value|"gimp-metadata"
end_define

begin_define
DECL|macro|METADATA_MARKER
define|#
directive|define
name|METADATA_MARKER
value|"GIMP_XMP_1"
end_define

begin_define
DECL|macro|METADATA_MARKER_LEN
define|#
directive|define
name|METADATA_MARKER_LEN
value|(sizeof (METADATA_MARKER) - 1)
end_define

begin_comment
comment|/* prototypes of local functions */
end_comment

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* local variables */
end_comment

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* local functions */
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* FIXME: uncomment when these are working   static const GimpParamDef editor_args[] =   {     { GIMP_PDB_INT32,       "run-mode",  "Interactive, non-interactive" },     { GIMP_PDB_IMAGE,       "image",     "Input image"                  },     { GIMP_PDB_DRAWABLE,    "drawable",  "Input drawable (unused)"      }   }; */
specifier|static
specifier|const
name|GimpParamDef
name|decode_xmp_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"xmp"
block|,
literal|"XMP packet"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|encode_xmp_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|encode_xmp_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"xmp"
block|,
literal|"XMP packet"
block|}
block|}
decl_stmt|;
comment|/* FIXME: uncomment when these are working   static const GimpParamDef decode_exif_args[] =   {     { GIMP_PDB_IMAGE,       "image",     "Input image"                  },     { GIMP_PDB_INT32,       "exif-size", "size of the EXIF block"       },     { GIMP_PDB_INT8ARRAY,   "exif",      "EXIF block"                   }   };    static const GimpParamDef encode_exif_args[] =   {     { GIMP_PDB_IMAGE,       "image",     "Input image"                  }   };   static const GimpParamDef encode_exif_return_vals[] =   {     { GIMP_PDB_INT32,       "exif-size", "size of the EXIF block"       },     { GIMP_PDB_INT8ARRAY,   "exif",      "EXIF block"                   }   }; */
specifier|static
specifier|const
name|GimpParamDef
name|get_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"schema"
block|,
literal|"XMP schema prefix or URI"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"property"
block|,
literal|"XMP property name"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|get_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"type"
block|,
literal|"XMP property type"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num-vals"
block|,
literal|"number of values"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"vals"
block|,
literal|"XMP property values"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|set_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"schema"
block|,
literal|"XMP schema prefix or URI"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"property"
block|,
literal|"XMP property name"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"type"
block|,
literal|"XMP property type"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num-vals"
block|,
literal|"number of values"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"vals"
block|,
literal|"XMP property values"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|get_simple_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"schema"
block|,
literal|"XMP schema prefix or URI"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"property"
block|,
literal|"XMP property name"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|get_simple_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"value"
block|,
literal|"XMP property value"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|set_simple_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"schema"
block|,
literal|"XMP schema prefix or URI"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"property"
block|,
literal|"XMP property name"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"value"
block|,
literal|"XMP property value"
block|}
block|}
decl_stmt|;
comment|/* FIXME: uncomment when these are working   static const GimpParamDef delete_args[] =   {     { GIMP_PDB_IMAGE,       "image",     "Input image"                  },     { GIMP_PDB_STRING,      "schema",    "XMP schema prefix or URI"     },     { GIMP_PDB_STRING,      "property",  "XMP property name"            }   };    static const GimpParamDef add_schema_args[] =   {     { GIMP_PDB_IMAGE,       "image",     "Input image"                  },     { GIMP_PDB_STRING,      "prefix",    "XMP schema prefix"            },     { GIMP_PDB_STRING,      "uri",       "XMP schema URI"               }   }; */
specifier|static
specifier|const
name|GimpParamDef
name|import_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the XMP file to import"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|export_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the XMP packet in"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"overwrite"
block|,
literal|"Overwrite existing file: { FALSE (0), TRUE (1) }"
block|}
block|}
decl_stmt|;
comment|/* FIXME: uncomment when these are working   gimp_install_procedure (EDITOR_PROC, 			  N_("View and edit metadata (EXIF, IPTC, XMP)"),                           "View and edit metadata information attached to the "                           "current image.  This can include EXIF, IPTC and/or "                           "XMP information.  Some or all of this metadata "                           "will be saved in the file, depending on the output "                           "file format.", 			  "RaphaÃ«l Quinet<raphael@gimp.org>", 			  "RaphaÃ«l Quinet<raphael@gimp.org>", 			  "2004-2005",                           N_("Propert_ies"),                           "RGB*, INDEXED*, GRAY*",                           GIMP_PLUGIN,                           G_N_ELEMENTS (editor_args), 0,                           editor_args, NULL);    gimp_plugin_menu_register (EDITOR_PROC, "<Image>/File/Info");   gimp_plugin_icon_register (EDITOR_PROC, GIMP_ICON_TYPE_STOCK_ID,  */
name|gimp_install_procedure
argument_list|(
name|DECODE_XMP_PROC
argument_list|,
literal|"Decode an XMP packet"
argument_list|,
literal|"Parse an XMP packet and merge the results with "
literal|"any metadata already attached to the image.  This "
literal|"should be used when an XMP packet is read from an "
literal|"image file."
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|decode_xmp_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|decode_xmp_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|ENCODE_XMP_PROC
argument_list|,
literal|"Encode metadata into an XMP packet"
argument_list|,
literal|"Generate an XMP packet from the metadata "
literal|"information attached to the image.  The new XMP "
literal|"packet can then be saved into a file."
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|encode_xmp_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|encode_xmp_return_vals
argument_list|)
argument_list|,
name|encode_xmp_args
argument_list|,
name|encode_xmp_return_vals
argument_list|)
expr_stmt|;
comment|/* FIXME: uncomment when these are working   gimp_install_procedure (DECODE_EXIF_PROC, 			  "Decode an EXIF block",                           "Parse an EXIF block and merge the results with "                           "any metadata already attached to the image.  This "                           "should be used when an EXIF block is read from an "                           "image file.", 			  "RaphaÃ«l Quinet<raphael@gimp.org>", 			  "RaphaÃ«l Quinet<raphael@gimp.org>", 			  "2005",                           NULL,                           NULL,                           GIMP_PLUGIN,                           G_N_ELEMENTS (decode_exif_args), 0,                           decode_exif_args, NULL);    gimp_install_procedure (ENCODE_EXIF_PROC, 			  "Encode metadata into an EXIF block",                           "Generate an EXIF block from the metadata "                           "information attached to the image.  The new EXIF "                           "block can then be saved into a file.", 			  "RaphaÃ«l Quinet<raphael@gimp.org>", 			  "RaphaÃ«l Quinet<raphael@gimp.org>", 			  "2005",                           NULL,                           NULL,                           GIMP_PLUGIN,                           G_N_ELEMENTS (encode_exif_args),                           G_N_ELEMENTS (encode_exif_return_vals),                           encode_exif_args, encode_exif_return_vals); */
name|gimp_install_procedure
argument_list|(
name|GET_PROC
argument_list|,
literal|"Retrieve the values of an XMP property"
argument_list|,
literal|"Retrieve the list of values associated with "
literal|"an XMP property."
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|get_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|get_return_vals
argument_list|)
argument_list|,
name|get_args
argument_list|,
name|get_return_vals
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SET_PROC
argument_list|,
literal|"Set the values of an XMP property"
argument_list|,
literal|"Set the list of values associated with "
literal|"an XMP property.  If a property with the same "
literal|"name already exists, it will be replaced."
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|set_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|set_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|GET_SIMPLE_PROC
argument_list|,
literal|"Retrieve the value of an XMP property"
argument_list|,
literal|"Retrieve value associated with a scalar XMP "
literal|"property.  This can only be done for simple "
literal|"property types such as text or integers.  "
literal|"Structured types must be retrieved with "
literal|"plug_in_metadata_get()."
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|get_simple_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|get_simple_return_vals
argument_list|)
argument_list|,
name|get_simple_args
argument_list|,
name|get_simple_return_vals
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SET_SIMPLE_PROC
argument_list|,
literal|"Set the value of an XMP property"
argument_list|,
literal|"Set the value of a scalar XMP property.  This "
literal|"can only be done for simple property types such "
literal|"as text or integers.  Structured types need to "
literal|"be set with plug_in_metadata_set()."
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|set_simple_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|set_simple_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|IMPORT_PROC
argument_list|,
literal|"Import XMP from a file into the current image"
argument_list|,
literal|"Load an XMP packet from a file and import it into "
literal|"the current image.  This can be used to add a "
literal|"license statement or some other predefined "
literal|"metadata to an image"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|import_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|import_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|EXPORT_PROC
argument_list|,
literal|"Export XMP from the current image to a file"
argument_list|,
literal|"Export the metadata associated with the current "
literal|"image into a file.  The metadata will be saved as "
literal|"an XMP packet.  If overwrite is TRUE, then any "
literal|"existing file will be overwritten without warning. "
literal|"If overwrite is FALSE, then an error will occur if "
literal|"the file already exists."
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"RaphaÃ«l Quinet<raphael@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|export_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|export_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|4
index|]
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|XMPModel
modifier|*
name|xmp_model
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
decl_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|EDITOR_PROC
argument_list|)
condition|)
name|image_ID
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
else|else
name|image_ID
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
name|xmp_model
operator|=
name|xmp_model_new
argument_list|()
expr_stmt|;
comment|/* if there is already a metadata parasite, load it */
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|image_ID
argument_list|,
name|METADATA_PARASITE
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
operator|!
name|strncmp
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|METADATA_MARKER
argument_list|,
name|METADATA_MARKER_LEN
argument_list|)
operator|||
operator|!
name|xmp_model_parse_buffer
argument_list|(
name|xmp_model
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
operator|+
name|METADATA_MARKER_LEN
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
operator|-
name|METADATA_MARKER_LEN
argument_list|,
name|FALSE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Metadata parasite seems to be corrupt"
argument_list|)
expr_stmt|;
comment|/* continue anyway, we will attach a clean parasite later */
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
comment|/* If we have no metadata yet, try to find an XMP packet in the file    * (but ignore errors if nothing is found).    *    * FIXME: This is a workaround until all file plug-ins do the right    * thing when loading their files.    */
if|if
condition|(
name|xmp_model_is_empty
argument_list|(
name|xmp_model
argument_list|)
operator|&&
operator|!
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|DECODE_XMP_PROC
argument_list|)
condition|)
block|{
specifier|const
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
name|filename
operator|=
name|gimp_image_get_filename
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
operator|!=
name|NULL
condition|)
if|if
condition|(
name|xmp_model_parse_file
argument_list|(
name|xmp_model
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
condition|)
comment|/* g_message ("XMP loaded from file '%s'\n", filename) */
empty_stmt|;
block|}
comment|/* Now check what we are supposed to do */
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|DECODE_XMP_PROC
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|buffer
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|buffer
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
if|if
condition|(
operator|!
name|xmp_model_parse_buffer
argument_list|(
name|xmp_model
argument_list|,
name|buffer
argument_list|,
name|strlen
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|FALSE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|ENCODE_XMP_PROC
argument_list|)
condition|)
block|{
comment|/* done below together with the parasite */
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|GET_PROC
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Not implemented yet (GET_PROC)\n"
argument_list|)
expr_stmt|;
comment|/* FIXME */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|SET_PROC
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Not implemented yet (SET_PROC)\n"
argument_list|)
expr_stmt|;
comment|/* FIXME */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|GET_SIMPLE_PROC
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|schema_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|property_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
name|schema_name
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
name|property_name
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
name|value
operator|=
name|xmp_model_get_scalar_property
argument_list|(
name|xmp_model
argument_list|,
name|schema_name
argument_list|,
name|property_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
else|else
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|SET_SIMPLE_PROC
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|schema_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|property_name
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|property_value
decl_stmt|;
name|schema_name
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
name|property_name
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
name|property_value
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
if|if
condition|(
operator|!
name|xmp_model_set_scalar_property
argument_list|(
name|xmp_model
argument_list|,
name|schema_name
argument_list|,
name|property_name
argument_list|,
name|property_value
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|IMPORT_PROC
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|buffer
decl_stmt|;
name|gsize
name|buffer_length
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|filename
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_get_contents
argument_list|(
name|filename
argument_list|,
operator|&
name|buffer
argument_list|,
operator|&
name|buffer_length
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|xmp_model_parse_buffer
argument_list|(
name|xmp_model
argument_list|,
name|buffer
argument_list|,
name|buffer_length
argument_list|,
name|TRUE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buffer
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
name|EXPORT_PROC
argument_list|)
condition|)
block|{
comment|/* FIXME: this is easy to implement, but the first thing to do is */
comment|/* to improve the code of export_dialog_response() in interface.c */
name|g_printerr
argument_list|(
literal|"Not implemented yet (EXPORT_PROC)\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|EDITOR_PROC
argument_list|)
condition|)
block|{
comment|/* FIXME: uncomment when these are working       GimpRunMode run_mode;        run_mode = param[0].data.d_int32;       if (run_mode == GIMP_RUN_INTERACTIVE)         {           if (! metadata_dialog (image_ID, xmp_model))             status = GIMP_PDB_CANCEL;         }         */
name|g_printerr
argument_list|(
literal|"Not implemented yet (EDITOR_PROC)\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|GString
modifier|*
name|buffer
decl_stmt|;
comment|/* Generate the updated parasite and attach it to the image */
name|buffer
operator|=
name|g_string_new
argument_list|(
name|METADATA_MARKER
argument_list|)
expr_stmt|;
name|xmp_generate_packet
argument_list|(
name|xmp_model
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|METADATA_PARASITE
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|buffer
operator|->
name|len
argument_list|,
operator|(
name|gpointer
operator|)
name|buffer
operator|->
name|str
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image_ID
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|ENCODE_XMP_PROC
argument_list|)
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|g_strdup
argument_list|(
name|buffer
operator|->
name|str
operator|+
name|METADATA_MARKER_LEN
argument_list|)
expr_stmt|;
block|}
name|g_string_free
argument_list|(
name|buffer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|xmp_model_free
argument_list|(
name|xmp_model
argument_list|)
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

end_unit


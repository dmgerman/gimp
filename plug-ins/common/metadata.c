begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * metadata.c  * Copyright (C) 2013 Hartmut Kuhse  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gexiv2/gexiv2.h>
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
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-metadata-editor"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"metadata"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-metadata"
end_define

begin_define
DECL|macro|EXIF_PREFIX
define|#
directive|define
name|EXIF_PREFIX
value|"Exif."
end_define

begin_define
DECL|macro|IPTC_PREFIX
define|#
directive|define
name|IPTC_PREFIX
value|"Iptc."
end_define

begin_define
DECL|macro|XMP_PREFIX
define|#
directive|define
name|XMP_PREFIX
value|"Xmp."
end_define

begin_enum
enum|enum
DECL|enum|__anon29fd062a0103
block|{
DECL|enumerator|C_XMP_TAG
name|C_XMP_TAG
init|=
literal|0
block|,
DECL|enumerator|C_XMP_VALUE
name|C_XMP_VALUE
block|,
DECL|enumerator|NUM_XMP_COLS
name|NUM_XMP_COLS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29fd062a0203
block|{
DECL|enumerator|C_EXIF_TAG
name|C_EXIF_TAG
init|=
literal|0
block|,
DECL|enumerator|C_EXIF_VALUE
name|C_EXIF_VALUE
block|,
DECL|enumerator|NUM_EXIF_COLS
name|NUM_EXIF_COLS
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29fd062a0308
block|{
DECL|member|tag
name|gchar
modifier|*
name|tag
decl_stmt|;
DECL|member|mode
name|gchar
modifier|*
name|mode
decl_stmt|;
DECL|typedef|iptc_tag
block|}
name|iptc_tag
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
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

begin_function_decl
specifier|static
name|gboolean
name|metadata_dialog
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|GExiv2Metadata
modifier|*
name|metadata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|metadata_dialog_set_metadata
parameter_list|(
name|GExiv2Metadata
modifier|*
name|metadata
parameter_list|,
name|GtkBuilder
modifier|*
name|builder
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|metadata_dialog_iptc_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GtkBuilder
modifier|*
name|builder
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

begin_decl_stmt
DECL|variable|iptc_tags
specifier|static
specifier|const
name|iptc_tag
specifier|const
name|iptc_tags
index|[]
init|=
block|{
block|{
literal|"Iptc.Application2.Byline"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.BylineTitle"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.Caption"
block|,
literal|"multi"
block|}
block|,
block|{
literal|"Iptc.Application2.Category"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.City"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.Copyright"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.CountryName"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.Credit"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.Headline"
block|,
literal|"multi"
block|}
block|,
block|{
literal|"Iptc.Application2.Keywords"
block|,
literal|"multi"
block|}
block|,
block|{
literal|"Iptc.Application2.ObjectName"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.ProvinceState"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.Source"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.SpecialInstructions"
block|,
literal|"multi"
block|}
block|,
block|{
literal|"Iptc.Application2.SubLocation"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.SuppCategory"
block|,
literal|"multi"
block|}
block|,
block|{
literal|"Iptc.Application2.TransmissionReference"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.Urgency"
block|,
literal|"single"
block|}
block|,
block|{
literal|"Iptc.Application2.Writer"
block|,
literal|"single"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  functions  */
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
specifier|static
specifier|const
name|GimpParamDef
name|metadata_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Run mode { RUN-INTERACTIVE (0) }"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"View and edit metadata (Exif, IPTC, XMP)"
argument_list|)
argument_list|,
literal|"View and edit metadata information attached to the "
literal|"current image.  This can include Exif, IPTC and/or "
literal|"XMP information.  Some or all of this metadata "
literal|"will be saved in the file, depending on the output "
literal|"file format."
argument_list|,
literal|"Hartmut Kuhse, Michael Natterer"
argument_list|,
literal|"Hartmut Kuhse, Michael Natterer"
argument_list|,
literal|"2013"
argument_list|,
name|N_
argument_list|(
literal|"Image Metadata"
argument_list|)
argument_list|,
literal|"*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|metadata_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|metadata_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Image"
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
literal|1
index|]
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
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
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
condition|)
block|{
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|gint32
name|image_ID
init|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
decl_stmt|;
name|metadata
operator|=
name|gimp_image_get_metadata
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|metadata_dialog
argument_list|(
name|image_ID
argument_list|,
name|metadata
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"This image has no metadata attached to it."
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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

begin_function
specifier|static
name|gboolean
DECL|function|metadata_dialog (gint32 image_id,GExiv2Metadata * metadata)
name|metadata_dialog
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|GExiv2Metadata
modifier|*
name|metadata
parameter_list|)
block|{
name|GtkBuilder
modifier|*
name|builder
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|metadata_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|content_area
decl_stmt|;
name|GObject
modifier|*
name|write_button
decl_stmt|;
name|gchar
modifier|*
name|ui_file
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|builder
operator|=
name|gtk_builder_new
argument_list|()
expr_stmt|;
name|ui_file
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"ui"
argument_list|,
literal|"plug-ins"
argument_list|,
literal|"plug-in-metadata.ui"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_builder_add_from_file
argument_list|(
name|builder
argument_list|,
name|ui_file
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Error occured while loading UI file!\n"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"Message: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ui_file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|builder
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_free
argument_list|(
name|ui_file
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_image_get_name
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|title
operator|=
name|g_strdup_printf
argument_list|(
literal|"Metadata: %s"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|title
argument_list|,
literal|"gimp-metadata-dialog"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|content_area
operator|=
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|metadata_vbox
operator|=
name|GTK_WIDGET
argument_list|(
name|gtk_builder_get_object
argument_list|(
name|builder
argument_list|,
literal|"metadata-vbox"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|metadata_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
argument_list|)
argument_list|,
name|metadata_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|write_button
operator|=
name|gtk_builder_get_object
argument_list|(
name|builder
argument_list|,
literal|"iptc-write-button"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|write_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|metadata_dialog_iptc_callback
argument_list|)
argument_list|,
name|builder
argument_list|)
expr_stmt|;
name|metadata_dialog_set_metadata
argument_list|(
name|metadata
argument_list|,
name|builder
argument_list|)
expr_stmt|;
name|gtk_dialog_run
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|metadata_dialog_set_metadata (GExiv2Metadata * metadata,GtkBuilder * builder)
name|metadata_dialog_set_metadata
parameter_list|(
name|GExiv2Metadata
modifier|*
name|metadata
parameter_list|,
name|GtkBuilder
modifier|*
name|builder
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|exif_store
decl_stmt|;
name|GtkListStore
modifier|*
name|xmp_store
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|exif_data
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|iptc_data
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|xmp_data
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|gchar
modifier|*
name|value_utf
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|exif_store
operator|=
name|GTK_LIST_STORE
argument_list|(
name|gtk_builder_get_object
argument_list|(
name|builder
argument_list|,
literal|"exif-liststore"
argument_list|)
argument_list|)
expr_stmt|;
name|xmp_store
operator|=
name|GTK_LIST_STORE
argument_list|(
name|gtk_builder_get_object
argument_list|(
name|builder
argument_list|,
literal|"xmp-liststore"
argument_list|)
argument_list|)
expr_stmt|;
name|exif_data
operator|=
name|gexiv2_metadata_get_exif_tags
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|exif_data
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
name|gtk_list_store_append
argument_list|(
name|exif_store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|value
operator|=
name|gexiv2_metadata_get_tag_interpreted_string
argument_list|(
name|metadata
argument_list|,
name|exif_data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|value_utf
operator|=
name|g_locale_to_utf8
argument_list|(
name|value
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|exif_store
argument_list|,
operator|&
name|iter
argument_list|,
name|C_EXIF_TAG
argument_list|,
name|exif_data
index|[
name|i
index|]
argument_list|,
name|C_EXIF_VALUE
argument_list|,
name|value_utf
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|xmp_data
operator|=
name|gexiv2_metadata_get_xmp_tags
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|xmp_data
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
name|gtk_list_store_append
argument_list|(
name|xmp_store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|value
operator|=
name|gexiv2_metadata_get_tag_interpreted_string
argument_list|(
name|metadata
argument_list|,
name|xmp_data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|value_utf
operator|=
name|g_locale_to_utf8
argument_list|(
name|value
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|xmp_store
argument_list|,
operator|&
name|iter
argument_list|,
name|C_XMP_TAG
argument_list|,
name|xmp_data
index|[
name|i
index|]
argument_list|,
name|C_XMP_VALUE
argument_list|,
name|value_utf
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|iptc_data
operator|=
name|gexiv2_metadata_get_iptc_tags
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|iptc_data
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|gtk_builder_get_object
argument_list|(
name|builder
argument_list|,
name|iptc_data
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
name|gexiv2_metadata_get_tag_interpreted_string
argument_list|(
name|metadata
argument_list|,
name|iptc_data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|value_utf
operator|=
name|g_locale_to_utf8
argument_list|(
name|value
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_ENTRY
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GtkEntry
modifier|*
name|entry_widget
init|=
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gtk_entry_set_text
argument_list|(
name|entry_widget
argument_list|,
name|value_utf
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GTK_IS_TEXT_VIEW
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GtkTextView
modifier|*
name|text_view
init|=
name|GTK_TEXT_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|text_view
argument_list|)
expr_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
name|value_utf
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|metadata_dialog_iptc_callback (GtkWidget * dialog,GtkBuilder * builder)
name|metadata_dialog_iptc_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GtkBuilder
modifier|*
name|builder
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GExiv2Metadata *metadata;   gint            i;    metadata = gimp_image_get_metadata (handler->image);    for (i = 0; i< G_N_ELEMENTS (iptc_tags); i++)     {       GObject *object = gtk_builder_get_object (handler->builder,                                                 iptc_tags[i].tag);        if (! strcmp ("single", iptc_tags[i].mode))         {           GtkEntry *entry = GTK_ENTRY (object);            gexiv2_metadata_set_tag_string (metadata, iptc_tags[i].tag,                                           gtk_entry_get_text (entry));         }       else  if (!strcmp ("multi", iptc_tags[i].mode))         {           GtkTextView   *text_view = GTK_TEXT_VIEW (object);           GtkTextBuffer *buffer;           GtkTextIter    start;           GtkTextIter    end;           gchar         *text;            buffer = gtk_text_view_get_buffer (text_view);           gtk_text_buffer_get_start_iter (buffer,&start);           gtk_text_buffer_get_end_iter (buffer,&end);            text = gtk_text_buffer_get_text (buffer,&start,&end, TRUE);           gexiv2_metadata_set_tag_string (metadata, iptc_tags[i].tag, text);           g_free (text);         }     }
endif|#
directive|endif
block|}
end_function

end_unit


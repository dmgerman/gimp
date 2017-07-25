begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * metadata-editor.c  * Copyright (C) 2016, 2017 Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<ctype.h>
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
file|<glib.h>
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
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"metadata-xml.h"
end_include

begin_include
include|#
directive|include
file|"metadata-misc.h"
end_include

begin_include
include|#
directive|include
file|"metadata-tags.h"
end_include

begin_include
include|#
directive|include
file|"metadata-impexp.h"
end_include

begin_include
include|#
directive|include
file|"metadata-editor.h"
end_include

begin_decl_stmt
specifier|extern
name|gboolean
name|gimpmetadata
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|xmptag
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|iptctag
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|tagvalue
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|tagname
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gboolean
name|force_write
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|str_tag_value
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|str_tag_name
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xml_markup_parser
specifier|const
name|GMarkupParser
name|xml_markup_parser
init|=
block|{
name|xml_parser_start_element
block|,
name|xml_parser_end_element
block|,
name|xml_parser_data
block|,
name|NULL
block|,
comment|/*  passthrough  */
name|NULL
comment|/*  error        */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* ============================================================================  * ==[ METADATA IMPORT TEMPLATE ]==============================================  * ============================================================================  */
end_comment

begin_function
name|void
DECL|function|import_file_metadata (metadata_editor * args)
name|import_file_metadata
parameter_list|(
name|metadata_editor
modifier|*
name|args
parameter_list|)
block|{
name|GimpXmlParser
modifier|*
name|xml_parser
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|gchar
modifier|*
name|xmldata
decl_stmt|;
name|gimpmetadata
operator|=
name|FALSE
expr_stmt|;
name|xmptag
operator|=
name|FALSE
expr_stmt|;
name|iptctag
operator|=
name|FALSE
expr_stmt|;
name|tagvalue
operator|=
name|FALSE
expr_stmt|;
name|tagname
operator|=
name|FALSE
expr_stmt|;
name|file
operator|=
name|g_fopen
argument_list|(
name|args
operator|->
name|filename
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
operator|!=
name|NULL
condition|)
block|{
comment|/* get xml data from file */
name|g_file_get_contents
argument_list|(
name|args
operator|->
name|filename
argument_list|,
operator|&
name|xmldata
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
comment|/* parse xml data fetched from file */
name|xml_parser
operator|=
name|xml_parser_new
argument_list|(
operator|&
name|xml_markup_parser
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|xml_parser_parse_file
argument_list|(
name|xml_parser
argument_list|,
name|args
operator|->
name|filename
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|xml_parser_free
argument_list|(
name|xml_parser
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* ============================================================================  * ==[ METADATA EXPORT TEMPLATE ]==============================================  * ============================================================================  */
end_comment

begin_function
name|void
DECL|function|export_file_metadata (metadata_editor * args)
name|export_file_metadata
parameter_list|(
name|metadata_editor
modifier|*
name|args
parameter_list|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|gchar
modifier|*
name|value_utf
decl_stmt|;
name|gchar
modifier|*
name|xmldata
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|size
decl_stmt|;
if|if
condition|(
name|force_write
operator|==
name|TRUE
condition|)
block|{
comment|/* Save fields in case of updates */
name|metadata_editor_write_callback
argument_list|(
name|args
operator|->
name|dialog
argument_list|,
name|args
operator|->
name|builder
argument_list|,
name|args
operator|->
name|image_id
argument_list|)
expr_stmt|;
comment|/* Fetch a fresh copy of the metadata */
name|args
operator|->
name|metadata
operator|=
name|GEXIV2_METADATA
argument_list|(
name|gimp_image_get_metadata
argument_list|(
name|args
operator|->
name|image_id
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|xmldata
operator|=
name|g_strconcat
argument_list|(
literal|"<?xml version=â1.0â encoding=âutf-8â?>\n"
argument_list|,
literal|"<gimp-metadata>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* HANDLE IPTC */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|equivalent_metadata_tags
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|int
name|index
init|=
name|equivalent_metadata_tags
index|[
name|i
index|]
operator|.
name|other_tag_index
decl_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t<iptc-tag>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-name>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|equivalent_metadata_tags
index|[
name|i
index|]
operator|.
name|tag
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</tag-name>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-mode>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|equivalent_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</tag-mode>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-value>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
literal|"single"
argument_list|,
name|default_metadata_tags
index|[
name|index
index|]
operator|.
name|mode
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
literal|"multi"
argument_list|,
name|default_metadata_tags
index|[
name|index
index|]
operator|.
name|mode
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
name|value
operator|=
name|get_tag_ui_text
argument_list|(
name|args
argument_list|,
name|default_metadata_tags
index|[
name|index
index|]
operator|.
name|tag
argument_list|,
name|default_metadata_tags
index|[
name|index
index|]
operator|.
name|mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
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
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|value_utf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
literal|"combo"
argument_list|,
name|default_metadata_tags
index|[
name|index
index|]
operator|.
name|mode
argument_list|)
condition|)
block|{
name|gint
name|data
init|=
name|get_tag_ui_combo
argument_list|(
name|args
argument_list|,
name|default_metadata_tags
index|[
name|index
index|]
operator|.
name|tag
argument_list|,
name|default_metadata_tags
index|[
name|index
index|]
operator|.
name|mode
argument_list|)
decl_stmt|;
name|value
operator|=
name|g_malloc
argument_list|(
literal|1024
argument_list|)
expr_stmt|;
name|g_sprintf
argument_list|(
name|value
argument_list|,
literal|"%d"
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
literal|"list"
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
condition|)
block|{
comment|/* No IPTC lists elements at this point */
block|}
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</tag-value>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t</iptc-tag>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* HANDLE XMP */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|default_metadata_tags
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t<xmp-tag>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-name>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|tag
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</tag-name>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-mode>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</tag-mode>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
literal|"single"
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
literal|"multi"
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-value>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|value
operator|=
name|get_tag_ui_text
argument_list|(
name|args
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|tag
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
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
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|value_utf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</tag-value>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
literal|"combo"
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
condition|)
block|{
name|gint
name|data
decl_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-value>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|get_tag_ui_combo
argument_list|(
name|args
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|tag
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
expr_stmt|;
name|value
operator|=
name|g_malloc
argument_list|(
literal|1024
argument_list|)
expr_stmt|;
name|g_sprintf
argument_list|(
name|value
argument_list|,
literal|"%d"
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</tag-value>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
literal|"list"
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|data
decl_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t<tag-list-value>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|get_tag_ui_list
argument_list|(
name|args
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|tag
argument_list|,
name|default_metadata_tags
index|[
name|i
index|]
operator|.
name|mode
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
name|data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t\t</tag-list-value>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"\t</xmp-tag>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|xmldata
operator|=
name|g_strconcat
argument_list|(
name|xmldata
argument_list|,
literal|"</gimp-metadata>\n"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|size
operator|=
name|strlen
argument_list|(
name|xmldata
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_fopen
argument_list|(
name|args
operator|->
name|filename
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
operator|!=
name|NULL
condition|)
block|{
name|g_file_set_contents
argument_list|(
name|args
operator|->
name|filename
argument_list|,
name|xmldata
argument_list|,
name|size
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|xmldata
condition|)
block|{
name|g_free
argument_list|(
name|xmldata
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

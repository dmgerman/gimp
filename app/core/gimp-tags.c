begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-tags.c  * Copyright (C) 2009 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpxmlparser.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-tags.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_TAGS_FILE
define|#
directive|define
name|GIMP_TAGS_FILE
value|"tags.xml"
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29c2ae5a0108
block|{
DECL|member|locale
specifier|const
name|gchar
modifier|*
name|locale
decl_stmt|;
DECL|member|buf
name|GString
modifier|*
name|buf
decl_stmt|;
DECL|member|locale_matches
name|gboolean
name|locale_matches
decl_stmt|;
DECL|typedef|GimpTagsInstaller
block|}
name|GimpTagsInstaller
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_tags_installer_load_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tags_installer_load_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tags_installer_load_text
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gsize
name|text_len
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|attribute_name_to_value
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|gimp_tags_user_install (void)
name|gimp_tags_user_install
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GMarkupParser
name|markup_parser
decl_stmt|;
name|GimpXmlParser
modifier|*
name|xml_parser
decl_stmt|;
specifier|const
name|char
modifier|*
name|tags_locale
decl_stmt|;
name|GimpTagsInstaller
name|tags_installer
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gboolean
name|result
init|=
name|TRUE
decl_stmt|;
comment|/* This is a special string to specify the language identifier to    * look for in the gimp-tags-default.xml file. Please translate the    * C in it according to the name of the po file used for    * gimp-tags-default.xml. E.g. lithuanian for the translation,    * that would be "tags-locale:lt".    */
name|tags_locale
operator|=
name|_
argument_list|(
literal|"tags-locale:C"
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|tags_locale
argument_list|,
literal|"tags-locale:"
argument_list|)
condition|)
block|{
name|tags_locale
operator|+=
name|strlen
argument_list|(
literal|"tags-locale:"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|tags_locale
operator|&&
operator|*
name|tags_locale
operator|!=
literal|'C'
condition|)
name|tags_installer
operator|.
name|locale
operator|=
name|tags_locale
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"Wrong translation for 'tags-locale:', fix the translation!"
argument_list|)
expr_stmt|;
block|}
name|tags_installer
operator|.
name|buf
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|tags_installer
operator|.
name|buf
argument_list|,
literal|"<?xml version='1.0' encoding='UTF-8'?>\n"
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|tags_installer
operator|.
name|buf
argument_list|,
literal|"<tags>\n"
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"tags"
argument_list|,
literal|"gimp-tags-default.xml"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|markup_parser
operator|.
name|start_element
operator|=
name|gimp_tags_installer_load_start_element
expr_stmt|;
name|markup_parser
operator|.
name|end_element
operator|=
name|gimp_tags_installer_load_end_element
expr_stmt|;
name|markup_parser
operator|.
name|text
operator|=
name|gimp_tags_installer_load_text
expr_stmt|;
name|markup_parser
operator|.
name|passthrough
operator|=
name|NULL
expr_stmt|;
name|markup_parser
operator|.
name|error
operator|=
name|NULL
expr_stmt|;
name|xml_parser
operator|=
name|gimp_xml_parser_new
argument_list|(
operator|&
name|markup_parser
argument_list|,
operator|&
name|tags_installer
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_xml_parser_parse_file
argument_list|(
name|xml_parser
argument_list|,
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
name|gimp_xml_parser_free
argument_list|(
name|xml_parser
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|result
condition|)
block|{
name|g_string_free
argument_list|(
name|tags_installer
operator|.
name|buf
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_string_append
argument_list|(
name|tags_installer
operator|.
name|buf
argument_list|,
literal|"\n</tags>\n"
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|GIMP_TAGS_FILE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|result
operator|=
name|g_file_set_contents
argument_list|(
name|filename
argument_list|,
name|tags_installer
operator|.
name|buf
operator|->
name|str
argument_list|,
name|tags_installer
operator|.
name|buf
operator|->
name|len
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
name|g_string_free
argument_list|(
name|tags_installer
operator|.
name|buf
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|result
condition|)
block|{
name|g_warning
argument_list|(
literal|"Error while creating tags.xml: %s\n"
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
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tags_installer_load_start_element (GMarkupParseContext * context,const gchar * element_name,const gchar ** attribute_names,const gchar ** attribute_values,gpointer user_data,GError ** error)
name|gimp_tags_installer_load_start_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTagsInstaller
modifier|*
name|tags_installer
init|=
name|user_data
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"resource"
argument_list|)
condition|)
block|{
name|g_string_append_printf
argument_list|(
name|tags_installer
operator|->
name|buf
argument_list|,
literal|"\n<resource"
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|attribute_names
condition|)
block|{
name|g_string_append_printf
argument_list|(
name|tags_installer
operator|->
name|buf
argument_list|,
literal|" %s=\"%s\""
argument_list|,
operator|*
name|attribute_names
argument_list|,
operator|*
name|attribute_values
argument_list|)
expr_stmt|;
name|attribute_names
operator|++
expr_stmt|;
name|attribute_values
operator|++
expr_stmt|;
block|}
name|g_string_append_printf
argument_list|(
name|tags_installer
operator|->
name|buf
argument_list|,
literal|">\n"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"thetag"
argument_list|)
condition|)
block|{
specifier|const
name|char
modifier|*
name|current_locale
decl_stmt|;
name|current_locale
operator|=
name|attribute_name_to_value
argument_list|(
name|attribute_names
argument_list|,
name|attribute_values
argument_list|,
literal|"xml:lang"
argument_list|)
expr_stmt|;
if|if
condition|(
name|current_locale
operator|&&
name|tags_installer
operator|->
name|locale
condition|)
block|{
name|tags_installer
operator|->
name|locale_matches
operator|=
operator|!
name|strcmp
argument_list|(
name|current_locale
argument_list|,
name|tags_installer
operator|->
name|locale
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tags_installer
operator|->
name|locale_matches
operator|=
operator|(
name|current_locale
operator|==
name|tags_installer
operator|->
name|locale
operator|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tags_installer_load_end_element (GMarkupParseContext * context,const gchar * element_name,gpointer user_data,GError ** error)
name|gimp_tags_installer_load_end_element
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|element_name
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTagsInstaller
modifier|*
name|tags_installer
init|=
name|user_data
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|element_name
argument_list|,
literal|"resource"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_string_append
argument_list|(
name|tags_installer
operator|->
name|buf
argument_list|,
literal|"</resource>\n"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tags_installer_load_text (GMarkupParseContext * context,const gchar * text,gsize text_len,gpointer user_data,GError ** error)
name|gimp_tags_installer_load_text
parameter_list|(
name|GMarkupParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gsize
name|text_len
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpTagsInstaller
modifier|*
name|tags_installer
init|=
name|user_data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|current_element
decl_stmt|;
name|gchar
modifier|*
name|tag_string
decl_stmt|;
name|current_element
operator|=
name|g_markup_parse_context_get_element
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tags_installer
operator|->
name|locale_matches
operator|&&
name|current_element
operator|&&
name|strcmp
argument_list|(
name|current_element
argument_list|,
literal|"thetag"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|tag_string
operator|=
name|g_markup_escape_text
argument_list|(
name|text
argument_list|,
name|text_len
argument_list|)
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|tags_installer
operator|->
name|buf
argument_list|,
literal|"<tag>%s</tag>\n"
argument_list|,
name|tag_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tag_string
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|attribute_name_to_value (const gchar ** attribute_names,const gchar ** attribute_values,const gchar * name)
name|attribute_name_to_value
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_names
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|attribute_values
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
while|while
condition|(
operator|*
name|attribute_names
condition|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
operator|*
name|attribute_names
argument_list|,
name|name
argument_list|)
condition|)
block|{
return|return
operator|*
name|attribute_values
return|;
block|}
name|attribute_names
operator|++
expr_stmt|;
name|attribute_values
operator|++
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit


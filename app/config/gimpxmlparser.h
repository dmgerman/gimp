begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GimpXmlParser  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_XML_PARSER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_XML_PARSER_H__
define|#
directive|define
name|__GIMP_XML_PARSER_H__
end_define

begin_function_decl
name|GimpXmlParser
modifier|*
name|gimp_xml_parser_new
parameter_list|(
specifier|const
name|GMarkupParser
modifier|*
name|markup_parser
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_xml_parser_parse_file
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_xml_parser_parse_fd
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|,
name|gint
name|fd
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_xml_parser_parse_io_channel
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|,
name|GIOChannel
modifier|*
name|io
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_xml_parser_parse_buffer
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer
parameter_list|,
name|gssize
name|len
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_xml_parser_free
parameter_list|(
name|GimpXmlParser
modifier|*
name|parser
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_XML_PARSER_H__ */
end_comment

end_unit


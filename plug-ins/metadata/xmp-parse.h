begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* xmp-parse.h - simple parser for XMP metadata  *  * Copyright (C) 2004, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|XMP_PARSE_H
end_ifndef

begin_define
DECL|macro|XMP_PARSE_H
define|#
directive|define
name|XMP_PARSE_H
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon293dd6dd0103
block|{
DECL|enumerator|XMP_ERROR_NO_XPACKET
name|XMP_ERROR_NO_XPACKET
block|,
DECL|enumerator|XMP_ERROR_BAD_ENCODING
name|XMP_ERROR_BAD_ENCODING
block|,
DECL|enumerator|XMP_ERROR_PARSE
name|XMP_ERROR_PARSE
block|,
DECL|enumerator|XMP_ERROR_MISSING_ABOUT
name|XMP_ERROR_MISSING_ABOUT
block|,
DECL|enumerator|XMP_ERROR_UNKNOWN_ELEMENT
name|XMP_ERROR_UNKNOWN_ELEMENT
block|,
DECL|enumerator|XMP_ERROR_UNKNOWN_ATTRIBUTE
name|XMP_ERROR_UNKNOWN_ATTRIBUTE
block|,
DECL|enumerator|XMP_ERROR_UNEXPECTED_ELEMENT
name|XMP_ERROR_UNEXPECTED_ELEMENT
block|,
DECL|enumerator|XMP_ERROR_INVALID_CONTENT
name|XMP_ERROR_INVALID_CONTENT
block|,
DECL|enumerator|XMP_ERROR_INVALID_COMMENT
name|XMP_ERROR_INVALID_COMMENT
DECL|typedef|XMPParseError
block|}
name|XMPParseError
typedef|;
end_typedef

begin_define
DECL|macro|XMP_PARSE_ERROR
define|#
directive|define
name|XMP_PARSE_ERROR
value|xmp_parse_error_quark ()
end_define

begin_function_decl
name|GQuark
name|xmp_parse_error_quark
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon293dd6dd0203
block|{
DECL|enumerator|XMP_FLAG_FIND_XPACKET
name|XMP_FLAG_FIND_XPACKET
init|=
literal|1
operator|<<
literal|0
block|,
comment|/* allow text before<?xpacket */
DECL|enumerator|XMP_FLAG_NO_COMMENTS
name|XMP_FLAG_NO_COMMENTS
init|=
literal|1
operator|<<
literal|1
block|,
comment|/* no XML comments allowed */
DECL|enumerator|XMP_FLAG_NO_UNKNOWN_ELEMENTS
name|XMP_FLAG_NO_UNKNOWN_ELEMENTS
init|=
literal|1
operator|<<
literal|2
block|,
comment|/* no unknown XML elements */
DECL|enumerator|XMP_FLAG_NO_UNKNOWN_ATTRIBUTES
name|XMP_FLAG_NO_UNKNOWN_ATTRIBUTES
init|=
literal|1
operator|<<
literal|3
block|,
comment|/* no unknown XML attributes */
DECL|enumerator|XMP_FLAG_NO_MISSING_ABOUT
name|XMP_FLAG_NO_MISSING_ABOUT
init|=
literal|1
operator|<<
literal|4
block|,
comment|/* schemas must have rdf:about */
DECL|enumerator|XMP_FLAG_DEFER_VALUE_FREE
name|XMP_FLAG_DEFER_VALUE_FREE
init|=
literal|1
operator|<<
literal|5
comment|/* prop. value[] freed by caller */
DECL|typedef|XMPParseFlags
block|}
name|XMPParseFlags
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon293dd6dd0303
block|{
DECL|enumerator|XMP_PTYPE_TEXT
name|XMP_PTYPE_TEXT
block|,
comment|/* value in value[0] */
DECL|enumerator|XMP_PTYPE_RESOURCE
name|XMP_PTYPE_RESOURCE
block|,
comment|/* value in value[0] */
DECL|enumerator|XMP_PTYPE_ORDERED_LIST
name|XMP_PTYPE_ORDERED_LIST
block|,
comment|/* values in value[0..n] */
DECL|enumerator|XMP_PTYPE_UNORDERED_LIST
name|XMP_PTYPE_UNORDERED_LIST
block|,
comment|/* values in value[0..n] */
DECL|enumerator|XMP_PTYPE_ALT_THUMBS
name|XMP_PTYPE_ALT_THUMBS
block|,
comment|/* values in value[0..n] */
DECL|enumerator|XMP_PTYPE_ALT_LANG
name|XMP_PTYPE_ALT_LANG
block|,
comment|/* lang in value[0,2..n*2], text in value[1,3..n*2+1] */
DECL|enumerator|XMP_PTYPE_STRUCTURE
name|XMP_PTYPE_STRUCTURE
block|,
comment|/* ns prefix in name[0], ns uri in name[1], */
comment|/* name in value[2,4..n*2+2], value in value[3,5..n*2+3] */
DECL|enumerator|XMP_PTYPE_UNKNOWN
name|XMP_PTYPE_UNKNOWN
DECL|typedef|XMPParseType
block|}
name|XMPParseType
typedef|;
end_typedef

begin_typedef
DECL|typedef|XMPParseContext
typedef|typedef
name|struct
name|_XMPParseContext
name|XMPParseContext
typedef|;
end_typedef

begin_typedef
DECL|typedef|XMPParser
typedef|typedef
name|struct
name|_XMPParser
name|XMPParser
typedef|;
end_typedef

begin_struct
DECL|struct|_XMPParser
struct|struct
name|_XMPParser
block|{
comment|/* Called whenever the parser sees a new namespace (usually an XMP    * schema) except for the basic RDF and XMP namespaces.  The value    * returned by this callback will be passed as "ns_user_data" to the    * callbacks end_schema and set_property.  It is allowed to return    * the pointers ns_uri or ns_prefix because they will remain valid    * at least until end_schema is called.    */
DECL|member|start_schema
name|gpointer
function_decl|(
modifier|*
name|start_schema
function_decl|)
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ns_uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ns_prefix
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
comment|/* Called when a namespace goes out of scope.  The ns_user_data will    * be the one that was returned by start_schema for the    * corresponding schema.    */
DECL|member|end_schema
name|void
function_decl|(
modifier|*
name|end_schema
function_decl|)
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|ns_user_data
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
comment|/* Called for each property that is defined in the XMP packet.  The    * way the value of the property is returned depends on its type.    * See the definition of XMPParseType for details.    */
DECL|member|set_property
name|void
function_decl|(
modifier|*
name|set_property
function_decl|)
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|XMPParseType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value
parameter_list|,
name|gpointer
name|ns_user_data
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
comment|/* Called on error, including one set by other methods in the    * vtable.  The GError should not be freed.    */
DECL|member|error
name|void
function_decl|(
modifier|*
name|error
function_decl|)
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
name|error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|XMPParseContext
modifier|*
name|xmp_parse_context_new
parameter_list|(
specifier|const
name|XMPParser
modifier|*
name|parser
parameter_list|,
name|XMPParseFlags
name|flags
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GDestroyNotify
name|user_data_dnotify
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|xmp_parse_context_free
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|xmp_parse_context_parse
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gssize
name|text_len
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
name|xmp_parse_context_end_parse
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* XMP_PARSE_H */
end_comment

end_unit


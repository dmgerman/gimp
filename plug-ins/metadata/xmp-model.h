begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* xmp-model.h - treeview model for XMP metadata  *  * Copyright (C) 2004, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|XMP_MODEL_H
end_ifndef

begin_define
DECL|macro|XMP_MODEL_H
define|#
directive|define
name|XMP_MODEL_H
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|XMPModel
typedef|typedef
name|struct
name|_XMPModel
name|XMPModel
typedef|;
end_typedef

begin_comment
comment|/* known data types for XMP properties, as found in the XMP specification */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c18eb830103
block|{
DECL|enumerator|XMP_TYPE_BOOLEAN
name|XMP_TYPE_BOOLEAN
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_DATE
name|XMP_TYPE_DATE
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_DIMENSIONS
name|XMP_TYPE_DIMENSIONS
block|,
comment|/* STRUCTURE */
DECL|enumerator|XMP_TYPE_INTEGER
name|XMP_TYPE_INTEGER
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_INTEGER_SEQ
name|XMP_TYPE_INTEGER_SEQ
block|,
comment|/* ORDERED_LIST */
DECL|enumerator|XMP_TYPE_LANG_ALT
name|XMP_TYPE_LANG_ALT
block|,
comment|/* ALT_LANG */
DECL|enumerator|XMP_TYPE_LOCALE_BAG
name|XMP_TYPE_LOCALE_BAG
block|,
comment|/* UNORDERED_LIST */
DECL|enumerator|XMP_TYPE_REAL
name|XMP_TYPE_REAL
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_MIME_TYPE
name|XMP_TYPE_MIME_TYPE
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_TEXT
name|XMP_TYPE_TEXT
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_TEXT_BAG
name|XMP_TYPE_TEXT_BAG
block|,
comment|/* UNORDERED_LIST */
DECL|enumerator|XMP_TYPE_TEXT_SEQ
name|XMP_TYPE_TEXT_SEQ
block|,
comment|/* ORDERED_LIST */
DECL|enumerator|XMP_TYPE_THUMBNAIL_ALT
name|XMP_TYPE_THUMBNAIL_ALT
block|,
comment|/* (?) */
DECL|enumerator|XMP_TYPE_URI
name|XMP_TYPE_URI
block|,
comment|/* TEXT or RESOURCE (?) */
DECL|enumerator|XMP_TYPE_XPATH_BAG
name|XMP_TYPE_XPATH_BAG
block|,
comment|/* UNORDERED_LIST */
DECL|enumerator|XMP_TYPE_RESOURCE_EVENT_SEQ
name|XMP_TYPE_RESOURCE_EVENT_SEQ
block|,
comment|/* ORDERED_LIST */
DECL|enumerator|XMP_TYPE_RESOURCE_REF
name|XMP_TYPE_RESOURCE_REF
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_JOB_BAG
name|XMP_TYPE_JOB_BAG
block|,
comment|/* UNORDERED_LIST */
DECL|enumerator|XMP_TYPE_RATIONAL
name|XMP_TYPE_RATIONAL
block|,
comment|/* TEXT */
DECL|enumerator|XMP_TYPE_RATIONAL_SEQ
name|XMP_TYPE_RATIONAL_SEQ
block|,
comment|/* ORDERED_LIST */
DECL|enumerator|XMP_TYPE_GPS_COORDINATE
name|XMP_TYPE_GPS_COORDINATE
block|,
comment|/* (?) */
DECL|enumerator|XMP_TYPE_FLASH
name|XMP_TYPE_FLASH
block|,
comment|/* STRUCTURE */
DECL|enumerator|XMP_TYPE_OECF_SFR
name|XMP_TYPE_OECF_SFR
block|,
comment|/* (?) */
DECL|enumerator|XMP_TYPE_CFA_PATTERN
name|XMP_TYPE_CFA_PATTERN
block|,
comment|/* (?) */
DECL|enumerator|XMP_TYPE_DEVICE_SETTINGS
name|XMP_TYPE_DEVICE_SETTINGS
block|,
comment|/* (?) */
DECL|enumerator|XMP_TYPE_UNKNOWN
name|XMP_TYPE_UNKNOWN
DECL|typedef|XMPType
block|}
name|XMPType
typedef|;
end_typedef

begin_comment
comment|/* columns used in the GtkTreeStore model holding the XMP metadata */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c18eb830203
block|{
DECL|enumerator|COL_XMP_NAME
name|COL_XMP_NAME
init|=
literal|0
block|,
comment|/* G_TYPE_STRING */
DECL|enumerator|COL_XMP_VALUE
name|COL_XMP_VALUE
block|,
comment|/* G_TYPE_STRING */
DECL|enumerator|COL_XMP_VALUE_RAW
name|COL_XMP_VALUE_RAW
block|,
comment|/* G_TYPE_POINTER */
DECL|enumerator|COL_XMP_TYPE_XREF
name|COL_XMP_TYPE_XREF
block|,
comment|/* G_TYPE_POINTER */
DECL|enumerator|COL_XMP_WIDGET_XREF
name|COL_XMP_WIDGET_XREF
block|,
comment|/* G_TYPE_POINTER */
DECL|enumerator|COL_XMP_EDITABLE
name|COL_XMP_EDITABLE
block|,
comment|/* G_TYPE_INT */
DECL|enumerator|COL_XMP_EDIT_ICON
name|COL_XMP_EDIT_ICON
block|,
comment|/* GDK_TYPE_PIXBUF */
DECL|enumerator|COL_XMP_VISIBLE
name|COL_XMP_VISIBLE
block|,
comment|/* G_TYPE_BOOLEAN */
DECL|enumerator|COL_XMP_WEIGHT
name|COL_XMP_WEIGHT
block|,
comment|/* G_TYPE_INT */
DECL|enumerator|COL_XMP_WEIGHT_SET
name|COL_XMP_WEIGHT_SET
block|,
comment|/* G_TYPE_BOOLEAN */
DECL|enumerator|XMP_MODEL_NUM_COLUMNS
name|XMP_MODEL_NUM_COLUMNS
DECL|typedef|XMPModelColumns
block|}
name|XMPModelColumns
typedef|;
end_typedef

begin_comment
comment|/* special value for the COL_XMP_EDITABLE column.  not strictly boolean... */
end_comment

begin_define
DECL|macro|XMP_AUTO_UPDATE
define|#
directive|define
name|XMP_AUTO_UPDATE
value|2
end_define

begin_comment
comment|/* XMP properties referenced in the tree via COL_XMP_TYPE_XREF (depth 2) */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c18eb830308
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|type
name|XMPType
name|type
decl_stmt|;
DECL|member|editable
name|gboolean
name|editable
decl_stmt|;
DECL|typedef|XMPProperty
block|}
name|XMPProperty
typedef|;
end_typedef

begin_comment
comment|/* XMP schemas referenced in the tree via COL_XMP_TYPE_XREF (depth 1) */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c18eb830408
block|{
DECL|member|uri
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
DECL|member|prefix
specifier|const
name|gchar
modifier|*
name|prefix
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|properties
name|XMPProperty
modifier|*
name|properties
decl_stmt|;
DECL|typedef|XMPSchema
block|}
name|XMPSchema
typedef|;
end_typedef

begin_function_decl
name|XMPModel
modifier|*
name|xmp_model_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|xmp_model_free
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|xmp_model_is_empty
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|xmp_model_parse_buffer
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer
parameter_list|,
name|gssize
name|buffer_length
parameter_list|,
name|gboolean
name|skip_other_data
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
name|xmp_model_parse_file
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
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
name|GtkTreeModel
modifier|*
name|xmp_model_get_tree_model
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|xmp_model_get_scalar_property
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
specifier|const
name|gchar
modifier|*
name|schema_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|xmp_model_set_scalar_property
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
specifier|const
name|gchar
modifier|*
name|schema_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_value
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
comment|/* XMP_MODEL_H */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* xmp-schemas.h - standard schemas defined in the XMP specifications  *  * Copyright (C) 2004, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|XMP_SCHEMAS_H
end_ifndef

begin_define
DECL|macro|XMP_SCHEMAS_H
define|#
directive|define
name|XMP_SCHEMAS_H
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* known data types for XMP properties, as found in the XMP specification */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29099ea80103
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
comment|/* ALT_THUMBS */
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
DECL|enumerator|XMP_TYPE_CONTACT_INFO
name|XMP_TYPE_CONTACT_INFO
block|,
comment|/* STRUCTURE */
DECL|enumerator|XMP_TYPE_GENERIC_STRUCTURE
name|XMP_TYPE_GENERIC_STRUCTURE
block|,
comment|/* STRUCTURE */
DECL|enumerator|XMP_TYPE_UNKNOWN
name|XMP_TYPE_UNKNOWN
DECL|typedef|XMPType
block|}
name|XMPType
typedef|;
end_typedef

begin_comment
comment|/* XMP properties referenced in the tree via COL_XMP_TYPE_XREF (depth 2) */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29099ea80208
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
DECL|struct|__anon29099ea80308
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

begin_comment
comment|/* URIs of standard XMP schemas (as of January 2004) */
end_comment

begin_define
DECL|macro|XMP_SCHEMA_DUBLIN_CORE
define|#
directive|define
name|XMP_SCHEMA_DUBLIN_CORE
value|"http://purl.org/dc/elements/1.1/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_XMP_BASIC
define|#
directive|define
name|XMP_SCHEMA_XMP_BASIC
value|"http://ns.adobe.com/xap/1.0/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_XMP_RIGHTS
define|#
directive|define
name|XMP_SCHEMA_XMP_RIGHTS
value|"http://ns.adobe.com/xap/1.0/rights/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_XMP_MM
define|#
directive|define
name|XMP_SCHEMA_XMP_MM
value|"http://ns.adobe.com/xap/1.0/mm/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_XMP_BJ
define|#
directive|define
name|XMP_SCHEMA_XMP_BJ
value|"http://ns.adobe.com/xap/1.0/bj/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_XMP_TPG
define|#
directive|define
name|XMP_SCHEMA_XMP_TPG
value|"http://ns.adobe.com/xap/1.0/t/pg/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_PDF
define|#
directive|define
name|XMP_SCHEMA_PDF
value|"http://ns.adobe.com/pdf/1.3/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_PHOTOSHOP
define|#
directive|define
name|XMP_SCHEMA_PHOTOSHOP
value|"http://ns.adobe.com/photoshop/1.0/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_TIFF
define|#
directive|define
name|XMP_SCHEMA_TIFF
value|"http://ns.adobe.com/tiff/1.0/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_EXIF
define|#
directive|define
name|XMP_SCHEMA_EXIF
value|"http://ns.adobe.com/exif/1.0/"
end_define

begin_comment
comment|/* Additional schemas published in March 2005 */
end_comment

begin_define
DECL|macro|XMP_SCHEMA_XMP_PLUS
define|#
directive|define
name|XMP_SCHEMA_XMP_PLUS
value|"http://ns.adobe.com/xap/1.0/PLUS/"
end_define

begin_define
DECL|macro|XMP_SCHEMA_IPTC_CORE
define|#
directive|define
name|XMP_SCHEMA_IPTC_CORE
value|"http://iptc.org/std/Iptc4xmpCore/1.0/xmlns/"
end_define

begin_comment
comment|/* recommended prefixes for the schemas listed above */
end_comment

begin_define
DECL|macro|XMP_PREFIX_DUBLIN_CORE
define|#
directive|define
name|XMP_PREFIX_DUBLIN_CORE
value|"dc"
end_define

begin_define
DECL|macro|XMP_PREFIX_XMP_BASIC
define|#
directive|define
name|XMP_PREFIX_XMP_BASIC
value|"xmp"
end_define

begin_define
DECL|macro|XMP_PREFIX_XMP_RIGHTS
define|#
directive|define
name|XMP_PREFIX_XMP_RIGHTS
value|"xmpRights"
end_define

begin_define
DECL|macro|XMP_PREFIX_XMP_MM
define|#
directive|define
name|XMP_PREFIX_XMP_MM
value|"xmpMM"
end_define

begin_define
DECL|macro|XMP_PREFIX_XMP_BJ
define|#
directive|define
name|XMP_PREFIX_XMP_BJ
value|"xmpBJ"
end_define

begin_define
DECL|macro|XMP_PREFIX_XMP_TPG
define|#
directive|define
name|XMP_PREFIX_XMP_TPG
value|"xmpTPg"
end_define

begin_define
DECL|macro|XMP_PREFIX_PDF
define|#
directive|define
name|XMP_PREFIX_PDF
value|"pdf"
end_define

begin_define
DECL|macro|XMP_PREFIX_PHOTOSHOP
define|#
directive|define
name|XMP_PREFIX_PHOTOSHOP
value|"photoshop"
end_define

begin_define
DECL|macro|XMP_PREFIX_TIFF
define|#
directive|define
name|XMP_PREFIX_TIFF
value|"tiff"
end_define

begin_define
DECL|macro|XMP_PREFIX_EXIF
define|#
directive|define
name|XMP_PREFIX_EXIF
value|"exif"
end_define

begin_define
DECL|macro|XMP_PREFIX_XMP_PLUS
define|#
directive|define
name|XMP_PREFIX_XMP_PLUS
value|"xmpPLUS"
end_define

begin_define
DECL|macro|XMP_PREFIX_IPTC_CORE
define|#
directive|define
name|XMP_PREFIX_IPTC_CORE
value|"Iptc4xmpCore"
end_define

begin_comment
comment|/* List of known XMP schemas and their properties */
end_comment

begin_decl_stmt
DECL|variable|xmp_schemas
name|XMPSchema
modifier|*
specifier|const
name|xmp_schemas
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* XMP_SCHEMAS_H */
end_comment

end_unit


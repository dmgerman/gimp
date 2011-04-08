begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* metadata.h - defines for the metadata editor  *  * Copyright (C) 2004-2005, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__METADATA_H__
end_ifndef

begin_define
DECL|macro|__METADATA_H__
define|#
directive|define
name|__METADATA_H__
end_define

begin_define
DECL|macro|EDITOR_PROC
define|#
directive|define
name|EDITOR_PROC
value|"plug-in-metadata-editor"
end_define

begin_define
DECL|macro|DECODE_XMP_PROC
define|#
directive|define
name|DECODE_XMP_PROC
value|"plug-in-metadata-decode-xmp"
end_define

begin_define
DECL|macro|ENCODE_XMP_PROC
define|#
directive|define
name|ENCODE_XMP_PROC
value|"plug-in-metadata-encode-xmp"
end_define

begin_define
DECL|macro|DECODE_EXIF_PROC
define|#
directive|define
name|DECODE_EXIF_PROC
value|"plug-in-metadata-decode-exif"
end_define

begin_define
DECL|macro|ENCODE_EXIF_PROC
define|#
directive|define
name|ENCODE_EXIF_PROC
value|"plug-in-metadata-encode-exif"
end_define

begin_define
DECL|macro|GET_PROC
define|#
directive|define
name|GET_PROC
value|"plug-in-metadata-get"
end_define

begin_define
DECL|macro|SET_PROC
define|#
directive|define
name|SET_PROC
value|"plug-in-metadata-set"
end_define

begin_define
DECL|macro|GET_SIMPLE_PROC
define|#
directive|define
name|GET_SIMPLE_PROC
value|"plug-in-metadata-get-simple"
end_define

begin_define
DECL|macro|SET_SIMPLE_PROC
define|#
directive|define
name|SET_SIMPLE_PROC
value|"plug-in-metadata-set-simple"
end_define

begin_define
DECL|macro|IMPORT_PROC
define|#
directive|define
name|IMPORT_PROC
value|"plug-in-metadata-import"
end_define

begin_define
DECL|macro|EXPORT_PROC
define|#
directive|define
name|EXPORT_PROC
value|"plug-in-metadata-export"
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __METADATA_H__ */
end_comment

end_unit


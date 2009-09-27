begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GimpXmpModelEntry.h - custom entry widget linked to the xmp model  *  * Copyright (C) 2009, RÃ³man Joost<romanofski@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_XMP_MODEL_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_XMP_MODEL_ENTRY_H__
define|#
directive|define
name|__GIMP_XMP_MODEL_ENTRY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_XMP_MODEL_ENTRY
define|#
directive|define
name|GIMP_TYPE_XMP_MODEL_ENTRY
value|(gimp_xmp_model_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_ENTRY (obj)
define|#
directive|define
name|GIMP_XMP_MODEL_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_XMP_MODEL_ENTRY, GimpXmpModelEntry))
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_XMP_MODEL_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_XMP_MODEL_ENTRY, XMPModelClass))
end_define

begin_define
DECL|macro|GIMP_IS_XMP_MODEL_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_XMP_MODEL_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_XMP_MODEL_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_XMP_MODEL_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_XMP_MODEL_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_XMP_MODEL_ENTRY))
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_XMP_MODEL_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_XMP_MODEL_ENTRY, XMPModelClass))
end_define

begin_typedef
DECL|typedef|GimpXmpModelEntry
typedef|typedef
name|struct
name|_GimpXmpModelEntry
name|GimpXmpModelEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpXmpModelEntryClass
typedef|typedef
name|struct
name|_GimpXmpModelEntryClass
name|GimpXmpModelEntryClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpXmpModelEntryPrivate
typedef|typedef
name|struct
name|_GimpXmpModelEntryPrivate
name|GimpXmpModelEntryPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpXmpModelEntry
struct|struct
name|_GimpXmpModelEntry
block|{
DECL|member|parent_instance
name|GtkEntry
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpXmpModelEntryPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpXmpModelEntryClass
struct|struct
name|_GimpXmpModelEntryClass
block|{
DECL|member|parent_class
name|GtkEntryClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpXmpModelEntryPrivate
struct|struct
name|_GimpXmpModelEntryPrivate
block|{
DECL|member|schema_uri
specifier|const
name|gchar
modifier|*
name|schema_uri
decl_stmt|;
DECL|member|property_name
specifier|const
name|gchar
modifier|*
name|property_name
decl_stmt|;
DECL|member|xmp_model
name|XMPModel
modifier|*
name|xmp_model
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_xmp_model_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_xmp_model_entry_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|schema_uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property
parameter_list|,
name|XMPModel
modifier|*
name|xmp_model
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
comment|/* __GIMP_XMP_MODEL_ENTRY_H__ */
end_comment

end_unit


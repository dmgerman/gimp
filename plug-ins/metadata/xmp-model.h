begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* xmp-model.h - treeview model for XMP metadata  *  * Copyright (C) 2004, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_XMP_MODEL
define|#
directive|define
name|GIMP_TYPE_XMP_MODEL
value|(xmp_model_get_type ())
end_define

begin_define
DECL|macro|XMP_MODEL (obj)
define|#
directive|define
name|XMP_MODEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_XMP_MODEL, XMPModel))
end_define

begin_define
DECL|macro|XMP_MODEL_CLASS (klass)
define|#
directive|define
name|XMP_MODEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_XMP_MODEL, XMPModelClass))
end_define

begin_define
DECL|macro|GIMP_IS_XMP_MODEL (obj)
define|#
directive|define
name|GIMP_IS_XMP_MODEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_XMP_MODEL))
end_define

begin_define
DECL|macro|GIMP_IS_XMP_MODEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_XMP_MODEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_XMP_MODEL))
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_XMP_MODEL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_XMP_MODEL, XMPModelClass))
end_define

begin_typedef
DECL|typedef|XMPModel
typedef|typedef
name|struct
name|_XMPModel
name|XMPModel
typedef|;
end_typedef

begin_typedef
DECL|typedef|XMPModelClass
typedef|typedef
name|struct
name|_XMPModelClass
name|XMPModelClass
typedef|;
end_typedef

begin_comment
comment|/* The main part of the XMPModel structure is the GtkTreeStore in  * which all references to XMP properties are stored.  In the tree,  * the elements at the root level are the schemas (namespaces) and the  * children of the schemas are the XMP properties.  *  * If the XMP file contains a schema that is not part of the XMP  * specification or a known extension (e.g., IPTC Core), it will be  * included in the custom_schemas list and the corresponding element  * in the tree will get a reference to that list element instead of a  * reference to one of the static schema definitions found in  * xmp-schemas.c.  Same for custom properties inside a known or custom  * schema.  */
end_comment

begin_struct
DECL|struct|_XMPModel
struct|struct
name|_XMPModel
block|{
DECL|member|parent_instance
name|GtkTreeStore
name|parent_instance
decl_stmt|;
DECL|member|custom_schemas
name|GSList
modifier|*
name|custom_schemas
decl_stmt|;
DECL|member|custom_properties
name|GSList
modifier|*
name|custom_properties
decl_stmt|;
DECL|member|cached_schema
name|XMPSchema
modifier|*
name|cached_schema
decl_stmt|;
DECL|member|cached_schema_iter
name|GtkTreeIter
name|cached_schema_iter
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_XMPModelClass
struct|struct
name|_XMPModelClass
block|{
DECL|member|parent_class
name|GtkTreeStoreClass
name|parent_class
decl_stmt|;
DECL|member|property_changed
name|void
function_decl|(
modifier|*
name|property_changed
function_decl|)
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
name|XMPSchema
modifier|*
name|schema
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/* columns used in the GtkTreeStore model holding the XMP metadata */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2920fad80103
block|{
DECL|enumerator|COL_XMP_NAME
name|COL_XMP_NAME
init|=
literal|0
block|,
comment|/* G_TYPE_STRING   - name */
DECL|enumerator|COL_XMP_VALUE
name|COL_XMP_VALUE
block|,
comment|/* G_TYPE_STRING   - value as string (for viewing) */
DECL|enumerator|COL_XMP_VALUE_RAW
name|COL_XMP_VALUE_RAW
block|,
comment|/* G_TYPE_POINTER  - value as array (from parser) */
DECL|enumerator|COL_XMP_TYPE_XREF
name|COL_XMP_TYPE_XREF
block|,
comment|/* G_TYPE_POINTER  - XMPProperty or XMPSchema */
DECL|enumerator|COL_XMP_WIDGET_XREF
name|COL_XMP_WIDGET_XREF
block|,
comment|/* G_TYPE_POINTER  - GtkWidget cross-reference */
DECL|enumerator|COL_XMP_EDITABLE
name|COL_XMP_EDITABLE
block|,
comment|/* G_TYPE_INT      - editable? */
DECL|enumerator|COL_XMP_EDIT_ICON
name|COL_XMP_EDIT_ICON
block|,
comment|/* GDK_TYPE_PIXBUF - edit icon */
DECL|enumerator|COL_XMP_VISIBLE
name|COL_XMP_VISIBLE
block|,
comment|/* G_TYPE_BOOLEAN  - visible? */
DECL|enumerator|COL_XMP_WEIGHT
name|COL_XMP_WEIGHT
block|,
comment|/* G_TYPE_INT      - font weight */
DECL|enumerator|COL_XMP_WEIGHT_SET
name|COL_XMP_WEIGHT_SET
block|,
comment|/* G_TYPE_BOOLEAN  - font weight set? */
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

begin_decl_stmt
name|GType
name|xmp_model_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

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

begin_comment
comment|/* Signals */
end_comment

begin_function_decl
name|void
name|xmp_model_property_changed
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
name|XMPSchema
modifier|*
name|schema
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
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


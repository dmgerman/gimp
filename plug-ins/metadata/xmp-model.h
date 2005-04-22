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
comment|/* columns used in the GtkTreeStore model holding the XMP metadata */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b9b5d470103
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


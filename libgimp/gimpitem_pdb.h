begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpitem_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_PDB_H__
define|#
directive|define
name|__GIMP_ITEM_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_item_is_valid
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_item_get_image
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_delete
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_is_drawable
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_is_layer
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_is_channel
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_is_layer_mask
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_is_selection
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_is_vectors
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_item_get_name
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_set_name
parameter_list|(
name|gint32
name|item_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_get_visible
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_set_visible
parameter_list|(
name|gint32
name|item_ID
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_get_linked
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_set_linked
parameter_list|(
name|gint32
name|item_ID
parameter_list|,
name|gboolean
name|linked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_get_lock_content
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_set_lock_content
parameter_list|(
name|gint32
name|item_ID
parameter_list|,
name|gboolean
name|lock_content
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_item_get_tattoo
parameter_list|(
name|gint32
name|item_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_item_set_tattoo
parameter_list|(
name|gint32
name|item_ID
parameter_list|,
name|gint
name|tattoo
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
comment|/* __GIMP_ITEM_PDB_H__ */
end_comment

end_unit


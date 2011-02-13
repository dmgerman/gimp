begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpvectors.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTORS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTORS_H__
define|#
directive|define
name|__GIMP_VECTORS_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
name|gboolean
name|gimp_vectors_is_valid
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_vectors_get_image
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_vectors_get_name
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_name
parameter_list|(
name|gint32
name|vectors_ID
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
name|gimp_vectors_get_visible
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_visible
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_get_linked
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_linked
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gboolean
name|linked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_vectors_get_tattoo
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_set_tattoo
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_vectors_parasite_find
parameter_list|(
name|gint32
name|vectors_ID
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
name|gimp_vectors_parasite_attach
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_vectors_parasite_detach
parameter_list|(
name|gint32
name|vectors_ID
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
name|gimp_vectors_parasite_list
parameter_list|(
name|gint32
name|vectors_ID
parameter_list|,
name|gint
modifier|*
name|num_parasites
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|parasites
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_VECTORS_H__ */
end_comment

end_unit


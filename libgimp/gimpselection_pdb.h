begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpselection_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SELECTION_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SELECTION_PDB_H__
define|#
directive|define
name|__GIMP_SELECTION_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
name|gboolean
name|gimp_selection_bounds
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
modifier|*
name|non_empty
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_selection_value
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_is_empty
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_translate
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|GimpLayer
modifier|*
name|_gimp_selection_float
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_invert
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_sharpen
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_all
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_none
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_feather
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_border
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_grow
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|steps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_shrink
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|steps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_flood
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_selection_save
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_define
define|#
directive|define
name|gimp_selection_bounds
value|_gimp_selection_bounds
end_define

begin_define
define|#
directive|define
name|gimp_selection_value
value|_gimp_selection_value
end_define

begin_define
define|#
directive|define
name|gimp_selection_is_empty
value|_gimp_selection_is_empty
end_define

begin_define
define|#
directive|define
name|gimp_selection_translate
value|_gimp_selection_translate
end_define

begin_define
define|#
directive|define
name|gimp_selection_invert
value|_gimp_selection_invert
end_define

begin_define
define|#
directive|define
name|gimp_selection_sharpen
value|_gimp_selection_sharpen
end_define

begin_define
define|#
directive|define
name|gimp_selection_all
value|_gimp_selection_all
end_define

begin_define
define|#
directive|define
name|gimp_selection_none
value|_gimp_selection_none
end_define

begin_define
define|#
directive|define
name|gimp_selection_feather
value|_gimp_selection_feather
end_define

begin_define
define|#
directive|define
name|gimp_selection_border
value|_gimp_selection_border
end_define

begin_define
define|#
directive|define
name|gimp_selection_grow
value|_gimp_selection_grow
end_define

begin_define
define|#
directive|define
name|gimp_selection_shrink
value|_gimp_selection_shrink
end_define

begin_define
define|#
directive|define
name|gimp_selection_flood
value|_gimp_selection_flood
end_define

begin_define
define|#
directive|define
name|gimp_selection_save
value|_gimp_selection_save
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_comment
comment|/* Below API are deprecated and should not be used by new plug-ins.  * They are not marked internal as a trick to keep the old API alive for now.  */
end_comment

begin_function_decl
name|gboolean
name|_gimp_selection_bounds
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gboolean
modifier|*
name|non_empty
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|_gimp_selection_value
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_is_empty
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_translate
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_invert
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_sharpen
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_all
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_none
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_feather
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_border
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_grow
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|steps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_shrink
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|steps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_selection_flood
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_selection_save
parameter_list|(
name|gint32
name|image_ID
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
comment|/* __GIMP_SELECTION_PDB_H__ */
end_comment

end_unit


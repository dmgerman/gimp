begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprocedure-private.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_PROCEDURE_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROCEDURE_PRIVATE_H__
define|#
directive|define
name|__GIMP_PROCEDURE_PRIVATE_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
name|GimpDisplay
modifier|*
name|_gimp_procedure_get_display
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gint32
name|display_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|_gimp_procedure_get_image
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|_gimp_procedure_get_item
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gint32
name|item_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_procedure_destroy_proxies
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
comment|/*  __GIMP_PROCEDURE_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GimpColorManaged interface  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_COLOR_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COLOR_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpcolor/gimpcolor.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_MANAGED_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_MANAGED_H__
define|#
directive|define
name|__GIMP_COLOR_MANAGED_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLOR_MANAGED
define|#
directive|define
name|GIMP_TYPE_COLOR_MANAGED
value|(gimp_color_managed_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_MANAGED (obj)
define|#
directive|define
name|GIMP_IS_COLOR_MANAGED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_MANAGED))
end_define

begin_define
DECL|macro|GIMP_COLOR_MANAGED (obj)
define|#
directive|define
name|GIMP_COLOR_MANAGED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_MANAGED, GimpColorManaged))
end_define

begin_define
DECL|macro|GIMP_COLOR_MANAGED_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_COLOR_MANAGED_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_COLOR_MANAGED, GimpColorManagedInterface))
end_define

begin_typedef
DECL|typedef|GimpColorManagedInterface
typedef|typedef
name|struct
name|_GimpColorManagedInterface
name|GimpColorManagedInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorManagedInterface
struct|struct
name|_GimpColorManagedInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|get_icc_profile
specifier|const
name|guint8
modifier|*
function_decl|(
modifier|*
name|get_icc_profile
function_decl|)
parameter_list|(
name|GimpColorManaged
modifier|*
name|managed
parameter_list|,
name|gsize
modifier|*
name|len
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|profile_changed
name|void
function_decl|(
modifier|*
name|profile_changed
function_decl|)
parameter_list|(
name|GimpColorManaged
modifier|*
name|managed
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_managed_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|const
name|guint8
modifier|*
name|gimp_color_managed_get_icc_profile
parameter_list|(
name|GimpColorManaged
modifier|*
name|managed
parameter_list|,
name|gsize
modifier|*
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_managed_profile_changed
parameter_list|(
name|GimpColorManaged
modifier|*
name|managed
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
comment|/* __GIMP_COLOR_MANAGED_IFACE_H__ */
end_comment

end_unit


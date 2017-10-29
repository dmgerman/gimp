begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbase-private.c  * Copyright (C) 2003 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpbase-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpcompatenums.h"
end_include

begin_decl_stmt
DECL|variable|_gimp_unit_vtable
name|GimpUnitVtable
name|_gimp_unit_vtable
init|=
block|{
name|NULL
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_base_init (GimpUnitVtable * vtable)
name|gimp_base_init
parameter_list|(
name|GimpUnitVtable
modifier|*
name|vtable
parameter_list|)
block|{
specifier|static
name|gboolean
name|gimp_base_initialized
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|vtable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_base_initialized
condition|)
name|g_error
argument_list|(
literal|"gimp_base_init() must only be called once!"
argument_list|)
expr_stmt|;
name|_gimp_unit_vtable
operator|=
operator|*
name|vtable
expr_stmt|;
name|gimp_base_compat_enums_init
argument_list|()
expr_stmt|;
name|gimp_base_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_base_compat_enums_init (void)
name|gimp_base_compat_enums_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|gimp_base_compat_initialized
init|=
name|FALSE
decl_stmt|;
name|GQuark
name|quark
decl_stmt|;
if|if
condition|(
name|gimp_base_compat_initialized
condition|)
return|return;
name|quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-compat-enum"
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_ADD_MASK_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_ADD_MASK_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_BLEND_MODE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_BLEND_MODE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_BUCKET_FILL_MODE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_BUCKET_FILL_MODE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_CHANNEL_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_CLONE_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_CLONE_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_CONVERT_PALETTE_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_CONVERT_PALETTE_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_CONVOLVE_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_CONVOLVE_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_DESATURATE_MODE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_DESATURATE_MODE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_DODGE_BURN_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_DODGE_BURN_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_FILL_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_FILL_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_HUE_RANGE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_HUE_RANGE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_ICON_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_ICON_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_INTERPOLATION_TYPE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_INTERPOLATION_TYPE_COMPAT
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|GIMP_TYPE_TRANSFER_MODE
argument_list|,
name|quark
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_TYPE_TRANSFER_MODE_COMPAT
argument_list|)
expr_stmt|;
name|gimp_base_compat_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GimpColorManaged interface  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolormanaged.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofile.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolormanaged  * @title: GimpColorManaged  * @short_description: An interface dealing with color profiles.  *  * An interface dealing with color profiles.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2b5f4def0103
block|{
DECL|enumerator|PROFILE_CHANGED
name|PROFILE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_macro
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpColorManaged
argument_list|,
argument|gimp_color_managed
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|guint
name|gimp_color_managed_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_color_managed_default_init (GimpColorManagedInterface * iface)
name|gimp_color_managed_default_init
parameter_list|(
name|GimpColorManagedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|gimp_color_managed_signals
index|[
name|PROFILE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"profile-changed"
argument_list|,
name|G_TYPE_FROM_INTERFACE
argument_list|(
name|iface
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpColorManagedInterface
argument_list|,
name|profile_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_color_managed_get_icc_profile:  * @managed: an object the implements the #GimpColorManaged interface  * @len:     return location for the number of bytes in the profile data  *  * Return value: A pointer to a blob of data that represents an ICC  *               color profile.  *  * Since: 2.4  **/
end_comment

begin_function
specifier|const
name|guint8
modifier|*
DECL|function|gimp_color_managed_get_icc_profile (GimpColorManaged * managed,gsize * len)
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
block|{
name|GimpColorManagedInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_MANAGED
argument_list|(
name|managed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|len
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|len
operator|=
literal|0
expr_stmt|;
name|iface
operator|=
name|GIMP_COLOR_MANAGED_GET_INTERFACE
argument_list|(
name|managed
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_icc_profile
condition|)
return|return
name|iface
operator|->
name|get_icc_profile
argument_list|(
name|managed
argument_list|,
name|len
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_managed_get_color_profile:  * @managed: an object the implements the #GimpColorManaged interface  *  * This function always returns a #GimpColorProfile and falls back to  * gimp_color_profile_new_rgb_srgb() if the method is not implemented.  *  * Return value: The @managed's #GimpColorProfile.  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpColorProfile
modifier|*
DECL|function|gimp_color_managed_get_color_profile (GimpColorManaged * managed)
name|gimp_color_managed_get_color_profile
parameter_list|(
name|GimpColorManaged
modifier|*
name|managed
parameter_list|)
block|{
name|GimpColorManagedInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_MANAGED
argument_list|(
name|managed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_COLOR_MANAGED_GET_INTERFACE
argument_list|(
name|managed
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_color_profile
condition|)
return|return
name|iface
operator|->
name|get_color_profile
argument_list|(
name|managed
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_managed_profile_changed:  * @managed: an object the implements the #GimpColorManaged interface  *  * Emits the "profile-changed" signal.  *  * Since: 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_managed_profile_changed (GimpColorManaged * managed)
name|gimp_color_managed_profile_changed
parameter_list|(
name|GimpColorManaged
modifier|*
name|managed
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_MANAGED
argument_list|(
name|managed
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|managed
argument_list|,
name|gimp_color_managed_signals
index|[
name|PROFILE_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


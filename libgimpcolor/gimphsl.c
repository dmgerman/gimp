begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimphsl.h"
end_include

begin_comment
comment|/*  * GIMP_TYPE_HSL  */
end_comment

begin_function_decl
specifier|static
name|GimpHSL
modifier|*
name|gimp_hsl_copy
parameter_list|(
specifier|const
name|GimpHSL
modifier|*
name|hsl
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_hsl_get_type (void)
name|gimp_hsl_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|hsl_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|hsl_type
condition|)
name|hsl_type
operator|=
name|g_boxed_type_register_static
argument_list|(
literal|"GimpHSL"
argument_list|,
operator|(
name|GBoxedCopyFunc
operator|)
name|gimp_hsl_copy
argument_list|,
operator|(
name|GBoxedFreeFunc
operator|)
name|g_free
argument_list|)
expr_stmt|;
return|return
name|hsl_type
return|;
block|}
end_function

begin_function
specifier|static
name|GimpHSL
modifier|*
DECL|function|gimp_hsl_copy (const GimpHSL * hsl)
name|gimp_hsl_copy
parameter_list|(
specifier|const
name|GimpHSL
modifier|*
name|hsl
parameter_list|)
block|{
return|return
name|g_memdup
argument_list|(
name|hsl
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpHSL
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  HSL functions  */
end_comment

begin_comment
comment|/**  * gimp_hsl_set:  * @hsl:  * @h:  * @s:  * @l:  *  * Since: 2.8  **/
end_comment

begin_function
name|void
DECL|function|gimp_hsl_set (GimpHSL * hsl,gdouble h,gdouble s,gdouble l)
name|gimp_hsl_set
parameter_list|(
name|GimpHSL
modifier|*
name|hsl
parameter_list|,
name|gdouble
name|h
parameter_list|,
name|gdouble
name|s
parameter_list|,
name|gdouble
name|l
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|hsl
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hsl
operator|->
name|h
operator|=
name|h
expr_stmt|;
name|hsl
operator|->
name|s
operator|=
name|s
expr_stmt|;
name|hsl
operator|->
name|l
operator|=
name|l
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_hsl_set_alpha:  * @hsl:  * @a:  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_hsl_set_alpha (GimpHSL * hsl,gdouble a)
name|gimp_hsl_set_alpha
parameter_list|(
name|GimpHSL
modifier|*
name|hsl
parameter_list|,
name|gdouble
name|a
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|hsl
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hsl
operator|->
name|a
operator|=
name|a
expr_stmt|;
block|}
end_function

end_unit


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
file|"gimphsv.h"
end_include

begin_comment
comment|/*  * GIMP_TYPE_HSV  */
end_comment

begin_function_decl
specifier|static
name|GimpHSV
modifier|*
name|gimp_hsv_copy
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_hsv_get_type (void)
name|gimp_hsv_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|hsv_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|hsv_type
condition|)
name|hsv_type
operator|=
name|g_boxed_type_register_static
argument_list|(
literal|"GimpHSV"
argument_list|,
operator|(
name|GBoxedCopyFunc
operator|)
name|gimp_hsv_copy
argument_list|,
operator|(
name|GBoxedFreeFunc
operator|)
name|g_free
argument_list|)
expr_stmt|;
return|return
name|hsv_type
return|;
block|}
end_function

begin_function
specifier|static
name|GimpHSV
modifier|*
DECL|function|gimp_hsv_copy (const GimpHSV * hsv)
name|gimp_hsv_copy
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
return|return
name|g_memdup
argument_list|(
name|hsv
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpHSV
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  HSV functions  */
end_comment

begin_function
name|void
DECL|function|gimp_hsv_set (GimpHSV * hsv,gdouble h,gdouble s,gdouble v)
name|gimp_hsv_set
parameter_list|(
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|gdouble
name|h
parameter_list|,
name|gdouble
name|s
parameter_list|,
name|gdouble
name|v
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hsv
operator|->
name|h
operator|=
name|h
expr_stmt|;
name|hsv
operator|->
name|s
operator|=
name|s
expr_stmt|;
name|hsv
operator|->
name|v
operator|=
name|v
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_hsv_clamp (GimpHSV * hsv)
name|gimp_hsv_clamp
parameter_list|(
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|hsv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hsv
operator|->
name|h
operator|-=
operator|(
name|gint
operator|)
name|hsv
operator|->
name|h
expr_stmt|;
if|if
condition|(
name|hsv
operator|->
name|h
operator|<
literal|0
condition|)
name|hsv
operator|->
name|h
operator|+=
literal|1.0
expr_stmt|;
name|hsv
operator|->
name|s
operator|=
name|CLAMP
argument_list|(
name|hsv
operator|->
name|s
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|hsv
operator|->
name|v
operator|=
name|CLAMP
argument_list|(
name|hsv
operator|->
name|v
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|hsv
operator|->
name|a
operator|=
name|CLAMP
argument_list|(
name|hsv
operator|->
name|a
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_hsva_set (GimpHSV * hsva,gdouble h,gdouble s,gdouble v,gdouble a)
name|gimp_hsva_set
parameter_list|(
name|GimpHSV
modifier|*
name|hsva
parameter_list|,
name|gdouble
name|h
parameter_list|,
name|gdouble
name|s
parameter_list|,
name|gdouble
name|v
parameter_list|,
name|gdouble
name|a
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|hsva
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|hsva
operator|->
name|h
operator|=
name|h
expr_stmt|;
name|hsva
operator|->
name|s
operator|=
name|s
expr_stmt|;
name|hsva
operator|->
name|v
operator|=
name|v
expr_stmt|;
name|hsva
operator|->
name|a
operator|=
name|a
expr_stmt|;
block|}
end_function

end_unit


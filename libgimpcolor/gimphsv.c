begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimphsv  * @title: GimpHSV  * @short_description: Definitions and Functions relating to HSV colors.  *  * Definitions and Functions relating to HSV colors.  **/
end_comment

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

begin_macro
DECL|function|G_DEFINE_BOXED_TYPE (GimpHSV,gimp_hsv,gimp_hsv_copy,g_free)
name|G_DEFINE_BOXED_TYPE
argument_list|(
argument|GimpHSV
argument_list|,
argument|gimp_hsv
argument_list|,
argument|gimp_hsv_copy
argument_list|,
argument|g_free
argument_list|)
end_macro

begin_function
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


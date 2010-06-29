begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpchecks.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpchecks.h"
end_include

begin_comment
comment|/**  * SECTION: gimpchecks  * @title: gimpchecks  * @short_description: Constants and functions related to rendering  *                     checkerboards.  *  * Constants and functions related to rendering checkerboards.  **/
end_comment

begin_comment
comment|/**  * gimp_checks_get_shades:  * @type:  the checkerboard type  * @light: return location for the light shade  * @dark:  return location for the dark shade  *  * Retrieves the actual shades of gray to use when drawing a  * checkerboard for a certain #GimpCheckType.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_checks_get_shades (GimpCheckType type,guchar * light,guchar * dark)
name|gimp_checks_get_shades
parameter_list|(
name|GimpCheckType
name|type
parameter_list|,
name|guchar
modifier|*
name|light
parameter_list|,
name|guchar
modifier|*
name|dark
parameter_list|)
block|{
specifier|const
name|guchar
name|shades
index|[
literal|6
index|]
index|[
literal|2
index|]
init|=
block|{
block|{
literal|204
block|,
literal|255
block|}
block|,
comment|/*  LIGHT_CHECKS  */
block|{
literal|102
block|,
literal|153
block|}
block|,
comment|/*  GRAY_CHECKS   */
block|{
literal|0
block|,
literal|51
block|}
block|,
comment|/*  DARK_CHECKS   */
block|{
literal|255
block|,
literal|255
block|}
block|,
comment|/*  WHITE_ONLY    */
block|{
literal|127
block|,
literal|127
block|}
block|,
comment|/*  GRAY_ONLY     */
block|{
literal|0
block|,
literal|0
block|}
comment|/*  BLACK_ONLY    */
block|}
decl_stmt|;
name|type
operator|=
name|MIN
argument_list|(
name|type
argument_list|,
literal|5
argument_list|)
expr_stmt|;
if|if
condition|(
name|light
condition|)
operator|*
name|light
operator|=
name|shades
index|[
name|type
index|]
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|dark
condition|)
operator|*
name|dark
operator|=
name|shades
index|[
name|type
index|]
index|[
literal|0
index|]
expr_stmt|;
block|}
end_function

end_unit


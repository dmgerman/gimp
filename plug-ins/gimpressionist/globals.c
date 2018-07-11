begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_decl_stmt
DECL|variable|img_has_alpha
name|gboolean
name|img_has_alpha
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|random_generator
name|GRand
modifier|*
name|random_generator
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pcvals
name|gimpressionist_vals_t
name|pcvals
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * The default values for the application, to be initialized at startup.  * */
end_comment

begin_decl_stmt
DECL|variable|defaultpcvals
specifier|static
specifier|const
name|gimpressionist_vals_t
name|defaultpcvals
init|=
block|{
literal|4
block|,
literal|0.0
block|,
literal|60.0
block|,
literal|0
block|,
literal|12.0
block|,
literal|20.0
block|,
literal|20.0
block|,
literal|1.0
block|,
literal|1
block|,
literal|0.1
block|,
literal|0.0
block|,
literal|30.0
block|,
literal|0
block|,
literal|0
block|,
literal|"defaultbrush.pgm"
block|,
literal|"defaultpaper.pgm"
block|,
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1.0
block|}
block|,
literal|1
block|,
literal|0
block|,
block|{
block|{
literal|0.5
block|,
literal|0.5
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|0
block|}
block|}
block|,
literal|1
block|,
literal|0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|20.0
block|,
literal|1
block|,
literal|10.0
block|,
literal|20.0
block|,
literal|0
block|,
literal|0.1
block|,
block|{
block|{
literal|0.5
block|,
literal|0.5
block|,
literal|50.0
block|,
literal|1.0
block|}
block|}
block|,
literal|1
block|,
literal|1.0
block|,
literal|0
block|,
literal|10
block|,
literal|4
block|,
literal|0
block|,
literal|0.0
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|restore_default_values (void)
name|restore_default_values
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|=
name|defaultpcvals
expr_stmt|;
block|}
end_function

end_unit


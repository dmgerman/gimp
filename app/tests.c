begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"tests.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
end_include

begin_comment
comment|/**  * gimp_init_for_testing:  *  * Initialize the GIMP object system for unit testing. This is a  * selected subset of the initialization happning in app_run().  **/
end_comment

begin_function
name|Gimp
modifier|*
DECL|function|gimp_init_for_testing (void)
name|gimp_init_for_testing
parameter_list|(
name|void
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_new
argument_list|(
literal|"Unit Tested GIMP"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|units_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp
return|;
block|}
end_function

end_unit


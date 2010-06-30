begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpcageoptions.c  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcagetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcageoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCageOptions,gimp_cage_options,GIMP_TYPE_TRANSFORM_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCageOptions
argument_list|,
argument|gimp_cage_options
argument_list|,
argument|GIMP_TYPE_TRANSFORM_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cage_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_cage_options_class_init
parameter_list|(
name|GimpCageOptionsClass
modifier|*
name|klass
parameter_list|)
block|{   }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_options_init (GimpCageOptions * options)
name|gimp_cage_options_init
parameter_list|(
name|GimpCageOptions
modifier|*
name|options
parameter_list|)
block|{ 	 }
end_function

end_unit


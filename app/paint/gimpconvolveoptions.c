begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolveoptions.h"
end_include

begin_define
DECL|macro|DEFAULT_CONVOLVE_RATE
define|#
directive|define
name|DEFAULT_CONVOLVE_RATE
value|50.0
end_define

begin_define
DECL|macro|DEFAULT_CONVOLVE_TYPE
define|#
directive|define
name|DEFAULT_CONVOLVE_TYPE
value|GIMP_BLUR_CONVOLVE
end_define

begin_function_decl
specifier|static
name|void
name|gimp_convolve_options_init
parameter_list|(
name|GimpConvolveOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_options_class_init
parameter_list|(
name|GimpConvolveOptionsClass
modifier|*
name|options_class
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_convolve_options_get_type (void)
name|gimp_convolve_options_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpConvolveOptionsClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_convolve_options_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpConvolveOptions
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_convolve_options_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
literal|"GimpConvolveOptions"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_options_class_init (GimpConvolveOptionsClass * klass)
name|gimp_convolve_options_class_init
parameter_list|(
name|GimpConvolveOptionsClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_options_init (GimpConvolveOptions * options)
name|gimp_convolve_options_init
parameter_list|(
name|GimpConvolveOptions
modifier|*
name|options
parameter_list|)
block|{
name|options
operator|->
name|type
operator|=
name|options
operator|->
name|type_d
operator|=
name|DEFAULT_CONVOLVE_TYPE
expr_stmt|;
name|options
operator|->
name|rate
operator|=
name|options
operator|->
name|rate_d
operator|=
name|DEFAULT_CONVOLVE_RATE
expr_stmt|;
block|}
end_function

end_unit


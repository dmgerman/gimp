begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpnpointdeformationoptions.h  * Copyright (C) 2013 Marek Dvoroznak<dvoromar@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"gimpnpointdeformationoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_n_point_deformation_options_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_n_point_deformation_options_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpNPointDeformationOptions,gimp_n_point_deformation_options,GIMP_TYPE_TOOL_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpNPointDeformationOptions
argument_list|,
argument|gimp_n_point_deformation_options
argument_list|,
argument|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_n_point_deformation_options_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_n_point_deformation_options_class_init
parameter_list|(
name|GimpNPointDeformationOptionsClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_n_point_deformation_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_n_point_deformation_options_get_property
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_options_init (GimpNPointDeformationOptions * options)
name|gimp_n_point_deformation_options_init
parameter_list|(
name|GimpNPointDeformationOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_n_point_deformation_options_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
comment|//  GimpNPointDeformationOptions *options = GIMP_N_POINT_DEFORMATION_OPTIONS (object);
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_n_point_deformation_options_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
comment|//  GimpNPointDeformationOptions *options = GIMP_N_POINT_DEFORMATION_OPTIONS (object);
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_n_point_deformation_options_gui (GimpToolOptions * tool_options)
name|gimp_n_point_deformation_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
comment|//  GObject   *config = G_OBJECT (tool_options);
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit


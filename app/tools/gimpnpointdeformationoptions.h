begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpnpointdeformationoptions.h  * Copyright (C) 2013 Marek Dvoroznak<dvoromar@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_N_POINT_DEFORMATION_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_N_POINT_DEFORMATION_OPTIONS_H__
define|#
directive|define
name|__GIMP_N_POINT_DEFORMATION_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS
define|#
directive|define
name|GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS
value|(gimp_n_point_deformation_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_N_POINT_DEFORMATION_OPTIONS (obj)
define|#
directive|define
name|GIMP_N_POINT_DEFORMATION_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS, GimpNPointDeformationOptions))
end_define

begin_define
DECL|macro|GIMP_N_POINT_DEFORMATION_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_N_POINT_DEFORMATION_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS, GimpNPointDeformationOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_N_POINT_DEFORMATION_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_N_POINT_DEFORMATION_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_N_POINT_DEFORMATION_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_N_POINT_DEFORMATION_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_N_POINT_DEFORMATION_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_N_POINT_DEFORMATION_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS, GimpNPointDeformationOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpNPointDeformationOptions
typedef|typedef
name|struct
name|_GimpNPointDeformationOptions
name|GimpNPointDeformationOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpNPointDeformationOptionsClass
typedef|typedef
name|struct
name|_GimpNPointDeformationOptionsClass
name|GimpNPointDeformationOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpNPointDeformationOptions
struct|struct
name|_GimpNPointDeformationOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
DECL|member|square_size
name|gdouble
name|square_size
decl_stmt|;
DECL|member|rigidity
name|gdouble
name|rigidity
decl_stmt|;
DECL|member|ASAP_deformation
name|gboolean
name|ASAP_deformation
decl_stmt|;
DECL|member|MLS_weights
name|gboolean
name|MLS_weights
decl_stmt|;
DECL|member|MLS_weights_alpha
name|gdouble
name|MLS_weights_alpha
decl_stmt|;
DECL|member|mesh_visible
name|gboolean
name|mesh_visible
decl_stmt|;
DECL|member|scale_square_size
name|GtkWidget
modifier|*
name|scale_square_size
decl_stmt|;
DECL|member|scale_MLS_weights_alpha
name|GtkWidget
modifier|*
name|scale_MLS_weights_alpha
decl_stmt|;
DECL|member|check_mesh_visible
name|GtkWidget
modifier|*
name|check_mesh_visible
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpNPointDeformationOptionsClass
struct|struct
name|_GimpNPointDeformationOptionsClass
block|{
DECL|member|parent_class
name|GimpToolOptionsClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_n_point_deformation_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_n_point_deformation_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_n_point_deformation_options_set_sensitivity
parameter_list|(
name|GimpNPointDeformationOptions
modifier|*
name|npd_options
parameter_list|,
name|gboolean
name|tool_active
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_N_POINT_DEFORMATION_OPTIONS_H__  */
end_comment

end_unit


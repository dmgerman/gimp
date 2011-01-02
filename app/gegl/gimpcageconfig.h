begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpcageconfig.h  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CAGE_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CAGE_CONFIG_H__
define|#
directive|define
name|__GIMP_CAGE_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpimagemapconfig.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CAGE_CONFIG
define|#
directive|define
name|GIMP_TYPE_CAGE_CONFIG
value|(gimp_cage_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_CAGE_CONFIG (obj)
define|#
directive|define
name|GIMP_CAGE_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CAGE_CONFIG, GimpCageConfig))
end_define

begin_define
DECL|macro|GIMP_CAGE_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_CAGE_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CAGE_CONFIG, GimpCageConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_CAGE_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CAGE_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_CAGE_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CAGE_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CAGE_CONFIG))
end_define

begin_define
DECL|macro|GIMP_CAGE_CONFIG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CAGE_CONFIG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CAGE_CONFIG, GimpCageConfigClass))
end_define

begin_typedef
DECL|typedef|GimpCageConfigClass
typedef|typedef
name|struct
name|_GimpCageConfigClass
name|GimpCageConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCageConfig
struct|struct
name|_GimpCageConfig
block|{
DECL|member|parent_instance
name|GimpImageMapConfig
name|parent_instance
decl_stmt|;
DECL|member|n_cage_vertices
name|gint
name|n_cage_vertices
decl_stmt|;
comment|/* vertices used by the cage */
DECL|member|max_cage_vertices
name|gint
name|max_cage_vertices
decl_stmt|;
comment|/* vertices allocated        */
DECL|member|displacement_x
name|gdouble
name|displacement_x
decl_stmt|;
DECL|member|displacement_y
name|gdouble
name|displacement_y
decl_stmt|;
DECL|member|cage_mode
name|GimpCageMode
name|cage_mode
decl_stmt|;
comment|/* Cage mode, used to commit displacement */
DECL|member|cage_points
name|GimpCagePoint
modifier|*
name|cage_points
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCageConfigClass
struct|struct
name|_GimpCageConfigClass
block|{
DECL|member|parent_class
name|GimpImageMapConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_cage_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_cage_config_add_cage_point
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_remove_last_cage_point
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_cage_config_get_point_coordinate
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|GimpCageMode
name|mode
parameter_list|,
name|gint
name|point_number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_add_displacement
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|GimpCageMode
name|mode
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_commit_displacement
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_reset_displacement
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gimp_cage_config_get_bounding_box
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_reverse_cage_if_needed
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_reverse_cage
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_cage_config_point_inside
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|gfloat
name|x
parameter_list|,
name|gfloat
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_select_point
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|gint
name|point_number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_config_toggle_point_selection
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|,
name|gint
name|point_number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cage_deselect_points
parameter_list|(
name|GimpCageConfig
modifier|*
name|gcc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CAGE_CONFIG_H__ */
end_comment

end_unit


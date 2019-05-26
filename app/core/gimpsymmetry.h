begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsymmetry.h  * Copyright (C) 2015 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SYMMETRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SYMMETRY_H__
define|#
directive|define
name|__GIMP_SYMMETRY_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_comment
comment|/* shift one more than GIMP_CONFIG_PARAM_IGNORE */
end_comment

begin_define
DECL|macro|GIMP_SYMMETRY_PARAM_GUI
define|#
directive|define
name|GIMP_SYMMETRY_PARAM_GUI
value|(1<< (6 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_TYPE_SYMMETRY
define|#
directive|define
name|GIMP_TYPE_SYMMETRY
value|(gimp_symmetry_get_type ())
end_define

begin_define
DECL|macro|GIMP_SYMMETRY (obj)
define|#
directive|define
name|GIMP_SYMMETRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SYMMETRY, GimpSymmetry))
end_define

begin_define
DECL|macro|GIMP_SYMMETRY_CLASS (klass)
define|#
directive|define
name|GIMP_SYMMETRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SYMMETRY, GimpSymmetryClass))
end_define

begin_define
DECL|macro|GIMP_IS_SYMMETRY (obj)
define|#
directive|define
name|GIMP_IS_SYMMETRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SYMMETRY))
end_define

begin_define
DECL|macro|GIMP_IS_SYMMETRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SYMMETRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SYMMETRY))
end_define

begin_define
DECL|macro|GIMP_SYMMETRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SYMMETRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SYMMETRY, GimpSymmetryClass))
end_define

begin_typedef
DECL|typedef|GimpSymmetryClass
typedef|typedef
name|struct
name|_GimpSymmetryClass
name|GimpSymmetryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSymmetry
struct|struct
name|_GimpSymmetry
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|origin
name|GimpCoords
modifier|*
name|origin
decl_stmt|;
DECL|member|active
name|gboolean
name|active
decl_stmt|;
DECL|member|version
name|gint
name|version
decl_stmt|;
DECL|member|strokes
name|GList
modifier|*
name|strokes
decl_stmt|;
DECL|member|stateful
name|gboolean
name|stateful
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSymmetryClass
struct|struct
name|_GimpSymmetryClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
comment|/* Virtual functions */
DECL|member|update_strokes
name|void
function_decl|(
modifier|*
name|update_strokes
function_decl|)
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpCoords
modifier|*
name|origin
parameter_list|)
function_decl|;
DECL|member|get_operation
name|GeglNode
modifier|*
function_decl|(
modifier|*
name|get_operation
function_decl|)
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gint
name|paint_width
parameter_list|,
name|gint
name|paint_height
parameter_list|)
function_decl|;
DECL|member|get_transform
name|void
function_decl|(
modifier|*
name|get_transform
function_decl|)
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gdouble
modifier|*
name|angle
parameter_list|,
name|gboolean
modifier|*
name|reflect
parameter_list|)
function_decl|;
DECL|member|active_changed
name|void
function_decl|(
modifier|*
name|active_changed
function_decl|)
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
function_decl|;
DECL|member|update_version
name|gboolean
function_decl|(
modifier|*
name|update_version
function_decl|)
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_symmetry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_symmetry_set_stateful
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|gboolean
name|stateful
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_symmetry_set_origin
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpCoords
modifier|*
name|origin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_symmetry_clear_origin
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCoords
modifier|*
name|gimp_symmetry_get_origin
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_symmetry_get_size
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCoords
modifier|*
name|gimp_symmetry_get_coords
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|gint
name|stroke
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_symmetry_get_operation
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gint
name|paint_width
parameter_list|,
name|gint
name|paint_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_symmetry_get_transform
parameter_list|(
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|,
name|gint
name|stroke
parameter_list|,
name|gdouble
modifier|*
name|angle
parameter_list|,
name|gboolean
modifier|*
name|reflect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_symmetry_parasite_name
parameter_list|(
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_symmetry_to_parasite
parameter_list|(
specifier|const
name|GimpSymmetry
modifier|*
name|symmetry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSymmetry
modifier|*
name|gimp_symmetry_from_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SYMMETRY_H__  */
end_comment

end_unit


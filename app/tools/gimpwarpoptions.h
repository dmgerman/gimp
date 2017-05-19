begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpwarpoptions.h  * Copyright (C) 2011 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WARP_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WARP_OPTIONS_H__
define|#
directive|define
name|__GIMP_WARP_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_WARP_OPTIONS
define|#
directive|define
name|GIMP_TYPE_WARP_OPTIONS
value|(gimp_warp_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_WARP_OPTIONS (obj)
define|#
directive|define
name|GIMP_WARP_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_WARP_OPTIONS, GimpWarpOptions))
end_define

begin_define
DECL|macro|GIMP_WARP_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_WARP_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_WARP_OPTIONS, GimpWarpOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_WARP_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_WARP_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_WARP_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_WARP_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_WARP_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_WARP_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_WARP_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_WARP_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_WARP_OPTIONS, GimpWarpOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpWarpOptions
typedef|typedef
name|struct
name|_GimpWarpOptions
name|GimpWarpOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpWarpOptionsClass
typedef|typedef
name|struct
name|_GimpWarpOptionsClass
name|GimpWarpOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpWarpOptions
struct|struct
name|_GimpWarpOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
DECL|member|behavior
name|GimpWarpBehavior
name|behavior
decl_stmt|;
DECL|member|effect_size
name|gdouble
name|effect_size
decl_stmt|;
DECL|member|effect_hardness
name|gdouble
name|effect_hardness
decl_stmt|;
DECL|member|effect_strength
name|gdouble
name|effect_strength
decl_stmt|;
DECL|member|stroke_spacing
name|gdouble
name|stroke_spacing
decl_stmt|;
DECL|member|interpolation
name|GimpInterpolationType
name|interpolation
decl_stmt|;
DECL|member|abyss_policy
name|GeglAbyssPolicy
name|abyss_policy
decl_stmt|;
DECL|member|high_quality_preview
name|gboolean
name|high_quality_preview
decl_stmt|;
DECL|member|stroke_during_motion
name|gboolean
name|stroke_during_motion
decl_stmt|;
DECL|member|stroke_periodically
name|gboolean
name|stroke_periodically
decl_stmt|;
DECL|member|stroke_periodically_rate
name|gdouble
name|stroke_periodically_rate
decl_stmt|;
DECL|member|n_animation_frames
name|gint
name|n_animation_frames
decl_stmt|;
comment|/*  options gui  */
DECL|member|animate_button
name|GtkWidget
modifier|*
name|animate_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpWarpOptionsClass
struct|struct
name|_GimpWarpOptionsClass
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
name|gimp_warp_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_warp_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_WARP_OPTIONS_H__  */
end_comment

end_unit


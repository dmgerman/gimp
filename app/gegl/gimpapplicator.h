begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpapplicator.h  * Copyright (C) 2012-2013 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_APPLICATOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_APPLICATOR_H__
define|#
directive|define
name|__GIMP_APPLICATOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_APPLICATOR
define|#
directive|define
name|GIMP_TYPE_APPLICATOR
value|(gimp_applicator_get_type ())
end_define

begin_define
DECL|macro|GIMP_APPLICATOR (obj)
define|#
directive|define
name|GIMP_APPLICATOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_APPLICATOR, GimpApplicator))
end_define

begin_define
DECL|macro|GIMP_APPLICATOR_CLASS (klass)
define|#
directive|define
name|GIMP_APPLICATOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_APPLICATOR, GimpApplicatorClass))
end_define

begin_define
DECL|macro|GIMP_IS_APPLICATOR (obj)
define|#
directive|define
name|GIMP_IS_APPLICATOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_APPLICATOR))
end_define

begin_define
DECL|macro|GIMP_IS_APPLICATOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_APPLICATOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_APPLICATOR))
end_define

begin_define
DECL|macro|GIMP_APPLICATOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_APPLICATOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_APPLICATOR, GimpApplicatorClass))
end_define

begin_typedef
DECL|typedef|GimpApplicatorClass
typedef|typedef
name|struct
name|_GimpApplicatorClass
name|GimpApplicatorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpApplicator
struct|struct
name|_GimpApplicator
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|node
name|GeglNode
modifier|*
name|node
decl_stmt|;
DECL|member|input_node
name|GeglNode
modifier|*
name|input_node
decl_stmt|;
DECL|member|aux_node
name|GeglNode
modifier|*
name|aux_node
decl_stmt|;
DECL|member|output_node
name|GeglNode
modifier|*
name|output_node
decl_stmt|;
DECL|member|apply_buffer
name|GeglBuffer
modifier|*
name|apply_buffer
decl_stmt|;
DECL|member|apply_src_node
name|GeglNode
modifier|*
name|apply_src_node
decl_stmt|;
DECL|member|apply_offset_x
name|gint
name|apply_offset_x
decl_stmt|;
DECL|member|apply_offset_y
name|gint
name|apply_offset_y
decl_stmt|;
DECL|member|apply_offset_node
name|GeglNode
modifier|*
name|apply_offset_node
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|paint_mode
name|GimpLayerModeEffects
name|paint_mode
decl_stmt|;
DECL|member|mode_node
name|GeglNode
modifier|*
name|mode_node
decl_stmt|;
DECL|member|affect
name|GimpComponentMask
name|affect
decl_stmt|;
DECL|member|affect_node
name|GeglNode
modifier|*
name|affect_node
decl_stmt|;
DECL|member|src_buffer
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
DECL|member|src_node
name|GeglNode
modifier|*
name|src_node
decl_stmt|;
DECL|member|dest_buffer
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
DECL|member|dest_node
name|GeglNode
modifier|*
name|dest_node
decl_stmt|;
DECL|member|mask_buffer
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
DECL|member|mask_node
name|GeglNode
modifier|*
name|mask_node
decl_stmt|;
DECL|member|mask_offset_x
name|gint
name|mask_offset_x
decl_stmt|;
DECL|member|mask_offset_y
name|gint
name|mask_offset_y
decl_stmt|;
DECL|member|mask_offset_node
name|GeglNode
modifier|*
name|mask_offset_node
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpApplicatorClass
struct|struct
name|_GimpApplicatorClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_applicator_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpApplicator
modifier|*
name|gimp_applicator_new
parameter_list|(
name|GeglNode
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_src_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_dest_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_mask_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_mask_offset
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|gint
name|mask_offset_x
parameter_list|,
name|gint
name|mask_offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_apply_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|apply_buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_apply_offset
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|gint
name|apply_offset_x
parameter_list|,
name|gint
name|apply_offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_mode
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_set_affect
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GimpComponentMask
name|affect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_applicator_blit
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_APPLICATOR_H__  */
end_comment

end_unit


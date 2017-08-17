begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationlayermode.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_LAYER_MODE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_LAYER_MODE_H__
define|#
directive|define
name|__GIMP_OPERATION_LAYER_MODE_H__
end_define

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_LAYER_MODE
define|#
directive|define
name|GIMP_TYPE_OPERATION_LAYER_MODE
value|(gimp_operation_layer_mode_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_LAYER_MODE (obj)
define|#
directive|define
name|GIMP_OPERATION_LAYER_MODE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_LAYER_MODE, GimpOperationLayerMode))
end_define

begin_define
DECL|macro|GIMP_OPERATION_LAYER_MODE_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_LAYER_MODE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_LAYER_MODE, GimpOperationLayerModeClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_LAYER_MODE (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_LAYER_MODE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_LAYER_MODE))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_LAYER_MODE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_LAYER_MODE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_LAYER_MODE))
end_define

begin_define
DECL|macro|GIMP_OPERATION_LAYER_MODE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_LAYER_MODE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_LAYER_MODE, GimpOperationLayerModeClass))
end_define

begin_typedef
DECL|typedef|GimpOperationLayerModeClass
typedef|typedef
name|struct
name|_GimpOperationLayerModeClass
name|GimpOperationLayerModeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationLayerMode
struct|struct
name|_GimpOperationLayerMode
block|{
DECL|member|parent_instance
name|GeglOperationPointComposer3
name|parent_instance
decl_stmt|;
DECL|member|layer_mode
name|GimpLayerMode
name|layer_mode
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|blend_space
name|GimpLayerColorSpace
name|blend_space
decl_stmt|;
DECL|member|composite_space
name|GimpLayerColorSpace
name|composite_space
decl_stmt|;
DECL|member|composite_mode
name|GimpLayerCompositeMode
name|composite_mode
decl_stmt|;
DECL|member|real_composite_mode
name|GimpLayerCompositeMode
name|real_composite_mode
decl_stmt|;
DECL|member|function
name|GimpLayerModeFunc
name|function
decl_stmt|;
DECL|member|blend_function
name|GimpLayerModeBlendFunc
name|blend_function
decl_stmt|;
DECL|member|is_last_node
name|gboolean
name|is_last_node
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationLayerModeClass
struct|struct
name|_GimpOperationLayerModeClass
block|{
DECL|member|parent_class
name|GeglOperationPointComposer3Class
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|process
name|gboolean
function_decl|(
modifier|*
name|process
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|aux
parameter_list|,
name|void
modifier|*
name|mask
parameter_list|,
name|void
modifier|*
name|out
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
comment|/* Returns the composite region (any combination of the layer and the    * backdrop) that the layer mode affects.  Most modes only affect the    * overlapping region, and don't need to override this function.    */
DECL|member|get_affected_region
name|GimpLayerCompositeRegion
function_decl|(
modifier|*
name|get_affected_region
function_decl|)
parameter_list|(
name|GimpOperationLayerMode
modifier|*
name|layer_mode
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_layer_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpLayerCompositeRegion
name|gimp_operation_layer_mode_get_affected_region
parameter_list|(
name|GimpOperationLayerMode
modifier|*
name|layer_mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OPERATION_LAYER_MODE_H__ */
end_comment

end_unit


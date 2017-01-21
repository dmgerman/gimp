begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationlchhue.h  * Copyright (C) 2015 Elle Stone<ellestone@ninedegreesbelow.com>  *                    Massimo Valentini<mvalentini@src.gnome.org>  *                    Thomas Manni<thomas.manni@free.fr>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_LCH_HUE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_LCH_HUE_H__
define|#
directive|define
name|__GIMP_OPERATION_LCH_HUE_H__
end_define

begin_include
include|#
directive|include
file|"gimpoperationlayermode.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_LCH_HUE
define|#
directive|define
name|GIMP_TYPE_OPERATION_LCH_HUE
value|(gimp_operation_lch_hue_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_LCH_HUE (obj)
define|#
directive|define
name|GIMP_OPERATION_LCH_HUE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_LCH_HUE, GimpOperationLchHue))
end_define

begin_define
DECL|macro|GIMP_OPERATION_LCH_HUE_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_LCH_HUE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_LCH_HUE, GimpOperationLchHueClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_LCH_HUE (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_LCH_HUE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_LCH_HUE))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_LCH_HUE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_LCH_HUE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_LCH_HUE))
end_define

begin_define
DECL|macro|GIMP_OPERATION_LCH_HUE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_LCH_HUE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_LCH_HUE, GimpOperationLchHueClass))
end_define

begin_typedef
DECL|typedef|GimpOperationLchHue
typedef|typedef
name|struct
name|_GimpOperationLchHue
name|GimpOperationLchHue
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationLchHueClass
typedef|typedef
name|struct
name|_GimpOperationLchHueClass
name|GimpOperationLchHueClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationLchHue
struct|struct
name|_GimpOperationLchHue
block|{
DECL|member|parent_instance
name|GimpOperationLayerMode
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationLchHueClass
struct|struct
name|_GimpOperationLchHueClass
block|{
DECL|member|parent_class
name|GimpOperationLayerModeClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_lch_hue_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_operation_lch_hue_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|layer
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
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OPERATION_LCH_HUE_H__ */
end_comment

end_unit


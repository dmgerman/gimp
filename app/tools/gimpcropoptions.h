begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CROP_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CROP_OPTIONS_H__
define|#
directive|define
name|__GIMP_CROP_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CROP_OPTIONS
define|#
directive|define
name|GIMP_TYPE_CROP_OPTIONS
value|(gimp_crop_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_CROP_OPTIONS (obj)
define|#
directive|define
name|GIMP_CROP_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CROP_OPTIONS, GimpCropOptions))
end_define

begin_define
DECL|macro|GIMP_CROP_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_CROP_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CROP_OPTIONS, GimpCropOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_CROP_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_CROP_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CROP_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_CROP_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CROP_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CROP_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_CROP_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CROP_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CROP_OPTIONS, GimpCropOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpCropOptions
typedef|typedef
name|struct
name|_GimpCropOptions
name|GimpCropOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCropOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpCropOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCropOptions
struct|struct
name|_GimpCropOptions
block|{
DECL|member|parent_instence
name|GimpToolOptions
name|parent_instence
decl_stmt|;
comment|/* Work on the current layer rather than the image. */
DECL|member|layer_only
name|gboolean
name|layer_only
decl_stmt|;
comment|/* Allow the crop rectangle to be larger than the image/layer. This    * will resize the image/layer.    */
DECL|member|allow_growing
name|gboolean
name|allow_growing
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_crop_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_crop_options_gui
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
comment|/* __GIMP_CROP_OPTIONS_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * operations-enums.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__OPERATIONS_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__OPERATIONS_ENUMS_H__
define|#
directive|define
name|__OPERATIONS_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_LAYER_COLOR_SPACE
define|#
directive|define
name|GIMP_TYPE_LAYER_COLOR_SPACE
value|(gimp_layer_color_space_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_color_space_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2baca7db0103
block|{
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
name|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
block|,
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
name|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
block|,
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_LAB
name|GIMP_LAYER_COLOR_SPACE_LAB
block|, }
DECL|typedef|GimpLayerColorSpace
name|GimpLayerColorSpace
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_LAYER_COMPOSITE_MODE
define|#
directive|define
name|GIMP_TYPE_LAYER_COMPOSITE_MODE
value|(gimp_layer_composite_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_composite_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2baca7db0203
block|{
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_ATOP
name|GIMP_LAYER_COMPOSITE_SRC_ATOP
block|,
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_OVER
name|GIMP_LAYER_COMPOSITE_SRC_OVER
block|,
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_IN
name|GIMP_LAYER_COMPOSITE_SRC_IN
block|,
DECL|enumerator|GIMP_LAYER_COMPOSITE_DST_ATOP
name|GIMP_LAYER_COMPOSITE_DST_ATOP
DECL|typedef|GimpLayerCompositeMode
block|}
name|GimpLayerCompositeMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __OPERATIONS_ENUMS_H__ */
end_comment

end_unit


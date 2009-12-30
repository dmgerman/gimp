begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-types.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GEGL_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GEGL_TYPES_H__
define|#
directive|define
name|__GIMP_GEGL_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_comment
comment|/*  operations  */
end_comment

begin_typedef
DECL|typedef|GimpOperationTileSink
typedef|typedef
name|struct
name|_GimpOperationTileSink
name|GimpOperationTileSink
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationTileSource
typedef|typedef
name|struct
name|_GimpOperationTileSource
name|GimpOperationTileSource
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationPointFilter
typedef|typedef
name|struct
name|_GimpOperationPointFilter
name|GimpOperationPointFilter
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationColorBalance
typedef|typedef
name|struct
name|_GimpOperationColorBalance
name|GimpOperationColorBalance
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationColorize
typedef|typedef
name|struct
name|_GimpOperationColorize
name|GimpOperationColorize
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationCurves
typedef|typedef
name|struct
name|_GimpOperationCurves
name|GimpOperationCurves
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationDesaturate
typedef|typedef
name|struct
name|_GimpOperationDesaturate
name|GimpOperationDesaturate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationHueSaturation
typedef|typedef
name|struct
name|_GimpOperationHueSaturation
name|GimpOperationHueSaturation
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationLevels
typedef|typedef
name|struct
name|_GimpOperationLevels
name|GimpOperationLevels
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationPosterize
typedef|typedef
name|struct
name|_GimpOperationPosterize
name|GimpOperationPosterize
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationThreshold
typedef|typedef
name|struct
name|_GimpOperationThreshold
name|GimpOperationThreshold
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationPointLayerMode
typedef|typedef
name|struct
name|_GimpOperationPointLayerMode
name|GimpOperationPointLayerMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationDissolveMode
typedef|typedef
name|struct
name|_GimpOperationDissolveMode
name|GimpOperationDissolveMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationBehindMode
typedef|typedef
name|struct
name|_GimpOperationBehindMode
name|GimpOperationBehindMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationMultiplyMode
typedef|typedef
name|struct
name|_GimpOperationMultiplyMode
name|GimpOperationMultiplyMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationScreenMode
typedef|typedef
name|struct
name|_GimpOperationScreenMode
name|GimpOperationScreenMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationOverlayMode
typedef|typedef
name|struct
name|_GimpOperationOverlayMode
name|GimpOperationOverlayMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationDifferenceMode
typedef|typedef
name|struct
name|_GimpOperationDifferenceMode
name|GimpOperationDifferenceMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationAdditionMode
typedef|typedef
name|struct
name|_GimpOperationAdditionMode
name|GimpOperationAdditionMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationSubtractMode
typedef|typedef
name|struct
name|_GimpOperationSubtractMode
name|GimpOperationSubtractMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationDarkenOnlyMode
typedef|typedef
name|struct
name|_GimpOperationDarkenOnlyMode
name|GimpOperationDarkenOnlyMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationLightenOnlyMode
typedef|typedef
name|struct
name|_GimpOperationLightenOnlyMode
name|GimpOperationLightenOnlyMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationHueMode
typedef|typedef
name|struct
name|_GimpOperationHueMode
name|GimpOperationHueMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationSaturationMode
typedef|typedef
name|struct
name|_GimpOperationSaturationMode
name|GimpOperationSaturationMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationColorMode
typedef|typedef
name|struct
name|_GimpOperationColorMode
name|GimpOperationColorMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationValueMode
typedef|typedef
name|struct
name|_GimpOperationValueMode
name|GimpOperationValueMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationDivideMode
typedef|typedef
name|struct
name|_GimpOperationDivideMode
name|GimpOperationDivideMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationDodgeMode
typedef|typedef
name|struct
name|_GimpOperationDodgeMode
name|GimpOperationDodgeMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationBurnMode
typedef|typedef
name|struct
name|_GimpOperationBurnMode
name|GimpOperationBurnMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationHardlightMode
typedef|typedef
name|struct
name|_GimpOperationHardlightMode
name|GimpOperationHardlightMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationSoftlightMode
typedef|typedef
name|struct
name|_GimpOperationSoftlightMode
name|GimpOperationSoftlightMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationGrainExtractMode
typedef|typedef
name|struct
name|_GimpOperationGrainExtractMode
name|GimpOperationGrainExtractMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationGrainMergeMode
typedef|typedef
name|struct
name|_GimpOperationGrainMergeMode
name|GimpOperationGrainMergeMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationColorEraseMode
typedef|typedef
name|struct
name|_GimpOperationColorEraseMode
name|GimpOperationColorEraseMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationEraseMode
typedef|typedef
name|struct
name|_GimpOperationEraseMode
name|GimpOperationEraseMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationReplaceMode
typedef|typedef
name|struct
name|_GimpOperationReplaceMode
name|GimpOperationReplaceMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationAntiEraseMode
typedef|typedef
name|struct
name|_GimpOperationAntiEraseMode
name|GimpOperationAntiEraseMode
typedef|;
end_typedef

begin_comment
comment|/*  operation config objects  */
end_comment

begin_typedef
DECL|typedef|GimpBrightnessContrastConfig
typedef|typedef
name|struct
name|_GimpBrightnessContrastConfig
name|GimpBrightnessContrastConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorBalanceConfig
typedef|typedef
name|struct
name|_GimpColorBalanceConfig
name|GimpColorBalanceConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorizeConfig
typedef|typedef
name|struct
name|_GimpColorizeConfig
name|GimpColorizeConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCurvesConfig
typedef|typedef
name|struct
name|_GimpCurvesConfig
name|GimpCurvesConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDesaturateConfig
typedef|typedef
name|struct
name|_GimpDesaturateConfig
name|GimpDesaturateConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHueSaturationConfig
typedef|typedef
name|struct
name|_GimpHueSaturationConfig
name|GimpHueSaturationConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLevelsConfig
typedef|typedef
name|struct
name|_GimpLevelsConfig
name|GimpLevelsConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPosterizeConfig
typedef|typedef
name|struct
name|_GimpPosterizeConfig
name|GimpPosterizeConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThresholdConfig
typedef|typedef
name|struct
name|_GimpThresholdConfig
name|GimpThresholdConfig
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GEGL_TYPES_H__ */
end_comment

end_unit


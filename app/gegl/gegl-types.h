begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gegl-types.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GEGL_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GEGL_TYPES_H__
define|#
directive|define
name|__GEGL_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gegl-types.h"
end_include

begin_comment
comment|/*  operations  */
end_comment

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

begin_comment
comment|/*  operation config objects  */
end_comment

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
comment|/* __GEGL_TYPES_H__ */
end_comment

end_unit


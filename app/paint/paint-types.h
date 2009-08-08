begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_TYPES_H__
end_ifndef

begin_define
DECL|macro|__PAINT_TYPES_H__
define|#
directive|define
name|__PAINT_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/paint-enums.h"
end_include

begin_comment
comment|/*  paint cores  */
end_comment

begin_typedef
DECL|typedef|GimpPaintCore
typedef|typedef
name|struct
name|_GimpPaintCore
name|GimpPaintCore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushCore
typedef|typedef
name|struct
name|_GimpBrushCore
name|GimpBrushCore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSourceCore
typedef|typedef
name|struct
name|_GimpSourceCore
name|GimpSourceCore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpAirbrush
typedef|typedef
name|struct
name|_GimpAirbrush
name|GimpAirbrush
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpClone
typedef|typedef
name|struct
name|_GimpClone
name|GimpClone
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpConvolve
typedef|typedef
name|struct
name|_GimpConvolve
name|GimpConvolve
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDodgeBurn
typedef|typedef
name|struct
name|_GimpDodgeBurn
name|GimpDodgeBurn
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEraser
typedef|typedef
name|struct
name|_GimpEraser
name|GimpEraser
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHeal
typedef|typedef
name|struct
name|_GimpHeal
name|GimpHeal
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpInk
typedef|typedef
name|struct
name|_GimpInk
name|GimpInk
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPaintbrush
typedef|typedef
name|struct
name|_GimpPaintbrush
name|GimpPaintbrush
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPencil
typedef|typedef
name|struct
name|_GimpPencil
name|GimpPencil
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPerspectiveClone
typedef|typedef
name|struct
name|_GimpPerspectiveClone
name|GimpPerspectiveClone
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSmudge
typedef|typedef
name|struct
name|_GimpSmudge
name|GimpSmudge
typedef|;
end_typedef

begin_comment
comment|/*  paint options  */
end_comment

begin_typedef
DECL|typedef|GimpPaintOptions
typedef|typedef
name|struct
name|_GimpPaintOptions
name|GimpPaintOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSourceOptions
typedef|typedef
name|struct
name|_GimpSourceOptions
name|GimpSourceOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDynamicsOptions
typedef|typedef
name|struct
name|_GimpDynamicsOptions
name|GimpDynamicsOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpAirbrushOptions
typedef|typedef
name|struct
name|_GimpAirbrushOptions
name|GimpAirbrushOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCloneOptions
typedef|typedef
name|struct
name|_GimpCloneOptions
name|GimpCloneOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpConvolveOptions
typedef|typedef
name|struct
name|_GimpConvolveOptions
name|GimpConvolveOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDodgeBurnOptions
typedef|typedef
name|struct
name|_GimpDodgeBurnOptions
name|GimpDodgeBurnOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEraserOptions
typedef|typedef
name|struct
name|_GimpEraserOptions
name|GimpEraserOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpInkOptions
typedef|typedef
name|struct
name|_GimpInkOptions
name|GimpInkOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPencilOptions
typedef|typedef
name|struct
name|_GimpPencilOptions
name|GimpPencilOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPerspectiveCloneOptions
typedef|typedef
name|struct
name|_GimpPerspectiveCloneOptions
name|GimpPerspectiveCloneOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSmudgeOptions
typedef|typedef
name|struct
name|_GimpSmudgeOptions
name|GimpSmudgeOptions
typedef|;
end_typedef

begin_comment
comment|/*  paint undos  */
end_comment

begin_typedef
DECL|typedef|GimpPaintCoreUndo
typedef|typedef
name|struct
name|_GimpPaintCoreUndo
name|GimpPaintCoreUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpInkUndo
typedef|typedef
name|struct
name|_GimpInkUndo
name|GimpInkUndo
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|GimpPaintRegisterCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpPaintRegisterCallback
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|paint_type
parameter_list|,
name|GType
name|paint_options_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpPaintRegisterFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpPaintRegisterFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PAINT_TYPES_H__ */
end_comment

end_unit


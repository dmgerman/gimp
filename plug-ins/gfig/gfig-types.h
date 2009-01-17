begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GFIG_ENUMS_H__
define|#
directive|define
name|__GFIG_ENUMS_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0103
block|{
DECL|enumerator|RECT_GRID
name|RECT_GRID
init|=
literal|0
block|,
DECL|enumerator|POLAR_GRID
name|POLAR_GRID
block|,
DECL|enumerator|ISO_GRID
name|ISO_GRID
DECL|typedef|GridType
block|}
name|GridType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0203
block|{
DECL|enumerator|ADD
name|ADD
init|=
literal|0
block|,
DECL|enumerator|SUBTRACT
name|SUBTRACT
block|,
DECL|enumerator|REPLACE
name|REPLACE
block|,
DECL|enumerator|INTERSECT
name|INTERSECT
DECL|typedef|SelectionType
block|}
name|SelectionType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0303
block|{
DECL|enumerator|ARC_SEGMENT
name|ARC_SEGMENT
init|=
literal|0
block|,
DECL|enumerator|ARC_SECTOR
name|ARC_SECTOR
DECL|typedef|ArcType
block|}
name|ArcType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0403
block|{
DECL|enumerator|FILL_NONE
name|FILL_NONE
init|=
literal|0
block|,
DECL|enumerator|FILL_COLOR
name|FILL_COLOR
block|,
DECL|enumerator|FILL_PATTERN
name|FILL_PATTERN
block|,
DECL|enumerator|FILL_GRADIENT
name|FILL_GRADIENT
block|,
DECL|enumerator|FILL_VERTICAL
name|FILL_VERTICAL
block|,
DECL|enumerator|FILL_HORIZONTAL
name|FILL_HORIZONTAL
DECL|typedef|FillType
block|}
name|FillType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0503
block|{
DECL|enumerator|ORIGINAL_LAYER
name|ORIGINAL_LAYER
init|=
literal|0
block|,
DECL|enumerator|SINGLE_LAYER
name|SINGLE_LAYER
block|,
DECL|enumerator|MULTI_LAYER
name|MULTI_LAYER
DECL|typedef|DrawonLayers
block|}
name|DrawonLayers
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0603
block|{
DECL|enumerator|LAYER_TRANS_BG
name|LAYER_TRANS_BG
init|=
literal|0
block|,
DECL|enumerator|LAYER_BG_BG
name|LAYER_BG_BG
block|,
DECL|enumerator|LAYER_FG_BG
name|LAYER_FG_BG
block|,
DECL|enumerator|LAYER_WHITE_BG
name|LAYER_WHITE_BG
block|,
DECL|enumerator|LAYER_COPY_BG
name|LAYER_COPY_BG
DECL|typedef|LayersBGType
block|}
name|LayersBGType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0703
block|{
DECL|enumerator|PAINT_NONE
name|PAINT_NONE
init|=
literal|0
block|,
DECL|enumerator|PAINT_BRUSH_TYPE
name|PAINT_BRUSH_TYPE
init|=
literal|1
DECL|typedef|PaintType
block|}
name|PaintType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0803
block|{
DECL|enumerator|BRUSH_BRUSH_TYPE
name|BRUSH_BRUSH_TYPE
init|=
literal|0
block|,
DECL|enumerator|BRUSH_PENCIL_TYPE
name|BRUSH_PENCIL_TYPE
block|,
DECL|enumerator|BRUSH_AIRBRUSH_TYPE
name|BRUSH_AIRBRUSH_TYPE
block|,
DECL|enumerator|BRUSH_PATTERN_TYPE
name|BRUSH_PATTERN_TYPE
DECL|typedef|BrushType
block|}
name|BrushType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29a4b87a0903
block|{
DECL|enumerator|OBJ_TYPE_NONE
name|OBJ_TYPE_NONE
init|=
literal|0
block|,
DECL|enumerator|LINE
name|LINE
block|,
DECL|enumerator|RECTANGLE
name|RECTANGLE
block|,
DECL|enumerator|CIRCLE
name|CIRCLE
block|,
DECL|enumerator|ELLIPSE
name|ELLIPSE
block|,
DECL|enumerator|ARC
name|ARC
block|,
DECL|enumerator|POLY
name|POLY
block|,
DECL|enumerator|STAR
name|STAR
block|,
DECL|enumerator|SPIRAL
name|SPIRAL
block|,
DECL|enumerator|BEZIER
name|BEZIER
block|,
DECL|enumerator|NUM_OBJ_TYPES
name|NUM_OBJ_TYPES
block|,
DECL|enumerator|MOVE_OBJ
name|MOVE_OBJ
block|,
DECL|enumerator|MOVE_POINT
name|MOVE_POINT
block|,
DECL|enumerator|COPY_OBJ
name|COPY_OBJ
block|,
DECL|enumerator|MOVE_COPY_OBJ
name|MOVE_COPY_OBJ
block|,
DECL|enumerator|DEL_OBJ
name|DEL_OBJ
block|,
DECL|enumerator|SELECT_OBJ
name|SELECT_OBJ
block|,
DECL|enumerator|NULL_OPER
name|NULL_OPER
DECL|typedef|DobjType
block|}
name|DobjType
typedef|;
end_typedef

begin_typedef
DECL|typedef|GFigObj
typedef|typedef
name|struct
name|_GFigObj
name|GFigObj
typedef|;
end_typedef

begin_typedef
DECL|typedef|GfigObject
typedef|typedef
name|struct
name|_GfigObject
name|GfigObject
typedef|;
end_typedef

begin_typedef
DECL|typedef|Style
typedef|typedef
name|struct
name|_Style
name|Style
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GFIG_ENUMS_H__ */
end_comment

end_unit


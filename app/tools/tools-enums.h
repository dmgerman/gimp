begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOLS_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__TOOLS_ENUMS_H__
define|#
directive|define
name|__TOOLS_ENUMS_H__
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|This file is parsed by two scripts, enumgen.pl in tools/pdbgen    and gimp-mkenums. All enums that are not marked with
comment|/*< pdb-skip>*/
end_comment

begin_comment
unit|are exported to libgimp and the PDB. Enums that are not marked with
comment|/*< skip>*/
end_comment

begin_comment
unit|are registered with the GType system. If you want the    enum to be skipped by both scripts, you have to use
comment|/*< pdb-skip>*/
end_comment

begin_comment
unit|_before_
comment|/*< skip>*/
end_comment

begin_comment
unit|.      All enum values that are marked with
comment|/*< skip>*/
end_comment

begin_endif
unit|are skipped for    both targets.
endif|#
directive|endif
end_endif

begin_comment
comment|/*   * these enums that are registered with the type system  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_CROP_TYPE
define|#
directive|define
name|GIMP_TYPE_CROP_TYPE
value|(gimp_crop_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_crop_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2742d5650103
block|{
DECL|enumerator|GIMP_CROP
name|GIMP_CROP
block|,
comment|/*< desc="Crop">*/
DECL|enumerator|GIMP_RESIZE
name|GIMP_RESIZE
comment|/*< desc="Resize">*/
DECL|typedef|GimpCropType
block|}
name|GimpCropType
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2742d5650203
block|{
DECL|enumerator|SELECTION_ADD
name|SELECTION_ADD
init|=
name|GIMP_CHANNEL_OP_ADD
block|,
DECL|enumerator|SELECTION_SUBTRACT
name|SELECTION_SUBTRACT
init|=
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
DECL|enumerator|SELECTION_REPLACE
name|SELECTION_REPLACE
init|=
name|GIMP_CHANNEL_OP_REPLACE
block|,
DECL|enumerator|SELECTION_INTERSECT
name|SELECTION_INTERSECT
init|=
name|GIMP_CHANNEL_OP_INTERSECT
block|,
DECL|enumerator|SELECTION_MOVE_MASK
name|SELECTION_MOVE_MASK
block|,
DECL|enumerator|SELECTION_MOVE
name|SELECTION_MOVE
block|,
DECL|enumerator|SELECTION_ANCHOR
name|SELECTION_ANCHOR
DECL|typedef|SelectOps
block|}
name|SelectOps
typedef|;
end_typedef

begin_comment
comment|/*  The possible states for tools  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2742d5650303
block|{
DECL|enumerator|INACTIVE
name|INACTIVE
block|,
DECL|enumerator|ACTIVE
name|ACTIVE
DECL|typedef|GimpToolState
block|}
name|GimpToolState
typedef|;
end_typedef

begin_comment
comment|/*  Tool control actions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2742d5650403
block|{
DECL|enumerator|PAUSE
name|PAUSE
block|,
DECL|enumerator|RESUME
name|RESUME
block|,
DECL|enumerator|HALT
name|HALT
DECL|typedef|GimpToolAction
block|}
name|GimpToolAction
typedef|;
end_typedef

begin_comment
comment|/*  Motion event report modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2742d5650503
block|{
DECL|enumerator|GIMP_MOTION_MODE_EXACT
name|GIMP_MOTION_MODE_EXACT
block|,
DECL|enumerator|GIMP_MOTION_MODE_HINT
name|GIMP_MOTION_MODE_HINT
block|,
DECL|enumerator|GIMP_MOTION_MODE_COMPRESS
name|GIMP_MOTION_MODE_COMPRESS
DECL|typedef|GimpMotionMode
block|}
name|GimpMotionMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RECT_SELECT_MODE
define|#
directive|define
name|GIMP_TYPE_RECT_SELECT_MODE
value|(gimp_rect_select_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_rect_select_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2742d5650603
block|{
DECL|enumerator|GIMP_RECT_SELECT_MODE_FREE
name|GIMP_RECT_SELECT_MODE_FREE
block|,
comment|/*< desc="Free Select">*/
DECL|enumerator|GIMP_RECT_SELECT_MODE_FIXED_SIZE
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
block|,
comment|/*< desc="Fixed Size">*/
DECL|enumerator|GIMP_RECT_SELECT_MODE_FIXED_RATIO
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
comment|/*< desc="Fixed Aspect Ratio">*/
DECL|typedef|GimpRectSelectMode
block|}
name|GimpRectSelectMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_GRID_TYPE
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_GRID_TYPE
value|(gimp_transform_grid_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_grid_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2742d5650703
block|{
DECL|enumerator|GIMP_TRANSFORM_GRID_TYPE_NONE
name|GIMP_TRANSFORM_GRID_TYPE_NONE
block|,
comment|/*< desc="Don't Show Grid">*/
DECL|enumerator|GIMP_TRANSFORM_GRID_TYPE_N_LINES
name|GIMP_TRANSFORM_GRID_TYPE_N_LINES
block|,
comment|/*< desc="Number of Grid Lines">*/
DECL|enumerator|GIMP_TRANSFORM_GRID_TYPE_SPACING
name|GIMP_TRANSFORM_GRID_TYPE_SPACING
comment|/*< desc="Grid Line Spacing">*/
DECL|typedef|GimpTransformGridType
block|}
name|GimpTransformGridType
typedef|;
end_typedef

begin_comment
comment|/*  Possible transform functions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2742d5650803
block|{
DECL|enumerator|TRANSFORM_CREATING
name|TRANSFORM_CREATING
block|,
DECL|enumerator|TRANSFORM_HANDLE_1
name|TRANSFORM_HANDLE_1
block|,
DECL|enumerator|TRANSFORM_HANDLE_2
name|TRANSFORM_HANDLE_2
block|,
DECL|enumerator|TRANSFORM_HANDLE_3
name|TRANSFORM_HANDLE_3
block|,
DECL|enumerator|TRANSFORM_HANDLE_4
name|TRANSFORM_HANDLE_4
block|,
DECL|enumerator|TRANSFORM_HANDLE_CENTER
name|TRANSFORM_HANDLE_CENTER
DECL|typedef|TransformAction
block|}
name|TransformAction
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TOOLS_ENUMS_H__ */
end_comment

end_unit


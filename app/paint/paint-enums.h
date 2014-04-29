begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__PAINT_ENUMS_H__
define|#
directive|define
name|__PAINT_ENUMS_H__
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|This file is parsed by two scripts, enumgen.pl in tools/pdbgen,    and gimp-mkenums. All enums that are not marked with
comment|/*< pdb-skip>*/
end_comment

begin_comment
unit|are exported to libgimp and the PDB. Enums that are    not marked with
comment|/*< skip>*/
end_comment

begin_comment
unit|are registered with the GType system.    If you want the enum to be skipped by both scripts, you have to use
comment|/*< pdb-skip, skip>*/
end_comment

begin_endif
unit|.     The same syntax applies to enum values.
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * enums that are registered with the type system  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_BRUSH_APPLICATION_MODE
define|#
directive|define
name|GIMP_TYPE_BRUSH_APPLICATION_MODE
value|(gimp_brush_application_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_brush_application_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29aded2c0103
block|{
DECL|enumerator|GIMP_BRUSH_HARD
name|GIMP_BRUSH_HARD
block|,
DECL|enumerator|GIMP_BRUSH_SOFT
name|GIMP_BRUSH_SOFT
block|,
DECL|enumerator|GIMP_BRUSH_PRESSURE
name|GIMP_BRUSH_PRESSURE
comment|/*< pdb-skip, skip>*/
DECL|typedef|GimpBrushApplicationMode
block|}
name|GimpBrushApplicationMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PERSPECTIVE_CLONE_MODE
define|#
directive|define
name|GIMP_TYPE_PERSPECTIVE_CLONE_MODE
value|(gimp_perspective_clone_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_perspective_clone_mode_get_type
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
DECL|enum|__anon29aded2c0203
block|{
DECL|enumerator|GIMP_PERSPECTIVE_CLONE_MODE_ADJUST
name|GIMP_PERSPECTIVE_CLONE_MODE_ADJUST
block|,
comment|/*< desc="Modify Perspective">*/
DECL|enumerator|GIMP_PERSPECTIVE_CLONE_MODE_PAINT
name|GIMP_PERSPECTIVE_CLONE_MODE_PAINT
comment|/*< desc="Perspective Clone">*/
DECL|typedef|GimpPerspectiveCloneMode
block|}
name|GimpPerspectiveCloneMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_SOURCE_ALIGN_MODE
define|#
directive|define
name|GIMP_TYPE_SOURCE_ALIGN_MODE
value|(gimp_source_align_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_source_align_mode_get_type
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
DECL|enum|__anon29aded2c0303
block|{
DECL|enumerator|GIMP_SOURCE_ALIGN_NO
name|GIMP_SOURCE_ALIGN_NO
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_SOURCE_ALIGN_YES
name|GIMP_SOURCE_ALIGN_YES
block|,
comment|/*< desc="Aligned">*/
DECL|enumerator|GIMP_SOURCE_ALIGN_REGISTERED
name|GIMP_SOURCE_ALIGN_REGISTERED
block|,
comment|/*< desc="Registered">*/
DECL|enumerator|GIMP_SOURCE_ALIGN_FIXED
name|GIMP_SOURCE_ALIGN_FIXED
comment|/*< desc="Fixed">*/
DECL|typedef|GimpSourceAlignMode
block|}
name|GimpSourceAlignMode
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip, pdb-skip>*/
DECL|enum|__anon29aded2c0403
block|{
DECL|enumerator|GIMP_PAINT_STATE_INIT
name|GIMP_PAINT_STATE_INIT
block|,
comment|/*  Setup PaintFunc internals                    */
DECL|enumerator|GIMP_PAINT_STATE_MOTION
name|GIMP_PAINT_STATE_MOTION
block|,
comment|/*  PaintFunc performs motion-related rendering  */
DECL|enumerator|GIMP_PAINT_STATE_FINISH
name|GIMP_PAINT_STATE_FINISH
comment|/*  Cleanup and/or reset PaintFunc operation     */
DECL|typedef|GimpPaintState
block|}
name|GimpPaintState
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PAINT_ENUMS_H__ */
end_comment

end_unit


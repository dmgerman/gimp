begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|macro|GIMP_TYPE_CLONE_TYPE
define|#
directive|define
name|GIMP_TYPE_CLONE_TYPE
value|(gimp_clone_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_clone_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2948a8080103
block|{
DECL|enumerator|GIMP_IMAGE_CLONE
name|GIMP_IMAGE_CLONE
block|,
comment|/*< desc="Image Source">*/
DECL|enumerator|GIMP_PATTERN_CLONE
name|GIMP_PATTERN_CLONE
comment|/*< desc="Pattern Source">*/
DECL|typedef|GimpCloneType
block|}
name|GimpCloneType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CLONE_ALIGN_MODE
define|#
directive|define
name|GIMP_TYPE_CLONE_ALIGN_MODE
value|(gimp_clone_align_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_clone_align_mode_get_type
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
DECL|enum|__anon2948a8080203
block|{
DECL|enumerator|GIMP_CLONE_ALIGN_NO
name|GIMP_CLONE_ALIGN_NO
block|,
comment|/*< desc="Non Aligned">*/
DECL|enumerator|GIMP_CLONE_ALIGN_YES
name|GIMP_CLONE_ALIGN_YES
block|,
comment|/*< desc="Aligned">*/
DECL|enumerator|GIMP_CLONE_ALIGN_REGISTERED
name|GIMP_CLONE_ALIGN_REGISTERED
comment|/*< desc="Registered">*/
DECL|typedef|GimpCloneAlignMode
block|}
name|GimpCloneAlignMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DODGE_BURN_TYPE
define|#
directive|define
name|GIMP_TYPE_DODGE_BURN_TYPE
value|(gimp_dodge_burn_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_dodge_burn_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2948a8080303
block|{
DECL|enumerator|GIMP_DODGE
name|GIMP_DODGE
block|,
comment|/*< desc="Dodge">*/
DECL|enumerator|GIMP_BURN
name|GIMP_BURN
comment|/*< desc="Burn">*/
DECL|typedef|GimpDodgeBurnType
block|}
name|GimpDodgeBurnType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_PAINT_MODE
define|#
directive|define
name|GIMP_TYPE_GRADIENT_PAINT_MODE
value|(gimp_gradient_paint_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_paint_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2948a8080403
block|{
DECL|enumerator|GIMP_GRADIENT_ONCE_FORWARD
name|GIMP_GRADIENT_ONCE_FORWARD
block|,
comment|/*< desc="Once Forward">*/
DECL|enumerator|GIMP_GRADIENT_ONCE_BACKWARD
name|GIMP_GRADIENT_ONCE_BACKWARD
block|,
comment|/*< desc="Once Backward">*/
DECL|enumerator|GIMP_GRADIENT_LOOP_SAWTOOTH
name|GIMP_GRADIENT_LOOP_SAWTOOTH
block|,
comment|/*< desc="Loop Sawtooth">*/
DECL|enumerator|GIMP_GRADIENT_LOOP_TRIANGLE
name|GIMP_GRADIENT_LOOP_TRIANGLE
comment|/*< desc="Loop Triangle">*/
DECL|typedef|GimpGradientPaintMode
block|}
name|GimpGradientPaintMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONVOLVE_TYPE
define|#
directive|define
name|GIMP_TYPE_CONVOLVE_TYPE
value|(gimp_convolve_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convolve_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2948a8080503
block|{
DECL|enumerator|GIMP_BLUR_CONVOLVE
name|GIMP_BLUR_CONVOLVE
block|,
comment|/*< desc="Blur">*/
DECL|enumerator|GIMP_SHARPEN_CONVOLVE
name|GIMP_SHARPEN_CONVOLVE
block|,
comment|/*< desc="Sharpen">*/
DECL|enumerator|GIMP_CUSTOM_CONVOLVE
name|GIMP_CUSTOM_CONVOLVE
comment|/*< skip>*/
DECL|typedef|GimpConvolveType
block|}
name|GimpConvolveType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_INK_BLOB_TYPE
define|#
directive|define
name|GIMP_TYPE_INK_BLOB_TYPE
value|(gimp_ink_blob_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_ink_blob_type_get_type
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
DECL|enum|__anon2948a8080603
block|{
DECL|enumerator|GIMP_INK_BLOB_TYPE_ELLIPSE
name|GIMP_INK_BLOB_TYPE_ELLIPSE
block|,
DECL|enumerator|GIMP_INK_BLOB_TYPE_SQUARE
name|GIMP_INK_BLOB_TYPE_SQUARE
block|,
DECL|enumerator|GIMP_INK_BLOB_TYPE_DIAMOND
name|GIMP_INK_BLOB_TYPE_DIAMOND
DECL|typedef|GimpInkBlobType
block|}
name|GimpInkBlobType
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2948a8080703
block|{
DECL|enumerator|GIMP_BRUSH_HARD
name|GIMP_BRUSH_HARD
block|,
DECL|enumerator|GIMP_BRUSH_SOFT
name|GIMP_BRUSH_SOFT
block|,
DECL|enumerator|GIMP_BRUSH_PRESSURE
name|GIMP_BRUSH_PRESSURE
comment|/*< skip>*/
DECL|typedef|GimpBrushApplicationMode
block|}
name|GimpBrushApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2948a8080803
block|{
DECL|enumerator|GIMP_PAINT_CONSTANT
name|GIMP_PAINT_CONSTANT
block|,
DECL|enumerator|GIMP_PAINT_INCREMENTAL
name|GIMP_PAINT_INCREMENTAL
DECL|typedef|GimpPaintApplicationMode
block|}
name|GimpPaintApplicationMode
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


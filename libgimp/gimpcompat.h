begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcompat.h  * Compatibility defines to ease migration from the GIMP-1.2 API  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPAT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPAT_H__
define|#
directive|define
name|__GIMP_COMPAT_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_ENABLE_COMPAT_CRUFT
end_ifdef

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* This file contains aliases that are kept for historical  * reasons, because a wide code base depends on them.  *  * These defines will be removed in the next development cycle.   */
DECL|macro|GimpRunModeType
define|#
directive|define
name|GimpRunModeType
value|GimpRunMode
DECL|macro|gimp_use_xshm
define|#
directive|define
name|gimp_use_xshm
value|TRUE
DECL|macro|gimp_color_cube
define|#
directive|define
name|gimp_color_cube
value|((guchar *) { 6, 6, 4, 24 })
DECL|macro|gimp_crop
define|#
directive|define
name|gimp_crop
value|gimp_image_crop
DECL|macro|gimp_gradients_get_active
define|#
directive|define
name|gimp_gradients_get_active
value|gimp_gradients_get_gradient
DECL|macro|gimp_gradients_set_active
define|#
directive|define
name|gimp_gradients_set_active
value|gimp_gradients_set_gradient
DECL|macro|gimp_help_init ()
define|#
directive|define
name|gimp_help_init
parameter_list|()
value|((void) 0)
DECL|macro|gimp_help_free ()
define|#
directive|define
name|gimp_help_free
parameter_list|()
value|((void) 0)
name|enum
DECL|enum|__anon2a2391cb0103
type|{
DECL|enumerator|GIMP_WHITE_MASK
name|GIMP_WHITE_MASK
init|=
name|GIMP_ADD_WHITE_MASK
decl_stmt|,
DECL|enumerator|GIMP_BLACK_MASK
name|GIMP_BLACK_MASK
init|=
name|GIMP_ADD_BLACK_MASK
decl_stmt|,
DECL|enumerator|GIMP_ALPHA_MASK
name|GIMP_ALPHA_MASK
init|=
name|GIMP_ADD_ALPHA_MASK
decl_stmt|,
DECL|enumerator|GIMP_SELECTION_MASK
name|GIMP_SELECTION_MASK
init|=
name|GIMP_ADD_SELECTION_MASK
decl_stmt|,
DECL|enumerator|GIMP_INV_SELECTION_MASK
name|GIMP_INV_SELECTION_MASK
init|=
name|GIMP_ADD_INVERSE_SELECTION_MASK
decl_stmt|,
DECL|enumerator|GIMP_COPY_MASK
name|GIMP_COPY_MASK
init|=
name|GIMP_ADD_COPY_MASK
decl_stmt|,
DECL|enumerator|GIMP_INV_COPY_MASK
name|GIMP_INV_COPY_MASK
init|=
name|GIMP_ADD_INVERSE_COPY_MASK
end_decl_stmt

begin_enum
unit|};
enum|enum
DECL|enum|__anon2a2391cb0203
block|{
DECL|enumerator|GIMP_ADD
name|GIMP_ADD
init|=
name|GIMP_CHANNEL_OP_ADD
block|,
DECL|enumerator|GIMP_SUB
name|GIMP_SUB
init|=
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
DECL|enumerator|GIMP_REPLACE
name|GIMP_REPLACE
init|=
name|GIMP_CHANNEL_OP_REPLACE
block|,
DECL|enumerator|GIMP_INTERSECT
name|GIMP_INTERSECT
init|=
name|GIMP_CHANNEL_OP_INTERSECT
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a2391cb0303
block|{
DECL|enumerator|GIMP_FG_BG_RGB
name|GIMP_FG_BG_RGB
init|=
name|GIMP_FG_BG_RGB_MODE
block|,
DECL|enumerator|GIMP_FG_BG_HSV
name|GIMP_FG_BG_HSV
init|=
name|GIMP_FG_BG_HSV_MODE
block|,
DECL|enumerator|GIMP_FG_TRANS
name|GIMP_FG_TRANS
init|=
name|GIMP_FG_TRANSPARENT_MODE
block|,
DECL|enumerator|GIMP_CUSTOM
name|GIMP_CUSTOM
init|=
name|GIMP_CUSTOM_MODE
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a2391cb0403
block|{
DECL|enumerator|GIMP_FG_IMAGE_FILL
name|GIMP_FG_IMAGE_FILL
init|=
name|GIMP_FOREGROUND_FILL
block|,
DECL|enumerator|GIMP_BG_IMAGE_FILL
name|GIMP_BG_IMAGE_FILL
init|=
name|GIMP_BACKGROUND_FILL
block|,
DECL|enumerator|GIMP_WHITE_IMAGE_FILL
name|GIMP_WHITE_IMAGE_FILL
init|=
name|GIMP_WHITE_FILL
block|,
DECL|enumerator|GIMP_TRANS_IMAGE_FILL
name|GIMP_TRANS_IMAGE_FILL
init|=
name|GIMP_TRANSPARENT_FILL
block|,
DECL|enumerator|GIMP_NO_IMAGE_FILL
name|GIMP_NO_IMAGE_FILL
init|=
name|GIMP_NO_FILL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a2391cb0503
block|{
DECL|enumerator|GIMP_APPLY
name|GIMP_APPLY
init|=
name|GIMP_MASK_APPLY
block|,
DECL|enumerator|GIMP_DISCARD
name|GIMP_DISCARD
init|=
name|GIMP_MASK_DISCARD
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a2391cb0603
block|{
DECL|enumerator|GIMP_ONCE_FORWARD
name|GIMP_ONCE_FORWARD
init|=
name|GIMP_GRADIENT_ONCE_FORWARD
block|,
DECL|enumerator|GIMP_ONCE_BACKWARDS
name|GIMP_ONCE_BACKWARDS
init|=
name|GIMP_GRADIENT_ONCE_BACKWARD
block|,
DECL|enumerator|GIMP_LOOP_SAWTOOTH
name|GIMP_LOOP_SAWTOOTH
init|=
name|GIMP_GRADIENT_LOOP_SAWTOOTH
block|,
DECL|enumerator|GIMP_LOOP_TRIANGLE
name|GIMP_LOOP_TRIANGLE
init|=
name|GIMP_GRADIENT_LOOP_TRIANGLE
block|, }
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a2391cb0703
block|{
DECL|enumerator|GIMP_HARD
name|GIMP_HARD
init|=
name|GIMP_BRUSH_HARD
block|,
DECL|enumerator|GIMP_SOFT
name|GIMP_SOFT
init|=
name|GIMP_BRUSH_SOFT
block|, }
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a2391cb0803
block|{
DECL|enumerator|GIMP_CONTINUOUS
name|GIMP_CONTINUOUS
init|=
name|GIMP_PAINT_CONSTANT
block|,
DECL|enumerator|GIMP_INCREMENTAL
name|GIMP_INCREMENTAL
init|=
name|GIMP_PAINT_INCREMENTAL
block|}
enum|;
end_enum

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_ENABLE_COMPAT_CRUFT */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPAT_H__ */
end_comment

end_unit


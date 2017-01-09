begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPAT_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPAT_ENUMS_H__
define|#
directive|define
name|__GIMP_COMPAT_ENUMS_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/*  These enums exist only for compatibility, their nicks are needed  *  for config file parsing; they are registered in gimp_base_init().  */
DECL|macro|GIMP_TYPE_ADD_MASK_TYPE_COMPAT
define|#
directive|define
name|GIMP_TYPE_ADD_MASK_TYPE_COMPAT
value|(gimp_add_mask_type_compat_get_type ())
name|GType
name|gimp_add_mask_type_compat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ceaa2e0103
block|{
DECL|enumerator|GIMP_ADD_WHITE_MASK
name|GIMP_ADD_WHITE_MASK
init|=
name|GIMP_ADD_MASK_WHITE
block|,
DECL|enumerator|GIMP_ADD_BLACK_MASK
name|GIMP_ADD_BLACK_MASK
init|=
name|GIMP_ADD_MASK_BLACK
block|,
DECL|enumerator|GIMP_ADD_ALPHA_MASK
name|GIMP_ADD_ALPHA_MASK
init|=
name|GIMP_ADD_MASK_ALPHA
block|,
DECL|enumerator|GIMP_ADD_ALPHA_TRANSFER_MASK
name|GIMP_ADD_ALPHA_TRANSFER_MASK
init|=
name|GIMP_ADD_MASK_ALPHA_TRANSFER
block|,
DECL|enumerator|GIMP_ADD_SELECTION_MASK
name|GIMP_ADD_SELECTION_MASK
init|=
name|GIMP_ADD_MASK_SELECTION
block|,
DECL|enumerator|GIMP_ADD_COPY_MASK
name|GIMP_ADD_COPY_MASK
init|=
name|GIMP_ADD_MASK_COPY
block|,
DECL|enumerator|GIMP_ADD_CHANNEL_MASK
name|GIMP_ADD_CHANNEL_MASK
init|=
name|GIMP_ADD_MASK_CHANNEL
DECL|typedef|GimpAddMaskTypeCompat
block|}
name|GimpAddMaskTypeCompat
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_BLEND_MODE_COMPAT
define|#
directive|define
name|GIMP_TYPE_BLEND_MODE_COMPAT
value|(gimp_blend_mode_compat_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_blend_mode_compat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ceaa2e0203
block|{
DECL|enumerator|GIMP_FG_BG_RGB_MODE
name|GIMP_FG_BG_RGB_MODE
init|=
name|GIMP_BLEND_FG_BG_RGB
block|,
DECL|enumerator|GIMP_FG_BG_HSV_MODE
name|GIMP_FG_BG_HSV_MODE
init|=
name|GIMP_BLEND_FG_BG_HSV
block|,
DECL|enumerator|GIMP_FG_TRANSPARENT_MODE
name|GIMP_FG_TRANSPARENT_MODE
init|=
name|GIMP_BLEND_FG_TRANSPARENT
block|,
DECL|enumerator|GIMP_CUSTOM_MODE
name|GIMP_CUSTOM_MODE
init|=
name|GIMP_BLEND_CUSTOM
DECL|typedef|GimpBlendModeCompat
block|}
name|GimpBlendModeCompat
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_BUCKET_FILL_MODE_COMPAT
define|#
directive|define
name|GIMP_TYPE_BUCKET_FILL_MODE_COMPAT
value|(gimp_bucket_fill_mode_compat_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_bucket_fill_mode_compat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ceaa2e0303
block|{
DECL|enumerator|GIMP_FG_BUCKET_FILL
name|GIMP_FG_BUCKET_FILL
init|=
name|GIMP_BUCKET_FILL_FG
block|,
DECL|enumerator|GIMP_BG_BUCKET_FILL
name|GIMP_BG_BUCKET_FILL
init|=
name|GIMP_BUCKET_FILL_BG
block|,
DECL|enumerator|GIMP_PATTERN_BUCKET_FILL
name|GIMP_PATTERN_BUCKET_FILL
init|=
name|GIMP_BUCKET_FILL_PATTERN
DECL|typedef|GimpBucketFillModeCompat
block|}
name|GimpBucketFillModeCompat
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CLONE_TYPE_COMPAT
define|#
directive|define
name|GIMP_TYPE_CLONE_TYPE_COMPAT
value|(gimp_clone_type_compat_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_clone_type_compat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ceaa2e0403
block|{
DECL|enumerator|GIMP_IMAGE_CLONE
name|GIMP_IMAGE_CLONE
init|=
name|GIMP_CLONE_IMAGE
block|,
DECL|enumerator|GIMP_PATTERN_CLONE
name|GIMP_PATTERN_CLONE
init|=
name|GIMP_CLONE_PATTERN
DECL|typedef|GimpCloneTypeCompat
block|}
name|GimpCloneTypeCompat
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONVOLVE_TYPE_COMPAT
define|#
directive|define
name|GIMP_TYPE_CONVOLVE_TYPE_COMPAT
value|(gimp_convolve_type_compat_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convolve_type_compat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ceaa2e0503
block|{
DECL|enumerator|GIMP_BLUR_CONVOLVE
name|GIMP_BLUR_CONVOLVE
init|=
name|GIMP_CONVOLVE_BLUR
block|,
DECL|enumerator|GIMP_SHARPEN_CONVOLVE
name|GIMP_SHARPEN_CONVOLVE
init|=
name|GIMP_CONVOLVE_SHARPEN
DECL|typedef|GimpConvolveTypeCompat
block|}
name|GimpConvolveTypeCompat
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_FILL_TYPE_COMPAT
define|#
directive|define
name|GIMP_TYPE_FILL_TYPE_COMPAT
value|(gimp_fill_type_compat_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_fill_type_compat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ceaa2e0603
block|{
DECL|enumerator|GIMP_FOREGROUND_FILL
name|GIMP_FOREGROUND_FILL
init|=
name|GIMP_FILL_FOREGROUND
block|,
DECL|enumerator|GIMP_BACKGROUND_FILL
name|GIMP_BACKGROUND_FILL
init|=
name|GIMP_FILL_BACKGROUND
block|,
DECL|enumerator|GIMP_WHITE_FILL
name|GIMP_WHITE_FILL
init|=
name|GIMP_FILL_WHITE
block|,
DECL|enumerator|GIMP_TRANSPARENT_FILL
name|GIMP_TRANSPARENT_FILL
init|=
name|GIMP_FILL_TRANSPARENT
block|,
DECL|enumerator|GIMP_PATTERN_FILL
name|GIMP_PATTERN_FILL
init|=
name|GIMP_FILL_PATTERN
DECL|typedef|GimpFillTypeCompat
block|}
name|GimpFillTypeCompat
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HUE_RANGE_COMPAT
define|#
directive|define
name|GIMP_TYPE_HUE_RANGE_COMPAT
value|(gimp_hue_range_compat_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_hue_range_compat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ceaa2e0703
block|{
DECL|enumerator|GIMP_ALL_HUES
name|GIMP_ALL_HUES
block|,
DECL|enumerator|GIMP_RED_HUES
name|GIMP_RED_HUES
block|,
DECL|enumerator|GIMP_YELLOW_HUES
name|GIMP_YELLOW_HUES
block|,
DECL|enumerator|GIMP_GREEN_HUES
name|GIMP_GREEN_HUES
block|,
DECL|enumerator|GIMP_CYAN_HUES
name|GIMP_CYAN_HUES
block|,
DECL|enumerator|GIMP_BLUE_HUES
name|GIMP_BLUE_HUES
block|,
DECL|enumerator|GIMP_MAGENTA_HUES
name|GIMP_MAGENTA_HUES
DECL|typedef|GimpHueRangeCompat
block|}
name|GimpHueRangeCompat
typedef|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPAT_ENUMS_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Generated data (by gimp-mkenums) */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcompatenums.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./gimpcompatenums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_add_mask_type_compat_get_type (void)
name|gimp_add_mask_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_ADD_WHITE_MASK
block|,
literal|"GIMP_ADD_WHITE_MASK"
block|,
literal|"white-mask"
block|}
block|,
block|{
name|GIMP_ADD_BLACK_MASK
block|,
literal|"GIMP_ADD_BLACK_MASK"
block|,
literal|"black-mask"
block|}
block|,
block|{
name|GIMP_ADD_ALPHA_MASK
block|,
literal|"GIMP_ADD_ALPHA_MASK"
block|,
literal|"alpha-mask"
block|}
block|,
block|{
name|GIMP_ADD_ALPHA_TRANSFER_MASK
block|,
literal|"GIMP_ADD_ALPHA_TRANSFER_MASK"
block|,
literal|"alpha-transfer-mask"
block|}
block|,
block|{
name|GIMP_ADD_SELECTION_MASK
block|,
literal|"GIMP_ADD_SELECTION_MASK"
block|,
literal|"selection-mask"
block|}
block|,
block|{
name|GIMP_ADD_COPY_MASK
block|,
literal|"GIMP_ADD_COPY_MASK"
block|,
literal|"copy-mask"
block|}
block|,
block|{
name|GIMP_ADD_CHANNEL_MASK
block|,
literal|"GIMP_ADD_CHANNEL_MASK"
block|,
literal|"channel-mask"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_ADD_WHITE_MASK
block|,
literal|"GIMP_ADD_WHITE_MASK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ADD_BLACK_MASK
block|,
literal|"GIMP_ADD_BLACK_MASK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ADD_ALPHA_MASK
block|,
literal|"GIMP_ADD_ALPHA_MASK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ADD_ALPHA_TRANSFER_MASK
block|,
literal|"GIMP_ADD_ALPHA_TRANSFER_MASK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ADD_SELECTION_MASK
block|,
literal|"GIMP_ADD_SELECTION_MASK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ADD_COPY_MASK
block|,
literal|"GIMP_ADD_COPY_MASK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ADD_CHANNEL_MASK
block|,
literal|"GIMP_ADD_CHANNEL_MASK"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpAddMaskTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"add-mask-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_blend_mode_compat_get_type (void)
name|gimp_blend_mode_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_FG_BG_RGB_MODE
block|,
literal|"GIMP_FG_BG_RGB_MODE"
block|,
literal|"fg-bg-rgb-mode"
block|}
block|,
block|{
name|GIMP_FG_BG_HSV_MODE
block|,
literal|"GIMP_FG_BG_HSV_MODE"
block|,
literal|"fg-bg-hsv-mode"
block|}
block|,
block|{
name|GIMP_FG_TRANSPARENT_MODE
block|,
literal|"GIMP_FG_TRANSPARENT_MODE"
block|,
literal|"fg-transparent-mode"
block|}
block|,
block|{
name|GIMP_CUSTOM_MODE
block|,
literal|"GIMP_CUSTOM_MODE"
block|,
literal|"custom-mode"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_FG_BG_RGB_MODE
block|,
literal|"GIMP_FG_BG_RGB_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_FG_BG_HSV_MODE
block|,
literal|"GIMP_FG_BG_HSV_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_FG_TRANSPARENT_MODE
block|,
literal|"GIMP_FG_TRANSPARENT_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CUSTOM_MODE
block|,
literal|"GIMP_CUSTOM_MODE"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpBlendModeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"blend-mode-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_bucket_fill_mode_compat_get_type (void)
name|gimp_bucket_fill_mode_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_FG_BUCKET_FILL
block|,
literal|"GIMP_FG_BUCKET_FILL"
block|,
literal|"fg-bucket-fill"
block|}
block|,
block|{
name|GIMP_BG_BUCKET_FILL
block|,
literal|"GIMP_BG_BUCKET_FILL"
block|,
literal|"bg-bucket-fill"
block|}
block|,
block|{
name|GIMP_PATTERN_BUCKET_FILL
block|,
literal|"GIMP_PATTERN_BUCKET_FILL"
block|,
literal|"pattern-bucket-fill"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_FG_BUCKET_FILL
block|,
literal|"GIMP_FG_BUCKET_FILL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BG_BUCKET_FILL
block|,
literal|"GIMP_BG_BUCKET_FILL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_PATTERN_BUCKET_FILL
block|,
literal|"GIMP_PATTERN_BUCKET_FILL"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpBucketFillModeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"bucket-fill-mode-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_channel_type_compat_get_type (void)
name|gimp_channel_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_RED_CHANNEL
block|,
literal|"GIMP_RED_CHANNEL"
block|,
literal|"red-channel"
block|}
block|,
block|{
name|GIMP_GREEN_CHANNEL
block|,
literal|"GIMP_GREEN_CHANNEL"
block|,
literal|"green-channel"
block|}
block|,
block|{
name|GIMP_BLUE_CHANNEL
block|,
literal|"GIMP_BLUE_CHANNEL"
block|,
literal|"blue-channel"
block|}
block|,
block|{
name|GIMP_GRAY_CHANNEL
block|,
literal|"GIMP_GRAY_CHANNEL"
block|,
literal|"gray-channel"
block|}
block|,
block|{
name|GIMP_INDEXED_CHANNEL
block|,
literal|"GIMP_INDEXED_CHANNEL"
block|,
literal|"indexed-channel"
block|}
block|,
block|{
name|GIMP_ALPHA_CHANNEL
block|,
literal|"GIMP_ALPHA_CHANNEL"
block|,
literal|"alpha-channel"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_RED_CHANNEL
block|,
literal|"GIMP_RED_CHANNEL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GREEN_CHANNEL
block|,
literal|"GIMP_GREEN_CHANNEL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BLUE_CHANNEL
block|,
literal|"GIMP_BLUE_CHANNEL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GRAY_CHANNEL
block|,
literal|"GIMP_GRAY_CHANNEL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_INDEXED_CHANNEL
block|,
literal|"GIMP_INDEXED_CHANNEL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ALPHA_CHANNEL
block|,
literal|"GIMP_ALPHA_CHANNEL"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpChannelTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"channel-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_clone_type_compat_get_type (void)
name|gimp_clone_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_IMAGE_CLONE
block|,
literal|"GIMP_IMAGE_CLONE"
block|,
literal|"image-clone"
block|}
block|,
block|{
name|GIMP_PATTERN_CLONE
block|,
literal|"GIMP_PATTERN_CLONE"
block|,
literal|"pattern-clone"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_IMAGE_CLONE
block|,
literal|"GIMP_IMAGE_CLONE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_PATTERN_CLONE
block|,
literal|"GIMP_PATTERN_CLONE"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpCloneTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"clone-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_convert_dither_type_compat_get_type (void)
name|gimp_convert_dither_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_NO_DITHER
block|,
literal|"GIMP_NO_DITHER"
block|,
literal|"no-dither"
block|}
block|,
block|{
name|GIMP_FS_DITHER
block|,
literal|"GIMP_FS_DITHER"
block|,
literal|"fs-dither"
block|}
block|,
block|{
name|GIMP_FSLOWBLEED_DITHER
block|,
literal|"GIMP_FSLOWBLEED_DITHER"
block|,
literal|"fslowbleed-dither"
block|}
block|,
block|{
name|GIMP_FIXED_DITHER
block|,
literal|"GIMP_FIXED_DITHER"
block|,
literal|"fixed-dither"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_NO_DITHER
block|,
literal|"GIMP_NO_DITHER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_FS_DITHER
block|,
literal|"GIMP_FS_DITHER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_FSLOWBLEED_DITHER
block|,
literal|"GIMP_FSLOWBLEED_DITHER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_FIXED_DITHER
block|,
literal|"GIMP_FIXED_DITHER"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpConvertDitherTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"convert-dither-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_convert_palette_type_compat_get_type (void)
name|gimp_convert_palette_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_MAKE_PALETTE
block|,
literal|"GIMP_MAKE_PALETTE"
block|,
literal|"make-palette"
block|}
block|,
block|{
name|GIMP_REUSE_PALETTE
block|,
literal|"GIMP_REUSE_PALETTE"
block|,
literal|"reuse-palette"
block|}
block|,
block|{
name|GIMP_WEB_PALETTE
block|,
literal|"GIMP_WEB_PALETTE"
block|,
literal|"web-palette"
block|}
block|,
block|{
name|GIMP_MONO_PALETTE
block|,
literal|"GIMP_MONO_PALETTE"
block|,
literal|"mono-palette"
block|}
block|,
block|{
name|GIMP_CUSTOM_PALETTE
block|,
literal|"GIMP_CUSTOM_PALETTE"
block|,
literal|"custom-palette"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_MAKE_PALETTE
block|,
literal|"GIMP_MAKE_PALETTE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_REUSE_PALETTE
block|,
literal|"GIMP_REUSE_PALETTE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WEB_PALETTE
block|,
literal|"GIMP_WEB_PALETTE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_MONO_PALETTE
block|,
literal|"GIMP_MONO_PALETTE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CUSTOM_PALETTE
block|,
literal|"GIMP_CUSTOM_PALETTE"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpConvertPaletteTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"convert-palette-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_convolve_type_compat_get_type (void)
name|gimp_convolve_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_BLUR_CONVOLVE
block|,
literal|"GIMP_BLUR_CONVOLVE"
block|,
literal|"blur-convolve"
block|}
block|,
block|{
name|GIMP_SHARPEN_CONVOLVE
block|,
literal|"GIMP_SHARPEN_CONVOLVE"
block|,
literal|"sharpen-convolve"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_BLUR_CONVOLVE
block|,
literal|"GIMP_BLUR_CONVOLVE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SHARPEN_CONVOLVE
block|,
literal|"GIMP_SHARPEN_CONVOLVE"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpConvolveTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"convolve-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_desaturate_mode_compat_get_type (void)
name|gimp_desaturate_mode_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_DESATURATE_LUMINOSITY
block|,
literal|"GIMP_DESATURATE_LUMINOSITY"
block|,
literal|"luminosity"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_DESATURATE_LUMINOSITY
block|,
literal|"GIMP_DESATURATE_LUMINOSITY"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpDesaturateModeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"desaturate-mode-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_dodge_burn_type_compat_get_type (void)
name|gimp_dodge_burn_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_DODGE
block|,
literal|"GIMP_DODGE"
block|,
literal|"dodge"
block|}
block|,
block|{
name|GIMP_BURN
block|,
literal|"GIMP_BURN"
block|,
literal|"burn"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_DODGE
block|,
literal|"GIMP_DODGE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BURN
block|,
literal|"GIMP_BURN"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpDodgeBurnTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"dodge-burn-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_fill_type_compat_get_type (void)
name|gimp_fill_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_FOREGROUND_FILL
block|,
literal|"GIMP_FOREGROUND_FILL"
block|,
literal|"foreground-fill"
block|}
block|,
block|{
name|GIMP_BACKGROUND_FILL
block|,
literal|"GIMP_BACKGROUND_FILL"
block|,
literal|"background-fill"
block|}
block|,
block|{
name|GIMP_WHITE_FILL
block|,
literal|"GIMP_WHITE_FILL"
block|,
literal|"white-fill"
block|}
block|,
block|{
name|GIMP_TRANSPARENT_FILL
block|,
literal|"GIMP_TRANSPARENT_FILL"
block|,
literal|"transparent-fill"
block|}
block|,
block|{
name|GIMP_PATTERN_FILL
block|,
literal|"GIMP_PATTERN_FILL"
block|,
literal|"pattern-fill"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_FOREGROUND_FILL
block|,
literal|"GIMP_FOREGROUND_FILL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BACKGROUND_FILL
block|,
literal|"GIMP_BACKGROUND_FILL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WHITE_FILL
block|,
literal|"GIMP_WHITE_FILL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSPARENT_FILL
block|,
literal|"GIMP_TRANSPARENT_FILL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_PATTERN_FILL
block|,
literal|"GIMP_PATTERN_FILL"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpFillTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"fill-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_hue_range_compat_get_type (void)
name|gimp_hue_range_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_ALL_HUES
block|,
literal|"GIMP_ALL_HUES"
block|,
literal|"all-hues"
block|}
block|,
block|{
name|GIMP_RED_HUES
block|,
literal|"GIMP_RED_HUES"
block|,
literal|"red-hues"
block|}
block|,
block|{
name|GIMP_YELLOW_HUES
block|,
literal|"GIMP_YELLOW_HUES"
block|,
literal|"yellow-hues"
block|}
block|,
block|{
name|GIMP_GREEN_HUES
block|,
literal|"GIMP_GREEN_HUES"
block|,
literal|"green-hues"
block|}
block|,
block|{
name|GIMP_CYAN_HUES
block|,
literal|"GIMP_CYAN_HUES"
block|,
literal|"cyan-hues"
block|}
block|,
block|{
name|GIMP_BLUE_HUES
block|,
literal|"GIMP_BLUE_HUES"
block|,
literal|"blue-hues"
block|}
block|,
block|{
name|GIMP_MAGENTA_HUES
block|,
literal|"GIMP_MAGENTA_HUES"
block|,
literal|"magenta-hues"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_ALL_HUES
block|,
literal|"GIMP_ALL_HUES"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RED_HUES
block|,
literal|"GIMP_RED_HUES"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_YELLOW_HUES
block|,
literal|"GIMP_YELLOW_HUES"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GREEN_HUES
block|,
literal|"GIMP_GREEN_HUES"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CYAN_HUES
block|,
literal|"GIMP_CYAN_HUES"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BLUE_HUES
block|,
literal|"GIMP_BLUE_HUES"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_MAGENTA_HUES
block|,
literal|"GIMP_MAGENTA_HUES"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpHueRangeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"hue-range-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_icon_type_compat_get_type (void)
name|gimp_icon_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_ICON_TYPE_STOCK_ID
block|,
literal|"GIMP_ICON_TYPE_STOCK_ID"
block|,
literal|"id"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_ICON_TYPE_STOCK_ID
block|,
literal|"GIMP_ICON_TYPE_STOCK_ID"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpIconTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"icon-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_interpolation_type_compat_get_type (void)
name|gimp_interpolation_type_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_INTERPOLATION_LANCZOS
block|,
literal|"GIMP_INTERPOLATION_LANCZOS"
block|,
literal|"lanczos"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_INTERPOLATION_LANCZOS
block|,
literal|"GIMP_INTERPOLATION_LANCZOS"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpInterpolationTypeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"interpolation-type-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_layer_mode_effects_get_type (void)
name|gimp_layer_mode_effects_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_NORMAL_MODE
block|,
literal|"GIMP_NORMAL_MODE"
block|,
literal|"normal-mode"
block|}
block|,
block|{
name|GIMP_DISSOLVE_MODE
block|,
literal|"GIMP_DISSOLVE_MODE"
block|,
literal|"dissolve-mode"
block|}
block|,
block|{
name|GIMP_BEHIND_MODE
block|,
literal|"GIMP_BEHIND_MODE"
block|,
literal|"behind-mode"
block|}
block|,
block|{
name|GIMP_MULTIPLY_MODE
block|,
literal|"GIMP_MULTIPLY_MODE"
block|,
literal|"multiply-mode"
block|}
block|,
block|{
name|GIMP_SCREEN_MODE
block|,
literal|"GIMP_SCREEN_MODE"
block|,
literal|"screen-mode"
block|}
block|,
block|{
name|GIMP_OVERLAY_MODE
block|,
literal|"GIMP_OVERLAY_MODE"
block|,
literal|"overlay-mode"
block|}
block|,
block|{
name|GIMP_DIFFERENCE_MODE
block|,
literal|"GIMP_DIFFERENCE_MODE"
block|,
literal|"difference-mode"
block|}
block|,
block|{
name|GIMP_ADDITION_MODE
block|,
literal|"GIMP_ADDITION_MODE"
block|,
literal|"addition-mode"
block|}
block|,
block|{
name|GIMP_SUBTRACT_MODE
block|,
literal|"GIMP_SUBTRACT_MODE"
block|,
literal|"subtract-mode"
block|}
block|,
block|{
name|GIMP_DARKEN_ONLY_MODE
block|,
literal|"GIMP_DARKEN_ONLY_MODE"
block|,
literal|"darken-only-mode"
block|}
block|,
block|{
name|GIMP_LIGHTEN_ONLY_MODE
block|,
literal|"GIMP_LIGHTEN_ONLY_MODE"
block|,
literal|"lighten-only-mode"
block|}
block|,
block|{
name|GIMP_HUE_MODE
block|,
literal|"GIMP_HUE_MODE"
block|,
literal|"hue-mode"
block|}
block|,
block|{
name|GIMP_SATURATION_MODE
block|,
literal|"GIMP_SATURATION_MODE"
block|,
literal|"saturation-mode"
block|}
block|,
block|{
name|GIMP_COLOR_MODE
block|,
literal|"GIMP_COLOR_MODE"
block|,
literal|"color-mode"
block|}
block|,
block|{
name|GIMP_VALUE_MODE
block|,
literal|"GIMP_VALUE_MODE"
block|,
literal|"value-mode"
block|}
block|,
block|{
name|GIMP_DIVIDE_MODE
block|,
literal|"GIMP_DIVIDE_MODE"
block|,
literal|"divide-mode"
block|}
block|,
block|{
name|GIMP_DODGE_MODE
block|,
literal|"GIMP_DODGE_MODE"
block|,
literal|"dodge-mode"
block|}
block|,
block|{
name|GIMP_BURN_MODE
block|,
literal|"GIMP_BURN_MODE"
block|,
literal|"burn-mode"
block|}
block|,
block|{
name|GIMP_HARDLIGHT_MODE
block|,
literal|"GIMP_HARDLIGHT_MODE"
block|,
literal|"hardlight-mode"
block|}
block|,
block|{
name|GIMP_SOFTLIGHT_MODE
block|,
literal|"GIMP_SOFTLIGHT_MODE"
block|,
literal|"softlight-mode"
block|}
block|,
block|{
name|GIMP_GRAIN_EXTRACT_MODE
block|,
literal|"GIMP_GRAIN_EXTRACT_MODE"
block|,
literal|"grain-extract-mode"
block|}
block|,
block|{
name|GIMP_GRAIN_MERGE_MODE
block|,
literal|"GIMP_GRAIN_MERGE_MODE"
block|,
literal|"grain-merge-mode"
block|}
block|,
block|{
name|GIMP_COLOR_ERASE_MODE
block|,
literal|"GIMP_COLOR_ERASE_MODE"
block|,
literal|"color-erase-mode"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_NORMAL_MODE
block|,
literal|"GIMP_NORMAL_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_DISSOLVE_MODE
block|,
literal|"GIMP_DISSOLVE_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BEHIND_MODE
block|,
literal|"GIMP_BEHIND_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_MULTIPLY_MODE
block|,
literal|"GIMP_MULTIPLY_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SCREEN_MODE
block|,
literal|"GIMP_SCREEN_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_OVERLAY_MODE
block|,
literal|"GIMP_OVERLAY_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_DIFFERENCE_MODE
block|,
literal|"GIMP_DIFFERENCE_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ADDITION_MODE
block|,
literal|"GIMP_ADDITION_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SUBTRACT_MODE
block|,
literal|"GIMP_SUBTRACT_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_DARKEN_ONLY_MODE
block|,
literal|"GIMP_DARKEN_ONLY_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LIGHTEN_ONLY_MODE
block|,
literal|"GIMP_LIGHTEN_ONLY_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HUE_MODE
block|,
literal|"GIMP_HUE_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SATURATION_MODE
block|,
literal|"GIMP_SATURATION_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_MODE
block|,
literal|"GIMP_COLOR_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_VALUE_MODE
block|,
literal|"GIMP_VALUE_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_DIVIDE_MODE
block|,
literal|"GIMP_DIVIDE_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_DODGE_MODE
block|,
literal|"GIMP_DODGE_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BURN_MODE
block|,
literal|"GIMP_BURN_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HARDLIGHT_MODE
block|,
literal|"GIMP_HARDLIGHT_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SOFTLIGHT_MODE
block|,
literal|"GIMP_SOFTLIGHT_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GRAIN_EXTRACT_MODE
block|,
literal|"GIMP_GRAIN_EXTRACT_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GRAIN_MERGE_MODE
block|,
literal|"GIMP_GRAIN_MERGE_MODE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_ERASE_MODE
block|,
literal|"GIMP_COLOR_ERASE_MODE"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpLayerModeEffects"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"layer-mode-effects"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_transfer_mode_compat_get_type (void)
name|gimp_transfer_mode_compat_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_SHADOWS
block|,
literal|"GIMP_SHADOWS"
block|,
literal|"shadows"
block|}
block|,
block|{
name|GIMP_MIDTONES
block|,
literal|"GIMP_MIDTONES"
block|,
literal|"midtones"
block|}
block|,
block|{
name|GIMP_HIGHLIGHTS
block|,
literal|"GIMP_HIGHLIGHTS"
block|,
literal|"highlights"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_SHADOWS
block|,
literal|"GIMP_SHADOWS"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_MIDTONES
block|,
literal|"GIMP_MIDTONES"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HIGHLIGHTS
block|,
literal|"GIMP_HIGHLIGHTS"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTransferModeCompat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"transfer-mode-compat"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_comment
comment|/* Generated data ends here */
end_comment

end_unit


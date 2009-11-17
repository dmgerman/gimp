begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GIMP PSD Plug-in  * Copyright 2007 by John Marshall  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PSD_H__
end_ifndef

begin_define
DECL|macro|__PSD_H__
define|#
directive|define
name|__PSD_H__
end_define

begin_comment
comment|/* Temporary disable of save functionality */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|PSD_SAVE
end_ifdef

begin_undef
undef|#
directive|undef
name|PSD_SAVE
end_undef

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* #define PSD_SAVE */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Set to the level of debugging output you want, 0 for none.  *   Setting higher than 2 will result in a very large amount of debug  *   output being produced. */
end_comment

begin_define
DECL|macro|PSD_DEBUG
define|#
directive|define
name|PSD_DEBUG
value|0
end_define

begin_define
DECL|macro|IFDBG (level)
define|#
directive|define
name|IFDBG
parameter_list|(
name|level
parameter_list|)
value|if (PSD_DEBUG>= level)
end_define

begin_comment
comment|/* Set to FALSE to supress pop-up warnings about lossy file conversions */
end_comment

begin_define
DECL|macro|CONVERSION_WARNINGS
define|#
directive|define
name|CONVERSION_WARNINGS
value|FALSE
end_define

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-psd-load"
end_define

begin_define
DECL|macro|LOAD_THUMB_PROC
define|#
directive|define
name|LOAD_THUMB_PROC
value|"file-psd-load-thumb"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-psd-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-psd"
end_define

begin_define
DECL|macro|DECODE_XMP_PROC
define|#
directive|define
name|DECODE_XMP_PROC
value|"plug-in-metadata-decode-xmp"
end_define

begin_define
DECL|macro|GIMP_PARASITE_COMMENT
define|#
directive|define
name|GIMP_PARASITE_COMMENT
value|"gimp-comment"
end_define

begin_define
DECL|macro|GIMP_PARASITE_ICC_PROFILE
define|#
directive|define
name|GIMP_PARASITE_ICC_PROFILE
value|"icc-profile"
end_define

begin_define
DECL|macro|GIMP_PARASITE_EXIF
define|#
directive|define
name|GIMP_PARASITE_EXIF
value|"exif-data"
end_define

begin_define
DECL|macro|GIMP_PARASITE_IPTC
define|#
directive|define
name|GIMP_PARASITE_IPTC
value|"iptc-data"
end_define

begin_define
DECL|macro|METADATA_PARASITE
define|#
directive|define
name|METADATA_PARASITE
value|"gimp-metadata"
end_define

begin_define
DECL|macro|METADATA_MARKER
define|#
directive|define
name|METADATA_MARKER
value|"GIMP_XMP_1"
end_define

begin_define
DECL|macro|PSD_PARASITE_DUOTONE_DATA
define|#
directive|define
name|PSD_PARASITE_DUOTONE_DATA
value|"psd-duotone-data"
end_define

begin_comment
comment|/* Copied from app/base/gimpimage-quick-mask.h - internal identifier for quick mask channel */
end_comment

begin_define
DECL|macro|GIMP_IMAGE_QUICK_MASK_NAME
define|#
directive|define
name|GIMP_IMAGE_QUICK_MASK_NAME
value|"Qmask"
end_define

begin_define
DECL|macro|MAX_RAW_SIZE
define|#
directive|define
name|MAX_RAW_SIZE
value|0
end_define

begin_comment
DECL|macro|MAX_RAW_SIZE
comment|/* FIXME all images are raw if 0 */
end_comment

begin_comment
comment|/* PSD spec defines */
end_comment

begin_define
DECL|macro|MAX_CHANNELS
define|#
directive|define
name|MAX_CHANNELS
value|56
end_define

begin_comment
DECL|macro|MAX_CHANNELS
comment|/* Photoshop CS to CS3 support 56 channels */
end_comment

begin_comment
comment|/* PSD spec constants */
end_comment

begin_comment
comment|/* Layer resource IDs */
end_comment

begin_comment
comment|/* Adjustment layer IDs */
end_comment

begin_define
DECL|macro|PSD_LADJ_LEVEL
define|#
directive|define
name|PSD_LADJ_LEVEL
value|"levl"
end_define

begin_comment
DECL|macro|PSD_LADJ_LEVEL
comment|/* Adjustment layer - levels (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_CURVE
define|#
directive|define
name|PSD_LADJ_CURVE
value|"curv"
end_define

begin_comment
DECL|macro|PSD_LADJ_CURVE
comment|/* Adjustment layer - curves (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_BRIGHTNESS
define|#
directive|define
name|PSD_LADJ_BRIGHTNESS
value|"brit"
end_define

begin_comment
DECL|macro|PSD_LADJ_BRIGHTNESS
comment|/* Adjustment layer - brightness/contrast (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_BALANCE
define|#
directive|define
name|PSD_LADJ_BALANCE
value|"blnc"
end_define

begin_comment
DECL|macro|PSD_LADJ_BALANCE
comment|/* Adjustment layer - color balance (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_BLACK_WHITE
define|#
directive|define
name|PSD_LADJ_BLACK_WHITE
value|"blwh"
end_define

begin_comment
DECL|macro|PSD_LADJ_BLACK_WHITE
comment|/* Adjustment layer - black& white (PS10) */
end_comment

begin_define
DECL|macro|PSD_LADJ_HUE
define|#
directive|define
name|PSD_LADJ_HUE
value|"hue "
end_define

begin_comment
DECL|macro|PSD_LADJ_HUE
comment|/* Adjustment layer - old hue/saturation (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_HUE2
define|#
directive|define
name|PSD_LADJ_HUE2
value|"hue2"
end_define

begin_comment
DECL|macro|PSD_LADJ_HUE2
comment|/* Adjustment layer - hue/saturation (PS5) */
end_comment

begin_define
DECL|macro|PSD_LADJ_SELECTIVE
define|#
directive|define
name|PSD_LADJ_SELECTIVE
value|"selc"
end_define

begin_comment
DECL|macro|PSD_LADJ_SELECTIVE
comment|/* Adjustment layer - selective color (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_MIXER
define|#
directive|define
name|PSD_LADJ_MIXER
value|"mixr"
end_define

begin_comment
DECL|macro|PSD_LADJ_MIXER
comment|/* Adjustment layer - channel mixer (PS9) */
end_comment

begin_define
DECL|macro|PSD_LADJ_GRAD_MAP
define|#
directive|define
name|PSD_LADJ_GRAD_MAP
value|"grdm"
end_define

begin_comment
DECL|macro|PSD_LADJ_GRAD_MAP
comment|/* Adjustment layer - gradient map (PS9) */
end_comment

begin_define
DECL|macro|PSD_LADJ_PHOTO_FILT
define|#
directive|define
name|PSD_LADJ_PHOTO_FILT
value|"phfl"
end_define

begin_comment
DECL|macro|PSD_LADJ_PHOTO_FILT
comment|/* Adjustment layer - photo filter (PS9) */
end_comment

begin_define
DECL|macro|PSD_LADJ_EXPOSURE
define|#
directive|define
name|PSD_LADJ_EXPOSURE
value|"expA"
end_define

begin_comment
DECL|macro|PSD_LADJ_EXPOSURE
comment|/* Adjustment layer - exposure (PS10) */
end_comment

begin_define
DECL|macro|PSD_LADJ_INVERT
define|#
directive|define
name|PSD_LADJ_INVERT
value|"nvrt"
end_define

begin_comment
DECL|macro|PSD_LADJ_INVERT
comment|/* Adjustment layer - invert (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_THRESHOLD
define|#
directive|define
name|PSD_LADJ_THRESHOLD
value|"thrs"
end_define

begin_comment
DECL|macro|PSD_LADJ_THRESHOLD
comment|/* Adjustment layer - threshold (PS4) */
end_comment

begin_define
DECL|macro|PSD_LADJ_POSTERIZE
define|#
directive|define
name|PSD_LADJ_POSTERIZE
value|"post"
end_define

begin_comment
DECL|macro|PSD_LADJ_POSTERIZE
comment|/* Adjustment layer - posterize (PS4) */
end_comment

begin_comment
comment|/* Fill Layer IDs */
end_comment

begin_define
DECL|macro|PSD_LFIL_SOLID
define|#
directive|define
name|PSD_LFIL_SOLID
value|"SoCo"
end_define

begin_comment
DECL|macro|PSD_LFIL_SOLID
comment|/* Solid color sheet setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LFIL_PATTERN
define|#
directive|define
name|PSD_LFIL_PATTERN
value|"PtFl"
end_define

begin_comment
DECL|macro|PSD_LFIL_PATTERN
comment|/* Pattern fill setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LFIL_GRADIENT
define|#
directive|define
name|PSD_LFIL_GRADIENT
value|"GdFl"
end_define

begin_comment
DECL|macro|PSD_LFIL_GRADIENT
comment|/* Gradient fill setting (PS6) */
end_comment

begin_comment
comment|/* Effects Layer IDs */
end_comment

begin_define
DECL|macro|PSD_LFX_FX
define|#
directive|define
name|PSD_LFX_FX
value|"lrFX"
end_define

begin_comment
DECL|macro|PSD_LFX_FX
comment|/* Effects layer info (PS5) */
end_comment

begin_define
DECL|macro|PSD_LFX_FX2
define|#
directive|define
name|PSD_LFX_FX2
value|"lfx2"
end_define

begin_comment
DECL|macro|PSD_LFX_FX2
comment|/* Object based effects layer info (PS6) */
end_comment

begin_comment
comment|/* Type Tool Layers */
end_comment

begin_define
DECL|macro|PSD_LTYP_TYPE
define|#
directive|define
name|PSD_LTYP_TYPE
value|"tySh"
end_define

begin_comment
DECL|macro|PSD_LTYP_TYPE
comment|/* Type tool layer (PS5) */
end_comment

begin_define
DECL|macro|PSD_LTYP_TYPE2
define|#
directive|define
name|PSD_LTYP_TYPE2
value|"TySh"
end_define

begin_comment
DECL|macro|PSD_LTYP_TYPE2
comment|/* Type tool object setting (PS6) */
end_comment

begin_comment
comment|/* Layer Properties */
end_comment

begin_define
DECL|macro|PSD_LPRP_UNICODE
define|#
directive|define
name|PSD_LPRP_UNICODE
value|"luni"
end_define

begin_comment
DECL|macro|PSD_LPRP_UNICODE
comment|/* Unicode layer name (PS5) */
end_comment

begin_define
DECL|macro|PSD_LPRP_SOURCE
define|#
directive|define
name|PSD_LPRP_SOURCE
value|"lnsr"
end_define

begin_comment
DECL|macro|PSD_LPRP_SOURCE
comment|/* Layer name source setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LPRP_ID
define|#
directive|define
name|PSD_LPRP_ID
value|"lyid"
end_define

begin_comment
DECL|macro|PSD_LPRP_ID
comment|/* Layer ID (PS5) */
end_comment

begin_define
DECL|macro|PSD_LPRP_BLEND_CLIP
define|#
directive|define
name|PSD_LPRP_BLEND_CLIP
value|"clbl"
end_define

begin_comment
DECL|macro|PSD_LPRP_BLEND_CLIP
comment|/* Blend clipping elements (PS6) */
end_comment

begin_define
DECL|macro|PSD_LPRP_BLEND_INT
define|#
directive|define
name|PSD_LPRP_BLEND_INT
value|"infx"
end_define

begin_comment
DECL|macro|PSD_LPRP_BLEND_INT
comment|/* Blend interior elements (PS6) */
end_comment

begin_define
DECL|macro|PSD_LPRP_KNOCKOUT
define|#
directive|define
name|PSD_LPRP_KNOCKOUT
value|"knko"
end_define

begin_comment
DECL|macro|PSD_LPRP_KNOCKOUT
comment|/* Knockout setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LPRP_PROTECT
define|#
directive|define
name|PSD_LPRP_PROTECT
value|"lspf"
end_define

begin_comment
DECL|macro|PSD_LPRP_PROTECT
comment|/* Protected setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LPRP_COLOR
define|#
directive|define
name|PSD_LPRP_COLOR
value|"lclr"
end_define

begin_comment
DECL|macro|PSD_LPRP_COLOR
comment|/* Sheet color setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LPRP_REF_POINT
define|#
directive|define
name|PSD_LPRP_REF_POINT
value|"fxrp"
end_define

begin_comment
DECL|macro|PSD_LPRP_REF_POINT
comment|/* Reference point (PS6) */
end_comment

begin_comment
comment|/* Vector mask */
end_comment

begin_define
DECL|macro|PSD_LMSK_VMASK
define|#
directive|define
name|PSD_LMSK_VMASK
value|"vmsk"
end_define

begin_comment
DECL|macro|PSD_LMSK_VMASK
comment|/* Vector mask setting (PS6) */
end_comment

begin_comment
comment|/* Parasites */
end_comment

begin_define
DECL|macro|PSD_LPAR_ANNOTATE
define|#
directive|define
name|PSD_LPAR_ANNOTATE
value|"Anno"
end_define

begin_comment
DECL|macro|PSD_LPAR_ANNOTATE
comment|/* Annotation (PS6) */
end_comment

begin_comment
comment|/* Other */
end_comment

begin_define
DECL|macro|PSD_LOTH_SECTION
define|#
directive|define
name|PSD_LOTH_SECTION
value|"lsct"
end_define

begin_comment
DECL|macro|PSD_LOTH_SECTION
comment|/* Section divider setting - Layer goups (PS6) */
end_comment

begin_define
DECL|macro|PSD_LOTH_PATTERN
define|#
directive|define
name|PSD_LOTH_PATTERN
value|"Patt"
end_define

begin_comment
DECL|macro|PSD_LOTH_PATTERN
comment|/* Patterns (PS6) */
end_comment

begin_define
DECL|macro|PSD_LOTH_GRADIENT
define|#
directive|define
name|PSD_LOTH_GRADIENT
value|"grdm"
end_define

begin_comment
DECL|macro|PSD_LOTH_GRADIENT
comment|/* Gradient settings (PS6) */
end_comment

begin_define
DECL|macro|PSD_LOTH_RESTRICT
define|#
directive|define
name|PSD_LOTH_RESTRICT
value|"brst"
end_define

begin_comment
DECL|macro|PSD_LOTH_RESTRICT
comment|/* Channel blending restirction setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LOTH_FOREIGN_FX
define|#
directive|define
name|PSD_LOTH_FOREIGN_FX
value|"ffxi"
end_define

begin_comment
DECL|macro|PSD_LOTH_FOREIGN_FX
comment|/* Foreign effect ID (PS6) */
end_comment

begin_define
DECL|macro|PSD_LOTH_PATT_DATA
define|#
directive|define
name|PSD_LOTH_PATT_DATA
value|"shpa"
end_define

begin_comment
DECL|macro|PSD_LOTH_PATT_DATA
comment|/* Pattern data (PS6) */
end_comment

begin_define
DECL|macro|PSD_LOTH_META_DATA
define|#
directive|define
name|PSD_LOTH_META_DATA
value|"shmd"
end_define

begin_comment
DECL|macro|PSD_LOTH_META_DATA
comment|/* Meta data setting (PS6) */
end_comment

begin_define
DECL|macro|PSD_LOTH_LAYER_DATA
define|#
directive|define
name|PSD_LOTH_LAYER_DATA
value|"layr"
end_define

begin_comment
DECL|macro|PSD_LOTH_LAYER_DATA
comment|/* Layer data (PS6) */
end_comment

begin_comment
comment|/* Effects layer resource IDs */
end_comment

begin_define
DECL|macro|PSD_LFX_COMMON
define|#
directive|define
name|PSD_LFX_COMMON
value|"cmnS"
end_define

begin_comment
DECL|macro|PSD_LFX_COMMON
comment|/* Effects layer - common state (PS5) */
end_comment

begin_define
DECL|macro|PSD_LFX_DROP_SDW
define|#
directive|define
name|PSD_LFX_DROP_SDW
value|"dsdw"
end_define

begin_comment
DECL|macro|PSD_LFX_DROP_SDW
comment|/* Effects layer - drop shadow (PS5) */
end_comment

begin_define
DECL|macro|PSD_LFX_INNER_SDW
define|#
directive|define
name|PSD_LFX_INNER_SDW
value|"isdw"
end_define

begin_comment
DECL|macro|PSD_LFX_INNER_SDW
comment|/* Effects layer - inner shadow (PS5) */
end_comment

begin_define
DECL|macro|PSD_LFX_OUTER_GLW
define|#
directive|define
name|PSD_LFX_OUTER_GLW
value|"oglw"
end_define

begin_comment
DECL|macro|PSD_LFX_OUTER_GLW
comment|/* Effects layer - outer glow (PS5) */
end_comment

begin_define
DECL|macro|PSD_LFX_INNER_GLW
define|#
directive|define
name|PSD_LFX_INNER_GLW
value|"iglw"
end_define

begin_comment
DECL|macro|PSD_LFX_INNER_GLW
comment|/* Effects layer - inner glow (PS5) */
end_comment

begin_define
DECL|macro|PSD_LFX_BEVEL
define|#
directive|define
name|PSD_LFX_BEVEL
value|"bevl"
end_define

begin_comment
DECL|macro|PSD_LFX_BEVEL
comment|/* Effects layer - bevel (PS5) */
end_comment

begin_comment
comment|/* PSD spec enums */
end_comment

begin_comment
comment|/* Image colour modes */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_BITMAP
name|PSD_BITMAP
init|=
literal|0
block|,
comment|/* Bitmap image */
DECL|enumerator|PSD_GRAYSCALE
name|PSD_GRAYSCALE
init|=
literal|1
block|,
comment|/* Greyscale image */
DECL|enumerator|PSD_INDEXED
name|PSD_INDEXED
init|=
literal|2
block|,
comment|/* Indexed image */
DECL|enumerator|PSD_RGB
name|PSD_RGB
init|=
literal|3
block|,
comment|/* RGB image */
DECL|enumerator|PSD_CMYK
name|PSD_CMYK
init|=
literal|4
block|,
comment|/* CMYK */
DECL|enumerator|PSD_MULTICHANNEL
name|PSD_MULTICHANNEL
init|=
literal|7
block|,
comment|/* Multichannel image*/
DECL|enumerator|PSD_DUOTONE
name|PSD_DUOTONE
init|=
literal|8
block|,
comment|/* Duotone image*/
DECL|enumerator|PSD_LAB
name|PSD_LAB
init|=
literal|9
comment|/* L*a*b image */
DECL|typedef|PSDColorMode
block|}
name|PSDColorMode
typedef|;
end_typedef

begin_comment
comment|/* Image colour spaces */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0203
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_CS_RGB
name|PSD_CS_RGB
init|=
literal|0
block|,
comment|/* RGB */
DECL|enumerator|PSD_CS_HSB
name|PSD_CS_HSB
init|=
literal|1
block|,
comment|/* Hue, Saturation, Brightness */
DECL|enumerator|PSD_CS_CMYK
name|PSD_CS_CMYK
init|=
literal|2
block|,
comment|/* CMYK */
DECL|enumerator|PSD_CS_PANTONE
name|PSD_CS_PANTONE
init|=
literal|3
block|,
comment|/* Pantone matching system (Lab)*/
DECL|enumerator|PSD_CS_FOCOLTONE
name|PSD_CS_FOCOLTONE
init|=
literal|4
block|,
comment|/* Focoltone colour system (CMYK)*/
DECL|enumerator|PSD_CS_TRUMATCH
name|PSD_CS_TRUMATCH
init|=
literal|5
block|,
comment|/* Trumatch color (CMYK)*/
DECL|enumerator|PSD_CS_TOYO
name|PSD_CS_TOYO
init|=
literal|6
block|,
comment|/* Toyo 88 colorfinder 1050 (Lab)*/
DECL|enumerator|PSD_CS_LAB
name|PSD_CS_LAB
init|=
literal|7
block|,
comment|/* L*a*b*/
DECL|enumerator|PSD_CS_GRAYSCALE
name|PSD_CS_GRAYSCALE
init|=
literal|8
block|,
comment|/* Grey scale */
DECL|enumerator|PSD_CS_HKS
name|PSD_CS_HKS
init|=
literal|10
block|,
comment|/* HKS colors (CMYK)*/
DECL|enumerator|PSD_CS_DIC
name|PSD_CS_DIC
init|=
literal|11
block|,
comment|/* DIC color guide (Lab)*/
DECL|enumerator|PSD_CS_ANPA
name|PSD_CS_ANPA
init|=
literal|3000
block|,
comment|/* Anpa color (Lab)*/
DECL|typedef|PSDColorSpace
block|}
name|PSDColorSpace
typedef|;
end_typedef

begin_comment
comment|/* Image Resource IDs */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0303
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_PS2_IMAGE_INFO
name|PSD_PS2_IMAGE_INFO
init|=
literal|1000
block|,
comment|/* 0x03e8 - Obsolete - ps 2.0 image info */
DECL|enumerator|PSD_MAC_PRINT_INFO
name|PSD_MAC_PRINT_INFO
init|=
literal|1001
block|,
comment|/* 0x03e9 - Optional - Mac print manager print info record */
DECL|enumerator|PSD_PS2_COLOR_TAB
name|PSD_PS2_COLOR_TAB
init|=
literal|1003
block|,
comment|/* 0x03eb - Obsolete - ps 2.0 indexed colour table */
DECL|enumerator|PSD_RESN_INFO
name|PSD_RESN_INFO
init|=
literal|1005
block|,
comment|/* 0x03ed - ResolutionInfo structure */
DECL|enumerator|PSD_ALPHA_NAMES
name|PSD_ALPHA_NAMES
init|=
literal|1006
block|,
comment|/* 0x03ee - Alpha channel names */
DECL|enumerator|PSD_DISPLAY_INFO
name|PSD_DISPLAY_INFO
init|=
literal|1007
block|,
comment|/* 0x03ef - DisplayInfo structure */
DECL|enumerator|PSD_CAPTION
name|PSD_CAPTION
init|=
literal|1008
block|,
comment|/* 0x03f0 - Optional - Caption string */
DECL|enumerator|PSD_BORDER_INFO
name|PSD_BORDER_INFO
init|=
literal|1009
block|,
comment|/* 0x03f1 - Border info */
DECL|enumerator|PSD_BACKGROUND_COL
name|PSD_BACKGROUND_COL
init|=
literal|1010
block|,
comment|/* 0x03f2 - Background colour */
DECL|enumerator|PSD_PRINT_FLAGS
name|PSD_PRINT_FLAGS
init|=
literal|1011
block|,
comment|/* 0x03f3 - Print flags */
DECL|enumerator|PSD_GREY_HALFTONE
name|PSD_GREY_HALFTONE
init|=
literal|1012
block|,
comment|/* 0x03f4 - Greyscale and multichannel halftoning info */
DECL|enumerator|PSD_COLOR_HALFTONE
name|PSD_COLOR_HALFTONE
init|=
literal|1013
block|,
comment|/* 0x03f5 - Colour halftoning info */
DECL|enumerator|PSD_DUOTONE_HALFTONE
name|PSD_DUOTONE_HALFTONE
init|=
literal|1014
block|,
comment|/* 0x03f6 - Duotone halftoning info */
DECL|enumerator|PSD_GREY_XFER
name|PSD_GREY_XFER
init|=
literal|1015
block|,
comment|/* 0x03f7 - Greyscale and multichannel transfer functions */
DECL|enumerator|PSD_COLOR_XFER
name|PSD_COLOR_XFER
init|=
literal|1016
block|,
comment|/* 0x03f8 - Colour transfer functions */
DECL|enumerator|PSD_DUOTONE_XFER
name|PSD_DUOTONE_XFER
init|=
literal|1017
block|,
comment|/* 0x03f9 - Duotone transfer functions */
DECL|enumerator|PSD_DUOTONE_INFO
name|PSD_DUOTONE_INFO
init|=
literal|1018
block|,
comment|/* 0x03fa - Duotone image information */
DECL|enumerator|PSD_EFFECTIVE_BW
name|PSD_EFFECTIVE_BW
init|=
literal|1019
block|,
comment|/* 0x03fb - Effective black& white values for dot range */
DECL|enumerator|PSD_OBSOLETE_01
name|PSD_OBSOLETE_01
init|=
literal|1020
block|,
comment|/* 0x03fc - Obsolete */
DECL|enumerator|PSD_EPS_OPT
name|PSD_EPS_OPT
init|=
literal|1021
block|,
comment|/* 0x03fd - EPS options */
DECL|enumerator|PSD_QUICK_MASK
name|PSD_QUICK_MASK
init|=
literal|1022
block|,
comment|/* 0x03fe - Quick mask info */
DECL|enumerator|PSD_OBSOLETE_02
name|PSD_OBSOLETE_02
init|=
literal|1023
block|,
comment|/* 0x03ff - Obsolete */
DECL|enumerator|PSD_LAYER_STATE
name|PSD_LAYER_STATE
init|=
literal|1024
block|,
comment|/* 0x0400 - Layer state info */
DECL|enumerator|PSD_WORKING_PATH
name|PSD_WORKING_PATH
init|=
literal|1025
block|,
comment|/* 0x0401 - Working path (not saved) */
DECL|enumerator|PSD_LAYER_GROUP
name|PSD_LAYER_GROUP
init|=
literal|1026
block|,
comment|/* 0x0402 - Layers group info */
DECL|enumerator|PSD_OBSOLETE_03
name|PSD_OBSOLETE_03
init|=
literal|1027
block|,
comment|/* 0x0403 - Obsolete */
DECL|enumerator|PSD_IPTC_NAA_DATA
name|PSD_IPTC_NAA_DATA
init|=
literal|1028
block|,
comment|/* 0x0404 - IPTC-NAA record (IMV4.pdf) */
DECL|enumerator|PSD_IMAGE_MODE_RAW
name|PSD_IMAGE_MODE_RAW
init|=
literal|1029
block|,
comment|/* 0x0405 - Image mode for raw format files */
DECL|enumerator|PSD_JPEG_QUAL
name|PSD_JPEG_QUAL
init|=
literal|1030
block|,
comment|/* 0x0406 - JPEG quality */
DECL|enumerator|PSD_GRID_GUIDE
name|PSD_GRID_GUIDE
init|=
literal|1032
block|,
comment|/* 0x0408 - Grid& guide info */
DECL|enumerator|PSD_THUMB_RES
name|PSD_THUMB_RES
init|=
literal|1033
block|,
comment|/* 0x0409 - Thumbnail resource */
DECL|enumerator|PSD_COPYRIGHT_FLG
name|PSD_COPYRIGHT_FLG
init|=
literal|1034
block|,
comment|/* 0x040a - Copyright flag */
DECL|enumerator|PSD_URL
name|PSD_URL
init|=
literal|1035
block|,
comment|/* 0x040b - URL string */
DECL|enumerator|PSD_THUMB_RES2
name|PSD_THUMB_RES2
init|=
literal|1036
block|,
comment|/* 0x040c - Thumbnail resource */
DECL|enumerator|PSD_GLOBAL_ANGLE
name|PSD_GLOBAL_ANGLE
init|=
literal|1037
block|,
comment|/* 0x040d - Global angle */
DECL|enumerator|PSD_COLOR_SAMPLER
name|PSD_COLOR_SAMPLER
init|=
literal|1038
block|,
comment|/* 0x040e - Colour samplers resource */
DECL|enumerator|PSD_ICC_PROFILE
name|PSD_ICC_PROFILE
init|=
literal|1039
block|,
comment|/* 0x040f - ICC Profile */
DECL|enumerator|PSD_WATERMARK
name|PSD_WATERMARK
init|=
literal|1040
block|,
comment|/* 0x0410 - Watermark */
DECL|enumerator|PSD_ICC_UNTAGGED
name|PSD_ICC_UNTAGGED
init|=
literal|1041
block|,
comment|/* 0x0411 - Do not use ICC profile flag */
DECL|enumerator|PSD_EFFECTS_VISIBLE
name|PSD_EFFECTS_VISIBLE
init|=
literal|1042
block|,
comment|/* 0x0412 - Show / hide all effects layers */
DECL|enumerator|PSD_SPOT_HALFTONE
name|PSD_SPOT_HALFTONE
init|=
literal|1043
block|,
comment|/* 0x0413 - Spot halftone */
DECL|enumerator|PSD_DOC_IDS
name|PSD_DOC_IDS
init|=
literal|1044
block|,
comment|/* 0x0414 - Document specific IDs */
DECL|enumerator|PSD_ALPHA_NAMES_UNI
name|PSD_ALPHA_NAMES_UNI
init|=
literal|1045
block|,
comment|/* 0x0415 - Unicode alpha names */
DECL|enumerator|PSD_IDX_COL_TAB_CNT
name|PSD_IDX_COL_TAB_CNT
init|=
literal|1046
block|,
comment|/* 0x0416 - Indexed colour table count */
DECL|enumerator|PSD_IDX_TRANSPARENT
name|PSD_IDX_TRANSPARENT
init|=
literal|1047
block|,
comment|/* 0x0417 - Index of transparent colour (if any) */
DECL|enumerator|PSD_GLOBAL_ALT
name|PSD_GLOBAL_ALT
init|=
literal|1049
block|,
comment|/* 0x0419 - Global altitude */
DECL|enumerator|PSD_SLICES
name|PSD_SLICES
init|=
literal|1050
block|,
comment|/* 0x041a - Slices */
DECL|enumerator|PSD_WORKFLOW_URL_UNI
name|PSD_WORKFLOW_URL_UNI
init|=
literal|1051
block|,
comment|/* 0x041b - Workflow URL - Unicode string */
DECL|enumerator|PSD_JUMP_TO_XPEP
name|PSD_JUMP_TO_XPEP
init|=
literal|1052
block|,
comment|/* 0x041c - Jump to XPEP (?) */
DECL|enumerator|PSD_ALPHA_ID
name|PSD_ALPHA_ID
init|=
literal|1053
block|,
comment|/* 0x041d - Alpha IDs */
DECL|enumerator|PSD_URL_LIST_UNI
name|PSD_URL_LIST_UNI
init|=
literal|1054
block|,
comment|/* 0x041e - URL list - unicode */
DECL|enumerator|PSD_VERSION_INFO
name|PSD_VERSION_INFO
init|=
literal|1057
block|,
comment|/* 0x0421 - Version info */
DECL|enumerator|PSD_EXIF_DATA
name|PSD_EXIF_DATA
init|=
literal|1058
block|,
comment|/* 0x0422 - Exif data block */
DECL|enumerator|PSD_XMP_DATA
name|PSD_XMP_DATA
init|=
literal|1060
block|,
comment|/* 0x0424 - XMP data block */
DECL|enumerator|PSD_PATH_INFO_FIRST
name|PSD_PATH_INFO_FIRST
init|=
literal|2000
block|,
comment|/* 0x07d0 - First path info block */
DECL|enumerator|PSD_PATH_INFO_LAST
name|PSD_PATH_INFO_LAST
init|=
literal|2998
block|,
comment|/* 0x0bb6 - Last path info block */
DECL|enumerator|PSD_CLIPPING_PATH
name|PSD_CLIPPING_PATH
init|=
literal|2999
block|,
comment|/* 0x0bb7 - Name of clipping path */
DECL|enumerator|PSD_PRINT_FLAGS_2
name|PSD_PRINT_FLAGS_2
init|=
literal|10000
comment|/* 0x2710 - Print flags */
DECL|typedef|PSDImageResID
block|}
name|PSDImageResID
typedef|;
end_typedef

begin_comment
comment|/* Display resolution units */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0403
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_RES_INCH
name|PSD_RES_INCH
init|=
literal|1
block|,
comment|/* Pixels / inch */
DECL|enumerator|PSD_RES_CM
name|PSD_RES_CM
init|=
literal|2
block|,
comment|/* Pixels / cm */
DECL|typedef|PSDDisplayResUnit
block|}
name|PSDDisplayResUnit
typedef|;
end_typedef

begin_comment
comment|/* Width and height units */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0503
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_UNIT_INCH
name|PSD_UNIT_INCH
init|=
literal|1
block|,
comment|/* inches */
DECL|enumerator|PSD_UNIT_CM
name|PSD_UNIT_CM
init|=
literal|2
block|,
comment|/* cm */
DECL|enumerator|PSD_UNIT_POINT
name|PSD_UNIT_POINT
init|=
literal|3
block|,
comment|/* points  (72 points =   1 inch) */
DECL|enumerator|PSD_UNIT_PICA
name|PSD_UNIT_PICA
init|=
literal|4
block|,
comment|/* pica    ( 6 pica   =   1 inch) */
DECL|enumerator|PSD_UNIT_COLUMN
name|PSD_UNIT_COLUMN
init|=
literal|5
block|,
comment|/* columns ( column defined in ps prefs, default = 2.5 inches) */
DECL|typedef|PSDUnit
block|}
name|PSDUnit
typedef|;
end_typedef

begin_comment
comment|/* Thumbnail image data encoding */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0603
typedef|typedef
enum|enum
block|{
DECL|enumerator|kRawRGB
name|kRawRGB
init|=
literal|0
block|,
comment|/* RAW data format (never used?) */
DECL|enumerator|kJpegRGB
name|kJpegRGB
init|=
literal|1
comment|/* JPEG compression */
DECL|typedef|PSDThumbFormat
block|}
name|PSDThumbFormat
typedef|;
end_typedef

begin_comment
comment|/* Path record types */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0703
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_PATH_CL_LEN
name|PSD_PATH_CL_LEN
init|=
literal|0
block|,
comment|/* Closed sub-path length record */
DECL|enumerator|PSD_PATH_CL_LNK
name|PSD_PATH_CL_LNK
init|=
literal|1
block|,
comment|/* Closed sub-path Bezier knot, linked */
DECL|enumerator|PSD_PATH_CL_UNLNK
name|PSD_PATH_CL_UNLNK
init|=
literal|2
block|,
comment|/* Closed sub-path Bezier knot, unlinked */
DECL|enumerator|PSD_PATH_OP_LEN
name|PSD_PATH_OP_LEN
init|=
literal|3
block|,
comment|/* Open sub-path length record */
DECL|enumerator|PSD_PATH_OP_LNK
name|PSD_PATH_OP_LNK
init|=
literal|4
block|,
comment|/* Open sub-path Bezier knot, linked */
DECL|enumerator|PSD_PATH_OP_UNLNK
name|PSD_PATH_OP_UNLNK
init|=
literal|5
block|,
comment|/* Open sub-path Bezier knot, unlinked */
DECL|enumerator|PSD_PATH_FILL_RULE
name|PSD_PATH_FILL_RULE
init|=
literal|6
block|,
comment|/* Path fill rule record */
DECL|enumerator|PSD_PATH_CLIPBOARD
name|PSD_PATH_CLIPBOARD
init|=
literal|7
block|,
comment|/* Path clipboard record */
DECL|enumerator|PSD_PATH_FILL_INIT
name|PSD_PATH_FILL_INIT
init|=
literal|8
comment|/* Path initial fill record */
DECL|typedef|PSDpathtype
block|}
name|PSDpathtype
typedef|;
end_typedef

begin_comment
comment|/* Channel ID */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0803
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_CHANNEL_MASK
name|PSD_CHANNEL_MASK
init|=
operator|-
literal|2
block|,
comment|/* User supplied layer mask */
DECL|enumerator|PSD_CHANNEL_ALPHA
name|PSD_CHANNEL_ALPHA
init|=
operator|-
literal|1
block|,
comment|/* Transparency mask */
DECL|enumerator|PSD_CHANNEL_RED
name|PSD_CHANNEL_RED
init|=
literal|0
block|,
comment|/* Red channel data */
DECL|enumerator|PSD_CHANNEL_GREEN
name|PSD_CHANNEL_GREEN
init|=
literal|1
block|,
comment|/* Green channel data */
DECL|enumerator|PSD_CHANNEL_BLUE
name|PSD_CHANNEL_BLUE
init|=
literal|2
comment|/* Blue channel data */
DECL|typedef|PSDChannelID
block|}
name|PSDChannelID
typedef|;
end_typedef

begin_comment
comment|/* Clipping */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0903
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_CLIPPING_BASE
name|PSD_CLIPPING_BASE
init|=
literal|0
block|,
comment|/* Base clipping */
DECL|enumerator|PSD_CLIPPING_NON_BASE
name|PSD_CLIPPING_NON_BASE
init|=
literal|1
comment|/* Non-base clipping */
DECL|typedef|PSDClipping
block|}
name|PSDClipping
typedef|;
end_typedef

begin_comment
comment|/* Image compression mode */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0a03
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_COMP_RAW
name|PSD_COMP_RAW
init|=
literal|0
block|,
comment|/* Raw data */
DECL|enumerator|PSD_COMP_RLE
name|PSD_COMP_RLE
block|,
comment|/* RLE compressed */
DECL|enumerator|PSD_COMP_ZIP
name|PSD_COMP_ZIP
block|,
comment|/* ZIP without prediction */
DECL|enumerator|PSD_COMP_ZIP_PRED
name|PSD_COMP_ZIP_PRED
comment|/* ZIP with prediction */
DECL|typedef|PSDCompressMode
block|}
name|PSDCompressMode
typedef|;
end_typedef

begin_comment
comment|/* Vertical - horizontal selection */
end_comment

begin_typedef
DECL|enum|__anon2c61b2dd0b03
typedef|typedef
enum|enum
block|{
DECL|enumerator|PSD_VERTICAL
name|PSD_VERTICAL
init|=
literal|0
block|,
comment|/* Vertical */
DECL|enumerator|PSD_HORIZONTAL
name|PSD_HORIZONTAL
init|=
literal|1
comment|/* Horizontal */
DECL|typedef|VHSelect
block|}
name|VHSelect
typedef|;
end_typedef

begin_comment
comment|/* PSD spec data structures */
end_comment

begin_comment
comment|/* PSD field types */
end_comment

begin_typedef
DECL|typedef|Fixed
typedef|typedef
name|gint32
name|Fixed
typedef|;
end_typedef

begin_comment
DECL|typedef|Fixed
comment|/* Represents a fixed point implied decimal */
end_comment

begin_comment
comment|/* Apple colour space data structures */
end_comment

begin_comment
comment|/* RGB Color Value    A color value expressed in the RGB color space is composed of red, green,    and blue component values. Each color component is expressed as a numeric    value within the range of 0 to 65535. */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd0c08
block|{
DECL|member|red
name|guint16
name|red
decl_stmt|;
DECL|member|green
name|guint16
name|green
decl_stmt|;
DECL|member|blue
name|guint16
name|blue
decl_stmt|;
DECL|typedef|CMRGBColor
block|}
name|CMRGBColor
typedef|;
end_typedef

begin_comment
comment|/*  HSV Color Value     A color value expressed in the HSV color space is composed of hue,     saturation, and value component values. Each color component is     expressed as a numeric value within the range of 0 to 65535 inclusive.     The hue value represents a fraction of a circle in which red is     positioned at 0. */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd0d08
block|{
DECL|member|hue
name|guint16
name|hue
decl_stmt|;
DECL|member|saturation
name|guint16
name|saturation
decl_stmt|;
DECL|member|value
name|guint16
name|value
decl_stmt|;
DECL|typedef|CMHSVColor
block|}
name|CMHSVColor
typedef|;
end_typedef

begin_comment
comment|/* CMYK Color Value   A color value expressed in the CMYK color space is composed of cyan, magenta,   yellow, and black component values. Each color component is expressed as a   numeric value within the range of 0 to 65535 inclusive, with 0 representing   100% ink (e.g. pure cyan = 0, 65535, 65535, 65535). */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd0e08
block|{
DECL|member|cyan
name|guint16
name|cyan
decl_stmt|;
DECL|member|magenta
name|guint16
name|magenta
decl_stmt|;
DECL|member|yellow
name|guint16
name|yellow
decl_stmt|;
DECL|member|black
name|guint16
name|black
decl_stmt|;
DECL|typedef|CMCMYKColor
block|}
name|CMCMYKColor
typedef|;
end_typedef

begin_comment
comment|/* L*a*b* Color Value    The first three values in the color data are, respectively, the colors    lightness, a chrominance, and b chrominance components. The lightness    component is a 16bit value ranging from 0 to 10000. The chrominance    components are each 16bit values ranging from 12800 to 12700. Gray    values are represented by chrominance components of 0 (e.g. pure white    is defined as 10000, 0, 0). */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd0f08
block|{
DECL|member|L
name|guint16
name|L
decl_stmt|;
DECL|member|a
name|gint16
name|a
decl_stmt|;
DECL|member|b
name|gint16
name|b
decl_stmt|;
DECL|typedef|CMLabColor
block|}
name|CMLabColor
typedef|;
end_typedef

begin_comment
comment|/* Gray Color Value   A color value expressed in the Gray color space is composed of a single component,   gray, represented as a numeric value within the range of 0 to 10000. */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1008
block|{
DECL|member|gray
name|guint16
name|gray
decl_stmt|;
DECL|typedef|CMGrayColor
block|}
name|CMGrayColor
typedef|;
end_typedef

begin_comment
comment|/* The color union is defined by the CMColor type definition. */
end_comment

begin_typedef
typedef|typedef
union|union
DECL|union|__anon2c61b2dd110a
block|{
DECL|member|rgb
name|CMRGBColor
name|rgb
decl_stmt|;
DECL|member|hsv
name|CMHSVColor
name|hsv
decl_stmt|;
DECL|member|Lab
name|CMLabColor
name|Lab
decl_stmt|;
DECL|member|cmyk
name|CMCMYKColor
name|cmyk
decl_stmt|;
DECL|member|gray
name|CMGrayColor
name|gray
decl_stmt|;
DECL|typedef|CMColor
block|}
name|CMColor
typedef|;
end_typedef

begin_comment
comment|/* Image resolution data */
end_comment

begin_typedef
DECL|struct|__anon2c61b2dd1208
typedef|typedef
struct|struct
block|{
DECL|member|hRes
name|Fixed
name|hRes
decl_stmt|;
comment|/* Horizontal resolution pixels/inch */
DECL|member|hResUnit
name|gint16
name|hResUnit
decl_stmt|;
comment|/* Horizontal display resolution unit */
DECL|member|widthUnit
name|gint16
name|widthUnit
decl_stmt|;
comment|/* Width unit ?? */
DECL|member|vRes
name|Fixed
name|vRes
decl_stmt|;
comment|/* Vertical resolution pixels/inch */
DECL|member|vResUnit
name|gint16
name|vResUnit
decl_stmt|;
comment|/* Vertical display resolution unit */
DECL|member|heightUnit
name|gint16
name|heightUnit
decl_stmt|;
comment|/* Height unit ?? */
DECL|typedef|ResolutionInfo
block|}
name|ResolutionInfo
typedef|;
end_typedef

begin_comment
comment|/* Grid& guide header */
end_comment

begin_typedef
DECL|struct|__anon2c61b2dd1308
typedef|typedef
struct|struct
block|{
DECL|member|fVersion
name|guint32
name|fVersion
decl_stmt|;
comment|/* Version - always 1 for PS */
DECL|member|fGridCycleV
name|guint32
name|fGridCycleV
decl_stmt|;
comment|/* Vertical grid size */
DECL|member|fGridCycleH
name|guint32
name|fGridCycleH
decl_stmt|;
comment|/* Horizontal grid size */
DECL|member|fGuideCount
name|guint32
name|fGuideCount
decl_stmt|;
comment|/* Number of guides */
DECL|typedef|GuideHeader
block|}
name|GuideHeader
typedef|;
end_typedef

begin_comment
comment|/* Guide resource block */
end_comment

begin_typedef
DECL|struct|__anon2c61b2dd1408
typedef|typedef
struct|struct
block|{
DECL|member|fLocation
name|guint32
name|fLocation
decl_stmt|;
comment|/* Guide position in Pixels * 100 */
DECL|member|fDirection
name|gchar
name|fDirection
decl_stmt|;
comment|/* Guide orientation */
DECL|typedef|GuideResource
block|}
name|GuideResource
typedef|;
end_typedef

begin_comment
comment|/* Thumbnail data */
end_comment

begin_typedef
DECL|struct|__anon2c61b2dd1508
typedef|typedef
struct|struct
block|{
DECL|member|format
name|gint32
name|format
decl_stmt|;
comment|/* Thumbnail image data format (1 = JPEG) */
DECL|member|width
name|gint32
name|width
decl_stmt|;
comment|/* Thumbnail width in pixels */
DECL|member|height
name|gint32
name|height
decl_stmt|;
comment|/* Thumbnail height in pixels */
DECL|member|widthbytes
name|gint32
name|widthbytes
decl_stmt|;
comment|/* Padded row bytes ((width * bitspixel + 31) / 32 * 4) */
DECL|member|size
name|gint32
name|size
decl_stmt|;
comment|/* Total size (widthbytes * height * planes */
DECL|member|compressedsize
name|gint32
name|compressedsize
decl_stmt|;
comment|/* Size after compression for consistency */
DECL|member|bitspixel
name|gint16
name|bitspixel
decl_stmt|;
comment|/* Bits per pixel (always 24) */
DECL|member|planes
name|gint16
name|planes
decl_stmt|;
comment|/* Number of planes (always 1) */
DECL|typedef|ThumbnailInfo
block|}
name|ThumbnailInfo
typedef|;
end_typedef

begin_comment
comment|/* Channel display info data */
end_comment

begin_typedef
DECL|struct|__anon2c61b2dd1608
typedef|typedef
struct|struct
block|{
DECL|member|colorSpace
name|gint16
name|colorSpace
decl_stmt|;
comment|/* Colour space from  PSDColorSpace */
DECL|member|color
name|guint16
name|color
index|[
literal|4
index|]
decl_stmt|;
comment|/* 4 * 16 bit color components */
DECL|member|opacity
name|gint16
name|opacity
decl_stmt|;
comment|/* Opacity 0 to 100 */
DECL|member|kind
name|gchar
name|kind
decl_stmt|;
comment|/* Selected = 0, Protected = 1 */
DECL|member|padding
name|gchar
name|padding
decl_stmt|;
comment|/* Padding */
DECL|typedef|DisplayInfo
block|}
name|DisplayInfo
typedef|;
end_typedef

begin_comment
comment|/* PSD Channel length info data structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1708
block|{
DECL|member|channel_id
name|gint16
name|channel_id
decl_stmt|;
comment|/* Channel ID */
DECL|member|data_len
name|guint32
name|data_len
decl_stmt|;
comment|/* Layer left */
DECL|typedef|ChannelLengthInfo
block|}
name|ChannelLengthInfo
typedef|;
end_typedef

begin_comment
comment|/* PSD Layer flags */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1808
block|{
DECL|member|trans_prot
name|gboolean
name|trans_prot
decl_stmt|;
comment|/* Transparency protected */
DECL|member|visible
name|gboolean
name|visible
decl_stmt|;
comment|/* Visible */
DECL|member|obsolete
name|gboolean
name|obsolete
decl_stmt|;
comment|/* Obsolete */
DECL|member|bit4
name|gboolean
name|bit4
decl_stmt|;
comment|/* Bit 4 in use */
DECL|member|irrelevant
name|gboolean
name|irrelevant
decl_stmt|;
comment|/* Pixel data irrelevant to image appearance */
DECL|typedef|LayerFlags
block|}
name|LayerFlags
typedef|;
end_typedef

begin_comment
comment|/* PSD Layer mask flags */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1908
block|{
DECL|member|relative_pos
name|gboolean
name|relative_pos
decl_stmt|;
comment|/* Mask position recorded relative to layer */
DECL|member|disabled
name|gboolean
name|disabled
decl_stmt|;
comment|/* Mask disabled */
DECL|member|invert
name|gboolean
name|invert
decl_stmt|;
comment|/* Invert mask on blending */
DECL|typedef|MaskFlags
block|}
name|MaskFlags
typedef|;
end_typedef

begin_comment
comment|/* PSD Layer mask data (length 20) */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1a08
block|{
DECL|member|top
name|gint32
name|top
decl_stmt|;
comment|/* Layer top */
DECL|member|left
name|gint32
name|left
decl_stmt|;
comment|/* Layer left */
DECL|member|bottom
name|gint32
name|bottom
decl_stmt|;
comment|/* Layer bottom */
DECL|member|right
name|gint32
name|right
decl_stmt|;
comment|/* Layer right */
DECL|member|def_color
name|guchar
name|def_color
decl_stmt|;
comment|/* Default background colour */
DECL|member|flags
name|guchar
name|flags
decl_stmt|;
comment|/* Layer flags */
DECL|member|extra_def_color
name|guchar
name|extra_def_color
decl_stmt|;
comment|/* Real default background colour */
DECL|member|extra_flags
name|guchar
name|extra_flags
decl_stmt|;
comment|/* Real layer flags */
DECL|member|mask_flags
name|MaskFlags
name|mask_flags
decl_stmt|;
comment|/* Flags */
DECL|typedef|LayerMask
block|}
name|LayerMask
typedef|;
end_typedef

begin_comment
comment|/* PSD Layer mask data (length 36) */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1b08
block|{
DECL|member|top
name|gint32
name|top
decl_stmt|;
comment|/* Layer top */
DECL|member|left
name|gint32
name|left
decl_stmt|;
comment|/* Layer left */
DECL|member|bottom
name|gint32
name|bottom
decl_stmt|;
comment|/* Layer bottom */
DECL|member|right
name|gint32
name|right
decl_stmt|;
comment|/* Layer right */
DECL|typedef|LayerMaskExtra
block|}
name|LayerMaskExtra
typedef|;
end_typedef

begin_comment
comment|/* PSD Layer data structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1c08
block|{
DECL|member|drop
name|gboolean
name|drop
decl_stmt|;
comment|/* Do not add layer to GIMP image */
DECL|member|top
name|gint32
name|top
decl_stmt|;
comment|/* Layer top */
DECL|member|left
name|gint32
name|left
decl_stmt|;
comment|/* Layer left */
DECL|member|bottom
name|gint32
name|bottom
decl_stmt|;
comment|/* Layer bottom */
DECL|member|right
name|gint32
name|right
decl_stmt|;
comment|/* Layer right */
DECL|member|num_channels
name|guint16
name|num_channels
decl_stmt|;
comment|/* Number of channels */
DECL|member|chn_info
name|ChannelLengthInfo
modifier|*
name|chn_info
decl_stmt|;
comment|/* Channel length info */
DECL|member|mode_key
name|gchar
name|mode_key
index|[
literal|4
index|]
decl_stmt|;
comment|/* Blend mode key */
DECL|member|blend_mode
name|gchar
name|blend_mode
index|[
literal|4
index|]
decl_stmt|;
comment|/* Blend mode */
DECL|member|opacity
name|guchar
name|opacity
decl_stmt|;
comment|/* Opacity - 0 = transparent ... 255 = opaque */
DECL|member|clipping
name|guchar
name|clipping
decl_stmt|;
comment|/* Clipping */
DECL|member|flags
name|guchar
name|flags
decl_stmt|;
comment|/* Layer flags */
DECL|member|filler
name|guchar
name|filler
decl_stmt|;
comment|/* Filler */
DECL|member|extra_len
name|guint32
name|extra_len
decl_stmt|;
comment|/* Extra data length */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* Layer name */
DECL|member|mask_len
name|guint32
name|mask_len
decl_stmt|;
comment|/* Layer mask data length */
DECL|member|layer_mask
name|LayerMask
name|layer_mask
decl_stmt|;
comment|/* Layer mask data */
DECL|member|layer_mask_extra
name|LayerMaskExtra
name|layer_mask_extra
decl_stmt|;
comment|/* Layer mask extra data */
DECL|member|layer_flags
name|LayerFlags
name|layer_flags
decl_stmt|;
comment|/* Layer flags */
DECL|member|id
name|guint32
name|id
decl_stmt|;
comment|/* Layer ID (Tattoo) */
DECL|typedef|PSDlayer
block|}
name|PSDlayer
typedef|;
end_typedef

begin_comment
comment|/* PSD Channel data structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1d08
block|{
DECL|member|id
name|gint16
name|id
decl_stmt|;
comment|/* Channel ID */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* Channel name */
DECL|member|data
name|gchar
modifier|*
name|data
decl_stmt|;
comment|/* Channel image data */
DECL|member|rows
name|guint32
name|rows
decl_stmt|;
comment|/* Channel rows */
DECL|member|columns
name|guint32
name|columns
decl_stmt|;
comment|/* Channel columns */
DECL|typedef|PSDchannel
block|}
name|PSDchannel
typedef|;
end_typedef

begin_comment
comment|/* PSD Channel data structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1e08
block|{
DECL|member|gimp_color
name|GimpRGB
name|gimp_color
decl_stmt|;
comment|/* Gimp RGB color */
DECL|member|opacity
name|gint16
name|opacity
decl_stmt|;
comment|/* Opacity */
DECL|member|ps_kind
name|guchar
name|ps_kind
decl_stmt|;
comment|/* PS type flag */
DECL|member|ps_cspace
name|gint16
name|ps_cspace
decl_stmt|;
comment|/* PS colour space */
DECL|member|ps_color
name|CMColor
name|ps_color
decl_stmt|;
comment|/* PS colour */
DECL|typedef|PSDchanneldata
block|}
name|PSDchanneldata
typedef|;
end_typedef

begin_comment
comment|/* PSD Image Resource data structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd1f08
block|{
DECL|member|type
name|gchar
name|type
index|[
literal|4
index|]
decl_stmt|;
comment|/* Image resource type */
DECL|member|id
name|gint16
name|id
decl_stmt|;
comment|/* Image resource ID */
DECL|member|name
name|gchar
name|name
index|[
literal|256
index|]
decl_stmt|;
comment|/* Image resource name (pascal string) */
DECL|member|data_start
name|gint32
name|data_start
decl_stmt|;
comment|/* Image resource data start */
DECL|member|data_len
name|gint32
name|data_len
decl_stmt|;
comment|/* Image resource data length */
DECL|typedef|PSDimageres
block|}
name|PSDimageres
typedef|;
end_typedef

begin_comment
comment|/* PSD Layer Resource data structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd2008
block|{
DECL|member|sig
name|gchar
name|sig
index|[
literal|4
index|]
decl_stmt|;
comment|/* Layer resource signature */
DECL|member|key
name|gchar
name|key
index|[
literal|4
index|]
decl_stmt|;
comment|/* Layer resource key */
DECL|member|data_start
name|gint32
name|data_start
decl_stmt|;
comment|/* Layer resource data start */
DECL|member|data_len
name|gint32
name|data_len
decl_stmt|;
comment|/* Layer resource data length */
DECL|typedef|PSDlayerres
block|}
name|PSDlayerres
typedef|;
end_typedef

begin_comment
comment|/* PSD File data structures */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c61b2dd2108
block|{
DECL|member|channels
name|guint16
name|channels
decl_stmt|;
comment|/* Number of channels: 1- 56 */
DECL|member|transparency
name|gboolean
name|transparency
decl_stmt|;
comment|/* Image has merged transparency alpha channel */
DECL|member|rows
name|guint32
name|rows
decl_stmt|;
comment|/* Number of rows: 1 - 30000 */
DECL|member|columns
name|guint32
name|columns
decl_stmt|;
comment|/* Number of columns: 1 - 30000 */
DECL|member|bps
name|guint16
name|bps
decl_stmt|;
comment|/* Bits per channel: 1, 8 or 16 */
DECL|member|color_mode
name|guint16
name|color_mode
decl_stmt|;
comment|/* Image colour mode: {PSDColorMode} */
DECL|member|base_type
name|GimpImageBaseType
name|base_type
decl_stmt|;
comment|/* Image base colour mode: (GIMP) */
DECL|member|comp_mode
name|guint16
name|comp_mode
decl_stmt|;
comment|/* Merged image compression mode */
DECL|member|color_map
name|guchar
modifier|*
name|color_map
decl_stmt|;
comment|/* Colour map data */
DECL|member|color_map_len
name|guint32
name|color_map_len
decl_stmt|;
comment|/* Colour map data length */
DECL|member|color_map_entries
name|guint32
name|color_map_entries
decl_stmt|;
comment|/* Colour map number of entries */
DECL|member|image_res_start
name|guint32
name|image_res_start
decl_stmt|;
comment|/* Image resource block start address */
DECL|member|image_res_len
name|guint32
name|image_res_len
decl_stmt|;
comment|/* Image resource block length */
DECL|member|mask_layer_start
name|guint32
name|mask_layer_start
decl_stmt|;
comment|/* Mask& layer block start address */
DECL|member|mask_layer_len
name|guint32
name|mask_layer_len
decl_stmt|;
comment|/* Mask& layer block length */
DECL|member|num_layers
name|gint16
name|num_layers
decl_stmt|;
comment|/* Number of layers */
DECL|member|layer_data_start
name|guint32
name|layer_data_start
decl_stmt|;
comment|/* Layer pixel data start */
DECL|member|layer_data_len
name|guint32
name|layer_data_len
decl_stmt|;
comment|/* Layer pixel data length */
DECL|member|merged_image_start
name|guint32
name|merged_image_start
decl_stmt|;
comment|/* Merged image pixel data block start address */
DECL|member|merged_image_len
name|guint32
name|merged_image_len
decl_stmt|;
comment|/* Merged image pixel data block length */
DECL|member|no_icc
name|gboolean
name|no_icc
decl_stmt|;
comment|/* Do not use ICC profile */
DECL|member|layer_state
name|guint16
name|layer_state
decl_stmt|;
comment|/* Active layer number counting from bottom up */
DECL|member|alpha_names
name|GPtrArray
modifier|*
name|alpha_names
decl_stmt|;
comment|/* Alpha channel names */
DECL|member|alpha_display_info
name|PSDchanneldata
modifier|*
modifier|*
name|alpha_display_info
decl_stmt|;
comment|/* Alpha channel display info */
DECL|member|alpha_display_count
name|guint16
name|alpha_display_count
decl_stmt|;
comment|/* Number of alpha channel display info recs */
DECL|member|alpha_id
name|guint32
modifier|*
name|alpha_id
decl_stmt|;
comment|/* Alpha channel ids (tattoos) */
DECL|member|alpha_id_count
name|guint16
name|alpha_id_count
decl_stmt|;
comment|/* Number of alpha channel id items */
DECL|member|quick_mask_id
name|guint16
name|quick_mask_id
decl_stmt|;
comment|/* Channel number containing quick mask */
DECL|typedef|PSDimage
block|}
name|PSDimage
typedef|;
end_typedef

begin_comment
comment|/* Public functions */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PSD_H__ */
end_comment

end_unit


# GIMP - The GNU Image Manipulation Program
# Copyright (C) 1999-2003 Manish Singh <yosh@gimp.org>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUTFILE ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# autogenerated by enumgen.pl

package Gimp::CodeGen::enums;

%enums = (
    GeglDistanceMetric =>
	{ contig => 1,
	  external => 1,
	  symbols => [ qw(GEGL_DISTANCE_METRIC_EUCLIDEAN
			  GEGL_DISTANCE_METRIC_MANHATTAN
			  GEGL_DISTANCE_METRIC_CHEBYSHEV) ],
	  mapping => { GEGL_DISTANCE_METRIC_EUCLIDEAN => '0',
		       GEGL_DISTANCE_METRIC_MANHATTAN => '1',
		       GEGL_DISTANCE_METRIC_CHEBYSHEV => '2' }
	},
    GimpAddMaskType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_ADD_MASK_WHITE GIMP_ADD_MASK_BLACK
			  GIMP_ADD_MASK_ALPHA GIMP_ADD_MASK_ALPHA_TRANSFER
			  GIMP_ADD_MASK_SELECTION GIMP_ADD_MASK_COPY
			  GIMP_ADD_MASK_CHANNEL) ],
	  mapping => { GIMP_ADD_MASK_WHITE => '0',
		       GIMP_ADD_MASK_BLACK => '1',
		       GIMP_ADD_MASK_ALPHA => '2',
		       GIMP_ADD_MASK_ALPHA_TRANSFER => '3',
		       GIMP_ADD_MASK_SELECTION => '4',
		       GIMP_ADD_MASK_COPY => '5',
		       GIMP_ADD_MASK_CHANNEL => '6' }
	},
    GimpBrushGeneratedShape =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_BRUSH_GENERATED_CIRCLE
			  GIMP_BRUSH_GENERATED_SQUARE
			  GIMP_BRUSH_GENERATED_DIAMOND) ],
	  mapping => { GIMP_BRUSH_GENERATED_CIRCLE => '0',
		       GIMP_BRUSH_GENERATED_SQUARE => '1',
		       GIMP_BRUSH_GENERATED_DIAMOND => '2' }
	},
    GimpCapStyle =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_CAP_BUTT GIMP_CAP_ROUND GIMP_CAP_SQUARE) ],
	  mapping => { GIMP_CAP_BUTT => '0',
		       GIMP_CAP_ROUND => '1',
		       GIMP_CAP_SQUARE => '2' }
	},
    GimpChannelOps =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_CHANNEL_OP_ADD GIMP_CHANNEL_OP_SUBTRACT
			  GIMP_CHANNEL_OP_REPLACE GIMP_CHANNEL_OP_INTERSECT) ],
	  mapping => { GIMP_CHANNEL_OP_ADD => '0',
		       GIMP_CHANNEL_OP_SUBTRACT => '1',
		       GIMP_CHANNEL_OP_REPLACE => '2',
		       GIMP_CHANNEL_OP_INTERSECT => '3' }
	},
    GimpChannelType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_CHANNEL_RED GIMP_CHANNEL_GREEN
			  GIMP_CHANNEL_BLUE GIMP_CHANNEL_GRAY
			  GIMP_CHANNEL_INDEXED GIMP_CHANNEL_ALPHA) ],
	  mapping => { GIMP_CHANNEL_RED => '0',
		       GIMP_CHANNEL_GREEN => '1',
		       GIMP_CHANNEL_BLUE => '2',
		       GIMP_CHANNEL_GRAY => '3',
		       GIMP_CHANNEL_INDEXED => '4',
		       GIMP_CHANNEL_ALPHA => '5' }
	},
    GimpCloneType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_CLONE_IMAGE GIMP_CLONE_PATTERN) ],
	  mapping => { GIMP_CLONE_IMAGE => '0',
		       GIMP_CLONE_PATTERN => '1' }
	},
    GimpColorTag =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_COLOR_TAG_NONE GIMP_COLOR_TAG_BLUE
			  GIMP_COLOR_TAG_GREEN GIMP_COLOR_TAG_YELLOW
			  GIMP_COLOR_TAG_ORANGE GIMP_COLOR_TAG_BROWN
			  GIMP_COLOR_TAG_RED GIMP_COLOR_TAG_VIOLET
			  GIMP_COLOR_TAG_GRAY) ],
	  mapping => { GIMP_COLOR_TAG_NONE => '0',
		       GIMP_COLOR_TAG_BLUE => '1',
		       GIMP_COLOR_TAG_GREEN => '2',
		       GIMP_COLOR_TAG_YELLOW => '3',
		       GIMP_COLOR_TAG_ORANGE => '4',
		       GIMP_COLOR_TAG_BROWN => '5',
		       GIMP_COLOR_TAG_RED => '6',
		       GIMP_COLOR_TAG_VIOLET => '7',
		       GIMP_COLOR_TAG_GRAY => '8' }
	},
    GimpComponentType =>
	{ contig => 0,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_COMPONENT_TYPE_U8 GIMP_COMPONENT_TYPE_U16
			  GIMP_COMPONENT_TYPE_U32 GIMP_COMPONENT_TYPE_HALF
			  GIMP_COMPONENT_TYPE_FLOAT
			  GIMP_COMPONENT_TYPE_DOUBLE) ],
	  mapping => { GIMP_COMPONENT_TYPE_U8 => '100',
		       GIMP_COMPONENT_TYPE_U16 => '200',
		       GIMP_COMPONENT_TYPE_U32 => '300',
		       GIMP_COMPONENT_TYPE_HALF => '500',
		       GIMP_COMPONENT_TYPE_FLOAT => '600',
		       GIMP_COMPONENT_TYPE_DOUBLE => '700' }
	},
    GimpConvertPaletteType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_CONVERT_PALETTE_GENERATE
			  GIMP_CONVERT_PALETTE_WEB GIMP_CONVERT_PALETTE_MONO
			  GIMP_CONVERT_PALETTE_CUSTOM) ],
	  mapping => { GIMP_CONVERT_PALETTE_GENERATE => '0',
		       GIMP_CONVERT_PALETTE_WEB => '1',
		       GIMP_CONVERT_PALETTE_MONO => '2',
		       GIMP_CONVERT_PALETTE_CUSTOM => '3' }
	},
    GimpConvolveType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_CONVOLVE_BLUR GIMP_CONVOLVE_SHARPEN) ],
	  mapping => { GIMP_CONVOLVE_BLUR => '0',
		       GIMP_CONVOLVE_SHARPEN => '1' }
	},
    GimpDesaturateMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_DESATURATE_LIGHTNESS GIMP_DESATURATE_LUMA
			  GIMP_DESATURATE_AVERAGE GIMP_DESATURATE_LUMINANCE
			  GIMP_DESATURATE_VALUE) ],
	  mapping => { GIMP_DESATURATE_LIGHTNESS => '0',
		       GIMP_DESATURATE_LUMA => '1',
		       GIMP_DESATURATE_AVERAGE => '2',
		       GIMP_DESATURATE_LUMINANCE => '3',
		       GIMP_DESATURATE_VALUE => '4' }
	},
    GimpDodgeBurnType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_DODGE_BURN_TYPE_DODGE
			  GIMP_DODGE_BURN_TYPE_BURN) ],
	  mapping => { GIMP_DODGE_BURN_TYPE_DODGE => '0',
		       GIMP_DODGE_BURN_TYPE_BURN => '1' }
	},
    GimpFillType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_FILL_FOREGROUND GIMP_FILL_BACKGROUND
			  GIMP_FILL_WHITE GIMP_FILL_TRANSPARENT
			  GIMP_FILL_PATTERN) ],
	  mapping => { GIMP_FILL_FOREGROUND => '0',
		       GIMP_FILL_BACKGROUND => '1',
		       GIMP_FILL_WHITE => '2',
		       GIMP_FILL_TRANSPARENT => '3',
		       GIMP_FILL_PATTERN => '4' }
	},
    GimpForegroundExtractMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_FOREGROUND_EXTRACT_SIOX
			  GIMP_FOREGROUND_EXTRACT_MATTING) ],
	  mapping => { GIMP_FOREGROUND_EXTRACT_SIOX => '0',
		       GIMP_FOREGROUND_EXTRACT_MATTING => '1' }
	},
    GimpGradientBlendColorSpace =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_GRADIENT_BLEND_RGB_PERCEPTUAL
			  GIMP_GRADIENT_BLEND_RGB_LINEAR
			  GIMP_GRADIENT_BLEND_CIE_LAB) ],
	  mapping => { GIMP_GRADIENT_BLEND_RGB_PERCEPTUAL => '0',
		       GIMP_GRADIENT_BLEND_RGB_LINEAR => '1',
		       GIMP_GRADIENT_BLEND_CIE_LAB => '2' }
	},
    GimpGradientSegmentColor =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_GRADIENT_SEGMENT_RGB
			  GIMP_GRADIENT_SEGMENT_HSV_CCW
			  GIMP_GRADIENT_SEGMENT_HSV_CW) ],
	  mapping => { GIMP_GRADIENT_SEGMENT_RGB => '0',
		       GIMP_GRADIENT_SEGMENT_HSV_CCW => '1',
		       GIMP_GRADIENT_SEGMENT_HSV_CW => '2' }
	},
    GimpGradientSegmentType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_GRADIENT_SEGMENT_LINEAR
			  GIMP_GRADIENT_SEGMENT_CURVED
			  GIMP_GRADIENT_SEGMENT_SINE
			  GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
			  GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING
			  GIMP_GRADIENT_SEGMENT_STEP) ],
	  mapping => { GIMP_GRADIENT_SEGMENT_LINEAR => '0',
		       GIMP_GRADIENT_SEGMENT_CURVED => '1',
		       GIMP_GRADIENT_SEGMENT_SINE => '2',
		       GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING => '3',
		       GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING => '4',
		       GIMP_GRADIENT_SEGMENT_STEP => '5' }
	},
    GimpGradientType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_GRADIENT_LINEAR GIMP_GRADIENT_BILINEAR
			  GIMP_GRADIENT_RADIAL GIMP_GRADIENT_SQUARE
			  GIMP_GRADIENT_CONICAL_SYMMETRIC
			  GIMP_GRADIENT_CONICAL_ASYMMETRIC
			  GIMP_GRADIENT_SHAPEBURST_ANGULAR
			  GIMP_GRADIENT_SHAPEBURST_SPHERICAL
			  GIMP_GRADIENT_SHAPEBURST_DIMPLED
			  GIMP_GRADIENT_SPIRAL_CLOCKWISE
			  GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE) ],
	  mapping => { GIMP_GRADIENT_LINEAR => '0',
		       GIMP_GRADIENT_BILINEAR => '1',
		       GIMP_GRADIENT_RADIAL => '2',
		       GIMP_GRADIENT_SQUARE => '3',
		       GIMP_GRADIENT_CONICAL_SYMMETRIC => '4',
		       GIMP_GRADIENT_CONICAL_ASYMMETRIC => '5',
		       GIMP_GRADIENT_SHAPEBURST_ANGULAR => '6',
		       GIMP_GRADIENT_SHAPEBURST_SPHERICAL => '7',
		       GIMP_GRADIENT_SHAPEBURST_DIMPLED => '8',
		       GIMP_GRADIENT_SPIRAL_CLOCKWISE => '9',
		       GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE => '10' }
	},
    GimpGridStyle =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_GRID_DOTS GIMP_GRID_INTERSECTIONS
			  GIMP_GRID_ON_OFF_DASH GIMP_GRID_DOUBLE_DASH
			  GIMP_GRID_SOLID) ],
	  mapping => { GIMP_GRID_DOTS => '0',
		       GIMP_GRID_INTERSECTIONS => '1',
		       GIMP_GRID_ON_OFF_DASH => '2',
		       GIMP_GRID_DOUBLE_DASH => '3',
		       GIMP_GRID_SOLID => '4' }
	},
    GimpHueRange =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_HUE_RANGE_ALL GIMP_HUE_RANGE_RED
			  GIMP_HUE_RANGE_YELLOW GIMP_HUE_RANGE_GREEN
			  GIMP_HUE_RANGE_CYAN GIMP_HUE_RANGE_BLUE
			  GIMP_HUE_RANGE_MAGENTA) ],
	  mapping => { GIMP_HUE_RANGE_ALL => '0',
		       GIMP_HUE_RANGE_RED => '1',
		       GIMP_HUE_RANGE_YELLOW => '2',
		       GIMP_HUE_RANGE_GREEN => '3',
		       GIMP_HUE_RANGE_CYAN => '4',
		       GIMP_HUE_RANGE_BLUE => '5',
		       GIMP_HUE_RANGE_MAGENTA => '6' }
	},
    GimpIconType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_ICON_TYPE_ICON_NAME GIMP_ICON_TYPE_PIXBUF
			  GIMP_ICON_TYPE_IMAGE_FILE) ],
	  mapping => { GIMP_ICON_TYPE_ICON_NAME => '0',
		       GIMP_ICON_TYPE_PIXBUF => '1',
		       GIMP_ICON_TYPE_IMAGE_FILE => '2' }
	},
    GimpImageBaseType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_RGB GIMP_GRAY GIMP_INDEXED) ],
	  mapping => { GIMP_RGB => '0',
		       GIMP_GRAY => '1',
		       GIMP_INDEXED => '2' }
	},
    GimpImageType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_RGB_IMAGE GIMP_RGBA_IMAGE GIMP_GRAY_IMAGE
			  GIMP_GRAYA_IMAGE GIMP_INDEXED_IMAGE
			  GIMP_INDEXEDA_IMAGE) ],
	  mapping => { GIMP_RGB_IMAGE => '0',
		       GIMP_RGBA_IMAGE => '1',
		       GIMP_GRAY_IMAGE => '2',
		       GIMP_GRAYA_IMAGE => '3',
		       GIMP_INDEXED_IMAGE => '4',
		       GIMP_INDEXEDA_IMAGE => '5' }
	},
    GimpInkBlobType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_INK_BLOB_TYPE_CIRCLE
			  GIMP_INK_BLOB_TYPE_SQUARE
			  GIMP_INK_BLOB_TYPE_DIAMOND) ],
	  mapping => { GIMP_INK_BLOB_TYPE_CIRCLE => '0',
		       GIMP_INK_BLOB_TYPE_SQUARE => '1',
		       GIMP_INK_BLOB_TYPE_DIAMOND => '2' }
	},
    GimpInterpolationType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_INTERPOLATION_NONE GIMP_INTERPOLATION_LINEAR
			  GIMP_INTERPOLATION_CUBIC GIMP_INTERPOLATION_NOHALO
			  GIMP_INTERPOLATION_LOHALO) ],
	  mapping => { GIMP_INTERPOLATION_NONE => '0',
		       GIMP_INTERPOLATION_LINEAR => '1',
		       GIMP_INTERPOLATION_CUBIC => '2',
		       GIMP_INTERPOLATION_NOHALO => '3',
		       GIMP_INTERPOLATION_LOHALO => '4' }
	},
    GimpJoinStyle =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_JOIN_MITER GIMP_JOIN_ROUND GIMP_JOIN_BEVEL) ],
	  mapping => { GIMP_JOIN_MITER => '0',
		       GIMP_JOIN_ROUND => '1',
		       GIMP_JOIN_BEVEL => '2' }
	},
    GimpMaskApplyMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_MASK_APPLY GIMP_MASK_DISCARD) ],
	  mapping => { GIMP_MASK_APPLY => '0',
		       GIMP_MASK_DISCARD => '1' }
	},
    GimpMergeType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_EXPAND_AS_NECESSARY GIMP_CLIP_TO_IMAGE
			  GIMP_CLIP_TO_BOTTOM_LAYER GIMP_FLATTEN_IMAGE) ],
	  mapping => { GIMP_EXPAND_AS_NECESSARY => '0',
		       GIMP_CLIP_TO_IMAGE => '1',
		       GIMP_CLIP_TO_BOTTOM_LAYER => '2',
		       GIMP_FLATTEN_IMAGE => '3' }
	},
    GimpMessageHandlerType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_MESSAGE_BOX GIMP_CONSOLE GIMP_ERROR_CONSOLE) ],
	  mapping => { GIMP_MESSAGE_BOX => '0',
		       GIMP_CONSOLE => '1',
		       GIMP_ERROR_CONSOLE => '2' }
	},
    GimpOffsetType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_OFFSET_BACKGROUND GIMP_OFFSET_TRANSPARENT
			  GIMP_OFFSET_WRAP_AROUND) ],
	  mapping => { GIMP_OFFSET_BACKGROUND => '0',
		       GIMP_OFFSET_TRANSPARENT => '1',
		       GIMP_OFFSET_WRAP_AROUND => '2' }
	},
    GimpOrientationType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_ORIENTATION_HORIZONTAL
			  GIMP_ORIENTATION_VERTICAL GIMP_ORIENTATION_UNKNOWN) ],
	  mapping => { GIMP_ORIENTATION_HORIZONTAL => '0',
		       GIMP_ORIENTATION_VERTICAL => '1',
		       GIMP_ORIENTATION_UNKNOWN => '2' }
	},
    GimpPaintApplicationMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PAINT_CONSTANT GIMP_PAINT_INCREMENTAL) ],
	  mapping => { GIMP_PAINT_CONSTANT => '0',
		       GIMP_PAINT_INCREMENTAL => '1' }
	},
    GimpPDBErrorHandler =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PDB_ERROR_HANDLER_INTERNAL
			  GIMP_PDB_ERROR_HANDLER_PLUGIN) ],
	  mapping => { GIMP_PDB_ERROR_HANDLER_INTERNAL => '0',
		       GIMP_PDB_ERROR_HANDLER_PLUGIN => '1' }
	},
    GimpPDBProcType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PDB_PROC_TYPE_INTERNAL
			  GIMP_PDB_PROC_TYPE_PLUGIN
			  GIMP_PDB_PROC_TYPE_EXTENSION
			  GIMP_PDB_PROC_TYPE_TEMPORARY) ],
	  mapping => { GIMP_PDB_PROC_TYPE_INTERNAL => '0',
		       GIMP_PDB_PROC_TYPE_PLUGIN => '1',
		       GIMP_PDB_PROC_TYPE_EXTENSION => '2',
		       GIMP_PDB_PROC_TYPE_TEMPORARY => '3' }
	},
    GimpPDBStatusType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PDB_EXECUTION_ERROR GIMP_PDB_CALLING_ERROR
			  GIMP_PDB_PASS_THROUGH GIMP_PDB_SUCCESS
			  GIMP_PDB_CANCEL) ],
	  mapping => { GIMP_PDB_EXECUTION_ERROR => '0',
		       GIMP_PDB_CALLING_ERROR => '1',
		       GIMP_PDB_PASS_THROUGH => '2',
		       GIMP_PDB_SUCCESS => '3',
		       GIMP_PDB_CANCEL => '4' }
	},
    GimpPrecision =>
	{ contig => 0,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PRECISION_U8_LINEAR
			  GIMP_PRECISION_U8_NON_LINEAR
			  GIMP_PRECISION_U8_PERCEPTUAL
			  GIMP_PRECISION_U16_LINEAR
			  GIMP_PRECISION_U16_NON_LINEAR
			  GIMP_PRECISION_U16_PERCEPTUAL
			  GIMP_PRECISION_U32_LINEAR
			  GIMP_PRECISION_U32_NON_LINEAR
			  GIMP_PRECISION_U32_PERCEPTUAL
			  GIMP_PRECISION_HALF_LINEAR
			  GIMP_PRECISION_HALF_NON_LINEAR
			  GIMP_PRECISION_HALF_PERCEPTUAL
			  GIMP_PRECISION_FLOAT_LINEAR
			  GIMP_PRECISION_FLOAT_NON_LINEAR
			  GIMP_PRECISION_FLOAT_PERCEPTUAL
			  GIMP_PRECISION_DOUBLE_LINEAR
			  GIMP_PRECISION_DOUBLE_NON_LINEAR
			  GIMP_PRECISION_DOUBLE_PERCEPTUAL
			  GIMP_PRECISION_U8_GAMMA GIMP_PRECISION_U16_GAMMA
			  GIMP_PRECISION_U32_GAMMA GIMP_PRECISION_HALF_GAMMA
			  GIMP_PRECISION_FLOAT_GAMMA
			  GIMP_PRECISION_DOUBLE_GAMMA) ],
	  mapping => { GIMP_PRECISION_U8_LINEAR => '100',
		       GIMP_PRECISION_U8_NON_LINEAR => '150',
		       GIMP_PRECISION_U8_PERCEPTUAL => '175',
		       GIMP_PRECISION_U16_LINEAR => '200',
		       GIMP_PRECISION_U16_NON_LINEAR => '250',
		       GIMP_PRECISION_U16_PERCEPTUAL => '275',
		       GIMP_PRECISION_U32_LINEAR => '300',
		       GIMP_PRECISION_U32_NON_LINEAR => '350',
		       GIMP_PRECISION_U32_PERCEPTUAL => '375',
		       GIMP_PRECISION_HALF_LINEAR => '500',
		       GIMP_PRECISION_HALF_NON_LINEAR => '550',
		       GIMP_PRECISION_HALF_PERCEPTUAL => '575',
		       GIMP_PRECISION_FLOAT_LINEAR => '600',
		       GIMP_PRECISION_FLOAT_NON_LINEAR => '650',
		       GIMP_PRECISION_FLOAT_PERCEPTUAL => '675',
		       GIMP_PRECISION_DOUBLE_LINEAR => '700',
		       GIMP_PRECISION_DOUBLE_NON_LINEAR => '750',
		       GIMP_PRECISION_DOUBLE_PERCEPTUAL => '775',
		       GIMP_PRECISION_U8_GAMMA => 'GIMP_PRECISION_U8_NON_LINEAR',
		       GIMP_PRECISION_U16_GAMMA => 'GIMP_PRECISION_U16_NON_LINEAR',
		       GIMP_PRECISION_U32_GAMMA => 'GIMP_PRECISION_U32_NON_LINEAR',
		       GIMP_PRECISION_HALF_GAMMA => 'GIMP_PRECISION_HALF_NON_LINEAR',
		       GIMP_PRECISION_FLOAT_GAMMA => 'GIMP_PRECISION_FLOAT_NON_LINEAR',
		       GIMP_PRECISION_DOUBLE_GAMMA => 'GIMP_PRECISION_DOUBLE_NON_LINEAR' }
	},
    GimpProgressCommand =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PROGRESS_COMMAND_START
			  GIMP_PROGRESS_COMMAND_END
			  GIMP_PROGRESS_COMMAND_SET_TEXT
			  GIMP_PROGRESS_COMMAND_SET_VALUE
			  GIMP_PROGRESS_COMMAND_PULSE
			  GIMP_PROGRESS_COMMAND_GET_WINDOW) ],
	  mapping => { GIMP_PROGRESS_COMMAND_START => '0',
		       GIMP_PROGRESS_COMMAND_END => '1',
		       GIMP_PROGRESS_COMMAND_SET_TEXT => '2',
		       GIMP_PROGRESS_COMMAND_SET_VALUE => '3',
		       GIMP_PROGRESS_COMMAND_PULSE => '4',
		       GIMP_PROGRESS_COMMAND_GET_WINDOW => '5' }
	},
    GimpRepeatMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_REPEAT_NONE GIMP_REPEAT_SAWTOOTH
			  GIMP_REPEAT_TRIANGULAR GIMP_REPEAT_TRUNCATE) ],
	  mapping => { GIMP_REPEAT_NONE => '0',
		       GIMP_REPEAT_SAWTOOTH => '1',
		       GIMP_REPEAT_TRIANGULAR => '2',
		       GIMP_REPEAT_TRUNCATE => '3' }
	},
    GimpRotationType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_ROTATE_90 GIMP_ROTATE_180 GIMP_ROTATE_270) ],
	  mapping => { GIMP_ROTATE_90 => '0',
		       GIMP_ROTATE_180 => '1',
		       GIMP_ROTATE_270 => '2' }
	},
    GimpRunMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_RUN_INTERACTIVE GIMP_RUN_NONINTERACTIVE
			  GIMP_RUN_WITH_LAST_VALS) ],
	  mapping => { GIMP_RUN_INTERACTIVE => '0',
		       GIMP_RUN_NONINTERACTIVE => '1',
		       GIMP_RUN_WITH_LAST_VALS => '2' }
	},
    GimpSelectCriterion =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_SELECT_CRITERION_COMPOSITE
			  GIMP_SELECT_CRITERION_R GIMP_SELECT_CRITERION_G
			  GIMP_SELECT_CRITERION_B GIMP_SELECT_CRITERION_H
			  GIMP_SELECT_CRITERION_S GIMP_SELECT_CRITERION_V
			  GIMP_SELECT_CRITERION_A
			  GIMP_SELECT_CRITERION_LCH_L
			  GIMP_SELECT_CRITERION_LCH_C
			  GIMP_SELECT_CRITERION_LCH_H) ],
	  mapping => { GIMP_SELECT_CRITERION_COMPOSITE => '0',
		       GIMP_SELECT_CRITERION_R => '1',
		       GIMP_SELECT_CRITERION_G => '2',
		       GIMP_SELECT_CRITERION_B => '3',
		       GIMP_SELECT_CRITERION_H => '4',
		       GIMP_SELECT_CRITERION_S => '5',
		       GIMP_SELECT_CRITERION_V => '6',
		       GIMP_SELECT_CRITERION_A => '7',
		       GIMP_SELECT_CRITERION_LCH_L => '8',
		       GIMP_SELECT_CRITERION_LCH_C => '9',
		       GIMP_SELECT_CRITERION_LCH_H => '10' }
	},
    GimpSizeType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PIXELS GIMP_POINTS) ],
	  mapping => { GIMP_PIXELS => '0',
		       GIMP_POINTS => '1' }
	},
    GimpStackTraceMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_STACK_TRACE_NEVER GIMP_STACK_TRACE_QUERY
			  GIMP_STACK_TRACE_ALWAYS) ],
	  mapping => { GIMP_STACK_TRACE_NEVER => '0',
		       GIMP_STACK_TRACE_QUERY => '1',
		       GIMP_STACK_TRACE_ALWAYS => '2' }
	},
    GimpStrokeMethod =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_STROKE_LINE GIMP_STROKE_PAINT_METHOD) ],
	  mapping => { GIMP_STROKE_LINE => '0',
		       GIMP_STROKE_PAINT_METHOD => '1' }
	},
    GimpTextDirection =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_TEXT_DIRECTION_LTR GIMP_TEXT_DIRECTION_RTL
			  GIMP_TEXT_DIRECTION_TTB_RTL
			  GIMP_TEXT_DIRECTION_TTB_RTL_UPRIGHT
			  GIMP_TEXT_DIRECTION_TTB_LTR
			  GIMP_TEXT_DIRECTION_TTB_LTR_UPRIGHT) ],
	  mapping => { GIMP_TEXT_DIRECTION_LTR => '0',
		       GIMP_TEXT_DIRECTION_RTL => '1',
		       GIMP_TEXT_DIRECTION_TTB_RTL => '2',
		       GIMP_TEXT_DIRECTION_TTB_RTL_UPRIGHT => '3',
		       GIMP_TEXT_DIRECTION_TTB_LTR => '4',
		       GIMP_TEXT_DIRECTION_TTB_LTR_UPRIGHT => '5' }
	},
    GimpTextHintStyle =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_TEXT_HINT_STYLE_NONE
			  GIMP_TEXT_HINT_STYLE_SLIGHT
			  GIMP_TEXT_HINT_STYLE_MEDIUM
			  GIMP_TEXT_HINT_STYLE_FULL) ],
	  mapping => { GIMP_TEXT_HINT_STYLE_NONE => '0',
		       GIMP_TEXT_HINT_STYLE_SLIGHT => '1',
		       GIMP_TEXT_HINT_STYLE_MEDIUM => '2',
		       GIMP_TEXT_HINT_STYLE_FULL => '3' }
	},
    GimpTextJustification =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_TEXT_JUSTIFY_LEFT GIMP_TEXT_JUSTIFY_RIGHT
			  GIMP_TEXT_JUSTIFY_CENTER GIMP_TEXT_JUSTIFY_FILL) ],
	  mapping => { GIMP_TEXT_JUSTIFY_LEFT => '0',
		       GIMP_TEXT_JUSTIFY_RIGHT => '1',
		       GIMP_TEXT_JUSTIFY_CENTER => '2',
		       GIMP_TEXT_JUSTIFY_FILL => '3' }
	},
    GimpTransferMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_TRANSFER_SHADOWS GIMP_TRANSFER_MIDTONES
			  GIMP_TRANSFER_HIGHLIGHTS) ],
	  mapping => { GIMP_TRANSFER_SHADOWS => '0',
		       GIMP_TRANSFER_MIDTONES => '1',
		       GIMP_TRANSFER_HIGHLIGHTS => '2' }
	},
    GimpTransformDirection =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_TRANSFORM_FORWARD GIMP_TRANSFORM_BACKWARD) ],
	  mapping => { GIMP_TRANSFORM_FORWARD => '0',
		       GIMP_TRANSFORM_BACKWARD => '1' }
	},
    GimpTransformResize =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_TRANSFORM_RESIZE_ADJUST
			  GIMP_TRANSFORM_RESIZE_CLIP
			  GIMP_TRANSFORM_RESIZE_CROP
			  GIMP_TRANSFORM_RESIZE_CROP_WITH_ASPECT) ],
	  mapping => { GIMP_TRANSFORM_RESIZE_ADJUST => '0',
		       GIMP_TRANSFORM_RESIZE_CLIP => '1',
		       GIMP_TRANSFORM_RESIZE_CROP => '2',
		       GIMP_TRANSFORM_RESIZE_CROP_WITH_ASPECT => '3' }
	},
    GimpUnit =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_UNIT_PIXEL GIMP_UNIT_INCH GIMP_UNIT_MM
			  GIMP_UNIT_POINT GIMP_UNIT_PICA GIMP_UNIT_END) ],
	  mapping => { GIMP_UNIT_PIXEL => '0',
		       GIMP_UNIT_INCH => '1',
		       GIMP_UNIT_MM => '2',
		       GIMP_UNIT_POINT => '3',
		       GIMP_UNIT_PICA => '4',
		       GIMP_UNIT_END => '5' }
	},
    GimpVectorsStrokeType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_VECTORS_STROKE_TYPE_BEZIER) ],
	  mapping => { GIMP_VECTORS_STROKE_TYPE_BEZIER => '0' }
	},
    GimpColorManagementMode =>
	{ contig => 1,
	  header => 'libgimpconfig/gimpconfigenums.h',
	  symbols => [ qw(GIMP_COLOR_MANAGEMENT_OFF
			  GIMP_COLOR_MANAGEMENT_DISPLAY
			  GIMP_COLOR_MANAGEMENT_SOFTPROOF) ],
	  mapping => { GIMP_COLOR_MANAGEMENT_OFF => '0',
		       GIMP_COLOR_MANAGEMENT_DISPLAY => '1',
		       GIMP_COLOR_MANAGEMENT_SOFTPROOF => '2' }
	},
    GimpColorRenderingIntent =>
	{ contig => 1,
	  header => 'libgimpconfig/gimpconfigenums.h',
	  symbols => [ qw(GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
			  GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
			  GIMP_COLOR_RENDERING_INTENT_SATURATION
			  GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC) ],
	  mapping => { GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL => '0',
		       GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC => '1',
		       GIMP_COLOR_RENDERING_INTENT_SATURATION => '2',
		       GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC => '3' }
	},
    GimpLayerColorSpace =>
	{ contig => 1,
	  header => 'operations/operations-enums.h',
	  symbols => [ qw(GIMP_LAYER_COLOR_SPACE_AUTO
			  GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
			  GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL) ],
	  mapping => { GIMP_LAYER_COLOR_SPACE_AUTO => '0',
		       GIMP_LAYER_COLOR_SPACE_RGB_LINEAR => '1',
		       GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL => '2' }
	},
    GimpLayerCompositeMode =>
	{ contig => 1,
	  header => 'operations/operations-enums.h',
	  symbols => [ qw(GIMP_LAYER_COMPOSITE_AUTO
			  GIMP_LAYER_COMPOSITE_UNION
			  GIMP_LAYER_COMPOSITE_CLIP_TO_BACKDROP
			  GIMP_LAYER_COMPOSITE_CLIP_TO_LAYER
			  GIMP_LAYER_COMPOSITE_INTERSECTION) ],
	  mapping => { GIMP_LAYER_COMPOSITE_AUTO => '0',
		       GIMP_LAYER_COMPOSITE_UNION => '1',
		       GIMP_LAYER_COMPOSITE_CLIP_TO_BACKDROP => '2',
		       GIMP_LAYER_COMPOSITE_CLIP_TO_LAYER => '3',
		       GIMP_LAYER_COMPOSITE_INTERSECTION => '4' }
	},
    GimpLayerMode =>
	{ contig => 1,
	  header => 'operations/operations-enums.h',
	  symbols => [ qw(GIMP_LAYER_MODE_NORMAL_LEGACY
			  GIMP_LAYER_MODE_DISSOLVE
			  GIMP_LAYER_MODE_BEHIND_LEGACY
			  GIMP_LAYER_MODE_MULTIPLY_LEGACY
			  GIMP_LAYER_MODE_SCREEN_LEGACY
			  GIMP_LAYER_MODE_OVERLAY_LEGACY
			  GIMP_LAYER_MODE_DIFFERENCE_LEGACY
			  GIMP_LAYER_MODE_ADDITION_LEGACY
			  GIMP_LAYER_MODE_SUBTRACT_LEGACY
			  GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
			  GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
			  GIMP_LAYER_MODE_HSV_HUE_LEGACY
			  GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
			  GIMP_LAYER_MODE_HSL_COLOR_LEGACY
			  GIMP_LAYER_MODE_HSV_VALUE_LEGACY
			  GIMP_LAYER_MODE_DIVIDE_LEGACY
			  GIMP_LAYER_MODE_DODGE_LEGACY
			  GIMP_LAYER_MODE_BURN_LEGACY
			  GIMP_LAYER_MODE_HARDLIGHT_LEGACY
			  GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
			  GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
			  GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
			  GIMP_LAYER_MODE_COLOR_ERASE_LEGACY
			  GIMP_LAYER_MODE_OVERLAY GIMP_LAYER_MODE_LCH_HUE
			  GIMP_LAYER_MODE_LCH_CHROMA
			  GIMP_LAYER_MODE_LCH_COLOR
			  GIMP_LAYER_MODE_LCH_LIGHTNESS
			  GIMP_LAYER_MODE_NORMAL GIMP_LAYER_MODE_BEHIND
			  GIMP_LAYER_MODE_MULTIPLY GIMP_LAYER_MODE_SCREEN
			  GIMP_LAYER_MODE_DIFFERENCE
			  GIMP_LAYER_MODE_ADDITION GIMP_LAYER_MODE_SUBTRACT
			  GIMP_LAYER_MODE_DARKEN_ONLY
			  GIMP_LAYER_MODE_LIGHTEN_ONLY
			  GIMP_LAYER_MODE_HSV_HUE
			  GIMP_LAYER_MODE_HSV_SATURATION
			  GIMP_LAYER_MODE_HSL_COLOR
			  GIMP_LAYER_MODE_HSV_VALUE GIMP_LAYER_MODE_DIVIDE
			  GIMP_LAYER_MODE_DODGE GIMP_LAYER_MODE_BURN
			  GIMP_LAYER_MODE_HARDLIGHT
			  GIMP_LAYER_MODE_SOFTLIGHT
			  GIMP_LAYER_MODE_GRAIN_EXTRACT
			  GIMP_LAYER_MODE_GRAIN_MERGE
			  GIMP_LAYER_MODE_VIVID_LIGHT
			  GIMP_LAYER_MODE_PIN_LIGHT
			  GIMP_LAYER_MODE_LINEAR_LIGHT
			  GIMP_LAYER_MODE_HARD_MIX GIMP_LAYER_MODE_EXCLUSION
			  GIMP_LAYER_MODE_LINEAR_BURN
			  GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
			  GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
			  GIMP_LAYER_MODE_LUMINANCE
			  GIMP_LAYER_MODE_COLOR_ERASE GIMP_LAYER_MODE_ERASE
			  GIMP_LAYER_MODE_MERGE GIMP_LAYER_MODE_SPLIT
			  GIMP_LAYER_MODE_PASS_THROUGH) ],
	  mapping => { GIMP_LAYER_MODE_NORMAL_LEGACY => '0',
		       GIMP_LAYER_MODE_DISSOLVE => '1',
		       GIMP_LAYER_MODE_BEHIND_LEGACY => '2',
		       GIMP_LAYER_MODE_MULTIPLY_LEGACY => '3',
		       GIMP_LAYER_MODE_SCREEN_LEGACY => '4',
		       GIMP_LAYER_MODE_OVERLAY_LEGACY => '5',
		       GIMP_LAYER_MODE_DIFFERENCE_LEGACY => '6',
		       GIMP_LAYER_MODE_ADDITION_LEGACY => '7',
		       GIMP_LAYER_MODE_SUBTRACT_LEGACY => '8',
		       GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY => '9',
		       GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY => '10',
		       GIMP_LAYER_MODE_HSV_HUE_LEGACY => '11',
		       GIMP_LAYER_MODE_HSV_SATURATION_LEGACY => '12',
		       GIMP_LAYER_MODE_HSL_COLOR_LEGACY => '13',
		       GIMP_LAYER_MODE_HSV_VALUE_LEGACY => '14',
		       GIMP_LAYER_MODE_DIVIDE_LEGACY => '15',
		       GIMP_LAYER_MODE_DODGE_LEGACY => '16',
		       GIMP_LAYER_MODE_BURN_LEGACY => '17',
		       GIMP_LAYER_MODE_HARDLIGHT_LEGACY => '18',
		       GIMP_LAYER_MODE_SOFTLIGHT_LEGACY => '19',
		       GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY => '20',
		       GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY => '21',
		       GIMP_LAYER_MODE_COLOR_ERASE_LEGACY => '22',
		       GIMP_LAYER_MODE_OVERLAY => '23',
		       GIMP_LAYER_MODE_LCH_HUE => '24',
		       GIMP_LAYER_MODE_LCH_CHROMA => '25',
		       GIMP_LAYER_MODE_LCH_COLOR => '26',
		       GIMP_LAYER_MODE_LCH_LIGHTNESS => '27',
		       GIMP_LAYER_MODE_NORMAL => '28',
		       GIMP_LAYER_MODE_BEHIND => '29',
		       GIMP_LAYER_MODE_MULTIPLY => '30',
		       GIMP_LAYER_MODE_SCREEN => '31',
		       GIMP_LAYER_MODE_DIFFERENCE => '32',
		       GIMP_LAYER_MODE_ADDITION => '33',
		       GIMP_LAYER_MODE_SUBTRACT => '34',
		       GIMP_LAYER_MODE_DARKEN_ONLY => '35',
		       GIMP_LAYER_MODE_LIGHTEN_ONLY => '36',
		       GIMP_LAYER_MODE_HSV_HUE => '37',
		       GIMP_LAYER_MODE_HSV_SATURATION => '38',
		       GIMP_LAYER_MODE_HSL_COLOR => '39',
		       GIMP_LAYER_MODE_HSV_VALUE => '40',
		       GIMP_LAYER_MODE_DIVIDE => '41',
		       GIMP_LAYER_MODE_DODGE => '42',
		       GIMP_LAYER_MODE_BURN => '43',
		       GIMP_LAYER_MODE_HARDLIGHT => '44',
		       GIMP_LAYER_MODE_SOFTLIGHT => '45',
		       GIMP_LAYER_MODE_GRAIN_EXTRACT => '46',
		       GIMP_LAYER_MODE_GRAIN_MERGE => '47',
		       GIMP_LAYER_MODE_VIVID_LIGHT => '48',
		       GIMP_LAYER_MODE_PIN_LIGHT => '49',
		       GIMP_LAYER_MODE_LINEAR_LIGHT => '50',
		       GIMP_LAYER_MODE_HARD_MIX => '51',
		       GIMP_LAYER_MODE_EXCLUSION => '52',
		       GIMP_LAYER_MODE_LINEAR_BURN => '53',
		       GIMP_LAYER_MODE_LUMA_DARKEN_ONLY => '54',
		       GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY => '55',
		       GIMP_LAYER_MODE_LUMINANCE => '56',
		       GIMP_LAYER_MODE_COLOR_ERASE => '57',
		       GIMP_LAYER_MODE_ERASE => '58',
		       GIMP_LAYER_MODE_MERGE => '59',
		       GIMP_LAYER_MODE_SPLIT => '60',
		       GIMP_LAYER_MODE_PASS_THROUGH => '61' }
	},
    GimpConvertDitherType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_CONVERT_DITHER_NONE GIMP_CONVERT_DITHER_FS
			  GIMP_CONVERT_DITHER_FS_LOWBLEED
			  GIMP_CONVERT_DITHER_FIXED) ],
	  mapping => { GIMP_CONVERT_DITHER_NONE => '0',
		       GIMP_CONVERT_DITHER_FS => '1',
		       GIMP_CONVERT_DITHER_FS_LOWBLEED => '2',
		       GIMP_CONVERT_DITHER_FIXED => '3' }
	},
    GimpHistogramChannel =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_HISTOGRAM_VALUE GIMP_HISTOGRAM_RED
			  GIMP_HISTOGRAM_GREEN GIMP_HISTOGRAM_BLUE
			  GIMP_HISTOGRAM_ALPHA GIMP_HISTOGRAM_LUMINANCE) ],
	  mapping => { GIMP_HISTOGRAM_VALUE => '0',
		       GIMP_HISTOGRAM_RED => '1',
		       GIMP_HISTOGRAM_GREEN => '2',
		       GIMP_HISTOGRAM_BLUE => '3',
		       GIMP_HISTOGRAM_ALPHA => '4',
		       GIMP_HISTOGRAM_LUMINANCE => '5' }
	},
    GimpBrushApplicationMode =>
	{ contig => 1,
	  header => 'paint/paint-enums.h',
	  symbols => [ qw(GIMP_BRUSH_HARD GIMP_BRUSH_SOFT) ],
	  mapping => { GIMP_BRUSH_HARD => '0',
		       GIMP_BRUSH_SOFT => '1' }
	}
);

foreach $e (values %enums) {
    $e->{info} = "";
    foreach (@{$e->{symbols}}) {
	$e->{info} .= "$_ ($e->{mapping}->{$_}), "
    }
    $e->{info} =~ s/, $//;
}

1;

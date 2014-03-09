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
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# autogenerated by enumgen.pl

package Gimp::CodeGen::enums;

%enums = (
    GimpAddMaskType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_ADD_WHITE_MASK GIMP_ADD_BLACK_MASK
			  GIMP_ADD_ALPHA_MASK GIMP_ADD_ALPHA_TRANSFER_MASK
			  GIMP_ADD_SELECTION_MASK GIMP_ADD_COPY_MASK
			  GIMP_ADD_CHANNEL_MASK) ],
	  mapping => { GIMP_ADD_WHITE_MASK => '0',
		       GIMP_ADD_BLACK_MASK => '1',
		       GIMP_ADD_ALPHA_MASK => '2',
		       GIMP_ADD_ALPHA_TRANSFER_MASK => '3',
		       GIMP_ADD_SELECTION_MASK => '4',
		       GIMP_ADD_COPY_MASK => '5',
		       GIMP_ADD_CHANNEL_MASK => '6' }
	},
    GimpBlendMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_FG_BG_RGB_MODE GIMP_FG_BG_HSV_MODE
			  GIMP_FG_TRANSPARENT_MODE GIMP_CUSTOM_MODE) ],
	  mapping => { GIMP_FG_BG_RGB_MODE => '0',
		       GIMP_FG_BG_HSV_MODE => '1',
		       GIMP_FG_TRANSPARENT_MODE => '2',
		       GIMP_CUSTOM_MODE => '3' }
	},
    GimpBucketFillMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_FG_BUCKET_FILL GIMP_BG_BUCKET_FILL
			  GIMP_PATTERN_BUCKET_FILL) ],
	  mapping => { GIMP_FG_BUCKET_FILL => '0',
		       GIMP_BG_BUCKET_FILL => '1',
		       GIMP_PATTERN_BUCKET_FILL => '2' }
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
	  symbols => [ qw(GIMP_RED_CHANNEL GIMP_GREEN_CHANNEL
			  GIMP_BLUE_CHANNEL GIMP_GRAY_CHANNEL
			  GIMP_INDEXED_CHANNEL GIMP_ALPHA_CHANNEL) ],
	  mapping => { GIMP_RED_CHANNEL => '0',
		       GIMP_GREEN_CHANNEL => '1',
		       GIMP_BLUE_CHANNEL => '2',
		       GIMP_GRAY_CHANNEL => '3',
		       GIMP_INDEXED_CHANNEL => '4',
		       GIMP_ALPHA_CHANNEL => '5' }
	},
    GimpCloneType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_IMAGE_CLONE GIMP_PATTERN_CLONE) ],
	  mapping => { GIMP_IMAGE_CLONE => '0',
		       GIMP_PATTERN_CLONE => '1' }
	},
    GimpDesaturateMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_DESATURATE_LIGHTNESS
			  GIMP_DESATURATE_LUMINOSITY GIMP_DESATURATE_AVERAGE) ],
	  mapping => { GIMP_DESATURATE_LIGHTNESS => '0',
		       GIMP_DESATURATE_LUMINOSITY => '1',
		       GIMP_DESATURATE_AVERAGE => '2' }
	},
    GimpDodgeBurnType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_DODGE GIMP_BURN) ],
	  mapping => { GIMP_DODGE => '0',
		       GIMP_BURN => '1' }
	},
    GimpForegroundExtractMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_FOREGROUND_EXTRACT_SIOX
			  GIMP_FOREGROUND_EXTRACT_MATTING) ],
	  mapping => { GIMP_FOREGROUND_EXTRACT_SIOX => '0',
		       GIMP_FOREGROUND_EXTRACT_MATTING => '1' }
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
    GimpIconType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_ICON_TYPE_STOCK_ID
			  GIMP_ICON_TYPE_INLINE_PIXBUF
			  GIMP_ICON_TYPE_IMAGE_FILE) ],
	  mapping => { GIMP_ICON_TYPE_STOCK_ID => '0',
		       GIMP_ICON_TYPE_INLINE_PIXBUF => '1',
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
    GimpPaintApplicationMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PAINT_CONSTANT GIMP_PAINT_INCREMENTAL) ],
	  mapping => { GIMP_PAINT_CONSTANT => '0',
		       GIMP_PAINT_INCREMENTAL => '1' }
	},
    GimpRepeatMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_REPEAT_NONE GIMP_REPEAT_SAWTOOTH
			  GIMP_REPEAT_TRIANGULAR) ],
	  mapping => { GIMP_REPEAT_NONE => '0',
		       GIMP_REPEAT_SAWTOOTH => '1',
		       GIMP_REPEAT_TRIANGULAR => '2' }
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
    GimpSizeType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PIXELS GIMP_POINTS) ],
	  mapping => { GIMP_PIXELS => '0',
		       GIMP_POINTS => '1' }
	},
    GimpTransferMode =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_SHADOWS GIMP_MIDTONES GIMP_HIGHLIGHTS) ],
	  mapping => { GIMP_SHADOWS => '0',
		       GIMP_MIDTONES => '1',
		       GIMP_HIGHLIGHTS => '2' }
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
    GimpPDBArgType =>
	{ contig => 0,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_PDB_INT32 GIMP_PDB_INT16 GIMP_PDB_INT8
			  GIMP_PDB_FLOAT GIMP_PDB_STRING GIMP_PDB_INT32ARRAY
			  GIMP_PDB_INT16ARRAY GIMP_PDB_INT8ARRAY
			  GIMP_PDB_FLOATARRAY GIMP_PDB_STRINGARRAY
			  GIMP_PDB_COLOR GIMP_PDB_ITEM GIMP_PDB_DISPLAY
			  GIMP_PDB_IMAGE GIMP_PDB_LAYER GIMP_PDB_CHANNEL
			  GIMP_PDB_DRAWABLE GIMP_PDB_SELECTION
			  GIMP_PDB_COLORARRAY GIMP_PDB_VECTORS
			  GIMP_PDB_PARASITE GIMP_PDB_STATUS GIMP_PDB_END
			  GIMP_PDB_PATH GIMP_PDB_BOUNDARY GIMP_PDB_REGION) ],
	  mapping => { GIMP_PDB_INT32 => '0',
		       GIMP_PDB_INT16 => '1',
		       GIMP_PDB_INT8 => '2',
		       GIMP_PDB_FLOAT => '3',
		       GIMP_PDB_STRING => '4',
		       GIMP_PDB_INT32ARRAY => '5',
		       GIMP_PDB_INT16ARRAY => '6',
		       GIMP_PDB_INT8ARRAY => '7',
		       GIMP_PDB_FLOATARRAY => '8',
		       GIMP_PDB_STRINGARRAY => '9',
		       GIMP_PDB_COLOR => '10',
		       GIMP_PDB_ITEM => '11',
		       GIMP_PDB_DISPLAY => '12',
		       GIMP_PDB_IMAGE => '13',
		       GIMP_PDB_LAYER => '14',
		       GIMP_PDB_CHANNEL => '15',
		       GIMP_PDB_DRAWABLE => '16',
		       GIMP_PDB_SELECTION => '17',
		       GIMP_PDB_COLORARRAY => '18',
		       GIMP_PDB_VECTORS => '19',
		       GIMP_PDB_PARASITE => '20',
		       GIMP_PDB_STATUS => '21',
		       GIMP_PDB_END => '22',
		       GIMP_PDB_PATH => 'GIMP_PDB_VECTORS',
		       GIMP_PDB_BOUNDARY => 'GIMP_PDB_COLORARRAY',
		       GIMP_PDB_REGION => 'GIMP_PDB_ITEM' }
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
	  symbols => [ qw(GIMP_INTERNAL GIMP_PLUGIN GIMP_EXTENSION
			  GIMP_TEMPORARY) ],
	  mapping => { GIMP_INTERNAL => '0',
		       GIMP_PLUGIN => '1',
		       GIMP_EXTENSION => '2',
		       GIMP_TEMPORARY => '3' }
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
    GimpMessageHandlerType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_MESSAGE_BOX GIMP_CONSOLE GIMP_ERROR_CONSOLE) ],
	  mapping => { GIMP_MESSAGE_BOX => '0',
		       GIMP_CONSOLE => '1',
		       GIMP_ERROR_CONSOLE => '2' }
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
    GimpTextDirection =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_TEXT_DIRECTION_LTR GIMP_TEXT_DIRECTION_RTL) ],
	  mapping => { GIMP_TEXT_DIRECTION_LTR => '0',
		       GIMP_TEXT_DIRECTION_RTL => '1' }
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
    GimpUserDirectory =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_USER_DIRECTORY_DESKTOP
			  GIMP_USER_DIRECTORY_DOCUMENTS
			  GIMP_USER_DIRECTORY_DOWNLOAD
			  GIMP_USER_DIRECTORY_MUSIC
			  GIMP_USER_DIRECTORY_PICTURES
			  GIMP_USER_DIRECTORY_PUBLIC_SHARE
			  GIMP_USER_DIRECTORY_TEMPLATES
			  GIMP_USER_DIRECTORY_VIDEOS) ],
	  mapping => { GIMP_USER_DIRECTORY_DESKTOP => '0',
		       GIMP_USER_DIRECTORY_DOCUMENTS => '1',
		       GIMP_USER_DIRECTORY_DOWNLOAD => '2',
		       GIMP_USER_DIRECTORY_MUSIC => '3',
		       GIMP_USER_DIRECTORY_PICTURES => '4',
		       GIMP_USER_DIRECTORY_PUBLIC_SHARE => '5',
		       GIMP_USER_DIRECTORY_TEMPLATES => '6',
		       GIMP_USER_DIRECTORY_VIDEOS => '7' }
	},
    GimpVectorsStrokeType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbaseenums.h',
	  symbols => [ qw(GIMP_VECTORS_STROKE_TYPE_BEZIER) ],
	  mapping => { GIMP_VECTORS_STROKE_TYPE_BEZIER => '0' }
	},
    GimpComponentType =>
	{ contig => 0,
	  header => 'core/core-enums.h',
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
    GimpConvertDitherType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_NO_DITHER GIMP_FS_DITHER
			  GIMP_FSLOWBLEED_DITHER GIMP_FIXED_DITHER) ],
	  mapping => { GIMP_NO_DITHER => '0',
		       GIMP_FS_DITHER => '1',
		       GIMP_FSLOWBLEED_DITHER => '2',
		       GIMP_FIXED_DITHER => '3' }
	},
    GimpConvertPaletteType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_MAKE_PALETTE GIMP_REUSE_PALETTE
			  GIMP_WEB_PALETTE GIMP_MONO_PALETTE
			  GIMP_CUSTOM_PALETTE) ],
	  mapping => { GIMP_MAKE_PALETTE => '0',
		       GIMP_REUSE_PALETTE => '1',
		       GIMP_WEB_PALETTE => '2',
		       GIMP_MONO_PALETTE => '3',
		       GIMP_CUSTOM_PALETTE => '4' }
	},
    GimpConvolutionType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_NORMAL_CONVOL GIMP_ABSOLUTE_CONVOL
			  GIMP_NEGATIVE_CONVOL) ],
	  mapping => { GIMP_NORMAL_CONVOL => '0',
		       GIMP_ABSOLUTE_CONVOL => '1',
		       GIMP_NEGATIVE_CONVOL => '2' }
	},
    GimpHistogramChannel =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_HISTOGRAM_VALUE GIMP_HISTOGRAM_RED
			  GIMP_HISTOGRAM_GREEN GIMP_HISTOGRAM_BLUE
			  GIMP_HISTOGRAM_ALPHA) ],
	  mapping => { GIMP_HISTOGRAM_VALUE => '0',
		       GIMP_HISTOGRAM_RED => '1',
		       GIMP_HISTOGRAM_GREEN => '2',
		       GIMP_HISTOGRAM_BLUE => '3',
		       GIMP_HISTOGRAM_ALPHA => '4' }
	},
    GimpHueRange =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_ALL_HUES GIMP_RED_HUES GIMP_YELLOW_HUES
			  GIMP_GREEN_HUES GIMP_CYAN_HUES GIMP_BLUE_HUES
			  GIMP_MAGENTA_HUES) ],
	  mapping => { GIMP_ALL_HUES => '0',
		       GIMP_RED_HUES => '1',
		       GIMP_YELLOW_HUES => '2',
		       GIMP_GREEN_HUES => '3',
		       GIMP_CYAN_HUES => '4',
		       GIMP_BLUE_HUES => '5',
		       GIMP_MAGENTA_HUES => '6' }
	},
    GimpLayerModeEffects =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_NORMAL_MODE GIMP_DISSOLVE_MODE
			  GIMP_BEHIND_MODE GIMP_MULTIPLY_MODE
			  GIMP_SCREEN_MODE GIMP_OVERLAY_MODE
			  GIMP_DIFFERENCE_MODE GIMP_ADDITION_MODE
			  GIMP_SUBTRACT_MODE GIMP_DARKEN_ONLY_MODE
			  GIMP_LIGHTEN_ONLY_MODE GIMP_HUE_MODE
			  GIMP_SATURATION_MODE GIMP_COLOR_MODE
			  GIMP_VALUE_MODE GIMP_DIVIDE_MODE GIMP_DODGE_MODE
			  GIMP_BURN_MODE GIMP_HARDLIGHT_MODE
			  GIMP_SOFTLIGHT_MODE GIMP_GRAIN_EXTRACT_MODE
			  GIMP_GRAIN_MERGE_MODE GIMP_COLOR_ERASE_MODE) ],
	  mapping => { GIMP_NORMAL_MODE => '0',
		       GIMP_DISSOLVE_MODE => '1',
		       GIMP_BEHIND_MODE => '2',
		       GIMP_MULTIPLY_MODE => '3',
		       GIMP_SCREEN_MODE => '4',
		       GIMP_OVERLAY_MODE => '5',
		       GIMP_DIFFERENCE_MODE => '6',
		       GIMP_ADDITION_MODE => '7',
		       GIMP_SUBTRACT_MODE => '8',
		       GIMP_DARKEN_ONLY_MODE => '9',
		       GIMP_LIGHTEN_ONLY_MODE => '10',
		       GIMP_HUE_MODE => '11',
		       GIMP_SATURATION_MODE => '12',
		       GIMP_COLOR_MODE => '13',
		       GIMP_VALUE_MODE => '14',
		       GIMP_DIVIDE_MODE => '15',
		       GIMP_DODGE_MODE => '16',
		       GIMP_BURN_MODE => '17',
		       GIMP_HARDLIGHT_MODE => '18',
		       GIMP_SOFTLIGHT_MODE => '19',
		       GIMP_GRAIN_EXTRACT_MODE => '20',
		       GIMP_GRAIN_MERGE_MODE => '21',
		       GIMP_COLOR_ERASE_MODE => '22' }
	},
    GimpFillType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_FOREGROUND_FILL GIMP_BACKGROUND_FILL
			  GIMP_WHITE_FILL GIMP_TRANSPARENT_FILL
			  GIMP_PATTERN_FILL) ],
	  mapping => { GIMP_FOREGROUND_FILL => '0',
		       GIMP_BACKGROUND_FILL => '1',
		       GIMP_WHITE_FILL => '2',
		       GIMP_TRANSPARENT_FILL => '3',
		       GIMP_PATTERN_FILL => '4' }
	},
    GimpBrushGeneratedShape =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_BRUSH_GENERATED_CIRCLE
			  GIMP_BRUSH_GENERATED_SQUARE
			  GIMP_BRUSH_GENERATED_DIAMOND) ],
	  mapping => { GIMP_BRUSH_GENERATED_CIRCLE => '0',
		       GIMP_BRUSH_GENERATED_SQUARE => '1',
		       GIMP_BRUSH_GENERATED_DIAMOND => '2' }
	},
    GimpOrientationType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_ORIENTATION_HORIZONTAL
			  GIMP_ORIENTATION_VERTICAL GIMP_ORIENTATION_UNKNOWN) ],
	  mapping => { GIMP_ORIENTATION_HORIZONTAL => '0',
		       GIMP_ORIENTATION_VERTICAL => '1',
		       GIMP_ORIENTATION_UNKNOWN => '2' }
	},
    GimpPrecision =>
	{ contig => 0,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_PRECISION_U8_LINEAR GIMP_PRECISION_U8_GAMMA
			  GIMP_PRECISION_U16_LINEAR GIMP_PRECISION_U16_GAMMA
			  GIMP_PRECISION_U32_LINEAR GIMP_PRECISION_U32_GAMMA
			  GIMP_PRECISION_HALF_LINEAR
			  GIMP_PRECISION_HALF_GAMMA
			  GIMP_PRECISION_FLOAT_LINEAR
			  GIMP_PRECISION_FLOAT_GAMMA
			  GIMP_PRECISION_DOUBLE_LINEAR
			  GIMP_PRECISION_DOUBLE_GAMMA) ],
	  mapping => { GIMP_PRECISION_U8_LINEAR => '100',
		       GIMP_PRECISION_U8_GAMMA => '150',
		       GIMP_PRECISION_U16_LINEAR => '200',
		       GIMP_PRECISION_U16_GAMMA => '250',
		       GIMP_PRECISION_U32_LINEAR => '300',
		       GIMP_PRECISION_U32_GAMMA => '350',
		       GIMP_PRECISION_HALF_LINEAR => '500',
		       GIMP_PRECISION_HALF_GAMMA => '550',
		       GIMP_PRECISION_FLOAT_LINEAR => '600',
		       GIMP_PRECISION_FLOAT_GAMMA => '650',
		       GIMP_PRECISION_DOUBLE_LINEAR => '700',
		       GIMP_PRECISION_DOUBLE_GAMMA => '750' }
	},
    GimpRotationType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_ROTATE_90 GIMP_ROTATE_180 GIMP_ROTATE_270) ],
	  mapping => { GIMP_ROTATE_90 => '0',
		       GIMP_ROTATE_180 => '1',
		       GIMP_ROTATE_270 => '2' }
	},
    GimpOffsetType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_OFFSET_BACKGROUND GIMP_OFFSET_TRANSPARENT) ],
	  mapping => { GIMP_OFFSET_BACKGROUND => '0',
		       GIMP_OFFSET_TRANSPARENT => '1' }
	},
    GimpGradientSegmentType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_GRADIENT_SEGMENT_LINEAR
			  GIMP_GRADIENT_SEGMENT_CURVED
			  GIMP_GRADIENT_SEGMENT_SINE
			  GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
			  GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING) ],
	  mapping => { GIMP_GRADIENT_SEGMENT_LINEAR => '0',
		       GIMP_GRADIENT_SEGMENT_CURVED => '1',
		       GIMP_GRADIENT_SEGMENT_SINE => '2',
		       GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING => '3',
		       GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING => '4' }
	},
    GimpGradientSegmentColor =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_GRADIENT_SEGMENT_RGB
			  GIMP_GRADIENT_SEGMENT_HSV_CCW
			  GIMP_GRADIENT_SEGMENT_HSV_CW) ],
	  mapping => { GIMP_GRADIENT_SEGMENT_RGB => '0',
		       GIMP_GRADIENT_SEGMENT_HSV_CCW => '1',
		       GIMP_GRADIENT_SEGMENT_HSV_CW => '2' }
	},
    GimpMaskApplyMode =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_MASK_APPLY GIMP_MASK_DISCARD) ],
	  mapping => { GIMP_MASK_APPLY => '0',
		       GIMP_MASK_DISCARD => '1' }
	},
    GimpMergeType =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_EXPAND_AS_NECESSARY GIMP_CLIP_TO_IMAGE
			  GIMP_CLIP_TO_BOTTOM_LAYER GIMP_FLATTEN_IMAGE) ],
	  mapping => { GIMP_EXPAND_AS_NECESSARY => '0',
		       GIMP_CLIP_TO_IMAGE => '1',
		       GIMP_CLIP_TO_BOTTOM_LAYER => '2',
		       GIMP_FLATTEN_IMAGE => '3' }
	},
    GimpSelectCriterion =>
	{ contig => 1,
	  header => 'core/core-enums.h',
	  symbols => [ qw(GIMP_SELECT_CRITERION_COMPOSITE
			  GIMP_SELECT_CRITERION_R GIMP_SELECT_CRITERION_G
			  GIMP_SELECT_CRITERION_B GIMP_SELECT_CRITERION_H
			  GIMP_SELECT_CRITERION_S GIMP_SELECT_CRITERION_V) ],
	  mapping => { GIMP_SELECT_CRITERION_COMPOSITE => '0',
		       GIMP_SELECT_CRITERION_R => '1',
		       GIMP_SELECT_CRITERION_G => '2',
		       GIMP_SELECT_CRITERION_B => '3',
		       GIMP_SELECT_CRITERION_H => '4',
		       GIMP_SELECT_CRITERION_S => '5',
		       GIMP_SELECT_CRITERION_V => '6' }
	},
    GimpBrushApplicationMode =>
	{ contig => 1,
	  header => 'paint/paint-enums.h',
	  symbols => [ qw(GIMP_BRUSH_HARD GIMP_BRUSH_SOFT) ],
	  mapping => { GIMP_BRUSH_HARD => '0',
		       GIMP_BRUSH_SOFT => '1' }
	},
    GimpConvolveType =>
	{ contig => 1,
	  header => 'paint/paint-enums.h',
	  symbols => [ qw(GIMP_BLUR_CONVOLVE GIMP_SHARPEN_CONVOLVE) ],
	  mapping => { GIMP_BLUR_CONVOLVE => '0',
		       GIMP_SHARPEN_CONVOLVE => '1' }
	},
    GimpInkBlobType =>
	{ contig => 1,
	  header => 'paint/paint-enums.h',
	  symbols => [ qw(GIMP_INK_BLOB_TYPE_CIRCLE
			  GIMP_INK_BLOB_TYPE_SQUARE
			  GIMP_INK_BLOB_TYPE_DIAMOND) ],
	  mapping => { GIMP_INK_BLOB_TYPE_CIRCLE => '0',
		       GIMP_INK_BLOB_TYPE_SQUARE => '1',
		       GIMP_INK_BLOB_TYPE_DIAMOND => '2' }
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

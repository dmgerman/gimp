# The GIMP -- an image manipulation program
# Copyright (C) 1999-2000 Manish Singh <yosh@gimp.org>

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUTFILE ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# autogenerated by enumgen.pl

package Gimp::CodeGen::enums;

%enums = (
    GimpUnit =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbasetypes.h',
	  symbols => [ qw(GIMP_UNIT_PIXEL GIMP_UNIT_INCH GIMP_UNIT_MM
			  GIMP_UNIT_POINT GIMP_UNIT_PICA GIMP_UNIT_END) ],
	  mapping => { GIMP_UNIT_PIXEL => '0',
		       GIMP_UNIT_INCH => '1',
		       GIMP_UNIT_MM => '2',
		       GIMP_UNIT_POINT => '3',
		       GIMP_UNIT_PICA => '4',
		       GIMP_UNIT_END => '5' },
	  nicks   => { GIMP_UNIT_PIXEL => 'UNIT_PIXEL',
		       GIMP_UNIT_INCH => 'UNIT_INCH',
		       GIMP_UNIT_MM => 'UNIT_MM',
		       GIMP_UNIT_POINT => 'UNIT_POINT',
		       GIMP_UNIT_PICA => 'UNIT_PICA',
		       GIMP_UNIT_END => 'UNIT_END' }
	},
    GimpPDBArgType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbasetypes.h',
	  symbols => [ qw(GIMP_PDB_INT32 GIMP_PDB_INT16 GIMP_PDB_INT8
			  GIMP_PDB_FLOAT GIMP_PDB_STRING GIMP_PDB_INT32ARRAY
			  GIMP_PDB_INT16ARRAY GIMP_PDB_INT8ARRAY
			  GIMP_PDB_FLOATARRAY GIMP_PDB_STRINGARRAY
			  GIMP_PDB_COLOR GIMP_PDB_REGION GIMP_PDB_DISPLAY
			  GIMP_PDB_IMAGE GIMP_PDB_LAYER GIMP_PDB_CHANNEL
			  GIMP_PDB_DRAWABLE GIMP_PDB_SELECTION
			  GIMP_PDB_BOUNDARY GIMP_PDB_PATH GIMP_PDB_PARASITE
			  GIMP_PDB_STATUS GIMP_PDB_END) ],
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
		       GIMP_PDB_REGION => '11',
		       GIMP_PDB_DISPLAY => '12',
		       GIMP_PDB_IMAGE => '13',
		       GIMP_PDB_LAYER => '14',
		       GIMP_PDB_CHANNEL => '15',
		       GIMP_PDB_DRAWABLE => '16',
		       GIMP_PDB_SELECTION => '17',
		       GIMP_PDB_BOUNDARY => '18',
		       GIMP_PDB_PATH => '19',
		       GIMP_PDB_PARASITE => '20',
		       GIMP_PDB_STATUS => '21',
		       GIMP_PDB_END => '22' },
	  nicks   => { GIMP_PDB_INT32 => 'PDB_INT32',
		       GIMP_PDB_INT16 => 'PDB_INT16',
		       GIMP_PDB_INT8 => 'PDB_INT8',
		       GIMP_PDB_FLOAT => 'PDB_FLOAT',
		       GIMP_PDB_STRING => 'PDB_STRING',
		       GIMP_PDB_INT32ARRAY => 'PDB_INT32ARRAY',
		       GIMP_PDB_INT16ARRAY => 'PDB_INT16ARRAY',
		       GIMP_PDB_INT8ARRAY => 'PDB_INT8ARRAY',
		       GIMP_PDB_FLOATARRAY => 'PDB_FLOATARRAY',
		       GIMP_PDB_STRINGARRAY => 'PDB_STRINGARRAY',
		       GIMP_PDB_COLOR => 'PDB_COLOR',
		       GIMP_PDB_REGION => 'PDB_REGION',
		       GIMP_PDB_DISPLAY => 'PDB_DISPLAY',
		       GIMP_PDB_IMAGE => 'PDB_IMAGE',
		       GIMP_PDB_LAYER => 'PDB_LAYER',
		       GIMP_PDB_CHANNEL => 'PDB_CHANNEL',
		       GIMP_PDB_DRAWABLE => 'PDB_DRAWABLE',
		       GIMP_PDB_SELECTION => 'PDB_SELECTION',
		       GIMP_PDB_BOUNDARY => 'PDB_BOUNDARY',
		       GIMP_PDB_PATH => 'PDB_PATH',
		       GIMP_PDB_PARASITE => 'PDB_PARASITE',
		       GIMP_PDB_STATUS => 'PDB_STATUS',
		       GIMP_PDB_END => 'PDB_END' }
	},
    GimpPDBProcType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbasetypes.h',
	  symbols => [ qw(GIMP_INTERNAL GIMP_PLUGIN GIMP_EXTENSION
			  GIMP_TEMPORARY) ],
	  mapping => { GIMP_INTERNAL => '0',
		       GIMP_PLUGIN => '1',
		       GIMP_EXTENSION => '2',
		       GIMP_TEMPORARY => '3' },
	  nicks   => { GIMP_INTERNAL => 'INTERNAL',
		       GIMP_PLUGIN => 'PLUGIN',
		       GIMP_EXTENSION => 'EXTENSION',
		       GIMP_TEMPORARY => 'TEMPORARY' }
	},
    GimpPDBStatusType =>
	{ contig => 1,
	  header => 'libgimpbase/gimpbasetypes.h',
	  symbols => [ qw(GIMP_PDB_EXECUTION_ERROR GIMP_PDB_CALLING_ERROR
			  GIMP_PDB_PASS_THROUGH GIMP_PDB_SUCCESS
			  GIMP_PDB_CANCEL) ],
	  mapping => { GIMP_PDB_EXECUTION_ERROR => '0',
		       GIMP_PDB_CALLING_ERROR => '1',
		       GIMP_PDB_PASS_THROUGH => '2',
		       GIMP_PDB_SUCCESS => '3',
		       GIMP_PDB_CANCEL => '4' },
	  nicks   => { GIMP_PDB_EXECUTION_ERROR => 'PDB_EXECUTION_ERROR',
		       GIMP_PDB_CALLING_ERROR => 'PDB_CALLING_ERROR',
		       GIMP_PDB_PASS_THROUGH => 'PDB_PASS_THROUGH',
		       GIMP_PDB_SUCCESS => 'PDB_SUCCESS',
		       GIMP_PDB_CANCEL => 'PDB_CANCEL' }
	},
    BrushApplicationMode =>
	{ contig => 1,
	  header => 'appenums.h',
	  symbols => [ qw(HARD SOFT PRESSURE) ],
	  mapping => { HARD => '0',
		       SOFT => '1',
		       PRESSURE => '2' }
	},
    PaintApplicationMode =>
	{ contig => 1,
	  header => 'appenums.h',
	  symbols => [ qw(CONSTANT INCREMENTAL) ],
	  mapping => { CONSTANT => '0',
		       INCREMENTAL => '1' },
	  nicks   => { CONSTANT => 'CONTINUOUS' }
	},
    AddMaskType =>
	{ contig => 1,
	  header => 'appenums.h',
	  symbols => [ qw(ADD_WHITE_MASK ADD_BLACK_MASK ADD_ALPHA_MASK
			  ADD_SELECTION_MASK ADD_INV_SELECTION_MASK) ],
	  mapping => { ADD_WHITE_MASK => '0',
		       ADD_BLACK_MASK => '1',
		       ADD_ALPHA_MASK => '2',
		       ADD_SELECTION_MASK => '3',
		       ADD_INV_SELECTION_MASK => '4' },
	  nicks   => { ADD_WHITE_MASK => 'WHITE_MASK',
		       ADD_BLACK_MASK => 'BLACK_MASK',
		       ADD_ALPHA_MASK => 'ALPHA_MASK',
		       ADD_SELECTION_MASK => 'SELECTION_MASK',
		       ADD_INV_SELECTION_MASK => 'INV_SELECTION_MASK' }
	},
    GradientPaintMode =>
	{ contig => 1,
	  header => 'appenums.h',
	  symbols => [ qw(ONCE_FORWARD ONCE_BACKWARDS LOOP_SAWTOOTH
			  LOOP_TRIANGLE ONCE_END_COLOR) ],
	  mapping => { ONCE_FORWARD => '0',
		       ONCE_BACKWARDS => '1',
		       LOOP_SAWTOOTH => '2',
		       LOOP_TRIANGLE => '3',
		       ONCE_END_COLOR => '4' }
	},
    OrientationType =>
	{ contig => 1,
	  header => 'appenums.h',
	  symbols => [ qw(HORIZONTAL VERTICAL UNKNOWN) ],
	  mapping => { HORIZONTAL => '0',
		       VERTICAL => '1',
		       UNKNOWN => '2' }
	},
    ChannelOps =>
	{ contig => 1,
	  header => 'appenums.h',
	  symbols => [ qw(CHANNEL_OP_ADD CHANNEL_OP_SUB CHANNEL_OP_REPLACE
			  CHANNEL_OP_INTERSECT) ],
	  mapping => { CHANNEL_OP_ADD => '0',
		       CHANNEL_OP_SUB => '1',
		       CHANNEL_OP_REPLACE => '2',
		       CHANNEL_OP_INTERSECT => '3' },
	  nicks   => { CHANNEL_OP_ADD => 'ADD',
		       CHANNEL_OP_SUB => 'SUB',
		       CHANNEL_OP_REPLACE => 'REPLACE',
		       CHANNEL_OP_INTERSECT => 'INTERSECT' }
	},
    RunModeType =>
	{ contig => 1,
	  header => 'appenums.h',
	  symbols => [ qw(RUN_INTERACTIVE RUN_NONINTERACTIVE
			  RUN_WITH_LAST_VALS) ],
	  mapping => { RUN_INTERACTIVE => '0',
		       RUN_NONINTERACTIVE => '1',
		       RUN_WITH_LAST_VALS => '2' }
	},
    MessageHandlerType =>
	{ contig => 1,
	  header => 'appenv.h',
	  symbols => [ qw(MESSAGE_BOX CONSOLE ERROR_CONSOLE) ],
	  mapping => { MESSAGE_BOX => '0',
		       CONSOLE => '1',
		       ERROR_CONSOLE => '2' }
	},
    StackTraceMode =>
	{ contig => 1,
	  header => 'errors.h',
	  symbols => [ qw(STACK_TRACE_NEVER STACK_TRACE_QUERY
			  STACK_TRACE_ALWAYS) ],
	  mapping => { STACK_TRACE_NEVER => '0',
		       STACK_TRACE_QUERY => '1',
		       STACK_TRACE_ALWAYS => '2' }
	},
    LayerModeEffects =>
	{ contig => 1,
	  header => 'base/base-types.h',
	  symbols => [ qw(NORMAL_MODE DISSOLVE_MODE BEHIND_MODE
			  MULTIPLY_MODE SCREEN_MODE OVERLAY_MODE
			  DIFFERENCE_MODE ADDITION_MODE SUBTRACT_MODE
			  DARKEN_ONLY_MODE LIGHTEN_ONLY_MODE HUE_MODE
			  SATURATION_MODE COLOR_MODE VALUE_MODE DIVIDE_MODE
			  DODGE_MODE BURN_MODE HARDLIGHT_MODE) ],
	  mapping => { NORMAL_MODE => '0',
		       DISSOLVE_MODE => '1',
		       BEHIND_MODE => '2',
		       MULTIPLY_MODE => '3',
		       SCREEN_MODE => '4',
		       OVERLAY_MODE => '5',
		       DIFFERENCE_MODE => '6',
		       ADDITION_MODE => '7',
		       SUBTRACT_MODE => '8',
		       DARKEN_ONLY_MODE => '9',
		       LIGHTEN_ONLY_MODE => '10',
		       HUE_MODE => '11',
		       SATURATION_MODE => '12',
		       COLOR_MODE => '13',
		       VALUE_MODE => '14',
		       DIVIDE_MODE => '15',
		       DODGE_MODE => '16',
		       BURN_MODE => '17',
		       HARDLIGHT_MODE => '18' }
	},
    ConvolutionType =>
	{ contig => 1,
	  header => 'base/base-types.h',
	  symbols => [ qw(NORMAL_CONVOL ABSOLUTE_CONVOL NEGATIVE_CONVOL) ],
	  mapping => { NORMAL_CONVOL => '0',
		       ABSOLUTE_CONVOL => '1',
		       NEGATIVE_CONVOL => '2' }
	},
    InterpolationType =>
	{ contig => 1,
	  header => 'base/base-types.h',
	  symbols => [ qw(LINEAR_INTERPOLATION CUBIC_INTERPOLATION
			  NEAREST_NEIGHBOR_INTERPOLATION) ],
	  mapping => { LINEAR_INTERPOLATION => '0',
		       CUBIC_INTERPOLATION => '1',
		       NEAREST_NEIGHBOR_INTERPOLATION => '2' }
	},
    ChannelLutType =>
	{ contig => 1,
	  header => 'base/base-types.h',
	  symbols => [ qw(VALUE_LUT RED_LUT GREEN_LUT BLUE_LUT ALPHA_LUT) ],
	  mapping => { VALUE_LUT => '0',
		       RED_LUT => '1',
		       GREEN_LUT => '2',
		       BLUE_LUT => '3',
		       ALPHA_LUT => '4' }
	},
    GimpImageBaseType =>
	{ contig => 1,
	  header => 'core/core-types.h',
	  symbols => [ qw(RGB GRAY INDEXED) ],
	  mapping => { RGB => '0',
		       GRAY => '1',
		       INDEXED => '2' }
	},
    GimpImageType =>
	{ contig => 1,
	  header => 'core/core-types.h',
	  symbols => [ qw(RGB_GIMAGE RGBA_GIMAGE GRAY_GIMAGE GRAYA_GIMAGE
			  INDEXED_GIMAGE INDEXEDA_GIMAGE) ],
	  mapping => { RGB_GIMAGE => '0',
		       RGBA_GIMAGE => '1',
		       GRAY_GIMAGE => '2',
		       GRAYA_GIMAGE => '3',
		       INDEXED_GIMAGE => '4',
		       INDEXEDA_GIMAGE => '5' },
	  nicks   => { RGB_GIMAGE => 'RGB_IMAGE',
		       RGBA_GIMAGE => 'RGBA_IMAGE',
		       GRAY_GIMAGE => 'GRAY_IMAGE',
		       GRAYA_GIMAGE => 'GRAYA_IMAGE',
		       INDEXED_GIMAGE => 'INDEXED_IMAGE',
		       INDEXEDA_GIMAGE => 'INDEXEDA_IMAGE' }
	},
    ChannelType =>
	{ contig => 1,
	  header => 'core/core-types.h',
	  symbols => [ qw(RED_CHANNEL GREEN_CHANNEL BLUE_CHANNEL
			  GRAY_CHANNEL INDEXED_CHANNEL ALPHA_CHANNEL) ],
	  mapping => { RED_CHANNEL => '0',
		       GREEN_CHANNEL => '1',
		       BLUE_CHANNEL => '2',
		       GRAY_CHANNEL => '3',
		       INDEXED_CHANNEL => '4',
		       ALPHA_CHANNEL => '5' }
	},
    MaskApplyMode =>
	{ contig => 1,
	  header => 'core/core-types.h',
	  symbols => [ qw(APPLY DISCARD) ],
	  mapping => { APPLY => '0',
		       DISCARD => '1' }
	},
    GimpFillType =>
	{ contig => 1,
	  header => 'core/core-types.h',
	  symbols => [ qw(FOREGROUND_FILL BACKGROUND_FILL WHITE_FILL
			  TRANSPARENT_FILL NO_FILL) ],
	  mapping => { FOREGROUND_FILL => '0',
		       BACKGROUND_FILL => '1',
		       WHITE_FILL => '2',
		       TRANSPARENT_FILL => '3',
		       NO_FILL => '4' },
	  nicks   => { FOREGROUND_FILL => 'FG_IMAGE_FILL',
		       BACKGROUND_FILL => 'BG_IMAGE_FILL',
		       WHITE_FILL => 'WHITE_IMAGE_FILL',
		       TRANSPARENT_FILL => 'TRANS_IMAGE_FILL',
		       NO_FILL => 'NO_IMAGE_FILL' }
	},
    GimpOffsetType =>
	{ contig => 1,
	  header => 'core/gimpdrawable-offset.h',
	  symbols => [ qw(OFFSET_BACKGROUND OFFSET_TRANSPARENT) ],
	  mapping => { OFFSET_BACKGROUND => '0',
		       OFFSET_TRANSPARENT => '1' }
	},
    MergeType =>
	{ contig => 1,
	  header => 'core/gimpimage.h',
	  symbols => [ qw(EXPAND_AS_NECESSARY CLIP_TO_IMAGE
			  CLIP_TO_BOTTOM_LAYER FLATTEN_IMAGE) ],
	  mapping => { EXPAND_AS_NECESSARY => '0',
		       CLIP_TO_IMAGE => '1',
		       CLIP_TO_BOTTOM_LAYER => '2',
		       FLATTEN_IMAGE => '3' }
	},
    ConvertPaletteType =>
	{ contig => 1,
	  header => 'core/gimpimage-convert.h',
	  symbols => [ qw(MAKE_PALETTE REUSE_PALETTE WEB_PALETTE
			  MONO_PALETTE CUSTOM_PALETTE) ],
	  mapping => { MAKE_PALETTE => '0',
		       REUSE_PALETTE => '1',
		       WEB_PALETTE => '2',
		       MONO_PALETTE => '3',
		       CUSTOM_PALETTE => '4' }
	},
    ConvertDitherType =>
	{ contig => 1,
	  header => 'core/gimpimage-convert.h',
	  symbols => [ qw(NO_DITHER FS_DITHER FSLOWBLEED_DITHER FIXED_DITHER
			  NODESTRUCT_DITHER) ],
	  mapping => { NO_DITHER => '0',
		       FS_DITHER => '1',
		       FSLOWBLEED_DITHER => '2',
		       FIXED_DITHER => '3',
		       NODESTRUCT_DITHER => '4' }
	},
    GradientType =>
	{ contig => 1,
	  header => 'tools/gimpblendtool.h',
	  symbols => [ qw(LINEAR BILINEAR RADIAL SQUARE CONICAL_SYMMETRIC
			  CONICAL_ASYMMETRIC SHAPEBURST_ANGULAR
			  SHAPEBURST_SPHERICAL SHAPEBURST_DIMPLED
			  SPIRAL_CLOCKWISE SPIRAL_ANTICLOCKWISE) ],
	  mapping => { LINEAR => '0',
		       BILINEAR => '1',
		       RADIAL => '2',
		       SQUARE => '3',
		       CONICAL_SYMMETRIC => '4',
		       CONICAL_ASYMMETRIC => '5',
		       SHAPEBURST_ANGULAR => '6',
		       SHAPEBURST_SPHERICAL => '7',
		       SHAPEBURST_DIMPLED => '8',
		       SPIRAL_CLOCKWISE => '9',
		       SPIRAL_ANTICLOCKWISE => '10' }
	},
    BlendMode =>
	{ contig => 1,
	  header => 'tools/gimpblendtool.h',
	  symbols => [ qw(FG_BG_RGB_MODE FG_BG_HSV_MODE FG_TRANS_MODE
			  CUSTOM_MODE) ],
	  mapping => { FG_BG_RGB_MODE => '0',
		       FG_BG_HSV_MODE => '1',
		       FG_TRANS_MODE => '2',
		       CUSTOM_MODE => '3' },
	  nicks   => { FG_BG_RGB_MODE => 'FG_BG_RGB',
		       FG_BG_HSV_MODE => 'FG_BG_HSV',
		       FG_TRANS_MODE => 'FG_TRANS',
		       CUSTOM_MODE => 'CUSTOM' }
	},
    RepeatMode =>
	{ contig => 1,
	  header => 'tools/gimpblendtool.h',
	  symbols => [ qw(REPEAT_NONE REPEAT_SAWTOOTH REPEAT_TRIANGULAR) ],
	  mapping => { REPEAT_NONE => '0',
		       REPEAT_SAWTOOTH => '1',
		       REPEAT_TRIANGULAR => '2' }
	},
    BucketFillMode =>
	{ contig => 1,
	  header => 'tools/gimpbucketfilltool.h',
	  symbols => [ qw(FG_BUCKET_FILL BG_BUCKET_FILL PATTERN_BUCKET_FILL) ],
	  mapping => { FG_BUCKET_FILL => '0',
		       BG_BUCKET_FILL => '1',
		       PATTERN_BUCKET_FILL => '2' }
	},
    CloneType =>
	{ contig => 1,
	  header => 'tools/gimpclonetool.h',
	  symbols => [ qw(IMAGE_CLONE PATTERN_CLONE) ],
	  mapping => { IMAGE_CLONE => '0',
		       PATTERN_CLONE => '1' }
	},
    TransferMode =>
	{ contig => 1,
	  header => 'tools/gimpcolorbalancetool.h',
	  symbols => [ qw(SHADOWS MIDTONES HIGHLIGHTS) ],
	  mapping => { SHADOWS => '0',
		       MIDTONES => '1',
		       HIGHLIGHTS => '2' }
	},
    ConvolveType =>
	{ contig => 1,
	  header => 'tools/gimpconvolvetool.h',
	  symbols => [ qw(BLUR_CONVOLVE SHARPEN_CONVOLVE CUSTOM_CONVOLVE) ],
	  mapping => { BLUR_CONVOLVE => '0',
		       SHARPEN_CONVOLVE => '1',
		       CUSTOM_CONVOLVE => '2' }
	},
    DodgeBurnType =>
	{ contig => 1,
	  header => 'tools/gimpdodgeburntool.h',
	  symbols => [ qw(DODGE BURN) ],
	  mapping => { DODGE => '0',
		       BURN => '1' }
	},
    DodgeBurnMode =>
	{ contig => 1,
	  header => 'tools/gimpdodgeburntool.h',
	  symbols => [ qw(DODGEBURN_HIGHLIGHTS DODGEBURN_MIDTONES
			  DODGEBURN_SHADOWS) ],
	  mapping => { DODGEBURN_HIGHLIGHTS => '0',
		       DODGEBURN_MIDTONES => '1',
		       DODGEBURN_SHADOWS => '2' }
	},
    HueRange =>
	{ contig => 1,
	  header => 'tools/gimphuesaturationtool.h',
	  symbols => [ qw(ALL_HUES RED_HUES YELLOW_HUES GREEN_HUES CYAN_HUES
			  BLUE_HUES MAGENTA_HUES) ],
	  mapping => { ALL_HUES => '0',
		       RED_HUES => '1',
		       YELLOW_HUES => '2',
		       GREEN_HUES => '3',
		       CYAN_HUES => '4',
		       BLUE_HUES => '5',
		       MAGENTA_HUES => '6' }
	},
    SizeType =>
	{ contig => 1,
	  header => 'tools/gimptexttool.h',
	  symbols => [ qw(PIXELS POINTS) ],
	  mapping => { PIXELS => '0',
		       POINTS => '1' }
	}
);

foreach $e (values %enums) {
    $e->{info} = "";
    foreach (@{$e->{symbols}}) {
	my $nick = exists $e->{nicks}->{$_} ? $e->{nicks}->{$_} : $_;
	$e->{info} .= "$nick ($e->{mapping}->{$_}), "
    }
    $e->{info} =~ s/, $//;
}

1;

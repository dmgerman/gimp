#   Gimp-Python - allows the writing of Gimp plugins in Python.
#   Copyright (C) 1997-2003  James Henstridge <james@daa.com.au>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# gimpenums.py -- constants for use with the gimp module
#
# this file contains constants that are useful for use in
# gimp plugins.  Just add 'from gimpenums import *' to the top
# of the script

# NOTE: This file is autogenerated by enumcode-py.pl.

# TRUE and FALSE constants ...
import __builtin__
if not hasattr(__builtin__, 'True'):
    __builtin__.True = (1 == 1)
    __builtin__.False = (1 != 1)
del __builtin__

FALSE = False
TRUE = True

# GimpAddMaskType
ADD_WHITE_MASK = 0
ADD_BLACK_MASK = 1
ADD_ALPHA_MASK = 2
ADD_SELECTION_MASK = 3
ADD_COPY_MASK = 4

# GimpBlendMode
FG_BG_RGB_MODE = 0
FG_BG_HSV_MODE = 1
FG_TRANSPARENT_MODE = 2
CUSTOM_MODE = 3

# GimpBrushApplicationMode
BRUSH_HARD = 0
BRUSH_SOFT = 1

# GimpBucketFillMode
FG_BUCKET_FILL = 0
BG_BUCKET_FILL = 1
PATTERN_BUCKET_FILL = 2

# GimpChannelLutType
VALUE_LUT = 0
RED_LUT = 1
GREEN_LUT = 2
BLUE_LUT = 3
ALPHA_LUT = 4

# GimpChannelOps
CHANNEL_OP_ADD = 0
CHANNEL_OP_SUBTRACT = 1
CHANNEL_OP_REPLACE = 2
CHANNEL_OP_INTERSECT = 3

# GimpChannelType
RED_CHANNEL = 0
GREEN_CHANNEL = 1
BLUE_CHANNEL = 2
GRAY_CHANNEL = 3
INDEXED_CHANNEL = 4
ALPHA_CHANNEL = 5

# GimpCloneType
IMAGE_CLONE = 0
PATTERN_CLONE = 1

# GimpConvertDitherType
NO_DITHER = 0
FS_DITHER = 1
FSLOWBLEED_DITHER = 2
FIXED_DITHER = 3

# GimpConvertPaletteType
MAKE_PALETTE = 0
REUSE_PALETTE = 1
WEB_PALETTE = 2
MONO_PALETTE = 3
CUSTOM_PALETTE = 4

# GimpConvolutionType
NORMAL_CONVOL = 0
ABSOLUTE_CONVOL = 1
NEGATIVE_CONVOL = 2

# GimpConvolveType
BLUR_CONVOLVE = 0
SHARPEN_CONVOLVE = 1

# GimpDodgeBurnType
DODGE = 0
BURN = 1

# GimpFillType
FOREGROUND_FILL = 0
BACKGROUND_FILL = 1
WHITE_FILL = 2
TRANSPARENT_FILL = 3
NO_FILL = 4

# GimpGradientType
LINEAR = 0
BILINEAR = 1
RADIAL = 2
SQUARE = 3
CONICAL_SYMMETRIC = 4
CONICAL_ASYMMETRIC = 5
SHAPEBURST_ANGULAR = 6
SHAPEBURST_SPHERICAL = 7
SHAPEBURST_DIMPLED = 8
SPIRAL_CLOCKWISE = 9
SPIRAL_ANTICLOCKWISE = 10

# GimpHueRange
ALL_HUES = 0
RED_HUES = 1
YELLOW_HUES = 2
GREEN_HUES = 3
CYAN_HUES = 4
BLUE_HUES = 5
MAGENTA_HUES = 6

# GimpImageBaseType
RGB = 0
GRAY = 1
INDEXED = 2

# GimpImageType
RGB_IMAGE = 0
RGBA_IMAGE = 1
GRAY_IMAGE = 2
GRAYA_IMAGE = 3
INDEXED_IMAGE = 4
INDEXEDA_IMAGE = 5

# GimpLayerModeEffects
NORMAL_MODE = 0
DISSOLVE_MODE = 1
BEHIND_MODE = 2
MULTIPLY_MODE = 3
SCREEN_MODE = 4
OVERLAY_MODE = 5
DIFFERENCE_MODE = 6
ADDITION_MODE = 7
SUBTRACT_MODE = 8
DARKEN_ONLY_MODE = 9
LIGHTEN_ONLY_MODE = 10
HUE_MODE = 11
SATURATION_MODE = 12
COLOR_MODE = 13
VALUE_MODE = 14
DIVIDE_MODE = 15
DODGE_MODE = 16
BURN_MODE = 17
HARDLIGHT_MODE = 18
SOFTLIGHT_MODE = 19
GRAIN_EXTRACT_MODE = 20
GRAIN_MERGE_MODE = 21
COLOR_ERASE_MODE = 22

# GimpMaskApplyMode
MASK_APPLY = 0
MASK_DISCARD = 1

# GimpMergeType
EXPAND_AS_NECESSARY = 0
CLIP_TO_IMAGE = 1
CLIP_TO_BOTTOM_LAYER = 2
FLATTEN_IMAGE = 3

# GimpMessageHandlerType
MESSAGE_BOX = 0
CONSOLE = 1
ERROR_CONSOLE = 2

# GimpOffsetType
OFFSET_BACKGROUND = 0
OFFSET_TRANSPARENT = 1

# GimpOrientationType
ORIENTATION_HORIZONTAL = 0
ORIENTATION_VERTICAL = 1
ORIENTATION_UNKNOWN = 2

# GimpPDBArgType
PDB_INT32 = 0
PDB_INT16 = 1
PDB_INT8 = 2
PDB_FLOAT = 3
PDB_STRING = 4
PDB_INT32ARRAY = 5
PDB_INT16ARRAY = 6
PDB_INT8ARRAY = 7
PDB_FLOATARRAY = 8
PDB_STRINGARRAY = 9
PDB_COLOR = 10
PDB_REGION = 11
PDB_DISPLAY = 12
PDB_IMAGE = 13
PDB_LAYER = 14
PDB_CHANNEL = 15
PDB_DRAWABLE = 16
PDB_SELECTION = 17
PDB_BOUNDARY = 18
PDB_PATH = 19
PDB_PARASITE = 20
PDB_STATUS = 21
PDB_END = 22

# GimpPDBProcType
INTERNAL = 0
PLUGIN = 1
EXTENSION = 2
TEMPORARY = 3

# GimpPDBStatusType
PDB_EXECUTION_ERROR = 0
PDB_CALLING_ERROR = 1
PDB_PASS_THROUGH = 2
PDB_SUCCESS = 3
PDB_CANCEL = 4

# GimpPaintApplicationMode
PAINT_CONSTANT = 0
PAINT_INCREMENTAL = 1

# GimpRepeatMode
REPEAT_NONE = 0
REPEAT_SAWTOOTH = 1
REPEAT_TRIANGULAR = 2

# GimpRunMode
RUN_INTERACTIVE = 0
RUN_NONINTERACTIVE = 1
RUN_WITH_LAST_VALS = 2

# GimpStackTraceMode
STACK_TRACE_NEVER = 0
STACK_TRACE_QUERY = 1
STACK_TRACE_ALWAYS = 2

# GimpTransferMode
SHADOWS = 0
MIDTONES = 1
HIGHLIGHTS = 2

# GimpUnit
UNIT_PIXEL = 0
UNIT_INCH = 1
UNIT_MM = 2
UNIT_POINT = 3
UNIT_PICA = 4
UNIT_END = 5

# GimpSizeType
PIXELS = 0
POINTS = 1


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by enumcode.pl. */
end_comment

begin_include
include|#
directive|include
file|"siod/siod.h"
end_include

begin_function
name|void
DECL|function|init_generated_constants (void)
name|init_generated_constants
parameter_list|(
name|void
parameter_list|)
block|{
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ADD-WHITE-MASK"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ADD-BLACK-MASK"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ADD-ALPHA-MASK"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ADD-ALPHA-TRANSFER-MASK"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ADD-SELECTION-MASK"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ADD-COPY-MASK"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FG-BG-RGB-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FG-BG-HSV-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FG-TRANSPARENT-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CUSTOM-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BRUSH-HARD"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BRUSH-SOFT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FG-BUCKET-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BG-BUCKET-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PATTERN-BUCKET-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"VALUE-LUT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RED-LUT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GREEN-LUT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BLUE-LUT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ALPHA-LUT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CHANNEL-OP-ADD"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CHANNEL-OP-SUBTRACT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CHANNEL-OP-REPLACE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CHANNEL-OP-INTERSECT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RED-CHANNEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GREEN-CHANNEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BLUE-CHANNEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRAY-CHANNEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"INDEXED-CHANNEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ALPHA-CHANNEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"IMAGE-CLONE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PATTERN-CLONE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"NO-DITHER"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FS-DITHER"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FSLOWBLEED-DITHER"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FIXED-DITHER"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MAKE-PALETTE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"REUSE-PALETTE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"WEB-PALETTE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MONO-PALETTE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CUSTOM-PALETTE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"NORMAL-CONVOL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ABSOLUTE-CONVOL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"NEGATIVE-CONVOL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BLUR-CONVOLVE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"SHARPEN-CONVOLVE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"DODGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BURN"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FOREGROUND-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BACKGROUND-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"WHITE-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"TRANSPARENT-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PATTERN-FILL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-LINEAR"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-BILINEAR"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-RADIAL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-SQUARE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-CONICAL-SYMMETRIC"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-CONICAL-ASYMMETRIC"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-SHAPEBURST-ANGULAR"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|6
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-SHAPEBURST-SPHERICAL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|7
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-SHAPEBURST-DIMPLED"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|8
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-SPIRAL-CLOCKWISE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|9
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRADIENT-SPIRAL-ANTICLOCKWISE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|10
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ALL-HUES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RED-HUES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"YELLOW-HUES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GREEN-HUES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CYAN-HUES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BLUE-HUES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MAGENTA-HUES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|6
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RGB"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRAY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"INDEXED"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RGB-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RGBA-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRAY-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRAYA-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"INDEXED-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"INDEXEDA-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"NORMAL-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"DISSOLVE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BEHIND-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MULTIPLY-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"SCREEN-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"OVERLAY-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"DIFFERENCE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|6
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ADDITION-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|7
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"SUBTRACT-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|8
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"DARKEN-ONLY-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|9
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"LIGHTEN-ONLY-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|10
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"HUE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|11
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"SATURATION-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|12
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"COLOR-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|13
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"VALUE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|14
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"DIVIDE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|15
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"DODGE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|16
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"BURN-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|17
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"HARDLIGHT-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|18
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"SOFTLIGHT-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|19
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRAIN-EXTRACT-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|20
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"GRAIN-MERGE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|21
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"COLOR-ERASE-MODE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|22
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MASK-APPLY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MASK-DISCARD"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"EXPAND-AS-NECESSARY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CLIP-TO-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CLIP-TO-BOTTOM-LAYER"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"FLATTEN-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MESSAGE-BOX"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"CONSOLE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ERROR-CONSOLE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"OFFSET-BACKGROUND"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"OFFSET-TRANSPARENT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ORIENTATION-HORIZONTAL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ORIENTATION-VERTICAL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ORIENTATION-UNKNOWN"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-INT32"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-INT16"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-INT8"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-FLOAT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-STRING"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-INT32ARRAY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-INT16ARRAY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|6
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-INT8ARRAY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|7
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-FLOATARRAY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|8
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-STRINGARRAY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|9
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-COLOR"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|10
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-REGION"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|11
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-DISPLAY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|12
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-IMAGE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|13
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-LAYER"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|14
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-CHANNEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|15
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-DRAWABLE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|16
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-SELECTION"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|17
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-BOUNDARY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|18
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-PATH"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|19
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-PARASITE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|20
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-STATUS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|21
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-END"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|22
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"INTERNAL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PLUGIN"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"EXTENSION"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"TEMPORARY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-EXECUTION-ERROR"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-CALLING-ERROR"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-PASS-THROUGH"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-SUCCESS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PDB-CANCEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PAINT-CONSTANT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PAINT-INCREMENTAL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"REPEAT-NONE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"REPEAT-SAWTOOTH"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"REPEAT-TRIANGULAR"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ROTATE-90"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ROTATE-180"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"ROTATE-270"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RUN-INTERACTIVE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RUN-NONINTERACTIVE"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"RUN-WITH-LAST-VALS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"STACK-TRACE-NEVER"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"STACK-TRACE-QUERY"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"STACK-TRACE-ALWAYS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"SHADOWS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"MIDTONES"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"HIGHLIGHTS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"UNIT-PIXEL"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"UNIT-INCH"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"UNIT-MM"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|2
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"UNIT-POINT"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|3
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"UNIT-PICA"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|4
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"UNIT-END"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|5
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"PIXELS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|0
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
name|setvar
argument_list|(
name|cintern
argument_list|(
literal|"POINTS"
argument_list|)
argument_list|,
name|flocons
argument_list|(
literal|1
argument_list|)
argument_list|,
name|NIL
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************  * file: gtclenums.h  *  * Copyright (c) 1996 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  * $Id$  */
end_comment

begin_comment
comment|/*  * enums that are needed both by the  * interface file and at compile time  */
end_comment

begin_comment
comment|/* bucket fill stuff */
end_comment

begin_enum
DECL|enum|__anon2c7870100103
enum|enum
block|{
DECL|enumerator|FG_BUCKET_FILL
name|FG_BUCKET_FILL
block|,
DECL|enumerator|BG_BUCKET_FILL
name|BG_BUCKET_FILL
block|,
DECL|enumerator|PATTERN_BUCKET_FILL
name|PATTERN_BUCKET_FILL
block|}
enum|;
end_enum

begin_comment
comment|/* blend stuff */
end_comment

begin_enum
DECL|enum|__anon2c7870100203
enum|enum
block|{
DECL|enumerator|LINEAR
name|LINEAR
block|,
DECL|enumerator|BILINEAR
name|BILINEAR
block|,
DECL|enumerator|RADIAL
name|RADIAL
block|,
DECL|enumerator|SQUARE
name|SQUARE
block|,
DECL|enumerator|CONICAL_SYMMETRIC
name|CONICAL_SYMMETRIC
block|,
DECL|enumerator|CONICAL_ASYMMETRIC
name|CONICAL_ASYMMETRIC
block|,
DECL|enumerator|SHAPEBURST_ANGULAR
name|SHAPEBURST_ANGULAR
block|,
DECL|enumerator|SHAPEBURST_SPHERICAL
name|SHAPEBURST_SPHERICAL
block|,
DECL|enumerator|SHAPEBURST_DIMPLED
name|SHAPEBURST_DIMPLED
block|}
enum|;
end_enum

begin_enum
DECL|enum|__anon2c7870100303
enum|enum
block|{
DECL|enumerator|FG_BG_RGB
name|FG_BG_RGB
block|,
DECL|enumerator|FG_BG_HSV
name|FG_BG_HSV
block|,
DECL|enumerator|FG_TRANS
name|FG_TRANS
block|,
DECL|enumerator|CUSTOM
name|CUSTOM
block|}
enum|;
end_enum

begin_comment
comment|/* layer modes */
end_comment

begin_enum
DECL|enum|__anon2c7870100403
enum|enum
block|{
DECL|enumerator|NORMAL
name|NORMAL
init|=
literal|0
block|,
DECL|enumerator|DISSOLVE
name|DISSOLVE
init|=
literal|1
block|,
DECL|enumerator|BEHIND
name|BEHIND
init|=
literal|2
block|,
DECL|enumerator|MULTIPLY
name|MULTIPLY
init|=
literal|3
block|,
DECL|enumerator|SCREEN
name|SCREEN
init|=
literal|4
block|,
DECL|enumerator|OVERLAY
name|OVERLAY
init|=
literal|5
block|,
DECL|enumerator|DIFFERENCE
name|DIFFERENCE
init|=
literal|6
block|,
DECL|enumerator|ADDITION
name|ADDITION
init|=
literal|7
block|,
DECL|enumerator|SUBTRACT
name|SUBTRACT
init|=
literal|8
block|,
DECL|enumerator|DARKEN_ONLY
name|DARKEN_ONLY
init|=
literal|9
block|,
DECL|enumerator|LIGHTEN_ONLY
name|LIGHTEN_ONLY
init|=
literal|10
block|,
DECL|enumerator|HUE
name|HUE
init|=
literal|11
block|,
DECL|enumerator|SATURATION
name|SATURATION
init|=
literal|12
block|,
DECL|enumerator|COLOR
name|COLOR
init|=
literal|13
block|,
DECL|enumerator|VALUE
name|VALUE
init|=
literal|14
block|}
enum|;
end_enum

begin_comment
comment|/* gimp image get components */
end_comment

begin_enum
DECL|enum|__anon2c7870100503
enum|enum
block|{
DECL|enumerator|RED_CHANNEL
name|RED_CHANNEL
block|,
DECL|enumerator|GREEN_CHANNEL
name|GREEN_CHANNEL
block|,
DECL|enumerator|BLUE_CHANNEL
name|BLUE_CHANNEL
block|,
DECL|enumerator|GRAY_CHANNEL
name|GRAY_CHANNEL
block|,
DECL|enumerator|INDEXED_CHANNEL
name|INDEXED_CHANNEL
block|}
enum|;
end_enum

begin_comment
comment|/* layer masks */
end_comment

begin_enum
DECL|enum|__anon2c7870100603
enum|enum
block|{
DECL|enumerator|WHITE_MASK
name|WHITE_MASK
block|,
DECL|enumerator|BLACK_MASK
name|BLACK_MASK
block|,
DECL|enumerator|ALPHA_MASK
name|ALPHA_MASK
block|}
enum|;
end_enum

begin_comment
comment|/* remove layer mask */
end_comment

begin_enum
DECL|enum|__anon2c7870100703
enum|enum
block|{
DECL|enumerator|APPLY
name|APPLY
block|,
DECL|enumerator|DISCARD
name|DISCARD
block|}
enum|;
end_enum

begin_comment
comment|/* types of layer merges */
end_comment

begin_enum
DECL|enum|__anon2c7870100803
enum|enum
block|{
DECL|enumerator|EXPAND_AS_NECESSARY
name|EXPAND_AS_NECESSARY
block|,
DECL|enumerator|CLIP_TO_IMAGE
name|CLIP_TO_IMAGE
block|,
DECL|enumerator|CLIP_TO_BOTTOM_LAYER
name|CLIP_TO_BOTTOM_LAYER
block|}
enum|;
end_enum

begin_comment
comment|/* rect_select args */
end_comment

begin_enum
DECL|enum|__anon2c7870100903
enum|enum
block|{
DECL|enumerator|ADD
name|ADD
block|,
DECL|enumerator|SUB
name|SUB
block|,
DECL|enumerator|REPLACE
name|REPLACE
block|}
enum|;
end_enum

begin_comment
comment|/* cloning */
end_comment

begin_enum
DECL|enum|__anon2c7870100a03
enum|enum
block|{
DECL|enumerator|IMAGE_CLONE
name|IMAGE_CLONE
block|,
DECL|enumerator|PATTERN_CLONE
name|PATTERN_CLONE
block|}
enum|;
end_enum

begin_comment
comment|/* convolving type */
end_comment

begin_enum
DECL|enum|__anon2c7870100b03
enum|enum
block|{
DECL|enumerator|BLUR
name|BLUR
block|,
DECL|enumerator|SHARPEN
name|SHARPEN
block|}
enum|;
end_enum

end_unit


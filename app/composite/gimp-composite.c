begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- mode: c tab-width: 2; c-basic-indent: 2; indent-tabs-mode: nil -*-  * The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  *  * Gimp image compositing  * Copyright (C) 2003  Helvetix Victorinox, a pseudonym,<helvetix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"base/cpu-accel.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-generic.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ARCH_X86
end_ifdef

begin_include
include|#
directive|include
file|"gimp-composite-mmx.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-sse.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * Details about pixel formats, bits-per-pixel alpha and non alpha  * versions of pixel formats.  */
end_comment

begin_comment
comment|/*  * Report on the number of bytes a particular pixel format consumes per pixel.  */
end_comment

begin_decl_stmt
DECL|variable|gimp_composite_pixel_bpp
specifier|const
name|guchar
name|gimp_composite_pixel_bpp
index|[]
init|=
block|{
literal|1
block|,
comment|/* GIMP_PIXELFORMAT_V8      */
literal|2
block|,
comment|/* GIMP_PIXELFORMAT_VA8     */
literal|3
block|,
comment|/* GIMP_PIXELFORMAT_RGB8    */
literal|4
block|,
comment|/* GIMP_PIXELFORMAT_RGBA8   */
if|#
directive|if
name|GIMP_COMPOSITE_16BIT
literal|2
block|,
comment|/* GIMP_PIXELFORMAT_V16     */
literal|4
block|,
comment|/* GIMP_PIXELFORMAT_VA16    */
literal|6
block|,
comment|/* GIMP_PIXELFORMAT_RGB16   */
literal|8
block|,
comment|/* GIMP_PIXELFORMAT_RGBA16  */
endif|#
directive|endif
if|#
directive|if
name|GIMP_COMPOSITE_32BIT
literal|2
block|,
comment|/* GIMP_PIXELFORMAT_V32     */
literal|4
block|,
comment|/* GIMP_PIXELFORMAT_VA32    */
literal|6
block|,
comment|/* GIMP_PIXELFORMAT_RGB32   */
literal|8
block|,
comment|/* GIMP_PIXELFORMAT_RGBA32  */
endif|#
directive|endif
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_ANY */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_composite_pixel_name
specifier|const
name|gchar
modifier|*
name|gimp_composite_pixel_name
index|[]
init|=
block|{
literal|"GIMP_PIXELFORMAT_V8"
block|,
literal|"GIMP_PIXELFORMAT_VA8"
block|,
literal|"GIMP_PIXELFORMAT_RGB8"
block|,
literal|"GIMP_PIXELFORMAT_RGBA8"
block|,
if|#
directive|if
name|GIMP_COMPOSITE_16BIT
literal|"GIMP_PIXELFORMAT_V16"
block|,
literal|"GIMP_PIXELFORMAT_VA16"
block|,
literal|"GIMP_PIXELFORMAT_RGB16 "
block|,
literal|"GIMP_PIXELFORMAT_RGBA16 "
block|,
endif|#
directive|endif
if|#
directive|if
name|GIMP_COMPOSITE_32BIT
literal|"GIMP_PIXELFORMAT_V32"
block|,
literal|"GIMP_PIXELFORMAT_VA32"
block|,
literal|"GIMP_PIXELFORMAT_RGB32 "
block|,
literal|"GIMP_PIXELFORMAT_RGBA32 "
block|,
endif|#
directive|endif
literal|"GIMP_PIXELFORMAT_ANY"
block|,   }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * Report true (non-zero) if a pixel format has alpha.  */
end_comment

begin_decl_stmt
DECL|variable|gimp_composite_pixel_alphap
specifier|const
name|guchar
name|gimp_composite_pixel_alphap
index|[]
init|=
block|{
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_V8      */
literal|1
block|,
comment|/* GIMP_PIXELFORMAT_VA8     */
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_RGB8    */
literal|1
block|,
comment|/* GIMP_PIXELFORMAT_RGBA8   */
if|#
directive|if
name|GIMP_COMPOSITE_16BIT
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_V16     */
literal|1
block|,
comment|/* GIMP_PIXELFORMAT_VA16    */
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_RGB16   */
literal|1
block|,
comment|/* GIMP_PIXELFORMAT_RGBA16  */
endif|#
directive|endif
if|#
directive|if
name|GIMP_COMPOSITE_32BIT
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_V32     */
literal|1
block|,
comment|/* GIMP_PIXELFORMAT_VA32    */
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_RGB32   */
literal|1
block|,
comment|/* GIMP_PIXELFORMAT_RGBA32  */
endif|#
directive|endif
literal|0
block|,
comment|/* GIMP_PIXELFORMAT_UNKNOWN */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * Convert to/from pixel formats with/without alpha.  */
end_comment

begin_decl_stmt
DECL|variable|gimp_composite_pixel_alpha
specifier|const
name|GimpPixelFormat
name|gimp_composite_pixel_alpha
index|[]
init|=
block|{
name|GIMP_PIXELFORMAT_VA8
block|,
comment|/* GIMP_PIXELFORMAT_V8      */
name|GIMP_PIXELFORMAT_V8
block|,
comment|/* GIMP_PIXELFORMAT_VA8     */
name|GIMP_PIXELFORMAT_RGBA8
block|,
comment|/* GIMP_PIXELFORMAT_RGB8    */
name|GIMP_PIXELFORMAT_RGB8
block|,
comment|/* GIMP_PIXELFORMAT_RGBA8   */
if|#
directive|if
name|GIMP_COMPOSITE_16BIT
name|GIMP_PIXELFORMAT_VA16
block|,
name|GIMP_PIXELFORMAT_V16
block|,
name|GIMP_PIXELFORMAT_RGBA16
block|,
name|GIMP_PIXELFORMAT_RGB16
endif|#
directive|endif
if|#
directive|if
name|GIMP_COMPOSITE_32BIT
name|GIMP_PIXELFORMAT_VA32
block|,
name|GIMP_PIXELFORMAT_V32
block|,
name|GIMP_PIXELFORMAT_RGBA32
block|,
name|GIMP_PIXELFORMAT_RGB32
endif|#
directive|endif
name|GIMP_PIXELFORMAT_ANY
block|,
comment|/* GIMP_PIXELFORMAT_ANY */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * XXX I don't like to put this here.  I think this information,  * specific to the functions, ought to be with the function.  */
end_comment

begin_decl_stmt
DECL|variable|gimp_composite_operation_effects
name|struct
name|GimpCompositeOperationEffects
name|gimp_composite_operation_effects
index|[]
init|=
block|{
block|{
name|TRUE
block|,
name|TRUE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_NORMAL_MODE        */
block|{
name|TRUE
block|,
name|TRUE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_DISSOLVE_MODE      */
block|{
name|TRUE
block|,
name|TRUE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_BEHIND_MODE        */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_MULTIPLY_MODE      */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_SCREEN_MODE        */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_OVERLAY_MODE       */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_DIFFERENCE_MODE    */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_ADDITION_MODE      */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_SUBTRACT_MODE      */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_DARKEN_ONLY_MODE   */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_LIGHTEN_ONLY_MODE  */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_HUE_MODE           */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_SATURATION_MODE    */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_COLOR_MODE         */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_VALUE_MODE         */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_DIVIDE_MODE        */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_DODGE_MODE         */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_BURN_MODE          */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_HARDLIGHT_MODE     */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_SOFTLIGHT_MODE     */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_GRAIN_EXTRACT_MODE */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_GRAIN_MERGE_MODE   */
block|{
name|TRUE
block|,
name|FALSE
block|,
name|TRUE
block|,  }
block|,
comment|/*  GIMP_COLOR_ERASE_MODE   */
block|{
name|TRUE
block|,
name|FALSE
block|,
name|TRUE
block|,  }
block|,
comment|/*  GIMP_ERASE_MODE         */
block|{
name|TRUE
block|,
name|TRUE
block|,
name|TRUE
block|,  }
block|,
comment|/*  GIMP_REPLACE_MODE       */
block|{
name|TRUE
block|,
name|TRUE
block|,
name|FALSE
block|, }
block|,
comment|/*  GIMP_ANTI_ERASE_MODE    */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|}
block|,
comment|/*  GIMP_SWAP */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|}
block|,
comment|/*  GIMP_SCALE */
block|{
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|}
block|,
comment|/*  GIMP_CONVERT */
block|}
decl_stmt|;
end_decl_stmt

begin_struct
struct|struct
DECL|struct|__anon2c278a640108
block|{
DECL|member|announce_function
name|gchar
name|announce_function
decl_stmt|;
DECL|variable|gimp_composite_debug
block|}
name|gimp_composite_debug
struct|;
end_struct

begin_decl_stmt
DECL|variable|gimp_composite_options
name|struct
name|GimpCompositeOptions
name|gimp_composite_options
init|=
block|{
name|GIMP_COMPOSITE_OPTION_USE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_composite_function_name
name|gchar
modifier|*
name|gimp_composite_function_name
index|[
name|GIMP_COMPOSITE_N
index|]
index|[
name|GIMP_PIXELFORMAT_N
index|]
index|[
name|GIMP_PIXELFORMAT_N
index|]
index|[
name|GIMP_PIXELFORMAT_N
index|]
decl_stmt|;
end_decl_stmt

begin_function_decl
DECL|variable|gimp_composite_function
name|void
function_decl|(
modifier|*
name|gimp_composite_function
index|[
name|GIMP_COMPOSITE_N
index|]
index|[
name|GIMP_PIXELFORMAT_N
index|]
index|[
name|GIMP_PIXELFORMAT_N
index|]
index|[
name|GIMP_PIXELFORMAT_N
index|]
function_decl|)
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_composite_dispatch (GimpCompositeContext * ctx)
name|gimp_composite_dispatch
parameter_list|(
name|GimpCompositeContext
modifier|*
name|ctx
parameter_list|)
block|{
name|void
function_decl|(
modifier|*
name|function
function_decl|)
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
name|function
operator|=
name|gimp_composite_function
index|[
name|ctx
operator|->
name|op
index|]
index|[
name|ctx
operator|->
name|pixelformat_A
index|]
index|[
name|ctx
operator|->
name|pixelformat_B
index|]
index|[
name|ctx
operator|->
name|pixelformat_D
index|]
expr_stmt|;
if|if
condition|(
name|function
condition|)
block|{
if|if
condition|(
name|gimp_composite_options
operator|.
name|bits
operator|&
name|GIMP_COMPOSITE_OPTION_VERBOSE
condition|)
block|{
name|printf
argument_list|(
literal|"%s %s %s %s = %p\n"
argument_list|,
name|gimp_composite_mode_astext
argument_list|(
name|ctx
operator|->
name|op
argument_list|)
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_A
argument_list|)
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_B
argument_list|)
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_D
argument_list|)
argument_list|,
name|function
argument_list|)
expr_stmt|;
block|}
call|(
modifier|*
name|function
call|)
argument_list|(
name|ctx
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|printf
argument_list|(
literal|"gimp_composite: unsupported operation: %s %s %s %s\n"
argument_list|,
name|gimp_composite_mode_astext
argument_list|(
name|ctx
operator|->
name|op
argument_list|)
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_A
argument_list|)
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_B
argument_list|)
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_D
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_context_print (GimpCompositeContext * ctx)
name|gimp_composite_context_print
parameter_list|(
name|GimpCompositeContext
modifier|*
name|ctx
parameter_list|)
block|{
name|printf
argument_list|(
literal|"%p: op=%s\n  A=%s(%d):%p\n  B=%s(%d):%p\n  D=%s(%d):%p\n  M=%s(%d):%p\n  n_pixels=%lu\n"
argument_list|,
name|ctx
argument_list|,
name|gimp_composite_mode_astext
argument_list|(
name|ctx
operator|->
name|op
argument_list|)
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_A
argument_list|)
argument_list|,
name|ctx
operator|->
name|pixelformat_A
argument_list|,
name|ctx
operator|->
name|A
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_B
argument_list|)
argument_list|,
name|ctx
operator|->
name|pixelformat_B
argument_list|,
name|ctx
operator|->
name|B
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_D
argument_list|)
argument_list|,
name|ctx
operator|->
name|pixelformat_D
argument_list|,
name|ctx
operator|->
name|D
argument_list|,
name|gimp_composite_pixelformat_astext
argument_list|(
name|ctx
operator|->
name|pixelformat_M
argument_list|)
argument_list|,
name|ctx
operator|->
name|pixelformat_M
argument_list|,
name|ctx
operator|->
name|M
argument_list|,
name|ctx
operator|->
name|n_pixels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_composite_mode_astext (GimpCompositeOperation op)
name|gimp_composite_mode_astext
parameter_list|(
name|GimpCompositeOperation
name|op
parameter_list|)
block|{
switch|switch
condition|(
name|op
condition|)
block|{
case|case
name|GIMP_COMPOSITE_NORMAL
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_NORMAL"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_DISSOLVE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_DISSOLVE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_BEHIND
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_BEHIND"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_MULTIPLY
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_MULTIPLY"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_SCREEN
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_SCREEN"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_OVERLAY
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_OVERLAY"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_DIFFERENCE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_DIFFERENCE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_ADDITION
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_ADDITION"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_SUBTRACT
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_SUBTRACT"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_DARKEN
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_DARKEN"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_LIGHTEN
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_LIGHTEN"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_HUE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_HUE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_SATURATION
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_SATURATION"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_COLOR_ONLY
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_COLOR_ONLY"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_VALUE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_VALUE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_DIVIDE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_DIVIDE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_DODGE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_DODGE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_BURN
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_BURN"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_HARDLIGHT
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_HARDLIGHT"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_SOFTLIGHT
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_SOFTLIGHT"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_GRAIN_EXTRACT
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_GRAIN_EXTRACT"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_GRAIN_MERGE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_GRAIN_MERGE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_COLOR_ERASE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_COLOR_ERASE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_ERASE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_ERASE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_REPLACE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_REPLACE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_ANTI_ERASE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_ANTI_ERASE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_BLEND
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_BLEND"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_SHADE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_SHADE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_SWAP
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_SWAP"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_SCALE
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_SCALE"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_CONVERT
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_CONVERT"
operator|)
return|;
case|case
name|GIMP_COMPOSITE_XOR
case|:
return|return
operator|(
literal|"GIMP_COMPOSITE_XOR"
operator|)
return|;
default|default:
break|break;
block|}
return|return
operator|(
literal|"bad mode"
operator|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_composite_pixelformat_astext (GimpPixelFormat f)
name|gimp_composite_pixelformat_astext
parameter_list|(
name|GimpPixelFormat
name|f
parameter_list|)
block|{
switch|switch
condition|(
name|f
condition|)
block|{
case|case
name|GIMP_PIXELFORMAT_V8
case|:
return|return
operator|(
literal|"V8"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_VA8
case|:
return|return
operator|(
literal|"VA8"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_RGB8
case|:
return|return
operator|(
literal|"RGB8"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_RGBA8
case|:
return|return
operator|(
literal|"RGBA8"
operator|)
return|;
if|#
directive|if
name|GIMP_COMPOSITE_16BIT
case|case
name|GIMP_PIXELFORMAT_V16
case|:
return|return
operator|(
literal|"V16"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_VA16
case|:
return|return
operator|(
literal|"VA16"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_RGB16
case|:
return|return
operator|(
literal|"RGB16"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_RGBA16
case|:
return|return
operator|(
literal|"RGBA16"
operator|)
return|;
endif|#
directive|endif
if|#
directive|if
name|GIMP_COMPOSITE_32BIT
case|case
name|GIMP_PIXELFORMAT_V32
case|:
return|return
operator|(
literal|"V32"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_VA32
case|:
return|return
operator|(
literal|"VA32"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_RGB32
case|:
return|return
operator|(
literal|"RGB32"
operator|)
return|;
case|case
name|GIMP_PIXELFORMAT_RGBA32
case|:
return|return
operator|(
literal|"RGBA32"
operator|)
return|;
endif|#
directive|endif
case|case
name|GIMP_PIXELFORMAT_ANY
case|:
return|return
operator|(
literal|"ANY"
operator|)
return|;
default|default:
break|break;
block|}
return|return
operator|(
literal|"bad format"
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_composite_init (void)
name|gimp_composite_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
if|if
condition|(
operator|(
name|p
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_COMPOSITE"
argument_list|)
operator|)
condition|)
block|{
name|gimp_composite_options
operator|.
name|bits
operator|=
name|strtoul
argument_list|(
name|p
argument_list|,
name|NULL
argument_list|,
literal|16
argument_list|)
expr_stmt|;
block|}
name|g_printerr
argument_list|(
literal|"gimp_composite: use=%s, verbose=%s"
argument_list|,
operator|(
name|gimp_composite_options
operator|.
name|bits
operator|&
name|GIMP_COMPOSITE_OPTION_USE
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|,
operator|(
name|gimp_composite_options
operator|.
name|bits
operator|&
name|GIMP_COMPOSITE_OPTION_VERBOSE
operator|)
condition|?
literal|"yes"
else|:
literal|"no"
argument_list|)
expr_stmt|;
name|gimp_composite_generic_install
argument_list|()
expr_stmt|;
comment|/*    * Here is where you "glue" in the initialisation of your    * optimisations.    *    * Declare the install() function external, and then call it.  A    * return value of TRUE from the install function means the    * installer was successful in instantiating itself.  For example,    * it succeeded in hooking in the functions with the special    * optimisation instructions, or hardware, or whatever.    */
if|if
condition|(
operator|!
operator|(
name|gimp_composite_options
operator|.
name|bits
operator|&
name|GIMP_COMPOSITE_OPTION_INITIALISED
operator|)
condition|)
block|{
specifier|extern
name|gboolean
name|gimp_composite_mmx_install
parameter_list|()
function_decl|;
specifier|extern
name|gboolean
name|gimp_composite_sse_install
parameter_list|()
function_decl|;
specifier|extern
name|gboolean
name|gimp_composite_sse2_install
parameter_list|()
function_decl|;
specifier|extern
name|gboolean
name|gimp_composite_3dnow_install
parameter_list|()
function_decl|;
specifier|extern
name|gboolean
name|gimp_composite_altivec_install
parameter_list|()
function_decl|;
specifier|extern
name|gboolean
name|gimp_composite_vis_install
parameter_list|()
function_decl|;
if|if
condition|(
name|gimp_composite_mmx_install
argument_list|()
condition|)
name|g_printerr
argument_list|(
literal|" +mmx"
argument_list|)
expr_stmt|;
else|else
name|g_printerr
argument_list|(
literal|" -mmx"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_sse_install
argument_list|()
condition|)
name|g_printerr
argument_list|(
literal|" +sse"
argument_list|)
expr_stmt|;
else|else
name|g_printerr
argument_list|(
literal|" -sse"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_sse2_install
argument_list|()
condition|)
name|g_printerr
argument_list|(
literal|" +sse2"
argument_list|)
expr_stmt|;
else|else
name|g_printerr
argument_list|(
literal|" -sse2"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_3dnow_install
argument_list|()
condition|)
name|g_printerr
argument_list|(
literal|" +3dnow"
argument_list|)
expr_stmt|;
else|else
name|g_printerr
argument_list|(
literal|" -3dnow"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_altivec_install
argument_list|()
condition|)
name|g_printerr
argument_list|(
literal|" +altivec"
argument_list|)
expr_stmt|;
else|else
name|g_printerr
argument_list|(
literal|" -altivec"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_composite_vis_install
argument_list|()
condition|)
name|g_printerr
argument_list|(
literal|" +vis"
argument_list|)
expr_stmt|;
else|else
name|g_printerr
argument_list|(
literal|" -vis"
argument_list|)
expr_stmt|;
name|gimp_composite_options
operator|.
name|bits
operator||=
name|GIMP_COMPOSITE_OPTION_INITIALISED
expr_stmt|;
block|}
name|g_printerr
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gimp image compositing  * Copyright (C) 2003  Helvetix Victorinox, a pseudonym,<helvetix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimp-composite.h"
end_include

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
block|, }
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

begin_function
name|void
DECL|function|gimp_composite_unsupported (GimpCompositeContext * ctx)
name|gimp_composite_unsupported
parameter_list|(
name|GimpCompositeContext
modifier|*
name|ctx
parameter_list|)
block|{
name|printf
argument_list|(
literal|"compositing function %d unsupported\n"
argument_list|,
name|ctx
operator|->
name|op
argument_list|)
expr_stmt|;
block|}
end_function

begin_struct
DECL|struct|__anon2bf137ac0108
struct|struct
block|{
DECL|member|announce_function
name|char
name|announce_function
decl_stmt|;
DECL|variable|gimp_composite_debug
block|}
name|gimp_composite_debug
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|char
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

begin_extern
extern|extern void (*gimp_composite_function[GIMP_COMPOSITE_N][GIMP_PIXELFORMAT_N][GIMP_PIXELFORMAT_N][GIMP_PIXELFORMAT_N]
end_extern

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

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
parameter_list|()
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
call|(
modifier|*
name|function
call|)
argument_list|(
name|ctx
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"unsupported composite operation %d %d %d (see gimp-composite.h)\n"
argument_list|,
name|ctx
operator|->
name|op
argument_list|,
name|ctx
operator|->
name|pixelformat_A
argument_list|,
name|ctx
operator|->
name|pixelformat_B
argument_list|)
expr_stmt|;
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
literal|"%p: %s op=%d A=%s(%d):%p B=%s(%d):%p D=%s(%d):%p M=%s(%d):%p n_pixels=%lu\n"
argument_list|,
name|ctx
argument_list|,
name|gimp_composite_function_name
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
argument_list|,
name|ctx
operator|->
name|op
argument_list|,
name|gimp_composite_pixel_name
index|[
name|ctx
operator|->
name|pixelformat_A
index|]
argument_list|,
name|ctx
operator|->
name|pixelformat_A
argument_list|,
name|ctx
operator|->
name|A
argument_list|,
name|gimp_composite_pixel_name
index|[
name|ctx
operator|->
name|pixelformat_B
index|]
argument_list|,
name|ctx
operator|->
name|pixelformat_B
argument_list|,
name|ctx
operator|->
name|A
argument_list|,
name|gimp_composite_pixel_name
index|[
name|ctx
operator|->
name|pixelformat_D
index|]
argument_list|,
name|ctx
operator|->
name|pixelformat_D
argument_list|,
name|ctx
operator|->
name|A
argument_list|,
name|gimp_composite_pixel_name
index|[
name|ctx
operator|->
name|pixelformat_M
index|]
argument_list|,
name|ctx
operator|->
name|pixelformat_M
argument_list|,
name|ctx
operator|->
name|A
argument_list|,
name|ctx
operator|->
name|n_pixels
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_composite_options
name|struct
name|GimpCompositeOptions
name|gimp_composite_options
decl_stmt|;
end_decl_stmt

end_unit


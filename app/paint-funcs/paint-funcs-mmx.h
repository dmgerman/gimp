begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * This file is supposed to contain the MMX implementation  of the   * pixelfiddeling paint-functions.   */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_FUNCS_MMX_H__
end_ifndef

begin_define
DECL|macro|__PAINT_FUNCS_MMX_H__
define|#
directive|define
name|__PAINT_FUNCS_MMX_H__
end_define

begin_comment
comment|/* FIXME: Needs a bigger overhaul. Maybe inline assembly would be better? */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_ASM_MMX
end_ifdef

begin_define
DECL|macro|MMX_PIXEL_OP (x)
define|#
directive|define
name|MMX_PIXEL_OP
parameter_list|(
name|x
parameter_list|)
define|\
value|void \ x( \   const unsigned char *src1, \   const unsigned char *src2, \   unsigned count, \   unsigned char *dst) __attribute((regparm(3)));
end_define

begin_comment
comment|/* A drawable has an alphachannel if contains either 4 or 2 bytes data  * aka GRAYA and RGBA and thus the macro below works. This will have  * to change if we support bigger formats. We'll do it so for now because  * masking is always cheaper than passing parameters over the stack.      */
end_comment

begin_define
DECL|macro|HAS_ALPHA (bytes)
define|#
directive|define
name|HAS_ALPHA
parameter_list|(
name|bytes
parameter_list|)
value|(~##bytes& 1)
end_define

begin_define
DECL|macro|MMX_PIXEL_OP_3A_1A (op)
define|#
directive|define
name|MMX_PIXEL_OP_3A_1A
parameter_list|(
name|op
parameter_list|)
define|\
value|MMX_PIXEL_OP(op##_pixels_3a_3a) \   MMX_PIXEL_OP(op##_pixels_1a_1a)
end_define

begin_define
DECL|macro|USE_MMX_PIXEL_OP_3A_1A (op)
define|#
directive|define
name|USE_MMX_PIXEL_OP_3A_1A
parameter_list|(
name|op
parameter_list|)
define|\
value|if (HAS_ALPHA (alms->bytes1)&& HAS_ALPHA (bytes2)) \     { \       if (alms->bytes1==2&& alms->bytes2==2) \ 	return op##_pixels_1a_1a(alms->src1, alms->src2, alms->length, alms->dest); \       if (alms->bytes1==4&& alms->bytes2==4) \ 	return op##_pixels_3a_3a(alms->src1, alms->src2, alms->length, alms->dest); \     }
end_define

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|multiply
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_multiply_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_multiply_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|multiply
argument_list|)
expr_stmt|;
block|}
end_function

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|screen
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_screen_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_screen_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|screen
argument_list|)
expr_stmt|;
block|}
end_function

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|overlay
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_overlay_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_overlay_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|overlay
argument_list|)
expr_stmt|;
block|}
end_function

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|difference
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_difference_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_difference_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|difference
argument_list|)
expr_stmt|;
block|}
end_function

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|add
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_addition_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_addition_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|add
argument_list|)
expr_stmt|;
block|}
end_function

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|substract
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_subtract_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_subtract_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|substract
argument_list|)
expr_stmt|;
block|}
end_function

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|darken
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_darken_only_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_darken_only_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|darken
argument_list|)
expr_stmt|;
block|}
end_function

begin_expr_stmt
name|MMX_PIXEL_OP_3A_1A
argument_list|(
name|lighten
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function
specifier|static
name|void
DECL|function|layer_lighten_only_mode_mmx (struct apply_layer_mode_struct * alms)
name|layer_lighten_only_mode_mmx
parameter_list|(
name|struct
name|apply_layer_mode_struct
modifier|*
name|alms
parameter_list|)
block|{
name|USE_MMX_PIXEL_OP_3A_1A
argument_list|(
name|lighten
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_ASM_MMX */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_FUNCS_MMX_H__  */
end_comment

end_unit


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
comment|/* FIXME: Needs a bigger overhaul. Maybe inline assembly would be better?   * 'bigger overhaul' indeed, but let's not talk about assembly language now (Nov-03-2002)  * This code is being disabled to address Bug #86290; point your favorite browser to  * http://bugzilla.gnome.org/show_bug.cgi?id=86290 for the reason this is being done.  * Presuming you've read the "Additional Comments" there, and really, really, think that  * Gimp ought to have this MMX code, RIGHT NOW (!) then this is what I believe you have to do:  * 1.  Be aware that the MMX code is incomplete; the macro USE_MMX_PIXEL_OP_3A_1A has been  *     written the way it has so that the MMX code is invoked only on region depths it knows  *     how to handle. In that case, the MMX code executes and the macro performs a return to  *     caller. Otherwise, it DOES NOT DO ANYTHING, and the macro ought to be followed by   *     code that had better do something. Check out an archival app/paint_funcs/paint_funcs.c  *     say, CVS version 1.98 (Nov 2, 2001) and study how USE_MMX_PIXEL_OP_3A_1A was used there;  *     you'll discover that it must have some kind of alternate code following in case program  *     flow does not return to the caller inside the macro.   * 2a. For this reason, you have to pretty much undo the separation of 'generic C' and 'mmx' code at  *     at the heart of Nov-18-2001, Nov-19-2001 check-ins (See Daniel Egger's comments in   *     ChangeLog). That, or replicate the 'generic C' in the various *_mmx functions implemented  *     in this header file, below. Not only would that make the separation effort rather pointless, but  *     the replication of functionality creates a maintenance problem.  * 2b. Alternatively, you can finish the MMX code so that it handles all cases that the generic  *     C does. This is ideal, and makes sensible the separation effort, for then  USE_MMX_PIXEL_OP_3A_1A  *     need not have any additional implementation following. For that matter, you'd likely not   *     even need the macro. You'd also be a better man than I am, Gunga Din.  * Whatever you do, proceed carefully and keep fresh batteries in your electric torch: there be monsters here.  *                                                                            grosgood@rcn.com  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_ASM_MMX
end_ifdef

begin_if
if|#
directive|if
name|GIMP_ENABLE_MMX
end_if

begin_define
DECL|macro|MMX_PIXEL_OP (x)
define|#
directive|define
name|MMX_PIXEL_OP
parameter_list|(
name|x
parameter_list|)
define|\
value|void \ x( \   const guchar *src1, \   const guchar *src2, \   guint count, \   guchar *dst) __attribute((regparm(3)));
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
value|if (HAS_ALPHA (alms->bytes1)&& HAS_ALPHA (alms->bytes2)) \     { \       if (alms->bytes1==2&& alms->bytes2==2) \ 	return op##_pixels_1a_1a(alms->src1, alms->src2, alms->length, *(alms->dest)); \       if (alms->bytes1==4&& alms->bytes2==4) \ 	return op##_pixels_3a_3a(alms->src1, alms->src2, alms->length, *(alms->dest)); \     }
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
comment|/* GIMP_ENABLE_MMX        */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_ASM_MMX           */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PAINT_FUNCS_MMX_H__  */
end_comment

end_unit


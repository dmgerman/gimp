begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Colormap-Rotation plug-in. Exchanges two color ranges.  *  * Copyright (C) 1999 Sven Anders (anderss@fmi.uni-passau.de)  *                    Based on code from Pavel Grinfeld (pavel@ml.com)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------  * Change log:  *   * Version 2.0, 04 April 1999.  *  Nearly complete rewrite, made plug-in stable.  *  (Works with GIMP 1.1 and GTK+ 1.2)  *  * Version 1.0, 27 March 1997.  *  Initial (unstable) release by Pavel Grinfeld  *  *-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Global defines */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_define
DECL|macro|SWAP (X,Y)
define|#
directive|define
name|SWAP
parameter_list|(
name|X
parameter_list|,
name|Y
parameter_list|)
value|{float t=X; X=Y; Y=t;}
end_define

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* used in 'rcm_callback.c' and 'rcm_dialog.c' */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|float
name|arctg
parameter_list|(
name|float
name|y
parameter_list|,
name|float
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|min_prox
parameter_list|(
name|float
name|alpha
parameter_list|,
name|float
name|beta
parameter_list|,
name|float
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
modifier|*
name|closest
parameter_list|(
name|float
modifier|*
name|alpha
parameter_list|,
name|float
modifier|*
name|beta
parameter_list|,
name|float
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|angle_mod_2PI
parameter_list|(
name|float
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ReducedImage
modifier|*
name|rcm_reduce_image
parameter_list|(
name|GDrawable
modifier|*
parameter_list|,
name|GDrawable
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_render_preview
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_render_circle
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|int
name|sum
parameter_list|,
name|int
name|margin
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* only used in 'rcm.c' (or local) */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|float
name|rcm_angle_inside_slice
parameter_list|(
name|float
name|angle
parameter_list|,
name|RcmAngle
modifier|*
name|slice
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_is_gray
parameter_list|(
name|float
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|rcm_linear
parameter_list|(
name|float
parameter_list|,
name|float
parameter_list|,
name|float
parameter_list|,
name|float
parameter_list|,
name|float
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|rcm_left_end
parameter_list|(
name|RcmAngle
modifier|*
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|rcm_right_end
parameter_list|(
name|RcmAngle
modifier|*
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

end_unit


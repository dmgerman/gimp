begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************************************/
end_comment

begin_comment
comment|/* GCK - The General Convenience Kit. Generally useful conveniece routines */
end_comment

begin_comment
comment|/* for GIMP plug-in writers and users of the GDK/GTK libraries.            */
end_comment

begin_comment
comment|/* Copyright (C) 1996 Tom Bech                                             */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is free software; you can redistribute it and/or modify    */
end_comment

begin_comment
comment|/* it under the terms of the GNU General Public License as published by    */
end_comment

begin_comment
comment|/* the Free Software Foundation; either version 2 of the License, or       */
end_comment

begin_comment
comment|/* (at your option) any later version.                                     */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is distributed in the hope that it will be useful,         */
end_comment

begin_comment
comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
end_comment

begin_comment
comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
end_comment

begin_comment
comment|/* GNU General Public License for more details.                            */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* You should have received a copy of the GNU General Public License       */
end_comment

begin_comment
comment|/* along with this program; if not, write to the Free Software             */
end_comment

begin_comment
comment|/* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               */
end_comment

begin_comment
comment|/***************************************************************************/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GCKVECTOR_H__
end_ifndef

begin_define
DECL|macro|__GCKVECTOR_H__
define|#
directive|define
name|__GCKVECTOR_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* Two dimensional vector functions */
comment|/* ================================ */
name|double
name|gck_vector2_inner_product
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
function_decl|;
name|GckVector3
name|gck_vector2_cross_product
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
function_decl|;
name|double
name|gck_vector2_length
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|)
function_decl|;
name|void
name|gck_vector2_normalize
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|)
function_decl|;
name|void
name|gck_vector2_mul
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|double
name|b
parameter_list|)
function_decl|;
name|void
name|gck_vector2_sub
parameter_list|(
name|GckVector2
modifier|*
name|c
parameter_list|,
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
function_decl|;
name|void
name|gck_vector2_set
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|)
function_decl|;
name|void
name|gck_vector2_add
parameter_list|(
name|GckVector2
modifier|*
name|c
parameter_list|,
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
function_decl|;
name|void
name|gck_vector2_neg
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|)
function_decl|;
name|void
name|gck_vector2_rotate
parameter_list|(
name|GckVector2
modifier|*
name|v
parameter_list|,
name|double
name|alpha
parameter_list|)
function_decl|;
comment|/* Three dimensional vector functions */
comment|/* ================================== */
name|double
name|gck_vector3_inner_product
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
function_decl|;
name|GckVector3
name|gck_vector3_cross_product
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
function_decl|;
name|double
name|gck_vector3_length
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|)
function_decl|;
name|void
name|gck_vector3_normalize
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|)
function_decl|;
name|void
name|gck_vector3_mul
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|double
name|b
parameter_list|)
function_decl|;
name|void
name|gck_vector3_sub
parameter_list|(
name|GckVector3
modifier|*
name|c
parameter_list|,
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
function_decl|;
name|void
name|gck_vector3_set
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|double
name|z
parameter_list|)
function_decl|;
name|void
name|gck_vector3_add
parameter_list|(
name|GckVector3
modifier|*
name|c
parameter_list|,
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
function_decl|;
name|void
name|gck_vector3_neg
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|)
function_decl|;
name|void
name|gck_vector3_rotate
parameter_list|(
name|GckVector3
modifier|*
name|v
parameter_list|,
name|double
name|alpha
parameter_list|,
name|double
name|beta
parameter_list|,
name|double
name|gamma
parameter_list|)
function_decl|;
name|void
name|gck_2d_to_3d
parameter_list|(
name|int
name|sx
parameter_list|,
name|int
name|sy
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|GckVector3
modifier|*
name|vp
parameter_list|,
name|GckVector3
modifier|*
name|p
parameter_list|)
function_decl|;
name|void
name|gck_3d_to_2d
parameter_list|(
name|int
name|sx
parameter_list|,
name|int
name|sy
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|double
modifier|*
name|x
parameter_list|,
name|double
modifier|*
name|y
parameter_list|,
name|GckVector3
modifier|*
name|vp
parameter_list|,
name|GckVector3
modifier|*
name|p
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit


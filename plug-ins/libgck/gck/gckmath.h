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
comment|/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,   */
end_comment

begin_comment
comment|/* USA.                                                                    */
end_comment

begin_comment
comment|/***************************************************************************/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GCKMATH_H__
end_ifndef

begin_define
DECL|macro|__GCKMATH_H__
define|#
directive|define
name|__GCKMATH_H__
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
name|double
name|gck_deg_to_rad
parameter_list|(
name|double
name|angle
parameter_list|)
function_decl|;
name|double
name|gck_rad_to_deg
parameter_list|(
name|double
name|angle
parameter_list|)
function_decl|;
name|void
name|gck_mat_to_deg
parameter_list|(
name|double
name|mat
index|[
literal|4
index|]
index|[
literal|4
index|]
parameter_list|,
name|double
modifier|*
name|a
parameter_list|,
name|double
modifier|*
name|b
parameter_list|,
name|double
modifier|*
name|c
parameter_list|)
function_decl|;
name|int
name|gck_clip_line
parameter_list|(
name|double
modifier|*
name|x1
parameter_list|,
name|double
modifier|*
name|y1
parameter_list|,
name|double
modifier|*
name|x2
parameter_list|,
name|double
modifier|*
name|y2
parameter_list|,
name|double
name|minx
parameter_list|,
name|double
name|miny
parameter_list|,
name|double
name|maxx
parameter_list|,
name|double
name|maxy
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


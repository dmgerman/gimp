begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_FUNCS_UTILS_H__
end_ifndef

begin_define
DECL|macro|__PAINT_FUNCS_UTILS_H__
define|#
directive|define
name|__PAINT_FUNCS_UTILS_H__
end_define

begin_define
DECL|macro|INT_MULT (a,b,t)
define|#
directive|define
name|INT_MULT
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|t
parameter_list|)
value|((t) = (a) * (b) + 0x80, ((((t)>> 8) + (t))>> 8))
end_define

begin_comment
comment|/* This version of INT_MULT3 is very fast, but suffers from some    slight roundoff errors.  It returns the correct result 99.987    percent of the time */
end_comment

begin_define
DECL|macro|INT_MULT3 (a,b,c,t)
define|#
directive|define
name|INT_MULT3
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|t
parameter_list|)
value|((t) = (a) * (b) * (c) + 0x7F5B, \                             ((((t)>> 7) + (t))>> 16))
end_define

begin_comment
comment|/*   This version of INT_MULT3 always gives the correct result, but runs at   approximatly one third the speed. */
end_comment

begin_comment
comment|/*  #define INT_MULT3(a,b,c,t) (((a) * (b) * (c) + 32512) / 65025.0)  */
end_comment

begin_define
DECL|macro|INT_BLEND (a,b,alpha,tmp)
define|#
directive|define
name|INT_BLEND
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|alpha
parameter_list|,
name|tmp
parameter_list|)
value|(INT_MULT((a) - (b), alpha, tmp) + (b))
end_define

begin_comment
comment|/* A drawable has an alphachannel if contains either 4 or 2 bytes data  * aka GRAYA and RGBA and thus the macro below works. This will have  * to change if we support bigger formats. We'll do it so for now because  * masking is always cheaper than passing parameters over the stack.      */
end_comment

begin_comment
comment|/* FIXME: Move to a global place */
end_comment

begin_define
DECL|macro|HAS_ALPHA (bytes)
define|#
directive|define
name|HAS_ALPHA
parameter_list|(
name|bytes
parameter_list|)
value|(~bytes& 1)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_FUNCS_UTILS_H__  */
end_comment

end_unit


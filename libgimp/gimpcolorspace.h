begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPCOLORSPACE_H__
end_ifndef

begin_define
DECL|macro|__GIMPCOLORSPACE_H__
define|#
directive|define
name|__GIMPCOLORSPACE_H__
end_define

begin_comment
comment|/*  Color conversion routines  */
end_comment

begin_function_decl
name|void
name|gimp_rgb_to_hsv
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsv_to_rgb
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_hls
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimp_rgb_to_l
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hls_to_rgb
parameter_list|(
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_hsv_double
parameter_list|(
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsv_to_rgb_double
parameter_list|(
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgb_to_hsv4
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_hsv_to_rgb4
parameter_list|(
name|guchar
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Map RGB to intensity  */
end_comment

begin_define
DECL|macro|INTENSITY_RED
define|#
directive|define
name|INTENSITY_RED
value|0.30
end_define

begin_define
DECL|macro|INTENSITY_GREEN
define|#
directive|define
name|INTENSITY_GREEN
value|0.59
end_define

begin_define
DECL|macro|INTENSITY_BLUE
define|#
directive|define
name|INTENSITY_BLUE
value|0.11
end_define

begin_define
DECL|macro|INTENSITY (r,g,b)
define|#
directive|define
name|INTENSITY
parameter_list|(
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
value|((r) * INTENSITY_RED   + \ 			  (g) * INTENSITY_GREEN + \ 			  (b) * INTENSITY_BLUE  + 0.001)
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit


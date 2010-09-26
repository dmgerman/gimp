begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Colormap-Rotation plug-in. Exchanges two color ranges.  *  * Copyright (C) 1999 Sven Anders (anderss@fmi.uni-passau.de)  *                    Based on code from Pavel Grinfeld (pavel@ml.com)  *  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*----------------------------------------------------------------------------  * Change log:  *  * Version 2.0, 04 April 1999.  *  Nearly complete rewrite, made plug-in stable.  *  (Works with GIMP 1.1 and GTK+ 1.2)  *  * Version 1.0, 27 March 1997.  *  Initial (unstable) release by Pavel Grinfeld  *  *----------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Global defines */
end_comment

begin_define
DECL|macro|RADIUS
define|#
directive|define
name|RADIUS
value|60
end_define

begin_define
DECL|macro|MARGIN
define|#
directive|define
name|MARGIN
value|4
end_define

begin_define
DECL|macro|SUM
define|#
directive|define
name|SUM
value|(2*RADIUS + 2*MARGIN)
end_define

begin_define
DECL|macro|CENTER
define|#
directive|define
name|CENTER
value|(SUM/2)
end_define

begin_define
DECL|macro|GRAY_RADIUS
define|#
directive|define
name|GRAY_RADIUS
value|60
end_define

begin_define
DECL|macro|GRAY_MARGIN
define|#
directive|define
name|GRAY_MARGIN
value|3
end_define

begin_define
DECL|macro|GRAY_SUM
define|#
directive|define
name|GRAY_SUM
value|(2*GRAY_RADIUS + 2*GRAY_MARGIN)
end_define

begin_define
DECL|macro|GRAY_CENTER
define|#
directive|define
name|GRAY_CENTER
value|(GRAY_SUM/2)
end_define

begin_define
DECL|macro|LITTLE_RADIUS
define|#
directive|define
name|LITTLE_RADIUS
value|3
end_define

begin_define
DECL|macro|EACH_OR_BOTH
define|#
directive|define
name|EACH_OR_BOTH
value|0.3
end_define

begin_function_decl
name|void
name|color_rotate_draw_little_circle
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gfloat
name|hue
parameter_list|,
name|gfloat
name|satur
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_rotate_draw_large_circle
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gfloat
name|gray_sat
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_rotate_draw_arrows
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|RcmAngle
modifier|*
name|angle
parameter_list|)
function_decl|;
end_function_decl

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Colormap-Rotation plug-in. Exchanges two color ranges.  *  * Copyright (C) 1999 Sven Anders (anderss@fmi.uni-passau.de)  *                    Based on code from Pavel Grinfeld (pavel@ml.com)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*----------------------------------------------------------------------------  * Change log:  *  * Version 2.0, 04 April 1999.  *  Nearly complete rewrite, made plug-in stable.  *  (Works with GIMP 1.1 and GTK+ 1.2)  *  * Version 1.0, 27 March 1997.  *  Initial (unstable) release by Pavel Grinfeld  *  *----------------------------------------------------------------------------*/
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"rcm.h"
end_include

begin_include
include|#
directive|include
file|"rcm_misc.h"
end_include

begin_include
include|#
directive|include
file|"rcm_dialog.h"
end_include

begin_include
include|#
directive|include
file|"rcm_gdk.h"
end_include

begin_comment
comment|/* Global variables */
end_comment

begin_decl_stmt
DECL|variable|xor_gc
name|GdkGC
modifier|*
name|xor_gc
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Drawing routines */
end_comment

begin_function
name|void
DECL|function|rcm_draw_little_circle (GdkWindow * window,GdkGC * color,gfloat hue,gfloat satur)
name|rcm_draw_little_circle
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|color
parameter_list|,
name|gfloat
name|hue
parameter_list|,
name|gfloat
name|satur
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
name|GRAY_CENTER
operator|+
name|GRAY_RADIUS
operator|*
name|satur
operator|*
name|cos
argument_list|(
name|hue
argument_list|)
expr_stmt|;
name|y
operator|=
name|GRAY_CENTER
operator|-
name|GRAY_RADIUS
operator|*
name|satur
operator|*
name|sin
argument_list|(
name|hue
argument_list|)
expr_stmt|;
name|gdk_draw_arc
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
literal|0
argument_list|,
name|x
operator|-
name|LITTLE_RADIUS
argument_list|,
name|y
operator|-
name|LITTLE_RADIUS
argument_list|,
literal|2
operator|*
name|LITTLE_RADIUS
argument_list|,
literal|2
operator|*
name|LITTLE_RADIUS
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|rcm_draw_large_circle (GdkWindow * window,GdkGC * color,gfloat gray_sat)
name|rcm_draw_large_circle
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|color
parameter_list|,
name|gfloat
name|gray_sat
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
name|GRAY_CENTER
expr_stmt|;
name|y
operator|=
name|GRAY_CENTER
expr_stmt|;
name|gdk_draw_arc
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
literal|0
argument_list|,
name|ROUND
argument_list|(
name|x
operator|-
name|GRAY_RADIUS
operator|*
name|gray_sat
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|y
operator|-
name|GRAY_RADIUS
operator|*
name|gray_sat
argument_list|)
argument_list|,
name|ROUND
argument_list|(
literal|2
operator|*
name|GRAY_RADIUS
operator|*
name|gray_sat
argument_list|)
argument_list|,
name|ROUND
argument_list|(
literal|2
operator|*
name|GRAY_RADIUS
operator|*
name|gray_sat
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
block|}
end_function

begin_define
DECL|macro|REL
define|#
directive|define
name|REL
value|.8
end_define

begin_define
DECL|macro|DEL
define|#
directive|define
name|DEL
value|.1
end_define

begin_define
DECL|macro|TICK
define|#
directive|define
name|TICK
value|10
end_define

begin_function
name|void
DECL|function|rcm_draw_arrows (GdkWindow * window,GdkGC * color,RcmAngle * angle)
name|rcm_draw_arrows
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|color
parameter_list|,
name|RcmAngle
modifier|*
name|angle
parameter_list|)
block|{
name|gint
name|dist
decl_stmt|;
name|gfloat
name|alpha
decl_stmt|,
name|beta
decl_stmt|,
name|cw_ccw
decl_stmt|,
name|delta
decl_stmt|;
name|alpha
operator|=
name|angle
operator|->
name|alpha
expr_stmt|;
name|beta
operator|=
name|angle
operator|->
name|beta
expr_stmt|;
name|cw_ccw
operator|=
name|angle
operator|->
name|cw_ccw
expr_stmt|;
name|delta
operator|=
name|angle_mod_2PI
argument_list|(
name|beta
operator|-
name|alpha
argument_list|)
expr_stmt|;
if|if
condition|(
name|cw_ccw
operator|==
operator|-
literal|1
condition|)
name|delta
operator|=
name|delta
operator|-
name|TP
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
name|CENTER
argument_list|,
name|CENTER
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|+
name|RADIUS
operator|*
name|cos
argument_list|(
name|alpha
argument_list|)
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|-
name|RADIUS
operator|*
name|sin
argument_list|(
name|alpha
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
name|CENTER
operator|+
name|RADIUS
operator|*
name|cos
argument_list|(
name|alpha
argument_list|)
argument_list|,
name|CENTER
operator|-
name|RADIUS
operator|*
name|sin
argument_list|(
name|alpha
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|+
name|RADIUS
operator|*
name|REL
operator|*
name|cos
argument_list|(
name|alpha
operator|-
name|DEL
argument_list|)
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|-
name|RADIUS
operator|*
name|REL
operator|*
name|sin
argument_list|(
name|alpha
operator|-
name|DEL
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
name|CENTER
operator|+
name|RADIUS
operator|*
name|cos
argument_list|(
name|alpha
argument_list|)
argument_list|,
name|CENTER
operator|-
name|RADIUS
operator|*
name|sin
argument_list|(
name|alpha
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|+
name|RADIUS
operator|*
name|REL
operator|*
name|cos
argument_list|(
name|alpha
operator|+
name|DEL
argument_list|)
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|-
name|RADIUS
operator|*
name|REL
operator|*
name|sin
argument_list|(
name|alpha
operator|+
name|DEL
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
name|CENTER
argument_list|,
name|CENTER
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|+
name|RADIUS
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|-
name|RADIUS
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
name|CENTER
operator|+
name|RADIUS
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
argument_list|,
name|CENTER
operator|-
name|RADIUS
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|+
name|RADIUS
operator|*
name|REL
operator|*
name|cos
argument_list|(
name|beta
operator|-
name|DEL
argument_list|)
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|-
name|RADIUS
operator|*
name|REL
operator|*
name|sin
argument_list|(
name|beta
operator|-
name|DEL
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
name|CENTER
operator|+
name|RADIUS
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
argument_list|,
name|CENTER
operator|-
name|RADIUS
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|+
name|RADIUS
operator|*
name|REL
operator|*
name|cos
argument_list|(
name|beta
operator|+
name|DEL
argument_list|)
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|-
name|RADIUS
operator|*
name|REL
operator|*
name|sin
argument_list|(
name|beta
operator|+
name|DEL
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|dist
operator|=
name|RADIUS
operator|*
name|EACH_OR_BOTH
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
name|CENTER
operator|+
name|dist
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
argument_list|,
name|CENTER
operator|-
name|dist
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|+
name|dist
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
operator|+
name|cw_ccw
operator|*
name|TICK
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
argument_list|)
argument_list|,
name|ROUND
argument_list|(
name|CENTER
operator|-
name|dist
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
operator|+
name|cw_ccw
operator|*
name|TICK
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|alpha
operator|*=
literal|180
operator|*
literal|64
operator|/
name|G_PI
expr_stmt|;
name|delta
operator|*=
literal|180
operator|*
literal|64
operator|/
name|G_PI
expr_stmt|;
name|gdk_draw_arc
argument_list|(
name|window
argument_list|,
name|color
argument_list|,
literal|0
argument_list|,
name|CENTER
operator|-
name|dist
argument_list|,
name|CENTER
operator|-
name|dist
argument_list|,
literal|2
operator|*
name|dist
argument_list|,
literal|2
operator|*
name|dist
argument_list|,
name|alpha
argument_list|,
name|delta
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


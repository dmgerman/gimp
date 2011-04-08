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
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-rotate-colormap"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"rcm"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-rcm"
end_define

begin_define
DECL|macro|TP
define|#
directive|define
name|TP
value|(2*G_PI)
end_define

begin_comment
comment|/* Typedefs */
end_comment

begin_enum
DECL|enum|__anon27d3ac000103
DECL|enumerator|ENTIRE_IMAGE
DECL|enumerator|SELECTION
DECL|enumerator|SELECTION_IN_CONTEXT
DECL|enumerator|PREVIEW_OPTIONS
enum|enum
block|{
name|ENTIRE_IMAGE
block|,
name|SELECTION
block|,
name|SELECTION_IN_CONTEXT
block|,
name|PREVIEW_OPTIONS
block|}
enum|;
end_enum

begin_enum
DECL|enum|__anon27d3ac000203
DECL|enumerator|EACH
DECL|enumerator|BOTH
DECL|enumerator|DEGREES
DECL|enumerator|RADIANS
DECL|enumerator|RADIANS_OVER_PI
enum|enum
block|{
name|EACH
block|,
name|BOTH
block|,
name|DEGREES
block|,
name|RADIANS
block|,
name|RADIANS_OVER_PI
block|,
DECL|enumerator|GRAY_FROM
DECL|enumerator|GRAY_TO
DECL|enumerator|CURRENT
DECL|enumerator|ORIGINAL
name|GRAY_FROM
block|,
name|GRAY_TO
block|,
name|CURRENT
block|,
name|ORIGINAL
block|}
enum|;
end_enum

begin_typedef
DECL|enum|__anon27d3ac000303
DECL|enumerator|VIRGIN
DECL|enumerator|DRAG_START
DECL|enumerator|DRAGING
DECL|enumerator|DO_NOTHING
DECL|typedef|RcmOp
typedef|typedef
enum|enum
block|{
name|VIRGIN
block|,
name|DRAG_START
block|,
name|DRAGING
block|,
name|DO_NOTHING
block|}
name|RcmOp
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d3ac000408
block|{
DECL|member|alpha
name|gfloat
name|alpha
decl_stmt|;
DECL|member|beta
name|gfloat
name|beta
decl_stmt|;
DECL|member|cw_ccw
name|gint
name|cw_ccw
decl_stmt|;
DECL|typedef|RcmAngle
block|}
name|RcmAngle
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d3ac000508
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|rgb
name|guchar
modifier|*
name|rgb
decl_stmt|;
DECL|member|hsv
name|gdouble
modifier|*
name|hsv
decl_stmt|;
DECL|member|mask
name|guchar
modifier|*
name|mask
decl_stmt|;
DECL|typedef|ReducedImage
block|}
name|ReducedImage
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d3ac000608
block|{
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|cw_ccw_button
name|GtkWidget
modifier|*
name|cw_ccw_button
decl_stmt|;
DECL|member|cw_ccw_box
name|GtkWidget
modifier|*
name|cw_ccw_box
decl_stmt|;
DECL|member|cw_ccw_label
name|GtkWidget
modifier|*
name|cw_ccw_label
decl_stmt|;
DECL|member|cw_ccw_pixmap
name|GtkWidget
modifier|*
name|cw_ccw_pixmap
decl_stmt|;
DECL|member|a_b_button
name|GtkWidget
modifier|*
name|a_b_button
decl_stmt|;
DECL|member|a_b_box
name|GtkWidget
modifier|*
name|a_b_box
decl_stmt|;
DECL|member|a_b_pixmap
name|GtkWidget
modifier|*
name|a_b_pixmap
decl_stmt|;
DECL|member|f360_button
name|GtkWidget
modifier|*
name|f360_button
decl_stmt|;
DECL|member|f360_box
name|GtkWidget
modifier|*
name|f360_box
decl_stmt|;
DECL|member|f360_pixmap
name|GtkWidget
modifier|*
name|f360_pixmap
decl_stmt|;
DECL|member|alpha_entry
name|GtkWidget
modifier|*
name|alpha_entry
decl_stmt|;
DECL|member|alpha_units_label
name|GtkWidget
modifier|*
name|alpha_units_label
decl_stmt|;
DECL|member|beta_entry
name|GtkWidget
modifier|*
name|beta_entry
decl_stmt|;
DECL|member|beta_units_label
name|GtkWidget
modifier|*
name|beta_units_label
decl_stmt|;
DECL|member|target
name|gfloat
modifier|*
name|target
decl_stmt|;
DECL|member|mode
name|gint
name|mode
decl_stmt|;
DECL|member|angle
name|RcmAngle
modifier|*
name|angle
decl_stmt|;
DECL|member|prev_clicked
name|gfloat
name|prev_clicked
decl_stmt|;
DECL|typedef|RcmCircle
block|}
name|RcmCircle
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d3ac000708
block|{
DECL|member|dlg
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
DECL|member|bna_frame
name|GtkWidget
modifier|*
name|bna_frame
decl_stmt|;
DECL|member|before
name|GtkWidget
modifier|*
name|before
decl_stmt|;
DECL|member|after
name|GtkWidget
modifier|*
name|after
decl_stmt|;
DECL|typedef|RcmBna
block|}
name|RcmBna
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d3ac000808
block|{
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|gray_sat
name|gfloat
name|gray_sat
decl_stmt|;
DECL|member|hue
name|gfloat
name|hue
decl_stmt|;
DECL|member|satur
name|gfloat
name|satur
decl_stmt|;
DECL|member|hue_entry
name|GtkWidget
modifier|*
name|hue_entry
decl_stmt|;
DECL|member|hue_units_label
name|GtkWidget
modifier|*
name|hue_units_label
decl_stmt|;
DECL|member|satur_entry
name|GtkWidget
modifier|*
name|satur_entry
decl_stmt|;
DECL|member|action_flag
name|RcmOp
name|action_flag
decl_stmt|;
DECL|typedef|RcmGray
block|}
name|RcmGray
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d3ac000908
block|{
DECL|member|Slctn
name|gint
name|Slctn
decl_stmt|;
DECL|member|RealTime
name|gint
name|RealTime
decl_stmt|;
DECL|member|Units
name|gint
name|Units
decl_stmt|;
DECL|member|Gray_to_from
name|gint
name|Gray_to_from
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|mask
name|GimpDrawable
modifier|*
name|mask
decl_stmt|;
DECL|member|reduced
name|ReducedImage
modifier|*
name|reduced
decl_stmt|;
DECL|member|To
name|RcmCircle
modifier|*
name|To
decl_stmt|;
DECL|member|From
name|RcmCircle
modifier|*
name|From
decl_stmt|;
DECL|member|Gray
name|RcmGray
modifier|*
name|Gray
decl_stmt|;
DECL|member|Bna
name|RcmBna
modifier|*
name|Bna
decl_stmt|;
DECL|typedef|RcmParams
block|}
name|RcmParams
typedef|;
end_typedef

begin_comment
comment|/* Global variables */
end_comment

begin_decl_stmt
specifier|extern
name|RcmParams
name|Current
decl_stmt|;
end_decl_stmt

end_unit


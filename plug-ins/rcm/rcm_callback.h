begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Colormap-Rotation plug-in. Exchanges two color ranges.  *  * Copyright (C) 1999 Sven Anders (anderss@fmi.uni-passau.de)  *                    Based on code from Pavel Grinfeld (pavel@ml.com)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------  * Change log:  *   * Version 2.0, 04 April 1999.  *  Nearly complete rewrite, made plug-in stable.  *  (Works with GIMP 1.1 and GTK+ 1.2)  *  * Version 1.0, 27 March 1997.  *  Initial (unstable) release by Pavel Grinfeld  *  *---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Misc functions */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|float
name|rcm_units_factor
parameter_list|(
name|gint
name|units
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|rcm_units_string
parameter_list|(
name|gint
name|units
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_pixmap
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GtkWidget
modifier|*
name|label_box
parameter_list|,
name|char
modifier|*
modifier|*
name|pixmap_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Ok Button */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|void
name|rcm_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Circle buttons */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|void
name|rcm_360_degrees
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_cw_ccw
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_a_to_b
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Misc: units buttons */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|void
name|rcm_switch_to_degrees
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_switch_to_radians
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_switch_to_radians_over_PI
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Misc: Gray: mode buttons */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|void
name|rcm_switch_to_gray_to
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_switch_to_gray_from
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Misc: Preview buttons */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|void
name|rcm_preview_as_you_drag
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_selection_in_context
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_selection
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_entire_image
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Circle events */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|gint
name|rcm_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_motion_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Gray circle events */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|gint
name|rcm_gray_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_gray_button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_gray_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_gray_motion_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Spinbuttons */
end_comment

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|void
name|rcm_set_alpha
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_beta
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_hue
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_satur
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_gray_sat
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*---------------------------------------------------------------------------*/
end_comment

end_unit


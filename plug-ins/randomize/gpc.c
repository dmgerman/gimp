begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/****************************************************************************  * This is a convenience library for plugins for the GIMP v 0.99.8 or later.  * Documentation is available at http://www.rru.com/~meo/gimp/ .  *  * Copyright (C) 1997 Miles O'Neal<meo@rru.com>  http://www.rru.com/~meo/  * Blur code Copyright (C) 1995 Spencer Kimball and Peter Mattis  * GUI based on GTK code from:  *    alienmap (Copyright (C) 1996, 1997 Daniel Cotting)  *    plasma   (Copyright (C) 1996 Stephen Norris),  *    oilify   (Copyright (C) 1996 Torsten Martinsen),  *    ripple   (Copyright (C) 1997 Brian Degenhardt) and  *    whirl    (Copyright (C) 1997 Federico Mena Quintero).  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  ****************************************************************************/
end_comment

begin_comment
comment|/****************************************************************************  * gpc:  *  * gpc version 1.1 (3 Feb 1998, MEO)  * history  *     1.1 -  3 Feb 1998 MEO  *         removed tooltips from action buttons  *     1.0 -  2 Feb 1998 MEO  *         FCS  *  * Please send any patches or suggestions to the author: meo@rru.com .  *   ****************************************************************************/
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_comment
comment|/*  *  TOGGLE UPDATE callback  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gpc_toggle_update (GtkWidget * widget,gpointer data)
name|gpc_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|int
modifier|*
name|toggle_val
decl_stmt|;
name|toggle_val
operator|=
operator|(
name|int
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
operator|*
name|toggle_val
operator|=
name|TRUE
expr_stmt|;
else|else
operator|*
name|toggle_val
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  DESTROY callback  */
end_comment

begin_function
name|void
DECL|function|gpc_close_callback (GtkWidget * widget,gpointer data)
name|gpc_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  CANCEL BUTTON callback  */
end_comment

begin_function
name|void
DECL|function|gpc_cancel_callback (GtkWidget * widget,gpointer data)
name|gpc_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  SCALE UPDATE callback  */
end_comment

begin_function
name|void
DECL|function|gpc_scale_update (GtkAdjustment * adjustment,double * scale_val)
name|gpc_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|double
modifier|*
name|scale_val
parameter_list|)
block|{
operator|*
name|scale_val
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  TEXT UPDATE callback  */
end_comment

begin_function
name|void
DECL|function|gpc_text_update (GtkWidget * widget,gpointer data)
name|gpc_text_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
modifier|*
name|text_val
decl_stmt|;
name|text_val
operator|=
operator|(
name|gint
operator|*
operator|)
name|data
expr_stmt|;
operator|*
name|text_val
operator|=
name|atoi
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  TOOLTIPS ROUTINES  */
end_comment

begin_decl_stmt
DECL|variable|tips
specifier|static
name|GtkTooltips
modifier|*
name|tips
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gpc_setup_tooltips (GtkWidget * parent)
name|gpc_setup_tooltips
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
specifier|static
name|GdkColor
name|tips_fg
decl_stmt|,
name|tips_bg
decl_stmt|;
name|tips
operator|=
name|gtk_tooltips_new
argument_list|()
expr_stmt|;
comment|/* black as foreground: */
name|tips_fg
operator|.
name|red
operator|=
literal|0
expr_stmt|;
name|tips_fg
operator|.
name|green
operator|=
literal|0
expr_stmt|;
name|tips_fg
operator|.
name|blue
operator|=
literal|0
expr_stmt|;
name|gdk_color_alloc
argument_list|(
name|gtk_widget_get_colormap
argument_list|(
name|parent
argument_list|)
argument_list|,
operator|&
name|tips_fg
argument_list|)
expr_stmt|;
comment|/* postit yellow (khaki) as background: */
name|tips_bg
operator|.
name|red
operator|=
literal|61669
expr_stmt|;
name|tips_bg
operator|.
name|green
operator|=
literal|59113
expr_stmt|;
name|tips_bg
operator|.
name|blue
operator|=
literal|35979
expr_stmt|;
name|gdk_color_alloc
argument_list|(
name|gtk_widget_get_colormap
argument_list|(
name|parent
argument_list|)
argument_list|,
operator|&
name|tips_bg
argument_list|)
expr_stmt|;
name|gtk_tooltips_set_colors
argument_list|(
name|tips
argument_list|,
operator|&
name|tips_bg
argument_list|,
operator|&
name|tips_fg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gpc_set_tooltip (GtkWidget * widget,const char * tip)
name|gpc_set_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|char
modifier|*
name|tip
parameter_list|)
block|{
if|if
condition|(
name|tip
operator|&&
name|tip
index|[
literal|0
index|]
condition|)
name|gtk_tooltips_set_tip
argument_list|(
name|tips
argument_list|,
name|widget
argument_list|,
operator|(
name|char
operator|*
operator|)
name|tip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gpc_add_action_button (char * label,GtkSignalFunc callback,GtkWidget * dialog)
name|gpc_add_action_button
parameter_list|(
name|char
modifier|*
name|label
parameter_list|,
name|GtkSignalFunc
name|callback
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
comment|/* , char *tip */
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|callback
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
comment|/* gpc_set_tooltip(button, tip); */
block|}
end_function

begin_function
name|void
DECL|function|gpc_add_radio_button (GSList ** group,char * label,GtkWidget * box,gint * value,char * tip)
name|gpc_add_radio_button
parameter_list|(
name|GSList
modifier|*
modifier|*
name|group
parameter_list|,
name|char
modifier|*
name|label
parameter_list|,
name|GtkWidget
modifier|*
name|box
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|,
name|char
modifier|*
name|tip
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|toggle
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
operator|*
name|group
argument_list|,
name|label
argument_list|)
expr_stmt|;
operator|*
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gpc_toggle_update
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
operator|*
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|gpc_set_tooltip
argument_list|(
name|toggle
argument_list|,
name|tip
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gpc_add_label (char * value,GtkWidget * table,int left,int right,int top,int bottom)
name|gpc_add_label
parameter_list|(
name|char
modifier|*
name|value
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|int
name|left
parameter_list|,
name|int
name|right
parameter_list|,
name|int
name|top
parameter_list|,
name|int
name|bottom
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
name|left
argument_list|,
name|right
argument_list|,
name|top
argument_list|,
name|bottom
argument_list|,
name|GTK_FILL
operator||
name|GTK_EXPAND
argument_list|,
name|GTK_FILL
argument_list|,
literal|5
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gpc_add_hscale (GtkWidget * table,int width,float low,float high,gdouble * val,int left,int right,int top,int bottom,char * tip)
name|gpc_add_hscale
parameter_list|(
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|int
name|width
parameter_list|,
name|float
name|low
parameter_list|,
name|float
name|high
parameter_list|,
name|gdouble
modifier|*
name|val
parameter_list|,
name|int
name|left
parameter_list|,
name|int
name|right
parameter_list|,
name|int
name|top
parameter_list|,
name|int
name|bottom
parameter_list|,
name|char
modifier|*
name|tip
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkObject
modifier|*
name|scale_data
decl_stmt|;
name|scale_data
operator|=
name|gtk_adjustment_new
argument_list|(
operator|*
name|val
argument_list|,
name|low
argument_list|,
name|high
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|scale_data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|scale
argument_list|,
name|width
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|scale
argument_list|,
name|left
argument_list|,
name|right
argument_list|,
name|top
argument_list|,
name|bottom
argument_list|,
name|GTK_FILL
operator||
name|GTK_EXPAND
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|scale_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gpc_scale_update
argument_list|,
name|val
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|gpc_set_tooltip
argument_list|(
name|scale
argument_list|,
name|tip
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


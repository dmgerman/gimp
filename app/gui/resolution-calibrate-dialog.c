begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_ops.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"resolution_calibrate.h"
end_include

begin_include
include|#
directive|include
file|"unitrc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|SET_STYLE (widget,style)
define|#
directive|define
name|SET_STYLE
parameter_list|(
name|widget
parameter_list|,
name|style
parameter_list|)
value|if (style) gtk_widget_set_style (widget, style)
end_define

begin_decl_stmt
DECL|variable|calibrate_entry
specifier|static
name|GtkWidget
modifier|*
name|calibrate_entry
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|calibrate_xres
specifier|static
name|gdouble
name|calibrate_xres
init|=
literal|1.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|calibrate_yres
specifier|static
name|gdouble
name|calibrate_yres
init|=
literal|1.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ruler_width
specifier|static
name|gint
name|ruler_width
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ruler_height
specifier|static
name|gint
name|ruler_height
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|resolution_calibrate_ok (GtkWidget * button,gpointer data)
name|resolution_calibrate_ok
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|resolution_entry
decl_stmt|;
name|GtkWidget
modifier|*
name|chain_button
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|resolution_entry
operator|=
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|x
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|calibrate_entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|y
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|calibrate_entry
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|calibrate_xres
operator|=
operator|(
name|gdouble
operator|)
name|ruler_width
operator|*
name|calibrate_xres
operator|/
name|x
expr_stmt|;
name|calibrate_yres
operator|=
operator|(
name|gdouble
operator|)
name|ruler_height
operator|*
name|calibrate_yres
operator|/
name|y
expr_stmt|;
name|chain_button
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
literal|"chain_button"
argument_list|)
expr_stmt|;
if|if
condition|(
name|chain_button
operator|&&
name|ABS
argument_list|(
name|x
operator|-
name|y
argument_list|)
operator|>
name|GIMP_MIN_RESOLUTION
condition|)
name|gimp_chain_button_set_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|chain_button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|calibrate_xres
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
literal|1
argument_list|,
name|calibrate_yres
argument_list|)
expr_stmt|;
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
comment|/**  * resolution_calibrate_dialog:  * @resolution_entry: a GimpSizeEntry to connect the dialog to  * @dialog_style: a GtkStyle for the main dialog (used by the user_installation_dialog)  * @ruler_style: a GtkStyle for the rulers and the entry area (used by the   *               user_installation_dialog)  * @expose_callback: an "expose_event" handler used by the user_installation_dialog  *   * Displays a dialog that allows the user to interactively determine her monitor  * resolution. This dialog runs it's own GTK main loop and is connected to a   * GimpSizeEntry handling the resolution to be set. The style and callback parameters  * are supposed to be only used by the user_installation_dialog.  */
end_comment

begin_function
name|void
DECL|function|resolution_calibrate_dialog (GtkWidget * resolution_entry,GtkStyle * dialog_style,GtkStyle * ruler_style,GtkSignalFunc expose_callback)
name|resolution_calibrate_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|resolution_entry
parameter_list|,
name|GtkStyle
modifier|*
name|dialog_style
parameter_list|,
name|GtkStyle
modifier|*
name|ruler_style
parameter_list|,
name|GtkSignalFunc
name|expose_callback
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|ebox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|darea
decl_stmt|;
name|GtkWidget
modifier|*
name|ruler
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SIZE_ENTRY
argument_list|(
name|resolution_entry
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  this dialog can only exist once  */
if|if
condition|(
name|calibrate_entry
condition|)
return|return;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Calibrate Monitor Resolution"
argument_list|)
argument_list|,
literal|"calibrate_resolution"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|resolution_calibrate_ok
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|resolution_entry
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
literal|"unmap"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|SET_STYLE
argument_list|(
name|dialog
argument_list|,
name|dialog_style
argument_list|)
expr_stmt|;
name|gimp_dialog_set_icon
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|ruler_width
operator|=
name|gdk_screen_width
argument_list|()
expr_stmt|;
name|ruler_height
operator|=
name|gdk_screen_height
argument_list|()
expr_stmt|;
name|ruler_width
operator|=
name|ruler_width
operator|-
literal|300
operator|-
operator|(
name|ruler_width
operator|%
literal|100
operator|)
expr_stmt|;
name|ruler_height
operator|=
name|ruler_height
operator|-
literal|300
operator|-
operator|(
name|ruler_height
operator|%
literal|100
operator|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
argument_list|,
literal|4
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|ruler
operator|=
name|gtk_hruler_new
argument_list|()
expr_stmt|;
name|SET_STYLE
argument_list|(
name|ruler
argument_list|,
name|ruler_style
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|ruler
argument_list|,
name|ruler_width
argument_list|,
literal|32
argument_list|)
expr_stmt|;
name|gtk_ruler_set_range
argument_list|(
name|GTK_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0
argument_list|,
name|ruler_width
argument_list|,
literal|0
argument_list|,
name|ruler_width
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|ruler
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
name|ruler
operator|=
name|gtk_vruler_new
argument_list|()
expr_stmt|;
name|SET_STYLE
argument_list|(
name|ruler
argument_list|,
name|ruler_style
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|ruler
argument_list|,
literal|32
argument_list|,
name|ruler_height
argument_list|)
expr_stmt|;
name|gtk_ruler_set_range
argument_list|(
name|GTK_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0
argument_list|,
name|ruler_height
argument_list|,
literal|0
argument_list|,
name|ruler_height
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|ruler
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
name|ebox
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|SET_STYLE
argument_list|(
name|ebox
argument_list|,
name|ruler_style
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|ebox
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ebox
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ebox
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|darea
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|SET_STYLE
argument_list|(
name|darea
argument_list|,
name|dialog_style
argument_list|)
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|16
argument_list|,
literal|16
argument_list|)
expr_stmt|;
if|if
condition|(
name|expose_callback
condition|)
name|gtk_signal_connect_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|expose_callback
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|GTK_CORNER_TOP_LEFT
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|darea
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|darea
argument_list|)
expr_stmt|;
name|darea
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|SET_STYLE
argument_list|(
name|darea
argument_list|,
name|dialog_style
argument_list|)
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|16
argument_list|,
literal|16
argument_list|)
expr_stmt|;
if|if
condition|(
name|expose_callback
condition|)
name|gtk_signal_connect_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|expose_callback
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|GTK_CORNER_BOTTOM_LEFT
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|darea
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|darea
argument_list|)
expr_stmt|;
name|darea
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|SET_STYLE
argument_list|(
name|darea
argument_list|,
name|dialog_style
argument_list|)
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|16
argument_list|,
literal|16
argument_list|)
expr_stmt|;
if|if
condition|(
name|expose_callback
condition|)
name|gtk_signal_connect_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|expose_callback
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|GTK_CORNER_TOP_RIGHT
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|darea
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|darea
argument_list|)
expr_stmt|;
name|darea
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|SET_STYLE
argument_list|(
name|darea
argument_list|,
name|dialog_style
argument_list|)
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|16
argument_list|,
literal|16
argument_list|)
expr_stmt|;
if|if
condition|(
name|expose_callback
condition|)
name|gtk_signal_connect_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|darea
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|expose_callback
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|GTK_CORNER_BOTTOM_RIGHT
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|darea
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_SHRINK
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|darea
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|vbox
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Measure the rulers and enter their lengths below."
argument_list|)
argument_list|)
expr_stmt|;
name|SET_STYLE
argument_list|(
name|label
argument_list|,
name|ruler_style
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|calibrate_xres
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|calibrate_yres
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|calibrate_entry
operator|=
name|gimp_coordinates_new
argument_list|(
name|GIMP_UNIT_INCH
argument_list|,
literal|"%p"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|75
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Horizontal:"
argument_list|)
argument_list|,
name|ruler_width
argument_list|,
name|calibrate_xres
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Vertical:"
argument_list|)
argument_list|,
name|ruler_height
argument_list|,
name|calibrate_yres
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|GIMP_COORDINATES_CHAINBUTTON
argument_list|(
name|calibrate_entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|calibrate_entry
argument_list|)
expr_stmt|;
if|if
condition|(
name|ruler_style
condition|)
block|{
for|for
control|(
name|list
operator|=
name|GTK_TABLE
argument_list|(
name|calibrate_entry
argument_list|)
operator|->
name|children
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GtkTableChild
modifier|*
name|child
init|=
operator|(
name|GtkTableChild
operator|*
operator|)
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|child
operator|&&
name|GTK_IS_LABEL
argument_list|(
name|child
operator|->
name|widget
argument_list|)
condition|)
name|SET_STYLE
argument_list|(
name|GTK_WIDGET
argument_list|(
name|child
operator|->
name|widget
argument_list|)
argument_list|,
name|ruler_style
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|calibrate_entry
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|calibrate_entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
block|}
end_function

end_unit


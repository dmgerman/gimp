begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"resolution-calibrate-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

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

begin_comment
comment|/**  * resolution_calibrate_dialog:  * @resolution_entry: a #GimpSizeEntry to connect the dialog to  * @pixbuf:           an optional #GdkPixbuf for the upper left corner  *  * Displays a dialog that allows the user to interactively determine  * her monitor resolution. This dialog runs it's own GTK main loop and  * is connected to a #GimpSizeEntry handling the resolution to be set.  **/
end_comment

begin_function
name|void
DECL|function|resolution_calibrate_dialog (GtkWidget * resolution_entry,GdkPixbuf * pixbuf)
name|resolution_calibrate_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|resolution_entry
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
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
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|ruler
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|;
name|gint
name|monitor
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SIZE_ENTRY
argument_list|(
name|resolution_entry
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_WIDGET_REALIZED
argument_list|(
name|resolution_entry
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|pixbuf
operator|==
name|NULL
operator|||
name|GDK_IS_PIXBUF
argument_list|(
name|pixbuf
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
literal|"gimp-resolution-calibration"
argument_list|,
name|gtk_widget_get_toplevel
argument_list|(
name|resolution_entry
argument_list|)
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|monitor
operator|=
name|gdk_screen_get_monitor_at_window
argument_list|(
name|screen
argument_list|,
name|resolution_entry
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_screen_get_monitor_geometry
argument_list|(
name|screen
argument_list|,
name|monitor
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|ruler_width
operator|=
name|rect
operator|.
name|width
operator|-
literal|300
operator|-
operator|(
name|rect
operator|.
name|width
operator|%
literal|100
operator|)
expr_stmt|;
name|ruler_height
operator|=
name|rect
operator|.
name|height
operator|-
literal|300
operator|-
operator|(
name|rect
operator|.
name|height
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
literal|12
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
if|if
condition|(
name|pixbuf
condition|)
block|{
name|GtkWidget
modifier|*
name|image
init|=
name|gtk_image_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|image
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
literal|4
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|ruler
operator|=
name|gtk_hruler_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
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
name|gtk_widget_set_size_request
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_table_attach
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
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Measure the rulers and enter their lengths:"
argument_list|)
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
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_LARGE
argument_list|,
name|PANGO_ATTR_WEIGHT
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
operator|-
literal|1
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
literal|10
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"_Horizontal:"
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
literal|"_Vertical:"
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
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|calibrate_entry
argument_list|)
expr_stmt|;
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
switch|switch
condition|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|GTK_RESPONSE_OK
case|:
block|{
name|GtkWidget
modifier|*
name|chain_button
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
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
name|GIMP_COORDINATES_CHAINBUTTON
argument_list|(
name|resolution_entry
argument_list|)
expr_stmt|;
if|if
condition|(
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
block|}
default|default:
break|break;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


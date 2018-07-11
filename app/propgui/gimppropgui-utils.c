begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui-utils.c  * Copyright (C) 2002-2017  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"propgui-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_prop_kelvin_presets_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GtkMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_prop_kelvin_presets_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_prop_random_seed_new_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adj
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_kelvin_presets_new (GObject * config,const gchar * property_name)
name|gimp_prop_kelvin_presets_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|gint
name|i
decl_stmt|;
specifier|const
struct|struct
DECL|struct|__anon2a08b2180108
block|{
DECL|member|kelvin
name|gdouble
name|kelvin
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
block|}
name|kelvin_presets
index|[]
init|=
block|{
block|{
literal|1700
block|,
name|N_
argument_list|(
literal|"1,700 K â Match flame"
argument_list|)
block|}
block|,
block|{
literal|1850
block|,
name|N_
argument_list|(
literal|"1,850 K â Candle flame, sunset/sunrise"
argument_list|)
block|}
block|,
block|{
literal|2700
block|,
name|N_
argument_list|(
literal|"2,700 K - Soft (or warm) LED lamps"
argument_list|)
block|}
block|,
block|{
literal|3000
block|,
name|N_
argument_list|(
literal|"3,000 K â Soft (or warm) white compact fluorescent lamps"
argument_list|)
block|}
block|,
block|{
literal|3200
block|,
name|N_
argument_list|(
literal|"3,200 K â Studio lamps, photofloods, etc."
argument_list|)
block|}
block|,
block|{
literal|3300
block|,
name|N_
argument_list|(
literal|"3,300 K â Incandescent lamps"
argument_list|)
block|}
block|,
block|{
literal|3350
block|,
name|N_
argument_list|(
literal|"3,350 K â Studio \"CP\" light"
argument_list|)
block|}
block|,
block|{
literal|4000
block|,
name|N_
argument_list|(
literal|"4,000 K - Cold (daylight) LED lamps"
argument_list|)
block|}
block|,
block|{
literal|4100
block|,
name|N_
argument_list|(
literal|"4,100 K â Moonlight"
argument_list|)
block|}
block|,
block|{
literal|5000
block|,
name|N_
argument_list|(
literal|"5,000 K â D50"
argument_list|)
block|}
block|,
block|{
literal|5000
block|,
name|N_
argument_list|(
literal|"5,000 K â Cool white/daylight compact fluorescent lamps"
argument_list|)
block|}
block|,
block|{
literal|5000
block|,
name|N_
argument_list|(
literal|"5,000 K â Horizon daylight"
argument_list|)
block|}
block|,
block|{
literal|5500
block|,
name|N_
argument_list|(
literal|"5,500 K â D55"
argument_list|)
block|}
block|,
block|{
literal|5500
block|,
name|N_
argument_list|(
literal|"5,500 K â Vertical daylight, electronic flash"
argument_list|)
block|}
block|,
block|{
literal|6200
block|,
name|N_
argument_list|(
literal|"6,200 K â Xenon short-arc lamp"
argument_list|)
block|}
block|,
block|{
literal|6500
block|,
name|N_
argument_list|(
literal|"6,500 K â D65"
argument_list|)
block|}
block|,
block|{
literal|6500
block|,
name|N_
argument_list|(
literal|"6,500 K â Daylight, overcast"
argument_list|)
block|}
block|,
block|{
literal|7500
block|,
name|N_
argument_list|(
literal|"7,500 K â D75"
argument_list|)
block|}
block|,
block|{
literal|9300
block|,
name|N_
argument_list|(
literal|"9,300 K"
argument_list|)
block|}
block|}
struct|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_button_set_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|GTK_RELIEF_NONE
argument_list|)
expr_stmt|;
name|gtk_button_set_image
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_ICON_MENU_LEFT
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gtk_menu_new
argument_list|()
expr_stmt|;
name|gtk_menu_attach_to_widget
argument_list|(
name|GTK_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|button
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|_
argument_list|(
literal|"Choose from a list of common "
literal|"color temperatures"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"button-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_kelvin_presets_button_press
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|kelvin_presets
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|item
decl_stmt|;
name|gdouble
modifier|*
name|kelvin
decl_stmt|;
name|item
operator|=
name|gtk_menu_item_new_with_label
argument_list|(
name|gettext
argument_list|(
name|kelvin_presets
index|[
name|i
index|]
operator|.
name|label
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_menu_shell_append
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
literal|"property-name"
argument_list|,
name|g_strdup
argument_list|(
name|property_name
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|kelvin
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|1
argument_list|)
expr_stmt|;
operator|*
name|kelvin
operator|=
name|kelvin_presets
index|[
name|i
index|]
operator|.
name|kelvin
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
literal|"kelvin"
argument_list|,
name|kelvin
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|item
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_kelvin_presets_activate
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prop_random_seed_new (GObject * config,const gchar * property_name)
name|gimp_prop_random_seed_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|spin
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|spin
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spin
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spin
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"New Seed"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gtk_spin_button_get_adjustment
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spin
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prop_random_seed_new_clicked
argument_list|)
argument_list|,
name|adj
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_prop_kelvin_presets_button_press (GtkWidget * widget,GdkEventButton * bevent,GtkMenu * menu)
name|gimp_prop_kelvin_presets_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GtkMenu
modifier|*
name|menu
parameter_list|)
block|{
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
name|gtk_menu_popup_at_widget
argument_list|(
name|menu
argument_list|,
name|widget
argument_list|,
name|GDK_GRAVITY_WEST
argument_list|,
name|GDK_GRAVITY_NORTH_EAST
argument_list|,
operator|(
name|GdkEvent
operator|*
operator|)
name|bevent
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prop_kelvin_presets_activate (GtkWidget * widget,GObject * config)
name|gimp_prop_kelvin_presets_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|property_name
decl_stmt|;
name|gdouble
modifier|*
name|kelvin
decl_stmt|;
name|property_name
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"property-name"
argument_list|)
expr_stmt|;
name|kelvin
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"kelvin"
argument_list|)
expr_stmt|;
if|if
condition|(
name|property_name
operator|&&
name|kelvin
condition|)
name|g_object_set
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
operator|*
name|kelvin
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prop_random_seed_new_clicked (GtkButton * button,GtkAdjustment * adj)
name|gimp_prop_random_seed_new_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adj
parameter_list|)
block|{
name|guint32
name|value
decl_stmt|;
name|value
operator|=
name|floor
argument_list|(
name|g_random_double_range
argument_list|(
name|gtk_adjustment_get_lower
argument_list|(
name|adj
argument_list|)
argument_list|,
name|gtk_adjustment_get_upper
argument_list|(
name|adj
argument_list|)
operator|+
literal|1.0
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|adj
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


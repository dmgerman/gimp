begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Watercolor color_select_module, Raph Levien<raph@acm.org>, February 1998  *  * Ported to loadable color-selector, Sven Neumann<sven@gimp.org>, May 1999  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/* definitions and variables */
end_comment

begin_define
DECL|macro|IMAGE_SIZE
define|#
directive|define
name|IMAGE_SIZE
value|GIMP_COLOR_SELECTOR_SIZE
end_define

begin_define
DECL|macro|COLORSEL_TYPE_WATER
define|#
directive|define
name|COLORSEL_TYPE_WATER
value|(colorsel_water_type)
end_define

begin_define
DECL|macro|COLORSEL_WATER (obj)
define|#
directive|define
name|COLORSEL_WATER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), COLORSEL_TYPE_WATER, ColorselWater))
end_define

begin_define
DECL|macro|COLORSEL_WATER_CLASS (klass)
define|#
directive|define
name|COLORSEL_WATER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), COLORSEL_TYPE_WATER, ColorselWaterClass))
end_define

begin_define
DECL|macro|COLORSEL_IS_WATER (obj)
define|#
directive|define
name|COLORSEL_IS_WATER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), COLORSEL_TYPE_WATER))
end_define

begin_define
DECL|macro|COLORSEL_IS_WATER_CLASS (klass)
define|#
directive|define
name|COLORSEL_IS_WATER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), COLORSEL_TYPE_WATER))
end_define

begin_typedef
DECL|typedef|ColorselWater
typedef|typedef
name|struct
name|_ColorselWater
name|ColorselWater
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorselWaterClass
typedef|typedef
name|struct
name|_ColorselWaterClass
name|ColorselWaterClass
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorselWater
struct|struct
name|_ColorselWater
block|{
DECL|member|parent_instance
name|GimpColorSelector
name|parent_instance
decl_stmt|;
DECL|member|last_x
name|gdouble
name|last_x
decl_stmt|;
DECL|member|last_y
name|gdouble
name|last_y
decl_stmt|;
DECL|member|last_pressure
name|gdouble
name|last_pressure
decl_stmt|;
DECL|member|pressure_adjust
name|gfloat
name|pressure_adjust
decl_stmt|;
DECL|member|motion_time
name|guint32
name|motion_time
decl_stmt|;
DECL|member|button_state
name|gint
name|button_state
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ColorselWaterClass
struct|struct
name|_ColorselWaterClass
block|{
DECL|member|parent_class
name|GimpColorSelectorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|GType
name|colorsel_water_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_class_init
parameter_list|(
name|ColorselWaterClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_init
parameter_list|(
name|ColorselWater
modifier|*
name|water
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|select_area_draw
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|button_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|motion_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|proximity_out_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventProximity
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pressure_adjust_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|colorsel_water_info
specifier|static
specifier|const
name|GimpModuleInfo
name|colorsel_water_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Watercolor style color selector"
argument_list|)
block|,
literal|"Raph Levien<raph@acm.org>, Sven Neumann<sven@gimp.org>"
block|,
literal|"v0.3"
block|,
literal|"(c) 1998-1999, released under the GPL"
block|,
literal|"May, 10 1999"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|targets
specifier|static
specifier|const
name|GtkTargetEntry
name|targets
index|[]
init|=
block|{
block|{
literal|"application/x-color"
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|colorsel_water_type
specifier|static
name|GType
name|colorsel_water_type
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorSelectorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
DECL|function|gimp_module_query (GTypeModule * module)
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|colorsel_water_info
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|gboolean
DECL|function|gimp_module_register (GTypeModule * module)
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|colorsel_water_get_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|colorsel_water_get_type (GTypeModule * module)
name|colorsel_water_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
if|if
condition|(
operator|!
name|colorsel_water_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|select_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|ColorselWaterClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|colorsel_water_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|ColorselWater
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|colorsel_water_init
block|,       }
decl_stmt|;
name|colorsel_water_type
operator|=
name|g_type_module_register_type
argument_list|(
name|module
argument_list|,
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|,
literal|"ColorselWater"
argument_list|,
operator|&
name|select_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|colorsel_water_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_class_init (ColorselWaterClass * klass)
name|colorsel_water_class_init
parameter_list|(
name|ColorselWaterClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|colorsel_water_finalize
expr_stmt|;
name|selector_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"_Watercolor"
argument_list|)
expr_stmt|;
name|selector_class
operator|->
name|help_page
operator|=
literal|"watercolor.html"
expr_stmt|;
name|selector_class
operator|->
name|stock_id
operator|=
name|GIMP_STOCK_TOOL_PAINTBRUSH
expr_stmt|;
name|selector_class
operator|->
name|set_color
operator|=
name|colorsel_water_set_color
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_init (ColorselWater * water)
name|colorsel_water_init
parameter_list|(
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|event_box
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox2
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|water
operator|->
name|pressure_adjust
operator|=
literal|1.0
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
name|water
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|hbox2
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|hbox2
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* the event box */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox2
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|event_box
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|event_box
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|IMAGE_SIZE
argument_list|,
name|IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|event_box
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|select_area_draw
argument_list|(
name|preview
argument_list|)
expr_stmt|;
comment|/* Event signals */
name|g_signal_connect
argument_list|(
name|event_box
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|motion_notify_event
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|event_box
argument_list|,
literal|"button_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|button_press_event
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|event_box
argument_list|,
literal|"button_release_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|button_release_event
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|event_box
argument_list|,
literal|"proximity_out_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|proximity_out_event
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|event_box
argument_list|,
name|GDK_EXPOSURE_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
operator||
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_KEY_PRESS_MASK
operator||
name|GDK_POINTER_MOTION_MASK
operator||
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_PROXIMITY_OUT_MASK
argument_list|)
expr_stmt|;
comment|/* The following call enables tracking and processing of extension    * events for the drawing area    */
name|gtk_widget_set_extension_events
argument_list|(
name|event_box
argument_list|,
name|GDK_EXTENSION_EVENTS_ALL
argument_list|)
expr_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|event_box
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gtk_adjustment_new
argument_list|(
literal|200.0
operator|-
name|water
operator|->
name|pressure_adjust
operator|*
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|200.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|pressure_adjust_update
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_vscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adj
argument_list|)
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
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|scale
argument_list|,
name|_
argument_list|(
literal|"Pressure"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox2
argument_list|)
argument_list|,
name|scale
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show_all
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_finalize (GObject * object)
name|colorsel_water_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|water
decl_stmt|;
name|water
operator|=
name|COLORSEL_WATER
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_set_color (GimpColorSelector * selector,const GimpRGB * rgb,const GimpHSV * hsv)
name|colorsel_water_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|water
decl_stmt|;
name|water
operator|=
name|COLORSEL_WATER
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|calc (gdouble x,gdouble y,gdouble angle)
name|calc
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|gdouble
name|s
decl_stmt|,
name|c
decl_stmt|;
name|s
operator|=
literal|1.6
operator|*
name|sin
argument_list|(
name|angle
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
operator|*
literal|256.0
operator|/
name|IMAGE_SIZE
expr_stmt|;
name|c
operator|=
literal|1.6
operator|*
name|cos
argument_list|(
name|angle
operator|*
name|G_PI
operator|/
literal|180
argument_list|)
operator|*
literal|256.0
operator|/
name|IMAGE_SIZE
expr_stmt|;
return|return
literal|128
operator|+
operator|(
name|x
operator|-
operator|(
name|IMAGE_SIZE
operator|>>
literal|1
operator|)
operator|)
operator|*
name|c
operator|-
operator|(
name|y
operator|-
operator|(
name|IMAGE_SIZE
operator|>>
literal|1
operator|)
operator|)
operator|*
name|s
return|;
block|}
end_function

begin_comment
comment|/* Initialize the preview */
end_comment

begin_function
specifier|static
name|void
DECL|function|select_area_draw (GtkWidget * preview)
name|select_area_draw
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
name|guchar
name|buf
index|[
literal|3
operator|*
name|IMAGE_SIZE
index|]
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gdouble
name|dr
decl_stmt|,
name|dg
decl_stmt|,
name|db
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|IMAGE_SIZE
condition|;
name|y
operator|++
control|)
block|{
name|r
operator|=
name|calc
argument_list|(
literal|0
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g
operator|=
name|calc
argument_list|(
literal|0
argument_list|,
name|y
argument_list|,
literal|120
argument_list|)
expr_stmt|;
name|b
operator|=
name|calc
argument_list|(
literal|0
argument_list|,
name|y
argument_list|,
literal|240
argument_list|)
expr_stmt|;
name|dr
operator|=
name|calc
argument_list|(
literal|1
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
operator|-
name|r
expr_stmt|;
name|dg
operator|=
name|calc
argument_list|(
literal|1
argument_list|,
name|y
argument_list|,
literal|120
argument_list|)
operator|-
name|g
expr_stmt|;
name|db
operator|=
name|calc
argument_list|(
literal|1
argument_list|,
name|y
argument_list|,
literal|240
argument_list|)
operator|-
name|b
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|IMAGE_SIZE
condition|;
name|x
operator|++
control|)
block|{
name|buf
index|[
name|x
operator|*
literal|3
index|]
operator|=
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|r
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|g
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|buf
index|[
name|x
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|b
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|r
operator|+=
name|dr
expr_stmt|;
name|g
operator|+=
name|dg
expr_stmt|;
name|b
operator|+=
name|db
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|IMAGE_SIZE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_pigment (ColorselWater * water,gboolean erase,gdouble x,gdouble y,gdouble much)
name|add_pigment
parameter_list|(
name|ColorselWater
modifier|*
name|water
parameter_list|,
name|gboolean
name|erase
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|much
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
decl_stmt|;
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|selector
operator|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|water
argument_list|)
expr_stmt|;
name|much
operator|*=
operator|(
name|gdouble
operator|)
name|water
operator|->
name|pressure_adjust
expr_stmt|;
if|if
condition|(
name|erase
condition|)
block|{
name|selector
operator|->
name|rgb
operator|.
name|r
operator|=
literal|1
operator|-
operator|(
literal|1
operator|-
name|selector
operator|->
name|rgb
operator|.
name|r
operator|)
operator|*
operator|(
literal|1
operator|-
name|much
operator|)
expr_stmt|;
name|selector
operator|->
name|rgb
operator|.
name|g
operator|=
literal|1
operator|-
operator|(
literal|1
operator|-
name|selector
operator|->
name|rgb
operator|.
name|g
operator|)
operator|*
operator|(
literal|1
operator|-
name|much
operator|)
expr_stmt|;
name|selector
operator|->
name|rgb
operator|.
name|b
operator|=
literal|1
operator|-
operator|(
literal|1
operator|-
name|selector
operator|->
name|rgb
operator|.
name|b
operator|)
operator|*
operator|(
literal|1
operator|-
name|much
operator|)
expr_stmt|;
block|}
else|else
block|{
name|r
operator|=
name|calc
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
operator|/
literal|255.0
expr_stmt|;
if|if
condition|(
name|r
operator|<
literal|0
condition|)
name|r
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|r
operator|>
literal|1
condition|)
name|r
operator|=
literal|1
expr_stmt|;
name|g
operator|=
name|calc
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|120
argument_list|)
operator|/
literal|255.0
expr_stmt|;
if|if
condition|(
name|g
operator|<
literal|0
condition|)
name|g
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|g
operator|>
literal|1
condition|)
name|g
operator|=
literal|1
expr_stmt|;
name|b
operator|=
name|calc
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|240
argument_list|)
operator|/
literal|255.0
expr_stmt|;
if|if
condition|(
name|b
operator|<
literal|0
condition|)
name|b
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|b
operator|>
literal|1
condition|)
name|b
operator|=
literal|1
expr_stmt|;
name|selector
operator|->
name|rgb
operator|.
name|r
operator|*=
operator|(
literal|1
operator|-
operator|(
literal|1
operator|-
name|r
operator|)
operator|*
name|much
operator|)
expr_stmt|;
name|selector
operator|->
name|rgb
operator|.
name|g
operator|*=
operator|(
literal|1
operator|-
operator|(
literal|1
operator|-
name|g
operator|)
operator|*
name|much
operator|)
expr_stmt|;
name|selector
operator|->
name|rgb
operator|.
name|b
operator|*=
operator|(
literal|1
operator|-
operator|(
literal|1
operator|-
name|b
operator|)
operator|*
name|much
operator|)
expr_stmt|;
block|}
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|gimp_color_selector_color_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_brush (ColorselWater * water,GtkWidget * widget,gboolean erase,gdouble x,gdouble y,gdouble pressure)
name|draw_brush
parameter_list|(
name|ColorselWater
modifier|*
name|water
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|erase
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|pressure
parameter_list|)
block|{
name|gdouble
name|much
decl_stmt|;
comment|/* how much pigment to mix in */
if|if
condition|(
name|pressure
operator|<
name|water
operator|->
name|last_pressure
condition|)
name|water
operator|->
name|last_pressure
operator|=
name|pressure
expr_stmt|;
name|much
operator|=
name|sqrt
argument_list|(
operator|(
name|x
operator|-
name|water
operator|->
name|last_x
operator|)
operator|*
operator|(
name|x
operator|-
name|water
operator|->
name|last_x
operator|)
operator|+
operator|(
name|y
operator|-
name|water
operator|->
name|last_y
operator|)
operator|*
operator|(
name|y
operator|-
name|water
operator|->
name|last_y
operator|)
operator|+
literal|1000
operator|*
operator|(
name|pressure
operator|-
name|water
operator|->
name|last_pressure
operator|)
operator|*
operator|(
name|pressure
operator|-
name|water
operator|->
name|last_pressure
operator|)
argument_list|)
expr_stmt|;
name|much
operator|*=
name|pressure
operator|*
literal|0.05
expr_stmt|;
name|add_pigment
argument_list|(
name|water
argument_list|,
name|erase
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|much
argument_list|)
expr_stmt|;
name|water
operator|->
name|last_x
operator|=
name|x
expr_stmt|;
name|water
operator|->
name|last_y
operator|=
name|y
expr_stmt|;
name|water
operator|->
name|last_pressure
operator|=
name|pressure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|button_press_event (GtkWidget * widget,GdkEventButton * event,ColorselWater * water)
name|button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
name|gboolean
name|erase
init|=
name|FALSE
decl_stmt|;
name|water
operator|->
name|last_x
operator|=
name|event
operator|->
name|x
expr_stmt|;
name|water
operator|->
name|last_y
operator|=
name|event
operator|->
name|y
expr_stmt|;
name|water
operator|->
name|last_pressure
operator|=
literal|0.5
expr_stmt|;
name|gdk_event_get_axis
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|event
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
operator|&
name|water
operator|->
name|last_pressure
argument_list|)
expr_stmt|;
name|water
operator|->
name|button_state
operator||=
literal|1
operator|<<
name|event
operator|->
name|button
expr_stmt|;
name|erase
operator|=
operator|(
name|event
operator|->
name|button
operator|!=
literal|1
operator|)
operator|||
name|FALSE
expr_stmt|;
comment|/* FIXME: (event->source == GDK_SOURCE_ERASER) */
name|add_pigment
argument_list|(
name|water
argument_list|,
name|erase
argument_list|,
name|event
operator|->
name|x
argument_list|,
name|event
operator|->
name|y
argument_list|,
literal|0.05
argument_list|)
expr_stmt|;
name|water
operator|->
name|motion_time
operator|=
name|event
operator|->
name|time
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|button_release_event (GtkWidget * widget,GdkEventButton * event,ColorselWater * water)
name|button_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
name|water
operator|->
name|button_state
operator|&=
operator|~
operator|(
literal|1
operator|<<
name|event
operator|->
name|button
operator|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|motion_notify_event (GtkWidget * widget,GdkEventMotion * event,ColorselWater * water)
name|motion_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
name|GdkTimeCoord
modifier|*
modifier|*
name|coords
decl_stmt|;
name|gint
name|nevents
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gboolean
name|erase
decl_stmt|;
if|if
condition|(
name|event
operator|->
name|state
operator|&
operator|(
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
operator||
name|GDK_BUTTON3_MASK
operator||
name|GDK_BUTTON4_MASK
operator|)
condition|)
block|{
name|guint32
name|last_motion_time
decl_stmt|;
name|last_motion_time
operator|=
name|event
operator|->
name|time
expr_stmt|;
name|erase
operator|=
operator|(
operator|(
name|event
operator|->
name|state
operator|&
operator|(
name|GDK_BUTTON2_MASK
operator||
name|GDK_BUTTON3_MASK
operator||
name|GDK_BUTTON4_MASK
operator|)
operator|)
operator|||
name|FALSE
operator|)
expr_stmt|;
comment|/* FIXME: (event->source == GDK_SOURCE_ERASER) */
name|water
operator|->
name|motion_time
operator|=
name|event
operator|->
name|time
expr_stmt|;
if|if
condition|(
name|gdk_device_get_history
argument_list|(
name|event
operator|->
name|device
argument_list|,
name|event
operator|->
name|window
argument_list|,
name|last_motion_time
argument_list|,
name|event
operator|->
name|time
argument_list|,
operator|&
name|coords
argument_list|,
operator|&
name|nevents
argument_list|)
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nevents
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|y
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|pressure
init|=
literal|0.5
decl_stmt|;
name|gdk_device_get_axis
argument_list|(
name|event
operator|->
name|device
argument_list|,
name|coords
index|[
name|i
index|]
operator|->
name|axes
argument_list|,
name|GDK_AXIS_X
argument_list|,
operator|&
name|x
argument_list|)
expr_stmt|;
name|gdk_device_get_axis
argument_list|(
name|event
operator|->
name|device
argument_list|,
name|coords
index|[
name|i
index|]
operator|->
name|axes
argument_list|,
name|GDK_AXIS_Y
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|gdk_device_get_axis
argument_list|(
name|event
operator|->
name|device
argument_list|,
name|coords
index|[
name|i
index|]
operator|->
name|axes
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
operator|&
name|pressure
argument_list|)
expr_stmt|;
name|draw_brush
argument_list|(
name|water
argument_list|,
name|widget
argument_list|,
name|erase
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|pressure
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|coords
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|pressure
init|=
literal|0.5
decl_stmt|;
name|gdk_event_get_axis
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|event
argument_list|,
name|GDK_AXIS_PRESSURE
argument_list|,
operator|&
name|pressure
argument_list|)
expr_stmt|;
name|draw_brush
argument_list|(
name|water
argument_list|,
name|widget
argument_list|,
name|erase
argument_list|,
name|event
operator|->
name|x
argument_list|,
name|event
operator|->
name|y
argument_list|,
name|pressure
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|event
operator|->
name|is_hint
condition|)
name|gdk_device_get_state
argument_list|(
name|event
operator|->
name|device
argument_list|,
name|event
operator|->
name|window
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|proximity_out_event (GtkWidget * widget,GdkEventProximity * event,ColorselWater * water)
name|proximity_out_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventProximity
modifier|*
name|event
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pressure_adjust_update (GtkAdjustment * adj,ColorselWater * water)
name|pressure_adjust_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
name|water
operator|->
name|pressure_adjust
operator|=
operator|(
name|adj
operator|->
name|upper
operator|-
name|adj
operator|->
name|value
operator|)
operator|/
literal|100.0
expr_stmt|;
block|}
end_function

end_unit


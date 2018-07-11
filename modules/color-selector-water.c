begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Watercolor color_select_module, Raph Levien<raph@acm.org>, February 1998  *  * Ported to loadable color-selector, Sven Neumann<sven@gimp.org>, May 1999  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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

begin_define
DECL|macro|COLORSEL_TYPE_WATER
define|#
directive|define
name|COLORSEL_TYPE_WATER
value|(colorsel_water_get_type ())
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
DECL|member|area
name|GtkWidget
modifier|*
name|area
decl_stmt|;
DECL|member|last_x
name|gdouble
name|last_x
decl_stmt|;
DECL|member|last_y
name|gdouble
name|last_y
decl_stmt|;
DECL|member|pressure_adjust
name|gfloat
name|pressure_adjust
decl_stmt|;
DECL|member|motion_time
name|guint32
name|motion_time
decl_stmt|;
DECL|member|config
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
DECL|member|transform
name|GimpColorTransform
modifier|*
name|transform
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
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_dispose
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
name|colorsel_water_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_create_transform
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
name|colorsel_water_destroy_transform
parameter_list|(
name|ColorselWater
modifier|*
name|water
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|select_area_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
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
literal|"v0.4"
block|,
literal|"released under the GPL"
block|,
literal|"1998-2006"
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_DYNAMIC_TYPE (ColorselWater,colorsel_water,GIMP_TYPE_COLOR_SELECTOR)
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|ColorselWater
argument_list|,
argument|colorsel_water
argument_list|,
argument|GIMP_TYPE_COLOR_SELECTOR
argument_list|)
end_macro

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
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
name|colorsel_water_register_type
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
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpColorSelectorClass
modifier|*
name|selector_class
init|=
name|GIMP_COLOR_SELECTOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|colorsel_water_dispose
expr_stmt|;
name|selector_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Watercolor"
argument_list|)
expr_stmt|;
name|selector_class
operator|->
name|help_id
operator|=
literal|"gimp-colorselector-watercolor"
expr_stmt|;
name|selector_class
operator|->
name|icon_name
operator|=
name|GIMP_ICON_COLOR_SELECTOR_WATER
expr_stmt|;
name|selector_class
operator|->
name|set_config
operator|=
name|colorsel_water_set_config
expr_stmt|;
name|gtk_widget_class_set_css_name
argument_list|(
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
literal|"ColorselWater"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_class_finalize (ColorselWaterClass * klass)
name|colorsel_water_class_finalize
parameter_list|(
name|ColorselWaterClass
modifier|*
name|klass
parameter_list|)
block|{ }
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
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|colorsel_water_get_type
argument_list|()
expr_stmt|;
comment|/* useless function call to silence compiler */
name|water
operator|->
name|pressure_adjust
operator|=
literal|1.0
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|2
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
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
name|hbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|water
operator|->
name|area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|water
operator|->
name|area
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|water
operator|->
name|area
argument_list|,
literal|"draw"
argument_list|,
name|G_CALLBACK
argument_list|(
name|select_area_draw
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
comment|/* Event signals */
name|g_signal_connect
argument_list|(
name|water
operator|->
name|area
argument_list|,
literal|"motion-notify-event"
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
name|water
operator|->
name|area
argument_list|,
literal|"button-press-event"
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
name|water
operator|->
name|area
argument_list|,
literal|"proximity-out-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|proximity_out_event
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|water
operator|->
name|area
argument_list|,
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
name|gtk_widget_grab_focus
argument_list|(
name|water
operator|->
name|area
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
literal|"value-changed"
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
name|gtk_scale_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
name|adj
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
name|hbox
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
name|gimp_widget_track_monitor
argument_list|(
name|GTK_WIDGET
argument_list|(
name|water
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorsel_water_destroy_transform
argument_list|)
argument_list|,
name|NULL
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
init|=
literal|2.0
operator|*
name|sin
argument_list|(
name|angle
operator|*
name|G_PI
operator|/
literal|180.0
argument_list|)
operator|*
literal|256.0
decl_stmt|;
name|gdouble
name|c
init|=
literal|2.0
operator|*
name|cos
argument_list|(
name|angle
operator|*
name|G_PI
operator|/
literal|180.0
argument_list|)
operator|*
literal|256.0
decl_stmt|;
return|return
literal|128
operator|+
operator|(
name|x
operator|-
literal|0.5
operator|)
operator|*
name|c
operator|-
operator|(
name|y
operator|-
literal|0.5
operator|)
operator|*
name|s
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_dispose (GObject * object)
name|colorsel_water_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|colorsel_water_set_config
argument_list|(
name|GIMP_COLOR_SELECTOR
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|colorsel_water_parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_set_config (GimpColorSelector * selector,GimpColorConfig * config)
name|colorsel_water_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|water
init|=
name|COLORSEL_WATER
argument_list|(
name|selector
argument_list|)
decl_stmt|;
if|if
condition|(
name|config
operator|!=
name|water
operator|->
name|config
condition|)
block|{
if|if
condition|(
name|water
operator|->
name|config
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|water
operator|->
name|config
argument_list|,
name|colorsel_water_destroy_transform
argument_list|,
name|water
argument_list|)
expr_stmt|;
name|colorsel_water_destroy_transform
argument_list|(
name|water
argument_list|)
expr_stmt|;
block|}
name|g_set_object
argument_list|(
operator|&
name|water
operator|->
name|config
argument_list|,
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
name|water
operator|->
name|config
condition|)
block|{
name|g_signal_connect_swapped
argument_list|(
name|water
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorsel_water_destroy_transform
argument_list|)
argument_list|,
name|water
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_create_transform (ColorselWater * water)
name|colorsel_water_create_transform
parameter_list|(
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
if|if
condition|(
name|water
operator|->
name|config
condition|)
block|{
specifier|static
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
init|=
name|babl_format
argument_list|(
literal|"cairo-RGB24"
argument_list|)
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|profile
argument_list|)
condition|)
name|profile
operator|=
name|gimp_color_profile_new_rgb_srgb
argument_list|()
expr_stmt|;
name|water
operator|->
name|transform
operator|=
name|gimp_widget_get_color_transform
argument_list|(
name|water
operator|->
name|area
argument_list|,
name|water
operator|->
name|config
argument_list|,
name|profile
argument_list|,
name|format
argument_list|,
name|format
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_destroy_transform (ColorselWater * water)
name|colorsel_water_destroy_transform
parameter_list|(
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
if|if
condition|(
name|water
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|water
operator|->
name|transform
argument_list|)
expr_stmt|;
name|water
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|water
operator|->
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|select_area_draw (GtkWidget * widget,cairo_t * cr,ColorselWater * water)
name|select_area_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|ColorselWater
modifier|*
name|water
parameter_list|)
block|{
name|GdkRectangle
name|area
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gdouble
name|dx
decl_stmt|;
name|gdouble
name|dy
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|cairo_clip_extents
argument_list|(
name|cr
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|area
operator|.
name|x
operator|=
name|floor
argument_list|(
name|x1
argument_list|)
expr_stmt|;
name|area
operator|.
name|y
operator|=
name|floor
argument_list|(
name|y1
argument_list|)
expr_stmt|;
name|area
operator|.
name|width
operator|=
name|ceil
argument_list|(
name|x2
argument_list|)
operator|-
name|area
operator|.
name|x
expr_stmt|;
name|area
operator|.
name|height
operator|=
name|ceil
argument_list|(
name|y2
argument_list|)
operator|-
name|area
operator|.
name|y
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|dx
operator|=
literal|1.0
operator|/
name|allocation
operator|.
name|width
expr_stmt|;
name|dy
operator|=
literal|1.0
operator|/
name|allocation
operator|.
name|height
expr_stmt|;
name|surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_RGB24
argument_list|,
name|area
operator|.
name|width
argument_list|,
name|area
operator|.
name|height
argument_list|)
expr_stmt|;
name|dest
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|surface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|water
operator|->
name|transform
condition|)
name|colorsel_water_create_transform
argument_list|(
name|water
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
operator|,
name|y
operator|=
name|area
operator|.
name|y
operator|/
name|allocation
operator|.
name|height
init|;
name|j
operator|<
name|area
operator|.
name|height
condition|;
name|j
operator|++
operator|,
name|y
operator|+=
name|dy
control|)
block|{
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gdouble
name|r
init|=
name|calc
argument_list|(
literal|0
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gdouble
name|g
init|=
name|calc
argument_list|(
literal|0
argument_list|,
name|y
argument_list|,
literal|120
argument_list|)
decl_stmt|;
name|gdouble
name|b
init|=
name|calc
argument_list|(
literal|0
argument_list|,
name|y
argument_list|,
literal|240
argument_list|)
decl_stmt|;
name|gdouble
name|dr
init|=
name|calc
argument_list|(
name|dx
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
operator|-
name|r
decl_stmt|;
name|gdouble
name|dg
init|=
name|calc
argument_list|(
name|dx
argument_list|,
name|y
argument_list|,
literal|120
argument_list|)
operator|-
name|g
decl_stmt|;
name|gdouble
name|db
init|=
name|calc
argument_list|(
name|dx
argument_list|,
name|y
argument_list|,
literal|240
argument_list|)
operator|-
name|b
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|r
operator|+=
name|area
operator|.
name|x
operator|*
name|dr
expr_stmt|;
name|g
operator|+=
name|area
operator|.
name|x
operator|*
name|dg
expr_stmt|;
name|b
operator|+=
name|area
operator|.
name|x
operator|*
name|db
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|area
operator|.
name|width
condition|;
name|i
operator|++
control|)
block|{
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
name|d
argument_list|,
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
argument_list|,
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
argument_list|,
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
name|d
operator|+=
literal|4
expr_stmt|;
block|}
if|if
condition|(
name|water
operator|->
name|transform
condition|)
name|gimp_color_transform_process_pixels
argument_list|(
name|water
operator|->
name|transform
argument_list|,
name|babl_format
argument_list|(
literal|"cairo-RGB24"
argument_list|)
argument_list|,
name|dest
argument_list|,
name|babl_format
argument_list|(
literal|"cairo-RGB24"
argument_list|)
argument_list|,
name|dest
argument_list|,
name|area
operator|.
name|width
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|cairo_image_surface_get_stride
argument_list|(
name|surface
argument_list|)
expr_stmt|;
block|}
name|cairo_surface_mark_dirty
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|surface
argument_list|,
name|area
operator|.
name|x
argument_list|,
name|area
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
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
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|water
argument_list|)
decl_stmt|;
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
literal|1.0
operator|-
operator|(
literal|1.0
operator|-
name|selector
operator|->
name|rgb
operator|.
name|r
operator|)
operator|*
operator|(
literal|1.0
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
literal|1.0
operator|-
operator|(
literal|1.0
operator|-
name|selector
operator|->
name|rgb
operator|.
name|g
operator|)
operator|*
operator|(
literal|1.0
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
literal|1.0
operator|-
operator|(
literal|1.0
operator|-
name|selector
operator|->
name|rgb
operator|.
name|b
operator|)
operator|*
operator|(
literal|1.0
operator|-
name|much
operator|)
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|r
init|=
name|calc
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
operator|/
literal|256.0
decl_stmt|;
name|gdouble
name|g
init|=
name|calc
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|120
argument_list|)
operator|/
literal|256.0
decl_stmt|;
name|gdouble
name|b
init|=
name|calc
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|240
argument_list|)
operator|/
literal|256.0
decl_stmt|;
name|selector
operator|->
name|rgb
operator|.
name|r
operator|*=
operator|(
literal|1.0
operator|-
operator|(
literal|1.0
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
literal|1.0
operator|-
operator|(
literal|1.0
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
literal|1.0
operator|-
operator|(
literal|1.0
operator|-
name|b
operator|)
operator|*
name|much
operator|)
expr_stmt|;
block|}
name|gimp_rgb_clamp
argument_list|(
operator|&
name|selector
operator|->
name|rgb
argument_list|)
expr_stmt|;
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
init|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|x
operator|-
name|water
operator|->
name|last_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
operator|-
name|water
operator|->
name|last_y
argument_list|)
argument_list|)
decl_stmt|;
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
operator|*
name|pressure
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
name|GtkAllocation
name|allocation
decl_stmt|;
name|gboolean
name|erase
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|water
operator|->
name|last_x
operator|=
name|event
operator|->
name|x
operator|/
name|allocation
operator|.
name|width
expr_stmt|;
name|water
operator|->
name|last_y
operator|=
name|event
operator|->
name|y
operator|/
name|allocation
operator|.
name|height
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
expr_stmt|;
comment|/* FIXME: (event->source == GDK_SOURCE_ERASER) */
if|if
condition|(
name|event
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
name|erase
operator|=
operator|!
name|erase
expr_stmt|;
name|add_pigment
argument_list|(
name|water
argument_list|,
name|erase
argument_list|,
name|water
operator|->
name|last_x
argument_list|,
name|water
operator|->
name|last_y
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
name|GtkAllocation
name|allocation
decl_stmt|;
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
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
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
init|=
name|event
operator|->
name|time
decl_stmt|;
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
if|if
condition|(
name|event
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
name|erase
operator|=
operator|!
name|erase
expr_stmt|;
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
operator|/
name|allocation
operator|.
name|width
argument_list|,
name|y
operator|/
name|allocation
operator|.
name|height
argument_list|,
name|pressure
argument_list|)
expr_stmt|;
block|}
name|gdk_device_free_history
argument_list|(
name|coords
argument_list|,
name|nevents
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
operator|/
name|allocation
operator|.
name|width
argument_list|,
name|event
operator|->
name|y
operator|/
name|allocation
operator|.
name|height
argument_list|,
name|pressure
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* Ask for more motion events in case the event was a hint */
name|gdk_event_request_motions
argument_list|(
name|event
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
name|gtk_adjustment_get_upper
argument_list|(
name|adj
argument_list|)
operator|-
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
operator|)
operator|/
literal|100.0
expr_stmt|;
block|}
end_function

end_unit


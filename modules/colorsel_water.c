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
file|"libgimp/gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpcolorselector.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimphelpui.h"
end_include

begin_include
include|#
directive|include
file|"gimpmodregister.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/* definitions and variables */
end_comment

begin_define
DECL|macro|IMAGE_SIZE
define|#
directive|define
name|IMAGE_SIZE
value|200
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2941a43b0108
block|{
DECL|member|rgb
name|GimpRGB
name|rgb
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
DECL|member|callback
name|GimpColorSelectorCallback
name|callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|typedef|ColorselWater
block|}
name|ColorselWater
typedef|;
end_typedef

begin_comment
comment|/* prototypes */
end_comment

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|colorsel_water_new
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|,
name|GimpColorSelectorCallback
parameter_list|,
name|gpointer
parameter_list|,
name|gpointer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_free
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_set_color
parameter_list|(
name|gpointer
name|data
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_water_update
parameter_list|(
name|ColorselWater
modifier|*
name|colorsel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* local methods */
end_comment

begin_decl_stmt
DECL|variable|methods
specifier|static
name|GimpColorSelectorMethods
name|methods
init|=
block|{
name|colorsel_water_new
block|,
name|colorsel_water_free
block|,
name|colorsel_water_set_color
block|,
name|NULL
comment|/*  set_channel  */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|info
specifier|static
name|GimpModuleInfo
name|info
init|=
block|{
name|NULL
block|,
name|N_
argument_list|(
literal|"Watercolor style color selector as a pluggable module"
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

begin_comment
comment|/*************************************************************/
end_comment

begin_comment
comment|/* globaly exported init function */
end_comment

begin_function
name|G_MODULE_EXPORT
name|GimpModuleStatus
DECL|function|module_init (GimpModuleInfo ** inforet)
name|module_init
parameter_list|(
name|GimpModuleInfo
modifier|*
modifier|*
name|inforet
parameter_list|)
block|{
name|GimpColorSelectorID
name|id
decl_stmt|;
ifndef|#
directive|ifndef
name|__EMX__
name|id
operator|=
name|gimp_color_selector_register
argument_list|(
name|_
argument_list|(
literal|"Watercolor"
argument_list|)
argument_list|,
literal|"watercolor.html"
argument_list|,
operator|&
name|methods
argument_list|)
expr_stmt|;
else|#
directive|else
name|id
operator|=
name|mod_color_selector_register
argument_list|(
name|_
argument_list|(
literal|"Watercolor"
argument_list|)
argument_list|,
literal|"watercolor.html"
argument_list|,
operator|&
name|methods
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|id
condition|)
block|{
name|info
operator|.
name|shutdown_data
operator|=
name|id
expr_stmt|;
operator|*
name|inforet
operator|=
operator|&
name|info
expr_stmt|;
return|return
name|GIMP_MODULE_OK
return|;
block|}
else|else
block|{
return|return
name|GIMP_MODULE_UNLOAD
return|;
block|}
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|void
DECL|function|module_unload (gpointer shutdown_data,GimpColorSelectorFinishedCB completed_cb,gpointer completed_data)
name|module_unload
parameter_list|(
name|gpointer
name|shutdown_data
parameter_list|,
name|GimpColorSelectorFinishedCB
name|completed_cb
parameter_list|,
name|gpointer
name|completed_data
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|__EMX__
name|gimp_color_selector_unregister
argument_list|(
name|shutdown_data
argument_list|,
name|completed_cb
argument_list|,
name|completed_data
argument_list|)
expr_stmt|;
else|#
directive|else
name|mod_color_selector_unregister
argument_list|(
name|shutdown_data
argument_list|,
name|completed_cb
argument_list|,
name|completed_data
argument_list|)
expr_stmt|;
endif|#
directive|endif
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
DECL|function|add_pigment (ColorselWater * colorsel,gboolean erase,gdouble x,gdouble y,gdouble much)
name|add_pigment
parameter_list|(
name|ColorselWater
modifier|*
name|colorsel
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
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|much
operator|*=
operator|(
name|gdouble
operator|)
name|colorsel
operator|->
name|pressure_adjust
expr_stmt|;
if|if
condition|(
name|erase
condition|)
block|{
name|colorsel
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
name|colorsel
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
name|colorsel
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
name|colorsel
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
name|colorsel
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
name|colorsel
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
name|colorsel
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
name|colorsel
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
name|colorsel
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
name|colorsel_water_update
argument_list|(
name|colorsel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_brush (ColorselWater * colorsel,GtkWidget * widget,gboolean erase,gdouble x,gdouble y,gdouble pressure)
name|draw_brush
parameter_list|(
name|ColorselWater
modifier|*
name|colorsel
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
name|colorsel
operator|->
name|last_pressure
condition|)
name|colorsel
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
name|colorsel
operator|->
name|last_x
operator|)
operator|*
operator|(
name|x
operator|-
name|colorsel
operator|->
name|last_x
operator|)
operator|+
operator|(
name|y
operator|-
name|colorsel
operator|->
name|last_y
operator|)
operator|*
operator|(
name|y
operator|-
name|colorsel
operator|->
name|last_y
operator|)
operator|+
literal|1000
operator|*
operator|(
name|pressure
operator|-
name|colorsel
operator|->
name|last_pressure
operator|)
operator|*
operator|(
name|pressure
operator|-
name|colorsel
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
name|colorsel
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
name|colorsel
operator|->
name|last_x
operator|=
name|x
expr_stmt|;
name|colorsel
operator|->
name|last_y
operator|=
name|y
expr_stmt|;
name|colorsel
operator|->
name|last_pressure
operator|=
name|pressure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|button_press_event (GtkWidget * widget,GdkEventButton * event,gpointer data)
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
name|gpointer
name|data
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|colorsel
decl_stmt|;
name|gboolean
name|erase
decl_stmt|;
name|colorsel
operator|=
operator|(
name|ColorselWater
operator|*
operator|)
name|data
expr_stmt|;
name|colorsel
operator|->
name|last_x
operator|=
name|event
operator|->
name|x
expr_stmt|;
name|colorsel
operator|->
name|last_y
operator|=
name|event
operator|->
name|y
expr_stmt|;
name|colorsel
operator|->
name|last_pressure
operator|=
name|event
operator|->
name|pressure
expr_stmt|;
name|colorsel
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
operator|(
name|event
operator|->
name|source
operator|==
name|GDK_SOURCE_ERASER
operator|)
expr_stmt|;
name|add_pigment
argument_list|(
name|colorsel
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
name|colorsel
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
name|gint
DECL|function|button_release_event (GtkWidget * widget,GdkEventButton * event,gpointer data)
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
name|gpointer
name|data
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|colorsel
decl_stmt|;
name|colorsel
operator|=
operator|(
name|ColorselWater
operator|*
operator|)
name|data
expr_stmt|;
name|colorsel
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
name|gint
DECL|function|motion_notify_event (GtkWidget * widget,GdkEventMotion * event,gpointer data)
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
name|gpointer
name|data
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|colorsel
decl_stmt|;
name|GdkTimeCoord
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
name|colorsel
operator|=
operator|(
name|ColorselWater
operator|*
operator|)
name|data
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
name|coords
operator|=
name|gdk_input_motion_events
argument_list|(
name|event
operator|->
name|window
argument_list|,
name|event
operator|->
name|deviceid
argument_list|,
name|colorsel
operator|->
name|motion_time
argument_list|,
name|event
operator|->
name|time
argument_list|,
operator|&
name|nevents
argument_list|)
expr_stmt|;
name|erase
operator|=
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
operator|(
name|event
operator|->
name|source
operator|==
name|GDK_SOURCE_ERASER
operator|)
expr_stmt|;
name|colorsel
operator|->
name|motion_time
operator|=
name|event
operator|->
name|time
expr_stmt|;
if|if
condition|(
name|coords
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
name|draw_brush
argument_list|(
name|colorsel
argument_list|,
name|widget
argument_list|,
name|erase
argument_list|,
name|coords
index|[
name|i
index|]
operator|.
name|x
argument_list|,
name|coords
index|[
name|i
index|]
operator|.
name|y
argument_list|,
name|coords
index|[
name|i
index|]
operator|.
name|pressure
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|coords
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|event
operator|->
name|is_hint
condition|)
name|gdk_input_window_get_pointer
argument_list|(
argument|event->window
argument_list|,
argument|event->deviceid
argument_list|,
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
else|#
directive|else
comment|/* !GTK_HAVE_SIX_VALUATORS */
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
argument_list|)
empty_stmt|;
name|draw_brush
argument_list|(
name|colorsel
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
name|event
operator|->
name|pressure
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gdk_input_window_get_pointer
argument_list|(
argument|event->window
argument_list|,
argument|event->deviceid
argument_list|,
argument|&event->x
argument_list|,
argument|&event->y
argument_list|,
ifdef|#
directive|ifdef
name|GTK_HAVE_SIX_VALUATORS
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
else|#
directive|else
comment|/* !GTK_HAVE_SIX_VALUATORS */
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
argument_list|,
argument|NULL
endif|#
directive|endif
comment|/* GTK_HAVE_SIX_VALUATORS */
argument_list|)
empty_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|proximity_out_event (GtkWidget * widget,GdkEventProximity * event,gpointer data)
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
name|gpointer
name|data
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|colorsel
decl_stmt|;
name|colorsel
operator|=
operator|(
name|ColorselWater
operator|*
operator|)
name|data
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pressure_adjust_update (GtkAdjustment * adj,gpointer data)
name|pressure_adjust_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|colorsel
decl_stmt|;
name|colorsel
operator|=
operator|(
name|ColorselWater
operator|*
operator|)
name|data
expr_stmt|;
name|colorsel
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

begin_comment
comment|/***********/
end_comment

begin_comment
comment|/* methods */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|colorsel_water_new (const GimpHSV * hsv,const GimpRGB * rgb,gboolean show_alpha,GimpColorSelectorCallback callback,gpointer callback_data,gpointer * selector_data)
name|colorsel_water_new
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|,
name|GimpColorSelectorCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
comment|/* RETURNS: */
name|gpointer
modifier|*
name|selector_data
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|coldata
decl_stmt|;
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
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|coldata
operator|=
name|g_new
argument_list|(
name|ColorselWater
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|coldata
operator|->
name|pressure_adjust
operator|=
literal|1.0
expr_stmt|;
name|coldata
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|coldata
operator|->
name|data
operator|=
name|callback_data
expr_stmt|;
operator|*
name|selector_data
operator|=
name|coldata
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|hbox
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
name|vbox
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
name|hbox
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|event_box
argument_list|)
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|motion_notify_event
argument_list|)
argument_list|,
name|coldata
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|event_box
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|button_press_event
argument_list|)
argument_list|,
name|coldata
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|event_box
argument_list|)
argument_list|,
literal|"button_release_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|button_release_event
argument_list|)
argument_list|,
name|coldata
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|event_box
argument_list|)
argument_list|,
literal|"proximity_out_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|proximity_out_event
argument_list|)
argument_list|,
name|coldata
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
name|coldata
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|pressure_adjust_update
argument_list|)
argument_list|,
name|coldata
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
name|vbox
argument_list|)
expr_stmt|;
name|colorsel_water_set_color
argument_list|(
name|coldata
argument_list|,
name|hsv
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_free (gpointer selector_data)
name|colorsel_water_free
parameter_list|(
name|gpointer
name|selector_data
parameter_list|)
block|{
name|g_free
argument_list|(
name|selector_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_set_color (gpointer data,const GimpHSV * hsv,const GimpRGB * rgb)
name|colorsel_water_set_color
parameter_list|(
name|gpointer
name|data
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|ColorselWater
modifier|*
name|colorsel
decl_stmt|;
name|colorsel
operator|=
operator|(
name|ColorselWater
operator|*
operator|)
name|data
expr_stmt|;
name|colorsel
operator|->
name|rgb
operator|=
operator|*
name|rgb
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_water_update (ColorselWater * colorsel)
name|colorsel_water_update
parameter_list|(
name|ColorselWater
modifier|*
name|colorsel
parameter_list|)
block|{
name|GimpHSV
name|hsv
decl_stmt|;
name|gimp_rgb_to_hsv
argument_list|(
operator|&
name|colorsel
operator|->
name|rgb
argument_list|,
operator|&
name|hsv
argument_list|)
expr_stmt|;
name|colorsel
operator|->
name|callback
argument_list|(
name|colorsel
operator|->
name|data
argument_list|,
operator|&
name|hsv
argument_list|,
operator|&
name|colorsel
operator|->
name|rgb
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


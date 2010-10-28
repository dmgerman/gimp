begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdasheditor.c  * Copyright (C) 2003 Simon Budig<simon@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdashpattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdasheditor.h"
end_include

begin_define
DECL|macro|MIN_WIDTH
define|#
directive|define
name|MIN_WIDTH
value|64
end_define

begin_define
DECL|macro|MIN_HEIGHT
define|#
directive|define
name|MIN_HEIGHT
value|20
end_define

begin_define
DECL|macro|DEFAULT_N_SEGMENTS
define|#
directive|define
name|DEFAULT_N_SEGMENTS
value|24
end_define

begin_enum
enum|enum
DECL|enum|__anon2c3b0e400103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_STROKE_OPTIONS
name|PROP_STROKE_OPTIONS
block|,
DECL|enumerator|PROP_N_SEGMENTS
name|PROP_N_SEGMENTS
block|,
DECL|enumerator|PROP_LENGTH
name|PROP_LENGTH
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_dash_editor_finalize
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
name|gimp_dash_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dash_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dash_editor_get_preferred_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dash_editor_get_preferred_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dash_editor_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dash_editor_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dash_editor_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dash_editor_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* helper function */
end_comment

begin_function_decl
specifier|static
name|void
name|update_segments_from_options
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|update_options_from_segments
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|update_blocksize
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|dash_x_to_index
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDashEditor,gimp_dash_editor,GTK_TYPE_DRAWING_AREA)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDashEditor
argument_list|,
argument|gimp_dash_editor
argument_list|,
argument|GTK_TYPE_DRAWING_AREA
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dash_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dash_editor_class_init
parameter_list|(
name|GimpDashEditorClass
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
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_dash_editor_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dash_editor_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dash_editor_set_property
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_width
operator|=
name|gimp_dash_editor_get_preferred_width
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_height
operator|=
name|gimp_dash_editor_get_preferred_height
expr_stmt|;
name|widget_class
operator|->
name|draw
operator|=
name|gimp_dash_editor_draw
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_dash_editor_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_dash_editor_button_release
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_dash_editor_motion_notify
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_STROKE_OPTIONS
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"stroke-options"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_STROKE_OPTIONS
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_N_SEGMENTS
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"n-segments"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|2
argument_list|,
literal|120
argument_list|,
name|DEFAULT_N_SEGMENTS
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LENGTH
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"dash-length"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|0.5
operator|*
name|DEFAULT_N_SEGMENTS
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dash_editor_init (GimpDashEditor * editor)
name|gimp_dash_editor_init
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|segments
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|block_width
operator|=
literal|6
expr_stmt|;
name|editor
operator|->
name|block_height
operator|=
literal|6
expr_stmt|;
name|editor
operator|->
name|edit_mode
operator|=
name|TRUE
expr_stmt|;
name|editor
operator|->
name|edit_button_x0
operator|=
literal|0
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dash_editor_finalize (GObject * object)
name|gimp_dash_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|editor
operator|->
name|stroke_options
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|editor
operator|->
name|segments
argument_list|,
name|g_free
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
DECL|function|gimp_dash_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dash_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_STROKE_OPTIONS
case|:
name|g_return_if_fail
argument_list|(
name|editor
operator|->
name|stroke_options
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|stroke_options
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|stroke_options
argument_list|,
literal|"notify::dash-info"
argument_list|,
name|G_CALLBACK
argument_list|(
name|update_segments_from_options
argument_list|)
argument_list|,
name|editor
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_N_SEGMENTS
case|:
name|editor
operator|->
name|n_segments
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|segments
condition|)
name|g_free
argument_list|(
name|editor
operator|->
name|segments
argument_list|)
expr_stmt|;
name|editor
operator|->
name|segments
operator|=
name|g_new0
argument_list|(
name|gboolean
argument_list|,
name|editor
operator|->
name|n_segments
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LENGTH
case|:
name|editor
operator|->
name|dash_length
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
name|update_segments_from_options
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dash_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dash_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_STROKE_OPTIONS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|stroke_options
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_N_SEGMENTS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|n_segments
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LENGTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|dash_length
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dash_editor_get_preferred_width (GtkWidget * widget,gint * minimum_width,gint * natural_width)
name|gimp_dash_editor_get_preferred_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
operator|*
name|minimum_width
operator|=
operator|*
name|natural_width
operator|=
name|MAX
argument_list|(
name|editor
operator|->
name|block_width
operator|*
name|editor
operator|->
name|n_segments
operator|+
literal|20
argument_list|,
name|MIN_WIDTH
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dash_editor_get_preferred_height (GtkWidget * widget,gint * minimum_height,gint * natural_height)
name|gimp_dash_editor_get_preferred_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
operator|*
name|minimum_height
operator|=
operator|*
name|natural_height
operator|=
name|MAX
argument_list|(
name|editor
operator|->
name|block_height
operator|+
literal|10
argument_list|,
name|MIN_HEIGHT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dash_editor_draw (GtkWidget * widget,cairo_t * cr)
name|gimp_dash_editor_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|update_blocksize
argument_list|(
name|editor
argument_list|)
expr_stmt|;
comment|/*  draw the background  */
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|base
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|w
operator|=
name|editor
operator|->
name|block_width
expr_stmt|;
name|h
operator|=
name|editor
operator|->
name|block_height
expr_stmt|;
name|editor
operator|->
name|x0
operator|=
operator|(
name|allocation
operator|.
name|width
operator|-
name|w
operator|*
name|editor
operator|->
name|n_segments
operator|)
operator|/
literal|2
expr_stmt|;
name|editor
operator|->
name|y0
operator|=
operator|(
name|allocation
operator|.
name|height
operator|-
name|h
operator|)
operator|/
literal|2
expr_stmt|;
comment|/*  draw the dash segments  */
name|x
operator|=
name|editor
operator|->
name|x0
operator|%
name|w
expr_stmt|;
if|if
condition|(
name|x
operator|>
literal|0
condition|)
name|x
operator|-=
name|w
expr_stmt|;
for|for
control|(
init|;
name|x
operator|<
name|editor
operator|->
name|x0
condition|;
name|x
operator|+=
name|w
control|)
block|{
name|gint
name|index
init|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|x
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|segments
index|[
name|index
index|]
condition|)
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|editor
operator|->
name|y0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|text_aa
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|x
operator|<
name|editor
operator|->
name|x0
operator|+
name|editor
operator|->
name|n_segments
operator|*
name|w
condition|;
name|x
operator|+=
name|w
control|)
block|{
name|gint
name|index
init|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|x
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|segments
index|[
name|index
index|]
condition|)
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|editor
operator|->
name|y0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|text
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|x
operator|<
name|allocation
operator|.
name|width
operator|+
name|w
condition|;
name|x
operator|+=
name|w
control|)
block|{
name|gint
name|index
init|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|x
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|segments
index|[
name|index
index|]
condition|)
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|editor
operator|->
name|y0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|text_aa
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/*  draw rulers  */
name|x
operator|=
name|editor
operator|->
name|x0
operator|%
name|w
expr_stmt|;
if|if
condition|(
name|x
operator|>
literal|0
condition|)
name|x
operator|-=
name|w
expr_stmt|;
for|for
control|(
init|;
name|x
operator|<
name|allocation
operator|.
name|width
operator|+
name|w
condition|;
name|x
operator|+=
name|w
control|)
block|{
name|gint
name|index
init|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|x
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|n_segments
operator|%
literal|4
operator|==
literal|0
operator|&&
operator|(
name|index
operator|+
literal|1
operator|)
operator|%
operator|(
name|editor
operator|->
name|n_segments
operator|/
literal|4
operator|)
operator|==
literal|0
condition|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|w
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|-
literal|2
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|w
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|+
name|h
operator|+
literal|2
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|index
operator|%
literal|2
operator|==
literal|1
condition|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|w
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|+
literal|1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|w
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|+
name|h
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|w
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|+
name|h
operator|/
literal|2
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|w
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|+
name|h
operator|/
literal|2
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|editor
operator|->
name|x0
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|editor
operator|->
name|x0
operator|-
literal|0.5
argument_list|,
name|editor
operator|->
name|y0
operator|+
name|h
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|text_aa
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_stroke
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
name|gboolean
DECL|function|gimp_dash_editor_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_dash_editor_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|index
decl_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
operator|&&
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|index
operator|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|bevent
operator|->
name|x
argument_list|)
expr_stmt|;
name|editor
operator|->
name|edit_mode
operator|=
operator|!
name|editor
operator|->
name|segments
index|[
name|index
index|]
expr_stmt|;
name|editor
operator|->
name|edit_button_x0
operator|=
name|bevent
operator|->
name|x
expr_stmt|;
name|editor
operator|->
name|segments
index|[
name|index
index|]
operator|=
name|editor
operator|->
name|edit_mode
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
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
name|gboolean
DECL|function|gimp_dash_editor_button_release (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_dash_editor_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|update_options_from_segments
argument_list|(
name|editor
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
name|gboolean
DECL|function|gimp_dash_editor_motion_notify (GtkWidget * widget,GdkEventMotion * mevent)
name|gimp_dash_editor_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|)
block|{
name|GimpDashEditor
modifier|*
name|editor
init|=
name|GIMP_DASH_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|index
decl_stmt|;
name|index
operator|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|mevent
operator|->
name|x
argument_list|)
expr_stmt|;
name|editor
operator|->
name|segments
index|[
name|index
index|]
operator|=
name|editor
operator|->
name|edit_mode
expr_stmt|;
if|if
condition|(
name|mevent
operator|->
name|x
operator|>
name|editor
operator|->
name|edit_button_x0
condition|)
block|{
for|for
control|(
name|x
operator|=
name|editor
operator|->
name|edit_button_x0
init|;
name|x
operator|<
name|mevent
operator|->
name|x
condition|;
name|x
operator|+=
name|editor
operator|->
name|block_width
control|)
block|{
name|index
operator|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|editor
operator|->
name|segments
index|[
name|index
index|]
operator|=
name|editor
operator|->
name|edit_mode
expr_stmt|;
block|}
block|}
if|if
condition|(
name|mevent
operator|->
name|x
operator|<
name|editor
operator|->
name|edit_button_x0
condition|)
block|{
for|for
control|(
name|x
operator|=
name|editor
operator|->
name|edit_button_x0
init|;
name|x
operator|>
name|mevent
operator|->
name|x
condition|;
name|x
operator|-=
name|editor
operator|->
name|block_width
control|)
block|{
name|index
operator|=
name|dash_x_to_index
argument_list|(
name|editor
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|editor
operator|->
name|segments
index|[
name|index
index|]
operator|=
name|editor
operator|->
name|edit_mode
expr_stmt|;
block|}
block|}
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dash_editor_new (GimpStrokeOptions * stroke_options)
name|gimp_dash_editor_new
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|stroke_options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|stroke_options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DASH_EDITOR
argument_list|,
literal|"stroke-options"
argument_list|,
name|stroke_options
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dash_editor_shift_right (GimpDashEditor * editor)
name|gimp_dash_editor_shift_right
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gboolean
name|swap
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DASH_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|editor
operator|->
name|n_segments
operator|>
literal|0
argument_list|)
expr_stmt|;
name|swap
operator|=
name|editor
operator|->
name|segments
index|[
name|editor
operator|->
name|n_segments
operator|-
literal|1
index|]
expr_stmt|;
for|for
control|(
name|i
operator|=
name|editor
operator|->
name|n_segments
operator|-
literal|1
init|;
name|i
operator|>
literal|0
condition|;
name|i
operator|--
control|)
name|editor
operator|->
name|segments
index|[
name|i
index|]
operator|=
name|editor
operator|->
name|segments
index|[
name|i
operator|-
literal|1
index|]
expr_stmt|;
name|editor
operator|->
name|segments
index|[
literal|0
index|]
operator|=
name|swap
expr_stmt|;
name|update_options_from_segments
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_dash_editor_shift_left (GimpDashEditor * editor)
name|gimp_dash_editor_shift_left
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gboolean
name|swap
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DASH_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|editor
operator|->
name|n_segments
operator|>
literal|0
argument_list|)
expr_stmt|;
name|swap
operator|=
name|editor
operator|->
name|segments
index|[
literal|0
index|]
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|editor
operator|->
name|n_segments
condition|;
name|i
operator|++
control|)
name|editor
operator|->
name|segments
index|[
name|i
operator|-
literal|1
index|]
operator|=
name|editor
operator|->
name|segments
index|[
name|i
index|]
expr_stmt|;
name|editor
operator|->
name|segments
index|[
name|editor
operator|->
name|n_segments
operator|-
literal|1
index|]
operator|=
name|swap
expr_stmt|;
name|update_options_from_segments
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|update_segments_from_options (GimpDashEditor * editor)
name|update_segments_from_options
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GArray
modifier|*
name|dash_info
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|stroke_options
operator|==
name|NULL
operator|||
name|editor
operator|->
name|segments
operator|==
name|NULL
condition|)
return|return;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|editor
operator|->
name|stroke_options
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|dash_info
operator|=
name|gimp_stroke_options_get_dash_info
argument_list|(
name|editor
operator|->
name|stroke_options
argument_list|)
expr_stmt|;
name|gimp_dash_pattern_fill_segments
argument_list|(
name|dash_info
argument_list|,
name|editor
operator|->
name|segments
argument_list|,
name|editor
operator|->
name|n_segments
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|update_options_from_segments (GimpDashEditor * editor)
name|update_options_from_segments
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GArray
modifier|*
name|pattern
init|=
name|gimp_dash_pattern_new_from_segments
argument_list|(
name|editor
operator|->
name|segments
argument_list|,
name|editor
operator|->
name|n_segments
argument_list|,
name|editor
operator|->
name|dash_length
argument_list|)
decl_stmt|;
name|gimp_stroke_options_take_dash_pattern
argument_list|(
name|editor
operator|->
name|stroke_options
argument_list|,
name|GIMP_DASH_CUSTOM
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|update_blocksize (GimpDashEditor * editor)
name|update_blocksize
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|editor
operator|->
name|block_height
operator|=
literal|6
expr_stmt|;
name|editor
operator|->
name|block_width
operator|=
name|MAX
argument_list|(
name|ROUND
argument_list|(
name|editor
operator|->
name|dash_length
operator|/
name|editor
operator|->
name|n_segments
operator|*
name|editor
operator|->
name|block_height
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|editor
operator|->
name|block_height
operator|=
name|MIN
argument_list|(
name|ROUND
argument_list|(
operator|(
operator|(
name|float
operator|)
name|editor
operator|->
name|block_width
operator|)
operator|*
name|editor
operator|->
name|n_segments
operator|/
name|editor
operator|->
name|dash_length
argument_list|)
argument_list|,
name|allocation
operator|.
name|height
operator|-
literal|4
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|dash_x_to_index (GimpDashEditor * editor,gint x)
name|dash_x_to_index
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|x
parameter_list|)
block|{
name|gint
name|index
init|=
name|x
operator|-
name|editor
operator|->
name|x0
decl_stmt|;
while|while
condition|(
name|index
operator|<
literal|0
condition|)
name|index
operator|+=
name|editor
operator|->
name|n_segments
operator|*
name|editor
operator|->
name|block_width
expr_stmt|;
name|index
operator|=
operator|(
name|index
operator|/
name|editor
operator|->
name|block_width
operator|)
operator|%
name|editor
operator|->
name|n_segments
expr_stmt|;
return|return
name|index
return|;
block|}
end_function

end_unit


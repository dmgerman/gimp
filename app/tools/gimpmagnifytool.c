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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"gimpmagnifytool.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
DECL|typedef|MagnifyOptions
typedef|typedef
name|struct
name|_MagnifyOptions
name|MagnifyOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_MagnifyOptions
struct|struct
name|_MagnifyOptions
block|{
DECL|member|tool_options
name|GimpToolOptions
name|tool_options
decl_stmt|;
comment|/* gint       allow_resize_windows; (from gimprc) */
DECL|member|allow_resize_d
name|gint
name|allow_resize_d
decl_stmt|;
DECL|member|allow_resize_w
name|GtkWidget
modifier|*
name|allow_resize_w
decl_stmt|;
DECL|member|type
name|GimpZoomType
name|type
decl_stmt|;
DECL|member|type_d
name|GimpZoomType
name|type_d
decl_stmt|;
DECL|member|type_w
name|GtkWidget
modifier|*
name|type_w
index|[
literal|2
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  magnify action functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_class_init
parameter_list|(
name|GimpMagnifyToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_init
parameter_list|(
name|GimpMagnifyTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_magnify_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  magnify utility functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|zoom_in
parameter_list|(
name|gint
modifier|*
name|src
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|,
name|gint
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|zoom_out
parameter_list|(
name|gint
modifier|*
name|src
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|,
name|gint
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|MagnifyOptions
modifier|*
name|magnify_options_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|magnify_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|magnify_options
specifier|static
name|MagnifyOptions
modifier|*
name|magnify_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDrawToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_magnify_tool_register (Gimp * gimp)
name|gimp_magnify_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|tool_manager_register_tool
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_MAGNIFY_TOOL
argument_list|,
name|FALSE
argument_list|,
literal|"gimp:magnify_tool"
argument_list|,
name|_
argument_list|(
literal|"Magnify"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Zoom in& out"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Magnify"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"tools/magnify.html"
argument_list|,
name|GIMP_STOCK_TOOL_ZOOM
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_magnify_tool_get_type (void)
name|gimp_magnify_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpMagnifyToolClass
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
name|gimp_magnify_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpMagnifyTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_magnify_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DRAW_TOOL
argument_list|,
literal|"GimpMagnifyTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_class_init (GimpMagnifyToolClass * klass)
name|gimp_magnify_tool_class_init
parameter_list|(
name|GimpMagnifyToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|draw_tool_class
operator|=
name|GIMP_DRAW_TOOL_CLASS
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
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_magnify_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_magnify_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_magnify_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_magnify_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_magnify_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_magnify_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_init (GimpMagnifyTool * magnify_tool)
name|gimp_magnify_tool_init
parameter_list|(
name|GimpMagnifyTool
modifier|*
name|magnify_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|magnify_tool
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|magnify_options
condition|)
block|{
name|magnify_options
operator|=
name|magnify_options_new
argument_list|()
expr_stmt|;
name|tool_manager_register_tool_options
argument_list|(
name|GIMP_TYPE_MAGNIFY_TOOL
argument_list|,
operator|(
name|GimpToolOptions
operator|*
operator|)
name|magnify_options
argument_list|)
expr_stmt|;
block|}
name|magnify_tool
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|magnify_tool
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|magnify_tool
operator|->
name|w
operator|=
literal|0
expr_stmt|;
name|magnify_tool
operator|->
name|h
operator|=
literal|0
expr_stmt|;
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_ZOOM_TOOL_CURSOR
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|TRUE
expr_stmt|;
comment|/*  Disallow scrolling    */
name|tool
operator|->
name|auto_snap_to
operator|=
name|FALSE
expr_stmt|;
comment|/*  Don't snap to guides  */
block|}
end_function

begin_comment
comment|/*  magnify tool options functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|magnify_options_reset (GimpToolOptions * tool_options)
name|magnify_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|MagnifyOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|MagnifyOptions
operator|*
operator|)
name|tool_options
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|allow_resize_w
argument_list|)
argument_list|,
name|options
operator|->
name|allow_resize_d
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
name|options
operator|->
name|type_d
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|MagnifyOptions
modifier|*
DECL|function|magnify_options_new (void)
name|magnify_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|MagnifyOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
comment|/*  the new magnify tool options structure  */
name|options
operator|=
name|g_new0
argument_list|(
name|MagnifyOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tool_options_init
argument_list|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
argument_list|,
name|magnify_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|allow_resize_d
operator|=
name|gimprc
operator|.
name|allow_resize_windows
expr_stmt|;
name|options
operator|->
name|type_d
operator|=
name|options
operator|->
name|type
operator|=
name|GIMP_ZOOM_IN
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
name|options
operator|->
name|tool_options
operator|.
name|main_vbox
expr_stmt|;
comment|/*  the allow_resize toggle button  */
name|options
operator|->
name|allow_resize_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Allow Window Resizing"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|allow_resize_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
operator|(
name|gimprc
operator|.
name|allow_resize_windows
operator|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|allow_resize_w
argument_list|)
argument_list|,
name|gimprc
operator|.
name|allow_resize_windows
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|options
operator|->
name|allow_resize_w
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
name|options
operator|->
name|allow_resize_w
argument_list|)
expr_stmt|;
comment|/*  tool toggle  */
name|frame
operator|=
name|gimp_radio_group_new2
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Tool Toggle"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|type
argument_list|,
operator|(
name|gpointer
operator|)
name|options
operator|->
name|type
argument_list|,
name|_
argument_list|(
literal|"Zoom in"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_ZOOM_IN
argument_list|,
operator|&
name|options
operator|->
name|type_w
index|[
literal|0
index|]
argument_list|,
name|_
argument_list|(
literal|"Zoom out"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|GIMP_ZOOM_OUT
argument_list|,
operator|&
name|options
operator|->
name|type_w
index|[
literal|1
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_comment
comment|/*  magnify utility functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|zoom_in (gint * src,gint * dest,gint scale)
name|zoom_in
parameter_list|(
name|gint
modifier|*
name|src
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|,
name|gint
name|scale
parameter_list|)
block|{
while|while
condition|(
name|scale
operator|--
condition|)
block|{
if|if
condition|(
operator|*
name|src
operator|>
literal|1
condition|)
operator|(
operator|*
name|src
operator|)
operator|--
expr_stmt|;
elseif|else
if|if
condition|(
operator|*
name|dest
operator|<
literal|0x10
condition|)
operator|(
operator|*
name|dest
operator|)
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|zoom_out (gint * src,gint * dest,gint scale)
name|zoom_out
parameter_list|(
name|gint
modifier|*
name|src
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|,
name|gint
name|scale
parameter_list|)
block|{
while|while
condition|(
name|scale
operator|--
condition|)
block|{
if|if
condition|(
operator|*
name|dest
operator|>
literal|1
condition|)
operator|(
operator|*
name|dest
operator|)
operator|--
expr_stmt|;
elseif|else
if|if
condition|(
operator|*
name|src
operator|<
literal|0x10
condition|)
operator|(
operator|*
name|src
operator|)
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  magnify action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_magnify_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMagnifyTool
modifier|*
name|magnify
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|magnify
operator|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|magnify
operator|->
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|magnify
operator|->
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|magnify
operator|->
name|w
operator|=
literal|0
expr_stmt|;
name|magnify
operator|->
name|h
operator|=
literal|0
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gdk_pointer_grab
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_magnify_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMagnifyTool
modifier|*
name|magnify
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gint
name|win_width
decl_stmt|,
name|win_height
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|scalesrc
decl_stmt|,
name|scaledest
decl_stmt|;
name|gint
name|scale
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|magnify
operator|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gdk_pointer_ungrab
argument_list|(
name|time
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
comment|/*  First take care of the case where the user "cancels" the action  */
if|if
condition|(
operator|!
operator|(
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
name|x1
operator|=
operator|(
name|magnify
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
name|magnify
operator|->
name|x
operator|+
name|magnify
operator|->
name|w
else|:
name|magnify
operator|->
name|x
expr_stmt|;
name|y1
operator|=
operator|(
name|magnify
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
name|magnify
operator|->
name|y
operator|+
name|magnify
operator|->
name|h
else|:
name|magnify
operator|->
name|y
expr_stmt|;
name|w
operator|=
operator|(
name|magnify
operator|->
name|w
operator|<
literal|0
operator|)
condition|?
operator|-
name|magnify
operator|->
name|w
else|:
name|magnify
operator|->
name|w
expr_stmt|;
name|h
operator|=
operator|(
name|magnify
operator|->
name|h
operator|<
literal|0
operator|)
condition|?
operator|-
name|magnify
operator|->
name|h
else|:
name|magnify
operator|->
name|h
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|w
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|h
expr_stmt|;
comment|/* these change the user zoom level, so should not be changed to        * the resolution-aware scale macros -- austin        */
name|scalesrc
operator|=
name|SCALESRC
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|scaledest
operator|=
name|SCALEDEST
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|win_width
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
name|win_height
operator|=
name|shell
operator|->
name|disp_height
expr_stmt|;
name|width
operator|=
operator|(
name|win_width
operator|*
name|scalesrc
operator|)
operator|/
name|scaledest
expr_stmt|;
name|height
operator|=
operator|(
name|win_height
operator|*
name|scalesrc
operator|)
operator|/
name|scaledest
expr_stmt|;
if|if
condition|(
operator|!
name|w
operator|||
operator|!
name|h
condition|)
name|scale
operator|=
literal|1
expr_stmt|;
else|else
name|scale
operator|=
name|MIN
argument_list|(
operator|(
name|width
operator|/
name|w
operator|)
argument_list|,
operator|(
name|height
operator|/
name|h
operator|)
argument_list|)
expr_stmt|;
name|magnify
operator|->
name|op
operator|=
name|magnify_options
operator|->
name|type
expr_stmt|;
switch|switch
condition|(
name|magnify
operator|->
name|op
condition|)
block|{
case|case
name|GIMP_ZOOM_IN
case|:
name|zoom_in
argument_list|(
operator|&
name|scalesrc
argument_list|,
operator|&
name|scaledest
argument_list|,
name|scale
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT
case|:
name|zoom_out
argument_list|(
operator|&
name|scalesrc
argument_list|,
operator|&
name|scaledest
argument_list|,
name|scale
argument_list|)
expr_stmt|;
break|break;
block|}
name|gdisp
operator|->
name|scale
operator|=
operator|(
name|scaledest
operator|<<
literal|8
operator|)
operator|+
name|scalesrc
expr_stmt|;
name|shell
operator|->
name|offset_x
operator|=
operator|(
operator|(
name|scaledest
operator|*
operator|(
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2
operator|)
operator|)
operator|/
name|scalesrc
operator|-
operator|(
name|win_width
operator|/
literal|2
operator|)
operator|)
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
operator|(
operator|(
name|scaledest
operator|*
operator|(
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2
operator|)
operator|)
operator|/
name|scalesrc
operator|-
operator|(
name|win_height
operator|/
literal|2
operator|)
operator|)
expr_stmt|;
comment|/*  resize the image  */
name|gimp_display_shell_scale_resize
argument_list|(
name|shell
argument_list|,
name|gimprc
operator|.
name|allow_resize_windows
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_magnify_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpMagnifyTool
modifier|*
name|magnify
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|state
operator|!=
name|ACTIVE
condition|)
return|return;
name|magnify
operator|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|magnify
operator|->
name|w
operator|=
operator|(
name|coords
operator|->
name|x
operator|-
name|magnify
operator|->
name|x
operator|)
expr_stmt|;
name|magnify
operator|->
name|h
operator|=
operator|(
name|coords
operator|->
name|y
operator|-
name|magnify
operator|->
name|y
operator|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_magnify_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
name|key
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
switch|switch
condition|(
name|magnify_options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_ZOOM_IN
case|:
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|magnify_options
operator|->
name|type_w
index|[
name|GIMP_ZOOM_OUT
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ZOOM_OUT
case|:
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|magnify_options
operator|->
name|type_w
index|[
name|GIMP_ZOOM_IN
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_magnify_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|magnify_options
operator|->
name|type
operator|==
name|GIMP_ZOOM_IN
condition|)
block|{
name|gimp_display_shell_install_tool_cursor
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_CURSOR
argument_list|,
name|GIMP_ZOOM_TOOL_CURSOR
argument_list|,
name|GIMP_CURSOR_MODIFIER_PLUS
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_display_shell_install_tool_cursor
argument_list|(
name|shell
argument_list|,
name|GIMP_ZOOM_CURSOR
argument_list|,
name|GIMP_ZOOM_TOOL_CURSOR
argument_list|,
name|GIMP_CURSOR_MODIFIER_MINUS
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_magnify_tool_draw (GimpDrawTool * draw_tool)
name|gimp_magnify_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpMagnifyTool
modifier|*
name|magnify
decl_stmt|;
name|magnify
operator|=
name|GIMP_MAGNIFY_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|gimp_draw_tool_draw_rectangle
argument_list|(
name|draw_tool
argument_list|,
name|FALSE
argument_list|,
name|magnify
operator|->
name|x
argument_list|,
name|magnify
operator|->
name|y
argument_list|,
name|magnify
operator|->
name|w
argument_list|,
name|magnify
operator|->
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


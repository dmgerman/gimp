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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-foreground-extract.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpscanconvert.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpforegroundselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectionoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_foreground_select_tool_class_init
parameter_list|(
name|GimpForegroundSelectToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_foreground_select_tool_init
parameter_list|(
name|GimpForegroundSelectTool
modifier|*
name|fg_select
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_foreground_select_tool_finalize
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
name|gimp_foreground_select_tool_button_press
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
name|gimp_foreground_select_tool_button_release
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
name|gimp_foreground_select_tool_motion
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
name|gimp_foreground_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_foreground_select_tool_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpFreeSelectToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_foreground_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_foreground_select_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_FOREGROUND_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
name|gimp_selection_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-foreground-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Foreground Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Extract foreground using SIOX algorithm"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Foreground Select"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_FOREGROUND_SELECT
argument_list|,
name|GIMP_STOCK_TOOL_FOREGROUND_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_foreground_select_tool_get_type (void)
name|gimp_foreground_select_tool_get_type
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
name|GimpForegroundSelectToolClass
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
name|gimp_foreground_select_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpForegroundSelectTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_foreground_select_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_FREE_SELECT_TOOL
argument_list|,
literal|"GimpForegroundSelectTool"
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_tool_class_init (GimpForegroundSelectToolClass * klass)
name|gimp_foreground_select_tool_class_init
parameter_list|(
name|GimpForegroundSelectToolClass
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
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolClass
modifier|*
name|free_select_tool_class
init|=
name|GIMP_FREE_SELECT_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
name|gimp_foreground_select_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_foreground_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_foreground_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_foreground_select_tool_motion
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_foreground_select_tool_draw
expr_stmt|;
name|free_select_tool_class
operator|->
name|select
operator|=
name|gimp_foreground_select_tool_select
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_tool_init (GimpForegroundSelectTool * fg_select)
name|gimp_foreground_select_tool_init
parameter_list|(
name|GimpForegroundSelectTool
modifier|*
name|fg_select
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|fg_select
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_FREE_SELECT
argument_list|)
expr_stmt|;
name|fg_select
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_tool_finalize (GObject * object)
name|gimp_foreground_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpForegroundSelectTool
modifier|*
name|fg_select
init|=
name|GIMP_FOREGROUND_SELECT_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|fg_select
operator|->
name|mask
condition|)
block|{
name|g_object_unref
argument_list|(
name|fg_select
operator|->
name|mask
argument_list|)
expr_stmt|;
name|fg_select
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_foreground_select_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_foreground_select_tool_button_press
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
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_foreground_select_tool_button_release
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
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_release
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_foreground_select_tool_motion
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
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|motion
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_tool_draw (GimpDrawTool * draw_tool)
name|gimp_foreground_select_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|draw
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_foreground_select_tool_select (GimpFreeSelectTool * free_sel,GimpDisplay * gdisp)
name|gimp_foreground_select_tool_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|free_sel
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|free_sel
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
init|=
name|gdisp
operator|->
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
decl_stmt|;
name|GimpScanConvert
modifier|*
name|scan_convert
decl_stmt|;
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|scan_convert
operator|=
name|gimp_scan_convert_new
argument_list|()
expr_stmt|;
name|gimp_scan_convert_add_polyline
argument_list|(
name|scan_convert
argument_list|,
name|free_sel
operator|->
name|num_points
argument_list|,
name|free_sel
operator|->
name|points
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_channel_new
argument_list|(
name|gimage
argument_list|,
name|gimp_image_get_width
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"foreground-extraction"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_scan_convert_render_value
argument_list|(
name|scan_convert
argument_list|,
name|gimp_drawable_data
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|127
argument_list|)
expr_stmt|;
name|gimp_scan_convert_free
argument_list|(
name|scan_convert
argument_list|)
expr_stmt|;
name|gimp_drawable_foreground_extract
argument_list|(
name|drawable
argument_list|,
name|GIMP_FOREGROUND_EXTRACT_SIOX
argument_list|,
name|GIMP_DRAWABLE
argument_list|(
name|mask
argument_list|)
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_channel_select_channel
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|tool
operator|->
name|tool_info
operator|->
name|blurb
argument_list|,
name|mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_SELECTION_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|op
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


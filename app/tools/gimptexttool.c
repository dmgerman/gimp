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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptext.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpfontselection.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptexteditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimptextoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptexttool.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_text_tool_class_init
parameter_list|(
name|GimpTextToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_tool_init
parameter_list|(
name|GimpTextTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|text_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
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
name|text_tool_button_press
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
name|text_tool_button_release
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
name|text_tool_cursor_update
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
name|gimp_text_tool_connect
parameter_list|(
name|GimpTextTool
modifier|*
name|tool
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|text_tool_create_layer
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|text_tool_editor
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|text_tool_editor_response
parameter_list|(
name|GtkWidget
modifier|*
name|editor
parameter_list|,
name|GtkResponseType
name|response
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpToolClass
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
DECL|function|gimp_text_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_text_tool_register
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
name|GIMP_TYPE_TEXT_TOOL
argument_list|,
name|GIMP_TYPE_TEXT_OPTIONS
argument_list|,
name|gimp_text_options_gui
argument_list|,
name|FALSE
argument_list|,
literal|"gimp-text-tool"
argument_list|,
name|_
argument_list|(
literal|"Text"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Add text to the image"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Text"
argument_list|)
argument_list|,
literal|"T"
argument_list|,
name|NULL
argument_list|,
literal|"tools/text.html"
argument_list|,
name|GIMP_STOCK_TOOL_TEXT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_text_tool_get_type (void)
name|gimp_text_tool_get_type
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
name|GimpTextToolClass
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
name|gimp_text_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpTextTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_text_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|,
literal|"GimpTextTool"
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
DECL|function|gimp_text_tool_class_init (GimpTextToolClass * klass)
name|gimp_text_tool_class_init
parameter_list|(
name|GimpTextToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
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
name|control
operator|=
name|text_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|text_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|text_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|text_tool_cursor_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_tool_init (GimpTextTool * text_tool)
name|gimp_text_tool_init
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
decl_stmt|;
name|text_tool
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
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
name|GIMP_TEXT_TOOL_CURSOR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|text_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|text_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
break|break;
case|case
name|HALT
case|:
if|if
condition|(
name|GIMP_TEXT_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|editor
condition|)
name|gtk_widget_destroy
argument_list|(
name|GIMP_TEXT_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|editor
argument_list|)
expr_stmt|;
name|gimp_text_tool_connect
argument_list|(
name|GIMP_TEXT_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|text_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|text_tool_button_press
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
name|GimpTextTool
modifier|*
name|text_tool
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpText
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|text_tool
operator|=
name|GIMP_TEXT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|text_tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|text_tool
operator|->
name|click_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|text_tool
operator|->
name|click_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|&&
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|coords
operator|->
name|x
operator|-=
name|drawable
operator|->
name|offset_x
expr_stmt|;
name|coords
operator|->
name|y
operator|-=
name|drawable
operator|->
name|offset_y
expr_stmt|;
if|if
condition|(
name|coords
operator|->
name|x
operator|>
literal|0
operator|&&
name|coords
operator|->
name|x
operator|<
name|drawable
operator|->
name|width
operator|&&
name|coords
operator|->
name|y
operator|>
literal|0
operator|&&
name|coords
operator|->
name|y
operator|<
name|drawable
operator|->
name|height
condition|)
block|{
name|text
operator|=
name|gimp_text_layer_get_text
argument_list|(
name|GIMP_TEXT_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|text
operator|||
name|text
operator|==
name|text_tool
operator|->
name|text
condition|)
name|text_tool_editor
argument_list|(
name|text_tool
argument_list|)
expr_stmt|;
name|gimp_text_tool_connect
argument_list|(
name|GIMP_TEXT_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|text_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|text_tool_button_release
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
comment|/*    gimp_tool_control_halt (tool->control); */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|text_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|text_tool_cursor_update
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
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
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
DECL|function|text_tool_create_layer (GimpTextTool * text_tool)
name|text_tool_create_layer
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
block|{
name|GimpTextOptions
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpText
modifier|*
name|text
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|text_tool
operator|->
name|text
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_TEXT_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|text_tool
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|text
operator|=
name|GIMP_TEXT
argument_list|(
name|gimp_config_duplicate
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|text
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_text_tool_connect
argument_list|(
name|text_tool
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_text_layer_new
argument_list|(
name|gimage
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
condition|)
return|return;
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_TEXT
argument_list|,
name|_
argument_list|(
literal|"Add Text Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_x
operator|=
name|text_tool
operator|->
name|click_x
expr_stmt|;
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
operator|->
name|offset_y
operator|=
name|text_tool
operator|->
name|click_y
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_tool_connect (GimpTextTool * tool,GimpText * text)
name|gimp_text_tool_connect
parameter_list|(
name|GimpTextTool
modifier|*
name|tool
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|GimpTextOptions
modifier|*
name|options
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|text
operator|==
name|text
condition|)
return|return;
name|options
operator|=
name|GIMP_TEXT_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|text
condition|)
block|{
name|gimp_config_disconnect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|text
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tool
operator|->
name|text
argument_list|)
expr_stmt|;
name|tool
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|text
condition|)
block|{
name|tool
operator|->
name|text
operator|=
name|g_object_ref
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gimp_config_copy_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|tool
operator|->
name|text
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|options
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|text
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|tool
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* text editor */
end_comment

begin_function
specifier|static
name|void
DECL|function|text_tool_editor (GimpTextTool * text_tool)
name|text_tool_editor
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
block|{
name|GimpTextOptions
modifier|*
name|options
decl_stmt|;
if|if
condition|(
name|text_tool
operator|->
name|editor
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|text_tool
operator|->
name|editor
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|options
operator|=
name|GIMP_TEXT_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|text_tool
operator|->
name|editor
operator|=
name|gimp_text_editor_new
argument_list|(
name|options
operator|->
name|buffer
argument_list|,
name|_
argument_list|(
literal|"GIMP Text Editor"
argument_list|)
argument_list|,
name|text_tool_editor_response
argument_list|,
name|text_tool
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|text_tool
operator|->
name|editor
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|text_tool
operator|->
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|text_tool
operator|->
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|text_tool_editor_response (GtkWidget * editor,GtkResponseType response,gpointer data)
name|text_tool_editor_response
parameter_list|(
name|GtkWidget
modifier|*
name|editor
parameter_list|,
name|GtkResponseType
name|response
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|editor
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|response
condition|)
block|{
case|case
name|GTK_RESPONSE_OK
case|:
block|{
name|GimpTextTool
modifier|*
name|text_tool
init|=
name|GIMP_TEXT_TOOL
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|text_tool
operator|->
name|text
condition|)
name|text_tool_create_layer
argument_list|(
name|text_tool
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

end_unit


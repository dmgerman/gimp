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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangoft2.h>
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-text.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpfontselection.h"
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
file|"gimpeditselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimptexttool.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
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

begin_define
DECL|macro|DEFAULT_FONT
define|#
directive|define
name|DEFAULT_FONT
value|"sans Normal"
end_define

begin_define
DECL|macro|DEFAULT_FONT_SIZE
define|#
directive|define
name|DEFAULT_FONT_SIZE
value|18
end_define

begin_comment
comment|/*  the text tool structures  */
end_comment

begin_typedef
DECL|typedef|TextOptions
typedef|typedef
name|struct
name|_TextOptions
name|TextOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_TextOptions
struct|struct
name|_TextOptions
block|{
DECL|member|tool_options
name|GimpToolOptions
name|tool_options
decl_stmt|;
DECL|member|fontname_d
name|gchar
modifier|*
name|fontname_d
decl_stmt|;
DECL|member|font_selection
name|GtkWidget
modifier|*
name|font_selection
decl_stmt|;
DECL|member|size
name|gdouble
name|size
decl_stmt|;
DECL|member|size_d
name|gdouble
name|size_d
decl_stmt|;
DECL|member|size_w
name|GtkObject
modifier|*
name|size_w
decl_stmt|;
DECL|member|border
name|gdouble
name|border
decl_stmt|;
DECL|member|border_d
name|gdouble
name|border_d
decl_stmt|;
DECL|member|border_w
name|GtkObject
modifier|*
name|border_w
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|unit_d
name|GimpUnit
name|unit_d
decl_stmt|;
DECL|member|unit_w
name|GtkWidget
modifier|*
name|unit_w
decl_stmt|;
DECL|member|line_spacing
name|gdouble
name|line_spacing
decl_stmt|;
DECL|member|line_spacing_d
name|gdouble
name|line_spacing_d
decl_stmt|;
DECL|member|line_spacing_w
name|GtkObject
modifier|*
name|line_spacing_w
decl_stmt|;
DECL|member|letter_spacing
name|gdouble
name|letter_spacing
decl_stmt|;
DECL|member|letter_spacing_d
name|gdouble
name|letter_spacing_d
decl_stmt|;
DECL|member|letter_spacing_w
name|GtkObject
modifier|*
name|letter_spacing_w
decl_stmt|;
block|}
struct|;
end_struct

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
name|gimp_text_tool_finalize
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
name|text_tool_render
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpToolOptions
modifier|*
name|text_tool_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|text_tool_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
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
name|text_tool_options_new
argument_list|,
name|FALSE
argument_list|,
literal|"gimp-text-tool"
argument_list|,
name|_
argument_list|(
literal|"Text Tool"
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
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_text_tool_finalize
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
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
expr_stmt|;
name|text_tool
operator|->
name|pango_context
operator|=
name|pango_ft2_get_context
argument_list|(
name|gimprc
operator|.
name|monitor_xres
argument_list|,
name|gimprc
operator|.
name|monitor_yres
argument_list|)
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
DECL|function|gimp_text_tool_finalize (GObject * object)
name|gimp_text_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTextTool
modifier|*
name|text_tool
decl_stmt|;
name|text_tool
operator|=
name|GIMP_TEXT_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_tool
operator|->
name|pango_context
condition|)
block|{
name|g_object_unref
argument_list|(
name|text_tool
operator|->
name|pango_context
argument_list|)
expr_stmt|;
name|text_tool
operator|->
name|pango_context
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
name|GimpLayer
modifier|*
name|layer
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
if|if
condition|(
operator|(
name|layer
operator|=
name|gimp_image_pick_correlate_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|text_tool
operator|->
name|click_x
argument_list|,
name|text_tool
operator|->
name|click_y
argument_list|)
operator|)
condition|)
comment|/* if there is a floating selection, and this aint it, use the move tool */
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
name|init_edit_selection
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|coords
argument_list|,
name|EDIT_LAYER_TRANSLATE
argument_list|)
expr_stmt|;
return|return;
block|}
name|text_tool_render
argument_list|(
name|GIMP_TEXT_TOOL
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
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
comment|/* sets paused_count to 0 -- is this ok? */
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
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|layer
operator|=
name|gimp_image_pick_correlate_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|&&
name|gimp_layer_is_floating_sel
argument_list|(
name|layer
argument_list|)
condition|)
block|{
comment|/* if there is a floating selection, and this aint it ... */
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MODIFIER_MOVE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
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
DECL|function|text_tool_render (GimpTextTool * text_tool)
name|text_tool_render
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
block|{
name|TextOptions
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
specifier|const
name|gchar
modifier|*
name|font
decl_stmt|;
name|options
operator|=
operator|(
name|TextOptions
operator|*
operator|)
name|GIMP_TOOL
argument_list|(
name|text_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|gimage
operator|=
name|text_tool
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|font
operator|=
name|gimp_font_selection_get_fontname
argument_list|(
name|GIMP_FONT_SELECTION
argument_list|(
name|options
operator|->
name|font_selection
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No font chosen or font invalid."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|text
operator|=
name|GIMP_TEXT
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT
argument_list|,
literal|"text"
argument_list|,
operator|(
literal|"No, you can't change this text.\n"
literal|"Please DON'T report this bug."
operator|)
argument_list|,
literal|"font"
argument_list|,
name|font
argument_list|,
literal|"size"
argument_list|,
name|options
operator|->
name|size
argument_list|,
literal|"border"
argument_list|,
name|options
operator|->
name|border
argument_list|,
literal|"unit"
argument_list|,
name|options
operator|->
name|unit
argument_list|,
literal|"letter-spacing"
argument_list|,
name|options
operator|->
name|letter_spacing
argument_list|,
literal|"line-spacing"
argument_list|,
name|options
operator|->
name|line_spacing
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_image_text_render
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
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|TEXT_UNDO_GROUP
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
comment|/*  If there is a selection mask clear it--    *  this might not always be desired, but in general,    *  it seems like the correct behavior.    */
if|if
condition|(
operator|!
name|gimp_image_mask_is_empty
argument_list|(
name|gimage
argument_list|)
condition|)
name|gimp_image_mask_clear
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|undo_push_group_end
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

begin_comment
comment|/*  tool options stuff  */
end_comment

begin_function
specifier|static
name|GimpToolOptions
modifier|*
DECL|function|text_tool_options_new (GimpToolInfo * tool_info)
name|text_tool_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|TextOptions
modifier|*
name|options
decl_stmt|;
name|PangoContext
modifier|*
name|pango_context
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|size_spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|border_spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|spin_button
decl_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|TextOptions
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
name|tool_info
argument_list|)
expr_stmt|;
operator|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|reset_func
operator|=
name|text_tool_options_reset
expr_stmt|;
name|options
operator|->
name|fontname_d
operator|=
name|DEFAULT_FONT
expr_stmt|;
name|options
operator|->
name|border
operator|=
name|options
operator|->
name|border_d
operator|=
literal|0
expr_stmt|;
name|options
operator|->
name|size
operator|=
name|options
operator|->
name|size_d
operator|=
name|DEFAULT_FONT_SIZE
expr_stmt|;
name|options
operator|->
name|unit
operator|=
name|options
operator|->
name|unit_d
operator|=
name|GIMP_UNIT_PIXEL
expr_stmt|;
name|options
operator|->
name|line_spacing
operator|=
name|options
operator|->
name|line_spacing_d
operator|=
literal|1.0
expr_stmt|;
name|options
operator|->
name|letter_spacing
operator|=
name|options
operator|->
name|letter_spacing_d
operator|=
literal|1.0
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
argument_list|,
literal|5
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|3
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|table
argument_list|)
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
name|table
argument_list|)
expr_stmt|;
name|pango_context
operator|=
name|pango_ft2_get_context
argument_list|(
name|gimprc
operator|.
name|monitor_xres
argument_list|,
name|gimprc
operator|.
name|monitor_yres
argument_list|)
expr_stmt|;
name|options
operator|->
name|font_selection
operator|=
name|gimp_font_selection_new
argument_list|(
name|pango_context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|pango_context
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_font_selection_set_fontname
argument_list|(
name|GIMP_FONT_SELECTION
argument_list|(
name|options
operator|->
name|font_selection
argument_list|)
argument_list|,
name|DEFAULT_FONT
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Font:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|options
operator|->
name|font_selection
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|options
operator|->
name|size_w
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Size:"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|5
argument_list|,
name|options
operator|->
name|size
argument_list|,
literal|1.0
argument_list|,
literal|256.0
argument_list|,
literal|1.0
argument_list|,
literal|50.0
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
literal|1e-5
argument_list|,
literal|32767.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|size_spinbutton
operator|=
name|GIMP_SCALE_ENTRY_SPINBUTTON
argument_list|(
name|options
operator|->
name|size_w
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|size_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|size
argument_list|)
expr_stmt|;
name|options
operator|->
name|border_w
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Border:"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|5
argument_list|,
name|options
operator|->
name|border
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|50.0
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|32767.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|border_spinbutton
operator|=
name|GIMP_SCALE_ENTRY_SPINBUTTON
argument_list|(
name|options
operator|->
name|border_w
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|border_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|border
argument_list|)
expr_stmt|;
name|options
operator|->
name|unit_w
operator|=
name|gimp_unit_menu_new
argument_list|(
literal|"%a"
argument_list|,
name|options
operator|->
name|unit
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"Unit:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|options
operator|->
name|unit_w
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|unit_w
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|size_spinbutton
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|size_spinbutton
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|border_spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|unit_w
argument_list|)
argument_list|,
literal|"unit_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_unit_menu_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|unit
argument_list|)
expr_stmt|;
name|spin_button
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|options
operator|->
name|letter_spacing_w
argument_list|,
name|options
operator|->
name|letter_spacing
argument_list|,
literal|0.0
argument_list|,
literal|64.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spin_button
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gimp_table_attach_stock
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|,
name|GIMP_STOCK_LETTER_SPACING
argument_list|,
name|spin_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|letter_spacing_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|letter_spacing
argument_list|)
expr_stmt|;
name|spin_button
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|options
operator|->
name|line_spacing_w
argument_list|,
name|options
operator|->
name|line_spacing
argument_list|,
literal|0.0
argument_list|,
literal|64.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spin_button
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gimp_table_attach_stock
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|5
argument_list|,
name|GIMP_STOCK_LINE_SPACING
argument_list|,
name|spin_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|line_spacing_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|line_spacing
argument_list|)
expr_stmt|;
return|return
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|text_tool_options_reset (GimpToolOptions * tool_options)
name|text_tool_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|TextOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|options
operator|=
operator|(
name|TextOptions
operator|*
operator|)
name|tool_options
expr_stmt|;
name|gimp_font_selection_set_fontname
argument_list|(
name|GIMP_FONT_SELECTION
argument_list|(
name|options
operator|->
name|font_selection
argument_list|)
argument_list|,
name|options
operator|->
name|fontname_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|size_w
argument_list|)
argument_list|,
name|options
operator|->
name|size_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|border_w
argument_list|)
argument_list|,
name|options
operator|->
name|border_d
argument_list|)
expr_stmt|;
comment|/* resetting the unit menu is a bit tricky ... */
name|options
operator|->
name|unit
operator|=
name|options
operator|->
name|unit_d
expr_stmt|;
name|gimp_unit_menu_set_unit
argument_list|(
name|GIMP_UNIT_MENU
argument_list|(
name|options
operator|->
name|unit_w
argument_list|)
argument_list|,
name|options
operator|->
name|unit_d
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|unit_w
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|)
expr_stmt|;
while|while
condition|(
name|spinbutton
condition|)
block|{
name|gtk_spin_button_set_digits
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|)
expr_stmt|;
block|}
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|letter_spacing_w
argument_list|)
argument_list|,
name|options
operator|->
name|letter_spacing_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|line_spacing_w
argument_list|)
argument_list|,
name|options
operator|->
name|line_spacing_d
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


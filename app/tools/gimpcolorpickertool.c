begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|FIXME #include "gui/gui-types.h"
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppaletteeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptoolbox-color-area.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gui/info-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpickeroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpickertool.h"
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

begin_define
DECL|macro|MAX_INFO_BUF
define|#
directive|define
name|MAX_INFO_BUF
value|8
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_class_init
parameter_list|(
name|GimpColorPickerToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_init
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_finalize
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
name|gimp_color_picker_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
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
name|gimp_color_picker_tool_control
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
name|gimp_color_picker_tool_picked
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|GimpImageType
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|InfoDialog
modifier|*
name|gimp_color_picker_tool_info_create
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_info_close
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_info_update
parameter_list|(
name|GimpImageType
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_color_picker_tool_info
specifier|static
name|InfoDialog
modifier|*
name|gimp_color_picker_tool_info
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_area
specifier|static
name|GtkWidget
modifier|*
name|color_area
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|red_buf
specifier|static
name|gchar
name|red_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|green_buf
specifier|static
name|gchar
name|green_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blue_buf
specifier|static
name|gchar
name|blue_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|alpha_buf
specifier|static
name|gchar
name|alpha_buf
index|[
literal|3
operator|*
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|index_buf
specifier|static
name|gchar
name|index_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|hex_buf
specifier|static
name|gchar
name|hex_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_color_picker_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_color_picker_tool_register
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
name|GIMP_TYPE_COLOR_PICKER_TOOL
argument_list|,
name|GIMP_TYPE_COLOR_PICKER_OPTIONS
argument_list|,
name|gimp_color_picker_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-color-picker-tool"
argument_list|,
name|_
argument_list|(
literal|"Color Picker"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Pick colors from the image"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/C_olor Picker"
argument_list|)
argument_list|,
literal|"O"
argument_list|,
name|NULL
argument_list|,
literal|"tools/color_picker.html"
argument_list|,
name|GIMP_STOCK_TOOL_COLOR_PICKER
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_color_picker_tool_get_type (void)
name|gimp_color_picker_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GimpColorPickerToolClass
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
name|gimp_color_picker_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorPickerTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_picker_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_COLOR_TOOL
argument_list|,
literal|"GimpColorPickerTool"
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
DECL|function|gimp_color_picker_tool_class_init (GimpColorPickerToolClass * klass)
name|gimp_color_picker_tool_class_init
parameter_list|(
name|GimpColorPickerToolClass
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
name|GimpColorToolClass
modifier|*
name|color_tool_class
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
name|color_tool_class
operator|=
name|GIMP_COLOR_TOOL_CLASS
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
name|gimp_color_picker_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_color_picker_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_color_picker_tool_control
expr_stmt|;
name|color_tool_class
operator|->
name|picked
operator|=
name|gimp_color_picker_tool_picked
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_init (GimpColorPickerTool * tool)
name|gimp_color_picker_tool_init
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|tool
parameter_list|)
block|{
name|gimp_tool_control_set_preserve
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|control
argument_list|,
name|GIMP_COLOR_PICKER_TOOL_CURSOR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_finalize (GObject * object)
name|gimp_color_picker_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|gimp_color_picker_tool_info
condition|)
block|{
name|info_dialog_free
argument_list|(
name|gimp_color_picker_tool_info
argument_list|)
expr_stmt|;
name|gimp_color_picker_tool_info
operator|=
name|NULL
expr_stmt|;
name|color_area
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
DECL|function|gimp_color_picker_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_color_picker_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
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
name|initialize
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  always pick colors  */
name|gimp_color_tool_enable
argument_list|(
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|GIMP_COLOR_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_color_picker_tool_control
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
name|HALT
case|:
if|if
condition|(
name|gimp_color_picker_tool_info
condition|)
block|{
name|info_dialog_free
argument_list|(
name|gimp_color_picker_tool_info
argument_list|)
expr_stmt|;
name|gimp_color_picker_tool_info
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_color_picker_tool_picked (GimpColorTool * color_tool,GimpImageType sample_type,GimpRGB * color,gint color_index)
name|gimp_color_picker_tool_picked
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|GimpImageType
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpColorPickerOptions
modifier|*
name|options
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|color_tool
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_color_picker_tool_info
condition|)
name|gimp_color_picker_tool_info
operator|=
name|gimp_color_picker_tool_info_create
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_color_picker_tool_info_update
argument_list|(
name|sample_type
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_COLOR_PICKER_OPTIONS
argument_list|(
name|color_tool
operator|->
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|update_active
condition|)
block|{
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|gimp_palette_editor_update_color (user_context, color, update_state);
endif|#
directive|endif
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gimp_context_set_foreground
argument_list|(
name|user_context
argument_list|,
name|color
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|active_color
operator|==
name|BACKGROUND
condition|)
name|gimp_context_set_background
argument_list|(
name|user_context
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|InfoDialog
modifier|*
DECL|function|gimp_color_picker_tool_info_create (GimpTool * tool)
name|gimp_color_picker_tool_info_create
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|InfoDialog
modifier|*
name|info_dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool
operator|->
name|drawable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|info_dialog
operator|=
name|info_dialog_new
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color Picker"
argument_list|)
argument_list|,
literal|"color_picker"
argument_list|,
name|GIMP_STOCK_TOOL_COLOR_PICKER
argument_list|,
name|_
argument_list|(
literal|"Color Picker Information"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|tool
operator|->
name|tool_info
operator|->
name|help_data
argument_list|)
expr_stmt|;
name|gimp_dialog_create_action_area
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|info_dialog
operator|->
name|shell
argument_list|)
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|gimp_color_picker_tool_info_close
argument_list|,
name|info_dialog
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  if the gdisplay is for a color image, the dialog must have RGB  */
switch|switch
condition|(
name|GIMP_IMAGE_TYPE_BASE_TYPE
argument_list|(
name|gimp_drawable_type
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Red:"
argument_list|)
argument_list|,
name|red_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Green:"
argument_list|)
argument_list|,
name|green_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Blue:"
argument_list|)
argument_list|,
name|blue_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Alpha:"
argument_list|)
argument_list|,
name|alpha_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Hex Triplet:"
argument_list|)
argument_list|,
name|hex_buf
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Intensity:"
argument_list|)
argument_list|,
name|red_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Alpha:"
argument_list|)
argument_list|,
name|alpha_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Hex Triplet:"
argument_list|)
argument_list|,
name|hex_buf
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Index:"
argument_list|)
argument_list|,
name|index_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Red:"
argument_list|)
argument_list|,
name|red_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Green:"
argument_list|)
argument_list|,
name|green_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Blue:"
argument_list|)
argument_list|,
name|blue_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Alpha:"
argument_list|)
argument_list|,
name|alpha_buf
argument_list|)
expr_stmt|;
name|info_dialog_add_label
argument_list|(
name|info_dialog
argument_list|,
name|_
argument_list|(
literal|"Hex Triplet"
argument_list|)
argument_list|,
name|hex_buf
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
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
name|info_dialog
operator|->
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
name|gtk_widget_reparent
argument_list|(
name|info_dialog
operator|->
name|info_table
argument_list|,
name|hbox
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
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|color_area
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|color
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
condition|?
name|GIMP_COLOR_AREA_LARGE_CHECKS
else|:
name|GIMP_COLOR_AREA_FLAT
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|color_area
argument_list|,
literal|48
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|gtk_drag_dest_unset
argument_list|(
name|color_area
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|color_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|color_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_add_foreign
argument_list|(
name|gimp_dialog_factory_from_name
argument_list|(
literal|"toplevel"
argument_list|)
argument_list|,
literal|"gimp-color-picker-tool-dialog"
argument_list|,
name|info_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|info_dialog
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|info_dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_info_close (GtkWidget * widget,gpointer client_data)
name|gimp_color_picker_tool_info_close
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|info_dialog_free
argument_list|(
name|gimp_color_picker_tool_info
argument_list|)
expr_stmt|;
name|gimp_color_picker_tool_info
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_info_update (GimpImageType sample_type,GimpRGB * color,gint color_index)
name|gimp_color_picker_tool_info_update
parameter_list|(
name|GimpImageType
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|red_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%d"
argument_list|,
name|r
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|green_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%d"
argument_list|,
name|g
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|blue_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%d"
argument_list|,
name|b
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|sample_type
argument_list|)
condition|)
name|g_snprintf
argument_list|(
name|alpha_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|alpha_buf
argument_list|)
argument_list|,
literal|"%d (%d %%)"
argument_list|,
name|a
argument_list|,
call|(
name|gint
call|)
argument_list|(
name|color
operator|->
name|a
operator|*
literal|100.0
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_snprintf
argument_list|(
name|alpha_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
name|_
argument_list|(
literal|"N/A"
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|GIMP_IMAGE_TYPE_BASE_TYPE
argument_list|(
name|sample_type
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
case|case
name|GIMP_GRAY
case|:
name|g_snprintf
argument_list|(
name|index_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
name|_
argument_list|(
literal|"N/A"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|g_snprintf
argument_list|(
name|index_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"%d"
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_snprintf
argument_list|(
name|hex_buf
argument_list|,
name|MAX_INFO_BUF
argument_list|,
literal|"#%.2x%.2x%.2x"
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|color_area
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|info_dialog_update
argument_list|(
name|gimp_color_picker_tool_info
argument_list|)
expr_stmt|;
name|info_dialog_popup
argument_list|(
name|gimp_color_picker_tool_info
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_comment
comment|/* playground */
end_comment

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_comment
comment|/* playground */
end_comment

begin_include
include|#
directive|include
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
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
file|"display/gimptoolhandlegrid.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptoolgui.h"
end_include

begin_include
include|#
directive|include
file|"gimphandletransformoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimphandletransformtool.h"
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

begin_comment
comment|/* the transformation is defined by 8 points:  *  * 4 points on the original image and 4 corresponding points on the  * transformed image. The first N_HANDLES points on the transformed  * image are visible as handles.  *  * For these handles, the constants TRANSFORM_HANDLE_N,  * TRANSFORM_HANDLE_S, TRANSFORM_HANDLE_E and TRANSFORM_HANDLE_W are  * used. Actually, it makes no sense to name the handles with north,  * south, east, and west.  But this way, we don't need to define even  * more enum constants.  */
end_comment

begin_comment
comment|/*  index into trans_info array  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2adf90bc0103
block|{
DECL|enumerator|X0
name|X0
block|,
DECL|enumerator|Y0
name|Y0
block|,
DECL|enumerator|X1
name|X1
block|,
DECL|enumerator|Y1
name|Y1
block|,
DECL|enumerator|X2
name|X2
block|,
DECL|enumerator|Y2
name|Y2
block|,
DECL|enumerator|X3
name|X3
block|,
DECL|enumerator|Y3
name|Y3
block|,
DECL|enumerator|OX0
name|OX0
block|,
DECL|enumerator|OY0
name|OY0
block|,
DECL|enumerator|OX1
name|OX1
block|,
DECL|enumerator|OY1
name|OY1
block|,
DECL|enumerator|OX2
name|OX2
block|,
DECL|enumerator|OY2
name|OY2
block|,
DECL|enumerator|OX3
name|OX3
block|,
DECL|enumerator|OY3
name|OY3
block|,
DECL|enumerator|N_HANDLES
name|N_HANDLES
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_tool_modifier_key
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpToolWidget
modifier|*
name|gimp_handle_transform_tool_get_widget
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_handle_transform_tool_get_undo_desc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_handle_transform_tool_widget_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpHandleTransformTool,gimp_handle_transform_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHandleTransformTool
argument_list|,
argument|gimp_handle_transform_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_handle_transform_tool_parent_class
end_define

begin_function
name|void
name|gimp_handle_transform_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
comment|/* we should not know that "data" is a Gimp*, but what the heck this    * is experimental playground stuff    */
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|GIMP
argument_list|(
name|data
argument_list|)
operator|->
name|config
argument_list|)
operator|->
name|playground_handle_transform_tool
condition|)
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_HANDLE_TRANSFORM_TOOL
argument_list|,
name|GIMP_TYPE_HANDLE_TRANSFORM_OPTIONS
argument_list|,
name|gimp_handle_transform_options_gui
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
argument_list|,
literal|"gimp-handle-transform-tool"
argument_list|,
name|_
argument_list|(
literal|"Handle Transform"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Handle Transform Tool: "
literal|"Deform the layer, selection or path with handles"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Handle Transform"
argument_list|)
argument_list|,
literal|"<ctrl><shift>H"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_HANDLE_TRANSFORM
argument_list|,
name|GIMP_ICON_TOOL_HANDLE_TRANSFORM
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_class_init (GimpHandleTransformToolClass * klass)
name|gimp_handle_transform_tool_class_init
parameter_list|(
name|GimpHandleTransformToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpTransformToolClass
modifier|*
name|trans_class
init|=
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_handle_transform_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|options_notify
operator|=
name|gimp_handle_transform_tool_options_notify
expr_stmt|;
name|trans_class
operator|->
name|dialog
operator|=
name|gimp_handle_transform_tool_dialog
expr_stmt|;
name|trans_class
operator|->
name|dialog_update
operator|=
name|gimp_handle_transform_tool_dialog_update
expr_stmt|;
name|trans_class
operator|->
name|prepare
operator|=
name|gimp_handle_transform_tool_prepare
expr_stmt|;
name|trans_class
operator|->
name|get_widget
operator|=
name|gimp_handle_transform_tool_get_widget
expr_stmt|;
name|trans_class
operator|->
name|recalc_matrix
operator|=
name|gimp_handle_transform_tool_recalc_matrix
expr_stmt|;
name|trans_class
operator|->
name|get_undo_desc
operator|=
name|gimp_handle_transform_tool_get_undo_desc
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_init (GimpHandleTransformTool * ht_tool)
name|gimp_handle_transform_tool_init
parameter_list|(
name|GimpHandleTransformTool
modifier|*
name|ht_tool
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|ht_tool
argument_list|)
decl_stmt|;
name|tr_tool
operator|->
name|progress_text
operator|=
name|_
argument_list|(
literal|"Handle transformation"
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|does_perspective
operator|=
name|TRUE
expr_stmt|;
name|ht_tool
operator|->
name|saved_handle_mode
operator|=
name|GIMP_HANDLE_MODE_ADD_TRANSFORM
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_handle_transform_tool_modifier_key
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
name|display
parameter_list|)
block|{
name|GimpHandleTransformTool
modifier|*
name|ht_tool
init|=
name|GIMP_HANDLE_TRANSFORM_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpHandleTransformOptions
modifier|*
name|options
decl_stmt|;
name|GdkModifierType
name|shift
init|=
name|gimp_get_extend_selection_mask
argument_list|()
decl_stmt|;
name|GdkModifierType
name|ctrl
init|=
name|gimp_get_constrain_behavior_mask
argument_list|()
decl_stmt|;
name|GimpTransformHandleMode
name|handle_mode
decl_stmt|;
name|options
operator|=
name|GIMP_HANDLE_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|handle_mode
operator|=
name|options
operator|->
name|handle_mode
expr_stmt|;
if|if
condition|(
name|press
condition|)
block|{
if|if
condition|(
name|key
operator|==
operator|(
name|state
operator|&
operator|(
name|shift
operator||
name|ctrl
operator|)
operator|)
condition|)
block|{
comment|/*  first modifier pressed  */
name|ht_tool
operator|->
name|saved_handle_mode
operator|=
name|options
operator|->
name|handle_mode
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
operator|!
operator|(
name|state
operator|&
operator|(
name|shift
operator||
name|ctrl
operator|)
operator|)
condition|)
block|{
comment|/*  last modifier released  */
name|handle_mode
operator|=
name|ht_tool
operator|->
name|saved_handle_mode
expr_stmt|;
block|}
block|}
if|if
condition|(
name|state
operator|&
name|shift
condition|)
block|{
name|handle_mode
operator|=
name|GIMP_HANDLE_MODE_MOVE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|state
operator|&
name|ctrl
condition|)
block|{
name|handle_mode
operator|=
name|GIMP_HANDLE_MODE_REMOVE
expr_stmt|;
block|}
if|if
condition|(
name|handle_mode
operator|!=
name|options
operator|->
name|handle_mode
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"handle-mode"
argument_list|,
name|handle_mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|modifier_key
argument_list|(
name|tool
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_options_notify (GimpTool * tool,GimpToolOptions * options,const GParamSpec * pspec)
name|gimp_handle_transform_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tr_tool
init|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpHandleTransformOptions
modifier|*
name|ht_options
init|=
name|GIMP_HANDLE_TRANSFORM_OPTIONS
argument_list|(
name|options
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"handle-mode"
argument_list|)
condition|)
block|{
if|if
condition|(
name|tr_tool
operator|->
name|widget
condition|)
name|g_object_set
argument_list|(
name|tr_tool
operator|->
name|widget
argument_list|,
literal|"handle-mode"
argument_list|,
name|ht_options
operator|->
name|handle_mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_dialog (GimpTransformTool * tr_tool)
name|gimp_handle_transform_tool_dialog
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpHandleTransformTool
modifier|*
name|ht_tool
init|=
name|GIMP_HANDLE_TRANSFORM_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Transformation Matrix"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_tool_gui_get_vbox
argument_list|(
name|tr_tool
operator|->
name|gui
argument_list|)
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|3
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|3
condition|;
name|x
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|gtk_label_new
argument_list|(
literal|" "
argument_list|)
decl_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_label_set_width_chars
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
name|x
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|y
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|GTK_EXPAND
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|ht_tool
operator|->
name|label
index|[
name|y
index|]
index|[
name|x
index|]
operator|=
name|label
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_dialog_update (GimpTransformTool * tr_tool)
name|gimp_handle_transform_tool_dialog_update
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpHandleTransformTool
modifier|*
name|ht_tool
init|=
name|GIMP_HANDLE_TRANSFORM_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|3
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|3
condition|;
name|x
operator|++
control|)
block|{
name|gchar
name|buf
index|[
literal|32
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%10.5f"
argument_list|,
name|tr_tool
operator|->
name|transform
operator|.
name|coeff
index|[
name|y
index|]
index|[
name|x
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|ht_tool
operator|->
name|label
index|[
name|y
index|]
index|[
name|x
index|]
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_prepare (GimpTransformTool * tr_tool)
name|gimp_handle_transform_tool_prepare
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OX0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OY0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OX1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OY1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OX2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x1
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OY2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OX3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|x2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|OY3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|tr_tool
operator|->
name|y2
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|N_HANDLES
index|]
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpToolWidget
modifier|*
DECL|function|gimp_handle_transform_tool_get_widget (GimpTransformTool * tr_tool)
name|gimp_handle_transform_tool_get_widget
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpTransformOptions
modifier|*
name|options
init|=
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
argument_list|(
name|tr_tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|GimpToolWidget
modifier|*
name|widget
decl_stmt|;
name|widget
operator|=
name|gimp_tool_handle_grid_new
argument_list|(
name|shell
argument_list|,
name|tr_tool
operator|->
name|x1
argument_list|,
name|tr_tool
operator|->
name|y1
argument_list|,
name|tr_tool
operator|->
name|x2
argument_list|,
name|tr_tool
operator|->
name|y2
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"n-handles"
argument_list|,
operator|(
name|gint
operator|)
name|tr_tool
operator|->
name|trans_info
index|[
name|N_HANDLES
index|]
argument_list|,
literal|"orig-x1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX0
index|]
argument_list|,
literal|"orig-y1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY0
index|]
argument_list|,
literal|"orig-x2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX1
index|]
argument_list|,
literal|"orig-y2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY1
index|]
argument_list|,
literal|"orig-x3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX2
index|]
argument_list|,
literal|"orig-y3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY2
index|]
argument_list|,
literal|"orig-x4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX3
index|]
argument_list|,
literal|"orig-y4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY3
index|]
argument_list|,
literal|"trans-x1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
literal|"trans-y1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|,
literal|"trans-x2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|,
literal|"trans-y2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
argument_list|,
literal|"trans-x3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
argument_list|,
literal|"trans-y3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
argument_list|,
literal|"trans-x4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
argument_list|,
literal|"trans-y4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"guide-type"
argument_list|,
name|options
operator|->
name|grid_type
argument_list|,
literal|"n-guides"
argument_list|,
name|options
operator|->
name|grid_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_handle_transform_tool_widget_changed
argument_list|)
argument_list|,
name|tr_tool
argument_list|)
expr_stmt|;
return|return
name|widget
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_recalc_matrix (GimpTransformTool * tr_tool,GimpToolWidget * widget)
name|gimp_handle_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gimp_matrix3_identity
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|)
expr_stmt|;
name|gimp_transform_matrix_handles
argument_list|(
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX0
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY0
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX1
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY1
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX2
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY2
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX3
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY3
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
condition|)
name|g_object_set
argument_list|(
name|widget
argument_list|,
literal|"transform"
argument_list|,
operator|&
name|tr_tool
operator|->
name|transform
argument_list|,
literal|"n-handles"
argument_list|,
operator|(
name|gint
operator|)
name|tr_tool
operator|->
name|trans_info
index|[
name|N_HANDLES
index|]
argument_list|,
literal|"orig-x1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX0
index|]
argument_list|,
literal|"orig-y1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY0
index|]
argument_list|,
literal|"orig-x2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX1
index|]
argument_list|,
literal|"orig-y2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY1
index|]
argument_list|,
literal|"orig-x3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX2
index|]
argument_list|,
literal|"orig-y3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY2
index|]
argument_list|,
literal|"orig-x4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OX3
index|]
argument_list|,
literal|"orig-y4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|OY3
index|]
argument_list|,
literal|"trans-x1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
literal|"trans-y1"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|,
literal|"trans-x2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|,
literal|"trans-y2"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
argument_list|,
literal|"trans-x3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
argument_list|,
literal|"trans-y3"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
argument_list|,
literal|"trans-x4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
argument_list|,
literal|"trans-y4"
argument_list|,
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_handle_transform_tool_get_undo_desc (GimpTransformTool * tr_tool)
name|gimp_handle_transform_tool_get_undo_desc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
return|return
name|g_strdup
argument_list|(
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Handle transform"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_transform_tool_widget_changed (GimpToolWidget * widget,GimpTransformTool * tr_tool)
name|gimp_handle_transform_tool_widget_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
block|{
name|gint
name|n_handles
decl_stmt|;
name|g_object_get
argument_list|(
name|widget
argument_list|,
literal|"n-handles"
argument_list|,
operator|&
name|n_handles
argument_list|,
literal|"orig-x1"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OX0
index|]
argument_list|,
literal|"orig-y1"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OY0
index|]
argument_list|,
literal|"orig-x2"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OX1
index|]
argument_list|,
literal|"orig-y2"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OY1
index|]
argument_list|,
literal|"orig-x3"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OX2
index|]
argument_list|,
literal|"orig-y3"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OY2
index|]
argument_list|,
literal|"orig-x4"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OX3
index|]
argument_list|,
literal|"orig-y4"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|OY3
index|]
argument_list|,
literal|"trans-x1"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X0
index|]
argument_list|,
literal|"trans-y1"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y0
index|]
argument_list|,
literal|"trans-x2"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X1
index|]
argument_list|,
literal|"trans-y2"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y1
index|]
argument_list|,
literal|"trans-x3"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X2
index|]
argument_list|,
literal|"trans-y3"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y2
index|]
argument_list|,
literal|"trans-x4"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|X3
index|]
argument_list|,
literal|"trans-y4"
argument_list|,
operator|&
name|tr_tool
operator|->
name|trans_info
index|[
name|Y3
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tr_tool
operator|->
name|trans_info
index|[
name|N_HANDLES
index|]
operator|=
name|n_handles
expr_stmt|;
name|gimp_transform_tool_recalc_matrix
argument_list|(
name|tr_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


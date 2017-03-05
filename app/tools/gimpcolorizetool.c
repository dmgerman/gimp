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
file|<string.h>
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
file|"libgimpconfig/gimpconfig.h"
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpspinscale.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorizetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilteroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_colorize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_colorize_tool_get_operation
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gchar
modifier|*
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
modifier|*
name|description
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|icon_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_dialog
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_color_picked
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gpointer
name|identifier
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpColorizeTool,gimp_colorize_tool,GIMP_TYPE_FILTER_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorizeTool
argument_list|,
argument|gimp_colorize_tool
argument_list|,
argument|GIMP_TYPE_FILTER_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_colorize_tool_parent_class
end_define

begin_function
name|void
name|gimp_colorize_tool_register
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
name|GIMP_TYPE_COLORIZE_TOOL
argument_list|,
name|GIMP_TYPE_FILTER_OPTIONS
argument_list|,
name|gimp_color_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-colorize-tool"
argument_list|,
name|_
argument_list|(
literal|"Colorize"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Colorize Tool: Colorize the image"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Colori_ze..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_COLORIZE
argument_list|,
name|GIMP_ICON_TOOL_COLORIZE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_class_init (GimpColorizeToolClass * klass)
name|gimp_colorize_tool_class_init
parameter_list|(
name|GimpColorizeToolClass
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
name|GimpFilterToolClass
modifier|*
name|filter_tool_class
init|=
name|GIMP_FILTER_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_colorize_tool_initialize
expr_stmt|;
name|filter_tool_class
operator|->
name|settings_name
operator|=
literal|"colorize"
expr_stmt|;
name|filter_tool_class
operator|->
name|import_dialog_title
operator|=
name|_
argument_list|(
literal|"Import Colorize Settings"
argument_list|)
expr_stmt|;
name|filter_tool_class
operator|->
name|export_dialog_title
operator|=
name|_
argument_list|(
literal|"Export Colorize Settings"
argument_list|)
expr_stmt|;
name|filter_tool_class
operator|->
name|get_operation
operator|=
name|gimp_colorize_tool_get_operation
expr_stmt|;
name|filter_tool_class
operator|->
name|dialog
operator|=
name|gimp_colorize_tool_dialog
expr_stmt|;
name|filter_tool_class
operator|->
name|color_picked
operator|=
name|gimp_colorize_tool_color_picked
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_init (GimpColorizeTool * col_tool)
name|gimp_colorize_tool_init
parameter_list|(
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_colorize_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_colorize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Colorize does not operate on grayscale layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|initialize
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_colorize_tool_get_operation (GimpFilterTool * filter_tool,gchar ** title,gchar ** description,gchar ** undo_desc,gchar ** icon_name,gchar ** help_id)
name|gimp_colorize_tool_get_operation
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gchar
modifier|*
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
modifier|*
name|description
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|icon_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help_id
parameter_list|)
block|{
operator|*
name|description
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Colorize the Image"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
literal|"gimp:colorize"
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  Hue-Saturation dialog  */
end_comment

begin_comment
comment|/***************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_dialog (GimpFilterTool * filter_tool)
name|gimp_colorize_tool_dialog
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|filter_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
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
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|main_vbox
operator|=
name|gimp_filter_tool_dialog_get_vbox
argument_list|(
name|filter_tool
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Select Color"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  Create the hue scale widget  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"hue"
argument_list|,
name|_
argument_list|(
literal|"_Hue"
argument_list|)
argument_list|,
literal|1.0
operator|/
literal|360.0
argument_list|,
literal|15.0
operator|/
literal|360.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_prop_widget_set_factor
argument_list|(
name|scale
argument_list|,
literal|360.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
comment|/*  Create the saturation scale widget  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"saturation"
argument_list|,
name|_
argument_list|(
literal|"_Saturation"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_prop_widget_set_factor
argument_list|(
name|scale
argument_list|,
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
comment|/*  Create the lightness scale widget  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"lightness"
argument_list|,
name|_
argument_list|(
literal|"_Lightness"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_prop_widget_set_factor
argument_list|(
name|scale
argument_list|,
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
comment|/*  Create the color button  */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
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
name|button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"color"
argument_list|,
name|_
argument_list|(
literal|"Colorize Color"
argument_list|)
argument_list|,
literal|128
argument_list|,
literal|24
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|gimp_color_button_set_update
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_color_panel_set_context
argument_list|(
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|col_tool
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_filter_tool_add_color_picker
argument_list|(
name|filter_tool
argument_list|,
literal|"colorize"
argument_list|,
name|GIMP_ICON_COLOR_PICKER_GRAY
argument_list|,
name|_
argument_list|(
literal|"Pick color from image"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_color_picked (GimpFilterTool * filter_tool,gpointer identifier,gdouble x,gdouble y,const Babl * sample_format,const GimpRGB * color)
name|gimp_colorize_tool_color_picked
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gpointer
name|identifier
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"color"
argument_list|,
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


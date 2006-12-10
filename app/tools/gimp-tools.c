begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-contexts.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolpresets.h"
end_include

begin_include
include|#
directive|include
file|"gimp-tools.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpaligntool.h"
end_include

begin_include
include|#
directive|include
file|"gimpblendtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrightnesscontrasttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbucketfilltool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbycolorselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpclonetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbalancetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorizetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpickertool.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolvetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcroptool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurvestool.h"
end_include

begin_include
include|#
directive|include
file|"gimpdodgeburntool.h"
end_include

begin_include
include|#
directive|include
file|"gimpellipseselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimperasertool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfliptool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfreeselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpforegroundselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfuzzyselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimphealtool.h"
end_include

begin_include
include|#
directive|include
file|"gimphuesaturationtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpinktool.h"
end_include

begin_include
include|#
directive|include
file|"gimpiscissorstool.h"
end_include

begin_include
include|#
directive|include
file|"gimplevelstool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmagnifytool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmeasuretool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmovetool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimppenciltool.h"
end_include

begin_include
include|#
directive|include
file|"gimpperspectiveclonetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpperspectivetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpposterizetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpthresholdtool.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimprotatetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpscaletool.h"
end_include

begin_include
include|#
directive|include
file|"gimpsheartool.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudgetool.h"
end_include

begin_include
include|#
directive|include
file|"gimptexttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectortool.h"
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
name|void
name|gimp_tools_register
parameter_list|(
name|GType
name|tool_type
parameter_list|,
name|GType
name|tool_options_type
parameter_list|,
name|GimpToolOptionsGUIFunc
name|options_gui_func
parameter_list|,
name|GimpContextPropMask
name|context_props
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_accel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|tool_options_deleted
specifier|static
name|gboolean
name|tool_options_deleted
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_tools_init (Gimp * gimp)
name|gimp_tools_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpToolRegisterFunc
name|register_funcs
index|[]
init|=
block|{
comment|/*  register tools in reverse order  */
comment|/*  color tools  */
name|gimp_posterize_tool_register
block|,
name|gimp_curves_tool_register
block|,
name|gimp_levels_tool_register
block|,
name|gimp_threshold_tool_register
block|,
name|gimp_brightness_contrast_tool_register
block|,
name|gimp_colorize_tool_register
block|,
name|gimp_hue_saturation_tool_register
block|,
name|gimp_color_balance_tool_register
block|,
comment|/*  paint tools  */
name|gimp_dodge_burn_tool_register
block|,
name|gimp_smudge_tool_register
block|,
name|gimp_convolve_tool_register
block|,
name|gimp_perspective_clone_tool_register
block|,
name|gimp_heal_tool_register
block|,
name|gimp_clone_tool_register
block|,
name|gimp_ink_tool_register
block|,
name|gimp_airbrush_tool_register
block|,
name|gimp_eraser_tool_register
block|,
name|gimp_paintbrush_tool_register
block|,
name|gimp_pencil_tool_register
block|,
name|gimp_blend_tool_register
block|,
name|gimp_bucket_fill_tool_register
block|,
name|gimp_text_tool_register
block|,
comment|/*  transform tools  */
name|gimp_flip_tool_register
block|,
name|gimp_perspective_tool_register
block|,
name|gimp_shear_tool_register
block|,
name|gimp_scale_tool_register
block|,
name|gimp_rotate_tool_register
block|,
name|gimp_crop_tool_register
block|,
name|gimp_align_tool_register
block|,
name|gimp_move_tool_register
block|,
comment|/*  non-modifying tools  */
name|gimp_measure_tool_register
block|,
name|gimp_magnify_tool_register
block|,
name|gimp_color_picker_tool_register
block|,
comment|/*  path tool */
name|gimp_vector_tool_register
block|,
comment|/*  selection tools */
name|gimp_foreground_select_tool_register
block|,
name|gimp_iscissors_tool_register
block|,
name|gimp_by_color_select_tool_register
block|,
name|gimp_fuzzy_select_tool_register
block|,
name|gimp_free_select_tool_register
block|,
name|gimp_ellipse_select_tool_register
block|,
name|gimp_rect_select_tool_register
block|}
decl_stmt|;
name|GList
modifier|*
name|default_order
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_container_freeze
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|register_funcs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|register_funcs
index|[
name|i
index|]
operator|(
name|gimp_tools_register
operator|,
name|gimp
operator|)
expr_stmt|;
block|}
name|gimp_container_thaw
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|identifier
init|=
name|gimp_object_get_name
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|default_order
operator|=
name|g_list_prepend
argument_list|(
name|default_order
argument_list|,
name|g_strdup
argument_list|(
name|identifier
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|default_order
operator|=
name|g_list_reverse
argument_list|(
name|default_order
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"gimp-tools-default-order"
argument_list|,
name|default_order
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tools_exit (Gimp * gimp)
name|gimp_tools_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|default_order
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|default_order
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"gimp-tools-default-order"
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|default_order
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|default_order
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"gimp-tools-default-order"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_manager_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tools_restore (Gimp * gimp)
name|gimp_tools_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|gimp_list
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_list
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"toolrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp_list
argument_list|)
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gint
name|n
init|=
name|gimp_container_num_children
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|gimp_list
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp_list
argument_list|)
operator|->
name|list
operator|,
name|i
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|object
operator|=
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|g_object_set
argument_list|(
name|object
argument_list|,
literal|"visible"
argument_list|,
name|GIMP_TOOL_INFO
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|visible
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_reorder
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|,
name|object
argument_list|,
name|MIN
argument_list|(
name|i
argument_list|,
name|n
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimp_list
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
comment|/*  get default values from prefs (see bug #120832)  */
name|gimp_tool_options_reset
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
name|gimp_contexts_load
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|GimpToolOptionsGUIFunc
name|options_gui_func
decl_stmt|;
name|GtkWidget
modifier|*
name|options_gui
decl_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_ALL_PROPS_MASK
argument_list|)
expr_stmt|;
name|gimp_tool_options_deserialize
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options_gui_func
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|"gimp-tool-options-gui-func"
argument_list|)
expr_stmt|;
if|if
condition|(
name|options_gui_func
condition|)
block|{
name|options_gui
operator|=
call|(
modifier|*
name|options_gui_func
call|)
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|options_gui
operator|=
name|gimp_tool_options_gui
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"This tool has\nno options."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_CENTER
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|options_gui
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"gimp-tool-options-gui"
argument_list|,
name|options_gui
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|presets
condition|)
name|gimp_tool_presets_load
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|gimp
operator|->
name|be_verbose
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_tools_save (Gimp * gimp,gboolean save_tool_options,gboolean always_save)
name|gimp_tools_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|save_tool_options
parameter_list|,
name|gboolean
name|always_save
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|save_tool_options
operator|&&
operator|(
operator|!
name|tool_options_deleted
operator|||
name|always_save
operator|)
condition|)
name|gimp_contexts_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|save_tool_options
operator|&&
operator|(
operator|!
name|tool_options_deleted
operator|||
name|always_save
operator|)
condition|)
name|gimp_tool_options_serialize
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|presets
condition|)
name|gimp_tool_presets_save
argument_list|(
name|tool_info
operator|->
name|presets
argument_list|,
name|gimp
operator|->
name|be_verbose
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"toolrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"GIMP toolrc"
argument_list|,
literal|"end of toolrc"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tools_clear (Gimp * gimp,GError ** error)
name|gimp_tools_clear
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|GIMP_TOOL_INFO
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|gimp_tool_options_build_filename
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
operator|->
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_unlink
argument_list|(
name|filename
argument_list|)
operator|!=
literal|0
operator|&&
name|errno
operator|!=
name|ENOENT
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Deleting \"%s\" failed: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|gimp_contexts_clear
argument_list|(
name|gimp
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|tool_options_deleted
operator|=
name|TRUE
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_tools_get_default_order (Gimp * gimp)
name|gimp_tools_get_default_order
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"gimp-tools-default-order"
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tools_register (GType tool_type,GType tool_options_type,GimpToolOptionsGUIFunc options_gui_func,GimpContextPropMask context_props,const gchar * identifier,const gchar * blurb,const gchar * help,const gchar * menu_path,const gchar * menu_accel,const gchar * help_domain,const gchar * help_data,const gchar * stock_id,gpointer data)
name|gimp_tools_register
parameter_list|(
name|GType
name|tool_type
parameter_list|,
name|GType
name|tool_options_type
parameter_list|,
name|GimpToolOptionsGUIFunc
name|options_gui_func
parameter_list|,
name|GimpContextPropMask
name|context_props
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_accel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
operator|(
name|Gimp
operator|*
operator|)
name|data
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|paint_core_name
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_TOOL
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|tool_options_type
operator|==
name|G_TYPE_NONE
operator|||
name|g_type_is_a
argument_list|(
name|tool_options_type
argument_list|,
name|GIMP_TYPE_TOOL_OPTIONS
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_options_type
operator|==
name|G_TYPE_NONE
condition|)
name|tool_options_type
operator|=
name|GIMP_TYPE_TOOL_OPTIONS
expr_stmt|;
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-pencil"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-paintbrush"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-eraser"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-airbrush"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-clone"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_HEAL_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-heal"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_PERSPECTIVE_CLONE_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-perspective-clone"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-convolve"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-smudge"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_DODGE_BURN_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-dodge-burn"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_INK_TOOL
condition|)
block|{
name|paint_core_name
operator|=
literal|"gimp-ink"
expr_stmt|;
block|}
else|else
block|{
name|paint_core_name
operator|=
literal|"gimp-paintbrush"
expr_stmt|;
block|}
name|tool_info
operator|=
name|gimp_tool_info_new
argument_list|(
name|gimp
argument_list|,
name|tool_type
argument_list|,
name|tool_options_type
argument_list|,
name|context_props
argument_list|,
name|identifier
argument_list|,
name|blurb
argument_list|,
name|help
argument_list|,
name|menu_path
argument_list|,
name|menu_accel
argument_list|,
name|help_domain
argument_list|,
name|help_data
argument_list|,
name|paint_core_name
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
name|visible
operator|=
operator|(
operator|!
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|)
operator|)
expr_stmt|;
name|g_object_set
argument_list|(
name|tool_info
argument_list|,
literal|"visible"
argument_list|,
name|visible
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|"gimp-tool-default-visible"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|visible
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
literal|"gimp-tool-options-gui-func"
argument_list|,
name|options_gui_func
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tool_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
condition|)
name|gimp_tool_info_set_standard
argument_list|(
name|gimp
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


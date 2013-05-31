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
file|<gegl-plugin.h>
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
file|"libgimpcolor/gimpcolor.h"
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
file|"gegl/gimp-gegl-config-proxy.h"
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
file|"core/gimpimagemap.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs-duplicate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpsettings.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpproptable.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcoloroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpoperationtool.h"
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
name|gimp_operation_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglNode
modifier|*
name|gimp_operation_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_operation_tool_get_settings_ui
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
name|GimpContainer
modifier|*
name|settings
parameter_list|,
specifier|const
name|gchar
modifier|*
name|settings_filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|import_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|export_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|file_dialog_help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_folder
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|settings_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_operation_tool_color_picked
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
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
DECL|function|G_DEFINE_TYPE (GimpOperationTool,gimp_operation_tool,GIMP_TYPE_IMAGE_MAP_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOperationTool
argument_list|,
argument|gimp_operation_tool
argument_list|,
argument|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_operation_tool_parent_class
end_define

begin_function
name|void
name|gimp_operation_tool_register
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
name|GIMP_TYPE_OPERATION_TOOL
argument_list|,
name|GIMP_TYPE_COLOR_OPTIONS
argument_list|,
name|gimp_color_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-operation-tool"
argument_list|,
name|_
argument_list|(
literal|"GEGL Operation"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Operation Tool: Use an arbitrary GEGL operation"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_GEGL Operation..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_GEGL
argument_list|,
name|GIMP_STOCK_GEGL
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tool_class_init (GimpOperationToolClass * klass)
name|gimp_operation_tool_class_init
parameter_list|(
name|GimpOperationToolClass
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
name|GimpImageMapToolClass
modifier|*
name|im_tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_operation_tool_finalize
expr_stmt|;
name|im_tool_class
operator|->
name|dialog_desc
operator|=
name|_
argument_list|(
literal|"GEGL Operation"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|get_operation
operator|=
name|gimp_operation_tool_get_operation
expr_stmt|;
name|im_tool_class
operator|->
name|map
operator|=
name|gimp_operation_tool_map
expr_stmt|;
name|im_tool_class
operator|->
name|dialog
operator|=
name|gimp_operation_tool_dialog
expr_stmt|;
name|im_tool_class
operator|->
name|reset
operator|=
name|gimp_operation_tool_reset
expr_stmt|;
name|im_tool_class
operator|->
name|get_settings_ui
operator|=
name|gimp_operation_tool_get_settings_ui
expr_stmt|;
name|im_tool_class
operator|->
name|color_picked
operator|=
name|gimp_operation_tool_color_picked
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tool_init (GimpOperationTool * tool)
name|gimp_operation_tool_init
parameter_list|(
name|GimpOperationTool
modifier|*
name|tool
parameter_list|)
block|{
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|settings_name
operator|=
name|NULL
expr_stmt|;
comment|/* XXX hack */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tool_finalize (GObject * object)
name|gimp_operation_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpOperationTool
modifier|*
name|tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|operation
condition|)
block|{
name|g_free
argument_list|(
name|tool
operator|->
name|operation
argument_list|)
expr_stmt|;
name|tool
operator|->
name|operation
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool
operator|->
name|config
condition|)
block|{
name|g_object_unref
argument_list|(
name|tool
operator|->
name|config
argument_list|)
expr_stmt|;
name|tool
operator|->
name|config
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool
operator|->
name|undo_desc
condition|)
block|{
name|g_free
argument_list|(
name|tool
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
name|tool
operator|->
name|undo_desc
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
name|GeglNode
modifier|*
DECL|function|gimp_operation_tool_get_operation (GimpImageMapTool * im_tool,GObject ** config,gchar ** undo_desc)
name|gimp_operation_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GimpOperationTool
modifier|*
name|tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|im_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|config
condition|)
operator|*
name|config
operator|=
name|g_object_ref
argument_list|(
name|tool
operator|->
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|undo_desc
condition|)
operator|*
name|undo_desc
operator|=
name|g_strdup
argument_list|(
name|tool
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|operation
condition|)
return|return
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
name|tool
operator|->
name|operation
argument_list|,
name|NULL
argument_list|)
return|;
return|return
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tool_map (GimpImageMapTool * image_map_tool)
name|gimp_operation_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpOperationTool
modifier|*
name|tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|config
condition|)
name|gimp_gegl_config_proxy_sync
argument_list|(
name|tool
operator|->
name|config
argument_list|,
name|image_map_tool
operator|->
name|operation
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_operation_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpOperationTool
modifier|*
name|tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|main_vbox
operator|=
name|gimp_image_map_tool_dialog_get_vbox
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
comment|/*  The options vbox  */
name|tool
operator|->
name|options_box
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|tool
operator|->
name|options_box
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
name|tool
operator|->
name|options_box
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|options_table
condition|)
block|{
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|tool
operator|->
name|options_box
argument_list|)
argument_list|,
name|tool
operator|->
name|options_table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tool
operator|->
name|options_table
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|tool
operator|->
name|undo_desc
condition|)
name|g_object_set
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|dialog
argument_list|,
literal|"description"
argument_list|,
name|tool
operator|->
name|undo_desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_operation_tool_reset (GimpImageMapTool * image_map_tool)
name|gimp_operation_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpOperationTool
modifier|*
name|tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|config
condition|)
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_operation_tool_get_settings_ui (GimpImageMapTool * image_map_tool,GimpContainer * settings,const gchar * settings_filename,const gchar * import_dialog_title,const gchar * export_dialog_title,const gchar * file_dialog_help_id,const gchar * default_folder,GtkWidget ** settings_box)
name|gimp_operation_tool_get_settings_ui
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
name|GimpContainer
modifier|*
name|settings
parameter_list|,
specifier|const
name|gchar
modifier|*
name|settings_filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|import_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|export_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|file_dialog_help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_folder
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
name|settings_box
parameter_list|)
block|{
name|GimpOperationTool
modifier|*
name|tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GType
name|type
init|=
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|tool
operator|->
name|config
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|import_title
decl_stmt|;
name|gchar
modifier|*
name|export_title
decl_stmt|;
name|settings
operator|=
name|gimp_gegl_get_config_container
argument_list|(
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_list_get_sort_func
argument_list|(
name|GIMP_LIST
argument_list|(
name|settings
argument_list|)
argument_list|)
condition|)
name|gimp_list_set_sort_func
argument_list|(
name|GIMP_LIST
argument_list|(
name|settings
argument_list|)
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_settings_compare
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_strconcat
argument_list|(
name|G_OBJECT_TYPE_NAME
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|,
literal|".settings"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"filters"
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|import_title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Import '%s' Settings"
argument_list|)
argument_list|,
name|tool
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
name|export_title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Export '%s' Settings"
argument_list|)
argument_list|,
name|tool
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_settings_ui
argument_list|(
name|image_map_tool
argument_list|,
name|settings
argument_list|,
name|filename
argument_list|,
name|import_title
argument_list|,
name|export_title
argument_list|,
literal|"help-foo"
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|,
name|settings_box
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|import_title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|export_title
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
DECL|function|gimp_operation_tool_color_picked (GimpImageMapTool * im_tool,gpointer identifier,gdouble x,gdouble y,const Babl * sample_format,const GimpRGB * color)
name|gimp_operation_tool_color_picked
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
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
name|GimpOperationTool
modifier|*
name|tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|im_tool
argument_list|)
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|pspecs
decl_stmt|;
name|pspecs
operator|=
name|g_strsplit
argument_list|(
name|identifier
argument_list|,
literal|":"
argument_list|,
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspecs
index|[
literal|1
index|]
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_TOOL
argument_list|(
name|im_tool
argument_list|)
operator|->
name|drawable
decl_stmt|;
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|tool
operator|->
name|config
argument_list|)
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec_x
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec_y
decl_stmt|;
comment|/* the operation's coordinate system is the selection bounds of        * the drawable        */
if|if
condition|(
name|drawable
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
if|if
condition|(
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
block|}
block|}
name|pspec_x
operator|=
name|g_object_class_find_property
argument_list|(
name|object_class
argument_list|,
name|pspecs
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|pspec_y
operator|=
name|g_object_class_find_property
argument_list|(
name|object_class
argument_list|,
name|pspecs
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspec_x
operator|&&
name|pspec_y
operator|&&
name|G_PARAM_SPEC_TYPE
argument_list|(
name|pspec_x
argument_list|)
operator|==
name|G_PARAM_SPEC_TYPE
argument_list|(
name|pspec_y
argument_list|)
condition|)
block|{
name|GValue
name|value_x
init|=
name|G_VALUE_INIT
decl_stmt|;
name|GValue
name|value_y
init|=
name|G_VALUE_INIT
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value_x
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspec_x
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value_y
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|pspec_y
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_IS_PARAM_SPEC_INT
argument_list|(
name|pspec_x
argument_list|)
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|value_x
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|value_y
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_param_value_validate
argument_list|(
name|pspec_x
argument_list|,
operator|&
name|value_x
argument_list|)
expr_stmt|;
name|g_param_value_validate
argument_list|(
name|pspec_y
argument_list|,
operator|&
name|value_y
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|tool
operator|->
name|config
argument_list|,
name|pspecs
index|[
literal|0
index|]
argument_list|,
name|g_value_get_int
argument_list|(
operator|&
name|value_x
argument_list|)
argument_list|,
name|pspecs
index|[
literal|1
index|]
argument_list|,
name|g_value_get_int
argument_list|(
operator|&
name|value_y
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec_x
argument_list|)
condition|)
block|{
name|g_value_set_double
argument_list|(
operator|&
name|value_x
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
operator|&
name|value_y
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_param_value_validate
argument_list|(
name|pspec_x
argument_list|,
operator|&
name|value_x
argument_list|)
expr_stmt|;
name|g_param_value_validate
argument_list|(
name|pspec_y
argument_list|,
operator|&
name|value_y
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|tool
operator|->
name|config
argument_list|,
name|pspecs
index|[
literal|0
index|]
argument_list|,
name|g_value_get_double
argument_list|(
operator|&
name|value_x
argument_list|)
argument_list|,
name|pspecs
index|[
literal|1
index|]
argument_list|,
name|g_value_get_double
argument_list|(
operator|&
name|value_y
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: unhandled param spec of type %s"
argument_list|,
name|G_STRFUNC
argument_list|,
name|G_PARAM_SPEC_TYPE_NAME
argument_list|(
name|pspec_x
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value_x
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value_y
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_object_set
argument_list|(
name|tool
operator|->
name|config
argument_list|,
name|pspecs
index|[
literal|0
index|]
argument_list|,
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_operation_tool_set_operation (GimpOperationTool * tool,const gchar * operation,const gchar * undo_desc)
name|gimp_operation_tool_set_operation
parameter_list|(
name|GimpOperationTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OPERATION_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|operation
condition|)
name|g_free
argument_list|(
name|tool
operator|->
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|undo_desc
condition|)
name|g_free
argument_list|(
name|tool
operator|->
name|undo_desc
argument_list|)
expr_stmt|;
name|tool
operator|->
name|operation
operator|=
name|g_strdup
argument_list|(
name|operation
argument_list|)
expr_stmt|;
name|tool
operator|->
name|undo_desc
operator|=
name|g_strdup
argument_list|(
name|undo_desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|config
condition|)
name|g_object_unref
argument_list|(
name|tool
operator|->
name|config
argument_list|)
expr_stmt|;
name|tool
operator|->
name|config
operator|=
name|gimp_gegl_get_config_proxy
argument_list|(
name|tool
operator|->
name|operation
argument_list|,
name|GIMP_TYPE_SETTINGS
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_get_operation
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo_desc
condition|)
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|settings_name
operator|=
literal|"yes"
expr_stmt|;
comment|/* XXX hack */
else|else
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|settings_name
operator|=
name|NULL
expr_stmt|;
comment|/* XXX hack */
if|if
condition|(
name|tool
operator|->
name|options_table
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|tool
operator|->
name|options_table
argument_list|)
expr_stmt|;
name|tool
operator|->
name|options_table
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|active_picker
condition|)
block|{
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|active_picker
operator|=
name|NULL
expr_stmt|;
name|gimp_color_tool_disable
argument_list|(
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|tool
operator|->
name|config
condition|)
block|{
name|tool
operator|->
name|options_table
operator|=
name|gimp_prop_table_new
argument_list|(
name|G_OBJECT
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|tool
operator|->
name|config
argument_list|)
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
argument_list|)
argument_list|,
operator|(
name|GimpCreatePickerFunc
operator|)
name|gimp_image_map_tool_add_color_picker
argument_list|,
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|options_box
condition|)
block|{
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|tool
operator|->
name|options_box
argument_list|)
argument_list|,
name|tool
operator|->
name|options_table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tool
operator|->
name|options_table
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|undo_desc
operator|&&
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|dialog
condition|)
name|g_object_set
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|dialog
argument_list|,
literal|"description"
argument_list|,
name|undo_desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|drawable
condition|)
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


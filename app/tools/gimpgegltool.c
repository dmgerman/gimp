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
file|"gimpcoloroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpgegltool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b81bad10103
block|{
DECL|enumerator|COLUMN_NAME
name|COLUMN_NAME
block|,
DECL|enumerator|COLUMN_LABEL
name|COLUMN_LABEL
block|,
DECL|enumerator|COLUMN_STOCK_ID
name|COLUMN_STOCK_ID
block|,
DECL|enumerator|N_COLUMNS
name|N_COLUMNS
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_gegl_tool_dialog
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
name|gimp_gegl_tool_operation_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpGeglTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGeglTool,gimp_gegl_tool,GIMP_TYPE_OPERATION_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGeglTool
argument_list|,
argument|gimp_gegl_tool
argument_list|,
argument|GIMP_TYPE_OPERATION_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_gegl_tool_parent_class
end_define

begin_function
name|void
name|gimp_gegl_tool_register
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
name|GIMP_TYPE_GEGL_TOOL
argument_list|,
name|GIMP_TYPE_COLOR_OPTIONS
argument_list|,
name|gimp_color_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-gegl-tool"
argument_list|,
name|_
argument_list|(
literal|"GEGL Operation"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"GEGL Tool: Use an arbitrary GEGL operation"
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
DECL|function|gimp_gegl_tool_class_init (GimpGeglToolClass * klass)
name|gimp_gegl_tool_class_init
parameter_list|(
name|GimpGeglToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|im_tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
name|dialog
operator|=
name|gimp_gegl_tool_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_tool_init (GimpGeglTool * tool)
name|gimp_gegl_tool_init
parameter_list|(
name|GimpGeglTool
modifier|*
name|tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_gegl_tool_operation_blacklisted (const gchar * name,const gchar * categories_str)
name|gimp_gegl_tool_operation_blacklisted
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|categories_str
parameter_list|)
block|{
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|category_blacklist
index|[]
init|=
block|{
literal|"compositors"
block|,
literal|"core"
block|,
literal|"debug"
block|,
literal|"hidden"
block|,
literal|"input"
block|,
literal|"output"
block|,
literal|"programming"
block|,
literal|"transform"
block|,
literal|"video"
block|}
decl_stmt|;
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|name_blacklist
index|[]
init|=
block|{
literal|"gegl:box-blur"
block|,
comment|/* in gimp */
literal|"gegl:c2g"
block|,
comment|/* in gimp */
literal|"gegl:cartoon"
block|,
comment|/* in gimp */
literal|"gegl:checkerboard"
block|,
comment|/* in gimp */
literal|"gegl:color"
block|,
comment|/* pointless */
literal|"gegl:color-reduction"
block|,
comment|/* in gimp */
literal|"gegl:color-temperature"
block|,
comment|/* in gimp */
literal|"gegl:color-to-alpha"
block|,
comment|/* in gimp */
literal|"gegl:colorize"
block|,
comment|/* in gimp */
literal|"gegl:cubism"
block|,
comment|/* in gimp */
literal|"gegl:contrast-curve"
block|,
literal|"gegl:convert-format"
block|,
literal|"gegl:difference-of-gaussians"
block|,
comment|/* in gimp */
literal|"gegl:display"
block|,
literal|"gegl:dot"
block|,
comment|/* in gimp */
literal|"gegl:edge-laplace"
block|,
comment|/* in gimp */
literal|"gegl:edge-sobel"
block|,
comment|/* in gimp */
literal|"gegl:exposure"
block|,
comment|/* in gimp */
literal|"gegl:fill-path"
block|,
literal|"gegl:gaussian-blur"
block|,
comment|/* in gimp */
literal|"gegl:grey"
block|,
comment|/* in gimp */
literal|"gegl:hstack"
block|,
literal|"gegl:introspect"
block|,
literal|"gegl:invert"
block|,
comment|/* in gimp */
literal|"gegl:layer"
block|,
literal|"gegl:lens-correct"
block|,
literal|"gegl:lens-distortion"
block|,
comment|/* in gimp */
literal|"gegl:matting-global"
block|,
comment|/* useless */
literal|"gegl:mono-mixer"
block|,
comment|/* in gimp */
literal|"gegl:noise-CIE_lch"
block|,
comment|/* in gimp */
literal|"gegl:noise-hsv"
block|,
comment|/* in gimp */
literal|"gegl:noise-hurl"
block|,
comment|/* in gimp */
literal|"gegl:noise-pick"
block|,
comment|/* in gimp */
literal|"gegl:noise-rgb"
block|,
comment|/* in gimp */
literal|"gegl:noise-slur"
block|,
comment|/* in gimp */
literal|"gegl:opacity"
block|,
comment|/* pointless */
literal|"gegl:path"
block|,
literal|"gegl:photocopy"
block|,
comment|/* in gimp */
literal|"gegl:pixelize"
block|,
comment|/* in gimp */
literal|"gegl:polar-coordinates"
block|,
comment|/* in gimp */
literal|"gegl:posterize"
block|,
comment|/* in gimp */
literal|"gegl:red-eye-removal"
block|,
comment|/* in gimp */
literal|"gegl:ripple"
block|,
comment|/* in gimp */
literal|"gegl:rotate"
block|,
comment|/* in gimp */
literal|"gegl:scale"
block|,
comment|/* in gimp */
literal|"gegl:sdl-display"
block|,
comment|/* useless */
literal|"gegl:seamless-clone"
block|,
literal|"gegl:shear"
block|,
comment|/* in gimp */
literal|"gegl:softglow"
block|,
comment|/* in gimp */
literal|"gegl:text"
block|,
literal|"gegl:threshold"
block|,
comment|/* in gimp */
literal|"gegl:tile"
block|,
comment|/* useless */
literal|"gegl:transform"
block|,
comment|/* in gimp */
literal|"gegl:translate"
block|,
comment|/* pointless */
literal|"gegl:unsharp-mask"
block|,
comment|/* in gimp */
literal|"gegl:value-invert"
block|,
comment|/* in gimp */
literal|"gegl:vector-stroke"
block|,
literal|"gegl:vignette"
block|,
comment|/* in gimp */
literal|"gegl:whirl-pinch"
block|,
comment|/* in gimp */
block|}
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|categories
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* Operations with no name are abstract base classes */
if|if
condition|(
operator|!
name|name
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|name
argument_list|,
literal|"gimp"
argument_list|)
condition|)
return|return
name|TRUE
return|;
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
name|name_blacklist
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|name_blacklist
index|[
name|i
index|]
argument_list|)
condition|)
return|return
name|TRUE
return|;
block|}
if|if
condition|(
operator|!
name|categories_str
condition|)
return|return
name|FALSE
return|;
name|categories
operator|=
name|g_strsplit
argument_list|(
name|categories_str
argument_list|,
literal|":"
argument_list|,
literal|0
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
name|category_blacklist
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|categories
index|[
name|j
index|]
condition|;
name|j
operator|++
control|)
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|categories
index|[
name|j
index|]
argument_list|,
name|category_blacklist
index|[
name|i
index|]
argument_list|)
condition|)
block|{
name|g_strfreev
argument_list|(
name|categories
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
name|g_strfreev
argument_list|(
name|categories
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/* Builds a GList of the class structures of all subtypes of type.  */
end_comment

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_get_subtype_classes (GType type,GList * classes)
name|gimp_get_subtype_classes
parameter_list|(
name|GType
name|type
parameter_list|,
name|GList
modifier|*
name|classes
parameter_list|)
block|{
name|GeglOperationClass
modifier|*
name|klass
decl_stmt|;
name|GType
modifier|*
name|ops
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|categories
decl_stmt|;
name|guint
name|n_ops
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
return|return
name|classes
return|;
name|klass
operator|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|g_type_class_ref
argument_list|(
name|type
argument_list|)
argument_list|)
expr_stmt|;
name|ops
operator|=
name|g_type_children
argument_list|(
name|type
argument_list|,
operator|&
name|n_ops
argument_list|)
expr_stmt|;
name|categories
operator|=
name|gegl_operation_class_get_key
argument_list|(
name|klass
argument_list|,
literal|"categories"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_gegl_tool_operation_blacklisted
argument_list|(
name|klass
operator|->
name|name
argument_list|,
name|categories
argument_list|)
condition|)
name|classes
operator|=
name|g_list_prepend
argument_list|(
name|classes
argument_list|,
name|klass
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
name|n_ops
condition|;
name|i
operator|++
control|)
name|classes
operator|=
name|gimp_get_subtype_classes
argument_list|(
name|ops
index|[
name|i
index|]
argument_list|,
name|classes
argument_list|)
expr_stmt|;
if|if
condition|(
name|ops
condition|)
name|g_free
argument_list|(
name|ops
argument_list|)
expr_stmt|;
return|return
name|classes
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_gegl_tool_compare_operation_names (GeglOperationClass * a,GeglOperationClass * b)
name|gimp_gegl_tool_compare_operation_names
parameter_list|(
name|GeglOperationClass
modifier|*
name|a
parameter_list|,
name|GeglOperationClass
modifier|*
name|b
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
name|a
operator|->
name|name
argument_list|,
name|b
operator|->
name|name
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_get_geglopclasses (void)
name|gimp_get_geglopclasses
parameter_list|(
name|void
parameter_list|)
block|{
name|GList
modifier|*
name|opclasses
decl_stmt|;
name|opclasses
operator|=
name|gimp_get_subtype_classes
argument_list|(
name|GEGL_TYPE_OPERATION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|opclasses
operator|=
name|g_list_sort
argument_list|(
name|opclasses
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_gegl_tool_compare_operation_names
argument_list|)
expr_stmt|;
return|return
name|opclasses
return|;
block|}
end_function

begin_comment
comment|/*****************/
end_comment

begin_comment
comment|/*  Gegl dialog  */
end_comment

begin_comment
comment|/*****************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_gegl_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpGeglTool
modifier|*
name|tool
init|=
name|GIMP_GEGL_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GimpOperationTool
modifier|*
name|o_tool
init|=
name|GIMP_OPERATION_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GList
modifier|*
name|opclasses
decl_stmt|;
name|GList
modifier|*
name|iter
decl_stmt|;
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dialog
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gimp_image_map_tool_dialog_get_vbox
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
comment|/*  The operation combo box  */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|N_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|opclasses
operator|=
name|gimp_get_geglopclasses
argument_list|()
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|opclasses
init|;
name|iter
condition|;
name|iter
operator|=
name|iter
operator|->
name|next
control|)
block|{
name|GeglOperationClass
modifier|*
name|opclass
init|=
name|GEGL_OPERATION_CLASS
argument_list|(
name|iter
operator|->
name|data
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|opclass
operator|->
name|name
argument_list|,
literal|"gegl:"
argument_list|)
condition|)
block|{
name|label
operator|=
name|opclass
operator|->
name|name
operator|+
name|strlen
argument_list|(
literal|"gegl:"
argument_list|)
expr_stmt|;
name|stock_id
operator|=
name|GIMP_STOCK_GEGL
expr_stmt|;
block|}
else|else
block|{
name|label
operator|=
name|opclass
operator|->
name|name
expr_stmt|;
name|stock_id
operator|=
name|NULL
expr_stmt|;
block|}
name|gtk_list_store_insert_with_values
argument_list|(
name|store
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|,
name|COLUMN_NAME
argument_list|,
name|opclass
operator|->
name|name
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|label
argument_list|,
name|COLUMN_STOCK_ID
argument_list|,
name|stock_id
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|opclasses
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gtk_combo_box_new_with_model
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_pixbuf_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo
argument_list|)
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_add_attribute
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo
argument_list|)
argument_list|,
name|cell
argument_list|,
literal|"stock-id"
argument_list|,
name|COLUMN_STOCK_ID
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo
argument_list|)
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_add_attribute
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo
argument_list|)
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_LABEL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_tool_operation_changed
argument_list|)
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|tool
operator|->
name|operation_combo
operator|=
name|combo
expr_stmt|;
comment|/*  The options vbox  */
name|o_tool
operator|->
name|options_table
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Select an operation from the list above"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|o_tool
operator|->
name|options_table
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
name|gtk_misc_set_padding
argument_list|(
name|GTK_MISC
argument_list|(
name|o_tool
operator|->
name|options_table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|o_tool
operator|->
name|options_box
argument_list|)
argument_list|,
name|o_tool
operator|->
name|options_table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|o_tool
operator|->
name|options_table
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_tool_operation_changed (GtkWidget * widget,GimpGeglTool * tool)
name|gimp_gegl_tool_operation_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpGeglTool
modifier|*
name|tool
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gchar
modifier|*
name|operation
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_combo_box_get_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
return|return;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_NAME
argument_list|,
operator|&
name|operation
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|operation
condition|)
block|{
name|gimp_operation_tool_set_operation
argument_list|(
name|GIMP_OPERATION_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|operation
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


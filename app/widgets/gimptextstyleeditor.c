begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextStyleEditor  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptextbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimptextstyleeditor.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2769f6160103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_BUFFER
name|PROP_BUFFER
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_text_style_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_style_editor_dispose
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
name|gimp_text_style_editor_finalize
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
name|gimp_text_style_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_style_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_text_style_editor_create_toggle
parameter_list|(
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|,
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_style_editor_clear_tags
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_style_editor_tag_toggled
parameter_list|(
name|GtkToggleButton
modifier|*
name|toggle
parameter_list|,
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_style_editor_mark_set
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GtkTextIter
modifier|*
name|location
parameter_list|,
name|GtkTextMark
modifier|*
name|mark
parameter_list|,
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTextStyleEditor,gimp_text_style_editor,GTK_TYPE_HBOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTextStyleEditor
argument_list|,
argument|gimp_text_style_editor
argument_list|,
argument|GTK_TYPE_HBOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_text_style_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_text_style_editor_class_init
parameter_list|(
name|GimpTextStyleEditorClass
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
name|object_class
operator|->
name|constructor
operator|=
name|gimp_text_style_editor_constructor
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_text_style_editor_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_text_style_editor_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_text_style_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_text_style_editor_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BUFFER
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"buffer"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT_BUFFER
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_init (GimpTextStyleEditor * editor)
name|gimp_text_style_editor_init
parameter_list|(
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|editor
operator|->
name|tag_to_toggle_hash
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|g_direct_equal
argument_list|)
expr_stmt|;
name|editor
operator|->
name|clear_button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|editor
operator|->
name|clear_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|clear_button
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
name|editor
operator|->
name|clear_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|clear_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_style_editor_clear_tags
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GTK_STOCK_CLEAR
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
operator|->
name|clear_button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_text_style_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_text_style_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpTextStyleEditor
modifier|*
name|editor
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_TEXT_STYLE_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_TEXT_BUFFER
argument_list|(
name|editor
operator|->
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_text_style_editor_create_toggle
argument_list|(
name|editor
argument_list|,
name|editor
operator|->
name|buffer
operator|->
name|bold_tag
argument_list|,
name|GTK_STOCK_BOLD
argument_list|)
expr_stmt|;
name|gimp_text_style_editor_create_toggle
argument_list|(
name|editor
argument_list|,
name|editor
operator|->
name|buffer
operator|->
name|italic_tag
argument_list|,
name|GTK_STOCK_ITALIC
argument_list|)
expr_stmt|;
name|gimp_text_style_editor_create_toggle
argument_list|(
name|editor
argument_list|,
name|editor
operator|->
name|buffer
operator|->
name|underline_tag
argument_list|,
name|GTK_STOCK_UNDERLINE
argument_list|)
expr_stmt|;
name|gimp_text_style_editor_create_toggle
argument_list|(
name|editor
argument_list|,
name|editor
operator|->
name|buffer
operator|->
name|strikethrough_tag
argument_list|,
name|GTK_STOCK_STRIKETHROUGH
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|buffer
argument_list|,
literal|"mark-set"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_style_editor_mark_set
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_dispose (GObject * object)
name|gimp_text_style_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTextStyleEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_STYLE_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|buffer
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|buffer
argument_list|,
name|gimp_text_style_editor_mark_set
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_finalize (GObject * object)
name|gimp_text_style_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTextStyleEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_STYLE_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|tag_to_toggle_hash
condition|)
block|{
name|g_hash_table_unref
argument_list|(
name|editor
operator|->
name|tag_to_toggle_hash
argument_list|)
expr_stmt|;
name|editor
operator|->
name|tag_to_toggle_hash
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|editor
operator|->
name|buffer
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|buffer
argument_list|)
expr_stmt|;
name|editor
operator|->
name|buffer
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
DECL|function|gimp_text_style_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_text_style_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTextStyleEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_STYLE_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_BUFFER
case|:
name|editor
operator|->
name|buffer
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_text_style_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTextStyleEditor
modifier|*
name|editor
init|=
name|GIMP_TEXT_STYLE_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_BUFFER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|buffer
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_text_style_editor_new (GimpTextBuffer * buffer)
name|gimp_text_style_editor_new
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT_STYLE_EDITOR
argument_list|,
literal|"buffer"
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_text_style_editor_create_toggle (GimpTextStyleEditor * editor,GtkTextTag * tag,const gchar * stock_id)
name|gimp_text_style_editor_create_toggle
parameter_list|(
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|,
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|toggle
operator|=
name|gtk_toggle_button_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|toggle
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|toggle
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
name|toggle
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"tag"
argument_list|,
name|tag
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|editor
operator|->
name|tag_to_toggle_hash
argument_list|,
name|tag
argument_list|,
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_text_style_editor_tag_toggled
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|stock_id
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|toggle
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_clear_tags (GtkButton * button,GimpTextStyleEditor * editor)
name|gimp_text_style_editor_clear_tags
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
init|=
name|GTK_TEXT_BUFFER
argument_list|(
name|editor
operator|->
name|buffer
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_text_buffer_get_has_selection
argument_list|(
name|buffer
argument_list|)
condition|)
block|{
name|GtkTextIter
name|start
decl_stmt|,
name|end
decl_stmt|;
name|gtk_text_buffer_get_selection_bounds
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|gtk_text_buffer_remove_all_tags
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_tag_toggled (GtkToggleButton * toggle,GimpTextStyleEditor * editor)
name|gimp_text_style_editor_tag_toggled
parameter_list|(
name|GtkToggleButton
modifier|*
name|toggle
parameter_list|,
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
init|=
name|GTK_TEXT_BUFFER
argument_list|(
name|editor
operator|->
name|buffer
argument_list|)
decl_stmt|;
name|GtkTextTag
modifier|*
name|tag
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"tag"
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_text_buffer_get_has_selection
argument_list|(
name|buffer
argument_list|)
condition|)
block|{
name|GtkTextIter
name|start
decl_stmt|,
name|end
decl_stmt|;
name|gtk_text_buffer_get_selection_bounds
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|toggle
argument_list|)
condition|)
block|{
name|gtk_text_buffer_apply_tag
argument_list|(
name|buffer
argument_list|,
name|tag
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_text_buffer_remove_tag
argument_list|(
name|buffer
argument_list|,
name|tag
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_enable_toggle (GtkTextTag * tag,GtkToggleButton * toggle,GimpTextStyleEditor * editor)
name|gimp_text_style_editor_enable_toggle
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
name|GtkToggleButton
modifier|*
name|toggle
parameter_list|,
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|toggle
argument_list|,
name|gimp_text_style_editor_tag_toggled
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|toggle
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|toggle
argument_list|,
name|gimp_text_style_editor_tag_toggled
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2769f6160208
block|{
DECL|member|editor
name|GimpTextStyleEditor
modifier|*
name|editor
decl_stmt|;
DECL|member|tags
name|GSList
modifier|*
name|tags
decl_stmt|;
DECL|member|tags_on
name|GSList
modifier|*
name|tags_on
decl_stmt|;
DECL|member|tags_off
name|GSList
modifier|*
name|tags_off
decl_stmt|;
DECL|member|iter
name|GtkTextIter
name|iter
decl_stmt|;
DECL|member|any_active
name|gboolean
name|any_active
decl_stmt|;
DECL|typedef|UpdateTogglesData
block|}
name|UpdateTogglesData
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_update_selection (GtkTextTag * tag,GtkToggleButton * toggle,UpdateTogglesData * data)
name|gimp_text_style_editor_update_selection
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
name|GtkToggleButton
modifier|*
name|toggle
parameter_list|,
name|UpdateTogglesData
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gtk_text_iter_has_tag
argument_list|(
operator|&
name|data
operator|->
name|iter
argument_list|,
name|tag
argument_list|)
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|toggle
argument_list|,
name|gimp_text_style_editor_tag_toggled
argument_list|,
name|data
operator|->
name|editor
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|toggle
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|toggle
argument_list|,
name|gimp_text_style_editor_tag_toggled
argument_list|,
name|data
operator|->
name|editor
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|data
operator|->
name|any_active
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_update_cursor (GtkTextTag * tag,GtkToggleButton * toggle,UpdateTogglesData * data)
name|gimp_text_style_editor_update_cursor
parameter_list|(
name|GtkTextTag
modifier|*
name|tag
parameter_list|,
name|GtkToggleButton
modifier|*
name|toggle
parameter_list|,
name|UpdateTogglesData
modifier|*
name|data
parameter_list|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|toggle
argument_list|,
name|gimp_text_style_editor_tag_toggled
argument_list|,
name|data
operator|->
name|editor
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|toggle
argument_list|,
operator|(
name|g_slist_find
argument_list|(
name|data
operator|->
name|tags
argument_list|,
name|tag
argument_list|)
operator|&&
operator|!
name|g_slist_find
argument_list|(
name|data
operator|->
name|tags_on
argument_list|,
name|tag
argument_list|)
operator|)
operator|||
name|g_slist_find
argument_list|(
name|data
operator|->
name|tags_off
argument_list|,
name|tag
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|toggle
argument_list|,
name|gimp_text_style_editor_tag_toggled
argument_list|,
name|data
operator|->
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_style_editor_mark_set (GtkTextBuffer * buffer,GtkTextIter * location,GtkTextMark * mark,GimpTextStyleEditor * editor)
name|gimp_text_style_editor_mark_set
parameter_list|(
name|GtkTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GtkTextIter
modifier|*
name|location
parameter_list|,
name|GtkTextMark
modifier|*
name|mark
parameter_list|,
name|GimpTextStyleEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|gtk_text_buffer_get_has_selection
argument_list|(
name|buffer
argument_list|)
condition|)
block|{
name|GtkTextIter
name|start
decl_stmt|,
name|end
decl_stmt|;
name|GtkTextIter
name|iter
decl_stmt|;
name|gtk_text_buffer_get_selection_bounds
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|gtk_text_iter_order
argument_list|(
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
comment|/*  first, switch all toggles on  */
name|g_hash_table_foreach
argument_list|(
name|editor
operator|->
name|tag_to_toggle_hash
argument_list|,
operator|(
name|GHFunc
operator|)
name|gimp_text_style_editor_enable_toggle
argument_list|,
name|editor
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|start
init|;
name|gtk_text_iter_in_range
argument_list|(
operator|&
name|iter
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
condition|;
name|gtk_text_iter_forward_cursor_position
argument_list|(
operator|&
name|iter
argument_list|)
control|)
block|{
name|UpdateTogglesData
name|data
decl_stmt|;
name|data
operator|.
name|editor
operator|=
name|editor
expr_stmt|;
name|data
operator|.
name|iter
operator|=
name|iter
expr_stmt|;
name|data
operator|.
name|any_active
operator|=
name|FALSE
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|editor
operator|->
name|tag_to_toggle_hash
argument_list|,
operator|(
name|GHFunc
operator|)
name|gimp_text_style_editor_update_selection
argument_list|,
operator|&
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|.
name|any_active
condition|)
break|break;
block|}
block|}
else|else
block|{
name|UpdateTogglesData
name|data
decl_stmt|;
name|GtkTextIter
name|cursor
decl_stmt|;
name|gtk_text_buffer_get_iter_at_mark
argument_list|(
name|buffer
argument_list|,
operator|&
name|cursor
argument_list|,
name|gtk_text_buffer_get_insert
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|.
name|editor
operator|=
name|editor
expr_stmt|;
name|data
operator|.
name|tags
operator|=
name|gtk_text_iter_get_tags
argument_list|(
operator|&
name|cursor
argument_list|)
expr_stmt|;
name|data
operator|.
name|tags_on
operator|=
name|gtk_text_iter_get_toggled_tags
argument_list|(
operator|&
name|cursor
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|data
operator|.
name|tags_off
operator|=
name|gtk_text_iter_get_toggled_tags
argument_list|(
operator|&
name|cursor
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|editor
operator|->
name|tag_to_toggle_hash
argument_list|,
operator|(
name|GHFunc
operator|)
name|gimp_text_style_editor_update_cursor
argument_list|,
operator|&
name|data
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|data
operator|.
name|tags
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|data
operator|.
name|tags_on
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|data
operator|.
name|tags_off
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


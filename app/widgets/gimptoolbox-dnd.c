begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-edit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbuffer.h"
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
file|"core/gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox-dnd.h"
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
name|gimp_toolbox_drop_uri_list
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GList
modifier|*
name|uri_list
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_toolbox_drop_drawable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_toolbox_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_toolbox_drop_buffer
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_toolbox_drop_component
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_toolbox_drop_pixbuf
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_toolbox_dnd_init (GimpToolbox * toolbox)
name|gimp_toolbox_dnd_init
parameter_list|(
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|)
block|{
name|GimpDock
modifier|*
name|dock
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|toolbox
argument_list|)
argument_list|)
expr_stmt|;
name|dock
operator|=
name|GIMP_DOCK
argument_list|(
name|toolbox
argument_list|)
expr_stmt|;
name|gimp_dnd_uri_list_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|toolbox
argument_list|)
argument_list|,
name|gimp_toolbox_drop_uri_list
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_uri_list_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|gimp_toolbox_drop_uri_list
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|,
name|gimp_toolbox_drop_drawable
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|GIMP_TYPE_LAYER_MASK
argument_list|,
name|gimp_toolbox_drop_drawable
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|,
name|gimp_toolbox_drop_drawable
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|gimp_toolbox_drop_tool
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|,
name|gimp_toolbox_drop_buffer
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_component_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|gimp_toolbox_drop_component
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_dnd_pixbuf_dest_add
argument_list|(
name|toolbox
operator|->
name|tool_wbox
argument_list|,
name|gimp_toolbox_drop_pixbuf
argument_list|,
name|dock
operator|->
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_toolbox_drop_uri_list (GtkWidget * widget,gint x,gint y,GList * uri_list,gpointer data)
name|gimp_toolbox_drop_uri_list
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GList
modifier|*
name|uri_list
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
for|for
control|(
name|list
operator|=
name|uri_list
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
name|uri
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|image
operator|=
name|file_open_with_display
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gimp_message
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_toolbox_drop_drawable (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_toolbox_drop_drawable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
name|GType
name|new_type
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|GimpImageBaseType
name|type
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|type
operator|=
name|GIMP_IMAGE_TYPE_BASE_TYPE
argument_list|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|GIMP_INDEXED
condition|)
name|gimp_image_set_colormap
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_colormap_size
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|new_image
argument_list|,
name|image
operator|->
name|xresolution
argument_list|,
name|image
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
name|new_type
operator|=
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
else|else
name|new_type
operator|=
name|GIMP_TYPE_LAYER
expr_stmt|;
name|new_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|new_image
argument_list|,
name|new_type
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|,
operator|-
name|off_x
argument_list|,
operator|-
name|off_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|new_layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|new_image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_toolbox_drop_tool (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_toolbox_drop_tool
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
name|gimp_context_set_tool
argument_list|(
name|context
argument_list|,
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_toolbox_drop_buffer (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_toolbox_drop_buffer
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
name|image
operator|=
name|gimp_edit_paste_as_new
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_BUFFER
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gimp_create_display
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_toolbox_drop_component (GtkWidget * widget,gint x,gint y,GimpImage * image,GimpChannelType component,gpointer data)
name|gimp_toolbox_drop_component
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_GRAY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|new_image
argument_list|,
name|image
operator|->
name|xresolution
argument_list|,
name|image
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|new_image
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|channel
operator|=
name|gimp_channel_new_from_component
argument_list|(
name|image
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|,
name|new_image
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|channel
argument_list|)
expr_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Channel Copy"
argument_list|)
argument_list|,
name|desc
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|new_layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|new_image
operator|->
name|gimp
argument_list|,
name|new_image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_toolbox_drop_pixbuf (GtkWidget * widget,gint x,gint y,GdkPixbuf * pixbuf,gpointer data)
name|gimp_toolbox_drop_pixbuf
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImageType
name|image_type
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
switch|switch
condition|(
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
condition|)
block|{
case|case
literal|1
case|:
name|image_type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|image_type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|image_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|image_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
break|break;
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
name|new_image
operator|=
name|gimp_create_image
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|GIMP_IMAGE_TYPE_BASE_TYPE
argument_list|(
name|image_type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|new_layer
operator|=
name|gimp_layer_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|,
name|new_image
argument_list|,
name|image_type
argument_list|,
name|_
argument_list|(
literal|"Dropped Buffer"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|new_image
argument_list|,
name|new_layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|new_image
operator|->
name|gimp
argument_list|,
name|new_image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


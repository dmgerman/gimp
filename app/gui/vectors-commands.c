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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
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
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintcore.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintcore-stroke.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemlistview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemtreeview.h"
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
file|"tools/gimppainttool.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpvectortool.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"vectors-commands.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|return_if_no_image (gimage,data)
define|#
directive|define
name|return_if_no_image
parameter_list|(
name|gimage
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gimage = ((GimpDisplay *) data)->gimage; \   else if (GIMP_IS_GIMP (data)) \     gimage = gimp_context_get_image (gimp_get_user_context (GIMP (data))); \   else if (GIMP_IS_ITEM_LIST_VIEW (data)) \     gimage = ((GimpItemListView *) data)->gimage; \   else if (GIMP_IS_ITEM_TREE_VIEW (data)) \     gimage = ((GimpItemTreeView *) data)->gimage; \   else \     gimage = NULL; \   \   if (! gimage) \     return
end_define

begin_define
DECL|macro|return_if_no_vectors (gimage,vectors,data)
define|#
directive|define
name|return_if_no_vectors
parameter_list|(
name|gimage
parameter_list|,
name|vectors
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage,data); \   vectors = gimp_image_get_active_vectors (gimage); \   if (! vectors) \     return
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|vectors_new_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_new_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|vectors_new_vectors_query
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_raise_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_raise_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_raise_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
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
name|void
DECL|function|vectors_lower_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_lower_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_lower_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
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
name|void
DECL|function|vectors_duplicate_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_duplicate_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|new_vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|active_vectors
argument_list|)
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|active_vectors
argument_list|)
argument_list|,
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|gimage
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
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
name|void
DECL|function|vectors_delete_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_delete_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_remove_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
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
DECL|function|vectors_vectors_to_sel (GtkWidget * widget,gpointer data,GimpChannelOps op)
name|vectors_vectors_to_sel
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_mask_select_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|op
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
literal|0
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
name|void
DECL|function|vectors_vectors_to_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_vectors_to_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|vectors_vectors_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_REPLACE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_add_vectors_to_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_add_vectors_to_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|vectors_vectors_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_ADD
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_sub_vectors_from_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_sub_vectors_from_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|vectors_vectors_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_SUBTRACT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_intersect_vectors_with_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_intersect_vectors_with_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|vectors_vectors_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_INTERSECT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_sel_to_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_sel_to_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: need gimp_vectors_from_mask(or something)
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|vectors_stroke_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_stroke_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|vectors_stroke_vectors
argument_list|(
name|active_vectors
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_copy_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_copy_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: need vectors clipoard
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|vectors_paste_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_paste_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: need vectors clipoard
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|vectors_import_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_import_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: need vectors import/export
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|vectors_export_vectors_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_export_vectors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: need vectors import/export
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|vectors_vectors_tool_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_vectors_tool_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|vectors_vectors_tool
argument_list|(
name|active_vectors
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_edit_vectors_attributes_cmd_callback (GtkWidget * widget,gpointer data)
name|vectors_edit_vectors_attributes_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpVectors
modifier|*
name|active_vectors
decl_stmt|;
name|return_if_no_vectors
argument_list|(
name|gimage
argument_list|,
name|active_vectors
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|vectors_edit_vectors_query
argument_list|(
name|active_vectors
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_stroke_vectors (GimpVectors * vectors)
name|vectors_stroke_vectors
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|active_drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|active_drawable
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There is no active Layer or Channel to stroke to"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|vectors
operator|&&
name|vectors
operator|->
name|strokes
condition|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
name|GimpPaintCore
modifier|*
name|core
decl_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|tool_info
operator|&&
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
operator|)
condition|)
block|{
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|tool_info_list
argument_list|,
literal|"gimp-paintbrush-tool"
argument_list|)
expr_stmt|;
block|}
name|paint_options
operator|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|core
operator|=
name|g_object_new
argument_list|(
name|tool_info
operator|->
name|paint_info
operator|->
name|paint_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_paint_core_stroke_vectors
argument_list|(
name|core
argument_list|,
name|active_drawable
argument_list|,
name|paint_options
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|core
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|vectors_vectors_tool (GimpVectors * vectors)
name|vectors_vectors_tool
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_VECTOR_TOOL
argument_list|(
name|active_tool
argument_list|)
condition|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|tool_info
operator|=
name|tool_manager_get_info_by_type
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|GIMP_TYPE_VECTOR_TOOL
argument_list|)
expr_stmt|;
name|gimp_context_set_tool
argument_list|(
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
name|gimp_vector_tool_set_vectors
argument_list|(
name|GIMP_VECTOR_TOOL
argument_list|(
name|active_tool
argument_list|)
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**********************************/
end_comment

begin_comment
comment|/*  The new vectors query dialog  */
end_comment

begin_comment
comment|/**********************************/
end_comment

begin_typedef
DECL|typedef|NewVectorsOptions
typedef|typedef
name|struct
name|_NewVectorsOptions
name|NewVectorsOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_NewVectorsOptions
struct|struct
name|_NewVectorsOptions
block|{
DECL|member|query_box
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
DECL|member|name_entry
name|GtkWidget
modifier|*
name|name_entry
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|vectors_name
specifier|static
name|gchar
modifier|*
name|vectors_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|new_vectors_query_ok_callback (GtkWidget * widget,gpointer data)
name|new_vectors_query_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|NewVectorsOptions
modifier|*
name|options
decl_stmt|;
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|options
operator|=
operator|(
name|NewVectorsOptions
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|vectors_name
condition|)
name|g_free
argument_list|(
name|vectors_name
argument_list|)
expr_stmt|;
name|vectors_name
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|gimage
operator|=
name|options
operator|->
name|gimage
operator|)
condition|)
block|{
name|new_vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|gimage
argument_list|,
name|vectors_name
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|gimage
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_new_vectors_query (GimpImage * gimage,GimpVectors * template,gboolean interactive)
name|vectors_new_vectors_query
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpVectors
modifier|*
name|template
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
block|{
name|NewVectorsOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
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
name|label
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|template
operator|||
name|GIMP_IS_VECTORS
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
operator|||
operator|!
name|interactive
condition|)
block|{
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|new_vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Empty Vectors Copy"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|gimage
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  the new options structure  */
name|options
operator|=
name|g_new
argument_list|(
name|NewVectorsOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
comment|/*  The dialog  */
name|options
operator|->
name|query_box
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"New Path"
argument_list|)
argument_list|,
literal|"new_path_options"
argument_list|,
name|GTK_STOCK_NEW
argument_list|,
name|_
argument_list|(
literal|"New Path Options"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/vectors/new_vectors.html"
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|new_vectors_query_ok_callback
argument_list|,
name|options
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|options
argument_list|)
expr_stmt|;
comment|/*  The main hbox  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
comment|/*  The vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  The table  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
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
literal|4
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  The name entry hbox, label and entry  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Path name:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
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
name|options
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|options
operator|->
name|name_entry
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|options
operator|->
name|name_entry
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|,
operator|(
name|vectors_name
condition|?
name|vectors_name
else|:
name|_
argument_list|(
literal|"New Path"
argument_list|)
operator|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/****************************************/
end_comment

begin_comment
comment|/*  The edit vectors attributes dialog  */
end_comment

begin_comment
comment|/****************************************/
end_comment

begin_typedef
DECL|typedef|EditVectorsOptions
typedef|typedef
name|struct
name|_EditVectorsOptions
name|EditVectorsOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_EditVectorsOptions
struct|struct
name|_EditVectorsOptions
block|{
DECL|member|query_box
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
DECL|member|name_entry
name|GtkWidget
modifier|*
name|name_entry
decl_stmt|;
DECL|member|vectors
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|edit_vectors_query_ok_callback (GtkWidget * widget,gpointer data)
name|edit_vectors_query_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|EditVectorsOptions
modifier|*
name|options
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|options
operator|=
operator|(
name|EditVectorsOptions
operator|*
operator|)
name|data
expr_stmt|;
name|vectors
operator|=
name|options
operator|->
name|vectors
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|gimage
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
name|new_name
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|new_name
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_item_rename
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|options
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_edit_vectors_query (GimpVectors * vectors)
name|vectors_edit_vectors_query
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|EditVectorsOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
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
name|label
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|EditVectorsOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|vectors
operator|=
name|vectors
expr_stmt|;
name|options
operator|->
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  The dialog  */
name|options
operator|->
name|query_box
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Path Attributes"
argument_list|)
argument_list|,
literal|"edit_path_attributes"
argument_list|,
name|GIMP_STOCK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Path Attributes"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/paths/edit_path_attributes.html"
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|edit_vectors_query_ok_callback
argument_list|,
name|options
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|options
argument_list|)
expr_stmt|;
comment|/*  The main hbox  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
comment|/*  The vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  The table  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
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
literal|4
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  The name entry  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Path name:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
operator||
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
name|options
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|options
operator|->
name|name_entry
argument_list|,
literal|150
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|options
operator|->
name|name_entry
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


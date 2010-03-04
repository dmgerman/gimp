begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextTool  * Copyright (C) 2002-2010  Sven Neumann<sven@gimp.org>  *                          Daniel Eddeland<danedde@svn.gnome.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_TOOL_H__
define|#
directive|define
name|__GIMP_TEXT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TEXT_TOOL
define|#
directive|define
name|GIMP_TYPE_TEXT_TOOL
value|(gimp_text_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_TOOL (obj)
define|#
directive|define
name|GIMP_TEXT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_TOOL, GimpTextTool))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TEXT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_TOOL))
end_define

begin_define
DECL|macro|GIMP_TEXT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT_TOOL, GimpTextToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT_TOOL))
end_define

begin_define
DECL|macro|GIMP_TEXT_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_TEXT_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_TEXT_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpTextTool
typedef|typedef
name|struct
name|_GimpTextTool
name|GimpTextTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTextToolClass
typedef|typedef
name|struct
name|_GimpTextToolClass
name|GimpTextToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextTool
struct|struct
name|_GimpTextTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|proxy
name|GimpText
modifier|*
name|proxy
decl_stmt|;
DECL|member|pending
name|GList
modifier|*
name|pending
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|moving
name|gboolean
name|moving
decl_stmt|;
DECL|member|buffer
name|GimpTextBuffer
modifier|*
name|buffer
decl_stmt|;
DECL|member|text
name|GimpText
modifier|*
name|text
decl_stmt|;
DECL|member|layer
name|GimpTextLayer
modifier|*
name|layer
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|confirm_dialog
name|GtkWidget
modifier|*
name|confirm_dialog
decl_stmt|;
DECL|member|ui_manager
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
DECL|member|handle_rectangle_change_complete
name|gboolean
name|handle_rectangle_change_complete
decl_stmt|;
DECL|member|text_box_fixed
name|gboolean
name|text_box_fixed
decl_stmt|;
DECL|member|layout
name|GimpTextLayout
modifier|*
name|layout
decl_stmt|;
DECL|member|drawing_blocked
name|gboolean
name|drawing_blocked
decl_stmt|;
comment|/* text editor state: */
DECL|member|style_overlay
name|GtkWidget
modifier|*
name|style_overlay
decl_stmt|;
DECL|member|style_editor
name|GtkWidget
modifier|*
name|style_editor
decl_stmt|;
DECL|member|selecting
name|gboolean
name|selecting
decl_stmt|;
DECL|member|select_start_iter
name|GtkTextIter
name|select_start_iter
decl_stmt|;
DECL|member|select_words
name|gboolean
name|select_words
decl_stmt|;
DECL|member|select_lines
name|gboolean
name|select_lines
decl_stmt|;
DECL|member|im_context
name|GtkIMContext
modifier|*
name|im_context
decl_stmt|;
DECL|member|needs_im_reset
name|gboolean
name|needs_im_reset
decl_stmt|;
DECL|member|preedit_overlay
name|GtkWidget
modifier|*
name|preedit_overlay
decl_stmt|;
DECL|member|preedit_label
name|GtkWidget
modifier|*
name|preedit_label
decl_stmt|;
DECL|member|preedit_string
name|gchar
modifier|*
name|preedit_string
decl_stmt|;
DECL|member|preedit_cursor
name|gint
name|preedit_cursor
decl_stmt|;
DECL|member|overwrite_mode
name|gboolean
name|overwrite_mode
decl_stmt|;
DECL|member|x_pos
name|gint
name|x_pos
decl_stmt|;
DECL|member|offscreen_window
name|GtkWidget
modifier|*
name|offscreen_window
decl_stmt|;
DECL|member|proxy_text_view
name|GtkWidget
modifier|*
name|proxy_text_view
decl_stmt|;
DECL|member|editor_dialog
name|GtkWidget
modifier|*
name|editor_dialog
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextToolClass
struct|struct
name|_GimpTextToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_text_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_text_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_text_tool_set_layer
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_tool_get_has_text_selection
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_delete_selection
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_cut_clipboard
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_copy_clipboard
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_paste_clipboard
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_create_vectors
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_create_vectors_warped
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  only for the text editor  */
end_comment

begin_function_decl
name|void
name|gimp_text_tool_clear_layout
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_ensure_layout
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_TOOL_H__ */
end_comment

end_unit


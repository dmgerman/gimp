begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfgbgeditor.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FG_BG_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FG_BG_EDITOR_H__
define|#
directive|define
name|__GIMP_FG_BG_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdrawingarea.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_FG_BG_EDITOR
define|#
directive|define
name|GIMP_TYPE_FG_BG_EDITOR
value|(gimp_fg_bg_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_FG_BG_EDITOR (obj)
define|#
directive|define
name|GIMP_FG_BG_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FG_BG_EDITOR, GimpFgBgEditor))
end_define

begin_define
DECL|macro|GIMP_FG_BG_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_FG_BG_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FG_BG_EDITOR, GimpFgBgEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_FG_BG_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_FG_BG_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FG_BG_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_FG_BG_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FG_BG_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FG_BG_EDITOR))
end_define

begin_define
DECL|macro|GIMP_FG_BG_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FG_BG_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FG_BG_EDITOR, GimpFgBgEditorClass))
end_define

begin_typedef
DECL|typedef|GimpFgBgEditorClass
typedef|typedef
name|struct
name|_GimpFgBgEditorClass
name|GimpFgBgEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFgBgEditor
struct|struct
name|_GimpFgBgEditor
block|{
DECL|member|parent_instance
name|GtkDrawingArea
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|active_color
name|GimpActiveColor
name|active_color
decl_stmt|;
DECL|member|render_buf
name|guchar
modifier|*
name|render_buf
decl_stmt|;
DECL|member|render_buf_size
name|gint
name|render_buf_size
decl_stmt|;
DECL|member|default_icon
name|GdkPixbuf
modifier|*
name|default_icon
decl_stmt|;
DECL|member|swap_icon
name|GdkPixbuf
modifier|*
name|swap_icon
decl_stmt|;
DECL|member|rect_width
name|gint
name|rect_width
decl_stmt|;
DECL|member|rect_height
name|gint
name|rect_height
decl_stmt|;
DECL|member|click_target
name|gint
name|click_target
decl_stmt|;
DECL|member|dnd_target
name|gint
name|dnd_target
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFgBgEditorClass
struct|struct
name|_GimpFgBgEditorClass
block|{
DECL|member|parent_class
name|GtkDrawingAreaClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|color_clicked
name|void
function_decl|(
modifier|*
name|color_clicked
function_decl|)
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|GimpActiveColor
name|color
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_fg_bg_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_fg_bg_editor_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_fg_bg_editor_set_context
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_fg_bg_editor_set_active
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|GimpActiveColor
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_FG_BG_EDITOR_H__  */
end_comment

end_unit


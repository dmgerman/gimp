begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DND_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DND_H__
define|#
directive|define
name|__GIMP_DND_H__
end_define

begin_enum
enum|enum
DECL|enum|__anon2b87170c0103
block|{
DECL|enumerator|GIMP_DND_TYPE_URI_LIST
name|GIMP_DND_TYPE_URI_LIST
block|,
DECL|enumerator|GIMP_DND_TYPE_TEXT_PLAIN
name|GIMP_DND_TYPE_TEXT_PLAIN
block|,
DECL|enumerator|GIMP_DND_TYPE_NETSCAPE_URL
name|GIMP_DND_TYPE_NETSCAPE_URL
block|,
DECL|enumerator|GIMP_DND_TYPE_IMAGE
name|GIMP_DND_TYPE_IMAGE
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER
name|GIMP_DND_TYPE_LAYER
block|,
DECL|enumerator|GIMP_DND_TYPE_CHANNEL
name|GIMP_DND_TYPE_CHANNEL
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER_MASK
name|GIMP_DND_TYPE_LAYER_MASK
block|,
DECL|enumerator|GIMP_DND_TYPE_COMPONENT
name|GIMP_DND_TYPE_COMPONENT
block|,
DECL|enumerator|GIMP_DND_TYPE_PATH
name|GIMP_DND_TYPE_PATH
block|,
DECL|enumerator|GIMP_DND_TYPE_COLOR
name|GIMP_DND_TYPE_COLOR
block|,
DECL|enumerator|GIMP_DND_TYPE_BRUSH
name|GIMP_DND_TYPE_BRUSH
block|,
DECL|enumerator|GIMP_DND_TYPE_PATTERN
name|GIMP_DND_TYPE_PATTERN
block|,
DECL|enumerator|GIMP_DND_TYPE_GRADIENT
name|GIMP_DND_TYPE_GRADIENT
block|,
DECL|enumerator|GIMP_DND_TYPE_PALETTE
name|GIMP_DND_TYPE_PALETTE
block|,
DECL|enumerator|GIMP_DND_TYPE_TOOL
name|GIMP_DND_TYPE_TOOL
block|,
DECL|enumerator|GIMP_DND_TYPE_DIALOG
name|GIMP_DND_TYPE_DIALOG
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TARGET_URI_LIST
define|#
directive|define
name|GIMP_TARGET_URI_LIST
define|\
value|{ "text/uri-list", 0, GIMP_DND_TYPE_URI_LIST }
end_define

begin_define
DECL|macro|GIMP_TARGET_TEXT_PLAIN
define|#
directive|define
name|GIMP_TARGET_TEXT_PLAIN
define|\
value|{ "text/plain", 0, GIMP_DND_TYPE_TEXT_PLAIN }
end_define

begin_define
DECL|macro|GIMP_TARGET_NETSCAPE_URL
define|#
directive|define
name|GIMP_TARGET_NETSCAPE_URL
define|\
value|{ "_NETSCAPE_URL", 0, GIMP_DND_TYPE_NETSCAPE_URL }
end_define

begin_define
DECL|macro|GIMP_TARGET_IMAGE
define|#
directive|define
name|GIMP_TARGET_IMAGE
define|\
value|{ "GIMP_IMAGE", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_IMAGE }
end_define

begin_define
DECL|macro|GIMP_TARGET_LAYER
define|#
directive|define
name|GIMP_TARGET_LAYER
define|\
value|{ "GIMP_LAYER", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_LAYER }
end_define

begin_define
DECL|macro|GIMP_TARGET_CHANNEL
define|#
directive|define
name|GIMP_TARGET_CHANNEL
define|\
value|{ "GIMP_CHANNEL", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_CHANNEL }
end_define

begin_define
DECL|macro|GIMP_TARGET_LAYER_MASK
define|#
directive|define
name|GIMP_TARGET_LAYER_MASK
define|\
value|{ "GIMP_LAYER_MASK", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_LAYER_MASK }
end_define

begin_define
DECL|macro|GIMP_TARGET_COMPONENT
define|#
directive|define
name|GIMP_TARGET_COMPONENT
define|\
value|{ "GIMP_COMPONENT", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_COMPONENT }
end_define

begin_define
DECL|macro|GIMP_TARGET_PATH
define|#
directive|define
name|GIMP_TARGET_PATH
define|\
value|{ "GIMP_PATH", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_PATH }
end_define

begin_define
DECL|macro|GIMP_TARGET_COLOR
define|#
directive|define
name|GIMP_TARGET_COLOR
define|\
value|{ "application/x-color", 0, GIMP_DND_TYPE_COLOR }
end_define

begin_define
DECL|macro|GIMP_TARGET_BRUSH
define|#
directive|define
name|GIMP_TARGET_BRUSH
define|\
value|{ "GIMP_BRUSH", 0, GIMP_DND_TYPE_BRUSH }
end_define

begin_define
DECL|macro|GIMP_TARGET_PATTERN
define|#
directive|define
name|GIMP_TARGET_PATTERN
define|\
value|{ "GIMP_PATTERN", 0, GIMP_DND_TYPE_PATTERN }
end_define

begin_define
DECL|macro|GIMP_TARGET_GRADIENT
define|#
directive|define
name|GIMP_TARGET_GRADIENT
define|\
value|{ "GIMP_GRADIENT", 0, GIMP_DND_TYPE_GRADIENT }
end_define

begin_define
DECL|macro|GIMP_TARGET_PALETTE
define|#
directive|define
name|GIMP_TARGET_PALETTE
define|\
value|{ "GIMP_PALETTE", 0, GIMP_DND_TYPE_PALETTE }
end_define

begin_define
DECL|macro|GIMP_TARGET_TOOL
define|#
directive|define
name|GIMP_TARGET_TOOL
define|\
value|{ "GIMP_TOOL", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_TOOL }
end_define

begin_define
DECL|macro|GIMP_TARGET_DIALOG
define|#
directive|define
name|GIMP_TARGET_DIALOG
define|\
value|{ "GIMP_DIALOG", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_DIALOG }
end_define

begin_comment
comment|/*  file / url dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDropFileFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropFileFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GList
modifier|*
name|files
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_file_dest_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDropFileFunc
name|set_file_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_file_dest_unset
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  standard callback  */
end_comment

begin_function_decl
name|void
name|gimp_dnd_open_files
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GList
modifier|*
name|files
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  color dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDropColorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropColorFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDragColorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDragColorFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_color_source_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDragColorFunc
name|get_color_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_color_dest_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDropColorFunc
name|set_color_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_color_dest_unset
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GimpViewable (by GtkType) dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDropViewableFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropViewableFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDragViewableFunc
typedef|typedef
name|GimpViewable
modifier|*
function_decl|(
modifier|*
name|GimpDndDragViewableFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_gtk_drag_source_set_by_type
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|start_button_mask
parameter_list|,
name|GtkType
name|type
parameter_list|,
name|GdkDragAction
name|actions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gtk_drag_dest_set_by_type
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkDestDefaults
name|flags
parameter_list|,
name|GtkType
name|type
parameter_list|,
name|GdkDragAction
name|actions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_viewable_source_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkType
name|type
parameter_list|,
name|GimpDndDragViewableFunc
name|get_viewable_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_viewable_source_unset
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_viewable_dest_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkType
name|type
parameter_list|,
name|GimpDndDropViewableFunc
name|set_viewable_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_viewable_dest_unset
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpViewable
modifier|*
name|gimp_dnd_get_drag_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  OLD drawable dnd functions  */
end_comment

begin_function_decl
name|void
name|gimp_dnd_set_drawable_preview_icon
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DND_H__ */
end_comment

end_unit


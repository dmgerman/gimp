begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LC_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__LC_DIALOG_H__
define|#
directive|define
name|__LC_DIALOG_H__
end_define

begin_define
DECL|macro|PREVIEW_EVENT_MASK
define|#
directive|define
name|PREVIEW_EVENT_MASK
value|(GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK | \                             GDK_ENTER_NOTIFY_MASK)
end_define

begin_define
DECL|macro|BUTTON_EVENT_MASK
define|#
directive|define
name|BUTTON_EVENT_MASK
value|(GDK_EXPOSURE_MASK | GDK_ENTER_NOTIFY_MASK | \                             GDK_LEAVE_NOTIFY_MASK | GDK_BUTTON_PRESS_MASK | \                             GDK_BUTTON_RELEASE_MASK)
end_define

begin_define
DECL|macro|LIST_WIDTH
define|#
directive|define
name|LIST_WIDTH
value|200
end_define

begin_define
DECL|macro|LIST_HEIGHT
define|#
directive|define
name|LIST_HEIGHT
value|150
end_define

begin_define
DECL|macro|NORMAL
define|#
directive|define
name|NORMAL
value|0
end_define

begin_define
DECL|macro|SELECTED
define|#
directive|define
name|SELECTED
value|1
end_define

begin_define
DECL|macro|INSENSITIVE
define|#
directive|define
name|INSENSITIVE
value|2
end_define

begin_typedef
DECL|typedef|LCDialog
typedef|typedef
name|struct
name|_LCDialog
name|LCDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_LCDialog
struct|struct
name|_LCDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|subshell
name|GtkWidget
modifier|*
name|subshell
decl_stmt|;
DECL|member|image_menu
name|GtkWidget
modifier|*
name|image_menu
decl_stmt|;
DECL|member|image_option_menu
name|GtkWidget
modifier|*
name|image_option_menu
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|auto_follow_active
name|gboolean
name|auto_follow_active
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Main dialog structure  */
end_comment

begin_decl_stmt
specifier|extern
name|LCDialog
modifier|*
name|lc_dialog
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|lc_dialog_create
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|lc_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  implies free& create  */
end_comment

begin_function_decl
name|void
name|lc_dialog_rebuild
parameter_list|(
name|gint
name|new_preview_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|lc_dialog_flush
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|lc_dialog_update_image_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|lc_dialog_preview_update
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|lc_dialog_menu_preview_dirty
parameter_list|(
name|GtkObject
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __LC_DIALOG_H__  */
end_comment

end_unit


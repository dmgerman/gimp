begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LAYERS_DIALOGP_H__
end_ifndef

begin_define
DECL|macro|__LAYERS_DIALOGP_H__
define|#
directive|define
name|__LAYERS_DIALOGP_H__
end_define

begin_include
include|#
directive|include
file|"buildmenu.h"
end_include

begin_function_decl
name|GtkWidget
modifier|*
name|layers_dialog_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|channels_dialog_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|create_image_menu
parameter_list|(
name|GimpImage
modifier|*
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|MenuItemCallback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layers_dialog_update
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channels_dialog_update
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layers_dialog_clear
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channels_dialog_clear
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layers_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channels_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|render_fs_preview
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkPixmap
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|render_preview
parameter_list|(
name|TempBuf
modifier|*
parameter_list|,
name|GtkWidget
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Main dialog widget  */
end_comment

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|lc_shell
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __LAYERS_DIALOGP_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GRADIENT_SELECT_H__
end_ifndef

begin_define
DECL|macro|__GRADIENT_SELECT_H__
define|#
directive|define
name|__GRADIENT_SELECT_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_define
DECL|macro|GRADIENT_SAMPLE_SIZE
define|#
directive|define
name|GRADIENT_SAMPLE_SIZE
value|40
end_define

begin_typedef
DECL|typedef|GradientSelect
typedef|typedef
name|struct
name|_GradientSelect
name|GradientSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_GradientSelect
struct|struct
name|_GradientSelect
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|clist
name|GtkWidget
modifier|*
name|clist
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|callback_name
name|gchar
modifier|*
name|callback_name
decl_stmt|;
DECL|member|sample_size
name|gint
name|sample_size
decl_stmt|;
DECL|member|dnd_gradient
name|gradient_t
modifier|*
name|dnd_gradient
decl_stmt|;
DECL|member|black
name|GdkColor
name|black
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  list of active dialogs    */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|gradient_active_dialogs
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the main gradient selection dialog  */
end_comment

begin_decl_stmt
specifier|extern
name|GradientSelect
modifier|*
name|gradient_select_dialog
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GradientSelect
modifier|*
name|gradient_select_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|initial_gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_select_free
parameter_list|(
name|GradientSelect
modifier|*
name|gsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_select_rename_all
parameter_list|(
name|gint
name|n
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_select_insert_all
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_select_delete_all
parameter_list|(
name|gint
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_select_free_all
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_select_refill_all
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_select_update_all
parameter_list|(
name|gint
name|row
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradients_check_dialogs
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the main gradient selection  */
end_comment

begin_function_decl
name|void
name|gradient_dialog_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GRADIENT_SELECT_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2002 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_DEFAULT_DIALOG_H
end_ifndef

begin_define
DECL|macro|_IMAP_DEFAULT_DIALOG_H
define|#
directive|define
name|_IMAP_DEFAULT_DIALOG_H
end_define

begin_typedef
DECL|struct|__anon2bd34f8e0108
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|ok
name|GtkWidget
modifier|*
name|ok
decl_stmt|;
DECL|member|apply
name|GtkWidget
modifier|*
name|apply
decl_stmt|;
DECL|member|cancel
name|GtkWidget
modifier|*
name|cancel
decl_stmt|;
DECL|member|help
name|GtkWidget
modifier|*
name|help
decl_stmt|;
DECL|member|ok_cb
name|void
function_decl|(
modifier|*
name|ok_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
function_decl|;
DECL|member|ok_cb_data
name|gpointer
name|ok_cb_data
decl_stmt|;
DECL|member|apply_cb
name|void
function_decl|(
modifier|*
name|apply_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
function_decl|;
DECL|member|apply_cb_data
name|gpointer
name|apply_cb_data
decl_stmt|;
DECL|member|cancel_cb
name|void
function_decl|(
modifier|*
name|cancel_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
function_decl|;
DECL|member|cancel_cb_data
name|gpointer
name|cancel_cb_data
decl_stmt|;
DECL|typedef|DefaultDialog_t
block|}
name|DefaultDialog_t
typedef|;
end_typedef

begin_function_decl
name|DefaultDialog_t
modifier|*
name|make_default_dialog
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_set_ok_cb
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|void
function_decl|(
modifier|*
name|ok_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
parameter_list|,
name|gpointer
name|ok_cb_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_set_apply_cb
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|void
function_decl|(
modifier|*
name|apply_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
parameter_list|,
name|gpointer
name|apply_cb_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_set_cancel_cb
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|void
function_decl|(
modifier|*
name|ok_cb
function_decl|)
parameter_list|(
name|gpointer
parameter_list|)
parameter_list|,
name|gpointer
name|ok_cb_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_show
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_hide_cancel_button
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_hide_apply_button
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_hide_help_button
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_set_title
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|default_dialog_set_label
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|default_dialog_add_table
parameter_list|(
name|DefaultDialog_t
modifier|*
name|dialog
parameter_list|,
name|gint
name|rows
parameter_list|,
name|gint
name|cols
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_DEFAULT_DIALOG_H */
end_comment

end_unit


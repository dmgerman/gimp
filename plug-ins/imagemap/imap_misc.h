begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_MISC_H
end_ifndef

begin_define
DECL|macro|_IMAP_MISC_H
define|#
directive|define
name|_IMAP_MISC_H
end_define

begin_function_decl
name|void
name|toolbar_add_space
parameter_list|(
name|GtkWidget
modifier|*
name|toolbar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|make_toolbar_stock_icon
parameter_list|(
name|GtkWidget
modifier|*
name|toolbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|char
modifier|*
name|identifier
parameter_list|,
specifier|const
name|char
modifier|*
name|tooltip
parameter_list|,
name|void
function_decl|(
modifier|*
name|callback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
parameter_list|,
name|gpointer
name|udata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_sash_size
parameter_list|(
name|gboolean
name|double_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_sash
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|near_sash
parameter_list|(
name|gint
name|sash_x
parameter_list|,
name|gint
name|sash_y
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_MISC_H */
end_comment

end_unit


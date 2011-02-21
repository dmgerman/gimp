begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
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
name|cairo_t
modifier|*
name|cr
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


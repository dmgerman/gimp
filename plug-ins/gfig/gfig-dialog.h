begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GFIG_DIALOG_H__
define|#
directive|define
name|__GFIG_DIALOG_H__
end_define

begin_define
DECL|macro|RESPONSE_UNDO
define|#
directive|define
name|RESPONSE_UNDO
value|1
end_define

begin_define
DECL|macro|RESPONSE_CLEAR
define|#
directive|define
name|RESPONSE_CLEAR
value|2
end_define

begin_define
DECL|macro|RESPONSE_SAVE
define|#
directive|define
name|RESPONSE_SAVE
value|3
end_define

begin_define
DECL|macro|RESPONSE_PAINT
define|#
directive|define
name|RESPONSE_PAINT
value|4
end_define

begin_function_decl
name|gint
name|gfig_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|update_options
parameter_list|(
name|GFigObj
modifier|*
name|old_obj
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|undo_water_mark
name|gint
name|undo_water_mark
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|undo_water_mark
comment|/* Last slot filled in -1 = no undo */
end_comment

begin_decl_stmt
DECL|variable|undo_table
name|DAllObjs
modifier|*
name|undo_table
index|[
name|MAX_UNDO
index|]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GFIG_DIALOG_H__ */
end_comment

end_unit


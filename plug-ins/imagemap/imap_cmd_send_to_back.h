begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_CMD_SEND_TO_BACK_H
end_ifndef

begin_define
DECL|macro|_IMAP_CMD_SEND_TO_BACK_H
define|#
directive|define
name|_IMAP_CMD_SEND_TO_BACK_H
end_define

begin_include
include|#
directive|include
file|"imap_command.h"
end_include

begin_include
include|#
directive|include
file|"imap_object.h"
end_include

begin_function_decl
name|Command_t
modifier|*
name|send_to_back_command_new
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_CMD_SEND_TO_BACK_H */
end_comment

end_unit


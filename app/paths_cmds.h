begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  * Some of this code is based on the layers_dialog box code.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PATHS_CMDS_H__
end_ifndef

begin_define
DECL|macro|__PATHS_CMDS_H__
define|#
directive|define
name|__PATHS_CMDS_H__
end_define

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_decl_stmt
specifier|extern
name|ProcRecord
name|path_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|path_get_points_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|path_get_current_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|path_set_current_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|path_set_points_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|path_stroke_current_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
endif|__PATHS_CMDS_H__
end_endif

end_unit


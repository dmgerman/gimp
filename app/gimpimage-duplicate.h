begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CHANNEL_OPS_H__
end_ifndef

begin_define
DECL|macro|__CHANNEL_OPS_H__
define|#
directive|define
name|__CHANNEL_OPS_H__
end_define

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_typedef
DECL|enum|__anon27caf2f50103
typedef|typedef
enum|enum
block|{
DECL|enumerator|OFFSET_BACKGROUND
name|OFFSET_BACKGROUND
block|,
DECL|enumerator|OFFSET_TRANSPARENT
name|OFFSET_TRANSPARENT
DECL|typedef|ChannelOffsetType
block|}
name|ChannelOffsetType
typedef|;
end_typedef

begin_comment
comment|/*  channel_ops functions  */
end_comment

begin_function_decl
name|void
name|channel_ops_offset
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Procedure definition and marshalling function  */
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|channel_ops_offset_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __CHANNEL_OPS_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BUCKET_FILL_H__
end_ifndef

begin_define
DECL|macro|__BUCKET_FILL_H__
define|#
directive|define
name|__BUCKET_FILL_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b03d58d0103
block|{
DECL|enumerator|FgColorFill
name|FgColorFill
block|,
DECL|enumerator|BgColorFill
name|BgColorFill
block|,
DECL|enumerator|PatternFill
name|PatternFill
DECL|typedef|FillMode
block|}
name|FillMode
typedef|;
end_typedef

begin_function_decl
name|Tool
modifier|*
name|tools_new_bucket_fill
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_bucket_fill
parameter_list|(
name|Tool
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
name|bucket_fill_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BUCKET_FILL_H__  */
end_comment

end_unit


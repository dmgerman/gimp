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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c969dcd0103
block|{
DECL|enumerator|FG_BUCKET_FILL
name|FG_BUCKET_FILL
block|,
DECL|enumerator|BG_BUCKET_FILL
name|BG_BUCKET_FILL
block|,
DECL|enumerator|PATTERN_BUCKET_FILL
name|PATTERN_BUCKET_FILL
DECL|typedef|BucketFillMode
block|}
name|BucketFillMode
typedef|;
end_typedef

begin_function_decl
name|void
name|bucket_fill
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|BucketFillMode
name|fill_mode
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bucket_fill_region
parameter_list|(
name|BucketFillMode
name|fill_mode
parameter_list|,
name|PixelRegion
modifier|*
name|bufPR
parameter_list|,
name|PixelRegion
modifier|*
name|maskPR
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|,
name|TempBuf
modifier|*
name|pattern
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|)
function_decl|;
end_function_decl

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
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BUCKET_FILL_H__  */
end_comment

end_unit


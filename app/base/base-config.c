begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"base-config.h"
end_include

begin_decl_stmt
DECL|variable|static_base_config
specifier|static
name|GimpBaseConfig
name|static_base_config
init|=
block|{
operator|.
name|temp_path
operator|=
name|NULL
block|,
operator|.
name|swap_path
operator|=
name|NULL
block|,
operator|.
name|tile_cache_size
operator|=
literal|33554432
block|,
operator|.
name|stingy_memory_use
operator|=
name|FALSE
block|,
operator|.
name|interpolation_type
operator|=
name|LINEAR_INTERPOLATION
block|,
operator|.
name|num_processors
operator|=
literal|1
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|base_config
name|GimpBaseConfig
modifier|*
name|base_config
init|=
operator|&
name|static_base_config
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_mmx
name|gboolean
name|use_mmx
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

end_unit


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
file|<glib-object.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_define
DECL|macro|INIT_MEMBER (m,v)
define|#
directive|define
name|INIT_MEMBER
parameter_list|(
name|m
parameter_list|,
name|v
parameter_list|)
value|.m = v
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* declaration order required ! */
end_comment

begin_define
DECL|macro|INIT_MEMBER (m,v)
define|#
directive|define
name|INIT_MEMBER
parameter_list|(
name|m
parameter_list|,
name|v
parameter_list|)
value|v
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|static_base_config
specifier|static
name|GimpBaseConfig
name|static_base_config
init|=
block|{
name|INIT_MEMBER
argument_list|(
name|temp_path
argument_list|,
name|NULL
argument_list|)
block|,
name|INIT_MEMBER
argument_list|(
name|swap_path
argument_list|,
name|NULL
argument_list|)
block|,
name|INIT_MEMBER
argument_list|(
name|tile_cache_size
argument_list|,
literal|33554432
argument_list|)
block|,
name|INIT_MEMBER
argument_list|(
name|stingy_memory_use
argument_list|,
name|FALSE
argument_list|)
block|,
name|INIT_MEMBER
argument_list|(
name|interpolation_type
argument_list|,
name|GIMP_LINEAR_INTERPOLATION
argument_list|)
block|,
name|INIT_MEMBER
argument_list|(
argument|num_processors
argument_list|,
literal|1
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_undef
undef|#
directive|undef
name|INIT_MEMBER
end_undef

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


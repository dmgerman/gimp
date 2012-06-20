begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl.c  * Copyright (C) 2007 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpgeglconfig.h"
end_include

begin_include
include|#
directive|include
file|"operations/gimp-operations.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_gegl_notify_tile_cache_size
parameter_list|(
name|GimpGeglConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gegl_notify_num_processors
parameter_list|(
name|GimpGeglConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_gegl_init (Gimp * gimp)
name|gimp_gegl_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGeglConfig
modifier|*
name|config
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GEGL_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|limiting tile cache size to G_MAXINT
endif|#
directive|endif
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|not setting GeglConfig:threads
endif|#
directive|endif
name|g_object_set
argument_list|(
name|gegl_config
argument_list|()
argument_list|,
if|#
directive|if
literal|0
argument_list|"tile-width",  TILE_WIDTH,                 "tile-height", TILE_HEIGHT,
endif|#
directive|endif
literal|"cache-size"
argument_list|,
operator|(
name|gint
operator|)
name|MIN
argument_list|(
name|config
operator|->
name|tile_cache_size
argument_list|,
name|G_MAXINT
argument_list|)
argument_list|,
if|#
directive|if
literal|0
argument_list|"threads",     config->num_processors,
endif|#
directive|endif
name|NULL
argument_list|)
expr_stmt|;
comment|/* turn down the precision of babl - permitting use of lookup tables for    * gamma conversions, this precision is anyways high enough for both 8bit    * and 16bit operation    */
name|g_object_set
argument_list|(
name|gegl_config
argument_list|()
argument_list|,
literal|"babl-tolerance"
argument_list|,
literal|0.00015
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::tile-cache-size"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_notify_tile_cache_size
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::num-processors"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_notify_num_processors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_babl_init
argument_list|()
expr_stmt|;
name|gimp_operations_init
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_notify_tile_cache_size (GimpGeglConfig * config)
name|gimp_gegl_notify_tile_cache_size
parameter_list|(
name|GimpGeglConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|gegl_config
argument_list|()
argument_list|,
literal|"cache-size"
argument_list|,
operator|(
name|gint
operator|)
name|MIN
argument_list|(
name|config
operator|->
name|tile_cache_size
argument_list|,
name|G_MAXINT
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_notify_num_processors (GimpGeglConfig * config)
name|gimp_gegl_notify_num_processors
parameter_list|(
name|GimpGeglConfig
modifier|*
name|config
parameter_list|)
block|{
if|#
directive|if
literal|0
block|g_object_set (gegl_config (),                 "threads", config->num_processors,                 NULL);
endif|#
directive|endif
block|}
end_function

end_unit


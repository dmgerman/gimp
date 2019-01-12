begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimptilebackendtilemanager.c  * Copyright (C) 2012 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_define
DECL|macro|GIMP_DISABLE_DEPRECATION_WARNINGS
define|#
directive|define
name|GIMP_DISABLE_DEPRECATION_WARNINGS
end_define

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimptilebackendplugin.h"
end_include

begin_define
DECL|macro|TILE_WIDTH
define|#
directive|define
name|TILE_WIDTH
value|gimp_tile_width()
end_define

begin_define
DECL|macro|TILE_HEIGHT
define|#
directive|define
name|TILE_HEIGHT
value|gimp_tile_height()
end_define

begin_struct
DECL|struct|_GimpTileBackendPluginPrivate
struct|struct
name|_GimpTileBackendPluginPrivate
block|{
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|shadow
name|gboolean
name|shadow
decl_stmt|;
DECL|member|mul
name|gint
name|mul
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|gint
DECL|function|gimp_gegl_tile_mul (void)
name|gimp_gegl_tile_mul
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gint
name|mul
init|=
literal|2
decl_stmt|;
specifier|static
name|gboolean
name|inited
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|G_LIKELY
argument_list|(
name|inited
argument_list|)
condition|)
return|return
name|mul
return|;
name|inited
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|g_getenv
argument_list|(
literal|"GIMP_GEGL_TILE_MUL"
argument_list|)
condition|)
name|mul
operator|=
name|atoi
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_GEGL_TILE_MUL"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|mul
operator|<
literal|1
condition|)
name|mul
operator|=
literal|1
expr_stmt|;
return|return
name|mul
return|;
block|}
end_function

begin_function_decl
specifier|static
name|void
name|gimp_tile_backend_plugin_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|gimp_tile_backend_plugin_command
parameter_list|(
name|GeglTileSource
modifier|*
name|tile_store
parameter_list|,
name|GeglTileCommand
name|command
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|z
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_write_mul
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|source
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglTile
modifier|*
name|gimp_tile_read_mul
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpTileBackendPlugin,_gimp_tile_backend_plugin,GEGL_TYPE_TILE_BACKEND)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpTileBackendPlugin
argument_list|,
argument|_gimp_tile_backend_plugin
argument_list|,
argument|GEGL_TYPE_TILE_BACKEND
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|_gimp_tile_backend_plugin_parent_class
end_define

begin_decl_stmt
specifier|static
name|GMutex
name|backend_plugin_mutex
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
name|_gimp_tile_backend_plugin_class_init
parameter_list|(
name|GimpTileBackendPluginClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tile_backend_plugin_finalize
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|64
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|_gimp_tile_backend_plugin_init (GimpTileBackendPlugin * backend)
name|_gimp_tile_backend_plugin_init
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend
parameter_list|)
block|{
name|GeglTileSource
modifier|*
name|source
init|=
name|GEGL_TILE_SOURCE
argument_list|(
name|backend
argument_list|)
decl_stmt|;
name|backend
operator|->
name|priv
operator|=
name|_gimp_tile_backend_plugin_get_instance_private
argument_list|(
name|backend
argument_list|)
expr_stmt|;
name|source
operator|->
name|command
operator|=
name|gimp_tile_backend_plugin_command
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_backend_plugin_finalize (GObject * object)
name|gimp_tile_backend_plugin_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTileBackendPlugin
modifier|*
name|backend
init|=
name|GIMP_TILE_BACKEND_PLUGIN
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|backend
operator|->
name|priv
operator|->
name|drawable
condition|)
comment|/* This also causes a flush */
name|gimp_drawable_detach
argument_list|(
name|backend
operator|->
name|priv
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|gimp_tile_backend_plugin_command (GeglTileSource * tile_store,GeglTileCommand command,gint x,gint y,gint z,gpointer data)
name|gimp_tile_backend_plugin_command
parameter_list|(
name|GeglTileSource
modifier|*
name|tile_store
parameter_list|,
name|GeglTileCommand
name|command
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|z
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
init|=
name|GIMP_TILE_BACKEND_PLUGIN
argument_list|(
name|tile_store
argument_list|)
decl_stmt|;
name|gpointer
name|result
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|command
condition|)
block|{
case|case
name|GEGL_TILE_GET
case|:
comment|/* TODO: fetch mipmapped tiles directly from gimp, instead of returning        * NULL to render them locally        */
if|if
condition|(
name|z
operator|==
literal|0
condition|)
block|{
name|g_mutex_lock
argument_list|(
operator|&
name|backend_plugin_mutex
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_tile_read_mul
argument_list|(
name|backend_plugin
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|backend_plugin_mutex
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GEGL_TILE_SET
case|:
comment|/* TODO: actually store mipmapped tiles */
if|if
condition|(
name|z
operator|==
literal|0
condition|)
block|{
name|g_mutex_lock
argument_list|(
operator|&
name|backend_plugin_mutex
argument_list|)
expr_stmt|;
name|gimp_tile_write_mul
argument_list|(
name|backend_plugin
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|gegl_tile_get_data
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|backend_plugin_mutex
argument_list|)
expr_stmt|;
block|}
name|gegl_tile_mark_as_stored
argument_list|(
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GEGL_TILE_FLUSH
case|:
name|g_mutex_lock
argument_list|(
operator|&
name|backend_plugin_mutex
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|backend_plugin
operator|->
name|priv
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
operator|&
name|backend_plugin_mutex
argument_list|)
expr_stmt|;
break|break;
default|default:
name|result
operator|=
name|gegl_tile_backend_command
argument_list|(
name|GEGL_TILE_BACKEND
argument_list|(
name|tile_store
argument_list|)
argument_list|,
name|command
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|z
argument_list|,
name|data
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|GeglTile
modifier|*
DECL|function|gimp_tile_read_mul (GimpTileBackendPlugin * backend_plugin,gint x,gint y)
name|gimp_tile_read_mul
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpTileBackendPluginPrivate
modifier|*
name|priv
init|=
name|backend_plugin
operator|->
name|priv
decl_stmt|;
name|GeglTileBackend
modifier|*
name|backend
init|=
name|GEGL_TILE_BACKEND
argument_list|(
name|backend_plugin
argument_list|)
decl_stmt|;
name|GeglTile
modifier|*
name|tile
decl_stmt|;
name|gint
name|tile_size
decl_stmt|;
name|gint
name|u
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|mul
init|=
name|priv
operator|->
name|mul
decl_stmt|;
name|guchar
modifier|*
name|tile_data
decl_stmt|;
name|x
operator|*=
name|mul
expr_stmt|;
name|y
operator|*=
name|mul
expr_stmt|;
name|tile_size
operator|=
name|gegl_tile_backend_get_tile_size
argument_list|(
name|backend
argument_list|)
expr_stmt|;
name|tile
operator|=
name|gegl_tile_new
argument_list|(
name|tile_size
argument_list|)
expr_stmt|;
name|tile_data
operator|=
name|gegl_tile_get_data
argument_list|(
name|tile
argument_list|)
expr_stmt|;
for|for
control|(
name|u
operator|=
literal|0
init|;
name|u
operator|<
name|mul
condition|;
name|u
operator|++
control|)
block|{
for|for
control|(
name|v
operator|=
literal|0
init|;
name|v
operator|<
name|mul
condition|;
name|v
operator|++
control|)
block|{
name|GimpTile
modifier|*
name|gimp_tile
decl_stmt|;
if|if
condition|(
name|x
operator|+
name|u
operator|>=
name|priv
operator|->
name|drawable
operator|->
name|ntile_cols
operator|||
name|y
operator|+
name|v
operator|>=
name|priv
operator|->
name|drawable
operator|->
name|ntile_rows
condition|)
continue|continue;
name|gimp_tile
operator|=
name|gimp_drawable_get_tile
argument_list|(
name|priv
operator|->
name|drawable
argument_list|,
name|priv
operator|->
name|shadow
argument_list|,
name|y
operator|+
name|v
argument_list|,
name|x
operator|+
name|u
argument_list|)
expr_stmt|;
name|gimp_tile_ref
argument_list|(
name|gimp_tile
argument_list|)
expr_stmt|;
block|{
name|gint
name|ewidth
init|=
name|gimp_tile
operator|->
name|ewidth
decl_stmt|;
name|gint
name|eheight
init|=
name|gimp_tile
operator|->
name|eheight
decl_stmt|;
name|gint
name|bpp
init|=
name|gimp_tile
operator|->
name|bpp
decl_stmt|;
name|gint
name|tile_stride
init|=
name|mul
operator|*
name|TILE_WIDTH
operator|*
name|bpp
decl_stmt|;
name|gint
name|gimp_tile_stride
init|=
name|ewidth
operator|*
name|bpp
decl_stmt|;
name|gint
name|row
decl_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|eheight
condition|;
name|row
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|tile_data
operator|+
operator|(
name|row
operator|+
name|TILE_HEIGHT
operator|*
name|v
operator|)
operator|*
name|tile_stride
operator|+
name|u
operator|*
name|TILE_WIDTH
operator|*
name|bpp
argument_list|,
operator|(
operator|(
name|gchar
operator|*
operator|)
name|gimp_tile
operator|->
name|data
operator|)
operator|+
name|row
operator|*
name|gimp_tile_stride
argument_list|,
name|gimp_tile_stride
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_tile_unref
argument_list|(
name|gimp_tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|tile
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_write_mul (GimpTileBackendPlugin * backend_plugin,gint x,gint y,guchar * source)
name|gimp_tile_write_mul
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|source
parameter_list|)
block|{
name|GimpTileBackendPluginPrivate
modifier|*
name|priv
init|=
name|backend_plugin
operator|->
name|priv
decl_stmt|;
name|gint
name|u
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|mul
init|=
name|priv
operator|->
name|mul
decl_stmt|;
name|x
operator|*=
name|mul
expr_stmt|;
name|y
operator|*=
name|mul
expr_stmt|;
for|for
control|(
name|v
operator|=
literal|0
init|;
name|v
operator|<
name|mul
condition|;
name|v
operator|++
control|)
block|{
for|for
control|(
name|u
operator|=
literal|0
init|;
name|u
operator|<
name|mul
condition|;
name|u
operator|++
control|)
block|{
name|GimpTile
modifier|*
name|gimp_tile
decl_stmt|;
if|if
condition|(
name|x
operator|+
name|u
operator|>=
name|priv
operator|->
name|drawable
operator|->
name|ntile_cols
operator|||
name|y
operator|+
name|v
operator|>=
name|priv
operator|->
name|drawable
operator|->
name|ntile_rows
condition|)
continue|continue;
name|gimp_tile
operator|=
name|gimp_drawable_get_tile
argument_list|(
name|priv
operator|->
name|drawable
argument_list|,
name|priv
operator|->
name|shadow
argument_list|,
name|y
operator|+
name|v
argument_list|,
name|x
operator|+
name|u
argument_list|)
expr_stmt|;
name|gimp_tile_ref
argument_list|(
name|gimp_tile
argument_list|)
expr_stmt|;
block|{
name|gint
name|ewidth
init|=
name|gimp_tile
operator|->
name|ewidth
decl_stmt|;
name|gint
name|eheight
init|=
name|gimp_tile
operator|->
name|eheight
decl_stmt|;
name|gint
name|bpp
init|=
name|gimp_tile
operator|->
name|bpp
decl_stmt|;
name|gint
name|tile_stride
init|=
name|mul
operator|*
name|TILE_WIDTH
operator|*
name|bpp
decl_stmt|;
name|gint
name|gimp_tile_stride
init|=
name|ewidth
operator|*
name|bpp
decl_stmt|;
name|gint
name|row
decl_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|eheight
condition|;
name|row
operator|++
control|)
name|memcpy
argument_list|(
operator|(
operator|(
name|gchar
operator|*
operator|)
name|gimp_tile
operator|->
name|data
operator|)
operator|+
name|row
operator|*
name|gimp_tile_stride
argument_list|,
name|source
operator|+
operator|(
name|row
operator|+
name|v
operator|*
name|TILE_HEIGHT
operator|)
operator|*
name|tile_stride
operator|+
name|u
operator|*
name|TILE_WIDTH
operator|*
name|bpp
argument_list|,
name|gimp_tile_stride
argument_list|)
expr_stmt|;
block|}
name|gimp_tile_unref
argument_list|(
name|gimp_tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|GeglTileBackend
modifier|*
DECL|function|_gimp_tile_backend_plugin_new (GimpDrawable * drawable,gint shadow)
name|_gimp_tile_backend_plugin_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|shadow
parameter_list|)
block|{
name|GeglTileBackend
modifier|*
name|backend
decl_stmt|;
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|width
init|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
decl_stmt|;
name|gint
name|mul
init|=
name|gimp_gegl_tile_mul
argument_list|()
decl_stmt|;
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|backend
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TILE_BACKEND_PLUGIN
argument_list|,
literal|"tile-width"
argument_list|,
name|TILE_WIDTH
operator|*
name|mul
argument_list|,
literal|"tile-height"
argument_list|,
name|TILE_HEIGHT
operator|*
name|mul
argument_list|,
literal|"format"
argument_list|,
name|format
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|backend_plugin
operator|=
name|GIMP_TILE_BACKEND_PLUGIN
argument_list|(
name|backend
argument_list|)
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|mul
operator|=
name|mul
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|shadow
operator|=
name|shadow
expr_stmt|;
name|gegl_tile_backend_set_extent
argument_list|(
name|backend
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|backend
return|;
block|}
end_function

end_unit


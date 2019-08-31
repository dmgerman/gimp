begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptilebackendplugin.c  * Copyright (C) 2011-2019 Ãyvind KolÃ¥s<pippin@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpprotocol.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpwire.h"
end_include

begin_include
include|#
directive|include
file|"gimp-shm.h"
end_include

begin_include
include|#
directive|include
file|"gimplegacy-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-private.h"
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

begin_typedef
DECL|typedef|GimpTile
typedef|typedef
name|struct
name|_GimpTile
name|GimpTile
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTile
struct|struct
name|_GimpTile
block|{
DECL|member|tile_num
name|guint
name|tile_num
decl_stmt|;
comment|/* the number of this tile within the drawable */
DECL|member|ewidth
name|guint
name|ewidth
decl_stmt|;
comment|/* the effective width of the tile */
DECL|member|eheight
name|guint
name|eheight
decl_stmt|;
comment|/* the effective height of the tile */
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/* the pixel data for the tile */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTileBackendPluginPrivate
struct|struct
name|_GimpTileBackendPluginPrivate
block|{
DECL|member|drawable_id
name|gint32
name|drawable_id
decl_stmt|;
DECL|member|shadow
name|gboolean
name|shadow
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
DECL|member|ntile_rows
name|gint
name|ntile_rows
decl_stmt|;
DECL|member|ntile_cols
name|gint
name|ntile_cols
decl_stmt|;
block|}
struct|;
end_struct

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
name|gboolean
name|gimp_tile_write
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
name|GeglTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglTile
modifier|*
name|gimp_tile_read
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

begin_function_decl
specifier|static
name|gboolean
name|gimp_tile_init
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_unset
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_get
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tile_put
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_macro
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
specifier|extern
name|GIOChannel
modifier|*
name|_gimp_readchannel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GIOChannel
modifier|*
name|_gimp_writechannel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|backend_plugin_mutex
specifier|static
name|GMutex
name|backend_plugin_mutex
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|_gimp_tile_backend_plugin_class_init (GimpTileBackendPluginClass * klass)
name|_gimp_tile_backend_plugin_class_init
parameter_list|(
name|GimpTileBackendPluginClass
modifier|*
name|klass
parameter_list|)
block|{ }
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
name|gimp_tile_read
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
name|gimp_tile_write
argument_list|(
name|backend_plugin
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|data
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

begin_comment
comment|/*  public functions  */
end_comment

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
init|=
name|gimp_drawable_get_format
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gint
name|width
init|=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|backend
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TILE_BACKEND_PLUGIN
argument_list|,
literal|"tile-width"
argument_list|,
name|TILE_WIDTH
argument_list|,
literal|"tile-height"
argument_list|,
name|TILE_HEIGHT
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
name|drawable_id
operator|=
name|gimp_item_get_id
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|shadow
operator|=
name|shadow
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|ntile_rows
operator|=
operator|(
name|height
operator|+
name|TILE_HEIGHT
operator|-
literal|1
operator|)
operator|/
name|TILE_HEIGHT
expr_stmt|;
name|backend_plugin
operator|->
name|priv
operator|->
name|ntile_cols
operator|=
operator|(
name|width
operator|+
name|TILE_WIDTH
operator|-
literal|1
operator|)
operator|/
name|TILE_WIDTH
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GeglTile
modifier|*
DECL|function|gimp_tile_read (GimpTileBackendPlugin * backend_plugin,gint x,gint y)
name|gimp_tile_read
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
name|GimpTile
name|gimp_tile
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|tile_size
decl_stmt|;
name|guchar
modifier|*
name|tile_data
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_tile_init
argument_list|(
name|backend_plugin
argument_list|,
operator|&
name|gimp_tile
argument_list|,
name|y
argument_list|,
name|x
argument_list|)
condition|)
return|return
name|NULL
return|;
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
name|gimp_tile_get
argument_list|(
name|backend_plugin
argument_list|,
operator|&
name|gimp_tile
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tile
operator|.
name|ewidth
operator|*
name|gimp_tile
operator|.
name|eheight
operator|*
name|priv
operator|->
name|bpp
operator|==
name|tile_size
condition|)
block|{
name|memcpy
argument_list|(
name|tile_data
argument_list|,
name|gimp_tile
operator|.
name|data
argument_list|,
name|tile_size
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|tile_stride
init|=
name|TILE_WIDTH
operator|*
name|priv
operator|->
name|bpp
decl_stmt|;
name|gint
name|gimp_tile_stride
init|=
name|gimp_tile
operator|.
name|ewidth
operator|*
name|priv
operator|->
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
name|gimp_tile
operator|.
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
name|row
operator|*
name|tile_stride
argument_list|,
name|gimp_tile
operator|.
name|data
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
name|gimp_tile_unset
argument_list|(
name|backend_plugin
argument_list|,
operator|&
name|gimp_tile
argument_list|)
expr_stmt|;
return|return
name|tile
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tile_write (GimpTileBackendPlugin * backend_plugin,gint x,gint y,GeglTile * tile)
name|gimp_tile_write
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
name|GeglTile
modifier|*
name|tile
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
name|GimpTile
name|gimp_tile
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gint
name|tile_size
decl_stmt|;
name|guchar
modifier|*
name|tile_data
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_tile_init
argument_list|(
name|backend_plugin
argument_list|,
operator|&
name|gimp_tile
argument_list|,
name|y
argument_list|,
name|x
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|tile_size
operator|=
name|gegl_tile_backend_get_tile_size
argument_list|(
name|backend
argument_list|)
expr_stmt|;
name|tile_data
operator|=
name|gegl_tile_get_data
argument_list|(
name|tile
argument_list|)
expr_stmt|;
name|gimp_tile
operator|.
name|data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|gimp_tile
operator|.
name|ewidth
operator|*
name|gimp_tile
operator|.
name|eheight
operator|*
name|priv
operator|->
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tile
operator|.
name|ewidth
operator|*
name|gimp_tile
operator|.
name|eheight
operator|*
name|priv
operator|->
name|bpp
operator|==
name|tile_size
condition|)
block|{
name|memcpy
argument_list|(
name|gimp_tile
operator|.
name|data
argument_list|,
name|tile_data
argument_list|,
name|tile_size
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|tile_stride
init|=
name|TILE_WIDTH
operator|*
name|priv
operator|->
name|bpp
decl_stmt|;
name|gint
name|gimp_tile_stride
init|=
name|gimp_tile
operator|.
name|ewidth
operator|*
name|priv
operator|->
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
name|gimp_tile
operator|.
name|eheight
condition|;
name|row
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|gimp_tile
operator|.
name|data
operator|+
name|row
operator|*
name|gimp_tile_stride
argument_list|,
name|tile_data
operator|+
name|row
operator|*
name|tile_stride
argument_list|,
name|gimp_tile_stride
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_tile_put
argument_list|(
name|backend_plugin
argument_list|,
operator|&
name|gimp_tile
argument_list|)
expr_stmt|;
name|gimp_tile_unset
argument_list|(
name|backend_plugin
argument_list|,
operator|&
name|gimp_tile
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tile_init (GimpTileBackendPlugin * backend_plugin,GimpTile * tile,gint row,gint col)
name|gimp_tile_init
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
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
if|if
condition|(
name|row
operator|>
name|priv
operator|->
name|ntile_rows
operator|-
literal|1
operator|||
name|col
operator|>
name|priv
operator|->
name|ntile_cols
operator|-
literal|1
condition|)
block|{
return|return
name|FALSE
return|;
block|}
name|tile
operator|->
name|tile_num
operator|=
name|row
operator|*
name|priv
operator|->
name|ntile_cols
operator|+
name|col
expr_stmt|;
if|if
condition|(
name|col
operator|==
operator|(
name|priv
operator|->
name|ntile_cols
operator|-
literal|1
operator|)
condition|)
name|tile
operator|->
name|ewidth
operator|=
name|priv
operator|->
name|width
operator|-
operator|(
operator|(
name|priv
operator|->
name|ntile_cols
operator|-
literal|1
operator|)
operator|*
name|TILE_WIDTH
operator|)
expr_stmt|;
else|else
name|tile
operator|->
name|ewidth
operator|=
name|TILE_WIDTH
expr_stmt|;
if|if
condition|(
name|row
operator|==
operator|(
name|priv
operator|->
name|ntile_rows
operator|-
literal|1
operator|)
condition|)
name|tile
operator|->
name|eheight
operator|=
name|priv
operator|->
name|height
operator|-
operator|(
operator|(
name|priv
operator|->
name|ntile_rows
operator|-
literal|1
operator|)
operator|*
name|TILE_HEIGHT
operator|)
expr_stmt|;
else|else
name|tile
operator|->
name|eheight
operator|=
name|TILE_HEIGHT
expr_stmt|;
name|tile
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_unset (GimpTileBackendPlugin * backend_plugin,GimpTile * tile)
name|gimp_tile_unset
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
parameter_list|)
block|{
name|g_clear_pointer
argument_list|(
operator|&
name|tile
operator|->
name|data
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_get (GimpTileBackendPlugin * backend_plugin,GimpTile * tile)
name|gimp_tile_get
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
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
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_get_plug_in
argument_list|()
decl_stmt|;
name|GPTileReq
name|tile_req
decl_stmt|;
name|GPTileData
modifier|*
name|tile_data
decl_stmt|;
name|GimpWireMessage
name|msg
decl_stmt|;
name|tile_req
operator|.
name|drawable_id
operator|=
name|priv
operator|->
name|drawable_id
expr_stmt|;
name|tile_req
operator|.
name|tile_num
operator|=
name|tile
operator|->
name|tile_num
expr_stmt|;
name|tile_req
operator|.
name|shadow
operator|=
name|priv
operator|->
name|shadow
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
if|if
condition|(
operator|!
name|gp_tile_req_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|plug_in
argument_list|)
argument_list|,
operator|&
name|tile_req
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|_gimp_plug_in_read_expect_msg
argument_list|(
name|plug_in
argument_list|,
operator|&
name|msg
argument_list|,
name|GP_TILE_DATA
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|gp_tile_req_write
argument_list|(
name|_gimp_writechannel
argument_list|,
operator|&
name|tile_req
argument_list|,
name|NULL
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|_gimp_legacy_read_expect_msg
argument_list|(
operator|&
name|msg
argument_list|,
name|GP_TILE_DATA
argument_list|)
expr_stmt|;
block|}
name|tile_data
operator|=
name|msg
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|tile_data
operator|->
name|drawable_id
operator|!=
name|priv
operator|->
name|drawable_id
operator|||
name|tile_data
operator|->
name|tile_num
operator|!=
name|tile
operator|->
name|tile_num
operator|||
name|tile_data
operator|->
name|shadow
operator|!=
name|priv
operator|->
name|shadow
operator|||
name|tile_data
operator|->
name|width
operator|!=
name|tile
operator|->
name|ewidth
operator|||
name|tile_data
operator|->
name|height
operator|!=
name|tile
operator|->
name|eheight
operator|||
name|tile_data
operator|->
name|bpp
operator|!=
name|priv
operator|->
name|bpp
condition|)
block|{
if|#
directive|if
literal|0
block|g_printerr ("tile_data: %d %d %d %d %d %d\n"                   "tile:      %d %d %d %d %d %d\n",                   tile_data->drawable_id,                   tile_data->tile_num,                   tile_data->shadow,                   tile_data->width,                   tile_data->height,                   tile_data->bpp,                   priv->drawable_id,                   tile->tile_num,                   priv->shadow,                   tile->ewidth,                   tile->eheight,                   priv->bpp);
endif|#
directive|endif
name|g_printerr
argument_list|(
literal|"received tile info did not match computed tile info"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|tile_data
operator|->
name|use_shm
condition|)
block|{
name|tile
operator|->
name|data
operator|=
name|g_memdup
argument_list|(
name|_gimp_shm_addr
argument_list|()
argument_list|,
name|tile
operator|->
name|ewidth
operator|*
name|tile
operator|->
name|eheight
operator|*
name|priv
operator|->
name|bpp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tile
operator|->
name|data
operator|=
name|tile_data
operator|->
name|data
expr_stmt|;
name|tile_data
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|plug_in
condition|)
block|{
if|if
condition|(
operator|!
name|gp_tile_ack_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|gp_tile_ack_write
argument_list|(
name|_gimp_writechannel
argument_list|,
name|NULL
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tile_put (GimpTileBackendPlugin * backend_plugin,GimpTile * tile)
name|gimp_tile_put
parameter_list|(
name|GimpTileBackendPlugin
modifier|*
name|backend_plugin
parameter_list|,
name|GimpTile
modifier|*
name|tile
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
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_get_plug_in
argument_list|()
decl_stmt|;
name|GPTileReq
name|tile_req
decl_stmt|;
name|GPTileData
name|tile_data
decl_stmt|;
name|GPTileData
modifier|*
name|tile_info
decl_stmt|;
name|GimpWireMessage
name|msg
decl_stmt|;
name|tile_req
operator|.
name|drawable_id
operator|=
operator|-
literal|1
expr_stmt|;
name|tile_req
operator|.
name|tile_num
operator|=
literal|0
expr_stmt|;
name|tile_req
operator|.
name|shadow
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
if|if
condition|(
operator|!
name|gp_tile_req_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|plug_in
argument_list|)
argument_list|,
operator|&
name|tile_req
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|_gimp_plug_in_read_expect_msg
argument_list|(
name|plug_in
argument_list|,
operator|&
name|msg
argument_list|,
name|GP_TILE_DATA
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|gp_tile_req_write
argument_list|(
name|_gimp_writechannel
argument_list|,
operator|&
name|tile_req
argument_list|,
name|NULL
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
name|_gimp_legacy_read_expect_msg
argument_list|(
operator|&
name|msg
argument_list|,
name|GP_TILE_DATA
argument_list|)
expr_stmt|;
block|}
name|tile_info
operator|=
name|msg
operator|.
name|data
expr_stmt|;
name|tile_data
operator|.
name|drawable_id
operator|=
name|priv
operator|->
name|drawable_id
expr_stmt|;
name|tile_data
operator|.
name|tile_num
operator|=
name|tile
operator|->
name|tile_num
expr_stmt|;
name|tile_data
operator|.
name|shadow
operator|=
name|priv
operator|->
name|shadow
expr_stmt|;
name|tile_data
operator|.
name|bpp
operator|=
name|priv
operator|->
name|bpp
expr_stmt|;
name|tile_data
operator|.
name|width
operator|=
name|tile
operator|->
name|ewidth
expr_stmt|;
name|tile_data
operator|.
name|height
operator|=
name|tile
operator|->
name|eheight
expr_stmt|;
name|tile_data
operator|.
name|use_shm
operator|=
name|tile_info
operator|->
name|use_shm
expr_stmt|;
name|tile_data
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|tile_info
operator|->
name|use_shm
condition|)
block|{
name|memcpy
argument_list|(
name|_gimp_shm_addr
argument_list|()
argument_list|,
name|tile
operator|->
name|data
argument_list|,
name|tile
operator|->
name|ewidth
operator|*
name|tile
operator|->
name|eheight
operator|*
name|priv
operator|->
name|bpp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tile_data
operator|.
name|data
operator|=
name|tile
operator|->
name|data
expr_stmt|;
block|}
if|if
condition|(
name|plug_in
condition|)
block|{
if|if
condition|(
operator|!
name|gp_tile_data_write
argument_list|(
name|_gimp_plug_in_get_write_channel
argument_list|(
name|plug_in
argument_list|)
argument_list|,
operator|&
name|tile_data
argument_list|,
name|plug_in
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|gp_tile_data_write
argument_list|(
name|_gimp_writechannel
argument_list|,
operator|&
name|tile_data
argument_list|,
name|NULL
argument_list|)
condition|)
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|tile_info
operator|->
name|use_shm
condition|)
name|tile_data
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in
condition|)
name|_gimp_plug_in_read_expect_msg
argument_list|(
name|plug_in
argument_list|,
operator|&
name|msg
argument_list|,
name|GP_TILE_ACK
argument_list|)
expr_stmt|;
else|else
name|_gimp_legacy_read_expect_msg
argument_list|(
operator|&
name|msg
argument_list|,
name|GP_TILE_ACK
argument_list|)
expr_stmt|;
name|gimp_wire_destroy
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


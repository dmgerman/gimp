begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROTOCOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROTOCOL_H__
define|#
directive|define
name|__GIMP_PROTOCOL_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* Increment every time the protocol changes  */
end_comment

begin_define
DECL|macro|GP_VERSION
define|#
directive|define
name|GP_VERSION
value|0x0002
end_define

begin_enum
DECL|enum|__anon2b393acd0103
enum|enum
block|{
DECL|enumerator|GP_QUIT
name|GP_QUIT
block|,
DECL|enumerator|GP_CONFIG
name|GP_CONFIG
block|,
DECL|enumerator|GP_TILE_REQ
name|GP_TILE_REQ
block|,
DECL|enumerator|GP_TILE_ACK
name|GP_TILE_ACK
block|,
DECL|enumerator|GP_TILE_DATA
name|GP_TILE_DATA
block|,
DECL|enumerator|GP_PROC_RUN
name|GP_PROC_RUN
block|,
DECL|enumerator|GP_PROC_RETURN
name|GP_PROC_RETURN
block|,
DECL|enumerator|GP_TEMP_PROC_RUN
name|GP_TEMP_PROC_RUN
block|,
DECL|enumerator|GP_TEMP_PROC_RETURN
name|GP_TEMP_PROC_RETURN
block|,
DECL|enumerator|GP_PROC_INSTALL
name|GP_PROC_INSTALL
block|,
DECL|enumerator|GP_PROC_UNINSTALL
name|GP_PROC_UNINSTALL
block|,
DECL|enumerator|GP_EXTENSION_ACK
name|GP_EXTENSION_ACK
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GPConfig
typedef|typedef
name|struct
name|_GPConfig
name|GPConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPTileReq
typedef|typedef
name|struct
name|_GPTileReq
name|GPTileReq
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPTileAck
typedef|typedef
name|struct
name|_GPTileAck
name|GPTileAck
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPTileData
typedef|typedef
name|struct
name|_GPTileData
name|GPTileData
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParam
typedef|typedef
name|struct
name|_GPParam
name|GPParam
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDef
typedef|typedef
name|struct
name|_GPParamDef
name|GPParamDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPProcRun
typedef|typedef
name|struct
name|_GPProcRun
name|GPProcRun
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPProcReturn
typedef|typedef
name|struct
name|_GPProcReturn
name|GPProcReturn
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPProcInstall
typedef|typedef
name|struct
name|_GPProcInstall
name|GPProcInstall
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPProcUninstall
typedef|typedef
name|struct
name|_GPProcUninstall
name|GPProcUninstall
typedef|;
end_typedef

begin_struct
DECL|struct|_GPConfig
struct|struct
name|_GPConfig
block|{
DECL|member|version
name|guint32
name|version
decl_stmt|;
DECL|member|tile_width
name|guint32
name|tile_width
decl_stmt|;
DECL|member|tile_height
name|guint32
name|tile_height
decl_stmt|;
DECL|member|shm_ID
name|gint32
name|shm_ID
decl_stmt|;
DECL|member|gamma
name|gdouble
name|gamma
decl_stmt|;
DECL|member|install_cmap
name|gint8
name|install_cmap
decl_stmt|;
DECL|member|use_xshm
name|gint8
name|use_xshm
decl_stmt|;
DECL|member|color_cube
name|guint8
name|color_cube
index|[
literal|4
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPTileReq
struct|struct
name|_GPTileReq
block|{
DECL|member|drawable_ID
name|gint32
name|drawable_ID
decl_stmt|;
DECL|member|tile_num
name|guint32
name|tile_num
decl_stmt|;
DECL|member|shadow
name|guint32
name|shadow
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPTileData
struct|struct
name|_GPTileData
block|{
DECL|member|drawable_ID
name|gint32
name|drawable_ID
decl_stmt|;
DECL|member|tile_num
name|guint32
name|tile_num
decl_stmt|;
DECL|member|shadow
name|guint32
name|shadow
decl_stmt|;
DECL|member|bpp
name|guint32
name|bpp
decl_stmt|;
DECL|member|width
name|guint32
name|width
decl_stmt|;
DECL|member|height
name|guint32
name|height
decl_stmt|;
DECL|member|use_shm
name|guint32
name|use_shm
decl_stmt|;
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParam
struct|struct
name|_GPParam
block|{
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|union|__anon2b393acd020a
union|union
block|{
DECL|member|d_int32
name|gint32
name|d_int32
decl_stmt|;
DECL|member|d_int16
name|gint16
name|d_int16
decl_stmt|;
DECL|member|d_int8
name|gint8
name|d_int8
decl_stmt|;
DECL|member|d_float
name|gdouble
name|d_float
decl_stmt|;
DECL|member|d_string
name|gchar
modifier|*
name|d_string
decl_stmt|;
DECL|member|d_int32array
name|gint32
modifier|*
name|d_int32array
decl_stmt|;
DECL|member|d_int16array
name|gint16
modifier|*
name|d_int16array
decl_stmt|;
DECL|member|d_int8array
name|gint8
modifier|*
name|d_int8array
decl_stmt|;
DECL|member|d_floatarray
name|gdouble
modifier|*
name|d_floatarray
decl_stmt|;
DECL|member|d_stringarray
name|gchar
modifier|*
modifier|*
name|d_stringarray
decl_stmt|;
DECL|struct|__anon2b393acd0308
struct|struct
block|{
DECL|member|red
name|guint8
name|red
decl_stmt|;
DECL|member|green
name|guint8
name|green
decl_stmt|;
DECL|member|blue
name|guint8
name|blue
decl_stmt|;
DECL|member|d_color
block|}
name|d_color
struct|;
DECL|struct|__anon2b393acd0408
struct|struct
block|{
DECL|member|x
name|gint32
name|x
decl_stmt|;
DECL|member|y
name|gint32
name|y
decl_stmt|;
DECL|member|width
name|gint32
name|width
decl_stmt|;
DECL|member|height
name|gint32
name|height
decl_stmt|;
DECL|member|d_region
block|}
name|d_region
struct|;
DECL|member|d_display
name|gint32
name|d_display
decl_stmt|;
DECL|member|d_image
name|gint32
name|d_image
decl_stmt|;
DECL|member|d_layer
name|gint32
name|d_layer
decl_stmt|;
DECL|member|d_channel
name|gint32
name|d_channel
decl_stmt|;
DECL|member|d_drawable
name|gint32
name|d_drawable
decl_stmt|;
DECL|member|d_selection
name|gint32
name|d_selection
decl_stmt|;
DECL|member|d_boundary
name|gint32
name|d_boundary
decl_stmt|;
DECL|member|d_path
name|gint32
name|d_path
decl_stmt|;
DECL|member|d_status
name|gint32
name|d_status
decl_stmt|;
DECL|member|data
block|}
name|data
union|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDef
struct|struct
name|_GPParamDef
block|{
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|description
name|char
modifier|*
name|description
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPProcRun
struct|struct
name|_GPProcRun
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|nparams
name|guint32
name|nparams
decl_stmt|;
DECL|member|params
name|GPParam
modifier|*
name|params
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPProcReturn
struct|struct
name|_GPProcReturn
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|nparams
name|guint32
name|nparams
decl_stmt|;
DECL|member|params
name|GPParam
modifier|*
name|params
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPProcInstall
struct|struct
name|_GPProcInstall
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
name|char
modifier|*
name|blurb
decl_stmt|;
DECL|member|help
name|char
modifier|*
name|help
decl_stmt|;
DECL|member|author
name|char
modifier|*
name|author
decl_stmt|;
DECL|member|copyright
name|char
modifier|*
name|copyright
decl_stmt|;
DECL|member|date
name|char
modifier|*
name|date
decl_stmt|;
DECL|member|menu_path
name|char
modifier|*
name|menu_path
decl_stmt|;
DECL|member|image_types
name|char
modifier|*
name|image_types
decl_stmt|;
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|nparams
name|guint32
name|nparams
decl_stmt|;
DECL|member|nreturn_vals
name|guint32
name|nreturn_vals
decl_stmt|;
DECL|member|params
name|GPParamDef
modifier|*
name|params
decl_stmt|;
DECL|member|return_vals
name|GPParamDef
modifier|*
name|return_vals
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPProcUninstall
struct|struct
name|_GPProcUninstall
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gp_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_quit_write
parameter_list|(
name|int
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_config_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_tile_req_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPTileReq
modifier|*
name|tile_req
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_tile_ack_write
parameter_list|(
name|int
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_tile_data_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPTileData
modifier|*
name|tile_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_proc_run_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_proc_return_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPProcReturn
modifier|*
name|proc_return
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_temp_proc_run_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_temp_proc_return_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPProcReturn
modifier|*
name|proc_return
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_proc_install_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPProcInstall
modifier|*
name|proc_install
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_proc_uninstall_write
parameter_list|(
name|int
name|fd
parameter_list|,
name|GPProcUninstall
modifier|*
name|proc_uninstall
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gp_extension_ack_write
parameter_list|(
name|int
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROTOCOL_H__ */
end_comment

end_unit


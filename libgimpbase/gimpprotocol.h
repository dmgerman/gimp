begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/* Increment every time the protocol changes  */
DECL|macro|GIMP_PROTOCOL_VERSION
define|#
directive|define
name|GIMP_PROTOCOL_VERSION
value|0x0011
name|enum
DECL|enum|__anon2c7dd08c0103
type|{
DECL|enumerator|GP_QUIT
name|GP_QUIT
decl_stmt|,
DECL|enumerator|GP_CONFIG
name|GP_CONFIG
decl_stmt|,
DECL|enumerator|GP_TILE_REQ
name|GP_TILE_REQ
decl_stmt|,
DECL|enumerator|GP_TILE_ACK
name|GP_TILE_ACK
decl_stmt|,
DECL|enumerator|GP_TILE_DATA
name|GP_TILE_DATA
decl_stmt|,
DECL|enumerator|GP_PROC_RUN
name|GP_PROC_RUN
decl_stmt|,
DECL|enumerator|GP_PROC_RETURN
name|GP_PROC_RETURN
decl_stmt|,
DECL|enumerator|GP_TEMP_PROC_RUN
name|GP_TEMP_PROC_RUN
decl_stmt|,
DECL|enumerator|GP_TEMP_PROC_RETURN
name|GP_TEMP_PROC_RETURN
decl_stmt|,
DECL|enumerator|GP_PROC_INSTALL
name|GP_PROC_INSTALL
decl_stmt|,
DECL|enumerator|GP_PROC_UNINSTALL
name|GP_PROC_UNINSTALL
decl_stmt|,
DECL|enumerator|GP_EXTENSION_ACK
name|GP_EXTENSION_ACK
decl_stmt|,
DECL|enumerator|GP_HAS_INIT
name|GP_HAS_INIT
end_decl_stmt

begin_typedef
unit|};
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
DECL|member|check_size
name|gint8
name|check_size
decl_stmt|;
DECL|member|check_type
name|gint8
name|check_type
decl_stmt|;
DECL|member|gimp_reserved_3
name|gint8
name|gimp_reserved_3
decl_stmt|;
DECL|member|gimp_reserved_4
name|gint8
name|gimp_reserved_4
decl_stmt|;
DECL|member|gimp_reserved_5
name|gint8
name|gimp_reserved_5
decl_stmt|;
DECL|member|gimp_reserved_6
name|gint8
name|gimp_reserved_6
decl_stmt|;
DECL|member|gimp_reserved_7
name|gint8
name|gimp_reserved_7
decl_stmt|;
DECL|member|gimp_reserved_8
name|gint8
name|gimp_reserved_8
decl_stmt|;
DECL|member|install_cmap
name|gint8
name|install_cmap
decl_stmt|;
DECL|member|show_tool_tips
name|gint8
name|show_tool_tips
decl_stmt|;
DECL|member|min_colors
name|gint32
name|min_colors
decl_stmt|;
DECL|member|gdisp_ID
name|gint32
name|gdisp_ID
decl_stmt|;
DECL|member|app_name
name|gchar
modifier|*
name|app_name
decl_stmt|;
DECL|member|wm_class
name|gchar
modifier|*
name|wm_class
decl_stmt|;
DECL|member|display_name
name|gchar
modifier|*
name|display_name
decl_stmt|;
DECL|member|monitor_number
name|gint32
name|monitor_number
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
union|union
DECL|union|__anon2c7dd08c020a
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
DECL|member|d_color
name|GimpRGB
name|d_color
decl_stmt|;
struct|struct
DECL|struct|__anon2c7dd08c0308
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
struct|struct
DECL|struct|__anon2c7dd08c0408
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|flags
name|guint32
name|flags
decl_stmt|;
DECL|member|size
name|guint32
name|size
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|d_parasite
block|}
name|d_parasite
struct|;
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
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|description
name|gchar
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
name|gchar
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
name|gchar
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
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|member|help
name|gchar
modifier|*
name|help
decl_stmt|;
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
DECL|member|copyright
name|gchar
modifier|*
name|copyright
decl_stmt|;
DECL|member|date
name|gchar
modifier|*
name|date
decl_stmt|;
DECL|member|menu_path
name|gchar
modifier|*
name|menu_path
decl_stmt|;
DECL|member|image_types
name|gchar
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
name|gchar
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
name|gboolean
name|gp_quit_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_config_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPConfig
modifier|*
name|config
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_tile_req_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPTileReq
modifier|*
name|tile_req
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_tile_ack_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_tile_data_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPTileData
modifier|*
name|tile_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_proc_run_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_proc_return_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPProcReturn
modifier|*
name|proc_return
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_temp_proc_run_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPProcRun
modifier|*
name|proc_run
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_temp_proc_return_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPProcReturn
modifier|*
name|proc_return
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_proc_install_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPProcInstall
modifier|*
name|proc_install
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_proc_uninstall_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|GPProcUninstall
modifier|*
name|proc_uninstall
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_extension_ack_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gp_has_init_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROTOCOL_H__ */
end_comment

end_unit


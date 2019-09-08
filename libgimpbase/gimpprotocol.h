begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
value|0x010B
name|enum
DECL|enum|__anon2a04b2f40103
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
typedef|typedef
enum|enum
DECL|enum|__anon2a04b2f40203
block|{
DECL|enumerator|GP_PARAM_DEF_TYPE_DEFAULT
name|GP_PARAM_DEF_TYPE_DEFAULT
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_INT
name|GP_PARAM_DEF_TYPE_INT
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_UNIT
name|GP_PARAM_DEF_TYPE_UNIT
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_ENUM
name|GP_PARAM_DEF_TYPE_ENUM
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_BOOLEAN
name|GP_PARAM_DEF_TYPE_BOOLEAN
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_FLOAT
name|GP_PARAM_DEF_TYPE_FLOAT
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_STRING
name|GP_PARAM_DEF_TYPE_STRING
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_COLOR
name|GP_PARAM_DEF_TYPE_COLOR
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_ID
name|GP_PARAM_DEF_TYPE_ID
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_ID_ARRAY
name|GP_PARAM_DEF_TYPE_ID_ARRAY
block|,
DECL|enumerator|GP_PARAM_DEF_TYPE_PARAM_DEF
name|GP_PARAM_DEF_TYPE_PARAM_DEF
DECL|typedef|GPParamDefType
block|}
name|GPParamDefType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a04b2f40303
block|{
DECL|enumerator|GP_PARAM_TYPE_INT
name|GP_PARAM_TYPE_INT
block|,
DECL|enumerator|GP_PARAM_TYPE_FLOAT
name|GP_PARAM_TYPE_FLOAT
block|,
DECL|enumerator|GP_PARAM_TYPE_STRING
name|GP_PARAM_TYPE_STRING
block|,
DECL|enumerator|GP_PARAM_TYPE_COLOR
name|GP_PARAM_TYPE_COLOR
block|,
DECL|enumerator|GP_PARAM_TYPE_PARASITE
name|GP_PARAM_TYPE_PARASITE
block|,
DECL|enumerator|GP_PARAM_TYPE_ARRAY
name|GP_PARAM_TYPE_ARRAY
block|,
DECL|enumerator|GP_PARAM_TYPE_STRING_ARRAY
name|GP_PARAM_TYPE_STRING_ARRAY
block|,
DECL|enumerator|GP_PARAM_TYPE_ID_ARRAY
name|GP_PARAM_TYPE_ID_ARRAY
block|,
DECL|enumerator|GP_PARAM_TYPE_PARAM_DEF
name|GP_PARAM_TYPE_PARAM_DEF
DECL|typedef|GPParamType
block|}
name|GPParamType
typedef|;
end_typedef

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
DECL|typedef|GPParamDef
typedef|typedef
name|struct
name|_GPParamDef
name|GPParamDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefInt
typedef|typedef
name|struct
name|_GPParamDefInt
name|GPParamDefInt
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefUnit
typedef|typedef
name|struct
name|_GPParamDefUnit
name|GPParamDefUnit
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefEnum
typedef|typedef
name|struct
name|_GPParamDefEnum
name|GPParamDefEnum
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefBoolean
typedef|typedef
name|struct
name|_GPParamDefBoolean
name|GPParamDefBoolean
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefFloat
typedef|typedef
name|struct
name|_GPParamDefFloat
name|GPParamDefFloat
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefString
typedef|typedef
name|struct
name|_GPParamDefString
name|GPParamDefString
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefColor
typedef|typedef
name|struct
name|_GPParamDefColor
name|GPParamDefColor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefID
typedef|typedef
name|struct
name|_GPParamDefID
name|GPParamDefID
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefIDArray
typedef|typedef
name|struct
name|_GPParamDefIDArray
name|GPParamDefIDArray
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamDefParamDef
typedef|typedef
name|struct
name|_GPParamDefParamDef
name|GPParamDefParamDef
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
DECL|typedef|GPParamArray
typedef|typedef
name|struct
name|_GPParamArray
name|GPParamArray
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamStringArray
typedef|typedef
name|struct
name|_GPParamStringArray
name|GPParamStringArray
typedef|;
end_typedef

begin_typedef
DECL|typedef|GPParamIDArray
typedef|typedef
name|struct
name|_GPParamIDArray
name|GPParamIDArray
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
DECL|member|tile_width
name|guint32
name|tile_width
decl_stmt|;
DECL|member|tile_height
name|guint32
name|tile_height
decl_stmt|;
DECL|member|shm_id
name|gint32
name|shm_id
decl_stmt|;
DECL|member|check_size
name|gint8
name|check_size
decl_stmt|;
DECL|member|check_type
name|gint8
name|check_type
decl_stmt|;
DECL|member|show_help_button
name|gint8
name|show_help_button
decl_stmt|;
DECL|member|use_cpu_accel
name|gint8
name|use_cpu_accel
decl_stmt|;
DECL|member|use_opencl
name|gint8
name|use_opencl
decl_stmt|;
DECL|member|export_profile
name|gint8
name|export_profile
decl_stmt|;
DECL|member|export_exif
name|gint8
name|export_exif
decl_stmt|;
DECL|member|export_xmp
name|gint8
name|export_xmp
decl_stmt|;
DECL|member|export_iptc
name|gint8
name|export_iptc
decl_stmt|;
DECL|member|gdisp_id
name|gint32
name|gdisp_id
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
DECL|member|timestamp
name|guint32
name|timestamp
decl_stmt|;
DECL|member|icon_theme_dir
name|gchar
modifier|*
name|icon_theme_dir
decl_stmt|;
DECL|member|tile_cache_size
name|guint64
name|tile_cache_size
decl_stmt|;
DECL|member|swap_path
name|gchar
modifier|*
name|swap_path
decl_stmt|;
DECL|member|num_processors
name|gint32
name|num_processors
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPTileReq
struct|struct
name|_GPTileReq
block|{
DECL|member|drawable_id
name|gint32
name|drawable_id
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
DECL|member|drawable_id
name|gint32
name|drawable_id
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
DECL|struct|_GPParamDefInt
struct|struct
name|_GPParamDefInt
block|{
DECL|member|min_val
name|gint64
name|min_val
decl_stmt|;
DECL|member|max_val
name|gint64
name|max_val
decl_stmt|;
DECL|member|default_val
name|gint64
name|default_val
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefUnit
struct|struct
name|_GPParamDefUnit
block|{
DECL|member|allow_pixels
name|gint32
name|allow_pixels
decl_stmt|;
DECL|member|allow_percent
name|gint32
name|allow_percent
decl_stmt|;
DECL|member|default_val
name|gint32
name|default_val
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefEnum
struct|struct
name|_GPParamDefEnum
block|{
DECL|member|type_name
name|gchar
modifier|*
name|type_name
decl_stmt|;
DECL|member|default_val
name|gint32
name|default_val
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefBoolean
struct|struct
name|_GPParamDefBoolean
block|{
DECL|member|default_val
name|gint32
name|default_val
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefFloat
struct|struct
name|_GPParamDefFloat
block|{
DECL|member|min_val
name|gdouble
name|min_val
decl_stmt|;
DECL|member|max_val
name|gdouble
name|max_val
decl_stmt|;
DECL|member|default_val
name|gdouble
name|default_val
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefString
struct|struct
name|_GPParamDefString
block|{
DECL|member|default_val
name|gchar
modifier|*
name|default_val
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefColor
struct|struct
name|_GPParamDefColor
block|{
DECL|member|has_alpha
name|gint32
name|has_alpha
decl_stmt|;
DECL|member|default_val
name|GimpRGB
name|default_val
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefID
struct|struct
name|_GPParamDefID
block|{
DECL|member|none_ok
name|gint32
name|none_ok
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefIDArray
struct|struct
name|_GPParamDefIDArray
block|{
DECL|member|type_name
name|gchar
modifier|*
name|type_name
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDefParamDef
struct|struct
name|_GPParamDefParamDef
block|{
DECL|member|type_name
name|gchar
modifier|*
name|type_name
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamDef
struct|struct
name|_GPParamDef
block|{
DECL|member|param_def_type
name|GPParamDefType
name|param_def_type
decl_stmt|;
DECL|member|type_name
name|gchar
modifier|*
name|type_name
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|nick
name|gchar
modifier|*
name|nick
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|member|flags
name|guint
name|flags
decl_stmt|;
union|union
DECL|union|__anon2a04b2f4040a
block|{
DECL|member|m_int
name|GPParamDefInt
name|m_int
decl_stmt|;
DECL|member|m_unit
name|GPParamDefUnit
name|m_unit
decl_stmt|;
DECL|member|m_enum
name|GPParamDefEnum
name|m_enum
decl_stmt|;
DECL|member|m_boolean
name|GPParamDefBoolean
name|m_boolean
decl_stmt|;
DECL|member|m_float
name|GPParamDefFloat
name|m_float
decl_stmt|;
DECL|member|m_string
name|GPParamDefString
name|m_string
decl_stmt|;
DECL|member|m_color
name|GPParamDefColor
name|m_color
decl_stmt|;
DECL|member|m_id
name|GPParamDefID
name|m_id
decl_stmt|;
DECL|member|m_id_array
name|GPParamDefIDArray
name|m_id_array
decl_stmt|;
DECL|member|m_param_def
name|GPParamDefParamDef
name|m_param_def
decl_stmt|;
DECL|member|meta
block|}
name|meta
union|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamArray
struct|struct
name|_GPParamArray
block|{
DECL|member|size
name|guint32
name|size
decl_stmt|;
DECL|member|data
name|guint8
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamStringArray
struct|struct
name|_GPParamStringArray
block|{
DECL|member|size
name|guint32
name|size
decl_stmt|;
DECL|member|data
name|gchar
modifier|*
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GPParamIDArray
struct|struct
name|_GPParamIDArray
block|{
DECL|member|type_name
name|gchar
modifier|*
name|type_name
decl_stmt|;
DECL|member|size
name|guint32
name|size
decl_stmt|;
DECL|member|data
name|gint32
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
DECL|member|param_type
name|GPParamType
name|param_type
decl_stmt|;
DECL|member|type_name
name|gchar
modifier|*
name|type_name
decl_stmt|;
union|union
DECL|union|__anon2a04b2f4050a
block|{
DECL|member|d_int
name|gint32
name|d_int
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
DECL|member|d_color
name|GimpRGB
name|d_color
decl_stmt|;
DECL|member|d_parasite
name|GimpParasite
name|d_parasite
decl_stmt|;
DECL|member|d_array
name|GPParamArray
name|d_array
decl_stmt|;
DECL|member|d_string_array
name|GPParamStringArray
name|d_string_array
decl_stmt|;
DECL|member|d_id_array
name|GPParamIDArray
name|d_id_array
decl_stmt|;
DECL|member|d_param_def
name|GPParamDef
name|d_param_def
decl_stmt|;
DECL|member|data
block|}
name|data
union|;
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
DECL|member|n_params
name|guint32
name|n_params
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
DECL|member|n_params
name|guint32
name|n_params
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
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|n_params
name|guint32
name|n_params
decl_stmt|;
DECL|member|n_return_vals
name|guint32
name|n_return_vals
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


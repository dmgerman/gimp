begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmoduleinfo.h  * (C) 1999 Austin Donnelly<austin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MODULE_INFO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MODULE_INFO_H__
define|#
directive|define
name|__GIMP_MODULE_INFO_H__
end_define

begin_include
include|#
directive|include
file|"libgimp/gimpmodule.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b89f4ef0103
block|{
DECL|enumerator|GIMP_MODULE_STATE_ERROR
name|GIMP_MODULE_STATE_ERROR
block|,
comment|/* missing module_load function or other error    */
DECL|enumerator|GIMP_MODULE_STATE_LOADED_OK
name|GIMP_MODULE_STATE_LOADED_OK
block|,
comment|/* happy and running (normal state of affairs)    */
DECL|enumerator|GIMP_MODULE_STATE_LOAD_FAILED
name|GIMP_MODULE_STATE_LOAD_FAILED
block|,
comment|/* module_load returned GIMP_MODULE_UNLOAD        */
DECL|enumerator|GIMP_MODULE_STATE_UNLOAD_REQUESTED
name|GIMP_MODULE_STATE_UNLOAD_REQUESTED
block|,
comment|/* sent unload request, waiting for callback      */
DECL|enumerator|GIMP_MODULE_STATE_UNLOADED_OK
name|GIMP_MODULE_STATE_UNLOADED_OK
comment|/* callback arrived, module not in memory anymore */
DECL|typedef|GimpModuleState
block|}
name|GimpModuleState
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_MODULE_INFO
define|#
directive|define
name|GIMP_TYPE_MODULE_INFO
value|(gimp_module_info_get_type ())
end_define

begin_define
DECL|macro|GIMP_MODULE_INFO (obj)
define|#
directive|define
name|GIMP_MODULE_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MODULE_INFO, GimpModuleInfoObj))
end_define

begin_define
DECL|macro|GIMP_MODULE_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_MODULE_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MODULE_INFO, GimpModuleInfoObjClass))
end_define

begin_define
DECL|macro|GIMP_IS_MODULE_INFO (obj)
define|#
directive|define
name|GIMP_IS_MODULE_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MODULE_INFO))
end_define

begin_define
DECL|macro|GIMP_IS_MODULE_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MODULE_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MODULE_INFO))
end_define

begin_define
DECL|macro|GIMP_MODULE_INFO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MODULE_INFO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MODULE_INFO, GimpModuleInfoObjClass))
end_define

begin_typedef
DECL|typedef|GimpModuleInfoObjClass
typedef|typedef
name|struct
name|_GimpModuleInfoObjClass
name|GimpModuleInfoObjClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpModuleInfoObj
struct|struct
name|_GimpModuleInfoObj
block|{
DECL|member|parent_instance
name|GTypeModule
name|parent_instance
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/* path to the module                        */
DECL|member|verbose
name|gboolean
name|verbose
decl_stmt|;
comment|/* verbose error reporting                   */
DECL|member|state
name|GimpModuleState
name|state
decl_stmt|;
comment|/* what's happened to the module             */
DECL|member|on_disk
name|gboolean
name|on_disk
decl_stmt|;
comment|/* TRUE if file still exists                 */
DECL|member|load_inhibit
name|gboolean
name|load_inhibit
decl_stmt|;
comment|/* user requests not to load at boot time    */
comment|/* stuff from now on may be NULL depending on the state the module is in    */
DECL|member|module
name|GModule
modifier|*
name|module
decl_stmt|;
comment|/* handle on the module                      */
DECL|member|info
name|GimpModuleInfo
name|info
decl_stmt|;
comment|/* returned values from module_query         */
DECL|member|last_module_error
name|gchar
modifier|*
name|last_module_error
decl_stmt|;
DECL|member|query_module
specifier|const
name|GimpModuleInfo
modifier|*
function_decl|(
modifier|*
name|query_module
function_decl|)
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
DECL|member|register_module
name|gboolean
function_decl|(
modifier|*
name|register_module
function_decl|)
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpModuleInfoObjClass
struct|struct
name|_GimpModuleInfoObjClass
block|{
DECL|member|parent_class
name|GTypeModuleClass
name|parent_class
decl_stmt|;
DECL|member|modified
name|void
function_decl|(
modifier|*
name|modified
function_decl|)
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module_info
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_module_info_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpModuleInfoObj
modifier|*
name|gimp_module_info_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|inhibit_str
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_module_info_modified
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_module_info_set_load_inhibit
parameter_list|(
name|GimpModuleInfoObj
modifier|*
name|module
parameter_list|,
specifier|const
name|gchar
modifier|*
name|inhibit_list
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MODULE_INFO_H__ */
end_comment

end_unit


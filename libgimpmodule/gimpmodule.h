begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmodule.h  * (C) 1999 Austin Donnelly<austin@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MODULE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MODULE_H__
define|#
directive|define
name|__GIMP_MODULE_H__
end_define

begin_include
include|#
directive|include
file|<gmodule.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmodule/gimpmoduletypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmodule/gimpmoduledb.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/*  increment the ABI version each time one of the following changes:  *  *  - the libgimpmodule implementation (if the change affects modules).  *  - one of the classes implemented by modules (currently GimpColorDisplay,  *    GimpColorSelector and GimpController).  */
end_comment

begin_define
DECL|macro|GIMP_MODULE_ABI_VERSION
define|#
directive|define
name|GIMP_MODULE_ABI_VERSION
value|0x0004
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c3a869b0103
block|{
DECL|enumerator|GIMP_MODULE_STATE_ERROR
name|GIMP_MODULE_STATE_ERROR
block|,
comment|/* missing gimp_module_register function                                   * or other error                                   */
DECL|enumerator|GIMP_MODULE_STATE_LOADED
name|GIMP_MODULE_STATE_LOADED
block|,
comment|/* an instance of a type implemented by                                   * this module is allocated                                   */
DECL|enumerator|GIMP_MODULE_STATE_LOAD_FAILED
name|GIMP_MODULE_STATE_LOAD_FAILED
block|,
comment|/* gimp_module_register returned FALSE                                   */
DECL|enumerator|GIMP_MODULE_STATE_NOT_LOADED
name|GIMP_MODULE_STATE_NOT_LOADED
comment|/* there are no instances allocated of                                   * types implemented by this module                                   */
DECL|typedef|GimpModuleState
block|}
name|GimpModuleState
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpModuleInfo
struct|struct
name|_GimpModuleInfo
block|{
DECL|member|abi_version
name|guint32
name|abi_version
decl_stmt|;
DECL|member|purpose
name|gchar
modifier|*
name|purpose
decl_stmt|;
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
DECL|member|version
name|gchar
modifier|*
name|version
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
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpModuleQueryFunc
typedef|typedef
specifier|const
name|GimpModuleInfo
modifier|*
function_decl|(
modifier|*
name|GimpModuleQueryFunc
function_decl|)
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpModuleRegisterFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpModuleRegisterFunc
function_decl|)
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_MODULE
define|#
directive|define
name|GIMP_TYPE_MODULE
value|(gimp_module_get_type ())
end_define

begin_define
DECL|macro|GIMP_MODULE (obj)
define|#
directive|define
name|GIMP_MODULE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MODULE, GimpModule))
end_define

begin_define
DECL|macro|GIMP_MODULE_CLASS (klass)
define|#
directive|define
name|GIMP_MODULE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MODULE, GimpModuleClass))
end_define

begin_define
DECL|macro|GIMP_IS_MODULE (obj)
define|#
directive|define
name|GIMP_IS_MODULE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MODULE))
end_define

begin_define
DECL|macro|GIMP_IS_MODULE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MODULE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MODULE))
end_define

begin_define
DECL|macro|GIMP_MODULE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MODULE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MODULE, GimpModuleClass))
end_define

begin_typedef
DECL|typedef|GimpModuleClass
typedef|typedef
name|struct
name|_GimpModuleClass
name|GimpModuleClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpModule
struct|struct
name|_GimpModule
block|{
DECL|member|parent_instance
name|GTypeModule
name|parent_instance
decl_stmt|;
comment|/*< public>*/
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/* path to the module                       */
DECL|member|verbose
name|gboolean
name|verbose
decl_stmt|;
comment|/* verbose error reporting                  */
DECL|member|state
name|GimpModuleState
name|state
decl_stmt|;
comment|/* what's happened to the module            */
DECL|member|on_disk
name|gboolean
name|on_disk
decl_stmt|;
comment|/* TRUE if file still exists                */
DECL|member|load_inhibit
name|gboolean
name|load_inhibit
decl_stmt|;
comment|/* user requests not to load at boot time   */
comment|/* stuff from now on may be NULL depending on the state the module is in   */
comment|/*< private>*/
DECL|member|module
name|GModule
modifier|*
name|module
decl_stmt|;
comment|/* handle on the module                     */
comment|/*< public>*/
DECL|member|info
name|GimpModuleInfo
modifier|*
name|info
decl_stmt|;
comment|/* returned values from module_query        */
DECL|member|last_module_error
name|gchar
modifier|*
name|last_module_error
decl_stmt|;
comment|/*< private>*/
DECL|member|query_module
name|GimpModuleQueryFunc
name|query_module
decl_stmt|;
DECL|member|register_module
name|GimpModuleRegisterFunc
name|register_module
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpModuleClass
struct|struct
name|_GimpModuleClass
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
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_module_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpModule
modifier|*
name|gimp_module_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|load_inhibit
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_module_query_module
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_module_modified
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_module_set_load_inhibit
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|,
name|gboolean
name|load_inhibit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_module_state_name
parameter_list|(
name|GimpModuleState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_function_decl
name|GType
name|gimp_module_register_enum
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GEnumValue
modifier|*
name|const_static_values
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

begin_comment
comment|/*  GimpModuleInfo functions  */
end_comment

begin_function_decl
name|GimpModuleInfo
modifier|*
name|gimp_module_info_new
parameter_list|(
name|guint32
name|abi_version
parameter_list|,
specifier|const
name|gchar
modifier|*
name|purpose
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|version
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpModuleInfo
modifier|*
name|gimp_module_info_copy
parameter_list|(
specifier|const
name|GimpModuleInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_module_info_free
parameter_list|(
name|GimpModuleInfo
modifier|*
name|info
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
comment|/* __GIMP_MODULE_INFO_H__ */
end_comment

end_unit


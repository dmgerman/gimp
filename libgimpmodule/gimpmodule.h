begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmodule.h  * (C) 1999 Austin Donnelly<austin@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_define
DECL|macro|__GIMP_MODULE_H_INSIDE__
define|#
directive|define
name|__GIMP_MODULE_H_INSIDE__
end_define

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

begin_undef
undef|#
directive|undef
name|__GIMP_MODULE_H_INSIDE__
end_undef

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/**  * GIMP_MODULE_ABI_VERSION:  *  * The version of the module system's ABI. Modules put this value into  * #GimpModuleInfo's @abi_version field so the code loading the modules  * can check if it was compiled against the same module ABI the modules  * are compiled against.  *  *  GIMP_MODULE_ABI_VERSION is incremented each time one of the  *  following changes:  *  *  - the libgimpmodule implementation (if the change affects modules).  *  *  - one of the classes implemented by modules (currently #GimpColorDisplay,  *    #GimpColorSelector and #GimpController).  **/
end_comment

begin_define
DECL|macro|GIMP_MODULE_ABI_VERSION
define|#
directive|define
name|GIMP_MODULE_ABI_VERSION
value|0x0005
end_define

begin_comment
comment|/**  * GimpModuleState:  * @GIMP_MODULE_STATE_ERROR:       Missing gimp_module_register() function  *                                 or other error.  * @GIMP_MODULE_STATE_LOADED:      An instance of a type implemented by  *                                 this module is allocated.  * @GIMP_MODULE_STATE_LOAD_FAILED: gimp_module_register() returned %FALSE.  * @GIMP_MODULE_STATE_NOT_LOADED:  There are no instances allocated of  *                                 types implemented by this module.  *  * The possible states a #GimpModule can be in.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b865d410103
block|{
DECL|enumerator|GIMP_MODULE_STATE_ERROR
name|GIMP_MODULE_STATE_ERROR
block|,
DECL|enumerator|GIMP_MODULE_STATE_LOADED
name|GIMP_MODULE_STATE_LOADED
block|,
DECL|enumerator|GIMP_MODULE_STATE_LOAD_FAILED
name|GIMP_MODULE_STATE_LOAD_FAILED
block|,
DECL|enumerator|GIMP_MODULE_STATE_NOT_LOADED
name|GIMP_MODULE_STATE_NOT_LOADED
DECL|typedef|GimpModuleState
block|}
name|GimpModuleState
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_MODULE_ERROR
define|#
directive|define
name|GIMP_MODULE_ERROR
value|(gimp_module_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_module_error_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * GimpModuleError:  * @GIMP_MODULE_FAILED: Generic error condition  *  * Types of errors returned by modules  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b865d410203
block|{
DECL|enumerator|GIMP_MODULE_FAILED
name|GIMP_MODULE_FAILED
DECL|typedef|GimpModuleError
block|}
name|GimpModuleError
typedef|;
end_typedef

begin_comment
comment|/**  * GimpModuleInfo:  * @abi_version: The #GIMP_MODULE_ABI_VERSION the module was compiled against.  * @purpose:     The module's general purpose.  * @author:      The module's author.  * @version:     The module's version.  * @copyright:   The module's copyright.  * @date:        The module's release date.  *  * This structure contains information about a loadable module.  **/
end_comment

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

begin_comment
comment|/**  * GimpModuleQueryFunc:  * @module:  The #GimpModule responsible for this loadable module.  * @Returns: The #GimpModuleInfo struct describing the module.  *  * The signature of the query function a loadable GIMP module must  * implement.  In the module, the function must be called  * gimp_module_query().  *  * #GimpModule will copy the returned #GimpModuleInfo struct, so the  * module doesn't need to keep these values around (however in most  * cases the module will just return a pointer to a constant  * structure).  **/
end_comment

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

begin_comment
comment|/**  * GimpModuleRegisterFunc:  * @module:  The #GimpModule responsible for this loadable module.  * @Returns: %TRUE on success, %FALSE otherwise.  *  * The signature of the register function a loadable GIMP module must  * implement.  In the module, the function must be called  * gimp_module_register().  *  * When this function is called, the module should register all the types  * it implements with the passed @module.  **/
end_comment

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

begin_comment
comment|/* GimpModules have to implement these */
end_comment

begin_function_decl
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_MODULE_EXPORT
name|gboolean
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

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
DECL|typedef|GimpModulePrivate
typedef|typedef
name|struct
name|_GimpModulePrivate
name|GimpModulePrivate
typedef|;
end_typedef

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
DECL|member|priv
name|GimpModulePrivate
modifier|*
name|priv
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
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
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
name|GFile
modifier|*
name|file
parameter_list|,
name|gboolean
name|auto_load
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GFile
modifier|*
name|gimp_module_get_file
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_module_set_auto_load
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|,
name|gboolean
name|auto_load
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_module_get_auto_load
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_module_is_on_disk
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_module_is_loaded
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpModuleInfo
modifier|*
name|gimp_module_get_info
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpModuleState
name|gimp_module_get_state
parameter_list|(
name|GimpModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_module_get_last_error
parameter_list|(
name|GimpModule
modifier|*
name|module
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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MODULE_H__ */
end_comment

end_unit


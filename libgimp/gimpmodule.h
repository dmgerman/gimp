begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmodule.h (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPMODULE_H__
end_ifndef

begin_define
DECL|macro|__GIMPMODULE_H__
define|#
directive|define
name|__GIMPMODULE_H__
end_define

begin_include
include|#
directive|include
file|<gmodule.h>
end_include

begin_typedef
DECL|enum|__anon2bc80e240103
typedef|typedef
enum|enum
block|{
DECL|enumerator|GIMP_MODULE_OK
name|GIMP_MODULE_OK
block|,
DECL|enumerator|GIMP_MODULE_UNLOAD
name|GIMP_MODULE_UNLOAD
DECL|typedef|GimpModuleStatus
block|}
name|GimpModuleStatus
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2bc80e240208
typedef|typedef
struct|struct
block|{
DECL|member|shutdown_data
name|void
modifier|*
name|shutdown_data
decl_stmt|;
DECL|member|purpose
specifier|const
name|char
modifier|*
name|purpose
decl_stmt|;
DECL|member|author
specifier|const
name|char
modifier|*
name|author
decl_stmt|;
DECL|member|version
specifier|const
name|char
modifier|*
name|version
decl_stmt|;
DECL|member|copyright
specifier|const
name|char
modifier|*
name|copyright
decl_stmt|;
DECL|member|date
specifier|const
name|char
modifier|*
name|date
decl_stmt|;
DECL|typedef|GimpModuleInfo
block|}
name|GimpModuleInfo
typedef|;
end_typedef

begin_comment
comment|/* GIMP modules should G_MODULE_EXPORT a function named "module_init"  * of the following type: */
end_comment

begin_typedef
DECL|typedef|GimpModuleInitFunc
typedef|typedef
name|GimpModuleStatus
function_decl|(
name|GimpModuleInitFunc
function_decl|)
parameter_list|(
name|GimpModuleInfo
modifier|*
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|MODULE_COMPILATION
end_ifndef

begin_comment
comment|/* On Win32 this declaration clashes with 				 * the definition (which uses G_MODULE_EXPORT) 				 * and thus should be bypassed when compiling 				 * the module itself. 				 */
end_comment

begin_decl_stmt
DECL|variable|module_init
name|GimpModuleInitFunc
name|module_init
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* This function is called by the GIMP at startup, and should return  * either GIMP_MODULE_OK if it sucessfully initialised or  * GIMP_MODULE_UNLOAD if the module failed to hook whatever functions  * it wanted.  GIMP_MODULE_UNLOAD causes the module to be closed, so  * the module must not have registered any internal functions or given  * out pointers to its data to anyone.  *  * If the module returns GIMP_MODULE_OK, it should also return a  * GimpModuleInfo structure describing itself.  */
end_comment

begin_comment
comment|/* If GIMP modules want to allow themselves to be unloaded, they  * should G_MODULE_EXPORT a function named "module_unload" with the  * following type: */
end_comment

begin_typedef
DECL|typedef|GimpModuleUnloadFunc
typedef|typedef
name|void
function_decl|(
name|GimpModuleUnloadFunc
function_decl|)
parameter_list|(
name|void
modifier|*
name|shutdown_data
parameter_list|,
name|void
function_decl|(
modifier|*
name|completed_cb
function_decl|)
parameter_list|(
name|void
modifier|*
parameter_list|)
parameter_list|,
name|void
modifier|*
name|completed_data
parameter_list|)
function_decl|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|MODULE_COMPILATION
end_ifndef

begin_comment
comment|/* The same as for module_init */
end_comment

begin_decl_stmt
DECL|variable|module_unload
name|GimpModuleUnloadFunc
name|module_unload
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP calls this unload request function to ask a module to  * prepare itself to be unloaded.  It is called with the value of  * shutdown_data supplied in the GimpModuleInfo struct.  The module  * should ensure that none of its code or data are being used, and  * then call the supplied "completed_cb" callback function with the  * data provided.  Typically the shutdown request function will queue  * de-registration activities then return.  Only when the  * de-registration has finished should the completed_cb be invoked. */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPMODULE_H__ */
end_comment

end_unit


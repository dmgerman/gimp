begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmodule.h (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* For information look at the html documentation */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bfe55480103
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
DECL|typedef|GimpModuleInfo
typedef|typedef
name|struct
name|_GimpModuleInfo
name|GimpModuleInfo
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpModuleInfo
struct|struct
name|_GimpModuleInfo
block|{
DECL|member|shutdown_data
name|gpointer
name|shutdown_data
decl_stmt|;
DECL|member|purpose
specifier|const
name|gchar
modifier|*
name|purpose
decl_stmt|;
DECL|member|author
specifier|const
name|gchar
modifier|*
name|author
decl_stmt|;
DECL|member|version
specifier|const
name|gchar
modifier|*
name|version
decl_stmt|;
DECL|member|copyright
specifier|const
name|gchar
modifier|*
name|copyright
decl_stmt|;
DECL|member|date
specifier|const
name|gchar
modifier|*
name|date
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Module initialization  */
end_comment

begin_typedef
DECL|typedef|GimpModuleInitFunc
typedef|typedef
name|GimpModuleStatus
function_decl|(
modifier|*
name|GimpModuleInitFunc
function_decl|)
parameter_list|(
name|GimpModuleInfo
modifier|*
modifier|*
name|module_info
parameter_list|)
function_decl|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|MODULE_COMPILATION
end_ifndef

begin_comment
comment|/*  On Win32 this declaration clashes with the definition  *  (which uses G_MODULE_EXPORT) and thus should be bypassed  *  when compiling the module itself.  */
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
comment|/* ! MODULE_COMPILATION */
end_comment

begin_comment
comment|/*  Module unload  */
end_comment

begin_typedef
DECL|typedef|GimpModuleCompletedCB
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpModuleCompletedCB
function_decl|)
parameter_list|(
name|gpointer
name|completed_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpModuleUnloadFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpModuleUnloadFunc
function_decl|)
parameter_list|(
name|gpointer
name|shutdown_data
parameter_list|,
name|GimpModuleCompletedCB
name|completed_cb
parameter_list|,
name|gpointer
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
comment|/*  The same as for module_init.  */
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
comment|/* ! MODULE_COMPILATION */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPMODULE_H__ */
end_comment

end_unit


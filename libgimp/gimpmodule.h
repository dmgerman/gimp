begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmodule.h (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look at the html documentation */
end_comment

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
parameter_list|,
name|GimpModuleInfo
modifier|*
modifier|*
name|module_info
parameter_list|)
function_decl|;
end_typedef

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


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasitelistP.h: Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PARASITE_LIST_P_H__
end_ifndef

begin_define
DECL|macro|__PARASITE_LIST_P_H__
define|#
directive|define
name|__PARASITE_LIST_P_H__
end_define

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_include
include|#
directive|include
file|"parasitelist.h"
end_include

begin_struct
DECL|struct|_ParasiteList
struct|struct
name|_ParasiteList
block|{
DECL|member|object
name|GimpObject
name|object
decl_stmt|;
DECL|member|table
name|GHashTable
modifier|*
name|table
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|_ParasiteListClass
typedef|typedef
struct|struct
name|_ParasiteListClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|add
name|void
function_decl|(
modifier|*
name|add
function_decl|)
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
DECL|member|remove
name|void
function_decl|(
modifier|*
name|remove
function_decl|)
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
DECL|typedef|ParasiteListClass
block|}
name|ParasiteListClass
typedef|;
end_typedef

begin_define
DECL|macro|PARASITE_LIST_CLASS (class)
define|#
directive|define
name|PARASITE_LIST_CLASS
parameter_list|(
name|class
parameter_list|)
value|GIMP_CHECK_CLASS_CAST (class, parasite_list_get_type(), ParasiteListClass)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PARASITE_LIST_P_H__  */
end_comment

end_unit


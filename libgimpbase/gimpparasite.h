begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasite.h  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PARASITE_H_
end_ifndef

begin_define
DECL|macro|_PARASITE_H_
define|#
directive|define
name|_PARASITE_H_
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/parasiteF.h>
end_include

begin_define
DECL|macro|PARASITE_PERSISTANT
define|#
directive|define
name|PARASITE_PERSISTANT
value|1
end_define

begin_function_decl
name|Parasite
modifier|*
name|parasite_new
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
name|guint32
name|flags
parameter_list|,
name|guint32
name|size
parameter_list|,
specifier|const
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|parasite_free
parameter_list|(
name|Parasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|parasite_is_type
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|parasite
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Parasite
modifier|*
name|parasite_copy
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Parasite
modifier|*
name|parasite_error
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|int
name|parasite_is_error
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|parasite_is_persistant
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* parasite list functions */
end_comment

begin_function_decl
name|GSList
modifier|*
name|parasite_add_to_gslist
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|parasite
parameter_list|,
name|GSList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Parasite
modifier|*
name|parasite_find_in_gslist
parameter_list|(
specifier|const
name|GSList
modifier|*
name|list
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|parasite_gslist_copy
parameter_list|(
specifier|const
name|GSList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|parasite_gslist_destroy
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
endif|_PARASITE_H_
end_endif

end_unit


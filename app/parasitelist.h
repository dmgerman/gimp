begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasitelist.h: Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PARASITE_LIST_H__
end_ifndef

begin_define
DECL|macro|__PARASITE_LIST_H__
define|#
directive|define
name|__PARASITE_LIST_H__
end_define

begin_include
include|#
directive|include
file|"libgimp/gimpparasite.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PARASITE_LIST
define|#
directive|define
name|GIMP_TYPE_PARASITE_LIST
value|(parasite_list_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARASITE_LIST (obj)
define|#
directive|define
name|GIMP_PARASITE_LIST
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_PARASITE_LIST, GimpParasiteList))
end_define

begin_define
DECL|macro|GIMP_IS_PARASITE_LIST (obj)
define|#
directive|define
name|GIMP_IS_PARASITE_LIST
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_PARASITE_LIST))
end_define

begin_comment
comment|/* Signals:    add    remove */
end_comment

begin_function_decl
name|GtkType
name|parasite_list_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|ParasiteList
modifier|*
name|parasite_list_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ParasiteList
modifier|*
name|parasite_list_copy
parameter_list|(
specifier|const
name|ParasiteList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|parasite_list_add
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
end_function_decl

begin_function_decl
name|void
name|parasite_list_remove
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|parasite_list_length
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|parasite_list_persistent_length
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|parasite_list_foreach
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
name|GHFunc
name|function
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|parasite_list_find
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|parasite_shift_parent
parameter_list|(
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PARASITE_LIST_H__  */
end_comment

end_unit


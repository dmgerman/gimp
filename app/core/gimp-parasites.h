begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpparasite.h: Copyright 1998 Jay Cox<jaycox@earthlink.net>   *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_GIMP_PARASITE_H__
end_ifndef

begin_define
DECL|macro|__APP_GIMP_PARASITE_H__
define|#
directive|define
name|__APP_GIMP_PARASITE_H__
end_define

begin_function_decl
name|void
name|gimp_parasites_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parasites_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parasite_attach
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parasite_detach
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_parasite_find
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_parasite_list
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parasiterc_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parasiterc_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __APP_GIMP_PARASITE_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DOMAIN_H__
end_ifndef

begin_define
DECL|macro|__DOMAIN_H__
define|#
directive|define
name|__DOMAIN_H__
end_define

begin_struct
DECL|struct|_GimpHelpDomain
struct|struct
name|_GimpHelpDomain
block|{
DECL|member|help_domain
name|gchar
modifier|*
name|help_domain
decl_stmt|;
DECL|member|help_uri
name|gchar
modifier|*
name|help_uri
decl_stmt|;
DECL|member|help_root
name|gchar
modifier|*
name|help_root
decl_stmt|;
DECL|member|help_locales
name|GHashTable
modifier|*
name|help_locales
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpHelpDomain
modifier|*
name|gimp_help_domain_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_root
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_domain_free
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpHelpLocale
modifier|*
name|gimp_help_domain_lookup_locale
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|locale_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_help_domain_map
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|,
name|GList
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpHelpLocale
modifier|*
modifier|*
name|locale
parameter_list|,
name|gboolean
modifier|*
name|fatal_error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_domain_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! __DOMAIN_H__ */
end_comment

end_unit


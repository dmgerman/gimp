begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help Browser  * Copyright (C) 1999-2002 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *  * domain.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_typedef
DECL|typedef|HelpDomain
typedef|typedef
name|struct
name|_HelpDomain
name|HelpDomain
typedef|;
end_typedef

begin_function_decl
name|void
name|domain_register
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|HelpDomain
modifier|*
name|domain_lookup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|domain_map
parameter_list|(
name|HelpDomain
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_locale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
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


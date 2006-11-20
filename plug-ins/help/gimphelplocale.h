begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_LOCALE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_LOCALE_H__
define|#
directive|define
name|__GIMP_HELP_LOCALE_H__
end_define

begin_struct
DECL|struct|_GimpHelpLocale
struct|struct
name|_GimpHelpLocale
block|{
DECL|member|locale_id
name|gchar
modifier|*
name|locale_id
decl_stmt|;
DECL|member|help_id_mapping
name|GHashTable
modifier|*
name|help_id_mapping
decl_stmt|;
DECL|member|help_missing
name|gchar
modifier|*
name|help_missing
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpHelpLocale
modifier|*
name|gimp_help_locale_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|locale_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_locale_free
parameter_list|(
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_help_locale_map
parameter_list|(
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_help_locale_parse
parameter_list|(
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HELP_LOCALE_H__ */
end_comment

end_unit


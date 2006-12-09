begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_PARASITE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_PARASITE_H__
define|#
directive|define
name|__GIMP_TEXT_PARASITE_H__
end_define

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_text_parasite_name
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_text_to_parasite
parameter_list|(
specifier|const
name|GimpText
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpText
modifier|*
name|gimp_text_from_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_text_gdyntext_parasite_name
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpText
modifier|*
name|gimp_text_from_gdyntext_parasite
parameter_list|(
specifier|const
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
comment|/* __GIMP_TEXT_PARASITE_H__ */
end_comment

end_unit


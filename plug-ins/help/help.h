begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__HELP_H__
end_ifndef

begin_define
DECL|macro|__HELP_H__
define|#
directive|define
name|__HELP_H__
end_define

begin_define
DECL|macro|GIMP_HELP_DEFAULT_DOMAIN
define|#
directive|define
name|GIMP_HELP_DEFAULT_DOMAIN
value|"http://www.gimp.org/help"
end_define

begin_define
DECL|macro|GIMP_HELP_DEFAULT_ID
define|#
directive|define
name|GIMP_HELP_DEFAULT_ID
value|"gimp-main"
end_define

begin_define
DECL|macro|GIMP_HELP_DEFAULT_LOCALE
define|#
directive|define
name|GIMP_HELP_DEFAULT_LOCALE
value|"en"
end_define

begin_define
DECL|macro|GIMP_HELP_PREFIX
define|#
directive|define
name|GIMP_HELP_PREFIX
value|"help"
end_define

begin_define
DECL|macro|GIMP_HELP_ENV_URI
define|#
directive|define
name|GIMP_HELP_ENV_URI
value|"GIMP2_HELP_URI"
end_define

begin_comment
comment|/*  #define GIMP_HELP_DEBUG  */
end_comment

begin_function_decl
name|void
name|help_exit
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
comment|/* ! __HELP_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_TYPES_H__
define|#
directive|define
name|__GIMP_HELP_TYPES_H__
end_define

begin_typedef
DECL|typedef|GimpHelpDomain
typedef|typedef
name|struct
name|_GimpHelpDomain
name|GimpHelpDomain
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHelpItem
typedef|typedef
name|struct
name|_GimpHelpItem
name|GimpHelpItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHelpLocale
typedef|typedef
name|struct
name|_GimpHelpLocale
name|GimpHelpLocale
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! __GIMP_HELP_TYPES_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Recent File Storage,  * see http://freedesktop.org/Standards/recent-file-spec/  *  * This code is taken from libegg and has been adapted to the GIMP needs.  * The original author is James Willcox<jwillcox@cs.indiana.edu>,  * responsible for bugs in this version is Sven Neumann<sven@gimp.org>.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RECENT_LIST_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RECENT_LIST_H__
define|#
directive|define
name|__GIMP_RECENT_LIST_H__
end_define

begin_function_decl
name|gboolean
name|gimp_recent_list_add_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RECENT_LIST_H__ */
end_comment

end_unit


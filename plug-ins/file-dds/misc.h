begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* 	DDS GIMP plugin  	Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,    with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  	This program is free software; you can redistribute it and/or 	modify it under the terms of the GNU General Public 	License as published by the Free Software Foundation; either 	version 2 of the License, or (at your option) any later version.  	This program is distributed in the hope that it will be useful, 	but WITHOUT ANY WARRANTY; without even the implied warranty of 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 	General Public License for more details.  	You should have received a copy of the GNU General Public License 	along with this program; see the file COPYING.  If not, write to 	the Free Software Foundation, 51 Franklin Street, Fifth Floor 	Boston, MA 02110-1301, USA. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|MISC_H
end_ifndef

begin_define
DECL|macro|MISC_H
define|#
directive|define
name|MISC_H
end_define

begin_function_decl
name|void
name|decode_ycocg_image
parameter_list|(
name|gint32
name|drawableID
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|decode_ycocg_scaled_image
parameter_list|(
name|gint32
name|drawableID
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|decode_alpha_exp_image
parameter_list|(
name|gint32
name|drawableID
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit


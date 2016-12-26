begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-webp - WebP file format plug-in for the GIMP  * Copyright (C) 2015  Nathan Osman  * Copyright (C) 2016  Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation, either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_WEBP_H__
end_ifndef

begin_define
DECL|macro|__FILE_WEBP_H__
define|#
directive|define
name|__FILE_WEBP_H__
end_define

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-webp-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-webp-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-webp"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-webp"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FILE_WEBP_H__ */
end_comment

end_unit


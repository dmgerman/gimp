begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-file.h  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILE_H__
define|#
directive|define
name|__GIMP_FILE_H__
end_define

begin_comment
comment|/* Data keys for Gimp */
end_comment

begin_define
DECL|macro|GIMP_FILE_OPEN_LAST_URI_KEY
define|#
directive|define
name|GIMP_FILE_OPEN_LAST_URI_KEY
value|"gimp-file-open-last-uri"
end_define

begin_define
DECL|macro|GIMP_FILE_SAVE_LAST_URI_KEY
define|#
directive|define
name|GIMP_FILE_SAVE_LAST_URI_KEY
value|"gimp-file-save-last-uri"
end_define

begin_define
DECL|macro|GIMP_FILE_EXPORT_LAST_URI_KEY
define|#
directive|define
name|GIMP_FILE_EXPORT_LAST_URI_KEY
value|"gimp-file-export-last-uri"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILE_H__ */
end_comment

end_unit


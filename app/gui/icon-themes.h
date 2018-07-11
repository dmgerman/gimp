begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * icon-themes.h  * Copyright (C) 2015 Benoit Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ICONS_THEMES_H__
end_ifndef

begin_define
DECL|macro|__ICONS_THEMES_H__
define|#
directive|define
name|__ICONS_THEMES_H__
end_define

begin_function_decl
name|void
name|icon_themes_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|icon_themes_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|icon_themes_list_themes
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
modifier|*
name|n_themes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GFile
modifier|*
name|icon_themes_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|theme_name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ICONS_THEMES_H__ */
end_comment

end_unit


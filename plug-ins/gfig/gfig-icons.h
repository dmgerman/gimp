begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas<alt@picnic.demon.co.uk>  *               2003 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_ICONS_H__
end_ifndef

begin_define
DECL|macro|__GFIG_ICONS_H__
define|#
directive|define
name|__GFIG_ICONS_H__
end_define

begin_define
DECL|macro|GFIG_ICON_BEZIER
define|#
directive|define
name|GFIG_ICON_BEZIER
value|"gfig-bezier"
end_define

begin_define
DECL|macro|GFIG_ICON_CIRCLE
define|#
directive|define
name|GFIG_ICON_CIRCLE
value|"gfig-circle"
end_define

begin_define
DECL|macro|GFIG_ICON_COPY_OBJECT
define|#
directive|define
name|GFIG_ICON_COPY_OBJECT
value|"gfig-copy-object"
end_define

begin_define
DECL|macro|GFIG_ICON_CURVE
define|#
directive|define
name|GFIG_ICON_CURVE
value|"gfig-curve"
end_define

begin_define
DECL|macro|GFIG_ICON_DELETE_OBJECT
define|#
directive|define
name|GFIG_ICON_DELETE_OBJECT
value|"gfig-delete-object"
end_define

begin_define
DECL|macro|GFIG_ICON_ELLIPSE
define|#
directive|define
name|GFIG_ICON_ELLIPSE
value|"gfig-ellipse"
end_define

begin_define
DECL|macro|GFIG_ICON_LINE
define|#
directive|define
name|GFIG_ICON_LINE
value|"gfig-line"
end_define

begin_define
DECL|macro|GFIG_ICON_MOVE_OBJECT
define|#
directive|define
name|GFIG_ICON_MOVE_OBJECT
value|"gfig-move-object"
end_define

begin_define
DECL|macro|GFIG_ICON_MOVE_POINT
define|#
directive|define
name|GFIG_ICON_MOVE_POINT
value|"gfig-move-point"
end_define

begin_define
DECL|macro|GFIG_ICON_POLYGON
define|#
directive|define
name|GFIG_ICON_POLYGON
value|"gfig-polygon"
end_define

begin_define
DECL|macro|GFIG_ICON_RECTANGLE
define|#
directive|define
name|GFIG_ICON_RECTANGLE
value|"gfig-rectangle"
end_define

begin_define
DECL|macro|GFIG_ICON_SELECT_OBJECT
define|#
directive|define
name|GFIG_ICON_SELECT_OBJECT
value|"gfig-select-object"
end_define

begin_define
DECL|macro|GFIG_ICON_SHOW_ALL
define|#
directive|define
name|GFIG_ICON_SHOW_ALL
value|"gfig-show-all"
end_define

begin_define
DECL|macro|GFIG_ICON_SPIRAL
define|#
directive|define
name|GFIG_ICON_SPIRAL
value|"gfig-spiral"
end_define

begin_define
DECL|macro|GFIG_ICON_STAR
define|#
directive|define
name|GFIG_ICON_STAR
value|"gfig-star"
end_define

begin_define
DECL|macro|GFIG_ICON_LOGO
define|#
directive|define
name|GFIG_ICON_LOGO
value|"gfig-logo"
end_define

begin_function_decl
name|void
name|gfig_icons_init
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
comment|/* __GFIG_ICONS_H__ */
end_comment

end_unit


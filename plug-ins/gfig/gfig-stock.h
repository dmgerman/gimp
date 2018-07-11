begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas<alt@picnic.demon.co.uk>  *               2003 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_STOCK_H__
end_ifndef

begin_define
DECL|macro|__GFIG_STOCK_H__
define|#
directive|define
name|__GFIG_STOCK_H__
end_define

begin_define
DECL|macro|GFIG_STOCK_BEZIER
define|#
directive|define
name|GFIG_STOCK_BEZIER
value|"gfig-bezier"
end_define

begin_define
DECL|macro|GFIG_STOCK_CIRCLE
define|#
directive|define
name|GFIG_STOCK_CIRCLE
value|"gfig-circle"
end_define

begin_define
DECL|macro|GFIG_STOCK_COPY_OBJECT
define|#
directive|define
name|GFIG_STOCK_COPY_OBJECT
value|"gfig-copy-object"
end_define

begin_define
DECL|macro|GFIG_STOCK_CURVE
define|#
directive|define
name|GFIG_STOCK_CURVE
value|"gfig-curve"
end_define

begin_define
DECL|macro|GFIG_STOCK_DELETE_OBJECT
define|#
directive|define
name|GFIG_STOCK_DELETE_OBJECT
value|"gfig-delete"
end_define

begin_define
DECL|macro|GFIG_STOCK_ELLIPSE
define|#
directive|define
name|GFIG_STOCK_ELLIPSE
value|"gfig-ellipse"
end_define

begin_define
DECL|macro|GFIG_STOCK_LINE
define|#
directive|define
name|GFIG_STOCK_LINE
value|"gfig-line"
end_define

begin_define
DECL|macro|GFIG_STOCK_MOVE_OBJECT
define|#
directive|define
name|GFIG_STOCK_MOVE_OBJECT
value|"gfig-move-object"
end_define

begin_define
DECL|macro|GFIG_STOCK_MOVE_POINT
define|#
directive|define
name|GFIG_STOCK_MOVE_POINT
value|"gfig-move-point"
end_define

begin_define
DECL|macro|GFIG_STOCK_POLYGON
define|#
directive|define
name|GFIG_STOCK_POLYGON
value|"gfig-polygon"
end_define

begin_define
DECL|macro|GFIG_STOCK_RECTANGLE
define|#
directive|define
name|GFIG_STOCK_RECTANGLE
value|"gfig-rectangle"
end_define

begin_define
DECL|macro|GFIG_STOCK_SELECT_OBJECT
define|#
directive|define
name|GFIG_STOCK_SELECT_OBJECT
value|"gfig-select-object"
end_define

begin_define
DECL|macro|GFIG_STOCK_SHOW_ALL
define|#
directive|define
name|GFIG_STOCK_SHOW_ALL
value|"gfig-show-all"
end_define

begin_define
DECL|macro|GFIG_STOCK_SPIRAL
define|#
directive|define
name|GFIG_STOCK_SPIRAL
value|"gfig-spiral"
end_define

begin_define
DECL|macro|GFIG_STOCK_STAR
define|#
directive|define
name|GFIG_STOCK_STAR
value|"gfig-star"
end_define

begin_function_decl
name|void
name|gfig_stock_init
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
comment|/* __GFIG_STOCK_H__ */
end_comment

end_unit


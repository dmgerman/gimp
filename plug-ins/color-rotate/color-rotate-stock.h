begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_ROTATE_STOCK_H__
end_ifndef

begin_define
DECL|macro|__COLOR_ROTATE_STOCK_H__
define|#
directive|define
name|__COLOR_ROTATE_STOCK_H__
end_define

begin_define
DECL|macro|STOCK_COLOR_ROTATE_SWITCH_CLOCKWISE
define|#
directive|define
name|STOCK_COLOR_ROTATE_SWITCH_CLOCKWISE
value|"color_rotate_cw"
end_define

begin_define
DECL|macro|STOCK_COLOR_ROTATE_SWITCH_COUNTERCLOCKWISE
define|#
directive|define
name|STOCK_COLOR_ROTATE_SWITCH_COUNTERCLOCKWISE
value|"color_rotate_ccw"
end_define

begin_define
DECL|macro|STOCK_COLOR_ROTATE_CHANGE_ORDER
define|#
directive|define
name|STOCK_COLOR_ROTATE_CHANGE_ORDER
value|"color_rotate_a_b"
end_define

begin_define
DECL|macro|STOCK_COLOR_ROTATE_SELECT_ALL
define|#
directive|define
name|STOCK_COLOR_ROTATE_SELECT_ALL
value|"color_rotate_360"
end_define

begin_function_decl
name|void
name|color_rotate_stock_init
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
comment|/* __COLOR_ROTATE_STOCK_H__ */
end_comment

end_unit


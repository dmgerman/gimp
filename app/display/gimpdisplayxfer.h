begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_XFER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_XFER_H__
define|#
directive|define
name|__GIMP_DISPLAY_XFER_H__
end_define

begin_define
DECL|macro|GIMP_DISPLAY_RENDER_BUF_WIDTH
define|#
directive|define
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
value|256
end_define

begin_define
DECL|macro|GIMP_DISPLAY_RENDER_BUF_HEIGHT
define|#
directive|define
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
value|256
end_define

begin_define
DECL|macro|GIMP_DISPLAY_RENDER_MAX_SCALE
define|#
directive|define
name|GIMP_DISPLAY_RENDER_MAX_SCALE
value|4.0
end_define

begin_function_decl
name|GimpDisplayXfer
modifier|*
name|gimp_display_xfer_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|cairo_surface_t
modifier|*
name|gimp_display_xfer_get_surface
parameter_list|(
name|GimpDisplayXfer
modifier|*
name|xfer
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
modifier|*
name|src_x
parameter_list|,
name|gint
modifier|*
name|src_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DISPLAY_XFER_H__  */
end_comment

end_unit


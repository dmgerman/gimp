begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCALE_H__
end_ifndef

begin_define
DECL|macro|__SCALE_H__
define|#
directive|define
name|__SCALE_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2959bee90103
block|{
DECL|enumerator|ZOOMIN
name|ZOOMIN
block|,
DECL|enumerator|ZOOMOUT
name|ZOOMOUT
DECL|typedef|ZoomType
block|}
name|ZoomType
typedef|;
end_typedef

begin_function_decl
name|void
name|change_scale
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|ZoomType
name|zoom_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|resize_display
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gboolean
name|resize_window
parameter_list|,
name|gboolean
name|redisplay
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|shrink_wrap_display
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|setup_scale
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|bounds_checking
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCALE_H__  */
end_comment

end_unit


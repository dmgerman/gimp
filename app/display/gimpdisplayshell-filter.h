begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Manish Singh  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GDISPLAY_COLOR_H__
end_ifndef

begin_define
DECL|macro|__GDISPLAY_COLOR_H__
define|#
directive|define
name|__GDISPLAY_COLOR_H__
end_define

begin_include
include|#
directive|include
file|"libgimp/color_display.h"
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_typedef
DECL|typedef|ColorDisplayNode
typedef|typedef
name|struct
name|_ColorDisplayNode
name|ColorDisplayNode
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorDisplayNode
struct|struct
name|_ColorDisplayNode
block|{
DECL|member|cd_ID
name|gpointer
name|cd_ID
decl_stmt|;
DECL|member|cd_name
name|char
modifier|*
name|cd_name
decl_stmt|;
DECL|member|cd_convert
name|GimpColorDisplayConvert
name|cd_convert
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpCDFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpCDFunc
function_decl|)
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|color_display_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_display_foreach
parameter_list|(
name|GimpCDFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ColorDisplayNode
modifier|*
name|gdisplay_color_attach
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_color_detach
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_color_detach_destroy
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_color_detach_all
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_color_reorder_up
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_color_reorder_down
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GDISPLAY_COLOR_H__ */
end_comment

end_unit


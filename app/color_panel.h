begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_PANEL_H__
end_ifndef

begin_define
DECL|macro|__COLOR_PANEL_H__
define|#
directive|define
name|__COLOR_PANEL_H__
end_define

begin_typedef
DECL|typedef|ColorPanel
typedef|typedef
name|struct
name|_ColorPanel
name|ColorPanel
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorPanel
struct|struct
name|_ColorPanel
block|{
comment|/*  The calling procedure is respondible for showing this widget  */
DECL|member|color_panel_widget
name|GtkWidget
modifier|*
name|color_panel_widget
decl_stmt|;
comment|/*  The actual color  */
DECL|member|color
name|unsigned
name|char
name|color
index|[
literal|3
index|]
decl_stmt|;
comment|/*  Don't touch this :)  */
DECL|member|private_part
name|void
modifier|*
name|private_part
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|ColorPanel
modifier|*
name|color_panel_new
parameter_list|(
name|unsigned
name|char
modifier|*
name|initial
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_panel_free
parameter_list|(
name|ColorPanel
modifier|*
name|color_panel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __COLOR_PANEL_H__  */
end_comment

end_unit


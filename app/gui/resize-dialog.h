begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__RESIZE_H__
end_ifndef

begin_define
DECL|macro|__RESIZE_H__
define|#
directive|define
name|__RESIZE_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29f49acf0103
block|{
DECL|enumerator|ScaleWidget
name|ScaleWidget
block|,
DECL|enumerator|ResizeWidget
name|ResizeWidget
DECL|typedef|ResizeType
block|}
name|ResizeType
typedef|;
end_typedef

begin_typedef
DECL|typedef|Resize
typedef|typedef
name|struct
name|_Resize
name|Resize
typedef|;
end_typedef

begin_struct
DECL|struct|_Resize
struct|struct
name|_Resize
block|{
comment|/*  The calling procedure is respondible for showing this widget  */
DECL|member|resize_widget
name|GtkWidget
modifier|*
name|resize_widget
decl_stmt|;
DECL|member|type
name|ResizeType
name|type
decl_stmt|;
DECL|member|width
name|int
name|width
decl_stmt|;
DECL|member|height
name|int
name|height
decl_stmt|;
DECL|member|off_x
name|int
name|off_x
decl_stmt|;
DECL|member|off_y
name|int
name|off_y
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
name|Resize
modifier|*
name|resize_widget_new
parameter_list|(
name|ResizeType
name|type
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
name|resize_widget_free
parameter_list|(
name|Resize
modifier|*
name|resize
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __RESIZE_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|"libgimp/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29e00c480103
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
typedef|typedef
enum|enum
DECL|enum|__anon29e00c480203
block|{
DECL|enumerator|ResizeImage
name|ResizeImage
block|,
DECL|enumerator|ResizeLayer
name|ResizeLayer
DECL|typedef|ResizeTarget
block|}
name|ResizeTarget
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
DECL|member|resize_shell
name|GtkWidget
modifier|*
name|resize_shell
decl_stmt|;
DECL|member|type
name|ResizeType
name|type
decl_stmt|;
DECL|member|target
name|ResizeTarget
name|target
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|resolution_x
name|gdouble
name|resolution_x
decl_stmt|;
DECL|member|resolution_y
name|gdouble
name|resolution_y
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|ratio_x
name|gdouble
name|ratio_x
decl_stmt|;
DECL|member|ratio_y
name|gdouble
name|ratio_y
decl_stmt|;
DECL|member|offset_x
name|gint
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gint
name|offset_y
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29e00c480308
block|{
DECL|member|resize
name|Resize
modifier|*
name|resize
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|typedef|ImageResize
block|}
name|ImageResize
typedef|;
end_typedef

begin_comment
comment|/* If resolution_x is zero, then don't show resolution modification  * parts of the dialog. If object is non-NULL, then attach the cancel  * callback to its destroy signal. */
end_comment

begin_function_decl
name|Resize
modifier|*
name|resize_widget_new
parameter_list|(
name|ResizeType
name|type
parameter_list|,
name|ResizeTarget
name|target
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
name|resolution_x
parameter_list|,
name|gdouble
name|resolution_y
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|GtkSignalFunc
name|ok_cb
parameter_list|,
name|GtkSignalFunc
name|cancel_cb
parameter_list|,
name|gpointer
name|user_data
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

begin_comment
comment|/* Layer scaling sanity check and warning dialogs */
end_comment

begin_function_decl
name|gboolean
name|resize_check_layer_scaling
parameter_list|(
name|ImageResize
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|resize_scale_implement
parameter_list|(
name|ImageResize
modifier|*
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


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__RESIZE_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__RESIZE_DIALOG_H__
define|#
directive|define
name|__RESIZE_DIALOG_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27e8b7b00103
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
DECL|enum|__anon27e8b7b00203
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
DECL|member|resize_shell
name|GtkWidget
modifier|*
name|resize_shell
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
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
DECL|member|interpolation
name|GimpInterpolationType
name|interpolation
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  If resolution_x is zero, then don't show resolution modification  *  parts of the dialog.  *  *  If object and signal are non-NULL, then attach the cancel callback to signal.  *  *  If cancel_callback is NULL, then the dialog will be destroyed on "Cancel".  */
end_comment

begin_function_decl
name|Resize
modifier|*
name|resize_widget_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|ResizeType
name|type
parameter_list|,
name|ResizeTarget
name|target
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal
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
name|GCallback
name|ok_cb
parameter_list|,
name|GCallback
name|cancel_cb
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __RESIZE_DIALOG_H__  */
end_comment

end_unit


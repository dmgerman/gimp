begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ACTIONS_H__
end_ifndef

begin_define
DECL|macro|__ACTIONS_H__
define|#
directive|define
name|__ACTIONS_H__
end_define

begin_decl_stmt
specifier|extern
name|GimpActionFactory
modifier|*
name|global_action_factory
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|actions_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|actions_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Gimp
modifier|*
name|action_data_get_gimp
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|action_data_get_image
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplay
modifier|*
name|action_data_get_display
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|action_data_get_widget
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|return_if_no_gimp (gimp,data)
define|#
directive|define
name|return_if_no_gimp
parameter_list|(
name|gimp
parameter_list|,
name|data
parameter_list|)
define|\
value|gimp = action_data_get_gimp (data); \   if (! gimp) \     return
end_define

begin_define
DECL|macro|return_if_no_image (gimage,data)
define|#
directive|define
name|return_if_no_image
parameter_list|(
name|gimage
parameter_list|,
name|data
parameter_list|)
define|\
value|gimage = action_data_get_image (data); \   if (! gimage) \     return
end_define

begin_define
DECL|macro|return_if_no_display (gdisp,data)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|gdisp
parameter_list|,
name|data
parameter_list|)
define|\
value|gdisp = action_data_get_display (data); \   if (! gdisp) \     return
end_define

begin_define
DECL|macro|return_if_no_widget (widget,data)
define|#
directive|define
name|return_if_no_widget
parameter_list|(
name|widget
parameter_list|,
name|data
parameter_list|)
define|\
value|widget = action_data_get_widget (data); \   if (! widget) \     return
end_define

begin_define
DECL|macro|return_if_no_drawable (gimage,drawable,data)
define|#
directive|define
name|return_if_no_drawable
parameter_list|(
name|gimage
parameter_list|,
name|drawable
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage,data); \   drawable = gimp_image_active_drawable (gimage); \   if (! drawable) \     return
end_define

begin_define
DECL|macro|return_if_no_layer (gimage,layer,data)
define|#
directive|define
name|return_if_no_layer
parameter_list|(
name|gimage
parameter_list|,
name|layer
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage,data); \   layer = gimp_image_get_active_layer (gimage); \   if (! layer) \     return
end_define

begin_define
DECL|macro|return_if_no_channel (gimage,channel,data)
define|#
directive|define
name|return_if_no_channel
parameter_list|(
name|gimage
parameter_list|,
name|channel
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage,data); \   channel = gimp_image_get_active_channel (gimage); \   if (! channel) \     return
end_define

begin_define
DECL|macro|return_if_no_vectors (gimage,vectors,data)
define|#
directive|define
name|return_if_no_vectors
parameter_list|(
name|gimage
parameter_list|,
name|vectors
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage,data); \   vectors = gimp_image_get_active_vectors (gimage); \   if (! vectors) \     return
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ACTIONS_H__ */
end_comment

end_unit


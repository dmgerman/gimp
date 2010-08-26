begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
name|GimpContext
modifier|*
name|action_data_get_context
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
name|GimpDisplayShell
modifier|*
name|action_data_get_shell
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

begin_function_decl
name|gint
name|action_data_sel_count
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|action_select_value
parameter_list|(
name|GimpActionSelectType
name|select_type
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gdouble
name|min
parameter_list|,
name|gdouble
name|max
parameter_list|,
name|gdouble
name|def
parameter_list|,
name|gdouble
name|small_inc
parameter_list|,
name|gdouble
name|inc
parameter_list|,
name|gdouble
name|skip_inc
parameter_list|,
name|gdouble
name|delta_factor
parameter_list|,
name|gboolean
name|wrap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|action_select_property
parameter_list|(
name|GimpActionSelectType
name|select_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gdouble
name|small_inc
parameter_list|,
name|gdouble
name|inc
parameter_list|,
name|gdouble
name|skip_inc
parameter_list|,
name|gdouble
name|delta_factor
parameter_list|,
name|gboolean
name|wrap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|action_select_object
parameter_list|(
name|GimpActionSelectType
name|select_type
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|current
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|action_message
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|3
operator|,
function_decl|4
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

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
DECL|macro|return_if_no_context (context,data)
define|#
directive|define
name|return_if_no_context
parameter_list|(
name|context
parameter_list|,
name|data
parameter_list|)
define|\
value|context = action_data_get_context (data); \   if (! context) \     return
end_define

begin_define
DECL|macro|return_if_no_image (image,data)
define|#
directive|define
name|return_if_no_image
parameter_list|(
name|image
parameter_list|,
name|data
parameter_list|)
define|\
value|image = action_data_get_image (data); \   if (! image) \     return
end_define

begin_define
DECL|macro|return_if_no_display (display,data)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|display
parameter_list|,
name|data
parameter_list|)
define|\
value|display = action_data_get_display (data); \   if (! display) \     return
end_define

begin_define
DECL|macro|return_if_no_shell (shell,data)
define|#
directive|define
name|return_if_no_shell
parameter_list|(
name|shell
parameter_list|,
name|data
parameter_list|)
define|\
value|shell = action_data_get_shell (data); \   if (! shell) \     return
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
DECL|macro|return_if_no_drawable (image,drawable,data)
define|#
directive|define
name|return_if_no_drawable
parameter_list|(
name|image
parameter_list|,
name|drawable
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (image,data); \   drawable = gimp_image_get_active_drawable (image); \   if (! drawable) \     return
end_define

begin_define
DECL|macro|return_if_no_layer (image,layer,data)
define|#
directive|define
name|return_if_no_layer
parameter_list|(
name|image
parameter_list|,
name|layer
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (image,data); \   layer = gimp_image_get_active_layer (image); \   if (! layer) \     return
end_define

begin_define
DECL|macro|return_if_no_channel (image,channel,data)
define|#
directive|define
name|return_if_no_channel
parameter_list|(
name|image
parameter_list|,
name|channel
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (image,data); \   channel = gimp_image_get_active_channel (image); \   if (! channel) \     return
end_define

begin_define
DECL|macro|return_if_no_vectors (image,vectors,data)
define|#
directive|define
name|return_if_no_vectors
parameter_list|(
name|image
parameter_list|,
name|vectors
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (image,data); \   vectors = gimp_image_get_active_vectors (image); \   if (! vectors) \     return
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ACTIONS_H__ */
end_comment

end_unit


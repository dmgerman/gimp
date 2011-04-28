begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewablebutton.h  * Copyright (C) 2003-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VIEWABLE_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VIEWABLE_BUTTON_H__
define|#
directive|define
name|__GIMP_VIEWABLE_BUTTON_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_VIEWABLE_BUTTON
define|#
directive|define
name|GIMP_TYPE_VIEWABLE_BUTTON
value|(gimp_viewable_button_get_type ())
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_BUTTON (obj)
define|#
directive|define
name|GIMP_VIEWABLE_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VIEWABLE_BUTTON, GimpViewableButton))
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_VIEWABLE_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VIEWABLE_BUTTON, GimpViewableButtonClass))
end_define

begin_define
DECL|macro|GIMP_IS_VIEWABLE_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_VIEWABLE_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VIEWABLE_BUTTON))
end_define

begin_define
DECL|macro|GIMP_IS_VIEWABLE_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VIEWABLE_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VIEWABLE_BUTTON))
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VIEWABLE_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VIEWABLE_BUTTON, GimpViewableButtonClass))
end_define

begin_typedef
DECL|typedef|GimpViewableButtonClass
typedef|typedef
name|struct
name|_GimpViewableButtonClass
name|GimpViewableButtonClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpViewableButton
struct|struct
name|_GimpViewableButton
block|{
DECL|member|parent_instance
name|GimpButton
name|parent_instance
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|popup_view_type
name|GimpViewType
name|popup_view_type
decl_stmt|;
DECL|member|popup_view_size
name|gint
name|popup_view_size
decl_stmt|;
DECL|member|button_view_size
name|gint
name|button_view_size
decl_stmt|;
DECL|member|view_border_width
name|gint
name|view_border_width
decl_stmt|;
DECL|member|dialog_factory
name|GimpDialogFactory
modifier|*
name|dialog_factory
decl_stmt|;
DECL|member|dialog_identifier
name|gchar
modifier|*
name|dialog_identifier
decl_stmt|;
DECL|member|dialog_stock_id
name|gchar
modifier|*
name|dialog_stock_id
decl_stmt|;
DECL|member|dialog_tooltip
name|gchar
modifier|*
name|dialog_tooltip
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpViewableButtonClass
struct|struct
name|_GimpViewableButtonClass
block|{
DECL|member|parent_class
name|GimpButtonClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_viewable_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_viewable_button_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|gint
name|button_view_size
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpViewType
name|gimp_viewable_button_get_view_type
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_viewable_button_set_view_type
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_viewable_button_get_view_size
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_viewable_button_set_view_size
parameter_list|(
name|GimpViewableButton
modifier|*
name|button
parameter_list|,
name|gint
name|view_size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_VIEWABLE_BUTTON_H__ */
end_comment

end_unit


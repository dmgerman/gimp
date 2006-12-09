begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerpopup.h  * Copyright (C) 2003-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_POPUP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_POPUP_H__
define|#
directive|define
name|__GIMP_CONTAINER_POPUP_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkwindow.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_POPUP
define|#
directive|define
name|GIMP_TYPE_CONTAINER_POPUP
value|(gimp_container_popup_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_POPUP (obj)
define|#
directive|define
name|GIMP_CONTAINER_POPUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_POPUP, GimpContainerPopup))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_POPUP_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_POPUP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_POPUP, GimpContainerPopupClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_POPUP (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_POPUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_POPUP))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_POPUP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_POPUP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_POPUP))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_POPUP_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_POPUP_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_POPUP, GimpContainerPopupClass))
end_define

begin_typedef
DECL|typedef|GimpContainerPopupClass
typedef|typedef
name|struct
name|_GimpContainerPopupClass
name|GimpContainerPopupClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerPopup
struct|struct
name|_GimpContainerPopup
block|{
DECL|member|parent_instance
name|GtkWindow
name|parent_instance
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|orig_context
name|GimpContext
modifier|*
name|orig_context
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|view_type
name|GimpViewType
name|view_type
decl_stmt|;
DECL|member|default_view_size
name|gint
name|default_view_size
decl_stmt|;
DECL|member|view_size
name|gint
name|view_size
decl_stmt|;
DECL|member|view_border_width
name|gint
name|view_border_width
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|editor
name|GimpContainerEditor
modifier|*
name|editor
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
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerPopupClass
struct|struct
name|_GimpContainerPopupClass
block|{
DECL|member|parent_instance
name|GtkWindowClass
name|parent_instance
decl_stmt|;
DECL|member|cancel
name|void
function_decl|(
modifier|*
name|cancel
function_decl|)
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
DECL|member|confirm
name|void
function_decl|(
modifier|*
name|confirm
function_decl|)
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_popup_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_container_popup_new
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
name|default_view_size
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
name|void
name|gimp_container_popup_show
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpViewType
name|gimp_container_popup_get_view_type
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_popup_set_view_type
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_container_popup_get_view_size
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_popup_set_view_size
parameter_list|(
name|GimpContainerPopup
modifier|*
name|popup
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
comment|/*  __GIMP_CONTAINER_POPUP_H__  */
end_comment

end_unit


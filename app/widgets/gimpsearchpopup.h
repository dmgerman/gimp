begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsearchpopup.h  * Copyright (C) 2015 Jehan<jehan at girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SEARCH_POPUP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SEARCH_POPUP_H__
define|#
directive|define
name|__GIMP_SEARCH_POPUP_H__
end_define

begin_include
include|#
directive|include
file|"gimppopup.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SEARCH_POPUP
define|#
directive|define
name|GIMP_TYPE_SEARCH_POPUP
value|(gimp_search_popup_get_type ())
end_define

begin_define
DECL|macro|GIMP_SEARCH_POPUP (obj)
define|#
directive|define
name|GIMP_SEARCH_POPUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SEARCH_POPUP, GimpSearchPopup))
end_define

begin_define
DECL|macro|GIMP_SEARCH_POPUP_CLASS (klass)
define|#
directive|define
name|GIMP_SEARCH_POPUP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SEARCH_POPUP, GimpSearchPopupClass))
end_define

begin_define
DECL|macro|GIMP_IS_SEARCH_POPUP (obj)
define|#
directive|define
name|GIMP_IS_SEARCH_POPUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SEARCH_POPUP))
end_define

begin_define
DECL|macro|GIMP_IS_SEARCH_POPUP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SEARCH_POPUP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SEARCH_POPUP))
end_define

begin_define
DECL|macro|GIMP_SEARCH_POPUP_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SEARCH_POPUP_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SEARCH_POPUP, GimpSearchPopupClass))
end_define

begin_comment
comment|/**  * GimpSearchPopupCallback:  * @popup:  the #GimpSearchPopup to operate on.  * @search: the text searched.  *   * Callback used by @popup to fill in its result list.  * It should make use of gimp_search_popup_add_result() to fill in  * results.  */
end_comment

begin_typedef
DECL|typedef|GimpSearchPopup
typedef|typedef
name|struct
name|_GimpSearchPopup
name|GimpSearchPopup
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSearchPopupClass
typedef|typedef
name|struct
name|_GimpSearchPopupClass
name|GimpSearchPopupClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSearchPopupPrivate
typedef|typedef
name|struct
name|_GimpSearchPopupPrivate
name|GimpSearchPopupPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSearchPopupCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSearchPopupCallback
function_decl|)
parameter_list|(
name|GimpSearchPopup
modifier|*
name|popup
parameter_list|,
specifier|const
name|gchar
modifier|*
name|search
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|_GimpSearchPopup
struct|struct
name|_GimpSearchPopup
block|{
DECL|member|parent_instance
name|GimpPopup
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpSearchPopupPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSearchPopupClass
struct|struct
name|_GimpSearchPopupClass
block|{
DECL|member|parent_class
name|GimpPopupClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_search_popup_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_search_popup_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpSearchPopupCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_search_popup_add_result
parameter_list|(
name|GimpSearchPopup
modifier|*
name|popup
parameter_list|,
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|section
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SEARCH_POPUP_H__  */
end_comment

end_unit


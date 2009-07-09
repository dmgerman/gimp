begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptagpopup.h  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TAG_POPUP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TAG_POPUP_H__
define|#
directive|define
name|__GIMP_TAG_POPUP_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TAG_POPUP
define|#
directive|define
name|GIMP_TYPE_TAG_POPUP
value|(gimp_tag_popup_get_type ())
end_define

begin_define
DECL|macro|GIMP_TAG_POPUP (obj)
define|#
directive|define
name|GIMP_TAG_POPUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TAG_POPUP, GimpTagPopup))
end_define

begin_define
DECL|macro|GIMP_IS_TAG_POPUP (obj)
define|#
directive|define
name|GIMP_IS_TAG_POPUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TAG_POPUP))
end_define

begin_define
DECL|macro|GIMP_IS_TAG_POPUP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TAG_POPUP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TAG_POPUP))
end_define

begin_define
DECL|macro|GIMP_TAG_POPUP_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TAG_POPUP_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TAG_POPUP, GimpTagPopupClass))
end_define

begin_typedef
DECL|typedef|GimpTagPopupClass
typedef|typedef
name|struct
name|_GimpTagPopupClass
name|GimpTagPopupClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|PopupTagData
typedef|typedef
name|struct
name|_PopupTagData
name|PopupTagData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTagPopup
struct|struct
name|_GimpTagPopup
block|{
DECL|member|parent_instance
name|GtkWindow
name|parent_instance
decl_stmt|;
DECL|member|combo_entry
name|GimpComboTagEntry
modifier|*
name|combo_entry
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|alignment
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
DECL|member|tag_area
name|GtkWidget
modifier|*
name|tag_area
decl_stmt|;
DECL|member|context
name|PangoContext
modifier|*
name|context
decl_stmt|;
DECL|member|layout
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
DECL|member|tag_data
name|PopupTagData
modifier|*
name|tag_data
decl_stmt|;
DECL|member|prelight
name|PopupTagData
modifier|*
name|prelight
decl_stmt|;
DECL|member|tag_count
name|gint
name|tag_count
decl_stmt|;
DECL|member|close_rectangles
name|GList
modifier|*
name|close_rectangles
decl_stmt|;
DECL|member|timeout_id
name|guint
name|timeout_id
decl_stmt|;
DECL|member|scroll_height
name|gint
name|scroll_height
decl_stmt|;
DECL|member|scroll_y
name|gint
name|scroll_y
decl_stmt|;
DECL|member|scroll_step
name|gint
name|scroll_step
decl_stmt|;
DECL|member|scroll_arrow_height
name|gint
name|scroll_arrow_height
decl_stmt|;
DECL|member|scroll_fast
name|gboolean
name|scroll_fast
decl_stmt|;
DECL|member|arrows_visible
name|gboolean
name|arrows_visible
decl_stmt|;
DECL|member|ignore_button_release
name|gboolean
name|ignore_button_release
decl_stmt|;
DECL|member|upper_arrow_prelight
name|gboolean
name|upper_arrow_prelight
decl_stmt|;
DECL|member|lower_arrow_prelight
name|gboolean
name|lower_arrow_prelight
decl_stmt|;
DECL|member|single_select_disabled
name|gboolean
name|single_select_disabled
decl_stmt|;
DECL|member|upper_arrow_state
name|GtkStateType
name|upper_arrow_state
decl_stmt|;
DECL|member|lower_arrow_state
name|GtkStateType
name|lower_arrow_state
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTagPopupClass
struct|struct
name|_GimpTagPopupClass
block|{
DECL|member|parent_class
name|GtkWindowClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tag_popup_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_tag_popup_new
parameter_list|(
name|GimpComboTagEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tag_popup_show
parameter_list|(
name|GimpTagPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TAG_POPUP_H__  */
end_comment

end_unit


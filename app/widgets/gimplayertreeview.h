begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplayerlistview.h  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_LIST_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_LIST_VIEW_H__
define|#
directive|define
name|__GIMP_LAYER_LIST_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawablelistview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LAYER_LIST_VIEW
define|#
directive|define
name|GIMP_TYPE_LAYER_LIST_VIEW
value|(gimp_layer_list_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER_LIST_VIEW (obj)
define|#
directive|define
name|GIMP_LAYER_LIST_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_LAYER_LIST_VIEW, GimpLayerListView))
end_define

begin_define
DECL|macro|GIMP_LAYER_LIST_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_LIST_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER_LIST_VIEW, GimpLayerListViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_LIST_VIEW (obj)
define|#
directive|define
name|GIMP_IS_LAYER_LIST_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_LAYER_LIST_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_LIST_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_LIST_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER_LIST_VIEW))
end_define

begin_typedef
DECL|typedef|GimpLayerListViewClass
typedef|typedef
name|struct
name|_GimpLayerListViewClass
name|GimpLayerListViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLayerListView
struct|struct
name|_GimpLayerListView
block|{
DECL|member|parent_instance
name|GimpDrawableListView
name|parent_instance
decl_stmt|;
DECL|member|options_box
name|GtkWidget
modifier|*
name|options_box
decl_stmt|;
DECL|member|paint_mode_menu
name|GtkWidget
modifier|*
name|paint_mode_menu
decl_stmt|;
DECL|member|preserve_trans_toggle
name|GtkWidget
modifier|*
name|preserve_trans_toggle
decl_stmt|;
DECL|member|opacity_adjustment
name|GtkAdjustment
modifier|*
name|opacity_adjustment
decl_stmt|;
DECL|member|anchor_button
name|GtkWidget
modifier|*
name|anchor_button
decl_stmt|;
comment|/*< private>*/
DECL|member|mode_changed_handler_id
name|GQuark
name|mode_changed_handler_id
decl_stmt|;
DECL|member|opacity_changed_handler_id
name|GQuark
name|opacity_changed_handler_id
decl_stmt|;
DECL|member|preserve_trans_changed_handler_id
name|GQuark
name|preserve_trans_changed_handler_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerListViewClass
struct|struct
name|_GimpLayerListViewClass
block|{
DECL|member|parent_class
name|GimpDrawableListViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_layer_list_view_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_LAYER_LIST_VIEW_H__  */
end_comment

end_unit


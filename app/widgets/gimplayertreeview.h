begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplayertreeview.h  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_TREE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_TREE_VIEW_H__
define|#
directive|define
name|__GIMP_LAYER_TREE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawabletreeview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LAYER_TREE_VIEW
define|#
directive|define
name|GIMP_TYPE_LAYER_TREE_VIEW
value|(gimp_layer_tree_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_LAYER_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LAYER_TREE_VIEW, GimpLayerTreeView))
end_define

begin_define
DECL|macro|GIMP_LAYER_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER_TREE_VIEW, GimpLayerTreeViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_LAYER_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LAYER_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_LAYER_TREE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LAYER_TREE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LAYER_TREE_VIEW, GimpLayerTreeViewClass))
end_define

begin_typedef
DECL|typedef|GimpLayerTreeViewClass
typedef|typedef
name|struct
name|_GimpLayerTreeViewClass
name|GimpLayerTreeViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLayerTreeView
struct|struct
name|_GimpLayerTreeView
block|{
DECL|member|parent_instance
name|GimpDrawableTreeView
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
DECL|member|opacity_adjustment
name|GtkAdjustment
modifier|*
name|opacity_adjustment
decl_stmt|;
DECL|member|lock_alpha_toggle
name|GtkWidget
modifier|*
name|lock_alpha_toggle
decl_stmt|;
DECL|member|model_column_mask
name|gint
name|model_column_mask
decl_stmt|;
DECL|member|model_column_mask_visible
name|gint
name|model_column_mask_visible
decl_stmt|;
DECL|member|mask_cell
name|GtkCellRenderer
modifier|*
name|mask_cell
decl_stmt|;
DECL|member|italic_attrs
name|PangoAttrList
modifier|*
name|italic_attrs
decl_stmt|;
DECL|member|bold_attrs
name|PangoAttrList
modifier|*
name|bold_attrs
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
DECL|member|lock_alpha_changed_handler_id
name|GQuark
name|lock_alpha_changed_handler_id
decl_stmt|;
DECL|member|mask_changed_handler_id
name|GQuark
name|mask_changed_handler_id
decl_stmt|;
DECL|member|alpha_changed_handler_id
name|GQuark
name|alpha_changed_handler_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerTreeViewClass
struct|struct
name|_GimpLayerTreeViewClass
block|{
DECL|member|parent_class
name|GimpDrawableTreeViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_layer_tree_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_LAYER_TREE_VIEW_H__  */
end_comment

end_unit


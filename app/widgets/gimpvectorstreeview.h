begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectorstreeview.h  * Copyright (C) 2001-2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTORS_TREE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTORS_TREE_VIEW_H__
define|#
directive|define
name|__GIMP_VECTORS_TREE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpitemtreeview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_VECTORS_TREE_VIEW
define|#
directive|define
name|GIMP_TYPE_VECTORS_TREE_VIEW
value|(gimp_vectors_tree_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_VECTORS_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_VECTORS_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VECTORS_TREE_VIEW, GimpVectorsTreeView))
end_define

begin_define
DECL|macro|GIMP_VECTORS_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_VECTORS_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VECTORS_TREE_VIEW, GimpVectorsTreeViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_VECTORS_TREE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_VECTORS_TREE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VECTORS_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_VECTORS_TREE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VECTORS_TREE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VECTORS_TREE_VIEW))
end_define

begin_define
DECL|macro|GIMP_VECTORS_TREE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VECTORS_TREE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VECTORS_TREE_VIEW, GimpVectorsTreeViewClass))
end_define

begin_typedef
DECL|typedef|GimpVectorsTreeViewClass
typedef|typedef
name|struct
name|_GimpVectorsTreeViewClass
name|GimpVectorsTreeViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpVectorsTreeView
struct|struct
name|_GimpVectorsTreeView
block|{
DECL|member|parent_instance
name|GimpItemTreeView
name|parent_instance
decl_stmt|;
DECL|member|toselection_button
name|GtkWidget
modifier|*
name|toselection_button
decl_stmt|;
DECL|member|tovectors_button
name|GtkWidget
modifier|*
name|tovectors_button
decl_stmt|;
DECL|member|stroke_button
name|GtkWidget
modifier|*
name|stroke_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpVectorsTreeViewClass
struct|struct
name|_GimpVectorsTreeViewClass
block|{
DECL|member|parent_class
name|GimpItemTreeViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_vectors_tree_view_get_type
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
comment|/*  __GIMP_VECTORS_TREE_VIEW_H__  */
end_comment

end_unit


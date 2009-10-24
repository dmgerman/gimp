begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppanedbox.h  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  * Copyright (C)      2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PANED_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PANED_BOX_H__
define|#
directive|define
name|__GIMP_PANED_BOX_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_PANED_BOX
define|#
directive|define
name|GIMP_TYPE_PANED_BOX
value|(gimp_paned_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_PANED_BOX (obj)
define|#
directive|define
name|GIMP_PANED_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PANED_BOX, GimpPanedBox))
end_define

begin_define
DECL|macro|GIMP_PANED_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_PANED_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PANED_BOX, GimpPanedBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_PANED_BOX (obj)
define|#
directive|define
name|GIMP_IS_PANED_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PANED_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_PANED_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PANED_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PANED_BOX))
end_define

begin_define
DECL|macro|GIMP_PANED_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PANED_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PANED_BOX, GimpPanedBoxClass))
end_define

begin_typedef
DECL|typedef|GimpPanedBoxClass
typedef|typedef
name|struct
name|_GimpPanedBoxClass
name|GimpPanedBoxClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPanedBoxPrivate
typedef|typedef
name|struct
name|_GimpPanedBoxPrivate
name|GimpPanedBoxPrivate
typedef|;
end_typedef

begin_comment
comment|/**  * GimpPanedBox:  *  * A #GtkBox with the children separated by #GtkPaned:s and basic  * docking mechanisms.  */
end_comment

begin_struct
DECL|struct|_GimpPanedBox
struct|struct
name|_GimpPanedBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpPanedBoxPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPanedBoxClass
struct|struct
name|_GimpPanedBoxClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_paned_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_paned_box_new
parameter_list|(
name|gboolean
name|homogeneous
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GtkOrientation
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paned_box_set_dropped_cb
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|GimpDockSeparatorDroppedFunc
name|dropped_cb
parameter_list|,
name|gpointer
name|dropped_cb_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paned_box_add_widget
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paned_box_remove_widget
parameter_list|(
name|GimpPanedBox
modifier|*
name|paned_box
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paned_box_show_separators
parameter_list|(
name|GimpPanedBox
modifier|*
name|dock
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paned_box_class_show_separators
parameter_list|(
name|GimpPanedBoxClass
modifier|*
name|klass
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PANED_BOX_H__ */
end_comment

end_unit


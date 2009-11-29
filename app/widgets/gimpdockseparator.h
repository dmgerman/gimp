begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockseparator.h  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCK_SEPARATOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCK_SEPARATOR_H__
define|#
directive|define
name|__GIMP_DOCK_SEPARATOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DOCK_SEPARATOR
define|#
directive|define
name|GIMP_TYPE_DOCK_SEPARATOR
value|(gimp_dock_separator_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCK_SEPARATOR (obj)
define|#
directive|define
name|GIMP_DOCK_SEPARATOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCK_SEPARATOR, GimpDockSeparator))
end_define

begin_define
DECL|macro|GIMP_DOCK_SEPARATOR_CLASS (klass)
define|#
directive|define
name|GIMP_DOCK_SEPARATOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCK_SEPARATOR, GimpDockSeparatorClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_SEPARATOR (obj)
define|#
directive|define
name|GIMP_IS_DOCK_SEPARATOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCK_SEPARATOR))
end_define

begin_define
DECL|macro|GIMP_IS_DOCK_SEPARATOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCK_SEPARATOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCK_SEPARATOR))
end_define

begin_define
DECL|macro|GIMP_DOCK_SEPARATOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DOCK_SEPARATOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DOCK_SEPARATOR, GimpDockSeparatorClass))
end_define

begin_typedef
DECL|typedef|GimpDockSeparatorPrivate
typedef|typedef
name|struct
name|_GimpDockSeparatorPrivate
name|GimpDockSeparatorPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDockSeparatorClass
typedef|typedef
name|struct
name|_GimpDockSeparatorClass
name|GimpDockSeparatorClass
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDockSeparator:  *  * Separates dockable and acts as drop-targets to allow rearrangements  * of them.  */
end_comment

begin_struct
DECL|struct|_GimpDockSeparator
struct|struct
name|_GimpDockSeparator
block|{
DECL|member|parent_instance
name|GtkEventBox
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpDockSeparatorPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDockSeparatorClass
struct|struct
name|_GimpDockSeparatorClass
block|{
DECL|member|parent_class
name|GtkEventBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dock_separator_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dock_separator_new
parameter_list|(
name|GtkAnchorType
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_separator_set_dropped_cb
parameter_list|(
name|GimpDockSeparator
modifier|*
name|separator
parameter_list|,
name|GimpPanedBoxDroppedFunc
name|dropped_cb
parameter_list|,
name|gpointer
name|dropped_cb_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_dock_separator_get_insert_pos
parameter_list|(
name|GimpDockSeparator
modifier|*
name|separator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dock_separator_set_show_label
parameter_list|(
name|GimpDockSeparator
modifier|*
name|separator
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
comment|/* __GIMP_DOCK_SEPARATOR_H__ */
end_comment

end_unit


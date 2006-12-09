begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpactionview.h  * Copyright (C) 2004-2005  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ACTION_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ACTION_VIEW_H__
define|#
directive|define
name|__GIMP_ACTION_VIEW_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtktreeview.h>
end_include

begin_enum
enum|enum
DECL|enum|__anon2c8573390103
block|{
DECL|enumerator|GIMP_ACTION_VIEW_COLUMN_ACTION
name|GIMP_ACTION_VIEW_COLUMN_ACTION
block|,
DECL|enumerator|GIMP_ACTION_VIEW_COLUMN_STOCK_ID
name|GIMP_ACTION_VIEW_COLUMN_STOCK_ID
block|,
DECL|enumerator|GIMP_ACTION_VIEW_COLUMN_LABEL
name|GIMP_ACTION_VIEW_COLUMN_LABEL
block|,
DECL|enumerator|GIMP_ACTION_VIEW_COLUMN_NAME
name|GIMP_ACTION_VIEW_COLUMN_NAME
block|,
DECL|enumerator|GIMP_ACTION_VIEW_COLUMN_ACCEL_KEY
name|GIMP_ACTION_VIEW_COLUMN_ACCEL_KEY
block|,
DECL|enumerator|GIMP_ACTION_VIEW_COLUMN_ACCEL_MASK
name|GIMP_ACTION_VIEW_COLUMN_ACCEL_MASK
block|,
DECL|enumerator|GIMP_ACTION_VIEW_COLUMN_ACCEL_CLOSURE
name|GIMP_ACTION_VIEW_COLUMN_ACCEL_CLOSURE
block|,
DECL|enumerator|GIMP_ACTION_VIEW_NUM_COLUMNS
name|GIMP_ACTION_VIEW_NUM_COLUMNS
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TYPE_ACTION_VIEW
define|#
directive|define
name|GIMP_TYPE_ACTION_VIEW
value|(gimp_action_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_ACTION_VIEW (obj)
define|#
directive|define
name|GIMP_ACTION_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ACTION_VIEW, GimpActionView))
end_define

begin_define
DECL|macro|GIMP_ACTION_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_ACTION_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ACTION_VIEW, GimpActionViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION_VIEW (obj)
define|#
directive|define
name|GIMP_IS_ACTION_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ACTION_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ACTION_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ACTION_VIEW))
end_define

begin_define
DECL|macro|GIMP_ACTION_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ACTION_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ACTION_VIEW, GimpActionViewClass))
end_define

begin_typedef
DECL|typedef|GimpActionViewClass
typedef|typedef
name|struct
name|_GimpActionViewClass
name|GimpActionViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpActionView
struct|struct
name|_GimpActionView
block|{
DECL|member|parent_instance
name|GtkTreeView
name|parent_instance
decl_stmt|;
DECL|member|manager
name|GimpUIManager
modifier|*
name|manager
decl_stmt|;
DECL|member|show_shortcuts
name|gboolean
name|show_shortcuts
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpActionViewClass
struct|struct
name|_GimpActionViewClass
block|{
DECL|member|parent_class
name|GtkTreeViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_action_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_action_view_new
parameter_list|(
name|GimpUIManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|select_action
parameter_list|,
name|gboolean
name|show_shortcuts
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ACTION_VIEW_H__  */
end_comment

end_unit


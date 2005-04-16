begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpaction.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ACTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ACTION_H__
define|#
directive|define
name|__GIMP_ACTION_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkaction.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_ACTION
define|#
directive|define
name|GIMP_TYPE_ACTION
value|(gimp_action_get_type ())
end_define

begin_define
DECL|macro|GIMP_ACTION (obj)
define|#
directive|define
name|GIMP_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ACTION, GimpAction))
end_define

begin_define
DECL|macro|GIMP_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ACTION, GimpActionClass))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION (obj)
define|#
directive|define
name|GIMP_IS_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ACTION))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((obj), GIMP_TYPE_ACTION))
end_define

begin_define
DECL|macro|GIMP_ACTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ACTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS((obj), GIMP_TYPE_ACTION, GimpActionClass))
end_define

begin_typedef
DECL|typedef|GimpActionClass
typedef|typedef
name|struct
name|_GimpActionClass
name|GimpActionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAction
struct|struct
name|_GimpAction
block|{
DECL|member|parent_instance
name|GtkAction
name|parent_instance
decl_stmt|;
DECL|member|color
name|GimpRGB
modifier|*
name|color
decl_stmt|;
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpActionClass
struct|struct
name|_GimpActionClass
block|{
DECL|member|parent_class
name|GtkActionClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpAction
modifier|*
name|gimp_action_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_action_name_compare
parameter_list|(
name|GimpAction
modifier|*
name|action1
parameter_list|,
name|GimpAction
modifier|*
name|action2
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ACTION_H__ */
end_comment

end_unit


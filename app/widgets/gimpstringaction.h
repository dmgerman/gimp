begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpstringaction.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_STRING_ACTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_STRING_ACTION_H__
define|#
directive|define
name|__GIMP_STRING_ACTION_H__
end_define

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_STRING_ACTION
define|#
directive|define
name|GIMP_TYPE_STRING_ACTION
value|(gimp_string_action_get_type ())
end_define

begin_define
DECL|macro|GIMP_STRING_ACTION (obj)
define|#
directive|define
name|GIMP_STRING_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_STRING_ACTION, GimpStringAction))
end_define

begin_define
DECL|macro|GIMP_STRING_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_STRING_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_STRING_ACTION, GimpStringActionClass))
end_define

begin_define
DECL|macro|GIMP_IS_STRING_ACTION (obj)
define|#
directive|define
name|GIMP_IS_STRING_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_STRING_ACTION))
end_define

begin_define
DECL|macro|GIMP_IS_STRING_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_STRING_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((obj), GIMP_TYPE_STRING_ACTION))
end_define

begin_define
DECL|macro|GIMP_STRING_ACTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_STRING_ACTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS((obj), GIMP_TYPE_STRING_ACTION, GimpStringActionClass))
end_define

begin_typedef
DECL|typedef|GimpStringActionClass
typedef|typedef
name|struct
name|_GimpStringActionClass
name|GimpStringActionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpStringAction
struct|struct
name|_GimpStringAction
block|{
DECL|member|parent_instance
name|GimpAction
name|parent_instance
decl_stmt|;
DECL|member|value
name|gchar
modifier|*
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpStringActionClass
struct|struct
name|_GimpStringActionClass
block|{
DECL|member|parent_class
name|GimpActionClass
name|parent_class
decl_stmt|;
DECL|member|selected
name|void
function_decl|(
modifier|*
name|selected
function_decl|)
parameter_list|(
name|GimpStringAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_string_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpStringAction
modifier|*
name|gimp_string_action_new
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_string_action_selected
parameter_list|(
name|GimpStringAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_STRING_ACTION_H__ */
end_comment

end_unit


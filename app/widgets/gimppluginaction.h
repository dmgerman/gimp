begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginaction.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_ACTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_ACTION_H__
define|#
directive|define
name|__GIMP_PLUG_IN_ACTION_H__
end_define

begin_include
include|#
directive|include
file|"gimpaction.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PLUG_IN_ACTION
define|#
directive|define
name|GIMP_TYPE_PLUG_IN_ACTION
value|(gimp_plug_in_action_get_type ())
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_ACTION (obj)
define|#
directive|define
name|GIMP_PLUG_IN_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PLUG_IN_ACTION, GimpPlugInAction))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_PLUG_IN_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PLUG_IN_ACTION, GimpPlugInActionClass))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_ACTION (obj)
define|#
directive|define
name|GIMP_IS_PLUG_IN_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PLUG_IN_ACTION))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PLUG_IN_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((obj), GIMP_TYPE_PLUG_IN_ACTION))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_ACTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PLUG_IN_ACTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS((obj), GIMP_TYPE_PLUG_IN_ACTION, GimpPlugInActionClass))
end_define

begin_typedef
DECL|typedef|GimpPlugInActionClass
typedef|typedef
name|struct
name|_GimpPlugInActionClass
name|GimpPlugInActionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInAction
struct|struct
name|_GimpPlugInAction
block|{
DECL|member|parent_instance
name|GimpAction
name|parent_instance
decl_stmt|;
DECL|member|procedure
name|GimpPlugInProcedure
modifier|*
name|procedure
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPlugInActionClass
struct|struct
name|_GimpPlugInActionClass
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
name|GimpPlugInAction
modifier|*
name|action
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_plug_in_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPlugInAction
modifier|*
name|gimp_plug_in_action_new
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
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_action_selected
parameter_list|(
name|GimpPlugInAction
modifier|*
name|action
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_ACTION_H__ */
end_comment

end_unit


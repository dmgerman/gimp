begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprocedureaction.h  * Copyright (C) 2004-2016 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROCEDURE_ACTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROCEDURE_ACTION_H__
define|#
directive|define
name|__GIMP_PROCEDURE_ACTION_H__
end_define

begin_include
include|#
directive|include
file|"gimpactionimpl.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PROCEDURE_ACTION
define|#
directive|define
name|GIMP_TYPE_PROCEDURE_ACTION
value|(gimp_procedure_action_get_type ())
end_define

begin_define
DECL|macro|GIMP_PROCEDURE_ACTION (obj)
define|#
directive|define
name|GIMP_PROCEDURE_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROCEDURE_ACTION, GimpProcedureAction))
end_define

begin_define
DECL|macro|GIMP_PROCEDURE_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_PROCEDURE_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PROCEDURE_ACTION, GimpProcedureActionClass))
end_define

begin_define
DECL|macro|GIMP_IS_PROCEDURE_ACTION (obj)
define|#
directive|define
name|GIMP_IS_PROCEDURE_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROCEDURE_ACTION))
end_define

begin_define
DECL|macro|GIMP_IS_PROCEDURE_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PROCEDURE_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((obj), GIMP_TYPE_PROCEDURE_ACTION))
end_define

begin_define
DECL|macro|GIMP_PROCEDURE_ACTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PROCEDURE_ACTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS((obj), GIMP_TYPE_PROCEDURE_ACTION, GimpProcedureActionClass))
end_define

begin_typedef
DECL|typedef|GimpProcedureActionClass
typedef|typedef
name|struct
name|_GimpProcedureActionClass
name|GimpProcedureActionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProcedureAction
struct|struct
name|_GimpProcedureAction
block|{
DECL|member|parent_instance
name|GimpActionImpl
name|parent_instance
decl_stmt|;
DECL|member|procedure
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProcedureActionClass
struct|struct
name|_GimpProcedureActionClass
block|{
DECL|member|parent_class
name|GimpActionImplClass
name|parent_class
decl_stmt|;
DECL|member|selected
name|void
function_decl|(
modifier|*
name|selected
function_decl|)
parameter_list|(
name|GimpProcedureAction
modifier|*
name|action
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_procedure_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProcedureAction
modifier|*
name|gimp_procedure_action_new
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
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_action_selected
parameter_list|(
name|GimpProcedureAction
modifier|*
name|action
parameter_list|,
name|GimpProcedure
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
comment|/* __GIMP_PROCEDURE_ACTION_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DYNAMICS_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DYNAMICS_EDITOR_H__
define|#
directive|define
name|__GIMP_DYNAMICS_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpdataeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DYNAMICS_EDITOR
define|#
directive|define
name|GIMP_TYPE_DYNAMICS_EDITOR
value|(gimp_dynamics_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_EDITOR (obj)
define|#
directive|define
name|GIMP_DYNAMICS_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DYNAMICS_EDITOR, GimpDynamicsEditor))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_DYNAMICS_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DYNAMICS_EDITOR, GimpDynamicsEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_DYNAMICS_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DYNAMICS_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DYNAMICS_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DYNAMICS_EDITOR))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DYNAMICS_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DYNAMICS_EDITOR, GimpDynamicsEditorClass))
end_define

begin_typedef
DECL|typedef|GimpDynamicsEditorClass
typedef|typedef
name|struct
name|_GimpDynamicsEditorClass
name|GimpDynamicsEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicsEditor
struct|struct
name|_GimpDynamicsEditor
block|{
DECL|member|parent_instance
name|GimpDataEditor
name|parent_instance
decl_stmt|;
DECL|member|options_vbox
name|GtkWidget
modifier|*
name|options_vbox
decl_stmt|;
comment|//GtkAdjustment  *data;
DECL|member|config_data
name|GObject
modifier|*
name|config_data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDynamicsEditorClass
struct|struct
name|_GimpDynamicsEditorClass
block|{
DECL|member|parent_class
name|GimpDataEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dynamics_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dynamics_editor_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|//GObject *   get_config_value          (GimpDynamics     *options);
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DYNAMICS_EDITOR_H__ */
end_comment

end_unit


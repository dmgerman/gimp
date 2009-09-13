begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOLBOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOLBOX_H__
define|#
directive|define
name|__GIMP_TOOLBOX_H__
end_define

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOLBOX
define|#
directive|define
name|GIMP_TYPE_TOOLBOX
value|(gimp_toolbox_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOLBOX (obj)
define|#
directive|define
name|GIMP_TOOLBOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOLBOX, GimpToolbox))
end_define

begin_define
DECL|macro|GIMP_TOOLBOX_CLASS (klass)
define|#
directive|define
name|GIMP_TOOLBOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOLBOX, GimpToolboxClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOLBOX (obj)
define|#
directive|define
name|GIMP_IS_TOOLBOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOLBOX))
end_define

begin_define
DECL|macro|GIMP_IS_TOOLBOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOLBOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOLBOX))
end_define

begin_define
DECL|macro|GIMP_TOOLBOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOLBOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOLBOX, GimpToolboxClass))
end_define

begin_typedef
DECL|typedef|GimpToolboxClass
typedef|typedef
name|struct
name|_GimpToolboxClass
name|GimpToolboxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolbox
struct|struct
name|_GimpToolbox
block|{
DECL|member|parent_instance
name|GimpDock
name|parent_instance
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|header
name|GtkWidget
modifier|*
name|header
decl_stmt|;
DECL|member|tool_wbox
name|GtkWidget
modifier|*
name|tool_wbox
decl_stmt|;
DECL|member|area_wbox
name|GtkWidget
modifier|*
name|area_wbox
decl_stmt|;
DECL|member|color_area
name|GtkWidget
modifier|*
name|color_area
decl_stmt|;
DECL|member|foo_area
name|GtkWidget
modifier|*
name|foo_area
decl_stmt|;
DECL|member|image_area
name|GtkWidget
modifier|*
name|image_area
decl_stmt|;
DECL|member|tool_rows
name|gint
name|tool_rows
decl_stmt|;
DECL|member|tool_columns
name|gint
name|tool_columns
decl_stmt|;
DECL|member|area_rows
name|gint
name|area_rows
decl_stmt|;
DECL|member|area_columns
name|gint
name|area_columns
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolboxClass
struct|struct
name|_GimpToolboxClass
block|{
DECL|member|parent_class
name|GimpDockClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_toolbox_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_toolbox_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOLBOX_H__ */
end_comment

end_unit


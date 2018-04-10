begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolgyroscope.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_GYROSCOPE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_GYROSCOPE_H__
define|#
directive|define
name|__GIMP_TOOL_GYROSCOPE_H__
end_define

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_GYROSCOPE
define|#
directive|define
name|GIMP_TYPE_TOOL_GYROSCOPE
value|(gimp_tool_gyroscope_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_GYROSCOPE (obj)
define|#
directive|define
name|GIMP_TOOL_GYROSCOPE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_GYROSCOPE, GimpToolGyroscope))
end_define

begin_define
DECL|macro|GIMP_TOOL_GYROSCOPE_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_GYROSCOPE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_GYROSCOPE, GimpToolGyroscopeClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_GYROSCOPE (obj)
define|#
directive|define
name|GIMP_IS_TOOL_GYROSCOPE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_GYROSCOPE))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_GYROSCOPE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_GYROSCOPE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_GYROSCOPE))
end_define

begin_define
DECL|macro|GIMP_TOOL_GYROSCOPE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_GYROSCOPE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_GYROSCOPE, GimpToolGyroscopeClass))
end_define

begin_typedef
DECL|typedef|GimpToolGyroscope
typedef|typedef
name|struct
name|_GimpToolGyroscope
name|GimpToolGyroscope
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolGyroscopePrivate
typedef|typedef
name|struct
name|_GimpToolGyroscopePrivate
name|GimpToolGyroscopePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolGyroscopeClass
typedef|typedef
name|struct
name|_GimpToolGyroscopeClass
name|GimpToolGyroscopeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolGyroscope
struct|struct
name|_GimpToolGyroscope
block|{
DECL|member|parent_instance
name|GimpToolWidget
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolGyroscopePrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolGyroscopeClass
struct|struct
name|_GimpToolGyroscopeClass
block|{
DECL|member|parent_class
name|GimpToolWidgetClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_gyroscope_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_gyroscope_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_GYROSCOPE_H__ */
end_comment

end_unit


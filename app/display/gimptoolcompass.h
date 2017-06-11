begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolcompass.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_COMPASS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_COMPASS_H__
define|#
directive|define
name|__GIMP_TOOL_COMPASS_H__
end_define

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_COMPASS
define|#
directive|define
name|GIMP_TYPE_TOOL_COMPASS
value|(gimp_tool_compass_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_COMPASS (obj)
define|#
directive|define
name|GIMP_TOOL_COMPASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_COMPASS, GimpToolCompass))
end_define

begin_define
DECL|macro|GIMP_TOOL_COMPASS_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_COMPASS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_COMPASS, GimpToolCompassClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_COMPASS (obj)
define|#
directive|define
name|GIMP_IS_TOOL_COMPASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_COMPASS))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_COMPASS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_COMPASS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_COMPASS))
end_define

begin_define
DECL|macro|GIMP_TOOL_COMPASS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_COMPASS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_COMPASS, GimpToolCompassClass))
end_define

begin_typedef
DECL|typedef|GimpToolCompass
typedef|typedef
name|struct
name|_GimpToolCompass
name|GimpToolCompass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolCompassPrivate
typedef|typedef
name|struct
name|_GimpToolCompassPrivate
name|GimpToolCompassPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolCompassClass
typedef|typedef
name|struct
name|_GimpToolCompassClass
name|GimpToolCompassClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolCompass
struct|struct
name|_GimpToolCompass
block|{
DECL|member|parent_instance
name|GimpToolWidget
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolCompassPrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolCompassClass
struct|struct
name|_GimpToolCompassClass
block|{
DECL|member|parent_class
name|GimpToolWidgetClass
name|parent_class
decl_stmt|;
DECL|member|create_guides
name|void
function_decl|(
modifier|*
name|create_guides
function_decl|)
parameter_list|(
name|GimpToolCompass
modifier|*
name|compass
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|horizontal
parameter_list|,
name|gboolean
name|vertical
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_compass_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_compass_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|y3
parameter_list|,
name|gint
name|x3
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_COMPASS_H__ */
end_comment

end_unit


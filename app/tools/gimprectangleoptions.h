begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RECTANGLE_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RECTANGLE_OPTIONS_H__
define|#
directive|define
name|__GIMP_RECTANGLE_OPTIONS_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27f054300103
block|{
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_0
name|GIMP_RECTANGLE_OPTIONS_PROP_0
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_HIGHLIGHT
name|GIMP_RECTANGLE_OPTIONS_PROP_HIGHLIGHT
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_GUIDE
name|GIMP_RECTANGLE_OPTIONS_PROP_GUIDE
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_WIDTH
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_WIDTH
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_WIDTH
name|GIMP_RECTANGLE_OPTIONS_PROP_WIDTH
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_HEIGHT
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_HEIGHT
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_HEIGHT
name|GIMP_RECTANGLE_OPTIONS_PROP_HEIGHT
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_ASPECT
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_ASPECT
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT_NUMERATOR
name|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT_NUMERATOR
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT_DENOMINATOR
name|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT_DENOMINATOR
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT_SQUARE
name|GIMP_RECTANGLE_OPTIONS_PROP_ASPECT_SQUARE
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_CENTER
name|GIMP_RECTANGLE_OPTIONS_PROP_FIXED_CENTER
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_X
name|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_X
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_Y
name|GIMP_RECTANGLE_OPTIONS_PROP_CENTER_Y
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_UNIT
name|GIMP_RECTANGLE_OPTIONS_PROP_UNIT
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_CONTROLS_EXPANDED
name|GIMP_RECTANGLE_OPTIONS_PROP_CONTROLS_EXPANDED
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_DIMENSIONS_ENTRY
name|GIMP_RECTANGLE_OPTIONS_PROP_DIMENSIONS_ENTRY
block|,
DECL|enumerator|GIMP_RECTANGLE_OPTIONS_PROP_LAST
name|GIMP_RECTANGLE_OPTIONS_PROP_LAST
init|=
name|GIMP_RECTANGLE_OPTIONS_PROP_DIMENSIONS_ENTRY
DECL|typedef|GimpRectangleOptionsProp
block|}
name|GimpRectangleOptionsProp
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_OPTIONS
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_OPTIONS
value|(gimp_rectangle_options_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_RECTANGLE_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_RECTANGLE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_RECTANGLE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_OPTIONS (obj)
define|#
directive|define
name|GIMP_RECTANGLE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RECTANGLE_OPTIONS, GimpRectangleOptions))
end_define

begin_define
DECL|macro|GIMP_RECTANGLE_OPTIONS_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_RECTANGLE_OPTIONS_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_RECTANGLE_OPTIONS, GimpRectangleOptionsInterface))
end_define

begin_typedef
DECL|typedef|GimpRectangleOptions
typedef|typedef
name|struct
name|_GimpRectangleOptions
name|GimpRectangleOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRectangleOptionsInterface
typedef|typedef
name|struct
name|_GimpRectangleOptionsInterface
name|GimpRectangleOptionsInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRectangleOptionsInterface
struct|struct
name|_GimpRectangleOptionsInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_rectangle_options_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_rectangle_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  convenience functions  */
end_comment

begin_function_decl
name|void
name|gimp_rectangle_options_install_properties
parameter_list|(
name|GObjectClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_options_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_options_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rectangle_options_set_highlight
parameter_list|(
name|GimpRectangleOptions
modifier|*
name|options
parameter_list|,
name|gboolean
name|highlight
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RECTANGLE_OPTIONS_H__ */
end_comment

end_unit


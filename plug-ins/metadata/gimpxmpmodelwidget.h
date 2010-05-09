begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpxmpmodelwidget.h - interface definition for xmpmodel gtkwidgets  *  * Copyright (C) 2010, RÃ³man Joost<romanofski@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_XMP_MODEL_WIDGET_H__
end_ifndef

begin_define
DECL|macro|__GIMP_XMP_MODEL_WIDGET_H__
define|#
directive|define
name|__GIMP_XMP_MODEL_WIDGET_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
name|enum
DECL|enum|__anon27a28b290103
type|{
DECL|enumerator|GIMP_XMP_MODEL_WIDGET_PROP_0
name|GIMP_XMP_MODEL_WIDGET_PROP_0
decl_stmt|,
DECL|enumerator|GIMP_XMP_MODEL_WIDGET_PROP_SCHEMA_URI
name|GIMP_XMP_MODEL_WIDGET_PROP_SCHEMA_URI
decl_stmt|,
DECL|enumerator|GIMP_XMP_MODEL_WIDGET_PROP_PROPERTY_NAME
name|GIMP_XMP_MODEL_WIDGET_PROP_PROPERTY_NAME
decl_stmt|,
DECL|enumerator|GIMP_XMP_MODEL_WIDGET_PROP_XMPMODEL
name|GIMP_XMP_MODEL_WIDGET_PROP_XMPMODEL
end_decl_stmt

begin_empty_stmt
DECL|variable|GimpXmpModelWidgetProp
unit|} GimpXmpModelWidgetProp
empty_stmt|;
end_empty_stmt

begin_define
DECL|macro|GIMP_TYPE_XMP_MODEL_WIDGET
define|#
directive|define
name|GIMP_TYPE_XMP_MODEL_WIDGET
value|(gimp_xmp_model_widget_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_XMP_MODEL_WIDGET (obj)
define|#
directive|define
name|GIMP_IS_XMP_MODEL_WIDGET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_XMP_MODEL_WIDGET))
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_WIDGET (obj)
define|#
directive|define
name|GIMP_XMP_MODEL_WIDGET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_XMP_MODEL_WIDGET, GimpXmpModelWidget))
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_WIDGET_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_XMP_MODEL_WIDGET_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_XMP_MODEL_WIDGET, GimpXmpModelWidgetInterface))
end_define

begin_typedef
DECL|typedef|GimpXmpModelWidget
typedef|typedef
name|struct
name|_GimpXmpModelWidget
name|GimpXmpModelWidget
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpXmpModelWidgetInterface
typedef|typedef
name|struct
name|_GimpXmpModelWidgetInterface
name|GimpXmpModelWidgetInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpXmpModelWidgetInterface
struct|struct
name|_GimpXmpModelWidgetInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
DECL|member|widget_set_text
name|void
function_decl|(
modifier|*
name|widget_set_text
function_decl|)
parameter_list|(
name|GimpXmpModelWidget
modifier|*
name|widget
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
name|gimp_xmp_model_widget_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_xmp_model_widget_install_properties
parameter_list|(
name|GObjectClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_xmp_model_widget_constructor
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_xmp_model_widget_set_text
parameter_list|(
name|GimpXmpModelWidget
modifier|*
name|widget
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
name|gimp_xmp_model_widget_set_property
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
name|gimp_xmp_model_widget_get_property
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
name|gimp_xmp_model_widget_changed
parameter_list|(
name|GimpXmpModelWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_XMP_MODEL_WIDGET_H__ */
end_comment

end_unit


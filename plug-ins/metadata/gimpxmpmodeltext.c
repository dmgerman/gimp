begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpxmpmodeltext.c - custom text widget linked to the xmp model  *  * Copyright (C) 2010, RÃ³man Joost<romanofski@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"xmp-schemas.h"
end_include

begin_include
include|#
directive|include
file|"xmp-model.h"
end_include

begin_include
include|#
directive|include
file|"gimpxmpmodelwidget.h"
end_include

begin_include
include|#
directive|include
file|"gimpxmpmodeltext.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_xmp_model_text_iface_init
parameter_list|(
name|GimpXmpModelWidgetInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_xmp_model_text_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_xmp_model_text_changed
parameter_list|(
name|GtkTextBuffer
modifier|*
name|text_buffer
parameter_list|,
name|gpointer
modifier|*
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_xmp_model_text_set_text
parameter_list|(
name|GimpXmpModelWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tree_value
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpXmpModelText,gimp_xmp_model_text,GTK_TYPE_TEXT_VIEW,G_IMPLEMENT_INTERFACE (GIMP_TYPE_XMP_MODEL_WIDGET,gimp_xmp_model_text_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpXmpModelText
argument_list|,
argument|gimp_xmp_model_text
argument_list|,
argument|GTK_TYPE_TEXT_VIEW
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_XMP_MODEL_WIDGET,                                                 gimp_xmp_model_text_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_xmp_model_text_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_xmp_model_text_class_init
parameter_list|(
name|GimpXmpModelTextClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_xmp_model_text_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_xmp_model_widget_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_xmp_model_widget_get_property
expr_stmt|;
name|gimp_xmp_model_widget_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_xmp_model_text_iface_init (GimpXmpModelWidgetInterface * iface)
name|gimp_xmp_model_text_iface_init
parameter_list|(
name|GimpXmpModelWidgetInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|widget_set_text
operator|=
name|gimp_xmp_model_text_set_text
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_xmp_model_text_init (GimpXmpModelText * text)
name|gimp_xmp_model_text_init
parameter_list|(
name|GimpXmpModelText
modifier|*
name|text
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|text_buffer
decl_stmt|;
name|text_buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|text_buffer
argument_list|,
literal|"end-user-action"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_xmp_model_text_changed
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_xmp_model_text_constructed (GObject * object)
name|gimp_xmp_model_text_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_xmp_model_widget_constructor
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_xmp_model_text_changed (GtkTextBuffer * text_buffer,gpointer * user_data)
name|gimp_xmp_model_text_changed
parameter_list|(
name|GtkTextBuffer
modifier|*
name|text_buffer
parameter_list|,
name|gpointer
modifier|*
name|user_data
parameter_list|)
block|{
name|GimpXmpModelText
modifier|*
name|text
init|=
name|GIMP_XMP_MODEL_TEXT
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GtkTextIter
name|start
decl_stmt|;
name|GtkTextIter
name|end
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
name|gtk_text_buffer_get_bounds
argument_list|(
name|text_buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|)
expr_stmt|;
name|value
operator|=
name|gtk_text_buffer_get_text
argument_list|(
name|text_buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_xmp_model_widget_changed
argument_list|(
name|GIMP_XMP_MODEL_WIDGET
argument_list|(
name|text
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_xmp_model_text_set_text (GimpXmpModelWidget * widget,const gchar * tree_value)
name|gimp_xmp_model_text_set_text
parameter_list|(
name|GimpXmpModelWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tree_value
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|text_buffer
decl_stmt|;
name|text_buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|text_buffer
argument_list|,
name|tree_value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


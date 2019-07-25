begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * SECTION: gimpplugin  * @title: GimpPlugIn  * @short_description: The base class for plug-ins to derive from  *  * The base class for plug-ins to derive from. Manages the plug-in's  * #GimpProcedure objects.  *  * Since: 3.0  **/
end_comment

begin_struct
DECL|struct|_GimpPlugInPrivate
struct|struct
name|_GimpPlugInPrivate
block|{
DECL|member|foo
name|gint
name|foo
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpPlugIn,gimp_plug_in,G_TYPE_OBJECT)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpPlugIn
argument_list|,
argument|gimp_plug_in
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_plug_in_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_plug_in_class_init
parameter_list|(
name|GimpPlugInClass
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
name|finalize
operator|=
name|gimp_plug_in_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_init (GimpPlugIn * plug_in)
name|gimp_plug_in_init
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|plug_in
operator|->
name|priv
operator|=
name|gimp_plug_in_get_instance_private
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_finalize (GObject * object)
name|gimp_plug_in_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  unrelated old API  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_plugin_icon_register (const gchar * procedure_name,GimpIconType icon_type,const guint8 * icon_data)
name|gimp_plugin_icon_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GimpIconType
name|icon_type
parameter_list|,
specifier|const
name|guint8
modifier|*
name|icon_data
parameter_list|)
block|{
name|gint
name|icon_data_length
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procedure_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_data
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|icon_type
condition|)
block|{
case|case
name|GIMP_ICON_TYPE_ICON_NAME
case|:
case|case
name|GIMP_ICON_TYPE_IMAGE_FILE
case|:
name|icon_data_length
operator|=
name|strlen
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|icon_data
argument_list|)
operator|+
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_ICON_TYPE_INLINE_PIXBUF
case|:
name|g_return_val_if_fail
argument_list|(
name|g_ntohl
argument_list|(
operator|*
operator|(
operator|(
name|gint32
operator|*
operator|)
name|icon_data
operator|)
argument_list|)
operator|==
literal|0x47646b50
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|icon_data_length
operator|=
name|g_ntohl
argument_list|(
operator|*
operator|(
operator|(
name|gint32
operator|*
operator|)
operator|(
name|icon_data
operator|+
literal|4
operator|)
operator|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|_gimp_plugin_icon_register
argument_list|(
name|procedure_name
argument_list|,
name|icon_type
argument_list|,
name|icon_data_length
argument_list|,
name|icon_data
argument_list|)
return|;
block|}
end_function

end_unit


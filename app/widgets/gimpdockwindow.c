begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockwindow.c  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  * Copyright (C)      2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"gimpwindow.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon277130050103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|, }
enum|;
end_enum

begin_struct
DECL|struct|_GimpDockWindowPrivate
struct|struct
name|_GimpDockWindowPrivate
block|{
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_dock_window_dispose
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
name|gimp_dock_window_set_property
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
specifier|static
name|void
name|gimp_dock_window_get_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDockWindow,gimp_dock_window,GIMP_TYPE_WINDOW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDockWindow
argument_list|,
argument|gimp_dock_window
argument_list|,
argument|GIMP_TYPE_WINDOW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dock_window_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dock_window_class_init
parameter_list|(
name|GimpDockWindowClass
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
name|dispose
operator|=
name|gimp_dock_window_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dock_window_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dock_window_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp-context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDockWindowPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_init (GimpDockWindow * dock_window)
name|gimp_dock_window_init
parameter_list|(
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
block|{
name|dock_window
operator|->
name|p
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|dock_window
argument_list|,
name|GIMP_TYPE_DOCK_WINDOW
argument_list|,
name|GimpDockWindowPrivate
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_dispose (GObject * object)
name|gimp_dock_window_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dock_window
operator|->
name|p
operator|->
name|context
condition|)
block|{
name|g_object_unref
argument_list|(
name|dock_window
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
name|dock_window
operator|->
name|p
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dock_window_set_property
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
block|{
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|dock_window
operator|->
name|p
operator|->
name|context
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dock_window_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dock_window_get_property
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
block|{
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|GIMP_DOCK_WINDOW
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|dock_window
operator|->
name|p
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit


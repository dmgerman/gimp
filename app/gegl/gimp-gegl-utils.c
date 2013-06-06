begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-utils.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-utils.h"
end_include

begin_function
name|GType
DECL|function|gimp_gegl_get_op_enum_type (const gchar * operation,const gchar * property)
name|gimp_gegl_get_op_enum_type
parameter_list|(
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GObject
modifier|*
name|op
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|property
operator|!=
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|node
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|node
argument_list|,
literal|"gegl-operation"
argument_list|,
operator|&
name|op
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|node
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|op
operator|!=
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|op
argument_list|)
argument_list|,
name|property
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|op
argument_list|)
expr_stmt|;
return|return
name|G_TYPE_FROM_CLASS
argument_list|(
name|G_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
operator|->
name|enum_class
argument_list|)
return|;
block|}
end_function

begin_function
name|GeglColor
modifier|*
DECL|function|gimp_gegl_color_new (const GimpRGB * rgb)
name|gimp_gegl_color_new
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
name|GeglColor
modifier|*
name|color
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rgb
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|color
operator|=
name|gegl_color_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gegl_color_set_pixel
argument_list|(
name|color
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
return|return
name|color
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_progress_notify (GObject * object,const GParamSpec * pspec,GimpProgress * progress)
name|gimp_gegl_progress_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|g_object_get
argument_list|(
name|object
argument_list|,
literal|"progress"
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"gimp-progress-text"
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
block|{
if|if
condition|(
name|value
operator|==
literal|0.0
condition|)
block|{
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|text
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return;
block|}
elseif|else
if|if
condition|(
name|value
operator|==
literal|1.0
condition|)
block|{
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|gimp_progress_set_value
argument_list|(
name|progress
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_progress_connect (GeglNode * node,GimpProgress * progress,const gchar * text)
name|gimp_gegl_progress_connect
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GObject
modifier|*
name|operation
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|node
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|node
argument_list|,
literal|"gegl-operation"
argument_list|,
operator|&
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"notify::progress"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_progress_notify
argument_list|)
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
condition|)
name|g_object_set_data_full
argument_list|(
name|operation
argument_list|,
literal|"gimp-progress-text"
argument_list|,
name|g_strdup
argument_list|(
name|text
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


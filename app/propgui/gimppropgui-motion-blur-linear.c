begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui-motion-blur-linear.c  * Copyright (C) 2019  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"propgui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui-generic.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui-motion-blur-linear.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|line_callback (GObject * config,GeglRectangle * area,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|line_callback
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
block|{
name|gdouble
name|length
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"area"
argument_list|,
name|g_memdup
argument_list|(
name|area
argument_list|,
sizeof|sizeof
argument_list|(
name|GeglRectangle
argument_list|)
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|length
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|x2
operator|-
name|x1
argument_list|)
operator|+
name|SQR
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
name|angle
operator|=
name|atan2
argument_list|(
name|y2
operator|-
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
name|angle
operator|=
name|angle
operator|/
name|G_PI
operator|*
literal|180.0
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"length"
argument_list|,
name|length
argument_list|,
literal|"angle"
argument_list|,
name|angle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|config_notify (GObject * config,const GParamSpec * pspec,gpointer set_data)
name|config_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|set_data
parameter_list|)
block|{
name|GimpControllerLineCallback
name|set_func
decl_stmt|;
name|GeglRectangle
modifier|*
name|area
decl_stmt|;
name|gdouble
name|length
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|set_func
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"set-func"
argument_list|)
expr_stmt|;
name|area
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"area"
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
literal|"length"
argument_list|,
operator|&
name|length
argument_list|,
literal|"angle"
argument_list|,
operator|&
name|angle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|angle
operator|=
name|angle
operator|/
literal|180.0
operator|*
name|G_PI
expr_stmt|;
name|x1
operator|=
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|width
operator|/
literal|2.0
expr_stmt|;
name|y1
operator|=
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|height
operator|/
literal|2.0
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|length
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|length
expr_stmt|;
name|set_func
argument_list|(
name|set_data
argument_list|,
name|area
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|_gimp_prop_gui_new_motion_blur_linear (GObject * config,GParamSpec ** param_specs,guint n_param_specs,GeglRectangle * area,GimpContext * context,GimpCreatePickerFunc create_picker_func,GimpCreateControllerFunc create_controller_func,gpointer creator)
name|_gimp_prop_gui_new_motion_blur_linear
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|param_specs
parameter_list|,
name|guint
name|n_param_specs
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpCreatePickerFunc
name|create_picker_func
parameter_list|,
name|GimpCreateControllerFunc
name|create_controller_func
parameter_list|,
name|gpointer
name|creator
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|param_specs
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_param_specs
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
argument_list|,
name|n_param_specs
argument_list|,
name|area
argument_list|,
name|context
argument_list|,
name|create_picker_func
argument_list|,
name|create_controller_func
argument_list|,
name|creator
argument_list|)
expr_stmt|;
if|if
condition|(
name|create_controller_func
condition|)
block|{
name|GCallback
name|set_func
decl_stmt|;
name|gpointer
name|set_data
decl_stmt|;
name|set_func
operator|=
name|create_controller_func
argument_list|(
name|creator
argument_list|,
name|GIMP_CONTROLLER_TYPE_LINE
argument_list|,
name|_
argument_list|(
literal|"Linear Motion Blur: "
argument_list|)
argument_list|,
operator|(
name|GCallback
operator|)
name|line_callback
argument_list|,
name|config
argument_list|,
operator|&
name|set_data
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"set-func"
argument_list|,
name|set_func
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"area"
argument_list|,
name|g_memdup
argument_list|(
name|area
argument_list|,
sizeof|sizeof
argument_list|(
name|GeglRectangle
argument_list|)
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|config_notify
argument_list|(
name|config
argument_list|,
name|NULL
argument_list|,
name|set_data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|config_notify
argument_list|)
argument_list|,
name|set_data
argument_list|)
expr_stmt|;
block|}
return|return
name|vbox
return|;
block|}
end_function

end_unit


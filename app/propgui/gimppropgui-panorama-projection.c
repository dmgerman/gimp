begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui-panorama-projection.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimppropgui.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui-generic.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui-panorama-projection.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gyroscope_callback (GObject * config,GeglRectangle * area,gdouble yaw,gdouble pitch,gdouble roll,gdouble zoom,gboolean invert)
name|gyroscope_callback
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
name|yaw
parameter_list|,
name|gdouble
name|pitch
parameter_list|,
name|gdouble
name|roll
parameter_list|,
name|gdouble
name|zoom
parameter_list|,
name|gboolean
name|invert
parameter_list|)
block|{
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
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"pan"
argument_list|,
operator|-
name|yaw
argument_list|,
literal|"tilt"
argument_list|,
operator|-
name|pitch
argument_list|,
literal|"spin"
argument_list|,
operator|-
name|roll
argument_list|,
literal|"zoom"
argument_list|,
name|CLAMP
argument_list|(
literal|100.0
operator|*
name|zoom
argument_list|,
literal|0.01
argument_list|,
literal|1000.0
argument_list|)
argument_list|,
literal|"inverse"
argument_list|,
name|invert
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
name|GimpControllerGyroscopeCallback
name|set_func
decl_stmt|;
name|GeglRectangle
modifier|*
name|area
decl_stmt|;
name|gdouble
name|pan
decl_stmt|;
name|gdouble
name|tilt
decl_stmt|;
name|gdouble
name|spin
decl_stmt|;
name|gdouble
name|zoom
decl_stmt|;
name|gboolean
name|inverse
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
literal|"pan"
argument_list|,
operator|&
name|pan
argument_list|,
literal|"tilt"
argument_list|,
operator|&
name|tilt
argument_list|,
literal|"spin"
argument_list|,
operator|&
name|spin
argument_list|,
literal|"zoom"
argument_list|,
operator|&
name|zoom
argument_list|,
literal|"inverse"
argument_list|,
operator|&
name|inverse
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|set_func
argument_list|(
name|set_data
argument_list|,
name|area
argument_list|,
operator|-
name|pan
argument_list|,
operator|-
name|tilt
argument_list|,
operator|-
name|spin
argument_list|,
name|zoom
operator|/
literal|100.0
argument_list|,
name|inverse
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|_gimp_prop_gui_new_panorama_projection (GObject * config,GParamSpec ** param_specs,guint n_param_specs,GeglRectangle * area,GimpContext * context,GimpCreatePickerFunc create_picker_func,GimpCreateControllerFunc create_controller_func,gpointer creator)
name|_gimp_prop_gui_new_panorama_projection
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
name|GIMP_CONTROLLER_TYPE_GYROSCOPE
argument_list|,
name|_
argument_list|(
literal|"Panorama Projection: "
argument_list|)
argument_list|,
operator|(
name|GCallback
operator|)
name|gyroscope_callback
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


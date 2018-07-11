begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui-color-to-alpha.c  * Copyright (C) 2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimppropgui-color-to-alpha.h"
end_include

begin_include
include|#
directive|include
file|"gimppropgui-generic.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|threshold_picked (GObject * config,gpointer identifier,gdouble x,gdouble y,const Babl * sample_format,const GimpRGB * picked_color)
name|threshold_picked
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|gpointer
name|identifier
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|picked_color
parameter_list|)
block|{
name|GimpRGB
modifier|*
name|color
decl_stmt|;
name|gdouble
name|threshold
init|=
literal|0.0
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
literal|"color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|threshold
operator|=
name|MAX
argument_list|(
name|threshold
argument_list|,
name|fabs
argument_list|(
name|picked_color
operator|->
name|r
operator|-
name|color
operator|->
name|r
argument_list|)
argument_list|)
expr_stmt|;
name|threshold
operator|=
name|MAX
argument_list|(
name|threshold
argument_list|,
name|fabs
argument_list|(
name|picked_color
operator|->
name|g
operator|-
name|color
operator|->
name|g
argument_list|)
argument_list|)
expr_stmt|;
name|threshold
operator|=
name|MAX
argument_list|(
name|threshold
argument_list|,
name|fabs
argument_list|(
name|picked_color
operator|->
name|b
operator|-
name|color
operator|->
name|b
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
name|identifier
argument_list|,
name|threshold
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|_gimp_prop_gui_new_color_to_alpha (GObject * config,GParamSpec ** param_specs,guint n_param_specs,GeglRectangle * area,GimpContext * context,GimpCreatePickerFunc create_picker_func,GimpCreateControllerFunc create_controller_func,gpointer creator)
name|_gimp_prop_gui_new_color_to_alpha
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
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label
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
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|button
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
argument_list|,
literal|1
argument_list|,
name|area
argument_list|,
name|context
argument_list|,
name|create_picker_func
argument_list|,
name|NULL
argument_list|,
name|creator
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_prop_widget_new
argument_list|(
name|config
argument_list|,
literal|"transparency-threshold"
argument_list|,
name|area
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|label
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|scale
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|create_picker_func
condition|)
block|{
name|button
operator|=
name|create_picker_func
argument_list|(
name|creator
argument_list|,
literal|"transparency-threshold"
argument_list|,
name|GIMP_ICON_COLOR_PICKER_GRAY
argument_list|,
name|_
argument_list|(
literal|"Pick farthest full-transparency color"
argument_list|)
argument_list|,
comment|/* pick_abyss = */
name|FALSE
argument_list|,
operator|(
name|GimpPickerCallback
operator|)
name|threshold_picked
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_prop_widget_new
argument_list|(
name|config
argument_list|,
literal|"opacity-threshold"
argument_list|,
name|area
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|label
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|scale
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|create_picker_func
condition|)
block|{
name|button
operator|=
name|create_picker_func
argument_list|(
name|creator
argument_list|,
literal|"opacity-threshold"
argument_list|,
name|GIMP_ICON_COLOR_PICKER_GRAY
argument_list|,
name|_
argument_list|(
literal|"Pick nearest full-opacity color"
argument_list|)
argument_list|,
comment|/* pick_abyss = */
name|FALSE
argument_list|,
operator|(
name|GimpPickerCallback
operator|)
name|threshold_picked
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
return|return
name|vbox
return|;
block|}
end_function

end_unit


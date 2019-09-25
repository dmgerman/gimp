begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui-diffraction-patterns.c  * Copyright (C) 2002-2014  Michael Natterer<mitch@gimp.org>  *                          Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimppropgui-diffraction-patterns.h"
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
name|GtkWidget
modifier|*
DECL|function|_gimp_prop_gui_new_diffraction_patterns (GObject * config,GParamSpec ** param_specs,guint n_param_specs,GeglRectangle * area,GimpContext * context,GimpCreatePickerFunc create_picker_func,GimpCreateControllerFunc create_controller_func,gpointer creator)
name|_gimp_prop_gui_new_diffraction_patterns
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
name|notebook
decl_stmt|;
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
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|vbox
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|0
argument_list|,
literal|3
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Frequencies"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|3
argument_list|,
literal|3
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Contours"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|6
argument_list|,
literal|3
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Sharp Edges"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|9
argument_list|,
literal|3
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Other Options"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|notebook
return|;
block|}
end_function

end_unit


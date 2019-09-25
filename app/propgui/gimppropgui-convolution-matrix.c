begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui-convolution-matrix.c  * Copyright (C) 2002-2014  Michael Natterer<mitch@gimp.org>  *                          Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimppropgui-convolution-matrix.h"
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
specifier|const
name|gchar
modifier|*
DECL|function|convolution_matrix_prop_name (gint x,gint y)
name|convolution_matrix_prop_name
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|prop_names
index|[
literal|5
index|]
index|[
literal|5
index|]
init|=
block|{
block|{
literal|"a1"
block|,
literal|"a2"
block|,
literal|"a3"
block|,
literal|"a4"
block|,
literal|"a5"
block|}
block|,
block|{
literal|"b1"
block|,
literal|"b2"
block|,
literal|"b3"
block|,
literal|"b4"
block|,
literal|"b5"
block|}
block|,
block|{
literal|"c1"
block|,
literal|"c2"
block|,
literal|"c3"
block|,
literal|"c4"
block|,
literal|"c5"
block|}
block|,
block|{
literal|"d1"
block|,
literal|"d2"
block|,
literal|"d3"
block|,
literal|"d4"
block|,
literal|"d5"
block|}
block|,
block|{
literal|"e1"
block|,
literal|"e2"
block|,
literal|"e3"
block|,
literal|"e4"
block|,
literal|"e5"
block|}
block|}
decl_stmt|;
return|return
name|prop_names
index|[
name|x
index|]
index|[
name|y
index|]
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convolution_matrix_rotate_flip (GtkWidget * button,GObject * config)
name|convolution_matrix_rotate_flip
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
block|{
name|gint
name|rotate
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"convolution-matrix-rotate"
argument_list|)
argument_list|)
decl_stmt|;
name|gint
name|flip
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"convolution-matrix-flip"
argument_list|)
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
while|while
condition|(
name|rotate
operator|--
condition|)
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|2
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
name|y
init|;
name|x
operator|<
literal|4
operator|-
name|y
condition|;
name|x
operator|++
control|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|temp
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
argument_list|,
operator|&
name|temp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|next_x
decl_stmt|,
name|next_y
decl_stmt|;
name|gdouble
name|val
decl_stmt|;
name|next_x
operator|=
literal|4
operator|-
name|y
expr_stmt|;
name|next_y
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|3
condition|)
block|{
name|g_object_get
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
name|next_x
argument_list|,
name|next_y
argument_list|)
argument_list|,
operator|&
name|val
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|val
operator|=
name|temp
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
argument_list|,
name|val
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|x
operator|=
name|next_x
expr_stmt|;
name|y
operator|=
name|next_y
expr_stmt|;
block|}
block|}
block|}
block|}
while|while
condition|(
name|flip
operator|--
condition|)
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|5
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|2
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|val1
decl_stmt|,
name|val2
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
argument_list|,
operator|&
name|val1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
literal|4
operator|-
name|x
argument_list|,
name|y
argument_list|)
argument_list|,
operator|&
name|val2
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
argument_list|,
name|val2
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
literal|4
operator|-
name|x
argument_list|,
name|y
argument_list|)
argument_list|,
name|val1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|_gimp_prop_gui_new_convolution_matrix (GObject * config,GParamSpec ** param_specs,guint n_param_specs,GeglRectangle * area,GimpContext * context,GimpCreatePickerFunc create_picker_func,GimpCreateControllerFunc create_controller_func,gpointer creator)
name|_gimp_prop_gui_new_convolution_matrix
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
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox2
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
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
name|main_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
comment|/* matrix */
name|grid
operator|=
name|gtk_grid_new
argument_list|()
expr_stmt|;
name|gtk_grid_set_row_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
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
name|grid
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
name|grid
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|5
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|5
condition|;
name|x
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|spin
decl_stmt|;
name|spin
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
name|convolution_matrix_prop_name
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spin
argument_list|)
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|spin
argument_list|,
name|y
argument_list|,
name|x
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* rotate / flip buttons */
block|{
typedef|typedef
struct|struct
DECL|struct|__anon2ac311c20108
block|{
DECL|member|tooltip
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|icon_name
specifier|const
name|gchar
modifier|*
name|icon_name
decl_stmt|;
DECL|member|rotate
name|gint
name|rotate
decl_stmt|;
DECL|member|flip
name|gint
name|flip
decl_stmt|;
DECL|typedef|ButtonInfo
block|}
name|ButtonInfo
typedef|;
name|gint
name|i
decl_stmt|;
specifier|const
name|ButtonInfo
name|buttons
index|[]
init|=
block|{
block|{
operator|.
name|tooltip
operator|=
name|_
argument_list|(
literal|"Rotate matrix 90Â° counter-clockwise"
argument_list|)
block|,
operator|.
name|icon_name
operator|=
name|GIMP_ICON_OBJECT_ROTATE_270
block|,
operator|.
name|rotate
operator|=
literal|1
block|,
operator|.
name|flip
operator|=
literal|0
block|}
block|,
block|{
operator|.
name|tooltip
operator|=
name|_
argument_list|(
literal|"Rotate matrix 90Â° clockwise"
argument_list|)
block|,
operator|.
name|icon_name
operator|=
name|GIMP_ICON_OBJECT_ROTATE_90
block|,
operator|.
name|rotate
operator|=
literal|3
block|,
operator|.
name|flip
operator|=
literal|0
block|}
block|,
block|{
operator|.
name|tooltip
operator|=
name|_
argument_list|(
literal|"Flip matrix horizontally"
argument_list|)
block|,
operator|.
name|icon_name
operator|=
name|GIMP_ICON_OBJECT_FLIP_HORIZONTAL
block|,
operator|.
name|rotate
operator|=
literal|0
block|,
operator|.
name|flip
operator|=
literal|1
block|}
block|,
block|{
operator|.
name|tooltip
operator|=
name|_
argument_list|(
literal|"Flip matrix vertically"
argument_list|)
block|,
operator|.
name|icon_name
operator|=
name|GIMP_ICON_OBJECT_FLIP_VERTICAL
block|,
operator|.
name|rotate
operator|=
literal|2
block|,
operator|.
name|flip
operator|=
literal|1
block|}
block|}
decl_stmt|;
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|buttons
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|ButtonInfo
modifier|*
name|info
init|=
operator|&
name|buttons
index|[
name|i
index|]
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_tooltip_text
argument_list|(
name|button
argument_list|,
name|info
operator|->
name|tooltip
argument_list|)
expr_stmt|;
name|gtk_widget_set_can_focus
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_button_set_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|GTK_RELIEF_NONE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|info
operator|->
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"convolution-matrix-rotate"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|info
operator|->
name|rotate
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"convolution-matrix-flip"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|info
operator|->
name|flip
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|convolution_matrix_rotate_flip
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
block|}
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
comment|/* divisor / offset spin scales */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|TRUE
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
literal|"divisor"
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
name|scale
operator|=
name|gimp_prop_widget_new
argument_list|(
name|config
argument_list|,
literal|"offset"
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
comment|/* rest of the properties */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|TRUE
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
name|vbox2
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|27
argument_list|,
literal|4
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox2
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|vbox2
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|31
argument_list|,
name|n_param_specs
operator|-
literal|31
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox2
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|main_vbox
return|;
block|}
end_function

end_unit


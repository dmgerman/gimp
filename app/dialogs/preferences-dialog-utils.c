begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"preferences-dialog-utils.h"
end_include

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_frame_new (const gchar * label,GtkContainer * parent,gboolean expand)
name|prefs_frame_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkContainer
modifier|*
name|parent
parameter_list|,
name|gboolean
name|expand
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_BOX
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|frame
argument_list|,
name|expand
argument_list|,
name|expand
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|gtk_container_add
argument_list|(
name|parent
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_grid_new (GtkContainer * parent)
name|prefs_grid_new
parameter_list|(
name|GtkContainer
modifier|*
name|parent
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
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
literal|6
argument_list|)
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_BOX
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
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
else|else
name|gtk_container_add
argument_list|(
name|parent
argument_list|,
name|grid
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|grid
argument_list|)
expr_stmt|;
return|return
name|grid
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_hint_box_new (const gchar * icon_name,const gchar * text)
name|prefs_hint_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_button_add (const gchar * icon_name,const gchar * label,GtkBox * box)
name|prefs_button_add
parameter_list|(
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkBox
modifier|*
name|box
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|gimp_icon_button_new
argument_list|(
name|icon_name
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
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
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_check_button_add (GObject * config,const gchar * property_name,const gchar * label,GtkBox * vbox)
name|prefs_check_button_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkBox
modifier|*
name|vbox
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|vbox
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
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_check_button_add_with_icon (GObject * config,const gchar * property_name,const gchar * label,const gchar * icon_name,GtkBox * vbox,GtkSizeGroup * group)
name|prefs_check_button_add_with_icon
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|GtkBox
modifier|*
name|vbox
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
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
name|image
decl_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|button
condition|)
return|return
name|NULL
return|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|vbox
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
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"margin-start"
argument_list|,
literal|2
argument_list|,
literal|"margin-end"
argument_list|,
literal|2
argument_list|,
literal|"margin-top"
argument_list|,
literal|2
argument_list|,
literal|"margin-bottom"
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
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
name|image
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|group
condition|)
name|gtk_size_group_add_widget
argument_list|(
name|group
argument_list|,
name|image
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_widget_add_aligned (GtkWidget * widget,const gchar * text,GtkGrid * grid,gint grid_top,gboolean left_align,GtkSizeGroup * group)
name|prefs_widget_add_aligned
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|gboolean
name|left_align
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
init|=
name|gimp_grid_attach_aligned
argument_list|(
name|grid
argument_list|,
literal|0
argument_list|,
name|grid_top
argument_list|,
name|text
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|widget
argument_list|,
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
name|group
condition|)
name|gtk_size_group_add_widget
argument_list|(
name|group
argument_list|,
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|left_align
operator|==
name|TRUE
condition|)
name|gtk_widget_set_halign
argument_list|(
name|widget
argument_list|,
name|GTK_ALIGN_START
argument_list|)
expr_stmt|;
return|return
name|label
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_color_button_add (GObject * config,const gchar * property_name,const gchar * label,const gchar * title,GtkGrid * grid,gint grid_top,GtkSizeGroup * group,GimpContext * context)
name|prefs_color_button_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
name|property_name
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_param_spec_rgb_has_alpha
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|title
argument_list|,
name|PREFS_COLOR_BUTTON_WIDTH
argument_list|,
name|PREFS_COLOR_BUTTON_HEIGHT
argument_list|,
name|has_alpha
condition|?
name|GIMP_COLOR_AREA_SMALL_CHECKS
else|:
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
condition|)
block|{
if|if
condition|(
name|context
condition|)
name|gimp_color_panel_set_context
argument_list|(
name|GIMP_COLOR_PANEL
argument_list|(
name|button
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|prefs_widget_add_aligned
argument_list|(
name|button
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|TRUE
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_entry_add (GObject * config,const gchar * property_name,const gchar * label,GtkGrid * grid,gint grid_top,GtkSizeGroup * group)
name|prefs_entry_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
init|=
name|gimp_prop_entry_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
operator|-
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
name|entry
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|entry
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|FALSE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|entry
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_spin_button_add (GObject * config,const gchar * property_name,gdouble step_increment,gdouble page_increment,gint digits,const gchar * label,GtkGrid * grid,gint grid_top,GtkSizeGroup * group)
name|prefs_spin_button_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gdouble
name|step_increment
parameter_list|,
name|gdouble
name|page_increment
parameter_list|,
name|gint
name|digits
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|step_increment
argument_list|,
name|page_increment
argument_list|,
name|digits
argument_list|)
decl_stmt|;
if|if
condition|(
name|button
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|button
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|TRUE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_memsize_entry_add (GObject * config,const gchar * property_name,const gchar * label,GtkGrid * grid,gint grid_top,GtkSizeGroup * group)
name|prefs_memsize_entry_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
init|=
name|gimp_prop_memsize_entry_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|entry
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|entry
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|TRUE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|entry
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_file_chooser_button_add (GObject * config,const gchar * property_name,const gchar * label,const gchar * dialog_title,GtkGrid * grid,gint grid_top,GtkSizeGroup * group)
name|prefs_file_chooser_button_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_title
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|gimp_prop_file_chooser_button_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|dialog_title
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|button
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|FALSE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_enum_combo_box_add (GObject * config,const gchar * property_name,gint minimum,gint maximum,const gchar * label,GtkGrid * grid,gint grid_top,GtkSizeGroup * group)
name|prefs_enum_combo_box_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo
init|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|minimum
argument_list|,
name|maximum
argument_list|)
decl_stmt|;
if|if
condition|(
name|combo
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|combo
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|FALSE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|combo
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_boolean_combo_box_add (GObject * config,const gchar * property_name,const gchar * true_text,const gchar * false_text,const gchar * label,GtkGrid * grid,gint grid_top,GtkSizeGroup * group)
name|prefs_boolean_combo_box_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|true_text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|false_text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo
init|=
name|gimp_prop_boolean_combo_box_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|true_text
argument_list|,
name|false_text
argument_list|)
decl_stmt|;
if|if
condition|(
name|combo
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|combo
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|FALSE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|combo
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_ISO_CODES
end_ifdef

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_language_combo_box_add (GObject * config,const gchar * property_name,GtkBox * vbox)
name|prefs_language_combo_box_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GtkBox
modifier|*
name|vbox
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo
init|=
name|gimp_prop_language_combo_box_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|combo
condition|)
block|{
name|gtk_box_pack_start
argument_list|(
name|vbox
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
block|}
return|return
name|combo
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_profile_combo_box_add (GObject * config,const gchar * property_name,GtkListStore * profile_store,const gchar * dialog_title,const gchar * label,GtkGrid * grid,gint grid_top,GtkSizeGroup * group,GObject * profile_path_config,const gchar * profile_path_property_name)
name|prefs_profile_combo_box_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GtkListStore
modifier|*
name|profile_store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|,
name|GObject
modifier|*
name|profile_path_config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|profile_path_property_name
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo
init|=
name|gimp_prop_profile_combo_box_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|profile_store
argument_list|,
name|dialog_title
argument_list|,
name|profile_path_config
argument_list|,
name|profile_path_property_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|combo
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|combo
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|FALSE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|combo
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|prefs_compression_combo_box_add (GObject * config,const gchar * property_name,const gchar * label,GtkGrid * grid,gint grid_top,GtkSizeGroup * group)
name|prefs_compression_combo_box_add
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkGrid
modifier|*
name|grid
parameter_list|,
name|gint
name|grid_top
parameter_list|,
name|GtkSizeGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo
init|=
name|gimp_prop_compression_combo_box_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|combo
condition|)
name|prefs_widget_add_aligned
argument_list|(
name|combo
argument_list|,
name|label
argument_list|,
name|grid
argument_list|,
name|grid_top
argument_list|,
name|FALSE
argument_list|,
name|group
argument_list|)
expr_stmt|;
return|return
name|combo
return|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui-newsprint.c  * Copyright (C) 2019  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimppropgui-newsprint.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a1a29330103
block|{
DECL|enumerator|COLOR_MODEL_WHITE_ON_BLACK
name|COLOR_MODEL_WHITE_ON_BLACK
block|,
DECL|enumerator|COLOR_MODEL_BLACK_ON_WHITE
name|COLOR_MODEL_BLACK_ON_WHITE
block|,
DECL|enumerator|COLOR_MODEL_RGB
name|COLOR_MODEL_RGB
block|,
DECL|enumerator|COLOR_MODEL_CMYK
name|COLOR_MODEL_CMYK
block|,
DECL|enumerator|N_COLOR_MODELS
name|N_COLOR_MODELS
DECL|typedef|ColorModel
block|}
name|ColorModel
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a1a29330203
block|{
DECL|enumerator|PATTERN_LINE
name|PATTERN_LINE
block|,
DECL|enumerator|PATTERN_CIRCLE
name|PATTERN_CIRCLE
block|,
DECL|enumerator|PATTERN_DIAMOND
name|PATTERN_DIAMOND
block|,
DECL|enumerator|PATTERN_PSCIRCLE
name|PATTERN_PSCIRCLE
block|,
DECL|enumerator|PATTERN_CROSS
name|PATTERN_CROSS
block|,
DECL|enumerator|N_PATTERNS
name|N_PATTERNS
DECL|typedef|Pattern
block|}
name|Pattern
typedef|;
end_typedef

begin_typedef
DECL|typedef|Newsprint
typedef|typedef
name|struct
name|_Newsprint
name|Newsprint
typedef|;
end_typedef

begin_struct
DECL|struct|_Newsprint
struct|struct
name|_Newsprint
block|{
DECL|member|config
name|GObject
modifier|*
name|config
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
DECL|member|pattern_check
name|GtkWidget
modifier|*
name|pattern_check
decl_stmt|;
DECL|member|period_check
name|GtkWidget
modifier|*
name|period_check
decl_stmt|;
DECL|member|angle_check
name|GtkWidget
modifier|*
name|angle_check
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|newsprint_color_model_notify
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
name|GtkWidget
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|newsprint_model_prop_notify
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
name|Newsprint
modifier|*
name|np
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|newsprint_lock_patterns_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|Newsprint
modifier|*
name|np
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|newsprint_lock_periods_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|Newsprint
modifier|*
name|np
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|newsprint_lock_angles_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|Newsprint
modifier|*
name|np
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|label_strings
specifier|static
specifier|const
name|gchar
modifier|*
name|label_strings
index|[
name|N_COLOR_MODELS
index|]
index|[
literal|4
index|]
init|=
block|{
block|{
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"White"
argument_list|)
block|}
block|,
block|{
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Black"
argument_list|)
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Red"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Green"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Blue"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Cyan"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Magenta"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Yellow"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Black"
argument_list|)
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pattern_props
specifier|static
specifier|const
name|gchar
modifier|*
name|pattern_props
index|[]
init|=
block|{
literal|"pattern2"
block|,
literal|"pattern3"
block|,
literal|"pattern4"
block|,
literal|"pattern"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|period_props
specifier|static
specifier|const
name|gchar
modifier|*
name|period_props
index|[]
init|=
block|{
literal|"period2"
block|,
literal|"period3"
block|,
literal|"period4"
block|,
literal|"period"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|angle_props
specifier|static
specifier|const
name|gchar
modifier|*
name|angle_props
index|[]
init|=
block|{
literal|"angle2"
block|,
literal|"angle3"
block|,
literal|"angle4"
block|,
literal|"angle"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|_gimp_prop_gui_new_newsprint (GObject * config,GParamSpec ** param_specs,guint n_param_specs,GeglRectangle * area,GimpContext * context,GimpCreatePickerFunc create_picker_func,GimpCreateControllerFunc create_controller_func,gpointer creator)
name|_gimp_prop_gui_new_newsprint
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
name|Newsprint
modifier|*
name|np
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|labels
index|[
literal|4
index|]
decl_stmt|;
name|GtkWidget
modifier|*
name|pages
index|[
literal|4
index|]
decl_stmt|;
name|GtkWidget
modifier|*
name|check
decl_stmt|;
name|gint
name|i
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
name|np
operator|=
name|g_new0
argument_list|(
name|Newsprint
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|np
operator|->
name|config
operator|=
name|config
expr_stmt|;
name|main_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|"newsprint"
argument_list|,
name|np
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Channels"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
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
name|combo
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|0
argument_list|,
literal|1
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
name|vbox
argument_list|)
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
name|np
operator|->
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|np
operator|->
name|notebook
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
name|np
operator|->
name|notebook
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
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|unused
decl_stmt|;
name|gint
name|remaining
decl_stmt|;
name|labels
index|[
name|i
index|]
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|pages
index|[
name|i
index|]
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|"channel"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|config
argument_list|,
literal|"notify::color-model"
argument_list|,
name|G_CALLBACK
argument_list|(
name|newsprint_color_model_notify
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|labels
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|newsprint_color_model_notify
argument_list|(
name|config
argument_list|,
name|NULL
argument_list|,
name|labels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|pages
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|np
operator|->
name|notebook
argument_list|)
argument_list|,
name|pages
index|[
name|i
index|]
argument_list|,
name|labels
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gimp_prop_widget_new_from_pspec
argument_list|(
name|config
argument_list|,
name|param_specs
index|[
literal|1
operator|+
literal|3
operator|*
name|i
index|]
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
argument_list|,
operator|&
name|unused
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|pages
index|[
name|i
index|]
argument_list|)
argument_list|,
name|widget
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
name|widget
argument_list|)
expr_stmt|;
name|g_object_bind_property
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"visible"
argument_list|,
name|G_OBJECT
argument_list|(
name|pages
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|"visible"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|==
literal|3
condition|)
name|remaining
operator|=
literal|3
expr_stmt|;
else|else
name|remaining
operator|=
literal|2
expr_stmt|;
name|widget
operator|=
name|_gimp_prop_gui_new_generic
argument_list|(
name|config
argument_list|,
name|param_specs
operator|+
literal|2
operator|+
literal|3
operator|*
name|i
argument_list|,
name|remaining
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
name|pages
index|[
name|i
index|]
argument_list|)
argument_list|,
name|widget
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
name|widget
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
name|np
operator|->
name|pattern_check
operator|=
name|check
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Lock patterns"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|check
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
name|check
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|check
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|newsprint_lock_patterns_toggled
argument_list|)
argument_list|,
name|np
argument_list|)
expr_stmt|;
name|np
operator|->
name|period_check
operator|=
name|check
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Loc_k periods"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|check
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
name|check
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|check
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|newsprint_lock_periods_toggled
argument_list|)
argument_list|,
name|np
argument_list|)
expr_stmt|;
name|np
operator|->
name|angle_check
operator|=
name|check
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Lock a_ngles"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|check
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
name|check
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|check
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|newsprint_lock_angles_toggled
argument_list|)
argument_list|,
name|np
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Quality"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
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
literal|14
argument_list|,
literal|1
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
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Effects"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
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
literal|15
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
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|newsprint_model_prop_notify
argument_list|)
argument_list|,
name|np
argument_list|)
expr_stmt|;
return|return
name|main_vbox
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|newsprint_color_model_notify (GObject * config,const GParamSpec * pspec,GtkWidget * label)
name|newsprint_color_model_notify
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
name|GtkWidget
modifier|*
name|label
parameter_list|)
block|{
name|ColorModel
name|model
decl_stmt|;
name|gint
name|channel
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
literal|"color-model"
argument_list|,
operator|&
name|model
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|channel
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|label
argument_list|)
argument_list|,
literal|"channel"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|label_strings
index|[
name|model
index|]
index|[
name|channel
index|]
condition|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|label_strings
index|[
name|model
index|]
index|[
name|channel
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|newsprint_sync_model_props (Newsprint * np,const GParamSpec * pspec,const gchar ** props,gint n_props)
name|newsprint_sync_model_props
parameter_list|(
name|Newsprint
modifier|*
name|np
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|props
parameter_list|,
name|gint
name|n_props
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_props
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
name|props
index|[
name|i
index|]
argument_list|)
condition|)
block|{
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|np
operator|->
name|config
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|n_props
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|!=
name|j
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|np
operator|->
name|config
argument_list|,
name|newsprint_model_prop_notify
argument_list|,
name|np
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|np
operator|->
name|config
argument_list|,
name|props
index|[
name|j
index|]
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|np
operator|->
name|config
argument_list|,
name|newsprint_model_prop_notify
argument_list|,
name|np
argument_list|)
expr_stmt|;
block|}
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|newsprint_model_prop_notify (GObject * config,const GParamSpec * pspec,Newsprint * np)
name|newsprint_model_prop_notify
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
name|Newsprint
modifier|*
name|np
parameter_list|)
block|{
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|np
operator|->
name|pattern_check
argument_list|)
argument_list|)
operator|&&
name|newsprint_sync_model_props
argument_list|(
name|np
argument_list|,
name|pspec
argument_list|,
name|pattern_props
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|pattern_props
argument_list|)
argument_list|)
condition|)
return|return;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|np
operator|->
name|period_check
argument_list|)
argument_list|)
operator|&&
name|newsprint_sync_model_props
argument_list|(
name|np
argument_list|,
name|pspec
argument_list|,
name|period_props
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|period_props
argument_list|)
argument_list|)
condition|)
return|return;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|np
operator|->
name|angle_check
argument_list|)
argument_list|)
operator|&&
name|newsprint_sync_model_props
argument_list|(
name|np
argument_list|,
name|pspec
argument_list|,
name|angle_props
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|angle_props
argument_list|)
argument_list|)
condition|)
return|return;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|newsprint_lock_patterns_toggled (GtkWidget * widget,Newsprint * np)
name|newsprint_lock_patterns_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|Newsprint
modifier|*
name|np
parameter_list|)
block|{
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
block|{
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|gint
name|channel
decl_stmt|;
name|channel
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|np
operator|->
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|np
operator|->
name|config
argument_list|)
argument_list|,
name|pattern_props
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
name|newsprint_sync_model_props
argument_list|(
name|np
argument_list|,
name|pspec
argument_list|,
name|pattern_props
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|pattern_props
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|newsprint_lock_periods_toggled (GtkWidget * widget,Newsprint * np)
name|newsprint_lock_periods_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|Newsprint
modifier|*
name|np
parameter_list|)
block|{
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
block|{
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|gint
name|channel
decl_stmt|;
name|channel
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|np
operator|->
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|np
operator|->
name|config
argument_list|)
argument_list|,
name|period_props
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
name|newsprint_sync_model_props
argument_list|(
name|np
argument_list|,
name|pspec
argument_list|,
name|period_props
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|period_props
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|newsprint_lock_angles_toggled (GtkWidget * widget,Newsprint * np)
name|newsprint_lock_angles_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|Newsprint
modifier|*
name|np
parameter_list|)
block|{
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
block|{
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|gint
name|channel
decl_stmt|;
name|channel
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|np
operator|->
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|np
operator|->
name|config
argument_list|)
argument_list|,
name|angle_props
index|[
name|channel
index|]
argument_list|)
expr_stmt|;
name|newsprint_sync_model_props
argument_list|(
name|np
argument_list|,
name|pspec
argument_list|,
name|angle_props
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|angle_props
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


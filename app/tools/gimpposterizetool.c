begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"base/gimplut.h"
end_include

begin_include
include|#
directive|include
file|"base/lut-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpposterizetool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
DECL|typedef|PosterizeDialog
typedef|typedef
name|struct
name|_PosterizeDialog
name|PosterizeDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_PosterizeDialog
struct|struct
name|_PosterizeDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|levels_data
name|GtkAdjustment
modifier|*
name|levels_data
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
modifier|*
name|image_map
decl_stmt|;
DECL|member|levels
name|gint
name|levels
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|member|lut
name|GimpLut
modifier|*
name|lut
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
name|gimp_posterize_tool_class_init
parameter_list|(
name|GimpPosterizeToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_posterize_tool_init
parameter_list|(
name|GimpPosterizeTool
modifier|*
name|bc_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_posterize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_posterize_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|PosterizeDialog
modifier|*
name|posterize_dialog_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_dialog_hide
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_preview
parameter_list|(
name|PosterizeDialog
modifier|*
name|pd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_levels_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|posterize_dialog
specifier|static
name|PosterizeDialog
modifier|*
name|posterize_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImageMapToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  functions  */
end_comment

begin_function
name|void
DECL|function|gimp_posterize_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_posterize_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_POSTERIZE_TOOL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
literal|"gimp-posterize-tool"
argument_list|,
name|_
argument_list|(
literal|"Posterize"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Reduce image to a fixed numer of colors"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Layer/Colors/Posterize..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"tools/posterize.html"
argument_list|,
name|GIMP_STOCK_TOOL_POSTERIZE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_posterize_tool_get_type (void)
name|gimp_posterize_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPosterizeToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_posterize_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPosterizeTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_posterize_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|,
literal|"GimpPosterizeTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_class_init (GimpPosterizeToolClass * klass)
name|gimp_posterize_tool_class_init
parameter_list|(
name|GimpPosterizeToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_posterize_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_posterize_tool_control
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_init (GimpPosterizeTool * bc_tool)
name|gimp_posterize_tool_init
parameter_list|(
name|GimpPosterizeTool
modifier|*
name|bc_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_posterize_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gdisp
condition|)
block|{
name|posterize_dialog_hide
argument_list|()
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Posterize does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  The posterize dialog  */
if|if
condition|(
operator|!
name|posterize_dialog
condition|)
name|posterize_dialog
operator|=
name|posterize_dialog_new
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|posterize_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|posterize_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|posterize_dialog
operator|->
name|levels
operator|=
literal|3
expr_stmt|;
name|posterize_dialog
operator|->
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|posterize_dialog
operator|->
name|image_map
operator|=
name|image_map_create
argument_list|(
name|gdisp
argument_list|,
name|posterize_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|posterize_dialog
operator|->
name|levels_data
argument_list|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
if|if
condition|(
name|posterize_dialog
operator|->
name|preview
condition|)
name|posterize_preview
argument_list|(
name|posterize_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_posterize_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_posterize_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
break|break;
case|case
name|HALT
case|:
name|posterize_dialog_hide
argument_list|()
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  Posterize dialog  */
end_comment

begin_comment
comment|/**********************/
end_comment

begin_function
specifier|static
name|PosterizeDialog
modifier|*
DECL|function|posterize_dialog_new (void)
name|posterize_dialog_new
parameter_list|(
name|void
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
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
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|pd
operator|=
name|g_new
argument_list|(
name|PosterizeDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|pd
operator|->
name|levels
operator|=
literal|3
expr_stmt|;
name|pd
operator|->
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
comment|/*  The shell and main vbox  */
name|pd
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Posterize"
argument_list|)
argument_list|,
literal|"posterize"
argument_list|,
name|tool_manager_help_func
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|posterize_cancel_callback
argument_list|,
name|pd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|posterize_reset_callback
argument_list|,
name|pd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|posterize_ok_callback
argument_list|,
name|pd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
comment|/*  Horizontal box for levels text widget  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Posterize Levels:"
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
name|label
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
name|label
argument_list|)
expr_stmt|;
comment|/*  levels spinbutton  */
name|data
operator|=
name|gtk_adjustment_new
argument_list|(
literal|3
argument_list|,
literal|2
argument_list|,
literal|256
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|pd
operator|->
name|levels_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|pd
operator|->
name|levels_data
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|spinbutton
argument_list|,
literal|75
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|pd
operator|->
name|levels_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|posterize_levels_adjustment_update
argument_list|)
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/*  Horizontal box for preview  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
comment|/*  The preview toggle  */
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|pd
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|posterize_preview_update
argument_list|)
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|pd
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_dialog_hide (void)
name|posterize_dialog_hide
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|posterize_dialog
condition|)
name|posterize_cancel_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|posterize_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_preview (PosterizeDialog * pd)
name|posterize_preview
parameter_list|(
name|PosterizeDialog
modifier|*
name|pd
parameter_list|)
block|{
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pd
operator|->
name|image_map
condition|)
block|{
name|g_warning
argument_list|(
literal|"posterize_preview(): No image map"
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|posterize_lut_setup
argument_list|(
name|pd
operator|->
name|lut
argument_list|,
name|pd
operator|->
name|levels
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|pd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|pd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|void
operator|*
operator|)
name|pd
operator|->
name|lut
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_reset_callback (GtkWidget * widget,gpointer data)
name|posterize_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|pd
operator|->
name|levels_data
argument_list|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_ok_callback (GtkWidget * widget,gpointer data)
name|posterize_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pd
operator|->
name|preview
condition|)
block|{
name|posterize_lut_setup
argument_list|(
name|pd
operator|->
name|lut
argument_list|,
name|pd
operator|->
name|levels
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|pd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|pd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|gpointer
operator|)
name|pd
operator|->
name|lut
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pd
operator|->
name|image_map
condition|)
name|image_map_commit
argument_list|(
name|pd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pd
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_cancel_callback (GtkWidget * widget,gpointer data)
name|posterize_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|pd
operator|->
name|image_map
condition|)
block|{
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|image_map_abort
argument_list|(
name|pd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pd
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|active_tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
name|active_tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_preview_update (GtkWidget * widget,gpointer data)
name|posterize_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|pd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|posterize_preview
argument_list|(
name|pd
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pd
operator|->
name|preview
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|pd
operator|->
name|image_map
condition|)
block|{
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|image_map_clear
argument_list|(
name|pd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|active_tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|active_tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_levels_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|posterize_levels_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|pd
operator|->
name|levels
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|pd
operator|->
name|levels
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
if|if
condition|(
name|pd
operator|->
name|preview
condition|)
name|posterize_preview
argument_list|(
name|pd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


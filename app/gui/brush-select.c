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
file|<string.h>
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"tools/paint_options.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"brush-select.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-constructors.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|MIN_CELL_SIZE
define|#
directive|define
name|MIN_CELL_SIZE
value|25
end_define

begin_define
DECL|macro|STD_BRUSH_COLUMNS
define|#
directive|define
name|STD_BRUSH_COLUMNS
value|5
end_define

begin_define
DECL|macro|STD_BRUSH_ROWS
define|#
directive|define
name|STD_BRUSH_ROWS
value|5
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|brush_select_change_callbacks
parameter_list|(
name|BrushSelect
modifier|*
name|bsp
parameter_list|,
name|gboolean
name|closing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_select_brush_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_select_opacity_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_select_paint_mode_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|LayerModeEffects
name|paint_mode
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_select_brush_renamed_callback
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_select_update_active_brush_field
parameter_list|(
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|opacity_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|paint_mode_menu_callback
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
name|spacing_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_select_close_callback
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

begin_comment
comment|/*  list of active dialogs  */
end_comment

begin_decl_stmt
DECL|variable|brush_active_dialogs
name|GSList
modifier|*
name|brush_active_dialogs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the main brush selection dialog  */
end_comment

begin_decl_stmt
DECL|variable|brush_select_dialog
name|BrushSelect
modifier|*
name|brush_select_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|brush_dialog_create (void)
name|brush_dialog_create
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|brush_select_dialog
condition|)
block|{
name|brush_select_dialog
operator|=
name|brush_select_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|brush_select_dialog
operator|->
name|shell
return|;
block|}
end_function

begin_function
name|void
DECL|function|brush_dialog_free (void)
name|brush_dialog_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|brush_select_dialog
condition|)
block|{
name|brush_select_free
argument_list|(
name|brush_select_dialog
argument_list|)
expr_stmt|;
name|brush_select_dialog
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  If title == NULL then it is the main brush dialog  */
end_comment

begin_function
name|BrushSelect
modifier|*
DECL|function|brush_select_new (gchar * title,gchar * init_name,gdouble init_opacity,gint init_spacing,gint init_mode)
name|brush_select_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
comment|/*  These are the required initial vals 		   *  If init_name == NULL then use current brush 		   */
name|gchar
modifier|*
name|init_name
parameter_list|,
name|gdouble
name|init_opacity
parameter_list|,
name|gint
name|init_spacing
parameter_list|,
name|gint
name|init_mode
parameter_list|)
block|{
name|BrushSelect
modifier|*
name|bsp
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|sep
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GimpBrush
modifier|*
name|active
init|=
name|NULL
decl_stmt|;
specifier|static
name|gboolean
name|first_call
init|=
name|TRUE
decl_stmt|;
name|bsp
operator|=
name|g_new0
argument_list|(
name|BrushSelect
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  The shell  */
name|bsp
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|title
condition|?
name|title
else|:
name|_
argument_list|(
literal|"Brush Selection"
argument_list|)
argument_list|,
literal|"brush_selection"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/brush_selection.html"
argument_list|,
name|title
condition|?
name|GTK_WIN_POS_MOUSE
else|:
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|"_delete_event_"
argument_list|,
name|brush_select_close_callback
argument_list|,
name|bsp
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|g_list_nth_data
argument_list|(
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_DIALOG
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
operator|->
name|action_area
argument_list|)
expr_stmt|;
if|if
condition|(
name|title
condition|)
block|{
name|bsp
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|title
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|bsp
operator|->
name|context
operator|=
name|gimp_context_get_user
argument_list|()
expr_stmt|;
name|dialog_register
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|no_data
operator|&&
name|first_call
condition|)
name|gimp_data_factory_data_init
argument_list|(
name|global_brush_factory
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|first_call
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|title
operator|&&
name|init_name
operator|&&
name|strlen
argument_list|(
name|init_name
argument_list|)
condition|)
block|{
name|active
operator|=
operator|(
name|GimpBrush
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|global_brush_factory
operator|->
name|container
argument_list|,
name|init_name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|active
operator|=
name|gimp_context_get_brush
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|active
condition|)
name|active
operator|=
name|gimp_context_get_brush
argument_list|(
name|gimp_context_get_standard
argument_list|()
argument_list|)
expr_stmt|;
if|if
condition|(
name|title
condition|)
block|{
name|gimp_context_set_brush
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|gimp_context_set_paint_mode
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|init_mode
argument_list|)
expr_stmt|;
name|gimp_context_set_opacity
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|init_opacity
argument_list|)
expr_stmt|;
name|bsp
operator|->
name|spacing_value
operator|=
name|init_spacing
expr_stmt|;
block|}
comment|/*  The main vbox  */
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
comment|/*  Create the active brush label  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|bsp
operator|->
name|brush_name
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"No Brushes available"
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
name|bsp
operator|->
name|brush_name
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|bsp
operator|->
name|brush_size
operator|=
name|gtk_label_new
argument_list|(
literal|"(0 x 0)"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|bsp
operator|->
name|brush_size
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|bsp
operator|->
name|brush_name
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|bsp
operator|->
name|brush_size
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/*  The Brush Grid  */
name|bsp
operator|->
name|view
operator|=
name|gimp_data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|,
name|global_brush_factory
argument_list|,
name|dialogs_edit_brush_func
argument_list|,
name|bsp
operator|->
name|context
argument_list|,
name|MIN_CELL_SIZE
argument_list|,
name|STD_BRUSH_COLUMNS
argument_list|,
name|STD_BRUSH_ROWS
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|bsp
operator|->
name|view
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
name|bsp
operator|->
name|view
argument_list|)
expr_stmt|;
comment|/*  The vbox for the paint options  */
name|bsp
operator|->
name|paint_options_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|bsp
operator|->
name|view
argument_list|)
argument_list|,
name|bsp
operator|->
name|paint_options_box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  Create the frame and the table for the options  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|bsp
operator|->
name|paint_options_box
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  Create the opacity scale widget  */
name|bsp
operator|->
name|opacity_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
name|gimp_context_get_opacity
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
operator|*
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|bsp
operator|->
name|opacity_data
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|opacity_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|opacity_scale_update
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Opacity:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  Create the paint mode option menu  */
name|bsp
operator|->
name|option_menu
operator|=
name|paint_mode_menu_new
argument_list|(
name|paint_mode_menu_callback
argument_list|,
operator|(
name|gpointer
operator|)
name|bsp
argument_list|,
name|TRUE
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Mode:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|bsp
operator|->
name|option_menu
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|bsp
operator|->
name|paint_options_box
argument_list|)
expr_stmt|;
comment|/*  A separator after the paint options  */
name|sep
operator|=
name|gtk_hseparator_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|bsp
operator|->
name|paint_options_box
argument_list|)
argument_list|,
name|sep
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
name|sep
argument_list|)
expr_stmt|;
comment|/*  Create the spacing scale widget  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|bsp
operator|->
name|view
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|bsp
operator|->
name|spacing_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1000.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|bsp
operator|->
name|spacing_data
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
if|if
condition|(
name|title
operator|&&
name|init_spacing
operator|>=
literal|0
condition|)
block|{
comment|/*  Use passed spacing instead of brushes default  */
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|bsp
operator|->
name|spacing_data
argument_list|)
argument_list|,
name|init_spacing
argument_list|)
expr_stmt|;
block|}
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|spacing_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|spacing_scale_update
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Spacing:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
comment|/*  add callbacks to keep the display area current  */
name|bsp
operator|->
name|name_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|global_brush_factory
operator|->
name|container
argument_list|,
literal|"name_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_select_brush_renamed_callback
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
comment|/*  Only for main dialog  */
if|if
condition|(
operator|!
name|title
condition|)
block|{
comment|/*  if we are in per-tool paint options mode, hide the paint options  */
name|brush_select_show_paint_options
argument_list|(
name|bsp
argument_list|,
name|global_paint_options
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
literal|"brush_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_select_brush_changed
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
literal|"opacity_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_select_opacity_changed
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
literal|"paint_mode_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_select_paint_mode_changed
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
name|brush_select_update_active_brush_field
argument_list|(
name|bsp
argument_list|)
expr_stmt|;
comment|/*  Add to active brush dialogs list  */
name|brush_active_dialogs
operator|=
name|g_slist_append
argument_list|(
name|brush_active_dialogs
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
return|return
name|bsp
return|;
block|}
end_function

begin_function
name|void
DECL|function|brush_select_free (BrushSelect * bsp)
name|brush_select_free
parameter_list|(
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|bsp
condition|)
return|return;
comment|/* remove from active list */
name|brush_active_dialogs
operator|=
name|g_slist_remove
argument_list|(
name|brush_active_dialogs
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
name|gtk_signal_disconnect_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsp
operator|->
name|callback_name
condition|)
block|{
name|g_free
argument_list|(
name|bsp
operator|->
name|callback_name
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_container_remove_handler
argument_list|(
name|global_brush_factory
operator|->
name|container
argument_list|,
name|bsp
operator|->
name|name_changed_handler_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bsp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|brush_select_show_paint_options (BrushSelect * bsp,gboolean show)
name|brush_select_show_paint_options
parameter_list|(
name|BrushSelect
modifier|*
name|bsp
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
if|if
condition|(
operator|(
name|bsp
operator|==
name|NULL
operator|)
operator|&&
operator|(
operator|(
name|bsp
operator|=
name|brush_select_dialog
operator|)
operator|==
name|NULL
operator|)
condition|)
return|return;
if|if
condition|(
name|show
condition|)
block|{
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|bsp
operator|->
name|paint_options_box
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|bsp
operator|->
name|paint_options_box
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|bsp
operator|->
name|paint_options_box
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|bsp
operator|->
name|paint_options_box
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  call this dialog's PDB callback  */
end_comment

begin_function
specifier|static
name|void
DECL|function|brush_select_change_callbacks (BrushSelect * bsp,gboolean closing)
name|brush_select_change_callbacks
parameter_list|(
name|BrushSelect
modifier|*
name|bsp
parameter_list|,
name|gboolean
name|closing
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|ProcRecord
modifier|*
name|prec
init|=
name|NULL
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
specifier|static
name|gboolean
name|busy
init|=
name|FALSE
decl_stmt|;
comment|/* Any procs registered to callback? */
name|Argument
modifier|*
name|return_vals
decl_stmt|;
if|if
condition|(
operator|!
name|bsp
operator|||
operator|!
name|bsp
operator|->
name|callback_name
operator|||
name|busy
condition|)
return|return;
name|busy
operator|=
name|TRUE
expr_stmt|;
name|name
operator|=
name|bsp
operator|->
name|callback_name
expr_stmt|;
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
expr_stmt|;
comment|/* If its still registered run it */
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|prec
operator|&&
name|brush
condition|)
block|{
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|name
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PDB_STRING
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
operator|->
name|name
argument_list|,
name|PDB_FLOAT
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
name|PDB_INT32
argument_list|,
name|bsp
operator|->
name|spacing_value
argument_list|,
name|PDB_INT32
argument_list|,
operator|(
name|gint
operator|)
name|gimp_context_get_paint_mode
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
name|PDB_INT32
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
argument_list|,
name|PDB_INT32
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|height
argument_list|,
name|PDB_INT32
argument_list|,
operator|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|*
name|brush
operator|->
name|mask
operator|->
name|height
operator|)
argument_list|,
name|PDB_INT8ARRAY
argument_list|,
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
argument_list|,
name|PDB_INT32
argument_list|,
operator|(
name|gint
operator|)
name|closing
argument_list|,
name|PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|return_vals
operator|||
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|!=
name|PDB_SUCCESS
condition|)
name|g_message
argument_list|(
literal|"failed to run brush callback function"
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
name|busy
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Close active dialogs that no longer have PDB registered for them */
end_comment

begin_function
name|void
DECL|function|brush_select_dialogs_check (void)
name|brush_select_dialogs_check
parameter_list|(
name|void
parameter_list|)
block|{
name|BrushSelect
modifier|*
name|bsp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|ProcRecord
modifier|*
name|prec
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|brush_active_dialogs
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|bsp
operator|=
operator|(
name|BrushSelect
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|name
operator|=
name|bsp
operator|->
name|callback_name
expr_stmt|;
if|if
condition|(
name|name
condition|)
block|{
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|prec
condition|)
block|{
comment|/*  Can alter brush_active_dialogs list  */
name|brush_select_close_callback
argument_list|(
name|NULL
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/*  *  Local functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|brush_select_brush_changed (GimpContext * context,GimpBrush * brush,BrushSelect * bsp)
name|brush_select_brush_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
block|{
if|if
condition|(
name|brush
condition|)
block|{
name|brush_select_update_active_brush_field
argument_list|(
name|bsp
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|bsp
operator|->
name|view
argument_list|)
operator|->
name|edit_button
argument_list|,
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsp
operator|->
name|callback_name
condition|)
name|brush_select_change_callbacks
argument_list|(
name|bsp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_select_opacity_changed (GimpContext * context,gdouble opacity,BrushSelect * bsp)
name|brush_select_opacity_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
block|{
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|opacity_data
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|bsp
operator|->
name|opacity_data
argument_list|)
argument_list|,
name|opacity
operator|*
literal|100.0
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|opacity_data
argument_list|)
argument_list|,
name|bsp
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsp
operator|->
name|callback_name
condition|)
name|brush_select_change_callbacks
argument_list|(
name|bsp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_select_paint_mode_changed (GimpContext * context,LayerModeEffects paint_mode,BrushSelect * bsp)
name|brush_select_paint_mode_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|LayerModeEffects
name|paint_mode
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
block|{
name|gimp_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|bsp
operator|->
name|option_menu
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|paint_mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsp
operator|->
name|callback_name
condition|)
name|brush_select_change_callbacks
argument_list|(
name|bsp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_select_brush_renamed_callback (GimpBrush * brush,BrushSelect * bsp)
name|brush_select_brush_renamed_callback
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
block|{
name|brush_select_update_active_brush_field
argument_list|(
name|bsp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_select_update_active_brush_field (BrushSelect * bsp)
name|brush_select_update_active_brush_field
parameter_list|(
name|BrushSelect
modifier|*
name|bsp
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|gchar
name|buf
index|[
literal|32
index|]
decl_stmt|;
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|brush
condition|)
return|return;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|bsp
operator|->
name|brush_name
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"(%d x %d)"
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|width
argument_list|,
name|brush
operator|->
name|mask
operator|->
name|height
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|bsp
operator|->
name|brush_size
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|bsp
operator|->
name|spacing_data
argument_list|)
argument_list|,
name|gimp_brush_get_spacing
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|opacity_scale_update (GtkAdjustment * adjustment,gpointer data)
name|opacity_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrushSelect
modifier|*
name|bsp
decl_stmt|;
name|bsp
operator|=
operator|(
name|BrushSelect
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_context_set_opacity
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|adjustment
operator|->
name|value
operator|/
literal|100.0
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paint_mode_menu_callback (GtkWidget * widget,gpointer data)
name|paint_mode_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrushSelect
modifier|*
name|bsp
decl_stmt|;
name|LayerModeEffects
name|paint_mode
decl_stmt|;
name|bsp
operator|=
operator|(
name|BrushSelect
operator|*
operator|)
name|data
expr_stmt|;
name|paint_mode
operator|=
operator|(
name|LayerModeEffects
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_paint_mode
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|spacing_scale_update (GtkAdjustment * adjustment,gpointer data)
name|spacing_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrushSelect
modifier|*
name|bsp
decl_stmt|;
name|bsp
operator|=
operator|(
name|BrushSelect
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|bsp
operator|==
name|brush_select_dialog
condition|)
block|{
name|gimp_brush_set_spacing
argument_list|(
name|gimp_context_get_brush
argument_list|(
name|bsp
operator|->
name|context
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|adjustment
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|bsp
operator|->
name|spacing_value
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|bsp
operator|->
name|spacing_value
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|brush_select_change_callbacks
argument_list|(
name|bsp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_select_close_callback (GtkWidget * widget,gpointer data)
name|brush_select_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrushSelect
modifier|*
name|bsp
decl_stmt|;
name|bsp
operator|=
operator|(
name|BrushSelect
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/* Free memory if poping down dialog which is not the main one */
if|if
condition|(
name|bsp
operator|!=
name|brush_select_dialog
condition|)
block|{
comment|/* Send data back */
name|brush_select_change_callbacks
argument_list|(
name|bsp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|bsp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|brush_select_free
argument_list|(
name|bsp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


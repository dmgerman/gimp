begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox-indicator-area.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|24
end_define

begin_comment
DECL|macro|CELL_SIZE
comment|/*  The size of the previews                  */
end_comment

begin_define
DECL|macro|GRAD_CELL_WIDTH
define|#
directive|define
name|GRAD_CELL_WIDTH
value|52
end_define

begin_comment
DECL|macro|GRAD_CELL_WIDTH
comment|/*  The width of the gradient preview         */
end_comment

begin_define
DECL|macro|GRAD_CELL_HEIGHT
define|#
directive|define
name|GRAD_CELL_HEIGHT
value|12
end_define

begin_comment
DECL|macro|GRAD_CELL_HEIGHT
comment|/*  The height of the gradient preview        */
end_comment

begin_define
DECL|macro|CELL_SPACING
define|#
directive|define
name|CELL_SPACING
value|2
end_define

begin_comment
DECL|macro|CELL_SPACING
comment|/*  How much between brush and pattern cells  */
end_comment

begin_function
specifier|static
name|void
DECL|function|brush_preview_clicked (GtkWidget * widget,GdkModifierType state,GimpToolbox * toolbox)
name|brush_preview_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|)
block|{
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|gimp_dock_get_dialog_factory
argument_list|(
name|GIMP_DOCK
argument_list|(
name|toolbox
argument_list|)
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-brush-grid|gimp-brush-list"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_preview_drop_brush (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|brush_preview_drop_brush
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_context_set_brush
argument_list|(
name|context
argument_list|,
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_preview_clicked (GtkWidget * widget,GdkModifierType state,GimpToolbox * toolbox)
name|pattern_preview_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|)
block|{
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|gimp_dock_get_dialog_factory
argument_list|(
name|GIMP_DOCK
argument_list|(
name|toolbox
argument_list|)
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-pattern-grid|gimp-pattern-list"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_preview_drop_pattern (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|pattern_preview_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_context_set_pattern
argument_list|(
name|context
argument_list|,
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_preview_clicked (GtkWidget * widget,GdkModifierType state,GimpToolbox * toolbox)
name|gradient_preview_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|)
block|{
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|gimp_dock_get_dialog_factory
argument_list|(
name|GIMP_DOCK
argument_list|(
name|toolbox
argument_list|)
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-gradient-list|gimp-gradient-grid"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_preview_drop_gradient (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gradient_preview_drop_gradient
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_context_set_gradient
argument_list|(
name|context
argument_list|,
name|GIMP_GRADIENT
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_toolbox_indicator_area_create (GimpToolbox * toolbox)
name|gimp_toolbox_indicator_area_create
parameter_list|(
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GtkWidget
modifier|*
name|indicator_table
decl_stmt|;
name|GtkWidget
modifier|*
name|brush_view
decl_stmt|;
name|GtkWidget
modifier|*
name|pattern_view
decl_stmt|;
name|GtkWidget
modifier|*
name|gradient_view
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|toolbox
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_dock_get_context
argument_list|(
name|GIMP_DOCK
argument_list|(
name|toolbox
argument_list|)
argument_list|)
expr_stmt|;
name|indicator_table
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
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|CELL_SPACING
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|CELL_SPACING
argument_list|)
expr_stmt|;
comment|/*  brush view  */
name|brush_view
operator|=
name|gimp_view_new_full_by_types
argument_list|(
name|context
argument_list|,
name|GIMP_TYPE_VIEW
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|brush_view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|brush_view
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|brush_view
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|brush_view
argument_list|,
name|_
argument_list|(
literal|"The active brush.\n"
literal|"Click to open the Brush Dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"brush-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_set_viewable
argument_list|)
argument_list|,
name|brush_view
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|brush_view
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_preview_clicked
argument_list|)
argument_list|,
name|toolbox
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|brush_view
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|,
name|brush_preview_drop_brush
argument_list|,
name|context
argument_list|)
expr_stmt|;
comment|/*  pattern view  */
name|pattern_view
operator|=
name|gimp_view_new_full_by_types
argument_list|(
name|context
argument_list|,
name|GIMP_TYPE_VIEW
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|pattern_view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|pattern_view
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pattern_view
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|pattern_view
argument_list|,
name|_
argument_list|(
literal|"The active pattern.\n"
literal|"Click to open the Pattern Dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"pattern-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_set_viewable
argument_list|)
argument_list|,
name|pattern_view
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|pattern_view
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|pattern_preview_clicked
argument_list|)
argument_list|,
name|toolbox
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|pattern_view
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|pattern_preview_drop_pattern
argument_list|,
name|context
argument_list|)
expr_stmt|;
comment|/*  gradient view  */
name|gradient_view
operator|=
name|gimp_view_new_full_by_types
argument_list|(
name|context
argument_list|,
name|GIMP_TYPE_VIEW
argument_list|,
name|GIMP_TYPE_GRADIENT
argument_list|,
name|GRAD_CELL_WIDTH
argument_list|,
name|GRAD_CELL_HEIGHT
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|gradient_view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|gradient_view
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gradient_view
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|gradient_view
argument_list|,
name|_
argument_list|(
literal|"The active gradient.\n"
literal|"Click to open the Gradient Dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"gradient-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_set_viewable
argument_list|)
argument_list|,
name|gradient_view
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gradient_view
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradient_preview_clicked
argument_list|)
argument_list|,
name|toolbox
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|gradient_view
argument_list|,
name|GIMP_TYPE_GRADIENT
argument_list|,
name|gradient_preview_drop_gradient
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|indicator_table
argument_list|)
expr_stmt|;
return|return
name|indicator_table
return|;
block|}
end_function

end_unit


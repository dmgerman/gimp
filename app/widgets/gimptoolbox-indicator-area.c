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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"brush_select.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gradient_select.h"
end_include

begin_include
include|#
directive|include
file|"indicator_area.h"
end_include

begin_include
include|#
directive|include
file|"pattern_select.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|CELL_SIZE
define|#
directive|define
name|CELL_SIZE
value|23
end_define

begin_comment
DECL|macro|CELL_SIZE
comment|/*  The size of the previews  */
end_comment

begin_define
DECL|macro|GRAD_CELL_WIDTH
define|#
directive|define
name|GRAD_CELL_WIDTH
value|48
end_define

begin_comment
DECL|macro|GRAD_CELL_WIDTH
comment|/*  The width of the gradient preview  */
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
comment|/*  The height of the gradient preview  */
end_comment

begin_define
DECL|macro|CELL_PADDING
define|#
directive|define
name|CELL_PADDING
value|2
end_define

begin_comment
DECL|macro|CELL_PADDING
comment|/*  How much between brush and pattern cells  */
end_comment

begin_comment
comment|/*  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|brush_preview
specifier|static
name|GtkWidget
modifier|*
name|brush_preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pattern_preview
specifier|static
name|GtkWidget
modifier|*
name|pattern_preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradient_preview
specifier|static
name|GtkWidget
modifier|*
name|gradient_preview
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|brush_preview_clicked (GtkWidget * widget,gpointer data)
name|brush_preview_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|brush_dialog_create
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_preview_drop_brush (GtkWidget * widget,GimpBrush * brush,gpointer data)
name|brush_preview_drop_brush
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|brush
condition|)
name|gimp_context_set_brush
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
name|brush
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_preview_clicked (GtkWidget * widget,gpointer data)
name|pattern_preview_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|pattern_dialog_create
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pattern_preview_drop_pattern (GtkWidget * widget,GimpPattern * pattern,gpointer data)
name|pattern_preview_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|pattern
condition|)
name|gimp_context_set_pattern
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_preview_clicked (GtkWidget * widget,gpointer data)
name|gradient_preview_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gradient_dialog_create
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradient_preview_drop_gradient (GtkWidget * widget,GimpGradient * gradient,gpointer data)
name|gradient_preview_drop_gradient
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|gradient
condition|)
name|gimp_context_set_gradient
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|indicator_area_create (void)
name|indicator_area_create
parameter_list|(
name|void
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
name|context
operator|=
name|gimp_context_get_user
argument_list|()
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
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|CELL_PADDING
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|CELL_PADDING
argument_list|)
expr_stmt|;
comment|/*  brush preview  */
name|brush_preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"brush_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|brush_preview
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|brush_preview
argument_list|,
name|_
argument_list|(
literal|"The active brush.\n"
literal|"Click to open the Brushes Dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brush_preview_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|brush_preview
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|brush_preview
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|,
name|brush_preview_drop_brush
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|brush_preview
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
comment|/*  pattern preview  */
name|pattern_preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
name|CELL_SIZE
argument_list|,
name|CELL_SIZE
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"pattern_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|pattern_preview
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|pattern_preview
argument_list|,
name|_
argument_list|(
literal|"The active pattern.\n"
literal|"Click to open the Patterns Dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pattern_preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|pattern_preview_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|pattern_preview
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|pattern_preview
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|pattern_preview_drop_pattern
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|pattern_preview
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
comment|/*  gradient preview  */
name|gradient_preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
name|GRAD_CELL_WIDTH
argument_list|,
name|GRAD_CELL_HEIGHT
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"gradient_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|gradient_preview
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|gradient_preview
argument_list|,
name|_
argument_list|(
literal|"The active gradient.\n"
literal|"Click to open the Gradients Dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gradient_preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gradient_preview_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gtk_drag_dest_set_by_type
argument_list|(
name|gradient_preview
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|GIMP_TYPE_GRADIENT
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_set
argument_list|(
name|gradient_preview
argument_list|,
name|GIMP_TYPE_GRADIENT
argument_list|,
name|gradient_preview_drop_gradient
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
argument_list|,
name|gradient_preview
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
name|brush_preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pattern_preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gradient_preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|indicator_table
argument_list|)
expr_stmt|;
return|return
operator|(
name|indicator_table
operator|)
return|;
block|}
end_function

end_unit


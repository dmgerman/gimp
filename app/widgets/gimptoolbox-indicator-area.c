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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

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
file|"gui-types.h"
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
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"indicator-area.h"
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
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
literal|"gimp:brush-grid"
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
DECL|function|brush_preview_drop_brush (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|brush_preview_drop_brush
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
decl_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
expr_stmt|;
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
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
literal|"gimp:pattern-grid"
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
DECL|function|pattern_preview_drop_pattern (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|pattern_preview_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
decl_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
expr_stmt|;
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
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
literal|"gimp:gradient-list"
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
DECL|function|gradient_preview_drop_gradient (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gradient_preview_drop_gradient
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
decl_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
expr_stmt|;
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

begin_function
name|GtkWidget
modifier|*
DECL|function|indicator_area_create (GimpContext * context)
name|indicator_area_create
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|indicator_table
decl_stmt|;
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
name|CELL_PADDING
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|indicator_table
argument_list|)
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
name|gtk_widget_show
argument_list|(
name|brush_preview
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|brush_preview
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
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"brush_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
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
name|context
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
name|gtk_widget_show
argument_list|(
name|pattern_preview
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|pattern_preview
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
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"pattern_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|pattern_preview
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|pattern_preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
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
name|context
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
name|gradient_preview
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|gradient_preview
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
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"gradient_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|gradient_preview
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gradient_preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
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


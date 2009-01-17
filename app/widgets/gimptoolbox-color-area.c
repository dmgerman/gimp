begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolordialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpfgbgeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox-color-area.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|color_area_color_clicked
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|GimpActiveColor
name|active_color
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_area_dialog_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|color_area
specifier|static
name|GtkWidget
modifier|*
name|color_area
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_dialog
specifier|static
name|GtkWidget
modifier|*
name|color_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_dialog_active
specifier|static
name|gboolean
name|color_dialog_active
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_color
specifier|static
name|GimpActiveColor
name|edit_color
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|revert_fg
specifier|static
name|GimpRGB
name|revert_fg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|revert_bg
specifier|static
name|GimpRGB
name|revert_bg
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_toolbox_color_area_create (GimpToolbox * toolbox,gint width,gint height)
name|gimp_toolbox_color_area_create
parameter_list|(
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
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
name|color_area
operator|=
name|gimp_fg_bg_editor_new
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|color_area
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|color_area
argument_list|,
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|color_area
argument_list|,
name|_
argument_list|(
literal|"Foreground& background colors.\n"
literal|"The black and white squares reset colors.\n"
literal|"The arrows swap colors.\n"
literal|"Click to open the color selection dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|color_area
argument_list|,
literal|"color-clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_area_color_clicked
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|color_area
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|color_area_dialog_update (GimpColorDialog * dialog,const GimpRGB * color,GimpColorDialogState state,GimpContext * context)
name|color_area_dialog_update
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|GIMP_COLOR_DIALOG_OK
case|:
name|gtk_widget_hide
argument_list|(
name|color_dialog
argument_list|)
expr_stmt|;
name|color_dialog_active
operator|=
name|FALSE
expr_stmt|;
comment|/* Fallthrough */
case|case
name|GIMP_COLOR_DIALOG_UPDATE
case|:
if|if
condition|(
name|edit_color
operator|==
name|GIMP_ACTIVE_COLOR_FOREGROUND
condition|)
name|gimp_context_set_foreground
argument_list|(
name|context
argument_list|,
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_context_set_background
argument_list|(
name|context
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_DIALOG_CANCEL
case|:
name|gtk_widget_hide
argument_list|(
name|color_dialog
argument_list|)
expr_stmt|;
name|color_dialog_active
operator|=
name|FALSE
expr_stmt|;
name|gimp_context_set_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|revert_fg
argument_list|)
expr_stmt|;
name|gimp_context_set_background
argument_list|(
name|context
argument_list|,
operator|&
name|revert_bg
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_color_clicked (GimpFgBgEditor * editor,GimpActiveColor active_color,GimpContext * context)
name|color_area_color_clicked
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|GimpActiveColor
name|active_color
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|title
decl_stmt|;
if|if
condition|(
operator|!
name|color_dialog_active
condition|)
block|{
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|revert_fg
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|revert_bg
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|active_color
operator|==
name|GIMP_ACTIVE_COLOR_FOREGROUND
condition|)
block|{
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|title
operator|=
name|_
argument_list|(
literal|"Change Foreground Color"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_context_get_background
argument_list|(
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|title
operator|=
name|_
argument_list|(
literal|"Change Background Color"
argument_list|)
expr_stmt|;
block|}
name|edit_color
operator|=
name|active_color
expr_stmt|;
if|if
condition|(
operator|!
name|color_dialog
condition|)
block|{
name|GimpDialogFactory
modifier|*
name|toplevel_factory
decl_stmt|;
name|toplevel_factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"toplevel"
argument_list|)
expr_stmt|;
name|color_dialog
operator|=
name|gimp_color_dialog_new
argument_list|(
name|NULL
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|toplevel_factory
argument_list|,
literal|"gimp-toolbox-color-dialog"
argument_list|,
operator|&
name|color
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|color_dialog
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_area_dialog_update
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|color_dialog
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|gimp_color_dialog_set_color
argument_list|(
name|GIMP_COLOR_DIALOG
argument_list|(
name|color_dialog
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|color_dialog
argument_list|)
argument_list|)
expr_stmt|;
name|color_dialog_active
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

end_unit


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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"brushes-actions.h"
end_include

begin_include
include|#
directive|include
file|"data-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|brushes_actions
specifier|static
specifier|const
name|GimpActionEntry
name|brushes_actions
index|[]
init|=
block|{
block|{
literal|"brushes-popup"
block|,
name|GIMP_STOCK_BRUSH
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Brushes Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_BRUSH_DIALOG
block|}
block|,
block|{
literal|"brushes-open-as-image"
block|,
literal|"document-open"
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"_Open Brush as Image"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Open brush as image"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_open_as_image_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_OPEN_AS_IMAGE
block|}
block|,
block|{
literal|"brushes-new"
block|,
literal|"document-new"
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"_New Brush"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Create a new brush"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_NEW
block|}
block|,
block|{
literal|"brushes-duplicate"
block|,
name|GIMP_STOCK_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"D_uplicate Brush"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Duplicate this brush"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_DUPLICATE
block|}
block|,
block|{
literal|"brushes-copy-location"
block|,
literal|"edit-copy"
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Copy Brush _Location"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Copy brush file location to clipboard"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_copy_location_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_COPY_LOCATION
block|}
block|,
block|{
literal|"brushes-delete"
block|,
literal|"edit-delete"
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"_Delete Brush"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Delete this brush"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_DELETE
block|}
block|,
block|{
literal|"brushes-refresh"
block|,
literal|"view-refresh"
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"_Refresh Brushes"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Refresh brushes"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|data_refresh_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_BRUSH_REFRESH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_edit_actions
specifier|static
specifier|const
name|GimpStringActionEntry
name|brushes_edit_actions
index|[]
init|=
block|{
block|{
literal|"brushes-edit"
block|,
literal|"gtk-edit"
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"_Edit Brush..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"brushes-action"
argument_list|,
literal|"Edit this brush"
argument_list|)
block|,
literal|"gimp-brush-editor"
block|,
name|GIMP_HELP_BRUSH_EDIT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|brushes_actions_setup (GimpActionGroup * group)
name|brushes_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
literal|"brushes-action"
argument_list|,
name|brushes_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|brushes_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
literal|"brushes-action"
argument_list|,
name|brushes_edit_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|brushes_edit_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|data_edit_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|brushes_actions_update (GimpActionGroup * group,gpointer user_data)
name|brushes_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|action_data_get_context
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
init|=
name|NULL
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|action_data_sel_count
argument_list|(
name|user_data
argument_list|)
operator|>
literal|1
condition|)
block|{
name|brush
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|brush
condition|)
block|{
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
block|}
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"brushes-edit"
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"brushes-open-as-image"
argument_list|,
name|brush
operator|&&
name|filename
operator|&&
operator|!
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"brushes-duplicate"
argument_list|,
name|brush
operator|&&
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|duplicate
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"brushes-copy-location"
argument_list|,
name|brush
operator|&&
name|filename
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"brushes-delete"
argument_list|,
name|brush
operator|&&
name|gimp_data_is_deletable
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit


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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
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
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"items-actions.h"
end_include

begin_include
include|#
directive|include
file|"vectors-actions.h"
end_include

begin_include
include|#
directive|include
file|"vectors-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|vectors_actions
specifier|static
specifier|const
name|GimpActionEntry
name|vectors_actions
index|[]
init|=
block|{
block|{
literal|"vectors-popup"
block|,
name|GIMP_ICON_DIALOG_PATHS
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paths Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_PATH_DIALOG
block|}
block|,
block|{
literal|"vectors-color-tag-menu"
block|,
name|GIMP_ICON_CLOSE
comment|/* abused */
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-edit"
block|,
name|GIMP_ICON_TOOL_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Edit Pa_th"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Edit the active path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_edit_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOL_VECTORS
block|}
block|,
block|{
literal|"vectors-edit-attributes"
block|,
name|GIMP_ICON_EDIT
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Edit Path Attributes..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Edit path attributes"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_edit_attributes_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_EDIT
block|}
block|,
block|{
literal|"vectors-new"
block|,
name|GIMP_ICON_DOCUMENT_NEW
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_New Path..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Create a new path..."
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_new_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_NEW
block|}
block|,
block|{
literal|"vectors-new-last-values"
block|,
name|GIMP_ICON_DOCUMENT_NEW
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_New Path with last values"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Create a new path with last used values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_new_last_vals_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_NEW
block|}
block|,
block|{
literal|"vectors-duplicate"
block|,
name|GIMP_ICON_OBJECT_DUPLICATE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"D_uplicate Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Duplicate this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_duplicate_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_DUPLICATE
block|}
block|,
block|{
literal|"vectors-delete"
block|,
name|GIMP_ICON_EDIT_DELETE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Delete Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Delete this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_delete_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_DELETE
block|}
block|,
block|{
literal|"vectors-merge-visible"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Merge _Visible Paths"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_merge_visible_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_MERGE_VISIBLE
block|}
block|,
block|{
literal|"vectors-raise"
block|,
name|GIMP_ICON_GO_UP
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Raise Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Raise this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_raise_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_RAISE
block|}
block|,
block|{
literal|"vectors-raise-to-top"
block|,
name|GIMP_ICON_GO_TOP
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Raise Path to _Top"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Raise this path to the top"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_raise_to_top_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_RAISE_TO_TOP
block|}
block|,
block|{
literal|"vectors-lower"
block|,
name|GIMP_ICON_GO_DOWN
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Lower Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Lower this path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_lower_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_LOWER
block|}
block|,
block|{
literal|"vectors-lower-to-bottom"
block|,
name|GIMP_ICON_GO_BOTTOM
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Lower Path to _Bottom"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Lower this path to the bottom"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_lower_to_bottom_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_LOWER_TO_BOTTOM
block|}
block|,
block|{
literal|"vectors-fill"
block|,
name|GIMP_ICON_TOOL_BUCKET_FILL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Fill Path..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Fill the path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_fill_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_FILL
block|}
block|,
block|{
literal|"vectors-fill-last-values"
block|,
name|GIMP_ICON_TOOL_BUCKET_FILL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Fill Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Fill the path with last values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_fill_last_vals_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_FILL
block|}
block|,
block|{
literal|"vectors-stroke"
block|,
name|GIMP_ICON_PATH_STROKE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Stro_ke Path..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paint along the path"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_stroke_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_STROKE
block|}
block|,
block|{
literal|"vectors-stroke-last-values"
block|,
name|GIMP_ICON_PATH_STROKE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Stro_ke Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paint along the path with last values"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|vectors_stroke_last_vals_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_STROKE
block|}
block|,
block|{
literal|"vectors-copy"
block|,
name|GIMP_ICON_EDIT_COPY
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Co_py Path"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_copy_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_COPY
block|}
block|,
block|{
literal|"vectors-paste"
block|,
name|GIMP_ICON_EDIT_PASTE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Paste Pat_h"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_paste_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_PASTE
block|}
block|,
block|{
literal|"vectors-export"
block|,
name|GIMP_ICON_DOCUMENT_SAVE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"E_xport Path..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_export_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_EXPORT
block|}
block|,
block|{
literal|"vectors-import"
block|,
name|GIMP_ICON_DOCUMENT_OPEN
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"I_mport Path..."
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_import_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_PATH_IMPORT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_toggle_actions
specifier|static
specifier|const
name|GimpToggleActionEntry
name|vectors_toggle_actions
index|[]
init|=
block|{
block|{
literal|"vectors-visible"
block|,
name|GIMP_ICON_VISIBLE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Visible"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_visible_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_VISIBLE
block|}
block|,
block|{
literal|"vectors-linked"
block|,
name|GIMP_ICON_LINKED
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Linked"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_linked_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_LINKED
block|}
block|,
block|{
literal|"vectors-lock-content"
block|,
name|NULL
comment|/* GIMP_ICON_LOCK */
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"L_ock strokes"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_lock_content_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_LOCK_STROKES
block|}
block|,
block|{
literal|"vectors-lock-position"
block|,
name|GIMP_ICON_TOOL_MOVE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"L_ock position"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|vectors_lock_position_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_LOCK_POSITION
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_color_tag_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|vectors_color_tag_actions
index|[]
init|=
block|{
block|{
literal|"vectors-color-tag-none"
block|,
name|GIMP_ICON_CLOSE
comment|/* abused */
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"None"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Clear"
argument_list|)
block|,
name|GIMP_COLOR_TAG_NONE
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-blue"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Blue"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to Blue"
argument_list|)
block|,
name|GIMP_COLOR_TAG_BLUE
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-green"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Green"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to Green"
argument_list|)
block|,
name|GIMP_COLOR_TAG_GREEN
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-yellow"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Yellow"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to Yellow"
argument_list|)
block|,
name|GIMP_COLOR_TAG_YELLOW
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-orange"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Orange"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to Orange"
argument_list|)
block|,
name|GIMP_COLOR_TAG_ORANGE
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-brown"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Brown"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to Brown"
argument_list|)
block|,
name|GIMP_COLOR_TAG_BROWN
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-red"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Red"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to Red"
argument_list|)
block|,
name|GIMP_COLOR_TAG_RED
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-violet"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Violet"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to Violet"
argument_list|)
block|,
name|GIMP_COLOR_TAG_VIOLET
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|,
block|{
literal|"vectors-color-tag-gray"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Gray"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Color Tag: Set to gray"
argument_list|)
block|,
name|GIMP_COLOR_TAG_GRAY
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_COLOR_TAG
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_to_selection_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|vectors_to_selection_actions
index|[]
init|=
block|{
block|{
literal|"vectors-selection-replace"
block|,
name|GIMP_ICON_SELECTION_REPLACE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Path to Sele_ction"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Path to selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_REPLACE
block|}
block|,
block|{
literal|"vectors-selection-from-vectors"
block|,
name|GIMP_ICON_SELECTION_REPLACE
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Fr_om Path"
argument_list|)
block|,
literal|"<shift>V"
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Replace selection with path"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_REPLACE
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_REPLACE
block|}
block|,
block|{
literal|"vectors-selection-add"
block|,
name|GIMP_ICON_SELECTION_ADD
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Add to Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Add path to selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_ADD
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_ADD
block|}
block|,
block|{
literal|"vectors-selection-subtract"
block|,
name|GIMP_ICON_SELECTION_SUBTRACT
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Subtract from Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Subtract path from selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_SUBTRACT
block|}
block|,
block|{
literal|"vectors-selection-intersect"
block|,
name|GIMP_ICON_SELECTION_INTERSECT
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"_Intersect with Selection"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Intersect path with selection"
argument_list|)
block|,
name|GIMP_CHANNEL_OP_INTERSECT
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_SELECTION_INTERSECT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_selection_to_vectors_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|vectors_selection_to_vectors_actions
index|[]
init|=
block|{
block|{
literal|"vectors-selection-to-vectors"
block|,
name|GIMP_ICON_SELECTION_TO_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selecti_on to Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selection to path"
argument_list|)
block|,
name|FALSE
block|,
name|FALSE
block|,
name|GIMP_HELP_SELECTION_TO_PATH
block|}
block|,
block|{
literal|"vectors-selection-to-vectors-short"
block|,
name|GIMP_ICON_SELECTION_TO_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"To _Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selection to path"
argument_list|)
block|,
name|FALSE
block|,
name|FALSE
block|,
name|GIMP_HELP_SELECTION_TO_PATH
block|}
block|,
block|{
literal|"vectors-selection-to-vectors-advanced"
block|,
name|GIMP_ICON_SELECTION_TO_PATH
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Selection to Path (_Advanced)"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Advanced options"
argument_list|)
block|,
name|TRUE
block|,
name|FALSE
block|,
name|GIMP_HELP_SELECTION_TO_PATH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|vectors_select_actions
specifier|static
specifier|const
name|GimpEnumActionEntry
name|vectors_select_actions
index|[]
init|=
block|{
block|{
literal|"vectors-select-top"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select _Top Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select the topmost path"
argument_list|)
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_TOP
block|}
block|,
block|{
literal|"vectors-select-bottom"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select _Bottom Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select the bottommost path"
argument_list|)
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_BOTTOM
block|}
block|,
block|{
literal|"vectors-select-previous"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select _Previous Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select the path above the current path"
argument_list|)
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_PREVIOUS
block|}
block|,
block|{
literal|"vectors-select-next"
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select _Next Path"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"vectors-action"
argument_list|,
literal|"Select the vector below the current path"
argument_list|)
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|FALSE
block|,
name|GIMP_HELP_PATH_NEXT
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|vectors_actions_setup (GimpActionGroup * group)
name|vectors_actions_setup
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
literal|"vectors-action"
argument_list|,
name|vectors_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_color_tag_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_color_tag_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_color_tag_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_to_selection_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_to_selection_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_to_selection_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_selection_to_vectors_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_selection_to_vectors_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_selection_to_vectors_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
literal|"vectors-action"
argument_list|,
name|vectors_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|vectors_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|vectors_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|items_actions_setup
argument_list|(
name|group
argument_list|,
literal|"vectors"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|vectors_actions_update (GimpActionGroup * group,gpointer data)
name|vectors_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
init|=
name|NULL
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|gint
name|n_vectors
init|=
literal|0
decl_stmt|;
name|gboolean
name|mask_empty
init|=
name|TRUE
decl_stmt|;
name|gboolean
name|dr_writable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|dr_children
init|=
name|FALSE
decl_stmt|;
name|GList
modifier|*
name|next
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|prev
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|n_vectors
operator|=
name|gimp_image_get_n_vectors
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|mask_empty
operator|=
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|gimp_image_get_active_vectors
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors
condition|)
block|{
name|GList
modifier|*
name|vectors_list
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|vectors_list
operator|=
name|gimp_item_get_container_iter
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_find
argument_list|(
name|vectors_list
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|prev
operator|=
name|g_list_previous
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|next
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
block|}
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|dr_writable
operator|=
operator|!
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|dr_children
operator|=
name|TRUE
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
DECL|macro|SET_ACTIVE (action,condition)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"vectors-edit"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-edit-attributes"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-new"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-new-last-values"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-duplicate"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-delete"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-merge-visible"
argument_list|,
name|n_vectors
operator|>
literal|1
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-raise"
argument_list|,
name|vectors
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-raise-to-top"
argument_list|,
name|vectors
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-lower"
argument_list|,
name|vectors
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-lower-to-bottom"
argument_list|,
name|vectors
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-copy"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-paste"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-export"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-import"
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-to-vectors"
argument_list|,
name|image
operator|&&
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-to-vectors-short"
argument_list|,
name|image
operator|&&
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-to-vectors-advanced"
argument_list|,
name|image
operator|&&
operator|!
name|mask_empty
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-fill"
argument_list|,
name|vectors
operator|&&
name|dr_writable
operator|&&
operator|!
name|dr_children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-fill-last-values"
argument_list|,
name|vectors
operator|&&
name|dr_writable
operator|&&
operator|!
name|dr_children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-stroke"
argument_list|,
name|vectors
operator|&&
name|dr_writable
operator|&&
operator|!
name|dr_children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-stroke-last-values"
argument_list|,
name|vectors
operator|&&
name|dr_writable
operator|&&
operator|!
name|dr_children
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-replace"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-from-vectors"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-add"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-subtract"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-selection-intersect"
argument_list|,
name|vectors
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-select-top"
argument_list|,
name|vectors
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-select-bottom"
argument_list|,
name|vectors
operator|&&
name|next
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-select-previous"
argument_list|,
name|vectors
operator|&&
name|prev
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"vectors-select-next"
argument_list|,
name|vectors
operator|&&
name|next
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
undef|#
directive|undef
name|SET_ACTIVE
name|items_actions_update
argument_list|(
name|group
argument_list|,
literal|"vectors"
argument_list|,
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


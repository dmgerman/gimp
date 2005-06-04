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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-actions.h"
end_include

begin_include
include|#
directive|include
file|"dockable-actions.h"
end_include

begin_include
include|#
directive|include
file|"dockable-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|dockable_actions
specifier|static
name|GimpActionEntry
name|dockable_actions
index|[]
init|=
block|{
block|{
literal|"dockable-popup"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Dialogs Menu"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_HELP_DOCK
block|}
block|,
block|{
literal|"dockable-menu"
block|,
name|GTK_STOCK_MISSING_IMAGE
block|,
literal|""
block|}
block|,
block|{
literal|"dockable-add-tab-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Add Tab"
argument_list|)
block|}
block|,
block|{
literal|"dockable-preview-size-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Preview Size"
argument_list|)
block|}
block|,
block|{
literal|"dockable-tab-style-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Tab Style"
argument_list|)
block|}
block|,
block|{
literal|"dockable-close-tab"
block|,
name|GTK_STOCK_CLOSE
block|,
name|N_
argument_list|(
literal|"_Close Tab"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dockable_close_tab_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCK_TAB_CLOSE
block|}
block|,
block|{
literal|"dockable-detach-tab"
block|,
name|GTK_STOCK_CONVERT
block|,
name|N_
argument_list|(
literal|"_Detach Tab"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dockable_detach_tab_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCK_TAB_DETACH
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|PREVIEW_SIZE (action,label,size)
define|#
directive|define
name|PREVIEW_SIZE
parameter_list|(
name|action
parameter_list|,
name|label
parameter_list|,
name|size
parameter_list|)
define|\
value|{ "dockable-preview-size-" action, NULL, \     (label), NULL, NULL, \     (size), \     GIMP_HELP_DOCK_PREVIEW_SIZE }
end_define

begin_define
DECL|macro|TAB_STYLE (action,label,style)
define|#
directive|define
name|TAB_STYLE
parameter_list|(
name|action
parameter_list|,
name|label
parameter_list|,
name|style
parameter_list|)
define|\
value|{ "dockable-tab-style-" action, NULL, \     (label), NULL, NULL, \     (style), \     GIMP_HELP_DOCK_TAB_STYLE }
end_define

begin_decl_stmt
DECL|variable|dockable_preview_size_actions
specifier|static
name|GimpRadioActionEntry
name|dockable_preview_size_actions
index|[]
init|=
block|{
name|PREVIEW_SIZE
argument_list|(
literal|"tiny"
argument_list|,
name|N_
argument_list|(
literal|"_Tiny"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_TINY
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"extra-small"
argument_list|,
name|N_
argument_list|(
literal|"E_xtra Small"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_EXTRA_SMALL
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"small"
argument_list|,
name|N_
argument_list|(
literal|"_Small"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"medium"
argument_list|,
name|N_
argument_list|(
literal|"_Medium"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"large"
argument_list|,
name|N_
argument_list|(
literal|"_Large"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_LARGE
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"extra-large"
argument_list|,
name|N_
argument_list|(
literal|"Ex_tra Large"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_EXTRA_LARGE
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"huge"
argument_list|,
name|N_
argument_list|(
literal|"_Huge"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_HUGE
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"enormous"
argument_list|,
name|N_
argument_list|(
literal|"_Enormous"
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_ENORMOUS
argument_list|)
block|,
name|PREVIEW_SIZE
argument_list|(
literal|"gigantic"
argument_list|,
argument|N_(
literal|"_Gigantic"
argument|)
argument_list|,
argument|GIMP_VIEW_SIZE_GIGANTIC
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dockable_tab_style_actions
specifier|static
name|GimpRadioActionEntry
name|dockable_tab_style_actions
index|[]
init|=
block|{
name|TAB_STYLE
argument_list|(
literal|"icon"
argument_list|,
name|N_
argument_list|(
literal|"_Icon"
argument_list|)
argument_list|,
name|GIMP_TAB_STYLE_ICON
argument_list|)
block|,
name|TAB_STYLE
argument_list|(
literal|"preview"
argument_list|,
name|N_
argument_list|(
literal|"Current _Status"
argument_list|)
argument_list|,
name|GIMP_TAB_STYLE_PREVIEW
argument_list|)
block|,
name|TAB_STYLE
argument_list|(
literal|"name"
argument_list|,
name|N_
argument_list|(
literal|"_Text"
argument_list|)
argument_list|,
name|GIMP_TAB_STYLE_NAME
argument_list|)
block|,
name|TAB_STYLE
argument_list|(
literal|"icon-name"
argument_list|,
name|N_
argument_list|(
literal|"I_con& Text"
argument_list|)
argument_list|,
name|GIMP_TAB_STYLE_ICON_NAME
argument_list|)
block|,
name|TAB_STYLE
argument_list|(
literal|"preview-name"
argument_list|,
argument|N_(
literal|"St_atus& Text"
argument|)
argument_list|,
argument|GIMP_TAB_STYLE_PREVIEW_NAME
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_undef
undef|#
directive|undef
name|PREVIEW_SIZE
end_undef

begin_undef
undef|#
directive|undef
name|TAB_STYLE
end_undef

begin_decl_stmt
DECL|variable|dockable_toggle_actions
specifier|static
name|GimpToggleActionEntry
name|dockable_toggle_actions
index|[]
init|=
block|{
block|{
literal|"dockable-show-button-bar"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Show Button Bar"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dockable_show_button_bar_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_DOCK_SHOW_BUTTON_BAR
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dockable_view_type_actions
specifier|static
name|GimpRadioActionEntry
name|dockable_view_type_actions
index|[]
init|=
block|{
block|{
literal|"dockable-view-type-list"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"View as _List"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_VIEW_TYPE_LIST
block|,
name|GIMP_HELP_DOCK_VIEW_AS_LIST
block|}
block|,
block|{
literal|"dockable-view-type-grid"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"View as _Grid"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_VIEW_TYPE_GRID
block|,
name|GIMP_HELP_DOCK_VIEW_AS_GRID
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|dockable_actions_setup (GimpActionGroup * group)
name|dockable_actions_setup
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
name|dockable_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dockable_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
name|dockable_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dockable_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
name|dialogs_dockable_actions
argument_list|,
name|n_dialogs_dockable_actions
argument_list|,
name|G_CALLBACK
argument_list|(
name|dockable_add_tab_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
name|dockable_preview_size_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dockable_preview_size_actions
argument_list|)
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
name|G_CALLBACK
argument_list|(
name|dockable_preview_size_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
name|dockable_tab_style_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dockable_tab_style_actions
argument_list|)
argument_list|,
name|GIMP_TAB_STYLE_PREVIEW
argument_list|,
name|G_CALLBACK
argument_list|(
name|dockable_tab_style_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
name|dockable_view_type_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dockable_view_type_actions
argument_list|)
argument_list|,
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|G_CALLBACK
argument_list|(
name|dockable_toggle_view_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dockable_actions_update (GimpActionGroup * group,gpointer data)
name|dockable_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
name|GimpDialogFactoryEntry
modifier|*
name|entry
decl_stmt|;
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
name|GimpViewType
name|view_type
init|=
operator|-
literal|1
decl_stmt|;
name|gboolean
name|list_view_available
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|grid_view_available
init|=
name|FALSE
decl_stmt|;
name|GimpViewSize
name|preview_size
init|=
operator|-
literal|1
decl_stmt|;
name|GimpTabStyle
name|tab_style
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|n_pages
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|gint
name|page_num
decl_stmt|;
name|dockbook
operator|=
name|GIMP_DOCKBOOK
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|page_num
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|dockable
operator|=
operator|(
name|GimpDockable
operator|*
operator|)
name|gtk_notebook_get_nth_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|dockable
operator|=
name|GIMP_DOCKABLE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|dockable
operator|->
name|dockbook
expr_stmt|;
block|}
else|else
block|{
return|return;
block|}
name|gimp_dialog_factory_from_widget
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|&
name|entry
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
condition|)
block|{
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|gchar
modifier|*
name|substring
init|=
name|NULL
decl_stmt|;
name|identifier
operator|=
name|g_strdup
argument_list|(
name|entry
operator|->
name|identifier
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|substring
operator|=
name|strstr
argument_list|(
name|identifier
argument_list|,
literal|"grid"
argument_list|)
operator|)
condition|)
name|view_type
operator|=
name|GIMP_VIEW_TYPE_GRID
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|substring
operator|=
name|strstr
argument_list|(
name|identifier
argument_list|,
literal|"list"
argument_list|)
operator|)
condition|)
name|view_type
operator|=
name|GIMP_VIEW_TYPE_LIST
expr_stmt|;
if|if
condition|(
name|substring
condition|)
block|{
name|memcpy
argument_list|(
name|substring
argument_list|,
literal|"list"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_factory_find_entry
argument_list|(
name|dockbook
operator|->
name|dock
operator|->
name|dialog_factory
argument_list|,
name|identifier
argument_list|)
condition|)
name|list_view_available
operator|=
name|TRUE
expr_stmt|;
name|memcpy
argument_list|(
name|substring
argument_list|,
literal|"grid"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_factory_find_entry
argument_list|(
name|dockbook
operator|->
name|dock
operator|->
name|dialog_factory
argument_list|,
name|identifier
argument_list|)
condition|)
name|grid_view_available
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
block|}
name|view
operator|=
name|gimp_container_view_get_by_dockable
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
condition|)
name|preview_size
operator|=
name|gimp_container_view_get_preview_size
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tab_style
operator|=
name|dockable
operator|->
name|tab_style
expr_stmt|;
name|n_pages
operator|=
name|gtk_notebook_get_n_pages
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
DECL|macro|SET_ACTIVE (action,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (active) != 0)
DECL|macro|SET_VISIBLE (action,active)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|action
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_action_group_set_action_visible (group, action, (active) != 0)
DECL|macro|SET_SENSITIVE (action,sensitive)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|sensitive
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (sensitive) != 0)
name|SET_VISIBLE
argument_list|(
literal|"dockable-preview-size-menu"
argument_list|,
name|preview_size
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview_size
operator|!=
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_GIGANTIC
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-gigantic"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_ENORMOUS
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-enormous"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_HUGE
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-huge"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_EXTRA_LARGE
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-extra-large"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_LARGE
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-large"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_MEDIUM
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-medium"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_SMALL
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-small"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_EXTRA_SMALL
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-extra-small"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|preview_size
operator|>=
name|GIMP_VIEW_SIZE_TINY
condition|)
block|{
name|SET_ACTIVE
argument_list|(
literal|"dockable-preview-size-tiny"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
name|SET_VISIBLE
argument_list|(
literal|"dockable-tab-style-menu"
argument_list|,
name|n_pages
operator|>
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_pages
operator|>
literal|1
condition|)
block|{
name|GimpDockedInterface
modifier|*
name|docked_iface
decl_stmt|;
name|docked_iface
operator|=
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
if|if
condition|(
name|tab_style
operator|==
name|GIMP_TAB_STYLE_ICON
condition|)
name|SET_ACTIVE
argument_list|(
literal|"dockable-tab-style-icon"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|tab_style
operator|==
name|GIMP_TAB_STYLE_PREVIEW
condition|)
name|SET_ACTIVE
argument_list|(
literal|"dockable-tab-style-preview"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|tab_style
operator|==
name|GIMP_TAB_STYLE_NAME
condition|)
name|SET_ACTIVE
argument_list|(
literal|"dockable-tab-style-name"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|tab_style
operator|==
name|GIMP_TAB_STYLE_ICON_NAME
condition|)
name|SET_ACTIVE
argument_list|(
literal|"dockable-tab-style-icon-name"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|tab_style
operator|==
name|GIMP_TAB_STYLE_PREVIEW_NAME
condition|)
name|SET_ACTIVE
argument_list|(
literal|"dockable-tab-style-preview-name"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"dockable-tab-style-preview"
argument_list|,
name|docked_iface
operator|->
name|get_preview
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"dockable-tab-style-preview-name"
argument_list|,
name|docked_iface
operator|->
name|get_preview
argument_list|)
expr_stmt|;
block|}
name|SET_VISIBLE
argument_list|(
literal|"dockable-view-type-grid"
argument_list|,
name|view_type
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"dockable-view-type-list"
argument_list|,
name|view_type
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|view_type
operator|!=
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|)
name|SET_ACTIVE
argument_list|(
literal|"dockable-view-type-list"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|SET_ACTIVE
argument_list|(
literal|"dockable-view-type-grid"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"dockable-view-type-grid"
argument_list|,
name|grid_view_available
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"dockable-view-type-list"
argument_list|,
name|list_view_available
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_EDITOR
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
operator|->
name|child
argument_list|)
condition|)
block|{
name|GimpEditor
modifier|*
name|editor
init|=
name|GIMP_EDITOR
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
operator|->
name|child
argument_list|)
decl_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"dockable-show-button-bar"
argument_list|,
name|gimp_editor_has_button_bar
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"dockable-show-button-bar"
argument_list|,
name|gimp_editor_get_show_button_bar
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|SET_VISIBLE
argument_list|(
literal|"dockable-show-button-bar"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
undef|#
directive|undef
name|SET_ACTIVE
undef|#
directive|undef
name|SET_VISIBLE
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit


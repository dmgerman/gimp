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
file|"libgimpbase/gimpbase.h"
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
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
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
file|"widgets/gimpitemtreeview.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-actions.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-commands.h"
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
name|plug_in_actions_build_path
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_translated
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|plug_in_actions
specifier|static
name|GimpActionEntry
name|plug_in_actions
index|[]
init|=
block|{
block|{
literal|"plug-in-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Filte_rs"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-blur-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Blur"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-colors-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Colors"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-colors-map-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Ma_p"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-noise-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Noise"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-edge-detect-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Edge-De_tect"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-enhance-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"En_hance"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-generic-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Generic"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-glass-effects-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Gla_ss Effects"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-light-effects-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Light Effects"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-distorts-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Distorts"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-artistic-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Artistic"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-map-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Map"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-render-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Render"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-render-clouds-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Clouds"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-render-nature-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Nature"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-render-pattern-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Pattern"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-web-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Web"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-animation-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"An_imation"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-combine-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"C_ombine"
argument_list|)
block|}
block|,
block|{
literal|"plug-in-toys-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"To_ys"
argument_list|)
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|plug_in_repeat_actions
specifier|static
name|GimpEnumActionEntry
name|plug_in_repeat_actions
index|[]
init|=
block|{
block|{
literal|"plug-in-repeat"
block|,
name|GTK_STOCK_EXECUTE
block|,
name|N_
argument_list|(
literal|"Repeat Last"
argument_list|)
block|,
literal|"<control>F"
block|,
name|NULL
block|,
name|FALSE
block|,
name|GIMP_HELP_FILTER_REPEAT
block|}
block|,
block|{
literal|"plug-in-reshow"
block|,
name|GIMP_STOCK_RESHOW_FILTER
block|,
name|N_
argument_list|(
literal|"Re-Show Last"
argument_list|)
block|,
literal|"<control><shift>F"
block|,
name|NULL
block|,
name|TRUE
block|,
name|GIMP_HELP_FILTER_RESHOW
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|plug_in_actions_setup (GimpActionGroup * group,gpointer data)
name|plug_in_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|plug_in_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|plug_in_actions
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|plug_in_repeat_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|plug_in_repeat_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_repeat_cmd_callback
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|group
operator|->
name|gimp
operator|->
name|plug_in_proc_defs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|PlugInProcDef
modifier|*
name|proc_def
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|prog
operator|&&
name|proc_def
operator|->
name|menu_path
operator|&&
operator|!
name|proc_def
operator|->
name|extensions
operator|&&
operator|!
name|proc_def
operator|->
name|prefixes
operator|&&
operator|!
name|proc_def
operator|->
name|magics
condition|)
block|{
name|plug_in_actions_add_proc
argument_list|(
name|group
argument_list|,
name|proc_def
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|plug_in_actions_update (GimpActionGroup * group,gpointer data)
name|plug_in_actions_update
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
name|gimage
init|=
name|NULL
decl_stmt|;
name|GimpImageType
name|type
init|=
operator|-
literal|1
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|GIMP_IS_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
condition|)
name|gimage
operator|=
name|GIMP_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
operator|->
name|gimage
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
condition|)
name|gimage
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
name|gimage
operator|=
name|GIMP_DISPLAY
argument_list|(
name|data
argument_list|)
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
decl_stmt|;
name|type
operator|=
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|group
operator|->
name|gimp
operator|->
name|plug_in_proc_defs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|PlugInProcDef
modifier|*
name|proc_def
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|menu_path
operator|&&
name|proc_def
operator|->
name|image_types_val
operator|&&
operator|!
name|proc_def
operator|->
name|extensions
operator|&&
operator|!
name|proc_def
operator|->
name|prefixes
operator|&&
operator|!
name|proc_def
operator|->
name|magics
condition|)
block|{
name|gboolean
name|sensitive
decl_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_RGB_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_RGBA_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_INDEXED_IMAGE
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|sensitive
operator|=
name|proc_def
operator|->
name|image_types_val
operator|&
name|PLUG_IN_INDEXEDA_IMAGE
expr_stmt|;
break|break;
default|default:
name|sensitive
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
if|if
condition|(
name|group
operator|->
name|gimp
operator|->
name|last_plug_in
operator|&&
name|group
operator|->
name|gimp
operator|->
name|last_plug_in
operator|==
operator|&
name|proc_def
operator|->
name|db_info
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|progname
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|path
decl_stmt|;
name|gchar
modifier|*
name|stripped
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|ellipses
decl_stmt|;
name|gchar
modifier|*
name|repeat
decl_stmt|;
name|gchar
modifier|*
name|reshow
decl_stmt|;
name|progname
operator|=
name|plug_in_proc_def_get_progname
argument_list|(
name|proc_def
argument_list|)
expr_stmt|;
name|path
operator|=
name|dgettext
argument_list|(
name|plug_ins_locale_domain
argument_list|(
name|group
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|proc_def
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|stripped
operator|=
name|gimp_strip_uline
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
name|ellipses
operator|=
name|strstr
argument_list|(
name|basename
argument_list|,
literal|"..."
argument_list|)
expr_stmt|;
if|if
condition|(
name|ellipses
operator|&&
name|ellipses
operator|==
operator|(
name|basename
operator|+
name|strlen
argument_list|(
name|basename
argument_list|)
operator|-
literal|3
operator|)
condition|)
operator|*
name|ellipses
operator|=
literal|'\0'
expr_stmt|;
name|repeat
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Re_peat \"%s\""
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|reshow
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"R_e-show \"%s\""
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"plug-in-repeat"
argument_list|,
name|repeat
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"plug-in-reshow"
argument_list|,
name|reshow
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|repeat
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|reshow
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
literal|"plug-in-repeat"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
literal|"plug-in-reshow"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
operator|!
name|group
operator|->
name|gimp
operator|->
name|last_plug_in
condition|)
block|{
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"plug-in-repeat"
argument_list|,
name|_
argument_list|(
literal|"Repeat Last"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"plug-in-reshow"
argument_list|,
name|_
argument_list|(
literal|"Re-Show Last"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
literal|"plug-in-repeat"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_sensitive
argument_list|(
name|group
argument_list|,
literal|"plug-in-reshow"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|plug_in_actions_add_proc (GimpActionGroup * group,PlugInProcDef * proc_def)
name|plug_in_actions_add_proc
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|progname
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|locale_domain
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_domain
decl_stmt|;
name|gchar
modifier|*
name|path_original
decl_stmt|;
name|gchar
modifier|*
name|path_translated
decl_stmt|;
name|gchar
modifier|*
name|help_id
decl_stmt|;
name|gchar
modifier|*
name|p1
decl_stmt|,
modifier|*
name|p2
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|proc_def
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|progname
operator|=
name|plug_in_proc_def_get_progname
argument_list|(
name|proc_def
argument_list|)
expr_stmt|;
name|locale_domain
operator|=
name|plug_ins_locale_domain
argument_list|(
name|group
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|help_domain
operator|=
name|plug_ins_help_domain
argument_list|(
name|group
operator|->
name|gimp
argument_list|,
name|progname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|help_id
operator|=
name|plug_in_proc_def_get_help_id
argument_list|(
name|proc_def
argument_list|,
name|help_domain
argument_list|)
expr_stmt|;
name|path_original
operator|=
name|g_strdup
argument_list|(
name|proc_def
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|path_translated
operator|=
name|g_strdup
argument_list|(
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|path_original
argument_list|)
argument_list|)
expr_stmt|;
name|p1
operator|=
name|strrchr
argument_list|(
name|path_original
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strrchr
argument_list|(
name|path_translated
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p1
operator|&&
name|p2
condition|)
block|{
name|gchar
modifier|*
name|label
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|label
operator|=
name|p2
operator|+
literal|1
expr_stmt|;
name|g_print
argument_list|(
literal|"adding plug-in action '%s' (%s)\n"
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_new
argument_list|(
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|action
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_run_cmd_callback
argument_list|)
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
argument_list|)
expr_stmt|;
name|gtk_action_group_add_action_with_accel
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action
argument_list|,
name|proc_def
operator|->
name|accelerator
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
operator|*
name|p1
operator|=
literal|'\0'
expr_stmt|;
operator|*
name|p2
operator|=
literal|'\0'
expr_stmt|;
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|path_original
argument_list|,
name|path_translated
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path_original
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path_translated
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|plug_in_actions_remove_proc (GimpActionGroup * group,PlugInProcDef * proc_def)
name|plug_in_actions_remove_proc
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|proc_def
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
block|{
name|g_print
argument_list|(
literal|"removing plug-in action '%s'\n"
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|)
expr_stmt|;
name|gtk_action_group_remove_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|plug_in_actions_build_path (GimpActionGroup * group,const gchar * path_original,const gchar * path_translated)
name|plug_in_actions_build_path
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_translated
parameter_list|)
block|{
name|GHashTable
modifier|*
name|path_table
decl_stmt|;
name|gchar
modifier|*
name|p1
decl_stmt|,
modifier|*
name|p2
decl_stmt|;
name|path_table
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"plug-in-path-table"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|path_table
condition|)
block|{
name|path_table
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"plug-in-path-table"
argument_list|,
name|path_table
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_hash_table_destroy
argument_list|)
expr_stmt|;
block|}
name|p1
operator|=
name|strrchr
argument_list|(
name|path_original
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strrchr
argument_list|(
name|path_translated
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p1
operator|&&
name|p2
operator|&&
operator|!
name|g_hash_table_lookup
argument_list|(
name|path_table
argument_list|,
name|path_original
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|copy_original
init|=
name|g_strdup
argument_list|(
name|path_original
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|copy_translated
init|=
name|g_strdup
argument_list|(
name|path_translated
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|label
operator|=
name|p2
operator|+
literal|1
expr_stmt|;
name|g_print
argument_list|(
literal|"adding plug-in submenu '%s' (%s)\n"
argument_list|,
name|path_original
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|action
operator|=
name|gtk_action_new
argument_list|(
name|path_original
argument_list|,
name|label
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_action_group_add_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|action
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|path_table
argument_list|,
name|g_strdup
argument_list|(
name|path_original
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
name|p1
operator|=
name|strrchr
argument_list|(
name|copy_original
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strrchr
argument_list|(
name|copy_translated
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
operator|*
name|p1
operator|=
literal|'\0'
expr_stmt|;
operator|*
name|p2
operator|=
literal|'\0'
expr_stmt|;
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|copy_original
argument_list|,
name|copy_translated
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|copy_original
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|copy_translated
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


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
file|"plug-in/plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc-def.h"
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
name|plug_in_actions_last_changed
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|plug_in_actions_check_translation
parameter_list|(
specifier|const
name|gchar
modifier|*
name|original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|translated
parameter_list|)
function_decl|;
end_function_decl

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
name|original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|translated
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
block|,
block|{
literal|"plug-in-reset-all"
block|,
name|GIMP_STOCK_RESET
block|,
name|N_
argument_list|(
literal|"Reset all Filters..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|plug_in_reset_all_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILTER_RESET_ALL
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
DECL|function|plug_in_actions_setup (GimpActionGroup * group)
name|plug_in_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
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
name|menu_paths
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
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
argument_list|,
literal|"last-plug-in-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_actions_last_changed
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|plug_in_actions_last_changed
argument_list|(
name|group
operator|->
name|gimp
argument_list|,
name|group
argument_list|)
expr_stmt|;
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
name|gimage
operator|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
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
if|if
condition|(
name|drawable
condition|)
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
name|menu_paths
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
init|=
name|plug_in_proc_def_get_sensitive
argument_list|(
name|proc_def
argument_list|,
name|type
argument_list|)
decl_stmt|;
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
block|}
block|}
if|if
condition|(
name|group
operator|->
name|gimp
operator|->
name|last_plug_in
operator|&&
name|plug_in_proc_def_get_sensitive
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|last_plug_in
argument_list|,
name|type
argument_list|)
condition|)
block|{
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
else|else
block|{
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
name|GimpPlugInActionEntry
name|entry
decl_stmt|;
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
specifier|const
name|gchar
modifier|*
name|label_translated
decl_stmt|;
name|gchar
modifier|*
name|path_original
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|path_translated
init|=
name|NULL
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
if|if
condition|(
name|proc_def
operator|->
name|menu_label
condition|)
block|{
name|label_translated
operator|=
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|proc_def
operator|->
name|menu_label
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|p1
decl_stmt|,
modifier|*
name|p2
decl_stmt|;
name|path_original
operator|=
name|proc_def
operator|->
name|menu_paths
operator|->
name|data
expr_stmt|;
name|path_translated
operator|=
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|path_original
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|plug_in_actions_check_translation
argument_list|(
name|path_original
argument_list|,
name|path_translated
argument_list|)
condition|)
return|return;
name|path_original
operator|=
name|g_strdup
argument_list|(
name|path_original
argument_list|)
expr_stmt|;
name|path_translated
operator|=
name|g_strdup
argument_list|(
name|path_translated
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
name|label_translated
operator|=
name|p2
operator|+
literal|1
expr_stmt|;
block|}
name|entry
operator|.
name|name
operator|=
name|proc_def
operator|->
name|db_info
operator|.
name|name
expr_stmt|;
name|entry
operator|.
name|stock_id
operator|=
name|plug_in_proc_def_get_stock_id
argument_list|(
name|proc_def
argument_list|)
expr_stmt|;
name|entry
operator|.
name|label
operator|=
name|label_translated
expr_stmt|;
name|entry
operator|.
name|accelerator
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|tooltip
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|proc_def
operator|=
name|proc_def
expr_stmt|;
name|entry
operator|.
name|help_id
operator|=
name|plug_in_proc_def_get_help_id
argument_list|(
name|proc_def
argument_list|,
name|help_domain
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|g_print ("adding plug-in action '%s' (%s)\n",            proc_def->db_info.name, label_translated);
endif|#
directive|endif
name|gimp_action_group_add_plug_in_actions
argument_list|(
name|group
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|,
name|G_CALLBACK
argument_list|(
name|plug_in_run_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|entry
operator|.
name|help_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_def
operator|->
name|menu_label
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|proc_def
operator|->
name|menu_paths
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|original
init|=
name|list
operator|->
name|data
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|translated
init|=
name|dgettext
argument_list|(
name|locale_domain
argument_list|,
name|original
argument_list|)
decl_stmt|;
if|if
condition|(
name|plug_in_actions_check_translation
argument_list|(
name|original
argument_list|,
name|translated
argument_list|)
condition|)
name|plug_in_actions_build_path
argument_list|(
name|group
argument_list|,
name|original
argument_list|,
name|translated
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
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
if|#
directive|if
literal|0
block|g_print ("removing plug-in action '%s'\n",                proc_def->db_info.name);
endif|#
directive|endif
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
DECL|function|plug_in_actions_last_changed (Gimp * gimp,GimpActionGroup * group)
name|plug_in_actions_last_changed
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
if|if
condition|(
name|gimp
operator|->
name|last_plug_in
condition|)
block|{
name|PlugInProcDef
modifier|*
name|proc_def
init|=
name|gimp
operator|->
name|last_plug_in
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|progname
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|domain
decl_stmt|;
name|gchar
modifier|*
name|label
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
name|domain
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
name|label
operator|=
name|plug_in_proc_def_get_label
argument_list|(
name|proc_def
argument_list|,
name|domain
argument_list|)
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
name|label
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
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
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
block|}
else|else
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
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|plug_in_actions_check_translation (const gchar * original,const gchar * translated)
name|plug_in_actions_check_translation
parameter_list|(
specifier|const
name|gchar
modifier|*
name|original
parameter_list|,
specifier|const
name|gchar
modifier|*
name|translated
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p1
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|p2
decl_stmt|;
comment|/*  first check if<Prefix> is present and identical in both strings  */
name|p1
operator|=
name|strchr
argument_list|(
name|original
argument_list|,
literal|'>'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strchr
argument_list|(
name|translated
argument_list|,
literal|'>'
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p1
operator|||
operator|!
name|p2
operator|||
operator|(
name|p1
operator|-
name|original
operator|)
operator|!=
operator|(
name|p2
operator|-
name|translated
operator|)
operator|||
name|strncmp
argument_list|(
name|original
argument_list|,
name|translated
argument_list|,
name|p1
operator|-
name|original
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"bad translation \"%s\"\n"
literal|"for menu path   \"%s\"\n"
literal|"(<Prefix> must not be translated)\n\n"
argument_list|,
name|translated
argument_list|,
name|original
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|p1
operator|++
expr_stmt|;
name|p2
operator|++
expr_stmt|;
comment|/*  then check if either a '/' or nothing follows in *both* strings  */
if|if
condition|(
operator|!
operator|(
operator|(
operator|*
name|p1
operator|==
literal|'/'
operator|&&
operator|*
name|p2
operator|==
literal|'/'
operator|)
operator|||
operator|(
operator|*
name|p1
operator|==
literal|'\0'
operator|&&
operator|*
name|p2
operator|==
literal|'\0'
operator|)
operator|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"bad translation \"%s\"\n"
literal|"for menu path   \"%s\"\n"
literal|"(<Prefix> must be followed by either nothing or '/')\n\n"
argument_list|,
name|translated
argument_list|,
name|original
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*  then check the number of slashes in the remaining string  */
while|while
condition|(
name|p1
operator|&&
name|p2
condition|)
block|{
name|p1
operator|=
name|strchr
argument_list|(
name|p1
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
name|p2
operator|=
name|strchr
argument_list|(
name|p2
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p1
condition|)
name|p1
operator|++
expr_stmt|;
if|if
condition|(
name|p2
condition|)
name|p2
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|p1
operator|||
name|p2
condition|)
block|{
name|g_printerr
argument_list|(
literal|"bad translation \"%s\"\n"
literal|"for menu path   \"%s\"\n"
literal|"(number of '/' must be the same)\n\n"
argument_list|,
name|translated
argument_list|,
name|original
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

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
if|#
directive|if
literal|0
block|g_print ("adding plug-in submenu '%s' (%s)\n",                path_original, label);
endif|#
directive|endif
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


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
file|<stdio.h>
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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-path.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"themes.h"
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
name|themes_directories_foreach
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|themes_list_themes_foreach
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|themes_theme_change_notify
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|themes_hash
specifier|static
name|GHashTable
modifier|*
name|themes_hash
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|themes_init (Gimp * gimp)
name|themes_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|gchar
modifier|*
name|themerc
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|themes_hash
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|theme_path
condition|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|path
operator|=
name|gimp_config_path_expand
argument_list|(
name|config
operator|->
name|theme_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_datafiles_read_directories
argument_list|(
name|path
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|,
name|themes_directories_foreach
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
name|themes_apply_theme
argument_list|(
name|gimp
argument_list|,
name|config
operator|->
name|theme
argument_list|)
expr_stmt|;
name|themerc
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"themerc"
argument_list|)
expr_stmt|;
name|gtk_rc_add_default_file
argument_list|(
name|themerc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|themerc
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::theme"
argument_list|,
name|G_CALLBACK
argument_list|(
name|themes_theme_change_notify
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|themes_exit (Gimp * gimp)
name|themes_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|themes_hash
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
name|themes_theme_change_notify
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|themes_hash
argument_list|)
expr_stmt|;
name|themes_hash
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|themes_list_themes (Gimp * gimp,gint * n_themes)
name|themes_list_themes
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
modifier|*
name|n_themes
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_themes
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|n_themes
operator|=
name|g_hash_table_size
argument_list|(
name|themes_hash
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|n_themes
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|themes
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|index
decl_stmt|;
name|themes
operator|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|n_themes
operator|+
literal|1
argument_list|)
expr_stmt|;
name|index
operator|=
name|themes
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|themes_hash
argument_list|,
name|themes_list_themes_foreach
argument_list|,
operator|&
name|index
argument_list|)
expr_stmt|;
return|return
name|themes
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|themes_get_theme_dir (Gimp * gimp,const gchar * theme_name)
name|themes_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|theme_name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|theme_name
condition|)
name|theme_name
operator|=
literal|"Default"
expr_stmt|;
return|return
name|g_hash_table_lookup
argument_list|(
name|themes_hash
argument_list|,
name|theme_name
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|themes_apply_theme (Gimp * gimp,const gchar * theme_name)
name|themes_apply_theme
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|theme_name
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|theme_dir
decl_stmt|;
name|gchar
modifier|*
name|gtkrc_theme
decl_stmt|;
name|gchar
modifier|*
name|gtkrc_user
decl_stmt|;
name|gchar
modifier|*
name|themerc
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|theme_dir
operator|=
name|themes_get_theme_dir
argument_list|(
name|gimp
argument_list|,
name|theme_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|theme_dir
condition|)
block|{
name|gtkrc_theme
operator|=
name|g_build_filename
argument_list|(
name|theme_dir
argument_list|,
literal|"gtkrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  get the hardcoded default theme gtkrc  */
name|gtkrc_theme
operator|=
name|g_strdup
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
block|}
name|gtkrc_user
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"gtkrc"
argument_list|)
expr_stmt|;
name|themerc
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"themerc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Writing '%s'\n"
argument_list|)
argument_list|,
name|themerc
argument_list|)
expr_stmt|;
name|file
operator|=
name|fopen
argument_list|(
name|themerc
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|g_message
argument_list|(
literal|"Can't open themerc"
argument_list|)
expr_stmt|;
goto|goto
name|cleanup
goto|;
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"# GIMP themerc\n"
literal|"#\n"
literal|"# This file is written on GIMP startup and on every theme change.\n"
literal|"# It is NOT supposed to be edited manually. Edit your personal\n"
literal|"# gtkrc file instead (%s).\n"
literal|"\n"
literal|"include \"%s\"\n"
literal|"include \"%s\"\n"
literal|"\n"
literal|"# end of themerc\n"
argument_list|,
name|gtkrc_user
argument_list|,
name|gtkrc_theme
argument_list|,
name|gtkrc_user
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|cleanup
label|:
name|g_free
argument_list|(
name|gtkrc_theme
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gtkrc_user
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|themerc
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|themes_directories_foreach (const GimpDatafileData * file_data,gpointer user_data)
name|themes_directories_foreach
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Adding theme '%s' (%s)\n"
argument_list|)
argument_list|,
name|file_data
operator|->
name|basename
argument_list|,
name|file_data
operator|->
name|filename
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|themes_hash
argument_list|,
name|g_strdup
argument_list|(
name|file_data
operator|->
name|basename
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
name|file_data
operator|->
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|themes_list_themes_foreach (gpointer key,gpointer value,gpointer data)
name|themes_list_themes_foreach
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
modifier|*
name|index
init|=
name|data
decl_stmt|;
operator|*
operator|*
name|index
operator|=
name|g_strdup
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|key
argument_list|)
expr_stmt|;
operator|*
name|index
operator|=
operator|(
operator|*
name|index
operator|)
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|themes_theme_change_notify (GimpGuiConfig * config,GParamSpec * pspec,Gimp * gimp)
name|themes_theme_change_notify
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|themes_apply_theme
argument_list|(
name|gimp
argument_list|,
name|config
operator|->
name|theme
argument_list|)
expr_stmt|;
name|gtk_rc_reparse_all
argument_list|()
expr_stmt|;
block|}
end_function

end_unit


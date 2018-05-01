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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_DISABLE_DEPRECATED
end_ifdef

begin_undef
undef|#
directive|undef
name|GDK_DISABLE_DEPRECATED
end_undef

begin_endif
endif|#
directive|endif
end_endif

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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
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
name|gint
name|themes_name_compare
parameter_list|(
specifier|const
name|void
modifier|*
name|p1
parameter_list|,
specifier|const
name|void
modifier|*
name|p2
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

begin_decl_stmt
DECL|variable|themes_style_provider
specifier|static
name|GtkStyleProvider
modifier|*
name|themes_style_provider
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
name|g_object_unref
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|theme_path
condition|)
block|{
name|GList
modifier|*
name|path
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|path
operator|=
name|gimp_config_path_expand_to_files
argument_list|(
name|config
operator|->
name|theme_path
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|path
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
name|GFile
modifier|*
name|dir
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GFileEnumerator
modifier|*
name|enumerator
decl_stmt|;
name|enumerator
operator|=
name|g_file_enumerate_children
argument_list|(
name|dir
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_NAME
literal|","
name|G_FILE_ATTRIBUTE_STANDARD_IS_HIDDEN
literal|","
name|G_FILE_ATTRIBUTE_STANDARD_TYPE
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|enumerator
condition|)
block|{
name|GFileInfo
modifier|*
name|info
decl_stmt|;
while|while
condition|(
operator|(
name|info
operator|=
name|g_file_enumerator_next_file
argument_list|(
name|enumerator
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
operator|!
name|g_file_info_get_is_hidden
argument_list|(
name|info
argument_list|)
operator|&&
name|g_file_info_get_file_type
argument_list|(
name|info
argument_list|)
operator|==
name|G_FILE_TYPE_DIRECTORY
condition|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|file
operator|=
name|g_file_enumerator_get_child
argument_list|(
name|enumerator
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|name
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
literal|"Adding theme '%s' (%s)\n"
argument_list|,
name|basename
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|themes_hash
argument_list|,
name|basename
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|enumerator
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_free_full
argument_list|(
name|path
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
name|themes_style_provider
operator|=
name|GTK_STYLE_PROVIDER
argument_list|(
name|gtk_css_provider_new
argument_list|()
argument_list|)
expr_stmt|;
comment|/*  Use GTK_STYLE_PROVIDER_PRIORITY_APPLICATION + 1 so theme files    *  override default styles provided by widgets themselves.    */
name|gtk_style_context_add_provider_for_screen
argument_list|(
name|gdk_screen_get_default
argument_list|()
argument_list|,
name|themes_style_provider
argument_list|,
name|GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
operator|+
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|themes_style_provider
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
name|g_signal_connect
argument_list|(
name|config
argument_list|,
literal|"notify::prefer-dark-theme"
argument_list|,
name|G_CALLBACK
argument_list|(
name|themes_theme_change_notify
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|themes_theme_change_notify
argument_list|(
name|config
argument_list|,
name|NULL
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
name|g_clear_object
argument_list|(
operator|&
name|themes_style_provider
argument_list|)
expr_stmt|;
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
name|qsort
argument_list|(
name|themes
argument_list|,
operator|*
name|n_themes
argument_list|,
sizeof|sizeof
argument_list|(
name|gchar
operator|*
argument_list|)
argument_list|,
name|themes_name_compare
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
name|GFile
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
name|GIMP_CONFIG_DEFAULT_THEME
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
name|GFile
modifier|*
DECL|function|themes_get_theme_file (Gimp * gimp,const gchar * first_component,...)
name|themes_get_theme_file
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|first_component
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|gui_config
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|component
decl_stmt|;
name|va_list
name|args
decl_stmt|;
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
name|first_component
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gui_config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_object_ref
argument_list|(
name|themes_get_theme_dir
argument_list|(
name|gimp
argument_list|,
name|gui_config
operator|->
name|theme
argument_list|)
argument_list|)
expr_stmt|;
name|component
operator|=
name|first_component
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_component
argument_list|)
expr_stmt|;
do|do
block|{
name|GFile
modifier|*
name|tmp
init|=
name|g_file_get_child
argument_list|(
name|file
argument_list|,
name|component
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|file
operator|=
name|tmp
expr_stmt|;
block|}
do|while
condition|(
operator|(
name|component
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gchar
operator|*
argument_list|)
operator|)
condition|)
do|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_query_exists
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_object_ref
argument_list|(
name|themes_get_theme_dir
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|component
operator|=
name|first_component
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_component
argument_list|)
expr_stmt|;
do|do
block|{
name|GFile
modifier|*
name|tmp
init|=
name|g_file_get_child
argument_list|(
name|file
argument_list|,
name|component
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|file
operator|=
name|tmp
expr_stmt|;
block|}
do|while
condition|(
operator|(
name|component
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gchar
operator|*
argument_list|)
operator|)
condition|)
do|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
return|return
name|file
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
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
name|GFile
modifier|*
name|theme_css
decl_stmt|;
name|GOutputStream
modifier|*
name|output
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|theme_css
operator|=
name|gimp_directory_file
argument_list|(
literal|"theme.css"
argument_list|,
name|NULL
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
literal|"Writing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|theme_css
argument_list|)
argument_list|)
expr_stmt|;
name|output
operator|=
name|G_OUTPUT_STREAM
argument_list|(
name|g_file_replace
argument_list|(
name|theme_css
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_FILE_CREATE_NONE
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|output
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GFile
modifier|*
name|theme_dir
init|=
name|themes_get_theme_dir
argument_list|(
name|gimp
argument_list|,
name|theme_name
argument_list|)
decl_stmt|;
name|GFile
modifier|*
name|css_theme
decl_stmt|;
name|GFile
modifier|*
name|css_user
decl_stmt|;
name|gchar
modifier|*
name|esc_css_theme
decl_stmt|;
name|gchar
modifier|*
name|esc_css_user
decl_stmt|;
name|gchar
modifier|*
name|tmp
decl_stmt|;
if|if
condition|(
name|theme_dir
condition|)
block|{
name|css_theme
operator|=
name|g_file_get_child
argument_list|(
name|theme_dir
argument_list|,
literal|"gimp.css"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tmp
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"themes"
argument_list|,
literal|"Default"
argument_list|,
literal|"gimp.css"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|css_theme
operator|=
name|g_file_new_for_path
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
name|css_user
operator|=
name|gimp_directory_file
argument_list|(
literal|"gimp.css"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|g_file_get_path
argument_list|(
name|css_theme
argument_list|)
expr_stmt|;
name|esc_css_theme
operator|=
name|g_strescape
argument_list|(
name|tmp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|g_file_get_path
argument_list|(
name|css_user
argument_list|)
expr_stmt|;
name|esc_css_user
operator|=
name|g_strescape
argument_list|(
name|tmp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_output_stream_printf
argument_list|(
name|output
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|,
literal|"/* GIMP theme.css\n"
literal|" *\n"
literal|" * This file is written on GIMP startup and on every theme change.\n"
literal|" * It is NOT supposed to be edited manually. Edit your personal\n"
literal|" * gimp.css file instead (%s).\n"
literal|" */\n"
literal|"\n"
literal|"@import url(\"%s\");\n"
literal|"@import url(\"%s\");\n"
literal|"\n"
literal|"/* end of theme.css */\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|css_user
argument_list|)
argument_list|,
name|esc_css_theme
argument_list|,
name|esc_css_user
argument_list|)
operator|||
operator|!
name|g_output_stream_close
argument_list|(
name|output
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Error writing '%s': %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|theme_css
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|esc_css_theme
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|esc_css_user
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|css_theme
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|css_user
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|output
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|theme_css
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
name|gint
DECL|function|themes_name_compare (const void * p1,const void * p2)
name|themes_name_compare
parameter_list|(
specifier|const
name|void
modifier|*
name|p1
parameter_list|,
specifier|const
name|void
modifier|*
name|p2
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
operator|*
operator|(
name|char
operator|*
operator|*
operator|)
name|p1
argument_list|,
operator|*
operator|(
name|char
operator|*
operator|*
operator|)
name|p2
argument_list|)
return|;
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
name|GFile
modifier|*
name|theme_css
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gboolean
name|prefer_dark_theme
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
literal|"prefer-dark-theme"
argument_list|,
operator|&
name|prefer_dark_theme
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|gtk_settings_get_for_screen
argument_list|(
name|gdk_screen_get_default
argument_list|()
argument_list|)
argument_list|,
literal|"gtk-application-prefer-dark-theme"
argument_list|,
name|prefer_dark_theme
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|themes_apply_theme
argument_list|(
name|gimp
argument_list|,
name|config
operator|->
name|theme
argument_list|)
expr_stmt|;
name|theme_css
operator|=
name|gimp_directory_file
argument_list|(
literal|"theme.css"
argument_list|,
name|NULL
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
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|theme_css
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_css_provider_load_from_file
argument_list|(
name|GTK_CSS_PROVIDER
argument_list|(
name|themes_style_provider
argument_list|)
argument_list|,
name|theme_css
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: error parsing %s: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|theme_css
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|theme_css
argument_list|)
expr_stmt|;
name|gtk_style_context_reset_widgets
argument_list|(
name|gdk_screen_get_default
argument_list|()
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


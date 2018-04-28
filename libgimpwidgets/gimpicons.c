begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpicons.c  * Copyright (C) 2001-2015 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpicons.h"
end_include

begin_include
include|#
directive|include
file|"icons/Color/gimp-icon-pixbufs.c"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpicons  * @title: GimpIcons  * @short_description: Prebuilt common menu/toolbar items and  *                     corresponding icons  *  * GIMP registers a set of menu/toolbar items and corresponding icons  * in addition to the standard GTK+ stock items. These can be used  * just like GTK+ stock items. GIMP also overrides a few of the GTK+  * icons (namely the ones in dialog size).  *  * Stock icons may have a RTL variant which gets used for  * right-to-left locales.  **/
end_comment

begin_define
DECL|macro|LIBGIMP_DOMAIN
define|#
directive|define
name|LIBGIMP_DOMAIN
value|GETTEXT_PACKAGE "-libgimp"
end_define

begin_define
DECL|macro|GIMP_TOILET_PAPER
define|#
directive|define
name|GIMP_TOILET_PAPER
value|"gimp-toilet-paper"
end_define

begin_define
DECL|macro|GIMP_DEFAULT_ICON_THEME
define|#
directive|define
name|GIMP_DEFAULT_ICON_THEME
value|"Symbolic"
end_define

begin_decl_stmt
DECL|variable|icon_theme_path
specifier|static
name|GFile
modifier|*
name|icon_theme_path
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|default_search_path
specifier|static
name|GFile
modifier|*
name|default_search_path
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_icons_change_icon_theme (GFile * new_search_path)
name|gimp_icons_change_icon_theme
parameter_list|(
name|GFile
modifier|*
name|new_search_path
parameter_list|)
block|{
name|GFile
modifier|*
name|old_search_path
init|=
name|g_file_get_parent
argument_list|(
name|icon_theme_path
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|default_search_path
condition|)
name|default_search_path
operator|=
name|gimp_data_directory_file
argument_list|(
literal|"icons"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_equal
argument_list|(
name|new_search_path
argument_list|,
name|old_search_path
argument_list|)
condition|)
block|{
name|GtkIconTheme
modifier|*
name|icon_theme
init|=
name|gtk_icon_theme_get_default
argument_list|()
decl_stmt|;
if|if
condition|(
name|g_file_equal
argument_list|(
name|old_search_path
argument_list|,
name|default_search_path
argument_list|)
condition|)
block|{
comment|/*  if the old icon theme is in the default search path,            *  simply prepend the new theme's path            */
name|gchar
modifier|*
name|path_str
init|=
name|g_file_get_path
argument_list|(
name|new_search_path
argument_list|)
decl_stmt|;
name|gtk_icon_theme_prepend_search_path
argument_list|(
name|icon_theme
argument_list|,
name|path_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  if the old theme is not in the default search path,            *  we need to deal with the search path's first element            */
name|gchar
modifier|*
modifier|*
name|paths
decl_stmt|;
name|gint
name|n_paths
decl_stmt|;
name|gtk_icon_theme_get_search_path
argument_list|(
name|icon_theme
argument_list|,
operator|&
name|paths
argument_list|,
operator|&
name|n_paths
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_equal
argument_list|(
name|new_search_path
argument_list|,
name|default_search_path
argument_list|)
condition|)
block|{
comment|/*  when switching to a theme in the default path, remove                *  the first search path element, the default search path                *  is still in the search path                */
name|gtk_icon_theme_set_search_path
argument_list|(
name|icon_theme
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|paths
operator|+
literal|1
argument_list|,
name|n_paths
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  when switching between two non-default search paths, replace                *  the first element of the search path with the new                *  theme's path                */
name|g_free
argument_list|(
name|paths
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|paths
index|[
literal|0
index|]
operator|=
name|g_file_get_path
argument_list|(
name|new_search_path
argument_list|)
expr_stmt|;
name|gtk_icon_theme_set_search_path
argument_list|(
name|icon_theme
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|paths
argument_list|,
name|n_paths
argument_list|)
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|paths
argument_list|)
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|old_search_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_icons_notify_system_icon_theme (GObject * settings,GParamSpec * param,gpointer unused)
name|gimp_icons_notify_system_icon_theme
parameter_list|(
name|GObject
modifier|*
name|settings
parameter_list|,
name|GParamSpec
modifier|*
name|param
parameter_list|,
name|gpointer
name|unused
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
init|=
name|gdk_screen_get_default
argument_list|()
decl_stmt|;
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_screen_get_setting
argument_list|(
name|screen
argument_list|,
literal|"gtk-icon-theme-name"
argument_list|,
operator|&
name|value
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|new_system_icon_theme
init|=
name|g_value_get_string
argument_list|(
operator|&
name|value
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|cur_system_icon_theme
init|=
name|NULL
decl_stmt|;
name|g_object_get
argument_list|(
name|settings
argument_list|,
literal|"gtk-fallback-icon-theme"
argument_list|,
operator|&
name|cur_system_icon_theme
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_strcmp0
argument_list|(
name|cur_system_icon_theme
argument_list|,
name|new_system_icon_theme
argument_list|)
condition|)
block|{
name|g_object_set
argument_list|(
name|settings
argument_list|,
literal|"gtk-fallback-icon-theme"
argument_list|,
name|new_system_icon_theme
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|settings
argument_list|,
literal|"gtk-icon-theme-name"
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|cur_system_icon_theme
argument_list|)
expr_stmt|;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_icons_sanity_check (GFile * path,const gchar * theme_name)
name|gimp_icons_sanity_check
parameter_list|(
name|GFile
modifier|*
name|path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|theme_name
parameter_list|)
block|{
name|gboolean
name|exists
init|=
name|FALSE
decl_stmt|;
name|GFile
modifier|*
name|child
init|=
name|g_file_get_child
argument_list|(
name|path
argument_list|,
name|theme_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_file_query_exists
argument_list|(
name|child
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GFile
modifier|*
name|index
init|=
name|g_file_get_child
argument_list|(
name|child
argument_list|,
literal|"index.theme"
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_file_query_exists
argument_list|(
name|index
argument_list|,
name|NULL
argument_list|)
condition|)
name|exists
operator|=
name|TRUE
expr_stmt|;
else|else
name|g_printerr
argument_list|(
literal|"%s: Icon theme path has no '%s/index.theme': %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|theme_name
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|path
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|index
argument_list|)
expr_stmt|;
block|}
else|else
name|g_printerr
argument_list|(
literal|"%s: Icon theme path has no '%s' subdirectory: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|theme_name
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|path
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|child
argument_list|)
expr_stmt|;
return|return
name|exists
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_icons_set_icon_theme (GFile * path)
name|gimp_icons_set_icon_theme
parameter_list|(
name|GFile
modifier|*
name|path
parameter_list|)
block|{
name|gchar
modifier|*
name|icon_theme_name
decl_stmt|;
name|GFile
modifier|*
name|search_path
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|path
operator|==
name|NULL
operator|||
name|G_IS_FILE
argument_list|(
name|path
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|path
condition|)
name|path
operator|=
name|g_object_ref
argument_list|(
name|path
argument_list|)
expr_stmt|;
else|else
name|path
operator|=
name|gimp_data_directory_file
argument_list|(
literal|"icons"
argument_list|,
name|GIMP_DEFAULT_ICON_THEME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|search_path
operator|=
name|g_file_get_parent
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|icon_theme_name
operator|=
name|g_file_get_basename
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_icons_sanity_check
argument_list|(
name|search_path
argument_list|,
literal|"hicolor"
argument_list|)
operator|&&
name|gimp_icons_sanity_check
argument_list|(
name|search_path
argument_list|,
name|icon_theme_name
argument_list|)
condition|)
block|{
if|if
condition|(
name|icon_theme_path
condition|)
block|{
comment|/*  this is an icon theme change  */
name|gimp_icons_change_icon_theme
argument_list|(
name|search_path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_equal
argument_list|(
name|icon_theme_path
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|icon_theme_path
argument_list|)
expr_stmt|;
name|icon_theme_path
operator|=
name|g_object_ref
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|gtk_settings_get_for_screen
argument_list|(
name|gdk_screen_get_default
argument_list|()
argument_list|)
argument_list|,
literal|"gtk-icon-theme-name"
argument_list|,
name|icon_theme_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  this is the first call upon initialization  */
name|icon_theme_path
operator|=
name|g_object_ref
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|icon_theme_name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|search_path
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_icons_init:  *  * Initializes the GIMP stock icon factory.  *  * You don't need to call this function as gimp_ui_init() already does  * this for you.  */
end_comment

begin_function
name|void
DECL|function|gimp_icons_init (void)
name|gimp_icons_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|GtkSettings
modifier|*
name|settings
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|icons_dir
decl_stmt|;
name|gchar
modifier|*
name|system_icon_theme
decl_stmt|;
name|gchar
modifier|*
name|gimp_icon_theme
decl_stmt|;
if|if
condition|(
name|initialized
condition|)
return|return;
comment|/*  always prepend the default icon theme, it's never removed from    *  the path again and acts as fallback for missing icons in other    *  themes.    */
if|if
condition|(
operator|!
name|default_search_path
condition|)
name|default_search_path
operator|=
name|gimp_data_directory_file
argument_list|(
literal|"icons"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|icons_dir
operator|=
name|g_file_get_path
argument_list|(
name|default_search_path
argument_list|)
expr_stmt|;
name|gtk_icon_theme_prepend_search_path
argument_list|(
name|gtk_icon_theme_get_default
argument_list|()
argument_list|,
name|icons_dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|icons_dir
argument_list|)
expr_stmt|;
comment|/*  if an icon theme was chosen before init(), change to it  */
if|if
condition|(
name|icon_theme_path
condition|)
block|{
name|GFile
modifier|*
name|search_path
init|=
name|g_file_get_parent
argument_list|(
name|icon_theme_path
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|g_file_equal
argument_list|(
name|search_path
argument_list|,
name|default_search_path
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|icon_dir
init|=
name|g_file_get_path
argument_list|(
name|search_path
argument_list|)
decl_stmt|;
name|gtk_icon_theme_prepend_search_path
argument_list|(
name|gtk_icon_theme_get_default
argument_list|()
argument_list|,
name|icon_dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|icon_dir
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|search_path
argument_list|)
expr_stmt|;
name|gimp_icon_theme
operator|=
name|g_file_get_basename
argument_list|(
name|icon_theme_path
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_icon_theme
operator|=
name|g_strdup
argument_list|(
name|GIMP_DEFAULT_ICON_THEME
argument_list|)
expr_stmt|;
block|}
name|settings
operator|=
name|gtk_settings_get_for_screen
argument_list|(
name|gdk_screen_get_default
argument_list|()
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|settings
argument_list|,
literal|"gtk-icon-theme-name"
argument_list|,
operator|&
name|system_icon_theme
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|settings
argument_list|,
literal|"gtk-fallback-icon-theme"
argument_list|,
name|system_icon_theme
argument_list|,
literal|"gtk-icon-theme-name"
argument_list|,
name|gimp_icon_theme
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimp_icon_theme
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|system_icon_theme
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|settings
argument_list|,
literal|"notify::gtk-icon-theme-name"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_icons_notify_system_icon_theme
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_resource
argument_list|(
literal|"/org/gimp/icons/64/gimp-wilber-eek.png"
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|gtk_icon_theme_add_builtin_icon
argument_list|(
name|GIMP_ICON_WILBER_EEK
argument_list|,
literal|64
argument_list|,
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_critical
argument_list|(
literal|"Failed to create icon image: %s"
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
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

end_unit


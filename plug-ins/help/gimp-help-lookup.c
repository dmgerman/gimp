begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-help-lookup - a standalone gimp-help ID to filename mapper  * Copyright (C)  2004 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpversion.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_decl_stmt
specifier|static
name|void
name|show_version
argument_list|(
name|void
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|gchar
modifier|*
name|lookup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|help_base
specifier|static
specifier|const
name|gchar
modifier|*
name|help_base
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|help_root
specifier|static
name|gchar
modifier|*
name|help_root
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|help_locales
specifier|static
specifier|const
name|gchar
modifier|*
name|help_locales
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|help_ids
specifier|static
specifier|const
name|gchar
modifier|*
modifier|*
name|help_ids
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|entries
specifier|static
specifier|const
name|GOptionEntry
name|entries
index|[]
init|=
block|{
block|{
literal|"version"
block|,
literal|'v'
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
operator|(
name|GOptionArgFunc
operator|)
name|show_version
block|,
literal|"Show version information and exit"
block|,
name|NULL
block|}
block|,
block|{
literal|"base"
block|,
literal|'b'
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING
block|,
operator|&
name|help_base
block|,
literal|"Speficies base URI"
block|,
literal|"URI"
block|}
block|,
block|{
literal|"root"
block|,
literal|'r'
block|,
literal|0
block|,
name|G_OPTION_ARG_FILENAME
block|,
operator|&
name|help_root
block|,
literal|"Speficies root directory for index files"
block|,
literal|"DIR"
block|}
block|,
block|{
literal|"lang"
block|,
literal|'l'
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING
block|,
operator|&
name|help_locales
block|,
literal|"Specifies help language"
block|,
literal|"LANG"
block|}
block|,
block|{
name|G_OPTION_REMAINING
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING_ARRAY
block|,
operator|&
name|help_ids
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|gint
DECL|function|main (gint argc,gchar * argv[])
name|main
parameter_list|(
name|gint
name|argc
parameter_list|,
name|gchar
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|GOptionContext
modifier|*
name|context
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|help_base
operator|=
name|g_getenv
argument_list|(
name|GIMP_HELP_ENV_URI
argument_list|)
expr_stmt|;
name|help_root
operator|=
name|g_build_path
argument_list|(
name|G_DIR_SEPARATOR_S
argument_list|,
name|gimp_data_directory
argument_list|()
argument_list|,
name|GIMP_HELP_PREFIX
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|context
operator|=
name|g_option_context_new
argument_list|(
literal|"HELP-ID"
argument_list|)
expr_stmt|;
name|g_option_context_add_main_entries
argument_list|(
name|context
argument_list|,
name|entries
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_option_context_parse
argument_list|(
name|context
argument_list|,
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
if|if
condition|(
name|help_base
condition|)
name|uri
operator|=
name|g_strdup
argument_list|(
name|help_base
argument_list|)
expr_stmt|;
else|else
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|help_root
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_register_domain
argument_list|(
name|GIMP_HELP_DEFAULT_DOMAIN
argument_list|,
name|uri
argument_list|,
name|help_root
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|uri
operator|=
name|lookup
argument_list|(
name|GIMP_HELP_DEFAULT_DOMAIN
argument_list|,
name|help_locales
condition|?
name|help_locales
else|:
name|GIMP_HELP_DEFAULT_LOCALE
argument_list|,
name|help_ids
condition|?
name|help_ids
index|[
literal|0
index|]
else|:
name|GIMP_HELP_DEFAULT_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
name|g_option_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_root
argument_list|)
expr_stmt|;
return|return
name|uri
condition|?
name|EXIT_SUCCESS
else|:
name|EXIT_FAILURE
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|lookup (const gchar * help_domain,const gchar * help_locales,const gchar * help_id)
name|lookup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|GimpHelpDomain
modifier|*
name|domain
init|=
name|gimp_help_lookup_domain
argument_list|(
name|help_domain
argument_list|)
decl_stmt|;
if|if
condition|(
name|domain
condition|)
block|{
name|GList
modifier|*
name|locales
init|=
name|gimp_help_parse_locales
argument_list|(
name|help_locales
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|full_uri
init|=
name|gimp_help_domain_map
argument_list|(
name|domain
argument_list|,
name|locales
argument_list|,
name|help_id
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_list_foreach
argument_list|(
name|locales
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|locales
argument_list|)
expr_stmt|;
return|return
name|full_uri
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|show_version (void)
name|show_version
parameter_list|(
name|void
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"gimp-help-lookup version %s\n"
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis and others  *  * text.c  * Copyright (C) 2003 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangoft2.h>
end_include

begin_comment
comment|/* PangoFT2 is assumed, so we should have this in our cflags */
end_comment

begin_include
include|#
directive|include
file|<fontconfig/fontconfig.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-path.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-fonts.h"
end_include

begin_include
include|#
directive|include
file|"gimpfontlist.h"
end_include

begin_define
DECL|macro|CONF_FNAME
define|#
directive|define
name|CONF_FNAME
value|"fonts.conf"
end_define

begin_function_decl
specifier|static
name|gboolean
name|gimp_fonts_load_fonts_conf
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
name|fonts_conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_fonts_add_directories
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_fonts_init (Gimp * gimp)
name|gimp_fonts_init
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
name|gimp
operator|->
name|fonts
operator|=
name|gimp_font_list_new
argument_list|(
literal|72.0
argument_list|,
literal|72.0
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|fonts
argument_list|)
argument_list|,
literal|"fonts"
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::font-path"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_fonts_load
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fonts_load (Gimp * gimp)
name|gimp_fonts_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|FcConfig
modifier|*
name|config
decl_stmt|;
name|gchar
modifier|*
name|fonts_conf
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FONT_LIST
argument_list|(
name|gimp
operator|->
name|fonts
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_container_clear
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|gimp
operator|->
name|fonts
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|FcInitLoadConfig
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return;
name|fonts_conf
operator|=
name|gimp_personal_rc_file
argument_list|(
name|CONF_FNAME
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_fonts_load_fonts_conf
argument_list|(
name|config
argument_list|,
name|fonts_conf
argument_list|)
condition|)
return|return;
name|fonts_conf
operator|=
name|g_build_filename
argument_list|(
name|gimp_sysconf_directory
argument_list|()
argument_list|,
name|CONF_FNAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_fonts_load_fonts_conf
argument_list|(
name|config
argument_list|,
name|fonts_conf
argument_list|)
condition|)
return|return;
name|path
operator|=
name|gimp_config_path_expand
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|font_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_fonts_add_directories
argument_list|(
name|config
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|FcConfigBuildFonts
argument_list|(
name|config
argument_list|)
condition|)
block|{
name|FcConfigDestroy
argument_list|(
name|config
argument_list|)
expr_stmt|;
return|return;
block|}
name|FcConfigSetCurrent
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|gimp_font_list_restore
argument_list|(
name|GIMP_FONT_LIST
argument_list|(
name|gimp
operator|->
name|fonts
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fonts_reset (Gimp * gimp)
name|gimp_fonts_reset
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
comment|/* We clear the default config here, so any subsequent fontconfig use will    * reinit the library with defaults. (Maybe we should call FcFini here too?)    */
name|FcConfigSetCurrent
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_fonts_load_fonts_conf (FcConfig * config,gchar * fonts_conf)
name|gimp_fonts_load_fonts_conf
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
name|fonts_conf
parameter_list|)
block|{
name|gboolean
name|ret
init|=
name|TRUE
decl_stmt|;
if|if
condition|(
operator|!
name|FcConfigParseAndLoad
argument_list|(
name|config
argument_list|,
name|fonts_conf
argument_list|,
name|FcFalse
argument_list|)
condition|)
block|{
name|FcConfigDestroy
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|ret
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|fonts_conf
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fonts_add_directories (FcConfig * config,const gchar * path_str)
name|gimp_fonts_add_directories
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|)
block|{
name|GList
modifier|*
name|path
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|config
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|path_str
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_path_parse
argument_list|(
name|path_str
argument_list|,
literal|256
argument_list|,
name|TRUE
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
name|list
operator|->
name|next
control|)
name|FcConfigAppFontAddDir
argument_list|(
name|config
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


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
file|"display-types.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|FIXME #include "gui/gui-types.h"
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gui/info-window.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-title.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MAX_TITLE_BUF
define|#
directive|define
name|MAX_TITLE_BUF
value|256
end_define

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_shell_update_title_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_format_title
parameter_list|(
name|GimpDisplayShell
modifier|*
name|gdisp
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|title_len
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_update_title (GimpDisplayShell * shell)
name|gimp_display_shell_update_title
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|title_idle_id
condition|)
name|g_source_remove
argument_list|(
name|shell
operator|->
name|title_idle_id
argument_list|)
expr_stmt|;
name|shell
operator|->
name|title_idle_id
operator|=
name|g_idle_add
argument_list|(
name|gimp_display_shell_update_title_idle
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_update_title_idle (gpointer data)
name|gimp_display_shell_update_title_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpDisplayConfig
modifier|*
name|config
decl_stmt|;
name|gchar
name|title
index|[
name|MAX_TITLE_BUF
index|]
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|shell
operator|->
name|title_idle_id
operator|=
literal|0
expr_stmt|;
comment|/* format the title */
name|gimp_display_shell_format_title
argument_list|(
name|shell
argument_list|,
name|title
argument_list|,
sizeof|sizeof
argument_list|(
name|title
argument_list|)
argument_list|,
name|config
operator|->
name|image_title_format
argument_list|)
expr_stmt|;
name|gdk_window_set_title
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
operator|->
name|window
argument_list|,
name|title
argument_list|)
expr_stmt|;
comment|/* format the statusbar */
if|if
condition|(
name|strcmp
argument_list|(
name|config
operator|->
name|image_title_format
argument_list|,
name|config
operator|->
name|image_status_format
argument_list|)
condition|)
block|{
name|gimp_display_shell_format_title
argument_list|(
name|shell
argument_list|,
name|title
argument_list|,
sizeof|sizeof
argument_list|(
name|title
argument_list|)
argument_list|,
name|config
operator|->
name|image_status_format
argument_list|)
expr_stmt|;
block|}
name|gimp_statusbar_pop
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"title"
argument_list|)
expr_stmt|;
name|gimp_statusbar_push
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: dont call info_window_update() here.
endif|#
directive|endif
name|info_window_update
argument_list|(
name|shell
operator|->
name|gdisp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function_decl
specifier|static
name|gint
name|print
parameter_list|(
name|gchar
modifier|*
name|buf
parameter_list|,
name|gint
name|len
parameter_list|,
name|gint
name|start
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|4
operator|,
function_decl|5
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function
specifier|static
name|gint
DECL|function|print (gchar * buf,gint len,gint start,const gchar * fmt,...)
name|print
parameter_list|(
name|gchar
modifier|*
name|buf
parameter_list|,
name|gint
name|len
parameter_list|,
name|gint
name|start
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gint
name|printed
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|printed
operator|=
name|g_vsnprintf
argument_list|(
name|buf
operator|+
name|start
argument_list|,
name|len
operator|-
name|start
argument_list|,
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|printed
operator|<
literal|0
condition|)
name|printed
operator|=
name|len
operator|-
name|start
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|printed
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_format_title (GimpDisplayShell * shell,gchar * title,gint title_len,const gchar * format)
name|gimp_display_shell_format_title
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|title_len
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gchar
modifier|*
name|image_type_str
init|=
name|NULL
decl_stmt|;
name|gboolean
name|empty
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gchar
name|unit_format
index|[
literal|8
index|]
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|empty
operator|=
name|gimp_image_is_empty
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|image_type_str
operator|=
name|empty
condition|?
name|_
argument_list|(
literal|"RGB-empty"
argument_list|)
else|:
name|_
argument_list|(
literal|"RGB"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|image_type_str
operator|=
name|empty
condition|?
name|_
argument_list|(
literal|"grayscale-empty"
argument_list|)
else|:
name|_
argument_list|(
literal|"grayscale"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|image_type_str
operator|=
name|empty
condition|?
name|_
argument_list|(
literal|"indexed-empty"
argument_list|)
else|:
name|_
argument_list|(
literal|"indexed"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
name|i
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|i
operator|<
name|title_len
operator|&&
operator|*
name|format
condition|)
block|{
switch|switch
condition|(
operator|*
name|format
condition|)
block|{
case|case
literal|'%'
case|:
name|format
operator|++
expr_stmt|;
switch|switch
condition|(
operator|*
name|format
condition|)
block|{
case|case
literal|0
case|:
name|g_warning
argument_list|(
literal|"image-title-format string ended within %%-sequence"
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'%'
case|:
name|title
index|[
name|i
operator|++
index|]
operator|=
literal|'%'
expr_stmt|;
break|break;
case|case
literal|'f'
case|:
comment|/* pruned filename */
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|basename
operator|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|'F'
case|:
comment|/* full filename */
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|'p'
case|:
comment|/* PDB id */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'i'
case|:
comment|/* instance */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|instance
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'t'
case|:
comment|/* type */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|image_type_str
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'s'
case|:
comment|/* user source zoom factor */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
name|SCALESRC
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'d'
case|:
comment|/* user destination zoom factor */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
name|SCALEDEST
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'z'
case|:
comment|/* user zoom factor (percentage) */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
literal|100
operator|*
name|SCALEDEST
argument_list|(
name|shell
argument_list|)
operator|/
name|SCALESRC
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'D'
case|:
comment|/* dirty flag */
if|if
condition|(
name|format
index|[
literal|1
index|]
operator|==
literal|0
condition|)
block|{
name|g_warning
argument_list|(
literal|"image-title-format string ended within "
literal|"%%D-sequence"
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|gimage
operator|->
name|dirty
condition|)
name|title
index|[
name|i
operator|++
index|]
operator|=
name|format
index|[
literal|1
index|]
expr_stmt|;
name|format
operator|++
expr_stmt|;
break|break;
case|case
literal|'C'
case|:
comment|/* clean flag */
if|if
condition|(
name|format
index|[
literal|1
index|]
operator|==
literal|0
condition|)
block|{
name|g_warning
argument_list|(
literal|"image-title-format string ended within "
literal|"%%C-sequence"
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|gimage
operator|->
name|dirty
condition|)
name|title
index|[
name|i
operator|++
index|]
operator|=
name|format
index|[
literal|1
index|]
expr_stmt|;
name|format
operator|++
expr_stmt|;
break|break;
case|case
literal|'m'
case|:
comment|/* memory used by image */
block|{
name|gulong
name|memsize
decl_stmt|;
name|gchar
modifier|*
name|memsize_str
decl_stmt|;
name|memsize
operator|=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|memsize_str
operator|=
name|gimp_memsize_to_string
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|memsize_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|memsize_str
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|'l'
case|:
comment|/* number of layers */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
name|gimp_container_num_children
argument_list|(
name|gimage
operator|->
name|layers
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'L'
case|:
comment|/* active drawable name */
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|_
argument_list|(
literal|"(none)"
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|'w'
case|:
comment|/* width in pixels */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'W'
case|:
comment|/* width in real-world units */
name|g_snprintf
argument_list|(
name|unit_format
argument_list|,
sizeof|sizeof
argument_list|(
name|unit_format
argument_list|)
argument_list|,
literal|"%%.%df"
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|gimage
operator|->
name|unit
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
name|unit_format
argument_list|,
operator|(
name|gimage
operator|->
name|width
operator|*
name|gimp_unit_get_factor
argument_list|(
name|gimage
operator|->
name|unit
argument_list|)
operator|/
name|gimage
operator|->
name|xresolution
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'h'
case|:
comment|/* height in pixels */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%d"
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'H'
case|:
comment|/* height in real-world units */
name|g_snprintf
argument_list|(
name|unit_format
argument_list|,
sizeof|sizeof
argument_list|(
name|unit_format
argument_list|)
argument_list|,
literal|"%%.%df"
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|gimage
operator|->
name|unit
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
name|unit_format
argument_list|,
operator|(
name|gimage
operator|->
name|height
operator|*
name|gimp_unit_get_factor
argument_list|(
name|gimage
operator|->
name|unit
argument_list|)
operator|/
name|gimage
operator|->
name|yresolution
operator|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'u'
case|:
comment|/* unit symbol */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|gimp_unit_get_symbol
argument_list|(
name|gimage
operator|->
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'U'
case|:
comment|/* unit abbreviation */
name|i
operator|+=
name|print
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|gimp_unit_get_abbreviation
argument_list|(
name|gimage
operator|->
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
comment|/* Other cool things to be added: 	       * %r = xresolution                * %R = yresolution                * %ø = image's fractal dimension                * %þ = the answer to everything 	       */
default|default:
name|g_warning
argument_list|(
literal|"image-title-format contains unknown "
literal|"format sequence '%%%c'"
argument_list|,
operator|*
name|format
argument_list|)
expr_stmt|;
break|break;
block|}
break|break;
default|default:
name|title
index|[
name|i
operator|++
index|]
operator|=
operator|*
name|format
expr_stmt|;
break|break;
block|}
name|format
operator|++
expr_stmt|;
block|}
name|title
index|[
name|MIN
argument_list|(
name|i
argument_list|,
name|title_len
operator|-
literal|1
argument_list|)
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
end_function

end_unit


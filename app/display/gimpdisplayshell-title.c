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
file|<string.h>
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
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
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"file/gimp-file.h"
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
file|"about.h"
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
value|512
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
name|gint
name|gimp_display_shell_format_title
parameter_list|(
name|GimpDisplayShell
modifier|*
name|display
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

begin_function_decl
specifier|static
name|gint
name|gimp_display_shell_format_filename
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
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_title_update (GimpDisplayShell * shell)
name|gimp_display_shell_title_update
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
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|shell
operator|->
name|title_idle_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|image
condition|)
block|{
name|GimpDisplayConfig
modifier|*
name|config
init|=
name|shell
operator|->
name|display
operator|->
name|config
decl_stmt|;
name|gchar
name|title
index|[
name|MAX_TITLE_BUF
index|]
decl_stmt|;
name|gchar
name|status
index|[
name|MAX_TITLE_BUF
index|]
decl_stmt|;
name|gint
name|len
decl_stmt|;
comment|/* format the title */
name|len
operator|=
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
if|if
condition|(
name|len
condition|)
comment|/* U+2013 EN DASH */
name|len
operator|+=
name|g_strlcpy
argument_list|(
name|title
operator|+
name|len
argument_list|,
literal|" \342\200\223 "
argument_list|,
sizeof|sizeof
argument_list|(
name|title
argument_list|)
operator|-
name|len
argument_list|)
expr_stmt|;
name|g_strlcpy
argument_list|(
name|title
operator|+
name|len
argument_list|,
name|GIMP_ACRONYM
argument_list|,
sizeof|sizeof
argument_list|(
name|title
argument_list|)
operator|-
name|len
argument_list|)
expr_stmt|;
comment|/* format the statusbar */
name|gimp_display_shell_format_title
argument_list|(
name|shell
argument_list|,
name|status
argument_list|,
sizeof|sizeof
argument_list|(
name|status
argument_list|)
argument_list|,
name|config
operator|->
name|image_status_format
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|shell
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"status"
argument_list|,
name|status
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_set
argument_list|(
name|shell
argument_list|,
literal|"title"
argument_list|,
name|GIMP_NAME
argument_list|,
literal|"status"
argument_list|,
literal|" "
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_display_shell_title_image_type (GimpImage * image)
name|gimp_display_shell_title_image_type
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
literal|""
decl_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_IMAGE_BASE_TYPE
argument_list|,
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_display_shell_title_drawable_type (GimpDrawable * drawable)
name|gimp_display_shell_title_drawable_type
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
literal|""
decl_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_IMAGE_TYPE
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|name
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
name|gint
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
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|num
decl_stmt|,
name|denom
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|image
operator|=
name|shell
operator|->
name|display
operator|->
name|image
expr_stmt|;
name|gimp
operator|=
name|shell
operator|->
name|display
operator|->
name|gimp
expr_stmt|;
if|if
condition|(
operator|!
name|image
condition|)
block|{
name|title
index|[
literal|0
index|]
operator|=
literal|'\n'
expr_stmt|;
return|return
literal|0
return|;
block|}
name|gimp_zoom_model_get_fraction
argument_list|(
name|shell
operator|->
name|zoom
argument_list|,
operator|&
name|num
argument_list|,
operator|&
name|denom
argument_list|)
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
comment|/* format string ends within %-sequence, print literal '%' */
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
comment|/* base filename */
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|i
operator|+=
name|gimp_display_shell_format_filename
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
name|image
argument_list|,
name|name
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
specifier|const
name|gchar
modifier|*
name|uri
init|=
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|i
operator|+=
name|gimp_display_shell_format_filename
argument_list|(
name|title
argument_list|,
name|title_len
argument_list|,
name|i
argument_list|,
name|image
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
name|image
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
name|gimp_display_get_instance
argument_list|(
name|shell
operator|->
name|display
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'t'
case|:
comment|/* image type */
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
name|gimp_display_shell_title_image_type
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'T'
case|:
comment|/* drawable type */
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
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
name|gimp_display_shell_title_drawable_type
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
name|denom
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
name|num
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'z'
case|:
comment|/* user zoom factor (percentage) */
block|{
name|gdouble
name|scale
init|=
name|gimp_zoom_model_get_factor
argument_list|(
name|shell
operator|->
name|zoom
argument_list|)
decl_stmt|;
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
name|scale
operator|>=
literal|0.15
condition|?
literal|"%.0f"
else|:
literal|"%.2f"
argument_list|,
literal|100.0
operator|*
name|scale
argument_list|)
expr_stmt|;
block|}
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
comment|/* format string ends within %D-sequence, print literal '%D' */
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
literal|"%%D"
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|gimp_image_is_dirty
argument_list|(
name|image
argument_list|)
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
comment|/* format string ends within %C-sequence, print literal '%C' */
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
literal|"%%C"
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|gimp_image_is_dirty
argument_list|(
name|image
argument_list|)
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
literal|'B'
case|:
comment|/* dirty flag (long) */
if|if
condition|(
name|gimp_image_is_dirty
argument_list|(
name|image
argument_list|)
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
name|_
argument_list|(
literal|"(modified)"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'A'
case|:
comment|/* clean flag (long) */
if|if
condition|(
operator|!
name|gimp_image_is_dirty
argument_list|(
name|image
argument_list|)
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
name|_
argument_list|(
literal|"(clean)"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'m'
case|:
comment|/* memory used by image */
block|{
name|GimpObject
modifier|*
name|object
init|=
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|str
operator|=
name|g_format_size_for_display
argument_list|(
name|gimp_object_get_memsize
argument_list|(
name|object
argument_list|,
name|NULL
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
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
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
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'L'
case|:
comment|/* number of layers (long) */
block|{
name|gint
name|num
init|=
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
decl_stmt|;
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
name|ngettext
argument_list|(
literal|"%d layer"
argument_list|,
literal|"%d layers"
argument_list|,
name|num
argument_list|)
argument_list|,
name|num
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|'n'
case|:
comment|/* active drawable name */
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|gchar
modifier|*
name|desc
decl_stmt|;
name|desc
operator|=
name|gimp_viewable_get_description
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
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
name|desc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
block|}
break|break;
case|case
literal|'P'
case|:
comment|/* active drawable PDB id */
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
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
literal|"%d"
argument_list|,
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
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
literal|'W'
case|:
comment|/* width in real-world units */
if|if
condition|(
name|shell
operator|->
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gchar
name|unit_format
index|[
literal|8
index|]
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
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
name|_gimp_unit_get_digits
argument_list|(
name|gimp
argument_list|,
name|shell
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
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|*
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
name|shell
operator|->
name|unit
argument_list|)
operator|/
name|xres
operator|)
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* else fallthru */
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
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'H'
case|:
comment|/* height in real-world units */
if|if
condition|(
name|shell
operator|->
name|unit
operator|!=
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gchar
name|unit_format
index|[
literal|8
index|]
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
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
name|_gimp_unit_get_digits
argument_list|(
name|gimp
argument_list|,
name|shell
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
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|*
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
name|shell
operator|->
name|unit
argument_list|)
operator|/
name|yres
operator|)
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* else fallthru */
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
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
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
name|_gimp_unit_get_symbol
argument_list|(
name|gimp
argument_list|,
name|shell
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
name|_gimp_unit_get_abbreviation
argument_list|(
name|gimp
argument_list|,
name|shell
operator|->
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
comment|/* Other cool things to be added:                * %r = xresolution                * %R = yresolution                * %ø = image's fractal dimension                * %þ = the answer to everything                */
default|default:
comment|/* format string contains unknown %-sequence, print it literally */
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
literal|"%%%c"
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
return|return
name|i
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_display_shell_format_filename (gchar * buf,gint len,gint start,GimpImage * image,const gchar * filename)
name|gimp_display_shell_format_filename
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
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|source
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name_format
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|export_status
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|format_string
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|gboolean
name|is_imported
init|=
name|FALSE
decl_stmt|;
name|gint
name|incr
init|=
literal|0
decl_stmt|;
name|source
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_FILE_IMPORT_SOURCE_URI_KEY
argument_list|)
expr_stmt|;
comment|/* Note that as soon as the image is saved, it is not considered    * imported any longer (GIMP_FILE_IMPORT_SOURCE_URI_KEY is set to    * NULL)    */
name|is_imported
operator|=
operator|(
name|source
operator|!=
name|NULL
operator|)
expr_stmt|;
comment|/* Calculate filename and format */
if|if
condition|(
operator|!
name|is_imported
condition|)
block|{
name|name
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|name_format
operator|=
literal|"%s"
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|source_no_ext
init|=
name|file_utils_uri_with_new_ext
argument_list|(
name|source
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|name
operator|=
name|file_utils_uri_display_basename
argument_list|(
name|source_no_ext
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|source_no_ext
argument_list|)
expr_stmt|;
name|name_format
operator|=
literal|"[%s]"
expr_stmt|;
block|}
comment|/* Calculate filename suffix */
if|if
condition|(
operator|!
name|gimp_image_is_export_dirty
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|gboolean
name|is_exported
decl_stmt|;
name|is_exported
operator|=
operator|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_FILE_EXPORT_TO_URI_KEY
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
if|if
condition|(
name|is_exported
condition|)
name|export_status
operator|=
name|_
argument_list|(
literal|" (exported)"
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|is_imported
condition|)
name|export_status
operator|=
name|_
argument_list|(
literal|" (overwritten)"
argument_list|)
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"Unexpected code path, Save+export implementation is buggy!"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|is_imported
condition|)
block|{
name|export_status
operator|=
name|_
argument_list|(
literal|" (imported)"
argument_list|)
expr_stmt|;
block|}
comment|/* Merge strings and print the result */
name|format_string
operator|=
name|g_strconcat
argument_list|(
name|name_format
argument_list|,
name|export_status
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|incr
operator|=
name|print
argument_list|(
name|buf
argument_list|,
name|len
argument_list|,
name|start
argument_list|,
name|format_string
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|format_string
argument_list|)
expr_stmt|;
comment|/* Cleanup */
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|incr
return|;
block|}
end_function

end_unit


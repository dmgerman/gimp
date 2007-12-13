begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimprender.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_render_setup_notify
parameter_list|(
name|gpointer
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  accelerate transparency of image scaling  */
end_comment

begin_decl_stmt
DECL|variable|gimp_render_dark_check
name|guchar
name|gimp_render_dark_check
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_render_light_check
name|guchar
name|gimp_render_light_check
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_render_check_buf
name|guchar
modifier|*
name|gimp_render_check_buf
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_render_empty_buf
name|guchar
modifier|*
name|gimp_render_empty_buf
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_render_white_buf
name|guchar
modifier|*
name|gimp_render_white_buf
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_render_blend_dark_check
name|guchar
modifier|*
name|gimp_render_blend_dark_check
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_render_blend_light_check
name|guchar
modifier|*
name|gimp_render_blend_light_check
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_render_blend_white
name|guchar
modifier|*
name|gimp_render_blend_white
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_render_init (Gimp * gimp)
name|gimp_render_init
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
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::transparency-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_render_setup_notify
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|gimp_render_setup_notify
argument_list|(
name|gimp
operator|->
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
DECL|function|gimp_render_exit (Gimp * gimp)
name|gimp_render_exit
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
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
name|gimp_render_setup_notify
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_render_blend_dark_check
condition|)
block|{
name|g_free
argument_list|(
name|gimp_render_blend_dark_check
argument_list|)
expr_stmt|;
name|gimp_render_blend_dark_check
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp_render_blend_light_check
condition|)
block|{
name|g_free
argument_list|(
name|gimp_render_blend_light_check
argument_list|)
expr_stmt|;
name|gimp_render_blend_light_check
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp_render_blend_white
condition|)
block|{
name|g_free
argument_list|(
name|gimp_render_blend_white
argument_list|)
expr_stmt|;
name|gimp_render_blend_white
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp_render_check_buf
condition|)
block|{
name|g_free
argument_list|(
name|gimp_render_check_buf
argument_list|)
expr_stmt|;
name|gimp_render_check_buf
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp_render_empty_buf
condition|)
block|{
name|g_free
argument_list|(
name|gimp_render_empty_buf
argument_list|)
expr_stmt|;
name|gimp_render_empty_buf
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp_render_white_buf
condition|)
block|{
name|g_free
argument_list|(
name|gimp_render_white_buf
argument_list|)
expr_stmt|;
name|gimp_render_white_buf
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_render_setup_notify (gpointer config,GParamSpec * param_spec,Gimp * gimp)
name|gimp_render_setup_notify
parameter_list|(
name|gpointer
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpCheckType
name|check_type
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
literal|"transparency-type"
argument_list|,
operator|&
name|check_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_checks_get_shades
argument_list|(
name|check_type
argument_list|,
operator|&
name|gimp_render_light_check
argument_list|,
operator|&
name|gimp_render_dark_check
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_render_blend_dark_check
condition|)
name|gimp_render_blend_dark_check
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|65536
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_render_blend_light_check
condition|)
name|gimp_render_blend_light_check
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|65536
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_render_blend_white
condition|)
name|gimp_render_blend_white
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|65536
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|256
condition|;
name|j
operator|++
control|)
block|{
name|gimp_render_blend_dark_check
index|[
operator|(
name|i
operator|<<
literal|8
operator|)
operator|+
name|j
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|j
operator|*
name|i
operator|+
name|gimp_render_dark_check
operator|*
operator|(
literal|255
operator|-
name|i
operator|)
operator|)
operator|/
literal|255
argument_list|)
expr_stmt|;
name|gimp_render_blend_light_check
index|[
operator|(
name|i
operator|<<
literal|8
operator|)
operator|+
name|j
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|j
operator|*
name|i
operator|+
name|gimp_render_light_check
operator|*
operator|(
literal|255
operator|-
name|i
operator|)
operator|)
operator|/
literal|255
argument_list|)
expr_stmt|;
name|gimp_render_blend_white
index|[
operator|(
name|i
operator|<<
literal|8
operator|)
operator|+
name|j
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
name|j
operator|*
name|i
operator|+
literal|255
operator|*
operator|(
literal|255
operator|-
name|i
operator|)
operator|)
operator|/
literal|255
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|gimp_render_check_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimp_render_empty_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimp_render_white_buf
argument_list|)
expr_stmt|;
DECL|macro|BUF_SIZE
define|#
directive|define
name|BUF_SIZE
value|(MAX (GIMP_RENDER_BUF_WIDTH, \                        GIMP_VIEWABLE_MAX_PREVIEW_SIZE) + 4)
name|gimp_render_check_buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|BUF_SIZE
operator|*
literal|3
argument_list|)
expr_stmt|;
name|gimp_render_empty_buf
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|BUF_SIZE
operator|*
literal|3
argument_list|)
expr_stmt|;
name|gimp_render_white_buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|BUF_SIZE
operator|*
literal|3
argument_list|)
expr_stmt|;
comment|/*  calculate check buffer for previews  */
name|memset
argument_list|(
name|gimp_render_white_buf
argument_list|,
literal|255
argument_list|,
name|BUF_SIZE
operator|*
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|BUF_SIZE
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|&
literal|0x4
condition|)
block|{
name|gimp_render_check_buf
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|gimp_render_dark_check
expr_stmt|;
name|gimp_render_check_buf
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|gimp_render_dark_check
expr_stmt|;
name|gimp_render_check_buf
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|gimp_render_dark_check
expr_stmt|;
block|}
else|else
block|{
name|gimp_render_check_buf
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|gimp_render_light_check
expr_stmt|;
name|gimp_render_check_buf
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|gimp_render_light_check
expr_stmt|;
name|gimp_render_check_buf
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|gimp_render_light_check
expr_stmt|;
block|}
block|}
undef|#
directive|undef
name|BUF_SIZE
block|}
end_function

end_unit


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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"datafiles.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatalist.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"patterns.h"
end_include

begin_include
include|#
directive|include
file|"pattern_select.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|patterns_load_pattern
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gpointer
name|loader_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|global_pattern_list
name|GimpContainer
modifier|*
name|global_pattern_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|patterns_init (gboolean no_data)
name|patterns_init
parameter_list|(
name|gboolean
name|no_data
parameter_list|)
block|{
if|if
condition|(
name|global_pattern_list
condition|)
name|patterns_free
argument_list|()
expr_stmt|;
else|else
name|global_pattern_list
operator|=
name|GIMP_CONTAINER
argument_list|(
name|gimp_data_list_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern_path
operator|!=
name|NULL
operator|&&
operator|!
name|no_data
condition|)
block|{
name|pattern_select_freeze_all
argument_list|()
expr_stmt|;
name|datafiles_read_directories
argument_list|(
name|pattern_path
argument_list|,
literal|0
argument_list|,
name|patterns_load_pattern
argument_list|,
name|global_pattern_list
argument_list|)
expr_stmt|;
name|pattern_select_thaw_all
argument_list|()
expr_stmt|;
block|}
name|gimp_context_refresh_patterns
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|patterns_free (void)
name|patterns_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|global_pattern_list
condition|)
return|return;
name|pattern_select_freeze_all
argument_list|()
expr_stmt|;
name|gimp_data_list_save_and_clear
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|global_pattern_list
argument_list|)
argument_list|,
name|pattern_path
argument_list|,
name|GIMP_PATTERN_FILE_EXTENSION
argument_list|)
expr_stmt|;
name|pattern_select_thaw_all
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|GimpPattern
modifier|*
DECL|function|patterns_get_standard_pattern (void)
name|patterns_get_standard_pattern
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpPattern
modifier|*
name|standard_pattern
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_pattern
condition|)
block|{
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|standard_pattern
operator|=
name|GIMP_PATTERN
argument_list|(
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|standard_pattern
argument_list|)
argument_list|,
literal|"Standard"
argument_list|)
expr_stmt|;
name|standard_pattern
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
literal|32
argument_list|,
literal|32
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|temp_buf_data
argument_list|(
name|standard_pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|standard_pattern
operator|->
name|mask
operator|->
name|height
condition|;
name|row
operator|++
control|)
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|standard_pattern
operator|->
name|mask
operator|->
name|width
condition|;
name|col
operator|++
control|)
block|{
name|memset
argument_list|(
name|data
argument_list|,
operator|(
name|col
operator|%
literal|2
operator|)
operator|&&
operator|(
name|row
operator|%
literal|2
operator|)
condition|?
literal|255
else|:
literal|0
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|data
operator|+=
literal|3
expr_stmt|;
block|}
comment|/*  set ref_count to 2 --> never swap the standard pattern  */
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|standard_pattern
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|standard_pattern
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|standard_pattern
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_pattern
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|patterns_load_pattern (const gchar * filename,gpointer loader_data)
name|patterns_load_pattern
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gpointer
name|loader_data
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|datafiles_check_extension
argument_list|(
name|filename
argument_list|,
name|GIMP_PATTERN_FILE_EXTENSION
argument_list|)
condition|)
block|{
name|pattern
operator|=
name|gimp_pattern_load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Warning: Failed to load pattern\n\"%s\""
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
else|else
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|loader_data
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|pattern
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


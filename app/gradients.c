begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURIGHTE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gradients.h"
end_include

begin_include
include|#
directive|include
file|"gradient_select.h"
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
name|gradients_load_gradient
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
DECL|variable|global_gradient_list
name|GimpContainer
modifier|*
name|global_gradient_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gradients_init (gint no_data)
name|gradients_init
parameter_list|(
name|gint
name|no_data
parameter_list|)
block|{
if|if
condition|(
name|global_gradient_list
condition|)
name|gradients_free
argument_list|()
expr_stmt|;
else|else
name|global_gradient_list
operator|=
name|GIMP_CONTAINER
argument_list|(
name|gimp_data_list_new
argument_list|(
name|GIMP_TYPE_GRADIENT
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient_path
operator|!=
name|NULL
operator|&&
operator|!
name|no_data
condition|)
block|{
name|gradient_select_freeze_all
argument_list|()
expr_stmt|;
name|datafiles_read_directories
argument_list|(
name|gradient_path
argument_list|,
literal|0
argument_list|,
name|gradients_load_gradient
argument_list|,
name|global_gradient_list
argument_list|)
expr_stmt|;
name|gradient_select_thaw_all
argument_list|()
expr_stmt|;
block|}
name|gimp_context_refresh_gradients
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gradients_free (void)
name|gradients_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|global_gradient_list
condition|)
return|return;
name|gradient_select_freeze_all
argument_list|()
expr_stmt|;
name|gimp_data_list_save_and_clear
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|global_gradient_list
argument_list|)
argument_list|,
name|gradient_path
argument_list|,
name|GIMP_GRADIENT_FILE_EXTENSION
argument_list|)
expr_stmt|;
name|gradient_select_thaw_all
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|GimpGradient
modifier|*
DECL|function|gradients_get_standard_gradient (void)
name|gradients_get_standard_gradient
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpGradient
modifier|*
name|standard_gradient
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_gradient
condition|)
block|{
name|standard_gradient
operator|=
name|gimp_gradient_new
argument_list|(
literal|"Standard"
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|standard_gradient
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|standard_gradient
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_gradient
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gradients_load_gradient (const gchar * filename,gpointer loader_data)
name|gradients_load_gradient
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
name|GimpGradient
modifier|*
name|gradient
init|=
name|NULL
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
operator|!
name|datafiles_check_extension
argument_list|(
name|filename
argument_list|,
name|GIMP_GRADIENT_FILE_EXTENSION
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s(): trying old gradient file format on file with "
literal|"unknown extension: %s"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
name|gradient
operator|=
name|gimp_gradient_load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gradient
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Warning: Failed to load gradient\n\"%s\""
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
name|gradient
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


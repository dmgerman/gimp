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
file|"context_manager.h"
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
name|gradients_free
argument_list|()
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
name|gimp_data_list_load
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|global_gradient_list
argument_list|)
argument_list|,
name|gradient_path
argument_list|,
operator|(
name|GimpDataObjectLoaderFunc
operator|)
name|gimp_gradient_load
argument_list|,
name|GIMP_GRADIENT_FILE_EXTENSION
argument_list|,
operator|(
name|GimpDataObjectLoaderFunc
operator|)
name|gimp_gradient_load
argument_list|,
name|NULL
comment|/* legacy loader */
argument_list|)
expr_stmt|;
block|}
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
name|gimp_container_num_children
argument_list|(
name|global_gradient_list
argument_list|)
operator|==
literal|0
condition|)
return|return;
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

end_unit


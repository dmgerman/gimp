begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpargument.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
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

begin_decl_stmt
DECL|variable|display_new_proc
specifier|static
name|GimpProcedure
name|display_new_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_delete_proc
specifier|static
name|GimpProcedure
name|display_delete_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_get_window_handle_proc
specifier|static
name|GimpProcedure
name|display_get_window_handle_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|displays_flush_proc
specifier|static
name|GimpProcedure
name|displays_flush_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|displays_reconnect_proc
specifier|static
name|GimpProcedure
name|displays_reconnect_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_display_procs (Gimp * gimp)
name|register_display_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * display_new    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|display_new_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_DISPLAY
argument_list|,
name|gimp_param_spec_display_id
argument_list|(
literal|"display"
argument_list|,
literal|"display"
argument_list|,
literal|"The new display"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * display_delete    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|display_delete_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_DISPLAY
argument_list|,
name|gimp_param_spec_display_id
argument_list|(
literal|"display"
argument_list|,
literal|"display"
argument_list|,
literal|"The display to delete"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * display_get_window_handle    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|display_get_window_handle_proc
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_DISPLAY
argument_list|,
name|gimp_param_spec_display_id
argument_list|(
literal|"display"
argument_list|,
literal|"display"
argument_list|,
literal|"The display to get the window handle from"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"window"
argument_list|,
literal|"window"
argument_list|,
literal|"The native window handle or 0"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * displays_flush    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|displays_flush_proc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * displays_reconnect    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|displays_reconnect_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"old-image"
argument_list|,
literal|"old image"
argument_list|,
literal|"The old image (must have at least one display)"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"new-image"
argument_list|,
literal|"new image"
argument_list|,
literal|"The new image (must not have a display)"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|display_new_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|display_new_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpArgument
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpObject
modifier|*
name|display
init|=
name|NULL
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|display
operator|=
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
condition|)
block|{
comment|/* the first display takes ownership of the image */
if|if
condition|(
name|image
operator|->
name|disp_count
operator|==
literal|1
condition|)
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_value_set_display
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|display
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|display_new_proc
specifier|static
name|GimpProcedure
name|display_new_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-display-new"
block|,
literal|"gimp-display-new"
block|,
literal|"Create a new display for the specified image."
block|,
literal|"Creates a new display for the specified image. If the image already has a display, another is added. Multiple displays are handled transparently by the GIMP. The newly created display is returned and can be subsequently destroyed with a call to 'gimp-display-delete'. This procedure only makes sense for use with the GIMP UI."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|display_new_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|display_delete_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|display_delete_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpObject
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gimp_value_get_display
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|gimp_delete_display
argument_list|(
name|gimp
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|display_delete_proc
specifier|static
name|GimpProcedure
name|display_delete_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-display-delete"
block|,
literal|"gimp-display-delete"
block|,
literal|"Delete the specified display."
block|,
literal|"This procedure removes the specified display. If this is the last remaining display for the underlying image, then the image is deleted also."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|display_delete_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|display_get_window_handle_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|display_get_window_handle_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpArgument
modifier|*
name|return_vals
decl_stmt|;
name|GimpObject
modifier|*
name|display
decl_stmt|;
name|gint32
name|window
init|=
literal|0
decl_stmt|;
name|display
operator|=
name|gimp_value_get_display
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|window
operator|=
operator|(
name|gint32
operator|)
name|gimp_get_display_window
argument_list|(
name|gimp
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|window
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|display_get_window_handle_proc
specifier|static
name|GimpProcedure
name|display_get_window_handle_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-display-get-window-handle"
block|,
literal|"gimp-display-get-window-handle"
block|,
literal|"Get a handle to the native window for an image display."
block|,
literal|"This procedure returns a handle to the native window for a given image display. For example in the X backend of GDK, a native window handle is an Xlib XID. A value of 0 is returned for an invalid display or if this function is unimplemented for the windowing system that is being used."
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"Sven Neumann"
block|,
literal|"2005"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|display_get_window_handle_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|displays_flush_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|displays_flush_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gimp_container_foreach
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_image_flush
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|displays_flush_proc
specifier|static
name|GimpProcedure
name|displays_flush_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-displays-flush"
block|,
literal|"gimp-displays-flush"
block|,
literal|"Flush all internal changes to the user interface"
block|,
literal|"This procedure takes no arguments and returns nothing except a success status. Its purpose is to flush all pending updates of image manipulations to the user interface. It should be called whenever appropriate."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|displays_flush_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|displays_reconnect_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|displays_reconnect_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpImage
modifier|*
name|old_image
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
name|old_image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|new_image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|success
operator|=
operator|(
name|old_image
operator|!=
name|new_image
operator|&&
name|old_image
operator|->
name|disp_count
operator|>
literal|0
operator|&&
name|new_image
operator|->
name|disp_count
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|gimp_reconnect_displays
argument_list|(
name|gimp
argument_list|,
name|old_image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
comment|/* take ownership of the image */
if|if
condition|(
name|new_image
operator|->
name|disp_count
operator|>
literal|0
condition|)
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|displays_reconnect_proc
specifier|static
name|GimpProcedure
name|displays_reconnect_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-displays-reconnect"
block|,
literal|"gimp-displays-reconnect"
block|,
literal|"Reconnect displays from one image to another image."
block|,
literal|"This procedure connects all displays of the old_image to the new_image. If the old_image has no display or new_image already has a display the reconnect is not performed and the procedure returns without success. You should rarely need to use this function."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|displays_reconnect_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit


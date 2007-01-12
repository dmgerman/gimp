begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdisplay_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_display_is_valid:  * @display_ID: The display to check.  *  * Returns TRUE if the display is valid.  *  * This procedure checks if the given display ID is valid and refers to  * an existing display.  *  * Returns: Whether the display ID is valid.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_display_is_valid (gint32 display_ID)
name|gimp_display_is_valid
parameter_list|(
name|gint32
name|display_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|valid
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-display-is-valid"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DISPLAY
argument_list|,
name|display_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|valid
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|valid
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_new:  * @image_ID: The image.  *  * Create a new display for the specified image.  *  * Creates a new display for the specified image. If the image already  * has a display, another is added. Multiple displays are handled  * transparently by the GIMP. The newly created display is returned and  * can be subsequently destroyed with a call to gimp_display_delete().  * This procedure only makes sense for use with the GIMP UI.  *  * Returns: The new display.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_display_new (gint32 image_ID)
name|gimp_display_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|display_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-display-new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|display_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_display
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|display_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_delete:  * @display_ID: The display to delete.  *  * Delete the specified display.  *  * This procedure removes the specified display. If this is the last  * remaining display for the underlying image, then the image is  * deleted also.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_display_delete (gint32 display_ID)
name|gimp_display_delete
parameter_list|(
name|gint32
name|display_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-display-delete"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DISPLAY
argument_list|,
name|display_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_get_window_handle:  * @display_ID: The display to get the window handle from.  *  * Get a handle to the native window for an image display.  *  * This procedure returns a handle to the native window for a given  * image display. For example in the X backend of GDK, a native window  * handle is an Xlib XID. A value of 0 is returned for an invalid  * display or if this function is unimplemented for the windowing  * system that is being used.  *  * Returns: The native window handle or 0.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gint
DECL|function|gimp_display_get_window_handle (gint32 display_ID)
name|gimp_display_get_window_handle
parameter_list|(
name|gint32
name|display_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|window
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-display-get-window-handle"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DISPLAY
argument_list|,
name|display_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|window
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|window
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_displays_flush:  *  * Flush all internal changes to the user interface  *  * This procedure takes no arguments and returns nothing except a  * success status. Its purpose is to flush all pending updates of image  * manipulations to the user interface. It should be called whenever  * appropriate.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_displays_flush (void)
name|gimp_displays_flush
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-displays-flush"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_displays_reconnect:  * @old_image_ID: The old image (must have at least one display).  * @new_image_ID: The new image (must not have a display).  *  * Reconnect displays from one image to another image.  *  * This procedure connects all displays of the old_image to the  * new_image. If the old_image has no display or new_image already has  * a display the reconnect is not performed and the procedure returns  * without success. You should rarely need to use this function.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_displays_reconnect (gint32 old_image_ID,gint32 new_image_ID)
name|gimp_displays_reconnect
parameter_list|(
name|gint32
name|old_image_ID
parameter_list|,
name|gint32
name|new_image_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-displays-reconnect"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|old_image_ID
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|new_image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit


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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay-handlers.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_update_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_mode_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_colormap_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|ncol
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_size_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_flush_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_connect (GimpDisplay * gdisp,GimpImage * gimage)
name|gimp_display_connect
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gdisp
operator|->
name|gimage
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|gdisp
operator|->
name|instance
operator|=
name|gimage
operator|->
name|instance_count
expr_stmt|;
name|gimage
operator|->
name|instance_count
operator|++
expr_stmt|;
comment|/* this is obsolete */
name|gimage
operator|->
name|disp_count
operator|++
expr_stmt|;
name|g_print
argument_list|(
literal|"%s: gimage->ref_count before refing: %d\n"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|->
name|ref_count
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_update_handler
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"mode_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_mode_changed_handler
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"colormap_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_colormap_changed_handler
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"size_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_size_changed_handler
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"flush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_flush_handler
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_disconnect (GimpDisplay * gdisp)
name|gimp_display_disconnect
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_display_flush_handler
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_display_size_changed_handler
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_display_colormap_changed_handler
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_display_mode_changed_handler
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_display_update_handler
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|gimage
operator|->
name|disp_count
operator|--
expr_stmt|;
name|g_print
argument_list|(
literal|"%s: gimage->ref_count before unrefing: %d\n"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|->
name|ref_count
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_update_handler (GimpImage * gimage,gint x,gint y,gint w,gint h,GimpDisplay * gdisp)
name|gimp_display_update_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gimp_display_add_update_area
argument_list|(
name|gdisp
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_mode_changed_handler (GimpImage * gimage,GimpDisplay * gdisp)
name|gimp_display_mode_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gimp_display_add_update_area
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_colormap_changed_handler (GimpImage * gimage,gint ncol,GimpDisplay * gdisp)
name|gimp_display_colormap_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|ncol
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|==
name|GIMP_INDEXED
condition|)
block|{
name|gimp_display_add_update_area
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_size_changed_handler (GimpImage * gimage,GimpDisplay * gdisp)
name|gimp_display_size_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gimp_display_add_update_area
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_flush_handler (GimpImage * gimage,GimpDisplay * gdisp)
name|gimp_display_flush_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gimp_display_flush
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
name|GimpProjection
modifier|*
name|projection
parameter_list|,
name|gboolean
name|now
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
name|display
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
name|image
parameter_list|,
name|gboolean
name|invalidate_preview
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_connect (GimpDisplay * display)
name|gimp_display_connect
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_update_handler
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"flush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_flush_handler
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_disconnect (GimpDisplay * display)
name|gimp_display_disconnect
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image
argument_list|,
name|gimp_display_flush_handler
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_display_update_handler
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_update_handler (GimpProjection * projection,gboolean now,gint x,gint y,gint w,gint h,GimpDisplay * display)
name|gimp_display_update_handler
parameter_list|(
name|GimpProjection
modifier|*
name|projection
parameter_list|,
name|gboolean
name|now
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
name|display
parameter_list|)
block|{
name|gimp_display_update_area
argument_list|(
name|display
argument_list|,
name|now
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
DECL|function|gimp_display_flush_handler (GimpImage * image,gboolean invalidate_preview,GimpDisplay * display)
name|gimp_display_flush_handler
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|invalidate_preview
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|gimp_display_flush
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


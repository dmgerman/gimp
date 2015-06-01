begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<lcms2.h>
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
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
file|"gimpdisplayshell-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayxfer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_display_shell_profile_dispose (GimpDisplayShell * shell)
name|gimp_display_shell_profile_dispose
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
name|shell
operator|->
name|profile_transform
condition|)
block|{
name|cmsDeleteTransform
argument_list|(
name|shell
operator|->
name|profile_transform
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_transform
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|profile_src_format
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|profile_dest_format
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|profile_buffer
condition|)
block|{
name|g_object_unref
argument_list|(
name|shell
operator|->
name|profile_buffer
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_buffer
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|profile_data
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|profile_stride
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_profile_update (GimpDisplayShell * shell)
name|gimp_display_shell_profile_update
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDisplayConfig
modifier|*
name|display_config
decl_stmt|;
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
name|GimpColorManaged
modifier|*
name|managed
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|src_format
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|dest_format
decl_stmt|;
name|gimp_display_shell_profile_dispose
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"gimp_display_shell_profile_update\n"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
name|display_config
operator|=
name|shell
operator|->
name|display
operator|->
name|config
expr_stmt|;
name|config
operator|=
name|GIMP_CORE_CONFIG
argument_list|(
name|display_config
argument_list|)
operator|->
name|color_management
expr_stmt|;
name|managed
operator|=
name|GIMP_COLOR_MANAGED
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|src_format
operator|=
name|gimp_pickable_get_format
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
condition|)
name|dest_format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
else|else
name|dest_format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"src_format: %s\n"
argument_list|,
name|babl_get_name
argument_list|(
name|src_format
argument_list|)
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"dest_format: %s\n"
argument_list|,
name|babl_get_name
argument_list|(
name|dest_format
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_transform
operator|=
name|gimp_widget_get_color_transform
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
argument_list|,
name|managed
argument_list|,
name|config
argument_list|,
operator|&
name|src_format
argument_list|,
operator|&
name|dest_format
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|profile_transform
condition|)
block|{
name|gint
name|w
init|=
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
operator|*
name|GIMP_DISPLAY_RENDER_MAX_SCALE
decl_stmt|;
name|gint
name|h
init|=
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
operator|*
name|GIMP_DISPLAY_RENDER_MAX_SCALE
decl_stmt|;
name|shell
operator|->
name|profile_src_format
operator|=
name|src_format
expr_stmt|;
name|shell
operator|->
name|profile_dest_format
operator|=
name|dest_format
expr_stmt|;
name|shell
operator|->
name|profile_data
operator|=
name|gegl_malloc
argument_list|(
name|w
operator|*
name|h
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|src_format
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_stride
operator|=
name|w
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|src_format
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_buffer
operator|=
name|gegl_buffer_linear_new_from_data
argument_list|(
name|shell
operator|->
name|profile_data
argument_list|,
name|src_format
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gegl_free
argument_list|,
name|shell
operator|->
name|profile_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_profile_convert_buffer (GimpDisplayShell * shell,GeglBuffer * src_buffer,GeglRectangle * src_area,GeglBuffer * dest_buffer,GeglRectangle * dest_area)
name|gimp_display_shell_profile_convert_buffer
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|src_area
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|dest_area
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|fish
decl_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|profile_transform
condition|)
return|return;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|src_area
argument_list|,
literal|0
argument_list|,
name|shell
operator|->
name|profile_src_format
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_area
argument_list|,
literal|0
argument_list|,
name|shell
operator|->
name|profile_dest_format
argument_list|,
name|GEGL_ACCESS_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|fish
operator|=
name|babl_fish
argument_list|(
name|shell
operator|->
name|profile_src_format
argument_list|,
name|shell
operator|->
name|profile_dest_format
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gpointer
name|src_data
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gpointer
name|dest_data
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
name|babl_process
argument_list|(
name|fish
argument_list|,
name|src_data
argument_list|,
name|dest_data
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
name|cmsDoTransform
argument_list|(
name|shell
operator|->
name|profile_transform
argument_list|,
name|src_data
argument_list|,
name|dest_data
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


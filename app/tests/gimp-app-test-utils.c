begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-app-test-utils.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gimp_test_utils_set_env_to_subdir (const gchar * root_env_var,const gchar * subdir,const gchar * target_env_var)
name|gimp_test_utils_set_env_to_subdir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target_env_var
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|root_dir
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|target_dir
init|=
name|NULL
decl_stmt|;
comment|/* Get root dir */
name|root_dir
operator|=
name|g_getenv
argument_list|(
name|root_env_var
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|root_dir
condition|)
name|g_printerr
argument_list|(
literal|"*\n"
literal|"*  The env var %s is not set, you are probably running\n"
literal|"*  in a debugger. Set it manually, e.g.:\n"
literal|"*\n"
literal|"*    set env %s=%s/source/gimp\n"
literal|"*\n"
argument_list|,
name|root_env_var
argument_list|,
name|root_env_var
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
comment|/* Construct path and setup target env var */
name|target_dir
operator|=
name|g_build_filename
argument_list|(
name|root_dir
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
name|target_env_var
argument_list|,
name|target_dir
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|target_dir
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_set_gimp2_directory:  * @root_env_var: Either "GIMP_TESTING_ABS_TOP_SRCDIR" or  *                "GIMP_TESTING_ABS_TOP_BUILDDIR"  * @subdir:       Subdir, may be %NULL  *  * Sets GIMP2_DIRECTORY to the source dir @root_env_var/@subdir. The  * environment variables is set up by the test runner, see Makefile.am  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_set_gimp2_directory (const gchar * root_env_var,const gchar * subdir)
name|gimp_test_utils_set_gimp2_directory
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|)
block|{
name|gimp_test_utils_set_env_to_subdir
argument_list|(
name|root_env_var
argument_list|,
name|subdir
argument_list|,
literal|"GIMP2_DIRECTORY"
comment|/*target_env_var*/
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_setup_menus_dir:  *  * Sets GIMP_TESTING_MENUS_DIR to "$top_srcdir/menus".  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_setup_menus_dir (void)
name|gimp_test_utils_setup_menus_dir
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* GIMP_TESTING_ABS_TOP_SRCDIR is set by the automake test runner,    * see Makefile.am    */
name|gimp_test_utils_set_env_to_subdir
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
comment|/*root_env_var*/
argument_list|,
literal|"menus"
comment|/*subdir*/
argument_list|,
literal|"GIMP_TESTING_MENUS_DIR"
comment|/*target_env_var*/
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_create_image:  * @gimp:   A #Gimp instance.  * @width:  Width of image (and layer)  * @height: Height of image (and layer)  *  * Creates a new image of a given size with one layer of same size and  * a display.  *  * Returns: The new #GimpImage.  **/
end_comment

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_test_utils_create_image (Gimp * gimp,gint width,gint height)
name|gimp_test_utils_create_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|image
operator|=
name|gimp_image_new
argument_list|(
name|gimp
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
literal|"layer1"
argument_list|,
literal|1.0
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|NULL
comment|/*parent*/
argument_list|,
literal|0
comment|/*position*/
argument_list|,
name|FALSE
comment|/*push_undo*/
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
comment|/*scale*/
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_synthesize_key_event:  * @widget: Widget to target.  * @keyval: Keyval, e.g. GDK_Return  *  * Simulates a keypress and release with gdk_test_simulate_key().  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_synthesize_key_event (GtkWidget * widget,guint keyval)
name|gimp_test_utils_synthesize_key_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|keyval
parameter_list|)
block|{
name|gdk_test_simulate_key
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
comment|/*x, y*/
name|keyval
argument_list|,
literal|0
comment|/*modifiers*/
argument_list|,
name|GDK_KEY_PRESS
argument_list|)
expr_stmt|;
name|gdk_test_simulate_key
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
comment|/*x, y*/
name|keyval
argument_list|,
literal|0
comment|/*modifiers*/
argument_list|,
name|GDK_KEY_RELEASE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


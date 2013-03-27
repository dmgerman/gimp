begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

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
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
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
file|"operations/gimplevelsconfig.h"
end_include

begin_include
include|#
directive|include
file|"tests.h"
end_include

begin_include
include|#
directive|include
file|"gimp-app-test-utils.h"
end_include

begin_define
DECL|macro|GIMP_TEST_IMAGE_SIZE
define|#
directive|define
name|GIMP_TEST_IMAGE_SIZE
value|100
end_define

begin_define
DECL|macro|ADD_IMAGE_TEST (function)
define|#
directive|define
name|ADD_IMAGE_TEST
parameter_list|(
name|function
parameter_list|)
define|\
value|g_test_add ("/gimp-core/" #function, \               GimpTestFixture, \               gimp, \               gimp_test_image_setup, \               function, \               gimp_test_image_teardown);
end_define

begin_define
DECL|macro|ADD_TEST (function)
define|#
directive|define
name|ADD_TEST
parameter_list|(
name|function
parameter_list|)
define|\
value|g_test_add ("/gimp-core/" #function, \               GimpTestFixture, \               gimp, \               NULL, \               function, \               NULL);
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c7d86380108
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|typedef|GimpTestFixture
block|}
name|GimpTestFixture
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_test_image_setup
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_test_image_teardown
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_test_image_setup:  * @fixture:  * @data:  *  * Test fixture setup for a single image.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_image_setup (GimpTestFixture * fixture,gconstpointer data)
name|gimp_test_image_setup
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|fixture
operator|->
name|image
operator|=
name|gimp_image_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|GIMP_RGB
argument_list|,
name|GIMP_PRECISION_FLOAT
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_image_teardown:  * @fixture:  * @data:  *  * Test fixture teardown for a single image.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_image_teardown (GimpTestFixture * fixture,gconstpointer data)
name|gimp_test_image_teardown
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|g_object_unref
argument_list|(
name|fixture
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * rotate_non_overlapping:  * @fixture:  * @data:  *  * Super basic test that makes sure we can add a layer  * and call gimp_item_rotate with center at (0, -10)  * without triggering a failed assertion .  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|rotate_non_overlapping (GimpTestFixture * fixture,gconstpointer data)
name|rotate_non_overlapping
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|fixture
operator|->
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_context_new
argument_list|(
name|gimp
argument_list|,
literal|"Test"
argument_list|,
name|NULL
comment|/*template*/
argument_list|)
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|g_assert_cmpint
argument_list|(
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
argument_list|,
literal|"Test Layer"
argument_list|,
literal|1.0
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|==
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|GIMP_IMAGE_ACTIVE_PARENT
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_rotate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|context
argument_list|,
name|GIMP_ROTATE_90
argument_list|,
literal|0.
argument_list|,
operator|-
literal|10.
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|result
argument_list|,
operator|==
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * add_layer:  * @fixture:  * @data:  *  * Super basic test that makes sure we can add a layer.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|add_layer (GimpTestFixture * fixture,gconstpointer data)
name|add_layer
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|fixture
operator|->
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|g_assert_cmpint
argument_list|(
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
argument_list|,
literal|"Test Layer"
argument_list|,
literal|1.0
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|==
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|GIMP_IMAGE_ACTIVE_PARENT
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|result
argument_list|,
operator|==
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * remove_layer:  * @fixture:  * @data:  *  * Super basic test that makes sure we can remove a layer.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|remove_layer (GimpTestFixture * fixture,gconstpointer data)
name|remove_layer
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|fixture
operator|->
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|g_assert_cmpint
argument_list|(
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|GIMP_TEST_IMAGE_SIZE
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
argument_list|,
literal|"Test Layer"
argument_list|,
literal|1.0
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|==
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|GIMP_IMAGE_ACTIVE_PARENT
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|result
argument_list|,
operator|==
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_remove_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|gimp_image_get_n_layers
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * white_graypoint_in_red_levels:  * @fixture:  * @data:  *  * Makes sure the levels algorithm can handle when the graypoint is  * white. It's easy to get a divide by zero problem when trying to  * calculate what gamma will give a white graypoint.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|white_graypoint_in_red_levels (GimpTestFixture * fixture,gconstpointer data)
name|white_graypoint_in_red_levels
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|GimpRGB
name|black
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GimpRGB
name|gray
init|=
block|{
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|}
decl_stmt|;
name|GimpRGB
name|white
init|=
block|{
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|}
decl_stmt|;
name|GimpHistogramChannel
name|channel
init|=
name|GIMP_HISTOGRAM_RED
decl_stmt|;
name|GimpLevelsConfig
modifier|*
name|config
decl_stmt|;
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LEVELS_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_levels_config_adjust_by_colors
argument_list|(
name|config
argument_list|,
name|channel
argument_list|,
operator|&
name|black
argument_list|,
operator|&
name|gray
argument_list|,
operator|&
name|white
argument_list|)
expr_stmt|;
comment|/* Make sure we didn't end up with an invalid gamma value */
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"gamma"
argument_list|,
name|config
operator|->
name|gamma
index|[
name|channel
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|main (int argc,char ** argv)
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|int
name|result
decl_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
name|g_test_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_test_utils_set_gimp2_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|,
literal|"app/tests/gimpdir"
argument_list|)
expr_stmt|;
comment|/* We share the same application instance across all tests */
name|gimp
operator|=
name|gimp_init_for_testing
argument_list|()
expr_stmt|;
comment|/* Add tests */
name|ADD_IMAGE_TEST
argument_list|(
name|add_layer
argument_list|)
expr_stmt|;
name|ADD_IMAGE_TEST
argument_list|(
name|remove_layer
argument_list|)
expr_stmt|;
name|ADD_IMAGE_TEST
argument_list|(
name|rotate_non_overlapping
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|white_graypoint_in_red_levels
argument_list|)
expr_stmt|;
comment|/* Run the tests */
name|result
operator|=
name|g_test_run
argument_list|()
expr_stmt|;
comment|/* Don't write files to the source dir */
name|gimp_test_utils_set_gimp2_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_BUILDDIR"
argument_list|,
literal|"app/tests/gimpdir-output"
argument_list|)
expr_stmt|;
comment|/* Exit so we don't break script-fu plug-in wire */
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

end_unit


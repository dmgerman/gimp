begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * test-gimptilebackendtilemanager.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-cache.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimptilebackendtilemanager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
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
DECL|macro|ADD_TEST (function)
define|#
directive|define
name|ADD_TEST
parameter_list|(
name|function
parameter_list|)
define|\
value|g_test_add ("/gimptilebackendtilemanager/" #function, \               GimpTestFixture, \               NULL, \               NULL, \               function, \               NULL);
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28d9474e0108
block|{
DECL|member|avoid_sizeof_zero
name|gint
name|avoid_sizeof_zero
decl_stmt|;
DECL|typedef|GimpTestFixture
block|}
name|GimpTestFixture
typedef|;
end_typedef

begin_comment
comment|/**  * basic_usage:  * @fixture:  * @data:  *  * Test basic usage.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|basic_usage (GimpTestFixture * fixture,gconstpointer data)
name|basic_usage
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|GeglRectangle
name|rect
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|10
block|,
literal|10
block|}
decl_stmt|;
name|GeglRectangle
name|pixel_rect
init|=
block|{
literal|5
block|,
literal|5
block|,
literal|1
block|,
literal|1
block|}
decl_stmt|;
name|guchar
name|opaque_magenta8
index|[
literal|4
index|]
init|=
block|{
literal|0xff
block|,
literal|0
block|,
literal|0xff
block|,
literal|0xff
block|}
decl_stmt|;
name|guint16
name|opaque_magenta16
index|[
literal|4
index|]
init|=
block|{
literal|0xffff
block|,
literal|0
block|,
literal|0xffff
block|,
literal|0xffff
block|}
decl_stmt|;
name|PixelRegion
name|pr
decl_stmt|;
name|TileManager
modifier|*
name|tm
decl_stmt|;
name|GeglTileBackend
modifier|*
name|backend
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|guint16
name|actual_data
index|[
literal|4
index|]
decl_stmt|;
comment|/* Write some pixels to the tile manager */
name|tm
operator|=
name|tile_manager_new
argument_list|(
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
name|height
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|pr
argument_list|,
name|tm
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|pr
argument_list|,
name|opaque_magenta8
argument_list|)
expr_stmt|;
comment|/* Make sure we can read them through the GeglBuffer using the    * TileManager backend. Use u16 to complicate code paths, decreasing    * risk of the test accidentally passing    */
name|backend
operator|=
name|gimp_tile_backend_tile_manager_new
argument_list|(
name|tm
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gegl_buffer_new_for_backend
argument_list|(
name|NULL
argument_list|,
name|backend
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
literal|1.0
comment|/*scale*/
argument_list|,
operator|&
name|pixel_rect
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA u16"
argument_list|)
argument_list|,
name|actual_data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
literal|0
argument_list|,
operator|==
argument_list|,
name|memcmp
argument_list|(
name|opaque_magenta16
argument_list|,
name|actual_data
argument_list|,
sizeof|sizeof
argument_list|(
name|actual_data
argument_list|)
argument_list|)
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
name|g_type_init
argument_list|()
expr_stmt|;
name|tile_cache_init
argument_list|(
name|G_MAXUINT32
argument_list|)
expr_stmt|;
name|gegl_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
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
name|ADD_TEST
argument_list|(
name|basic_usage
argument_list|)
expr_stmt|;
return|return
name|g_test_run
argument_list|()
return|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gximage.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_typedef
DECL|typedef|GXImage
typedef|typedef
name|struct
name|_GXImage
name|GXImage
typedef|;
end_typedef

begin_struct
DECL|struct|_GXImage
struct|struct
name|_GXImage
block|{
DECL|member|width
DECL|member|height
name|long
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  width and height of ximage structure    */
DECL|member|visual
name|GdkVisual
modifier|*
name|visual
decl_stmt|;
comment|/*  visual appropriate to our depth         */
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
comment|/*  graphics context                        */
DECL|member|image
name|GdkImage
modifier|*
name|image
decl_stmt|;
comment|/*  private data  */
block|}
struct|;
end_struct

begin_comment
comment|/*  The static gximages for drawing to windows  */
end_comment

begin_decl_stmt
DECL|variable|gximage
specifier|static
name|GXImage
modifier|*
name|gximage
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|QUANTUM
define|#
directive|define
name|QUANTUM
value|32
end_define

begin_comment
comment|/*  STATIC functions  */
end_comment

begin_function
specifier|static
name|GXImage
modifier|*
DECL|function|create_gximage (GdkVisual * visual,int width,int height)
name|create_gximage
parameter_list|(
name|GdkVisual
modifier|*
name|visual
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
block|{
name|GXImage
modifier|*
name|gximage
decl_stmt|;
name|gximage
operator|=
operator|(
name|GXImage
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GXImage
argument_list|)
argument_list|)
expr_stmt|;
name|gximage
operator|->
name|visual
operator|=
name|visual
expr_stmt|;
name|gximage
operator|->
name|gc
operator|=
name|NULL
expr_stmt|;
name|gximage
operator|->
name|image
operator|=
name|gdk_image_new
argument_list|(
name|GDK_IMAGE_FASTEST
argument_list|,
name|visual
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
return|return
name|gximage
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|delete_gximage (GXImage * gximage)
name|delete_gximage
parameter_list|(
name|GXImage
modifier|*
name|gximage
parameter_list|)
block|{
name|gdk_image_destroy
argument_list|(
name|gximage
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|gximage
operator|->
name|gc
condition|)
name|gdk_gc_destroy
argument_list|(
name|gximage
operator|->
name|gc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gximage
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/****************************************************************/
end_comment

begin_comment
comment|/*  Function definitions  */
end_comment

begin_function
name|void
DECL|function|gximage_init ()
name|gximage_init
parameter_list|()
block|{
name|gximage
operator|=
name|create_gximage
argument_list|(
name|g_visual
argument_list|,
name|GXIMAGE_WIDTH
argument_list|,
name|GXIMAGE_HEIGHT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gximage_free ()
name|gximage_free
parameter_list|()
block|{
name|delete_gximage
argument_list|(
name|gximage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|gximage_get_data ()
name|gximage_get_data
parameter_list|()
block|{
return|return
name|gximage
operator|->
name|image
operator|->
name|mem
return|;
block|}
end_function

begin_function
name|int
DECL|function|gximage_get_bpp ()
name|gximage_get_bpp
parameter_list|()
block|{
return|return
name|gximage
operator|->
name|image
operator|->
name|bpp
return|;
block|}
end_function

begin_function
name|int
DECL|function|gximage_get_bpl ()
name|gximage_get_bpl
parameter_list|()
block|{
return|return
name|gximage
operator|->
name|image
operator|->
name|bpl
return|;
block|}
end_function

begin_function
name|int
DECL|function|gximage_get_byte_order ()
name|gximage_get_byte_order
parameter_list|()
block|{
return|return
name|gximage
operator|->
name|image
operator|->
name|byte_order
return|;
block|}
end_function

begin_function
name|void
DECL|function|gximage_put (GdkWindow * win,int x,int y,int w,int h)
name|gximage_put
parameter_list|(
name|GdkWindow
modifier|*
name|win
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|)
block|{
comment|/*  create the GC if it doesn't yet exist  */
if|if
condition|(
operator|!
name|gximage
operator|->
name|gc
condition|)
block|{
name|gximage
operator|->
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|win
argument_list|)
expr_stmt|;
name|gdk_gc_set_exposures
argument_list|(
name|gximage
operator|->
name|gc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gdk_draw_image
argument_list|(
name|win
argument_list|,
name|gximage
operator|->
name|gc
argument_list|,
name|gximage
operator|->
name|image
argument_list|,
literal|0
argument_list|,
literal|0
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
comment|/*  sync the draw image to make sure it has been displayed before continuing  */
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

end_unit


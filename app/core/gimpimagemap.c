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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
end_include

begin_define
DECL|macro|WAITING
define|#
directive|define
name|WAITING
value|0
end_define

begin_define
DECL|macro|WORKING
define|#
directive|define
name|WORKING
value|1
end_define

begin_define
DECL|macro|WORK_DELAY
define|#
directive|define
name|WORK_DELAY
value|1
end_define

begin_comment
comment|/*  Local structures  */
end_comment

begin_typedef
DECL|struct|_ImageMap
typedef|typedef
struct|struct
name|_ImageMap
block|{
DECL|member|gdisp
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|undo_tiles
name|TileManager
modifier|*
name|undo_tiles
decl_stmt|;
DECL|member|apply_func
name|ImageMapApplyFunc
name|apply_func
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|srcPR
DECL|member|destPR
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
DECL|member|pr
name|void
modifier|*
name|pr
decl_stmt|;
DECL|member|state
name|gint
name|state
decl_stmt|;
DECL|member|idle
name|gint
name|idle
decl_stmt|;
DECL|typedef|_ImageMap
block|}
name|_ImageMap
typedef|;
end_typedef

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  Function definitions  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|image_map_do (gpointer data)
name|image_map_do
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|_ImageMap
modifier|*
name|_image_map
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|PixelRegion
name|shadowPR
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|_image_map
operator|=
operator|(
name|_ImageMap
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
operator|(
name|_image_map
operator|->
name|drawable
operator|)
argument_list|)
operator|)
condition|)
block|{
name|_image_map
operator|->
name|state
operator|=
name|WAITING
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*  Process the pixel regions and apply the image mapping  */
call|(
modifier|*
name|_image_map
operator|->
name|apply_func
call|)
argument_list|(
operator|&
name|_image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|_image_map
operator|->
name|destPR
argument_list|,
name|_image_map
operator|->
name|user_data
argument_list|)
expr_stmt|;
name|x
operator|=
name|_image_map
operator|->
name|destPR
operator|.
name|x
expr_stmt|;
name|y
operator|=
name|_image_map
operator|->
name|destPR
operator|.
name|y
expr_stmt|;
name|w
operator|=
name|_image_map
operator|->
name|destPR
operator|.
name|w
expr_stmt|;
name|h
operator|=
name|_image_map
operator|->
name|destPR
operator|.
name|h
expr_stmt|;
comment|/*  apply the results  */
name|pixel_region_init
argument_list|(
operator|&
name|shadowPR
argument_list|,
name|gimage
operator|->
name|shadow
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_apply_image
argument_list|(
name|gimage
argument_list|,
name|_image_map
operator|->
name|drawable
argument_list|,
operator|&
name|shadowPR
argument_list|,
name|FALSE
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|REPLACE_MODE
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/*  display the results  */
if|if
condition|(
name|_image_map
operator|->
name|gdisp
condition|)
block|{
name|drawable_update
argument_list|(
operator|(
name|_image_map
operator|->
name|drawable
operator|)
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
name|gdisplay_flush_now
argument_list|(
name|_image_map
operator|->
name|gdisp
argument_list|)
expr_stmt|;
block|}
name|_image_map
operator|->
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|_image_map
operator|->
name|pr
argument_list|)
expr_stmt|;
if|if
condition|(
name|_image_map
operator|->
name|pr
operator|==
name|NULL
condition|)
block|{
name|_image_map
operator|->
name|state
operator|=
name|WAITING
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
return|return
name|FALSE
return|;
block|}
else|else
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|ImageMap
DECL|function|image_map_create (GDisplay * gdisp,GimpDrawable * drawable)
name|image_map_create
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|_ImageMap
modifier|*
name|_image_map
decl_stmt|;
name|_image_map
operator|=
name|g_new
argument_list|(
name|_ImageMap
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|_image_map
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|_image_map
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|_image_map
operator|->
name|undo_tiles
operator|=
name|NULL
expr_stmt|;
name|_image_map
operator|->
name|state
operator|=
name|WAITING
expr_stmt|;
comment|/* Interactive tools based on image_map disable the undo stack */
comment|/* to avert any unintented undo interaction through the UI     */
name|gimp_image_undo_freeze
argument_list|(
name|_image_map
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gdisplay_set_menu_sensitivity
argument_list|(
name|_image_map
operator|->
name|gdisp
argument_list|)
expr_stmt|;
return|return
operator|(
name|ImageMap
operator|)
name|_image_map
return|;
block|}
end_function

begin_function
name|void
DECL|function|image_map_apply (ImageMap image_map,ImageMapApplyFunc apply_func,void * user_data)
name|image_map_apply
parameter_list|(
name|ImageMap
name|image_map
parameter_list|,
name|ImageMapApplyFunc
name|apply_func
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|)
block|{
name|_ImageMap
modifier|*
name|_image_map
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|_image_map
operator|=
operator|(
name|_ImageMap
operator|*
operator|)
name|image_map
expr_stmt|;
name|_image_map
operator|->
name|apply_func
operator|=
name|apply_func
expr_stmt|;
name|_image_map
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
comment|/*  If we're still working, remove the timer  */
if|if
condition|(
name|_image_map
operator|->
name|state
operator|==
name|WORKING
condition|)
block|{
name|gtk_idle_remove
argument_list|(
name|_image_map
operator|->
name|idle
argument_list|)
expr_stmt|;
name|pixel_regions_process_stop
argument_list|(
name|_image_map
operator|->
name|pr
argument_list|)
expr_stmt|;
name|_image_map
operator|->
name|pr
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  Make sure the drawable is still valid  */
if|if
condition|(
operator|!
name|gimp_drawable_gimage
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
condition|)
return|return;
comment|/*  The application should occur only within selection bounds  */
name|gimp_drawable_mask_bounds
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
comment|/*  If undo tiles don't exist, or change size, (re)allocate  */
if|if
condition|(
operator|!
name|_image_map
operator|->
name|undo_tiles
operator|||
name|_image_map
operator|->
name|undo_tiles
operator|->
name|x
operator|!=
name|x1
operator|||
name|_image_map
operator|->
name|undo_tiles
operator|->
name|y
operator|!=
name|y1
operator|||
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
operator|!=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
operator|!=
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
block|{
comment|/*  If either the extents changed or the tiles don't exist, allocate new  */
if|if
condition|(
operator|!
name|_image_map
operator|->
name|undo_tiles
operator|||
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
operator|!=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
operator|!=
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
block|{
comment|/*  Destroy old tiles--If they exist  */
if|if
condition|(
name|_image_map
operator|->
name|undo_tiles
operator|!=
name|NULL
condition|)
name|tile_manager_destroy
argument_list|(
name|_image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
comment|/*  Allocate new tiles  */
name|_image_map
operator|->
name|undo_tiles
operator|=
name|tile_manager_new
argument_list|(
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  Copy from the image to the new tiles  */
name|pixel_region_init
argument_list|(
operator|&
name|_image_map
operator|->
name|srcPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|_image_map
operator|->
name|destPR
argument_list|,
name|_image_map
operator|->
name|undo_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|_image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|_image_map
operator|->
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Set the offsets  */
name|_image_map
operator|->
name|undo_tiles
operator|->
name|x
operator|=
name|x1
expr_stmt|;
name|_image_map
operator|->
name|undo_tiles
operator|->
name|y
operator|=
name|y1
expr_stmt|;
block|}
else|else
comment|/* _image_map->undo_tiles exist AND drawable dimensions have not changed... */
block|{
comment|/* Reset to initial drawable conditions.            */
comment|/* Copy from the backup undo tiles to the drawable  */
name|pixel_region_init
argument_list|(
operator|&
name|_image_map
operator|->
name|srcPR
argument_list|,
name|_image_map
operator|->
name|undo_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|_image_map
operator|->
name|destPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|x
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|y
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|_image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|_image_map
operator|->
name|destPR
argument_list|)
expr_stmt|;
block|}
comment|/*  Configure the src from the drawable data  */
name|pixel_region_init
argument_list|(
operator|&
name|_image_map
operator|->
name|srcPR
argument_list|,
name|_image_map
operator|->
name|undo_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  Configure the dest as the shadow buffer  */
name|pixel_region_init
argument_list|(
operator|&
name|_image_map
operator|->
name|destPR
argument_list|,
name|gimp_drawable_shadow
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Apply the image transformation to the pixels  */
name|_image_map
operator|->
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|2
argument_list|,
operator|&
name|_image_map
operator|->
name|srcPR
argument_list|,
operator|&
name|_image_map
operator|->
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Start the intermittant work procedure  */
name|_image_map
operator|->
name|state
operator|=
name|WORKING
expr_stmt|;
name|_image_map
operator|->
name|idle
operator|=
name|gtk_idle_add
argument_list|(
name|image_map_do
argument_list|,
name|image_map
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_map_commit (ImageMap image_map)
name|image_map_commit
parameter_list|(
name|ImageMap
name|image_map
parameter_list|)
block|{
name|_ImageMap
modifier|*
name|_image_map
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|_image_map
operator|=
operator|(
name|_ImageMap
operator|*
operator|)
name|image_map
expr_stmt|;
if|if
condition|(
name|_image_map
operator|->
name|state
operator|==
name|WORKING
condition|)
block|{
name|gtk_idle_remove
argument_list|(
name|_image_map
operator|->
name|idle
argument_list|)
expr_stmt|;
comment|/*  Finish the changes  */
while|while
condition|(
name|image_map_do
argument_list|(
name|image_map
argument_list|)
condition|)
empty_stmt|;
block|}
comment|/*  Make sure the drawable is still valid  */
if|if
condition|(
operator|!
name|gimp_drawable_gimage
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
condition|)
return|return;
comment|/* Interactive phase ends: we can commit an undo frame now */
name|gimp_image_undo_thaw
argument_list|(
name|_image_map
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
comment|/*  Register an undo step  */
if|if
condition|(
name|_image_map
operator|->
name|undo_tiles
condition|)
block|{
name|x1
operator|=
name|_image_map
operator|->
name|undo_tiles
operator|->
name|x
expr_stmt|;
name|y1
operator|=
name|_image_map
operator|->
name|undo_tiles
operator|->
name|y
expr_stmt|;
name|x2
operator|=
name|_image_map
operator|->
name|undo_tiles
operator|->
name|x
operator|+
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
expr_stmt|;
name|y2
operator|=
name|_image_map
operator|->
name|undo_tiles
operator|->
name|y
operator|+
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
expr_stmt|;
name|drawable_apply_image
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|_image_map
operator|->
name|undo_tiles
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gdisplay_set_menu_sensitivity
argument_list|(
name|_image_map
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|_image_map
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_map_clear (ImageMap image_map)
name|image_map_clear
parameter_list|(
name|ImageMap
name|image_map
parameter_list|)
block|{
name|_ImageMap
modifier|*
name|_image_map
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|_image_map
operator|=
operator|(
name|_ImageMap
operator|*
operator|)
name|image_map
expr_stmt|;
if|if
condition|(
name|_image_map
operator|->
name|state
operator|==
name|WORKING
condition|)
block|{
name|gtk_idle_remove
argument_list|(
name|_image_map
operator|->
name|idle
argument_list|)
expr_stmt|;
name|pixel_regions_process_stop
argument_list|(
name|_image_map
operator|->
name|pr
argument_list|)
expr_stmt|;
name|_image_map
operator|->
name|pr
operator|=
name|NULL
expr_stmt|;
block|}
name|_image_map
operator|->
name|state
operator|=
name|WAITING
expr_stmt|;
comment|/*  Make sure the drawable is still valid  */
if|if
condition|(
operator|!
name|gimp_drawable_gimage
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
condition|)
return|return;
comment|/*  restore the original image  */
if|if
condition|(
name|_image_map
operator|->
name|undo_tiles
condition|)
block|{
comment|/*  Copy from the drawable to the tiles  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|_image_map
operator|->
name|undo_tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|x
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|y
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* if the user has changed the image depth get out quickly */
if|if
condition|(
name|destPR
operator|.
name|bytes
operator|!=
name|srcPR
operator|.
name|bytes
condition|)
block|{
name|g_message
argument_list|(
literal|"image depth change, unable to restore original image"
argument_list|)
expr_stmt|;
name|tile_manager_destroy
argument_list|(
name|_image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|gimp_image_undo_thaw
argument_list|(
name|_image_map
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gdisplay_set_menu_sensitivity
argument_list|(
name|_image_map
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|_image_map
argument_list|)
expr_stmt|;
return|return;
block|}
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
comment|/*  Update the area  */
name|drawable_update
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|x
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|y
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
argument_list|,
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  Free the undo_tiles tile manager  */
name|tile_manager_destroy
argument_list|(
name|_image_map
operator|->
name|undo_tiles
argument_list|)
expr_stmt|;
name|_image_map
operator|->
name|undo_tiles
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|image_map_abort (ImageMap image_map)
name|image_map_abort
parameter_list|(
name|ImageMap
name|image_map
parameter_list|)
block|{
name|_ImageMap
modifier|*
name|_image_map
init|=
operator|(
name|_ImageMap
operator|*
operator|)
name|image_map
decl_stmt|;
name|image_map_clear
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
name|gimp_image_undo_thaw
argument_list|(
name|_image_map
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gdisplay_set_menu_sensitivity
argument_list|(
name|_image_map
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|image_map
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guchar
modifier|*
DECL|function|image_map_get_color_at (ImageMap image_map,gint x,gint y)
name|image_map_get_color_at
parameter_list|(
name|ImageMap
name|image_map
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|Tile
modifier|*
name|tile
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|_ImageMap
modifier|*
name|_image_map
decl_stmt|;
if|if
condition|(
operator|!
name|image_map
condition|)
return|return
name|NULL
return|;
name|_image_map
operator|=
operator|(
name|_ImageMap
operator|*
operator|)
name|image_map
expr_stmt|;
if|if
condition|(
name|x
operator|>=
literal|0
operator|&&
name|x
operator|<
name|gimp_drawable_width
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
operator|&&
name|y
operator|>=
literal|0
operator|&&
name|y
operator|<
name|gimp_drawable_height
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
condition|)
block|{
comment|/* Check if done damage to original image */
if|if
condition|(
operator|!
name|_image_map
operator|->
name|undo_tiles
condition|)
return|return
operator|(
name|gimp_drawable_get_color_at
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|)
return|;
if|if
condition|(
operator|!
name|image_map
operator|||
operator|(
operator|!
name|gimp_drawable_gimage
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
operator|&&
name|gimp_drawable_is_indexed
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
operator|)
operator|||
name|x
operator|<
literal|0
operator|||
name|y
operator|<
literal|0
operator|||
name|x
operator|>=
name|_image_map
operator|->
name|undo_tiles
operator|->
name|width
operator|||
name|y
operator|>=
name|_image_map
operator|->
name|undo_tiles
operator|->
name|height
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|_image_map
operator|->
name|undo_tiles
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|src
operator|=
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|x
operator|%
name|TILE_WIDTH
argument_list|,
name|y
operator|%
name|TILE_HEIGHT
argument_list|)
expr_stmt|;
name|gimp_image_get_color
argument_list|(
name|gimp_drawable_gimage
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_type
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|,
name|dest
argument_list|,
name|src
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|gimp_drawable_type
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
argument_list|)
condition|)
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
name|gimp_drawable_bytes
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
operator|-
literal|1
index|]
expr_stmt|;
else|else
name|dest
index|[
literal|3
index|]
operator|=
literal|255
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|_image_map
operator|->
name|drawable
argument_list|)
condition|)
name|dest
index|[
literal|4
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
else|else
name|dest
index|[
literal|4
index|]
operator|=
literal|0
expr_stmt|;
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|dest
return|;
block|}
else|else
comment|/* out of bounds error */
block|{
return|return
name|NULL
return|;
block|}
block|}
end_function

end_unit


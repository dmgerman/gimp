begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_if
if|#
directive|if
literal|0
end_if

begin_include
include|#
directive|include
file|"base/siox.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-foreground-extract.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_drawable_foreground_extract (GimpDrawable * drawable,GimpForegroundExtractMode mode,GimpDrawable * mask,GimpProgress * progress)
name|gimp_drawable_foreground_extract
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpForegroundExtractMode
name|mode
parameter_list|,
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
if|#
directive|if
literal|0
block|SioxState    *state;   const gdouble sensitivity[3] = { SIOX_DEFAULT_SENSITIVITY_L,                                    SIOX_DEFAULT_SENSITIVITY_A,                                    SIOX_DEFAULT_SENSITIVITY_B };    g_return_if_fail (GIMP_IS_DRAWABLE (mask));   g_return_if_fail (mode == GIMP_FOREGROUND_EXTRACT_SIOX);    state =     gimp_drawable_foreground_extract_siox_init (drawable,                                                 0, 0,                                                 gimp_item_get_width  (GIMP_ITEM (mask)),                                                 gimp_item_get_height (GIMP_ITEM (mask)));    if (state)     {       gimp_drawable_foreground_extract_siox (mask, state,                                              SIOX_REFINEMENT_RECALCULATE,                                              SIOX_DEFAULT_SMOOTHNESS,                                              sensitivity,                                              FALSE,                                              progress);        gimp_drawable_foreground_extract_siox_done (state);     }
endif|#
directive|endif
block|}
end_function

begin_function
name|SioxState
modifier|*
DECL|function|gimp_drawable_foreground_extract_siox_init (GimpDrawable * drawable,gint x,gint y,gint width,gint height)
name|gimp_drawable_foreground_extract_siox_init
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GeglBuffer   *buffer;   const guchar *colormap = NULL;   gboolean      intersect;   gint          offset_x;   gint          offset_y;    g_return_val_if_fail (GIMP_IS_DRAWABLE (drawable), NULL);   g_return_val_if_fail (gimp_item_is_attached (GIMP_ITEM (drawable)), NULL);    if (gimp_drawable_is_indexed (drawable))     colormap = gimp_drawable_get_colormap (drawable);    gimp_item_get_offset (GIMP_ITEM (drawable),&offset_x,&offset_y);    intersect = gimp_rectangle_intersect (offset_x, offset_y,                                         gimp_item_get_width  (GIMP_ITEM (drawable)),                                         gimp_item_get_height (GIMP_ITEM (drawable)),                                         x, y, width, height,&x,&y,&width,&height);
comment|/* FIXME:    * Clear the mask outside the rectangle that we are working on?    */
block|if (! intersect)     return NULL;    buffer = gimp_drawable_get_buffer (drawable);    return siox_init (gimp_gegl_buffer_get_tiles (buffer), colormap,                     offset_x, offset_y,                     x, y, width, height);
endif|#
directive|endif
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_foreground_extract_siox (GimpDrawable * mask,SioxState * state,SioxRefinementType refinement,gint smoothness,const gdouble sensitivity[3],gboolean multiblob,GimpProgress * progress)
name|gimp_drawable_foreground_extract_siox
parameter_list|(
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
name|SioxState
modifier|*
name|state
parameter_list|,
name|SioxRefinementType
name|refinement
parameter_list|,
name|gint
name|smoothness
parameter_list|,
specifier|const
name|gdouble
name|sensitivity
index|[
literal|3
index|]
parameter_list|,
name|gboolean
name|multiblob
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GeglBuffer *buffer;   gint        x1, y1;   gint        x2, y2;    g_return_if_fail (GIMP_IS_DRAWABLE (mask));   g_return_if_fail (babl_format_get_bytes_per_pixel (gimp_drawable_get_format (mask)) == 1);    g_return_if_fail (state != NULL);    g_return_if_fail (progress == NULL || GIMP_IS_PROGRESS (progress));    if (progress)     gimp_progress_start (progress, _("Foreground Extraction"), FALSE);    if (GIMP_IS_CHANNEL (mask))     {       gimp_channel_bounds (GIMP_CHANNEL (mask),&x1,&y1,&x2,&y2);     }   else     {       x1 = 0;       y1 = 0;       x2 = gimp_item_get_width  (GIMP_ITEM (mask));       y2 = gimp_item_get_height (GIMP_ITEM (mask));     }    buffer = gimp_drawable_get_buffer (mask);    siox_foreground_extract (state, refinement,                            gimp_gegl_buffer_get_tiles (buffer),                            x1, y1, x2, y2,                            smoothness, sensitivity, multiblob,                            (SioxProgressFunc) gimp_progress_set_value,                            progress);    if (progress)     gimp_progress_end (progress);    gimp_drawable_update (mask, x1, y1, x2, y2);
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_foreground_extract_siox_done (SioxState * state)
name|gimp_drawable_foreground_extract_siox_done
parameter_list|(
name|SioxState
modifier|*
name|state
parameter_list|)
block|{
if|#
directive|if
literal|0
block|g_return_if_fail (state != NULL);    siox_done (state);
endif|#
directive|endif
block|}
end_function

end_unit


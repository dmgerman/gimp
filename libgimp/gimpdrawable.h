begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawable.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_H__
define|#
directive|define
name|__GIMP_DRAWABLE_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
DECL|struct|_GimpDrawable
struct|struct
name|_GimpDrawable
block|{
DECL|member|id
name|gint32
name|id
decl_stmt|;
comment|/* drawable ID */
DECL|member|width
name|guint
name|width
decl_stmt|;
comment|/* width of drawble */
DECL|member|height
name|guint
name|height
decl_stmt|;
comment|/* height of drawble */
DECL|member|bpp
name|guint
name|bpp
decl_stmt|;
comment|/* bytes per pixel of drawable */
DECL|member|ntile_rows
name|guint
name|ntile_rows
decl_stmt|;
comment|/* # of tile rows */
DECL|member|ntile_cols
name|guint
name|ntile_cols
decl_stmt|;
comment|/* # of tile columns */
DECL|member|tiles
name|GimpTile
modifier|*
name|tiles
decl_stmt|;
comment|/* the normal tiles */
DECL|member|shadow_tiles
name|GimpTile
modifier|*
name|shadow_tiles
decl_stmt|;
comment|/* the shadow tiles */
block|}
struct|;
name|GimpDrawable
modifier|*
name|gimp_drawable_get
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
name|void
name|gimp_drawable_detach
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
name|void
name|gimp_drawable_flush
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
name|void
name|gimp_drawable_delete
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_drawable_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
name|gboolean
name|gimp_drawable_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
name|void
name|gimp_drawable_set_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
name|GimpTile
modifier|*
name|gimp_drawable_get_tile
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|shadow
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
function_decl|;
name|GimpTile
modifier|*
name|gimp_drawable_get_tile2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|shadow
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_H__ */
end_comment

end_unit


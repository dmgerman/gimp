begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPDRAWABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMPDRAWABLE_H__
define|#
directive|define
name|__GIMPDRAWABLE_H__
end_define

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawableF.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/parasiteF.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE
define|#
directive|define
name|GIMP_TYPE_DRAWABLE
value|(gimp_drawable_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAWABLE (obj)
define|#
directive|define
name|GIMP_DRAWABLE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DRAWABLE, GimpDrawable))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE (obj)
define|#
directive|define
name|GIMP_IS_DRAWABLE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DRAWABLE))
end_define

begin_function_decl
name|GtkType
name|gimp_drawable_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  drawable access functions  */
end_comment

begin_function_decl
name|void
name|gimp_drawable_merge_shadow
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|guchar
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_mask_bounds
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_invalidate_preview
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_dirty
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_clean
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_has_alpha
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type_with_alpha
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_color
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_gray
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_indexed
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_drawable_data
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_drawable_shadow
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_bytes
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_width
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_height
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_visible
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_offsets
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_drawable_cmap
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_drawable_get_name
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_name
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_drawable_get_color_at
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_parasite_attach
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|Parasite
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_parasite_detach
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
specifier|const
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Parasite
modifier|*
name|gimp_drawable_parasite_find
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
parameter_list|,
specifier|const
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_drawable_parasite_list
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tattoo
name|gimp_drawable_get_tattoo
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_drawable_get_ID
parameter_list|(
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_deallocate
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_drawable_gimage
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_gimage
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPDRAWABLE_H__ */
end_comment

end_unit


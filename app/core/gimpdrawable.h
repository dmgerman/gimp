begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|"gimpobject.h"
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

begin_define
DECL|macro|GIMP_DRAWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_DRAWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAWABLE, GimpDrawableClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAWABLE))
end_define

begin_typedef
DECL|typedef|GimpDrawableClass
typedef|typedef
name|struct
name|_GimpDrawableClass
name|GimpDrawableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawable
struct|struct
name|_GimpDrawable
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/* tiles for drawable data        */
DECL|member|visible
name|gboolean
name|visible
decl_stmt|;
comment|/* controls visibility            */
DECL|member|width
DECL|member|height
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/* size of drawable               */
DECL|member|offset_x
DECL|member|offset_y
name|gint
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
comment|/* offset of layer in image       */
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
comment|/* bytes per pixel                */
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/* provides a unique ID           */
DECL|member|tattoo
name|guint32
name|tattoo
decl_stmt|;
comment|/* provides a perminant ID        */
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/* gimage owner                   */
DECL|member|type
name|GimpImageType
name|type
decl_stmt|;
comment|/* type of drawable               */
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
comment|/* drawable has alpha             */
DECL|member|parasites
name|ParasiteList
modifier|*
name|parasites
decl_stmt|;
comment|/* Plug-in parasite data          */
comment|/*  Preview variables  */
DECL|member|preview_cache
name|GSList
modifier|*
name|preview_cache
decl_stmt|;
comment|/* preview caches of the channel  */
DECL|member|preview_valid
name|gboolean
name|preview_valid
decl_stmt|;
comment|/* is the preview valid?          */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawableClass
struct|struct
name|_GimpDrawableClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|invalidate_preview
name|void
function_decl|(
modifier|*
name|invalidate_preview
function_decl|)
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  drawable access functions  */
end_comment

begin_function_decl
name|GtkType
name|gimp_drawable_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_merge_shadow
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|undo
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
name|drawable
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_invalidate_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|emit_signal
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_has_alpha
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type_with_alpha
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_rgb
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_gray
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_indexed
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_drawable_data
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
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
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_offsets
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
modifier|*
name|offset_x
parameter_list|,
name|gint
modifier|*
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_drawable_cmap
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
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
name|drawable
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
name|drawable
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_parasite_detach
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_drawable_parasite_find
parameter_list|(
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_drawable_parasite_list
parameter_list|(
specifier|const
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
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_tattoo
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|Tattoo
name|tattoo
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
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_set_gimage
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_configure
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_H__ */
end_comment

end_unit


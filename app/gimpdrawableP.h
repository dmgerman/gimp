begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPDRAWABLEP_H__
end_ifndef

begin_define
DECL|macro|__GIMPDRAWABLEP_H__
define|#
directive|define
name|__GIMPDRAWABLEP_H__
end_define

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"parasitelistF.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewcache.h"
end_include

begin_struct
DECL|struct|_GimpDrawable
struct|struct
name|_GimpDrawable
block|{
DECL|member|data
name|GimpObject
name|data
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
comment|/* name of drawable */
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/* tiles for drawable data */
DECL|member|visible
name|int
name|visible
decl_stmt|;
comment|/* controls visibility */
DECL|member|width
DECL|member|height
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/* size of drawable */
DECL|member|offset_x
DECL|member|offset_y
name|int
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
comment|/* offset of layer in image */
DECL|member|bytes
name|int
name|bytes
decl_stmt|;
comment|/* bytes per pixel */
DECL|member|dirty
name|int
name|dirty
decl_stmt|;
comment|/* dirty bit */
DECL|member|ID
name|int
name|ID
decl_stmt|;
comment|/* provides a unique ID */
DECL|member|tattoo
name|guint32
name|tattoo
decl_stmt|;
comment|/* provides a perminant ID */
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/* gimage owner */
DECL|member|type
name|GimpImageType
name|type
decl_stmt|;
comment|/* type of drawable */
DECL|member|has_alpha
name|int
name|has_alpha
decl_stmt|;
comment|/* drawable has alpha */
DECL|member|parasites
name|ParasiteList
modifier|*
name|parasites
decl_stmt|;
comment|/* Plug-in parasite data   */
comment|/*  Preview variables  */
DECL|member|preview_cache
name|GSList
modifier|*
name|preview_cache
decl_stmt|;
comment|/* preview caches of the channel */
DECL|member|preview_valid
name|int
name|preview_valid
decl_stmt|;
comment|/* is the preview valid? */
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
name|GtkObject
modifier|*
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpDrawableClass
typedef|typedef
name|struct
name|_GimpDrawableClass
name|GimpDrawableClass
typedef|;
end_typedef

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

begin_function_decl
name|void
name|gimp_drawable_configure
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|GimpImageType
parameter_list|,
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPDRAWABLEP_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpNavigationPreview Widget  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_NAVIGATION_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_NAVIGATION_PREVIEW_H__
define|#
directive|define
name|__GIMP_NAVIGATION_PREVIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpimagepreview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_NAVIGATION_PREVIEW
define|#
directive|define
name|GIMP_TYPE_NAVIGATION_PREVIEW
value|(gimp_navigation_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_PREVIEW (obj)
define|#
directive|define
name|GIMP_NAVIGATION_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_NAVIGATION_PREVIEW, GimpNavigationPreview))
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_NAVIGATION_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_NAVIGATION_PREVIEW, GimpNavigationPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_NAVIGATION_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_NAVIGATION_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_NAVIGATION_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_NAVIGATION_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_NAVIGATION_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_NAVIGATION_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_NAVIGATION_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_NAVIGATION_PREVIEW, GimpNavigationPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpNavigationPreviewClass
typedef|typedef
name|struct
name|_GimpNavigationPreviewClass
name|GimpNavigationPreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpNavigationPreview
struct|struct
name|_GimpNavigationPreview
block|{
DECL|member|parent_instance
name|GimpImagePreview
name|parent_instance
decl_stmt|;
comment|/*  values in image coordinates  */
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|width
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
name|height
decl_stmt|;
comment|/*  values in preview coordinates  */
DECL|member|p_x
name|gint
name|p_x
decl_stmt|;
DECL|member|p_y
name|gint
name|p_y
decl_stmt|;
DECL|member|p_width
name|guint
name|p_width
decl_stmt|;
DECL|member|p_height
name|guint
name|p_height
decl_stmt|;
DECL|member|motion_offset_x
name|gint
name|motion_offset_x
decl_stmt|;
DECL|member|motion_offset_y
name|gint
name|motion_offset_y
decl_stmt|;
DECL|member|has_grab
name|guint
name|has_grab
range|:
literal|1
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpNavigationPreviewClass
struct|struct
name|_GimpNavigationPreviewClass
block|{
DECL|member|parent_class
name|GimpPreviewClass
name|parent_class
decl_stmt|;
DECL|member|marker_changed
name|void
function_decl|(
modifier|*
name|marker_changed
function_decl|)
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
DECL|member|zoom
name|void
function_decl|(
modifier|*
name|zoom
function_decl|)
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|preview
parameter_list|,
name|GimpZoomType
name|direction
parameter_list|)
function_decl|;
DECL|member|scroll
name|void
function_decl|(
modifier|*
name|scroll
function_decl|)
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|preview
parameter_list|,
name|GdkScrollDirection
name|direction
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_navigation_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_navigation_preview_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_navigation_preview_set_marker
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|preview
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_NAVIGATION_PREVIEW_H__ */
end_comment

end_unit


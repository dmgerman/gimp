begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpNavigationView Widget  * Copyright (C) 2001-2002 Michael Natterer<mitch@gimp.org>  *  * partly based on app/nav_window  * Copyright (C) 1999 Andy Thomas<alt@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_NAVIGATION_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_NAVIGATION_VIEW_H__
define|#
directive|define
name|__GIMP_NAVIGATION_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_NAVIGATION_VIEW
define|#
directive|define
name|GIMP_TYPE_NAVIGATION_VIEW
value|(gimp_navigation_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_VIEW (obj)
define|#
directive|define
name|GIMP_NAVIGATION_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_NAVIGATION_VIEW, GimpNavigationView))
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_NAVIGATION_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_NAVIGATION_VIEW, GimpNavigationViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_NAVIGATION_VIEW (obj)
define|#
directive|define
name|GIMP_IS_NAVIGATION_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_NAVIGATION_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_NAVIGATION_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_NAVIGATION_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_NAVIGATION_VIEW))
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_NAVIGATION_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_NAVIGATION_VIEW, GimpNavigationViewClass))
end_define

begin_typedef
DECL|typedef|GimpNavigationViewClass
typedef|typedef
name|struct
name|_GimpNavigationViewClass
name|GimpNavigationViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpNavigationView
struct|struct
name|_GimpNavigationView
block|{
DECL|member|parent_instance
name|GimpView
name|parent_instance
decl_stmt|;
comment|/*  values in image coordinates  */
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
DECL|member|width
name|gdouble
name|width
decl_stmt|;
DECL|member|height
name|gdouble
name|height
decl_stmt|;
comment|/*  values in view coordinates  */
DECL|member|p_x
name|gint
name|p_x
decl_stmt|;
DECL|member|p_y
name|gint
name|p_y
decl_stmt|;
DECL|member|p_width
name|gint
name|p_width
decl_stmt|;
DECL|member|p_height
name|gint
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
name|gboolean
name|has_grab
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
DECL|struct|_GimpNavigationViewClass
struct|struct
name|_GimpNavigationViewClass
block|{
DECL|member|parent_class
name|GimpViewClass
name|parent_class
decl_stmt|;
DECL|member|marker_changed
name|void
function_decl|(
modifier|*
name|marker_changed
function_decl|)
parameter_list|(
name|GimpNavigationView
modifier|*
name|view
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
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
name|GimpNavigationView
modifier|*
name|view
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
name|GimpNavigationView
modifier|*
name|view
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
name|gimp_navigation_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_navigation_view_set_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|view
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_navigation_view_grab_pointer
parameter_list|(
name|GimpNavigationView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_NAVIGATION_VIEW_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_H__
define|#
directive|define
name|__GIMP_DISPLAY_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_typedef
DECL|typedef|IdleRenderStruct
typedef|typedef
name|struct
name|_IdleRenderStruct
name|IdleRenderStruct
typedef|;
end_typedef

begin_struct
DECL|struct|_IdleRenderStruct
struct|struct
name|_IdleRenderStruct
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|basex
name|gint
name|basex
decl_stmt|;
DECL|member|basey
name|gint
name|basey
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|update_areas
name|GSList
modifier|*
name|update_areas
decl_stmt|;
comment|/*  flushed update areas */
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_DISPLAY
define|#
directive|define
name|GIMP_TYPE_DISPLAY
value|(gimp_display_get_type ())
end_define

begin_define
DECL|macro|GIMP_DISPLAY (obj)
define|#
directive|define
name|GIMP_DISPLAY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DISPLAY, GimpDisplay))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_CLASS (klass)
define|#
directive|define
name|GIMP_DISPLAY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DISPLAY, GimpDisplayClass))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY (obj)
define|#
directive|define
name|GIMP_IS_DISPLAY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DISPLAY))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DISPLAY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DISPLAY))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DISPLAY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DISPLAY, GimpDisplayClass))
end_define

begin_typedef
DECL|typedef|GimpDisplayClass
typedef|typedef
name|struct
name|_GimpDisplayClass
name|GimpDisplayClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDisplay
struct|struct
name|_GimpDisplay
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  unique identifier for this gdisplay     */
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/*  pointer to the associated gimage        */
DECL|member|instance
name|gint
name|instance
decl_stmt|;
comment|/*  the instance # of this gdisplay as      */
comment|/*  taken from the gimage at creation       */
DECL|member|monitor_xres
name|gdouble
name|monitor_xres
decl_stmt|;
DECL|member|monitor_yres
name|gdouble
name|monitor_yres
decl_stmt|;
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
comment|/*  shell widget for this gdisplay          */
DECL|member|draw_guides
name|gboolean
name|draw_guides
decl_stmt|;
comment|/*  should the guides be drawn?             */
DECL|member|snap_to_guides
name|gboolean
name|snap_to_guides
decl_stmt|;
comment|/*  should the guides be snapped to?        */
DECL|member|update_areas
name|GSList
modifier|*
name|update_areas
decl_stmt|;
comment|/*  Update areas list                       */
DECL|member|idle_render
name|IdleRenderStruct
name|idle_render
decl_stmt|;
comment|/*  state of this gdisplay's render thread  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDisplayClass
struct|struct
name|_GimpDisplayClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_display_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDisplay
modifier|*
name|gimp_display_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guint
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_delete
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_display_get_ID
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplay
modifier|*
name|gimp_display_get_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_reconnect
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_add_update_area
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_flush
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_flush_now
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_finish_draw
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_coords_in_active_drawable
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DISPLAY_H__  */
end_comment

end_unit


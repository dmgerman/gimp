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

begin_comment
comment|/*  some useful macros  */
end_comment

begin_comment
comment|/* unpacking the user scale level (char) */
end_comment

begin_define
DECL|macro|SCALESRC (g)
define|#
directive|define
name|SCALESRC
parameter_list|(
name|g
parameter_list|)
value|(g->scale& 0x00ff)
end_define

begin_define
DECL|macro|SCALEDEST (g)
define|#
directive|define
name|SCALEDEST
parameter_list|(
name|g
parameter_list|)
value|(g->scale>> 8)
end_define

begin_comment
comment|/* finding the effective screen resolution (double) */
end_comment

begin_define
DECL|macro|SCREEN_XRES (g)
define|#
directive|define
name|SCREEN_XRES
parameter_list|(
name|g
parameter_list|)
value|(g->dot_for_dot ? \                            g->gimage->xresolution : gimprc.monitor_xres)
end_define

begin_define
DECL|macro|SCREEN_YRES (g)
define|#
directive|define
name|SCREEN_YRES
parameter_list|(
name|g
parameter_list|)
value|(g->dot_for_dot ? \                            g->gimage->yresolution : gimprc.monitor_yres)
end_define

begin_comment
comment|/* calculate scale factors (double) */
end_comment

begin_define
DECL|macro|SCALEFACTOR_X (g)
define|#
directive|define
name|SCALEFACTOR_X
parameter_list|(
name|g
parameter_list|)
value|((SCALEDEST(g) * SCREEN_XRES(g)) / \ 			   (SCALESRC(g) * g->gimage->xresolution))
end_define

begin_define
DECL|macro|SCALEFACTOR_Y (g)
define|#
directive|define
name|SCALEFACTOR_Y
parameter_list|(
name|g
parameter_list|)
value|((SCALEDEST(g) * SCREEN_YRES(g)) / \ 			   (SCALESRC(g) * g->gimage->yresolution))
end_define

begin_comment
comment|/* scale values */
end_comment

begin_define
DECL|macro|SCALEX (g,x)
define|#
directive|define
name|SCALEX
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|((gint) (x * SCALEFACTOR_X(g)))
end_define

begin_define
DECL|macro|SCALEY (g,y)
define|#
directive|define
name|SCALEY
parameter_list|(
name|g
parameter_list|,
name|y
parameter_list|)
value|((gint) (y * SCALEFACTOR_Y(g)))
end_define

begin_comment
comment|/* unscale values */
end_comment

begin_define
DECL|macro|UNSCALEX (g,x)
define|#
directive|define
name|UNSCALEX
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|((gint) (x / SCALEFACTOR_X(g)))
end_define

begin_define
DECL|macro|UNSCALEY (g,y)
define|#
directive|define
name|UNSCALEY
parameter_list|(
name|g
parameter_list|,
name|y
parameter_list|)
value|((gint) (y / SCALEFACTOR_Y(g)))
end_define

begin_comment
comment|/* (and float-returning versions) */
end_comment

begin_define
DECL|macro|FUNSCALEX (g,x)
define|#
directive|define
name|FUNSCALEX
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|(x / SCALEFACTOR_X(g))
end_define

begin_define
DECL|macro|FUNSCALEY (g,y)
define|#
directive|define
name|FUNSCALEY
parameter_list|(
name|g
parameter_list|,
name|y
parameter_list|)
value|(y / SCALEFACTOR_Y(g))
end_define

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
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
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

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|display_list
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* EEK */
end_comment

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
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
comment|/*  shell widget for this gdisplay          */
DECL|member|scale
name|gint
name|scale
decl_stmt|;
comment|/*  scale factor from original raw image    */
DECL|member|dot_for_dot
name|guint
name|dot_for_dot
range|:
literal|1
decl_stmt|;
comment|/*  is monitor resolution being ignored?    */
DECL|member|draw_guides
name|guint
name|draw_guides
range|:
literal|1
decl_stmt|;
comment|/*  should the guides be drawn?             */
DECL|member|snap_to_guides
name|guint
name|snap_to_guides
range|:
literal|1
decl_stmt|;
comment|/*  should the guides be snapped to?      */
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

begin_comment
comment|/*  stuff that will go to GimpDisplayShell  */
end_comment

begin_function_decl
name|void
name|gdisplay_transform_coords
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
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_untransform_coords
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
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|,
name|gboolean
name|round
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_transform_coords_f
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_untransform_coords_f
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
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


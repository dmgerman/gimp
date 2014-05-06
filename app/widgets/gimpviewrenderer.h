begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrenderer.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VIEW_RENDERER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VIEW_RENDERER_H__
define|#
directive|define
name|__GIMP_VIEW_RENDERER_H__
end_define

begin_define
DECL|macro|GIMP_VIEW_MAX_BORDER_WIDTH
define|#
directive|define
name|GIMP_VIEW_MAX_BORDER_WIDTH
value|16
end_define

begin_define
DECL|macro|GIMP_TYPE_VIEW_RENDERER
define|#
directive|define
name|GIMP_TYPE_VIEW_RENDERER
value|(gimp_view_renderer_get_type ())
end_define

begin_define
DECL|macro|GIMP_VIEW_RENDERER (obj)
define|#
directive|define
name|GIMP_VIEW_RENDERER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VIEW_RENDERER, GimpViewRenderer))
end_define

begin_define
DECL|macro|GIMP_VIEW_RENDERER_CLASS (klass)
define|#
directive|define
name|GIMP_VIEW_RENDERER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VIEW_RENDERER, GimpViewRendererClass))
end_define

begin_define
DECL|macro|GIMP_IS_VIEW_RENDERER (obj)
define|#
directive|define
name|GIMP_IS_VIEW_RENDERER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_VIEW_RENDERER))
end_define

begin_define
DECL|macro|GIMP_IS_VIEW_RENDERER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VIEW_RENDERER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VIEW_RENDERER))
end_define

begin_define
DECL|macro|GIMP_VIEW_RENDERER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VIEW_RENDERER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VIEW_RENDERER, GimpViewRendererClass))
end_define

begin_typedef
DECL|typedef|GimpViewRendererClass
typedef|typedef
name|struct
name|_GimpViewRendererClass
name|GimpViewRendererClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpViewRenderer
struct|struct
name|_GimpViewRenderer
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|viewable_type
name|GType
name|viewable_type
decl_stmt|;
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|border_width
name|gint
name|border_width
decl_stmt|;
DECL|member|dot_for_dot
name|guint
name|dot_for_dot
range|:
literal|1
decl_stmt|;
DECL|member|is_popup
name|guint
name|is_popup
range|:
literal|1
decl_stmt|;
DECL|member|border_type
name|GimpViewBorderType
name|border_type
decl_stmt|;
DECL|member|border_color
name|GimpRGB
name|border_color
decl_stmt|;
comment|/*< protected>*/
DECL|member|surface
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
comment|/*< private>*/
DECL|member|pattern
name|cairo_pattern_t
modifier|*
name|pattern
decl_stmt|;
DECL|member|pixbuf
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
DECL|member|bg_icon_name
name|gchar
modifier|*
name|bg_icon_name
decl_stmt|;
DECL|member|size
name|gint
name|size
decl_stmt|;
DECL|member|needs_render
name|gboolean
name|needs_render
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpViewRendererClass
struct|struct
name|_GimpViewRendererClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
DECL|member|frame
name|GdkPixbuf
modifier|*
name|frame
decl_stmt|;
DECL|member|frame_left
name|gint
name|frame_left
decl_stmt|;
DECL|member|frame_right
name|gint
name|frame_right
decl_stmt|;
DECL|member|frame_bottom
name|gint
name|frame_bottom
decl_stmt|;
DECL|member|frame_top
name|gint
name|frame_top
decl_stmt|;
comment|/*  signals  */
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|set_context
name|void
function_decl|(
modifier|*
name|set_context
function_decl|)
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
DECL|member|invalidate
name|void
function_decl|(
modifier|*
name|invalidate
function_decl|)
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|available_width
parameter_list|,
name|gint
name|available_height
parameter_list|)
function_decl|;
DECL|member|render
name|void
function_decl|(
modifier|*
name|render
function_decl|)
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_view_renderer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpViewRenderer
modifier|*
name|gimp_view_renderer_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GType
name|viewable_type
parameter_list|,
name|gint
name|size
parameter_list|,
name|gint
name|border_width
parameter_list|,
name|gboolean
name|is_popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpViewRenderer
modifier|*
name|gimp_view_renderer_new_full
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GType
name|viewable_type
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|border_width
parameter_list|,
name|gboolean
name|is_popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_context
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_viewable
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_size
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|gint
name|size
parameter_list|,
name|gint
name|border_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_size_full
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|border_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_dot_for_dot
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_border_type
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpViewBorderType
name|border_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_border_color
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|border_color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_set_background
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_invalidate
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_update
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_update_idle
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_remove_idle
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_draw
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|available_width
parameter_list|,
name|gint
name|available_height
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|void
name|gimp_view_renderer_render_temp_buf_simple
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpTempBuf
modifier|*
name|temp_buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_render_temp_buf
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpTempBuf
modifier|*
name|temp_buf
parameter_list|,
name|gint
name|temp_buf_x
parameter_list|,
name|gint
name|temp_buf_y
parameter_list|,
name|gint
name|channel
parameter_list|,
name|GimpViewBG
name|inside_bg
parameter_list|,
name|GimpViewBG
name|outside_bg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_render_pixbuf
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_view_renderer_render_icon
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_VIEW_RENDERER_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppreviewrenderer.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_RENDERER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_RENDERER_H__
define|#
directive|define
name|__GIMP_PREVIEW_RENDERER_H__
end_define

begin_define
DECL|macro|GIMP_PREVIEW_MAX_BORDER_WIDTH
define|#
directive|define
name|GIMP_PREVIEW_MAX_BORDER_WIDTH
value|16
end_define

begin_define
DECL|macro|GIMP_TYPE_PREVIEW_RENDERER
define|#
directive|define
name|GIMP_TYPE_PREVIEW_RENDERER
value|(gimp_preview_renderer_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER (obj)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREVIEW_RENDERER, GimpPreviewRenderer))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW_RENDERER, GimpPreviewRendererClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_RENDERER (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW_RENDERER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_PREVIEW_RENDERER))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_RENDERER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_RENDERER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW_RENDERER))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREVIEW_RENDERER, GimpPreviewRendererClass))
end_define

begin_typedef
DECL|typedef|GimpPreviewRendererClass
typedef|typedef
name|struct
name|_GimpPreviewRendererClass
name|GimpPreviewRendererClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPreviewRenderer
struct|struct
name|_GimpPreviewRenderer
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
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
name|gboolean
name|dot_for_dot
decl_stmt|;
DECL|member|is_popup
name|gboolean
name|is_popup
decl_stmt|;
DECL|member|border_type
name|GimpPreviewBorderType
name|border_type
decl_stmt|;
DECL|member|border_color
name|GimpRGB
name|border_color
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
comment|/*< private>*/
DECL|member|buffer
name|guchar
modifier|*
name|buffer
decl_stmt|;
DECL|member|rowstride
name|gint
name|rowstride
decl_stmt|;
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
DECL|member|no_preview_pixbuf
name|GdkPixbuf
modifier|*
name|no_preview_pixbuf
decl_stmt|;
DECL|member|bg_stock_id
name|gchar
modifier|*
name|bg_stock_id
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
DECL|struct|_GimpPreviewRendererClass
struct|struct
name|_GimpPreviewRendererClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|draw_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|expose_area
parameter_list|)
function_decl|;
DECL|member|render
name|void
function_decl|(
modifier|*
name|render
function_decl|)
parameter_list|(
name|GimpPreviewRenderer
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
name|gimp_preview_renderer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPreviewRenderer
modifier|*
name|gimp_preview_renderer_new
parameter_list|(
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
name|GimpPreviewRenderer
modifier|*
name|gimp_preview_renderer_new_full
parameter_list|(
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
name|gimp_preview_renderer_set_viewable
parameter_list|(
name|GimpPreviewRenderer
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
name|gimp_preview_renderer_set_size
parameter_list|(
name|GimpPreviewRenderer
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
name|gimp_preview_renderer_set_size_full
parameter_list|(
name|GimpPreviewRenderer
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
name|gimp_preview_renderer_set_dot_for_dot
parameter_list|(
name|GimpPreviewRenderer
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
name|gimp_preview_renderer_set_border_type
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpPreviewBorderType
name|border_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_set_border_color
parameter_list|(
name|GimpPreviewRenderer
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
name|gimp_preview_renderer_set_background
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_unrealize
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_invalidate
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_update
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_update_idle
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_remove_idle
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_draw
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|draw_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|expose_area
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|void
name|gimp_preview_renderer_default_render_buffer
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|TempBuf
modifier|*
name|temp_buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_default_render_stock
parameter_list|(
name|GimpPreviewRenderer
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
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_renderer_render_buffer
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|TempBuf
modifier|*
name|temp_buf
parameter_list|,
name|gint
name|channel
parameter_list|,
name|GimpPreviewBG
name|inside_bg
parameter_list|,
name|GimpPreviewBG
name|outside_bg
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  general purpose temp_buf to buffer projection function  */
end_comment

begin_function_decl
name|void
name|gimp_preview_render_to_buffer
parameter_list|(
name|TempBuf
modifier|*
name|temp_buf
parameter_list|,
name|gint
name|channel
parameter_list|,
name|GimpPreviewBG
name|inside_bg
parameter_list|,
name|GimpPreviewBG
name|outside_bg
parameter_list|,
name|guchar
modifier|*
name|dest_buffer
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|,
name|gint
name|dest_rowstride
parameter_list|,
name|gint
name|dest_bytes
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PREVIEW_RENDERER_H__ */
end_comment

end_unit


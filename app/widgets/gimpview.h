begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppreview.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_H__
define|#
directive|define
name|__GIMP_PREVIEW_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_PREVIEW
define|#
directive|define
name|GIMP_TYPE_PREVIEW
value|(gimp_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREVIEW (obj)
define|#
directive|define
name|GIMP_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREVIEW, GimpPreview))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW, GimpPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREVIEW, GimpPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpPreviewClass
typedef|typedef
name|struct
name|_GimpPreviewClass
name|GimpPreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPreview
struct|struct
name|_GimpPreview
block|{
DECL|member|parent_instance
name|GtkWidget
name|parent_instance
decl_stmt|;
DECL|member|event_window
name|GdkWindow
modifier|*
name|event_window
decl_stmt|;
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
DECL|member|renderer
name|GimpPreviewRenderer
modifier|*
name|renderer
decl_stmt|;
DECL|member|clickable
name|gboolean
name|clickable
decl_stmt|;
DECL|member|eat_button_events
name|gboolean
name|eat_button_events
decl_stmt|;
DECL|member|show_popup
name|gboolean
name|show_popup
decl_stmt|;
DECL|member|expand
name|gboolean
name|expand
decl_stmt|;
comment|/*< private>*/
DECL|member|in_button
name|gboolean
name|in_button
decl_stmt|;
DECL|member|press_state
name|GdkModifierType
name|press_state
decl_stmt|;
DECL|member|bg_stock_id
name|gchar
modifier|*
name|bg_stock_id
decl_stmt|;
DECL|member|bg_pixmap
name|GdkPixmap
modifier|*
name|bg_pixmap
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPreviewClass
struct|struct
name|_GimpPreviewClass
block|{
DECL|member|parent_class
name|GtkWidgetClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|clicked
name|void
function_decl|(
modifier|*
name|clicked
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GdkModifierType
name|modifier_state
parameter_list|)
function_decl|;
DECL|member|double_clicked
name|void
function_decl|(
modifier|*
name|double_clicked
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
DECL|member|context
name|void
function_decl|(
modifier|*
name|context
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_preview_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
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
name|GtkWidget
modifier|*
name|gimp_preview_new_full
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
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
parameter_list|,
name|gboolean
name|clickable
parameter_list|,
name|gboolean
name|show_popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_preview_new_by_types
parameter_list|(
name|GType
name|preview_type
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
name|GtkWidget
modifier|*
name|gimp_preview_new_full_by_types
parameter_list|(
name|GType
name|preview_type
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
parameter_list|,
name|gboolean
name|clickable
parameter_list|,
name|gboolean
name|show_popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_viewable
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_size
parameter_list|(
name|GimpPreview
modifier|*
name|preview
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
name|gimp_preview_set_size_full
parameter_list|(
name|GimpPreview
modifier|*
name|preview
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
name|gimp_preview_set_expand
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gboolean
name|expand
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_dot_for_dot
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_border_color
parameter_list|(
name|GimpPreview
modifier|*
name|preview
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
name|gimp_preview_set_background
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PREVIEW_H__ */
end_comment

end_unit


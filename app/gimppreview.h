begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpPreview Widget  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<gtk/gtkpreview.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GIMP_TYPE_PREVIEW
define|#
directive|define
name|GIMP_TYPE_PREVIEW
value|(gimp_preview_get_type ())
DECL|macro|GIMP_PREVIEW (obj)
define|#
directive|define
name|GIMP_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_PREVIEW, GimpPreview))
DECL|macro|GIMP_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW, GimpPreviewClass))
DECL|macro|GIMP_IS_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_PREVIEW))
DECL|macro|GIMP_IS_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW))
DECL|typedef|GimpPreviewClass
typedef|typedef
name|struct
name|_GimpPreviewClass
name|GimpPreviewClass
typedef|;
DECL|struct|_GimpPreview
struct|struct
name|_GimpPreview
block|{
DECL|member|parent_instance
name|GtkPreview
name|parent_instance
decl_stmt|;
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
DECL|member|clickable
name|gboolean
name|clickable
decl_stmt|;
DECL|member|show_popup
name|gboolean
name|show_popup
decl_stmt|;
DECL|member|in_button
name|gboolean
name|in_button
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|popup_id
name|guint
name|popup_id
decl_stmt|;
DECL|member|popup_x
name|gint
name|popup_x
decl_stmt|;
DECL|member|popup_y
name|gint
name|popup_y
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpPreviewClass
struct|struct
name|_GimpPreviewClass
block|{
DECL|member|parent_class
name|GtkPreviewClass
name|parent_class
decl_stmt|;
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
parameter_list|)
function_decl|;
block|}
struct|;
name|GtkType
name|gimp_preview_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_preview_new
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
name|gboolean
name|clickable
parameter_list|,
name|gboolean
name|show_popup
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PREVIEW_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_PREVIEW_H_
define|#
directive|define
name|__GIMP_BRUSH_PREVIEW_H_
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
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
DECL|macro|GIMP_TYPE_BRUSH_PREVIEW
define|#
directive|define
name|GIMP_TYPE_BRUSH_PREVIEW
value|(gimp_brush_preview_get_type ())
DECL|macro|GIMP_BRUSH_PREVIEW (obj)
define|#
directive|define
name|GIMP_BRUSH_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_PREVIEW, GimpBrushPreview))
DECL|macro|GIMP_BRUSH_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH_PREVIEW, GimpBrushPreviewClass))
DECL|macro|GIMP_IS_BRUSH_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_BRUSH_PREVIEW))
DECL|macro|GIMP_IS_BRUSH_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH_PREVIEW))
DECL|typedef|GimpBrushPreview
typedef|typedef
name|struct
name|_GimpBrushPreview
name|GimpBrushPreview
typedef|;
DECL|typedef|GimpBrushPreviewClass
typedef|typedef
name|struct
name|_GimpBrushPreviewClass
name|GimpBrushPreviewClass
typedef|;
DECL|struct|_GimpBrushPreview
struct|struct
name|_GimpBrushPreview
block|{
DECL|member|preview
name|GtkPreview
name|preview
decl_stmt|;
DECL|member|brush
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|tooltips
name|GtkTooltips
modifier|*
name|tooltips
decl_stmt|;
DECL|member|popup
name|GtkWidget
modifier|*
name|popup
decl_stmt|;
DECL|member|popup_preview
name|GtkWidget
modifier|*
name|popup_preview
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpBrushPreviewClass
struct|struct
name|_GimpBrushPreviewClass
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
name|GimpBrushPreview
modifier|*
name|gbp
parameter_list|)
function_decl|;
block|}
struct|;
name|GtkType
name|gimp_brush_preview_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_brush_preview_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
name|void
name|gimp_brush_preview_update
parameter_list|(
name|GimpBrushPreview
modifier|*
name|gbp
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
name|void
name|gimp_brush_preview_set_tooltips
parameter_list|(
name|GimpBrushPreview
modifier|*
name|gbp
parameter_list|,
name|GtkTooltips
modifier|*
name|tooltips
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
comment|/* __GIMP_BRUSH_PREVIEW_H__ */
end_comment

end_unit


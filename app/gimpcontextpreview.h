begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpContextPreview Widget  * Copyright (C) 1999 Sven Neumann  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTEXT_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTEXT_PREVIEW_H_
define|#
directive|define
name|__GIMP_CONTEXT_PREVIEW_H_
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
DECL|macro|GIMP_TYPE_CONTEXT_PREVIEW
define|#
directive|define
name|GIMP_TYPE_CONTEXT_PREVIEW
value|(gimp_context_preview_get_type ())
DECL|macro|GIMP_CONTEXT_PREVIEW (obj)
define|#
directive|define
name|GIMP_CONTEXT_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_CONTEXT_PREVIEW, GimpContextPreview))
DECL|macro|GIMP_CONTEXT_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_CONTEXT_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTEXT_PREVIEW, GimpContextPreviewClass))
DECL|macro|GIMP_IS_CONTEXT_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_CONTEXT_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_CONTEXT_PREVIEW))
DECL|macro|GIMP_IS_CONTEXT_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTEXT_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTEXT_PREVIEW))
DECL|typedef|GimpContextPreview
typedef|typedef
name|struct
name|_GimpContextPreview
name|GimpContextPreview
typedef|;
DECL|typedef|GimpContextPreviewClass
typedef|typedef
name|struct
name|_GimpContextPreviewClass
name|GimpContextPreviewClass
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon2c7810f40103
block|{
DECL|enumerator|GCP_BRUSH
name|GCP_BRUSH
init|=
literal|0
block|,
DECL|enumerator|GCP_PATTERN
name|GCP_PATTERN
block|,
DECL|enumerator|GCP_LAST
name|GCP_LAST
DECL|typedef|GimpContextPreviewType
block|}
name|GimpContextPreviewType
typedef|;
DECL|struct|_GimpContextPreview
struct|struct
name|_GimpContextPreview
block|{
DECL|member|preview
name|GtkPreview
name|preview
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|type
name|GimpContextPreviewType
name|type
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|show_tooltips
name|gboolean
name|show_tooltips
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpContextPreviewClass
struct|struct
name|_GimpContextPreviewClass
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
name|GimpContextPreview
modifier|*
name|gbp
parameter_list|)
function_decl|;
block|}
struct|;
name|GtkType
name|gimp_context_preview_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_context_preview_new
parameter_list|(
name|GimpContextPreviewType
name|type
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|show_tooltips
parameter_list|)
function_decl|;
name|void
name|gimp_context_preview_update
parameter_list|(
name|GimpContextPreview
modifier|*
name|gcp
parameter_list|,
name|gpointer
name|data
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
comment|/* __GIMP_CONTEXT_PREVIEW_H__ */
end_comment

end_unit


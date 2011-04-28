begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpzoompreview.h  * Copyright (C) 2005  David Odin<dindinx@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ZOOM_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ZOOM_PREVIEW_H__
define|#
directive|define
name|__GIMP_ZOOM_PREVIEW_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_ZOOM_PREVIEW
define|#
directive|define
name|GIMP_TYPE_ZOOM_PREVIEW
value|(gimp_zoom_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_ZOOM_PREVIEW (obj)
define|#
directive|define
name|GIMP_ZOOM_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ZOOM_PREVIEW, GimpZoomPreview))
end_define

begin_define
DECL|macro|GIMP_ZOOM_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_ZOOM_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ZOOM_PREVIEW, GimpZoomPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_ZOOM_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_ZOOM_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ZOOM_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_ZOOM_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ZOOM_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ZOOM_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_ZOOM_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ZOOM_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ZOOM_PREVIEW, GimpZoomPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpZoomPreviewClass
typedef|typedef
name|struct
name|_GimpZoomPreviewClass
name|GimpZoomPreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpZoomPreview
struct|struct
name|_GimpZoomPreview
block|{
DECL|member|parent_instance
name|GimpScrolledPreview
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpZoomPreviewClass
struct|struct
name|_GimpZoomPreviewClass
block|{
DECL|member|parent_class
name|GimpScrolledPreviewClass
name|parent_class
decl_stmt|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_zoom_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_zoom_preview_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_zoom_preview_new_with_model
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpZoomModel
modifier|*
name|model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_zoom_preview_get_source
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_zoom_preview_get_drawable
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpZoomModel
modifier|*
name|gimp_zoom_preview_get_model
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_zoom_preview_get_factor
parameter_list|(
name|GimpZoomPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ZOOM_PREVIEW_H__ */
end_comment

end_unit


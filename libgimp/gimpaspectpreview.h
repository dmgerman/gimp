begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpaspectpreview.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ASPECT_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ASPECT_PREVIEW_H__
define|#
directive|define
name|__GIMP_ASPECT_PREVIEW_H__
end_define

begin_include
include|#
directive|include
file|<libgimpwidgets/gimppreview.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_ASPECT_PREVIEW
define|#
directive|define
name|GIMP_TYPE_ASPECT_PREVIEW
value|(gimp_aspect_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_ASPECT_PREVIEW (obj)
define|#
directive|define
name|GIMP_ASPECT_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ASPECT_PREVIEW, GimpAspectPreview))
end_define

begin_define
DECL|macro|GIMP_ASPECT_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_ASPECT_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ASPECT_PREVIEW, GimpAspectPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_ASPECT_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_ASPECT_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ASPECT_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_ASPECT_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ASPECT_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ASPECT_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_ASPECT_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ASPECT_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ASPECT_PREVIEW, GimpAspectPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpAspectPreviewClass
typedef|typedef
name|struct
name|_GimpAspectPreviewClass
name|GimpAspectPreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAspectPreview
struct|struct
name|_GimpAspectPreview
block|{
DECL|member|parent_instance
name|GimpPreview
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpAspectPreviewClass
struct|struct
name|_GimpAspectPreviewClass
block|{
DECL|member|parent_class
name|GimpPreviewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_aspect_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_aspect_preview_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
modifier|*
name|toggle
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
comment|/* __GIMP_ASPECT_PREVIEW_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbufferpreview.h  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BUFFER_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BUFFER_PREVIEW_H__
define|#
directive|define
name|__GIMP_BUFFER_PREVIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimppreview.h"
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
DECL|macro|GIMP_TYPE_BUFFER_PREVIEW
define|#
directive|define
name|GIMP_TYPE_BUFFER_PREVIEW
value|(gimp_buffer_preview_get_type ())
DECL|macro|GIMP_BUFFER_PREVIEW (obj)
define|#
directive|define
name|GIMP_BUFFER_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BUFFER_PREVIEW, GimpBufferPreview))
DECL|macro|GIMP_BUFFER_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_BUFFER_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BUFFER_PREVIEW, GimpBufferPreviewClass))
DECL|macro|GIMP_IS_BUFFER_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_BUFFER_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_BUFFER_PREVIEW))
DECL|macro|GIMP_IS_BUFFER_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BUFFER_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BUFFER_PREVIEW))
DECL|macro|GIMP_BUFFER_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BUFFER_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BUFFER_PREVIEW, GimpBufferPreviewClass))
DECL|typedef|GimpBufferPreviewClass
typedef|typedef
name|struct
name|_GimpBufferPreviewClass
name|GimpBufferPreviewClass
typedef|;
DECL|struct|_GimpBufferPreview
struct|struct
name|_GimpBufferPreview
block|{
DECL|member|parent_instance
name|GimpPreview
name|parent_instance
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpBufferPreviewClass
struct|struct
name|_GimpBufferPreviewClass
block|{
DECL|member|parent_class
name|GimpPreviewClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|GType
name|gimp_buffer_preview_get_type
parameter_list|(
name|void
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
comment|/* __GIMP_BUFFER_PREVIEW_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppreviewrenderertextlayer.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_RENDERER_TEXT_LAYER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_RENDERER_TEXT_LAYER_H__
define|#
directive|define
name|__GIMP_PREVIEW_RENDERER_TEXT_LAYER_H__
end_define

begin_include
include|#
directive|include
file|"gimppreviewrendererdrawable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PREVIEW_RENDERER_TEXT_LAYER
define|#
directive|define
name|GIMP_TYPE_PREVIEW_RENDERER_TEXT_LAYER
value|(gimp_preview_renderer_text_layer_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_TEXT_LAYER (obj)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_TEXT_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREVIEW_RENDERER_TEXT_LAYER, GimpPreviewRendererTextLayer))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_TEXT_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_TEXT_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW_RENDERER_TEXT_LAYER, GimpPreviewRendererTextLayerClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_RENDERER_TEXT_LAYER (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW_RENDERER_TEXT_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_PREVIEW_RENDERER_TEXT_LAYER))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_RENDERER_TEXT_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_RENDERER_TEXT_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW_RENDERER_TEXT_LAYER))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_TEXT_LAYER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_TEXT_LAYER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREVIEW_RENDERER_TEXT_LAYER, GimpPreviewRendererTextLayerClass))
end_define

begin_typedef
DECL|typedef|GimpPreviewRendererTextLayerClass
typedef|typedef
name|struct
name|_GimpPreviewRendererTextLayerClass
name|GimpPreviewRendererTextLayerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPreviewRendererTextLayer
struct|struct
name|_GimpPreviewRendererTextLayer
block|{
DECL|member|parent_instance
name|GimpPreviewRendererDrawable
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPreviewRendererTextLayerClass
struct|struct
name|_GimpPreviewRendererTextLayerClass
block|{
DECL|member|parent_class
name|GimpPreviewRendererDrawableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_preview_renderer_text_layer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PREVIEW_RENDERER_TEXT_LAYER_H__ */
end_comment

end_unit


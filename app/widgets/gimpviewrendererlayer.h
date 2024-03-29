begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererlayer.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VIEW_RENDERER_LAYER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VIEW_RENDERER_LAYER_H__
define|#
directive|define
name|__GIMP_VIEW_RENDERER_LAYER_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewrendererdrawable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_VIEW_RENDERER_LAYER
define|#
directive|define
name|GIMP_TYPE_VIEW_RENDERER_LAYER
value|(gimp_view_renderer_layer_get_type ())
end_define

begin_define
DECL|macro|GIMP_VIEW_RENDERER_LAYER (obj)
define|#
directive|define
name|GIMP_VIEW_RENDERER_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VIEW_RENDERER_LAYER, GimpViewRendererLayer))
end_define

begin_define
DECL|macro|GIMP_VIEW_RENDERER_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_VIEW_RENDERER_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VIEW_RENDERER_LAYER, GimpViewRendererLayerClass))
end_define

begin_define
DECL|macro|GIMP_IS_VIEW_RENDERER_LAYER (obj)
define|#
directive|define
name|GIMP_IS_VIEW_RENDERER_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_VIEW_RENDERER_LAYER))
end_define

begin_define
DECL|macro|GIMP_IS_VIEW_RENDERER_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VIEW_RENDERER_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VIEW_RENDERER_LAYER))
end_define

begin_define
DECL|macro|GIMP_VIEW_RENDERER_LAYER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VIEW_RENDERER_LAYER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VIEW_RENDERER_LAYER, GimpViewRendererLayerClass))
end_define

begin_typedef
DECL|typedef|GimpViewRendererLayerClass
typedef|typedef
name|struct
name|_GimpViewRendererLayerClass
name|GimpViewRendererLayerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpViewRendererLayer
struct|struct
name|_GimpViewRendererLayer
block|{
DECL|member|parent_instance
name|GimpViewRendererDrawable
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpViewRendererLayerClass
struct|struct
name|_GimpViewRendererLayerClass
block|{
DECL|member|parent_class
name|GimpViewRendererDrawableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_view_renderer_layer_get_type
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
comment|/* __GIMP_VIEW_RENDERER_LAYER_H__ */
end_comment

end_unit


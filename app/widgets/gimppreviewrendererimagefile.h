begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppreviewrendererimagefile.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_RENDERER_IMAGEFILE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_RENDERER_IMAGEFILE_H__
define|#
directive|define
name|__GIMP_PREVIEW_RENDERER_IMAGEFILE_H__
end_define

begin_include
include|#
directive|include
file|"gimppreviewrenderer.h"
end_include

begin_comment
comment|/* #define ENABLE_FILE_SYSTEM_ICONS 1 */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PREVIEW_RENDERER_IMAGEFILE
define|#
directive|define
name|GIMP_TYPE_PREVIEW_RENDERER_IMAGEFILE
value|(gimp_preview_renderer_imagefile_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_IMAGEFILE (obj)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_IMAGEFILE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREVIEW_RENDERER_IMAGEFILE, GimpPreviewRendererImagefile))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_IMAGEFILE_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_IMAGEFILE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW_RENDERER_IMAGEFILE, GimpPreviewRendererImagefileClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_RENDERER_IMAGEFILE (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW_RENDERER_IMAGEFILE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_PREVIEW_RENDERER_IMAGEFILE))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_RENDERER_IMAGEFILE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_RENDERER_IMAGEFILE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW_RENDERER_IMAGEFILE))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_RENDERER_IMAGEFILE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREVIEW_RENDERER_IMAGEFILE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREVIEW_RENDERER_IMAGEFILE, GimpPreviewRendererImagefileClass))
end_define

begin_typedef
DECL|typedef|GimpPreviewRendererImagefileClass
typedef|typedef
name|struct
name|_GimpPreviewRendererImagefileClass
name|GimpPreviewRendererImagefileClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPreviewRendererImagefile
struct|struct
name|_GimpPreviewRendererImagefile
block|{
DECL|member|parent_instance
name|GimpPreviewRenderer
name|parent_instance
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_FILE_SYSTEM_ICONS
DECL|member|file_system
name|gpointer
name|file_system
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPreviewRendererImagefileClass
struct|struct
name|_GimpPreviewRendererImagefileClass
block|{
DECL|member|parent_class
name|GimpPreviewRendererClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_preview_renderer_imagefile_get_type
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
comment|/* __GIMP_PREVIEW_RENDERER_IMAGEFILE_H__ */
end_comment

end_unit


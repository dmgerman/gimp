begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppreviewrenderertextlayer.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrenderertextlayer.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_preview_renderer_text_layer_class_init
parameter_list|(
name|GimpPreviewRendererTextLayerClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_renderer_text_layer_init
parameter_list|(
name|GimpPreviewRendererTextLayer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_renderer_text_layer_render
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPreviewRendererDrawableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_preview_renderer_text_layer_get_type (void)
name|gimp_preview_renderer_text_layer_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|renderer_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|renderer_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|renderer_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPreviewRendererTextLayerClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_preview_renderer_text_layer_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpPreviewRendererTextLayer
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_preview_renderer_text_layer_init
block|,       }
decl_stmt|;
name|renderer_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PREVIEW_RENDERER_DRAWABLE
argument_list|,
literal|"GimpPreviewRendererTextLayer"
argument_list|,
operator|&
name|renderer_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|renderer_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_renderer_text_layer_class_init (GimpPreviewRendererTextLayerClass * klass)
name|gimp_preview_renderer_text_layer_class_init
parameter_list|(
name|GimpPreviewRendererTextLayerClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPreviewRendererClass
modifier|*
name|renderer_class
decl_stmt|;
name|renderer_class
operator|=
name|GIMP_PREVIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_preview_renderer_text_layer_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_renderer_text_layer_init (GimpPreviewRendererTextLayer * renderer)
name|gimp_preview_renderer_text_layer_init
parameter_list|(
name|GimpPreviewRendererTextLayer
modifier|*
name|renderer
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_renderer_text_layer_render (GimpPreviewRenderer * renderer,GtkWidget * widget)
name|gimp_preview_renderer_text_layer_render
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gimp_preview_renderer_default_render_stock
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


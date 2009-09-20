begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererlayer.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererlayer.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_layer_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpViewRendererLayer,gimp_view_renderer_layer,GIMP_TYPE_VIEW_RENDERER_DRAWABLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpViewRendererLayer
argument_list|,
argument|gimp_view_renderer_layer
argument_list|,
argument|GIMP_TYPE_VIEW_RENDERER_DRAWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_layer_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_view_renderer_layer_class_init
parameter_list|(
name|GimpViewRendererLayerClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpViewRendererClass
modifier|*
name|renderer_class
init|=
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_view_renderer_layer_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_layer_init (GimpViewRendererLayer * renderer)
name|gimp_view_renderer_layer_init
parameter_list|(
name|GimpViewRendererLayer
modifier|*
name|renderer
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_layer_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_layer_render
parameter_list|(
name|GimpViewRenderer
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
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|GIMP_LAYER
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|stock_id
operator|=
name|GIMP_STOCK_FLOATING_SELECTION
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_drawable_is_text_layer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpContainer
modifier|*
name|children
init|=
name|gimp_viewable_get_children
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|children
operator|&&
name|gimp_container_get_n_children
argument_list|(
name|children
argument_list|)
operator|==
literal|0
condition|)
name|stock_id
operator|=
name|GTK_STOCK_DIRECTORY
expr_stmt|;
block|}
if|if
condition|(
name|stock_id
condition|)
name|gimp_view_renderer_default_render_stock
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
else|else
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|render
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


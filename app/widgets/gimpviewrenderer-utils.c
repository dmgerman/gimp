begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrenderer-utils.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderergradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererimagefile.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererpalette.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderervectors.h"
end_include

begin_function
name|GType
DECL|function|gimp_view_renderer_type_from_viewable_type (GType viewable_type)
name|gimp_view_renderer_type_from_viewable_type
parameter_list|(
name|GType
name|viewable_type
parameter_list|)
block|{
name|GType
name|type
init|=
name|GIMP_TYPE_VIEW_RENDERER
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_VIEWABLE
argument_list|)
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_BRUSH
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_BUFFER
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_IMAGE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_LAYER
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_DRAWABLE
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_DRAWABLE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_GRADIENT
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_GRADIENT
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_VECTORS
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_IMAGEFILE
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_IMAGEFILE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_type_is_a
argument_list|(
name|viewable_type
argument_list|,
name|GIMP_TYPE_PALETTE
argument_list|)
condition|)
block|{
name|type
operator|=
name|GIMP_TYPE_VIEW_RENDERER_PALETTE
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

end_unit


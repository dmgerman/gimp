begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppreviewrenderer-utils.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrendererbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrendererdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrendererimage.h"
end_include

begin_function
name|GType
DECL|function|gimp_preview_renderer_type_from_viewable_type (GType viewable_type)
name|gimp_preview_renderer_type_from_viewable_type
parameter_list|(
name|GType
name|viewable_type
parameter_list|)
block|{
name|GType
name|type
init|=
name|GIMP_TYPE_PREVIEW_RENDERER
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
name|GIMP_TYPE_PREVIEW_RENDERER_BRUSH
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
name|GIMP_TYPE_PREVIEW_RENDERER_IMAGE
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
name|GIMP_TYPE_PREVIEW_RENDERER_DRAWABLE
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

end_unit


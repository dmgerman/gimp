begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDrawablePreview Widget  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablepreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_class_init
parameter_list|(
name|GimpDrawablePreviewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_init
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_render
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_drawable_preview_create_popup
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPreviewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_drawable_preview_get_type (void)
name|gimp_drawable_preview_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|preview_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|preview_type
condition|)
block|{
name|GtkTypeInfo
name|preview_info
init|=
block|{
literal|"GimpDrawablePreview"
block|,
sizeof|sizeof
argument_list|(
name|GimpDrawablePreview
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpDrawablePreviewClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_drawable_preview_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_drawable_preview_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|preview_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_PREVIEW
argument_list|,
operator|&
name|preview_info
argument_list|)
expr_stmt|;
block|}
return|return
name|preview_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_class_init (GimpDrawablePreviewClass * klass)
name|gimp_drawable_preview_class_init
parameter_list|(
name|GimpDrawablePreviewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpPreviewClass
modifier|*
name|preview_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|preview_class
operator|=
operator|(
name|GimpPreviewClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_PREVIEW
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_init (GimpDrawablePreview * preview)
name|gimp_drawable_preview_init
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|preview
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_render (GimpPreview * preview)
name|gimp_drawable_preview_render
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_drawable_preview_create_popup (GimpPreview * preview)
name|gimp_drawable_preview_create_popup
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{ }
end_function

end_unit


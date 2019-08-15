begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpselection.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSelection,gimp_selection,GIMP_TYPE_CHANNEL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSelection
argument_list|,
argument|gimp_selection
argument_list|,
argument|GIMP_TYPE_CHANNEL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_selection_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_selection_class_init
parameter_list|(
name|GimpSelectionClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_init (GimpSelection * selection)
name|gimp_selection_init
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|)
block|{ }
end_function

begin_comment
comment|/**  * gimp_selection_float:  * @image: ignored  * @drawable: The drawable from which to float selection.  * @offx: x offset for translation.  * @offy: y offset for translation.  *  * Float the selection from the specified drawable with initial offsets  * as specified.  *  * This procedure determines the region of the specified drawable that  * lies beneath the current selection. The region is then cut from the  * drawable and the resulting data is made into a new layer which is  * instantiated as a floating selection. The offsets allow initial  * positioning of the new floating selection.  *  * Returns: (transfer full): The floated layer.  */
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_selection_float (GimpImage * image,GimpDrawable * drawable,gint offx,gint offy)
name|gimp_selection_float
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
block|{
return|return
name|_gimp_selection_float
argument_list|(
name|drawable
argument_list|,
name|offx
argument_list|,
name|offy
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* Deprecated API. */
end_comment

begin_comment
comment|/**  * gimp_selection_float_deprecated: (skip)  * @image_ID: ignored  * @drawable_ID: The drawable from which to float selection.  * @offx: x offset for translation.  * @offy: y offset for translation.  *  * Float the selection from the specified drawable with initial offsets  * as specified.  *  * This procedure determines the region of the specified drawable that  * lies beneath the current selection. The region is then cut from the  * drawable and the resulting data is made into a new layer which is  * instantiated as a floating selection. The offsets allow initial  * positioning of the new floating selection.  *  * Returns: The floated layer.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_selection_float_deprecated (gint32 image_ID,gint32 drawable_ID,gint offx,gint offy)
name|gimp_selection_float_deprecated
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpLayer
modifier|*
name|selection
decl_stmt|;
name|gint32
name|selection_id
init|=
operator|-
literal|1
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_item_new_by_id
argument_list|(
name|drawable_ID
argument_list|)
argument_list|)
expr_stmt|;
name|selection
operator|=
name|gimp_selection_float
argument_list|(
name|gimp_image_get_by_id
argument_list|(
name|image_ID
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|offx
argument_list|,
name|offy
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
condition|)
name|selection_id
operator|=
name|gimp_item_get_id
argument_list|(
name|GIMP_ITEM
argument_list|(
name|selection
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|selection
argument_list|)
expr_stmt|;
return|return
name|selection_id
return|;
block|}
end_function

end_unit


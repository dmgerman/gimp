begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintinfo.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_paint_info_class_init
parameter_list|(
name|GimpPaintInfoClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paint_info_init
parameter_list|(
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paint_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_paint_info_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_paint_info_get_type (void)
name|gimp_paint_info_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|paint_info_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|paint_info_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|paint_info_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPaintInfoClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_paint_info_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPaintInfo
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_paint_info_init
block|,         }
decl_stmt|;
name|paint_info_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
literal|"GimpPaintInfo"
argument_list|,
operator|&
name|paint_info_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|paint_info_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_info_class_init (GimpPaintInfoClass * klass)
name|gimp_paint_info_class_init
parameter_list|(
name|GimpPaintInfoClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_paint_info_finalize
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_paint_info_get_description
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_info_init (GimpPaintInfo * paint_info)
name|gimp_paint_info_init
parameter_list|(
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
block|{
name|paint_info
operator|->
name|gimp
operator|=
name|NULL
expr_stmt|;
name|paint_info
operator|->
name|paint_type
operator|=
name|G_TYPE_NONE
expr_stmt|;
name|paint_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
name|paint_info
operator|->
name|paint_options
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_info_finalize (GObject * object)
name|gimp_paint_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
name|paint_info
operator|=
name|GIMP_PAINT_INFO
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|paint_info
operator|->
name|blurb
condition|)
block|{
name|g_free
argument_list|(
name|paint_info
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|paint_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|paint_info
operator|->
name|paint_options
condition|)
block|{
name|g_object_unref
argument_list|(
name|paint_info
operator|->
name|paint_options
argument_list|)
expr_stmt|;
name|paint_info
operator|->
name|paint_options
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_paint_info_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_paint_info_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
init|=
name|GIMP_PAINT_INFO
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|tooltip
condition|)
operator|*
name|tooltip
operator|=
name|NULL
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|paint_info
operator|->
name|blurb
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPaintInfo
modifier|*
DECL|function|gimp_paint_info_new (Gimp * gimp,GType paint_type,GType paint_options_type,const gchar * blurb)
name|gimp_paint_info_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|paint_type
parameter_list|,
name|GType
name|paint_options_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|blurb
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|paint_info
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PAINT_INFO
argument_list|,
literal|"name"
argument_list|,
name|g_type_name
argument_list|(
name|paint_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|paint_info
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|paint_info
operator|->
name|paint_type
operator|=
name|paint_type
expr_stmt|;
name|paint_info
operator|->
name|paint_options_type
operator|=
name|paint_options_type
expr_stmt|;
name|paint_info
operator|->
name|blurb
operator|=
name|g_strdup
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|paint_info
operator|->
name|paint_options
operator|=
name|gimp_paint_options_new
argument_list|(
name|paint_info
argument_list|)
expr_stmt|;
return|return
name|paint_info
return|;
block|}
end_function

end_unit


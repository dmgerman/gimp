begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfontlist.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *                    Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangoft2.h>
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpfont.h"
end_include

begin_include
include|#
directive|include
file|"gimpfontlist.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_font_list_class_init
parameter_list|(
name|GimpFontListClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_list_init
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_list_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_font_list_font_compare_func
parameter_list|(
name|gconstpointer
name|first
parameter_list|,
name|gconstpointer
name|second
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpListClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_font_list_get_type (void)
name|gimp_font_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|list_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|list_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|list_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpFontListClass
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
name|gimp_font_list_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_font     */
sizeof|sizeof
argument_list|(
name|GimpFontList
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_font_list_init
block|,       }
decl_stmt|;
name|list_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_LIST
argument_list|,
literal|"GimpFontList"
argument_list|,
operator|&
name|list_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|list_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_class_init (GimpFontListClass * klass)
name|gimp_font_list_class_init
parameter_list|(
name|GimpFontListClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpContainerClass
modifier|*
name|container_class
decl_stmt|;
name|container_class
operator|=
name|GIMP_CONTAINER_CLASS
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
name|container_class
operator|->
name|add
operator|=
name|gimp_font_list_add
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_init (GimpFontList * list)
name|gimp_font_list_init
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_add (GimpContainer * container,GimpObject * object)
name|gimp_font_list_add
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|list
operator|->
name|list
operator|=
name|g_list_insert_sorted
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|,
name|gimp_font_list_font_compare_func
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_font_list_new (gdouble xresolution,gdouble yresolution)
name|gimp_font_list_new
parameter_list|(
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|)
block|{
name|GimpFontList
modifier|*
name|list
decl_stmt|;
name|PangoContext
modifier|*
name|pango_context
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|xresolution
operator|>
literal|0.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|yresolution
operator|>
literal|0.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT_LIST
argument_list|,
literal|"children_type"
argument_list|,
name|GIMP_TYPE_FONT
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|->
name|xresolution
operator|=
name|xresolution
expr_stmt|;
name|list
operator|->
name|yresolution
operator|=
name|yresolution
expr_stmt|;
name|pango_context
operator|=
name|pango_ft2_get_context
argument_list|(
name|xresolution
argument_list|,
name|yresolution
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"pango-context"
argument_list|,
name|pango_context
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
return|return
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_font_list_restore (GimpFontList * list)
name|gimp_font_list_restore
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|)
block|{
name|PangoContext
modifier|*
name|pango_context
decl_stmt|;
name|PangoFontFamily
modifier|*
modifier|*
name|families
decl_stmt|;
name|PangoFontFace
modifier|*
modifier|*
name|faces
decl_stmt|;
name|gint
name|n_families
decl_stmt|;
name|gint
name|n_faces
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FONT_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|pango_context
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
literal|"pango-context"
argument_list|)
expr_stmt|;
name|pango_context_list_families
argument_list|(
name|pango_context
argument_list|,
operator|&
name|families
argument_list|,
operator|&
name|n_families
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_families
condition|;
name|i
operator|++
control|)
block|{
name|pango_font_family_list_faces
argument_list|(
name|families
index|[
name|i
index|]
argument_list|,
operator|&
name|faces
argument_list|,
operator|&
name|n_faces
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|n_faces
condition|;
name|j
operator|++
control|)
block|{
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|GimpFont
modifier|*
name|font
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|desc
operator|=
name|pango_font_face_describe
argument_list|(
name|faces
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|name
operator|=
name|pango_font_description_to_string
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|font
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"pango-context"
argument_list|,
name|pango_context
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|font
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|font
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|families
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_font_list_font_compare_func (gconstpointer first,gconstpointer second)
name|gimp_font_list_font_compare_func
parameter_list|(
name|gconstpointer
name|first
parameter_list|,
name|gconstpointer
name|second
parameter_list|)
block|{
return|return
name|strcmp
argument_list|(
operator|(
operator|(
specifier|const
name|GimpObject
operator|*
operator|)
name|first
operator|)
operator|->
name|name
argument_list|,
operator|(
operator|(
specifier|const
name|GimpObject
operator|*
operator|)
name|second
operator|)
operator|->
name|name
argument_list|)
return|;
block|}
end_function

end_unit


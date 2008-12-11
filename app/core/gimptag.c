begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptag.c  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimptag.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpTag,gimp_tag,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpTag
argument_list|,
argument|gimp_tag
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tag_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tag_class_init
parameter_list|(
name|GimpTagClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tag_init (GimpTag * tag)
name|gimp_tag_init
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|)
block|{ }
end_function

begin_comment
comment|/**  * gimp_tag_equals:  * @tag:   a gimp tag.  * @other: another gimp tag to compare with.  *  * Compares tags for equality according to tag comparison rules.  *  * Return value: TRUE if tags are equal, FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_tag_equals (const GimpTag * tag,const GimpTag * other)
name|gimp_tag_equals
parameter_list|(
specifier|const
name|GimpTag
modifier|*
name|tag
parameter_list|,
specifier|const
name|GimpTag
modifier|*
name|other
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|tag
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TAG
argument_list|(
name|other
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit


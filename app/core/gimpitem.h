begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_H__
define|#
directive|define
name|__GIMP_ITEM_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_ITEM
define|#
directive|define
name|GIMP_TYPE_ITEM
value|(gimp_item_get_type ())
end_define

begin_define
DECL|macro|GIMP_ITEM (obj)
define|#
directive|define
name|GIMP_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ITEM, GimpItem))
end_define

begin_define
DECL|macro|GIMP_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ITEM, GimpItemClass))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM (obj)
define|#
directive|define
name|GIMP_IS_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ITEM))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ITEM))
end_define

begin_define
DECL|macro|GIMP_ITEM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ITEM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ITEM, GimpItemClass))
end_define

begin_typedef
DECL|typedef|GimpItemClass
typedef|typedef
name|struct
name|_GimpItemClass
name|GimpItemClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItem
struct|struct
name|_GimpItem
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  provides a unique ID     */
DECL|member|tattoo
name|guint32
name|tattoo
decl_stmt|;
comment|/*  provides a permanent ID  */
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/*  gimage owner             */
DECL|member|parasites
name|GimpParasiteList
modifier|*
name|parasites
decl_stmt|;
comment|/*  Plug-in parasite data    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpItemClass
struct|struct
name|_GimpItemClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
DECL|member|removed
name|void
function_decl|(
modifier|*
name|removed
function_decl|)
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_item_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_item_removed
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_configure
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_copy
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_item_get_ID
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_get_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTattoo
name|gimp_item_get_tattoo
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_set_tattoo
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_item_get_image
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_set_image
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_parasite_attach
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_parasite_detach
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_item_parasite_find
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_item_parasite_list
parameter_list|(
specifier|const
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ITEM_H__ */
end_comment

end_unit


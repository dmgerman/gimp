begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcomponentlistitem.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPONENT_LIST_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPONENT_LIST_ITEM_H__
define|#
directive|define
name|__GIMP_COMPONENT_LIST_ITEM_H__
end_define

begin_include
include|#
directive|include
file|"gimplistitem.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COMPONENT_LIST_ITEM
define|#
directive|define
name|GIMP_TYPE_COMPONENT_LIST_ITEM
value|(gimp_component_list_item_get_type ())
end_define

begin_define
DECL|macro|GIMP_COMPONENT_LIST_ITEM (obj)
define|#
directive|define
name|GIMP_COMPONENT_LIST_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COMPONENT_LIST_ITEM, GimpComponentListItem))
end_define

begin_define
DECL|macro|GIMP_COMPONENT_LIST_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_COMPONENT_LIST_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COMPONENT_LIST_ITEM, GimpComponentListItemClass))
end_define

begin_define
DECL|macro|GIMP_IS_COMPONENT_LIST_ITEM (obj)
define|#
directive|define
name|GIMP_IS_COMPONENT_LIST_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COMPONENT_LIST_ITEM))
end_define

begin_define
DECL|macro|GIMP_IS_COMPONENT_LIST_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COMPONENT_LIST_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COMPONENT_LIST_ITEM))
end_define

begin_define
DECL|macro|GIMP_COMPONENT_LIST_ITEM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COMPONENT_LIST_ITEM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COMPONENT_LIST_ITEM, GimpComponentListItemClass))
end_define

begin_typedef
DECL|typedef|GimpComponentListItemClass
typedef|typedef
name|struct
name|_GimpComponentListItemClass
name|GimpComponentListItemClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpComponentListItem
struct|struct
name|_GimpComponentListItem
block|{
DECL|member|parent_instance
name|GimpListItem
name|parent_instance
decl_stmt|;
DECL|member|channel
name|GimpChannelType
name|channel
decl_stmt|;
DECL|member|eye_button
name|GtkWidget
modifier|*
name|eye_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpComponentListItemClass
struct|struct
name|_GimpComponentListItemClass
block|{
DECL|member|parent_class
name|GimpListItemClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_component_list_item_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_component_list_item_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|preview_size
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPONENT_LIST_ITEM_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpchannellistitem.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHANNEL_LIST_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHANNEL_LIST_ITEM_H__
define|#
directive|define
name|__GIMP_CHANNEL_LIST_ITEM_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawablelistitem.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GIMP_TYPE_CHANNEL_LIST_ITEM
define|#
directive|define
name|GIMP_TYPE_CHANNEL_LIST_ITEM
value|(gimp_channel_list_item_get_type ())
DECL|macro|GIMP_CHANNEL_LIST_ITEM (obj)
define|#
directive|define
name|GIMP_CHANNEL_LIST_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CHANNEL_LIST_ITEM, GimpChannelListItem))
DECL|macro|GIMP_CHANNEL_LIST_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_CHANNEL_LIST_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CHANNEL_LIST_ITEM, GimpChannelListItemClass))
DECL|macro|GIMP_IS_CHANNEL_LIST_ITEM (obj)
define|#
directive|define
name|GIMP_IS_CHANNEL_LIST_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CHANNEL_LIST_ITEM))
DECL|macro|GIMP_IS_CHANNEL_LIST_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CHANNEL_LIST_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CHANNEL_LIST_ITEM))
DECL|macro|GIMP_CHANNEL_LIST_ITEM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CHANNEL_LIST_ITEM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CHANNEL_LIST_ITEM, GimpChannelListItemClass))
DECL|typedef|GimpChannelListItemClass
typedef|typedef
name|struct
name|_GimpChannelListItemClass
name|GimpChannelListItemClass
typedef|;
DECL|struct|_GimpChannelListItem
struct|struct
name|_GimpChannelListItem
block|{
DECL|member|parent_instance
name|GimpDrawableListItem
name|parent_instance
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpChannelListItemClass
struct|struct
name|_GimpChannelListItemClass
block|{
DECL|member|parent_class
name|GimpDrawableListItemClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|GType
name|gimp_channel_list_item_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CHANNEL_LIST_ITEM_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_AUX_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_AUX_ITEM_H__
define|#
directive|define
name|__GIMP_AUX_ITEM_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_AUX_ITEM
define|#
directive|define
name|GIMP_TYPE_AUX_ITEM
value|(gimp_aux_item_get_type ())
end_define

begin_define
DECL|macro|GIMP_AUX_ITEM (obj)
define|#
directive|define
name|GIMP_AUX_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_AUX_ITEM, GimpAuxItem))
end_define

begin_define
DECL|macro|GIMP_AUX_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_AUX_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_AUX_ITEM, GimpAuxItemClass))
end_define

begin_define
DECL|macro|GIMP_IS_AUX_ITEM (obj)
define|#
directive|define
name|GIMP_IS_AUX_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_AUX_ITEM))
end_define

begin_define
DECL|macro|GIMP_IS_AUX_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_AUX_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_AUX_ITEM))
end_define

begin_define
DECL|macro|GIMP_AUX_ITEM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_AUX_ITEM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_AUX_ITEM, GimpAuxItemClass))
end_define

begin_typedef
DECL|typedef|GimpAuxItemPrivate
typedef|typedef
name|struct
name|_GimpAuxItemPrivate
name|GimpAuxItemPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpAuxItemClass
typedef|typedef
name|struct
name|_GimpAuxItemClass
name|GimpAuxItemClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAuxItem
struct|struct
name|_GimpAuxItem
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpAuxItemPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpAuxItemClass
struct|struct
name|_GimpAuxItemClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|removed
name|void
function_decl|(
modifier|*
name|removed
function_decl|)
parameter_list|(
name|GimpAuxItem
modifier|*
name|aux_item
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_aux_item_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|guint32
name|gimp_aux_item_get_id
parameter_list|(
name|GimpAuxItem
modifier|*
name|aux_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_aux_item_removed
parameter_list|(
name|GimpAuxItem
modifier|*
name|aux_item
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_AUX_ITEM_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprofilestore-private.h  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_PROFILE_STORE_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_PROFILE_STORE_PRIVATE_H__
define|#
directive|define
name|__GIMP_COLOR_PROFILE_STORE_PRIVATE_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27e0abc40103
block|{
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_ITEM_FILE
name|GIMP_COLOR_PROFILE_STORE_ITEM_FILE
block|,
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_ITEM_SEPARATOR_TOP
name|GIMP_COLOR_PROFILE_STORE_ITEM_SEPARATOR_TOP
block|,
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_ITEM_SEPARATOR_BOTTOM
name|GIMP_COLOR_PROFILE_STORE_ITEM_SEPARATOR_BOTTOM
block|,
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_ITEM_DIALOG
name|GIMP_COLOR_PROFILE_STORE_ITEM_DIALOG
DECL|typedef|GimpColorProfileStoreItemType
block|}
name|GimpColorProfileStoreItemType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27e0abc40203
block|{
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_ITEM_TYPE
name|GIMP_COLOR_PROFILE_STORE_ITEM_TYPE
block|,
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_LABEL
name|GIMP_COLOR_PROFILE_STORE_LABEL
block|,
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_FILE
name|GIMP_COLOR_PROFILE_STORE_FILE
block|,
DECL|enumerator|GIMP_COLOR_PROFILE_STORE_INDEX
name|GIMP_COLOR_PROFILE_STORE_INDEX
DECL|typedef|GimpColorProfileStoreColumns
block|}
name|GimpColorProfileStoreColumns
typedef|;
end_typedef

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_color_profile_store_history_add
parameter_list|(
name|GimpColorProfileStore
modifier|*
name|store
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|void
name|_gimp_color_profile_store_history_reorder
parameter_list|(
name|GimpColorProfileStore
modifier|*
name|store
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_PROFILE_STORE_PRIVATE_H__ */
end_comment

end_unit


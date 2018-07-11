begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPAT_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPAT_ENUMS_H__
define|#
directive|define
name|__GIMP_COMPAT_ENUMS_H__
end_define

begin_expr_stmt
name|G_BEGIN_DECLS
comment|/*  These enums exist only for compatibility, their nicks are needed  *  for config file parsing; they are registered in gimp_base_init().  */
if|#
directive|if
literal|0
comment|/*  Leave one enum here for documentation purposes, remove it as  *  soon as we need a real compat enum again, also don't have  *  that "skip" on the compat enum...  */
define|#
directive|define
name|GIMP_TYPE_ADD_MASK_TYPE_COMPAT
value|(gimp_add_mask_type_compat_get_type ())
expr|GType gimp_add_mask_type_compat_get_type (void) G_GNUC_CONST;  typedef enum
comment|/*< skip>*/
expr|{   GIMP_ADD_WHITE_MASK          = GIMP_ADD_MASK_WHITE,   GIMP_ADD_BLACK_MASK          = GIMP_ADD_MASK_BLACK,   GIMP_ADD_ALPHA_MASK          = GIMP_ADD_MASK_ALPHA,   GIMP_ADD_ALPHA_TRANSFER_MASK = GIMP_ADD_MASK_ALPHA_TRANSFER,   GIMP_ADD_SELECTION_MASK      = GIMP_ADD_MASK_SELECTION,   GIMP_ADD_COPY_MASK           = GIMP_ADD_MASK_COPY,   GIMP_ADD_CHANNEL_MASK        = GIMP_ADD_MASK_CHANNEL } GimpAddMaskTypeCompat;
endif|#
directive|endif
name|G_END_DECLS
end_expr_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPAT_ENUMS_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DIALOG_TYPES_H__
end_ifndef

begin_define
DECL|macro|__DIALOG_TYPES_H__
define|#
directive|define
name|__DIALOG_TYPES_H__
end_define

begin_comment
comment|/* Types of dialog items that can be made.  */
end_comment

begin_enum
DECL|enum|__anon2ae216190103
enum|enum
block|{
DECL|enumerator|GROUP_ROWS
name|GROUP_ROWS
init|=
literal|1
block|,
DECL|enumerator|GROUP_COLUMNS
name|GROUP_COLUMNS
block|,
DECL|enumerator|GROUP_FORM
name|GROUP_FORM
block|,
DECL|enumerator|ITEM_PUSH_BUTTON
name|ITEM_PUSH_BUTTON
block|,
DECL|enumerator|ITEM_CHECK_BUTTON
name|ITEM_CHECK_BUTTON
block|,
DECL|enumerator|ITEM_RADIO_BUTTON
name|ITEM_RADIO_BUTTON
block|,
DECL|enumerator|ITEM_IMAGE_MENU
name|ITEM_IMAGE_MENU
block|,
DECL|enumerator|ITEM_SCALE
name|ITEM_SCALE
block|,
DECL|enumerator|ITEM_FRAME
name|ITEM_FRAME
block|,
DECL|enumerator|ITEM_LABEL
name|ITEM_LABEL
block|,
DECL|enumerator|ITEM_TEXT
name|ITEM_TEXT
block|,
DECL|enumerator|GROUP_RADIO
name|GROUP_RADIO
init|=
literal|1
operator|<<
literal|16
block|}
enum|;
end_enum

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DIALOG_TYPES_H__ */
end_comment

end_unit


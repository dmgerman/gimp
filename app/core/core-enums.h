begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CORE_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__CORE_ENUMS_H__
define|#
directive|define
name|__CORE_ENUMS_H__
end_define

begin_comment
comment|/* These enums that are registered with the type system. */
end_comment

begin_define
DECL|macro|GIMP_TYPE_IMAGE_BASE_TYPE
define|#
directive|define
name|GIMP_TYPE_IMAGE_BASE_TYPE
value|(gimp_image_base_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_image_base_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2778950e0103
block|{
DECL|enumerator|GIMP_RGB
name|GIMP_RGB
block|,
DECL|enumerator|GIMP_GRAY
name|GIMP_GRAY
block|,
DECL|enumerator|GIMP_INDEXED
name|GIMP_INDEXED
DECL|typedef|GimpImageBaseType
block|}
name|GimpImageBaseType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PREVIEW_SIZE
define|#
directive|define
name|GIMP_TYPE_PREVIEW_SIZE
value|(gimp_preview_size_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_preview_size_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2778950e0203
block|{
DECL|enumerator|GIMP_PREVIEW_SIZE_NONE
name|GIMP_PREVIEW_SIZE_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_TINY
name|GIMP_PREVIEW_SIZE_TINY
init|=
literal|16
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_SMALL
name|GIMP_PREVIEW_SIZE_EXTRA_SMALL
init|=
literal|24
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_SMALL
name|GIMP_PREVIEW_SIZE_SMALL
init|=
literal|32
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_MEDIUM
name|GIMP_PREVIEW_SIZE_MEDIUM
init|=
literal|48
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_LARGE
name|GIMP_PREVIEW_SIZE_LARGE
init|=
literal|64
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_LARGE
name|GIMP_PREVIEW_SIZE_EXTRA_LARGE
init|=
literal|96
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_HUGE
name|GIMP_PREVIEW_SIZE_HUGE
init|=
literal|128
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_ENORMOUS
name|GIMP_PREVIEW_SIZE_ENORMOUS
init|=
literal|192
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_GIGANTIC
name|GIMP_PREVIEW_SIZE_GIGANTIC
init|=
literal|256
DECL|typedef|GimpPreviewSize
block|}
name|GimpPreviewSize
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CORE_TYPES_H__ */
end_comment

end_unit


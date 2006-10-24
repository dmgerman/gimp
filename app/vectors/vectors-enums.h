begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * vectors-enums.h  * Copyright (C) 2006 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__VECTORS_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__VECTORS_ENUMS_H__
define|#
directive|define
name|__VECTORS_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_VECTORS_STROKE_TYPE
define|#
directive|define
name|GIMP_TYPE_VECTORS_STROKE_TYPE
value|(gimp_vectors_stroke_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_vectors_stroke_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon288da3090103
block|{
DECL|enumerator|GIMP_VECTORS_STROKE_TYPE_BEZIER
name|GIMP_VECTORS_STROKE_TYPE_BEZIER
DECL|typedef|GimpVectorsStrokeType
block|}
name|GimpVectorsStrokeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon288da3090203
block|{
DECL|enumerator|GIMP_ANCHOR_ANCHOR
name|GIMP_ANCHOR_ANCHOR
block|,
DECL|enumerator|GIMP_ANCHOR_CONTROL
name|GIMP_ANCHOR_CONTROL
DECL|typedef|GimpAnchorType
block|}
name|GimpAnchorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon288da3090303
block|{
DECL|enumerator|GIMP_ANCHOR_FEATURE_NONE
name|GIMP_ANCHOR_FEATURE_NONE
block|,
DECL|enumerator|GIMP_ANCHOR_FEATURE_EDGE
name|GIMP_ANCHOR_FEATURE_EDGE
block|,
DECL|enumerator|GIMP_ANCHOR_FEATURE_ALIGNED
name|GIMP_ANCHOR_FEATURE_ALIGNED
block|,
DECL|enumerator|GIMP_ANCHOR_FEATURE_SYMMETRIC
name|GIMP_ANCHOR_FEATURE_SYMMETRIC
DECL|typedef|GimpAnchorFeatureType
block|}
name|GimpAnchorFeatureType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon288da3090403
block|{
DECL|enumerator|EXTEND_SIMPLE
name|EXTEND_SIMPLE
block|,
DECL|enumerator|EXTEND_EDITABLE
name|EXTEND_EDITABLE
DECL|typedef|GimpVectorExtendMode
block|}
name|GimpVectorExtendMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __VECTORS_ENUMS_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TEXT_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__TEXT_ENUMS_H__
define|#
directive|define
name|__TEXT_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TEXT_BOX_MODE
define|#
directive|define
name|GIMP_TYPE_TEXT_BOX_MODE
value|(gimp_text_box_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_text_box_mode_get_type
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
DECL|enum|__anon2b5605380103
block|{
DECL|enumerator|GIMP_TEXT_BOX_DYNAMIC
name|GIMP_TEXT_BOX_DYNAMIC
block|,
DECL|enumerator|GIMP_TEXT_BOX_FIXED
name|GIMP_TEXT_BOX_FIXED
DECL|typedef|GimpTextBoxMode
block|}
name|GimpTextBoxMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TEXT_DIRECTION
define|#
directive|define
name|GIMP_TYPE_TEXT_DIRECTION
value|(gimp_text_direction_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_text_direction_get_type
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
DECL|enum|__anon2b5605380203
block|{
DECL|enumerator|GIMP_TEXT_DIRECTION_LTR
name|GIMP_TEXT_DIRECTION_LTR
block|,
comment|/*< desc="From left to right">*/
DECL|enumerator|GIMP_TEXT_DIRECTION_RTL
name|GIMP_TEXT_DIRECTION_RTL
comment|/*< desc="From right to left">*/
DECL|typedef|GimpTextDirection
block|}
name|GimpTextDirection
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TEXT_JUSTIFICATION
define|#
directive|define
name|GIMP_TYPE_TEXT_JUSTIFICATION
value|(gimp_text_justification_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_text_justification_get_type
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
DECL|enum|__anon2b5605380303
block|{
DECL|enumerator|GIMP_TEXT_JUSTIFY_LEFT
name|GIMP_TEXT_JUSTIFY_LEFT
block|,
comment|/*< desc="Left justified">*/
DECL|enumerator|GIMP_TEXT_JUSTIFY_RIGHT
name|GIMP_TEXT_JUSTIFY_RIGHT
block|,
comment|/*< desc="Right justified">*/
DECL|enumerator|GIMP_TEXT_JUSTIFY_CENTER
name|GIMP_TEXT_JUSTIFY_CENTER
block|,
comment|/*< desc="Centered">*/
DECL|enumerator|GIMP_TEXT_JUSTIFY_FILL
name|GIMP_TEXT_JUSTIFY_FILL
comment|/*< desc="Filled">*/
DECL|typedef|GimpTextJustification
block|}
name|GimpTextJustification
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TEXT_OUTLINE
define|#
directive|define
name|GIMP_TYPE_TEXT_OUTLINE
value|(gimp_text_outline_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_text_outline_get_type
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
DECL|enum|__anon2b5605380403
block|{
DECL|enumerator|GIMP_TEXT_OUTLINE_NONE
name|GIMP_TEXT_OUTLINE_NONE
block|,
DECL|enumerator|GIMP_TEXT_OUTLINE_STROKE_ONLY
name|GIMP_TEXT_OUTLINE_STROKE_ONLY
block|,
DECL|enumerator|GIMP_TEXT_OUTLINE_STROKE_FILL
name|GIMP_TEXT_OUTLINE_STROKE_FILL
DECL|typedef|GimpTextOutline
block|}
name|GimpTextOutline
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TEXT_ENUMS_H__ */
end_comment

end_unit


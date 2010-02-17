begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
DECL|enum|__anon28f750a50103
block|{
DECL|enumerator|GIMP_TEXT_BOX_DYNAMIC
name|GIMP_TEXT_BOX_DYNAMIC
block|,
comment|/*< desc="Dynamic">*/
DECL|enumerator|GIMP_TEXT_BOX_FIXED
name|GIMP_TEXT_BOX_FIXED
comment|/*< desc="Fixed">*/
DECL|typedef|GimpTextBoxMode
block|}
name|GimpTextBoxMode
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
DECL|enum|__anon28f750a50203
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


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|enum|__anon2c2e1dbc0103
block|{
DECL|enumerator|GIMP_TEXT_JUSTIFY_LEFT
name|GIMP_TEXT_JUSTIFY_LEFT
block|,
comment|/*< desc="Left Justified">*/
DECL|enumerator|GIMP_TEXT_JUSTIFY_RIGHT
name|GIMP_TEXT_JUSTIFY_RIGHT
block|,
comment|/*< desc="Right Justified">*/
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TEXT_ENUMS_H__ */
end_comment

end_unit


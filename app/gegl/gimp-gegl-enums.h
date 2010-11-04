begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-enums.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GEGL_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GEGL_ENUMS_H__
define|#
directive|define
name|__GIMP_GEGL_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CAGE_MODE
define|#
directive|define
name|GIMP_TYPE_CAGE_MODE
value|(gimp_cage_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cage_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27b2eba90103
block|{
DECL|enumerator|GIMP_CAGE_MODE_CAGE_CHANGE
name|GIMP_CAGE_MODE_CAGE_CHANGE
block|,
comment|/*< desc="Create or adjust the cage">*/
DECL|enumerator|GIMP_CAGE_MODE_DEFORM
name|GIMP_CAGE_MODE_DEFORM
comment|/*< desc="Deform the cage to deform the image">*/
DECL|typedef|GimpCageMode
block|}
name|GimpCageMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GEGL_ENUMS_H__ */
end_comment

end_unit


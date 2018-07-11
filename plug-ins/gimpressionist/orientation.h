begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ORIENTATION_H
end_ifndef

begin_define
DECL|macro|__ORIENTATION_H
define|#
directive|define
name|__ORIENTATION_H
end_define

begin_define
DECL|macro|NUMORIENTRADIO
define|#
directive|define
name|NUMORIENTRADIO
value|8
end_define

begin_enum
DECL|enum|ORIENTATION_ENUM
enum|enum
name|ORIENTATION_ENUM
block|{
DECL|enumerator|ORIENTATION_VALUE
name|ORIENTATION_VALUE
init|=
literal|0
block|,
DECL|enumerator|ORIENTATION_RADIUS
name|ORIENTATION_RADIUS
init|=
literal|1
block|,
DECL|enumerator|ORIENTATION_RANDOM
name|ORIENTATION_RANDOM
init|=
literal|2
block|,
DECL|enumerator|ORIENTATION_RADIAL
name|ORIENTATION_RADIAL
init|=
literal|3
block|,
DECL|enumerator|ORIENTATION_FLOWING
name|ORIENTATION_FLOWING
init|=
literal|4
block|,
DECL|enumerator|ORIENTATION_HUE
name|ORIENTATION_HUE
init|=
literal|5
block|,
DECL|enumerator|ORIENTATION_ADAPTIVE
name|ORIENTATION_ADAPTIVE
init|=
literal|6
block|,
DECL|enumerator|ORIENTATION_MANUAL
name|ORIENTATION_MANUAL
init|=
literal|7
block|, }
enum|;
end_enum

begin_function_decl
name|void
name|create_orientationpage
parameter_list|(
name|GtkNotebook
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|orientation_restore
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|orientation_type_input
parameter_list|(
name|int
name|in
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* #ifndef __ORIENTATION_H */
end_comment

end_unit


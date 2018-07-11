begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLACEMENT_H
end_ifndef

begin_define
DECL|macro|__PLACEMENT_H
define|#
directive|define
name|__PLACEMENT_H
end_define

begin_enum
DECL|enum|PLACEMENT_TYPE_ENUM
enum|enum
name|PLACEMENT_TYPE_ENUM
block|{
DECL|enumerator|PLACEMENT_TYPE_RANDOM
name|PLACEMENT_TYPE_RANDOM
init|=
literal|0
block|,
DECL|enumerator|PLACEMENT_TYPE_EVEN_DIST
name|PLACEMENT_TYPE_EVEN_DIST
init|=
literal|1
block|, }
enum|;
end_enum

begin_function_decl
name|void
name|place_store
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|place_restore
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_placementpage
parameter_list|(
name|GtkNotebook
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|place_type_input
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

end_unit


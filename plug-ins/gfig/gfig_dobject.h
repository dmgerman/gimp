begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_DOBJECT_H__
end_ifndef

begin_define
DECL|macro|__GFIG_DOBJECT_H__
define|#
directive|define
name|__GFIG_DOBJECT_H__
end_define

begin_struct_decl
struct_decl|struct
name|Dobject
struct_decl|;
end_struct_decl

begin_comment
comment|/* fwd declaration for DobjFunc */
end_comment

begin_typedef
DECL|typedef|DobjFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|DobjFunc
function_decl|)
parameter_list|(
name|struct
name|Dobject
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|DobjGenFunc
typedef|typedef
name|struct
name|Dobject
modifier|*
function_decl|(
modifier|*
name|DobjGenFunc
function_decl|)
parameter_list|(
name|struct
name|Dobject
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|DobjLoadFunc
typedef|typedef
name|struct
name|Dobject
modifier|*
function_decl|(
modifier|*
name|DobjLoadFunc
function_decl|)
parameter_list|(
name|FILE
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|DobjSaveFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|DobjSaveFunc
function_decl|)
parameter_list|(
name|struct
name|Dobject
modifier|*
parameter_list|,
name|FILE
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c1a0c8c0103
block|{
DECL|enumerator|LINE
name|LINE
block|,
DECL|enumerator|CIRCLE
name|CIRCLE
block|,
DECL|enumerator|ELLIPSE
name|ELLIPSE
block|,
DECL|enumerator|ARC
name|ARC
block|,
DECL|enumerator|POLY
name|POLY
block|,
DECL|enumerator|STAR
name|STAR
block|,
DECL|enumerator|SPIRAL
name|SPIRAL
block|,
DECL|enumerator|BEZIER
name|BEZIER
block|,
DECL|enumerator|MOVE_OBJ
name|MOVE_OBJ
block|,
DECL|enumerator|MOVE_POINT
name|MOVE_POINT
block|,
DECL|enumerator|COPY_OBJ
name|COPY_OBJ
block|,
DECL|enumerator|MOVE_COPY_OBJ
name|MOVE_COPY_OBJ
block|,
DECL|enumerator|DEL_OBJ
name|DEL_OBJ
block|,
DECL|enumerator|NULL_OPER
name|NULL_OPER
DECL|typedef|DobjType
block|}
name|DobjType
typedef|;
end_typedef

begin_typedef
DECL|struct|DobjPoints
typedef|typedef
struct|struct
name|DobjPoints
block|{
DECL|member|next
name|struct
name|DobjPoints
modifier|*
name|next
decl_stmt|;
DECL|member|pnt
name|GdkPoint
name|pnt
decl_stmt|;
DECL|member|found_me
name|gint
name|found_me
decl_stmt|;
DECL|typedef|DobjPoints
block|}
name|DobjPoints
typedef|;
end_typedef

begin_comment
comment|/* The object itself */
end_comment

begin_typedef
DECL|struct|Dobject
typedef|typedef
struct|struct
name|Dobject
block|{
DECL|member|type
name|DobjType
name|type
decl_stmt|;
comment|/* What is the type? */
DECL|member|type_data
name|gint
name|type_data
decl_stmt|;
comment|/* Extra data needed by the object */
DECL|member|points
name|DobjPoints
modifier|*
name|points
decl_stmt|;
comment|/* List of points */
DECL|member|drawfunc
name|DobjFunc
name|drawfunc
decl_stmt|;
comment|/* How do I draw myself */
DECL|member|paintfunc
name|DobjFunc
name|paintfunc
decl_stmt|;
comment|/* Draw me on canvas */
DECL|member|copyfunc
name|DobjGenFunc
name|copyfunc
decl_stmt|;
comment|/* copy */
DECL|member|loadfunc
name|DobjLoadFunc
name|loadfunc
decl_stmt|;
comment|/* Load this type of object */
DECL|member|savefunc
name|DobjSaveFunc
name|savefunc
decl_stmt|;
comment|/* Save me out */
DECL|typedef|Dobject
block|}
name|Dobject
typedef|;
end_typedef

begin_comment
comment|/* States of the object */
end_comment

begin_define
DECL|macro|GFIG_OK
define|#
directive|define
name|GFIG_OK
value|0x0
end_define

begin_define
DECL|macro|GFIG_MODIFIED
define|#
directive|define
name|GFIG_MODIFIED
value|0x1
end_define

begin_define
DECL|macro|GFIG_READONLY
define|#
directive|define
name|GFIG_READONLY
value|0x2
end_define

begin_decl_stmt
specifier|extern
name|Dobject
modifier|*
name|obj_creating
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|d_pnt_add_line
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DobjPoints
modifier|*
name|d_copy_dobjpoints
parameter_list|(
name|DobjPoints
modifier|*
name|pnts
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|free_one_obj
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|d_delete_dobjpoints
parameter_list|(
name|DobjPoints
modifier|*
name|pnts
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GFIG_DOBJECT_H__ */
end_comment

end_unit


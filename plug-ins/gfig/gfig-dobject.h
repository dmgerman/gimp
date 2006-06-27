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

begin_include
include|#
directive|include
file|"gfig-types.h"
end_include

begin_include
include|#
directive|include
file|"gfig-style.h"
end_include

begin_typedef
DECL|typedef|DobjFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|DobjFunc
function_decl|)
parameter_list|(
name|GfigObject
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|DobjGenFunc
typedef|typedef
name|GfigObject
modifier|*
function_decl|(
modifier|*
name|DobjGenFunc
function_decl|)
parameter_list|(
name|GfigObject
modifier|*
parameter_list|)
function_decl|;
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
name|gboolean
name|found_me
decl_stmt|;
DECL|typedef|DobjPoints
block|}
name|DobjPoints
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon297d0be10108
block|{
DECL|member|type
name|DobjType
name|type
decl_stmt|;
comment|/* the object type for this class */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* virtuals */
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
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
function_decl|;
DECL|typedef|GfigObjectClass
block|}
name|GfigObjectClass
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|GfigObjectClass
name|dobj_class
index|[
literal|10
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* The object itself */
end_comment

begin_struct
DECL|struct|_GfigObject
struct|struct
name|_GfigObject
block|{
DECL|member|type
name|DobjType
name|type
decl_stmt|;
comment|/* What is the type? */
DECL|member|class
name|GfigObjectClass
modifier|*
name|class
decl_stmt|;
comment|/* What class does it belong to? */
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
DECL|member|style
name|Style
name|style
decl_stmt|;
comment|/* this object's individual style settings */
DECL|member|style_no
name|gint
name|style_no
decl_stmt|;
comment|/* style index of this specific object */
block|}
struct|;
end_struct

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
name|GfigObject
modifier|*
name|obj_creating
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GfigObject
modifier|*
name|tmp_line
decl_stmt|;
end_decl_stmt

begin_function_decl
name|DobjPoints
modifier|*
name|new_dobjpoint
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|do_save_obj
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|,
name|GString
modifier|*
name|to
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
name|GfigObject
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

begin_function_decl
name|void
name|object_update
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|copy_all_objs
parameter_list|(
name|GList
modifier|*
name|objs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_objects
parameter_list|(
name|GList
modifier|*
name|objs
parameter_list|,
name|gboolean
name|show_single
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GfigObject
modifier|*
name|d_load_object
parameter_list|(
name|gchar
modifier|*
name|desc
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GfigObject
modifier|*
name|d_new_object
parameter_list|(
name|DobjType
name|type
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|d_save_object
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|,
name|GString
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|free_all_objs
parameter_list|(
name|GList
modifier|*
name|objs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|clear_undo
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|new_obj_2edit
parameter_list|(
name|GFigObj
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_init_object_classes
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|d_pnt_add_line
parameter_list|(
name|GfigObject
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GFIG_DOBJECT_H__ */
end_comment

end_unit


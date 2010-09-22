begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasitem.h  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CANVAS_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CANVAS_ITEM_H__
define|#
directive|define
name|__GIMP_CANVAS_ITEM_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CANVAS_ITEM
define|#
directive|define
name|GIMP_TYPE_CANVAS_ITEM
value|(gimp_canvas_item_get_type ())
end_define

begin_define
DECL|macro|GIMP_CANVAS_ITEM (obj)
define|#
directive|define
name|GIMP_CANVAS_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CANVAS_ITEM, GimpCanvasItem))
end_define

begin_define
DECL|macro|GIMP_CANVAS_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_CANVAS_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CANVAS_ITEM, GimpCanvasItemClass))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_ITEM (obj)
define|#
directive|define
name|GIMP_IS_CANVAS_ITEM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CANVAS_ITEM))
end_define

begin_define
DECL|macro|GIMP_IS_CANVAS_ITEM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CANVAS_ITEM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CANVAS_ITEM))
end_define

begin_define
DECL|macro|GIMP_CANVAS_ITEM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CANVAS_ITEM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CANVAS_ITEM, GimpCanvasItemClass))
end_define

begin_typedef
DECL|typedef|GimpCanvasItem
typedef|typedef
name|struct
name|_GimpCanvasItem
name|GimpCanvasItem
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCanvasItemClass
typedef|typedef
name|struct
name|_GimpCanvasItemClass
name|GimpCanvasItemClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasItem
struct|struct
name|_GimpCanvasItem
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCanvasItemClass
struct|struct
name|_GimpCanvasItemClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
DECL|member|get_extents
name|GdkRegion
modifier|*
function_decl|(
modifier|*
name|get_extents
function_decl|)
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_canvas_item_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_canvas_item_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkRegion
modifier|*
name|gimp_canvas_item_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|void
name|_gimp_canvas_item_stroke
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_canvas_item_fill
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CANVAS_ITEM_H__ */
end_comment

end_unit


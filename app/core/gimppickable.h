begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppickable.h  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PICKABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PICKABLE_H__
define|#
directive|define
name|__GIMP_PICKABLE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_PICKABLE
define|#
directive|define
name|GIMP_TYPE_PICKABLE
value|(gimp_pickable_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PICKABLE (obj)
define|#
directive|define
name|GIMP_IS_PICKABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PICKABLE))
end_define

begin_define
DECL|macro|GIMP_PICKABLE (obj)
define|#
directive|define
name|GIMP_PICKABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PICKABLE, GimpPickable))
end_define

begin_define
DECL|macro|GIMP_PICKABLE_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_PICKABLE_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_PICKABLE, GimpPickableInterface))
end_define

begin_typedef
DECL|typedef|GimpPickableInterface
typedef|typedef
name|struct
name|_GimpPickableInterface
name|GimpPickableInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPickableInterface
struct|struct
name|_GimpPickableInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|get_image_type
name|GimpImageType
function_decl|(
modifier|*
name|get_image_type
function_decl|)
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
DECL|member|get_tiles
name|TileManager
modifier|*
function_decl|(
modifier|*
name|get_tiles
function_decl|)
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
DECL|member|get_color_at
name|guchar
modifier|*
function_decl|(
modifier|*
name|get_color_at
function_decl|)
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_pickable_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpImageType
name|gimp_pickable_get_image_type
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_pickable_get_tiles
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_pickable_get_color_at
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
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
name|gboolean
name|gimp_pickable_pick_color
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gboolean
name|sample_average
parameter_list|,
name|gdouble
name|average_radius
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PICKABLE_H__ */
end_comment

end_unit


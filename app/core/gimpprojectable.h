begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpprojectable.h  * Copyright (C) 2008  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROJECTABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROJECTABLE_H__
define|#
directive|define
name|__GIMP_PROJECTABLE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_PROJECTABLE
define|#
directive|define
name|GIMP_TYPE_PROJECTABLE
value|(gimp_projectable_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PROJECTABLE (obj)
define|#
directive|define
name|GIMP_IS_PROJECTABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROJECTABLE))
end_define

begin_define
DECL|macro|GIMP_PROJECTABLE (obj)
define|#
directive|define
name|GIMP_PROJECTABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROJECTABLE, GimpProjectable))
end_define

begin_define
DECL|macro|GIMP_PROJECTABLE_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_PROJECTABLE_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_PROJECTABLE, GimpProjectableInterface))
end_define

begin_typedef
DECL|typedef|GimpProjectableInterface
typedef|typedef
name|struct
name|_GimpProjectableInterface
name|GimpProjectableInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProjectableInterface
struct|struct
name|_GimpProjectableInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  signals  */
DECL|member|invalidate
name|void
function_decl|(
modifier|*
name|invalidate
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
DECL|member|flush
name|void
function_decl|(
modifier|*
name|flush
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gboolean
name|invalidate_preview
parameter_list|)
function_decl|;
DECL|member|structure_changed
name|void
function_decl|(
modifier|*
name|structure_changed
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|get_image
name|GimpImage
modifier|*
function_decl|(
modifier|*
name|get_image
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
DECL|member|get_format
specifier|const
name|Babl
modifier|*
function_decl|(
modifier|*
name|get_format
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
DECL|member|get_color_profile
name|GimpColorProfile
modifier|*
function_decl|(
modifier|*
name|get_color_profile
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
DECL|member|get_offset
name|void
function_decl|(
modifier|*
name|get_offset
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
DECL|member|get_size
name|void
function_decl|(
modifier|*
name|get_size
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
DECL|member|get_graph
name|GeglNode
modifier|*
function_decl|(
modifier|*
name|get_graph
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
DECL|member|invalidate_preview
name|void
function_decl|(
modifier|*
name|invalidate_preview
function_decl|)
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_projectable_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_projectable_invalidate
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projectable_flush
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gboolean
name|preview_invalidated
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projectable_structure_changed
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_projectable_get_image
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_projectable_get_format
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_projectable_get_color_profile
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projectable_get_offset
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projectable_get_size
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gimp_projectable_get_graph
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_projectable_invalidate_preview
parameter_list|(
name|GimpProjectable
modifier|*
name|projectable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROJECTABLE_H__ */
end_comment

end_unit


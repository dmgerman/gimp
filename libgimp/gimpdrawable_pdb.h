begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdrawable_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_PDB_H__
define|#
directive|define
name|__GIMP_DRAWABLE_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_drawable_delete
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_layer
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_layer_mask
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_channel
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_drawable_type_with_alpha
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_has_alpha
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_rgb
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_gray
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_is_indexed
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_bpp
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_width
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_height
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_offsets
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
modifier|*
name|offset_x
parameter_list|,
name|gint
modifier|*
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_drawable_get_image
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_set_image
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_drawable_get_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_set_name
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_get_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_set_visible
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_get_linked
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_set_linked
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|linked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_drawable_get_tattoo
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_set_tattoo
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_mask_bounds
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_merge_shadow
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_update
parameter_list|(
name|gint32
name|drawable_ID
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
name|guint8
modifier|*
name|gimp_drawable_get_pixel
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|x_coord
parameter_list|,
name|gint
name|y_coord
parameter_list|,
name|gint
modifier|*
name|num_channels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_set_pixel
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|x_coord
parameter_list|,
name|gint
name|y_coord
parameter_list|,
name|gint
name|num_channels
parameter_list|,
specifier|const
name|guint8
modifier|*
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_offset
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|wrap_around
parameter_list|,
name|GimpOffsetType
name|fill_type
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_drawable_thumbnail
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
modifier|*
name|ret_width
parameter_list|,
name|gint
modifier|*
name|ret_height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|,
name|gint
modifier|*
name|thumbnail_data_count
parameter_list|,
name|guint8
modifier|*
modifier|*
name|thumbnail_data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_PDB_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LAYER_H__
end_ifndef

begin_define
DECL|macro|__LAYER_H__
define|#
directive|define
name|__LAYER_H__
end_define

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_define
DECL|macro|APPLY
define|#
directive|define
name|APPLY
value|0
end_define

begin_define
DECL|macro|DISCARD
define|#
directive|define
name|DISCARD
value|1
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c9bb8da0103
block|{
DECL|enumerator|WhiteMask
name|WhiteMask
block|,
DECL|enumerator|BlackMask
name|BlackMask
block|,
DECL|enumerator|AlphaMask
name|AlphaMask
DECL|typedef|AddMaskType
block|}
name|AddMaskType
typedef|;
end_typedef

begin_comment
comment|/* structure declarations */
end_comment

begin_define
DECL|macro|GIMP_LAYER (obj)
define|#
directive|define
name|GIMP_LAYER
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, gimp_layer_get_type (), GimpLayer)
end_define

begin_define
DECL|macro|GIMP_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, gimp_layer_get_type(), GimpLayerClass)
end_define

begin_define
DECL|macro|GIMP_IS_LAYER (obj)
define|#
directive|define
name|GIMP_IS_LAYER
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, gimp_layer_get_type())
end_define

begin_define
DECL|macro|GIMP_LAYER_MASK (obj)
define|#
directive|define
name|GIMP_LAYER_MASK
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, gimp_layer_mask_get_type (), GimpLayerMask)
end_define

begin_define
DECL|macro|GIMP_LAYER_MASK_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_MASK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, gimp_layer_mask_get_type(), GimpLayerMaskClass)
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_MASK (obj)
define|#
directive|define
name|GIMP_IS_LAYER_MASK
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, gimp_layer_mask_get_type())
end_define

begin_typedef
DECL|typedef|GimpLayer
typedef|typedef
name|struct
name|_GimpLayer
name|GimpLayer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerClass
typedef|typedef
name|struct
name|_GimpLayerClass
name|GimpLayerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMask
typedef|typedef
name|struct
name|_GimpLayerMask
name|GimpLayerMask
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMaskClass
typedef|typedef
name|struct
name|_GimpLayerMaskClass
name|GimpLayerMaskClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|Layer
typedef|typedef
name|GimpLayer
name|Layer
typedef|;
end_typedef

begin_comment
DECL|typedef|Layer
comment|/* convenience */
end_comment

begin_typedef
DECL|typedef|LayerMask
typedef|typedef
name|GimpLayerMask
name|LayerMask
typedef|;
end_typedef

begin_comment
DECL|typedef|LayerMask
comment|/* convenience */
end_comment

begin_function_decl
name|guint
name|gimp_layer_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint
name|gimp_layer_mask_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Special undo types  */
end_comment

begin_typedef
DECL|typedef|LayerUndo
typedef|typedef
name|struct
name|_layer_undo
name|LayerUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_layer_undo
struct|struct
name|_layer_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the actual layer         */
DECL|member|prev_position
name|int
name|prev_position
decl_stmt|;
comment|/*  former position in list  */
DECL|member|prev_layer
name|Layer
modifier|*
name|prev_layer
decl_stmt|;
comment|/*  previous active layer    */
DECL|member|undo_type
name|int
name|undo_type
decl_stmt|;
comment|/*  is this a new layer undo */
comment|/*  or a remove layer undo?  */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|LayerMaskUndo
typedef|typedef
name|struct
name|_layer_mask_undo
name|LayerMaskUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_layer_mask_undo
struct|struct
name|_layer_mask_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the layer                */
DECL|member|apply_mask
name|int
name|apply_mask
decl_stmt|;
comment|/*  apply mask?              */
DECL|member|edit_mask
name|int
name|edit_mask
decl_stmt|;
comment|/*  edit mask or layer?      */
DECL|member|show_mask
name|int
name|show_mask
decl_stmt|;
comment|/*  show the mask?           */
DECL|member|mask
name|LayerMask
modifier|*
name|mask
decl_stmt|;
comment|/*  the layer mask           */
DECL|member|mode
name|int
name|mode
decl_stmt|;
comment|/*  the application mode     */
DECL|member|undo_type
name|int
name|undo_type
decl_stmt|;
comment|/*  is this a new layer mask */
comment|/*  or a remove layer mask   */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|FStoLayerUndo
typedef|typedef
name|struct
name|_fs_to_layer_undo
name|FStoLayerUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_fs_to_layer_undo
struct|struct
name|_fs_to_layer_undo
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
comment|/*  the layer                */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/*  drawable of floating sel */
block|}
struct|;
end_struct

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|Layer
modifier|*
name|layer_new
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_copy
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_ref
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_unref
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_from_tiles
parameter_list|(
name|void
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_add_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|LayerMask
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_create_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|AddMaskType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|layer_get_ID
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_delete
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_apply_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_translate
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_add_alpha
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_scale
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_resize
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|BoundSeg
modifier|*
name|layer_boundary
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_invalidate_boundary
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|layer_pick_correlate
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask_new
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask_copy
parameter_list|(
name|LayerMask
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_mask_delete
parameter_list|(
name|LayerMask
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask_get_ID
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask_ref
parameter_list|(
name|LayerMask
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_mask_unref
parameter_list|(
name|LayerMask
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* access functions */
end_comment

begin_function_decl
name|unsigned
name|char
modifier|*
name|layer_data
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|layer_mask
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|layer_has_alpha
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|layer_is_floating_sel
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|layer_linked
parameter_list|(
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|layer_preview
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|layer_mask_preview
parameter_list|(
name|Layer
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|layer_invalidate_previews
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* from drawable.c */
end_comment

begin_function_decl
name|Layer
modifier|*
name|drawable_layer
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|drawable_layer_mask
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* from channel.c */
end_comment

begin_function_decl
name|void
name|channel_layer_alpha
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|channel_layer_mask
parameter_list|(
name|Channel
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LAYER_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPIMAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMPIMAGE_H__
define|#
directive|define
name|__GIMPIMAGE_H__
end_define

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_include
include|#
directive|include
file|"boundary.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
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

begin_include
include|#
directive|include
file|"path.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpparasite.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpunit.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE
define|#
directive|define
name|GIMP_TYPE_IMAGE
value|gimp_image_get_type()
end_define

begin_define
DECL|macro|GIMP_IMAGE (obj)
define|#
directive|define
name|GIMP_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, GIMP_TYPE_IMAGE, GimpImage)
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE (obj)
define|#
directive|define
name|GIMP_IS_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, GIMP_TYPE_IMAGE)
end_define

begin_define
DECL|macro|TYPE_HAS_ALPHA (t)
define|#
directive|define
name|TYPE_HAS_ALPHA
parameter_list|(
name|t
parameter_list|)
value|((t)==RGBA_GIMAGE || (t)==GRAYA_GIMAGE || (t)==INDEXEDA_GIMAGE)
end_define

begin_define
DECL|macro|GRAY_PIX
define|#
directive|define
name|GRAY_PIX
value|0
end_define

begin_define
DECL|macro|ALPHA_G_PIX
define|#
directive|define
name|ALPHA_G_PIX
value|1
end_define

begin_define
DECL|macro|RED_PIX
define|#
directive|define
name|RED_PIX
value|0
end_define

begin_define
DECL|macro|GREEN_PIX
define|#
directive|define
name|GREEN_PIX
value|1
end_define

begin_define
DECL|macro|BLUE_PIX
define|#
directive|define
name|BLUE_PIX
value|2
end_define

begin_define
DECL|macro|ALPHA_PIX
define|#
directive|define
name|ALPHA_PIX
value|3
end_define

begin_define
DECL|macro|INDEXED_PIX
define|#
directive|define
name|INDEXED_PIX
value|0
end_define

begin_define
DECL|macro|ALPHA_I_PIX
define|#
directive|define
name|ALPHA_I_PIX
value|1
end_define

begin_define
DECL|macro|COLORMAP_SIZE
define|#
directive|define
name|COLORMAP_SIZE
value|768
end_define

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b1fb48f0103
block|{
DECL|enumerator|ORIENTATION_UNKNOWN
name|ORIENTATION_UNKNOWN
block|,
DECL|enumerator|ORIENTATION_HORIZONTAL
name|ORIENTATION_HORIZONTAL
block|,
DECL|enumerator|ORIENTATION_VERTICAL
name|ORIENTATION_VERTICAL
DECL|typedef|InternalOrientationType
block|}
name|InternalOrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b1fb48f0203
block|{
DECL|enumerator|HORIZONTAL
name|HORIZONTAL
block|,
DECL|enumerator|VERTICAL
name|VERTICAL
block|,
DECL|enumerator|UNKNOWN
name|UNKNOWN
DECL|typedef|OrientationType
block|}
name|OrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b1fb48f0303
block|{
DECL|enumerator|RED_CHANNEL
name|RED_CHANNEL
block|,
DECL|enumerator|GREEN_CHANNEL
name|GREEN_CHANNEL
block|,
DECL|enumerator|BLUE_CHANNEL
name|BLUE_CHANNEL
block|,
DECL|enumerator|GRAY_CHANNEL
name|GRAY_CHANNEL
block|,
DECL|enumerator|INDEXED_CHANNEL
name|INDEXED_CHANNEL
block|,
DECL|enumerator|AUXILLARY_CHANNEL
name|AUXILLARY_CHANNEL
DECL|typedef|ChannelType
block|}
name|ChannelType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b1fb48f0403
block|{
DECL|enumerator|EXPAND_AS_NECESSARY
name|EXPAND_AS_NECESSARY
block|,
DECL|enumerator|CLIP_TO_IMAGE
name|CLIP_TO_IMAGE
block|,
DECL|enumerator|CLIP_TO_BOTTOM_LAYER
name|CLIP_TO_BOTTOM_LAYER
block|,
DECL|enumerator|FLATTEN_IMAGE
name|FLATTEN_IMAGE
DECL|typedef|MergeType
block|}
name|MergeType
typedef|;
end_typedef

begin_comment
comment|/* Ugly! Move this someplace else! Prolly to gdisplay.. */
end_comment

begin_struct
DECL|struct|_Guide
struct|struct
name|_Guide
block|{
DECL|member|ref_count
name|int
name|ref_count
decl_stmt|;
DECL|member|position
name|int
name|position
decl_stmt|;
DECL|member|orientation
name|int
name|orientation
decl_stmt|;
DECL|member|guide_ID
name|guint32
name|guide_ID
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|_GimpImageRepaintArg
typedef|typedef
struct|struct
name|_GimpImageRepaintArg
block|{
DECL|member|layer
name|Layer
modifier|*
name|layer
decl_stmt|;
DECL|member|x
name|guint
name|x
decl_stmt|;
DECL|member|y
name|guint
name|y
decl_stmt|;
DECL|member|width
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
name|height
decl_stmt|;
DECL|typedef|GimpImageRepaintArg
block|}
name|GimpImageRepaintArg
typedef|;
end_typedef

begin_function_decl
name|GtkType
name|gimp_image_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_new
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|,
name|GimpImageBaseType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_filename
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_resolution
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_resolution
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gdouble
modifier|*
parameter_list|,
name|gdouble
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_unit
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpUnit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_image_get_unit
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_save_proc
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|PlugInProcDef
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PlugInProcDef
modifier|*
name|gimp_image_get_save_proc
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_width
parameter_list|(
specifier|const
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_height
parameter_list|(
specifier|const
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_resize
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_scale
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_get_named
parameter_list|(
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_get_ID
parameter_list|(
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_image_shadow
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_free_shadow
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_apply_image
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|LayerModeEffects
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_replace_image
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_foreground
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_background
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_image_get_color_at
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_color
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpImageType
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_transform_color
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|GimpImageBaseType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Guide
modifier|*
name|gimp_image_add_hguide
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Guide
modifier|*
name|gimp_image_add_vguide
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_add_guide
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_remove_guide
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_delete_guide
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_image_parasite_find
parameter_list|(
specifier|const
name|GimpImage
modifier|*
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_image_parasite_list
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_parasite_attach
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpParasite
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_parasite_detach
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
specifier|const
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tattoo
name|gimp_image_get_new_tattoo
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_tattoo_state
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tattoo
name|gimp_image_get_tattoo_state
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_paths
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|PathList
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PathList
modifier|*
name|gimp_image_get_paths
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Temporary hack till colormap manipulation is encapsulated in functions.    Call this whenever you modify an image's colormap. The ncol argument    specifies which color has changed, or negative if there's a bigger change.    Currently, use this also when the image's base type is changed to/from    indexed.  */
end_comment

begin_function_decl
name|void
name|gimp_image_colormap_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|ncol
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  layer/channel functions  */
end_comment

begin_function_decl
name|gint
name|gimp_image_get_layer_index
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_channel_index
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_get_active_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_active_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_get_layer_by_tattoo
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_channel_by_tattoo
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_channel_by_name
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_mask
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_component_active
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_component_visible
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_layer_boundary
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_set_active_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_set_active_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_unset_active_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_component_active
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_component_visible
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_pick_correlate_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_layer_mask_apply
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_layer_mask_edit
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_layer_mask_show
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_raise_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_lower_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_raise_layer_to_top
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_lower_layer_to_bottom
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_position_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gboolean
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_merge_visible_layers
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|MergeType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_merge_down
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|MergeType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_flatten
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_merge_layers
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GSList
modifier|*
parameter_list|,
name|MergeType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_add_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_remove_layer
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|LayerMask
modifier|*
name|gimp_image_add_layer_mask
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|LayerMask
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_remove_layer_mask
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Layer
modifier|*
parameter_list|,
name|MaskApplyMode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_raise_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_lower_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_position_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_add_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_remove_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_construct
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gboolean
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_without_render
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_validate
parameter_list|(
name|TileManager
modifier|*
parameter_list|,
name|Tile
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Access functions  */
end_comment

begin_function_decl
name|gboolean
name|gimp_image_is_empty
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_image_active_drawable
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageBaseType
name|gimp_image_base_type
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_image_base_type_with_alpha
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_image_filename
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_is_enabled
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_enable
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_disable
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_freeze
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_thaw
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_undo_event
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_dirty
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_clean
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_clean_all
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_floating_sel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_image_cmap
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  projection access functions  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|gimp_image_projection
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_image_projection_type
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_projection_bytes
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_projection_opacity
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_projection_realloc
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  composite access functions  */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|gimp_image_composite
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_image_composite_type
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_composite_bytes
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_image_composite_preview
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_preview_valid
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|ChannelType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_preview
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_previews
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_image_construct_composite_preview
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPIMAGE_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattisbvf  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_H__
define|#
directive|define
name|__GIMP_IMAGE_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|MAX_CHANNELS
define|#
directive|define
name|MAX_CHANNELS
value|4
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

begin_define
DECL|macro|GIMP_TYPE_IMAGE
define|#
directive|define
name|GIMP_TYPE_IMAGE
value|(gimp_image_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE (obj)
define|#
directive|define
name|GIMP_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST (obj, GIMP_TYPE_IMAGE, GimpImage))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE (obj)
define|#
directive|define
name|GIMP_IS_IMAGE
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_IMAGE))
end_define

begin_define
DECL|macro|GIMP_IMAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST (klass, GIMP_TYPE_IMAGE, GimpImageClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE))
end_define

begin_typedef
DECL|typedef|GimpImageClass
typedef|typedef
name|struct
name|_GimpImageClass
name|GimpImageClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImage
struct|struct
name|_GimpImage
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|save_proc
name|PlugInProcDef
modifier|*
name|save_proc
decl_stmt|;
comment|/*  last PDB save proc used      */
DECL|member|width
DECL|member|height
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  width and height attributes  */
DECL|member|xresolution
name|gdouble
name|xresolution
decl_stmt|;
comment|/*  image x-res, in dpi          */
DECL|member|yresolution
name|gdouble
name|yresolution
decl_stmt|;
comment|/*  image y-res, in dpi          */
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
comment|/*  image unit                   */
DECL|member|base_type
name|GimpImageBaseType
name|base_type
decl_stmt|;
comment|/*  base gimp_image type         */
DECL|member|cmap
name|guchar
modifier|*
name|cmap
decl_stmt|;
comment|/*  colormap--for indexed        */
DECL|member|num_cols
name|gint
name|num_cols
decl_stmt|;
comment|/*  number of cols--for indexed  */
DECL|member|dirty
name|gint
name|dirty
decl_stmt|;
comment|/*  dirty flag -- # of ops       */
DECL|member|undo_on
name|gboolean
name|undo_on
decl_stmt|;
comment|/*  Is undo enabled?             */
DECL|member|instance_count
name|gint
name|instance_count
decl_stmt|;
comment|/*  number of instances          */
DECL|member|disp_count
name|gint
name|disp_count
decl_stmt|;
comment|/*  number of displays           */
DECL|member|tattoo_state
name|Tattoo
name|tattoo_state
decl_stmt|;
comment|/*  the next unique tattoo to use*/
DECL|member|shadow
name|TileManager
modifier|*
name|shadow
decl_stmt|;
comment|/*  shadow buffer tiles          */
comment|/*  Projection attributes  */
DECL|member|construct_flag
name|gint
name|construct_flag
decl_stmt|;
comment|/*  flag for construction        */
DECL|member|proj_type
name|GimpImageType
name|proj_type
decl_stmt|;
comment|/*  type of the projection image */
DECL|member|proj_bytes
name|gint
name|proj_bytes
decl_stmt|;
comment|/*  bpp in projection image      */
DECL|member|proj_level
name|gint
name|proj_level
decl_stmt|;
comment|/*  projection level             */
DECL|member|projection
name|TileManager
modifier|*
name|projection
decl_stmt|;
comment|/*  The projection--layers&     */
comment|/*  channels                     */
DECL|member|guides
name|GList
modifier|*
name|guides
decl_stmt|;
comment|/*  guides                       */
comment|/*  Layer/Channel attributes  */
DECL|member|layers
name|GSList
modifier|*
name|layers
decl_stmt|;
comment|/*  the list of layers           */
DECL|member|channels
name|GSList
modifier|*
name|channels
decl_stmt|;
comment|/*  the list of masks            */
DECL|member|layer_stack
name|GSList
modifier|*
name|layer_stack
decl_stmt|;
comment|/*  the layers in MRU order      */
DECL|member|active_layer
name|Layer
modifier|*
name|active_layer
decl_stmt|;
comment|/*  ID of active layer           */
DECL|member|active_channel
name|Channel
modifier|*
name|active_channel
decl_stmt|;
comment|/*  ID of active channel         */
DECL|member|floating_sel
name|Layer
modifier|*
name|floating_sel
decl_stmt|;
comment|/*  ID of fs layer               */
DECL|member|selection_mask
name|Channel
modifier|*
name|selection_mask
decl_stmt|;
comment|/*  selection mask channel       */
DECL|member|parasites
name|ParasiteList
modifier|*
name|parasites
decl_stmt|;
comment|/*  Plug-in parasite data        */
DECL|member|paths
name|PathList
modifier|*
name|paths
decl_stmt|;
comment|/*  Paths data for this image    */
DECL|member|visible
name|gboolean
name|visible
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  visible channels             */
DECL|member|active
name|gboolean
name|active
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  active channels              */
DECL|member|by_color_select
name|gboolean
name|by_color_select
decl_stmt|;
comment|/*  TRUE if there's an active    */
comment|/*  "by color" selection dialog  */
DECL|member|qmask_state
name|gboolean
name|qmask_state
decl_stmt|;
comment|/*  TRUE if qmask is on          */
DECL|member|qmask_color
name|GimpRGB
name|qmask_color
decl_stmt|;
comment|/*  rgba triplet of the color    */
comment|/*  Undo apparatus  */
DECL|member|undo_stack
name|GSList
modifier|*
name|undo_stack
decl_stmt|;
comment|/*  stack for undo operations    */
DECL|member|redo_stack
name|GSList
modifier|*
name|redo_stack
decl_stmt|;
comment|/*  stack for redo operations    */
DECL|member|undo_bytes
name|gint
name|undo_bytes
decl_stmt|;
comment|/*  bytes in undo stack          */
DECL|member|undo_levels
name|gint
name|undo_levels
decl_stmt|;
comment|/*  levels in undo stack         */
DECL|member|group_count
name|gint
name|group_count
decl_stmt|;
comment|/*  nested undo groups           */
DECL|member|pushing_undo_group
name|UndoType
name|pushing_undo_group
decl_stmt|;
comment|/*  undo group status flag       */
DECL|member|undo_history
name|GtkWidget
modifier|*
name|undo_history
decl_stmt|;
comment|/*  history viewer, or NULL      */
comment|/*  Composite preview  */
DECL|member|comp_preview
name|TempBuf
modifier|*
name|comp_preview
decl_stmt|;
comment|/*  the composite preview        */
DECL|member|comp_preview_valid
name|gboolean
name|comp_preview_valid
index|[
literal|3
index|]
decl_stmt|;
comment|/*  preview valid-1/channel      */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageClass
struct|struct
name|_GimpImageClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|clean
name|void
function_decl|(
modifier|*
name|clean
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
DECL|member|dirty
name|void
function_decl|(
modifier|*
name|dirty
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
DECL|member|repaint
name|void
function_decl|(
modifier|*
name|repaint
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
DECL|member|resize
name|void
function_decl|(
modifier|*
name|resize
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
DECL|member|restructure
name|void
function_decl|(
modifier|*
name|restructure
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
DECL|member|colormap_changed
name|void
function_decl|(
modifier|*
name|colormap_changed
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
DECL|member|undo_event
name|void
function_decl|(
modifier|*
name|undo_event
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_IMAGE_TYPE_HAS_ALPHA (t)
define|#
directive|define
name|GIMP_IMAGE_TYPE_HAS_ALPHA
parameter_list|(
name|t
parameter_list|)
value|((t)==RGBA_GIMAGE || (t)==GRAYA_GIMAGE || (t)==INDEXEDA_GIMAGE)
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bbff0f60103
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
DECL|enum|__anon2bbff0f60203
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
name|gint
name|ref_count
decl_stmt|;
DECL|member|position
name|gint
name|position
decl_stmt|;
DECL|member|orientation
name|InternalOrientationType
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

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|GtkType
name|gimp_image_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageBaseType
name|base_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_filename
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_resolution
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_resolution
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
modifier|*
name|xresolution
parameter_list|,
name|gdouble
modifier|*
name|yresolution
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_unit
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_image_get_unit
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_save_proc
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PlugInProcDef
modifier|*
name|gimp_image_get_save_proc
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
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
name|gimage
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
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_resize
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
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
name|void
name|gimp_image_scale
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|new_width
parameter_list|,
name|gint
name|new_height
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
name|gimage
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_free_shadow
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_apply_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
parameter_list|,
name|gint
name|undo
parameter_list|,
name|gint
name|opacity
parameter_list|,
name|LayerModeEffects
name|mode
parameter_list|,
name|TileManager
modifier|*
name|src1_tiles
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
name|gimp_image_replace_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PixelRegion
modifier|*
name|src2PR
parameter_list|,
name|gint
name|undo
parameter_list|,
name|gint
name|opacity
parameter_list|,
name|PixelRegion
modifier|*
name|maskPR
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
name|gimp_image_get_foreground
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guchar
modifier|*
name|fg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_get_background
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guchar
modifier|*
name|bg
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
name|gimage
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
name|gimp_image_get_color
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpImageType
name|d_type
parameter_list|,
name|guchar
modifier|*
name|rgb
parameter_list|,
name|guchar
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_transform_color
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|GimpImageBaseType
name|type
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
name|gimage
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
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_add_guide
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Guide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_remove_guide
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Guide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_delete_guide
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Guide
modifier|*
name|guide
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
name|gimage
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
specifier|const
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
name|gimage
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_parasite_detach
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tattoo
name|gimp_image_get_new_tattoo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_tattoo_state
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Tattoo
name|val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tattoo
name|gimp_image_get_tattoo_state
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_paths
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|PathList
modifier|*
name|paths
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PathList
modifier|*
name|gimp_image_get_paths
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
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
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|col
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
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|Layer
modifier|*
name|layer_arg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_get_layer_by_index
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|layer_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_get_channel_index
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|Channel
modifier|*
name|channel_arg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_get_active_layer
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_active_channel
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_get_layer_by_tattoo
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Tattoo
name|tatoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_channel_by_tattoo
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Tattoo
name|tatoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_channel_by_name
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Channel
modifier|*
name|gimp_image_get_mask
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_component_active
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|ChannelType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_get_component_visible
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|ChannelType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_layer_boundary
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
name|segs
parameter_list|,
name|gint
modifier|*
name|n_segs
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer
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
name|gimage
parameter_list|,
name|Channel
modifier|*
name|channel
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
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_component_active
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|ChannelType
name|type
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_set_component_visible
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|ChannelType
name|type
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_pick_correlate_layer
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
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
name|Layer
modifier|*
name|gimp_image_raise_layer
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer_arg
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer_arg
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer_arg
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer_arg
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer_arg
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gboolean
name|push_undo
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
name|gimage
parameter_list|,
name|MergeType
name|merge_type
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|current_layer
parameter_list|,
name|MergeType
name|merge_type
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
name|gimage
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
name|gimage
parameter_list|,
name|GSList
modifier|*
name|merge_list
parameter_list|,
name|MergeType
name|merge_type
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|float_layer
parameter_list|,
name|gint
name|position
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMask
modifier|*
name|gimp_image_add_layer_mask
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerMask
modifier|*
name|mask
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
name|gimage
parameter_list|,
name|Layer
modifier|*
name|layer
parameter_list|,
name|MaskApplyMode
name|mode
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
name|gimage
parameter_list|,
name|Channel
modifier|*
name|channel_arg
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
name|gimage
parameter_list|,
name|Channel
modifier|*
name|channel_arg
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
name|gimage
parameter_list|,
name|Channel
modifier|*
name|channel_arg
parameter_list|,
name|gint
name|position
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
name|gimage
parameter_list|,
name|Channel
modifier|*
name|channel
parameter_list|,
name|gint
name|position
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
name|gimage
parameter_list|,
name|Channel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_construct
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_without_render
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_validate
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_layer_previews
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_channel_previews
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDrawable
modifier|*
name|gimp_image_active_drawable
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageBaseType
name|gimp_image_base_type
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_image_base_type_with_alpha
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_image_filename
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_is_enabled
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_enable
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_disable
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_freeze
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_undo_thaw
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_undo_event
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_dirty
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_clean
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_clean_all
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Layer
modifier|*
name|gimp_image_floating_sel
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|gimp_image_cmap
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
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
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_image_projection_type
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_projection_bytes
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_projection_opacity
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_projection_realloc
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageType
name|gimp_image_composite_type
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_image_composite_bytes
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
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
name|gimage
parameter_list|,
name|ChannelType
name|type
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
name|gint
name|gimp_image_preview_valid
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|ChannelType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_invalidate_preview
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gimage
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_H__ */
end_comment

end_unit


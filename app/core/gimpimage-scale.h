begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
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
DECL|macro|GIMP_IS_GIMAGE (obj)
define|#
directive|define
name|GIMP_IS_GIMAGE
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, GIMP_TYPE_IMAGE)
end_define

begin_comment
comment|/* the image types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28dc2eff0103
block|{
DECL|enumerator|RGB_GIMAGE
name|RGB_GIMAGE
block|,
DECL|enumerator|RGBA_GIMAGE
name|RGBA_GIMAGE
block|,
DECL|enumerator|GRAY_GIMAGE
name|GRAY_GIMAGE
block|,
DECL|enumerator|GRAYA_GIMAGE
name|GRAYA_GIMAGE
block|,
DECL|enumerator|INDEXED_GIMAGE
name|INDEXED_GIMAGE
block|,
DECL|enumerator|INDEXEDA_GIMAGE
name|INDEXEDA_GIMAGE
DECL|typedef|GimpImageType
block|}
name|GimpImageType
typedef|;
end_typedef

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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28dc2eff0203
block|{
DECL|enumerator|RGB
name|RGB
block|,
DECL|enumerator|GRAY
name|GRAY
block|,
DECL|enumerator|INDEXED
name|INDEXED
DECL|typedef|GimpImageBaseType
block|}
name|GimpImageBaseType
typedef|;
end_typedef

begin_define
DECL|macro|COLORMAP_SIZE
define|#
directive|define
name|COLORMAP_SIZE
value|768
end_define

begin_define
DECL|macro|HORIZONTAL_GUIDE
define|#
directive|define
name|HORIZONTAL_GUIDE
value|1
end_define

begin_define
DECL|macro|VERTICAL_GUIDE
define|#
directive|define
name|VERTICAL_GUIDE
value|2
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28dc2eff0303
block|{
DECL|enumerator|Red
name|Red
block|,
DECL|enumerator|Green
name|Green
block|,
DECL|enumerator|Blue
name|Blue
block|,
DECL|enumerator|Gray
name|Gray
block|,
DECL|enumerator|Indexed
name|Indexed
block|,
DECL|enumerator|Auxillary
name|Auxillary
DECL|typedef|ChannelType
block|}
name|ChannelType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28dc2eff0403
block|{
DECL|enumerator|ExpandAsNecessary
name|ExpandAsNecessary
block|,
DECL|enumerator|ClipToImage
name|ClipToImage
block|,
DECL|enumerator|ClipToBottomLayer
name|ClipToBottomLayer
block|,
DECL|enumerator|FlattenImage
name|FlattenImage
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
name|gimp_image_set_filename
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|char
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
name|void
name|gimp_image_scale
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_get_named
parameter_list|(
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_image_get_ID
parameter_list|(
name|int
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
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|TileManager
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
name|int
parameter_list|,
name|int
parameter_list|,
name|PixelRegion
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
name|gimp_image_get_foreground
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|unsigned
name|char
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
name|unsigned
name|char
modifier|*
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
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
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
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|int
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

begin_comment
comment|/*  layer/channel functions  */
end_comment

begin_function_decl
name|int
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
name|int
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
name|int
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
name|int
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
name|int
name|gimp_image_layer_boundary
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|BoundSeg
modifier|*
modifier|*
parameter_list|,
name|int
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
name|int
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
name|int
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
name|int
parameter_list|,
name|int
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
name|int
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
name|int
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
name|int
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
name|int
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
name|int
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
name|gimp_image_add_channel
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Channel
modifier|*
parameter_list|,
name|int
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
name|void
name|gimp_image_invalidate
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
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
name|int
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
name|int
name|gimp_image_base_type
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimp_image_base_type_with_alpha
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|gimp_image_filename
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimp_image_enable_undo
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimp_image_disable_undo
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimp_image_dirty
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
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
name|unsigned
name|char
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
name|int
name|gimp_image_projection_type
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gimp_image_projection_bytes
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
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
name|int
name|gimp_image_composite_type
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
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
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
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

begin_comment
comment|/* Exported for PDB */
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimp_image_add_hguide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimp_image_add_vguide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimp_image_delete_guide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimp_image_findnext_guide_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimp_image_get_guide_orientation_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gimp_image_get_guide_position_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPIMAGEP_H__
end_ifndef

begin_define
DECL|macro|__GIMPIMAGEP_H__
define|#
directive|define
name|__GIMPIMAGEP_H__
end_define

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
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

begin_define
DECL|macro|MAX_CHANNELS
define|#
directive|define
name|MAX_CHANNELS
value|4
end_define

begin_struct
DECL|struct|_GimpImage
struct|struct
name|_GimpImage
block|{
DECL|member|gobject
name|GimpObject
name|gobject
decl_stmt|;
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
comment|/*  original filename            */
DECL|member|has_filename
name|int
name|has_filename
decl_stmt|;
comment|/*  has a valid filename         */
DECL|member|width
DECL|member|height
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/*  width and height attributes  */
DECL|member|resolution
name|float
name|resolution
decl_stmt|;
comment|/*  image res, in dpi            */
DECL|member|base_type
name|int
name|base_type
decl_stmt|;
comment|/*  base gimp_image type         */
DECL|member|cmap
name|unsigned
name|char
modifier|*
name|cmap
decl_stmt|;
comment|/*  colormap--for indexed        */
DECL|member|num_cols
name|int
name|num_cols
decl_stmt|;
comment|/*  number of cols--for indexed  */
DECL|member|dirty
name|int
name|dirty
decl_stmt|;
comment|/*  dirty flag -- # of ops       */
DECL|member|undo_on
name|int
name|undo_on
decl_stmt|;
comment|/*  Is undo enabled?             */
DECL|member|instance_count
name|int
name|instance_count
decl_stmt|;
comment|/*  number of instances          */
DECL|member|ref_count
name|int
name|ref_count
decl_stmt|;
comment|/*  number of references         */
DECL|member|shadow
name|TileManager
modifier|*
name|shadow
decl_stmt|;
comment|/*  shadow buffer tiles          */
comment|/*  Projection attributes  */
DECL|member|construct_flag
name|int
name|construct_flag
decl_stmt|;
comment|/*  flag for construction        */
DECL|member|proj_type
name|int
name|proj_type
decl_stmt|;
comment|/*  type of the projection image */
DECL|member|proj_bytes
name|int
name|proj_bytes
decl_stmt|;
comment|/*  bpp in projection image      */
DECL|member|proj_level
name|int
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
name|GSList
modifier|*
name|parasites
decl_stmt|;
comment|/*  Plug-in parasite data        */
DECL|member|visible
name|int
name|visible
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  visible channels             */
DECL|member|active
name|int
name|active
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
comment|/*  active channels              */
DECL|member|by_color_select
name|int
name|by_color_select
decl_stmt|;
comment|/*  TRUE if there's an active    */
comment|/*  "by color" selection dialog  */
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
name|int
name|undo_bytes
decl_stmt|;
comment|/*  bytes in undo stack          */
DECL|member|undo_levels
name|int
name|undo_levels
decl_stmt|;
comment|/*  levels in undo stack         */
DECL|member|pushing_undo_group
name|int
name|pushing_undo_group
decl_stmt|;
comment|/*  undo group status flag       */
comment|/*  Composite preview  */
DECL|member|comp_preview
name|TempBuf
modifier|*
name|comp_preview
decl_stmt|;
comment|/*  the composite preview        */
DECL|member|comp_preview_valid
name|int
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
DECL|member|dirty
name|void
function_decl|(
modifier|*
name|dirty
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
parameter_list|)
function_decl|;
DECL|member|repaint
name|void
function_decl|(
modifier|*
name|repaint
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
parameter_list|)
function_decl|;
DECL|member|rename
name|void
function_decl|(
modifier|*
name|rename
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpImageClass
typedef|typedef
name|struct
name|_GimpImageClass
name|GimpImageClass
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_IMAGE_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_CLASS
parameter_list|(
name|klass
parameter_list|)
define|\
value|GTK_CHECK_CLASS_CAST (klass, GIMP_TYPE_IMAGE, GimpImageClass)
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_TOOL_H__
define|#
directive|define
name|__GIMP_TRANSFORM_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"tools/gimptool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_TOOL
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_TOOL
value|(gimp_transform_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformTool))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_TRANSFORM_TOOL))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TRANSFORM_TOOL))
end_define

begin_typedef
DECL|typedef|GimpTransformToolClass
typedef|typedef
name|struct
name|_GimpTransformToolClass
name|GimpTransformToolClass
typedef|;
end_typedef

begin_comment
comment|/*  transform directions  */
end_comment

begin_define
DECL|macro|TRANSFORM_TRADITIONAL
define|#
directive|define
name|TRANSFORM_TRADITIONAL
value|0
end_define

begin_define
DECL|macro|TRANSFORM_CORRECTIVE
define|#
directive|define
name|TRANSFORM_CORRECTIVE
value|1
end_define

begin_comment
comment|/* buffer sizes for scaling information strings (for the info dialog) */
end_comment

begin_define
DECL|macro|MAX_INFO_BUF
define|#
directive|define
name|MAX_INFO_BUF
value|40
end_define

begin_define
DECL|macro|TRAN_INFO_SIZE
define|#
directive|define
name|TRAN_INFO_SIZE
value|8
end_define

begin_enum
DECL|enum|BoundingBox
enum|enum
name|BoundingBox
block|{
DECL|enumerator|X0
DECL|enumerator|Y0
DECL|enumerator|X1
DECL|enumerator|Y1
DECL|enumerator|X2
DECL|enumerator|Y2
DECL|enumerator|X3
DECL|enumerator|Y3
name|X0
block|,
name|Y0
block|,
name|X1
block|,
name|Y1
block|,
name|X2
block|,
name|Y2
block|,
name|X3
block|,
name|Y3
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|TranInfo
typedef|typedef
name|gdouble
name|TranInfo
index|[
name|TRAN_INFO_SIZE
index|]
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTransformTool
struct|struct
name|_GimpTransformTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|startx
name|gint
name|startx
decl_stmt|;
comment|/*  starting x coord            */
DECL|member|starty
name|gint
name|starty
decl_stmt|;
comment|/*  starting y coord            */
DECL|member|curx
name|gint
name|curx
decl_stmt|;
comment|/*  current x coord             */
DECL|member|cury
name|gint
name|cury
decl_stmt|;
comment|/*  current y coord             */
DECL|member|lastx
name|gint
name|lastx
decl_stmt|;
comment|/*  last x coord                */
DECL|member|lasty
name|gint
name|lasty
decl_stmt|;
comment|/*  last y coord                */
DECL|member|state
name|gint
name|state
decl_stmt|;
comment|/*  state of buttons and keys   */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate  */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords     */
DECL|member|cx
DECL|member|cy
name|gint
name|cx
decl_stmt|,
name|cy
decl_stmt|;
comment|/*  center point (for rotation) */
DECL|member|tx1
DECL|member|ty1
name|gdouble
name|tx1
decl_stmt|,
name|ty1
decl_stmt|;
comment|/*  transformed coords          */
DECL|member|tx2
DECL|member|ty2
name|gdouble
name|tx2
decl_stmt|,
name|ty2
decl_stmt|;
comment|/*                              */
DECL|member|tx3
DECL|member|ty3
name|gdouble
name|tx3
decl_stmt|,
name|ty3
decl_stmt|;
comment|/*                              */
DECL|member|tx4
DECL|member|ty4
name|gdouble
name|tx4
decl_stmt|,
name|ty4
decl_stmt|;
comment|/*                              */
DECL|member|tcx
DECL|member|tcy
name|gdouble
name|tcx
decl_stmt|,
name|tcy
decl_stmt|;
comment|/*                              */
DECL|member|sx1
DECL|member|sy1
name|gint
name|sx1
decl_stmt|,
name|sy1
decl_stmt|;
comment|/*  transformed screen coords   */
DECL|member|sx2
DECL|member|sy2
name|gint
name|sx2
decl_stmt|,
name|sy2
decl_stmt|;
comment|/*  position of four handles    */
DECL|member|sx3
DECL|member|sy3
name|gint
name|sx3
decl_stmt|,
name|sy3
decl_stmt|;
comment|/*                              */
DECL|member|sx4
DECL|member|sy4
name|gint
name|sx4
decl_stmt|,
name|sy4
decl_stmt|;
comment|/*                              */
DECL|member|scx
DECL|member|scy
name|gint
name|scx
decl_stmt|,
name|scy
decl_stmt|;
comment|/*  and center for rotation     */
DECL|member|transform
name|GimpMatrix3
name|transform
decl_stmt|;
comment|/*  transformation matrix       */
DECL|member|trans_info
name|TranInfo
name|trans_info
decl_stmt|;
comment|/*  transformation info         */
DECL|member|original
name|TileManager
modifier|*
name|original
decl_stmt|;
comment|/*  pointer to original tiles   */
DECL|member|function
name|TransformAction
name|function
decl_stmt|;
comment|/*  current tool activity       */
DECL|member|interactive
name|gboolean
name|interactive
decl_stmt|;
comment|/*  tool is interactive         */
DECL|member|bpressed
name|gboolean
name|bpressed
decl_stmt|;
comment|/*  Bug work around make sure we have  				 *  a button pressed before we deal with 				 *  motion events. ALT. 				 */
DECL|member|ngx
DECL|member|ngy
name|gint
name|ngx
decl_stmt|,
name|ngy
decl_stmt|;
comment|/*  number of grid lines in original 				 *  x and y directions 				 */
DECL|member|grid_coords
name|gdouble
modifier|*
name|grid_coords
decl_stmt|;
comment|/*  x and y coordinates of the grid 				 *  endpoints (a total of (ngx+ngy)*2 				 *  coordinate pairs) 				 */
DECL|member|tgrid_coords
name|gdouble
modifier|*
name|tgrid_coords
decl_stmt|;
comment|/*  transformed grid_coords     */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTransformToolClass
struct|struct
name|_GimpTransformToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
DECL|member|transform
name|TileManager
modifier|*
function_decl|(
modifier|*
name|transform
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Special undo type  */
end_comment

begin_typedef
DECL|typedef|TransformUndo
typedef|typedef
name|struct
name|_TransformUndo
name|TransformUndo
typedef|;
end_typedef

begin_struct
DECL|struct|_TransformUndo
struct|struct
name|_TransformUndo
block|{
comment|/* Is this the right thing to do? */
DECL|member|tool
name|GimpTransformTool
modifier|*
name|tool
decl_stmt|;
DECL|member|trans_info
name|TranInfo
name|trans_info
decl_stmt|;
DECL|member|original
name|TileManager
modifier|*
name|original
decl_stmt|;
DECL|member|path_undo
name|gpointer
name|path_undo
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  make this variable available to all  */
end_comment

begin_comment
comment|/*  Do we still need to do this?  -- rock */
end_comment

begin_decl_stmt
specifier|extern
name|InfoDialog
modifier|*
name|transform_info
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  transform tool functions  */
end_comment

begin_comment
comment|/* make PDB compile: ToolType doesn't exist any more  Tool        * gimp_transform_tool_new                    (GimpTransformToolType        tool_type, 						     gboolean        interactive); */
end_comment

begin_function_decl
name|void
name|gimp_transform_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_no_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_transform_bounding_box
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_reset
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_grid_density_changed
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_showpath_changed
parameter_list|(
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_transform_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  transform functions  */
end_comment

begin_comment
comment|/* FIXME this function needs to be renamed */
end_comment

begin_function_decl
name|TileManager
modifier|*
name|gimp_transform_tool_do
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TileManager
modifier|*
name|float_tiles
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|GimpMatrix3
name|matrix
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_transform_tool_cut
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
modifier|*
name|new_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_transform_tool_paste
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gboolean
name|new_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_transform_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  FIXME These probably should no longer be global  */
end_comment

begin_function_decl
name|gboolean
name|gimp_transform_tool_smoothing
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_transform_tool_showpath
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_transform_tool_clip
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_transform_tool_direction
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_transform_tool_grid_size
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_transform_tool_show_grid
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TRANSFORM_TOOL_H__  */
end_comment

end_unit


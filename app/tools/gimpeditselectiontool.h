begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EDIT_SELECTION_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EDIT_SELECTION_TOOL_H__
define|#
directive|define
name|__GIMP_EDIT_SELECTION_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_EDIT_SELECTION_TOOL
define|#
directive|define
name|GIMP_TYPE_EDIT_SELECTION_TOOL
value|(gimp_edit_selection_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_EDIT_SELECTION_TOOL (obj)
define|#
directive|define
name|GIMP_EDIT_SELECTION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_EDIT_SELECTION_TOOL, GimpEditSelectionTool))
end_define

begin_define
DECL|macro|GIMP_EDIT_SELECTION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_EDIT_SELECTION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_EDIT_SELECTION_TOOL, GimpEditSelectionToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_EDIT_SELECTION_TOOL (obj)
define|#
directive|define
name|GIMP_IS_EDIT_SELECTION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_EDIT_SELECTION_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_EDIT_SELECTION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_EDIT_SELECTION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_EDIT_SELECTION_TOOL))
end_define

begin_typedef
DECL|typedef|GimpEditSelectionTool
typedef|typedef
name|struct
name|_GimpEditSelectionTool
name|GimpEditSelectionTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEditSelectionToolClass
typedef|typedef
name|struct
name|_GimpEditSelectionToolClass
name|GimpEditSelectionToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEditSelectionTool
struct|struct
name|_GimpEditSelectionTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|origx
DECL|member|origy
name|gint
name|origx
decl_stmt|,
name|origy
decl_stmt|;
comment|/*  Last x and y coords               */
DECL|member|cumlx
DECL|member|cumly
name|gint
name|cumlx
decl_stmt|,
name|cumly
decl_stmt|;
comment|/*  Cumulative changes to x and yed   */
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  Current x and y coords            */
DECL|member|num_segs_in
name|gint
name|num_segs_in
decl_stmt|;
comment|/*  Num seg in selection boundary     */
DECL|member|num_segs_out
name|gint
name|num_segs_out
decl_stmt|;
comment|/*  Num seg in selection boundary     */
DECL|member|segs_in
name|BoundSeg
modifier|*
name|segs_in
decl_stmt|;
comment|/*  Pointer to the channel sel. segs  */
DECL|member|segs_out
name|BoundSeg
modifier|*
name|segs_out
decl_stmt|;
comment|/*  Pointer to the channel sel. segs  */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  Bounding box of selection mask    */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
DECL|member|edit_mode
name|GimpTranslateMode
name|edit_mode
decl_stmt|;
comment|/*  Translate the mask or layer?      */
DECL|member|first_move
name|gboolean
name|first_move
decl_stmt|;
comment|/*  Don't push undos after the first  */
DECL|member|propagate_release
name|gboolean
name|propagate_release
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEditSelectionToolClass
struct|struct
name|_GimpEditSelectionToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_edit_selection_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_edit_selection_tool_start
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpTranslateMode
name|edit_mode
parameter_list|,
name|gboolean
name|propagate_release
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_edit_selection_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* could move this function to a more central location  * so it can be used by other tools?  */
end_comment

begin_function_decl
name|gint
name|process_event_queue_keys
parameter_list|(
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
modifier|...
comment|/* GdkKeyType, GdkModifierType, value ... 0 */
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_EDIT_SELECTION_TOOL_H__  */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|PAINT_LEFT_THRESHOLD
define|#
directive|define
name|PAINT_LEFT_THRESHOLD
value|0.05
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_INCREMENTAL
define|#
directive|define
name|PAINTBRUSH_DEFAULT_INCREMENTAL
value|FALSE
end_define

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_tool_class_init
parameter_list|(
name|GimpPaintbrushToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_tool_init
parameter_list|(
name|GimpPaintbrushTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_paintbrush_tool_register (Gimp * gimp,GimpToolRegisterCallback callback)
name|gimp_paintbrush_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|,
name|paint_options_new
argument_list|,
name|TRUE
argument_list|,
literal|"gimp:paintbrush_tool"
argument_list|,
name|_
argument_list|(
literal|"Paintbrush"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Paint fuzzy brush strokes"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Paint Tools/Paintbrush"
argument_list|)
argument_list|,
literal|"P"
argument_list|,
name|NULL
argument_list|,
literal|"tools/paintbrush.html"
argument_list|,
name|GIMP_STOCK_TOOL_PAINTBRUSH
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_paintbrush_tool_get_type (void)
name|gimp_paintbrush_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPaintbrushToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_paintbrush_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPaintbrushTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_paintbrush_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_TOOL
argument_list|,
literal|"GimpPaintbrushTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_paintbrush_tool_class_init (GimpPaintbrushToolClass * klass)
name|gimp_paintbrush_tool_class_init
parameter_list|(
name|GimpPaintbrushToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintToolClass
modifier|*
name|paint_tool_class
decl_stmt|;
name|paint_tool_class
operator|=
name|GIMP_PAINT_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paintbrush_tool_init (GimpPaintbrushTool * paintbrush)
name|gimp_paintbrush_tool_init
parameter_list|(
name|GimpPaintbrushTool
modifier|*
name|paintbrush
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|paintbrush
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|paintbrush
argument_list|)
expr_stmt|;
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_PAINTBRUSH_TOOL_CURSOR
expr_stmt|;
name|paint_tool
operator|->
name|pick_colors
operator|=
name|TRUE
expr_stmt|;
name|paint_tool
operator|->
name|core
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PAINTBRUSH
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|static GimpPaintbrushTool *non_gui_paintbrush = NULL;  gboolean gimp_paintbrush_tool_non_gui_default (GimpDrawable *drawable, 				      gint          num_strokes, 				      gdouble      *stroke_array) {   GimpPaintTool *paint_tool;   gint           i;    if (! non_gui_paintbrush)     {       non_gui_paintbrush = g_object_new (GIMP_TYPE_PAINTBRUSH_TOOL, NULL);     }    paint_tool = GIMP_PAINT_TOOL (non_gui_paintbrush);
comment|/* Hmmm... PDB paintbrush should have gradient type added to it!    * thats why the code below is duplicated.    */
end_comment

begin_comment
unit|if (gimp_paint_tool_start (paint_tool, drawable, 			     stroke_array[0], 			     stroke_array[1]))     {       paint_tool->start_coords.x = paint_tool->last_coords.x = stroke_array[0];       paint_tool->start_coords.y = paint_tool->last_coords.y = stroke_array[1];        gimp_paint_tool_paint (paint_tool, drawable, MOTION_PAINT);        for (i = 1; i< num_strokes; i++) 	{ 	  paint_tool->cur_coords.x = stroke_array[i * 2 + 0]; 	  paint_tool->cur_coords.y = stroke_array[i * 2 + 1];  	  gimp_paint_tool_interpolate (paint_tool, drawable);  	  paint_tool->last_coords.x = paint_tool->cur_coords.x; 	  paint_tool->last_coords.y = paint_tool->cur_coords.y; 	}        gimp_paint_tool_finish (paint_tool, drawable);        return TRUE;     }    return FALSE; }  gboolean gimp_paintbrush_tool_non_gui (GimpDrawable *drawable, 			      gint          num_strokes, 			      gdouble      *stroke_array, 			      gdouble       fade_out, 			      gint          method, 			      gdouble       gradient_length) {   GimpPaintTool *paint_tool;   gint           i;    if (! non_gui_paintbrush)     {       non_gui_paintbrush = g_object_new (GIMP_TYPE_PAINTBRUSH_TOOL, NULL);     }    paint_tool = GIMP_PAINT_TOOL (non_gui_paintbrush);
comment|/* Code duplicated above */
end_comment

begin_endif
unit|if (gimp_paint_tool_start (paint_tool, drawable, 			     stroke_array[0], 			     stroke_array[1]))     {       non_gui_gradient_options.fade_out        = fade_out;       non_gui_gradient_options.gradient_length = gradient_length;       non_gui_gradient_options.gradient_type   = LOOP_TRIANGLE;       non_gui_incremental                      = method;        paint_tool->start_coords.x = paint_tool->last_coords.x = stroke_array[0];       paint_tool->start_coords.y = paint_tool->last_coords.y = stroke_array[1];        gimp_paint_tool_paint (paint_tool, drawable, MOTION_PAINT);        for (i = 1; i< num_strokes; i++)        {          paint_tool->cur_coords.x = stroke_array[i * 2 + 0];          paint_tool->cur_coords.y = stroke_array[i * 2 + 1];           gimp_paint_tool_interpolate (paint_tool, drawable);  	 paint_tool->last_coords.x = paint_tool->cur_coords.x;          paint_tool->last_coords.y = paint_tool->cur_coords.y;        }        gimp_paint_tool_finish (paint_tool, drawable);        return TRUE;     }    return FALSE; }
endif|#
directive|endif
end_endif

end_unit


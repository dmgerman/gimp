begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbezierselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpblendtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrightnesscontrasttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbucketfilltool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbycolorselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpclonetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbalancetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpickertool.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolvetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcroptool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurvestool.h"
end_include

begin_include
include|#
directive|include
file|"gimpdodgeburntool.h"
end_include

begin_include
include|#
directive|include
file|"gimpellipseselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimperasertool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfliptool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfreeselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfuzzyselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogramtool.h"
end_include

begin_include
include|#
directive|include
file|"gimphuesaturationtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpinktool.h"
end_include

begin_include
include|#
directive|include
file|"gimpiscissorstool.h"
end_include

begin_include
include|#
directive|include
file|"gimplevelstool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmagnifytool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmeasuretool.h"
end_include

begin_include
include|#
directive|include
file|"gimpmovetool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimppathtool.h"
end_include

begin_include
include|#
directive|include
file|"gimppenciltool.h"
end_include

begin_include
include|#
directive|include
file|"gimpperspectivetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpposterizetool.h"
end_include

begin_include
include|#
directive|include
file|"gimprectselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpthresholdtool.h"
end_include

begin_include
include|#
directive|include
file|"gimprotatetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpscaletool.h"
end_include

begin_include
include|#
directive|include
file|"gimpsheartool.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudgetool.h"
end_include

begin_include
include|#
directive|include
file|"gimptexttool.h"
end_include

begin_function
name|void
DECL|function|tools_init (void)
name|tools_init
parameter_list|(
name|void
parameter_list|)
block|{
comment|/*  register tools in reverse order  */
comment|/*  color tools  */
name|gimp_posterize_tool_register
argument_list|()
expr_stmt|;
name|gimp_curves_tool_register
argument_list|()
expr_stmt|;
name|gimp_levels_tool_register
argument_list|()
expr_stmt|;
name|gimp_threshold_tool_register
argument_list|()
expr_stmt|;
name|gimp_brightness_contrast_tool_register
argument_list|()
expr_stmt|;
name|gimp_hue_saturation_tool_register
argument_list|()
expr_stmt|;
name|gimp_color_balance_tool_register
argument_list|()
expr_stmt|;
comment|/*  paint tools  */
name|gimp_smudge_tool_register
argument_list|()
expr_stmt|;
name|gimp_dodgeburn_tool_register
argument_list|()
expr_stmt|;
name|gimp_convolve_tool_register
argument_list|()
expr_stmt|;
name|gimp_clone_tool_register
argument_list|()
expr_stmt|;
name|gimp_ink_tool_register
argument_list|()
expr_stmt|;
name|gimp_airbrush_tool_register
argument_list|()
expr_stmt|;
name|gimp_eraser_tool_register
argument_list|()
expr_stmt|;
name|gimp_paintbrush_tool_register
argument_list|()
expr_stmt|;
name|gimp_pencil_tool_register
argument_list|()
expr_stmt|;
name|gimp_blend_tool_register
argument_list|()
expr_stmt|;
name|gimp_bucket_fill_tool_register
argument_list|()
expr_stmt|;
name|gimp_text_tool_register
argument_list|()
expr_stmt|;
comment|/*  transform tools  */
name|gimp_flip_tool_register
argument_list|()
expr_stmt|;
name|gimp_perspective_tool_register
argument_list|()
expr_stmt|;
name|gimp_shear_tool_register
argument_list|()
expr_stmt|;
name|gimp_scale_tool_register
argument_list|()
expr_stmt|;
name|gimp_rotate_tool_register
argument_list|()
expr_stmt|;
name|gimp_crop_tool_register
argument_list|()
expr_stmt|;
name|gimp_move_tool_register
argument_list|()
expr_stmt|;
comment|/*  non-modifying tools  */
name|gimp_path_tool_register
argument_list|()
expr_stmt|;
name|gimp_measure_tool_register
argument_list|()
expr_stmt|;
name|gimp_magnify_tool_register
argument_list|()
expr_stmt|;
name|gimp_histogram_tool_register
argument_list|()
expr_stmt|;
name|gimp_color_picker_tool_register
argument_list|()
expr_stmt|;
comment|/*  selection tools */
name|gimp_bezier_select_tool_register
argument_list|()
expr_stmt|;
name|gimp_iscissors_tool_register
argument_list|()
expr_stmt|;
name|gimp_by_color_select_tool_register
argument_list|()
expr_stmt|;
name|gimp_fuzzy_select_tool_register
argument_list|()
expr_stmt|;
name|gimp_free_select_tool_register
argument_list|()
expr_stmt|;
name|gimp_ellipse_select_tool_register
argument_list|()
expr_stmt|;
name|gimp_rect_select_tool_register
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_exit (void)
name|tools_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|hue_saturation_free
argument_list|()
expr_stmt|;
name|curves_free
argument_list|()
expr_stmt|;
name|levels_free
argument_list|()
expr_stmt|;
block|}
end_function

end_unit


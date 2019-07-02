begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsamplepointeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptoggleaction.h"
end_include

begin_include
include|#
directive|include
file|"sample-points-commands.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|sample_points_sample_merged_cmd_callback (GimpAction * action,gpointer data)
name|sample_points_sample_merged_cmd_callback
parameter_list|(
name|GimpAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpSamplePointEditor
modifier|*
name|editor
init|=
name|GIMP_SAMPLE_POINT_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|active
operator|=
name|gimp_toggle_action_get_active
argument_list|(
name|GIMP_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_sample_point_editor_set_sample_merged
argument_list|(
name|editor
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpsmudgeoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudgetool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_smudge_tool_init
parameter_list|(
name|GimpSmudgeTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_smudge_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_smudge_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_smudge_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_SMUDGE_TOOL
argument_list|,
name|GIMP_TYPE_SMUDGE_OPTIONS
argument_list|,
name|gimp_smudge_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
argument_list|,
literal|"gimp-smudge-tool"
argument_list|,
name|_
argument_list|(
literal|"Smudge"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Smudge image"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Smudge"
argument_list|)
argument_list|,
literal|"S"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_SMUDGE
argument_list|,
name|GIMP_STOCK_TOOL_SMUDGE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_smudge_tool_get_type (void)
name|gimp_smudge_tool_get_type
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
name|GimpSmudgeToolClass
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
name|NULL
block|,
comment|/* class_init     */
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpSmudgeTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_smudge_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_TOOL
argument_list|,
literal|"GimpSmudgeTool"
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

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_tool_init (GimpSmudgeTool * smudge)
name|gimp_smudge_tool_init
parameter_list|(
name|GimpSmudgeTool
modifier|*
name|smudge
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|smudge
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_SMUDGE
argument_list|)
expr_stmt|;
name|gimp_paint_tool_enable_color_picker
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|smudge
argument_list|)
argument_list|,
name|GIMP_COLOR_PICK_MODE_FOREGROUND
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  tool options stuff  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_smudge_options_gui (GimpToolOptions * tool_options)
name|gimp_smudge_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
comment|/*  the rate scale  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"rate"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Rate:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit


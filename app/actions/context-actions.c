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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"context-actions.h"
end_include

begin_include
include|#
directive|include
file|"context-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_decl_stmt
DECL|variable|context_actions
specifier|static
name|GimpActionEntry
name|context_actions
index|[]
init|=
block|{
block|{
literal|"context-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Context"
argument_list|)
block|}
block|,
block|{
literal|"context-colors-menu"
block|,
name|GIMP_STOCK_DEFAULT_COLORS
block|,
name|N_
argument_list|(
literal|"_Colors"
argument_list|)
block|}
block|,
block|{
literal|"context-opacity-menu"
block|,
name|GIMP_STOCK_TRANSPARENCY
block|,
name|N_
argument_list|(
literal|"_Opacity"
argument_list|)
block|}
block|,
block|{
literal|"context-brush-menu"
block|,
name|GIMP_STOCK_BRUSH
block|,
name|N_
argument_list|(
literal|"_Brush"
argument_list|)
block|}
block|,
block|{
literal|"context-pattern-menu"
block|,
name|GIMP_STOCK_PATTERN
block|,
name|N_
argument_list|(
literal|"_Pattern"
argument_list|)
block|}
block|,
block|{
literal|"context-palette-menu"
block|,
name|GIMP_STOCK_PALETTE
block|,
name|N_
argument_list|(
literal|"_Palette"
argument_list|)
block|}
block|,
block|{
literal|"context-gradient-menu"
block|,
name|GIMP_STOCK_GRADIENT
block|,
name|N_
argument_list|(
literal|"_Gradient"
argument_list|)
block|}
block|,
block|{
literal|"context-font-menu"
block|,
name|GIMP_STOCK_FONT
block|,
name|N_
argument_list|(
literal|"_Font"
argument_list|)
block|}
block|,
block|{
literal|"context-colors-default"
block|,
name|GIMP_STOCK_DEFAULT_COLORS
block|,
name|N_
argument_list|(
literal|"_Default Colors"
argument_list|)
block|,
literal|"D"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|context_colors_default_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOLBOX_DEFAULT_COLORS
block|}
block|,
block|{
literal|"context-colors-swap"
block|,
name|GIMP_STOCK_SWAP_COLORS
block|,
name|N_
argument_list|(
literal|"S_wap Colors"
argument_list|)
block|,
literal|"X"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|context_colors_swap_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOLBOX_SWAP_COLORS
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_foreground_red_actions
specifier|static
name|GimpEnumActionEntry
name|context_foreground_red_actions
index|[]
init|=
block|{
block|{
literal|"context-foreground-red-set"
block|,
name|NULL
block|,
literal|"Set Foreground Red"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-red-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Foreground Red Minimum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-red-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Foreground Red Maximum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-red-decrease"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Foreground Red Decrease"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-red-increase"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Foreground Red Increase"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-red-decrease-skip"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Foreground Red Decrease 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-red-increase-skip"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Foreground Red Increase 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_foreground_green_actions
specifier|static
name|GimpEnumActionEntry
name|context_foreground_green_actions
index|[]
init|=
block|{
block|{
literal|"context-foreground-green-set"
block|,
name|NULL
block|,
literal|"Set Foreground Green"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-green-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Foreground Green Minimum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-green-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Foreground Green Maximum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-green-decrease"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Foreground Green Decrease"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-green-increase"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Foreground Green Increase"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-green-decrease-skip"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Foreground Green Decrease 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-green-increase-skip"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Foreground Green Increase 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_foreground_blue_actions
specifier|static
name|GimpEnumActionEntry
name|context_foreground_blue_actions
index|[]
init|=
block|{
block|{
literal|"context-foreground-blue-set"
block|,
name|NULL
block|,
literal|"Set Foreground Blue"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-blue-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Foreground Blue Minimum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-blue-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Foreground Blue Maximum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-blue-decrease"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Foreground Blue Decrease"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-blue-increase"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Foreground Blue Increase"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-blue-decrease-skip"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Foreground Blue Decrease 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-foreground-blue-increase-skip"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Foreground Blue Increase 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_background_red_actions
specifier|static
name|GimpEnumActionEntry
name|context_background_red_actions
index|[]
init|=
block|{
block|{
literal|"context-background-red-set"
block|,
name|NULL
block|,
literal|"Set Background Red"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-red-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Background Red Minimum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-red-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Background Red Maximum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-red-decrease"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Background Red Decrease"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-red-increase"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Background Red Increase"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-red-decrease-skip"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Background Red Decrease 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-red-increase-skip"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Background Red Increase 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_background_green_actions
specifier|static
name|GimpEnumActionEntry
name|context_background_green_actions
index|[]
init|=
block|{
block|{
literal|"context-background-green-set"
block|,
name|NULL
block|,
literal|"Set Background Green"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-green-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Background Green Minimum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-green-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Background Green Maximum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-green-decrease"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Background Green Decrease"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-green-increase"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Background Green Increase"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-green-decrease-skip"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Background Green Decrease 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-green-increase-skip"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Background Green Increase 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_background_blue_actions
specifier|static
name|GimpEnumActionEntry
name|context_background_blue_actions
index|[]
init|=
block|{
block|{
literal|"context-background-blue-set"
block|,
name|NULL
block|,
literal|"Set Background Blue"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-blue-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Background Blue Minimum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-blue-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Background Blue Maximum"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-blue-decrease"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Background Blue Decrease"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-blue-increase"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Background Blue Increase"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-blue-decrease-skip"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"Background Blue Decrease 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-background-blue-increase-skip"
block|,
name|GTK_STOCK_ADD
block|,
literal|"Background Blue Increase 10%"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_opacity_actions
specifier|static
name|GimpEnumActionEntry
name|context_opacity_actions
index|[]
init|=
block|{
block|{
literal|"context-opacity-set"
block|,
name|NULL
block|,
literal|"Set Transparency"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"context-opacity-transparent"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Completely Transparent"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-opacity-opaque"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Completely Opaque"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-opacity-decrease"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"More Transparent"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-opacity-increase"
block|,
name|GTK_STOCK_ADD
block|,
literal|"More Opaque"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-opacity-decrease-skip"
block|,
name|GTK_STOCK_REMOVE
block|,
literal|"10% More Transparent"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-opacity-increase-skip"
block|,
name|GTK_STOCK_ADD
block|,
literal|"10% More Opaque"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_tool_select_actions
specifier|static
name|GimpEnumActionEntry
name|context_tool_select_actions
index|[]
init|=
block|{
block|{
literal|"context-tool-first"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"First Tool"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-tool-last"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Last Tool"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-tool-previous"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Previous Tool"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-tool-next"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Next Tool"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_brush_select_actions
specifier|static
name|GimpEnumActionEntry
name|context_brush_select_actions
index|[]
init|=
block|{
block|{
literal|"context-brush-first"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"First Brush"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-last"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Last Brush"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-previous"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Previous Brush"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-next"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Next Brush"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_pattern_select_actions
specifier|static
name|GimpEnumActionEntry
name|context_pattern_select_actions
index|[]
init|=
block|{
block|{
literal|"context-pattern-first"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"First Pattern"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-pattern-last"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Last Pattern"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-pattern-previous"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Previous Pattern"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-pattern-next"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Next Pattern"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_palette_select_actions
specifier|static
name|GimpEnumActionEntry
name|context_palette_select_actions
index|[]
init|=
block|{
block|{
literal|"context-palette-first"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"First Palette"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-palette-last"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Last Palette"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-palette-previous"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Previous Palette"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-palette-next"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Next Palette"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_gradient_select_actions
specifier|static
name|GimpEnumActionEntry
name|context_gradient_select_actions
index|[]
init|=
block|{
block|{
literal|"context-gradient-first"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"First Gradient"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-gradient-last"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Last Gradient"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-gradient-previous"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Previous Gradient"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-gradient-next"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Next Gradient"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_font_select_actions
specifier|static
name|GimpEnumActionEntry
name|context_font_select_actions
index|[]
init|=
block|{
block|{
literal|"context-font-first"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"First Font"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-font-last"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Last Font"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-font-previous"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Previous Font"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-font-next"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Next Font"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_brush_radius_actions
specifier|static
name|GimpEnumActionEntry
name|context_brush_radius_actions
index|[]
init|=
block|{
block|{
literal|"context-brush-radius-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Minumum Radius"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-radius-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Maximum Radius"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-radius-decrease"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Decrease Radius"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-radius-increase"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Increase Radius"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-radius-decrease-skip"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Decrease Radius More"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-radius-increase-skip"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Increase Radius More"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_brush_hardness_actions
specifier|static
name|GimpEnumActionEntry
name|context_brush_hardness_actions
index|[]
init|=
block|{
block|{
literal|"context-brush-hardness-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Minumum Hardness"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-hardness-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Maximum Hardness"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-hardness-decrease"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Decrease Hardness"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-hardness-increase"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Increase Hardness"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-hardness-decrease-skip"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Decrease Hardness More"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-hardness-increase-skip"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Increase Hardness More"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_brush_aspect_actions
specifier|static
name|GimpEnumActionEntry
name|context_brush_aspect_actions
index|[]
init|=
block|{
block|{
literal|"context-brush-aspect-minimum"
block|,
name|GTK_STOCK_GOTO_FIRST
block|,
literal|"Minumum Aspect"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-aspect-maximum"
block|,
name|GTK_STOCK_GOTO_LAST
block|,
literal|"Maximum Aspect"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-aspect-decrease"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Decrease Aspect"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-aspect-increase"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Increase Aspect"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-aspect-decrease-skip"
block|,
name|GTK_STOCK_GO_BACK
block|,
literal|"Decrease Aspect More"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-aspect-increase-skip"
block|,
name|GTK_STOCK_GO_FORWARD
block|,
literal|"Increase Aspect More"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|context_brush_angle_actions
specifier|static
name|GimpEnumActionEntry
name|context_brush_angle_actions
index|[]
init|=
block|{
block|{
literal|"context-brush-angle-minimum"
block|,
name|GIMP_STOCK_FLIP_HORIZONTAL
block|,
literal|"Horizontal"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-angle-maximum"
block|,
name|GIMP_STOCK_FLIP_VERTICAL
block|,
literal|"Vertical"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-angle-decrease"
block|,
name|GIMP_STOCK_ROTATE_90
block|,
literal|"Rotate Right"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-angle-increase"
block|,
name|GIMP_STOCK_ROTATE_270
block|,
literal|"Rotate Left"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-angle-decrease-skip"
block|,
name|GIMP_STOCK_ROTATE_90
block|,
literal|"Rotate Right 15 degrees"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"context-brush-angle-increase-skip"
block|,
name|GIMP_STOCK_ROTATE_270
block|,
literal|"Rotate Left 15 degrees"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|context_actions_setup (GimpActionGroup * group)
name|context_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|context_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_foreground_red_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_foreground_red_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_foreground_red_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_foreground_green_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_foreground_green_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_foreground_green_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_foreground_blue_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_foreground_blue_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_foreground_blue_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_background_red_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_background_red_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_background_red_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_background_green_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_background_green_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_background_green_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_background_blue_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_background_blue_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_background_blue_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_opacity_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_opacity_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_opacity_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_tool_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_tool_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_tool_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_brush_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_brush_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_brush_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_pattern_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_pattern_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_pattern_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_palette_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_palette_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_palette_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_gradient_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_gradient_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_gradient_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_font_select_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_font_select_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_font_select_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_brush_radius_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_brush_radius_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_brush_radius_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_brush_hardness_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_brush_hardness_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_brush_hardness_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_brush_aspect_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_brush_aspect_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_brush_aspect_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|context_brush_angle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|context_brush_angle_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|context_brush_angle_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|context_actions_update (GimpActionGroup * group,gpointer data)
name|context_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|gboolean
name|generated
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|radius
init|=
literal|0.0
decl_stmt|;
name|gboolean
name|hardness
init|=
literal|0.0
decl_stmt|;
name|gboolean
name|aspect
init|=
literal|0.0
decl_stmt|;
name|gboolean
name|angle
init|=
literal|0.0
decl_stmt|;
name|context
operator|=
name|action_data_get_context
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
condition|)
block|{
name|GimpBrushGenerated
modifier|*
name|gen
init|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
decl_stmt|;
name|generated
operator|=
name|TRUE
expr_stmt|;
name|radius
operator|=
name|gimp_brush_generated_get_radius
argument_list|(
name|gen
argument_list|)
expr_stmt|;
name|hardness
operator|=
name|gimp_brush_generated_get_hardness
argument_list|(
name|gen
argument_list|)
expr_stmt|;
name|aspect
operator|=
name|gimp_brush_generated_get_aspect_ratio
argument_list|(
name|gen
argument_list|)
expr_stmt|;
name|angle
operator|=
name|gimp_brush_generated_get_angle
argument_list|(
name|gen
argument_list|)
expr_stmt|;
block|}
block|}
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, "context-" action, (condition) != 0)
if|#
directive|if
literal|0
block|SET_SENSITIVE ("brush-radius-minimum",       generated&& radius> 1.0);   SET_SENSITIVE ("brush-radius-decrease",      generated&& radius> 1.0);   SET_SENSITIVE ("brush-radius-decrease-skip", generated&& radius> 1.0);    SET_SENSITIVE ("brush-radius-maximum",       generated&& radius< 4096.0);   SET_SENSITIVE ("brush-radius-increase",      generated&& radius< 4096.0);   SET_SENSITIVE ("brush-radius-increase-skip", generated&& radius< 4096.0);    SET_SENSITIVE ("brush-angle-minimum",       generated);   SET_SENSITIVE ("brush-angle-decrease",      generated);   SET_SENSITIVE ("brush-angle-decrease-skip", generated);    SET_SENSITIVE ("brush-angle-maximum",       generated);   SET_SENSITIVE ("brush-angle-increase",      generated);   SET_SENSITIVE ("brush-angle-increase-skip", generated);
endif|#
directive|endif
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit


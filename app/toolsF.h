begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOLS_F_H__
end_ifndef

begin_define
DECL|macro|__TOOLS_F_H__
define|#
directive|define
name|__TOOLS_F_H__
end_define

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_comment
comment|/*  eeek */
end_comment

begin_comment
comment|/*  Tool control actions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b205f980103
block|{
DECL|enumerator|PAUSE
name|PAUSE
block|,
DECL|enumerator|RESUME
name|RESUME
block|,
DECL|enumerator|HALT
name|HALT
block|,
DECL|enumerator|CURSOR_UPDATE
name|CURSOR_UPDATE
block|,
DECL|enumerator|DESTROY
name|DESTROY
block|,
DECL|enumerator|RECREATE
name|RECREATE
DECL|typedef|ToolAction
block|}
name|ToolAction
typedef|;
end_typedef

begin_comment
comment|/*  Tool types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b205f980203
block|{
DECL|enumerator|TOOL_TYPE_NONE
name|TOOL_TYPE_NONE
init|=
operator|-
literal|1
block|,
DECL|enumerator|FIRST_TOOLBOX_TOOL
name|FIRST_TOOLBOX_TOOL
init|=
literal|0
block|,
DECL|enumerator|RECT_SELECT
name|RECT_SELECT
init|=
name|FIRST_TOOLBOX_TOOL
block|,
DECL|enumerator|ELLIPSE_SELECT
name|ELLIPSE_SELECT
block|,
DECL|enumerator|FREE_SELECT
name|FREE_SELECT
block|,
DECL|enumerator|FUZZY_SELECT
name|FUZZY_SELECT
block|,
DECL|enumerator|BEZIER_SELECT
name|BEZIER_SELECT
block|,
DECL|enumerator|ISCISSORS
name|ISCISSORS
block|,
DECL|enumerator|MOVE
name|MOVE
block|,
DECL|enumerator|MAGNIFY
name|MAGNIFY
block|,
DECL|enumerator|CROP
name|CROP
block|,
DECL|enumerator|ROTATE
name|ROTATE
block|,
DECL|enumerator|SCALE
name|SCALE
block|,
DECL|enumerator|SHEAR
name|SHEAR
block|,
DECL|enumerator|PERSPECTIVE
name|PERSPECTIVE
block|,
DECL|enumerator|FLIP
name|FLIP
block|,
DECL|enumerator|TEXT
name|TEXT
block|,
DECL|enumerator|COLOR_PICKER
name|COLOR_PICKER
block|,
DECL|enumerator|BUCKET_FILL
name|BUCKET_FILL
block|,
DECL|enumerator|BLEND
name|BLEND
block|,
DECL|enumerator|PENCIL
name|PENCIL
block|,
DECL|enumerator|PAINTBRUSH
name|PAINTBRUSH
block|,
DECL|enumerator|ERASER
name|ERASER
block|,
DECL|enumerator|AIRBRUSH
name|AIRBRUSH
block|,
DECL|enumerator|CLONE
name|CLONE
block|,
DECL|enumerator|CONVOLVE
name|CONVOLVE
block|,
DECL|enumerator|INK
name|INK
block|,
DECL|enumerator|DODGEBURN
name|DODGEBURN
block|,
DECL|enumerator|SMUDGE
name|SMUDGE
block|,
DECL|enumerator|MEASURE
name|MEASURE
block|,
DECL|enumerator|LAST_TOOLBOX_TOOL
name|LAST_TOOLBOX_TOOL
init|=
name|MEASURE
block|,
comment|/*  Non-toolbox tools  */
DECL|enumerator|BY_COLOR_SELECT
name|BY_COLOR_SELECT
block|,
DECL|enumerator|COLOR_BALANCE
name|COLOR_BALANCE
block|,
DECL|enumerator|BRIGHTNESS_CONTRAST
name|BRIGHTNESS_CONTRAST
block|,
DECL|enumerator|HUE_SATURATION
name|HUE_SATURATION
block|,
DECL|enumerator|POSTERIZE
name|POSTERIZE
block|,
DECL|enumerator|THRESHOLD
name|THRESHOLD
block|,
DECL|enumerator|CURVES
name|CURVES
block|,
DECL|enumerator|LEVELS
name|LEVELS
block|,
DECL|enumerator|HISTOGRAM
name|HISTOGRAM
DECL|typedef|ToolType
block|}
name|ToolType
typedef|;
end_typedef

begin_comment
comment|/*  Structure definitions  */
end_comment

begin_typedef
DECL|typedef|Tool
typedef|typedef
name|struct
name|_Tool
name|Tool
typedef|;
end_typedef

begin_typedef
DECL|typedef|ToolInfo
typedef|typedef
name|struct
name|_ToolInfo
name|ToolInfo
typedef|;
end_typedef

begin_comment
comment|/*  Tool action function declarations  */
end_comment

begin_typedef
DECL|typedef|ButtonPressFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ButtonPressFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ButtonReleaseFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ButtonReleaseFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|MotionFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|MotionFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ArrowKeysFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ArrowKeysFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventKey
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ModifierKeyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ModifierKeyFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventKey
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|CursorUpdateFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|CursorUpdateFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|OperUpdateFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|OperUpdateFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ToolCtlFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ToolCtlFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|ToolAction
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  ToolInfo function declarations  */
end_comment

begin_typedef
DECL|typedef|ToolInfoNewFunc
typedef|typedef
name|Tool
modifier|*
function_decl|(
modifier|*
name|ToolInfoNewFunc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ToolInfoFreeFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ToolInfoFreeFunc
function_decl|)
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ToolInfoInitFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ToolInfoInitFunc
function_decl|)
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TOOLS_F_H__ */
end_comment

end_unit


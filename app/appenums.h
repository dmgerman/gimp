begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APPENUMS_H__
end_ifndef

begin_define
DECL|macro|__APPENUMS_H__
define|#
directive|define
name|__APPENUMS_H__
end_define

begin_comment
comment|/* Brush application types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28cae8310103
block|{
DECL|enumerator|HARD
name|HARD
block|,
comment|/* pencil */
DECL|enumerator|SOFT
name|SOFT
block|,
comment|/* paintbrush */
DECL|enumerator|PRESSURE
name|PRESSURE
comment|/* paintbrush with variable pressure */
DECL|typedef|BrushApplicationMode
block|}
name|BrushApplicationMode
typedef|;
end_typedef

begin_comment
comment|/* Paint application modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28cae8310203
block|{
DECL|enumerator|CONSTANT
name|CONSTANT
block|,
comment|/*< nick=CONTINUOUS>*/
comment|/* pencil, paintbrush, airbrush, clone */
DECL|enumerator|INCREMENTAL
name|INCREMENTAL
comment|/* convolve, smudge */
DECL|typedef|PaintApplicationMode
block|}
name|PaintApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=ADD_>*/
DECL|enum|__anon28cae8310303
block|{
DECL|enumerator|ADD_WHITE_MASK
name|ADD_WHITE_MASK
block|,
DECL|enumerator|ADD_BLACK_MASK
name|ADD_BLACK_MASK
block|,
DECL|enumerator|ADD_ALPHA_MASK
name|ADD_ALPHA_MASK
block|,
DECL|enumerator|ADD_SELECTION_MASK
name|ADD_SELECTION_MASK
block|,
DECL|enumerator|ADD_INV_SELECTION_MASK
name|ADD_INV_SELECTION_MASK
DECL|typedef|AddMaskType
block|}
name|AddMaskType
typedef|;
end_typedef

begin_comment
comment|/* gradient paint modes */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28cae8310403
block|{
DECL|enumerator|ONCE_FORWARD
name|ONCE_FORWARD
block|,
comment|/* paint through once, then stop */
DECL|enumerator|ONCE_BACKWARDS
name|ONCE_BACKWARDS
block|,
comment|/* paint once, then stop, but run the gradient the other way */
DECL|enumerator|LOOP_SAWTOOTH
name|LOOP_SAWTOOTH
block|,
comment|/* keep painting, looping through the grad start->end,start->end /|/|/| */
DECL|enumerator|LOOP_TRIANGLE
name|LOOP_TRIANGLE
block|,
comment|/* keep paiting, looping though the grad start->end,end->start /\/\/\/  */
DECL|enumerator|ONCE_END_COLOR
name|ONCE_END_COLOR
comment|/* paint once, but keep painting with the end color */
DECL|typedef|GradientPaintMode
block|}
name|GradientPaintMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28cae8310503
block|{
DECL|enumerator|ORIENTATION_UNKNOWN
name|ORIENTATION_UNKNOWN
block|,
DECL|enumerator|ORIENTATION_HORIZONTAL
name|ORIENTATION_HORIZONTAL
block|,
DECL|enumerator|ORIENTATION_VERTICAL
name|ORIENTATION_VERTICAL
DECL|typedef|InternalOrientationType
block|}
name|InternalOrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28cae8310603
block|{
DECL|enumerator|HORIZONTAL
name|HORIZONTAL
block|,
DECL|enumerator|VERTICAL
name|VERTICAL
block|,
DECL|enumerator|UNKNOWN
name|UNKNOWN
DECL|typedef|OrientationType
block|}
name|OrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28cae8310703
block|{
DECL|enumerator|GIMP_ZOOM_IN
name|GIMP_ZOOM_IN
block|,
DECL|enumerator|GIMP_ZOOM_OUT
name|GIMP_ZOOM_OUT
DECL|typedef|GimpZoomType
block|}
name|GimpZoomType
typedef|;
end_typedef

begin_comment
comment|/*  Selection Boolean operations  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=CHANNEL_OP_>*/
DECL|enum|__anon28cae8310803
block|{
DECL|enumerator|CHANNEL_OP_ADD
name|CHANNEL_OP_ADD
block|,
DECL|enumerator|CHANNEL_OP_SUB
name|CHANNEL_OP_SUB
block|,
DECL|enumerator|CHANNEL_OP_REPLACE
name|CHANNEL_OP_REPLACE
block|,
DECL|enumerator|CHANNEL_OP_INTERSECT
name|CHANNEL_OP_INTERSECT
DECL|typedef|ChannelOps
block|}
name|ChannelOps
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28cae8310903
block|{
DECL|enumerator|SELECTION_ADD
name|SELECTION_ADD
init|=
name|CHANNEL_OP_ADD
block|,
DECL|enumerator|SELECTION_SUB
name|SELECTION_SUB
init|=
name|CHANNEL_OP_SUB
block|,
DECL|enumerator|SELECTION_REPLACE
name|SELECTION_REPLACE
init|=
name|CHANNEL_OP_REPLACE
block|,
DECL|enumerator|SELECTION_INTERSECT
name|SELECTION_INTERSECT
init|=
name|CHANNEL_OP_INTERSECT
block|,
DECL|enumerator|SELECTION_MOVE_MASK
name|SELECTION_MOVE_MASK
block|,
DECL|enumerator|SELECTION_MOVE
name|SELECTION_MOVE
block|,
DECL|enumerator|SELECTION_ANCHOR
name|SELECTION_ANCHOR
DECL|typedef|SelectOps
block|}
name|SelectOps
typedef|;
end_typedef

begin_comment
comment|/*  Plug-In run modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28cae8310a03
block|{
DECL|enumerator|RUN_INTERACTIVE
name|RUN_INTERACTIVE
init|=
literal|0
block|,
DECL|enumerator|RUN_NONINTERACTIVE
name|RUN_NONINTERACTIVE
init|=
literal|1
block|,
DECL|enumerator|RUN_WITH_LAST_VALS
name|RUN_WITH_LAST_VALS
init|=
literal|2
DECL|typedef|RunModeType
block|}
name|RunModeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28cae8310b03
block|{
DECL|enumerator|CURSOR_MODE_TOOL_ICON
name|CURSOR_MODE_TOOL_ICON
block|,
DECL|enumerator|CURSOR_MODE_TOOL_CROSSHAIR
name|CURSOR_MODE_TOOL_CROSSHAIR
block|,
DECL|enumerator|CURSOR_MODE_CROSSHAIR
name|CURSOR_MODE_CROSSHAIR
DECL|typedef|CursorMode
block|}
name|CursorMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APPENUMS_H__ */
end_comment

end_unit


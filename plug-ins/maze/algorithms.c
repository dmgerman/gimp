begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* $Id$  * Contains routines for generating mazes, somewhat intertwined with   * Gimp plug-in-maze specific stuff.  *  * Kevin Turner<acapnotic@users.sourceforge.net>  * http://gimp-plug-ins.sourceforge.net/maze/  */
end_comment

begin_comment
comment|/* mazegen code from rec.games.programmer's maze-faq:  * * maz.c - generate a maze  * *  * * algorithm posted to rec.games.programmer by jallen@ic.sunysb.edu  * * program cleaned and reorganized by mzraly@ldbvax.dnet.lotus.com  * *  * * don't make people pay for this, or I'll jump up and down and  * * yell and scream and embarass you in front of your friends...  */
end_comment

begin_comment
comment|/* I've put a HTMLized version of the FAQ up at   * http://www.poboxes.com/kevint/gimp/maze-faq/maze-faq.html  */
end_comment

begin_comment
comment|/*  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|SOLO_COMPILE
end_ifndef

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"maze.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
specifier|extern
name|MazeValues
name|mvals
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|mazegen
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gchar
modifier|*
name|maz
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mazegen_tileable
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gchar
modifier|*
name|maz
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|prim
parameter_list|(
name|guint
name|pos
parameter_list|,
name|gchar
modifier|*
name|maz
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|prim_tileable
parameter_list|(
name|gchar
modifier|*
name|maz
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ABSMOD (A,B)
define|#
directive|define
name|ABSMOD
parameter_list|(
name|A
parameter_list|,
name|B
parameter_list|)
value|( ((A)< 0) ? (((B) + (A)) % (B)) : ((A) % (B)) )
end_define

begin_comment
comment|/* Since we are using a 1D array on 2D space, we need to do our own    calculations.  (Ok, so there are ways of doing dynamically allocated    2D arrays, but we started this way, so let's stick with it. */
end_comment

begin_comment
comment|/* The difference between CELL_* and WALL_* is that cell moves two spaces,    while wall moves one. */
end_comment

begin_comment
comment|/* Macros assume that x and y will be defined where they are used. */
end_comment

begin_comment
comment|/* A return of -1 means "no such place, don't go there". */
end_comment

begin_define
DECL|macro|CELL_UP (POS)
define|#
directive|define
name|CELL_UP
parameter_list|(
name|POS
parameter_list|)
value|((POS)< (x*2) ? -1 : (POS) - x - x)
end_define

begin_define
DECL|macro|CELL_DOWN (POS)
define|#
directive|define
name|CELL_DOWN
parameter_list|(
name|POS
parameter_list|)
value|((POS)>= x*(y-2) ? -1 : (POS) + x + x)
end_define

begin_define
DECL|macro|CELL_LEFT (POS)
define|#
directive|define
name|CELL_LEFT
parameter_list|(
name|POS
parameter_list|)
value|(((POS) % x)<= 1 ? -1 : (POS) - 2)
end_define

begin_define
DECL|macro|CELL_RIGHT (POS)
define|#
directive|define
name|CELL_RIGHT
parameter_list|(
name|POS
parameter_list|)
value|(((POS) % x)>= (x - 2) ? -1 : (POS) + 2)
end_define

begin_comment
comment|/* With walls, we don't need to check for boundaries, since we are    assured that there *is* a valid cell on the other side of the    wall. */
end_comment

begin_define
DECL|macro|WALL_UP (POS)
define|#
directive|define
name|WALL_UP
parameter_list|(
name|POS
parameter_list|)
value|((POS) - x)
end_define

begin_define
DECL|macro|WALL_DOWN (POS)
define|#
directive|define
name|WALL_DOWN
parameter_list|(
name|POS
parameter_list|)
value|((POS) + x)
end_define

begin_define
DECL|macro|WALL_LEFT (POS)
define|#
directive|define
name|WALL_LEFT
parameter_list|(
name|POS
parameter_list|)
value|((POS) - 1)
end_define

begin_define
DECL|macro|WALL_RIGHT (POS)
define|#
directive|define
name|WALL_RIGHT
parameter_list|(
name|POS
parameter_list|)
value|((POS) + 1)
end_define

begin_comment
comment|/***** For tileable mazes *****/
end_comment

begin_define
DECL|macro|CELL_UP_TILEABLE (POS)
define|#
directive|define
name|CELL_UP_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|((POS)< (x*2) ? x*(y-2)+(POS) : (POS) - x - x)
end_define

begin_define
DECL|macro|CELL_DOWN_TILEABLE (POS)
define|#
directive|define
name|CELL_DOWN_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|((POS)>= x*(y-2) ? (POS) - x*(y-2) : (POS) + x + x)
end_define

begin_define
DECL|macro|CELL_LEFT_TILEABLE (POS)
define|#
directive|define
name|CELL_LEFT_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|(((POS) % x)<= 1 ? (POS) + x - 2 : (POS) - 2)
end_define

begin_define
DECL|macro|CELL_RIGHT_TILEABLE (POS)
define|#
directive|define
name|CELL_RIGHT_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|(((POS) % x)>= (x - 2) ? (POS) + 2 - x : (POS) + 2)
end_define

begin_comment
comment|/* Up and left need checks, but down and right should never have to    wrap on an even sized maze. */
end_comment

begin_define
DECL|macro|WALL_UP_TILEABLE (POS)
define|#
directive|define
name|WALL_UP_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|((POS)< x ? x*(y-1)+(POS) : (POS) - x)
end_define

begin_define
DECL|macro|WALL_DOWN_TILEABLE (POS)
define|#
directive|define
name|WALL_DOWN_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|((POS) + x)
end_define

begin_define
DECL|macro|WALL_LEFT_TILEABLE (POS)
define|#
directive|define
name|WALL_LEFT_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|(((POS) % x) == 0 ? (POS) + x - 1 : (POS) - 1)
end_define

begin_define
DECL|macro|WALL_RIGHT_TILEABLE (POS)
define|#
directive|define
name|WALL_RIGHT_TILEABLE
parameter_list|(
name|POS
parameter_list|)
value|((POS) + 1)
end_define

begin_comment
comment|/* Down and right with checks. #define WALL_DOWN_TILEABLE(POS) ((POS)>= x*(y-1) ? (POS) - x * (y-1) : (POS) + x) #define WALL_RIGHT_TILEABLE(POS) (((POS) % x) == (x - 1) ? (POS) + 1 - x : (POS) + 1) */
end_comment

begin_comment
comment|/* The Incredible Recursive Maze Generation Routine */
end_comment

begin_comment
comment|/* Ripped from rec.programmers.games maze-faq       */
end_comment

begin_comment
comment|/* Modified and commented by me, Kevin Turner. */
end_comment

begin_function
name|void
DECL|function|mazegen (gint pos,gchar * maz,gint x,gint y,gint rnd)
name|mazegen
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gchar
modifier|*
name|maz
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
block|{
name|gchar
name|d
decl_stmt|,
name|i
decl_stmt|;
name|gint
name|c
init|=
literal|0
decl_stmt|,
name|j
init|=
literal|1
decl_stmt|;
comment|/* Punch a hole here...  */
name|maz
index|[
name|pos
index|]
operator|=
name|IN
expr_stmt|;
comment|/* If there is a wall two rows above us, bit 1 is 1. */
while|while
condition|(
operator|(
name|d
operator|=
operator|(
name|pos
operator|<=
operator|(
name|x
operator|*
literal|2
operator|)
condition|?
literal|0
else|:
operator|(
name|maz
index|[
name|pos
operator|-
name|x
operator|-
name|x
index|]
condition|?
literal|0
else|:
literal|1
operator|)
operator|)
comment|/* If there is a wall two rows below us, bit 2 is 1. */
operator||
operator|(
name|pos
operator|>=
name|x
operator|*
operator|(
name|y
operator|-
literal|2
operator|)
condition|?
literal|0
else|:
operator|(
name|maz
index|[
name|pos
operator|+
name|x
operator|+
name|x
index|]
condition|?
literal|0
else|:
literal|2
operator|)
operator|)
comment|/* If there is a wall two columns to the right, bit 3 is 1. */
operator||
operator|(
name|pos
operator|%
name|x
operator|==
name|x
operator|-
literal|2
condition|?
literal|0
else|:
operator|(
name|maz
index|[
name|pos
operator|+
literal|2
index|]
condition|?
literal|0
else|:
literal|4
operator|)
operator|)
comment|/* If there is a wall two colums to the left, bit 4 is 1.  */
operator||
operator|(
operator|(
name|pos
operator|%
name|x
operator|==
literal|1
operator|)
condition|?
literal|0
else|:
operator|(
name|maz
index|[
name|pos
operator|-
literal|2
index|]
condition|?
literal|0
else|:
literal|8
operator|)
operator|)
operator|)
condition|)
block|{
comment|/* Note if all bits are 0, d is false, we don't do this 	   while loop, we don't call ourselves again, so this branch            is done.  */
comment|/* I see what this loop does (more or less), but I don't know 	   _why_ it does it this way...  I also haven't figured out exactly 	   which values of multiple will work and which won't.  */
do|do
block|{
name|rnd
operator|=
operator|(
name|rnd
operator|*
name|mvals
operator|.
name|multiple
operator|+
name|mvals
operator|.
name|offset
operator|)
expr_stmt|;
name|i
operator|=
literal|3
operator|&
operator|(
name|rnd
operator|/
name|d
operator|)
expr_stmt|;
if|if
condition|(
operator|++
name|c
operator|>
literal|100
condition|)
block|{
comment|/* Break and try to salvage something */
name|i
operator|=
literal|99
expr_stmt|;
comment|/* if it looks like we're going to be */
break|break;
comment|/* here forever...                    */
block|}
block|}
do|while
condition|(
operator|!
operator|(
name|d
operator|&
operator|(
literal|1
operator|<<
name|i
operator|)
operator|)
condition|)
do|;
comment|/* ...While there's *not* a wall in direction i. */
comment|/* (stop looping when there is) */
switch|switch
condition|(
name|i
condition|)
block|{
comment|/* This is simple enough. */
case|case
literal|0
case|:
comment|/* Go in the direction we just figured . . . */
name|j
operator|=
operator|-
name|x
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|j
operator|=
name|x
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|j
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|j
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
literal|99
case|:
return|return;
comment|/* Hey neat, broken mazes! */
break|break;
comment|/* (Umm... Wow... Yeah, neat.) */
default|default:
name|g_warning
argument_list|(
literal|"maze: mazegen: Going in unknown direction.\n"
literal|"i: %d, d: %d, seed: %d, mw: %d, mh: %d, mult: %d, offset: %d\n"
argument_list|,
name|i
argument_list|,
name|d
argument_list|,
name|mvals
operator|.
name|seed
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|mvals
operator|.
name|multiple
argument_list|,
name|mvals
operator|.
name|offset
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* And punch a hole there. */
name|maz
index|[
name|pos
operator|+
name|j
index|]
operator|=
literal|1
expr_stmt|;
comment|/* Now, start again just past where we punched the hole... */
name|mazegen
argument_list|(
name|pos
operator|+
literal|2
operator|*
name|j
argument_list|,
name|maz
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|rnd
argument_list|)
expr_stmt|;
block|}
comment|/* End while(d=...) Loop */
comment|/* This routine is quite quick, even for rather large mazes.        For that reason, it doesn't need a progress bar. */
return|return;
block|}
end_function

begin_comment
comment|/* Tileable mazes are my creation, based on the routine above. */
end_comment

begin_function
name|void
DECL|function|mazegen_tileable (gint pos,gchar * maz,gint x,gint y,gint rnd)
name|mazegen_tileable
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gchar
modifier|*
name|maz
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
block|{
name|gchar
name|d
decl_stmt|,
name|i
decl_stmt|;
name|gint
name|c
init|=
literal|0
decl_stmt|,
name|npos
init|=
literal|2
decl_stmt|;
comment|/* Punch a hole here...  */
name|maz
index|[
name|pos
index|]
operator|=
name|IN
expr_stmt|;
comment|/* If there is a wall two rows above us, bit 1 is 1. */
while|while
condition|(
operator|(
name|d
operator|=
operator|(
name|maz
index|[
name|CELL_UP_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
condition|?
literal|0
else|:
literal|1
operator|)
comment|/* If there is a wall two rows below us, bit 2 is 1. */
operator||
operator|(
name|maz
index|[
name|CELL_DOWN_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
condition|?
literal|0
else|:
literal|2
operator|)
comment|/* If there is a wall two columns to the right, bit 3 is 1. */
operator||
operator|(
name|maz
index|[
name|CELL_RIGHT_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
condition|?
literal|0
else|:
literal|4
operator|)
comment|/* If there is a wall two colums to the left, bit 4 is 1.  */
operator||
operator|(
name|maz
index|[
name|CELL_LEFT_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
condition|?
literal|0
else|:
literal|8
operator|)
operator|)
condition|)
block|{
comment|/* Note if all bits are 0, d is false, we don't do this 	   while loop, we don't call ourselves again, so this branch            is done.  */
comment|/* I see what this loop does (more or less), but I don't know 	   _why_ it does it this way...  I also haven't figured out exactly 	   which values of multiple will work and which won't.  */
do|do
block|{
name|rnd
operator|=
operator|(
name|rnd
operator|*
name|mvals
operator|.
name|multiple
operator|+
name|mvals
operator|.
name|offset
operator|)
expr_stmt|;
name|i
operator|=
literal|3
operator|&
operator|(
name|rnd
operator|/
name|d
operator|)
expr_stmt|;
if|if
condition|(
operator|++
name|c
operator|>
literal|100
condition|)
block|{
comment|/* Break and try to salvage something */
name|i
operator|=
literal|99
expr_stmt|;
comment|/* if it looks like we're going to be */
break|break;
comment|/* here forever...                    */
block|}
block|}
do|while
condition|(
operator|!
operator|(
name|d
operator|&
operator|(
literal|1
operator|<<
name|i
operator|)
operator|)
condition|)
do|;
comment|/* ...While there's *not* a wall in direction i. */
comment|/* (stop looping when there is) */
switch|switch
condition|(
name|i
condition|)
block|{
comment|/* This is simple enough. */
case|case
literal|0
case|:
comment|/* Go in the direction we just figured . . . */
name|maz
index|[
name|WALL_UP_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
name|IN
expr_stmt|;
name|npos
operator|=
name|CELL_UP_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|maz
index|[
name|WALL_DOWN_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
name|IN
expr_stmt|;
name|npos
operator|=
name|CELL_DOWN_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|maz
index|[
name|WALL_RIGHT_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
name|IN
expr_stmt|;
name|npos
operator|=
name|CELL_RIGHT_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|maz
index|[
name|WALL_LEFT_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
name|IN
expr_stmt|;
name|npos
operator|=
name|CELL_LEFT_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
break|break;
case|case
literal|99
case|:
return|return;
comment|/* Hey neat, broken mazes! */
break|break;
comment|/* (Umm... Wow... Yeah, neat.) */
default|default:
name|g_warning
argument_list|(
literal|"maze: mazegen_tileable: Going in unknown direction.\n"
literal|"i: %d, d: %d, seed: %d, mw: %d, mh: %d, mult: %d, offset: %d\n"
argument_list|,
name|i
argument_list|,
name|d
argument_list|,
name|mvals
operator|.
name|seed
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|mvals
operator|.
name|multiple
argument_list|,
name|mvals
operator|.
name|offset
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/* Now, start again just past where we punched the hole... */
name|mazegen_tileable
argument_list|(
name|npos
argument_list|,
name|maz
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|rnd
argument_list|)
expr_stmt|;
block|}
comment|/* End while(d=...) Loop */
return|return;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static void print_glist(gpointer data, gpointer user_data) {      g_print("%d ",(guint)data); }
endif|#
directive|endif
end_endif

begin_comment
comment|/* This function (as well as prim_tileable) make use of the somewhat    unclean practice of storing ints as pointers.  I've been informed    that this may cause problems with 64-bit stuff.  However, hopefully    it will be okay, since the only values stored are positive.  If it    does break, let me know, and I'll go cry in a corner for a while    before I get up the strength to re-code it. */
end_comment

begin_function
name|void
DECL|function|prim (guint pos,gchar * maz,guint x,guint y,gint rnd)
name|prim
parameter_list|(
name|guint
name|pos
parameter_list|,
name|gchar
modifier|*
name|maz
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
block|{
name|GSList
modifier|*
name|front_cells
init|=
name|NULL
decl_stmt|;
name|guint
name|current
decl_stmt|;
name|gint
name|up
decl_stmt|,
name|down
decl_stmt|,
name|left
decl_stmt|,
name|right
decl_stmt|;
comment|/* Not unsigned, because macros return -1. */
name|guint
name|progress
init|=
literal|0
decl_stmt|,
name|max_progress
decl_stmt|;
name|char
name|d
decl_stmt|,
name|i
decl_stmt|;
name|guint
name|c
init|=
literal|0
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Constructing maze using Prim's Algorithm..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/* OUT is zero, so we should be already initalized. */
name|max_progress
operator|=
name|x
operator|*
name|y
operator|/
literal|4
expr_stmt|;
comment|/* Starting position has already been determined by the calling function. */
name|maz
index|[
name|pos
index|]
operator|=
name|IN
expr_stmt|;
comment|/* For now, repeating everything four times seems manageable.  But when  	Gimp is extended to drawings in n-dimensional space instead of 2D,         this will require a bit of a re-write. */
comment|/* Add frontier. */
name|up
operator|=
name|CELL_UP
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|down
operator|=
name|CELL_DOWN
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|left
operator|=
name|CELL_LEFT
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|right
operator|=
name|CELL_RIGHT
argument_list|(
name|pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|up
operator|>=
literal|0
condition|)
block|{
name|maz
index|[
name|up
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|up
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|down
operator|>=
literal|0
condition|)
block|{
name|maz
index|[
name|up
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|down
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|left
operator|>=
literal|0
condition|)
block|{
name|maz
index|[
name|up
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|left
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|right
operator|>=
literal|0
condition|)
block|{
name|maz
index|[
name|up
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|right
argument_list|)
expr_stmt|;
block|}
comment|/* While frontier is not empty do the following... */
while|while
condition|(
name|g_slist_length
argument_list|(
name|front_cells
argument_list|)
operator|>
literal|0
condition|)
block|{
comment|/* Remove one cell at random from frontier and place it in IN. */
name|current
operator|=
name|rand
argument_list|()
operator|%
name|g_slist_length
argument_list|(
name|front_cells
argument_list|)
expr_stmt|;
name|pos
operator|=
operator|(
name|guint
operator|)
name|g_slist_nth
argument_list|(
name|front_cells
argument_list|,
name|current
argument_list|)
operator|->
name|data
expr_stmt|;
name|front_cells
operator|=
name|g_slist_remove
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|pos
argument_list|)
expr_stmt|;
name|maz
index|[
name|pos
index|]
operator|=
name|IN
expr_stmt|;
comment|/* If the cell has any neighbors in OUT, remove them from              OUT and place them in FRONTIER. */
name|up
operator|=
name|CELL_UP
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|down
operator|=
name|CELL_DOWN
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|left
operator|=
name|CELL_LEFT
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|right
operator|=
name|CELL_RIGHT
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|d
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|up
operator|>=
literal|0
condition|)
block|{
switch|switch
condition|(
name|maz
index|[
name|up
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|up
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_prepend
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|up
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
block|}
if|if
condition|(
name|down
operator|>=
literal|0
condition|)
block|{
switch|switch
condition|(
name|maz
index|[
name|down
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|down
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_prepend
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|down
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
name|d
operator||
literal|2
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
block|}
if|if
condition|(
name|left
operator|>=
literal|0
condition|)
block|{
switch|switch
condition|(
name|maz
index|[
name|left
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|left
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_prepend
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|left
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
name|d
operator||
literal|4
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
block|}
if|if
condition|(
name|right
operator|>=
literal|0
condition|)
block|{
switch|switch
condition|(
name|maz
index|[
name|right
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|right
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_prepend
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|right
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
name|d
operator||
literal|8
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
block|}
comment|/* The cell is guaranteed to have at least one neighbor in 	     IN (otherwise it would not have been in FRONTIER); pick 	     one such neighbor at random and connect it to the new 	     cell (ie knock out a wall).  */
if|if
condition|(
operator|!
name|d
condition|)
block|{
name|g_warning
argument_list|(
literal|"maze: prim: Lack of neighbors.\n"
literal|"seed: %d, mw: %d, mh: %d, mult: %d, offset: %d\n"
argument_list|,
name|mvals
operator|.
name|seed
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|mvals
operator|.
name|multiple
argument_list|,
name|mvals
operator|.
name|offset
argument_list|)
expr_stmt|;
break|break;
block|}
name|c
operator|=
literal|0
expr_stmt|;
do|do
block|{
name|rnd
operator|=
operator|(
name|rnd
operator|*
name|mvals
operator|.
name|multiple
operator|+
name|mvals
operator|.
name|offset
operator|)
expr_stmt|;
name|i
operator|=
literal|3
operator|&
operator|(
name|rnd
operator|/
name|d
operator|)
expr_stmt|;
if|if
condition|(
operator|++
name|c
operator|>
literal|100
condition|)
block|{
comment|/* Break and try to salvage something */
name|i
operator|=
literal|99
expr_stmt|;
comment|/* if it looks like we're going to be */
break|break;
comment|/* here forever...                    */
block|}
block|}
do|while
condition|(
operator|!
operator|(
name|d
operator|&
operator|(
literal|1
operator|<<
name|i
operator|)
operator|)
condition|)
do|;
switch|switch
condition|(
name|i
condition|)
block|{
case|case
literal|0
case|:
name|maz
index|[
name|WALL_UP
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|maz
index|[
name|WALL_DOWN
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|maz
index|[
name|WALL_LEFT
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|maz
index|[
name|WALL_RIGHT
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|99
case|:
break|break;
default|default:
name|g_warning
argument_list|(
literal|"maze: prim: Going in unknown direction.\n"
literal|"i: %d, d: %d, seed: %d, mw: %d, mh: %d, mult: %d, offset: %d\n"
argument_list|,
name|i
argument_list|,
name|d
argument_list|,
name|mvals
operator|.
name|seed
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|mvals
operator|.
name|multiple
argument_list|,
name|mvals
operator|.
name|offset
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|progress
operator|++
operator|%
name|PRIMS_PROGRESS_UPDATE
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
comment|/* while front_cells */
name|g_slist_free
argument_list|(
name|front_cells
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* prim */
end_comment

begin_function
name|void
DECL|function|prim_tileable (gchar * maz,guint x,guint y,gint rnd)
name|prim_tileable
parameter_list|(
name|gchar
modifier|*
name|maz
parameter_list|,
name|guint
name|x
parameter_list|,
name|guint
name|y
parameter_list|,
name|gint
name|rnd
parameter_list|)
block|{
name|GSList
modifier|*
name|front_cells
init|=
name|NULL
decl_stmt|;
name|guint
name|current
decl_stmt|,
name|pos
decl_stmt|;
name|guint
name|up
decl_stmt|,
name|down
decl_stmt|,
name|left
decl_stmt|,
name|right
decl_stmt|;
name|guint
name|progress
init|=
literal|0
decl_stmt|,
name|max_progress
decl_stmt|;
name|char
name|d
decl_stmt|,
name|i
decl_stmt|;
name|guint
name|c
init|=
literal|0
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Constructing tileable maze using Prim's Algorithm..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/* OUT is zero, so we should be already initalized. */
name|max_progress
operator|=
name|x
operator|*
name|y
operator|/
literal|4
expr_stmt|;
comment|/* Pick someplace to start. */
name|srand
argument_list|(
name|rnd
argument_list|)
expr_stmt|;
name|pos
operator|=
name|x
operator|*
literal|2
operator|*
operator|(
name|rand
argument_list|()
operator|%
name|y
operator|/
literal|2
operator|)
operator|+
literal|2
operator|*
operator|(
name|rand
argument_list|()
operator|%
name|x
operator|/
literal|2
operator|)
expr_stmt|;
name|maz
index|[
name|pos
index|]
operator|=
name|IN
expr_stmt|;
comment|/* Add frontier. */
name|up
operator|=
name|CELL_UP_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|down
operator|=
name|CELL_DOWN_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|left
operator|=
name|CELL_LEFT_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|right
operator|=
name|CELL_RIGHT_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|maz
index|[
name|up
index|]
operator|=
name|maz
index|[
name|down
index|]
operator|=
name|maz
index|[
name|left
index|]
operator|=
name|maz
index|[
name|right
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|up
argument_list|)
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|down
argument_list|)
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|left
argument_list|)
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|right
argument_list|)
expr_stmt|;
comment|/* While frontier is not empty do the following... */
while|while
condition|(
name|g_slist_length
argument_list|(
name|front_cells
argument_list|)
operator|>
literal|0
condition|)
block|{
comment|/* Remove one cell at random from frontier and place it in IN. */
name|current
operator|=
name|rand
argument_list|()
operator|%
name|g_slist_length
argument_list|(
name|front_cells
argument_list|)
expr_stmt|;
name|pos
operator|=
operator|(
name|guint
operator|)
name|g_slist_nth
argument_list|(
name|front_cells
argument_list|,
name|current
argument_list|)
operator|->
name|data
expr_stmt|;
name|front_cells
operator|=
name|g_slist_remove
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|pos
argument_list|)
expr_stmt|;
name|maz
index|[
name|pos
index|]
operator|=
name|IN
expr_stmt|;
comment|/* If the cell has any neighbors in OUT, remove them from              OUT and place them in FRONTIER. */
name|up
operator|=
name|CELL_UP_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|down
operator|=
name|CELL_DOWN_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|left
operator|=
name|CELL_LEFT_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|right
operator|=
name|CELL_RIGHT_TILEABLE
argument_list|(
name|pos
argument_list|)
expr_stmt|;
name|d
operator|=
literal|0
expr_stmt|;
switch|switch
condition|(
name|maz
index|[
name|up
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|up
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|up
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
switch|switch
condition|(
name|maz
index|[
name|down
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|down
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|down
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
name|d
operator||
literal|2
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
switch|switch
condition|(
name|maz
index|[
name|left
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|left
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|left
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
name|d
operator||
literal|4
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
switch|switch
condition|(
name|maz
index|[
name|right
index|]
condition|)
block|{
case|case
name|OUT
case|:
name|maz
index|[
name|right
index|]
operator|=
name|FRONTIER
expr_stmt|;
name|front_cells
operator|=
name|g_slist_append
argument_list|(
name|front_cells
argument_list|,
operator|(
name|gpointer
operator|)
name|right
argument_list|)
expr_stmt|;
break|break;
case|case
name|IN
case|:
name|d
operator|=
name|d
operator||
literal|8
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
comment|/* The cell is guaranteed to have at least one neighbor in 	     IN (otherwise it would not have been in FRONTIER); pick 	     one such neighbor at random and connect it to the new 	     cell (ie knock out a wall).  */
if|if
condition|(
operator|!
name|d
condition|)
block|{
name|g_warning
argument_list|(
literal|"maze: prim's tileable: Lack of neighbors.\n"
literal|"seed: %d, mw: %d, mh: %d, mult: %d, offset: %d\n"
argument_list|,
name|mvals
operator|.
name|seed
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|mvals
operator|.
name|multiple
argument_list|,
name|mvals
operator|.
name|offset
argument_list|)
expr_stmt|;
break|break;
block|}
name|c
operator|=
literal|0
expr_stmt|;
do|do
block|{
name|rnd
operator|=
operator|(
name|rnd
operator|*
name|mvals
operator|.
name|multiple
operator|+
name|mvals
operator|.
name|offset
operator|)
expr_stmt|;
name|i
operator|=
literal|3
operator|&
operator|(
name|rnd
operator|/
name|d
operator|)
expr_stmt|;
if|if
condition|(
operator|++
name|c
operator|>
literal|100
condition|)
block|{
comment|/* Break and try to salvage something */
name|i
operator|=
literal|99
expr_stmt|;
comment|/* if it looks like we're going to be */
break|break;
comment|/* here forever...                    */
block|}
block|}
do|while
condition|(
operator|!
operator|(
name|d
operator|&
operator|(
literal|1
operator|<<
name|i
operator|)
operator|)
condition|)
do|;
switch|switch
condition|(
name|i
condition|)
block|{
case|case
literal|0
case|:
name|maz
index|[
name|WALL_UP_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|maz
index|[
name|WALL_DOWN_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|maz
index|[
name|WALL_LEFT_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|maz
index|[
name|WALL_RIGHT_TILEABLE
argument_list|(
name|pos
argument_list|)
index|]
operator|=
literal|1
expr_stmt|;
break|break;
case|case
literal|99
case|:
break|break;
default|default:
name|g_warning
argument_list|(
literal|"maze: prim's tileable: Going in unknown direction.\n"
literal|"i: %d, d: %d, seed: %d, mw: %d, mh: %d, mult: %d, offset: %d\n"
argument_list|,
name|i
argument_list|,
name|d
argument_list|,
name|mvals
operator|.
name|seed
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|mvals
operator|.
name|multiple
argument_list|,
name|mvals
operator|.
name|offset
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|progress
operator|++
operator|%
name|PRIMS_PROGRESS_UPDATE
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
comment|/* while front_cells */
name|g_slist_free
argument_list|(
name|front_cells
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


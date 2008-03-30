begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimparea.h"
end_include

begin_define
DECL|macro|OVERHEAD
define|#
directive|define
name|OVERHEAD
value|25
end_define

begin_comment
DECL|macro|OVERHEAD
comment|/*  in units of pixel area  */
end_comment

begin_function
name|GimpArea
modifier|*
DECL|function|gimp_area_new (gint x1,gint y1,gint x2,gint y2)
name|gimp_area_new
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
block|{
name|GimpArea
modifier|*
name|area
init|=
name|g_slice_new
argument_list|(
name|GimpArea
argument_list|)
decl_stmt|;
name|area
operator|->
name|x1
operator|=
name|x1
expr_stmt|;
name|area
operator|->
name|y1
operator|=
name|y1
expr_stmt|;
name|area
operator|->
name|x2
operator|=
name|x2
expr_stmt|;
name|area
operator|->
name|y2
operator|=
name|y2
expr_stmt|;
return|return
name|area
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_area_free (GimpArea * area)
name|gimp_area_free
parameter_list|(
name|GimpArea
modifier|*
name|area
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|GimpArea
argument_list|,
name|area
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  *  As far as I can tell, this function takes a GimpArea and unifies it with  *  an existing list of GimpAreas, trying to avoid overdraw.  [adam]  */
end_comment

begin_function
name|GSList
modifier|*
DECL|function|gimp_area_list_process (GSList * list,GimpArea * area)
name|gimp_area_list_process
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|GimpArea
modifier|*
name|area
parameter_list|)
block|{
name|GSList
modifier|*
name|new_list
decl_stmt|;
name|GSList
modifier|*
name|l
decl_stmt|;
name|gint
name|area1
decl_stmt|,
name|area2
decl_stmt|,
name|area3
decl_stmt|;
comment|/*  start new list off  */
name|new_list
operator|=
name|g_slist_prepend
argument_list|(
name|NULL
argument_list|,
name|area
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|list
init|;
name|l
condition|;
name|l
operator|=
name|g_slist_next
argument_list|(
name|l
argument_list|)
control|)
block|{
name|GimpArea
modifier|*
name|ga2
init|=
name|l
operator|->
name|data
decl_stmt|;
name|area1
operator|=
operator|(
name|area
operator|->
name|x2
operator|-
name|area
operator|->
name|x1
operator|)
operator|*
operator|(
name|area
operator|->
name|y2
operator|-
name|area
operator|->
name|y1
operator|)
operator|+
name|OVERHEAD
expr_stmt|;
name|area2
operator|=
operator|(
name|ga2
operator|->
name|x2
operator|-
name|ga2
operator|->
name|x1
operator|)
operator|*
operator|(
name|ga2
operator|->
name|y2
operator|-
name|ga2
operator|->
name|y1
operator|)
operator|+
name|OVERHEAD
expr_stmt|;
name|area3
operator|=
operator|(
operator|(
name|MAX
argument_list|(
name|ga2
operator|->
name|x2
argument_list|,
name|area
operator|->
name|x2
argument_list|)
operator|-
name|MIN
argument_list|(
name|ga2
operator|->
name|x1
argument_list|,
name|area
operator|->
name|x1
argument_list|)
operator|)
operator|*
operator|(
name|MAX
argument_list|(
name|ga2
operator|->
name|y2
argument_list|,
name|area
operator|->
name|y2
argument_list|)
operator|-
name|MIN
argument_list|(
name|ga2
operator|->
name|y1
argument_list|,
name|area
operator|->
name|y1
argument_list|)
operator|)
operator|+
name|OVERHEAD
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|area1
operator|+
name|area2
operator|)
operator|<
name|area3
condition|)
block|{
name|new_list
operator|=
name|g_slist_prepend
argument_list|(
name|new_list
argument_list|,
name|ga2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|area
operator|->
name|x1
operator|=
name|MIN
argument_list|(
name|area
operator|->
name|x1
argument_list|,
name|ga2
operator|->
name|x1
argument_list|)
expr_stmt|;
name|area
operator|->
name|y1
operator|=
name|MIN
argument_list|(
name|area
operator|->
name|y1
argument_list|,
name|ga2
operator|->
name|y1
argument_list|)
expr_stmt|;
name|area
operator|->
name|x2
operator|=
name|MAX
argument_list|(
name|area
operator|->
name|x2
argument_list|,
name|ga2
operator|->
name|x2
argument_list|)
expr_stmt|;
name|area
operator|->
name|y2
operator|=
name|MAX
argument_list|(
name|area
operator|->
name|y2
argument_list|,
name|ga2
operator|->
name|y2
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpArea
argument_list|,
name|ga2
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|list
condition|)
name|g_slist_free
argument_list|(
name|list
argument_list|)
expr_stmt|;
return|return
name|new_list
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_area_list_free (GSList * areas)
name|gimp_area_list_free
parameter_list|(
name|GSList
modifier|*
name|areas
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|areas
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|gimp_area_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|areas
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


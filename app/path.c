begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  * Some of this code is based on the layers_dialog box code.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"tools/tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpbezierselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gui/paths-dialog.h"
end_include

begin_include
include|#
directive|include
file|"path.h"
end_include

begin_include
include|#
directive|include
file|"pathP.h"
end_include

begin_function_decl
specifier|static
name|gchar
modifier|*
name|unique_name
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gchar
modifier|*
name|cstr
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|Path
modifier|*
DECL|function|path_new (GimpImage * gimage,PathType ptype,GSList * path_details,gint closed,gint state,gint locked,gint tattoo,gchar * name)
name|path_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|PathType
name|ptype
parameter_list|,
name|GSList
modifier|*
name|path_details
parameter_list|,
name|gint
name|closed
parameter_list|,
name|gint
name|state
parameter_list|,
name|gint
name|locked
parameter_list|,
name|gint
name|tattoo
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|gchar
modifier|*
name|suniq
decl_stmt|;
name|Path
modifier|*
name|path
init|=
name|g_new0
argument_list|(
name|Path
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|suniq
operator|=
name|unique_name
argument_list|(
name|gimage
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|suniq
condition|)
name|path
operator|->
name|name
operator|=
name|suniq
expr_stmt|;
else|else
name|path
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|path
operator|->
name|path_details
operator|=
name|path_details
expr_stmt|;
name|path
operator|->
name|closed
operator|=
name|closed
expr_stmt|;
name|path
operator|->
name|state
operator|=
name|state
expr_stmt|;
name|path
operator|->
name|locked
operator|=
name|locked
expr_stmt|;
name|path
operator|->
name|pathtype
operator|=
name|ptype
expr_stmt|;
if|if
condition|(
name|tattoo
condition|)
name|path
operator|->
name|tattoo
operator|=
name|tattoo
expr_stmt|;
else|else
name|path
operator|->
name|tattoo
operator|=
name|gimp_image_get_new_tattoo
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|path
return|;
block|}
end_function

begin_function
name|Path
modifier|*
DECL|function|path_copy (GimpImage * gimage,Path * path)
name|path_copy
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Path
modifier|*
name|path
parameter_list|)
block|{
name|Path
modifier|*
name|p_copy
init|=
name|g_new0
argument_list|(
name|Path
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|unique_name
argument_list|(
name|gimage
argument_list|,
name|path
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
condition|)
name|p_copy
operator|->
name|name
operator|=
name|name
expr_stmt|;
else|else
name|p_copy
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|path
operator|->
name|name
argument_list|)
expr_stmt|;
name|p_copy
operator|->
name|closed
operator|=
name|path
operator|->
name|closed
expr_stmt|;
name|p_copy
operator|->
name|state
operator|=
name|path
operator|->
name|state
expr_stmt|;
name|p_copy
operator|->
name|pathtype
operator|=
name|path
operator|->
name|pathtype
expr_stmt|;
name|p_copy
operator|->
name|path_details
operator|=
name|pathpoints_copy
argument_list|(
name|path
operator|->
name|path_details
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
name|p_copy
operator|->
name|tattoo
operator|=
name|gimp_image_get_new_tattoo
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
else|else
name|p_copy
operator|->
name|tattoo
operator|=
name|path
operator|->
name|tattoo
expr_stmt|;
return|return
name|p_copy
return|;
block|}
end_function

begin_function
name|void
DECL|function|path_free (Path * path)
name|path_free
parameter_list|(
name|Path
modifier|*
name|path
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
operator|->
name|name
argument_list|)
expr_stmt|;
name|pathpoints_free
argument_list|(
name|path
operator|->
name|path_details
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|PathPoint
modifier|*
DECL|function|path_point_new (guint type,gdouble x,gdouble y)
name|path_point_new
parameter_list|(
name|guint
name|type
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|PathPoint
modifier|*
name|pathpoint
init|=
name|g_new0
argument_list|(
name|PathPoint
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|pathpoint
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|pathpoint
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|pathpoint
operator|->
name|y
operator|=
name|y
expr_stmt|;
return|return
name|pathpoint
return|;
block|}
end_function

begin_function
name|void
DECL|function|path_point_free (PathPoint * pathpoint)
name|path_point_free
parameter_list|(
name|PathPoint
modifier|*
name|pathpoint
parameter_list|)
block|{
name|g_free
argument_list|(
name|pathpoint
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|path_stroke (GimpImage * gimage,PathList * pl,Path * bzp)
name|path_stroke
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|PathList
modifier|*
name|pl
parameter_list|,
name|Path
modifier|*
name|bzp
parameter_list|)
block|{
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|gdisplays_check_valid
argument_list|(
name|pl
operator|->
name|gdisp
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|bezier_sel
operator|=
name|path_to_beziersel
argument_list|(
name|bzp
argument_list|)
expr_stmt|;
name|bezier_stroke
argument_list|(
name|bezier_sel
argument_list|,
name|gdisp
argument_list|,
name|SUBDIVIDE
argument_list|,
operator|!
name|bzp
operator|->
name|closed
argument_list|)
expr_stmt|;
name|bezier_select_free
argument_list|(
name|bezier_sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|path_distance (Path * bzp,gdouble dist,gint * x,gint * y,gdouble * grad)
name|path_distance
parameter_list|(
name|Path
modifier|*
name|bzp
parameter_list|,
name|gdouble
name|dist
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gdouble
modifier|*
name|grad
parameter_list|)
block|{
name|gint
name|ret
decl_stmt|;
name|GimpBezierSelectTool
modifier|*
name|bezier_sel
decl_stmt|;
name|bezier_sel
operator|=
name|path_to_beziersel
argument_list|(
name|bzp
argument_list|)
expr_stmt|;
name|ret
operator|=
name|bezier_distance_along
argument_list|(
name|bezier_sel
argument_list|,
operator|!
name|bzp
operator|->
name|closed
argument_list|,
name|dist
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|grad
argument_list|)
expr_stmt|;
name|bezier_select_free
argument_list|(
name|bezier_sel
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
name|GimpTattoo
DECL|function|path_get_tattoo (Path * p)
name|path_get_tattoo
parameter_list|(
name|Path
modifier|*
name|p
parameter_list|)
block|{
if|if
condition|(
operator|!
name|p
condition|)
block|{
name|g_warning
argument_list|(
literal|"path_get_tattoo: invalid path"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
return|return
name|p
operator|->
name|tattoo
return|;
block|}
end_function

begin_function
name|Path
modifier|*
DECL|function|path_get_path_by_tattoo (GimpImage * gimage,GimpTattoo tattoo)
name|path_get_path_by_tattoo
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
block|{
name|GSList
modifier|*
name|tlist
decl_stmt|;
name|PathList
modifier|*
name|plp
decl_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|||
operator|!
name|tattoo
condition|)
return|return
name|NULL
return|;
comment|/* Go around the list and check all tattoos. */
comment|/* Get path structure  */
name|plp
operator|=
operator|(
name|PathList
operator|*
operator|)
name|gimp_image_get_paths
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|plp
condition|)
return|return
operator|(
name|NULL
operator|)
return|;
for|for
control|(
name|tlist
operator|=
name|plp
operator|->
name|bz_paths
init|;
name|tlist
condition|;
name|tlist
operator|=
name|g_slist_next
argument_list|(
name|tlist
argument_list|)
control|)
block|{
name|Path
modifier|*
name|p
init|=
operator|(
name|Path
operator|*
operator|)
operator|(
name|tlist
operator|->
name|data
operator|)
decl_stmt|;
if|if
condition|(
name|p
operator|->
name|tattoo
operator|==
name|tattoo
condition|)
return|return
operator|(
name|p
operator|)
return|;
block|}
return|return
operator|(
name|NULL
operator|)
return|;
block|}
end_function

begin_function
name|PathList
modifier|*
DECL|function|path_list_new (GimpImage * gimage,gint last_selected_row,GSList * bz_paths)
name|path_list_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|last_selected_row
parameter_list|,
name|GSList
modifier|*
name|bz_paths
parameter_list|)
block|{
name|PathList
modifier|*
name|pip
init|=
name|g_new0
argument_list|(
name|PathList
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|pip
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|pip
operator|->
name|last_selected_row
operator|=
name|last_selected_row
expr_stmt|;
comment|/* add connector to image delete/destroy */
name|pip
operator|->
name|sig_id
operator|=
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|paths_dialog_destroy_cb
argument_list|)
argument_list|,
name|pip
argument_list|)
expr_stmt|;
name|pip
operator|->
name|bz_paths
operator|=
name|bz_paths
expr_stmt|;
return|return
operator|(
name|PathList
operator|*
operator|)
name|pip
return|;
block|}
end_function

begin_function
name|void
DECL|function|path_list_free (PathList * iml)
name|path_list_free
parameter_list|(
name|PathList
modifier|*
name|iml
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|iml
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|iml
operator|->
name|bz_paths
condition|)
block|{
name|g_slist_foreach
argument_list|(
name|iml
operator|->
name|bz_paths
argument_list|,
operator|(
name|GFunc
operator|)
name|path_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|iml
operator|->
name|bz_paths
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|iml
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Always return a copy that must be freed later */
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|strip_off_cnumber (gchar * str)
name|strip_off_cnumber
parameter_list|(
name|gchar
modifier|*
name|str
parameter_list|)
block|{
name|gchar
modifier|*
name|hashptr
decl_stmt|;
name|gint
name|num
decl_stmt|;
name|gchar
modifier|*
name|copy
decl_stmt|;
if|if
condition|(
operator|!
name|str
condition|)
return|return
name|str
return|;
name|copy
operator|=
name|g_strdup
argument_list|(
name|str
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|hashptr
operator|=
name|strrchr
argument_list|(
name|copy
argument_list|,
literal|'#'
argument_list|)
operator|)
operator|&&
comment|/* have a hash */
name|strlen
argument_list|(
name|hashptr
argument_list|)
operator|>
literal|0
operator|&&
comment|/* followed by something */
operator|(
name|num
operator|=
name|atoi
argument_list|(
name|hashptr
operator|+
literal|1
argument_list|)
operator|)
operator|>
literal|0
operator|&&
comment|/* which is a number */
operator|(
operator|(
name|int
operator|)
name|log10
argument_list|(
name|num
argument_list|)
operator|+
literal|1
operator|)
operator|==
name|strlen
argument_list|(
name|hashptr
operator|+
literal|1
argument_list|)
condition|)
comment|/* which is at the end */
block|{
name|gchar
modifier|*
name|tstr
decl_stmt|;
comment|/* Has a #<number> */
operator|*
name|hashptr
operator|=
literal|'\0'
expr_stmt|;
name|tstr
operator|=
name|g_strdup
argument_list|(
name|copy
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|copy
argument_list|)
expr_stmt|;
name|copy
operator|=
name|tstr
expr_stmt|;
block|}
return|return
name|copy
return|;
block|}
end_function

begin_comment
comment|/* Return NULL if already unique else a unique string */
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|unique_name (GimpImage * gimage,gchar * cstr)
name|unique_name
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gchar
modifier|*
name|cstr
parameter_list|)
block|{
name|GSList
modifier|*
name|tlist
decl_stmt|;
name|PathList
modifier|*
name|plp
decl_stmt|;
name|gboolean
name|unique
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|copy_cstr
decl_stmt|;
name|gchar
modifier|*
name|copy_test
decl_stmt|;
name|gchar
modifier|*
name|stripped_copy
decl_stmt|;
name|gint
name|counter
init|=
literal|1
decl_stmt|;
comment|/* Get bzpath structure  */
if|if
condition|(
operator|!
name|gimage
operator|||
operator|!
operator|(
name|plp
operator|=
operator|(
name|PathList
operator|*
operator|)
name|gimp_image_get_paths
argument_list|(
name|gimage
argument_list|)
operator|)
condition|)
return|return
name|NULL
return|;
name|tlist
operator|=
name|plp
operator|->
name|bz_paths
expr_stmt|;
while|while
condition|(
name|tlist
condition|)
block|{
name|gchar
modifier|*
name|test_str
decl_stmt|;
name|test_str
operator|=
operator|(
operator|(
name|Path
operator|*
operator|)
operator|(
name|tlist
operator|->
name|data
operator|)
operator|)
operator|->
name|name
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|cstr
argument_list|,
name|test_str
argument_list|)
operator|==
literal|0
condition|)
block|{
name|unique
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
name|tlist
operator|=
name|g_slist_next
argument_list|(
name|tlist
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|unique
condition|)
return|return
name|NULL
return|;
comment|/* OK Clashes with something */
comment|/* restart scan to find unique name */
name|stripped_copy
operator|=
name|strip_off_cnumber
argument_list|(
name|cstr
argument_list|)
expr_stmt|;
name|copy_cstr
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s#%d"
argument_list|,
name|stripped_copy
argument_list|,
name|counter
operator|++
argument_list|)
expr_stmt|;
name|tlist
operator|=
name|plp
operator|->
name|bz_paths
expr_stmt|;
while|while
condition|(
name|tlist
condition|)
block|{
name|copy_test
operator|=
operator|(
operator|(
name|Path
operator|*
operator|)
operator|(
name|tlist
operator|->
name|data
operator|)
operator|)
operator|->
name|name
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|copy_cstr
argument_list|,
name|copy_test
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|copy_cstr
argument_list|)
expr_stmt|;
name|copy_cstr
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s#%d"
argument_list|,
name|stripped_copy
argument_list|,
name|counter
operator|++
argument_list|)
expr_stmt|;
name|tlist
operator|=
name|plp
operator|->
name|bz_paths
expr_stmt|;
continue|continue;
block|}
name|tlist
operator|=
name|g_slist_next
argument_list|(
name|tlist
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|stripped_copy
argument_list|)
expr_stmt|;
return|return
name|copy_cstr
return|;
block|}
end_function

end_unit


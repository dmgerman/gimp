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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-run.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-commands.h"
end_include

begin_function
name|void
DECL|function|plug_in_run_cmd_callback (GtkAction * action,PlugInProcDef * proc_def,gpointer data)
name|plug_in_run_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|ProcRecord
modifier|*
name|proc_rec
decl_stmt|;
name|Argument
modifier|*
name|args
decl_stmt|;
name|gint
name|gdisp_ID
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|argc
decl_stmt|;
name|GimpImageType
name|drawable_type
init|=
name|GIMP_RGB_IMAGE
decl_stmt|;
name|gimp
operator|=
name|action_data_get_gimp
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp
condition|)
return|return;
name|proc_rec
operator|=
operator|&
name|proc_def
operator|->
name|db_info
expr_stmt|;
comment|/* construct the procedures arguments */
name|args
operator|=
name|g_new0
argument_list|(
name|Argument
argument_list|,
name|proc_rec
operator|->
name|num_args
argument_list|)
expr_stmt|;
comment|/* initialize the argument types */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|proc_rec
operator|->
name|num_args
condition|;
name|i
operator|++
control|)
name|args
index|[
name|i
index|]
operator|.
name|arg_type
operator|=
name|proc_rec
operator|->
name|args
index|[
name|i
index|]
operator|.
name|arg_type
expr_stmt|;
comment|/* initialize the first argument  */
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|GIMP_RUN_INTERACTIVE
expr_stmt|;
name|argc
operator|=
literal|1
expr_stmt|;
switch|switch
condition|(
name|proc_rec
operator|->
name|proc_type
condition|)
block|{
case|case
name|GIMP_EXTENSION
case|:
break|break;
case|case
name|GIMP_PLUGIN
case|:
case|case
name|GIMP_TEMPORARY
case|:
if|if
condition|(
name|proc_rec
operator|->
name|num_args
operator|>=
literal|2
operator|&&
name|proc_rec
operator|->
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|==
name|GIMP_PDB_IMAGE
condition|)
block|{
name|GimpDisplay
modifier|*
name|gdisplay
init|=
name|action_data_get_display
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|gdisplay
condition|)
block|{
name|gdisp_ID
operator|=
name|gimp_display_get_ID
argument_list|(
name|gdisplay
argument_list|)
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_image_get_ID
argument_list|(
name|gdisplay
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|argc
operator|++
expr_stmt|;
if|if
condition|(
name|proc_rec
operator|->
name|num_args
operator|>=
literal|2
operator|&&
name|proc_rec
operator|->
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|==
name|GIMP_PDB_DRAWABLE
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisplay
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|drawable_type
operator|=
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|argc
operator|++
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"Uh-oh, no active drawable for the plug-in!"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
block|}
block|}
break|break;
default|default:
name|g_error
argument_list|(
literal|"Unknown procedure type."
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* run the plug-in procedure */
name|plug_in_run
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|proc_rec
argument_list|,
name|args
argument_list|,
name|argc
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|gdisp_ID
argument_list|)
expr_stmt|;
comment|/* remember only "standard" plug-ins */
if|if
condition|(
name|proc_rec
operator|->
name|proc_type
operator|==
name|GIMP_PLUGIN
operator|&&
name|proc_rec
operator|->
name|num_args
operator|>=
literal|2
operator|&&
name|proc_rec
operator|->
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|==
name|GIMP_PDB_IMAGE
operator|&&
name|proc_rec
operator|->
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|==
name|GIMP_PDB_DRAWABLE
condition|)
block|{
name|gimp
operator|->
name|last_plug_in
operator|=
name|proc_rec
expr_stmt|;
if|#
directive|if
literal|0
block|FIXME       plug_in_menus_update (GIMP_ITEM_FACTORY (item_factory), drawable_type);
endif|#
directive|endif
block|}
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_repeat_cmd_callback (GtkAction * action,gint value,gpointer data)
name|plug_in_repeat_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|interactive
decl_stmt|;
name|gdisp
operator|=
name|action_data_get_display
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdisp
condition|)
return|return;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|interactive
operator|=
name|value
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|plug_in_repeat
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|gimp_display_get_ID
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|interactive
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


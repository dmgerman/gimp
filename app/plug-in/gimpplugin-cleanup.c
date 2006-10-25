begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugin-cleanup.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"glib-object.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundostack.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-cleanup.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-locale-domain.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginprocedure.h"
end_include

begin_typedef
DECL|typedef|GimpPlugInCleanupImage
typedef|typedef
name|struct
name|_GimpPlugInCleanupImage
name|GimpPlugInCleanupImage
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInCleanupImage
struct|struct
name|_GimpPlugInCleanupImage
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|undo_group_count
name|gint
name|undo_group_count
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpPlugInCleanupImage
modifier|*
name|gimp_plug_in_cleanup_get_image
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_plug_in_cleanup_undo_group_start (GimpPlugIn * plug_in,GimpImage * image)
name|gimp_plug_in_cleanup_undo_group_start
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|GimpPlugInCleanupImage
modifier|*
name|cleanup
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|cleanup
operator|=
name|gimp_plug_in_cleanup_get_image
argument_list|(
name|proc_frame
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"\n%s: procedure %s starts undo group on\n"
literal|"image with group count %d\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|proc_frame
operator|->
name|procedure
argument_list|)
operator|->
name|name
argument_list|,
name|image
operator|->
name|group_count
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cleanup
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: creating new cleanup entry => SUCCESS\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|cleanup
operator|=
name|g_new0
argument_list|(
name|GimpPlugInCleanupImage
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cleanup
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|cleanup
operator|->
name|undo_group_count
operator|=
name|image
operator|->
name|group_count
expr_stmt|;
name|proc_frame
operator|->
name|cleanups
operator|=
name|g_list_prepend
argument_list|(
name|proc_frame
operator|->
name|cleanups
argument_list|,
name|cleanup
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: using existing cleanup entry => SUCCESS\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_plug_in_cleanup_undo_group_end (GimpPlugIn * plug_in,GimpImage * image)
name|gimp_plug_in_cleanup_undo_group_end
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
decl_stmt|;
name|GimpPlugInCleanupImage
modifier|*
name|cleanup
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|proc_frame
operator|=
name|gimp_plug_in_get_proc_frame
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
name|cleanup
operator|=
name|gimp_plug_in_cleanup_get_image
argument_list|(
name|proc_frame
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"\n%s: procedure %s ends undo group on\n"
literal|"image with group count %d\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|proc_frame
operator|->
name|procedure
argument_list|)
operator|->
name|name
argument_list|,
name|image
operator|->
name|group_count
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cleanup
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: no cleanup entry found => FAILURE\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|cleanup
operator|->
name|undo_group_count
operator|==
name|image
operator|->
name|group_count
operator|-
literal|1
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: group count balanced, deleting cleanup entry => SUCCESS\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|cleanups
operator|=
name|g_list_remove
argument_list|(
name|proc_frame
operator|->
name|cleanups
argument_list|,
name|cleanup
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cleanup
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: undo groups still open, keeping cleanup entry => SUCCESS\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_cleanup (GimpPlugIn * plug_in,GimpPlugInProcFrame * proc_frame)
name|gimp_plug_in_cleanup
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN
argument_list|(
name|plug_in
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|proc_frame
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|proc_frame
operator|->
name|cleanups
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInCleanupImage
modifier|*
name|cleanup
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|cleanup
operator|->
name|image
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_container_have
argument_list|(
name|plug_in
operator|->
name|manager
operator|->
name|gimp
operator|->
name|images
argument_list|,
operator|(
name|GimpObject
operator|*
operator|)
name|image
argument_list|)
condition|)
continue|continue;
if|if
condition|(
name|image
operator|->
name|pushing_undo_group
operator|==
name|GIMP_UNDO_GROUP_NONE
condition|)
continue|continue;
name|g_printerr
argument_list|(
literal|"\n%s: checking image with group count %d\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|image
operator|->
name|group_count
argument_list|)
expr_stmt|;
if|if
condition|(
name|cleanup
operator|->
name|undo_group_count
operator|!=
name|image
operator|->
name|group_count
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|domain
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|domain
operator|=
name|gimp_plug_in_manager_get_locale_domain
argument_list|(
name|plug_in
operator|->
name|manager
argument_list|,
name|plug_in
operator|->
name|prog
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_plug_in_procedure_get_label
argument_list|(
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|proc_frame
operator|->
name|procedure
argument_list|)
argument_list|,
name|domain
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"Plug-In '%s' left image undo in inconsistent state, "
literal|"closing open undo groups."
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
while|while
condition|(
name|image
operator|->
name|pushing_undo_group
operator|!=
name|GIMP_UNDO_GROUP_NONE
operator|&&
name|cleanup
operator|->
name|undo_group_count
operator|<
name|image
operator|->
name|group_count
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
condition|)
break|break;
block|}
block|}
name|g_free
argument_list|(
name|cleanup
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|proc_frame
operator|->
name|cleanups
argument_list|)
expr_stmt|;
name|proc_frame
operator|->
name|cleanups
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpPlugInCleanupImage
modifier|*
DECL|function|gimp_plug_in_cleanup_get_image (GimpPlugInProcFrame * proc_frame,GimpImage * image)
name|gimp_plug_in_cleanup_get_image
parameter_list|(
name|GimpPlugInProcFrame
modifier|*
name|proc_frame
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|proc_frame
operator|->
name|cleanups
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInCleanupImage
modifier|*
name|cleanup
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|cleanup
operator|->
name|image
operator|==
name|image
condition|)
return|return
name|cleanup
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit


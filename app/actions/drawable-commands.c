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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-desaturate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-equalize.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-invert.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemtreeview.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"drawable-commands.h"
end_include

begin_include
include|#
directive|include
file|"offset-dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|return_if_no_image (gimage,data)
define|#
directive|define
name|return_if_no_image
parameter_list|(
name|gimage
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gimage = ((GimpDisplay *) data)->gimage; \   else if (GIMP_IS_GIMP (data)) \     gimage = gimp_context_get_image (gimp_get_user_context (GIMP (data))); \   else if (GIMP_IS_ITEM_TREE_VIEW (data)) \     gimage = ((GimpItemTreeView *) data)->gimage; \   else \     gimage = NULL; \   \   if (! gimage) \     return
end_define

begin_define
DECL|macro|return_if_no_drawable (gimage,drawable,data)
define|#
directive|define
name|return_if_no_drawable
parameter_list|(
name|gimage
parameter_list|,
name|drawable
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage,data); \   drawable = gimp_image_active_drawable (gimage); \   if (! drawable) \     return
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|drawable_desaturate_cmd_callback (GtkWidget * widget,gpointer data)
name|drawable_desaturate_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|active_drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|active_drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Desaturate operates only on RGB color drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_desaturate
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_invert_cmd_callback (GtkWidget * widget,gpointer data)
name|drawable_invert_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|active_drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|active_drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Invert does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_invert
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_equalize_cmd_callback (GtkWidget * widget,gpointer data)
name|drawable_equalize_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|active_drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|active_drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Equalize does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_equalize
argument_list|(
name|active_drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|drawable_offset_cmd_callback (GtkWidget * widget,gpointer data)
name|drawable_offset_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|active_drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|offset_dialog_create
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


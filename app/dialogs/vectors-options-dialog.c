begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"item-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"vectors-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|VectorsOptionsDialog
typedef|typedef
name|struct
name|_VectorsOptionsDialog
name|VectorsOptionsDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_VectorsOptionsDialog
struct|struct
name|_VectorsOptionsDialog
block|{
DECL|member|callback
name|GimpVectorsOptionsCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|vectors_options_dialog_free
parameter_list|(
name|VectorsOptionsDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|vectors_options_dialog_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|item_name
parameter_list|,
name|gboolean
name|item_visible
parameter_list|,
name|gboolean
name|item_linked
parameter_list|,
name|GimpColorTag
name|item_color_tag
parameter_list|,
name|gboolean
name|item_lock_content
parameter_list|,
name|gboolean
name|item_lock_position
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|vectors_options_dialog_new (GimpImage * image,GimpVectors * vectors,GimpContext * context,GtkWidget * parent,const gchar * title,const gchar * role,const gchar * icon_name,const gchar * desc,const gchar * help_id,const gchar * vectors_name,gboolean vectors_visible,gboolean vectors_linked,GimpColorTag vectors_color_tag,gboolean vectors_lock_content,gboolean vectors_lock_position,GimpVectorsOptionsCallback callback,gpointer user_data)
name|vectors_options_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|vectors_name
parameter_list|,
name|gboolean
name|vectors_visible
parameter_list|,
name|gboolean
name|vectors_linked
parameter_list|,
name|GimpColorTag
name|vectors_color_tag
parameter_list|,
name|gboolean
name|vectors_lock_content
parameter_list|,
name|gboolean
name|vectors_lock_position
parameter_list|,
name|GimpVectorsOptionsCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|VectorsOptionsDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vectors
operator|==
name|NULL
operator|||
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|desc
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_slice_new0
argument_list|(
name|VectorsOptionsDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|private
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
name|dialog
operator|=
name|item_options_dialog_new
argument_list|(
name|image
argument_list|,
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|context
argument_list|,
name|parent
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|icon_name
argument_list|,
name|desc
argument_list|,
name|help_id
argument_list|,
name|_
argument_list|(
literal|"Path _name:"
argument_list|)
argument_list|,
name|GIMP_ICON_TOOL_PATH
argument_list|,
name|_
argument_list|(
literal|"Lock path _strokes"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Lock path _position"
argument_list|)
argument_list|,
name|vectors_name
argument_list|,
name|vectors_visible
argument_list|,
name|vectors_linked
argument_list|,
name|vectors_color_tag
argument_list|,
name|vectors_lock_content
argument_list|,
name|vectors_lock_position
argument_list|,
name|vectors_options_dialog_callback
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|vectors_options_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|vectors_options_dialog_free (VectorsOptionsDialog * private)
name|vectors_options_dialog_free
parameter_list|(
name|VectorsOptionsDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|VectorsOptionsDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|vectors_options_dialog_callback (GtkWidget * dialog,GimpImage * image,GimpItem * item,GimpContext * context,const gchar * item_name,gboolean item_visible,gboolean item_linked,GimpColorTag item_color_tag,gboolean item_lock_content,gboolean item_lock_position,gpointer user_data)
name|vectors_options_dialog_callback
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|item_name
parameter_list|,
name|gboolean
name|item_visible
parameter_list|,
name|gboolean
name|item_linked
parameter_list|,
name|GimpColorTag
name|item_color_tag
parameter_list|,
name|gboolean
name|item_lock_content
parameter_list|,
name|gboolean
name|item_lock_position
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|VectorsOptionsDialog
modifier|*
name|private
init|=
name|user_data
decl_stmt|;
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|image
argument_list|,
name|GIMP_VECTORS
argument_list|(
name|item
argument_list|)
argument_list|,
name|context
argument_list|,
name|item_name
argument_list|,
name|item_visible
argument_list|,
name|item_linked
argument_list|,
name|item_color_tag
argument_list|,
name|item_lock_content
argument_list|,
name|item_lock_position
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


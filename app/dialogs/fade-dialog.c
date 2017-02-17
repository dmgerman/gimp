begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"core/gimp-edit.h"
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
file|"core/gimpdrawableundo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpundostack.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"fade-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28c90a240108
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|applied
name|gboolean
name|applied
decl_stmt|;
DECL|member|orig_paint_mode
name|GimpLayerMode
name|orig_paint_mode
decl_stmt|;
DECL|member|orig_opacity
name|gdouble
name|orig_opacity
decl_stmt|;
DECL|typedef|FadeDialog
block|}
name|FadeDialog
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|fade_dialog_free
parameter_list|(
name|FadeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fade_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|FadeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fade_dialog_context_changed
parameter_list|(
name|FadeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|fade_dialog_new (GimpImage * image,GtkWidget * parent)
name|fade_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|FadeDialog
modifier|*
name|private
decl_stmt|;
name|GimpDrawableUndo
modifier|*
name|undo
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|gint
name|table_row
init|=
literal|0
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
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|undo
operator|=
name|GIMP_DRAWABLE_UNDO
argument_list|(
name|gimp_image_undo_get_fadeable
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|undo
operator|&&
name|undo
operator|->
name|applied_buffer
operator|)
condition|)
return|return
name|NULL
return|;
name|item
operator|=
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
expr_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_slice_new0
argument_list|(
name|FadeDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|private
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|private
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
literal|"fade-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|->
name|applied
operator|=
name|FALSE
expr_stmt|;
name|private
operator|->
name|orig_paint_mode
operator|=
name|undo
operator|->
name|paint_mode
expr_stmt|;
name|private
operator|->
name|orig_opacity
operator|=
name|undo
operator|->
name|opacity
expr_stmt|;
name|g_object_set
argument_list|(
name|private
operator|->
name|context
argument_list|,
literal|"paint-mode"
argument_list|,
name|undo
operator|->
name|paint_mode
argument_list|,
literal|"opacity"
argument_list|,
name|undo
operator|->
name|opacity
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Fade %s"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|private
operator|->
name|context
argument_list|,
name|title
argument_list|,
literal|"gimp-edit-fade"
argument_list|,
literal|"edit-undo"
argument_list|,
name|title
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_EDIT_FADE
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Fade"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_window_set_modal
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
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
name|fade_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|fade_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  the paint mode menu  */
name|menu
operator|=
name|gimp_prop_layer_mode_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|context
argument_list|)
argument_list|,
literal|"paint-mode"
argument_list|,
name|GIMP_LAYER_MODE_CONTEXT_FADE
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"_Mode:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|menu
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  the opacity scale  */
name|gimp_prop_opacity_entry_new
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|context
argument_list|)
argument_list|,
literal|"opacity"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"_Opacity:"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|private
operator|->
name|context
argument_list|,
literal|"paint-mode-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|fade_dialog_context_changed
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|private
operator|->
name|context
argument_list|,
literal|"opacity-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|fade_dialog_context_changed
argument_list|)
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
DECL|function|fade_dialog_free (FadeDialog * private)
name|fade_dialog_free
parameter_list|(
name|FadeDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|FadeDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|fade_dialog_response (GtkWidget * dialog,gint response_id,FadeDialog * private)
name|fade_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|FadeDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|private
operator|->
name|context
argument_list|,
name|fade_dialog_context_changed
argument_list|,
name|private
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|!=
name|GTK_RESPONSE_OK
operator|&&
name|private
operator|->
name|applied
condition|)
block|{
name|g_object_set
argument_list|(
name|private
operator|->
name|context
argument_list|,
literal|"paint-mode"
argument_list|,
name|private
operator|->
name|orig_paint_mode
argument_list|,
literal|"opacity"
argument_list|,
name|private
operator|->
name|orig_opacity
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fade_dialog_context_changed
argument_list|(
name|private
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|private
operator|->
name|context
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|fade_dialog_context_changed (FadeDialog * private)
name|fade_dialog_context_changed
parameter_list|(
name|FadeDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
name|gimp_edit_fade
argument_list|(
name|private
operator|->
name|image
argument_list|,
name|private
operator|->
name|context
argument_list|)
condition|)
block|{
name|private
operator|->
name|applied
operator|=
name|TRUE
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|private
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


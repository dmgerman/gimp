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
file|<stdio.h>
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|#include "tools/tools-types.h"
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"tools/tools-types.h"
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
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-projection.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpselectionoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectioneditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_class_init
parameter_list|(
name|GimpSelectionEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_init
parameter_list|(
name|GimpSelectionEditor
modifier|*
name|selection_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_abox_resized
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_invert_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_all_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_none_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_selection_preview_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImageEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_selection_editor_get_type (void)
name|gimp_selection_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|editor_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|editor_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|editor_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpSelectionEditorClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_selection_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpSelectionEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_selection_editor_init
block|,       }
decl_stmt|;
name|editor_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_EDITOR
argument_list|,
literal|"GimpSelectionEditor"
argument_list|,
operator|&
name|editor_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|editor_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_class_init (GimpSelectionEditorClass * klass)
name|gimp_selection_editor_class_init
parameter_list|(
name|GimpSelectionEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpImageEditorClass
modifier|*
name|image_editor_class
decl_stmt|;
name|image_editor_class
operator|=
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|image_editor_class
operator|->
name|set_image
operator|=
name|gimp_selection_editor_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_init (GimpSelectionEditor * selection_editor)
name|gimp_selection_editor_init
parameter_list|(
name|GimpSelectionEditor
modifier|*
name|selection_editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|abox
decl_stmt|;
comment|/* FIXME: take value from GimpGuiConfig */
name|GimpPreviewSize
name|nav_preview_size
init|=
name|GIMP_PREVIEW_SIZE_HUGE
decl_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|selection_editor
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|abox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|abox
argument_list|,
name|nav_preview_size
argument_list|,
name|nav_preview_size
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|abox
argument_list|,
literal|"size_allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_editor_abox_resized
argument_list|)
argument_list|,
name|selection_editor
argument_list|)
expr_stmt|;
name|selection_editor
operator|->
name|preview
operator|=
name|gimp_preview_new_by_types
argument_list|(
name|GIMP_TYPE_PREVIEW
argument_list|,
name|GIMP_TYPE_DRAWABLE
argument_list|,
name|nav_preview_size
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
name|selection_editor
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|selection_editor
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|selection_editor
operator|->
name|preview
argument_list|,
literal|"button_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_preview_button_press
argument_list|)
argument_list|,
name|selection_editor
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|selection_editor
operator|->
name|preview
argument_list|,
name|gimp_selection_editor_drop_color
argument_list|,
name|selection_editor
argument_list|)
expr_stmt|;
name|selection_editor
operator|->
name|all_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|selection_editor
argument_list|)
argument_list|,
name|GIMP_STOCK_SELECTION_ALL
argument_list|,
name|_
argument_list|(
literal|"Select All"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_editor_all_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|selection_editor
argument_list|)
expr_stmt|;
name|selection_editor
operator|->
name|none_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|selection_editor
argument_list|)
argument_list|,
name|GIMP_STOCK_SELECTION_NONE
argument_list|,
name|_
argument_list|(
literal|"Select None"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_editor_none_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|selection_editor
argument_list|)
expr_stmt|;
name|selection_editor
operator|->
name|invert_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|selection_editor
argument_list|)
argument_list|,
name|GIMP_STOCK_INVERT
argument_list|,
name|_
argument_list|(
literal|"Invert Selection"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_editor_invert_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|selection_editor
argument_list|)
expr_stmt|;
name|selection_editor
operator|->
name|save_button
operator|=
name|gimp_editor_add_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|selection_editor
argument_list|)
argument_list|,
name|GIMP_STOCK_SELECTION_TO_CHANNEL
argument_list|,
name|_
argument_list|(
literal|"Save Selection to Channel"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_editor_save_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|selection_editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|selection_editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_set_image (GimpImageEditor * image_editor,GimpImage * gimage)
name|gimp_selection_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|image_editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpSelectionEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_SELECTION_EDITOR
argument_list|(
name|image_editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|gimage
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|gimage
argument_list|,
name|gimp_selection_editor_mask_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|image_editor
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"mask_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_editor_mask_changed
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_preview_set_viewable
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|editor
operator|->
name|preview
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_preview_set_viewable
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|editor
operator|->
name|preview
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_define
DECL|macro|PREVIEW_WIDTH
define|#
directive|define
name|PREVIEW_WIDTH
value|256
end_define

begin_define
DECL|macro|PREVIEW_HEIGHT
define|#
directive|define
name|PREVIEW_HEIGHT
value|256
end_define

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_selection_editor_new (GimpImage * gimage)
name|gimp_selection_editor_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpSelectionEditor
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|gimage
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SELECTION_EDITOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
name|gimp_image_editor_set_image
argument_list|(
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_abox_resized (GtkWidget * widget,GtkAllocation * allocation,GimpSelectionEditor * editor)
name|gimp_selection_editor_abox_resized
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|image_editor
decl_stmt|;
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|image_editor
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|preview
operator|=
name|GIMP_PREVIEW
argument_list|(
name|editor
operator|->
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
operator|->
name|viewable
condition|)
return|return;
if|if
condition|(
name|preview
operator|->
name|renderer
operator|->
name|width
operator|>
name|allocation
operator|->
name|width
operator|||
name|preview
operator|->
name|renderer
operator|->
name|height
operator|>
name|allocation
operator|->
name|height
operator|||
operator|(
name|preview
operator|->
name|renderer
operator|->
name|width
operator|!=
name|allocation
operator|->
name|width
operator|&&
name|preview
operator|->
name|renderer
operator|->
name|height
operator|!=
name|allocation
operator|->
name|height
operator|)
condition|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gboolean
name|dummy
decl_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|preview
operator|->
name|viewable
argument_list|,
name|image_editor
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|image_editor
operator|->
name|gimage
operator|->
name|height
argument_list|,
name|MIN
argument_list|(
name|allocation
operator|->
name|width
argument_list|,
name|GIMP_PREVIEW_MAX_SIZE
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|allocation
operator|->
name|height
argument_list|,
name|GIMP_PREVIEW_MAX_SIZE
argument_list|)
argument_list|,
name|preview
operator|->
name|renderer
operator|->
name|dot_for_dot
argument_list|,
name|image_editor
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|image_editor
operator|->
name|gimage
operator|->
name|yresolution
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|dummy
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|>
name|allocation
operator|->
name|width
condition|)
block|{
name|height
operator|=
name|height
operator|*
name|allocation
operator|->
name|width
operator|/
name|width
expr_stmt|;
name|width
operator|=
name|width
operator|*
name|allocation
operator|->
name|width
operator|/
name|width
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|height
operator|>
name|allocation
operator|->
name|height
condition|)
block|{
name|width
operator|=
name|width
operator|*
name|allocation
operator|->
name|height
operator|/
name|height
expr_stmt|;
name|height
operator|=
name|height
operator|*
name|allocation
operator|->
name|height
operator|/
name|height
expr_stmt|;
block|}
name|gimp_preview_set_size_full
argument_list|(
name|preview
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|preview
operator|->
name|renderer
operator|->
name|border_width
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_invert_clicked (GtkWidget * widget,GimpImageEditor * editor)
name|gimp_selection_editor_invert_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
name|gimp_image_mask_invert
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_all_clicked (GtkWidget * widget,GimpImageEditor * editor)
name|gimp_selection_editor_all_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
name|gimp_image_mask_all
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_none_clicked (GtkWidget * widget,GimpImageEditor * editor)
name|gimp_selection_editor_none_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
name|gimp_image_mask_clear
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_save_clicked (GtkWidget * widget,GimpImageEditor * editor)
name|gimp_selection_editor_save_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
name|gimp_image_mask_save
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_selection_preview_button_press (GtkWidget * widget,GdkEventButton * bevent,GimpSelectionEditor * editor)
name|gimp_selection_preview_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|image_editor
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|SelectOps
name|operation
init|=
name|SELECTION_REPLACE
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|guchar
modifier|*
name|col
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|image_editor
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image_editor
operator|->
name|gimage
condition|)
return|return
name|TRUE
return|;
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|image_editor
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|tool_info_list
argument_list|,
literal|"gimp-by-color-select-tool"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return
name|TRUE
return|;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|image_editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|operation
operator|=
name|SELECTION_INTERSECT
expr_stmt|;
block|}
else|else
block|{
name|operation
operator|=
name|SELECTION_ADD
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|operation
operator|=
name|SELECTION_SUBTRACT
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|sample_merged
condition|)
block|{
name|x
operator|=
operator|(
name|image_editor
operator|->
name|gimage
operator|->
name|width
operator|*
name|bevent
operator|->
name|x
operator|/
name|editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|width
operator|)
expr_stmt|;
name|y
operator|=
operator|(
name|image_editor
operator|->
name|gimage
operator|->
name|height
operator|*
name|bevent
operator|->
name|y
operator|/
name|editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|height
operator|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|y
operator|<
literal|0
operator|||
name|x
operator|>=
name|image_editor
operator|->
name|gimage
operator|->
name|width
operator|||
name|y
operator|>=
name|image_editor
operator|->
name|gimage
operator|->
name|height
condition|)
return|return
name|TRUE
return|;
name|col
operator|=
name|gimp_image_projection_get_color_at
argument_list|(
name|image_editor
operator|->
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|offx
argument_list|,
operator|&
name|offy
argument_list|)
expr_stmt|;
name|x
operator|=
operator|(
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|*
name|bevent
operator|->
name|x
operator|/
name|editor
operator|->
name|preview
operator|->
name|requisition
operator|.
name|width
operator|-
name|offx
operator|)
expr_stmt|;
name|y
operator|=
operator|(
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
operator|*
name|bevent
operator|->
name|y
operator|/
name|editor
operator|->
name|preview
operator|->
name|requisition
operator|.
name|height
operator|-
name|offy
operator|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|y
operator|<
literal|0
operator|||
name|x
operator|>=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|||
name|y
operator|>=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|TRUE
return|;
name|col
operator|=
name|gimp_drawable_get_color_at
argument_list|(
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|col
index|[
literal|0
index|]
argument_list|,
name|col
index|[
literal|1
index|]
argument_list|,
name|col
index|[
literal|2
index|]
argument_list|,
name|col
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|col
argument_list|)
expr_stmt|;
name|gimp_image_mask_select_by_color
argument_list|(
name|image_editor
operator|->
name|gimage
argument_list|,
name|drawable
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
operator|&
name|color
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|select_transparent
argument_list|,
name|operation
argument_list|,
name|options
operator|->
name|antialias
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image_editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_drop_color (GtkWidget * widget,const GimpRGB * color,gpointer data)
name|gimp_selection_editor_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpImageEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|editor
operator|->
name|gimage
condition|)
return|return;
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|editor
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|tool_info_list
argument_list|,
literal|"gimp-by-color-select-tool"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|editor
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
name|gimp_image_mask_select_by_color
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
name|drawable
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|color
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|select_transparent
argument_list|,
name|options
operator|->
name|operation
argument_list|,
name|options
operator|->
name|antialias
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_mask_changed (GimpImage * gimage,GimpSelectionEditor * editor)
name|gimp_selection_editor_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_preview_renderer_invalidate
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|editor
operator|->
name|preview
argument_list|)
operator|->
name|renderer
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


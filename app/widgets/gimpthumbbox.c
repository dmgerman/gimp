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
file|"libgimpthumb/gimpthumb.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimpthumbbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_class_init
parameter_list|(
name|GimpThumbBoxClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_init
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_thumb_box_ebox_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_thumbnail_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_imagefile_info_changed
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_create_thumbnails
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
name|gboolean
name|always_create
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_box_create_thumbnail
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpThumbnailSize
name|size
parameter_list|,
name|gboolean
name|always_create
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkFrameClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_thumb_box_get_type (void)
name|gimp_thumb_box_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|box_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|box_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|box_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpThumbBoxClass
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
name|gimp_thumb_box_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpThumbBox
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_thumb_box_init
block|,       }
decl_stmt|;
name|box_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_FRAME
argument_list|,
literal|"GimpThumbBox"
argument_list|,
operator|&
name|box_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|box_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_thumb_box_class_init (GimpThumbBoxClass * klass)
name|gimp_thumb_box_class_init
parameter_list|(
name|GimpThumbBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_thumb_box_finalize
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_thumb_box_style_set
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_thumb_box_init (GimpThumbBox * box)
name|gimp_thumb_box_init
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
block|{
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|box
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_thumb_box_finalize (GObject * object)
name|gimp_thumb_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpThumbBox
modifier|*
name|box
init|=
name|GIMP_THUMB_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_thumb_box_set_uris
argument_list|(
name|box
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|imagefile
condition|)
block|{
name|g_object_unref
argument_list|(
name|box
operator|->
name|imagefile
argument_list|)
expr_stmt|;
name|box
operator|->
name|imagefile
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_thumb_box_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_thumb_box_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpThumbBox
modifier|*
name|box
init|=
name|GIMP_THUMB_BOX
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|ebox
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_modify_bg
argument_list|(
name|box
operator|->
name|preview
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
operator|&
name|widget
operator|->
name|style
operator|->
name|base
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_modify_bg
argument_list|(
name|box
operator|->
name|preview
argument_list|,
name|GTK_STATE_INSENSITIVE
argument_list|,
operator|&
name|widget
operator|->
name|style
operator|->
name|base
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|ebox
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_modify_bg
argument_list|(
name|ebox
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
operator|&
name|widget
operator|->
name|style
operator|->
name|base
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_modify_bg
argument_list|(
name|ebox
argument_list|,
name|GTK_STATE_INSENSITIVE
argument_list|,
operator|&
name|widget
operator|->
name|style
operator|->
name|base
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_thumb_box_new (Gimp * gimp)
name|gimp_thumb_box_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpThumbBox
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox2
decl_stmt|;
name|GtkWidget
modifier|*
name|ebox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|GtkRequisition
name|info_requisition
decl_stmt|;
name|GtkRequisition
name|progress_requisition
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_THUMB_BOX
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ebox
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|,
name|ebox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ebox
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|ebox
argument_list|,
literal|"button_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_thumb_box_ebox_button_press
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Click to update preview\n"
literal|"%s  Click to force update even "
literal|"if preview is up-to-date"
argument_list|)
argument_list|,
name|gimp_get_mod_name_control
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|ebox
argument_list|,
name|str
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ebox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"button_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"button_release_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"enter_notify_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"leave_notify_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox2
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox2
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|vbox2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox2
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|box
operator|->
name|imagefile
operator|=
name|gimp_imagefile_new
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|box
operator|->
name|imagefile
argument_list|,
literal|"info_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_thumb_box_imagefile_info_changed
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|box
operator|->
name|preview
operator|=
name|gimp_preview_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|box
operator|->
name|imagefile
argument_list|)
argument_list|,
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|box
operator|->
name|preview
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|box
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|box
operator|->
name|preview
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_thumb_box_thumbnail_clicked
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|box
operator|->
name|filename
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"No Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|box
operator|->
name|filename
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
name|box
operator|->
name|filename
argument_list|)
expr_stmt|;
name|box
operator|->
name|info
operator|=
name|gtk_label_new
argument_list|(
literal|" \n \n "
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|box
operator|->
name|info
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|box
operator|->
name|info
argument_list|)
argument_list|,
name|GTK_JUSTIFY_CENTER
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|box
operator|->
name|info
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
name|box
operator|->
name|info
argument_list|)
expr_stmt|;
name|box
operator|->
name|progress
operator|=
name|gtk_progress_bar_new
argument_list|()
expr_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|box
operator|->
name|progress
argument_list|)
argument_list|,
literal|"foo"
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|box
operator|->
name|progress
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* don't gtk_widget_show (box->progress); */
comment|/* eek */
name|gtk_widget_size_request
argument_list|(
name|box
operator|->
name|info
argument_list|,
operator|&
name|info_requisition
argument_list|)
expr_stmt|;
name|gtk_widget_size_request
argument_list|(
name|box
operator|->
name|progress
argument_list|,
operator|&
name|progress_requisition
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|box
operator|->
name|info
argument_list|,
name|progress_requisition
operator|.
name|width
argument_list|,
name|info_requisition
operator|.
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|box
operator|->
name|filename
argument_list|,
name|progress_requisition
operator|.
name|width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_thumb_box_set_uri (GimpThumbBox * box,const gchar * uri)
name|gimp_thumb_box_set_uri
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_THUMB_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|box
operator|->
name|imagefile
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|basename
operator|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|box
operator|->
name|filename
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|box
operator|->
name|filename
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"No Selection"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|,
name|uri
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_imagefile_update
argument_list|(
name|box
operator|->
name|imagefile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_thumb_box_set_uris (GimpThumbBox * box,GSList * uris)
name|gimp_thumb_box_set_uris
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
name|GSList
modifier|*
name|uris
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_THUMB_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|uris
condition|)
block|{
name|g_slist_foreach
argument_list|(
name|box
operator|->
name|uris
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|box
operator|->
name|uris
argument_list|)
expr_stmt|;
name|box
operator|->
name|uris
operator|=
name|NULL
expr_stmt|;
block|}
name|box
operator|->
name|uris
operator|=
name|uris
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_thumb_box_ebox_button_press (GtkWidget * widget,GdkEventButton * bevent,GimpThumbBox * box)
name|gimp_thumb_box_ebox_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
block|{
name|gimp_thumb_box_thumbnail_clicked
argument_list|(
name|widget
argument_list|,
name|bevent
operator|->
name|state
argument_list|,
name|box
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
DECL|function|gimp_thumb_box_thumbnail_clicked (GtkWidget * widget,GdkModifierType state,GimpThumbBox * box)
name|gimp_thumb_box_thumbnail_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
block|{
name|gimp_thumb_box_create_thumbnails
argument_list|(
name|box
argument_list|,
operator|(
name|state
operator|&
name|GDK_CONTROL_MASK
operator|)
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_thumb_box_imagefile_info_changed (GimpImagefile * imagefile,GimpThumbBox * box)
name|gimp_thumb_box_imagefile_info_changed
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpThumbBox
modifier|*
name|box
parameter_list|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|box
operator|->
name|info
argument_list|)
argument_list|,
name|gimp_imagefile_get_desc_string
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_thumb_box_create_thumbnails (GimpThumbBox * box,gboolean always_create)
name|gimp_thumb_box_create_thumbnails
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
name|gboolean
name|always_create
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|box
operator|->
name|imagefile
operator|->
name|gimp
decl_stmt|;
if|if
condition|(
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
operator|!=
name|GIMP_THUMBNAIL_SIZE_NONE
operator|&&
name|gimp
operator|->
name|config
operator|->
name|layer_previews
condition|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|n_uris
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|n_uris
operator|=
name|g_slist_length
argument_list|(
name|box
operator|->
name|uris
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_uris
operator|>
literal|1
condition|)
block|{
name|gchar
modifier|*
name|str
decl_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|box
operator|->
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|box
operator|->
name|progress
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|box
operator|->
name|info
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
operator|->
name|progress
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|box
operator|->
name|uris
operator|->
name|next
operator|,
name|i
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Thumbnail %d of %d"
argument_list|)
argument_list|,
name|i
argument_list|,
name|n_uris
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|box
operator|->
name|progress
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_thumb_box_create_thumbnail
argument_list|(
name|box
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
argument_list|,
name|always_create
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|box
operator|->
name|progress
argument_list|)
argument_list|,
operator|(
name|gdouble
operator|)
name|i
operator|/
operator|(
name|gdouble
operator|)
name|n_uris
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Thumbnail %d of %d"
argument_list|)
argument_list|,
name|n_uris
argument_list|,
name|n_uris
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|box
operator|->
name|progress
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|box
operator|->
name|uris
condition|)
block|{
name|gimp_thumb_box_create_thumbnail
argument_list|(
name|box
argument_list|,
name|box
operator|->
name|uris
operator|->
name|data
argument_list|,
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
argument_list|,
name|always_create
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_uris
operator|>
literal|1
condition|)
block|{
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|box
operator|->
name|progress
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|n_uris
operator|>
literal|1
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|box
operator|->
name|progress
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
operator|->
name|info
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_thumb_box_create_thumbnail (GimpThumbBox * box,const gchar * uri,GimpThumbnailSize size,gboolean always_create)
name|gimp_thumb_box_create_thumbnail
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpThumbnailSize
name|size
parameter_list|,
name|gboolean
name|always_create
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
operator|&&
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|basename
init|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|box
operator|->
name|filename
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|box
operator|->
name|imagefile
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|always_create
operator|||
name|gimp_thumbnail_peek_thumb
argument_list|(
name|box
operator|->
name|imagefile
operator|->
name|thumbnail
argument_list|,
name|size
argument_list|)
operator|<
name|GIMP_THUMB_STATE_FAILED
condition|)
block|{
name|gimp_imagefile_create_thumbnail
argument_list|(
name|box
operator|->
name|imagefile
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


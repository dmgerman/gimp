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
file|"config/gimpguiconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-scale.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagedialog.h"
end_include

begin_include
include|#
directive|include
file|"scale-dialog.h"
end_include

begin_include
include|#
directive|include
file|"image-scale-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c6268870108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|interpolation
name|GimpInterpolationType
name|interpolation
decl_stmt|;
DECL|member|xresolution
name|gdouble
name|xresolution
decl_stmt|;
DECL|member|yresolution
name|gdouble
name|yresolution
decl_stmt|;
DECL|member|resolution_unit
name|GimpUnit
name|resolution_unit
decl_stmt|;
DECL|member|callback
name|GimpScaleCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|typedef|ImageScaleDialog
block|}
name|ImageScaleDialog
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|image_scale_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|,
name|GimpUnit
name|resolution_unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_dialog_free
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|image_scale_confirm_dialog
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_confirm_large
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|,
name|gint64
name|new_memsize
parameter_list|,
name|gint64
name|max_memsize
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_confirm_small
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|image_scale_dialog_new (GimpImage * image,GimpContext * context,GtkWidget * parent,GimpUnit unit,GimpInterpolationType interpolation,GimpScaleCallback callback,gpointer user_data)
name|image_scale_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|GimpScaleCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|ImageScaleDialog
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
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_slice_new0
argument_list|(
name|ImageScaleDialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|dialog
operator|->
name|dialog
operator|=
name|scale_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|C_
argument_list|(
literal|"dialog-title"
argument_list|,
literal|"Scale Image"
argument_list|)
argument_list|,
literal|"gimp-image-scale"
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_SCALE
argument_list|,
name|unit
argument_list|,
name|interpolation
argument_list|,
name|image_scale_callback
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|image_scale_dialog_free
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|dialog
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
return|return
name|dialog
operator|->
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_callback (GtkWidget * widget,GimpViewable * viewable,gint width,gint height,GimpUnit unit,GimpInterpolationType interpolation,gdouble xresolution,gdouble yresolution,GimpUnit resolution_unit,gpointer data)
name|image_scale_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|,
name|GimpUnit
name|resolution_unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ImageScaleDialog
modifier|*
name|dialog
init|=
name|data
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|GimpImageScaleCheckType
name|scale_check
decl_stmt|;
name|gint64
name|max_memsize
decl_stmt|;
name|gint64
name|new_memsize
decl_stmt|;
name|dialog
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|dialog
operator|->
name|height
operator|=
name|height
expr_stmt|;
name|dialog
operator|->
name|unit
operator|=
name|unit
expr_stmt|;
name|dialog
operator|->
name|interpolation
operator|=
name|interpolation
expr_stmt|;
name|dialog
operator|->
name|xresolution
operator|=
name|xresolution
expr_stmt|;
name|dialog
operator|->
name|yresolution
operator|=
name|yresolution
expr_stmt|;
name|dialog
operator|->
name|resolution_unit
operator|=
name|resolution_unit
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|widget
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|max_memsize
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|max_new_image_size
expr_stmt|;
name|scale_check
operator|=
name|gimp_image_scale_check
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|max_memsize
argument_list|,
operator|&
name|new_memsize
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|scale_check
condition|)
block|{
case|case
name|GIMP_IMAGE_SCALE_TOO_BIG
case|:
name|image_scale_confirm_large
argument_list|(
name|dialog
argument_list|,
name|new_memsize
argument_list|,
name|max_memsize
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_IMAGE_SCALE_TOO_SMALL
case|:
name|image_scale_confirm_small
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_IMAGE_SCALE_OK
case|:
comment|/* If all is well, return directly after scaling image. */
name|dialog
operator|->
name|callback
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
argument_list|,
name|dialog
operator|->
name|width
argument_list|,
name|dialog
operator|->
name|height
argument_list|,
name|dialog
operator|->
name|unit
argument_list|,
name|dialog
operator|->
name|interpolation
argument_list|,
name|dialog
operator|->
name|xresolution
argument_list|,
name|dialog
operator|->
name|yresolution
argument_list|,
name|dialog
operator|->
name|resolution_unit
argument_list|,
name|dialog
operator|->
name|user_data
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
comment|/* remember the last used unit */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"scale-dialog-unit"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_dialog_free (ImageScaleDialog * dialog)
name|image_scale_dialog_free
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|ImageScaleDialog
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|image_scale_confirm_dialog (ImageScaleDialog * dialog)
name|image_scale_confirm_dialog
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|widget
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Confirm Scaling"
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|dialog
operator|->
name|dialog
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_SCALE_WARNING
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GIMP_STOCK_SCALE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|widget
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
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_scale_confirm_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
return|return
name|widget
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_confirm_large (ImageScaleDialog * dialog,gint64 new_memsize,gint64 max_memsize)
name|image_scale_confirm_large
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|,
name|gint64
name|new_memsize
parameter_list|,
name|gint64
name|max_memsize
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|image_scale_confirm_dialog
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|size
decl_stmt|;
name|size
operator|=
name|g_format_size_for_display
argument_list|(
name|new_memsize
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|widget
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"You are trying to create an image "
literal|"with a size of %s."
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|size
operator|=
name|g_format_size_for_display
argument_list|(
name|max_memsize
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|widget
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Scaling the image to the chosen size will "
literal|"make it use more memory than what is "
literal|"configured as \"Maximum Image Size\" in the "
literal|"Preferences dialog (currently %s)."
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_confirm_small (ImageScaleDialog * dialog)
name|image_scale_confirm_small
parameter_list|(
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|image_scale_confirm_dialog
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|widget
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Scaling the image to the chosen size "
literal|"will shrink some layers completely "
literal|"away."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|widget
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Is this what you want to do?"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_confirm_response (GtkWidget * widget,gint response_id,ImageScaleDialog * dialog)
name|image_scale_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageScaleDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|dialog
operator|->
name|callback
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
argument_list|,
name|dialog
operator|->
name|width
argument_list|,
name|dialog
operator|->
name|height
argument_list|,
name|dialog
operator|->
name|unit
argument_list|,
name|dialog
operator|->
name|interpolation
argument_list|,
name|dialog
operator|->
name|xresolution
argument_list|,
name|dialog
operator|->
name|yresolution
argument_list|,
name|dialog
operator|->
name|resolution_unit
argument_list|,
name|dialog
operator|->
name|user_data
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


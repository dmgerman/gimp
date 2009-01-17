begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpImageProfileView  * Copyright (C) 2006  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-icc-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageprofileview.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_image_profile_view_dispose
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
name|gimp_image_profile_view_update
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpImageProfileView,gimp_image_profile_view,GIMP_TYPE_IMAGE_PARASITE_VIEW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageProfileView
argument_list|,
argument|gimp_image_profile_view
argument_list|,
argument|GIMP_TYPE_IMAGE_PARASITE_VIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_profile_view_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_image_profile_view_class_init
parameter_list|(
name|GimpImageProfileViewClass
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
name|GimpImageParasiteViewClass
modifier|*
name|view_class
decl_stmt|;
name|view_class
operator|=
name|GIMP_IMAGE_PARASITE_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_image_profile_view_dispose
expr_stmt|;
name|view_class
operator|->
name|update
operator|=
name|gimp_image_profile_view_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_profile_view_init (GimpImageProfileView * view)
name|gimp_image_profile_view_init
parameter_list|(
name|GimpImageProfileView
modifier|*
name|view
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkWidget
modifier|*
name|text_view
decl_stmt|;
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|view
argument_list|)
argument_list|,
name|scrolled_window
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_window
argument_list|)
expr_stmt|;
name|text_view
operator|=
name|gtk_text_view_new
argument_list|()
expr_stmt|;
name|gtk_text_view_set_editable
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_text_view_set_wrap_mode
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
name|GTK_WRAP_WORD
argument_list|)
expr_stmt|;
name|gtk_text_view_set_pixels_above_lines
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_text_view_set_left_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_text_view_set_right_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|text_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|text_view
argument_list|)
expr_stmt|;
name|view
operator|->
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|text_view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
literal|"strong"
argument_list|,
literal|"weight"
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
literal|"scale"
argument_list|,
name|PANGO_SCALE_LARGE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
literal|"emphasis"
argument_list|,
literal|"style"
argument_list|,
name|PANGO_STYLE_OBLIQUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|view
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_profile_view_dispose (GObject * object)
name|gimp_image_profile_view_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageProfileView
modifier|*
name|view
init|=
name|GIMP_IMAGE_PROFILE_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|view
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|view
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
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
DECL|function|gimp_image_profile_view_new (GimpImage * image)
name|gimp_image_profile_view_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
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
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_PROFILE_VIEW
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
literal|"parasite"
argument_list|,
literal|"icc-profile"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_profile_view_query (GimpImageProfileView * view)
name|gimp_image_profile_view_query
parameter_list|(
name|GimpImageProfileView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|desc
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|info
init|=
name|NULL
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|GtkTextIter
name|iter
decl_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_start_iter
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_image_parasite_view_get_image
argument_list|(
name|GIMP_IMAGE_PARASITE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_icc_profile_info
argument_list|(
name|image
argument_list|,
name|gimp_get_user_context
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|name
argument_list|,
operator|&
name|desc
argument_list|,
operator|&
name|info
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|desc
operator|||
name|name
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|title
decl_stmt|;
if|if
condition|(
name|desc
operator|&&
name|strlen
argument_list|(
name|desc
argument_list|)
condition|)
name|title
operator|=
name|desc
expr_stmt|;
else|else
name|title
operator|=
name|name
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
name|title
argument_list|,
operator|-
literal|1
argument_list|,
literal|"strong"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|info
condition|)
name|gtk_text_buffer_insert
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
name|info
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|view
operator|->
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
name|error
operator|->
name|message
argument_list|,
operator|-
literal|1
argument_list|,
literal|"emphasis"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_profile_view_update (GimpImageParasiteView * view)
name|gimp_image_profile_view_update
parameter_list|(
name|GimpImageParasiteView
modifier|*
name|view
parameter_list|)
block|{
name|GimpImageProfileView
modifier|*
name|profile_view
init|=
name|GIMP_IMAGE_PROFILE_VIEW
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GtkTextIter
name|iter
decl_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|profile_view
operator|->
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_start_iter
argument_list|(
name|profile_view
operator|->
name|buffer
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|profile_view
operator|->
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
name|_
argument_list|(
literal|"Querying..."
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|"emphasis"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile_view
operator|->
name|idle_id
condition|)
name|g_source_remove
argument_list|(
name|profile_view
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|profile_view
operator|->
name|idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_image_profile_view_query
argument_list|,
name|profile_view
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


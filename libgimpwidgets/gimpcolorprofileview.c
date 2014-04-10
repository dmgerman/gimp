begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpColorProfileView  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<lcms2.h>
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofileview.h"
end_include

begin_struct
DECL|struct|_GimpColorProfileViewPrivate
struct|struct
name|_GimpColorProfileViewPrivate
block|{
DECL|member|profile
name|GimpColorProfile
name|profile
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_color_profile_view_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpColorProfileView
argument_list|,
name|gimp_color_profile_view
argument_list|,
name|GTK_TYPE_TEXT_VIEW
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_profile_view_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_view_class_init (GimpColorProfileViewClass * klass)
name|gimp_color_profile_view_class_init
parameter_list|(
name|GimpColorProfileViewClass
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_color_profile_view_constructed
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpColorProfileViewPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_view_init (GimpColorProfileView * view)
name|gimp_color_profile_view_init
parameter_list|(
name|GimpColorProfileView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|private
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|view
argument_list|,
name|GIMP_TYPE_COLOR_PROFILE_VIEW
argument_list|,
name|GimpColorProfileViewPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_view_constructed (GObject * object)
name|gimp_color_profile_view_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_create_tag
argument_list|(
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
name|gtk_text_view_set_editable
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_text_view_set_wrap_mode
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|object
argument_list|)
argument_list|,
name|GTK_WRAP_WORD
argument_list|)
expr_stmt|;
name|gtk_text_view_set_pixels_above_lines
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|object
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_text_view_set_left_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|object
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_text_view_set_right_margin
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|object
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_profile_view_new (void)
name|gimp_color_profile_view_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_PROFILE_VIEW
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_profile_view_set_profile (GimpColorProfileView * view,GimpColorProfile profile)
name|gimp_color_profile_view_set_profile
parameter_list|(
name|GimpColorProfileView
modifier|*
name|view
parameter_list|,
name|GimpColorProfile
name|profile
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|GtkTextIter
name|iter
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|summary
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|view
operator|->
name|private
operator|->
name|profile
operator|=
name|profile
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
return|return;
name|gtk_text_buffer_get_start_iter
argument_list|(
name|buffer
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_lcms_profile_get_label
argument_list|(
name|profile
argument_list|)
expr_stmt|;
name|summary
operator|=
name|gimp_lcms_profile_get_summary
argument_list|(
name|profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|label
operator|&&
name|strlen
argument_list|(
name|label
argument_list|)
condition|)
block|{
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
name|label
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
name|summary
condition|)
name|gtk_text_buffer_insert
argument_list|(
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
name|summary
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|summary
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_profile_view_set_error (GimpColorProfileView * view,const gchar * message)
name|gimp_color_profile_view_set_error
parameter_list|(
name|GimpColorProfileView
modifier|*
name|view
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|GtkTextIter
name|iter
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
literal|""
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_start_iter
argument_list|(
name|buffer
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert_with_tags_by_name
argument_list|(
name|buffer
argument_list|,
operator|&
name|iter
argument_list|,
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
block|}
end_function

end_unit


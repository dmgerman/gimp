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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/* maximal width of the string holding the cursor-coordinates for  * the status line  */
end_comment

begin_define
DECL|macro|CURSOR_STR_LENGTH
define|#
directive|define
name|CURSOR_STR_LENGTH
value|256
end_define

begin_function_decl
specifier|static
name|void
name|gimp_statusbar_class_init
parameter_list|(
name|GimpStatusbarClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_statusbar_init
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_statusbar_update
parameter_list|(
name|GtkStatusbar
modifier|*
name|gtk_statusbar
parameter_list|,
name|guint
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkStatusbarClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_statusbar_get_type (void)
name|gimp_statusbar_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|statusbar_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|statusbar_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|statusbar_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpStatusbarClass
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
name|gimp_statusbar_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpStatusbar
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_statusbar_init
block|,       }
decl_stmt|;
name|statusbar_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_STATUSBAR
argument_list|,
literal|"GimpStatusbar"
argument_list|,
operator|&
name|statusbar_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|statusbar_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_statusbar_class_init (GimpStatusbarClass * klass)
name|gimp_statusbar_class_init
parameter_list|(
name|GimpStatusbarClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkStatusbarClass
modifier|*
name|gtk_statusbar_class
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gtk_statusbar_class
operator|=
name|GTK_STATUSBAR_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gtk_statusbar_class
operator|->
name|text_pushed
operator|=
name|gimp_statusbar_update
expr_stmt|;
name|gtk_statusbar_class
operator|->
name|text_popped
operator|=
name|gimp_statusbar_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_statusbar_init (GimpStatusbar * statusbar)
name|gimp_statusbar_init
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|)
block|{
name|GtkStatusbar
modifier|*
name|gtk_statusbar
decl_stmt|;
name|GtkBox
modifier|*
name|box
decl_stmt|;
name|GtkShadowType
name|shadow_type
decl_stmt|;
name|gtk_statusbar
operator|=
name|GTK_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
expr_stmt|;
name|box
operator|=
name|GTK_BOX
argument_list|(
name|statusbar
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|gtk_statusbar
operator|->
name|frame
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
name|statusbar
operator|->
name|cursor_format_str
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
name|statusbar
operator|->
name|progressid
operator|=
literal|0
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|statusbar
argument_list|)
argument_list|,
literal|"shadow_type"
argument_list|,
operator|&
name|shadow_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|cursor_frame
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
name|statusbar
operator|->
name|cursor_frame
argument_list|)
argument_list|,
name|shadow_type
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|box
argument_list|,
name|statusbar
operator|->
name|cursor_frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|box
argument_list|,
name|statusbar
operator|->
name|cursor_frame
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|statusbar
operator|->
name|cursor_frame
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|cursor_label
operator|=
name|gtk_label_new
argument_list|(
literal|"0, 0"
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|statusbar
operator|->
name|cursor_label
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|statusbar
operator|->
name|cursor_frame
argument_list|)
argument_list|,
name|statusbar
operator|->
name|cursor_label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|statusbar
operator|->
name|cursor_label
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|progressbar
operator|=
name|gtk_progress_bar_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|box
argument_list|,
name|statusbar
operator|->
name|progressbar
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
name|statusbar
operator|->
name|progressbar
argument_list|)
expr_stmt|;
name|GTK_PROGRESS_BAR
argument_list|(
name|statusbar
operator|->
name|progressbar
argument_list|)
operator|->
name|progress
operator|.
name|x_align
operator|=
literal|0.0
expr_stmt|;
name|GTK_PROGRESS_BAR
argument_list|(
name|statusbar
operator|->
name|progressbar
argument_list|)
operator|->
name|progress
operator|.
name|y_align
operator|=
literal|0.5
expr_stmt|;
name|statusbar
operator|->
name|cancelbutton
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|statusbar
operator|->
name|cancelbutton
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|box
argument_list|,
name|statusbar
operator|->
name|cancelbutton
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
name|statusbar
operator|->
name|cancelbutton
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_statusbar_update (GtkStatusbar * gtk_statusbar,guint context_id,const gchar * text)
name|gimp_statusbar_update
parameter_list|(
name|GtkStatusbar
modifier|*
name|gtk_statusbar
parameter_list|,
name|guint
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GimpStatusbar
modifier|*
name|statusbar
decl_stmt|;
name|statusbar
operator|=
name|GIMP_STATUSBAR
argument_list|(
name|gtk_statusbar
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|text
condition|)
name|text
operator|=
literal|""
expr_stmt|;
name|gtk_progress_bar_set_text
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|statusbar
operator|->
name|progressbar
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_statusbar_new (GimpDisplayShell * shell)
name|gimp_statusbar_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpStatusbar
modifier|*
name|statusbar
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|statusbar
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_STATUSBAR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|statusbar
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|statusbar
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_statusbar_push (GimpStatusbar * statusbar,const gchar * context_id,const gchar * message)
name|gimp_statusbar_push
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|guint
name|context_uint
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|context_uint
operator|=
name|gtk_statusbar_get_context_id
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|,
name|context_id
argument_list|)
expr_stmt|;
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|,
name|context_uint
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_statusbar_push_coords (GimpStatusbar * statusbar,const gchar * context_id,const gchar * title,gdouble x,const gchar * separator,gdouble y)
name|gimp_statusbar_push_coords
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
name|x
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separator
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|gchar
name|buf
index|[
literal|256
index|]
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|separator
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|statusbar
operator|->
name|shell
operator|->
name|dot_for_dot
condition|)
block|{
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
name|title
argument_list|,
name|ROUND
argument_list|(
name|x
argument_list|)
argument_list|,
name|separator
argument_list|,
name|ROUND
argument_list|(
name|y
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* show real world units */
block|{
name|gdouble
name|unit_factor
decl_stmt|;
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|statusbar
operator|->
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
name|title
argument_list|,
name|x
operator|*
name|unit_factor
operator|/
name|statusbar
operator|->
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
name|separator
argument_list|,
name|y
operator|*
name|unit_factor
operator|/
name|statusbar
operator|->
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
block|}
name|gimp_statusbar_push
argument_list|(
name|statusbar
argument_list|,
name|context_id
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_statusbar_pop (GimpStatusbar * statusbar,const gchar * context_id)
name|gimp_statusbar_pop
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context_id
parameter_list|)
block|{
name|guint
name|context_uint
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|context_uint
operator|=
name|gtk_statusbar_get_context_id
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|,
name|context_id
argument_list|)
expr_stmt|;
name|gtk_statusbar_pop
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|,
name|context_uint
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_statusbar_update_cursor (GimpStatusbar * statusbar,gdouble x,gdouble y)
name|gimp_statusbar_update_cursor
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|=
name|statusbar
operator|->
name|shell
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
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|||
name|y
operator|>=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|statusbar
operator|->
name|cursor_label
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
name|buffer
index|[
name|CURSOR_STR_LENGTH
index|]
decl_stmt|;
if|if
condition|(
name|shell
operator|->
name|dot_for_dot
condition|)
block|{
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
literal|""
argument_list|,
name|ROUND
argument_list|(
name|x
argument_list|)
argument_list|,
literal|", "
argument_list|,
name|ROUND
argument_list|(
name|y
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* show real world units */
block|{
name|gdouble
name|unit_factor
decl_stmt|;
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|unit
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
literal|""
argument_list|,
name|x
operator|*
name|unit_factor
operator|/
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
literal|", "
argument_list|,
name|y
operator|*
name|unit_factor
operator|/
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|statusbar
operator|->
name|cursor_label
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_statusbar_resize_cursor (GimpStatusbar * statusbar)
name|gimp_statusbar_resize_cursor
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|)
block|{
specifier|static
name|PangoLayout
modifier|*
name|layout
init|=
name|NULL
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gchar
name|buffer
index|[
name|CURSOR_STR_LENGTH
index|]
decl_stmt|;
name|gint
name|cursor_label_width
decl_stmt|;
name|gint
name|label_frame_size_difference
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STATUSBAR
argument_list|(
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|=
name|statusbar
operator|->
name|shell
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|dot_for_dot
condition|)
block|{
name|g_snprintf
argument_list|(
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
sizeof|sizeof
argument_list|(
name|statusbar
operator|->
name|cursor_format_str
argument_list|)
argument_list|,
literal|"%%s%%d%%s%%d"
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
literal|""
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
literal|", "
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* show real world units */
block|{
name|GimpUnit
name|unit
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|unit
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|unit
expr_stmt|;
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
sizeof|sizeof
argument_list|(
name|statusbar
operator|->
name|cursor_format_str
argument_list|)
argument_list|,
literal|"%%s%%.%df%%s%%.%df %s"
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|unit
argument_list|)
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|unit
argument_list|)
argument_list|,
name|gimp_unit_get_symbol
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|statusbar
operator|->
name|cursor_format_str
argument_list|,
literal|""
argument_list|,
operator|(
name|gdouble
operator|)
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|*
name|unit_factor
operator|/
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|xresolution
argument_list|,
literal|", "
argument_list|,
operator|(
name|gdouble
operator|)
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|height
operator|*
name|unit_factor
operator|/
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
block|}
comment|/* one static layout for all displays should be fine */
if|if
condition|(
operator|!
name|layout
condition|)
name|layout
operator|=
name|gtk_widget_create_pango_layout
argument_list|(
name|statusbar
operator|->
name|cursor_label
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
else|else
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|buffer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_size
argument_list|(
name|layout
argument_list|,
operator|&
name|cursor_label_width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  find out how many pixels the label's parent frame is bigger than    *  the label itself    */
name|label_frame_size_difference
operator|=
operator|(
name|statusbar
operator|->
name|cursor_frame
operator|->
name|allocation
operator|.
name|width
operator|-
name|statusbar
operator|->
name|cursor_label
operator|->
name|allocation
operator|.
name|width
operator|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|statusbar
operator|->
name|cursor_label
argument_list|,
name|cursor_label_width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* don't resize if this is a new display */
if|if
condition|(
name|label_frame_size_difference
condition|)
name|gtk_widget_set_size_request
argument_list|(
name|statusbar
operator|->
name|cursor_frame
argument_list|,
name|cursor_label_width
operator|+
name|label_frame_size_difference
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|gimp_display_shell_update_cursor (shell,                                     shell->cursor_x,                                     shell->cursor_y);
endif|#
directive|endif
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2002 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"imap_circle.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_misc.h"
end_include

begin_include
include|#
directive|include
file|"imap_object_popup.h"
end_include

begin_include
include|#
directive|include
file|"imap_stock.h"
end_include

begin_include
include|#
directive|include
file|"imap_table.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|circle_is_valid
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Object_t
modifier|*
name|circle_clone
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_assign
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|Object_t
modifier|*
name|des
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_draw
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_draw_sashes
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|MoveSashFunc_t
name|circle_near_sash
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|circle_point_is_on
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_get_dimensions
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_resize
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|percentage_x
parameter_list|,
name|gint
name|percentage_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_move
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|dx
parameter_list|,
name|gint
name|dy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gpointer
name|circle_create_info_widget
parameter_list|(
name|GtkWidget
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_fill_info_tab
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_set_initial_focus
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_update
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_write_csim
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_write_cern
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|circle_write_ncsa
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|circle_get_stock_icon_name
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|circle_class
specifier|static
name|ObjectClass_t
name|circle_class
init|=
block|{
name|N_
argument_list|(
literal|"C_ircle"
argument_list|)
block|,
name|NULL
block|,
comment|/* info_dialog */
name|NULL
block|,
comment|/* icon */
name|NULL
block|,
comment|/* mask */
name|circle_is_valid
block|,
name|NULL
block|,
comment|/* circle_destruct */
name|circle_clone
block|,
name|circle_assign
block|,
name|NULL
block|,
comment|/* circle_normalize */
name|circle_draw
block|,
name|circle_draw_sashes
block|,
name|circle_near_sash
block|,
name|circle_point_is_on
block|,
name|circle_get_dimensions
block|,
name|circle_resize
block|,
name|circle_move
block|,
name|circle_create_info_widget
block|,
name|circle_fill_info_tab
block|,
comment|/* circle_update_info_widget */
name|circle_fill_info_tab
block|,
name|circle_set_initial_focus
block|,
name|circle_update
block|,
name|circle_write_csim
block|,
name|circle_write_cern
block|,
name|circle_write_ncsa
block|,
name|object_do_popup
block|,
name|circle_get_stock_icon_name
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|Object_t
modifier|*
DECL|function|create_circle (gint x,gint y,gint r)
name|create_circle
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|r
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|g_new
argument_list|(
name|Circle_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|circle
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|circle
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|circle
operator|->
name|r
operator|=
name|r
expr_stmt|;
return|return
name|object_init
argument_list|(
operator|&
name|circle
operator|->
name|obj
argument_list|,
operator|&
name|circle_class
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|circle_is_valid (Object_t * obj)
name|circle_is_valid
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
block|{
return|return
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
operator|->
name|r
operator|>
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|Object_t
modifier|*
DECL|function|circle_clone (Object_t * obj)
name|circle_clone
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|Circle_t
modifier|*
name|clone
init|=
name|g_new
argument_list|(
name|Circle_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|clone
operator|->
name|x
operator|=
name|circle
operator|->
name|x
expr_stmt|;
name|clone
operator|->
name|y
operator|=
name|circle
operator|->
name|y
expr_stmt|;
name|clone
operator|->
name|r
operator|=
name|circle
operator|->
name|r
expr_stmt|;
return|return
operator|&
name|clone
operator|->
name|obj
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_assign (Object_t * obj,Object_t * des)
name|circle_assign
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|Object_t
modifier|*
name|des
parameter_list|)
block|{
name|Circle_t
modifier|*
name|src_circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|Circle_t
modifier|*
name|des_circle
init|=
name|ObjectToCircle
argument_list|(
name|des
argument_list|)
decl_stmt|;
name|des_circle
operator|->
name|x
operator|=
name|src_circle
operator|->
name|x
expr_stmt|;
name|des_circle
operator|->
name|y
operator|=
name|src_circle
operator|->
name|y
expr_stmt|;
name|des_circle
operator|->
name|r
operator|=
name|src_circle
operator|->
name|r
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_draw (Object_t * obj,GdkWindow * window,GdkGC * gc)
name|circle_draw
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|draw_circle
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|FALSE
argument_list|,
name|circle
operator|->
name|x
argument_list|,
name|circle
operator|->
name|y
argument_list|,
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_draw_sashes (Object_t * obj,GdkWindow * window,GdkGC * gc)
name|circle_draw_sashes
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|draw_sash
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|circle
operator|->
name|x
operator|-
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|-
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
name|draw_sash
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|circle
operator|->
name|x
operator|+
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|-
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
name|draw_sash
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|circle
operator|->
name|x
operator|-
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|+
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
name|draw_sash
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|circle
operator|->
name|x
operator|+
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|+
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|sash_x
specifier|static
name|gint
name|sash_x
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sash_y
specifier|static
name|gint
name|sash_y
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|move_sash (Object_t * obj,gint dx,gint dy)
name|move_sash
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|dx
parameter_list|,
name|gint
name|dy
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|gint
name|rx
decl_stmt|,
name|ry
decl_stmt|;
name|sash_x
operator|+=
name|dx
expr_stmt|;
name|sash_y
operator|+=
name|dy
expr_stmt|;
name|rx
operator|=
name|abs
argument_list|(
name|circle
operator|->
name|x
operator|-
name|sash_x
argument_list|)
expr_stmt|;
name|ry
operator|=
name|abs
argument_list|(
name|circle
operator|->
name|y
operator|-
name|sash_y
argument_list|)
expr_stmt|;
name|circle
operator|->
name|r
operator|=
operator|(
name|rx
operator|>
name|ry
operator|)
condition|?
name|rx
else|:
name|ry
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_resize (Object_t * obj,gint percentage_x,gint percentage_y)
name|circle_resize
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|percentage_x
parameter_list|,
name|gint
name|percentage_y
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|circle
operator|->
name|x
operator|=
name|circle
operator|->
name|x
operator|*
name|percentage_x
operator|/
literal|100
expr_stmt|;
name|circle
operator|->
name|y
operator|=
name|circle
operator|->
name|y
operator|*
name|percentage_y
operator|/
literal|100
expr_stmt|;
name|circle
operator|->
name|r
operator|=
name|circle
operator|->
name|r
operator|*
operator|(
operator|(
name|percentage_x
operator|<
name|percentage_y
operator|)
condition|?
name|percentage_x
else|:
name|percentage_y
operator|)
operator|/
literal|100
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|MoveSashFunc_t
DECL|function|circle_near_sash (Object_t * obj,gint x,gint y)
name|circle_near_sash
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|sash_x
operator|=
name|x
expr_stmt|;
name|sash_y
operator|=
name|y
expr_stmt|;
if|if
condition|(
name|near_sash
argument_list|(
name|circle
operator|->
name|x
operator|-
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|-
name|circle
operator|->
name|r
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|||
name|near_sash
argument_list|(
name|circle
operator|->
name|x
operator|+
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|-
name|circle
operator|->
name|r
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|||
name|near_sash
argument_list|(
name|circle
operator|->
name|x
operator|-
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|+
name|circle
operator|->
name|r
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
operator|||
name|near_sash
argument_list|(
name|circle
operator|->
name|x
operator|+
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|y
operator|+
name|circle
operator|->
name|r
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
condition|)
return|return
name|move_sash
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|circle_point_is_on (Object_t * obj,gint x,gint y)
name|circle_point_is_on
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|x
operator|-=
name|circle
operator|->
name|x
expr_stmt|;
name|y
operator|-=
name|circle
operator|->
name|y
expr_stmt|;
return|return
name|x
operator|*
name|x
operator|+
name|y
operator|*
name|y
operator|<=
name|circle
operator|->
name|r
operator|*
name|circle
operator|->
name|r
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_get_dimensions (Object_t * obj,gint * x,gint * y,gint * width,gint * height)
name|circle_get_dimensions
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
operator|*
name|x
operator|=
name|circle
operator|->
name|x
operator|-
name|circle
operator|->
name|r
expr_stmt|;
operator|*
name|y
operator|=
name|circle
operator|->
name|y
operator|-
name|circle
operator|->
name|r
expr_stmt|;
operator|*
name|width
operator|=
operator|*
name|height
operator|=
literal|2
operator|*
name|circle
operator|->
name|r
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_move (Object_t * obj,gint dx,gint dy)
name|circle_move
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gint
name|dx
parameter_list|,
name|gint
name|dy
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|circle
operator|->
name|x
operator|+=
name|dx
expr_stmt|;
name|circle
operator|->
name|y
operator|+=
name|dy
expr_stmt|;
block|}
end_function

begin_typedef
DECL|struct|__anon277c21260108
typedef|typedef
struct|struct
block|{
DECL|member|obj
name|Object_t
modifier|*
name|obj
decl_stmt|;
DECL|member|x
name|GtkWidget
modifier|*
name|x
decl_stmt|;
DECL|member|y
name|GtkWidget
modifier|*
name|y
decl_stmt|;
DECL|member|r
name|GtkWidget
modifier|*
name|r
decl_stmt|;
DECL|typedef|CircleProperties_t
block|}
name|CircleProperties_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|x_changed_cb (GtkWidget * widget,gpointer data)
name|x_changed_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
operator|(
operator|(
name|CircleProperties_t
operator|*
operator|)
name|data
operator|)
operator|->
name|obj
decl_stmt|;
name|gint
name|x
init|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|edit_area_info_dialog_emit_geometry_signal
argument_list|(
name|obj
operator|->
name|class
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|y_changed_cb (GtkWidget * widget,gpointer data)
name|y_changed_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
operator|(
operator|(
name|CircleProperties_t
operator|*
operator|)
name|data
operator|)
operator|->
name|obj
decl_stmt|;
name|gint
name|y
init|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|edit_area_info_dialog_emit_geometry_signal
argument_list|(
name|obj
operator|->
name|class
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|r_changed_cb (GtkWidget * widget,gpointer data)
name|r_changed_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Object_t
modifier|*
name|obj
init|=
operator|(
operator|(
name|CircleProperties_t
operator|*
operator|)
name|data
operator|)
operator|->
name|obj
decl_stmt|;
name|gint
name|r
init|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
operator|->
name|r
operator|=
name|r
expr_stmt|;
name|edit_area_info_dialog_emit_geometry_signal
argument_list|(
name|obj
operator|->
name|class
operator|->
name|info_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gpointer
DECL|function|circle_create_info_widget (GtkWidget * frame)
name|circle_create_info_widget
parameter_list|(
name|GtkWidget
modifier|*
name|frame
parameter_list|)
block|{
name|CircleProperties_t
modifier|*
name|props
init|=
name|g_new
argument_list|(
name|CircleProperties_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|,
modifier|*
name|label
decl_stmt|;
name|gint
name|max_width
init|=
name|get_image_width
argument_list|()
decl_stmt|;
name|gint
name|max_height
init|=
name|get_image_height
argument_list|()
decl_stmt|;
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Center _x:"
argument_list|)
argument_list|)
expr_stmt|;
name|props
operator|->
name|x
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|max_width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|props
operator|->
name|x
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|x_changed_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|props
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Center _y:"
argument_list|)
argument_list|)
expr_stmt|;
name|props
operator|->
name|y
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|max_height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|props
operator|->
name|y
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|y_changed_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|props
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Radius:"
argument_list|)
argument_list|)
expr_stmt|;
name|props
operator|->
name|r
operator|=
name|create_spin_button_in_table
argument_list|(
name|table
argument_list|,
name|label
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|props
operator|->
name|r
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|r_changed_cb
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|props
argument_list|)
expr_stmt|;
name|create_label_in_table
argument_list|(
name|table
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|props
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_fill_info_tab (Object_t * obj,gpointer data)
name|circle_fill_info_tab
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|CircleProperties_t
modifier|*
name|props
init|=
operator|(
name|CircleProperties_t
operator|*
operator|)
name|data
decl_stmt|;
name|props
operator|->
name|obj
operator|=
name|obj
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|props
operator|->
name|x
argument_list|)
argument_list|,
name|circle
operator|->
name|x
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|props
operator|->
name|y
argument_list|)
argument_list|,
name|circle
operator|->
name|y
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_value
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|props
operator|->
name|r
argument_list|)
argument_list|,
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_set_initial_focus (Object_t * obj,gpointer data)
name|circle_set_initial_focus
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|CircleProperties_t
modifier|*
name|props
init|=
operator|(
name|CircleProperties_t
operator|*
operator|)
name|data
decl_stmt|;
name|gtk_widget_grab_focus
argument_list|(
name|props
operator|->
name|x
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_update (Object_t * obj,gpointer data)
name|circle_update
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|CircleProperties_t
modifier|*
name|props
init|=
operator|(
name|CircleProperties_t
operator|*
operator|)
name|data
decl_stmt|;
name|circle
operator|->
name|x
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|props
operator|->
name|x
argument_list|)
argument_list|)
expr_stmt|;
name|circle
operator|->
name|y
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|props
operator|->
name|y
argument_list|)
argument_list|)
expr_stmt|;
name|circle
operator|->
name|r
operator|=
name|gtk_spin_button_get_value_as_int
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|props
operator|->
name|r
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_write_csim (Object_t * obj,gpointer param,OutputFunc_t output)
name|circle_write_csim
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|output
argument_list|(
name|param
argument_list|,
literal|"\"circle\" coords=\"%d,%d,%d\""
argument_list|,
name|circle
operator|->
name|x
argument_list|,
name|circle
operator|->
name|y
argument_list|,
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_write_cern (Object_t * obj,gpointer param,OutputFunc_t output)
name|circle_write_cern
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|output
argument_list|(
name|param
argument_list|,
literal|"circ (%d,%d) %d"
argument_list|,
name|circle
operator|->
name|x
argument_list|,
name|circle
operator|->
name|y
argument_list|,
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_write_ncsa (Object_t * obj,gpointer param,OutputFunc_t output)
name|circle_write_ncsa
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|output
argument_list|(
name|param
argument_list|,
literal|"circle %s %d,%d %d,%d"
argument_list|,
name|obj
operator|->
name|url
argument_list|,
name|circle
operator|->
name|x
argument_list|,
name|circle
operator|->
name|y
argument_list|,
name|circle
operator|->
name|x
argument_list|,
name|circle
operator|->
name|y
operator|+
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|circle_get_stock_icon_name (void)
name|circle_get_stock_icon_name
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|IMAP_STOCK_CIRCLE
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|_start_x
DECL|variable|_start_y
specifier|static
name|gint
name|_start_x
decl_stmt|,
name|_start_y
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Object_t
modifier|*
DECL|function|circle_factory_create_object1 (gint x,gint y)
name|circle_factory_create_object1
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|_start_x
operator|=
name|x
expr_stmt|;
name|_start_y
operator|=
name|y
expr_stmt|;
return|return
name|create_circle
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_factory_set_xy1 (Object_t * obj,guint state,gint x,gint y)
name|circle_factory_set_xy1
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|guint
name|state
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|circle
operator|->
name|x
operator|=
operator|(
name|_start_x
operator|+
name|x
operator|)
operator|/
literal|2
expr_stmt|;
name|circle
operator|->
name|y
operator|=
operator|(
name|_start_y
operator|+
name|y
operator|)
operator|/
literal|2
expr_stmt|;
name|x
operator|-=
name|_start_x
expr_stmt|;
name|y
operator|-=
name|_start_y
expr_stmt|;
name|circle
operator|->
name|r
operator|=
operator|(
name|gint
operator|)
name|sqrt
argument_list|(
name|x
operator|*
name|x
operator|+
name|y
operator|*
name|y
argument_list|)
operator|/
literal|2
expr_stmt|;
name|main_set_dimension
argument_list|(
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|circle_factory1
specifier|static
name|ObjectFactory_t
name|circle_factory1
init|=
block|{
name|NULL
block|,
comment|/* Object pointer */
name|NULL
block|,
comment|/* Finish func */
name|NULL
block|,
comment|/* Cancel func */
name|circle_factory_create_object1
block|,
name|circle_factory_set_xy1
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Object_t
modifier|*
DECL|function|circle_factory_create_object2 (gint x,gint y)
name|circle_factory_create_object2
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
return|return
name|create_circle
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|circle_factory_set_xy2 (Object_t * obj,guint state,gint x,gint y)
name|circle_factory_set_xy2
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|guint
name|state
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|Circle_t
modifier|*
name|circle
init|=
name|ObjectToCircle
argument_list|(
name|obj
argument_list|)
decl_stmt|;
name|x
operator|-=
name|circle
operator|->
name|x
expr_stmt|;
name|y
operator|-=
name|circle
operator|->
name|y
expr_stmt|;
name|circle
operator|->
name|r
operator|=
operator|(
name|gint
operator|)
name|sqrt
argument_list|(
name|x
operator|*
name|x
operator|+
name|y
operator|*
name|y
argument_list|)
expr_stmt|;
name|main_set_dimension
argument_list|(
name|circle
operator|->
name|r
argument_list|,
name|circle
operator|->
name|r
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|circle_factory2
specifier|static
name|ObjectFactory_t
name|circle_factory2
init|=
block|{
name|NULL
block|,
comment|/* Object pointer */
name|NULL
block|,
comment|/* Finish func */
name|NULL
block|,
comment|/* Cancel func */
name|circle_factory_create_object2
block|,
name|circle_factory_set_xy2
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|ObjectFactory_t
modifier|*
DECL|function|get_circle_factory (guint state)
name|get_circle_factory
parameter_list|(
name|guint
name|state
parameter_list|)
block|{
return|return
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|?
operator|&
name|circle_factory1
else|:
operator|&
name|circle_factory2
return|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_OBJECT_H
end_ifndef

begin_define
DECL|macro|_IMAP_OBJECT_H
define|#
directive|define
name|_IMAP_OBJECT_H
end_define

begin_typedef
DECL|typedef|Object_t
typedef|typedef
name|struct
name|Object_t
name|Object_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ObjectClass_t
typedef|typedef
name|struct
name|ObjectClass_t
name|ObjectClass_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ObjectList_t
typedef|typedef
name|struct
name|ObjectList_t
name|ObjectList_t
typedef|;
end_typedef

begin_include
include|#
directive|include
file|"imap_edit_area_info.h"
end_include

begin_include
include|#
directive|include
file|"imap_menu_funcs.h"
end_include

begin_struct
DECL|struct|Object_t
struct|struct
name|Object_t
block|{
DECL|member|class
name|ObjectClass_t
modifier|*
name|class
decl_stmt|;
DECL|member|list
name|ObjectList_t
modifier|*
name|list
decl_stmt|;
DECL|member|refcount
name|gint
name|refcount
decl_stmt|;
DECL|member|selected
name|gboolean
name|selected
decl_stmt|;
DECL|member|locked
name|gboolean
name|locked
decl_stmt|;
DECL|member|url
name|gchar
modifier|*
name|url
decl_stmt|;
DECL|member|target
name|gchar
modifier|*
name|target
decl_stmt|;
DECL|member|comment
name|gchar
modifier|*
name|comment
decl_stmt|;
DECL|member|mouse_over
name|gchar
modifier|*
name|mouse_over
decl_stmt|;
DECL|member|mouse_out
name|gchar
modifier|*
name|mouse_out
decl_stmt|;
DECL|member|focus
name|gchar
modifier|*
name|focus
decl_stmt|;
DECL|member|blur
name|gchar
modifier|*
name|blur
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|MoveSashFunc_t
typedef|typedef
name|void
function_decl|(
modifier|*
name|MoveSashFunc_t
function_decl|)
parameter_list|(
name|Object_t
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|OutputFunc_t
typedef|typedef
name|void
function_decl|(
modifier|*
name|OutputFunc_t
function_decl|)
parameter_list|(
name|gpointer
parameter_list|,
specifier|const
name|char
modifier|*
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
typedef|);
end_typedef

begin_struct_decl
struct_decl|struct
name|AreaInfoDialog_t
struct_decl|;
end_struct_decl

begin_struct
DECL|struct|ObjectClass_t
struct|struct
name|ObjectClass_t
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|info_dialog
name|AreaInfoDialog_t
modifier|*
name|info_dialog
decl_stmt|;
DECL|member|is_valid
name|gboolean
function_decl|(
modifier|*
name|is_valid
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
DECL|member|destruct
name|void
function_decl|(
modifier|*
name|destruct
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
DECL|member|clone
name|Object_t
modifier|*
function_decl|(
modifier|*
name|clone
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
DECL|member|assign
name|void
function_decl|(
modifier|*
name|assign
function_decl|)
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
DECL|member|normalize
name|void
function_decl|(
modifier|*
name|normalize
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
DECL|member|draw_sashes
name|void
function_decl|(
modifier|*
name|draw_sashes
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
DECL|member|near_sash
name|MoveSashFunc_t
function_decl|(
modifier|*
name|near_sash
function_decl|)
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
DECL|member|point_is_on
name|gboolean
function_decl|(
modifier|*
name|point_is_on
function_decl|)
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
DECL|member|get_dimensions
name|void
function_decl|(
modifier|*
name|get_dimensions
function_decl|)
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
DECL|member|resize
name|void
function_decl|(
modifier|*
name|resize
function_decl|)
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
DECL|member|move
name|void
function_decl|(
modifier|*
name|move
function_decl|)
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
DECL|member|create_info_widget
name|gpointer
function_decl|(
modifier|*
name|create_info_widget
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|frame
parameter_list|)
function_decl|;
DECL|member|update_info_widget
name|void
function_decl|(
modifier|*
name|update_info_widget
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|fill_info_tab
name|void
function_decl|(
modifier|*
name|fill_info_tab
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|set_initial_focus
name|void
function_decl|(
modifier|*
name|set_initial_focus
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|write_csim
name|void
function_decl|(
modifier|*
name|write_csim
function_decl|)
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
DECL|member|write_cern
name|void
function_decl|(
modifier|*
name|write_cern
function_decl|)
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
DECL|member|write_ncsa
name|void
function_decl|(
modifier|*
name|write_ncsa
function_decl|)
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
DECL|member|do_popup
name|void
function_decl|(
modifier|*
name|do_popup
function_decl|)
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
DECL|member|get_stock_icon_name
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_stock_icon_name
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|Object_t
modifier|*
name|object_ref
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_unref
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Object_t
modifier|*
name|object_init
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|ObjectClass_t
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Object_t
modifier|*
name|object_clone
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Object_t
modifier|*
name|object_assign
parameter_list|(
name|Object_t
modifier|*
name|src
parameter_list|,
name|Object_t
modifier|*
name|des
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_draw
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_edit
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gboolean
name|add
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_select
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_unselect
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_move
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
name|void
name|object_move_sash
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
name|void
name|object_remove
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_lock
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_unlock
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_set_url
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
specifier|const
name|gchar
modifier|*
name|url
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_set_target
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_set_comment
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
specifier|const
name|gchar
modifier|*
name|comment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_set_mouse_over
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mouse_over
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_set_mouse_out
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mouse_out
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_set_focus
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
specifier|const
name|gchar
modifier|*
name|focus
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_set_blur
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blur
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|object_get_position_in_list
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_emit_changed_signal
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_emit_geometry_signal
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_emit_update_signal
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|object_is_valid (obj)
define|#
directive|define
name|object_is_valid
parameter_list|(
name|obj
parameter_list|)
define|\
value|((obj)->class->is_valid(obj))
end_define

begin_define
DECL|macro|object_get_dimensions (obj,x,y,width,height)
define|#
directive|define
name|object_get_dimensions
parameter_list|(
name|obj
parameter_list|,
name|x
parameter_list|,
name|y
parameter_list|,
name|width
parameter_list|,
name|height
parameter_list|)
define|\
value|((obj)->class->get_dimensions((obj), (x), (y), (width), (height)))
end_define

begin_define
DECL|macro|object_normalize (obj)
define|#
directive|define
name|object_normalize
parameter_list|(
name|obj
parameter_list|)
define|\
value|((obj)->class->normalize(obj))
end_define

begin_define
DECL|macro|object_resize (obj,per_x,per_y)
define|#
directive|define
name|object_resize
parameter_list|(
name|obj
parameter_list|,
name|per_x
parameter_list|,
name|per_y
parameter_list|)
define|\
value|((obj)->class->resize((obj), (per_x), (per_y)))
end_define

begin_define
DECL|macro|object_update (obj,data)
define|#
directive|define
name|object_update
parameter_list|(
name|obj
parameter_list|,
name|data
parameter_list|)
define|\
value|((obj)->class->update((obj), (data)))
end_define

begin_define
DECL|macro|object_update_info_widget (obj,data)
define|#
directive|define
name|object_update_info_widget
parameter_list|(
name|obj
parameter_list|,
name|data
parameter_list|)
define|\
value|((obj)->class->update_info_widget((obj), (data)))
end_define

begin_define
DECL|macro|object_fill_info_tab (obj,data)
define|#
directive|define
name|object_fill_info_tab
parameter_list|(
name|obj
parameter_list|,
name|data
parameter_list|)
define|\
value|((obj)->class->fill_info_tab((obj), (data)))
end_define

begin_define
DECL|macro|object_get_stock_icon_name (obj)
define|#
directive|define
name|object_get_stock_icon_name
parameter_list|(
name|obj
parameter_list|)
define|\
value|((obj)->class->get_stock_icon_name())
end_define

begin_typedef
DECL|struct|__anon2b17801b0108
typedef|typedef
struct|struct
block|{
DECL|member|obj
name|Object_t
modifier|*
name|obj
decl_stmt|;
DECL|member|finish
name|gboolean
function_decl|(
modifier|*
name|finish
function_decl|)
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
DECL|member|cancel
name|gboolean
function_decl|(
modifier|*
name|cancel
function_decl|)
parameter_list|(
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
DECL|member|create_object
name|Object_t
modifier|*
function_decl|(
modifier|*
name|create_object
function_decl|)
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
DECL|member|set_xy
name|void
function_decl|(
modifier|*
name|set_xy
function_decl|)
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
function_decl|;
DECL|typedef|ObjectFactory_t
block|}
name|ObjectFactory_t
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|object_on_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|struct|__anon2b17801b0208
typedef|typedef
struct|struct
block|{
DECL|member|list
name|GList
modifier|*
name|list
decl_stmt|;
DECL|typedef|ObjectListCallback_t
block|}
name|ObjectListCallback_t
typedef|;
end_typedef

begin_struct
DECL|struct|ObjectList_t
struct|struct
name|ObjectList_t
block|{
DECL|member|list
name|GList
modifier|*
name|list
decl_stmt|;
DECL|member|changed
name|gboolean
name|changed
decl_stmt|;
DECL|member|changed_cb
name|ObjectListCallback_t
name|changed_cb
decl_stmt|;
DECL|member|update_cb
name|ObjectListCallback_t
name|update_cb
decl_stmt|;
DECL|member|add_cb
name|ObjectListCallback_t
name|add_cb
decl_stmt|;
DECL|member|remove_cb
name|ObjectListCallback_t
name|remove_cb
decl_stmt|;
DECL|member|select_cb
name|ObjectListCallback_t
name|select_cb
decl_stmt|;
DECL|member|move_cb
name|ObjectListCallback_t
name|move_cb
decl_stmt|;
DECL|member|geometry_cb
name|ObjectListCallback_t
name|geometry_cb
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|ObjectList_t
modifier|*
name|make_object_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_destruct
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ObjectList_t
modifier|*
name|object_list_copy
parameter_list|(
name|ObjectList_t
modifier|*
name|des
parameter_list|,
name|ObjectList_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ObjectList_t
modifier|*
name|object_list_append_list
parameter_list|(
name|ObjectList_t
modifier|*
name|des
parameter_list|,
name|ObjectList_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_append
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_prepend
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_insert
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gint
name|position
parameter_list|,
name|Object_t
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove_link
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|GList
modifier|*
name|link
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_update
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_draw
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_draw_selected
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Object_t
modifier|*
name|object_list_find
parameter_list|(
name|ObjectList_t
modifier|*
name|list
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
name|Object_t
modifier|*
name|object_list_near_sash
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|MoveSashFunc_t
modifier|*
name|sash_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|object_list_cut
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_copy_to_paste_buffer
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_paste
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove_all
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_delete_selected
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_edit_selected
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|object_list_select_all
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_select_next
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_select_prev
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|object_list_select_region
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|object_list_deselect_all
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|exception
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|object_list_nr_selected
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_resize
parameter_list|(
name|ObjectList_t
modifier|*
name|list
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
name|void
name|object_list_move_selected
parameter_list|(
name|ObjectList_t
modifier|*
name|list
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
name|void
name|object_list_move_up
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_move_down
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_move_selected_up
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_move_selected_down
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_move_to_front
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_send_to_back
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_move_sash_selected
parameter_list|(
name|ObjectList_t
modifier|*
name|list
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
name|void
name|object_list_write_csim
parameter_list|(
name|ObjectList_t
modifier|*
name|list
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
name|void
name|object_list_write_cern
parameter_list|(
name|ObjectList_t
modifier|*
name|list
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
name|void
name|object_list_write_ncsa
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|ObjectListCallbackFunc_t
typedef|typedef
name|void
function_decl|(
modifier|*
name|ObjectListCallbackFunc_t
function_decl|)
parameter_list|(
name|Object_t
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|gpointer
name|object_list_add_changed_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|object_list_add_update_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|object_list_add_add_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|object_list_add_remove_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|object_list_add_select_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|object_list_add_move_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|object_list_add_geometry_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove_add_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gpointer
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove_select_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gpointer
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove_remove_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gpointer
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove_move_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gpointer
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_list_remove_geometry_cb
parameter_list|(
name|ObjectList_t
modifier|*
name|list
parameter_list|,
name|gpointer
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|object_list_clear_changed (list)
define|#
directive|define
name|object_list_clear_changed
parameter_list|(
name|list
parameter_list|)
value|((list)->changed = FALSE)
end_define

begin_define
DECL|macro|object_list_set_changed (list,ischanged)
define|#
directive|define
name|object_list_set_changed
parameter_list|(
name|list
parameter_list|,
name|ischanged
parameter_list|)
define|\
value|((list)->changed = (ischanged))
end_define

begin_define
DECL|macro|object_list_get_changed (list)
define|#
directive|define
name|object_list_get_changed
parameter_list|(
name|list
parameter_list|)
value|((list)->changed)
end_define

begin_function_decl
name|void
name|clear_paste_buffer
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|paste_buffer_add_add_cb
parameter_list|(
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|paste_buffer_add_remove_cb
parameter_list|(
name|ObjectListCallbackFunc_t
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ObjectList_t
modifier|*
name|get_paste_buffer
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|do_object_locked_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_OBJECT_H */
end_comment

end_unit


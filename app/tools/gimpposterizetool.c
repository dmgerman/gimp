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
file|<math.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_RINT
end_ifndef

begin_define
DECL|macro|rint (x)
define|#
directive|define
name|rint
parameter_list|(
name|x
parameter_list|)
value|floor (x + 0.5)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"actionarea.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"posterize.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
end_include

begin_include
include|#
directive|include
file|"lut_funcs.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|TEXT_WIDTH
define|#
directive|define
name|TEXT_WIDTH
value|55
end_define

begin_comment
comment|/*  the posterize structures  */
end_comment

begin_typedef
DECL|typedef|Posterize
typedef|typedef
name|struct
name|_Posterize
name|Posterize
typedef|;
end_typedef

begin_struct
DECL|struct|_Posterize
struct|struct
name|_Posterize
block|{
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  coords for last mouse click  */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PosterizeDialog
typedef|typedef
name|struct
name|_PosterizeDialog
name|PosterizeDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_PosterizeDialog
struct|struct
name|_PosterizeDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|levels_text
name|GtkWidget
modifier|*
name|levels_text
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
name|image_map
decl_stmt|;
DECL|member|levels
name|int
name|levels
decl_stmt|;
DECL|member|preview
name|gint
name|preview
decl_stmt|;
DECL|member|lut
name|GimpLut
modifier|*
name|lut
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the posterize tool options  */
end_comment

begin_decl_stmt
DECL|variable|posterize_options
specifier|static
name|ToolOptions
modifier|*
name|posterize_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* the posterize tool dialog  */
end_comment

begin_decl_stmt
DECL|variable|posterize_dialog
specifier|static
name|PosterizeDialog
modifier|*
name|posterize_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  posterize action functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|posterize_button_press
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_button_release
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventButton
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_motion
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_cursor_update
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|GdkEventMotion
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_control
parameter_list|(
name|Tool
modifier|*
parameter_list|,
name|ToolAction
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|PosterizeDialog
modifier|*
name|posterize_new_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_preview
parameter_list|(
name|PosterizeDialog
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_preview_update
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|posterize_levels_text_update
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|posterize_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  posterize select action functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|posterize_button_press (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|posterize_button_press
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|gdisp_ptr
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_button_release (Tool * tool,GdkEventButton * bevent,gpointer gdisp_ptr)
name|posterize_button_release
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_motion (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|posterize_motion
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_cursor_update (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|posterize_cursor_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_TOP_LEFT_ARROW
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_control (Tool * tool,ToolAction action,gpointer gdisp_ptr)
name|posterize_control
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|Posterize
modifier|*
name|post
decl_stmt|;
name|post
operator|=
operator|(
name|Posterize
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
break|break;
case|case
name|HALT
case|:
if|if
condition|(
name|posterize_dialog
condition|)
block|{
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|image_map_abort
argument_list|(
name|posterize_dialog
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|posterize_dialog
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|posterize_cancel_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|posterize_dialog
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_posterize ()
name|tools_new_posterize
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|Posterize
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|posterize_options
condition|)
block|{
name|posterize_options
operator|=
name|tool_options_new
argument_list|(
operator|(
literal|"Posterize Options"
operator|)
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|POSTERIZE
argument_list|,
name|posterize_options
argument_list|)
expr_stmt|;
block|}
comment|/*  The posterize dialog  */
if|if
condition|(
operator|!
name|posterize_dialog
condition|)
name|posterize_dialog
operator|=
name|posterize_new_dialog
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|posterize_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|posterize_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|tool
operator|=
operator|(
name|Tool
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Tool
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
operator|(
name|Posterize
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Posterize
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|->
name|type
operator|=
name|POSTERIZE
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
literal|1
expr_stmt|;
comment|/*  Disallow scrolling  */
name|tool
operator|->
name|auto_snap_to
operator|=
name|TRUE
expr_stmt|;
name|tool
operator|->
name|private
operator|=
operator|(
name|void
operator|*
operator|)
name|private
expr_stmt|;
name|tool
operator|->
name|button_press_func
operator|=
name|posterize_button_press
expr_stmt|;
name|tool
operator|->
name|button_release_func
operator|=
name|posterize_button_release
expr_stmt|;
name|tool
operator|->
name|motion_func
operator|=
name|posterize_motion
expr_stmt|;
name|tool
operator|->
name|arrow_keys_func
operator|=
name|standard_arrow_keys_func
expr_stmt|;
name|tool
operator|->
name|modifier_key_func
operator|=
name|standard_modifier_key_func
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|posterize_cursor_update
expr_stmt|;
name|tool
operator|->
name|control_func
operator|=
name|posterize_control
expr_stmt|;
name|tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|tool
operator|->
name|gdisp_ptr
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_posterize (Tool * tool)
name|tools_free_posterize
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|Posterize
modifier|*
name|post
decl_stmt|;
name|post
operator|=
operator|(
name|Posterize
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  Close the color select dialog  */
if|if
condition|(
name|posterize_dialog
condition|)
name|posterize_cancel_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|posterize_dialog
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|post
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|posterize_initialize (GDisplay * gdisp)
name|posterize_initialize
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
name|drawable_indexed
argument_list|(
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Posterize does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  The posterize dialog  */
if|if
condition|(
operator|!
name|posterize_dialog
condition|)
name|posterize_dialog
operator|=
name|posterize_new_dialog
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|posterize_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|posterize_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|posterize_dialog
operator|->
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|posterize_dialog
operator|->
name|image_map
operator|=
name|image_map_create
argument_list|(
name|gdisp
argument_list|,
name|posterize_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|posterize_dialog
operator|->
name|preview
condition|)
name|posterize_preview
argument_list|(
name|posterize_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/****************************/
end_comment

begin_comment
comment|/*  Select by Color dialog  */
end_comment

begin_comment
comment|/****************************/
end_comment

begin_comment
comment|/*  the action area structure  */
end_comment

begin_decl_stmt
DECL|variable|action_items
specifier|static
name|ActionAreaItem
name|action_items
index|[]
init|=
block|{
block|{
name|N_
argument_list|(
literal|"OK"
argument_list|)
block|,
name|posterize_ok_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|N_
argument_list|(
literal|"Cancel"
argument_list|)
block|,
name|posterize_cancel_callback
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|PosterizeDialog
modifier|*
DECL|function|posterize_new_dialog ()
name|posterize_new_dialog
parameter_list|()
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|pd
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|PosterizeDialog
argument_list|)
argument_list|)
expr_stmt|;
name|pd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|pd
operator|->
name|levels
operator|=
literal|3
expr_stmt|;
name|pd
operator|->
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
comment|/*  The shell and main vbox  */
name|pd
operator|->
name|shell
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
argument_list|,
literal|"posterize"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Posterize"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|posterize_delete_callback
argument_list|)
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|vbox
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
name|vbox
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  Horizontal box for levels text widget  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Posterize Levels: "
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/*  levels text  */
name|pd
operator|->
name|levels_text
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|pd
operator|->
name|levels_text
argument_list|)
argument_list|,
literal|"3"
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|pd
operator|->
name|levels_text
argument_list|,
name|TEXT_WIDTH
argument_list|,
literal|25
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|pd
operator|->
name|levels_text
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pd
operator|->
name|levels_text
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|posterize_levels_text_update
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pd
operator|->
name|levels_text
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/*  Horizontal box for preview  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
comment|/*  The preview toggle  */
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|pd
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|posterize_preview_update
argument_list|,
name|pd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/*  The action area  */
name|action_items
index|[
literal|0
index|]
operator|.
name|user_data
operator|=
name|pd
expr_stmt|;
name|action_items
index|[
literal|1
index|]
operator|.
name|user_data
operator|=
name|pd
expr_stmt|;
name|build_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
argument_list|,
name|action_items
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|pd
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_preview (PosterizeDialog * pd)
name|posterize_preview
parameter_list|(
name|PosterizeDialog
modifier|*
name|pd
parameter_list|)
block|{
if|if
condition|(
operator|!
name|pd
operator|->
name|image_map
condition|)
name|g_warning
argument_list|(
literal|"posterize_preview(): No image map"
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|posterize_lut_setup
argument_list|(
name|pd
operator|->
name|lut
argument_list|,
name|pd
operator|->
name|levels
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|pd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|pd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|void
operator|*
operator|)
name|pd
operator|->
name|lut
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_ok_callback (GtkWidget * widget,gpointer client_data)
name|posterize_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|pd
operator|->
name|preview
condition|)
block|{
name|posterize_lut_setup
argument_list|(
name|pd
operator|->
name|lut
argument_list|,
name|pd
operator|->
name|levels
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|pd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|pd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|void
operator|*
operator|)
name|pd
operator|->
name|lut
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pd
operator|->
name|image_map
condition|)
name|image_map_commit
argument_list|(
name|pd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|pd
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|posterize_delete_callback (GtkWidget * w,GdkEvent * e,gpointer data)
name|posterize_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GdkEvent
modifier|*
name|e
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|posterize_cancel_callback
argument_list|(
name|w
argument_list|,
name|data
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
DECL|function|posterize_cancel_callback (GtkWidget * widget,gpointer client_data)
name|posterize_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|client_data
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|pd
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|pd
operator|->
name|image_map
condition|)
block|{
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|image_map_abort
argument_list|(
name|pd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
name|pd
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_preview_update (GtkWidget * w,gpointer data)
name|posterize_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|w
argument_list|)
operator|->
name|active
condition|)
block|{
name|pd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|posterize_preview
argument_list|(
name|pd
argument_list|)
expr_stmt|;
block|}
else|else
name|pd
operator|->
name|preview
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|posterize_levels_text_update (GtkWidget * w,gpointer data)
name|posterize_levels_text_update
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PosterizeDialog
modifier|*
name|pd
decl_stmt|;
name|char
modifier|*
name|str
decl_stmt|;
name|int
name|value
decl_stmt|;
name|pd
operator|=
operator|(
name|PosterizeDialog
operator|*
operator|)
name|data
expr_stmt|;
name|str
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|w
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
name|BOUNDS
argument_list|(
operator|(
operator|(
name|int
operator|)
name|atof
argument_list|(
name|str
argument_list|)
operator|)
argument_list|,
literal|2
argument_list|,
literal|256
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|pd
operator|->
name|levels
condition|)
block|{
name|pd
operator|->
name|levels
operator|=
name|value
expr_stmt|;
if|if
condition|(
name|pd
operator|->
name|preview
condition|)
name|posterize_preview
argument_list|(
name|pd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


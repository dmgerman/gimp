begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* docindex.c - Creates the window used by the document index in go and gimp.  *  * Copyright (C) 1998 Chris Lahey.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
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
file|"docindexif.h"
end_include

begin_include
include|#
directive|include
file|"docindex.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpenv.h"
end_include

begin_decl_stmt
DECL|variable|ideas
name|idea_manager
modifier|*
name|ideas
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|idea_list
specifier|static
name|GList
modifier|*
name|idea_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|idea_list
comment|/* of gchar *. */
end_comment

begin_decl_stmt
DECL|variable|x
DECL|variable|y
DECL|variable|width
DECL|variable|height
specifier|static
name|gint
name|x
init|=
literal|0
decl_stmt|,
name|y
init|=
literal|0
decl_stmt|,
name|width
init|=
literal|0
decl_stmt|,
name|height
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_enum
DECL|enum|__anon2bf68c020103
enum|enum
block|{
DECL|enumerator|TARGET_URI_LIST
name|TARGET_URI_LIST
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|create_idea_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|docindex_configure_drop_on_widget
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|docindex_cell_configure_drop_on_widget
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|docindex_dnd_filenames_dropped (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection_data,guint info,guint time)
name|docindex_dnd_filenames_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection_data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gint
name|len
decl_stmt|;
name|gchar
modifier|*
name|data
decl_stmt|;
name|gchar
modifier|*
name|end
decl_stmt|;
switch|switch
condition|(
name|info
condition|)
block|{
case|case
name|TARGET_URI_LIST
case|:
name|data
operator|=
operator|(
name|gchar
operator|*
operator|)
name|selection_data
operator|->
name|data
expr_stmt|;
name|len
operator|=
name|selection_data
operator|->
name|length
expr_stmt|;
while|while
condition|(
name|len
operator|>
literal|0
condition|)
block|{
name|end
operator|=
name|strstr
argument_list|(
name|data
argument_list|,
literal|"\x0D\x0A"
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|!=
name|NULL
condition|)
operator|*
name|end
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|*
name|data
operator|!=
literal|'#'
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|strchr
argument_list|(
name|data
argument_list|,
literal|':'
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
operator|!=
name|NULL
condition|)
name|filename
operator|++
expr_stmt|;
else|else
name|filename
operator|=
name|data
expr_stmt|;
name|open_file_in_position
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|end
condition|)
block|{
name|len
operator|-=
name|end
operator|-
name|data
operator|+
literal|2
expr_stmt|;
name|data
operator|=
name|end
operator|+
literal|2
expr_stmt|;
block|}
else|else
name|len
operator|=
literal|0
expr_stmt|;
block|}
break|break;
block|}
return|return;
block|}
end_function

begin_function
name|void
DECL|function|docindex_configure_drop_on_widget (GtkWidget * widget)
name|docindex_configure_drop_on_widget
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
specifier|static
name|GtkTargetEntry
name|drag_types
index|[]
init|=
block|{
block|{
literal|"text/uri-list"
block|,
literal|0
block|,
name|TARGET_URI_LIST
block|}
block|,   }
decl_stmt|;
specifier|static
name|gint
name|n_drag_types
init|=
sizeof|sizeof
argument_list|(
name|drag_types
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|drag_types
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|widget
argument_list|,
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|drag_types
argument_list|,
name|n_drag_types
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"drag_data_received"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|docindex_dnd_filenames_dropped
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|docindex_cell_dnd_filenames_dropped (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection_data,guint info,guint time)
name|docindex_cell_dnd_filenames_dropped
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection_data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gint
name|len
decl_stmt|;
name|gchar
modifier|*
name|data
decl_stmt|;
name|gchar
modifier|*
name|end
decl_stmt|;
name|gint
name|position
init|=
name|g_list_index
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|,
name|widget
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|info
condition|)
block|{
case|case
name|TARGET_URI_LIST
case|:
name|data
operator|=
operator|(
name|gchar
operator|*
operator|)
name|selection_data
operator|->
name|data
expr_stmt|;
name|len
operator|=
name|selection_data
operator|->
name|length
expr_stmt|;
while|while
condition|(
name|len
operator|>
literal|0
condition|)
block|{
name|end
operator|=
name|strstr
argument_list|(
name|data
argument_list|,
literal|"\x0D\x0A"
argument_list|)
expr_stmt|;
if|if
condition|(
name|end
operator|!=
name|NULL
condition|)
operator|*
name|end
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|*
name|data
operator|!=
literal|'#'
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|strchr
argument_list|(
name|data
argument_list|,
literal|':'
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
operator|!=
name|NULL
condition|)
name|filename
operator|++
expr_stmt|;
else|else
name|filename
operator|=
name|data
expr_stmt|;
name|open_file_in_position
argument_list|(
name|filename
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|end
condition|)
block|{
name|len
operator|-=
name|end
operator|-
name|data
operator|+
literal|2
expr_stmt|;
name|data
operator|=
name|end
operator|+
literal|2
expr_stmt|;
block|}
else|else
name|len
operator|=
literal|0
expr_stmt|;
block|}
break|break;
block|}
return|return;
block|}
end_function

begin_function
name|void
DECL|function|docindex_cell_configure_drop_on_widget (GtkWidget * widget)
name|docindex_cell_configure_drop_on_widget
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
specifier|static
name|GtkTargetEntry
name|drag_types
index|[]
init|=
block|{
block|{
literal|"text/uri-list"
block|,
literal|0
block|,
name|TARGET_URI_LIST
block|}
block|,   }
decl_stmt|;
specifier|static
name|gint
name|n_drag_types
init|=
sizeof|sizeof
argument_list|(
name|drag_types
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|drag_types
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|widget
argument_list|,
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|drag_types
argument_list|,
name|n_drag_types
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"drag_data_received"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|docindex_cell_dnd_filenames_dropped
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|idea_window_delete_event_callback (GtkWidget * widget,GdkEvent * event,gpointer data)
name|idea_window_delete_event_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|exit_from_go
argument_list|()
condition|)
block|{
name|save_idea_manager
argument_list|(
name|ideas
argument_list|)
expr_stmt|;
name|create_idea_list
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|ideas
argument_list|)
expr_stmt|;
name|ideas
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|idea_hide_callback (GtkWidget * widget,gpointer data)
name|idea_hide_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|ideas
operator|||
name|idea_list
operator|||
name|width
operator|||
name|height
condition|)
name|save_idea_manager
argument_list|(
name|ideas
argument_list|)
expr_stmt|;
comment|/* False if exitting */
if|if
condition|(
operator|(
operator|!
name|exit_from_go
argument_list|()
operator|)
operator|&&
name|ideas
condition|)
block|{
name|create_idea_list
argument_list|()
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ideas
argument_list|)
expr_stmt|;
name|ideas
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|open_idea_window (void)
name|open_idea_window
parameter_list|(
name|void
parameter_list|)
block|{
name|make_idea_window
argument_list|(
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|load_from_list (gpointer data,gpointer data_null)
name|load_from_list
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|data_null
parameter_list|)
block|{
name|idea_add_in_position
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|data
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|FILE
modifier|*
DECL|function|idea_manager_parse_init (int * window_x,int * window_y,int * window_width,int * window_height)
name|idea_manager_parse_init
parameter_list|(
comment|/* RETURNS: */
name|int
modifier|*
name|window_x
parameter_list|,
name|int
modifier|*
name|window_y
parameter_list|,
name|int
modifier|*
name|window_width
parameter_list|,
name|int
modifier|*
name|window_height
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|desktopfile
decl_stmt|;
name|desktopfile
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"ideas"
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|desktopfile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desktopfile
argument_list|)
expr_stmt|;
comment|/* Read in persistant desktop information. */
if|if
condition|(
name|fp
condition|)
block|{
operator|*
name|window_x
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
operator|*
name|window_y
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
operator|*
name|window_width
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
operator|*
name|window_height
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
return|return
name|fp
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|idea_manager_parse_line (FILE * fp)
name|idea_manager_parse_line
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|)
block|{
name|int
name|length
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|length
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|feof
argument_list|(
name|fp
argument_list|)
operator|&&
operator|!
name|ferror
argument_list|(
name|fp
argument_list|)
condition|)
block|{
name|filename
operator|=
name|g_malloc0
argument_list|(
name|length
operator|+
literal|1
argument_list|)
expr_stmt|;
name|filename
index|[
name|fread
argument_list|(
name|filename
argument_list|,
literal|1
argument_list|,
name|length
argument_list|,
name|fp
argument_list|)
index|]
operator|=
literal|0
expr_stmt|;
name|clear_white
argument_list|(
name|fp
argument_list|)
expr_stmt|;
return|return
name|filename
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|load_idea_manager (idea_manager * ideas)
name|load_idea_manager
parameter_list|(
name|idea_manager
modifier|*
name|ideas
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|idea_list
condition|)
name|fp
operator|=
name|idea_manager_parse_init
argument_list|(
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|idea_list
operator|||
name|fp
condition|)
block|{
name|gtk_widget_set_usize
argument_list|(
name|ideas
operator|->
name|window
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
expr_stmt|;
name|gtk_widget_set_uposition
argument_list|(
name|ideas
operator|->
name|window
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gtk_idle_add
argument_list|(
name|reset_usize
argument_list|,
name|ideas
operator|->
name|window
argument_list|)
expr_stmt|;
if|if
condition|(
name|fp
condition|)
block|{
name|gchar
modifier|*
name|title
decl_stmt|;
name|clear_white
argument_list|(
name|fp
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|title
operator|=
name|idea_manager_parse_line
argument_list|(
name|fp
argument_list|)
operator|)
condition|)
block|{
name|idea_add_in_position
argument_list|(
name|title
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_list_foreach
argument_list|(
name|idea_list
argument_list|,
name|load_from_list
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|idea_list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|idea_list
argument_list|)
expr_stmt|;
name|idea_list
operator|=
literal|0
expr_stmt|;
block|}
block|}
else|else
name|gtk_widget_show
argument_list|(
name|ideas
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|save_to_ideas (gpointer data,gpointer user_data)
name|save_to_ideas
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gchar
modifier|*
name|title
init|=
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|data
argument_list|)
operator|->
name|child
argument_list|)
operator|->
name|label
decl_stmt|;
name|fprintf
argument_list|(
operator|(
name|FILE
operator|*
operator|)
name|user_data
argument_list|,
literal|"%d %s\n"
argument_list|,
name|strlen
argument_list|(
name|title
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|save_list_to_ideas (gpointer data,gpointer user_data)
name|save_list_to_ideas
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gchar
modifier|*
name|title
init|=
operator|(
name|gchar
operator|*
operator|)
name|data
decl_stmt|;
name|fprintf
argument_list|(
operator|(
name|FILE
operator|*
operator|)
name|user_data
argument_list|,
literal|"%d %s\n"
argument_list|,
name|strlen
argument_list|(
name|title
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|save_idea_manager (idea_manager * ideas)
name|save_idea_manager
parameter_list|(
name|idea_manager
modifier|*
name|ideas
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gchar
modifier|*
name|desktopfile
decl_stmt|;
comment|/* open persistant desktop file. */
name|desktopfile
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"ideas"
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|desktopfile
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desktopfile
argument_list|)
expr_stmt|;
if|if
condition|(
name|fp
condition|)
block|{
if|if
condition|(
name|ideas
condition|)
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdk_window_get_geometry
argument_list|(
name|ideas
operator|->
name|window
operator|->
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_get_origin
argument_list|(
name|ideas
operator|->
name|window
operator|->
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%d %d %d %d\n"
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|,
name|save_to_ideas
argument_list|,
name|fp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|idea_list
condition|)
block|{
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%d %d %d %d\n"
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|idea_list
argument_list|,
name|save_list_to_ideas
argument_list|,
name|fp
argument_list|)
expr_stmt|;
block|}
block|}
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|save_to_list (gpointer data,gpointer null_data)
name|save_to_list
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|null_data
parameter_list|)
block|{
name|gchar
modifier|*
name|title
init|=
name|g_strdup
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
operator|(
name|GtkWidget
operator|*
operator|)
name|data
argument_list|)
operator|->
name|child
argument_list|)
operator|->
name|label
argument_list|)
decl_stmt|;
name|idea_list
operator|=
name|g_list_append
argument_list|(
name|idea_list
argument_list|,
name|title
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|create_idea_list (void)
name|create_idea_list
parameter_list|(
name|void
parameter_list|)
block|{
name|gdk_window_get_geometry
argument_list|(
name|ideas
operator|->
name|window
operator|->
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_get_origin
argument_list|(
name|ideas
operator|->
name|window
operator|->
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|idea_list
condition|)
block|{
name|g_list_foreach
argument_list|(
name|idea_list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|idea_list
argument_list|)
expr_stmt|;
name|idea_list
operator|=
literal|0
expr_stmt|;
block|}
name|g_list_foreach
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|,
name|save_to_list
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|open_or_raise_callback (GtkWidget * widget,GdkEventButton * event,gpointer func_data)
name|open_or_raise_callback
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
name|func_data
parameter_list|)
block|{
if|if
condition|(
name|GTK_IS_TREE_ITEM
argument_list|(
name|widget
argument_list|)
operator|&&
name|event
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
condition|)
block|{
name|open_or_raise
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
operator|->
name|child
argument_list|)
operator|->
name|label
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
DECL|function|raise_idea_callback (GtkWidget * widget,gpointer data)
name|void
name|raise_idea_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|ideas
condition|)
name|gdk_window_raise
argument_list|(
name|ideas
operator|->
name|window
operator|->
name|window
argument_list|)
expr_stmt|;
else|else
name|open_idea_window
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
DECL|function|check_needed (gpointer data,gpointer user_data)
specifier|static
name|void
name|check_needed
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
operator|(
name|GtkWidget
operator|*
operator|)
name|data
decl_stmt|;
name|struct
name|bool_char_pair
modifier|*
name|pair
init|=
operator|(
expr|struct
name|bool_char_pair
operator|*
operator|)
name|user_data
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|pair
operator|->
name|string
argument_list|,
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
operator|->
name|child
argument_list|)
operator|->
name|label
argument_list|)
operator|==
literal|0
condition|)
block|{
name|pair
operator|->
name|boole
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|check_needed_list (gpointer data,gpointer user_data)
specifier|static
name|void
name|check_needed_list
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|struct
name|bool_char_pair
modifier|*
name|pair
init|=
operator|(
expr|struct
name|bool_char_pair
operator|*
operator|)
name|user_data
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|pair
operator|->
name|string
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|data
argument_list|)
operator|==
literal|0
condition|)
block|{
name|pair
operator|->
name|boole
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|idea_add (gchar * title)
name|void
name|idea_add
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|idea_add_in_position
argument_list|(
name|title
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|idea_add_in_position_with_select (gchar * title,gint position,gboolean select)
specifier|static
name|void
name|idea_add_in_position_with_select
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|position
parameter_list|,
name|gboolean
name|select
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|treeitem
decl_stmt|;
name|struct
name|bool_char_pair
name|pair
decl_stmt|;
name|pair
operator|.
name|boole
operator|=
name|FALSE
expr_stmt|;
name|pair
operator|.
name|string
operator|=
name|title
expr_stmt|;
if|if
condition|(
name|ideas
condition|)
block|{
name|g_list_foreach
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|,
name|check_needed
argument_list|,
operator|&
name|pair
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pair
operator|.
name|boole
condition|)
block|{
name|treeitem
operator|=
name|gtk_tree_item_new_with_label
argument_list|(
name|title
argument_list|)
expr_stmt|;
if|if
condition|(
name|position
operator|<
literal|0
condition|)
name|gtk_tree_append
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|treeitem
argument_list|)
expr_stmt|;
else|else
name|gtk_tree_insert
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|treeitem
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|treeitem
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|open_or_raise_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|docindex_cell_configure_drop_on_widget
argument_list|(
name|treeitem
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|treeitem
argument_list|)
expr_stmt|;
if|if
condition|(
name|select
condition|)
name|gtk_tree_select_item
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|gtk_tree_child_position
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|treeitem
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
operator|!
name|idea_list
condition|)
block|{
name|FILE
modifier|*
name|fp
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|desktopfile
decl_stmt|;
comment|/* open persistant desktop file. */
name|desktopfile
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"ideas"
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|desktopfile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desktopfile
argument_list|)
expr_stmt|;
comment|/* Read in persistant desktop information. */
if|if
condition|(
name|fp
condition|)
block|{
name|gchar
modifier|*
name|title
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|x
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|y
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|width
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|height
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|clear_white
argument_list|(
name|fp
argument_list|)
expr_stmt|;
while|while
condition|(
operator|!
name|feof
argument_list|(
name|fp
argument_list|)
operator|&&
operator|!
name|ferror
argument_list|(
name|fp
argument_list|)
condition|)
block|{
name|length
operator|=
name|getinteger
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|title
operator|=
name|g_malloc0
argument_list|(
name|length
operator|+
literal|1
argument_list|)
expr_stmt|;
name|title
index|[
name|fread
argument_list|(
name|title
argument_list|,
literal|1
argument_list|,
name|length
argument_list|,
name|fp
argument_list|)
index|]
operator|=
literal|0
expr_stmt|;
name|idea_list
operator|=
name|g_list_append
argument_list|(
name|idea_list
argument_list|,
name|g_strdup
argument_list|(
name|title
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|clear_white
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
block|}
name|g_list_foreach
argument_list|(
name|idea_list
argument_list|,
name|check_needed_list
argument_list|,
operator|&
name|pair
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pair
operator|.
name|boole
condition|)
block|{
if|if
condition|(
name|position
operator|<
literal|0
condition|)
name|idea_list
operator|=
name|g_list_append
argument_list|(
name|idea_list
argument_list|,
name|g_strdup
argument_list|(
name|title
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|idea_list
operator|=
name|g_list_insert
argument_list|(
name|idea_list
argument_list|,
name|g_strdup
argument_list|(
name|title
argument_list|)
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
DECL|function|idea_add_in_position (gchar * title,gint position)
name|void
name|idea_add_in_position
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|position
parameter_list|)
block|{
name|idea_add_in_position_with_select
argument_list|(
name|title
argument_list|,
name|position
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|idea_move (GtkWidget * widget,gint distance,gboolean select)
specifier|static
name|gint
name|idea_move
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|distance
parameter_list|,
name|gboolean
name|select
parameter_list|)
block|{
name|gint
name|orig_position
init|=
name|g_list_index
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|,
name|widget
argument_list|)
decl_stmt|;
name|gint
name|position
init|=
name|orig_position
operator|+
name|distance
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
if|if
condition|(
name|position
operator|<
literal|0
condition|)
name|position
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|position
operator|>=
name|g_list_length
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|)
condition|)
name|position
operator|=
name|g_list_length
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|)
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|position
operator|!=
name|orig_position
condition|)
block|{
name|title
operator|=
name|g_strdup
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
operator|->
name|child
argument_list|)
operator|->
name|label
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|idea_add_in_position_with_select
argument_list|(
name|title
argument_list|,
name|position
argument_list|,
name|select
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
return|return
name|position
operator|-
name|orig_position
return|;
block|}
end_function

begin_function
DECL|function|idea_remove (GtkWidget * widget)
specifier|static
name|void
name|idea_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gint
name|position
init|=
name|g_list_index
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|,
name|widget
argument_list|)
decl_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_length
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|)
operator|-
literal|1
operator|<
name|position
condition|)
name|position
operator|=
name|g_list_length
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|children
argument_list|)
operator|-
literal|1
expr_stmt|;
name|gtk_tree_select_item
argument_list|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
argument_list|,
name|position
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|idea_up_callback (GtkWidget * widget,gpointer data)
name|void
name|idea_up_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|selected
decl_stmt|;
if|if
condition|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|selection
condition|)
block|{
name|selected
operator|=
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|selection
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|idea_move
argument_list|(
name|selected
argument_list|,
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|)
operator|!=
operator|-
literal|1
condition|)
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
argument_list|,
name|ideas
operator|->
name|contextid
argument_list|,
name|_
argument_list|(
literal|"This file cannot be moved up."
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
argument_list|,
name|ideas
operator|->
name|contextid
argument_list|,
name|_
argument_list|(
literal|"There's no selection to move up."
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|idea_down_callback (GtkWidget * widget,gpointer data)
name|void
name|idea_down_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|selected
decl_stmt|;
if|if
condition|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|selection
condition|)
block|{
name|selected
operator|=
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|selection
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|idea_move
argument_list|(
name|selected
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
operator|!=
literal|1
condition|)
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
argument_list|,
name|ideas
operator|->
name|contextid
argument_list|,
name|_
argument_list|(
literal|"This file cannot be moved down."
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
argument_list|,
name|ideas
operator|->
name|contextid
argument_list|,
name|_
argument_list|(
literal|"There's no selection to move down."
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|idea_remove_callback (GtkWidget * widget,gpointer data)
name|void
name|idea_remove_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|selected
decl_stmt|;
if|if
condition|(
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|selection
condition|)
block|{
name|selected
operator|=
name|GTK_TREE
argument_list|(
name|ideas
operator|->
name|tree
argument_list|)
operator|->
name|selection
operator|->
name|data
expr_stmt|;
name|idea_remove
argument_list|(
name|selected
argument_list|)
expr_stmt|;
block|}
else|else
name|gtk_statusbar_push
argument_list|(
name|GTK_STATUSBAR
argument_list|(
name|ideas
operator|->
name|status
argument_list|)
argument_list|,
name|ideas
operator|->
name|contextid
argument_list|,
name|_
argument_list|(
literal|"There's no selection to remove."
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|close_idea_window (void)
name|close_idea_window
parameter_list|(
name|void
parameter_list|)
block|{
name|idea_hide_callback
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


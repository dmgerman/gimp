begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *   * gimp-remote.c  * Copyright (C) 2000-2003  Sven Neumann<sven@gimp.org>  *                          Simon Budig<simon@gimp.org>  *  * Tells a running gimp to open files by creating a synthetic drop-event.  *  * compile with  *  gcc -o gimp-remote `pkg-config --cflags --libs gtk+-2.0` -lXmu gimp-remote.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Disclaimer:  *  * It is a really bad idea to use Drag'n'Drop for inter-client  * communication. Dont even think about doing this in your own newly  * created application. We do this *only*, because we are in a  * feature freeze for Gimp 1.2 and adding a completely new communication  * infrastructure for remote controlling Gimp is definitely a new  * feature...  * Think about sockets or Corba when you want to do something similiar.  * We definitely consider this for Gimp 2.0.  *                                                Simon  */
end_comment

begin_comment
comment|/* TODO:  *  * Should try to execv the gimp in the same path as the gimp-remote  * executable, then fall back to execvp ("gimp", argv).  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

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
file|<X11/Xmu/WinUtil.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkx.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpversion.h"
end_include

begin_decl_stmt
DECL|variable|start_new
specifier|static
name|gboolean
name|start_new
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GdkWindow
modifier|*
DECL|function|gimp_remote_find_window (void)
name|gimp_remote_find_window
parameter_list|(
name|void
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|result
init|=
name|NULL
decl_stmt|;
name|Window
name|root
decl_stmt|,
name|parent
decl_stmt|;
name|Window
modifier|*
name|children
decl_stmt|;
name|Atom
name|class_atom
decl_stmt|;
name|Atom
name|string_atom
decl_stmt|;
name|guint
name|nchildren
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|XQueryTree
argument_list|(
name|gdk_display
argument_list|,
name|gdk_x11_get_default_root_xwindow
argument_list|()
argument_list|,
operator|&
name|root
argument_list|,
operator|&
name|parent
argument_list|,
operator|&
name|children
argument_list|,
operator|&
name|nchildren
argument_list|)
operator|==
literal|0
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|!
operator|(
name|children
operator|&&
name|nchildren
operator|)
condition|)
return|return
name|NULL
return|;
name|class_atom
operator|=
name|XInternAtom
argument_list|(
name|gdk_display
argument_list|,
literal|"WM_CLASS"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|string_atom
operator|=
name|XInternAtom
argument_list|(
name|gdk_display
argument_list|,
literal|"STRING"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|nchildren
operator|-
literal|1
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
block|{
name|Window
name|window
decl_stmt|;
name|Atom
name|ret_type
decl_stmt|;
name|gint
name|ret_format
decl_stmt|;
name|gulong
name|bytes_after
decl_stmt|;
name|gulong
name|nitems
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/*  The XmuClientWindow() function finds a window at or below the        *  specified window, that has a WM_STATE property. If such a        *  window is found, it is returned; otherwise the argument window        *  is returned.        */
name|window
operator|=
name|XmuClientWindow
argument_list|(
name|gdk_display
argument_list|,
name|children
index|[
name|i
index|]
argument_list|)
expr_stmt|;
comment|/*  We are searching the Gimp toolbox: Its WM_CLASS Property        *  has the values "toolbox\0Gimp\0". This is pretty relieable,        *  it is more reliable when we ask a special property, explicitely        *  set from the gimp. See below... :-)        */
if|if
condition|(
name|XGetWindowProperty
argument_list|(
name|gdk_display
argument_list|,
name|window
argument_list|,
name|class_atom
argument_list|,
literal|0
argument_list|,
literal|32
argument_list|,
name|FALSE
argument_list|,
name|string_atom
argument_list|,
operator|&
name|ret_type
argument_list|,
operator|&
name|ret_format
argument_list|,
operator|&
name|nitems
argument_list|,
operator|&
name|bytes_after
argument_list|,
operator|&
name|data
argument_list|)
operator|==
name|Success
operator|&&
name|ret_type
condition|)
block|{
if|if
condition|(
name|nitems
operator|>
literal|12
operator|&&
name|strcmp
argument_list|(
name|data
argument_list|,
literal|"toolbox"
argument_list|)
operator|==
literal|0
operator|&&
name|strcmp
argument_list|(
name|data
operator|+
literal|8
argument_list|,
literal|"Gimp"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|XFree
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|result
operator|=
name|gdk_window_foreign_new
argument_list|(
name|window
argument_list|)
expr_stmt|;
break|break;
block|}
name|XFree
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
block|}
name|XFree
argument_list|(
name|children
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|source_selection_get (GtkWidget * widget,GtkSelectionData * selection_data,guint info,guint time,gpointer data)
name|source_selection_get
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
init|=
operator|(
name|gchar
operator|*
operator|)
name|data
decl_stmt|;
name|gtk_selection_data_set
argument_list|(
name|selection_data
argument_list|,
name|selection_data
operator|->
name|target
argument_list|,
literal|8
argument_list|,
name|uri
argument_list|,
name|strlen
argument_list|(
name|uri
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|toolbox_hidden (gpointer data)
name|toolbox_hidden
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|g_printerr
argument_list|(
literal|"Could not connect to the Gimp.\n"
literal|"Make sure that the Toolbox is visible!\n"
argument_list|)
expr_stmt|;
name|gtk_main_quit
argument_list|()
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|usage (const gchar * name)
name|usage
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"gimp-remote version %s\n\n"
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"Tells a running Gimp to open a (local or remote) image file.\n\n"
literal|"Usage: %s [options] [FILE|URI]...\n\n"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"Valid options are:\n"
literal|"  -h --help       Output this help.\n"
literal|"  -v --version    Output version info.\n"
literal|"  -n --new        Start gimp if no active gimp window was found.\n\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"Example:  %s http://www.gimp.org/icons/frontpage-small.gif\n"
literal|"     or:  %s localfile.png\n\n"
argument_list|,
name|name
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|start_new_gimp (GString * file_list)
name|start_new_gimp
parameter_list|(
name|GString
modifier|*
name|file_list
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|file_list
operator|=
name|g_string_prepend
argument_list|(
name|file_list
argument_list|,
literal|"gimp\n"
argument_list|)
expr_stmt|;
name|argv
operator|=
name|g_strsplit
argument_list|(
name|file_list
operator|->
name|str
argument_list|,
literal|"\n"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|file_list
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|argv
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_ascii_strncasecmp
argument_list|(
literal|"file:"
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|,
literal|5
argument_list|)
operator|==
literal|0
condition|)
name|argv
index|[
name|i
index|]
operator|+=
literal|5
expr_stmt|;
block|}
name|execvp
argument_list|(
literal|"gimp-1.3"
argument_list|,
name|argv
argument_list|)
expr_stmt|;
comment|/*  if execvp returns, there was an arror  */
name|g_printerr
argument_list|(
literal|"Couldn't start gimp-1.3 for the following reason: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|exit
argument_list|(
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parse_option (const gchar * progname,const gchar * arg)
name|parse_option
parameter_list|(
specifier|const
name|gchar
modifier|*
name|progname
parameter_list|,
specifier|const
name|gchar
modifier|*
name|arg
parameter_list|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-v"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--version"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_print
argument_list|(
literal|"gimp-remote version %s\n"
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-h"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-?"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--help"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--usage"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|usage
argument_list|(
name|progname
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-n"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--new"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|start_new
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"Unknown option %s\n"
argument_list|,
name|arg
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"Try gimp-remote --help to get detailed usage instructions.\n"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|main (gint argc,gchar ** argv)
name|main
parameter_list|(
name|gint
name|argc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|source
decl_stmt|;
name|GdkWindow
modifier|*
name|gimp_window
decl_stmt|;
name|GdkDragContext
modifier|*
name|context
decl_stmt|;
name|GdkDragProtocol
name|protocol
decl_stmt|;
name|GdkAtom
name|sel_type
decl_stmt|;
name|GdkAtom
name|sel_id
decl_stmt|;
name|GList
modifier|*
name|targetlist
decl_stmt|;
name|guint
name|timeout
decl_stmt|;
name|gboolean
name|options
init|=
name|TRUE
decl_stmt|;
name|GString
modifier|*
name|file_list
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|cwd
init|=
name|g_get_current_dir
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|file_uri
init|=
literal|""
decl_stmt|;
name|guint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|argc
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|strlen
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|)
operator|==
literal|0
condition|)
continue|continue;
if|if
condition|(
name|options
operator|&&
operator|*
name|argv
index|[
name|i
index|]
operator|==
literal|'-'
condition|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--"
argument_list|)
condition|)
block|{
name|parse_option
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|)
expr_stmt|;
continue|continue;
block|}
else|else
block|{
comment|/*  everything following a -- is interpreted as arguments  */
name|options
operator|=
name|FALSE
expr_stmt|;
continue|continue;
block|}
block|}
comment|/* If not already a valid URI */
if|if
condition|(
name|g_ascii_strncasecmp
argument_list|(
literal|"file:"
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|,
literal|5
argument_list|)
operator|&&
name|g_ascii_strncasecmp
argument_list|(
literal|"ftp:"
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|,
literal|4
argument_list|)
operator|&&
name|g_ascii_strncasecmp
argument_list|(
literal|"http:"
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|,
literal|5
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_path_is_absolute
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|)
condition|)
name|file_uri
operator|=
name|g_strconcat
argument_list|(
literal|"file:"
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|file_uri
operator|=
name|g_strconcat
argument_list|(
literal|"file:"
argument_list|,
name|cwd
argument_list|,
literal|"/"
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
name|file_uri
operator|=
name|g_strdup
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_list
operator|->
name|len
operator|>
literal|0
condition|)
name|file_list
operator|=
name|g_string_append_c
argument_list|(
name|file_list
argument_list|,
literal|'\n'
argument_list|)
expr_stmt|;
name|file_list
operator|=
name|g_string_append
argument_list|(
name|file_list
argument_list|,
name|file_uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|file_uri
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|file_list
operator|->
name|len
operator|==
literal|0
condition|)
block|{
name|usage
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
comment|/*  locate Gimp window */
name|gimp_window
operator|=
name|gimp_remote_find_window
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_window
condition|)
block|{
if|if
condition|(
name|start_new
condition|)
name|start_new_gimp
argument_list|(
name|file_list
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"No gimp window found on display %s\n"
argument_list|,
name|gdk_get_display
argument_list|()
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
name|gdk_drag_get_protocol
argument_list|(
name|GDK_WINDOW_XID
argument_list|(
name|gimp_window
argument_list|)
argument_list|,
operator|&
name|protocol
argument_list|)
expr_stmt|;
if|if
condition|(
name|protocol
operator|!=
name|GDK_DRAG_PROTO_XDND
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Gimp Window doesnt use Xdnd-Protocol - huh?\n"
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
comment|/*  Problem: If the Toolbox is hidden via Tab (gtk_widget_hide)    *  it does not accept DnD-Operations and gtk_main() will not be    *  terminated. If the Toolbox is simply unmapped (by the Windowmanager)    *  DnD works. But in both cases gdk_window_is_visible () == 0.... :-(     *  To work around this add a timeout and abort after 1.5 seconds.    */
name|timeout
operator|=
name|g_timeout_add
argument_list|(
literal|1500
argument_list|,
name|toolbox_hidden
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  set up an DND-source  */
name|source
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_TOPLEVEL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|source
argument_list|,
literal|"selection_get"
argument_list|,
name|G_CALLBACK
argument_list|(
name|source_selection_get
argument_list|)
argument_list|,
name|file_list
operator|->
name|str
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|source
argument_list|)
expr_stmt|;
comment|/*  specify the id and the content-type of the selection used to    *  pass the URIs to Gimp.    */
name|sel_id
operator|=
name|gdk_atom_intern
argument_list|(
literal|"XdndSelection"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|sel_type
operator|=
name|gdk_atom_intern
argument_list|(
literal|"text/uri-list"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|targetlist
operator|=
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|sel_type
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  assign the selection to our DnD-source  */
name|gtk_selection_owner_set
argument_list|(
name|source
argument_list|,
name|sel_id
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
name|gtk_selection_add_target
argument_list|(
name|source
argument_list|,
name|sel_id
argument_list|,
name|sel_type
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  drag_begin/motion/drop  */
name|context
operator|=
name|gdk_drag_begin
argument_list|(
name|source
operator|->
name|window
argument_list|,
name|targetlist
argument_list|)
expr_stmt|;
name|gdk_drag_motion
argument_list|(
name|context
argument_list|,
name|gimp_window
argument_list|,
name|protocol
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GDK_ACTION_COPY
argument_list|,
name|GDK_ACTION_COPY
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
name|gdk_drag_drop
argument_list|(
name|context
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
comment|/*  finally enter the mainloop to handle the events  */
name|gtk_main
argument_list|()
expr_stmt|;
name|g_source_remove
argument_list|(
name|timeout
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|file_list
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * test-clipboard.c -- do clipboard things  *  * Copyright (C) 2005  Michael Natterer<mitch@gimp.org>  *  * Use this code for whatever you like.  */
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
file|<fcntl.h>
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_typedef
DECL|typedef|CopyData
typedef|typedef
name|struct
name|_CopyData
name|CopyData
typedef|;
end_typedef

begin_struct
DECL|struct|_CopyData
struct|struct
name|_CopyData
block|{
DECL|member|filename
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|file_copied
name|gboolean
name|file_copied
decl_stmt|;
DECL|member|error
name|GError
modifier|*
name|error
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|static
name|void
name|test_clipboard_show_version
argument_list|(
name|void
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|gboolean
name|test_clipboard_parse_selection
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|test_clipboard_list_targets
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|test_clipboard_copy
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|test_clipboard_store
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|test_clipboard_paste
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|test_clipboard_copy_callback
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|option_selection_type
specifier|static
name|GdkAtom
name|option_selection_type
init|=
name|GDK_SELECTION_CLIPBOARD
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|option_list_targets
specifier|static
name|gboolean
name|option_list_targets
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|option_target
specifier|static
name|gchar
modifier|*
name|option_target
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|option_copy_filename
specifier|static
name|gchar
modifier|*
name|option_copy_filename
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|option_store_filename
specifier|static
name|gchar
modifier|*
name|option_store_filename
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|option_paste_filename
specifier|static
name|gchar
modifier|*
name|option_paste_filename
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|main_entries
specifier|static
specifier|const
name|GOptionEntry
name|main_entries
index|[]
init|=
block|{
block|{
literal|"selection-type"
block|,
literal|'s'
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|test_clipboard_parse_selection
block|,
literal|"Selection type (primary|secondary|clipboard)"
block|,
literal|"<type>"
block|}
block|,
block|{
literal|"list-targets"
block|,
literal|'l'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|option_list_targets
block|,
literal|"List the targets offered by the clipboard"
block|,
name|NULL
block|}
block|,
block|{
literal|"target"
block|,
literal|'t'
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING
block|,
operator|&
name|option_target
block|,
literal|"The target format to copy or paste"
block|,
literal|"<target>"
block|}
block|,
block|{
literal|"copy"
block|,
literal|'c'
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING
block|,
operator|&
name|option_copy_filename
block|,
literal|"Copy<file> to clipboard"
block|,
literal|"<file>"
block|}
block|,
block|{
literal|"store"
block|,
literal|'S'
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING
block|,
operator|&
name|option_store_filename
block|,
literal|"Store<file> in the clipboard manager"
block|,
literal|"<file>"
block|}
block|,
block|{
literal|"paste"
block|,
literal|'p'
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING
block|,
operator|&
name|option_paste_filename
block|,
literal|"Paste clipoard into<file> ('-' pastes to STDOUT)"
block|,
literal|"<file>"
block|}
block|,
block|{
literal|"version"
block|,
literal|'v'
block|,
name|G_OPTION_FLAG_NO_ARG
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|test_clipboard_show_version
block|,
literal|"Show version information and exit"
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|gint
DECL|function|main (gint argc,gchar * argv[])
name|main
parameter_list|(
name|gint
name|argc
parameter_list|,
name|gchar
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|GOptionContext
modifier|*
name|context
decl_stmt|;
name|GtkClipboard
modifier|*
name|clipboard
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|context
operator|=
name|g_option_context_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_option_context_add_main_entries
argument_list|(
name|context
argument_list|,
name|main_entries
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_option_context_add_group
argument_list|(
name|context
argument_list|,
name|gtk_get_option_group
argument_list|(
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_option_context_parse
argument_list|(
name|context
argument_list|,
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
literal|"Could not initialize the graphical user interface.\n"
literal|"Make sure a proper setup for your display environment "
literal|"exists."
argument_list|)
expr_stmt|;
block|}
return|return
name|EXIT_FAILURE
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
name|clipboard
operator|=
name|gtk_clipboard_get_for_display
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|,
name|option_selection_type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|clipboard
condition|)
name|g_error
argument_list|(
literal|"gtk_clipboard_get_for_display"
argument_list|)
expr_stmt|;
if|if
condition|(
name|option_list_targets
condition|)
block|{
if|if
condition|(
operator|!
name|test_clipboard_list_targets
argument_list|(
name|clipboard
argument_list|)
condition|)
return|return
name|EXIT_FAILURE
return|;
return|return
name|EXIT_SUCCESS
return|;
block|}
if|if
condition|(
operator|(
name|option_copy_filename
operator|&&
name|option_paste_filename
operator|)
operator|||
operator|(
name|option_copy_filename
operator|&&
name|option_store_filename
operator|)
operator|||
operator|(
name|option_paste_filename
operator|&&
name|option_store_filename
operator|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Can't perform two operations at the same time\n"
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
if|if
condition|(
name|option_copy_filename
condition|)
block|{
if|if
condition|(
operator|!
name|option_target
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Usage: %s -t<target> -c<file>\n"
argument_list|,
name|argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
if|if
condition|(
operator|!
name|test_clipboard_copy
argument_list|(
name|clipboard
argument_list|,
name|option_target
argument_list|,
name|option_copy_filename
argument_list|)
condition|)
return|return
name|EXIT_FAILURE
return|;
block|}
if|if
condition|(
name|option_store_filename
condition|)
block|{
if|if
condition|(
operator|!
name|option_target
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Usage: %s -t<target> -S<file>\n"
argument_list|,
name|argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
if|if
condition|(
operator|!
name|test_clipboard_store
argument_list|(
name|clipboard
argument_list|,
name|option_target
argument_list|,
name|option_store_filename
argument_list|)
condition|)
return|return
name|EXIT_FAILURE
return|;
block|}
if|if
condition|(
name|option_paste_filename
condition|)
block|{
if|if
condition|(
operator|!
name|option_target
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Usage: %s -t<target> -p<file>\n"
argument_list|,
name|argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
return|return
name|EXIT_FAILURE
return|;
block|}
if|if
condition|(
operator|!
name|test_clipboard_paste
argument_list|(
name|clipboard
argument_list|,
name|option_target
argument_list|,
name|option_paste_filename
argument_list|)
condition|)
return|return
name|EXIT_FAILURE
return|;
block|}
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|test_clipboard_show_version (void)
name|test_clipboard_show_version
parameter_list|(
name|void
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"test-clipboard (GIMP clipboard testbed) version %s\n"
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|test_clipboard_parse_selection (const gchar * option_name,const gchar * value,gpointer data,GError ** error)
name|test_clipboard_parse_selection
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"primary"
argument_list|)
condition|)
name|option_selection_type
operator|=
name|GDK_SELECTION_PRIMARY
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"secondary"
argument_list|)
condition|)
name|option_selection_type
operator|=
name|GDK_SELECTION_SECONDARY
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"clipboard"
argument_list|)
condition|)
name|option_selection_type
operator|=
name|GDK_SELECTION_CLIPBOARD
expr_stmt|;
else|else
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|test_clipboard_list_targets (GtkClipboard * clipboard)
name|test_clipboard_list_targets
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|)
block|{
name|GtkSelectionData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
name|gtk_clipboard_wait_for_contents
argument_list|(
name|clipboard
argument_list|,
name|gdk_atom_intern
argument_list|(
literal|"TARGETS"
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
name|GdkAtom
modifier|*
name|targets
decl_stmt|;
name|gint
name|n_targets
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|success
operator|=
name|gtk_selection_data_get_targets
argument_list|(
name|data
argument_list|,
operator|&
name|targets
argument_list|,
operator|&
name|n_targets
argument_list|)
expr_stmt|;
name|gtk_selection_data_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_targets
condition|;
name|i
operator|++
control|)
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|gdk_atom_name
argument_list|(
name|targets
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|targets
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|test_clipboard_copy (GtkClipboard * clipboard,const gchar * target,const gchar * filename)
name|test_clipboard_copy
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GtkTargetEntry
name|entry
decl_stmt|;
name|CopyData
name|data
decl_stmt|;
name|entry
operator|.
name|target
operator|=
name|g_strdup
argument_list|(
name|target
argument_list|)
expr_stmt|;
name|entry
operator|.
name|flags
operator|=
literal|0
expr_stmt|;
name|entry
operator|.
name|info
operator|=
literal|1
expr_stmt|;
name|data
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|data
operator|.
name|file_copied
operator|=
name|FALSE
expr_stmt|;
name|data
operator|.
name|error
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_clipboard_set_with_data
argument_list|(
name|clipboard
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|,
name|test_clipboard_copy_callback
argument_list|,
name|NULL
argument_list|,
operator|&
name|data
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: gtk_clipboard_set_with_data() failed\n"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gtk_main
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|.
name|file_copied
condition|)
block|{
if|if
condition|(
name|data
operator|.
name|error
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: copying failed: %s\n"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|data
operator|.
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|data
operator|.
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: copying failed\n"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|test_clipboard_store (GtkClipboard * clipboard,const gchar * target,const gchar * filename)
name|test_clipboard_store
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GtkTargetEntry
name|entry
decl_stmt|;
name|CopyData
name|data
decl_stmt|;
name|entry
operator|.
name|target
operator|=
name|g_strdup
argument_list|(
name|target
argument_list|)
expr_stmt|;
name|entry
operator|.
name|flags
operator|=
literal|0
expr_stmt|;
name|entry
operator|.
name|info
operator|=
literal|1
expr_stmt|;
name|data
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|data
operator|.
name|file_copied
operator|=
name|FALSE
expr_stmt|;
name|data
operator|.
name|error
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_clipboard_set_with_data
argument_list|(
name|clipboard
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|,
name|test_clipboard_copy_callback
argument_list|,
name|NULL
argument_list|,
operator|&
name|data
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: gtk_clipboard_set_with_data() failed\n"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gtk_clipboard_set_can_store
argument_list|(
name|clipboard
argument_list|,
operator|&
name|entry
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_clipboard_store
argument_list|(
name|clipboard
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|.
name|file_copied
condition|)
block|{
if|if
condition|(
name|data
operator|.
name|error
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: storing failed: %s\n"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|data
operator|.
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|data
operator|.
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s: could not contact clipboard manager\n"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|test_clipboard_paste (GtkClipboard * clipboard,const gchar * target,const gchar * filename)
name|test_clipboard_paste
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GtkSelectionData
modifier|*
name|sel_data
decl_stmt|;
name|sel_data
operator|=
name|gtk_clipboard_wait_for_contents
argument_list|(
name|clipboard
argument_list|,
name|gdk_atom_intern
argument_list|(
name|target
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|sel_data
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|gint
name|fd
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|filename
argument_list|,
literal|"-"
argument_list|)
condition|)
name|fd
operator|=
literal|1
expr_stmt|;
else|else
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_WRONLY
operator||
name|O_CREAT
operator||
name|O_TRUNC
argument_list|,
literal|0666
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|<
literal|0
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: open() filed: %s"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|data
operator|=
name|gtk_selection_data_get_data
argument_list|(
name|sel_data
argument_list|)
expr_stmt|;
name|length
operator|=
name|gtk_selection_data_get_length
argument_list|(
name|sel_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|fd
argument_list|,
name|data
argument_list|,
name|length
argument_list|)
operator|<
name|length
condition|)
block|{
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"%s: write() failed: %s"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|close
argument_list|(
name|fd
argument_list|)
operator|<
literal|0
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: close() failed: %s"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gtk_selection_data_free
argument_list|(
name|sel_data
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|test_clipboard_copy_callback (GtkClipboard * clipboard,GtkSelectionData * selection,guint info,gpointer data)
name|test_clipboard_copy_callback
parameter_list|(
name|GtkClipboard
modifier|*
name|clipboard
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|CopyData
modifier|*
name|copy_data
init|=
name|data
decl_stmt|;
name|gchar
modifier|*
name|buf
decl_stmt|;
name|gsize
name|buf_size
decl_stmt|;
if|if
condition|(
operator|!
name|g_file_get_contents
argument_list|(
name|copy_data
operator|->
name|filename
argument_list|,
operator|&
name|buf
argument_list|,
operator|&
name|buf_size
argument_list|,
operator|&
name|copy_data
operator|->
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|option_store_filename
condition|)
name|gtk_main_quit
argument_list|()
expr_stmt|;
return|return;
block|}
name|gtk_selection_data_set
argument_list|(
name|selection
argument_list|,
name|gtk_selection_data_get_target
argument_list|(
name|selection
argument_list|)
argument_list|,
literal|8
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|buf
argument_list|,
name|buf_size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|copy_data
operator|->
name|file_copied
operator|=
name|TRUE
expr_stmt|;
name|g_print
argument_list|(
literal|"%s: data transfer in progress, hit<ctrl>+c when pasted..."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


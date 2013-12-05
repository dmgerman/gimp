begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * gimp-thumbnail-list.c  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<libgimpthumb/gimpthumb.h>
end_include

begin_define
DECL|macro|STATE_NONE
define|#
directive|define
name|STATE_NONE
value|-1
end_define

begin_define
DECL|macro|STATE_ERROR
define|#
directive|define
name|STATE_ERROR
value|-2
end_define

begin_function_decl
specifier|static
name|gboolean
name|parse_option_state
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
name|parse_option_path
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
name|void
name|process_folder
parameter_list|(
specifier|const
name|gchar
modifier|*
name|folder
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|process_thumbnail
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|option_state
specifier|static
name|GimpThumbState
name|option_state
init|=
name|STATE_NONE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|option_verbose
specifier|static
name|gboolean
name|option_verbose
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|option_path
specifier|static
name|gchar
modifier|*
name|option_path
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
literal|"state"
block|,
literal|'s'
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|parse_option_state
block|,
literal|"Filter by thumbnail state "
literal|"(unknown|remote|folder|special|not-found|exists|old|failed|ok|error)"
block|,
literal|"<state>"
block|}
block|,
block|{
literal|"path"
block|,
literal|'p'
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|parse_option_path
block|,
literal|"Filter by original file's path"
block|,
literal|"<path>"
block|}
block|,
block|{
literal|"verbose"
block|,
literal|'v'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|option_verbose
block|,
literal|"Print additional info per matched file"
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
name|GDir
modifier|*
name|dir
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|thumb_folder
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|folder
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimp_thumb_init
argument_list|(
literal|"gimp-thumbnail-list"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|thumb_folder
operator|=
name|gimp_thumb_get_thumb_base_dir
argument_list|()
expr_stmt|;
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
name|g_printerr
argument_list|(
literal|"%s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|dir
operator|=
name|g_dir_open
argument_list|(
name|thumb_folder
argument_list|,
literal|0
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
name|g_error
argument_list|(
literal|"Error opening %s: %s"
argument_list|,
name|thumb_folder
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|folder
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|thumb_folder
argument_list|,
name|folder
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
name|process_folder
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|parse_option_state (const gchar * option_name,const gchar * value,gpointer data,GError ** error)
name|parse_option_state
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
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"unknown"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_UNKNOWN
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"remote"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_REMOTE
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"folder"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_FOLDER
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"special"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_SPECIAL
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"not-found"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_NOT_FOUND
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"exists"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_EXISTS
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"old"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_OLD
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"failed"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_FAILED
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"ok"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|GIMP_THUMB_STATE_OK
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"error"
argument_list|)
operator|==
literal|0
condition|)
name|option_state
operator|=
name|STATE_ERROR
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
DECL|function|parse_option_path (const gchar * option_name,const gchar * value,gpointer data,GError ** error)
name|parse_option_path
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
name|option_path
operator|=
name|g_strdup
argument_list|(
name|value
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
DECL|function|process_folder (const gchar * folder)
name|process_folder
parameter_list|(
specifier|const
name|gchar
modifier|*
name|folder
parameter_list|)
block|{
name|GDir
modifier|*
name|dir
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|#
directive|if
literal|0
block|g_print ("processing folder: %s\n", folder);
endif|#
directive|endif
name|dir
operator|=
name|g_dir_open
argument_list|(
name|folder
argument_list|,
literal|0
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Error opening '%s': %s"
argument_list|,
name|folder
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
return|return;
block|}
while|while
condition|(
operator|(
name|name
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|folder
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
name|process_folder
argument_list|(
name|filename
argument_list|)
expr_stmt|;
else|else
name|process_thumbnail
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|process_thumbnail (const gchar * filename)
name|process_thumbnail
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpThumbnail
modifier|*
name|thumbnail
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|thumbnail
operator|=
name|gimp_thumbnail_new
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_thumbnail_set_from_thumb
argument_list|(
name|thumbnail
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|option_state
operator|==
name|STATE_ERROR
condition|)
block|{
if|if
condition|(
name|option_verbose
condition|)
name|g_print
argument_list|(
literal|"%s '%s'\n"
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpThumbState
name|state
init|=
name|gimp_thumbnail_peek_image
argument_list|(
name|thumbnail
argument_list|)
decl_stmt|;
if|if
condition|(
operator|(
name|option_state
operator|==
name|STATE_NONE
operator|||
name|state
operator|==
name|option_state
operator|)
operator|&&
operator|(
name|option_path
operator|==
name|NULL
operator|||
name|strstr
argument_list|(
name|thumbnail
operator|->
name|image_uri
argument_list|,
name|option_path
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|option_verbose
condition|)
name|g_print
argument_list|(
literal|"%s '%s'\n"
argument_list|,
name|filename
argument_list|,
name|thumbnail
operator|->
name|image_uri
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
literal|0
block|switch (foo)         {         case GIMP_THUMB_STATE_REMOTE:           g_print ("%s Remote image '%s'\n", filename, thumbnail->image_uri);           break;          case GIMP_THUMB_STATE_FOLDER:           g_print ("%s Folder '%s'\n", filename, thumbnail->image_uri);           break;          case GIMP_THUMB_STATE_SPECIAL:           g_print ("%s Special file '%s'\n", filename, thumbnail->image_uri);           break;          case GIMP_THUMB_STATE_NOT_FOUND:           g_print ("%s Image not found '%s'\n", filename, thumbnail->image_uri);           break;          case GIMP_THUMB_STATE_OLD:           g_print ("%s Thumbnail old '%s'\n", filename, thumbnail->image_uri);           break;          case GIMP_THUMB_STATE_FAILED:           g_print ("%s EEEEEEEEK '%s'\n", filename, thumbnail->image_uri);           break;          default:           g_print ("%s '%s'\n", filename, thumbnail->image_uri);           break;         }
endif|#
directive|endif
block|}
name|g_object_unref
argument_list|(
name|thumbnail
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


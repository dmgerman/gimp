begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* simple program to test the XMP parser on files given on the command line */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"xmp-parse.h"
end_include

begin_include
include|#
directive|include
file|"xmp-encode.h"
end_include

begin_function
specifier|static
name|gpointer
DECL|function|start_schema (XMPParseContext * context,const gchar * ns_uri,const gchar * ns_prefix,gpointer user_data,GError ** error)
name|start_schema
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ns_uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ns_prefix
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"Schema %s = \"%s\"\n"
argument_list|,
name|ns_prefix
argument_list|,
name|ns_uri
argument_list|)
expr_stmt|;
return|return
operator|(
name|gpointer
operator|)
name|ns_prefix
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|end_schema (XMPParseContext * context,gpointer user_ns_data,gpointer user_data,GError ** error)
name|end_schema
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|user_ns_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
comment|/* g_print ("End of %s\n", user_ns_prefix); */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|set_property (XMPParseContext * context,const gchar * name,XMPParseType type,const gchar ** value,gpointer user_ns_data,gpointer user_data,GError ** error)
name|set_property
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|XMPParseType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|value
parameter_list|,
name|gpointer
name|user_ns_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|ns_prefix
init|=
name|user_ns_data
decl_stmt|;
name|int
name|i
decl_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|XMP_PTYPE_TEXT
case|:
name|g_print
argument_list|(
literal|"\t%s:%s = \"%s\"\n"
argument_list|,
name|ns_prefix
argument_list|,
name|name
argument_list|,
name|value
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|XMP_PTYPE_RESOURCE
case|:
name|g_print
argument_list|(
literal|"\t%s:%s @ = \"%s\"\n"
argument_list|,
name|ns_prefix
argument_list|,
name|name
argument_list|,
name|value
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|XMP_PTYPE_ORDERED_LIST
case|:
case|case
name|XMP_PTYPE_UNORDERED_LIST
case|:
name|g_print
argument_list|(
literal|"\t%s:%s [] ="
argument_list|,
name|ns_prefix
argument_list|,
name|name
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|value
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|i
operator|==
literal|0
condition|)
name|g_print
argument_list|(
literal|" \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|", \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
break|break;
case|case
name|XMP_PTYPE_ALT_THUMBS
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|value
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|+=
literal|2
control|)
name|g_print
argument_list|(
literal|"\t%s:%s [size = %d] = \"...\"\n"
argument_list|,
name|ns_prefix
argument_list|,
name|name
argument_list|,
operator|*
operator|(
name|int
operator|*
operator|)
operator|(
name|value
index|[
name|i
index|]
operator|)
argument_list|)
expr_stmt|;
comment|/* FIXME: show part of image */
break|break;
case|case
name|XMP_PTYPE_ALT_LANG
case|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|value
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|+=
literal|2
control|)
name|g_print
argument_list|(
literal|"\t%s:%s [lang:%s] = \"%s\"\n"
argument_list|,
name|ns_prefix
argument_list|,
name|name
argument_list|,
name|value
index|[
name|i
index|]
argument_list|,
name|value
index|[
name|i
operator|+
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|XMP_PTYPE_STRUCTURE
case|:
name|g_print
argument_list|(
literal|"\tLocal schema %s = \"%s\"\n"
argument_list|,
name|value
index|[
literal|0
index|]
argument_list|,
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|2
init|;
name|value
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|+=
literal|2
control|)
name|g_print
argument_list|(
literal|"\t%s:%s [%s] = \"%s\"\n"
argument_list|,
name|ns_prefix
argument_list|,
name|name
argument_list|,
name|value
index|[
name|i
index|]
argument_list|,
name|value
index|[
name|i
operator|+
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_print
argument_list|(
literal|"\t%s:%s = ?\n"
argument_list|,
name|ns_prefix
argument_list|,
name|name
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_error (XMPParseContext * context,GError * error,gpointer user_data)
name|print_error
parameter_list|(
name|XMPParseContext
modifier|*
name|context
parameter_list|,
name|GError
modifier|*
name|error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|user_data
decl_stmt|;
name|g_printerr
argument_list|(
literal|"While parsing XMP metadata in %s:\n%s\n"
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|xmp_parser
specifier|static
name|XMPParser
name|xmp_parser
init|=
block|{
name|start_schema
block|,
name|end_schema
block|,
name|set_property
block|,
name|print_error
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|property_changed (XMPModel * tree_model,GtkTreeIter * iter,gpointer user_data)
name|property_changed
parameter_list|(
name|XMPModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|g_print
argument_list|(
literal|"Wuff Wuff!\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|scan_file (const gchar * filename)
name|scan_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gchar
modifier|*
name|contents
decl_stmt|;
name|gsize
name|length
decl_stmt|;
name|GError
modifier|*
name|error
decl_stmt|;
name|XMPParseContext
modifier|*
name|context
decl_stmt|;
name|XMPModel
modifier|*
name|xmp_model
init|=
name|xmp_model_new
argument_list|()
decl_stmt|;
name|g_print
argument_list|(
literal|"\nFile: %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|error
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_get_contents
argument_list|(
name|filename
argument_list|,
operator|&
name|contents
argument_list|,
operator|&
name|length
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|print_error
argument_list|(
name|NULL
argument_list|,
name|error
argument_list|,
operator|(
name|gpointer
operator|)
name|filename
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
block|}
name|context
operator|=
name|xmp_parse_context_new
argument_list|(
operator|&
name|xmp_parser
argument_list|,
name|XMP_FLAG_FIND_XPACKET
argument_list|,
operator|(
name|gpointer
operator|)
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * used for testing the XMPModel    */
name|g_signal_connect
argument_list|(
name|xmp_model
argument_list|,
literal|"property-changed::xmpMM:DocumentID"
argument_list|,
name|G_CALLBACK
argument_list|(
name|property_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|xmp_model_parse_file
argument_list|(
name|xmp_model
argument_list|,
name|filename
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
return|return
literal|1
return|;
block|}
if|if
condition|(
operator|!
name|xmp_parse_context_parse
argument_list|(
name|context
argument_list|,
name|contents
argument_list|,
name|length
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|xmp_parse_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
block|}
if|if
condition|(
operator|!
name|xmp_parse_context_end_parse
argument_list|(
name|context
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|xmp_parse_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
block|}
name|xmp_parse_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|main (int argc,char * argv[])
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|g_set_prgname
argument_list|(
literal|"xmpdump"
argument_list|)
expr_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
if|if
condition|(
name|argc
operator|>
literal|1
condition|)
block|{
for|for
control|(
name|argv
operator|++
operator|,
name|argc
operator|--
init|;
name|argc
condition|;
name|argv
operator|++
operator|,
name|argc
operator|--
control|)
if|if
condition|(
name|scan_file
argument_list|(
operator|*
name|argv
argument_list|)
operator|!=
literal|0
condition|)
return|return
literal|1
return|;
return|return
literal|0
return|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"Usage:\n"
literal|"\txmpdump file [file [...]]\n\n"
literal|"The file(s) given on the command line will be scanned "
literal|"for XMP metadata\n"
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
block|}
block|}
end_function

end_unit


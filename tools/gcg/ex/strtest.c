begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ex/file_ostream_i.h>
end_include

begin_function
DECL|function|putstring_handler (Ostream * o,gchar * msg,gpointer data)
name|void
name|putstring_handler
parameter_list|(
name|Ostream
modifier|*
name|o
parameter_list|,
name|gchar
modifier|*
name|msg
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|s
init|=
name|data
decl_stmt|;
name|g_print
argument_list|(
literal|"Putstring: %s (%p), \"%s\"..\n"
argument_list|,
name|s
argument_list|,
name|o
argument_list|,
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|close_handler (Ostream * o,gpointer data)
name|void
name|close_handler
parameter_list|(
name|Ostream
modifier|*
name|o
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|s
init|=
name|data
decl_stmt|;
name|g_print
argument_list|(
literal|"Closed: %s (%p)!\n"
argument_list|,
name|s
argument_list|,
name|o
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|main (void)
name|int
name|main
parameter_list|(
name|void
parameter_list|)
block|{
name|Ostream
modifier|*
name|x
decl_stmt|;
name|gtk_type_init
argument_list|()
expr_stmt|;
name|x
operator|=
name|OSTREAM
argument_list|(
name|file_ostream_open
argument_list|(
literal|"foo"
argument_list|)
argument_list|)
expr_stmt|;
name|ostream_connect_putstring
argument_list|(
name|putstring_handler
argument_list|,
literal|"foo"
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|ostream_connect_close
argument_list|(
name|close_handler
argument_list|,
literal|"foo"
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|ostream_putstring
argument_list|(
name|x
argument_list|,
literal|"Whammo!\n"
argument_list|)
expr_stmt|;
name|ostream_close
argument_list|(
name|x
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

end_unit


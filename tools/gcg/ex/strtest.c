begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ex/file_ostream_i.h>
end_include

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
init|=
name|OSTREAM
argument_list|(
name|file_ostream_open
argument_list|(
literal|"foo"
argument_list|)
argument_list|)
decl_stmt|;
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


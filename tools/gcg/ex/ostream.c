begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Aye, _mondo_ slow default method.. */
end_comment

begin_function
DECL|function|putstring (ExOstream * str,gchar * string)
specifier|static
name|void
name|putstring
parameter_list|(
name|ExOstream
modifier|*
name|str
parameter_list|,
name|gchar
modifier|*
name|string
parameter_list|)
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
name|string
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
name|ex_ostream_putchar
argument_list|(
name|str
argument_list|,
name|string
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ex_ostream_init_real (ExOstream * str)
specifier|static
name|void
name|ex_ostream_init_real
parameter_list|(
name|ExOstream
modifier|*
name|str
parameter_list|)
block|{ }
end_function

begin_function
DECL|function|ex_ostream_class_init_real (ExOstreamClass * klass)
specifier|static
name|void
name|ex_ostream_class_init_real
parameter_list|(
name|ExOstreamClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|putstring
operator|=
name|putstring
expr_stmt|;
block|}
end_function

end_unit


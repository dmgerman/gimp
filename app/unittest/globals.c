begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GLOBAL data */
end_comment

begin_decl_stmt
DECL|variable|no_interface
name|int
name|no_interface
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_data
name|int
name|no_data
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_splash
name|int
name|no_splash
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_splash_image
name|int
name|no_splash_image
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|be_verbose
name|int
name|be_verbose
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_shm
name|int
name|use_shm
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_debug_handler
name|int
name|use_debug_handler
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|console_messages
name|int
name|console_messages
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|restore_session
name|int
name|restore_session
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_context
name|GimpSet
modifier|*
name|image_context
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_handler
name|MessageHandlerType
name|message_handler
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|prog_name
name|char
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|prog_name
comment|/* The path name we are invoked with */
end_comment

begin_decl_stmt
DECL|variable|alternate_gimprc
name|char
modifier|*
name|alternate_gimprc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|alternate_system_gimprc
name|char
modifier|*
name|alternate_system_gimprc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|batch_cmds
name|char
modifier|*
modifier|*
name|batch_cmds
decl_stmt|;
end_decl_stmt

end_unit


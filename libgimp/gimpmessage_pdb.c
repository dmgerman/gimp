begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpmessage_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * SECTION: gimpmessage  * @title: gimpmessage  * @short_description: Display a dialog box with a message.  *  * Display a dialog box with a message.  **/
end_comment

begin_comment
comment|/**  * gimp_message:  * @message: Message to display in the dialog.  *  * Displays a dialog box with a message.  *  * Displays a dialog box with a message. Useful for status or error  * reporting. The message must be in UTF-8 encoding.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_message (const gchar * message)
name|gimp_message
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|message
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-message"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-message"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_message_get_handler:  *  * Returns the current state of where warning messages are displayed.  *  * This procedure returns the way g_message warnings are displayed.  * They can be shown in a dialog box or printed on the console where  * gimp was started.  *  * Returns: The current handler type.  **/
end_comment

begin_function
name|GimpMessageHandlerType
DECL|function|gimp_message_get_handler (void)
name|gimp_message_get_handler
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpMessageHandlerType
name|handler
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-message-get-handler"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-message-get-handler"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|handler
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|handler
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_message_set_handler:  * @handler: The new handler type.  *  * Controls where warning messages are displayed.  *  * This procedure controls how g_message warnings are displayed. They  * can be shown in a dialog box or printed on the console where gimp  * was started.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_message_set_handler (GimpMessageHandlerType handler)
name|gimp_message_set_handler
parameter_list|(
name|GimpMessageHandlerType
name|handler
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_MESSAGE_HANDLER_TYPE
argument_list|,
name|handler
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-message-set-handler"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-message-set-handler"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit


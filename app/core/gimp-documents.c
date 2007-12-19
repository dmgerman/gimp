begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-documents.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocumentlist.h"
end_include

begin_comment
comment|/* functions to load and save the gimp documents files */
end_comment

begin_function
name|gboolean
DECL|function|gimp_documents_load (Gimp * gimp,GError ** error)
name|gimp_documents_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCUMENT_LIST
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"documents"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
argument_list|,
name|filename
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
argument_list|)
argument_list|,
operator|&
name|my_error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
block|{
if|if
condition|(
name|my_error
operator|->
name|code
operator|==
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
block|{
name|g_clear_error
argument_list|(
operator|&
name|my_error
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|g_propagate_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_documents_save (Gimp * gimp,GError ** error)
name|gimp_documents_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|header
init|=
literal|"GIMP documents\n"
literal|"\n"
literal|"This file will be entirely rewritten each time you exit."
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|footer
init|=
literal|"end of documents"
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCUMENT_LIST
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"documents"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
argument_list|,
name|filename
argument_list|,
name|header
argument_list|,
name|footer
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit


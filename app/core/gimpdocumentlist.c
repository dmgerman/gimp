begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdio.h>
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpscanner.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocuments.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function
name|void
DECL|function|gimp_documents_init (Gimp * gimp)
name|gimp_documents_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp
operator|->
name|documents
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|documents
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_IMAGEFILE
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
argument_list|,
literal|"documents"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_documents_exit (Gimp * gimp)
name|gimp_documents_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|documents
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|documents
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_documents_load (Gimp * gimp)
name|gimp_documents_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"documents"
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner
condition|)
return|return;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"document"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
do|do
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
break|break;
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
if|if
condition|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
operator|==
name|GINT_TO_POINTER
argument_list|(
literal|1
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|uri
argument_list|)
condition|)
block|{
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
break|break;
block|}
name|imagefile
operator|=
name|gimp_imagefile_new
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
operator|->
name|list
operator|=
name|g_list_append
argument_list|(
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
operator|->
name|list
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|documents
operator|->
name|num_children
operator|++
expr_stmt|;
block|}
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
break|break;
default|default:
comment|/* do nothing */
break|break;
block|}
block|}
do|while
condition|(
name|token
operator|!=
name|G_TOKEN_EOF
condition|)
do|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"fatal parse error"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_documents_save_func (GimpImagefile * imagefile,FILE * fp)
name|gimp_documents_save_func
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
block|{
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"(document \"%s\")\n"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_documents_save (Gimp * gimp)
name|gimp_documents_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|tmp_filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|bak_filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|rc_filename
init|=
name|NULL
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|tmp_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"#documents.tmp~"
argument_list|)
expr_stmt|;
name|bak_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"documents.bak"
argument_list|)
expr_stmt|;
name|rc_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"documents"
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|tmp_filename
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
goto|goto
name|cleanup
goto|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"# GIMP documents\n"
literal|"#\n"
literal|"# This file will be entirely rewritten every time you\n"
literal|"# quit the gimp.\n\n"
argument_list|)
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|gimp
operator|->
name|documents
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_documents_save_func
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|__EMX__
argument_list|)
comment|/* First rename the old documents out of the way */
name|unlink
argument_list|(
name|bak_filename
argument_list|)
expr_stmt|;
name|rename
argument_list|(
name|rc_filename
argument_list|,
name|bak_filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|rename
argument_list|(
name|tmp_filename
argument_list|,
name|rc_filename
argument_list|)
operator|!=
literal|0
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|__EMX__
argument_list|)
comment|/* Rename the old documentrc back */
name|rename
argument_list|(
name|bak_filename
argument_list|,
name|rc_filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|unlink
argument_list|(
name|tmp_filename
argument_list|)
expr_stmt|;
block|}
name|cleanup
label|:
name|g_free
argument_list|(
name|tmp_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bak_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rc_filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_documents_add (Gimp * gimp,const gchar * filename)
name|gimp_documents_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|imagefile
operator|=
operator|(
name|GimpImagefile
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|documents
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
condition|)
block|{
name|gimp_container_reorder
argument_list|(
name|gimp
operator|->
name|documents
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|imagefile
operator|=
name|gimp_imagefile_new
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp
operator|->
name|documents
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit


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
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfigwriter.h"
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
file|"gimpdocumentlist.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagefile.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_document_list_config_iface_init
parameter_list|(
name|gpointer
name|iface
parameter_list|,
name|gpointer
name|iface_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_document_list_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_document_list_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|document_symbol
specifier|static
specifier|const
name|gchar
modifier|*
name|document_symbol
init|=
literal|"document"
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_document_list_get_type (void)
name|gimp_document_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|document_list_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|document_list_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|document_list_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDocumentListClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
name|NULL
block|,
comment|/* class_init     */
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpDocumentList
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|document_list_iface_info
init|=
block|{
name|gimp_document_list_config_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|document_list_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_LIST
argument_list|,
literal|"GimpDocumentList"
argument_list|,
operator|&
name|document_list_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|document_list_type
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|,
operator|&
name|document_list_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|document_list_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_document_list_config_iface_init (gpointer iface,gpointer iface_data)
name|gimp_document_list_config_iface_init
parameter_list|(
name|gpointer
name|iface
parameter_list|,
name|gpointer
name|iface_data
parameter_list|)
block|{
name|GimpConfigInterface
modifier|*
name|config_iface
init|=
operator|(
name|GimpConfigInterface
operator|*
operator|)
name|iface
decl_stmt|;
name|config_iface
operator|->
name|serialize
operator|=
name|gimp_document_list_serialize
expr_stmt|;
name|config_iface
operator|->
name|deserialize
operator|=
name|gimp_document_list_deserialize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_document_list_serialize (GimpConfig * config,GimpConfigWriter * writer,gpointer data)
name|gimp_document_list_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|config
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|document_symbol
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
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
name|gboolean
DECL|function|gimp_document_list_deserialize (GimpConfig * config,GScanner * scanner,gint nest_level,gpointer data)
name|gimp_document_list_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDocumentList
modifier|*
name|document_list
init|=
name|GIMP_DOCUMENT_LIST
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|gint
name|size
decl_stmt|;
name|size
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
name|document_symbol
argument_list|,
operator|(
name|gpointer
operator|)
name|document_symbol
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
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
name|document_symbol
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
name|document_list
operator|->
name|gimp
argument_list|,
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|>
literal|0
condition|)
name|gimp_imagefile_update
argument_list|(
name|imagefile
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|document_list
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|imagefile
argument_list|)
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
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|document_list
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|gimp_config_deserialize_return
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|,
name|nest_level
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_document_list_new (Gimp * gimp)
name|gimp_document_list_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDocumentList
modifier|*
name|document_list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|document_list
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DOCUMENT_LIST
argument_list|,
literal|"name"
argument_list|,
literal|"document_list"
argument_list|,
literal|"children_type"
argument_list|,
name|GIMP_TYPE_IMAGEFILE
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|document_list
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
return|return
name|GIMP_CONTAINER
argument_list|(
name|document_list
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpImagefile
modifier|*
DECL|function|gimp_document_list_add_uri (GimpDocumentList * document_list,const gchar * uri)
name|gimp_document_list_add_uri
parameter_list|(
name|GimpDocumentList
modifier|*
name|document_list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCUMENT_LIST
argument_list|(
name|document_list
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|container
operator|=
name|GIMP_CONTAINER
argument_list|(
name|document_list
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
name|container
argument_list|,
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
condition|)
block|{
name|gimp_container_reorder
argument_list|(
name|container
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
name|document_list
operator|->
name|gimp
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|imagefile
argument_list|)
expr_stmt|;
block|}
return|return
name|imagefile
return|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Config file serialization and deserialization interface  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

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
file|"gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-deserialize.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*   * The GimpConfig serialization and deserialization interface.  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_config_iface_serialize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|gint
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_iface_deserialize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_config_interface_get_type (void)
name|gimp_config_interface_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|config_iface_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|config_iface_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|config_iface_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpConfigInterface
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|gimp_config_iface_init
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|config_iface_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INTERFACE
argument_list|,
literal|"GimpConfigInterface"
argument_list|,
operator|&
name|config_iface_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_interface_add_prerequisite
argument_list|(
name|config_iface_type
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
expr_stmt|;
block|}
return|return
name|config_iface_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_iface_init (GimpConfigInterface * gimp_config_iface)
name|gimp_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
parameter_list|)
block|{
name|gimp_config_iface
operator|->
name|serialize
operator|=
name|gimp_config_iface_serialize
expr_stmt|;
name|gimp_config_iface
operator|->
name|deserialize
operator|=
name|gimp_config_iface_deserialize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_iface_serialize (GObject * object,gint fd)
name|gimp_config_iface_serialize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|gint
name|fd
parameter_list|)
block|{
name|gimp_config_serialize_properties
argument_list|(
name|object
argument_list|,
name|fd
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_iface_deserialize (GObject * object,GScanner * scanner)
name|gimp_config_iface_deserialize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
return|return
name|gimp_config_deserialize_properties
argument_list|(
name|object
argument_list|,
name|scanner
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_config_serialize (GObject * object,const gchar * filename)
name|gimp_config_serialize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_config_iface
operator|=
name|GIMP_GET_CONFIG_INTERFACE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_config_iface
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_WRONLY
operator||
name|O_CREAT
operator||
name|O_TRUNC
argument_list|,
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|S_IRUSR
operator||
name|S_IWUSR
operator||
name|S_IRGRP
operator||
name|S_IROTH
argument_list|)
expr_stmt|;
else|#
directive|else
name|_S_IREAD
operator||
name|_S_IWRITE
block|)
function|;
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to open file '%s': %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_if

begin_expr_stmt
name|gimp_config_iface
operator|->
name|serialize
argument_list|(
name|object
argument_list|,
name|fd
argument_list|)
expr_stmt|;
end_expr_stmt

begin_expr_stmt
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
end_expr_stmt

begin_return
return|return
name|TRUE
return|;
end_return

begin_macro
unit|}  gboolean
DECL|function|gimp_config_deserialize (GObject * object,const gchar * filename)
name|gimp_config_deserialize
argument_list|(
argument|GObject      *object
argument_list|,
argument|const gchar  *filename
argument_list|)
end_macro

begin_block
block|{
name|GimpConfigInterface
modifier|*
name|gimp_config_iface
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_config_iface
operator|=
name|GIMP_GET_CONFIG_INTERFACE
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_config_iface
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Failed to open file '%s': %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|scanner
operator|=
name|g_scanner_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_first
operator|=
operator|(
name|G_CSET_a_2_z
operator|)
expr_stmt|;
name|scanner
operator|->
name|config
operator|->
name|cset_identifier_nth
operator|=
operator|(
name|G_CSET_a_2_z
literal|"-_"
operator|)
expr_stmt|;
name|g_scanner_input_file
argument_list|(
name|scanner
argument_list|,
name|fd
argument_list|)
expr_stmt|;
name|scanner
operator|->
name|input_name
operator|=
name|filename
expr_stmt|;
name|success
operator|=
name|gimp_config_iface
operator|->
name|deserialize
argument_list|(
name|object
argument_list|,
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_block

begin_comment
comment|/*   * Code to store and lookup unknown tokens (string key/value pairs).  */
end_comment

begin_define
DECL|macro|GIMP_CONFIG_UNKNOWN_TOKENS
define|#
directive|define
name|GIMP_CONFIG_UNKNOWN_TOKENS
value|"gimp-config-unknown-tokens"
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2ade2ce70108
block|{
DECL|member|key
name|gchar
modifier|*
name|key
decl_stmt|;
DECL|member|value
name|gchar
modifier|*
name|value
decl_stmt|;
DECL|typedef|GimpConfigToken
block|}
name|GimpConfigToken
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_config_destroy_unknown_tokens
parameter_list|(
name|GSList
modifier|*
name|unknown_tokens
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_config_add_unknown_token (GObject * object,const gchar * key,const gchar * value)
name|gimp_config_add_unknown_token
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|unknown_tokens
decl_stmt|;
name|GSList
modifier|*
name|last
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|key
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|value
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|unknown_tokens
operator|=
operator|(
name|GSList
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|)
expr_stmt|;
for|for
control|(
name|last
operator|=
name|NULL
operator|,
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|last
operator|=
name|list
operator|,
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|token
operator|->
name|key
argument_list|,
name|key
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* FIXME: should we emit a warning here ?? */
name|g_free
argument_list|(
name|token
operator|->
name|value
argument_list|)
expr_stmt|;
name|token
operator|->
name|value
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|token
operator|=
name|g_new
argument_list|(
name|GimpConfigToken
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|token
operator|->
name|key
operator|=
name|g_strdup
argument_list|(
name|key
argument_list|)
expr_stmt|;
name|token
operator|->
name|value
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|last
condition|)
block|{
name|g_slist_append
argument_list|(
name|last
argument_list|,
name|token
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|unknown_tokens
operator|=
name|g_slist_append
argument_list|(
name|NULL
argument_list|,
name|token
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|,
name|unknown_tokens
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_config_destroy_unknown_tokens
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_config_lookup_unknown_token (GObject * object,const gchar * key)
name|gimp_config_lookup_unknown_token
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|unknown_tokens
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|key
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|unknown_tokens
operator|=
operator|(
name|GSList
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|token
operator|->
name|key
argument_list|,
name|key
argument_list|)
operator|==
literal|0
condition|)
return|return
name|token
operator|->
name|value
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_config_foreach_unknown_token (GObject * object,GimpConfigForeachFunc func,gpointer user_data)
name|gimp_config_foreach_unknown_token
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GimpConfigForeachFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|unknown_tokens
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|unknown_tokens
operator|=
operator|(
name|GSList
operator|*
operator|)
name|g_object_get_data
argument_list|(
name|object
argument_list|,
name|GIMP_CONFIG_UNKNOWN_TOKENS
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|func
argument_list|(
name|token
operator|->
name|key
argument_list|,
name|token
operator|->
name|value
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_destroy_unknown_tokens (GSList * unknown_tokens)
name|gimp_config_destroy_unknown_tokens
parameter_list|(
name|GSList
modifier|*
name|unknown_tokens
parameter_list|)
block|{
name|GimpConfigToken
modifier|*
name|token
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|unknown_tokens
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|token
operator|=
operator|(
name|GimpConfigToken
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|g_free
argument_list|(
name|token
operator|->
name|key
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|token
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|token
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|unknown_tokens
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


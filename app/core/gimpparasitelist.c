begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasitelist.c: Copyright 1998 Jay Cox<jaycox@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasitelist.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a53417f0103
block|{
DECL|enumerator|ADD
name|ADD
block|,
DECL|enumerator|REMOVE
name|REMOVE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_parasite_list_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_parasite_list_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_parasite_list_config_iface_init
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
name|gimp_parasite_list_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|list
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
name|gimp_parasite_list_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|list
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

begin_function_decl
specifier|static
name|void
name|parasite_serialize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|parasite_copy
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GimpParasiteList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|parasite_free
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gpointer
name|unused
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|parasite_count_if_persistent
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpParasiteList
argument_list|,
argument|gimp_parasite_list
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_parasite_list_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_parasite_list_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|parasite_list_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parasite_symbol
specifier|static
specifier|const
name|gchar
name|parasite_symbol
index|[]
init|=
literal|"parasite"
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_parasite_list_class_init (GimpParasiteListClass * klass)
name|gimp_parasite_list_class_init
parameter_list|(
name|GimpParasiteListClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parasite_list_signals
index|[
name|ADD
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"add"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpParasiteListClass
argument_list|,
name|add
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|parasite_list_signals
index|[
name|REMOVE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"remove"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpParasiteListClass
argument_list|,
name|remove
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_parasite_list_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_parasite_list_get_memsize
expr_stmt|;
name|klass
operator|->
name|add
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|remove
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_parasite_list_config_iface_init (gpointer iface,gpointer iface_data)
name|gimp_parasite_list_config_iface_init
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
name|gimp_parasite_list_serialize
expr_stmt|;
name|config_iface
operator|->
name|deserialize
operator|=
name|gimp_parasite_list_deserialize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_parasite_list_init (GimpParasiteList * list)
name|gimp_parasite_list_init
parameter_list|(
name|GimpParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|list
operator|->
name|table
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_parasite_list_finalize (GObject * object)
name|gimp_parasite_list_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpParasiteList
modifier|*
name|list
init|=
name|GIMP_PARASITE_LIST
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
block|{
name|g_hash_table_foreach_remove
argument_list|(
name|list
operator|->
name|table
argument_list|,
operator|(
name|GHRFunc
operator|)
name|parasite_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|list
operator|->
name|table
argument_list|)
expr_stmt|;
name|list
operator|->
name|table
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_parasite_list_get_memsize_foreach (gpointer key,gpointer p,gpointer m)
name|gimp_parasite_list_get_memsize_foreach
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|p
parameter_list|,
name|gpointer
name|m
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
init|=
name|p
decl_stmt|;
name|gint64
modifier|*
name|memsize
init|=
name|m
decl_stmt|;
operator|*
name|memsize
operator|+=
operator|(
sizeof|sizeof
argument_list|(
name|GimpParasite
argument_list|)
operator|+
name|strlen
argument_list|(
name|parasite
operator|->
name|name
argument_list|)
operator|+
literal|1
operator|+
name|parasite
operator|->
name|size
operator|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_parasite_list_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_parasite_list_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpParasiteList
modifier|*
name|list
init|=
name|GIMP_PARASITE_LIST
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
block|{
name|memsize
operator|+=
name|gimp_g_hash_table_get_memsize
argument_list|(
name|list
operator|->
name|table
argument_list|)
expr_stmt|;
name|g_hash_table_foreach
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|gimp_parasite_list_get_memsize_foreach
argument_list|,
operator|&
name|memsize
argument_list|)
expr_stmt|;
block|}
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_parasite_list_serialize (GimpConfig * list,GimpConfigWriter * writer,gpointer data)
name|gimp_parasite_list_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|list
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|GIMP_PARASITE_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|table
condition|)
name|g_hash_table_foreach
argument_list|(
name|GIMP_PARASITE_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|table
argument_list|,
operator|(
name|GHFunc
operator|)
name|parasite_serialize
argument_list|,
name|writer
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_parasite_list_deserialize (GimpConfig * list,GScanner * scanner,gint nest_level,gpointer data)
name|gimp_parasite_list_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|list
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
name|GTokenType
name|token
decl_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
name|parasite_symbol
argument_list|,
operator|(
name|gpointer
operator|)
name|parasite_symbol
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
if|if
condition|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
operator|==
name|parasite_symbol
condition|)
block|{
name|gchar
modifier|*
name|parasite_name
init|=
name|NULL
decl_stmt|;
name|gint
name|parasite_flags
init|=
literal|0
decl_stmt|;
name|guint8
modifier|*
name|parasite_data
init|=
name|NULL
decl_stmt|;
name|gint
name|parasite_data_size
init|=
literal|0
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
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
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|parasite_name
argument_list|)
condition|)
break|break;
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
goto|goto
name|cleanup
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|parasite_flags
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
block|{
comment|/*  old format -- plain string  */
name|gchar
modifier|*
name|str
decl_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_STRING
condition|)
goto|goto
name|cleanup
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|str
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
name|parasite_data_size
operator|=
name|strlen
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|parasite_data
operator|=
operator|(
name|guint8
operator|*
operator|)
name|str
expr_stmt|;
block|}
else|else
block|{
comment|/*  new format -- properly encoded binary data  */
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|parasite_data_size
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
goto|goto
name|cleanup
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_data
argument_list|(
name|scanner
argument_list|,
name|parasite_data_size
argument_list|,
operator|&
name|parasite_data
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
block|}
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|parasite_name
argument_list|,
name|parasite_flags
argument_list|,
name|parasite_data_size
argument_list|,
name|parasite_data
argument_list|)
expr_stmt|;
name|gimp_parasite_list_add
argument_list|(
name|GIMP_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
comment|/* adds a copy */
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
name|g_free
argument_list|(
name|parasite_data
argument_list|)
expr_stmt|;
name|cleanup
label|:
name|g_free
argument_list|(
name|parasite_name
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
name|GimpParasiteList
modifier|*
DECL|function|gimp_parasite_list_new (void)
name|gimp_parasite_list_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParasiteList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PARASITE_LIST
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
name|GimpParasiteList
modifier|*
DECL|function|gimp_parasite_list_copy (const GimpParasiteList * list)
name|gimp_parasite_list_copy
parameter_list|(
specifier|const
name|GimpParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|GimpParasiteList
modifier|*
name|newlist
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|newlist
operator|=
name|gimp_parasite_list_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
name|g_hash_table_foreach
argument_list|(
name|list
operator|->
name|table
argument_list|,
operator|(
name|GHFunc
operator|)
name|parasite_copy
argument_list|,
name|newlist
argument_list|)
expr_stmt|;
return|return
name|newlist
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_list_add (GimpParasiteList * list,const GimpParasite * parasite)
name|gimp_parasite_list_add
parameter_list|(
name|GimpParasiteList
modifier|*
name|list
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|copy
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|parasite
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|parasite
operator|->
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
operator|==
name|NULL
condition|)
name|list
operator|->
name|table
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|gimp_parasite_list_remove
argument_list|(
name|list
argument_list|,
name|parasite
operator|->
name|name
argument_list|)
expr_stmt|;
name|copy
operator|=
name|gimp_parasite_copy
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|copy
operator|->
name|name
argument_list|,
name|copy
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|list
argument_list|,
name|parasite_list_signals
index|[
name|ADD
index|]
argument_list|,
literal|0
argument_list|,
name|copy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_list_remove (GimpParasiteList * list,const gchar * name)
name|gimp_parasite_list_remove
parameter_list|(
name|GimpParasiteList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
operator|(
name|GimpParasite
operator|*
operator|)
name|gimp_parasite_list_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|g_hash_table_remove
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|list
argument_list|,
name|parasite_list_signals
index|[
name|REMOVE
index|]
argument_list|,
literal|0
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_parasite_list_length (GimpParasiteList * list)
name|gimp_parasite_list_length
parameter_list|(
name|GimpParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
operator|->
name|table
condition|)
return|return
literal|0
return|;
return|return
name|g_hash_table_size
argument_list|(
name|list
operator|->
name|table
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_parasite_list_persistent_length (GimpParasiteList * list)
name|gimp_parasite_list_persistent_length
parameter_list|(
name|GimpParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|gint
name|len
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
operator|->
name|table
condition|)
return|return
literal|0
return|;
name|gimp_parasite_list_foreach
argument_list|(
name|list
argument_list|,
operator|(
name|GHFunc
operator|)
name|parasite_count_if_persistent
argument_list|,
operator|&
name|len
argument_list|)
expr_stmt|;
return|return
name|len
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_list_foreach (GimpParasiteList * list,GHFunc function,gpointer user_data)
name|gimp_parasite_list_foreach
parameter_list|(
name|GimpParasiteList
modifier|*
name|list
parameter_list|,
name|GHFunc
name|function
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
operator|->
name|table
condition|)
return|return;
name|g_hash_table_foreach
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|function
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|GimpParasite
modifier|*
DECL|function|gimp_parasite_list_find (GimpParasiteList * list,const gchar * name)
name|gimp_parasite_list_find
parameter_list|(
name|GimpParasiteList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
return|return
operator|(
name|GimpParasite
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|name
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parasite_serialize (const gchar * key,GimpParasite * parasite,GimpConfigWriter * writer)
name|parasite_serialize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_parasite_is_persistent
argument_list|(
name|parasite
argument_list|)
condition|)
return|return;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|parasite_symbol
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"\"%s\" %lu %lu"
argument_list|,
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_flags
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_data
argument_list|(
name|writer
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parasite_copy (const gchar * key,GimpParasite * parasite,GimpParasiteList * list)
name|parasite_copy
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GimpParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|gimp_parasite_list_add
argument_list|(
name|list
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|parasite_free (const gchar * key,GimpParasite * parasite,gpointer unused)
name|parasite_free
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gpointer
name|unused
parameter_list|)
block|{
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parasite_count_if_persistent (const gchar * key,GimpParasite * parasite,gint * count)
name|parasite_count_if_persistent
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
block|{
if|if
condition|(
name|gimp_parasite_is_persistent
argument_list|(
name|parasite
argument_list|)
condition|)
operator|*
name|count
operator|=
operator|*
name|count
operator|+
literal|1
expr_stmt|;
block|}
end_function

end_unit


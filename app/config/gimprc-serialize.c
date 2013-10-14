begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpRc serialization routines  * Copyright (C) 2001-2005  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
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
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-unknown.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_rc_serialize_properties_diff
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfig
modifier|*
name|compare
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_rc_serialize_unknown_tokens
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|gimp_rc_serialize (GimpConfig * config,GimpConfigWriter * writer,gpointer data)
name|gimp_rc_serialize
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
if|if
condition|(
name|data
operator|&&
name|GIMP_IS_RC
argument_list|(
name|data
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_rc_serialize_properties_diff
argument_list|(
name|config
argument_list|,
name|data
argument_list|,
name|writer
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|gimp_config_serialize_properties
argument_list|(
name|config
argument_list|,
name|writer
argument_list|)
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|gimp_rc_serialize_unknown_tokens
argument_list|(
name|config
argument_list|,
name|writer
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rc_serialize_properties_diff (GimpConfig * config,GimpConfig * compare,GimpConfigWriter * writer)
name|gimp_rc_serialize_properties_diff
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfig
modifier|*
name|compare
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|GList
modifier|*
name|diff
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|retval
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|compare
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|config
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|compare
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|diff
operator|=
name|gimp_config_diff
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|compare
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|diff
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GParamSpec
modifier|*
name|prop_spec
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
condition|)
continue|continue;
if|if
condition|(
operator|!
name|gimp_config_serialize_property
argument_list|(
name|config
argument_list|,
name|prop_spec
argument_list|,
name|writer
argument_list|)
condition|)
block|{
name|retval
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
name|g_list_free
argument_list|(
name|diff
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|serialize_unknown_token (const gchar * key,const gchar * value,gpointer data)
name|serialize_unknown_token
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
init|=
name|data
decl_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|key
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_rc_serialize_unknown_tokens (GimpConfig * config,GimpConfigWriter * writer)
name|gimp_rc_serialize_unknown_tokens
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_rc_foreach_unknown_token
argument_list|(
name|config
argument_list|,
name|serialize_unknown_token
argument_list|,
name|writer
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpRc, the object for GIMPs user configuration file gimprc.  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|"libgimpbase/gimpbase.h"
end_include

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
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_rc_config_iface_init
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
name|void
name|gimp_rc_serialize
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
name|gimp_rc_deserialize
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

begin_function_decl
specifier|static
name|void
name|gimp_rc_write_header
parameter_list|(
name|gint
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_rc_get_type (void)
name|gimp_rc_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|rc_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|rc_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|rc_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpRcClass
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
name|GimpRc
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
name|rc_iface_info
init|=
block|{
name|gimp_rc_config_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|rc_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_GUI_CONFIG
argument_list|,
literal|"GimpRc"
argument_list|,
operator|&
name|rc_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|rc_type
argument_list|,
name|GIMP_TYPE_CONFIG_INTERFACE
argument_list|,
operator|&
name|rc_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|rc_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rc_config_iface_init (gpointer iface,gpointer iface_data)
name|gimp_rc_config_iface_init
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
name|gimp_rc_serialize
expr_stmt|;
name|config_iface
operator|->
name|deserialize
operator|=
name|gimp_rc_deserialize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_rc_serialize (GObject * object,gint fd)
name|gimp_rc_serialize
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
name|gimp_config_serialize_unknown_tokens
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
DECL|function|gimp_rc_deserialize (GObject * object,GScanner * scanner)
name|gimp_rc_deserialize
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
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rc_new:  *   * Creates a new #GimpRc object with default configuration values.  *   * Return value: the newly generated #GimpRc object.  **/
end_comment

begin_function
name|GimpRc
modifier|*
DECL|function|gimp_rc_new (void)
name|gimp_rc_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|GIMP_RC
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
name|NULL
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rc_write_changes:  * @new_rc: a #GimpRc object.  * @old_rc: another #GimpRc object.  * @filename: the name of the rc file to generate. If it is %NULL, stdout   * will be used.  *   * Writes all configuration values of @new_rc that differ from the values  * set in @old_rc to the file specified by @filename. If the file already  * exists, it is overwritten.  *   * Return value: TRUE on success, FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_rc_write_changes (GimpRc * new_rc,GimpRc * old_rc,const gchar * filename)
name|gimp_rc_write_changes
parameter_list|(
name|GimpRc
modifier|*
name|new_rc
parameter_list|,
name|GimpRc
modifier|*
name|old_rc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gint
name|fd
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_RC
argument_list|(
name|new_rc
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_RC
argument_list|(
name|old_rc
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_WRONLY
operator||
name|O_CREAT
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

begin_else
else|else
name|fd
operator|=
literal|1
expr_stmt|;
end_else

begin_comment
comment|/* stdout */
end_comment

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
name|gimp_rc_write_header
argument_list|(
name|fd
argument_list|)
expr_stmt|;
end_expr_stmt

begin_expr_stmt
name|gimp_config_serialize_changed_properties
argument_list|(
name|G_OBJECT
argument_list|(
name|new_rc
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|old_rc
argument_list|)
argument_list|,
name|fd
argument_list|)
expr_stmt|;
end_expr_stmt

begin_expr_stmt
name|gimp_config_serialize_unknown_tokens
argument_list|(
name|G_OBJECT
argument_list|(
name|new_rc
argument_list|)
argument_list|,
name|fd
argument_list|)
expr_stmt|;
end_expr_stmt

begin_if
if|if
condition|(
name|filename
condition|)
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
end_if

begin_return
return|return
name|TRUE
return|;
end_return

begin_function
unit|}  static
name|void
DECL|function|gimp_rc_write_header (gint fd)
name|gimp_rc_write_header
parameter_list|(
name|gint
name|fd
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|top
init|=
literal|"# This is your personal gimprc file.  Any variable defined in this file\n"
literal|"# takes precedence over the value defined in the system-wide gimprc:\n"
literal|"#   "
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|bottom
init|=
literal|"\n"
literal|"# Most values can be set within The GIMP by changing some options in\n"
literal|"# the Preferences dialog.\n\n"
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_sysconf_directory
argument_list|()
argument_list|,
literal|"gimprc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|top
argument_list|,
name|strlen
argument_list|(
name|top
argument_list|)
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|filename
argument_list|,
name|strlen
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|write
argument_list|(
name|fd
argument_list|,
name|bottom
argument_list|,
name|strlen
argument_list|(
name|bottom
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Config file serialization and deserialization interface  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_H__
define|#
directive|define
name|__GIMP_CONFIG_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27dc508d0103
block|{
DECL|enumerator|GIMP_CONFIG_ERROR_OPEN
name|GIMP_CONFIG_ERROR_OPEN
block|,
comment|/*  open failed          */
DECL|enumerator|GIMP_CONFIG_ERROR_OPEN_ENOENT
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
block|,
comment|/*  file does not exist  */
DECL|enumerator|GIMP_CONFIG_ERROR_WRITE
name|GIMP_CONFIG_ERROR_WRITE
block|,
comment|/*  write failed         */
DECL|enumerator|GIMP_CONFIG_ERROR_PARSE
name|GIMP_CONFIG_ERROR_PARSE
comment|/*  parser error         */
DECL|typedef|GimpConfigError
block|}
name|GimpConfigError
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONFIG_INTERFACE
define|#
directive|define
name|GIMP_TYPE_CONFIG_INTERFACE
value|(gimp_config_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_GET_CONFIG_INTERFACE (obj)
define|#
directive|define
name|GIMP_GET_CONFIG_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_CONFIG_INTERFACE, GimpConfigInterface))
end_define

begin_typedef
DECL|typedef|GimpConfigInterface
typedef|typedef
name|struct
name|_GimpConfigInterface
name|GimpConfigInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpConfigInterface
struct|struct
name|_GimpConfigInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
DECL|member|serialize
name|gboolean
function_decl|(
modifier|*
name|serialize
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|gint
name|fd
parameter_list|,
name|gint
name|indent_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|deserialize
name|gboolean
function_decl|(
modifier|*
name|deserialize
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|object
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
DECL|member|serialize_property
name|gboolean
function_decl|(
modifier|*
name|serialize_property
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GString
modifier|*
name|string
parameter_list|)
function_decl|;
DECL|member|deserialize_property
name|gboolean
function_decl|(
modifier|*
name|deserialize_property
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
modifier|*
name|expected
parameter_list|)
function_decl|;
DECL|member|duplicate
name|GObject
modifier|*
function_decl|(
modifier|*
name|duplicate
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|equal
name|gboolean
function_decl|(
modifier|*
name|equal
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpConfigForeachFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpConfigForeachFunc
function_decl|)
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
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_config_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|header
parameter_list|,
specifier|const
name|gchar
modifier|*
name|footer
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_deserialize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_deserialize_return
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GTokenType
name|expected_token
parameter_list|,
name|gint
name|nest_level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GObject
modifier|*
name|gimp_config_duplicate
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_is_equal_to
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_CONFIG_ERROR
define|#
directive|define
name|GIMP_CONFIG_ERROR
value|(gimp_config_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_config_error_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_config_string_indent
parameter_list|(
name|GString
modifier|*
name|string
parameter_list|,
name|gint
name|indent_level
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_H__ */
end_comment

end_unit


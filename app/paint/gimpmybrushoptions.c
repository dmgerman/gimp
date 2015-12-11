begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LIBMYPAINT
end_ifdef

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_include
include|#
directive|include
file|<mypaint-brush.h>
end_include

begin_enum
enum|enum
DECL|enum|__anon2b65133a0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RADIUS
name|PROP_RADIUS
block|,
DECL|enumerator|PROP_OPAQUE
name|PROP_OPAQUE
block|,
DECL|enumerator|PROP_HARDNESS
name|PROP_HARDNESS
block|,
DECL|enumerator|PROP_MYBRUSH
name|PROP_MYBRUSH
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b65133a0208
block|{
DECL|member|radius
name|gdouble
name|radius
decl_stmt|;
DECL|member|opaque
name|gdouble
name|opaque
decl_stmt|;
DECL|member|hardness
name|gdouble
name|hardness
decl_stmt|;
DECL|member|brush_json
name|gchar
modifier|*
name|brush_json
decl_stmt|;
DECL|typedef|OptionsState
block|}
name|OptionsState
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|loaded_myb
specifier|static
name|GHashTable
modifier|*
name|loaded_myb
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_mybrush_options_set_property
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_mybrush_options_get_property
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
parameter_list|)
function_decl|;
end_function_decl

begin_function
DECL|function|options_state_free (gpointer options)
specifier|static
name|void
name|options_state_free
parameter_list|(
name|gpointer
name|options
parameter_list|)
block|{
name|OptionsState
modifier|*
name|state
init|=
name|options
decl_stmt|;
name|g_free
argument_list|(
name|state
operator|->
name|brush_json
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|state
argument_list|)
expr_stmt|;
block|}
end_function

begin_macro
DECL|function|G_DEFINE_TYPE (GimpMybrushOptions,gimp_mybrush_options,GIMP_TYPE_PAINT_OPTIONS)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpMybrushOptions
argument_list|,
argument|gimp_mybrush_options
argument_list|,
argument|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_mybrush_options_class_init
parameter_list|(
name|GimpMybrushOptionsClass
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_mybrush_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_mybrush_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_RADIUS
argument_list|,
literal|"radius"
argument_list|,
name|_
argument_list|(
literal|"Radius"
argument_list|)
argument_list|,
operator|-
literal|2.0
argument_list|,
literal|6.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_OPAQUE
argument_list|,
literal|"opaque"
argument_list|,
name|_
argument_list|(
literal|"Base Opacity"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|2.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_HARDNESS
argument_list|,
literal|"hardness"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_MYBRUSH
argument_list|,
literal|"mybrush"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|loaded_myb
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|options_state_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_load_path (GObject * object,gchar * path)
name|gimp_mybrush_options_load_path
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|)
block|{
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|OptionsState
modifier|*
name|state
init|=
name|g_hash_table_lookup
argument_list|(
name|loaded_myb
argument_list|,
name|path
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|state
condition|)
block|{
name|gchar
modifier|*
name|brush_json
init|=
name|NULL
decl_stmt|;
name|MyPaintBrush
modifier|*
name|brush
init|=
name|mypaint_brush_new
argument_list|()
decl_stmt|;
name|state
operator|=
name|g_new0
argument_list|(
name|OptionsState
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|mypaint_brush_from_defaults
argument_list|(
name|brush
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_get_contents
argument_list|(
name|path
argument_list|,
operator|&
name|brush_json
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|mypaint_brush_from_string
argument_list|(
name|brush
argument_list|,
name|brush_json
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"Failed to deserialize MyPaint brush\n"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush_json
argument_list|)
expr_stmt|;
name|brush_json
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|state
operator|->
name|brush_json
operator|=
name|brush_json
expr_stmt|;
name|state
operator|->
name|radius
operator|=
name|mypaint_brush_get_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC
argument_list|)
expr_stmt|;
name|state
operator|->
name|opaque
operator|=
name|mypaint_brush_get_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_OPAQUE
argument_list|)
expr_stmt|;
name|state
operator|->
name|hardness
operator|=
name|mypaint_brush_get_base_value
argument_list|(
name|brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_HARDNESS
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|loaded_myb
argument_list|,
name|g_strdup
argument_list|(
name|path
argument_list|)
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
name|options
operator|->
name|radius
operator|=
name|state
operator|->
name|radius
expr_stmt|;
name|options
operator|->
name|opaque
operator|=
name|state
operator|->
name|opaque
expr_stmt|;
name|options
operator|->
name|hardness
operator|=
name|state
operator|->
name|hardness
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"radius"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"opaque"
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"hardness"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_init (GimpMybrushOptions * options)
name|gimp_mybrush_options_init
parameter_list|(
name|GimpMybrushOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_mybrush_options_set_property
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
parameter_list|)
block|{
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_RADIUS
case|:
name|options
operator|->
name|radius
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARDNESS
case|:
name|options
operator|->
name|hardness
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|options
operator|->
name|opaque
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MYBRUSH
case|:
name|g_free
argument_list|(
name|options
operator|->
name|mybrush
argument_list|)
expr_stmt|;
name|options
operator|->
name|mybrush
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|mybrush
condition|)
name|gimp_mybrush_options_load_path
argument_list|(
name|object
argument_list|,
name|options
operator|->
name|mybrush
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_mybrush_options_get_property
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
parameter_list|)
block|{
name|GimpMybrushOptions
modifier|*
name|options
init|=
name|GIMP_MYBRUSH_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_RADIUS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|radius
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|opaque
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARDNESS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|hardness
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MYBRUSH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|mybrush
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_mybrush_options_get_brush_data (GimpMybrushOptions * options)
name|gimp_mybrush_options_get_brush_data
parameter_list|(
name|GimpMybrushOptions
modifier|*
name|options
parameter_list|)
block|{
name|OptionsState
modifier|*
name|state
init|=
name|g_hash_table_lookup
argument_list|(
name|loaded_myb
argument_list|,
name|options
operator|->
name|mybrush
argument_list|)
decl_stmt|;
if|if
condition|(
name|state
condition|)
return|return
name|state
operator|->
name|brush_json
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit


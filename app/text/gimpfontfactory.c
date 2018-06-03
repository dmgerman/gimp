begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfontfactory.c  * Copyright (C) 2003-2018 Michael Natterer<mitch@gimp.org>  *  * Partly based on code Copyright (C) Sven Neumann<sven@gimp.org>  *                                    Manish Singh<yosh@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangocairo.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangofc-fontmap.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-parallel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpasync.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpasyncset.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpfont.h"
end_include

begin_include
include|#
directive|include
file|"gimpfontfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* Use fontconfig directly for speed. We can use the pango stuff when/if  * fontconfig/pango get more efficient.  */
end_comment

begin_define
DECL|macro|USE_FONTCONFIG_DIRECTLY
define|#
directive|define
name|USE_FONTCONFIG_DIRECTLY
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|USE_FONTCONFIG_DIRECTLY
end_ifdef

begin_include
include|#
directive|include
file|<fontconfig/fontconfig.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|CONF_FNAME
define|#
directive|define
name|CONF_FNAME
value|"fonts.conf"
end_define

begin_struct
DECL|struct|_GimpFontFactoryPrivate
struct|struct
name|_GimpFontFactoryPrivate
block|{
DECL|member|foo
name|gpointer
name|foo
decl_stmt|;
comment|/* can't have an empty struct */
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(((GimpFontFactory *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_font_factory_data_init
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|no_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_factory_data_refresh
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_factory_data_save
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpData
modifier|*
name|gimp_font_factory_data_new
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpData
modifier|*
name|gimp_font_factory_data_duplicate
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_font_factory_data_delete
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|gboolean
name|delete_from_disk
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_factory_load
parameter_list|(
name|GimpFontFactory
modifier|*
name|factory
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_font_factory_load_fonts_conf
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|GFile
modifier|*
name|fonts_conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_factory_add_directories
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|GList
modifier|*
name|path
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_factory_recursive_add_fontdir
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_factory_load_names
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|PangoFontMap
modifier|*
name|fontmap
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFontFactory,gimp_font_factory,GIMP_TYPE_DATA_FACTORY)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFontFactory
argument_list|,
argument|gimp_font_factory
argument_list|,
argument|GIMP_TYPE_DATA_FACTORY
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_font_factory_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_font_factory_class_init
parameter_list|(
name|GimpFontFactoryClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpDataFactoryClass
modifier|*
name|factory_class
init|=
name|GIMP_DATA_FACTORY_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|factory_class
operator|->
name|data_init
operator|=
name|gimp_font_factory_data_init
expr_stmt|;
name|factory_class
operator|->
name|data_refresh
operator|=
name|gimp_font_factory_data_refresh
expr_stmt|;
name|factory_class
operator|->
name|data_save
operator|=
name|gimp_font_factory_data_save
expr_stmt|;
name|factory_class
operator|->
name|data_new
operator|=
name|gimp_font_factory_data_new
expr_stmt|;
name|factory_class
operator|->
name|data_duplicate
operator|=
name|gimp_font_factory_data_duplicate
expr_stmt|;
name|factory_class
operator|->
name|data_delete
operator|=
name|gimp_font_factory_data_delete
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpFontFactoryPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_init (GimpFontFactory * factory)
name|gimp_font_factory_init
parameter_list|(
name|GimpFontFactory
modifier|*
name|factory
parameter_list|)
block|{
name|factory
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|factory
argument_list|,
name|GIMP_TYPE_FONT_FACTORY
argument_list|,
name|GimpFontFactoryPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_data_init (GimpDataFactory * factory,GimpContext * context,gboolean no_data)
name|gimp_font_factory_data_init
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|no_data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|no_data
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimp_font_factory_load
argument_list|(
name|GIMP_FONT_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp_data_factory_get_gimp
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_INFO
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_data_refresh (GimpDataFactory * factory,GimpContext * context)
name|gimp_font_factory_data_refresh
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimp_font_factory_load
argument_list|(
name|GIMP_FONT_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp_data_factory_get_gimp
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_INFO
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_data_save (GimpDataFactory * factory)
name|gimp_font_factory_data_save
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|)
block|{
comment|/*  this is not "saving" but this functions is called at the right    *  time at exit to reset the config    */
comment|/* if font loading is in progress in another thread, do nothing.  calling    * FcInitReinitialize() while loading takes place is unsafe.    */
if|if
condition|(
operator|!
name|gimp_async_set_is_empty
argument_list|(
name|gimp_data_factory_get_async_set
argument_list|(
name|factory
argument_list|)
argument_list|)
condition|)
return|return;
comment|/* Reinit the library with defaults. */
name|FcInitReinitialize
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpData
modifier|*
DECL|function|gimp_font_factory_data_new (GimpDataFactory * factory,GimpContext * context,const gchar * name)
name|gimp_font_factory_data_new
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|GimpData
modifier|*
DECL|function|gimp_font_factory_data_duplicate (GimpDataFactory * factory,GimpData * data)
name|gimp_font_factory_data_duplicate
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_font_factory_data_delete (GimpDataFactory * factory,GimpData * data,gboolean delete_from_disk,GError ** error)
name|gimp_font_factory_data_delete
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|gboolean
name|delete_from_disk
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
return|return
name|GIMP_DATA_FACTORY_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|data_delete
argument_list|(
name|factory
argument_list|,
name|data
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpDataFactory
modifier|*
DECL|function|gimp_font_factory_new (Gimp * gimp,const gchar * path_property_name)
name|gimp_font_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path_property_name
parameter_list|)
block|{
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
name|g_return_val_if_fail
argument_list|(
name|path_property_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT_FACTORY
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"data-type"
argument_list|,
name|GIMP_TYPE_FONT
argument_list|,
literal|"path-property-name"
argument_list|,
name|path_property_name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_load_async (GimpAsync * async,FcConfig * config)
name|gimp_font_factory_load_async
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|FcConfig
modifier|*
name|config
parameter_list|)
block|{
if|if
condition|(
name|FcConfigBuildFonts
argument_list|(
name|config
argument_list|)
condition|)
block|{
name|gimp_async_finish
argument_list|(
name|async
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|FcConfigDestroy
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|gimp_async_abort
argument_list|(
name|async
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_load_async_callback (GimpAsync * async,GimpFontFactory * factory)
name|gimp_font_factory_load_async_callback
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|GimpFontFactory
modifier|*
name|factory
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|GIMP_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_async_is_canceled
argument_list|(
name|async
argument_list|)
condition|)
block|{
name|gimp_container_thaw
argument_list|(
name|container
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|gimp_async_is_finished
argument_list|(
name|async
argument_list|)
condition|)
block|{
name|FcConfig
modifier|*
name|config
init|=
name|gimp_async_get_result
argument_list|(
name|async
argument_list|)
decl_stmt|;
name|PangoFontMap
modifier|*
name|fontmap
decl_stmt|;
name|PangoContext
modifier|*
name|context
decl_stmt|;
name|FcConfigSetCurrent
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|fontmap
operator|=
name|pango_cairo_font_map_new_for_font_type
argument_list|(
name|CAIRO_FONT_TYPE_FT
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fontmap
condition|)
name|g_error
argument_list|(
literal|"You are using a Pango that has been built against a cairo "
literal|"that lacks the Freetype font backend"
argument_list|)
expr_stmt|;
name|pango_cairo_font_map_set_resolution
argument_list|(
name|PANGO_CAIRO_FONT_MAP
argument_list|(
name|fontmap
argument_list|)
argument_list|,
literal|72.0
comment|/* FIXME */
argument_list|)
expr_stmt|;
name|context
operator|=
name|pango_font_map_create_context
argument_list|(
name|fontmap
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|fontmap
argument_list|)
expr_stmt|;
name|gimp_font_factory_load_names
argument_list|(
name|container
argument_list|,
name|PANGO_FONT_MAP
argument_list|(
name|fontmap
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gimp_container_thaw
argument_list|(
name|container
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_load (GimpFontFactory * factory,GError ** error)
name|gimp_font_factory_load
parameter_list|(
name|GimpFontFactory
modifier|*
name|factory
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpAsyncSet
modifier|*
name|async_set
decl_stmt|;
name|FcConfig
modifier|*
name|config
decl_stmt|;
name|GFile
modifier|*
name|fonts_conf
decl_stmt|;
name|GList
modifier|*
name|path
decl_stmt|;
name|GimpAsync
modifier|*
name|async
decl_stmt|;
name|async_set
operator|=
name|gimp_data_factory_get_async_set
argument_list|(
name|GIMP_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_async_set_is_empty
argument_list|(
name|async_set
argument_list|)
condition|)
block|{
comment|/* font loading is already in progress */
return|return;
block|}
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|GIMP_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|gimp_data_factory_get_gimp
argument_list|(
name|GIMP_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
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
literal|"Loading fonts\n"
argument_list|)
expr_stmt|;
name|config
operator|=
name|FcInitLoadConfig
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|config
condition|)
return|return;
name|fonts_conf
operator|=
name|gimp_directory_file
argument_list|(
name|CONF_FNAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_font_factory_load_fonts_conf
argument_list|(
name|config
argument_list|,
name|fonts_conf
argument_list|)
condition|)
return|return;
name|fonts_conf
operator|=
name|gimp_sysconf_directory_file
argument_list|(
name|CONF_FNAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_font_factory_load_fonts_conf
argument_list|(
name|config
argument_list|,
name|fonts_conf
argument_list|)
condition|)
return|return;
name|path
operator|=
name|gimp_data_factory_get_data_path
argument_list|(
name|GIMP_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|path
condition|)
return|return;
name|gimp_container_freeze
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|gimp_container_clear
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|gimp_font_factory_add_directories
argument_list|(
name|config
argument_list|,
name|path
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|path
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
comment|/* We perform font cache initialization in a separate thread, so    * in the case a cache rebuild is to be done it will not block    * the UI.    */
name|async
operator|=
name|gimp_parallel_run_async
argument_list|(
name|TRUE
argument_list|,
operator|(
name|GimpParallelRunAsyncFunc
operator|)
name|gimp_font_factory_load_async
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|gimp_async_add_callback
argument_list|(
name|async
argument_list|,
operator|(
name|GimpAsyncCallback
operator|)
name|gimp_font_factory_load_async_callback
argument_list|,
name|factory
argument_list|)
expr_stmt|;
name|gimp_async_set_add
argument_list|(
name|async_set
argument_list|,
name|async
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|async
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_font_factory_load_fonts_conf (FcConfig * config,GFile * fonts_conf)
name|gimp_font_factory_load_fonts_conf
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|GFile
modifier|*
name|fonts_conf
parameter_list|)
block|{
name|gchar
modifier|*
name|path
init|=
name|g_file_get_path
argument_list|(
name|fonts_conf
argument_list|)
decl_stmt|;
name|gboolean
name|ret
init|=
name|TRUE
decl_stmt|;
if|if
condition|(
operator|!
name|FcConfigParseAndLoad
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|path
argument_list|,
name|FcFalse
argument_list|)
condition|)
block|{
name|FcConfigDestroy
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|ret
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|fonts_conf
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_add_directories (FcConfig * config,GList * path,GError ** error)
name|gimp_font_factory_add_directories
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|GList
modifier|*
name|path
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|path
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
comment|/* The configured directories must exist or be created. */
name|g_file_make_directory_with_parents
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Do not use FcConfigAppFontAddDir(). Instead use        * FcConfigAppFontAddFile() with our own recursive loop.        * Otherwise, when some fonts fail to load (e.g. permission        * issues), we end up in weird situations where the fonts are in        * the list, but are unusable and output many errors.        * See bug 748553.        */
name|gimp_font_factory_recursive_add_fontdir
argument_list|(
name|config
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|error
operator|&&
operator|*
name|error
condition|)
block|{
name|gchar
modifier|*
name|font_list
init|=
name|g_strdup
argument_list|(
operator|(
operator|*
name|error
operator|)
operator|->
name|message
argument_list|)
decl_stmt|;
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Some fonts failed to load:\n%s"
argument_list|)
argument_list|,
name|font_list
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|font_list
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_recursive_add_fontdir (FcConfig * config,GFile * file,GError ** error)
name|gimp_font_factory_recursive_add_fontdir
parameter_list|(
name|FcConfig
modifier|*
name|config
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFileEnumerator
modifier|*
name|enumerator
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|config
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|enumerator
operator|=
name|g_file_enumerate_children
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_NAME
literal|","
name|G_FILE_ATTRIBUTE_STANDARD_IS_HIDDEN
literal|","
name|G_FILE_ATTRIBUTE_STANDARD_TYPE
literal|","
name|G_FILE_ATTRIBUTE_TIME_MODIFIED
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|enumerator
condition|)
block|{
name|GFileInfo
modifier|*
name|info
decl_stmt|;
while|while
condition|(
operator|(
name|info
operator|=
name|g_file_enumerator_next_file
argument_list|(
name|enumerator
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|)
condition|)
block|{
name|GFileType
name|file_type
decl_stmt|;
name|GFile
modifier|*
name|child
decl_stmt|;
if|if
condition|(
name|g_file_info_get_is_hidden
argument_list|(
name|info
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|file_type
operator|=
name|g_file_info_get_file_type
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|child
operator|=
name|g_file_enumerator_get_child
argument_list|(
name|enumerator
argument_list|,
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_type
operator|==
name|G_FILE_TYPE_DIRECTORY
condition|)
block|{
name|gimp_font_factory_recursive_add_fontdir
argument_list|(
name|config
argument_list|,
name|child
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|file_type
operator|==
name|G_FILE_TYPE_REGULAR
condition|)
block|{
name|gchar
modifier|*
name|path
init|=
name|g_file_get_path
argument_list|(
name|child
argument_list|)
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|gchar
modifier|*
name|tmp
init|=
name|g_win32_locale_filename_from_utf8
argument_list|(
name|path
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
comment|/* XXX: g_win32_locale_filename_from_utf8() may return                * NULL. So we need to check that path is not NULL before                * trying to load with fontconfig.                */
name|path
operator|=
name|tmp
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|path
operator|||
name|FcFalse
operator|==
name|FcConfigAppFontAddFile
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|FcChar8
operator|*
operator|)
name|path
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: adding font file '%s' failed.\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
if|if
condition|(
operator|*
name|error
condition|)
block|{
name|gchar
modifier|*
name|current_message
init|=
name|g_strdup
argument_list|(
operator|(
operator|*
name|error
operator|)
operator|->
name|message
argument_list|)
decl_stmt|;
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"%s\n- %s"
argument_list|,
name|current_message
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|current_message
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"- %s"
argument_list|,
name|path
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|child
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|error
condition|)
block|{
name|gchar
modifier|*
name|path
init|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
decl_stmt|;
if|if
condition|(
operator|*
name|error
condition|)
block|{
name|gchar
modifier|*
name|current_message
init|=
name|g_strdup
argument_list|(
operator|(
operator|*
name|error
operator|)
operator|->
name|message
argument_list|)
decl_stmt|;
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"%s\n- %s%s"
argument_list|,
name|current_message
argument_list|,
name|path
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|current_message
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"- %s%s"
argument_list|,
name|path
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_add_font (GimpContainer * container,PangoContext * context,PangoFontDescription * desc)
name|gimp_font_factory_add_font
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|,
name|PangoFontDescription
modifier|*
name|desc
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
operator|!
name|desc
condition|)
return|return;
name|name
operator|=
name|pango_font_description_to_string
argument_list|(
name|desc
argument_list|)
expr_stmt|;
comment|/* It doesn't look like pango_font_description_to_string() could ever    * return NULL. But just to be double sure and avoid a segfault, I    * check before validating the string.    */
if|if
condition|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
operator|>
literal|0
operator|&&
name|g_utf8_validate
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GimpFont
modifier|*
name|font
decl_stmt|;
name|font
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"pango-context"
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|font
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|font
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|USE_FONTCONFIG_DIRECTLY
end_ifdef

begin_comment
comment|/* We're really chummy here with the implementation. Oh well. */
end_comment

begin_comment
comment|/* This is copied straight from make_alias_description in pango, plus  * the gimp_font_list_add_font bits.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_make_alias (GimpContainer * container,PangoContext * context,const gchar * family,gboolean bold,gboolean italic)
name|gimp_font_factory_make_alias
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|family
parameter_list|,
name|gboolean
name|bold
parameter_list|,
name|gboolean
name|italic
parameter_list|)
block|{
name|PangoFontDescription
modifier|*
name|desc
init|=
name|pango_font_description_new
argument_list|()
decl_stmt|;
name|pango_font_description_set_family
argument_list|(
name|desc
argument_list|,
name|family
argument_list|)
expr_stmt|;
name|pango_font_description_set_style
argument_list|(
name|desc
argument_list|,
name|italic
condition|?
name|PANGO_STYLE_ITALIC
else|:
name|PANGO_STYLE_NORMAL
argument_list|)
expr_stmt|;
name|pango_font_description_set_variant
argument_list|(
name|desc
argument_list|,
name|PANGO_VARIANT_NORMAL
argument_list|)
expr_stmt|;
name|pango_font_description_set_weight
argument_list|(
name|desc
argument_list|,
name|bold
condition|?
name|PANGO_WEIGHT_BOLD
else|:
name|PANGO_WEIGHT_NORMAL
argument_list|)
expr_stmt|;
name|pango_font_description_set_stretch
argument_list|(
name|desc
argument_list|,
name|PANGO_STRETCH_NORMAL
argument_list|)
expr_stmt|;
name|gimp_font_factory_add_font
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_load_aliases (GimpContainer * container,PangoContext * context)
name|gimp_font_factory_load_aliases
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|families
index|[]
init|=
block|{
literal|"Sans-serif"
block|,
literal|"Serif"
block|,
literal|"Monospace"
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
name|gimp_font_factory_make_alias
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_font_factory_make_alias
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_font_factory_make_alias
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_font_factory_make_alias
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_load_names (GimpContainer * container,PangoFontMap * fontmap,PangoContext * context)
name|gimp_font_factory_load_names
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|PangoFontMap
modifier|*
name|fontmap
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
block|{
name|FcObjectSet
modifier|*
name|os
decl_stmt|;
name|FcPattern
modifier|*
name|pat
decl_stmt|;
name|FcFontSet
modifier|*
name|fontset
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|os
operator|=
name|FcObjectSetBuild
argument_list|(
name|FC_FAMILY
argument_list|,
name|FC_STYLE
argument_list|,
name|FC_SLANT
argument_list|,
name|FC_WEIGHT
argument_list|,
name|FC_WIDTH
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|os
argument_list|)
expr_stmt|;
name|pat
operator|=
name|FcPatternCreate
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|pat
condition|)
block|{
name|FcObjectSetDestroy
argument_list|(
name|os
argument_list|)
expr_stmt|;
name|g_critical
argument_list|(
literal|"%s: FcPatternCreate() returned NULL."
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
name|fontset
operator|=
name|FcFontList
argument_list|(
name|NULL
argument_list|,
name|pat
argument_list|,
name|os
argument_list|)
expr_stmt|;
name|FcPatternDestroy
argument_list|(
name|pat
argument_list|)
expr_stmt|;
name|FcObjectSetDestroy
argument_list|(
name|os
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|fontset
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|fontset
operator|->
name|nfont
condition|;
name|i
operator|++
control|)
block|{
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|desc
operator|=
name|pango_fc_font_description_from_pattern
argument_list|(
name|fontset
operator|->
name|fonts
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_font_factory_add_font
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
comment|/*  only create aliases if there is at least one font available  */
if|if
condition|(
name|fontset
operator|->
name|nfont
operator|>
literal|0
condition|)
name|gimp_font_factory_load_aliases
argument_list|(
name|container
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|FcFontSetDestroy
argument_list|(
name|fontset
argument_list|)
expr_stmt|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* ! USE_FONTCONFIG_DIRECTLY */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_font_factory_load_names (GimpContainer * container,PangoFontMap * fontmap,PangoContext * context)
name|gimp_font_factory_load_names
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|PangoFontMap
modifier|*
name|fontmap
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
block|{
name|PangoFontFamily
modifier|*
modifier|*
name|families
decl_stmt|;
name|PangoFontFace
modifier|*
modifier|*
name|faces
decl_stmt|;
name|gint
name|n_families
decl_stmt|;
name|gint
name|n_faces
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|pango_font_map_list_families
argument_list|(
name|fontmap
argument_list|,
operator|&
name|families
argument_list|,
operator|&
name|n_families
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_families
condition|;
name|i
operator|++
control|)
block|{
name|pango_font_family_list_faces
argument_list|(
name|families
index|[
name|i
index|]
argument_list|,
operator|&
name|faces
argument_list|,
operator|&
name|n_faces
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|n_faces
condition|;
name|j
operator|++
control|)
block|{
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|desc
operator|=
name|pango_font_face_describe
argument_list|(
name|faces
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|gimp_font_factory_add_font
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|families
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* USE_FONTCONFIG_DIRECTLY */
end_comment

end_unit


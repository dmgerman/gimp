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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-new.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasite.h"
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
name|gimp_class_init
parameter_list|(
name|GimpClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_get_type (void)
name|gimp_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|object_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|object_type
condition|)
block|{
name|GtkTypeInfo
name|object_info
init|=
block|{
literal|"Gimp"
block|,
sizeof|sizeof
argument_list|(
name|Gimp
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|object_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
operator|&
name|object_info
argument_list|)
expr_stmt|;
block|}
return|return
name|object_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_class_init (GimpClass * klass)
name|gimp_class_init
parameter_list|(
name|GimpClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_init (Gimp * gimp)
name|gimp_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|brush_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_brush_load
block|,
name|GIMP_BRUSH_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_brush_load
block|,
name|GIMP_BRUSH_PIXMAP_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_brush_generated_load
block|,
name|GIMP_BRUSH_GENERATED_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_brush_pipe_load
block|,
name|GIMP_BRUSH_PIPE_FILE_EXTENSION
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_brush_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|brush_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|brush_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|pattern_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_pattern_load
block|,
name|GIMP_PATTERN_FILE_EXTENSION
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_pattern_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|pattern_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|pattern_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|gradient_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_gradient_load
block|,
name|GIMP_GRADIENT_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_gradient_load
block|,
name|NULL
comment|/* legacy loader */
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_gradient_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|gradient_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|gradient_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|palette_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_palette_load
block|,
name|GIMP_PALETTE_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_palette_load
block|,
name|NULL
comment|/* legacy loader */
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_palette_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|palette_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|palette_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
name|gimp
operator|->
name|images
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_CONTAINER_POLICY_WEAK
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|images
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|images
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|global_buffer
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|named_buffers
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_BUFFER
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_parasites_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|brush_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|gimprc
operator|.
name|brush_path
argument_list|,
name|brush_loader_entries
argument_list|,
name|n_brush_loader_entries
argument_list|,
name|gimp_brush_new
argument_list|,
name|gimp_brush_get_standard
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|pattern_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|gimprc
operator|.
name|pattern_path
argument_list|,
name|pattern_loader_entries
argument_list|,
name|n_pattern_loader_entries
argument_list|,
name|gimp_pattern_new
argument_list|,
name|gimp_pattern_get_standard
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|gradient_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_GRADIENT
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|gimprc
operator|.
name|gradient_path
argument_list|,
name|gradient_loader_entries
argument_list|,
name|n_gradient_loader_entries
argument_list|,
name|gimp_gradient_new
argument_list|,
name|gimp_gradient_get_standard
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|palette_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|gimprc
operator|.
name|palette_path
argument_list|,
name|palette_loader_entries
argument_list|,
name|n_palette_loader_entries
argument_list|,
name|gimp_palette_new
argument_list|,
name|gimp_palette_get_standard
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|tool_info_list
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_TOOL_INFO
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|)
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_new_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_destroy (GtkObject * object)
name|gimp_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_image_new_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|tool_info_list
condition|)
block|{
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|tool_info_list
operator|=
name|NULL
expr_stmt|;
block|}
name|procedural_db_free
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|brush_factory
condition|)
block|{
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|brush_factory
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|pattern_factory
condition|)
block|{
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|pattern_factory
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|gradient_factory
condition|)
block|{
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|gradient_factory
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|palette_factory
condition|)
block|{
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|palette_factory
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_parasites_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|named_buffers
condition|)
block|{
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|named_buffers
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|global_buffer
condition|)
block|{
name|tile_manager_destroy
argument_list|(
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|global_buffer
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|images
condition|)
block|{
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|images
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|images
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Gimp
modifier|*
DECL|function|gimp_new (void)
name|gimp_new
parameter_list|(
name|void
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gimp
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_GIMP
argument_list|)
expr_stmt|;
return|return
name|gimp
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_restore (Gimp * gimp)
name|gimp_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  initialize  the global parasite table  */
name|app_init_update_status
argument_list|(
name|_
argument_list|(
literal|"Looking for data files"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Parasites"
argument_list|)
argument_list|,
literal|0.00
argument_list|)
expr_stmt|;
name|gimp_parasiterc_load
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp brushes    */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Brushes"
argument_list|)
argument_list|,
literal|0.20
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp patterns   */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Patterns"
argument_list|)
argument_list|,
literal|0.40
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp palettes   */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Palettes"
argument_list|)
argument_list|,
literal|0.60
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp gradients  */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gradients"
argument_list|)
argument_list|,
literal|0.80
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1.00
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_shutdown (Gimp * gimp)
name|gimp_shutdown
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gimp_data_factory_data_save
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_save
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_save
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_save
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
name|gimp_parasiterc_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_create_image (Gimp * gimp,gint width,gint height,GimpImageBaseType type)
name|gimp_create_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageBaseType
name|type
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|gimage
operator|=
name|gimage_new
argument_list|(
name|gimp
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return
name|gimage
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_create_display (Gimp * gimp,GimpImage * gimage)
name|gimp_create_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|create_display_func
condition|)
name|gimp
operator|->
name|create_display_func
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


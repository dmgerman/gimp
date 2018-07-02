begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-data-factories.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gradients.h"
end_include

begin_include
include|#
directive|include
file|"gimp-memsize.h"
end_include

begin_include
include|#
directive|include
file|"gimp-palettes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushclipboard.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpdataloaderfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamics-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrush-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrush.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette-load.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern-load.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimppatternclipboard.h"
end_include

begin_include
include|#
directive|include
file|"gimptagcache.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpreset.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpreset-load.h"
end_include

begin_include
include|#
directive|include
file|"text/gimpfontfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_data_factories_init (Gimp * gimp)
name|gimp_data_factories_init
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
name|gimp
operator|->
name|brush_factory
operator|=
name|gimp_data_loader_factory_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|,
literal|"brush-path"
argument_list|,
literal|"brush-path-writable"
argument_list|,
literal|"brush-paths"
argument_list|,
name|gimp_brush_new
argument_list|,
name|gimp_brush_get_standard
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|,
literal|"brush factory"
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
literal|"GIMP Brush"
argument_list|,
name|gimp_brush_load
argument_list|,
name|GIMP_BRUSH_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
literal|"GIMP Brush Pixmap"
argument_list|,
name|gimp_brush_load
argument_list|,
name|GIMP_BRUSH_PIXMAP_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
literal|"Photoshop ABR Brush"
argument_list|,
name|gimp_brush_load_abr
argument_list|,
name|GIMP_BRUSH_PS_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
literal|"Paint Shop Pro JBR Brush"
argument_list|,
name|gimp_brush_load_abr
argument_list|,
name|GIMP_BRUSH_PSP_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
literal|"GIMP Generated Brush"
argument_list|,
name|gimp_brush_generated_load
argument_list|,
name|GIMP_BRUSH_GENERATED_FILE_EXTENSION
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
literal|"GIMP Brush Pipe"
argument_list|,
name|gimp_brush_pipe_load
argument_list|,
name|GIMP_BRUSH_PIPE_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|dynamics_factory
operator|=
name|gimp_data_loader_factory_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_DYNAMICS
argument_list|,
literal|"dynamics-path"
argument_list|,
literal|"dynamics-path-writable"
argument_list|,
literal|"dynamics-paths"
argument_list|,
name|gimp_dynamics_new
argument_list|,
name|gimp_dynamics_get_standard
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|dynamics_factory
argument_list|)
argument_list|,
literal|"dynamics factory"
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|dynamics_factory
argument_list|,
literal|"GIMP Paint Dynamics"
argument_list|,
name|gimp_dynamics_load
argument_list|,
name|GIMP_DYNAMICS_FILE_EXTENSION
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|mybrush_factory
operator|=
name|gimp_data_loader_factory_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_MYBRUSH
argument_list|,
literal|"mypaint-brush-path"
argument_list|,
literal|"mypaint-brush-path-writable"
argument_list|,
literal|"mypaint-brush-paths"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|mybrush_factory
argument_list|)
argument_list|,
literal|"mypaint brush factory"
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|mybrush_factory
argument_list|,
literal|"MyPaint Brush"
argument_list|,
name|gimp_mybrush_load
argument_list|,
name|GIMP_MYBRUSH_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|pattern_factory
operator|=
name|gimp_data_loader_factory_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
literal|"pattern-path"
argument_list|,
literal|"pattern-path-writable"
argument_list|,
literal|"pattern-paths"
argument_list|,
name|NULL
argument_list|,
name|gimp_pattern_get_standard
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
argument_list|,
literal|"pattern factory"
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|,
literal|"GIMP Pattern"
argument_list|,
name|gimp_pattern_load
argument_list|,
name|GIMP_PATTERN_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_fallback
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|,
literal|"Pattern from GdkPixbuf"
argument_list|,
name|gimp_pattern_load_pixbuf
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|gradient_factory
operator|=
name|gimp_data_loader_factory_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_GRADIENT
argument_list|,
literal|"gradient-path"
argument_list|,
literal|"gradient-path-writable"
argument_list|,
literal|"gradient-paths"
argument_list|,
name|gimp_gradient_new
argument_list|,
name|gimp_gradient_get_standard
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|,
literal|"gradient factory"
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|,
literal|"GIMP Gradient"
argument_list|,
name|gimp_gradient_load
argument_list|,
name|GIMP_GRADIENT_FILE_EXTENSION
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|,
literal|"SVG Gradient"
argument_list|,
name|gimp_gradient_load_svg
argument_list|,
name|GIMP_GRADIENT_SVG_FILE_EXTENSION
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|palette_factory
operator|=
name|gimp_data_loader_factory_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_PALETTE
argument_list|,
literal|"palette-path"
argument_list|,
literal|"palette-path-writable"
argument_list|,
literal|"palette-paths"
argument_list|,
name|gimp_palette_new
argument_list|,
name|gimp_palette_get_standard
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|,
literal|"palette factory"
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|,
literal|"GIMP Palette"
argument_list|,
name|gimp_palette_load
argument_list|,
name|GIMP_PALETTE_FILE_EXTENSION
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|font_factory
operator|=
name|gimp_font_factory_new
argument_list|(
name|gimp
argument_list|,
literal|"font-path"
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|font_factory
argument_list|)
argument_list|,
literal|"font factory"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|tool_preset_factory
operator|=
name|gimp_data_loader_factory_new
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_TOOL_PRESET
argument_list|,
literal|"tool-preset-path"
argument_list|,
literal|"tool-preset-path-writable"
argument_list|,
literal|"tool-preset-paths"
argument_list|,
name|gimp_tool_preset_new
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|)
argument_list|,
literal|"tool preset factory"
argument_list|)
expr_stmt|;
name|gimp_data_loader_factory_add_loader
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|,
literal|"GIMP Tool Preset"
argument_list|,
name|gimp_tool_preset_load
argument_list|,
name|GIMP_TOOL_PRESET_FILE_EXTENSION
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|tag_cache
operator|=
name|gimp_tag_cache_new
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factories_add_builtin (Gimp * gimp)
name|gimp_data_factories_add_builtin
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpData
modifier|*
name|data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  add the builtin FG -> BG etc. gradients  */
name|gimp_gradients_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  add the color history palette  */
name|gimp_palettes_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  add the clipboard brushes  */
name|data
operator|=
name|gimp_brush_clipboard_new
argument_list|(
name|gimp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|data
argument_list|,
literal|"gimp-brush-clipboard-image"
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_brush_clipboard_new
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|data
argument_list|,
literal|"gimp-brush-clipboard-mask"
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/*  add the clipboard pattern  */
name|data
operator|=
name|gimp_pattern_clipboard_new
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|data
argument_list|,
literal|"gimp-pattern-clipboard-image"
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factories_clear (Gimp * gimp)
name|gimp_data_factories_clear
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
name|brush_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|dynamics_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|dynamics_factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|mybrush_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|mybrush_factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|pattern_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|gradient_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|palette_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|font_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|font_factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|tool_preset_factory
condition|)
name|gimp_data_factory_data_free
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factories_exit (Gimp * gimp)
name|gimp_data_factories_exit
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
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|brush_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|dynamics_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|mybrush_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|pattern_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|gradient_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|font_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|tool_preset_factory
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|gimp
operator|->
name|tag_cache
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint64
DECL|function|gimp_data_factories_get_memsize (Gimp * gimp,gint64 * gui_size)
name|gimp_data_factories_get_memsize
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|dynamics_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|mybrush_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|font_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|)
argument_list|,
name|gui_size
argument_list|)
expr_stmt|;
return|return
name|memsize
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factories_data_clean (Gimp * gimp)
name|gimp_data_factories_data_clean
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
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|dynamics_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|mybrush_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|font_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_clean
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factories_load (Gimp * gimp,GimpInitStatusFunc status_callback)
name|gimp_data_factories_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
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
comment|/*  initialize the list of gimp brushes    */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Brushes"
argument_list|)
argument_list|,
literal|0.1
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp dynamics   */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Dynamics"
argument_list|)
argument_list|,
literal|0.15
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|dynamics_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of mypaint brushes    */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"MyPaint Brushes"
argument_list|)
argument_list|,
literal|0.2
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|mybrush_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp patterns   */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Patterns"
argument_list|)
argument_list|,
literal|0.3
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp palettes   */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Palettes"
argument_list|)
argument_list|,
literal|0.4
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp gradients  */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gradients"
argument_list|)
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the color history   */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color History"
argument_list|)
argument_list|,
literal|0.55
argument_list|)
expr_stmt|;
name|gimp_palettes_load
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp fonts   */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Fonts"
argument_list|)
argument_list|,
literal|0.6
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|font_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_fonts
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp tool presets if we have a GUI  */
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
block|{
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Tool Presets"
argument_list|)
argument_list|,
literal|0.7
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|,
name|gimp
operator|->
name|user_context
argument_list|,
name|gimp
operator|->
name|no_data
argument_list|)
expr_stmt|;
block|}
comment|/* update tag cache */
name|status_callback
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Updating tag cache"
argument_list|)
argument_list|,
literal|0.75
argument_list|)
expr_stmt|;
name|gimp_tag_cache_load
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|dynamics_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|mybrush_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|pattern_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|font_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tag_cache_add_container
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_factories_save (Gimp * gimp)
name|gimp_data_factories_save
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
name|gimp_tag_cache_save
argument_list|(
name|gimp
operator|->
name|tag_cache
argument_list|)
expr_stmt|;
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
name|dynamics_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_save
argument_list|(
name|gimp
operator|->
name|mybrush_factory
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
name|gimp_data_factory_data_save
argument_list|(
name|gimp
operator|->
name|font_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_save
argument_list|(
name|gimp
operator|->
name|tool_preset_factory
argument_list|)
expr_stmt|;
name|gimp_palettes_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


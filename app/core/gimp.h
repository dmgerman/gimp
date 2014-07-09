begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_H__
define|#
directive|define
name|__GIMP_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gui.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_GIMP
define|#
directive|define
name|GIMP_TYPE_GIMP
value|(gimp_get_type ())
end_define

begin_define
DECL|macro|GIMP (obj)
define|#
directive|define
name|GIMP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GIMP, Gimp))
end_define

begin_define
DECL|macro|GIMP_CLASS (klass)
define|#
directive|define
name|GIMP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GIMP, GimpClass))
end_define

begin_define
DECL|macro|GIMP_IS_GIMP (obj)
define|#
directive|define
name|GIMP_IS_GIMP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GIMP))
end_define

begin_define
DECL|macro|GIMP_IS_GIMP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GIMP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GIMP))
end_define

begin_typedef
DECL|typedef|GimpClass
typedef|typedef
name|struct
name|_GimpClass
name|GimpClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Gimp
struct|struct
name|_Gimp
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|config
name|GimpCoreConfig
modifier|*
name|config
decl_stmt|;
DECL|member|edit_config
name|GimpCoreConfig
modifier|*
name|edit_config
decl_stmt|;
comment|/* don't use this one, it's just                                         * for the preferences dialog                                         */
DECL|member|session_name
name|gchar
modifier|*
name|session_name
decl_stmt|;
DECL|member|default_folder
name|GFile
modifier|*
name|default_folder
decl_stmt|;
DECL|member|be_verbose
name|gboolean
name|be_verbose
decl_stmt|;
DECL|member|no_data
name|gboolean
name|no_data
decl_stmt|;
DECL|member|no_fonts
name|gboolean
name|no_fonts
decl_stmt|;
DECL|member|no_interface
name|gboolean
name|no_interface
decl_stmt|;
DECL|member|show_gui
name|gboolean
name|show_gui
decl_stmt|;
DECL|member|use_shm
name|gboolean
name|use_shm
decl_stmt|;
DECL|member|use_cpu_accel
name|gboolean
name|use_cpu_accel
decl_stmt|;
DECL|member|message_handler
name|GimpMessageHandlerType
name|message_handler
decl_stmt|;
DECL|member|console_messages
name|gboolean
name|console_messages
decl_stmt|;
DECL|member|stack_trace_mode
name|GimpStackTraceMode
name|stack_trace_mode
decl_stmt|;
DECL|member|pdb_compat_mode
name|GimpPDBCompatMode
name|pdb_compat_mode
decl_stmt|;
DECL|member|gui
name|GimpGui
name|gui
decl_stmt|;
comment|/* gui vtable */
DECL|member|restored
name|gboolean
name|restored
decl_stmt|;
comment|/* becomes TRUE in gimp_restore() */
DECL|member|busy
name|gint
name|busy
decl_stmt|;
DECL|member|busy_idle_id
name|guint
name|busy_idle_id
decl_stmt|;
DECL|member|user_units
name|GList
modifier|*
name|user_units
decl_stmt|;
DECL|member|n_user_units
name|gint
name|n_user_units
decl_stmt|;
DECL|member|parasites
name|GimpParasiteList
modifier|*
name|parasites
decl_stmt|;
DECL|member|paint_info_list
name|GimpContainer
modifier|*
name|paint_info_list
decl_stmt|;
DECL|member|standard_paint_info
name|GimpPaintInfo
modifier|*
name|standard_paint_info
decl_stmt|;
DECL|member|module_db
name|GimpModuleDB
modifier|*
name|module_db
decl_stmt|;
DECL|member|write_modulerc
name|gboolean
name|write_modulerc
decl_stmt|;
DECL|member|plug_in_manager
name|GimpPlugInManager
modifier|*
name|plug_in_manager
decl_stmt|;
DECL|member|images
name|GimpContainer
modifier|*
name|images
decl_stmt|;
DECL|member|next_guide_ID
name|guint32
name|next_guide_ID
decl_stmt|;
DECL|member|next_sample_point_ID
name|guint32
name|next_sample_point_ID
decl_stmt|;
DECL|member|image_table
name|GimpIdTable
modifier|*
name|image_table
decl_stmt|;
DECL|member|item_table
name|GimpIdTable
modifier|*
name|item_table
decl_stmt|;
DECL|member|displays
name|GimpContainer
modifier|*
name|displays
decl_stmt|;
DECL|member|next_display_ID
name|gint
name|next_display_ID
decl_stmt|;
DECL|member|image_windows
name|GList
modifier|*
name|image_windows
decl_stmt|;
DECL|member|global_buffer
name|GimpBuffer
modifier|*
name|global_buffer
decl_stmt|;
DECL|member|named_buffers
name|GimpContainer
modifier|*
name|named_buffers
decl_stmt|;
DECL|member|fonts
name|GimpContainer
modifier|*
name|fonts
decl_stmt|;
DECL|member|brush_factory
name|GimpDataFactory
modifier|*
name|brush_factory
decl_stmt|;
DECL|member|dynamics_factory
name|GimpDataFactory
modifier|*
name|dynamics_factory
decl_stmt|;
DECL|member|pattern_factory
name|GimpDataFactory
modifier|*
name|pattern_factory
decl_stmt|;
DECL|member|gradient_factory
name|GimpDataFactory
modifier|*
name|gradient_factory
decl_stmt|;
DECL|member|palette_factory
name|GimpDataFactory
modifier|*
name|palette_factory
decl_stmt|;
DECL|member|tool_preset_factory
name|GimpDataFactory
modifier|*
name|tool_preset_factory
decl_stmt|;
DECL|member|tag_cache
name|GimpTagCache
modifier|*
name|tag_cache
decl_stmt|;
DECL|member|pdb
name|GimpPDB
modifier|*
name|pdb
decl_stmt|;
DECL|member|tool_info_list
name|GimpContainer
modifier|*
name|tool_info_list
decl_stmt|;
DECL|member|standard_tool_info
name|GimpToolInfo
modifier|*
name|standard_tool_info
decl_stmt|;
comment|/*  the opened and saved images in MRU order  */
DECL|member|documents
name|GimpContainer
modifier|*
name|documents
decl_stmt|;
comment|/*  image_new values  */
DECL|member|templates
name|GimpContainer
modifier|*
name|templates
decl_stmt|;
DECL|member|image_new_last_template
name|GimpTemplate
modifier|*
name|image_new_last_template
decl_stmt|;
comment|/*  the list of all contexts  */
DECL|member|context_list
name|GList
modifier|*
name|context_list
decl_stmt|;
comment|/*  the default context which is initialized from gimprc  */
DECL|member|default_context
name|GimpContext
modifier|*
name|default_context
decl_stmt|;
comment|/*  the context used by the interface  */
DECL|member|user_context
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpClass
struct|struct
name|_GimpClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|initialize
name|void
function_decl|(
modifier|*
name|initialize
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
DECL|member|restore
name|void
function_decl|(
modifier|*
name|restore
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
DECL|member|exit
name|gboolean
function_decl|(
modifier|*
name|exit
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|force
parameter_list|)
function_decl|;
DECL|member|buffer_changed
name|void
function_decl|(
modifier|*
name|buffer_changed
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
comment|/*  emitted if an image is loaded and opened with a display  */
DECL|member|image_opened
name|void
function_decl|(
modifier|*
name|image_opened
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|Gimp
modifier|*
name|gimp_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|session_name
parameter_list|,
name|GFile
modifier|*
name|default_folder
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|gboolean
name|no_data
parameter_list|,
name|gboolean
name|no_fonts
parameter_list|,
name|gboolean
name|no_interface
parameter_list|,
name|gboolean
name|use_shm
parameter_list|,
name|gboolean
name|use_cpu_accel
parameter_list|,
name|gboolean
name|console_messages
parameter_list|,
name|GimpStackTraceMode
name|stack_trace_mode
parameter_list|,
name|GimpPDBCompatMode
name|pdb_compat_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_show_gui
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|show_gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_get_show_gui
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_load_config
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_system_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_gimprc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_initialize
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_is_restored
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|force
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_get_image_iter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_get_display_iter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_get_image_windows
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_get_paint_info_iter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_get_tool_info_iter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_global_buffer
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
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
parameter_list|,
name|GimpPrecision
name|precision
parameter_list|,
name|gboolean
name|attach_comment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_default_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_get_default_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_user_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_get_user_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolInfo
modifier|*
name|gimp_get_tool_info
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tool_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_message
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|handler
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|4
operator|,
function_decl|5
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_message_valist
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|handler
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|4
operator|,
function_decl|0
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_message_literal
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|handler
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_opened
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_get_temp_filename
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpimage-new.h"
end_include

begin_typedef
DECL|typedef|GimpThreadFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpThreadFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpCreateDisplayFunc
typedef|typedef
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|GimpCreateDisplayFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guint
name|scale
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpSetBusyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSetBusyFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpUnsetBusyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpUnsetBusyFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpMessageFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpMessageFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_typedef

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
comment|/* don't use this one, it's just                                        * for the preferences dialog                                        */
DECL|member|be_verbose
name|gboolean
name|be_verbose
decl_stmt|;
DECL|member|no_data
name|gboolean
name|no_data
decl_stmt|;
DECL|member|no_interface
name|gboolean
name|no_interface
decl_stmt|;
DECL|member|use_shm
name|gboolean
name|use_shm
decl_stmt|;
DECL|member|message_handler
name|GimpMessageHandlerType
name|message_handler
decl_stmt|;
DECL|member|stack_trace_mode
name|GimpStackTraceMode
name|stack_trace_mode
decl_stmt|;
DECL|member|gui_threads_enter_func
name|GimpThreadFunc
name|gui_threads_enter_func
decl_stmt|;
DECL|member|gui_threads_leave_func
name|GimpThreadFunc
name|gui_threads_leave_func
decl_stmt|;
DECL|member|gui_create_display_func
name|GimpCreateDisplayFunc
name|gui_create_display_func
decl_stmt|;
DECL|member|gui_set_busy_func
name|GimpSetBusyFunc
name|gui_set_busy_func
decl_stmt|;
DECL|member|gui_unset_busy_func
name|GimpUnsetBusyFunc
name|gui_unset_busy_func
decl_stmt|;
DECL|member|gui_message_func
name|GimpMessageFunc
name|gui_message_func
decl_stmt|;
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
DECL|member|module_db
name|GimpModuleDB
modifier|*
name|module_db
decl_stmt|;
DECL|member|write_modulerc
name|gboolean
name|write_modulerc
decl_stmt|;
DECL|member|plug_in_defs
name|GSList
modifier|*
name|plug_in_defs
decl_stmt|;
DECL|member|write_pluginrc
name|gboolean
name|write_pluginrc
decl_stmt|;
DECL|member|plug_in_proc_defs
name|GSList
modifier|*
name|plug_in_proc_defs
decl_stmt|;
DECL|member|plug_in_locale_domains
name|GSList
modifier|*
name|plug_in_locale_domains
decl_stmt|;
DECL|member|plug_in_help_paths
name|GSList
modifier|*
name|plug_in_help_paths
decl_stmt|;
DECL|member|current_plug_in
name|PlugIn
modifier|*
name|current_plug_in
decl_stmt|;
DECL|member|open_plug_ins
name|GSList
modifier|*
name|open_plug_ins
decl_stmt|;
DECL|member|plug_in_stack
name|GSList
modifier|*
name|plug_in_stack
decl_stmt|;
DECL|member|last_plug_in
name|ProcRecord
modifier|*
name|last_plug_in
decl_stmt|;
DECL|member|plug_in_shm
name|PlugInShm
modifier|*
name|plug_in_shm
decl_stmt|;
DECL|member|environ_table
name|GimpEnvironTable
modifier|*
name|environ_table
decl_stmt|;
DECL|member|plug_in_debug
name|GimpPlugInDebug
modifier|*
name|plug_in_debug
decl_stmt|;
DECL|member|images
name|GimpContainer
modifier|*
name|images
decl_stmt|;
DECL|member|next_image_ID
name|gint
name|next_image_ID
decl_stmt|;
DECL|member|next_guide_ID
name|guint32
name|next_guide_ID
decl_stmt|;
DECL|member|image_table
name|GHashTable
modifier|*
name|image_table
decl_stmt|;
DECL|member|next_item_ID
name|gint
name|next_item_ID
decl_stmt|;
DECL|member|item_table
name|GHashTable
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
DECL|member|brush_factory
name|GimpDataFactory
modifier|*
name|brush_factory
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
DECL|member|procedural_ht
name|GHashTable
modifier|*
name|procedural_ht
decl_stmt|;
DECL|member|procedural_db_data_list
name|GList
modifier|*
name|procedural_db_data_list
decl_stmt|;
DECL|member|load_procs
name|GSList
modifier|*
name|load_procs
decl_stmt|;
DECL|member|save_procs
name|GSList
modifier|*
name|save_procs
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
DECL|member|image_new_last_values
name|GimpImageNewValues
name|image_new_last_values
decl_stmt|;
DECL|member|have_current_cut_buffer
name|gboolean
name|have_current_cut_buffer
decl_stmt|;
comment|/*  the list of all contexts  */
DECL|member|context_list
name|GList
modifier|*
name|context_list
decl_stmt|;
comment|/*  the hardcoded standard context  */
DECL|member|standard_context
name|GimpContext
modifier|*
name|standard_context
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
comment|/*  the currently active context  */
DECL|member|current_context
name|GimpContext
modifier|*
name|current_context
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
name|kill_it
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
name|gboolean
name|be_verbose
parameter_list|,
name|gboolean
name|no_data
parameter_list|,
name|gboolean
name|no_interface
parameter_list|,
name|gboolean
name|use_shm
parameter_list|,
name|GimpStackTraceMode
name|stack_trace_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_config
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpCoreConfig
modifier|*
name|core_config
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
parameter_list|,
name|gboolean
name|no_data
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
name|kill_it
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_threads_enter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_threads_leave
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy_until_idle
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
specifier|const
name|gchar
modifier|*
name|message
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
name|gboolean
name|attach_comment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_create_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guint
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_get_standard_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|void
name|gimp_set_current_context
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
name|gimp_get_current_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
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


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpactiongroup.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ACTION_GROUP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ACTION_GROUP_H__
define|#
directive|define
name|__GIMP_ACTION_GROUP_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkactiongroup.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_ACTION_GROUP
define|#
directive|define
name|GIMP_TYPE_ACTION_GROUP
value|(gimp_action_group_get_type ())
end_define

begin_define
DECL|macro|GIMP_ACTION_GROUP (obj)
define|#
directive|define
name|GIMP_ACTION_GROUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ACTION_GROUP, GimpActionGroup))
end_define

begin_define
DECL|macro|GIMP_ACTION_GROUP_CLASS (vtable)
define|#
directive|define
name|GIMP_ACTION_GROUP_CLASS
parameter_list|(
name|vtable
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((vtable), GIMP_TYPE_ACTION_GROUP, GimpActionGroupClass))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION_GROUP (obj)
define|#
directive|define
name|GIMP_IS_ACTION_GROUP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ACTION_GROUP))
end_define

begin_define
DECL|macro|GIMP_IS_ACTION_GROUP_CLASS (vtable)
define|#
directive|define
name|GIMP_IS_ACTION_GROUP_CLASS
parameter_list|(
name|vtable
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((vtable), GIMP_TYPE_ACTION_GROUP))
end_define

begin_define
DECL|macro|GIMP_ACTION_GROUP_GET_CLASS (inst)
define|#
directive|define
name|GIMP_ACTION_GROUP_GET_CLASS
parameter_list|(
name|inst
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((inst), GIMP_TYPE_ACTION_GROUP, GimpActionGroupClass))
end_define

begin_typedef
DECL|typedef|GimpActionGroupClass
typedef|typedef
name|struct
name|_GimpActionGroupClass
name|GimpActionGroupClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpActionGroup
struct|struct
name|_GimpActionGroup
block|{
DECL|member|parent_instance
name|GtkActionGroup
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|label
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|mnemonics
name|gboolean
name|mnemonics
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|update_func
name|GimpActionGroupUpdateFunc
name|update_func
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpActionGroupClass
struct|struct
name|_GimpActionGroupClass
block|{
DECL|member|parent_class
name|GtkActionGroupClass
name|parent_class
decl_stmt|;
DECL|member|groups
name|GHashTable
modifier|*
name|groups
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpActionEntry
struct|struct
name|_GimpActionEntry
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|accelerator
specifier|const
name|gchar
modifier|*
name|accelerator
decl_stmt|;
DECL|member|tooltip
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|callback
name|GCallback
name|callback
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToggleActionEntry
struct|struct
name|_GimpToggleActionEntry
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|accelerator
specifier|const
name|gchar
modifier|*
name|accelerator
decl_stmt|;
DECL|member|tooltip
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|callback
name|GCallback
name|callback
decl_stmt|;
DECL|member|is_active
name|gboolean
name|is_active
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpRadioActionEntry
struct|struct
name|_GimpRadioActionEntry
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|accelerator
specifier|const
name|gchar
modifier|*
name|accelerator
decl_stmt|;
DECL|member|tooltip
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|value
name|gint
name|value
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEnumActionEntry
struct|struct
name|_GimpEnumActionEntry
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|accelerator
specifier|const
name|gchar
modifier|*
name|accelerator
decl_stmt|;
DECL|member|tooltip
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|value
name|gint
name|value
decl_stmt|;
DECL|member|value_variable
name|gboolean
name|value_variable
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpStringActionEntry
struct|struct
name|_GimpStringActionEntry
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|accelerator
specifier|const
name|gchar
modifier|*
name|accelerator
decl_stmt|;
DECL|member|tooltip
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|value
specifier|const
name|gchar
modifier|*
name|value
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPlugInActionEntry
struct|struct
name|_GimpPlugInActionEntry
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|accelerator
specifier|const
name|gchar
modifier|*
name|accelerator
decl_stmt|;
DECL|member|tooltip
specifier|const
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|procedure
name|GimpPlugInProcedure
modifier|*
name|procedure
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_action_group_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpActionGroup
modifier|*
name|gimp_action_group_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|gboolean
name|mnemonics
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GimpActionGroupUpdateFunc
name|update_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_action_groups_from_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|update_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_add_actions
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|GimpActionEntry
modifier|*
name|entries
parameter_list|,
name|guint
name|n_entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_add_toggle_actions
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|GimpToggleActionEntry
modifier|*
name|entries
parameter_list|,
name|guint
name|n_entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|gimp_action_group_add_radio_actions
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|GimpRadioActionEntry
modifier|*
name|entries
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GSList
modifier|*
name|radio_group
parameter_list|,
name|gint
name|value
parameter_list|,
name|GCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_add_enum_actions
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|GimpEnumActionEntry
modifier|*
name|entries
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_add_string_actions
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|GimpStringActionEntry
modifier|*
name|entries
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_add_plug_in_actions
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|GimpPlugInActionEntry
modifier|*
name|entries
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_set_action_visible
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_set_action_sensitive
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_set_action_active
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_set_action_label
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_set_action_color
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|set_label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_set_action_viewable
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_action_group_set_action_hide_empty
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
parameter_list|,
name|gboolean
name|is_important
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ACTION_GROUP_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2005 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_PREFERENCES_H
end_ifndef

begin_define
DECL|macro|_IMAP_PREFERENCES_H
define|#
directive|define
name|_IMAP_PREFERENCES_H
end_define

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_typedef
DECL|struct|__anon2738bfa70108
typedef|typedef
struct|struct
block|{
DECL|member|normal_fg
name|GdkColor
name|normal_fg
decl_stmt|;
DECL|member|normal_bg
name|GdkColor
name|normal_bg
decl_stmt|;
DECL|member|selected_fg
name|GdkColor
name|selected_fg
decl_stmt|;
DECL|member|selected_bg
name|GdkColor
name|selected_bg
decl_stmt|;
DECL|typedef|ColorSelData_t
block|}
name|ColorSelData_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2738bfa70208
typedef|typedef
struct|struct
block|{
DECL|member|default_map_type
name|gint
name|default_map_type
decl_stmt|;
DECL|member|prompt_for_area_info
name|gboolean
name|prompt_for_area_info
decl_stmt|;
DECL|member|require_default_url
name|gboolean
name|require_default_url
decl_stmt|;
DECL|member|show_area_handle
name|gboolean
name|show_area_handle
decl_stmt|;
DECL|member|keep_circles_round
name|gboolean
name|keep_circles_round
decl_stmt|;
DECL|member|show_url_tip
name|gboolean
name|show_url_tip
decl_stmt|;
DECL|member|use_doublesized
name|gboolean
name|use_doublesized
decl_stmt|;
DECL|member|auto_convert
name|gboolean
name|auto_convert
decl_stmt|;
DECL|member|threshold
name|gdouble
name|threshold
decl_stmt|;
DECL|member|undo_levels
name|gint
name|undo_levels
decl_stmt|;
DECL|member|mru_size
name|gint
name|mru_size
decl_stmt|;
DECL|member|colors
name|ColorSelData_t
name|colors
decl_stmt|;
DECL|member|normal_gc
name|GdkGC
modifier|*
name|normal_gc
decl_stmt|;
DECL|member|selected_gc
name|GdkGC
modifier|*
name|selected_gc
decl_stmt|;
DECL|typedef|PreferencesData_t
block|}
name|PreferencesData_t
typedef|;
end_typedef

begin_function_decl
name|void
name|do_preferences_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|preferences_load
parameter_list|(
name|PreferencesData_t
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preferences_save
parameter_list|(
name|PreferencesData_t
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_PREFERENCES_H */
end_comment

end_unit


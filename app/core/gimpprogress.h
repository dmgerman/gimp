begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprogress.h  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROGRESS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROGRESS_H__
define|#
directive|define
name|__GIMP_PROGRESS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_PROGRESS
define|#
directive|define
name|GIMP_TYPE_PROGRESS
value|(gimp_progress_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PROGRESS (obj)
define|#
directive|define
name|GIMP_IS_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROGRESS))
end_define

begin_define
DECL|macro|GIMP_PROGRESS (obj)
define|#
directive|define
name|GIMP_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROGRESS, GimpProgress))
end_define

begin_define
DECL|macro|GIMP_PROGRESS_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_PROGRESS_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_PROGRESS, GimpProgressInterface))
end_define

begin_typedef
DECL|typedef|GimpProgressInterface
typedef|typedef
name|struct
name|_GimpProgressInterface
name|GimpProgressInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProgressInterface
struct|struct
name|_GimpProgressInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|start
name|GimpProgress
modifier|*
function_decl|(
modifier|*
name|start
function_decl|)
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
function_decl|;
DECL|member|end
name|void
function_decl|(
modifier|*
name|end
function_decl|)
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
DECL|member|is_active
name|gboolean
function_decl|(
modifier|*
name|is_active
function_decl|)
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
DECL|member|set_text
name|void
function_decl|(
modifier|*
name|set_text
function_decl|)
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
DECL|member|set_value
name|void
function_decl|(
modifier|*
name|set_value
function_decl|)
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
DECL|member|get_value
name|gdouble
function_decl|(
modifier|*
name|get_value
function_decl|)
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|cancel
name|void
function_decl|(
modifier|*
name|cancel
function_decl|)
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_progress_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProgress
modifier|*
name|gimp_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
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
name|gimp_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_progress_cancel
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_progress_update_and_flush
parameter_list|(
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gint
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROGRESS_H__ */
end_comment

end_unit


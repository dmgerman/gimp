begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprogress.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpProgressVtable
typedef|typedef
name|struct
name|_GimpProgressVtable
name|GimpProgressVtable
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProgressVtable
struct|struct
name|_GimpProgressVtable
block|{
DECL|member|start
name|void
function_decl|(
modifier|*
name|start
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
DECL|member|end
name|void
function_decl|(
modifier|*
name|end
function_decl|)
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
DECL|member|set_text
name|void
function_decl|(
modifier|*
name|set_text
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
DECL|member|set_value
name|void
function_decl|(
modifier|*
name|set_value
function_decl|)
parameter_list|(
name|gdouble
name|percentage
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
DECL|member|pulse
name|void
function_decl|(
modifier|*
name|pulse
function_decl|)
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
DECL|member|get_window
name|guint32
function_decl|(
modifier|*
name|get_window
function_decl|)
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
comment|/* Padding for future expansion. Must be initialized with NULL! */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_progress_install_vtable
parameter_list|(
specifier|const
name|GimpProgressVtable
modifier|*
name|vtable
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|gimp_progress_uninstall
parameter_list|(
specifier|const
name|gchar
modifier|*
name|progress_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_progress_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_progress_init_printf
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|1
operator|,
function_decl|2
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|gboolean
name|gimp_progress_set_text_printf
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|1
operator|,
function_decl|2
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|gboolean
name|gimp_progress_update
parameter_list|(
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROGRESS_H__ */
end_comment

end_unit


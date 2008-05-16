begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_PROGRESS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_PROGRESS_H__
define|#
directive|define
name|__GIMP_HELP_PROGRESS_H__
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c8f437b0108
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
DECL|typedef|GimpHelpProgressVTable
block|}
name|GimpHelpProgressVTable
typedef|;
end_typedef

begin_function_decl
name|GimpHelpProgress
modifier|*
name|gimp_help_progress_new
parameter_list|(
specifier|const
name|GimpHelpProgressVTable
modifier|*
name|vtable
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_progress_free
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_progress_cancel
parameter_list|(
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! __GIMP_HELP_PROGRESS_H__ */
end_comment

end_unit


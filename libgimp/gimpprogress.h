begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprogress.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpProgressStartCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProgressStartCallback
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
end_typedef

begin_typedef
DECL|typedef|GimpProgressEndCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProgressEndCallback
function_decl|)
parameter_list|(
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpProgressTextCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProgressTextCallback
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
end_typedef

begin_typedef
DECL|typedef|GimpProgressValueCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpProgressValueCallback
function_decl|)
parameter_list|(
name|gdouble
name|percentage
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_progress_install
parameter_list|(
name|GimpProgressStartCallback
name|start_callback
parameter_list|,
name|GimpProgressEndCallback
name|end_callback
parameter_list|,
name|GimpProgressTextCallback
name|text_callback
parameter_list|,
name|GimpProgressValueCallback
name|value_callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_progress_uninstall
parameter_list|(
specifier|const
name|gchar
modifier|*
name|progress_callback
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


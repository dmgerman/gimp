begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprogressbar.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROGRESS_BAR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROGRESS_BAR_H__
define|#
directive|define
name|__GIMP_PROGRESS_BAR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PROGRESS_BAR
define|#
directive|define
name|GIMP_TYPE_PROGRESS_BAR
value|(gimp_progress_bar_get_type ())
end_define

begin_define
DECL|macro|GIMP_PROGRESS_BAR (obj)
define|#
directive|define
name|GIMP_PROGRESS_BAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROGRESS_BAR, GimpProgressBar))
end_define

begin_define
DECL|macro|GIMP_PROGRESS_BAR_CLASS (klass)
define|#
directive|define
name|GIMP_PROGRESS_BAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PROGRESS_BAR, GimpProgressBarClass))
end_define

begin_define
DECL|macro|GIMP_IS_PROGRESS_BAR (obj)
define|#
directive|define
name|GIMP_IS_PROGRESS_BAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROGRESS_BAR))
end_define

begin_define
DECL|macro|GIMP_IS_PROGRESS_BAR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PROGRESS_BAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PROGRESS_BAR))
end_define

begin_define
DECL|macro|GIMP_PROGRESS_BAR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PROGRESS_BAR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PROGRESS_BAR, GimpProgressBarClass))
end_define

begin_typedef
DECL|typedef|GimpProgressBarClass
typedef|typedef
name|struct
name|_GimpProgressBarClass
name|GimpProgressBarClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProgressBar
struct|struct
name|_GimpProgressBar
block|{
DECL|member|parent_instance
name|GtkProgressBar
name|parent_instance
decl_stmt|;
DECL|member|progress_callback
specifier|const
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
DECL|member|cancelable
name|gboolean
name|cancelable
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProgressBarClass
struct|struct
name|_GimpProgressBarClass
block|{
DECL|member|parent_class
name|GtkProgressBarClass
name|parent_class
decl_stmt|;
comment|/* Padding for future expansion */
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_progress_bar_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_progress_bar_new
parameter_list|(
name|void
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
comment|/* __GIMP_PROGRESS_BAR_H__ */
end_comment

end_unit


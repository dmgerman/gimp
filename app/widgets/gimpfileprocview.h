begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfileprocview.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILE_PROC_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILE_PROC_VIEW_H__
define|#
directive|define
name|__GIMP_FILE_PROC_VIEW_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtktreeview.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_FILE_PROC_VIEW
define|#
directive|define
name|GIMP_TYPE_FILE_PROC_VIEW
value|(gimp_file_proc_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILE_PROC_VIEW (obj)
define|#
directive|define
name|GIMP_FILE_PROC_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILE_PROC_VIEW, GimpFileProcView))
end_define

begin_define
DECL|macro|GIMP_FILE_PROC_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_FILE_PROC_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILE_PROC_VIEW, GimpFileProcViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILE_PROC_VIEW (obj)
define|#
directive|define
name|GIMP_IS_FILE_PROC_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILE_PROC_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_FILE_PROC_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILE_PROC_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILE_PROC_VIEW))
end_define

begin_define
DECL|macro|GIMP_FILE_PROC_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FILE_PROC_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILE_PROC_VIEW, GimpFileProcViewClass))
end_define

begin_typedef
DECL|typedef|GimpFileProcViewClass
typedef|typedef
name|struct
name|_GimpFileProcViewClass
name|GimpFileProcViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFileProcView
struct|struct
name|_GimpFileProcView
block|{
DECL|member|parent_instance
name|GtkTreeView
name|parent_instance
decl_stmt|;
DECL|member|meta_extensions
name|GList
modifier|*
name|meta_extensions
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFileProcViewClass
struct|struct
name|_GimpFileProcViewClass
block|{
DECL|member|parent_class
name|GtkTreeViewClass
name|parent_class
decl_stmt|;
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_file_proc_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_file_proc_view_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GSList
modifier|*
name|procedures
parameter_list|,
specifier|const
name|gchar
modifier|*
name|automatic
parameter_list|,
specifier|const
name|gchar
modifier|*
name|automatic_help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|gimp_file_proc_view_get_proc
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|,
name|gchar
modifier|*
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_file_proc_view_set_proc
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_file_proc_view_get_help_id
parameter_list|(
name|GimpFileProcView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_FILE_PROC_VIEW_H__  */
end_comment

end_unit


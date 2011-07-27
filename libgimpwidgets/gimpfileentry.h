begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpfileentry.h  * Copyright (C) 1999-2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILE_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILE_ENTRY_H__
define|#
directive|define
name|__GIMP_FILE_ENTRY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_FILE_ENTRY
define|#
directive|define
name|GIMP_TYPE_FILE_ENTRY
value|(gimp_file_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILE_ENTRY (obj)
define|#
directive|define
name|GIMP_FILE_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILE_ENTRY, GimpFileEntry))
end_define

begin_define
DECL|macro|GIMP_FILE_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_FILE_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILE_ENTRY, GimpFileEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILE_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_FILE_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_FILE_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_FILE_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILE_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILE_ENTRY))
end_define

begin_define
DECL|macro|GIMP_FILE_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FILE_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILE_ENTRY, GimpFileEntryClass))
end_define

begin_typedef
DECL|typedef|GimpFileEntryClass
typedef|typedef
name|struct
name|_GimpFileEntryClass
name|GimpFileEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFileEntry
struct|struct
name|_GimpFileEntry
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|file_exists
name|GtkWidget
modifier|*
name|file_exists
decl_stmt|;
DECL|member|entry
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
DECL|member|browse_button
name|GtkWidget
modifier|*
name|browse_button
decl_stmt|;
DECL|member|file_dialog
name|GtkWidget
modifier|*
name|file_dialog
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|dir_only
name|gboolean
name|dir_only
decl_stmt|;
DECL|member|check_valid
name|gboolean
name|check_valid
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFileEntryClass
struct|struct
name|_GimpFileEntryClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|filename_changed
name|void
function_decl|(
modifier|*
name|filename_changed
function_decl|)
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
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
name|gimp_file_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_file_entry_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|dir_only
parameter_list|,
name|gboolean
name|check_valid
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_file_entry_get_filename
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_file_entry_set_filename
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
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
comment|/* __GIMP_FILE_ENTRY_H__ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

end_unit


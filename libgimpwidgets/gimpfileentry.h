begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpfileselection.h  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILE_SELECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILE_SELECTION_H__
define|#
directive|define
name|__GIMP_FILE_SELECTION_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimppixmap.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GIMP_TYPE_FILE_SELECTION
define|#
directive|define
name|GIMP_TYPE_FILE_SELECTION
value|(gimp_file_selection_get_type ())
DECL|macro|GIMP_FILE_SELECTION (obj)
define|#
directive|define
name|GIMP_FILE_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_FILE_SELECTION, GimpFileSelection))
DECL|macro|GIMP_FILE_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_FILE_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILE_SELECTION, GimpFileSelectionClass))
DECL|macro|GIMP_IS_FILE_SELECTION (obj)
define|#
directive|define
name|GIMP_IS_FILE_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_FILE_SELECTION))
DECL|macro|GIMP_IS_FILE_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILE_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILE_SELECTION))
DECL|typedef|GimpFileSelection
typedef|typedef
name|struct
name|_GimpFileSelection
name|GimpFileSelection
typedef|;
DECL|typedef|GimpFileSelectionClass
typedef|typedef
name|struct
name|_GimpFileSelectionClass
name|GimpFileSelectionClass
typedef|;
DECL|struct|_GimpFileSelection
struct|struct
name|_GimpFileSelection
block|{
DECL|member|hbox
name|GtkHBox
name|hbox
decl_stmt|;
DECL|member|yes_pixmap
name|GtkWidget
modifier|*
name|yes_pixmap
decl_stmt|;
DECL|member|no_pixmap
name|GtkWidget
modifier|*
name|no_pixmap
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
DECL|member|file_selection
name|GtkWidget
modifier|*
name|file_selection
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
DECL|struct|_GimpFileSelectionClass
struct|struct
name|_GimpFileSelectionClass
block|{
DECL|member|parent_class
name|GtkHBoxClass
name|parent_class
decl_stmt|;
DECL|member|filename_changed
name|void
function_decl|(
modifier|*
name|filename_changed
function_decl|)
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|)
function_decl|;
block|}
struct|;
comment|/* For information look into the C source or the html documentation */
name|GtkType
name|gimp_file_selection_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_file_selection_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
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
name|gchar
modifier|*
name|gimp_file_selection_get_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|)
function_decl|;
name|void
name|gimp_file_selection_set_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILE_SELECTION_H__ */
end_comment

end_unit


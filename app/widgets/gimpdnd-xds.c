begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpdnd-xds.c  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * Saving Files via Drag-and-Drop:  * The Direct Save Protocol for the X Window System  *  *   http://www.newplanetsoftware.com/xds/  *   http://rox.sourceforge.net/xds.html  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"file/file-save.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd-xds.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG_DND
end_ifdef

begin_define
DECL|macro|D (stmnt)
define|#
directive|define
name|D
parameter_list|(
name|stmnt
parameter_list|)
value|stmnt
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|D (stmnt)
define|#
directive|define
name|D
parameter_list|(
name|stmnt
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|MAX_URI_LEN
define|#
directive|define
name|MAX_URI_LEN
value|4096
end_define

begin_function
name|void
DECL|function|gimp_dnd_xds_source_set (GdkDragContext * context,GimpImage * image)
name|gimp_dnd_xds_source_set
parameter_list|(
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GdkAtom
name|property
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GDK_IS_DRAG_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|D
argument_list|(
name|g_printerr
argument_list|(
literal|"\ngimp_dnd_xds_source_set\n"
argument_list|)
argument_list|)
expr_stmt|;
name|property
operator|=
name|gdk_atom_intern
argument_list|(
literal|"XdndDirectSave0"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|&&
operator|(
name|filename
operator|=
name|gimp_image_get_filename
argument_list|(
name|image
argument_list|)
operator|)
condition|)
block|{
name|GdkAtom
name|type
init|=
name|gdk_atom_intern
argument_list|(
literal|"text/plain"
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|basename
init|=
name|g_path_get_basename
argument_list|(
name|filename
argument_list|)
decl_stmt|;
name|gdk_property_change
argument_list|(
name|context
operator|->
name|source_window
argument_list|,
name|property
argument_list|,
name|type
argument_list|,
literal|8
argument_list|,
name|GDK_PROP_MODE_REPLACE
argument_list|,
name|basename
argument_list|,
name|strlen
argument_list|(
name|basename
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_property_delete
argument_list|(
name|context
operator|->
name|source_window
argument_list|,
name|property
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_dnd_xds_save_image (GdkDragContext * context,GimpImage * image,GtkSelectionData * selection,GdkAtom atom)
name|gimp_dnd_xds_save_image
parameter_list|(
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|GdkAtom
name|atom
parameter_list|)
block|{
name|PlugInProcDef
modifier|*
name|proc
decl_stmt|;
name|GdkAtom
name|property
init|=
name|gdk_atom_intern
argument_list|(
literal|"XdndDirectSave0"
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|GdkAtom
name|type
init|=
name|gdk_atom_intern
argument_list|(
literal|"text/plain"
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|gint
name|length
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GDK_IS_DRAG_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|D
argument_list|(
name|g_printerr
argument_list|(
literal|"\ngimp_dnd_xds_save_image\n"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdk_property_get
argument_list|(
name|context
operator|->
name|source_window
argument_list|,
name|property
argument_list|,
name|type
argument_list|,
literal|0
argument_list|,
name|MAX_URI_LEN
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|length
argument_list|,
operator|&
name|data
argument_list|)
condition|)
return|return;
name|uri
operator|=
name|g_strndup
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|data
argument_list|,
name|length
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|proc
operator|=
name|file_utils_find_proc
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|save_procs
argument_list|,
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc
condition|)
name|proc
operator|=
name|file_utils_find_proc
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|save_procs
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc
condition|)
block|{
if|if
condition|(
name|file_save
argument_list|(
name|image
argument_list|,
name|gimp_get_user_context
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
name|proc
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|FALSE
argument_list|,
operator|&
name|error
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gtk_selection_data_set
argument_list|(
name|selection
argument_list|,
name|atom
argument_list|,
literal|8
argument_list|,
literal|"S"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_selection_data_set
argument_list|(
name|selection
argument_list|,
name|atom
argument_list|,
literal|8
argument_list|,
literal|"E"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Saving '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|gtk_selection_data_set
argument_list|(
name|selection
argument_list|,
name|atom
argument_list|,
literal|8
argument_list|,
literal|"E"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The given filename does not have any known "
literal|"file extension."
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


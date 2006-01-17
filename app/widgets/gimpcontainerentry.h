begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerentry.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_ENTRY_H__
define|#
directive|define
name|__GIMP_CONTAINER_ENTRY_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkentry.h>
end_include

begin_enum
enum|enum
DECL|enum|__anon297448ac0103
block|{
DECL|enumerator|GIMP_CONTAINER_ENTRY_COLUMN_RENDERER
name|GIMP_CONTAINER_ENTRY_COLUMN_RENDERER
block|,
DECL|enumerator|GIMP_CONTAINER_ENTRY_COLUMN_NAME
name|GIMP_CONTAINER_ENTRY_COLUMN_NAME
block|,
DECL|enumerator|GIMP_CONTAINER_ENTRY_NUM_COLUMNS
name|GIMP_CONTAINER_ENTRY_NUM_COLUMNS
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_ENTRY
define|#
directive|define
name|GIMP_TYPE_CONTAINER_ENTRY
value|(gimp_container_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_ENTRY (obj)
define|#
directive|define
name|GIMP_CONTAINER_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_ENTRY, GimpContainerEntry))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_ENTRY, GimpContainerEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_ENTRY))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_ENTRY, GimpContainerEntryClass))
end_define

begin_typedef
DECL|typedef|GimpContainerEntryClass
typedef|typedef
name|struct
name|_GimpContainerEntryClass
name|GimpContainerEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerEntry
struct|struct
name|_GimpContainerEntry
block|{
DECL|member|parent_instance
name|GtkEntry
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerEntryClass
struct|struct
name|_GimpContainerEntryClass
block|{
DECL|member|parent_class
name|GtkEntryClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_container_entry_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_ENTRY_H__  */
end_comment

end_unit


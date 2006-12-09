begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcellrendereraccel.h  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * Derived from: libegg/libegg/treeviewutils/eggcellrendererkeys.h  * Copyright (C) 2000  Red Hat, Inc.,  Jonathan Blandford<jrb@redhat.com>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CELL_RENDERER_ACCEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CELL_RENDERER_ACCEL_H__
define|#
directive|define
name|__GIMP_CELL_RENDERER_ACCEL_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkcellrenderertext.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_CELL_RENDERER_ACCEL
define|#
directive|define
name|GIMP_TYPE_CELL_RENDERER_ACCEL
value|(gimp_cell_renderer_accel_get_type ())
end_define

begin_define
DECL|macro|GIMP_CELL_RENDERER_ACCEL (obj)
define|#
directive|define
name|GIMP_CELL_RENDERER_ACCEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CELL_RENDERER_ACCEL, GimpCellRendererAccel))
end_define

begin_define
DECL|macro|GIMP_CELL_RENDERER_ACCEL_CLASS (klass)
define|#
directive|define
name|GIMP_CELL_RENDERER_ACCEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CELL_RENDERER_ACCEL, GimpCellRendererAccelClass))
end_define

begin_define
DECL|macro|GIMP_IS_CELL_RENDERER_ACCEL (obj)
define|#
directive|define
name|GIMP_IS_CELL_RENDERER_ACCEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CELL_RENDERER_ACCEL))
end_define

begin_define
DECL|macro|GIMP_IS_CELL_RENDERER_ACCEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CELL_RENDERER_ACCEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CELL_RENDERER_ACCEL))
end_define

begin_define
DECL|macro|GIMP_CELL_RENDERER_ACCEL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CELL_RENDERER_ACCEL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CELL_RENDERER_ACCEL, GimpCellRendererAccelClass))
end_define

begin_typedef
DECL|typedef|GimpCellRendererAccelClass
typedef|typedef
name|struct
name|_GimpCellRendererAccelClass
name|GimpCellRendererAccelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCellRendererAccel
struct|struct
name|_GimpCellRendererAccel
block|{
DECL|member|parent_instance
name|GtkCellRendererText
name|parent_instance
decl_stmt|;
DECL|member|accel_key
name|guint
name|accel_key
decl_stmt|;
DECL|member|accel_mask
name|GdkModifierType
name|accel_mask
decl_stmt|;
DECL|member|edit_widget
name|GtkWidget
modifier|*
name|edit_widget
decl_stmt|;
DECL|member|grab_widget
name|GtkWidget
modifier|*
name|grab_widget
decl_stmt|;
DECL|member|edit_key
name|guint
name|edit_key
decl_stmt|;
DECL|member|sizing_label
name|GtkWidget
modifier|*
name|sizing_label
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCellRendererAccelClass
struct|struct
name|_GimpCellRendererAccelClass
block|{
DECL|member|parent_class
name|GtkCellRendererTextClass
name|parent_class
decl_stmt|;
DECL|member|accel_edited
name|void
function_decl|(
modifier|*
name|accel_edited
function_decl|)
parameter_list|(
name|GimpCellRendererAccel
modifier|*
name|accel
parameter_list|,
specifier|const
name|char
modifier|*
name|path_string
parameter_list|,
name|gboolean
name|delete
parameter_list|,
name|guint
name|accel_key
parameter_list|,
name|GdkModifierType
name|accel_mask
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_cell_renderer_accel_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkCellRenderer
modifier|*
name|gimp_cell_renderer_accel_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cell_renderer_accel_set_accelerator
parameter_list|(
name|GimpCellRendererAccel
modifier|*
name|accel
parameter_list|,
name|guint
name|accel_kaey
parameter_list|,
name|GdkModifierType
name|accel_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cell_renderer_accel_get_accelerator
parameter_list|(
name|GimpCellRendererAccel
modifier|*
name|accel
parameter_list|,
name|guint
modifier|*
name|accel_key
parameter_list|,
name|GdkModifierType
modifier|*
name|accel_mask
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CELL_RENDERER_ACCEL_H__ */
end_comment

end_unit


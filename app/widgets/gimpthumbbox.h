begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THUMB_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THUMB_BOX_H__
define|#
directive|define
name|__GIMP_THUMB_BOX_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_THUMB_BOX
define|#
directive|define
name|GIMP_TYPE_THUMB_BOX
value|(gimp_thumb_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_THUMB_BOX (obj)
define|#
directive|define
name|GIMP_THUMB_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_THUMB_BOX, GimpThumbBox))
end_define

begin_define
DECL|macro|GIMP_THUMB_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_THUMB_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_THUMB_BOX, GimpThumbBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_THUMB_BOX (obj)
define|#
directive|define
name|GIMP_IS_THUMB_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_THUMB_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_THUMB_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_THUMB_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_THUMB_BOX))
end_define

begin_define
DECL|macro|GIMP_THUMB_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_THUMB_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_THUMB_BOX, GimpThumbBoxClass))
end_define

begin_typedef
DECL|typedef|GimpThumbBoxClass
typedef|typedef
name|struct
name|_GimpThumbBoxClass
name|GimpThumbBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpThumbBox
struct|struct
name|_GimpThumbBox
block|{
DECL|member|parent_instance
name|GtkFrame
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|imagefile
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
DECL|member|uris
name|GSList
modifier|*
name|uris
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|filename
name|GtkWidget
modifier|*
name|filename
decl_stmt|;
DECL|member|info
name|GtkWidget
modifier|*
name|info
decl_stmt|;
DECL|member|thumb_progress
name|GtkWidget
modifier|*
name|thumb_progress
decl_stmt|;
DECL|member|progress_active
name|gboolean
name|progress_active
decl_stmt|;
DECL|member|progress
name|GtkWidget
modifier|*
name|progress
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpThumbBoxClass
struct|struct
name|_GimpThumbBoxClass
block|{
DECL|member|parent_class
name|GtkFrameClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_thumb_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_thumb_box_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_thumb_box_take_uri
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_thumb_box_take_uris
parameter_list|(
name|GimpThumbBox
modifier|*
name|box
parameter_list|,
name|GSList
modifier|*
name|uris
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_THUMB_BOX_H__  */
end_comment

end_unit


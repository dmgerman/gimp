begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CLONE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CLONE_H__
define|#
directive|define
name|__GIMP_CLONE_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintcore.h"
end_include

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
comment|/*< pdb-skip>*/
DECL|enum|__anon2738ed7f0103
block|{
DECL|enumerator|ALIGN_NO
name|ALIGN_NO
block|,
DECL|enumerator|ALIGN_YES
name|ALIGN_YES
block|,
DECL|enumerator|ALIGN_REGISTERED
name|ALIGN_REGISTERED
DECL|typedef|AlignType
block|}
name|AlignType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CLONE
define|#
directive|define
name|GIMP_TYPE_CLONE
value|(gimp_clone_get_type ())
end_define

begin_define
DECL|macro|GIMP_CLONE (obj)
define|#
directive|define
name|GIMP_CLONE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CLONE, GimpClone))
end_define

begin_define
DECL|macro|GIMP_CLONE_CLASS (klass)
define|#
directive|define
name|GIMP_CLONE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CLONE, GimpCloneClass))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE (obj)
define|#
directive|define
name|GIMP_IS_CLONE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CLONE))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CLONE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CLONE))
end_define

begin_define
DECL|macro|GIMP_CLONE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CLONE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CLONE, GimpCloneClass))
end_define

begin_typedef
DECL|typedef|GimpClone
typedef|typedef
name|struct
name|_GimpClone
name|GimpClone
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCloneClass
typedef|typedef
name|struct
name|_GimpCloneClass
name|GimpCloneClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpClone
struct|struct
name|_GimpClone
block|{
DECL|member|parent_instance
name|GimpPaintCore
name|parent_instance
decl_stmt|;
DECL|member|set_source
name|gboolean
name|set_source
decl_stmt|;
DECL|member|src_drawable
name|GimpDrawable
modifier|*
name|src_drawable
decl_stmt|;
DECL|member|src_x
name|gint
name|src_x
decl_stmt|;
DECL|member|src_y
name|gint
name|src_y
decl_stmt|;
DECL|member|init_callback
name|void
function_decl|(
modifier|*
name|init_callback
function_decl|)
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|finish_callback
name|void
function_decl|(
modifier|*
name|finish_callback
function_decl|)
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|pretrace_callback
name|void
function_decl|(
modifier|*
name|pretrace_callback
function_decl|)
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|posttrace_callback
name|void
function_decl|(
modifier|*
name|posttrace_callback
function_decl|)
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|member|callback_data
name|gpointer
name|callback_data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCloneClass
struct|struct
name|_GimpCloneClass
block|{
DECL|member|parent_class
name|GimpPaintCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|CloneOptions
typedef|typedef
name|struct
name|_CloneOptions
name|CloneOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_CloneOptions
struct|struct
name|_CloneOptions
block|{
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
DECL|member|type
name|CloneType
name|type
decl_stmt|;
DECL|member|type_d
name|CloneType
name|type_d
decl_stmt|;
DECL|member|type_w
name|GtkWidget
modifier|*
name|type_w
index|[
literal|2
index|]
decl_stmt|;
comment|/* 2 radio buttons */
DECL|member|aligned
name|AlignType
name|aligned
decl_stmt|;
DECL|member|aligned_d
name|AlignType
name|aligned_d
decl_stmt|;
DECL|member|aligned_w
name|GtkWidget
modifier|*
name|aligned_w
index|[
literal|3
index|]
decl_stmt|;
comment|/* 3 radio buttons */
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_clone_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CLONE_H__  */
end_comment

end_unit


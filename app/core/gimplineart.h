begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2017 SÃ©bastien Fourey& David TchumperlÃ©  * Copyright (C) 2018 Jehan  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LINEART__
end_ifndef

begin_define
DECL|macro|__GIMP_LINEART__
define|#
directive|define
name|__GIMP_LINEART__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LINE_ART
define|#
directive|define
name|GIMP_TYPE_LINE_ART
value|(gimp_line_art_get_type ())
end_define

begin_define
DECL|macro|GIMP_LINE_ART (obj)
define|#
directive|define
name|GIMP_LINE_ART
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LINE_ART, GimpLineArt))
end_define

begin_define
DECL|macro|GIMP_LINE_ART_CLASS (klass)
define|#
directive|define
name|GIMP_LINE_ART_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LINE_ART, GimpLineArtClass))
end_define

begin_define
DECL|macro|GIMP_IS_LINE_ART (obj)
define|#
directive|define
name|GIMP_IS_LINE_ART
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LINE_ART))
end_define

begin_define
DECL|macro|GIMP_IS_LINE_ART_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LINE_ART_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LINE_ART))
end_define

begin_define
DECL|macro|GIMP_LINE_ART_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LINE_ART_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LINE_ART, GimpLineArtClass))
end_define

begin_typedef
DECL|typedef|GimpLineArtClass
typedef|typedef
name|struct
name|_GimpLineArtClass
name|GimpLineArtClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLineArtPrivate
typedef|typedef
name|struct
name|_GimpLineArtPrivate
name|GimpLineArtPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLineArt
struct|struct
name|_GimpLineArt
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpLineArtPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLineArtClass
struct|struct
name|_GimpLineArtClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_line_art_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpLineArt
modifier|*
name|gimp_line_art_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_line_art_set_input
parameter_list|(
name|GimpLineArt
modifier|*
name|line_art
parameter_list|,
name|GimpPickable
modifier|*
name|pickable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPickable
modifier|*
name|gimp_line_art_get_input
parameter_list|(
name|GimpLineArt
modifier|*
name|line_art
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_line_art_freeze
parameter_list|(
name|GimpLineArt
modifier|*
name|line_art
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_line_art_thaw
parameter_list|(
name|GimpLineArt
modifier|*
name|line_art
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_line_art_get
parameter_list|(
name|GimpLineArt
modifier|*
name|line_art
parameter_list|,
name|gfloat
modifier|*
modifier|*
name|distmap
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LINEART__ */
end_comment

end_unit


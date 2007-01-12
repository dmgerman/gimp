begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpanchor.h  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ANCHOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ANCHOR_H__
define|#
directive|define
name|__GIMP_ANCHOR_H__
end_define

begin_define
DECL|macro|GIMP_ANCHOR (anchor)
define|#
directive|define
name|GIMP_ANCHOR
parameter_list|(
name|anchor
parameter_list|)
value|((GimpAnchor *) (anchor))
end_define

begin_define
DECL|macro|GIMP_TYPE_ANCHOR
define|#
directive|define
name|GIMP_TYPE_ANCHOR
value|(gimp_anchor_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_ANCHOR (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_ANCHOR
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_ANCHOR))
end_define

begin_decl_stmt
name|GType
name|gimp_anchor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_struct
DECL|struct|_GimpAnchor
struct|struct
name|_GimpAnchor
block|{
DECL|member|position
name|GimpCoords
name|position
decl_stmt|;
DECL|member|type
name|GimpAnchorType
name|type
decl_stmt|;
comment|/* Interpretation dependant on GimpStroke type */
DECL|member|selected
name|gboolean
name|selected
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_anchor_new
parameter_list|(
name|GimpAnchorType
name|type
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_anchor_copy
parameter_list|(
specifier|const
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_anchor_free
parameter_list|(
name|GimpAnchor
modifier|*
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ANCHOR_H__ */
end_comment

end_unit


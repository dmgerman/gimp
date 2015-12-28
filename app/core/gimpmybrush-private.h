begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmybrush-private.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MYBRUSH_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MYBRUSH_PRIVATE_H__
define|#
directive|define
name|__GIMP_MYBRUSH_PRIVATE_H__
end_define

begin_struct
DECL|struct|_GimpMybrushPrivate
struct|struct
name|_GimpMybrushPrivate
block|{
DECL|member|json_loaded
name|gboolean
name|json_loaded
decl_stmt|;
DECL|member|brush_json
name|gchar
modifier|*
name|brush_json
decl_stmt|;
DECL|member|radius
name|gdouble
name|radius
decl_stmt|;
DECL|member|opaque
name|gdouble
name|opaque
decl_stmt|;
DECL|member|hardness
name|gdouble
name|hardness
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MYBRUSH_PRIVATE_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdial.h  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * Based on code from the color-rotate plug-in  * Copyright (C) 1997-1999 Sven Anders (anderss@fmi.uni-passau.de)  *                         Based on code from Pavel Grinfeld (pavel@ml.com)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DIAL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DIAL_H__
define|#
directive|define
name|__GIMP_DIAL_H__
end_define

begin_include
include|#
directive|include
file|"gimpcircle.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DIAL
define|#
directive|define
name|GIMP_TYPE_DIAL
value|(gimp_dial_get_type ())
end_define

begin_define
DECL|macro|GIMP_DIAL (obj)
define|#
directive|define
name|GIMP_DIAL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DIAL, GimpDial))
end_define

begin_define
DECL|macro|GIMP_DIAL_CLASS (klass)
define|#
directive|define
name|GIMP_DIAL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DIAL, GimpDialClass))
end_define

begin_define
DECL|macro|GIMP_IS_DIAL (obj)
define|#
directive|define
name|GIMP_IS_DIAL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_DIAL))
end_define

begin_define
DECL|macro|GIMP_IS_DIAL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DIAL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DIAL))
end_define

begin_define
DECL|macro|GIMP_DIAL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DIAL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DIAL, GimpDialClass))
end_define

begin_typedef
DECL|typedef|GimpDialPrivate
typedef|typedef
name|struct
name|_GimpDialPrivate
name|GimpDialPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDialClass
typedef|typedef
name|struct
name|_GimpDialClass
name|GimpDialClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDial
struct|struct
name|_GimpDial
block|{
DECL|member|parent_instance
name|GimpCircle
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpDialPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDialClass
struct|struct
name|_GimpDialClass
block|{
DECL|member|parent_class
name|GimpCircleClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dial_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dial_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DIAL_H__ */
end_comment

end_unit


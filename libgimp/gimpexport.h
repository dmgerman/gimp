begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EXPORT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EXPORT_H__
define|#
directive|define
name|__GIMP_EXPORT_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
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
DECL|macro|CAN_HANDLE_RGB
define|#
directive|define
name|CAN_HANDLE_RGB
value|1<< 0
DECL|macro|CAN_HANDLE_GRAY
define|#
directive|define
name|CAN_HANDLE_GRAY
value|1<< 1
DECL|macro|CAN_HANDLE_INDEXED
define|#
directive|define
name|CAN_HANDLE_INDEXED
value|1<< 2
DECL|macro|CAN_HANDLE_ALPHA
define|#
directive|define
name|CAN_HANDLE_ALPHA
value|1<< 3
DECL|macro|CAN_HANDLE_LAYERS
define|#
directive|define
name|CAN_HANDLE_LAYERS
value|1<< 4
DECL|macro|CAN_HANDLE_LAYERS_AS_ANIMATION
define|#
directive|define
name|CAN_HANDLE_LAYERS_AS_ANIMATION
value|1<< 5
DECL|macro|NEEDS_ALPHA
define|#
directive|define
name|NEEDS_ALPHA
value|1<< 6
typedef|typedef
enum|enum
DECL|enum|__anon2c6fc1050103
block|{
DECL|enumerator|EXPORT_CANCEL
name|EXPORT_CANCEL
block|,
DECL|enumerator|EXPORT_IGNORE
name|EXPORT_IGNORE
block|,
DECL|enumerator|EXPORT_EXPORT
name|EXPORT_EXPORT
DECL|typedef|GimpExportReturnType
block|}
name|GimpExportReturnType
typedef|;
name|GimpExportReturnType
name|gimp_export_image
parameter_list|(
name|gint32
modifier|*
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|,
name|gchar
modifier|*
name|format_name
parameter_list|,
name|gint
name|capabilities
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

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimpexport.h  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>  *   * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
comment|/* For information look into the C source or the html documentation */
typedef|typedef
enum|enum
DECL|enum|__anon2c39681e0103
block|{
DECL|enumerator|CAN_HANDLE_RGB
name|CAN_HANDLE_RGB
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|CAN_HANDLE_GRAY
name|CAN_HANDLE_GRAY
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|CAN_HANDLE_INDEXED
name|CAN_HANDLE_INDEXED
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|CAN_HANDLE_ALPHA
name|CAN_HANDLE_ALPHA
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|CAN_HANDLE_LAYERS
name|CAN_HANDLE_LAYERS
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|CAN_HANDLE_LAYERS_AS_ANIMATION
name|CAN_HANDLE_LAYERS_AS_ANIMATION
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|NEEDS_ALPHA
name|NEEDS_ALPHA
init|=
literal|1
operator|<<
literal|6
DECL|typedef|GimpExportCapabilities
block|}
name|GimpExportCapabilities
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon2c39681e0203
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
name|GimpExportCapabilities
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

begin_comment
comment|/* __GIMP_EXPORT_H__ */
end_comment

end_unit


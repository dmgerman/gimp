begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimpexport.h  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_UI_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimpui.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * GimpExportCapabilities:  * @GIMP_EXPORT_CAN_HANDLE_RGB:                 Handles RGB images  * @GIMP_EXPORT_CAN_HANDLE_GRAY:                Handles grayscale images  * @GIMP_EXPORT_CAN_HANDLE_INDEXED:             Handles indexed images  * @GIMP_EXPORT_CAN_HANDLE_BITMAP:              Handles two-color indexed images  * @GIMP_EXPORT_CAN_HANDLE_ALPHA:               Handles alpha channels  * @GIMP_EXPORT_CAN_HANDLE_LAYERS:              Handles layers  * @GIMP_EXPORT_CAN_HANDLE_LAYERS_AS_ANIMATION: Handles animation of layers  * @GIMP_EXPORT_CAN_HANDLE_LAYER_MASKS:         Handles layer masks  * @GIMP_EXPORT_NEEDS_ALPHA:                    Needs alpha channels  *  * The types of images and layers an export procedure can handle  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a2d60da0103
block|{
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_RGB
name|GIMP_EXPORT_CAN_HANDLE_RGB
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_GRAY
name|GIMP_EXPORT_CAN_HANDLE_GRAY
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_INDEXED
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_BITMAP
name|GIMP_EXPORT_CAN_HANDLE_BITMAP
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_ALPHA
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_LAYERS
name|GIMP_EXPORT_CAN_HANDLE_LAYERS
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_LAYERS_AS_ANIMATION
name|GIMP_EXPORT_CAN_HANDLE_LAYERS_AS_ANIMATION
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_EXPORT_CAN_HANDLE_LAYER_MASKS
name|GIMP_EXPORT_CAN_HANDLE_LAYER_MASKS
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_EXPORT_NEEDS_ALPHA
name|GIMP_EXPORT_NEEDS_ALPHA
init|=
literal|1
operator|<<
literal|8
DECL|typedef|GimpExportCapabilities
block|}
name|GimpExportCapabilities
typedef|;
end_typedef

begin_comment
comment|/**  * GimpExportReturn:  * @GIMP_EXPORT_CANCEL: The export was cancelled  * @GIMP_EXPORT_IGNORE: The image is unmodified but export shall continue anyway  * @GIMP_EXPORT_EXPORT: The chosen transforms were applied to the image  *  * Possible return values of gimp_export_image().  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a2d60da0203
block|{
DECL|enumerator|GIMP_EXPORT_CANCEL
name|GIMP_EXPORT_CANCEL
block|,
DECL|enumerator|GIMP_EXPORT_IGNORE
name|GIMP_EXPORT_IGNORE
block|,
DECL|enumerator|GIMP_EXPORT_EXPORT
name|GIMP_EXPORT_EXPORT
DECL|typedef|GimpExportReturn
block|}
name|GimpExportReturn
typedef|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_export_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_export_dialog_get_content_area
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
end_ifndef

begin_function_decl
name|GimpExportReturn
name|gimp_export_image
parameter_list|(
name|GimpImage
modifier|*
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format_name
parameter_list|,
name|GimpExportCapabilities
name|capabilities
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_define
DECL|macro|gimp_export_image
define|#
directive|define
name|gimp_export_image
value|gimp_export_image_deprecated
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_function_decl
name|GimpExportReturn
name|gimp_export_image_deprecated
parameter_list|(
name|gint32
modifier|*
name|image_id
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format_name
parameter_list|,
name|GimpExportCapabilities
name|capabilities
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_EXPORT_H__ */
end_comment

end_unit


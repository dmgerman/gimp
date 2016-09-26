begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CONVERT_PRECISION_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__CONVERT_PRECISION_DIALOG_H__
define|#
directive|define
name|__CONVERT_PRECISION_DIALOG_H__
end_define

begin_typedef
DECL|typedef|GimpConvertPrecisionCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpConvertPrecisionCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPrecision
name|precision
parameter_list|,
name|GeglDitherMethod
name|layer_dither_method
parameter_list|,
name|GeglDitherMethod
name|text_layer_dither_method
parameter_list|,
name|GeglDitherMethod
name|channel_dither_method
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|convert_precision_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpComponentType
name|component_type
parameter_list|,
name|GeglDitherMethod
name|layer_dither_method
parameter_list|,
name|GeglDitherMethod
name|text_layer_dither_method
parameter_list|,
name|GeglDitherMethod
name|channel_dither_method
parameter_list|,
name|GimpConvertPrecisionCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __CONVERT_PRECISION_DIALOG_H__  */
end_comment

end_unit


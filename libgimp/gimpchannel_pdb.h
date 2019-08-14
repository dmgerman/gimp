begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpchannel_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
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
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHANNEL_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHANNEL_PDB_H__
define|#
directive|define
name|__GIMP_CHANNEL_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
ifndef|#
directive|ifndef
name|GIMP_DEPRECATED_REPLACE_NEW_API
name|G_GNUC_INTERNAL
name|GimpChannel
modifier|*
name|_gimp_channel_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_channel_new_from_component
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_channel_copy
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_channel_combine_masks
parameter_list|(
name|GimpChannel
modifier|*
name|channel1
parameter_list|,
name|GimpChannel
modifier|*
name|channel2
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_channel_get_show_masked
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_channel_set_show_masked
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gboolean
name|show_masked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_channel_get_opacity
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_channel_set_opacity
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_channel_get_color
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_channel_set_color
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
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
define|#
directive|define
name|gimp_channel_new_from_component
value|_gimp_channel_new_from_component
end_define

begin_define
define|#
directive|define
name|gimp_channel_copy
value|_gimp_channel_copy
end_define

begin_define
define|#
directive|define
name|gimp_channel_combine_masks
value|_gimp_channel_combine_masks
end_define

begin_define
define|#
directive|define
name|gimp_channel_get_show_masked
value|_gimp_channel_get_show_masked
end_define

begin_define
define|#
directive|define
name|gimp_channel_set_show_masked
value|_gimp_channel_set_show_masked
end_define

begin_define
define|#
directive|define
name|gimp_channel_get_opacity
value|_gimp_channel_get_opacity
end_define

begin_define
define|#
directive|define
name|gimp_channel_set_opacity
value|_gimp_channel_set_opacity
end_define

begin_define
define|#
directive|define
name|gimp_channel_get_color
value|_gimp_channel_get_color
end_define

begin_define
define|#
directive|define
name|gimp_channel_set_color
value|_gimp_channel_set_color
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DEPRECATED_REPLACE_NEW_API */
end_comment

begin_comment
comment|/* Below API are deprecated and should not be used by new plug-ins.  * They are not marked internal as a trick to keep the old API alive for now.  */
end_comment

begin_function_decl
name|gint32
name|_gimp_channel_new_from_component
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|_gimp_channel_copy
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_channel_combine_masks
parameter_list|(
name|gint32
name|channel1_ID
parameter_list|,
name|gint32
name|channel2_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_channel_get_show_masked
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_channel_set_show_masked
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|gboolean
name|show_masked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|_gimp_channel_get_opacity
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_channel_set_opacity
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_channel_get_color
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_channel_set_color
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
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
comment|/* __GIMP_CHANNEL_PDB_H__ */
end_comment

end_unit


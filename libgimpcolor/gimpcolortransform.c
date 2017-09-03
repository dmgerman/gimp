begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcolortransform.c  * Copyright (C) 2014  Michael Natterer<mitch@gimp.org>  *                     Elle Stone<ellestone@ninedegreesbelow.com>  *                     Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<lcms2.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofile.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolortransform.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolortransform  * @title: GimpColorTransform  * @short_description: Definitions and Functions relating to LCMS.  *  * Definitions and Functions relating to LCMS.  **/
end_comment

begin_comment
comment|/**  * GimpColorTransform:  *  * Simply a typedef to #gpointer, but actually is a cmsHTRANSFORM. It's  * used in public GIMP APIs in order to avoid having to include LCMS  * headers.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2761ffe10103
block|{
DECL|enumerator|PROGRESS
name|PROGRESS
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpColorTransformPrivate
struct|struct
name|_GimpColorTransformPrivate
block|{
DECL|member|src_profile
name|GimpColorProfile
modifier|*
name|src_profile
decl_stmt|;
DECL|member|src_format
specifier|const
name|Babl
modifier|*
name|src_format
decl_stmt|;
DECL|member|src_space_format
specifier|const
name|Babl
modifier|*
name|src_space_format
decl_stmt|;
DECL|member|dest_profile
name|GimpColorProfile
modifier|*
name|dest_profile
decl_stmt|;
DECL|member|dest_format
specifier|const
name|Babl
modifier|*
name|dest_format
decl_stmt|;
DECL|member|dest_space_format
specifier|const
name|Babl
modifier|*
name|dest_space_format
decl_stmt|;
DECL|member|transform
name|cmsHTRANSFORM
name|transform
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_color_transform_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpColorTransform
argument_list|,
name|gimp_color_transform
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_transform_parent_class
end_define

begin_decl_stmt
DECL|variable|gimp_color_transform_signals
specifier|static
name|guint
name|gimp_color_transform_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|lcms_last_error
specifier|static
name|gchar
modifier|*
name|lcms_last_error
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|lcms_error_clear (void)
name|lcms_error_clear
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|lcms_last_error
condition|)
block|{
name|g_free
argument_list|(
name|lcms_last_error
argument_list|)
expr_stmt|;
name|lcms_last_error
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|lcms_error_handler (cmsContext ContextID,cmsUInt32Number ErrorCode,const gchar * text)
name|lcms_error_handler
parameter_list|(
name|cmsContext
name|ContextID
parameter_list|,
name|cmsUInt32Number
name|ErrorCode
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|lcms_error_clear
argument_list|()
expr_stmt|;
name|lcms_last_error
operator|=
name|g_strdup_printf
argument_list|(
literal|"lcms2 error %d: %s"
argument_list|,
name|ErrorCode
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_transform_class_init (GimpColorTransformClass * klass)
name|gimp_color_transform_class_init
parameter_list|(
name|GimpColorTransformClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_transform_finalize
expr_stmt|;
name|gimp_color_transform_signals
index|[
name|PROGRESS
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"progress"
argument_list|,
name|G_OBJECT_CLASS_TYPE
argument_list|(
name|object_class
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpColorTransformClass
argument_list|,
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpColorTransformPrivate
argument_list|)
argument_list|)
expr_stmt|;
name|cmsSetLogErrorHandler
argument_list|(
name|lcms_error_handler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_transform_init (GimpColorTransform * transform)
name|gimp_color_transform_init
parameter_list|(
name|GimpColorTransform
modifier|*
name|transform
parameter_list|)
block|{
name|transform
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|transform
argument_list|,
name|GIMP_TYPE_COLOR_TRANSFORM
argument_list|,
name|GimpColorTransformPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_transform_finalize (GObject * object)
name|gimp_color_transform_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorTransform
modifier|*
name|transform
init|=
name|GIMP_COLOR_TRANSFORM
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|transform
operator|->
name|priv
operator|->
name|src_profile
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|transform
operator|->
name|priv
operator|->
name|dest_profile
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|transform
operator|->
name|priv
operator|->
name|transform
argument_list|,
name|cmsDeleteTransform
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_transform_new:  * @src_profile:      the source #GimpColorProfile  * @src_format:       the source #Babl format  * @dest_profile:     the destination #GimpColorProfile  * @dest_format:      the destination #Babl format  * @rendering_intent: the rendering intent  * @flags:            transform flags  *  * This function creates an color transform.  *  * Return value: the #GimpColorTransform, or %NULL if no transform is needed  *               to convert between pixels of @src_profile and @dest_profile.  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpColorTransform
modifier|*
DECL|function|gimp_color_transform_new (GimpColorProfile * src_profile,const Babl * src_format,GimpColorProfile * dest_profile,const Babl * dest_format,GimpColorRenderingIntent rendering_intent,GimpColorTransformFlags flags)
name|gimp_color_transform_new
parameter_list|(
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|src_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|dest_format
parameter_list|,
name|GimpColorRenderingIntent
name|rendering_intent
parameter_list|,
name|GimpColorTransformFlags
name|flags
parameter_list|)
block|{
name|GimpColorTransform
modifier|*
name|transform
decl_stmt|;
name|GimpColorTransformPrivate
modifier|*
name|priv
decl_stmt|;
name|cmsHPROFILE
name|src_lcms
decl_stmt|;
name|cmsHPROFILE
name|dest_lcms
decl_stmt|;
name|cmsUInt32Number
name|lcms_src_format
decl_stmt|;
name|cmsUInt32Number
name|lcms_dest_format
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|src_profile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|dest_profile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_color_transform_can_gegl_copy
argument_list|(
name|src_profile
argument_list|,
name|dest_profile
argument_list|)
condition|)
return|return
name|NULL
return|;
name|transform
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_TRANSFORM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|transform
operator|->
name|priv
expr_stmt|;
name|priv
operator|->
name|src_space_format
operator|=
name|gimp_color_profile_get_format
argument_list|(
name|src_profile
argument_list|,
name|src_format
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|priv
operator|->
name|src_space_format
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: error making format: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|priv
operator|->
name|dest_space_format
operator|=
name|gimp_color_profile_get_format
argument_list|(
name|dest_profile
argument_list|,
name|dest_format
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|priv
operator|->
name|dest_space_format
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s: error making format: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|g_getenv
argument_list|(
literal|"GIMP_COLOR_TRANSFORM_DISABLE_BABL"
argument_list|)
operator|&&
name|priv
operator|->
name|src_space_format
operator|&&
name|priv
operator|->
name|dest_space_format
condition|)
block|{
name|priv
operator|->
name|src_format
operator|=
name|src_format
expr_stmt|;
name|priv
operator|->
name|dest_format
operator|=
name|dest_format
expr_stmt|;
name|g_printerr
argument_list|(
literal|"%s: using babl for '%s' -> '%s'\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|gimp_color_profile_get_label
argument_list|(
name|src_profile
argument_list|)
argument_list|,
name|gimp_color_profile_get_label
argument_list|(
name|dest_profile
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|transform
return|;
block|}
name|priv
operator|->
name|src_space_format
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|dest_space_format
operator|=
name|NULL
expr_stmt|;
name|priv
operator|->
name|src_format
operator|=
name|gimp_color_profile_get_lcms_format
argument_list|(
name|src_format
argument_list|,
operator|&
name|lcms_src_format
argument_list|)
expr_stmt|;
name|priv
operator|->
name|dest_format
operator|=
name|gimp_color_profile_get_lcms_format
argument_list|(
name|dest_format
argument_list|,
operator|&
name|lcms_dest_format
argument_list|)
expr_stmt|;
name|src_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
name|dest_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
name|lcms_error_clear
argument_list|()
expr_stmt|;
name|priv
operator|->
name|transform
operator|=
name|cmsCreateTransform
argument_list|(
name|src_lcms
argument_list|,
name|lcms_src_format
argument_list|,
name|dest_lcms
argument_list|,
name|lcms_dest_format
argument_list|,
name|rendering_intent
argument_list|,
name|flags
operator||
name|cmsFLAGS_COPY_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|lcms_last_error
condition|)
block|{
if|if
condition|(
name|priv
operator|->
name|transform
condition|)
block|{
name|cmsDeleteTransform
argument_list|(
name|priv
operator|->
name|transform
argument_list|)
expr_stmt|;
name|priv
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
name|g_printerr
argument_list|(
literal|"%s\n"
argument_list|,
name|lcms_last_error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|priv
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|transform
argument_list|)
expr_stmt|;
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|transform
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_transform_new_proofing:  * @src_profile:    the source #GimpColorProfile  * @src_format:     the source #Babl format  * @dest_profile:   the destination #GimpColorProfile  * @dest_format:    the destination #Babl format  * @proof_profile:  the proof #GimpColorProfile  * @proof_intent:   the proof intent  * @display_intent: the display intent  * @flags:          transform flags  *  * This function creates a simulation / proofing color transform.  *  * Return value: the #GimpColorTransform, or %NULL.  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpColorTransform
modifier|*
DECL|function|gimp_color_transform_new_proofing (GimpColorProfile * src_profile,const Babl * src_format,GimpColorProfile * dest_profile,const Babl * dest_format,GimpColorProfile * proof_profile,GimpColorRenderingIntent proof_intent,GimpColorRenderingIntent display_intent,GimpColorTransformFlags flags)
name|gimp_color_transform_new_proofing
parameter_list|(
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|src_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|,
specifier|const
name|Babl
modifier|*
name|dest_format
parameter_list|,
name|GimpColorProfile
modifier|*
name|proof_profile
parameter_list|,
name|GimpColorRenderingIntent
name|proof_intent
parameter_list|,
name|GimpColorRenderingIntent
name|display_intent
parameter_list|,
name|GimpColorTransformFlags
name|flags
parameter_list|)
block|{
name|GimpColorTransform
modifier|*
name|transform
decl_stmt|;
name|GimpColorTransformPrivate
modifier|*
name|priv
decl_stmt|;
name|cmsHPROFILE
name|src_lcms
decl_stmt|;
name|cmsHPROFILE
name|dest_lcms
decl_stmt|;
name|cmsHPROFILE
name|proof_lcms
decl_stmt|;
name|cmsUInt32Number
name|lcms_src_format
decl_stmt|;
name|cmsUInt32Number
name|lcms_dest_format
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|src_profile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|src_format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|dest_profile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dest_format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|proof_profile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|transform
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_TRANSFORM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|transform
operator|->
name|priv
expr_stmt|;
name|src_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|src_profile
argument_list|)
expr_stmt|;
name|dest_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|dest_profile
argument_list|)
expr_stmt|;
name|proof_lcms
operator|=
name|gimp_color_profile_get_lcms_profile
argument_list|(
name|proof_profile
argument_list|)
expr_stmt|;
name|priv
operator|->
name|src_format
operator|=
name|gimp_color_profile_get_lcms_format
argument_list|(
name|src_format
argument_list|,
operator|&
name|lcms_src_format
argument_list|)
expr_stmt|;
name|priv
operator|->
name|dest_format
operator|=
name|gimp_color_profile_get_lcms_format
argument_list|(
name|dest_format
argument_list|,
operator|&
name|lcms_dest_format
argument_list|)
expr_stmt|;
name|lcms_error_clear
argument_list|()
expr_stmt|;
name|priv
operator|->
name|transform
operator|=
name|cmsCreateProofingTransform
argument_list|(
name|src_lcms
argument_list|,
name|lcms_src_format
argument_list|,
name|dest_lcms
argument_list|,
name|lcms_dest_format
argument_list|,
name|proof_lcms
argument_list|,
name|proof_intent
argument_list|,
name|display_intent
argument_list|,
name|flags
operator||
name|cmsFLAGS_SOFTPROOFING
operator||
name|cmsFLAGS_COPY_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|lcms_last_error
condition|)
block|{
if|if
condition|(
name|priv
operator|->
name|transform
condition|)
block|{
name|cmsDeleteTransform
argument_list|(
name|priv
operator|->
name|transform
argument_list|)
expr_stmt|;
name|priv
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
name|g_printerr
argument_list|(
literal|"%s\n"
argument_list|,
name|lcms_last_error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|priv
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|transform
argument_list|)
expr_stmt|;
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|transform
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_transform_process_pixels:  * @transform:   a #GimpColorTransform  * @src_format:  #Babl format of @src_pixels  * @src_pixels:  pointer to the source pixels  * @dest_format: #Babl format of @dest_pixels  * @dest_pixels: pointer to the destination pixels  * @length:      number of pixels to process  *  * This function transforms a contiguous line of pixels.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_transform_process_pixels (GimpColorTransform * transform,const Babl * src_format,gconstpointer src_pixels,const Babl * dest_format,gpointer dest_pixels,gsize length)
name|gimp_color_transform_process_pixels
parameter_list|(
name|GimpColorTransform
modifier|*
name|transform
parameter_list|,
specifier|const
name|Babl
modifier|*
name|src_format
parameter_list|,
name|gconstpointer
name|src_pixels
parameter_list|,
specifier|const
name|Babl
modifier|*
name|dest_format
parameter_list|,
name|gpointer
name|dest_pixels
parameter_list|,
name|gsize
name|length
parameter_list|)
block|{
name|GimpColorTransformPrivate
modifier|*
name|priv
decl_stmt|;
name|gpointer
modifier|*
name|src
decl_stmt|;
name|gpointer
modifier|*
name|dest
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_TRANSFORM
argument_list|(
name|transform
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|src_format
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|src_pixels
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dest_format
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dest_pixels
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|transform
operator|->
name|priv
expr_stmt|;
if|if
condition|(
name|src_format
operator|!=
name|priv
operator|->
name|src_format
condition|)
block|{
name|src
operator|=
name|g_malloc
argument_list|(
name|length
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|priv
operator|->
name|src_format
argument_list|)
argument_list|)
expr_stmt|;
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|src_format
argument_list|,
name|priv
operator|->
name|src_format
argument_list|)
argument_list|,
name|src_pixels
argument_list|,
name|src
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|src
operator|=
operator|(
name|gpointer
operator|)
name|src_pixels
expr_stmt|;
block|}
if|if
condition|(
name|dest_format
operator|!=
name|priv
operator|->
name|dest_format
condition|)
block|{
name|dest
operator|=
name|g_malloc
argument_list|(
name|length
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|priv
operator|->
name|dest_format
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dest
operator|=
name|dest_pixels
expr_stmt|;
block|}
if|if
condition|(
name|priv
operator|->
name|transform
condition|)
block|{
name|cmsDoTransform
argument_list|(
name|priv
operator|->
name|transform
argument_list|,
name|src
argument_list|,
name|dest
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|priv
operator|->
name|src_space_format
argument_list|,
name|priv
operator|->
name|dest_space_format
argument_list|)
argument_list|,
name|src
argument_list|,
name|dest
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|src_format
operator|!=
name|priv
operator|->
name|src_format
condition|)
block|{
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dest_format
operator|!=
name|priv
operator|->
name|dest_format
condition|)
block|{
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|priv
operator|->
name|dest_format
argument_list|,
name|dest_format
argument_list|)
argument_list|,
name|dest
argument_list|,
name|dest_pixels
argument_list|,
name|length
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_transform_process_buffer:  * @transform:   a #GimpColorTransform  * @src_buffer:  source #GeglBuffer  * @src_rect:    rectangle in @src_buffer  * @dest_buffer: destination #GeglBuffer  * @dest_rect:   rectangle in @dest_buffer  *  * This function transforms buffer into another buffer.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_transform_process_buffer (GimpColorTransform * transform,GeglBuffer * src_buffer,const GeglRectangle * src_rect,GeglBuffer * dest_buffer,const GeglRectangle * dest_rect)
name|gimp_color_transform_process_buffer
parameter_list|(
name|GimpColorTransform
modifier|*
name|transform
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|src_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|dest_rect
parameter_list|)
block|{
name|GimpColorTransformPrivate
modifier|*
name|priv
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|gint
name|total_pixels
decl_stmt|;
name|gint
name|done_pixels
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_TRANSFORM
argument_list|(
name|transform
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|src_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|dest_buffer
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|transform
operator|->
name|priv
expr_stmt|;
if|if
condition|(
name|src_rect
condition|)
block|{
name|total_pixels
operator|=
name|src_rect
operator|->
name|width
operator|*
name|src_rect
operator|->
name|height
expr_stmt|;
block|}
else|else
block|{
name|total_pixels
operator|=
operator|(
name|gegl_buffer_get_width
argument_list|(
name|src_buffer
argument_list|)
operator|*
name|gegl_buffer_get_height
argument_list|(
name|src_buffer
argument_list|)
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|src_buffer
operator|!=
name|dest_buffer
condition|)
block|{
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|src_rect
argument_list|,
literal|0
argument_list|,
name|priv
operator|->
name|src_format
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|dest_buffer
argument_list|,
name|dest_rect
argument_list|,
literal|0
argument_list|,
name|priv
operator|->
name|dest_format
argument_list|,
name|GEGL_ACCESS_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
if|if
condition|(
name|priv
operator|->
name|transform
condition|)
block|{
name|cmsDoTransform
argument_list|(
name|priv
operator|->
name|transform
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|data
index|[
literal|1
index|]
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|priv
operator|->
name|src_space_format
argument_list|,
name|priv
operator|->
name|dest_space_format
argument_list|)
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|data
index|[
literal|1
index|]
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
block|}
name|done_pixels
operator|+=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
operator|*
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|height
expr_stmt|;
name|g_signal_emit
argument_list|(
name|transform
argument_list|,
name|gimp_color_transform_signals
index|[
name|PROGRESS
index|]
argument_list|,
literal|0
argument_list|,
operator|(
name|gdouble
operator|)
name|done_pixels
operator|/
operator|(
name|gdouble
operator|)
name|total_pixels
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|src_rect
argument_list|,
literal|0
argument_list|,
name|priv
operator|->
name|src_format
argument_list|,
name|GEGL_ACCESS_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
if|if
condition|(
name|priv
operator|->
name|transform
condition|)
block|{
name|cmsDoTransform
argument_list|(
name|priv
operator|->
name|transform
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|babl_process
argument_list|(
name|babl_fish
argument_list|(
name|priv
operator|->
name|src_space_format
argument_list|,
name|priv
operator|->
name|dest_space_format
argument_list|)
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|data
index|[
literal|0
index|]
argument_list|,
name|iter
operator|->
name|length
argument_list|)
expr_stmt|;
block|}
name|done_pixels
operator|+=
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|width
operator|*
name|iter
operator|->
name|roi
index|[
literal|0
index|]
operator|.
name|height
expr_stmt|;
name|g_signal_emit
argument_list|(
name|transform
argument_list|,
name|gimp_color_transform_signals
index|[
name|PROGRESS
index|]
argument_list|,
literal|0
argument_list|,
operator|(
name|gdouble
operator|)
name|done_pixels
operator|/
operator|(
name|gdouble
operator|)
name|total_pixels
argument_list|)
expr_stmt|;
block|}
block|}
name|g_signal_emit
argument_list|(
name|transform
argument_list|,
name|gimp_color_transform_signals
index|[
name|PROGRESS
index|]
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_transform_can_gegl_copy:  * @src_profile:  source #GimpColorProfile  * @dest_profile: destination #GimpColorProfile  *  * This function checks if a GimpColorTransform is needed at all.  *  * Return value: %TRUE if pixels can be correctly converted between  *               @src_profile and @dest_profile by simply using  *               gegl_buffer_copy(), babl_process() or similar.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_color_transform_can_gegl_copy (GimpColorProfile * src_profile,GimpColorProfile * dest_profile)
name|gimp_color_transform_can_gegl_copy
parameter_list|(
name|GimpColorProfile
modifier|*
name|src_profile
parameter_list|,
name|GimpColorProfile
modifier|*
name|dest_profile
parameter_list|)
block|{
specifier|static
name|GimpColorProfile
modifier|*
name|srgb_profile
init|=
name|NULL
decl_stmt|;
specifier|static
name|GimpColorProfile
modifier|*
name|srgb_linear_profile
init|=
name|NULL
decl_stmt|;
specifier|static
name|GimpColorProfile
modifier|*
name|gray_profile
init|=
name|NULL
decl_stmt|;
specifier|static
name|GimpColorProfile
modifier|*
name|gray_linear_profile
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|src_profile
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|dest_profile
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_color_profile_is_equal
argument_list|(
name|src_profile
argument_list|,
name|dest_profile
argument_list|)
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
operator|!
name|srgb_profile
condition|)
block|{
name|srgb_profile
operator|=
name|gimp_color_profile_new_rgb_srgb
argument_list|()
expr_stmt|;
name|srgb_linear_profile
operator|=
name|gimp_color_profile_new_rgb_srgb_linear
argument_list|()
expr_stmt|;
name|gray_profile
operator|=
name|gimp_color_profile_new_d65_gray_srgb_trc
argument_list|()
expr_stmt|;
name|gray_linear_profile
operator|=
name|gimp_color_profile_new_d65_gray_linear
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|gimp_color_profile_is_equal
argument_list|(
name|src_profile
argument_list|,
name|srgb_profile
argument_list|)
operator|||
name|gimp_color_profile_is_equal
argument_list|(
name|src_profile
argument_list|,
name|srgb_linear_profile
argument_list|)
operator|||
name|gimp_color_profile_is_equal
argument_list|(
name|src_profile
argument_list|,
name|gray_profile
argument_list|)
operator|||
name|gimp_color_profile_is_equal
argument_list|(
name|src_profile
argument_list|,
name|gray_linear_profile
argument_list|)
operator|)
operator|&&
operator|(
name|gimp_color_profile_is_equal
argument_list|(
name|dest_profile
argument_list|,
name|srgb_profile
argument_list|)
operator|||
name|gimp_color_profile_is_equal
argument_list|(
name|dest_profile
argument_list|,
name|srgb_linear_profile
argument_list|)
operator|||
name|gimp_color_profile_is_equal
argument_list|(
name|dest_profile
argument_list|,
name|gray_profile
argument_list|)
operator|||
name|gimp_color_profile_is_equal
argument_list|(
name|dest_profile
argument_list|,
name|gray_linear_profile
argument_list|)
operator|)
condition|)
block|{
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit


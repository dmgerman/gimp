begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * DDS GIMP plugin  *  * Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,  * with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DDSPLUGIN_H__
end_ifndef

begin_define
DECL|macro|__DDSPLUGIN_H__
define|#
directive|define
name|__DDSPLUGIN_H__
end_define

begin_define
DECL|macro|DDS_PLUGIN_VERSION_MAJOR
define|#
directive|define
name|DDS_PLUGIN_VERSION_MAJOR
value|3
end_define

begin_define
DECL|macro|DDS_PLUGIN_VERSION_MINOR
define|#
directive|define
name|DDS_PLUGIN_VERSION_MINOR
value|9
end_define

begin_define
DECL|macro|DDS_PLUGIN_VERSION_REVISION
define|#
directive|define
name|DDS_PLUGIN_VERSION_REVISION
value|90
end_define

begin_define
DECL|macro|DDS_PLUGIN_VERSION
define|#
directive|define
name|DDS_PLUGIN_VERSION
define|\
value|((unsigned int)(DDS_PLUGIN_VERSION_MAJOR<< 16) | \     (unsigned int)(DDS_PLUGIN_VERSION_MINOR<<  8) | \     (unsigned int)(DDS_PLUGIN_VERSION_REVISION))
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon274420610108
block|{
DECL|member|compression
name|gint
name|compression
decl_stmt|;
DECL|member|mipmaps
name|gint
name|mipmaps
decl_stmt|;
DECL|member|savetype
name|gint
name|savetype
decl_stmt|;
DECL|member|format
name|gint
name|format
decl_stmt|;
DECL|member|transindex
name|gint
name|transindex
decl_stmt|;
DECL|member|mipmap_filter
name|gint
name|mipmap_filter
decl_stmt|;
DECL|member|mipmap_wrap
name|gint
name|mipmap_wrap
decl_stmt|;
DECL|member|gamma_correct
name|gboolean
name|gamma_correct
decl_stmt|;
DECL|member|srgb
name|gboolean
name|srgb
decl_stmt|;
DECL|member|gamma
name|gdouble
name|gamma
decl_stmt|;
DECL|member|perceptual_metric
name|gboolean
name|perceptual_metric
decl_stmt|;
DECL|member|preserve_alpha_coverage
name|gboolean
name|preserve_alpha_coverage
decl_stmt|;
DECL|member|alpha_test_threshold
name|gdouble
name|alpha_test_threshold
decl_stmt|;
DECL|typedef|DDSWriteVals
block|}
name|DDSWriteVals
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|DDSWriteVals
name|dds_write_vals
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|GimpPDBStatusType
name|read_dds
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImage
modifier|*
modifier|*
name|image
parameter_list|,
name|gboolean
name|interactive
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpPDBStatusType
name|write_dds
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-dds-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-dds-save"
end_define

begin_define
DECL|macro|DECODE_YCOCG_PROC
define|#
directive|define
name|DECODE_YCOCG_PROC
value|"color-decode-ycocg"
end_define

begin_define
DECL|macro|DECODE_YCOCG_SCALED_PROC
define|#
directive|define
name|DECODE_YCOCG_SCALED_PROC
value|"color-decode-ycocg-scaled"
end_define

begin_define
DECL|macro|DECODE_ALPHA_EXP_PROC
define|#
directive|define
name|DECODE_ALPHA_EXP_PROC
value|"color-decode-alpha-exp"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DDSPLUGIN_H__ */
end_comment

end_unit


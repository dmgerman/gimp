begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* 	DDS GIMP plugin  	Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,    with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  	This program is free software; you can redistribute it and/or 	modify it under the terms of the GNU General Public 	License as published by the Free Software Foundation; either 	version 2 of the License, or (at your option) any later version.  	This program is distributed in the hope that it will be useful, 	but WITHOUT ANY WARRANTY; without even the implied warranty of 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 	General Public License for more details.  	You should have received a copy of the GNU General Public License 	along with this program; see the file COPYING.  If not, write to 	the Free Software Foundation, 51 Franklin Street, Fifth Floor 	Boston, MA 02110-1301, USA. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DDSPLUGIN_H
end_ifndef

begin_define
DECL|macro|__DDSPLUGIN_H
define|#
directive|define
name|__DDSPLUGIN_H
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
DECL|struct|__anon29660f130108
block|{
DECL|member|compression
name|int
name|compression
decl_stmt|;
DECL|member|mipmaps
name|int
name|mipmaps
decl_stmt|;
DECL|member|savetype
name|int
name|savetype
decl_stmt|;
DECL|member|format
name|int
name|format
decl_stmt|;
DECL|member|transindex
name|int
name|transindex
decl_stmt|;
DECL|member|mipmap_filter
name|int
name|mipmap_filter
decl_stmt|;
DECL|member|mipmap_wrap
name|int
name|mipmap_wrap
decl_stmt|;
DECL|member|gamma_correct
name|int
name|gamma_correct
decl_stmt|;
DECL|member|srgb
name|int
name|srgb
decl_stmt|;
DECL|member|gamma
name|float
name|gamma
decl_stmt|;
DECL|member|perceptual_metric
name|int
name|perceptual_metric
decl_stmt|;
DECL|member|show_adv_opt
name|int
name|show_adv_opt
decl_stmt|;
DECL|member|preserve_alpha_coverage
name|int
name|preserve_alpha_coverage
decl_stmt|;
DECL|member|alpha_test_threshold
name|float
name|alpha_test_threshold
decl_stmt|;
DECL|typedef|DDSWriteVals
block|}
name|DDSWriteVals
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29660f130208
block|{
DECL|member|show_dialog
name|int
name|show_dialog
decl_stmt|;
DECL|member|mipmaps
name|int
name|mipmaps
decl_stmt|;
DECL|member|decode_images
name|int
name|decode_images
decl_stmt|;
DECL|typedef|DDSReadVals
block|}
name|DDSReadVals
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|DDSWriteVals
name|dds_write_vals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|DDSReadVals
name|dds_read_vals
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|GimpPDBStatusType
name|read_dds
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
modifier|*
name|imageID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpPDBStatusType
name|write_dds
parameter_list|(
name|gchar
modifier|*
parameter_list|,
name|gint32
parameter_list|,
name|gint32
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|gint
name|interactive_dds
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|filename
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|FILE
modifier|*
name|errorFile
decl_stmt|;
end_decl_stmt

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

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_lib.h  * 1997.11.01 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * basic anim functions  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * 0.99.00; 1999/03/15   hof: prepared for win/dos filename conventions  * 0.96.02; 1998/08/05   hof: extended gap_dup (duplicate range instead of singele frame)  *                            added gap_shift (framesequence shift)  * 0.96.00; 1998/06/27   hof: added gap animation sizechange plugins  *                            (moved range_ops to seperate .h file)  * 0.94.01; 1998/04/27   hof: added flatten_mode to plugin: gap_range_to_multilayer  * 0.90.00;              hof: 1.st (pre) release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_LIB_H
end_ifndef

begin_define
DECL|macro|_GAP_LIB_H
define|#
directive|define
name|_GAP_LIB_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* G_DIR_SEPARATOR (is defined in glib.h if you have glib-1.2.0 or later) */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|NATIVE_WIN32
end_ifdef

begin_comment
comment|/* Filenames in WIN/DOS Style */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|G_DIR_SEPARATOR
end_ifndef

begin_define
DECL|macro|G_DIR_SEPARATOR
define|#
directive|define
name|G_DIR_SEPARATOR
value|'\\'
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|DIR_ROOT
define|#
directive|define
name|DIR_ROOT
value|':'
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !NATIVE_WIN32 */
end_comment

begin_comment
comment|/* Filenames in UNIX Style */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|G_DIR_SEPARATOR
end_ifndef

begin_define
DECL|macro|G_DIR_SEPARATOR
define|#
directive|define
name|G_DIR_SEPARATOR
value|'/'
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|DIR_ROOT
define|#
directive|define
name|DIR_ROOT
value|'/'
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !NATIVE_WIN32 */
end_comment

begin_typedef
DECL|struct|t_anim_info
typedef|typedef
struct|struct
name|t_anim_info
block|{
DECL|member|image_id
name|gint32
name|image_id
decl_stmt|;
DECL|member|basename
name|char
modifier|*
name|basename
decl_stmt|;
comment|/* may include path */
DECL|member|frame_nr
name|long
name|frame_nr
decl_stmt|;
DECL|member|extension
name|char
modifier|*
name|extension
decl_stmt|;
DECL|member|new_filename
name|char
modifier|*
name|new_filename
decl_stmt|;
DECL|member|old_filename
name|char
modifier|*
name|old_filename
decl_stmt|;
DECL|member|run_mode
name|GRunModeType
name|run_mode
decl_stmt|;
DECL|member|width
name|long
name|width
decl_stmt|;
DECL|member|height
name|long
name|height
decl_stmt|;
DECL|member|type
name|long
name|type
decl_stmt|;
DECL|member|frame_cnt
name|long
name|frame_cnt
decl_stmt|;
DECL|member|curr_frame_nr
name|long
name|curr_frame_nr
decl_stmt|;
DECL|member|first_frame_nr
name|long
name|first_frame_nr
decl_stmt|;
DECL|member|last_frame_nr
name|long
name|last_frame_nr
decl_stmt|;
DECL|typedef|t_anim_info
block|}
name|t_anim_info
typedef|;
end_typedef

begin_comment
comment|/* procedures used in other gap*.c files */
end_comment

begin_function_decl
name|int
name|p_file_exists
parameter_list|(
name|char
modifier|*
name|fname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_file_copy
parameter_list|(
name|char
modifier|*
name|fname
parameter_list|,
name|char
modifier|*
name|fname_copy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_free_ainfo
parameter_list|(
name|t_anim_info
modifier|*
modifier|*
name|ainfo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|p_alloc_basename
parameter_list|(
name|char
modifier|*
name|imagename
parameter_list|,
name|long
modifier|*
name|number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|p_alloc_extension
parameter_list|(
name|char
modifier|*
name|imagename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|t_anim_info
modifier|*
name|p_alloc_ainfo
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|GRunModeType
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_dir_ainfo
parameter_list|(
name|t_anim_info
modifier|*
name|ainfo_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_chk_framerange
parameter_list|(
name|t_anim_info
modifier|*
name|ainfo_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_chk_framechange
parameter_list|(
name|t_anim_info
modifier|*
name|ainfo_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_save_named_frame
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|sav_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_load_named_frame
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|lod_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_load_image
parameter_list|(
name|char
modifier|*
name|lod_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_save_named_image
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|sav_name
parameter_list|,
name|GRunModeType
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|p_alloc_fname
parameter_list|(
name|char
modifier|*
name|basename
parameter_list|,
name|long
name|nr
parameter_list|,
name|char
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|p_gzip
parameter_list|(
name|char
modifier|*
name|orig_name
parameter_list|,
name|char
modifier|*
name|new_name
parameter_list|,
name|char
modifier|*
name|zip
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* animation menu fuctions provided by gap_lib.c */
end_comment

begin_function_decl
name|int
name|gap_next
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_prev
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_first
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_last
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_goto
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|int
name|nr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_dup
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|int
name|nr
parameter_list|,
name|long
name|range_from
parameter_list|,
name|long
name|range_to
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_del
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|int
name|nr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_exchg
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|int
name|nr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_shift
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|int
name|nr
parameter_list|,
name|long
name|range_from
parameter_list|,
name|long
name|range_to
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_msg_win
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|char
modifier|*
name|msg
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit


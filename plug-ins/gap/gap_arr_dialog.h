begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_arr_dialog.h  * 1998.May.23 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins (Standard array dialog)  *  * - p_array_dialog   Dialog Window with one or more rows  *                    each row can contain one of the following GAP widgets:  *                       - float pair widget  *                         (horizontal slidebar combined with a float input field)  *                       - int pair widget  *                         (horizontal slidebar combined with a int input field)  *                       - Toggle Button widget  *                       - Textentry widget  *                       - Float entry widget  *                       - Int entry widget  * - p_slider_dialog  *                         simplified call of p_pair_array_dialog,  *                         using an array with one WGT_INT_PAIR.  * - p_buttons_dialog  *  *  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 0.96.03; 1998/08/15  hof: p_arr_gtk_init   * version 0.96.00; 1998/07/09  hof: 1.st release   *                                   (re-implementation of gap_sld_dialog.c)  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_ARR_DIALOG_H
end_ifndef

begin_define
DECL|macro|_ARR_DIALOG_H
define|#
directive|define
name|_ARR_DIALOG_H
end_define

begin_comment
comment|/* GIMP includes */
end_comment

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2890e7bb0103
block|{
DECL|enumerator|WGT_LABEL
name|WGT_LABEL
DECL|enumerator|WGT_TEXT
block|,
name|WGT_TEXT
DECL|enumerator|WGT_INT
block|,
name|WGT_INT
DECL|enumerator|WGT_FLT
block|,
name|WGT_FLT
DECL|enumerator|WGT_TOGGLE
block|,
name|WGT_TOGGLE
DECL|enumerator|WGT_RADIO
block|,
name|WGT_RADIO
DECL|enumerator|WGT_OPTIONMENU
block|,
name|WGT_OPTIONMENU
DECL|enumerator|WGT_FLT_PAIR
block|,
name|WGT_FLT_PAIR
DECL|enumerator|WGT_INT_PAIR
block|,
name|WGT_INT_PAIR
DECL|enumerator|WGT_ACT_BUTTON
block|,
name|WGT_ACT_BUTTON
DECL|enumerator|WGT_FILESEL
block|,
name|WGT_FILESEL
DECL|typedef|t_gap_widget
block|}
name|t_gap_widget
typedef|;
end_typedef

begin_typedef
DECL|typedef|t_action_func
typedef|typedef
name|int
function_decl|(
modifier|*
name|t_action_func
function_decl|)
parameter_list|(
name|gpointer
name|action_data
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  * - If one of the Args has set 'has_default' to TRUE  *   the action Area will contain an additional Button 'Default'  *  */
end_comment

begin_typedef
DECL|struct|__anon2890e7bb0208
typedef|typedef
struct|struct
block|{
DECL|member|widget_type
name|t_gap_widget
name|widget_type
decl_stmt|;
comment|/* common fields for all widget types */
DECL|member|label_txt
name|char
modifier|*
name|label_txt
decl_stmt|;
DECL|member|help_txt
name|char
modifier|*
name|help_txt
decl_stmt|;
DECL|member|entry_width
name|gint
name|entry_width
decl_stmt|;
comment|/* for all Widgets with  an entry */
DECL|member|scale_width
name|gint
name|scale_width
decl_stmt|;
comment|/* for the Widgets with a scale */
DECL|member|constraint
name|gint
name|constraint
decl_stmt|;
comment|/* TRUE: check for min/max values */
DECL|member|has_default
name|gint
name|has_default
decl_stmt|;
comment|/* TRUE: default value available */
comment|/* flt_ fileds are used for WGT_FLT and WGT_FLT_PAIR */
DECL|member|flt_format
name|char
modifier|*
name|flt_format
decl_stmt|;
comment|/* NULL or something like "%0.2f" */
DECL|member|flt_min
name|gdouble
name|flt_min
decl_stmt|;
DECL|member|flt_max
name|gdouble
name|flt_max
decl_stmt|;
DECL|member|flt_step
name|gdouble
name|flt_step
decl_stmt|;
DECL|member|flt_default
name|gdouble
name|flt_default
decl_stmt|;
DECL|member|flt_ret
name|gdouble
name|flt_ret
decl_stmt|;
DECL|member|flt_ret_lim
name|gdouble
name|flt_ret_lim
decl_stmt|;
comment|/* int_ fileds are used for WGT_INT and WGT_INT_PAIR WGT_TOGGLE */
DECL|member|int_format
name|char
modifier|*
name|int_format
decl_stmt|;
comment|/* NULL or something like "%d" */
DECL|member|int_min
name|gint
name|int_min
decl_stmt|;
DECL|member|int_max
name|gint
name|int_max
decl_stmt|;
DECL|member|int_step
name|gint
name|int_step
decl_stmt|;
DECL|member|int_default
name|gint
name|int_default
decl_stmt|;
DECL|member|int_ret
name|gint
name|int_ret
decl_stmt|;
DECL|member|int_ret_lim
name|gint
name|int_ret_lim
decl_stmt|;
comment|/* for private (arr_dialog.c) use only */
comment|/* togg_ field are used for WGT_TOGGLE */
DECL|member|togg_label
name|char
modifier|*
name|togg_label
decl_stmt|;
comment|/* extra label attached right to toggle button */
comment|/* radio_ fileds are used for WGT_RADIO and WGT_OPTIONMENU */
DECL|member|radio_argc
name|gint
name|radio_argc
decl_stmt|;
DECL|member|radio_default
name|gint
name|radio_default
decl_stmt|;
DECL|member|radio_ret
name|gint
name|radio_ret
decl_stmt|;
DECL|member|radio_argv
name|char
modifier|*
modifier|*
name|radio_argv
decl_stmt|;
DECL|member|radio_help_argv
name|char
modifier|*
modifier|*
name|radio_help_argv
decl_stmt|;
comment|/* text_ fileds are used for WGT_TEXT */
DECL|member|text_buf_len
name|gint
name|text_buf_len
decl_stmt|;
comment|/* common length for init, default and ret text_buffers */
DECL|member|text_buf_default
name|char
modifier|*
name|text_buf_default
decl_stmt|;
DECL|member|text_buf_ret
name|char
modifier|*
name|text_buf_ret
decl_stmt|;
DECL|member|text_filesel
name|GtkWidget
modifier|*
name|text_filesel
decl_stmt|;
comment|/* for private (arr_dialog.c) use only */
DECL|member|text_entry
name|GtkWidget
modifier|*
name|text_entry
decl_stmt|;
comment|/* for private (arr_dialog.c) use only */
comment|/* action_ fileds are used for WGT_ACT_BUTTON */
DECL|member|action_functon
name|t_action_func
name|action_functon
decl_stmt|;
DECL|member|action_data
name|gpointer
name|action_data
decl_stmt|;
DECL|typedef|t_arr_arg
block|}
name|t_arr_arg
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2890e7bb0308
typedef|typedef
struct|struct
block|{
DECL|member|but_txt
name|char
modifier|*
name|but_txt
decl_stmt|;
DECL|member|but_val
name|gint
name|but_val
decl_stmt|;
DECL|typedef|t_but_arg
block|}
name|t_but_arg
typedef|;
end_typedef

begin_function_decl
name|void
name|p_init_arr_arg
parameter_list|(
name|t_arr_arg
modifier|*
name|arr_ptr
parameter_list|,
name|gint
name|widget_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_array_dialog
parameter_list|(
name|char
modifier|*
name|title_txt
parameter_list|,
name|char
modifier|*
name|frame_txt
parameter_list|,
name|int
name|argc
parameter_list|,
name|t_arr_arg
name|argv
index|[]
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|long
name|p_slider_dialog
parameter_list|(
name|char
modifier|*
name|title_txt
parameter_list|,
name|char
modifier|*
name|frame_txt
parameter_list|,
name|char
modifier|*
name|label_txt
parameter_list|,
name|char
modifier|*
name|tooltip_txt
parameter_list|,
name|long
name|min
parameter_list|,
name|long
name|max
parameter_list|,
name|long
name|curr
parameter_list|,
name|long
name|constraint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_buttons_dialog
parameter_list|(
name|char
modifier|*
name|title_txt
parameter_list|,
name|char
modifier|*
name|frame_txt
parameter_list|,
name|int
name|b_argc
parameter_list|,
name|t_but_arg
name|b_argv
index|[]
parameter_list|,
name|gint
name|b_def_val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_array_std_dialog
parameter_list|(
name|char
modifier|*
name|title_txt
parameter_list|,
name|char
modifier|*
name|frame_txt
parameter_list|,
name|int
name|argc
parameter_list|,
name|t_arr_arg
name|argv
index|[]
parameter_list|,
name|int
name|b_argc
parameter_list|,
name|t_but_arg
name|b_argv
index|[]
parameter_list|,
name|gint
name|b_def_val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_arr_gtk_init
parameter_list|(
name|gint
name|flag
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit


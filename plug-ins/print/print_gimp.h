begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * "$Id$"  *  *   Print plug-in for the GIMP.  *  *   Copyright 1997-2000 Michael Sweet (mike@easysw.com),  *	Robert Krawitz (rlk@alum.mit.edu). and Steve Miller (smiller@rni.net  *  *   This program is free software; you can redistribute it and/or modify it  *   under the terms of the GNU General Public License as published by the Free  *   Software Foundation; either version 2 of the License, or (at your option)  *   any later version.  *  *   This program is distributed in the hope that it will be useful, but  *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  *   for more details.  *  *   You should have received a copy of the GNU General Public License  *   along with this program; if not, write to the Free Software  *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Revision History:  *  *   See ChangeLog  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PRINT_GIMP_H__
end_ifndef

begin_define
DECL|macro|__PRINT_GIMP_H__
define|#
directive|define
name|__PRINT_GIMP_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_define
DECL|macro|inline
define|#
directive|define
name|inline
value|__inline__
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * All Gimp-specific code is in this file.  */
end_comment

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"4.2"
end_define

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"Print"
end_define

begin_typedef
typedef|typedef
struct|struct
comment|/**** Printer List ****/
DECL|struct|__anon2774fe350108
block|{
DECL|member|active
name|int
name|active
decl_stmt|;
comment|/* Do we know about this printer? */
DECL|member|name
name|char
name|name
index|[
literal|128
index|]
decl_stmt|;
comment|/* Name of printer */
DECL|member|v
name|stp_vars_t
name|v
decl_stmt|;
DECL|typedef|gp_plist_t
block|}
name|gp_plist_t
typedef|;
end_typedef

begin_define
DECL|macro|THUMBNAIL_MAXW
define|#
directive|define
name|THUMBNAIL_MAXW
value|(128)
end_define

begin_define
DECL|macro|THUMBNAIL_MAXH
define|#
directive|define
name|THUMBNAIL_MAXH
value|(128)
end_define

begin_decl_stmt
specifier|extern
name|gint
name|thumbnail_w
decl_stmt|,
name|thumbnail_h
decl_stmt|,
name|thumbnail_bpp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|thumbnail_data
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|adjusted_thumbnail_bpp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|guchar
modifier|*
name|adjusted_thumbnail_data
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|stp_vars_t
name|vars
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|plist_count
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Number of system printers */
end_comment

begin_decl_stmt
specifier|extern
name|gint
name|plist_current
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Current system printer */
end_comment

begin_decl_stmt
specifier|extern
name|gp_plist_t
modifier|*
name|plist
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* System printers */
end_comment

begin_decl_stmt
specifier|extern
name|gint32
name|image_ID
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|image_name
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|image_width
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|image_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|stp_printer_t
name|current_printer
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|runme
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|saveme
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|gimp_color_adjust_dialog
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|dither_algo_combo
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|stp_vars_t
modifier|*
name|pv
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * Function prototypes  */
end_comment

begin_comment
comment|/* How to create an Image wrapping a Gimp drawable */
end_comment

begin_function_decl
specifier|extern
name|void
name|printrc_save
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|stp_image_t
modifier|*
name|Image_GimpDrawable_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|add_printer
parameter_list|(
specifier|const
name|gp_plist_t
modifier|*
name|key
parameter_list|,
name|int
name|add_only
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|initialize_printer
parameter_list|(
name|gp_plist_t
modifier|*
name|printer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_update_adjusted_thumbnail
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_plist_build_combo
parameter_list|(
name|GtkWidget
modifier|*
name|combo
parameter_list|,
name|gint
name|num_items
parameter_list|,
name|stp_param_t
modifier|*
name|items
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cur_item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|def_value
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gint
modifier|*
name|callback_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_invalidate_frame
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_invalidate_preview_thumbnail
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_do_color_updates
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_redraw_color_swatch
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_build_dither_combo
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_create_color_adjust_window
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_update_adjusted_thumbnail
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_create_main_window
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_set_color_sliders_active
parameter_list|(
name|int
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_writefunc
parameter_list|(
name|void
modifier|*
name|file
parameter_list|,
specifier|const
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|set_adjustment_tooltip
parameter_list|(
name|GtkObject
modifier|*
name|adjustment
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PRINT_GIMP_H__ */
end_comment

end_unit


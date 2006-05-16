begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Eiichi Takamori  * Copyright (C) 1996, 1997 Torsten Martinsen  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Some useful macros */
end_comment

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-engrave"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"engrave"
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|125
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|16
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27cc01160108
block|{
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|limit
name|gboolean
name|limit
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|EngraveValues
block|}
name|EngraveValues
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|engrave_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|engrave
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static void      engrave_large  (GimpDrawable *drawable,                                  gint          height,                                  gboolean      limit,                                  GimpPreview  *preview);
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|void
name|engrave_small
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|limit
parameter_list|,
name|gint
name|tile_width
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|engrave_sub
parameter_list|(
name|gint
name|height
parameter_list|,
name|gboolean
name|limit
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|color_n
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pvals
specifier|static
name|EngraveValues
name|pvals
init|=
block|{
literal|10
block|,
comment|/* height  */
name|FALSE
block|,
comment|/* limit   */
name|TRUE
comment|/* preview */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (unused)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"Resolution in pixels"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"limit"
block|,
literal|"If true, limit line width"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Simulate an antique engraving"
argument_list|)
argument_list|,
literal|"Creates a black-and-white 'engraved' version of an image as seen in old illustrations"
argument_list|,
literal|"Spencer Kimball& Peter Mattis, Eiichi Takamori, Torsten Martinsen"
argument_list|,
literal|"Spencer Kimball& Peter Mattis, Eiichi Takamori, Torsten Martinsen"
argument_list|,
literal|"1995,1996,1997"
argument_list|,
name|N_
argument_list|(
literal|"En_grave..."
argument_list|)
argument_list|,
literal|"RGBA, GRAYA"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Filters/Distorts"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
comment|/*  Get the specified drawable  */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|engrave_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|5
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|pvals
operator|.
name|height
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|pvals
operator|.
name|limit
operator|=
operator|(
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
operator|&&
name|pvals
operator|.
name|height
operator|<
literal|0
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Engraving"
argument_list|)
argument_list|)
expr_stmt|;
name|engrave
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
comment|/*  Store data  */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|pvals
argument_list|,
sizeof|sizeof
argument_list|(
name|EngraveValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|engrave_dialog (GimpDrawable * drawable)
name|engrave_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Engrave"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_drawable_preview_new
argument_list|(
name|drawable
argument_list|,
operator|&
name|pvals
operator|.
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|engrave
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Height:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|pvals
operator|.
name|height
argument_list|,
literal|2.0
argument_list|,
literal|16.0
argument_list|,
literal|1.0
argument_list|,
literal|4.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|pvals
operator|.
name|height
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Limit line width"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|pvals
operator|.
name|limit
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|pvals
operator|.
name|limit
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

begin_comment
comment|/*  Engrave interface functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|engrave (GimpDrawable * drawable,GimpPreview * preview)
name|engrave
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|gint
name|tile_width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gboolean
name|limit
decl_stmt|;
name|tile_width
operator|=
name|gimp_tile_width
argument_list|()
expr_stmt|;
name|height
operator|=
name|pvals
operator|.
name|height
expr_stmt|;
name|limit
operator|=
name|pvals
operator|.
name|limit
expr_stmt|;
comment|/* [DindinX] this test is always false since    * tile_width == 64 and height<= 16 */
if|#
directive|if
literal|0
block|if (height>= tile_width)     engrave_large (drawable, height, limit, preview);   else
endif|#
directive|endif
name|engrave_small
argument_list|(
name|drawable
argument_list|,
name|height
argument_list|,
name|limit
argument_list|,
name|tile_width
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|static void engrave_large (GimpDrawable *drawable,                gint          height,                gboolean      limit,                GimpPreview  *preview) {   GimpPixelRgn  src_rgn, dest_rgn;   guchar       *src_row, *dest_row;   guchar       *src, *dest;   gulong       *average;   gint          row, col, b, bpp;   gint          x, y, y_step, inten, v;   gulong        count;   gint          x1, y1, x2, y2;   gint          progress, max_progress;   gpointer      pr;    gimp_drawable_mask_bounds (drawable->drawable_id,&x1,&y1,&x2,&y2);    bpp = (gimp_drawable_is_rgb (drawable->drawable_id)) ? 3 : 1;   average = g_new (gulong, bpp);
comment|/* Initialize progress */
end_comment

begin_comment
unit|progress = 0;   max_progress = 2 * (x2 - x1) * (y2 - y1);    for (y = y1; y< y2; y += height - (y % height))     {       for (x = x1; x< x2; ++x)         {           y_step = height - (y % height);           y_step = MIN (y_step, x2 - x);            gimp_pixel_rgn_init (&src_rgn, drawable, x, y, 1, y_step,                                FALSE, FALSE);           for (b = 0; b< bpp; b++)             average[b] = 0;           count = 0;            for (pr = gimp_pixel_rgns_register (1,&src_rgn);                pr != NULL;                pr = gimp_pixel_rgns_process(pr))             {               src_row = src_rgn.data;               for (row = 0; row< src_rgn.h; row++)                 {                   src = src_row;                   for (col = 0; col< src_rgn.w; col++)                     {                       for (b = 0; b< bpp; b++)                         average[b] += src[b];                       src += src_rgn.bpp;                       count += 1;                     }                   src_row += src_rgn.rowstride;                 }
comment|/* Update progress */
end_comment

begin_comment
unit|progress += src_rgn.w * src_rgn.h;               gimp_progress_update ((double) progress / (double) max_progress);             }            if (count> 0)             for (b = 0; b< bpp; b++)               average[b] = (guchar) (average[b] / count);            if (bpp< 3)             inten = average[0] / 254.0 * height;           else             inten = GIMP_RGB_LUMINANCE (average[0],                                         average[1],                                         average[2]) / 254.0 * height;            gimp_pixel_rgn_init (&dest_rgn,                                drawable, x, y, 1, y_step, TRUE, TRUE);           for (pr = gimp_pixel_rgns_register (1,&dest_rgn);                pr != NULL;                pr = gimp_pixel_rgns_process(pr))             {               dest_row = dest_rgn.data;               for (row = 0; row< dest_rgn.h; row++)                 {                   dest = dest_row;                   v = inten> row ? 255 : 0;                   if (limit)                     {                       if (row == 0)                         v = 255;                       else if (row == height-1)                         v = 0;                     }                   for (b = 0; b< bpp; b++)                     dest[b] = v;                   dest_row += dest_rgn.rowstride;                 }
comment|/* Update progress */
end_comment

begin_comment
unit|progress += dest_rgn.w * dest_rgn.h;               gimp_progress_update((double) progress / (double) max_progress);             }         }     }    g_free (average);
comment|/*  update the engraved region  */
end_comment

begin_endif
unit|gimp_drawable_flush( drawable);   gimp_drawable_merge_shadow (drawable->drawable_id, TRUE);   gimp_drawable_update (drawable->drawable_id, x1, y1, x2 - x1, y2 - y1); }
endif|#
directive|endif
end_endif

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27cc01160208
block|{
DECL|member|x
DECL|member|y
DECL|member|h
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|h
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
DECL|typedef|PixelArea
block|}
name|PixelArea
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|area
name|PixelArea
name|area
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|engrave_small (GimpDrawable * drawable,gint line_height,gboolean limit,gint tile_width,GimpPreview * preview)
name|engrave_small
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|line_height
parameter_list|,
name|gboolean
name|limit
parameter_list|,
name|gint
name|tile_width
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|gint
name|bpp
decl_stmt|,
name|color_n
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
comment|/*     For speed efficiency, operates on PixelAreas, whose each width and     height are less than tile size.      If both ends of area cannot be divided by line_height ( as     x1%line_height != 0 etc.), operates on the remainder pixels.   */
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|height
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
block|}
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|preview
operator|==
name|NULL
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* Initialize progress */
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|width
operator|*
name|height
expr_stmt|;
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|color_n
operator|=
operator|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|)
condition|?
literal|3
else|:
literal|1
expr_stmt|;
name|area
operator|.
name|width
operator|=
operator|(
name|tile_width
operator|/
name|line_height
operator|)
operator|*
name|line_height
expr_stmt|;
name|area
operator|.
name|data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|glong
operator|)
name|bpp
operator|*
name|area
operator|.
name|width
operator|*
name|area
operator|.
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|area
operator|.
name|y
operator|=
name|y1
init|;
name|area
operator|.
name|y
operator|<
name|y2
condition|;
name|area
operator|.
name|y
operator|+=
name|area
operator|.
name|width
operator|-
operator|(
name|area
operator|.
name|y
operator|%
name|area
operator|.
name|width
operator|)
control|)
block|{
name|area
operator|.
name|h
operator|=
name|area
operator|.
name|width
operator|-
operator|(
name|area
operator|.
name|y
operator|%
name|area
operator|.
name|width
operator|)
expr_stmt|;
name|area
operator|.
name|h
operator|=
name|MIN
argument_list|(
name|area
operator|.
name|h
argument_list|,
name|y2
operator|-
name|area
operator|.
name|y
argument_list|)
expr_stmt|;
for|for
control|(
name|area
operator|.
name|x
operator|=
name|x1
init|;
name|area
operator|.
name|x
operator|<
name|x2
condition|;
operator|++
name|area
operator|.
name|x
control|)
block|{
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|area
operator|.
name|data
argument_list|,
name|area
operator|.
name|x
argument_list|,
name|area
operator|.
name|y
argument_list|,
literal|1
argument_list|,
name|area
operator|.
name|h
argument_list|)
expr_stmt|;
name|engrave_sub
argument_list|(
name|line_height
argument_list|,
name|limit
argument_list|,
name|bpp
argument_list|,
name|color_n
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|area
operator|.
name|data
argument_list|,
name|area
operator|.
name|x
argument_list|,
name|area
operator|.
name|y
argument_list|,
literal|1
argument_list|,
name|area
operator|.
name|h
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|preview
condition|)
block|{
comment|/* Update progress */
name|progress
operator|+=
name|area
operator|.
name|h
operator|*
name|width
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|area
operator|.
name|data
argument_list|)
expr_stmt|;
comment|/*  update the engraved region  */
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_drawable_preview_draw_region
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|dest_rgn
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|engrave_sub (gint height,gint limit,gint bpp,gint color_n)
name|engrave_sub
parameter_list|(
name|gint
name|height
parameter_list|,
name|gint
name|limit
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|color_n
parameter_list|)
block|{
name|glong
name|average
index|[
literal|3
index|]
decl_stmt|;
comment|/* color_n<= 3 */
name|gint
name|y
decl_stmt|,
name|h
decl_stmt|,
name|inten
decl_stmt|,
name|v
decl_stmt|;
name|guchar
modifier|*
name|buf_row
decl_stmt|,
modifier|*
name|buf
decl_stmt|;
name|gint
name|row
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/*     Since there's so many nested FOR's,     put a few of them here...   */
name|rowstride
operator|=
name|bpp
expr_stmt|;
for|for
control|(
name|y
operator|=
name|area
operator|.
name|y
init|;
name|y
operator|<
name|area
operator|.
name|y
operator|+
name|area
operator|.
name|h
condition|;
name|y
operator|+=
name|height
operator|-
operator|(
name|y
operator|%
name|height
operator|)
control|)
block|{
name|h
operator|=
name|height
operator|-
operator|(
name|y
operator|%
name|height
operator|)
expr_stmt|;
name|h
operator|=
name|MIN
argument_list|(
name|h
argument_list|,
name|area
operator|.
name|y
operator|+
name|area
operator|.
name|h
operator|-
name|y
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|color_n
condition|;
name|i
operator|++
control|)
name|average
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
name|count
operator|=
literal|0
expr_stmt|;
comment|/* Read */
name|buf_row
operator|=
name|area
operator|.
name|data
operator|+
operator|(
name|y
operator|-
name|area
operator|.
name|y
operator|)
operator|*
name|rowstride
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|h
condition|;
name|row
operator|++
control|)
block|{
name|buf
operator|=
name|buf_row
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|color_n
condition|;
name|i
operator|++
control|)
name|average
index|[
name|i
index|]
operator|+=
name|buf
index|[
name|i
index|]
expr_stmt|;
name|count
operator|++
expr_stmt|;
name|buf_row
operator|+=
name|rowstride
expr_stmt|;
block|}
comment|/* Average */
if|if
condition|(
name|count
operator|>
literal|0
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|color_n
condition|;
name|i
operator|++
control|)
name|average
index|[
name|i
index|]
operator|/=
name|count
expr_stmt|;
if|if
condition|(
name|bpp
operator|<
literal|3
condition|)
name|inten
operator|=
name|average
index|[
literal|0
index|]
operator|/
literal|254.0
operator|*
name|height
expr_stmt|;
else|else
name|inten
operator|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|average
index|[
literal|0
index|]
argument_list|,
name|average
index|[
literal|1
index|]
argument_list|,
name|average
index|[
literal|2
index|]
argument_list|)
operator|/
literal|254.0
operator|*
name|height
expr_stmt|;
comment|/* Write */
name|buf_row
operator|=
name|area
operator|.
name|data
operator|+
operator|(
name|y
operator|-
name|area
operator|.
name|y
operator|)
operator|*
name|rowstride
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|h
condition|;
name|row
operator|++
control|)
block|{
name|buf
operator|=
name|buf_row
expr_stmt|;
name|v
operator|=
name|inten
operator|>
name|row
condition|?
literal|255
else|:
literal|0
expr_stmt|;
if|if
condition|(
name|limit
condition|)
block|{
if|if
condition|(
name|row
operator|==
literal|0
condition|)
name|v
operator|=
literal|255
expr_stmt|;
elseif|else
if|if
condition|(
name|row
operator|==
name|height
operator|-
literal|1
condition|)
name|v
operator|=
literal|0
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|color_n
condition|;
name|i
operator|++
control|)
name|buf
index|[
name|i
index|]
operator|=
name|v
expr_stmt|;
name|buf_row
operator|+=
name|rowstride
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit


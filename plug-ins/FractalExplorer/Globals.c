begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"FractalExplorer.h"
end_include

begin_comment
comment|/**********************************************************************   Global variables    *********************************************************************/
end_comment

begin_decl_stmt
DECL|variable|xmin
name|double
name|xmin
init|=
operator|-
literal|2
decl_stmt|,
DECL|variable|xmax
name|xmax
init|=
literal|1
decl_stmt|,
DECL|variable|ymin
name|ymin
init|=
operator|-
literal|1.5
decl_stmt|,
DECL|variable|ymax
name|ymax
init|=
literal|1.5
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xbild
name|double
name|xbild
decl_stmt|,
DECL|variable|ybild
name|ybild
decl_stmt|,
DECL|variable|xdiff
name|xdiff
decl_stmt|,
DECL|variable|ydiff
name|ydiff
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|x_press
name|double
name|x_press
init|=
operator|-
literal|1.0
decl_stmt|,
DECL|variable|y_press
name|y_press
init|=
operator|-
literal|1.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|x_release
name|double
name|x_release
init|=
operator|-
literal|1.0
decl_stmt|,
DECL|variable|y_release
name|y_release
init|=
operator|-
literal|1.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cx
name|float
name|cx
init|=
operator|-
literal|0.75
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cy
name|float
name|cy
init|=
operator|-
literal|0.2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tile_width
name|gint
name|tile_width
decl_stmt|,
DECL|variable|tile_height
name|tile_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|img_width
name|gint
name|img_width
decl_stmt|,
DECL|variable|img_height
name|img_height
decl_stmt|,
DECL|variable|img_bpp
name|img_bpp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sel_x1
name|gint
name|sel_x1
decl_stmt|,
DECL|variable|sel_y1
name|sel_y1
decl_stmt|,
DECL|variable|sel_x2
name|sel_x2
decl_stmt|,
DECL|variable|sel_y2
name|sel_y2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sel_width
name|gint
name|sel_width
decl_stmt|,
DECL|variable|sel_height
name|sel_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview_width
name|gint
name|preview_width
decl_stmt|,
DECL|variable|preview_height
name|preview_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|the_tile
name|GimpTile
modifier|*
name|the_tile
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cen_x
name|double
name|cen_x
decl_stmt|,
DECL|variable|cen_y
name|cen_y
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xpos
name|double
name|xpos
decl_stmt|,
DECL|variable|ypos
name|ypos
decl_stmt|,
DECL|variable|oldxpos
name|oldxpos
init|=
operator|-
literal|1
decl_stmt|,
DECL|variable|oldypos
name|oldypos
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|maindlg
name|GtkWidget
modifier|*
name|maindlg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|logodlg
name|GtkWidget
modifier|*
name|logodlg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cmap_preview
name|GtkWidget
modifier|*
name|cmap_preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|delete_frame_to_freeze
name|GtkWidget
modifier|*
name|delete_frame_to_freeze
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fractalexplorer_gtk_list
name|GtkWidget
modifier|*
name|fractalexplorer_gtk_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|save_menu_item
name|GtkWidget
modifier|*
name|save_menu_item
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fractalexplorer_op_menu
name|GtkWidget
modifier|*
name|fractalexplorer_op_menu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|MyCursor
name|GdkCursor
modifier|*
name|MyCursor
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ready_now
name|int
name|ready_now
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|zooms
name|explorer_vals_t
name|zooms
index|[
literal|100
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|elements
name|DialogElements
modifier|*
name|elements
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|zoomindex
name|int
name|zoomindex
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|zoommax
name|int
name|zoommax
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gg
name|gdouble
modifier|*
name|gg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|line_no
name|int
name|line_no
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|colormap
name|clrmap
name|colormap
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fractalexplorer_path_list
name|GList
modifier|*
name|fractalexplorer_path_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fractalexplorer_list
name|GList
modifier|*
name|fractalexplorer_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradient_list
name|GList
modifier|*
name|gradient_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tpath
name|gchar
modifier|*
name|tpath
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fractalexplorer_obj_for_menu
name|fractalexplorerOBJ
modifier|*
name|fractalexplorer_obj_for_menu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rescan_list
name|GList
modifier|*
name|rescan_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wint
name|explorer_interface_t
name|wint
init|=
block|{
name|NULL
block|,
comment|/* preview */
name|NULL
block|,
comment|/* wimage */
name|FALSE
comment|/* run */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* wint */
end_comment

begin_decl_stmt
DECL|variable|wvals
name|explorer_vals_t
name|wvals
init|=
block|{
literal|0
block|,
operator|-
literal|2.0
block|,
literal|2.0
block|,
operator|-
literal|1.5
block|,
literal|1.5
block|,
literal|50.0
block|,
operator|-
literal|0.75
block|,
operator|-
literal|0.2
block|,
literal|0
block|,
literal|128.0
block|,
literal|128.0
block|,
literal|128.0
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|256
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* wvals */
end_comment

begin_decl_stmt
DECL|variable|standardvals
name|explorer_vals_t
name|standardvals
init|=
block|{
literal|0
block|,
operator|-
literal|2.0
block|,
literal|2.0
block|,
operator|-
literal|1.5
block|,
literal|1.5
block|,
literal|50.0
block|,
operator|-
literal|0.75
block|,
operator|-
literal|0.2
block|,
literal|0
block|,
literal|128.0
block|,
literal|128.0
block|,
literal|128.0
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|256
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* standardvals */
end_comment

begin_decl_stmt
DECL|variable|current_obj
name|fractalexplorerOBJ
modifier|*
name|current_obj
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pic_obj
name|fractalexplorerOBJ
modifier|*
name|pic_obj
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|delete_dialog
name|GtkWidget
modifier|*
name|delete_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

end_unit


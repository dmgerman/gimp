begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__FRACTALEXPLORER_H__
end_ifndef

begin_define
DECL|macro|__FRACTALEXPLORER_H__
define|#
directive|define
name|__FRACTALEXPLORER_H__
end_define

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

begin_comment
comment|/**********************************************************************  Magic numbers    *********************************************************************/
end_comment

begin_define
DECL|macro|PREVIEW_SIZE
define|#
directive|define
name|PREVIEW_SIZE
value|128
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|200
end_define

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|60
end_define

begin_define
DECL|macro|MAX_LOAD_LINE
define|#
directive|define
name|MAX_LOAD_LINE
value|256
end_define

begin_define
DECL|macro|GR_WIDTH
define|#
directive|define
name|GR_WIDTH
value|325
end_define

begin_define
DECL|macro|MAXNCOLORS
define|#
directive|define
name|MAXNCOLORS
value|8192
end_define

begin_define
DECL|macro|MAXSTRLEN
define|#
directive|define
name|MAXSTRLEN
value|256
end_define

begin_define
DECL|macro|FRACTAL_HEADER
define|#
directive|define
name|FRACTAL_HEADER
value|"Fractal Explorer Plug-In Version 2 - (c) 1997<cotting@mygale.org>\n"
end_define

begin_define
DECL|macro|fractalexplorer_HEADER
define|#
directive|define
name|fractalexplorer_HEADER
value|"Fractal Explorer Plug-In Version 2 - (c) 1997<cotting@mygale.org>\n"
end_define

begin_enum
enum|enum
DECL|enum|__anon293456fa0103
block|{
DECL|enumerator|SINUS
name|SINUS
block|,
DECL|enumerator|COSINUS
name|COSINUS
block|,
DECL|enumerator|NONE
name|NONE
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon293456fa0203
block|{
DECL|enumerator|TYPE_MANDELBROT
name|TYPE_MANDELBROT
block|,
DECL|enumerator|TYPE_JULIA
name|TYPE_JULIA
block|,
DECL|enumerator|TYPE_BARNSLEY_1
name|TYPE_BARNSLEY_1
block|,
DECL|enumerator|TYPE_BARNSLEY_2
name|TYPE_BARNSLEY_2
block|,
DECL|enumerator|TYPE_BARNSLEY_3
name|TYPE_BARNSLEY_3
block|,
DECL|enumerator|TYPE_SPIDER
name|TYPE_SPIDER
block|,
DECL|enumerator|TYPE_MAN_O_WAR
name|TYPE_MAN_O_WAR
block|,
DECL|enumerator|TYPE_LAMBDA
name|TYPE_LAMBDA
block|,
DECL|enumerator|TYPE_SIERPINSKI
name|TYPE_SIERPINSKI
block|,
DECL|enumerator|NUM_TYPES
name|NUM_TYPES
block|}
enum|;
end_enum

begin_comment
comment|/**********************************************************************  Types    *********************************************************************/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon293456fa0308
block|{
DECL|member|fractaltype
name|gint
name|fractaltype
decl_stmt|;
DECL|member|xmin
name|gdouble
name|xmin
decl_stmt|;
DECL|member|xmax
name|gdouble
name|xmax
decl_stmt|;
DECL|member|ymin
name|gdouble
name|ymin
decl_stmt|;
DECL|member|ymax
name|gdouble
name|ymax
decl_stmt|;
DECL|member|iter
name|gdouble
name|iter
decl_stmt|;
DECL|member|cx
name|gdouble
name|cx
decl_stmt|;
DECL|member|cy
name|gdouble
name|cy
decl_stmt|;
DECL|member|colormode
name|gint
name|colormode
decl_stmt|;
DECL|member|redstretch
name|gdouble
name|redstretch
decl_stmt|;
DECL|member|greenstretch
name|gdouble
name|greenstretch
decl_stmt|;
DECL|member|bluestretch
name|gdouble
name|bluestretch
decl_stmt|;
DECL|member|redmode
name|gint
name|redmode
decl_stmt|;
DECL|member|greenmode
name|gint
name|greenmode
decl_stmt|;
DECL|member|bluemode
name|gint
name|bluemode
decl_stmt|;
DECL|member|redinvert
name|gint
name|redinvert
decl_stmt|;
DECL|member|greeninvert
name|gint
name|greeninvert
decl_stmt|;
DECL|member|blueinvert
name|gint
name|blueinvert
decl_stmt|;
DECL|member|alwayspreview
name|gint
name|alwayspreview
decl_stmt|;
DECL|member|ncolors
name|gint
name|ncolors
decl_stmt|;
DECL|member|useloglog
name|gint
name|useloglog
decl_stmt|;
DECL|typedef|explorer_vals_t
block|}
name|explorer_vals_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon293456fa0408
block|{
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|wimage
name|guchar
modifier|*
name|wimage
decl_stmt|;
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|explorer_interface_t
block|}
name|explorer_interface_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|colorvalue
typedef|typedef
name|gint
name|colorvalue
index|[
literal|3
index|]
typedef|;
end_typedef

begin_typedef
DECL|typedef|clrmap
typedef|typedef
name|colorvalue
name|clrmap
index|[
name|MAXNCOLORS
index|]
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon293456fa0508
block|{
DECL|member|text
name|GtkWidget
modifier|*
name|text
decl_stmt|;
DECL|member|data
name|GtkAdjustment
modifier|*
name|data
decl_stmt|;
DECL|typedef|scaledata
block|}
name|scaledata
typedef|;
end_typedef

begin_typedef
DECL|typedef|DialogElements
typedef|typedef
name|struct
name|_DialogElements
name|DialogElements
typedef|;
end_typedef

begin_struct
DECL|struct|_DialogElements
struct|struct
name|_DialogElements
block|{
DECL|member|type
name|GtkWidget
modifier|*
name|type
index|[
name|NUM_TYPES
index|]
decl_stmt|;
DECL|member|xmin
name|GtkObject
modifier|*
name|xmin
decl_stmt|;
DECL|member|xmax
name|GtkObject
modifier|*
name|xmax
decl_stmt|;
DECL|member|ymin
name|GtkObject
modifier|*
name|ymin
decl_stmt|;
DECL|member|ymax
name|GtkObject
modifier|*
name|ymax
decl_stmt|;
DECL|member|iter
name|GtkObject
modifier|*
name|iter
decl_stmt|;
DECL|member|cx
name|GtkObject
modifier|*
name|cx
decl_stmt|;
DECL|member|cy
name|GtkObject
modifier|*
name|cy
decl_stmt|;
DECL|member|ncol
name|GtkObject
modifier|*
name|ncol
decl_stmt|;
DECL|member|useloglog
name|GtkWidget
modifier|*
name|useloglog
decl_stmt|;
DECL|member|red
name|GtkObject
modifier|*
name|red
decl_stmt|;
DECL|member|green
name|GtkObject
modifier|*
name|green
decl_stmt|;
DECL|member|blue
name|GtkObject
modifier|*
name|blue
decl_stmt|;
DECL|member|redmode
name|GtkWidget
modifier|*
name|redmode
index|[
literal|3
index|]
decl_stmt|;
DECL|member|redinvert
name|GtkWidget
modifier|*
name|redinvert
decl_stmt|;
DECL|member|greenmode
name|GtkWidget
modifier|*
name|greenmode
index|[
literal|3
index|]
decl_stmt|;
DECL|member|greeninvert
name|GtkWidget
modifier|*
name|greeninvert
decl_stmt|;
DECL|member|bluemode
name|GtkWidget
modifier|*
name|bluemode
index|[
literal|3
index|]
decl_stmt|;
DECL|member|blueinvert
name|GtkWidget
modifier|*
name|blueinvert
decl_stmt|;
DECL|member|colormode
name|GtkWidget
modifier|*
name|colormode
index|[
literal|2
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|DFigObj
typedef|typedef
struct|struct
name|DFigObj
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* Trailing name of file  */
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/* Filename itself */
DECL|member|draw_name
name|gchar
modifier|*
name|draw_name
decl_stmt|;
comment|/* Name of the drawing */
DECL|member|opts
name|explorer_vals_t
name|opts
decl_stmt|;
comment|/* Options enforced when fig saved */
DECL|member|list_item
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
DECL|member|label_widget
name|GtkWidget
modifier|*
name|label_widget
decl_stmt|;
DECL|member|pixmap_widget
name|GtkWidget
modifier|*
name|pixmap_widget
decl_stmt|;
DECL|member|obj_status
name|gint
name|obj_status
decl_stmt|;
DECL|typedef|fractalexplorerOBJ
block|}
name|fractalexplorerOBJ
typedef|;
end_typedef

begin_typedef
DECL|struct|GigObj
typedef|typedef
struct|struct
name|GigObj
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* Trailing name of file  */
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/* Filename itself */
DECL|member|draw_name
name|gchar
modifier|*
name|draw_name
decl_stmt|;
comment|/* Name of the drawing */
DECL|member|typus
name|gint
name|typus
decl_stmt|;
DECL|member|list_item
name|GtkWidget
modifier|*
name|list_item
decl_stmt|;
DECL|member|label_widget
name|GtkWidget
modifier|*
name|label_widget
decl_stmt|;
DECL|member|pixmap_widget
name|GtkWidget
modifier|*
name|pixmap_widget
decl_stmt|;
DECL|member|obj_status
name|gint
name|obj_status
decl_stmt|;
DECL|typedef|gradientOBJ
block|}
name|gradientOBJ
typedef|;
end_typedef

begin_typedef
DECL|struct|_fractalexplorerListOptions
typedef|typedef
struct|struct
name|_fractalexplorerListOptions
block|{
DECL|member|query_box
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
DECL|member|name_entry
name|GtkWidget
modifier|*
name|name_entry
decl_stmt|;
DECL|member|list_entry
name|GtkWidget
modifier|*
name|list_entry
decl_stmt|;
DECL|member|obj
name|fractalexplorerOBJ
modifier|*
name|obj
decl_stmt|;
DECL|member|created
name|gint
name|created
decl_stmt|;
DECL|typedef|fractalexplorerListOptions
block|}
name|fractalexplorerListOptions
typedef|;
end_typedef

begin_comment
comment|/* States of the object */
end_comment

begin_define
DECL|macro|fractalexplorer_OK
define|#
directive|define
name|fractalexplorer_OK
value|0x0
end_define

begin_define
DECL|macro|fractalexplorer_MODIFIED
define|#
directive|define
name|fractalexplorer_MODIFIED
value|0x1
end_define

begin_define
DECL|macro|fractalexplorer_READONLY
define|#
directive|define
name|fractalexplorer_READONLY
value|0x2
end_define

begin_define
DECL|macro|gradient_GRADIENTEDITOR
define|#
directive|define
name|gradient_GRADIENTEDITOR
value|0x2
end_define

begin_decl_stmt
specifier|extern
name|fractalexplorerOBJ
modifier|*
name|current_obj
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|fractalexplorerOBJ
modifier|*
name|pic_obj
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|delete_dialog
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|add_objects_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_parse_fractalexplorer_path
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**********************************************************************   Global variables    *********************************************************************/
end_comment

begin_decl_stmt
specifier|extern
name|double
name|xmin
decl_stmt|,
name|xmax
decl_stmt|,
name|ymin
decl_stmt|,
name|ymax
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|xbild
decl_stmt|,
name|ybild
decl_stmt|,
name|xdiff
decl_stmt|,
name|ydiff
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|x_press
decl_stmt|,
name|y_press
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|x_release
decl_stmt|,
name|y_release
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|float
name|cx
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|float
name|cy
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|tile_width
decl_stmt|,
name|tile_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|img_width
decl_stmt|,
name|img_height
decl_stmt|,
name|img_bpp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|sel_x1
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|sel_width
decl_stmt|,
name|sel_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|preview_width
decl_stmt|,
name|preview_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GTile
modifier|*
name|the_tile
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|cen_x
decl_stmt|,
name|cen_y
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|double
name|xpos
decl_stmt|,
name|ypos
decl_stmt|,
name|oldxpos
decl_stmt|,
name|oldypos
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|maindlg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|logodlg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|cmap_preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|delete_frame_to_freeze
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|fractalexplorer_gtk_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|save_menu_item
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|fractalexplorer_op_menu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GdkCursor
modifier|*
name|MyCursor
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ready_now
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|explorer_vals_t
name|zooms
index|[
literal|100
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|DialogElements
modifier|*
name|elements
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|zoomindex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|zoommax
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gdouble
modifier|*
name|gg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|line_no
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
name|clrmap
name|colormap
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GList
modifier|*
name|fractalexplorer_path_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GList
modifier|*
name|fractalexplorer_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GList
modifier|*
name|gradient_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|tpath
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|fractalexplorerOBJ
modifier|*
name|fractalexplorer_obj_for_menu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GList
modifier|*
name|rescan_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|lng
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|explorer_interface_t
name|wint
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|explorer_vals_t
name|wvals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|explorer_vals_t
name|standardvals
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

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

begin_include
include|#
directive|include
file|"rcm_hsv.h"
end_include

begin_include
include|#
directive|include
file|"pmg_gtk_objects.h"
end_include

begin_define
DECL|macro|RCM_XPM_DIR
define|#
directive|define
name|RCM_XPM_DIR
value|"./"
end_define

begin_define
DECL|macro|MAX_PREVIEW_SIZE
define|#
directive|define
name|MAX_PREVIEW_SIZE
value|150
end_define

begin_define
DECL|macro|ALL
define|#
directive|define
name|ALL
value|255
end_define

begin_define
DECL|macro|INITIAL_ALPHA
define|#
directive|define
name|INITIAL_ALPHA
value|0
end_define

begin_define
DECL|macro|INITIAL_BETA
define|#
directive|define
name|INITIAL_BETA
value|(PI/2.0)
end_define

begin_define
DECL|macro|INITIAL_GRAY_SAT
define|#
directive|define
name|INITIAL_GRAY_SAT
value|0.0
end_define

begin_define
DECL|macro|RADIUS
define|#
directive|define
name|RADIUS
value|60
end_define

begin_define
DECL|macro|MARGIN
define|#
directive|define
name|MARGIN
value|4
end_define

begin_define
DECL|macro|SUM
define|#
directive|define
name|SUM
value|(2*RADIUS+2*MARGIN)
end_define

begin_define
DECL|macro|CENTER
define|#
directive|define
name|CENTER
value|(SUM/2)
end_define

begin_define
DECL|macro|TP
define|#
directive|define
name|TP
value|(2*PI)
end_define

begin_define
DECL|macro|GRAY_RADIUS
define|#
directive|define
name|GRAY_RADIUS
value|60
end_define

begin_define
DECL|macro|GRAY_MARGIN
define|#
directive|define
name|GRAY_MARGIN
value|3
end_define

begin_define
DECL|macro|GRAY_SUM
define|#
directive|define
name|GRAY_SUM
value|(2*GRAY_RADIUS+2*GRAY_MARGIN)
end_define

begin_define
DECL|macro|GRAY_CENTER
define|#
directive|define
name|GRAY_CENTER
value|(GRAY_SUM/2)
end_define

begin_define
DECL|macro|LITTLE_RADIUS
define|#
directive|define
name|LITTLE_RADIUS
value|3
end_define

begin_define
DECL|macro|EACH_OR_BOTH
define|#
directive|define
name|EACH_OR_BOTH
value|.3
end_define

begin_define
DECL|macro|sqr (X)
define|#
directive|define
name|sqr
parameter_list|(
name|X
parameter_list|)
value|((X)*(X))
end_define

begin_define
DECL|macro|SWAP (X,Y)
define|#
directive|define
name|SWAP
parameter_list|(
name|X
parameter_list|,
name|Y
parameter_list|)
value|{float t=X; X=Y; Y=t;}
end_define

begin_define
DECL|macro|RANGE_ADJUST_MASK
define|#
directive|define
name|RANGE_ADJUST_MASK
value|GDK_EXPOSURE_MASK | \                           GDK_ENTER_NOTIFY_MASK | \                           GDK_BUTTON_PRESS_MASK | \                           GDK_BUTTON_RELEASE_MASK | \                           GDK_BUTTON1_MOTION_MASK | \                           GDK_POINTER_MOTION_HINT_MASK
end_define

begin_typedef
DECL|struct|__anon28c0aed40108
typedef|typedef
struct|struct
block|{
DECL|member|alpha
name|float
name|alpha
decl_stmt|;
DECL|member|beta
name|float
name|beta
decl_stmt|;
DECL|member|cw_ccw
name|int
name|cw_ccw
decl_stmt|;
DECL|typedef|RcmAngle
block|}
name|RcmAngle
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon28c0aed40203
typedef|typedef
enum|enum
block|{
DECL|enumerator|VIRGIN
name|VIRGIN
block|,
DECL|enumerator|DRAG_START
name|DRAG_START
block|,
DECL|enumerator|DRAGING
name|DRAGING
block|,
DECL|enumerator|DO_NOTHING
name|DO_NOTHING
DECL|typedef|RcmOp
block|}
name|RcmOp
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c0aed40308
typedef|typedef
struct|struct
block|{
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|cw_ccw_xpm_button
name|PmgButtonLabelXpm
modifier|*
name|cw_ccw_xpm_button
decl_stmt|;
DECL|member|alpha_entry
name|GtkWidget
modifier|*
name|alpha_entry
decl_stmt|;
DECL|member|alpha_units_label
name|GtkWidget
modifier|*
name|alpha_units_label
decl_stmt|;
DECL|member|beta_entry
name|GtkWidget
modifier|*
name|beta_entry
decl_stmt|;
DECL|member|beta_units_label
name|GtkWidget
modifier|*
name|beta_units_label
decl_stmt|;
DECL|member|target
name|gfloat
modifier|*
name|target
decl_stmt|;
DECL|member|mode
name|gint
name|mode
decl_stmt|;
DECL|member|angle
name|RcmAngle
modifier|*
name|angle
decl_stmt|;
DECL|member|action_flag
name|RcmOp
name|action_flag
decl_stmt|;
DECL|member|prev_clicked
name|gfloat
name|prev_clicked
decl_stmt|;
DECL|typedef|RcmCircle
block|}
name|RcmCircle
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c0aed40408
typedef|typedef
struct|struct
block|{
DECL|member|dlg
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
DECL|member|bna_frame
name|GtkWidget
modifier|*
name|bna_frame
decl_stmt|;
DECL|member|before
name|GtkWidget
modifier|*
name|before
decl_stmt|;
DECL|member|after
name|GtkWidget
modifier|*
name|after
decl_stmt|;
DECL|typedef|RcmBna
block|}
name|RcmBna
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c0aed40508
typedef|typedef
struct|struct
block|{
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|gray_sat
name|float
name|gray_sat
decl_stmt|;
DECL|member|hue
name|float
name|hue
decl_stmt|;
DECL|member|satur
name|float
name|satur
decl_stmt|;
DECL|member|gray_sat_entry
name|GtkWidget
modifier|*
name|gray_sat_entry
decl_stmt|;
DECL|member|hue_entry
name|GtkWidget
modifier|*
name|hue_entry
decl_stmt|;
DECL|member|hue_units_label
name|GtkWidget
modifier|*
name|hue_units_label
decl_stmt|;
DECL|member|satur_entry
name|GtkWidget
modifier|*
name|satur_entry
decl_stmt|;
DECL|member|action_flag
name|RcmOp
name|action_flag
decl_stmt|;
DECL|typedef|RcmGray
block|}
name|RcmGray
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c0aed40608
typedef|typedef
struct|struct
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|rgb
name|guchar
modifier|*
name|rgb
decl_stmt|;
DECL|member|hsv
name|hsv
modifier|*
name|hsv
decl_stmt|;
DECL|member|mask
name|guchar
modifier|*
name|mask
decl_stmt|;
DECL|typedef|ReducedImage
block|}
name|ReducedImage
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c0aed40708
typedef|typedef
struct|struct
block|{
DECL|member|Slctn
name|gint
name|Slctn
decl_stmt|;
DECL|member|RealTime
name|gint
name|RealTime
decl_stmt|;
DECL|member|Success
name|gint
name|Success
decl_stmt|;
DECL|member|Units
name|gint
name|Units
decl_stmt|;
DECL|member|Gray_to_from
name|gint
name|Gray_to_from
decl_stmt|;
DECL|member|drawable
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|mask
name|GDrawable
modifier|*
name|mask
decl_stmt|;
DECL|member|reduced
name|ReducedImage
modifier|*
name|reduced
decl_stmt|;
DECL|member|To
name|RcmCircle
modifier|*
name|To
decl_stmt|;
DECL|member|From
name|RcmCircle
modifier|*
name|From
decl_stmt|;
DECL|member|Gray
name|RcmGray
modifier|*
name|Gray
decl_stmt|;
DECL|member|Bna
name|RcmBna
modifier|*
name|Bna
decl_stmt|;
DECL|typedef|RcmParams
block|}
name|RcmParams
typedef|;
end_typedef

begin_enum
DECL|enum|__anon28c0aed40803
enum|enum
block|{
DECL|enumerator|ENTIRE_IMAGE
name|ENTIRE_IMAGE
block|,
DECL|enumerator|SELECTION
name|SELECTION
block|,
DECL|enumerator|SELECTION_IN_CONTEXT
name|SELECTION_IN_CONTEXT
block|,
DECL|enumerator|PREVIEW_OPTIONS
name|PREVIEW_OPTIONS
block|}
enum|;
end_enum

begin_enum
DECL|enum|__anon28c0aed40903
enum|enum
block|{
DECL|enumerator|EACH
name|EACH
block|,
DECL|enumerator|BOTH
name|BOTH
block|,
DECL|enumerator|DEGREES
name|DEGREES
block|,
DECL|enumerator|RADIANS
name|RADIANS
block|,
DECL|enumerator|RADIANS_OVER_PI
name|RADIANS_OVER_PI
block|,
DECL|enumerator|GRAY_FROM
name|GRAY_FROM
block|,
DECL|enumerator|GRAY_TO
name|GRAY_TO
block|,
DECL|enumerator|CURRENT
name|CURRENT
block|,
DECL|enumerator|ORIGINAL
name|ORIGINAL
block|}
enum|;
end_enum

begin_function_decl
name|gint
name|rcm_dialog
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|rcm_create_bna
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|rcm_create_from_to
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|arctg
parameter_list|(
name|float
name|y
parameter_list|,
name|float
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|min_prox
parameter_list|(
name|float
name|alpha
parameter_list|,
name|float
name|beta
parameter_list|,
name|float
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
modifier|*
name|closest
parameter_list|(
name|float
modifier|*
name|alpha
parameter_list|,
name|float
modifier|*
name|beta
parameter_list|,
name|float
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|beta_from_alpha_and_delta
parameter_list|(
name|float
name|alpha
parameter_list|,
name|float
name|delta
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|angle_mod_2PI
parameter_list|(
name|float
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|angle_inside_slice
parameter_list|(
name|float
name|angle
parameter_list|,
name|RcmAngle
modifier|*
name|slice
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_draw_arrows
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|color
parameter_list|,
name|RcmAngle
modifier|*
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_motion_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/***************** GRAY ***********************/
end_comment

begin_function_decl
name|void
name|rcm_draw_little_circle
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|color
parameter_list|,
name|float
name|hue
parameter_list|,
name|float
name|satur
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_draw_large_circle
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|color
parameter_list|,
name|float
name|gray_sat
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_gray_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_gray_button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_gray_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_gray_motion_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|RcmGray
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/***************** END GRAY ***********************/
end_comment

begin_function_decl
name|float
name|rcm_units_factor
parameter_list|(
name|gint
name|units
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|rcm_units_string
parameter_list|(
name|gint
name|units
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_alpha
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_beta
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_hue
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_satur
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_set_gray_sat
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_show_hide_frame
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|GtkWidget
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|RcmCircle
modifier|*
name|rcm_create_square_preview
parameter_list|(
name|gint
parameter_list|,
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ReducedImage
modifier|*
name|Reduce_The_Image
parameter_list|(
name|GDrawable
modifier|*
parameter_list|,
name|GDrawable
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|rcm_widget_in_a_table
parameter_list|(
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|guchar
modifier|*
name|string
parameter_list|,
name|gint
name|x_spot
parameter_list|,
name|gint
name|y_spot
parameter_list|,
name|GtkSignalFunc
modifier|*
name|function
parameter_list|,
name|gpointer
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|rcm_label_in_a_table
parameter_list|(
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|guchar
modifier|*
name|string
parameter_list|,
name|int
name|x_spot
parameter_list|,
name|int
name|y_spot
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|rcm_entry_in_a_table
parameter_list|(
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|float
name|value
parameter_list|,
name|gint
name|x_spot
parameter_list|,
name|gint
name|y_spot
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_render_preview
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_render_circle_preview
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|int
name|sum
parameter_list|,
name|int
name|margin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_preview_what
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_cw_ccw
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|RcmCircle
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_a_to_b
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|RcmCircle
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_360_degrees
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|RcmCircle
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_close_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Create_A_Preview
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
parameter_list|,
name|GtkWidget
modifier|*
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Create_A_Table_Entry
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
parameter_list|,
name|GtkWidget
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GSList
modifier|*
name|Button_In_A_Box
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GSList
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|GtkSignalFunc
parameter_list|,
name|gpointer
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Check_Button_In_A_Box
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|guchar
modifier|*
name|label
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|int
name|clicked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src_row
parameter_list|,
name|guchar
modifier|*
name|dest_row
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|row_width
parameter_list|,
name|gint
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|As_You_Drag
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preview_size_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|float
modifier|*
name|scale_val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ErrorMessage
parameter_list|(
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_advanced_ok
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_fake_transparency
parameter_list|(
name|gint
name|i
parameter_list|,
name|gint
name|j
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_float_angle_in_an_entry
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|float
name|value
parameter_list|,
name|gint
name|units
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_float_in_an_entry
parameter_list|(
name|GtkWidget
modifier|*
name|entry
parameter_list|,
name|float
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|rcm_update_entries
parameter_list|(
name|gint
name|units
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|rcm_unit_factor
parameter_list|(
name|gint
name|units
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_is_gray
parameter_list|(
name|float
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|rcm_linear
parameter_list|(
name|float
parameter_list|,
name|float
parameter_list|,
name|float
parameter_list|,
name|float
parameter_list|,
name|float
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|rcm_left_end
parameter_list|(
name|RcmAngle
modifier|*
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|rcm_right_end
parameter_list|(
name|RcmAngle
modifier|*
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|rcm_xpm_label_box
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gchar
modifier|*
name|xpm_filename
parameter_list|,
name|gchar
modifier|*
name|label_text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|rcm_fake_transparency
parameter_list|(
name|gint
name|i
parameter_list|,
name|gint
name|j
parameter_list|)
function_decl|;
end_function_decl

end_unit


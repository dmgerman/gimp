begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_define
DECL|macro|MAX_PREVIEW_SIZE
define|#
directive|define
name|MAX_PREVIEW_SIZE
value|125
end_define

begin_define
DECL|macro|MAX_ROUGHNESS
define|#
directive|define
name|MAX_ROUGHNESS
value|128
end_define

begin_define
DECL|macro|RANGE_HEIGHT
define|#
directive|define
name|RANGE_HEIGHT
value|15
end_define

begin_define
DECL|macro|PR_BX_BRDR
define|#
directive|define
name|PR_BX_BRDR
value|4
end_define

begin_define
DECL|macro|ALL
define|#
directive|define
name|ALL
value|255
end_define

begin_define
DECL|macro|MARGIN
define|#
directive|define
name|MARGIN
value|4
end_define

begin_define
DECL|macro|RANGE_ADJUST_MASK
define|#
directive|define
name|RANGE_ADJUST_MASK
value|GDK_EXPOSURE_MASK | \                         GDK_ENTER_NOTIFY_MASK | \                         GDK_BUTTON_PRESS_MASK | \                         GDK_BUTTON_RELEASE_MASK | \                         GDK_BUTTON1_MOTION_MASK | \                         GDK_POINTER_MOTION_HINT_MASK
end_define

begin_typedef
DECL|struct|__anon29b5cb1d0108
typedef|typedef
struct|struct
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|fpInterface
block|}
name|fpInterface
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29b5cb1d0208
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
name|gdouble
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
DECL|enum|__anon29b5cb1d0303
typedef|typedef
enum|enum
block|{
DECL|enumerator|SHADOWS
name|SHADOWS
block|,
DECL|enumerator|MIDTONES
name|MIDTONES
block|,
DECL|enumerator|HIGHLIGHTS
name|HIGHLIGHTS
block|,
DECL|enumerator|INTENSITIES
name|INTENSITIES
DECL|typedef|FP_Intensity
block|}
name|FP_Intensity
typedef|;
end_typedef

begin_enum
DECL|enum|__anon29b5cb1d0403
enum|enum
block|{
DECL|enumerator|NONEATALL
name|NONEATALL
init|=
literal|0
block|,
DECL|enumerator|CURRENT
name|CURRENT
init|=
literal|1
block|,
DECL|enumerator|HUE
name|HUE
init|=
literal|2
block|,
DECL|enumerator|SATURATION
name|SATURATION
init|=
literal|4
block|,
DECL|enumerator|VALUE
name|VALUE
init|=
literal|8
block|}
enum|;
end_enum

begin_enum
DECL|enum|__anon29b5cb1d0503
enum|enum
block|{
DECL|enumerator|RED
name|RED
block|,
DECL|enumerator|GREEN
name|GREEN
block|,
DECL|enumerator|BLUE
name|BLUE
block|,
DECL|enumerator|CYAN
name|CYAN
block|,
DECL|enumerator|YELLOW
name|YELLOW
block|,
DECL|enumerator|MAGENTA
name|MAGENTA
block|,
DECL|enumerator|ALL_PRIMARY
name|ALL_PRIMARY
block|}
enum|;
end_enum

begin_enum
DECL|enum|__anon29b5cb1d0603
enum|enum
block|{
DECL|enumerator|DOWN
name|DOWN
init|=
operator|-
literal|1
block|,
DECL|enumerator|UP
name|UP
init|=
literal|1
block|}
enum|;
end_enum

begin_enum
DECL|enum|__anon29b5cb1d0703
enum|enum
block|{
DECL|enumerator|BY_HUE
name|BY_HUE
block|,
DECL|enumerator|BY_SAT
name|BY_SAT
block|,
DECL|enumerator|BY_VAL
name|BY_VAL
block|,
DECL|enumerator|JUDGE_BY
name|JUDGE_BY
block|}
enum|;
end_enum

begin_typedef
DECL|struct|__anon29b5cb1d0808
typedef|typedef
struct|struct
block|{
DECL|member|window
name|GtkWidget
modifier|*
name|window
decl_stmt|;
DECL|member|shadowsEntry
name|GtkWidget
modifier|*
name|shadowsEntry
decl_stmt|;
DECL|member|midtonesEntry
name|GtkWidget
modifier|*
name|midtonesEntry
decl_stmt|;
DECL|member|rangePreview
name|GtkWidget
modifier|*
name|rangePreview
decl_stmt|;
DECL|member|aliasingPreview
name|GtkWidget
modifier|*
name|aliasingPreview
decl_stmt|;
DECL|member|aliasingData
name|GtkObject
modifier|*
name|aliasingData
decl_stmt|;
DECL|member|aliasingGraph
name|GtkWidget
modifier|*
name|aliasingGraph
decl_stmt|;
DECL|typedef|AdvancedWindow
block|}
name|AdvancedWindow
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29b5cb1d0908
typedef|typedef
struct|struct
block|{
DECL|member|Color
name|int
name|Color
decl_stmt|;
DECL|member|Rough
name|float
name|Rough
decl_stmt|;
DECL|member|roughnessScale
name|GtkWidget
modifier|*
name|roughnessScale
decl_stmt|;
DECL|member|Alias
name|float
name|Alias
decl_stmt|;
DECL|member|aliasingScale
name|GtkWidget
modifier|*
name|aliasingScale
decl_stmt|;
DECL|member|PreviewSize
name|float
name|PreviewSize
decl_stmt|;
DECL|member|previewSizeScale
name|GtkWidget
modifier|*
name|previewSizeScale
decl_stmt|;
DECL|member|Range
name|FP_Intensity
name|Range
decl_stmt|;
DECL|member|ValueBy
name|gint
name|ValueBy
decl_stmt|;
DECL|member|SlctnOnly
name|gint
name|SlctnOnly
decl_stmt|;
DECL|member|RealTime
name|gint
name|RealTime
decl_stmt|;
DECL|member|Offset
name|guchar
name|Offset
decl_stmt|;
DECL|member|VisibleFrames
name|guchar
name|VisibleFrames
decl_stmt|;
DECL|member|Cutoffs
name|guchar
name|Cutoffs
index|[
name|INTENSITIES
index|]
decl_stmt|;
DECL|member|Touched
name|gint
name|Touched
index|[
name|JUDGE_BY
index|]
decl_stmt|;
DECL|member|redAdj
name|gint
name|redAdj
index|[
name|JUDGE_BY
index|]
index|[
literal|256
index|]
decl_stmt|;
DECL|member|blueAdj
name|gint
name|blueAdj
index|[
name|JUDGE_BY
index|]
index|[
literal|256
index|]
decl_stmt|;
DECL|member|greenAdj
name|gint
name|greenAdj
index|[
name|JUDGE_BY
index|]
index|[
literal|256
index|]
decl_stmt|;
DECL|member|satAdj
name|gint
name|satAdj
index|[
name|JUDGE_BY
index|]
index|[
literal|256
index|]
decl_stmt|;
DECL|member|rangeLabels
name|GtkWidget
modifier|*
name|rangeLabels
index|[
literal|12
index|]
decl_stmt|;
DECL|typedef|FP_Params
block|}
name|FP_Params
typedef|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_bna
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_rough
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_range
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_circle_palette
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_lnd
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_show
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_msnls
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_frame_select
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|fp_create_pixels_select_by
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_show_hide_frame
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
name|ReducedImage
modifier|*
name|Reduce_The_Image
parameter_list|(
name|GimpDrawable
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_render_preview
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Update_Current_FP
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_Create_Nudge
parameter_list|(
name|gint
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|fp_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_advanced_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_advanced_call
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_entire_image
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
name|fp_selection_only
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
name|fp_selection_in_context
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
name|selectionMade
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
name|fp_close_callback
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
name|fp_ok_callback
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
name|fp_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
parameter_list|,
name|float
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_change_current_range
parameter_list|(
name|GtkAdjustment
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_change_current_pixels_by
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|resetFilterPacks
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|update_range_labels
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_create_smoothness_graph
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_range_preview_spill
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
specifier|const
name|gchar
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
specifier|const
name|gchar
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
specifier|const
name|gchar
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
name|Frames_Check_Button_In_A_Box
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|GtkWidget
modifier|*
name|frame
parameter_list|,
name|int
name|clicked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Adjust_Preview_Sizes
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|refreshPreviews
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|initializeFilterPacks
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fp_row
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
name|draw_slider
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|border_gc
parameter_list|,
name|GdkGC
modifier|*
name|fill_gc
parameter_list|,
name|int
name|xpos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|FP_Range_Change_Events
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|,
name|FP_Params
modifier|*
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
name|fp_advanced_ok
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|fp_fake_transparency
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


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
file|<math.h>
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
file|"fp.h"
end_include

begin_include
include|#
directive|include
file|"fp_hsv.h"
end_include

begin_decl_stmt
specifier|extern
name|AdvancedWindow
name|AW
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|FP_Params
name|Current
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|nudgeArray
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|slider_erase (GdkWindow * window,int xpos)
name|slider_erase
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|int
name|xpos
parameter_list|)
block|{
name|gdk_window_clear_area
argument_list|(
name|window
argument_list|,
name|MARGIN
operator|+
name|xpos
operator|-
operator|(
name|RANGE_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
literal|0
argument_list|,
name|RANGE_HEIGHT
argument_list|,
name|RANGE_HEIGHT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|draw_slider (GdkWindow * window,GdkGC * border_gc,GdkGC * fill_gc,int xpos)
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
block|{
name|int
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|RANGE_HEIGHT
condition|;
name|i
operator|++
control|)
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|fill_gc
argument_list|,
name|MARGIN
operator|+
name|xpos
operator|-
name|i
operator|/
literal|2
argument_list|,
name|i
argument_list|,
name|MARGIN
operator|+
name|xpos
operator|+
name|i
operator|/
literal|2
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|border_gc
argument_list|,
name|MARGIN
operator|+
name|xpos
argument_list|,
literal|0
argument_list|,
name|MARGIN
operator|+
name|xpos
operator|-
operator|(
name|RANGE_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|RANGE_HEIGHT
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|border_gc
argument_list|,
name|MARGIN
operator|+
name|xpos
argument_list|,
literal|0
argument_list|,
name|MARGIN
operator|+
name|xpos
operator|+
operator|(
name|RANGE_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|RANGE_HEIGHT
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|window
argument_list|,
name|border_gc
argument_list|,
name|MARGIN
operator|+
name|xpos
operator|-
operator|(
name|RANGE_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|RANGE_HEIGHT
operator|-
literal|1
argument_list|,
name|MARGIN
operator|+
name|xpos
operator|+
operator|(
name|RANGE_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|RANGE_HEIGHT
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|draw_it (GtkWidget * widget)
name|draw_it
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|draw_slider
argument_list|(
name|AW
operator|.
name|aliasingGraph
operator|->
name|window
argument_list|,
name|AW
operator|.
name|aliasingGraph
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|AW
operator|.
name|aliasingGraph
operator|->
name|style
operator|->
name|dark_gc
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|Current
operator|.
name|Cutoffs
index|[
name|SHADOWS
index|]
argument_list|)
expr_stmt|;
name|draw_slider
argument_list|(
name|AW
operator|.
name|aliasingGraph
operator|->
name|window
argument_list|,
name|AW
operator|.
name|aliasingGraph
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|AW
operator|.
name|aliasingGraph
operator|->
name|style
operator|->
name|dark_gc
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|Current
operator|.
name|Cutoffs
index|[
name|MIDTONES
index|]
argument_list|)
expr_stmt|;
name|draw_slider
argument_list|(
name|AW
operator|.
name|aliasingGraph
operator|->
name|window
argument_list|,
name|AW
operator|.
name|aliasingGraph
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|AW
operator|.
name|aliasingGraph
operator|->
name|style
operator|->
name|dark_gc
index|[
name|GTK_STATE_SELECTED
index|]
argument_list|,
name|Current
operator|.
name|Offset
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|FP_Range_Change_Events (GtkWidget * widget,GdkEvent * event,FP_Params * current)
name|FP_Range_Change_Events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|FP_Params
modifier|*
name|current
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|GdkEventMotion
modifier|*
name|mevent
decl_stmt|;
name|gint
name|shad
decl_stmt|,
name|mid
decl_stmt|,
name|offset
decl_stmt|,
name|min
decl_stmt|;
specifier|static
name|guchar
modifier|*
name|new
decl_stmt|;
name|gint
name|x
decl_stmt|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_EXPOSE
case|:
name|draw_it
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_BUTTON_PRESS
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
name|shad
operator|=
name|abs
argument_list|(
name|bevent
operator|->
name|x
operator|-
name|Current
operator|.
name|Cutoffs
index|[
name|SHADOWS
index|]
argument_list|)
expr_stmt|;
name|mid
operator|=
name|abs
argument_list|(
name|bevent
operator|->
name|x
operator|-
name|Current
operator|.
name|Cutoffs
index|[
name|MIDTONES
index|]
argument_list|)
expr_stmt|;
name|offset
operator|=
name|abs
argument_list|(
name|bevent
operator|->
name|x
operator|-
name|Current
operator|.
name|Offset
argument_list|)
expr_stmt|;
name|min
operator|=
name|MIN
argument_list|(
name|MIN
argument_list|(
name|shad
argument_list|,
name|mid
argument_list|)
argument_list|,
name|offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|x
operator|>
literal|0
operator|&&
name|bevent
operator|->
name|x
operator|<
literal|256
condition|)
block|{
if|if
condition|(
name|min
operator|==
name|shad
condition|)
name|new
operator|=
operator|&
name|Current
operator|.
name|Cutoffs
index|[
name|SHADOWS
index|]
expr_stmt|;
elseif|else
if|if
condition|(
name|min
operator|==
name|mid
condition|)
name|new
operator|=
operator|&
name|Current
operator|.
name|Cutoffs
index|[
name|MIDTONES
index|]
expr_stmt|;
else|else
name|new
operator|=
operator|&
name|Current
operator|.
name|Offset
expr_stmt|;
name|slider_erase
argument_list|(
name|AW
operator|.
name|aliasingGraph
operator|->
name|window
argument_list|,
operator|*
name|new
argument_list|)
expr_stmt|;
operator|*
name|new
operator|=
name|bevent
operator|->
name|x
expr_stmt|;
block|}
name|draw_it
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|Current
operator|.
name|RealTime
condition|)
block|{
name|fp_range_preview_spill
argument_list|(
name|AW
operator|.
name|rangePreview
argument_list|,
name|Current
operator|.
name|ValueBy
argument_list|)
expr_stmt|;
name|update_range_labels
argument_list|()
expr_stmt|;
name|fp_create_smoothness_graph
argument_list|(
name|AW
operator|.
name|aliasingPreview
argument_list|)
expr_stmt|;
name|refreshPreviews
argument_list|(
name|Current
operator|.
name|VisibleFrames
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
if|if
condition|(
operator|!
name|Current
operator|.
name|RealTime
condition|)
block|{
name|fp_range_preview_spill
argument_list|(
name|AW
operator|.
name|rangePreview
argument_list|,
name|Current
operator|.
name|ValueBy
argument_list|)
expr_stmt|;
name|update_range_labels
argument_list|()
expr_stmt|;
name|fp_create_smoothness_graph
argument_list|(
name|AW
operator|.
name|aliasingPreview
argument_list|)
expr_stmt|;
name|refreshPreviews
argument_list|(
name|Current
operator|.
name|VisibleFrames
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_MOTION_NOTIFY
case|:
name|mevent
operator|=
operator|(
name|GdkEventMotion
operator|*
operator|)
name|event
expr_stmt|;
name|gdk_window_get_pointer
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|x
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|>=
literal|0
operator|&&
name|x
operator|<
literal|256
condition|)
block|{
name|slider_erase
argument_list|(
name|AW
operator|.
name|aliasingGraph
operator|->
name|window
argument_list|,
operator|*
name|new
argument_list|)
expr_stmt|;
operator|*
name|new
operator|=
name|x
expr_stmt|;
name|draw_it
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|Current
operator|.
name|RealTime
condition|)
block|{
name|fp_range_preview_spill
argument_list|(
name|AW
operator|.
name|rangePreview
argument_list|,
name|Current
operator|.
name|ValueBy
argument_list|)
expr_stmt|;
name|update_range_labels
argument_list|()
expr_stmt|;
name|fp_create_smoothness_graph
argument_list|(
name|AW
operator|.
name|aliasingPreview
argument_list|)
expr_stmt|;
name|refreshPreviews
argument_list|(
name|Current
operator|.
name|VisibleFrames
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
default|default:
break|break;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|update_range_labels ()
name|update_range_labels
parameter_list|()
block|{
name|guchar
name|buffer
index|[
literal|3
index|]
decl_stmt|;
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|Current
operator|.
name|rangeLabels
index|[
literal|1
index|]
argument_list|)
argument_list|,
literal|"0"
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"%d"
argument_list|,
name|Current
operator|.
name|Cutoffs
index|[
name|SHADOWS
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|Current
operator|.
name|rangeLabels
index|[
literal|3
index|]
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|Current
operator|.
name|rangeLabels
index|[
literal|5
index|]
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"%d"
argument_list|,
name|Current
operator|.
name|Cutoffs
index|[
name|MIDTONES
index|]
argument_list|)
expr_stmt|;
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|Current
operator|.
name|rangeLabels
index|[
literal|7
index|]
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|Current
operator|.
name|rangeLabels
index|[
literal|9
index|]
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gtk_label_set
argument_list|(
name|GTK_LABEL
argument_list|(
name|Current
operator|.
name|rangeLabels
index|[
literal|11
index|]
argument_list|)
argument_list|,
literal|"255"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the Free  * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gint32
DECL|function|gimp_channel_new (gint32 image_ID,char * name,guint width,guint height,gdouble opacity,guchar * color)
name|gimp_channel_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|char
modifier|*
name|name
parameter_list|,
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|guchar
modifier|*
name|color
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gint32
name|channel_ID
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|width
argument_list|,
name|PARAM_INT32
argument_list|,
name|height
argument_list|,
name|PARAM_STRING
argument_list|,
name|name
argument_list|,
name|PARAM_FLOAT
argument_list|,
name|opacity
argument_list|,
name|PARAM_COLOR
argument_list|,
name|color
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|channel_ID
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|channel_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_channel
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|channel_ID
return|;
block|}
end_function

begin_function
name|gint32
DECL|function|gimp_channel_copy (gint32 channel_ID)
name|gimp_channel_copy
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_copy"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|channel_ID
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|channel_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_channel
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|channel_ID
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_delete (gint32 channel_ID)
name|gimp_channel_delete
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_delete"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_channel_width (gint32 channel_ID)
name|gimp_channel_width
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
return|return
name|gimp_drawable_width
argument_list|(
name|channel_ID
argument_list|)
return|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_channel_height (gint32 channel_ID)
name|gimp_channel_height
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
return|return
name|gimp_drawable_height
argument_list|(
name|channel_ID
argument_list|)
return|;
block|}
end_function

begin_function
name|gint32
DECL|function|gimp_channel_get_image_id (gint32 channel_ID)
name|gimp_channel_get_image_id
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
return|return
name|gimp_drawable_image_id
argument_list|(
name|channel_ID
argument_list|)
return|;
block|}
end_function

begin_function
name|gint32
DECL|function|gimp_channel_get_layer_id (gint32 channel_ID)
name|gimp_channel_get_layer_id
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_get_color (gint32 channel_ID,guchar * red,guchar * green,guchar * blue)
name|gimp_channel_get_color
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|guchar
modifier|*
name|red
parameter_list|,
name|guchar
modifier|*
name|green
parameter_list|,
name|guchar
modifier|*
name|blue
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_get_color"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
operator|*
name|red
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|red
expr_stmt|;
operator|*
name|green
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|green
expr_stmt|;
operator|*
name|blue
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|blue
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|char
modifier|*
DECL|function|gimp_channel_get_name (gint32 channel_ID)
name|gimp_channel_get_name
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|char
modifier|*
name|name
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_get_name"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|name
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_channel_get_opacity (gint32 channel_ID)
name|gimp_channel_get_opacity
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_get_opacity"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|opacity
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|opacity
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|opacity
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_channel_get_visible (gint32 channel_ID)
name|gimp_channel_get_visible
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|visible
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_get_visible"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|visible
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|visible
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|visible
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_set_color (gint32 channel_ID,guchar red,guchar green,guchar blue)
name|gimp_channel_set_color
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|guchar
name|color
index|[
literal|3
index|]
decl_stmt|;
name|color
index|[
literal|0
index|]
operator|=
name|red
expr_stmt|;
name|color
index|[
literal|1
index|]
operator|=
name|green
expr_stmt|;
name|color
index|[
literal|2
index|]
operator|=
name|blue
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_set_color"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_COLOR
argument_list|,
name|color
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_set_name (gint32 channel_ID,char * name)
name|gimp_channel_set_name
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|char
modifier|*
name|name
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_set_name"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_STRING
argument_list|,
name|name
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_set_opacity (gint32 channel_ID,gdouble opacity)
name|gimp_channel_set_opacity
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_set_opacity"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_FLOAT
argument_list|,
name|opacity
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_channel_set_visible (gint32 channel_ID,gint visible)
name|gimp_channel_set_visible
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|gint
name|visible
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_set_visible"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|channel_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|visible
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


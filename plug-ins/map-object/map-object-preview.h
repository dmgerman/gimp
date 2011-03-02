begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__MAPOBJECT_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__MAPOBJECT_PREVIEW_H__
define|#
directive|define
name|__MAPOBJECT_PREVIEW_H__
end_define

begin_define
DECL|macro|PREVIEW_WIDTH
define|#
directive|define
name|PREVIEW_WIDTH
value|200
end_define

begin_define
DECL|macro|PREVIEW_HEIGHT
define|#
directive|define
name|PREVIEW_HEIGHT
value|200
end_define

begin_define
DECL|macro|WIRESIZE
define|#
directive|define
name|WIRESIZE
value|16
end_define

begin_comment
comment|/* Externally visible variables */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_decl_stmt
specifier|extern
name|gdouble
name|mat
index|[
literal|3
index|]
index|[
literal|4
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|lightx
decl_stmt|,
name|lighty
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Externally visible functions */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_function_decl
name|void
name|compute_preview_image
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|preview_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|check_light_hit
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|update_light
parameter_list|(
name|gint
name|xpos
parameter_list|,
name|gint
name|ypos
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAPOBJECT_PREVIEW_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__DIALOG_F_H__
end_ifndef

begin_define
DECL|macro|__DIALOG_F_H__
define|#
directive|define
name|__DIALOG_F_H__
end_define

begin_define
DECL|macro|MAX_ENTRY_LENGTH
define|#
directive|define
name|MAX_ENTRY_LENGTH
value|5
end_define

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|40
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|100
end_define

begin_define
DECL|macro|ENTRY_PRECISION
define|#
directive|define
name|ENTRY_PRECISION
value|1
end_define

begin_function_decl
name|void
name|dialog_create_value_f
parameter_list|(
name|char
modifier|*
name|title
parameter_list|,
name|GtkTable
modifier|*
name|table
parameter_list|,
name|int
name|row
parameter_list|,
name|gdouble
modifier|*
name|value
parameter_list|,
name|gdouble
name|increment
parameter_list|,
name|int
name|precision
parameter_list|,
name|int
name|left
parameter_list|,
name|int
name|right
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialog_fscale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gdouble
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialog_fentry_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DIALOG_F_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__PRESETS_H
end_ifndef

begin_define
DECL|macro|__PRESETS_H
define|#
directive|define
name|__PRESETS_H
end_define

begin_enum
DECL|enum|SELECT_PRESET_RETURN_VALUES
enum|enum
name|SELECT_PRESET_RETURN_VALUES
block|{
DECL|enumerator|SELECT_PRESET_OK
name|SELECT_PRESET_OK
init|=
literal|0
block|,
DECL|enumerator|SELECT_PRESET_FILE_NOT_FOUND
name|SELECT_PRESET_FILE_NOT_FOUND
init|=
operator|-
literal|1
block|,
DECL|enumerator|SELECT_PRESET_LOAD_FAILED
name|SELECT_PRESET_LOAD_FAILED
init|=
operator|-
literal|2
block|, }
enum|;
end_enum

begin_function_decl
name|void
name|create_presetpage
parameter_list|(
name|GtkNotebook
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|select_preset
parameter_list|(
specifier|const
name|gchar
modifier|*
name|preset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preset_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preset_save_button_set_sensitive
parameter_list|(
name|gboolean
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__ORIENTMAP_H
end_ifndef

begin_define
DECL|macro|__ORIENTMAP_H
define|#
directive|define
name|__ORIENTMAP_H
end_define

begin_function_decl
name|void
name|create_orientmap_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|update_orientmap_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|orientation_map_free_resources
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit


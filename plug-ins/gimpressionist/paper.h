begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__PAPER_H
end_ifndef

begin_define
DECL|macro|__PAPER_H
define|#
directive|define
name|__PAPER_H
end_define

begin_function_decl
name|void
name|create_paperpage
parameter_list|(
name|GtkNotebook
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paper_store
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paper_restore
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


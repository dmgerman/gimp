begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__MAPOBJECT_APPLY_H__
end_ifndef

begin_define
DECL|macro|__MAPOBJECT_APPLY_H__
define|#
directive|define
name|__MAPOBJECT_APPLY_H__
end_define

begin_decl_stmt
specifier|extern
name|gdouble
name|imat
index|[
literal|4
index|]
index|[
literal|4
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gfloat
name|rotmat
index|[
literal|16
index|]
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|init_compute
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|compute_image
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAPOBJECT_APPLY_H__ */
end_comment

end_unit


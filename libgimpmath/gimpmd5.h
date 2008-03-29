begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  *  * gimpmd5.h  *  * Use of this code is deprecated! Use %GChecksum from GLib instead.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MD5_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MD5_H__
define|#
directive|define
name|__GIMP_MD5_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
name|void
name|gimp_md5_get_digest
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|buffer_size
parameter_list|,
name|guchar
name|digest
index|[
literal|16
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MD5_H__ */
end_comment

end_unit


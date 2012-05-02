begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  *  * gimpmd5.h  *  * Use of this code is deprecated! Use %GChecksum from GLib instead.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_MATH_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_MATH_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpmath/gimpmath.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|GIMP_DEPRECATED_FOR
argument_list|(
name|GChecksum
argument_list|)
name|void
name|gimp_md5_get_digest
argument_list|(
specifier|const
name|gchar
operator|*
name|buffer
argument_list|,
name|gint
name|buffer_size
argument_list|,
name|guchar
name|digest
index|[
literal|16
index|]
argument_list|)
decl_stmt|;
end_decl_stmt

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


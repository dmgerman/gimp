begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  *  * gimpmd5.c  *  * Use of this code is deprecated! Use %GChecksum from GLib instead.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpmd5.h"
end_include

begin_comment
comment|/**  * SECTION: gimpmd5  * @title: GimpMD5  * @short_description: The MD5 message-digest algorithm  *  * The MD5 message-digest algorithm  **/
end_comment

begin_comment
comment|/**  * gimp_md5_get_digest:  * @buffer:      byte buffer  * @buffer_size: buffer size (in bytes) or -1 if @buffer is nul-terminated.  * @digest:      16 bytes buffer receiving the hash code.  *  * This function is deprecated! Use %GChecksum from GLib instead.  *  * Get the md5 hash of a buffer. The result is put in the 16 bytes  * buffer @digest. For more information see RFC 1321.  **/
end_comment

begin_function
name|void
DECL|function|gimp_md5_get_digest (const gchar * buffer,gint buffer_size,guchar digest[16])
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
block|{
name|GChecksum
modifier|*
name|checksum
decl_stmt|;
name|gsize
name|len
init|=
literal|16
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|buffer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|digest
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|checksum
operator|=
name|g_checksum_new
argument_list|(
name|G_CHECKSUM_MD5
argument_list|)
expr_stmt|;
name|g_checksum_update
argument_list|(
name|checksum
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|buffer
argument_list|,
name|buffer_size
argument_list|)
expr_stmt|;
name|g_checksum_get_digest
argument_list|(
name|checksum
argument_list|,
name|digest
argument_list|,
operator|&
name|len
argument_list|)
expr_stmt|;
name|g_checksum_free
argument_list|(
name|checksum
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


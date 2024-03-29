begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* jpeg-icc.h  *  * This code was originally proposed for the Independent JPEG Group's  * software, but that fell through, and only recently got merged into  * libjpeg-turbo. This code comes with the following copyright notice:  *  * Copyright (C) 1997-1998, Thomas G. Lane, Todd Newman.  *  * For conditions of distribution and use, see the accompanying  * COPYING.ijg file.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__JPEG_ICC_H__
end_ifndef

begin_define
DECL|macro|__JPEG_ICC_H__
define|#
directive|define
name|__JPEG_ICC_H__
end_define

begin_function_decl
name|void
name|jpeg_icc_write_profile
parameter_list|(
name|j_compress_ptr
name|cinfo
parameter_list|,
specifier|const
name|guchar
modifier|*
name|icc_data_ptr
parameter_list|,
name|guint
name|icc_data_len
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Reading a JPEG file that may contain an ICC profile requires two steps:  *  * 1. After jpeg_create_decompress() but before jpeg_read_header(),  *    ask the IJG library to save in memory any APP2 markers it may find  *    in the file.  *  * 2. After jpeg_read_header(), call jpeg_icc_read_profile() to find  *    out whether there was a profile and obtain it if so.  *  * See if there was an ICC profile in the JPEG file being read;  * if so, reassemble and return the profile data.  *  * TRUE is returned if an ICC profile was found, FALSE if not.  * If TRUE is returned, *icc_data_ptr is set to point to the  * returned data, and *icc_data_len is set to its length.  *  * IMPORTANT: the data at **icc_data_ptr has been allocated with malloc()  * and must be freed by the caller with free() when the caller no longer  * needs it.  (Alternatively, we could write this routine to use the  * IJG library's memory allocator, so that the data would be freed implicitly  * at jpeg_finish_decompress() time.  But it seems likely that many apps  * will prefer to have the data stick around after decompression finishes.)  */
end_comment

begin_function_decl
name|gboolean
name|jpeg_icc_read_profile
parameter_list|(
name|j_decompress_ptr
name|cinfo
parameter_list|,
name|guchar
modifier|*
modifier|*
name|icc_data_ptr
parameter_list|,
name|guint
modifier|*
name|icc_data_len
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __JPEG_ICC_H__ */
end_comment

end_unit


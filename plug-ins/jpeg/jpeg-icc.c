begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* jpeg-icc.c  *  * This file provides code to read and write International Color  * Consortium (ICC) device profiles embedded in JFIF JPEG image files.  * The ICC has defined a standard format for including such data in  * JPEG "APP2" markers.  The code given here does not know anything  * about the internal structure of the ICC profile data; it just knows  * how to put the profile data into a JPEG file being written, or get  * it back out when reading.  *  * This code depends on new features added to the IJG JPEG library as of  * IJG release 6b; it will not compile or work with older IJG versions.  */
end_comment

begin_comment
comment|/* This code was originally copied from the jpegicc tool as found in  * the lcms source code. This code comes with the following copyright  * notice:  *  * Little cms  * Copyright (C) 1998-2004 Marti Maria  *  *  Permission is hereby granted, free of charge, to any person  *  obtaining a copy of this software and associated documentation  *  files (the "Software"), to deal in the Software without  *  restriction, including without limitation the rights to use, copy,  *  modify, merge, publish, distribute, sublicense, and/or sell copies  *  of the Software, and to permit persons to whom the Software is  *  furnished to do so, subject to the following conditions:  *  * The above copyright notice and this permission notice shall be  *  included in all copies or substantial portions of the Software.  */
end_comment

begin_comment
comment|/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN  * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  * SOFTWARE.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<jpeglib.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"jpeg-icc.h"
end_include

begin_comment
comment|/*  * Since an ICC profile can be larger than the maximum size of a JPEG  * marker (64K), we need provisions to split it into multiple markers.  * The format defined by the ICC specifies one or more APP2 markers  * containing the following data:  *  *	Identifying string	ASCII "ICC_PROFILE\0"  (12 bytes)  *	Marker sequence number	1 for first APP2, 2 for next, etc (1 byte)  *	Number of markers	Total number of APP2's used (1 byte)  *      Profile data		(remainder of APP2 data)   * Decoders should use the marker sequence numbers to reassemble the  * profile, rather than assuming that the APP2 markers appear in the  * correct sequence.  */
end_comment

begin_define
DECL|macro|ICC_MARKER
define|#
directive|define
name|ICC_MARKER
value|(JPEG_APP0 + 2)
end_define

begin_comment
DECL|macro|ICC_MARKER
comment|/* JPEG marker code for ICC */
end_comment

begin_define
DECL|macro|ICC_OVERHEAD_LEN
define|#
directive|define
name|ICC_OVERHEAD_LEN
value|14
end_define

begin_comment
DECL|macro|ICC_OVERHEAD_LEN
comment|/* size of non-profile data in APP2 */
end_comment

begin_define
DECL|macro|MAX_BYTES_IN_MARKER
define|#
directive|define
name|MAX_BYTES_IN_MARKER
value|65533
end_define

begin_comment
DECL|macro|MAX_BYTES_IN_MARKER
comment|/* maximum data len of a JPEG marker */
end_comment

begin_define
DECL|macro|MAX_DATA_BYTES_IN_MARKER
define|#
directive|define
name|MAX_DATA_BYTES_IN_MARKER
value|(MAX_BYTES_IN_MARKER - ICC_OVERHEAD_LEN)
end_define

begin_comment
comment|/*  * This routine writes the given ICC profile data into a JPEG file.  * It *must* be called AFTER calling jpeg_start_compress() and BEFORE  * the first call to jpeg_write_scanlines().  * (This ordering ensures that the APP2 marker(s) will appear after the  * SOI and JFIF or Adobe markers, but before all else.)  */
end_comment

begin_function
name|void
DECL|function|jpeg_icc_write_profile (j_compress_ptr cinfo,const guchar * icc_data_ptr,guint icc_data_len)
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
block|{
name|unsigned
name|int
name|num_markers
decl_stmt|;
comment|/* total number of markers we'll write */
name|int
name|cur_marker
init|=
literal|1
decl_stmt|;
comment|/* per spec, counting starts at 1 */
name|unsigned
name|int
name|length
decl_stmt|;
comment|/* number of bytes to write in this marker */
comment|/* Calculate the number of markers we'll need, rounding up of course */
name|num_markers
operator|=
name|icc_data_len
operator|/
name|MAX_DATA_BYTES_IN_MARKER
expr_stmt|;
if|if
condition|(
name|num_markers
operator|*
name|MAX_DATA_BYTES_IN_MARKER
operator|!=
name|icc_data_len
condition|)
name|num_markers
operator|++
expr_stmt|;
while|while
condition|(
name|icc_data_len
operator|>
literal|0
condition|)
block|{
comment|/* length of profile to put in this marker */
name|length
operator|=
name|icc_data_len
expr_stmt|;
if|if
condition|(
name|length
operator|>
name|MAX_DATA_BYTES_IN_MARKER
condition|)
name|length
operator|=
name|MAX_DATA_BYTES_IN_MARKER
expr_stmt|;
name|icc_data_len
operator|-=
name|length
expr_stmt|;
comment|/* Write the JPEG marker header (APP2 code and marker length) */
name|jpeg_write_m_header
argument_list|(
name|cinfo
argument_list|,
name|ICC_MARKER
argument_list|,
call|(
name|unsigned
name|int
call|)
argument_list|(
name|length
operator|+
name|ICC_OVERHEAD_LEN
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Write the marker identifying string "ICC_PROFILE" (null-terminated).      * We code it in this less-than-transparent way so that the code works      * even if the local character set is not ASCII.      */
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x49
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x43
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x43
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x5F
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x50
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x52
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x4F
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x46
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x49
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x4C
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x45
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
literal|0x0
argument_list|)
expr_stmt|;
comment|/* Add the sequencing info */
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
name|cur_marker
argument_list|)
expr_stmt|;
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
operator|(
name|int
operator|)
name|num_markers
argument_list|)
expr_stmt|;
comment|/* Add the profile data */
while|while
condition|(
name|length
operator|--
condition|)
block|{
name|jpeg_write_m_byte
argument_list|(
name|cinfo
argument_list|,
operator|*
name|icc_data_ptr
argument_list|)
expr_stmt|;
name|icc_data_ptr
operator|++
expr_stmt|;
block|}
name|cur_marker
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  * Prepare for reading an ICC profile  */
end_comment

begin_function
name|void
DECL|function|jpeg_icc_setup_read_profile (j_decompress_ptr cinfo)
name|jpeg_icc_setup_read_profile
parameter_list|(
name|j_decompress_ptr
name|cinfo
parameter_list|)
block|{
comment|/* Tell the library to keep any APP2 data it may find */
name|jpeg_save_markers
argument_list|(
name|cinfo
argument_list|,
name|ICC_MARKER
argument_list|,
literal|0xFFFF
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * Handy subroutine to test whether a saved marker is an ICC profile marker.  */
end_comment

begin_function
specifier|static
name|boolean
DECL|function|marker_is_icc (jpeg_saved_marker_ptr marker)
name|marker_is_icc
parameter_list|(
name|jpeg_saved_marker_ptr
name|marker
parameter_list|)
block|{
return|return
name|marker
operator|->
name|marker
operator|==
name|ICC_MARKER
operator|&&
name|marker
operator|->
name|data_length
operator|>=
name|ICC_OVERHEAD_LEN
operator|&&
comment|/* verify the identifying string */
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|0
index|]
argument_list|)
operator|==
literal|0x49
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|1
index|]
argument_list|)
operator|==
literal|0x43
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|2
index|]
argument_list|)
operator|==
literal|0x43
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|3
index|]
argument_list|)
operator|==
literal|0x5F
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|4
index|]
argument_list|)
operator|==
literal|0x50
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|5
index|]
argument_list|)
operator|==
literal|0x52
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|6
index|]
argument_list|)
operator|==
literal|0x4F
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|7
index|]
argument_list|)
operator|==
literal|0x46
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|8
index|]
argument_list|)
operator|==
literal|0x49
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|9
index|]
argument_list|)
operator|==
literal|0x4C
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|10
index|]
argument_list|)
operator|==
literal|0x45
operator|&&
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|11
index|]
argument_list|)
operator|==
literal|0x0
return|;
block|}
end_function

begin_comment
comment|/*  * See if there was an ICC profile in the JPEG file being read;  * if so, reassemble and return the profile data.  *  * TRUE is returned if an ICC profile was found, FALSE if not.  * If TRUE is returned, *icc_data_ptr is set to point to the  * returned data, and *icc_data_len is set to its length.  *  * NOTE: if the file contains invalid ICC APP2 markers, we just silently  * return FALSE.  You might want to issue an error message instead.  */
end_comment

begin_function
name|gboolean
DECL|function|jpeg_icc_read_profile (j_decompress_ptr cinfo,guchar ** icc_data_ptr,guint * icc_data_len)
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
block|{
name|jpeg_saved_marker_ptr
name|marker
decl_stmt|;
name|int
name|num_markers
init|=
literal|0
decl_stmt|;
name|int
name|seq_no
decl_stmt|;
name|JOCTET
modifier|*
name|icc_data
decl_stmt|;
name|unsigned
name|int
name|total_length
decl_stmt|;
DECL|macro|MAX_SEQ_NO
define|#
directive|define
name|MAX_SEQ_NO
value|255
comment|/* sufficient since marker numbers are bytes */
name|char
name|marker_present
index|[
name|MAX_SEQ_NO
operator|+
literal|1
index|]
decl_stmt|;
comment|/* 1 if marker found */
name|unsigned
name|int
name|data_length
index|[
name|MAX_SEQ_NO
operator|+
literal|1
index|]
decl_stmt|;
comment|/* size of profile data in marker */
name|unsigned
name|int
name|data_offset
index|[
name|MAX_SEQ_NO
operator|+
literal|1
index|]
decl_stmt|;
comment|/* offset for data in marker */
operator|*
name|icc_data_ptr
operator|=
name|NULL
expr_stmt|;
comment|/* avoid confusion if FALSE return */
operator|*
name|icc_data_len
operator|=
literal|0
expr_stmt|;
comment|/* This first pass over the saved markers discovers whether there are    * any ICC markers and verifies the consistency of the marker numbering.    */
for|for
control|(
name|seq_no
operator|=
literal|1
init|;
name|seq_no
operator|<=
name|MAX_SEQ_NO
condition|;
name|seq_no
operator|++
control|)
name|marker_present
index|[
name|seq_no
index|]
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|marker
operator|=
name|cinfo
operator|->
name|marker_list
init|;
name|marker
operator|!=
name|NULL
condition|;
name|marker
operator|=
name|marker
operator|->
name|next
control|)
block|{
if|if
condition|(
name|marker_is_icc
argument_list|(
name|marker
argument_list|)
condition|)
block|{
if|if
condition|(
name|num_markers
operator|==
literal|0
condition|)
name|num_markers
operator|=
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|13
index|]
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|num_markers
operator|!=
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|13
index|]
argument_list|)
condition|)
return|return
name|FALSE
return|;
comment|/* inconsistent num_markers fields */
name|seq_no
operator|=
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|12
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|seq_no
operator|<=
literal|0
operator|||
name|seq_no
operator|>
name|num_markers
condition|)
return|return
name|FALSE
return|;
comment|/* bogus sequence number */
if|if
condition|(
name|marker_present
index|[
name|seq_no
index|]
condition|)
return|return
name|FALSE
return|;
comment|/* duplicate sequence numbers */
name|marker_present
index|[
name|seq_no
index|]
operator|=
literal|1
expr_stmt|;
name|data_length
index|[
name|seq_no
index|]
operator|=
name|marker
operator|->
name|data_length
operator|-
name|ICC_OVERHEAD_LEN
expr_stmt|;
block|}
block|}
if|if
condition|(
name|num_markers
operator|==
literal|0
condition|)
return|return
name|FALSE
return|;
comment|/* Check for missing markers, count total space needed,    * compute offset of each marker's part of the data.    */
name|total_length
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|seq_no
operator|=
literal|1
init|;
name|seq_no
operator|<=
name|num_markers
condition|;
name|seq_no
operator|++
control|)
block|{
if|if
condition|(
name|marker_present
index|[
name|seq_no
index|]
operator|==
literal|0
condition|)
return|return
name|FALSE
return|;
comment|/* missing sequence number */
name|data_offset
index|[
name|seq_no
index|]
operator|=
name|total_length
expr_stmt|;
name|total_length
operator|+=
name|data_length
index|[
name|seq_no
index|]
expr_stmt|;
block|}
if|if
condition|(
name|total_length
operator|<=
literal|0
condition|)
return|return
name|FALSE
return|;
comment|/* found only empty markers? */
comment|/* Allocate space for assembled data */
name|icc_data
operator|=
name|g_try_malloc
argument_list|(
name|total_length
operator|*
sizeof|sizeof
argument_list|(
name|JOCTET
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|icc_data
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
comment|/* oops, out of memory */
comment|/* and fill it in */
for|for
control|(
name|marker
operator|=
name|cinfo
operator|->
name|marker_list
init|;
name|marker
operator|!=
name|NULL
condition|;
name|marker
operator|=
name|marker
operator|->
name|next
control|)
block|{
if|if
condition|(
name|marker_is_icc
argument_list|(
name|marker
argument_list|)
condition|)
block|{
name|JOCTET
name|FAR
modifier|*
name|src_ptr
decl_stmt|;
name|JOCTET
modifier|*
name|dst_ptr
decl_stmt|;
name|unsigned
name|int
name|length
decl_stmt|;
name|seq_no
operator|=
name|GETJOCTET
argument_list|(
name|marker
operator|->
name|data
index|[
literal|12
index|]
argument_list|)
expr_stmt|;
name|dst_ptr
operator|=
name|icc_data
operator|+
name|data_offset
index|[
name|seq_no
index|]
expr_stmt|;
name|src_ptr
operator|=
name|marker
operator|->
name|data
operator|+
name|ICC_OVERHEAD_LEN
expr_stmt|;
name|length
operator|=
name|data_length
index|[
name|seq_no
index|]
expr_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
operator|*
name|dst_ptr
operator|++
operator|=
operator|*
name|src_ptr
operator|++
expr_stmt|;
block|}
block|}
block|}
operator|*
name|icc_data_ptr
operator|=
name|icc_data
expr_stmt|;
operator|*
name|icc_data_len
operator|=
name|total_length
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit


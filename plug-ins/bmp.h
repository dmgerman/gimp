begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_define
DECL|macro|TRUE
define|#
directive|define
name|TRUE
value|1
end_define

begin_define
DECL|macro|FALSE
define|#
directive|define
name|FALSE
value|0
end_define

begin_define
DECL|macro|MAXCOLORS
define|#
directive|define
name|MAXCOLORS
value|256
end_define

begin_define
DECL|macro|Image
define|#
directive|define
name|Image
value|gint32
end_define

begin_define
DECL|macro|BitSet (byte,bit)
define|#
directive|define
name|BitSet
parameter_list|(
name|byte
parameter_list|,
name|bit
parameter_list|)
value|(((byte)& (bit)) == (bit))
end_define

begin_define
DECL|macro|ReadOK (file,buffer,len)
define|#
directive|define
name|ReadOK
parameter_list|(
name|file
parameter_list|,
name|buffer
parameter_list|,
name|len
parameter_list|)
value|(fread(buffer, len, 1, file) != 0)
end_define

begin_define
DECL|macro|WriteOK (file,buffer,len)
define|#
directive|define
name|WriteOK
parameter_list|(
name|file
parameter_list|,
name|buffer
parameter_list|,
name|len
parameter_list|)
value|(fwrite(buffer, len, 1, file) != 0)
end_define

begin_function_decl
specifier|extern
name|gint32
name|ReadBMP
parameter_list|(
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gint
name|WriteBMP
parameter_list|(
name|char
modifier|*
parameter_list|,
name|gint32
parameter_list|,
name|gint32
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gint
name|ReadColorMap
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|unsigned
name|char
index|[
literal|256
index|]
index|[
literal|3
index|]
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|Image
name|ReadImage
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
index|[
literal|256
index|]
index|[
literal|3
index|]
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|WriteColorMap
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|WriteImage
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|int
name|interactive_bmp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|filename
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|FILE
modifier|*
name|errorfile
decl_stmt|;
end_decl_stmt

begin_struct
specifier|static
struct|struct
DECL|struct|__anon2b16cab30108
block|{
DECL|member|bfSize
name|unsigned
name|long
name|bfSize
decl_stmt|;
comment|/* 02 */
DECL|member|reserverd
name|unsigned
name|long
name|reserverd
decl_stmt|;
comment|/* 06 */
DECL|member|bfOffs
name|unsigned
name|long
name|bfOffs
decl_stmt|;
comment|/* 0A */
DECL|member|biSize
name|unsigned
name|long
name|biSize
decl_stmt|;
comment|/* 0E */
DECL|variable|Bitmap_File_Head
block|}
name|Bitmap_File_Head
struct|;
end_struct

begin_struct
specifier|static
struct|struct
DECL|struct|__anon2b16cab30208
block|{
DECL|member|biWidth
name|unsigned
name|long
name|biWidth
decl_stmt|;
comment|/* 12 */
DECL|member|biHeight
name|unsigned
name|long
name|biHeight
decl_stmt|;
comment|/* 16 */
DECL|member|biPlanes_biBitCnt
name|unsigned
name|long
name|biPlanes_biBitCnt
decl_stmt|;
comment|/* 1A */
DECL|member|biCompr
name|unsigned
name|long
name|biCompr
decl_stmt|;
comment|/* 1E */
DECL|member|biSizeIm
name|unsigned
name|long
name|biSizeIm
decl_stmt|;
comment|/* 22 */
DECL|member|biXPels
name|unsigned
name|long
name|biXPels
decl_stmt|;
comment|/* 26 */
DECL|member|biYPels
name|unsigned
name|long
name|biYPels
decl_stmt|;
comment|/* 2A */
DECL|member|biClrUsed
name|unsigned
name|long
name|biClrUsed
decl_stmt|;
comment|/* 2E */
DECL|member|biClrImp
name|unsigned
name|long
name|biClrImp
decl_stmt|;
comment|/* 32 */
comment|/* 36 */
DECL|variable|Bitmap_Head
block|}
name|Bitmap_Head
struct|;
end_struct

begin_struct
specifier|static
struct|struct
DECL|struct|__anon2b16cab30308
block|{
DECL|member|bcWidth_bcHeight
name|unsigned
name|long
name|bcWidth_bcHeight
decl_stmt|;
comment|/* 12 */
DECL|member|bcPlanes_bcBitCnt
name|unsigned
name|long
name|bcPlanes_bcBitCnt
decl_stmt|;
comment|/* 1A */
DECL|variable|Bitmap_OS2_Head
block|}
name|Bitmap_OS2_Head
struct|;
end_struct

begin_define
DECL|macro|biBitCnt
define|#
directive|define
name|biBitCnt
value|((Bitmap_Head.biPlanes_biBitCnt& 0xffff0000)>> 16)
end_define

begin_define
DECL|macro|bcBitCnt
define|#
directive|define
name|bcBitCnt
value|((Bitmap_OS2_Head.biPlanes_biBitCnt& 0xffff0000)>> 16)
end_define

begin_define
DECL|macro|bcHeight
define|#
directive|define
name|bcHeight
value|((Bitmap_OS2_Head.bcWidth_bcHeight& 0xffff0000)>> 16)
end_define

begin_define
DECL|macro|bcWidth
define|#
directive|define
name|bcWidth
value|(Bitmap_OS2_Head.bcWidth_bcHeight& 0x0000ffff)
end_define

end_unit


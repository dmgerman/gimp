begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

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
DECL|macro|Write (file,buffer,len)
define|#
directive|define
name|Write
parameter_list|(
name|file
parameter_list|,
name|buffer
parameter_list|,
name|len
parameter_list|)
value|fwrite(buffer, len, 1, file)
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
value|(Write(buffer, len, file) != 0)
end_define

begin_function_decl
specifier|extern
name|gint32
name|ToL
parameter_list|(
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|FromL
parameter_list|(
name|gint32
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gint16
name|ToS
parameter_list|(
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|FromS
parameter_list|(
name|gint16
parameter_list|,
name|guchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gint32
name|ReadBMP
parameter_list|(
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GStatusType
name|WriteBMP
parameter_list|(
name|gchar
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
name|guchar
index|[
literal|256
index|]
index|[
literal|3
index|]
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
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
name|gint
parameter_list|,
name|gint
parameter_list|,
name|guchar
index|[
literal|256
index|]
index|[
literal|3
index|]
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
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
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
modifier|*
parameter_list|,
name|gint
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
name|guchar
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|gint
name|interactive_bmp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gchar
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
DECL|struct|Bitmap_File_Head_Struct
specifier|extern
struct|struct
name|Bitmap_File_Head_Struct
block|{
DECL|member|zzMagic
name|gchar
name|zzMagic
index|[
literal|2
index|]
decl_stmt|;
comment|/* 00 "BM" */
DECL|member|bfSize
name|gulong
name|bfSize
decl_stmt|;
comment|/* 02 */
DECL|member|zzHotX
name|gushort
name|zzHotX
decl_stmt|;
comment|/* 06 */
DECL|member|zzHotY
name|gushort
name|zzHotY
decl_stmt|;
comment|/* 08 */
DECL|member|bfOffs
name|gulong
name|bfOffs
decl_stmt|;
comment|/* 0A */
DECL|member|biSize
name|gulong
name|biSize
decl_stmt|;
comment|/* 0E */
DECL|variable|Bitmap_File_Head
block|}
name|Bitmap_File_Head
struct|;
end_struct

begin_struct
DECL|struct|Bitmap_Head_Struct
specifier|extern
struct|struct
name|Bitmap_Head_Struct
block|{
DECL|member|biWidth
name|gulong
name|biWidth
decl_stmt|;
comment|/* 12 */
DECL|member|biHeight
name|gulong
name|biHeight
decl_stmt|;
comment|/* 16 */
DECL|member|biPlanes
name|gushort
name|biPlanes
decl_stmt|;
comment|/* 1A */
DECL|member|biBitCnt
name|gushort
name|biBitCnt
decl_stmt|;
comment|/* 1C */
DECL|member|biCompr
name|gulong
name|biCompr
decl_stmt|;
comment|/* 1E */
DECL|member|biSizeIm
name|gulong
name|biSizeIm
decl_stmt|;
comment|/* 22 */
DECL|member|biXPels
name|gulong
name|biXPels
decl_stmt|;
comment|/* 26 */
DECL|member|biYPels
name|gulong
name|biYPels
decl_stmt|;
comment|/* 2A */
DECL|member|biClrUsed
name|gulong
name|biClrUsed
decl_stmt|;
comment|/* 2E */
DECL|member|biClrImp
name|gulong
name|biClrImp
decl_stmt|;
comment|/* 32 */
comment|/* 36 */
DECL|variable|Bitmap_Head
block|}
name|Bitmap_Head
struct|;
end_struct

end_unit


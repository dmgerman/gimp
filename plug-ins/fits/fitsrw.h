begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/******************************************************************************/
end_comment

begin_comment
comment|/*                      Peter Kirchgessner                                    */
end_comment

begin_comment
comment|/*                      e-mail: pkirchg@aol.com                               */
end_comment

begin_comment
comment|/*                      WWW   : http://members.aol.com/pkirchg                */
end_comment

begin_comment
comment|/******************************************************************************/
end_comment

begin_comment
comment|/*  #BEG-HDR                                                                  */
end_comment

begin_comment
comment|/*                                                                            */
end_comment

begin_comment
comment|/*  Package       : FITS reading/writing library                              */
end_comment

begin_comment
comment|/*  Modul-Name    : fitsrw.h                                                  */
end_comment

begin_comment
comment|/*  Description   : Include file for FITS-r/w-library                         */
end_comment

begin_comment
comment|/*  Function(s)   :                                                           */
end_comment

begin_comment
comment|/*  Author        : P. Kirchgessner                                           */
end_comment

begin_comment
comment|/*  Date of Gen.  : 12-Apr-97                                                 */
end_comment

begin_comment
comment|/*  Last modified : 17-May-97                                                 */
end_comment

begin_comment
comment|/*  Version       : 0.10                                                      */
end_comment

begin_comment
comment|/*  Compiler Opt. :                                                           */
end_comment

begin_comment
comment|/*  Changes       :                                                           */
end_comment

begin_comment
comment|/*                                                                            */
end_comment

begin_comment
comment|/*  #END-HDR                                                                  */
end_comment

begin_comment
comment|/******************************************************************************/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|FITS_MAX_AXIS
end_ifndef

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_define
DECL|macro|FITS_CARD_SIZE
define|#
directive|define
name|FITS_CARD_SIZE
value|80
end_define

begin_define
DECL|macro|FITS_RECORD_SIZE
define|#
directive|define
name|FITS_RECORD_SIZE
value|2880
end_define

begin_define
DECL|macro|FITS_MAX_AXIS
define|#
directive|define
name|FITS_MAX_AXIS
value|999
end_define

begin_define
DECL|macro|FITS_NADD_CARDS
define|#
directive|define
name|FITS_NADD_CARDS
value|128
end_define

begin_comment
comment|/* Data representations */
end_comment

begin_typedef
DECL|typedef|FITS_BITPIX8
typedef|typedef
name|unsigned
name|char
name|FITS_BITPIX8
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_BITPIX16
typedef|typedef
name|short
name|FITS_BITPIX16
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_BITPIX32
typedef|typedef
name|long
name|FITS_BITPIX32
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_BITPIXM32
typedef|typedef
name|float
name|FITS_BITPIXM32
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_BITPIXM64
typedef|typedef
name|double
name|FITS_BITPIXM64
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_BOOL
typedef|typedef
name|int
name|FITS_BOOL
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_LONG
typedef|typedef
name|long
name|FITS_LONG
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_DOUBLE
typedef|typedef
name|double
name|FITS_DOUBLE
typedef|;
end_typedef

begin_typedef
DECL|typedef|FITS_STRING
typedef|typedef
name|char
name|FITS_STRING
index|[
name|FITS_CARD_SIZE
index|]
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon28e2feb10103
typedef|typedef
enum|enum
block|{
DECL|enumerator|typ_bitpix8
DECL|enumerator|typ_bitpix16
DECL|enumerator|typ_bitpix32
DECL|enumerator|typ_bitpixm32
DECL|enumerator|typ_bitpixm64
name|typ_bitpix8
block|,
name|typ_bitpix16
block|,
name|typ_bitpix32
block|,
name|typ_bitpixm32
block|,
name|typ_bitpixm64
block|,
DECL|enumerator|typ_fbool
DECL|enumerator|typ_flong
DECL|enumerator|typ_fdouble
DECL|enumerator|typ_fstring
name|typ_fbool
block|,
name|typ_flong
block|,
name|typ_fdouble
block|,
name|typ_fstring
DECL|typedef|FITS_DATA_TYPES
block|}
name|FITS_DATA_TYPES
typedef|;
end_typedef

begin_comment
comment|/* How to transform FITS pixel values */
end_comment

begin_typedef
DECL|struct|__anon28e2feb10208
typedef|typedef
struct|struct
block|{
DECL|member|pixmin
DECL|member|pixmax
name|double
name|pixmin
decl_stmt|,
name|pixmax
decl_stmt|;
comment|/* Pixel values [pixmin,pixmax] should be mapped */
DECL|member|datamin
DECL|member|datamax
name|double
name|datamin
decl_stmt|,
name|datamax
decl_stmt|;
comment|/* to [datamin,datamax] */
DECL|member|replacement
name|double
name|replacement
decl_stmt|;
comment|/* datavalue to use for blank or NaN pixels */
DECL|member|dsttyp
name|char
name|dsttyp
decl_stmt|;
comment|/* Destination typ ('c' = char) */
DECL|typedef|FITS_PIX_TRANSFORM
block|}
name|FITS_PIX_TRANSFORM
typedef|;
end_typedef

begin_typedef
DECL|union|__anon28e2feb1030a
typedef|typedef
union|union
block|{
DECL|member|bitpix8
name|FITS_BITPIX8
name|bitpix8
decl_stmt|;
DECL|member|bitpix16
name|FITS_BITPIX16
name|bitpix16
decl_stmt|;
DECL|member|bitpix32
name|FITS_BITPIX32
name|bitpix32
decl_stmt|;
DECL|member|bitpixm32
name|FITS_BITPIXM32
name|bitpixm32
decl_stmt|;
DECL|member|bitpixm64
name|FITS_BITPIXM64
name|bitpixm64
decl_stmt|;
DECL|member|fbool
name|FITS_BOOL
name|fbool
decl_stmt|;
DECL|member|flong
name|FITS_LONG
name|flong
decl_stmt|;
DECL|member|fdouble
name|FITS_DOUBLE
name|fdouble
decl_stmt|;
DECL|member|fstring
name|FITS_STRING
name|fstring
decl_stmt|;
DECL|typedef|FITS_DATA
block|}
name|FITS_DATA
typedef|;
end_typedef

begin_typedef
DECL|struct|fits_record_list
typedef|typedef
struct|struct
name|fits_record_list
block|{
comment|/* Record list */
DECL|member|data
name|char
name|data
index|[
name|FITS_RECORD_SIZE
index|]
decl_stmt|;
DECL|member|next_record
name|struct
name|fits_record_list
modifier|*
name|next_record
decl_stmt|;
DECL|typedef|FITS_RECORD_LIST
block|}
name|FITS_RECORD_LIST
typedef|;
end_typedef

begin_typedef
DECL|struct|fits_hdu_list
typedef|typedef
struct|struct
name|fits_hdu_list
block|{
comment|/* Header and Data Unit List */
DECL|member|header_offset
name|long
name|header_offset
decl_stmt|;
comment|/* Offset of header in the file */
DECL|member|data_offset
name|long
name|data_offset
decl_stmt|;
comment|/* Offset of data in the file */
DECL|member|data_size
name|long
name|data_size
decl_stmt|;
comment|/* Size of data in the HDU (including pad)*/
DECL|member|udata_size
name|long
name|udata_size
decl_stmt|;
comment|/* Size of used data in the HDU (excl. pad) */
DECL|member|bpp
name|int
name|bpp
decl_stmt|;
comment|/* Bytes per pixel */
DECL|member|numpic
name|int
name|numpic
decl_stmt|;
comment|/* Number of interpretable images in HDU */
DECL|member|naddcards
name|int
name|naddcards
decl_stmt|;
comment|/* Number of additional cards */
DECL|member|addcards
name|char
name|addcards
index|[
name|FITS_NADD_CARDS
index|]
index|[
name|FITS_CARD_SIZE
index|]
decl_stmt|;
DECL|struct|__anon28e2feb10408
struct|struct
block|{
DECL|member|nan_value
name|char
name|nan_value
decl_stmt|;
comment|/* NaN's found in data ? */
DECL|member|blank_value
name|char
name|blank_value
decl_stmt|;
comment|/* Blanks found in data ? */
comment|/* Flags specifying if some cards are used */
DECL|member|blank
name|char
name|blank
decl_stmt|;
comment|/* The corresponding data below is only */
DECL|member|datamin
name|char
name|datamin
decl_stmt|;
comment|/* valid, if the flag is set. */
DECL|member|datamax
name|char
name|datamax
decl_stmt|;
DECL|member|simple
name|char
name|simple
decl_stmt|;
comment|/* This indicates a simple HDU */
DECL|member|xtension
name|char
name|xtension
decl_stmt|;
comment|/* This indicates an extension */
DECL|member|gcount
name|char
name|gcount
decl_stmt|;
DECL|member|pcount
name|char
name|pcount
decl_stmt|;
DECL|member|bzero
name|char
name|bzero
decl_stmt|;
DECL|member|bscale
name|char
name|bscale
decl_stmt|;
DECL|member|groups
name|char
name|groups
decl_stmt|;
DECL|member|extend
name|char
name|extend
decl_stmt|;
DECL|member|used
block|}
name|used
struct|;
DECL|member|pixmin
DECL|member|pixmax
name|double
name|pixmin
decl_stmt|,
name|pixmax
decl_stmt|;
comment|/* Minimum/Maximum pixel values */
comment|/* Some decoded data of the HDU: */
DECL|member|naxis
name|int
name|naxis
decl_stmt|;
comment|/* Number of axes */
DECL|member|naxisn
name|int
name|naxisn
index|[
name|FITS_MAX_AXIS
index|]
decl_stmt|;
comment|/* Sizes of axes (NAXIS1 --> naxisn[0]) */
DECL|member|bitpix
name|int
name|bitpix
decl_stmt|;
comment|/* Data representation (8,16,32,-16,-32) */
comment|/* When using the following data, */
comment|/* the used-flags must be checked before. */
DECL|member|blank
name|long
name|blank
decl_stmt|;
comment|/* Blank value */
DECL|member|datamin
DECL|member|datamax
name|double
name|datamin
decl_stmt|,
name|datamax
decl_stmt|;
comment|/* Minimum/Maximum physical data values */
DECL|member|xtension
name|char
name|xtension
index|[
name|FITS_CARD_SIZE
index|]
decl_stmt|;
comment|/* Type of extension */
DECL|member|gcount
DECL|member|pcount
name|long
name|gcount
decl_stmt|,
name|pcount
decl_stmt|;
comment|/* Used by XTENSION */
DECL|member|bzero
DECL|member|bscale
name|double
name|bzero
decl_stmt|,
name|bscale
decl_stmt|;
comment|/* Transformation values */
DECL|member|groups
name|int
name|groups
decl_stmt|;
comment|/* Random groups indicator */
DECL|member|extend
name|int
name|extend
decl_stmt|;
comment|/* Extend flag */
DECL|member|header_record_list
name|FITS_RECORD_LIST
modifier|*
name|header_record_list
decl_stmt|;
comment|/* Header records read in */
DECL|member|next_hdu
name|struct
name|fits_hdu_list
modifier|*
name|next_hdu
decl_stmt|;
DECL|typedef|FITS_HDU_LIST
block|}
name|FITS_HDU_LIST
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28e2feb10508
typedef|typedef
struct|struct
block|{
DECL|member|fp
name|FILE
modifier|*
name|fp
decl_stmt|;
comment|/* File pointer to fits file */
DECL|member|openmode
name|char
name|openmode
decl_stmt|;
comment|/* Mode the file was opened (0, 'r', 'w') */
DECL|member|n_hdu
name|int
name|n_hdu
decl_stmt|;
comment|/* Number of HDUs in file */
DECL|member|n_pic
name|int
name|n_pic
decl_stmt|;
comment|/* Total number of interpretable pictures */
DECL|member|nan_used
name|int
name|nan_used
decl_stmt|;
comment|/* NaN's used in the file ? */
DECL|member|blank_used
name|int
name|blank_used
decl_stmt|;
comment|/* Blank's used in the file ? */
DECL|member|hdu_list
name|FITS_HDU_LIST
modifier|*
name|hdu_list
decl_stmt|;
comment|/* Header and Data Unit List */
DECL|typedef|FITS_FILE
block|}
name|FITS_FILE
typedef|;
end_typedef

begin_comment
comment|/* User callable functions of the FITS-library */
end_comment

begin_function_decl
name|FITS_FILE
modifier|*
name|fits_open
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|char
modifier|*
name|openmode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fits_close
parameter_list|(
name|FITS_FILE
modifier|*
name|ff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FITS_HDU_LIST
modifier|*
name|fits_add_hdu
parameter_list|(
name|FITS_FILE
modifier|*
name|ff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|fits_add_card
parameter_list|(
name|FITS_HDU_LIST
modifier|*
name|hdulist
parameter_list|,
name|char
modifier|*
name|card
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|fits_write_header
parameter_list|(
name|FITS_FILE
modifier|*
name|ff
parameter_list|,
name|FITS_HDU_LIST
modifier|*
name|hdulist
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FITS_HDU_LIST
modifier|*
name|fits_image_info
parameter_list|(
name|FITS_FILE
modifier|*
name|ff
parameter_list|,
name|int
name|picind
parameter_list|,
name|int
modifier|*
name|hdupicind
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FITS_HDU_LIST
modifier|*
name|fits_seek_image
parameter_list|(
name|FITS_FILE
modifier|*
name|ff
parameter_list|,
name|int
name|picind
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fits_print_header
parameter_list|(
name|FITS_HDU_LIST
modifier|*
name|hdr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FITS_DATA
modifier|*
name|fits_decode_card
parameter_list|(
specifier|const
name|char
modifier|*
name|card
parameter_list|,
name|FITS_DATA_TYPES
name|data_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|fits_search_card
parameter_list|(
name|FITS_RECORD_LIST
modifier|*
name|rl
parameter_list|,
name|char
modifier|*
name|keyword
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|fits_read_pixel
parameter_list|(
name|FITS_FILE
modifier|*
name|ff
parameter_list|,
name|FITS_HDU_LIST
modifier|*
name|hdulist
parameter_list|,
name|int
name|npix
parameter_list|,
name|FITS_PIX_TRANSFORM
modifier|*
name|trans
parameter_list|,
name|void
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|fits_get_error
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Demo functions */
end_comment

begin_define
DECL|macro|FITS_NO_DEMO
define|#
directive|define
name|FITS_NO_DEMO
end_define

begin_function_decl
name|int
name|fits_to_pgmraw
parameter_list|(
name|char
modifier|*
name|fitsfile
parameter_list|,
name|char
modifier|*
name|pgmfile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|pgmraw_to_fits
parameter_list|(
name|char
modifier|*
name|pgmfile
parameter_list|,
name|char
modifier|*
name|fitsfile
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit


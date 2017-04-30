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
name|__FITS_IO_H__
end_ifndef

begin_define
DECL|macro|__FITS_IO_H__
define|#
directive|define
name|__FITS_IO_H__
end_define

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
DECL|typedef|FitsBitpix8
typedef|typedef
name|guchar
name|FitsBitpix8
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsBitpix16
typedef|typedef
name|gint16
name|FitsBitpix16
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsBitpix32
typedef|typedef
name|gint32
name|FitsBitpix32
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsBitpixM32
typedef|typedef
name|float
name|FitsBitpixM32
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsBitpixM64
typedef|typedef
name|double
name|FitsBitpixM64
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsBool
typedef|typedef
name|gint32
name|FitsBool
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsLong
typedef|typedef
name|gint32
name|FitsLong
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsDouble
typedef|typedef
name|double
name|FitsDouble
typedef|;
end_typedef

begin_typedef
DECL|typedef|FitsString
typedef|typedef
name|char
name|FitsString
index|[
name|FITS_CARD_SIZE
index|]
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c52e8d10103
block|{
DECL|enumerator|FITS_DATA_TYPE_BITPIX_8
name|FITS_DATA_TYPE_BITPIX_8
block|,
DECL|enumerator|FITS_DATA_TYPE_BITPIX_16
name|FITS_DATA_TYPE_BITPIX_16
block|,
DECL|enumerator|FITS_DATA_TYPE_BITPIX_32
name|FITS_DATA_TYPE_BITPIX_32
block|,
DECL|enumerator|FITS_DATA_TYPE_BITPIX_M32
name|FITS_DATA_TYPE_BITPIX_M32
block|,
DECL|enumerator|FITS_DATA_TYPE_BITPIX_M64
name|FITS_DATA_TYPE_BITPIX_M64
block|,
DECL|enumerator|FITS_DATA_TYPE_FBOOL
name|FITS_DATA_TYPE_FBOOL
block|,
DECL|enumerator|FITS_DATA_TYPE_FLONG
name|FITS_DATA_TYPE_FLONG
block|,
DECL|enumerator|FITS_DATA_TYPE_FDOUBLE
name|FITS_DATA_TYPE_FDOUBLE
block|,
DECL|enumerator|FITS_DATA_TYPE_FSTRING
name|FITS_DATA_TYPE_FSTRING
DECL|typedef|FitsDataType
block|}
name|FitsDataType
typedef|;
end_typedef

begin_typedef
typedef|typedef
union|union
DECL|union|__anon2c52e8d1020a
block|{
DECL|member|bitpix8
name|FitsBitpix8
name|bitpix8
decl_stmt|;
DECL|member|bitpix16
name|FitsBitpix16
name|bitpix16
decl_stmt|;
DECL|member|bitpix32
name|FitsBitpix32
name|bitpix32
decl_stmt|;
DECL|member|bitpixm32
name|FitsBitpixM32
name|bitpixm32
decl_stmt|;
DECL|member|bitpixm64
name|FitsBitpixM64
name|bitpixm64
decl_stmt|;
DECL|member|fbool
name|FitsBool
name|fbool
decl_stmt|;
DECL|member|flong
name|FitsLong
name|flong
decl_stmt|;
DECL|member|fdouble
name|FitsDouble
name|fdouble
decl_stmt|;
DECL|member|fstring
name|FitsString
name|fstring
decl_stmt|;
DECL|typedef|FitsData
block|}
name|FitsData
typedef|;
end_typedef

begin_comment
comment|/* How to transform FITS pixel values */
end_comment

begin_typedef
DECL|typedef|FitsPixTransform
typedef|typedef
name|struct
name|_FitsPixTransform
name|FitsPixTransform
typedef|;
end_typedef

begin_struct
DECL|struct|_FitsPixTransform
struct|struct
name|_FitsPixTransform
block|{
DECL|member|pixmin
DECL|member|pixmax
name|gdouble
name|pixmin
decl_stmt|,
name|pixmax
decl_stmt|;
comment|/* Pixel values [pixmin,pixmax] should be mapped */
DECL|member|datamin
DECL|member|datamax
name|gdouble
name|datamin
decl_stmt|,
name|datamax
decl_stmt|;
comment|/* to [datamin,datamax] */
DECL|member|replacement
name|gdouble
name|replacement
decl_stmt|;
comment|/* datavalue to use for blank or NaN pixels */
DECL|member|dsttyp
name|gchar
name|dsttyp
decl_stmt|;
comment|/* Destination typ ('c' = char) */
block|}
struct|;
end_struct

begin_comment
comment|/* Record list */
end_comment

begin_typedef
DECL|typedef|FitsRecordList
typedef|typedef
name|struct
name|_FitsRecordList
name|FitsRecordList
typedef|;
end_typedef

begin_struct
DECL|struct|_FitsRecordList
struct|struct
name|_FitsRecordList
block|{
DECL|member|data
name|gchar
name|data
index|[
name|FITS_RECORD_SIZE
index|]
decl_stmt|;
DECL|member|next_record
name|FitsRecordList
modifier|*
name|next_record
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Header and Data Unit List */
end_comment

begin_typedef
DECL|typedef|FitsHduList
typedef|typedef
name|struct
name|_FitsHduList
name|FitsHduList
typedef|;
end_typedef

begin_struct
DECL|struct|_FitsHduList
struct|struct
name|_FitsHduList
block|{
DECL|member|header_offset
name|glong
name|header_offset
decl_stmt|;
comment|/* Offset of header in the file */
DECL|member|data_offset
name|glong
name|data_offset
decl_stmt|;
comment|/* Offset of data in the file */
DECL|member|data_size
name|glong
name|data_size
decl_stmt|;
comment|/* Size of data in the HDU (including pad)*/
DECL|member|udata_size
name|glong
name|udata_size
decl_stmt|;
comment|/* Size of used data in the HDU (excl. pad) */
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
comment|/* Bytes per pixel */
DECL|member|numpic
name|gint
name|numpic
decl_stmt|;
comment|/* Number of interpretable images in HDU */
DECL|member|naddcards
name|gint
name|naddcards
decl_stmt|;
comment|/* Number of additional cards */
DECL|member|addcards
name|gchar
name|addcards
index|[
name|FITS_NADD_CARDS
index|]
index|[
name|FITS_CARD_SIZE
index|]
decl_stmt|;
struct|struct
DECL|struct|__anon2c52e8d10308
block|{
DECL|member|nan_value
name|gboolean
name|nan_value
decl_stmt|;
comment|/* NaN's found in data ? */
DECL|member|blank_value
name|gboolean
name|blank_value
decl_stmt|;
comment|/* Blanks found in data ? */
comment|/* Flags specifying if some cards are used */
DECL|member|blank
name|gchar
name|blank
decl_stmt|;
comment|/* The corresponding data below is only */
DECL|member|datamin
name|gchar
name|datamin
decl_stmt|;
comment|/* valid, if the flag is set. */
DECL|member|datamax
name|gchar
name|datamax
decl_stmt|;
DECL|member|simple
name|gchar
name|simple
decl_stmt|;
comment|/* This indicates a simple HDU */
DECL|member|xtension
name|gchar
name|xtension
decl_stmt|;
comment|/* This indicates an extension */
DECL|member|gcount
name|gchar
name|gcount
decl_stmt|;
DECL|member|pcount
name|gchar
name|pcount
decl_stmt|;
DECL|member|bzero
name|gchar
name|bzero
decl_stmt|;
DECL|member|bscale
name|gchar
name|bscale
decl_stmt|;
DECL|member|groups
name|gchar
name|groups
decl_stmt|;
DECL|member|extend
name|gchar
name|extend
decl_stmt|;
DECL|member|used
block|}
name|used
struct|;
DECL|member|pixmin
DECL|member|pixmax
name|gdouble
name|pixmin
decl_stmt|,
name|pixmax
decl_stmt|;
comment|/* Minimum/Maximum pixel values */
comment|/* Some decoded data of the HDU: */
DECL|member|naxis
name|gint
name|naxis
decl_stmt|;
comment|/* Number of axes */
DECL|member|naxisn
name|gint
name|naxisn
index|[
name|FITS_MAX_AXIS
index|]
decl_stmt|;
comment|/* Sizes of axes (NAXIS1 --> naxisn[0]) */
DECL|member|bitpix
name|gint
name|bitpix
decl_stmt|;
comment|/* Data representation (8,16,32,-16,-32) */
comment|/* When using the following data, */
comment|/* the used-flags must be checked before. */
DECL|member|blank
name|glong
name|blank
decl_stmt|;
comment|/* Blank value */
DECL|member|datamin
DECL|member|datamax
name|gdouble
name|datamin
decl_stmt|,
name|datamax
decl_stmt|;
comment|/* Minimum/Maximum physical data values */
DECL|member|xtension
name|gchar
name|xtension
index|[
name|FITS_CARD_SIZE
index|]
decl_stmt|;
comment|/* Type of extension */
DECL|member|gcount
DECL|member|pcount
name|glong
name|gcount
decl_stmt|,
name|pcount
decl_stmt|;
comment|/* Used by XTENSION */
DECL|member|bzero
DECL|member|bscale
name|gdouble
name|bzero
decl_stmt|,
name|bscale
decl_stmt|;
comment|/* Transformation values */
DECL|member|groups
name|gint
name|groups
decl_stmt|;
comment|/* Random groups indicator */
DECL|member|extend
name|gint
name|extend
decl_stmt|;
comment|/* Extend flag */
DECL|member|header_record_list
name|FitsRecordList
modifier|*
name|header_record_list
decl_stmt|;
comment|/* Header records read in */
DECL|member|next_hdu
name|FitsHduList
modifier|*
name|next_hdu
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|FitsFile
typedef|typedef
name|struct
name|_FitsFile
name|FitsFile
typedef|;
end_typedef

begin_struct
DECL|struct|_FitsFile
struct|struct
name|_FitsFile
block|{
DECL|member|fp
name|FILE
modifier|*
name|fp
decl_stmt|;
comment|/* File pointer to fits file */
DECL|member|openmode
name|gchar
name|openmode
decl_stmt|;
comment|/* Mode the file was opened (0, 'r', 'w') */
DECL|member|n_hdu
name|gint
name|n_hdu
decl_stmt|;
comment|/* Number of HDUs in file */
DECL|member|n_pic
name|gint
name|n_pic
decl_stmt|;
comment|/* Total number of interpretable pictures */
DECL|member|nan_used
name|gboolean
name|nan_used
decl_stmt|;
comment|/* NaN's used in the file ? */
DECL|member|blank_used
name|gboolean
name|blank_used
decl_stmt|;
comment|/* Blank's used in the file ? */
DECL|member|hdu_list
name|FitsHduList
modifier|*
name|hdu_list
decl_stmt|;
comment|/* Header and Data Unit List */
block|}
struct|;
end_struct

begin_comment
comment|/* User callable functions of the FITS-library */
end_comment

begin_function_decl
name|FitsFile
modifier|*
name|fits_open
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|openmode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fits_close
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FitsHduList
modifier|*
name|fits_add_hdu
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|fits_add_card
parameter_list|(
name|FitsHduList
modifier|*
name|hdulist
parameter_list|,
specifier|const
name|gchar
modifier|*
name|card
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|fits_write_header
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|,
name|FitsHduList
modifier|*
name|hdulist
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FitsHduList
modifier|*
name|fits_image_info
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|,
name|gint
name|picind
parameter_list|,
name|gint
modifier|*
name|hdupicind
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FitsHduList
modifier|*
name|fits_seek_image
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|,
name|gint
name|picind
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fits_print_header
parameter_list|(
name|FitsHduList
modifier|*
name|hdr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FitsData
modifier|*
name|fits_decode_card
parameter_list|(
specifier|const
name|gchar
modifier|*
name|card
parameter_list|,
name|FitsDataType
name|data_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|fits_search_card
parameter_list|(
name|FitsRecordList
modifier|*
name|rl
parameter_list|,
name|gchar
modifier|*
name|keyword
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|fits_read_pixel
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|,
name|FitsHduList
modifier|*
name|hdulist
parameter_list|,
name|gint
name|npix
parameter_list|,
name|FitsPixTransform
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
name|gchar
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
name|gint
name|fits_to_pgmraw
parameter_list|(
name|gchar
modifier|*
name|fitsfile
parameter_list|,
name|gchar
modifier|*
name|pgmfile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|pgmraw_to_fits
parameter_list|(
name|gchar
modifier|*
name|pgmfile
parameter_list|,
name|gchar
modifier|*
name|fitsfile
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FITS_IO_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/******************************************************************************/
end_comment

begin_comment
comment|/*                      Peter Kirchgessner                                    */
end_comment

begin_comment
comment|/*                      e-mail: peter@kirchgessner.net                        */
end_comment

begin_comment
comment|/*                      WWW   : http://www.kirchgessner.net                   */
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
comment|/*  Modul-Name    : fitsrw.c                                                  */
end_comment

begin_comment
comment|/*  Description   : Support of reading/writing FITS-files                     */
end_comment

begin_comment
comment|/*  Function(s)   : fits_new_filestruct    - (local) initialize file structure*/
end_comment

begin_comment
comment|/*                  fits_new_hdulist       - (local) initialize hdulist struct*/
end_comment

begin_comment
comment|/*                  fits_delete_filestruct - (local) delete file structure    */
end_comment

begin_comment
comment|/*                  fits_delete_recordlist - (local) delete record list       */
end_comment

begin_comment
comment|/*                  fits_delete_hdulist    - (local) delete hdu list          */
end_comment

begin_comment
comment|/*                  fits_nan_32            - (local) check IEEE NaN values    */
end_comment

begin_comment
comment|/*                  fits_nan_64            - (local) check IEEE NaN values    */
end_comment

begin_comment
comment|/*                  fits_get_error         - get error message                */
end_comment

begin_comment
comment|/*                  fits_set_error         - (local) set error message        */
end_comment

begin_comment
comment|/*                  fits_drop_error        - (local) remove an error message  */
end_comment

begin_comment
comment|/*                  fits_open              - open a FITS file                 */
end_comment

begin_comment
comment|/*                  fits_close             - close a FITS file                */
end_comment

begin_comment
comment|/*                  fits_add_hdu           - add a HDU to a FITS file         */
end_comment

begin_comment
comment|/*                  fits_add_card          - add a card to the HDU            */
end_comment

begin_comment
comment|/*                  fits_print_header      - print a single FITS header       */
end_comment

begin_comment
comment|/*                  fits_read_header       - (local) read in FITS header      */
end_comment

begin_comment
comment|/*                  fits_write_header      - write a FITS header              */
end_comment

begin_comment
comment|/*                  fits_decode_header     - (local) decode a header          */
end_comment

begin_comment
comment|/*                  fits_eval_pixrange     - (local) evaluate range of pixels */
end_comment

begin_comment
comment|/*                  fits_decode_card       - decode a card                    */
end_comment

begin_comment
comment|/*                  fits_search_card       - search a card in a record list   */
end_comment

begin_comment
comment|/*                  fits_image_info        - get information about image      */
end_comment

begin_comment
comment|/*                  fits_seek_image        - position to an image             */
end_comment

begin_comment
comment|/*                  fits_read_pixel        - read pixel values from file      */
end_comment

begin_comment
comment|/*                  fits_to_pgmraw         - convert FITS-file to PGM-file    */
end_comment

begin_comment
comment|/*                  pgmraw_to_fits         - convert PGM-file to FITS-file    */
end_comment

begin_comment
comment|/*                                                                            */
end_comment

begin_comment
comment|/*  Author        : P. Kirchgessner                                           */
end_comment

begin_comment
comment|/*  Date of Gen.  : 12-Apr-97                                                 */
end_comment

begin_comment
comment|/*  Last modified : 25-Aug-06                                                 */
end_comment

begin_comment
comment|/*  Version       : 0.12                                                      */
end_comment

begin_comment
comment|/*  Compiler Opt. :                                                           */
end_comment

begin_comment
comment|/*  Changes       :                                                           */
end_comment

begin_comment
comment|/*  #MOD-0001, nn, 20-Dec-97, Initialize some variables                       */
end_comment

begin_comment
comment|/*  #MOD-0002, pk, 16-Aug-06, Fix problems with internationalization          */
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

begin_comment
comment|/*  References:                                                               */
end_comment

begin_comment
comment|/*  - NOST, Definition of the Flexible Image Transport System (FITS),         */
end_comment

begin_comment
comment|/*    September 29, 1995, Standard, NOST 100-1.1                              */
end_comment

begin_comment
comment|/*    (ftp://nssdc.gsfc.nasa.gov/pub/fits/fits_standard_ps.Z)                 */
end_comment

begin_comment
comment|/*  - The FITS IMAGE Extension. A Proposal. J.D. Ponz, R.W. Thompson,         */
end_comment

begin_comment
comment|/*    J.R. Munoz, Feb. 7, 1992                                                */
end_comment

begin_comment
comment|/*    (ftp://www.cv.nrao.edu/fits/documents/standards/image.ps.gz)            */
end_comment

begin_comment
comment|/*                                                                            */
end_comment

begin_comment
comment|/******************************************************************************/
end_comment

begin_define
DECL|macro|VERSIO
define|#
directive|define
name|VERSIO
value|0.12
end_define

begin_comment
comment|/******************************************************************************/
end_comment

begin_comment
comment|/* FITS reading/writing library                                               */
end_comment

begin_comment
comment|/* Copyright (C) 1997 Peter Kirchgessner                                      */
end_comment

begin_comment
comment|/* (email: peter@kirchgessner.net, WWW: http://www.kirchgessner.net)          */
end_comment

begin_comment
comment|/* The library was developed for a FITS-plug-in to GIMP, the GNU Image        */
end_comment

begin_comment
comment|/* Manipulation Program. But it is completely independent to that (beside use */
end_comment

begin_comment
comment|/* of glib). If someone finds it useful for other purposes, try to keep it    */
end_comment

begin_comment
comment|/* independent from your application.                                         */
end_comment

begin_comment
comment|/******************************************************************************/
end_comment

begin_comment
comment|/*                                                                            */
end_comment

begin_comment
comment|/* This program is free software: you can redistribute it and/or modify       */
end_comment

begin_comment
comment|/* it under the terms of the GNU General Public License as published by       */
end_comment

begin_comment
comment|/* the Free Software Foundation; either version 3 of the License, or          */
end_comment

begin_comment
comment|/* (at your option) any later version.                                        */
end_comment

begin_comment
comment|/*                                                                            */
end_comment

begin_comment
comment|/* This program is distributed in the hope that it will be useful,            */
end_comment

begin_comment
comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
end_comment

begin_comment
comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              */
end_comment

begin_comment
comment|/* GNU General Public License for more details.                               */
end_comment

begin_comment
comment|/*                                                                            */
end_comment

begin_comment
comment|/* You should have received a copy of the GNU General Public License          */
end_comment

begin_comment
comment|/* along with this program.  If not, see<http://www.gnu.org/licenses/>.      */
end_comment

begin_comment
comment|/******************************************************************************/
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"fits-io.h"
end_include

begin_comment
comment|/* Declaration of local functions */
end_comment

begin_function_decl
specifier|static
name|FitsFile
modifier|*
name|fits_new_filestruct
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|FitsHduList
modifier|*
name|fits_new_hdulist
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fits_delete_filestruct
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fits_delete_recordlist
parameter_list|(
name|FitsRecordList
modifier|*
name|rl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fits_delete_hdulist
parameter_list|(
name|FitsHduList
modifier|*
name|hl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|fits_nan_32
parameter_list|(
name|guchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|fits_nan_64
parameter_list|(
name|guchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fits_set_error
parameter_list|(
specifier|const
name|char
modifier|*
name|errmsg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fits_drop_error
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|FitsRecordList
modifier|*
name|fits_read_header
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|,
name|gint
modifier|*
name|nrec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|FitsHduList
modifier|*
name|fits_decode_header
parameter_list|(
name|FitsRecordList
modifier|*
name|hdr
parameter_list|,
name|glong
name|hdr_offset
parameter_list|,
name|glong
name|dat_offset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|fits_eval_pixrange
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|,
name|FitsHduList
modifier|*
name|hdu
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Error handling like a FIFO */
end_comment

begin_define
DECL|macro|FITS_MAX_ERROR
define|#
directive|define
name|FITS_MAX_ERROR
value|16
end_define

begin_define
DECL|macro|FITS_ERROR_LENGTH
define|#
directive|define
name|FITS_ERROR_LENGTH
value|256
end_define

begin_decl_stmt
DECL|variable|fits_n_error
specifier|static
name|gint
name|fits_n_error
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fits_error
specifier|static
name|gchar
name|fits_error
index|[
name|FITS_MAX_ERROR
index|]
index|[
name|FITS_ERROR_LENGTH
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* What byte ordering for IEEE-format we are running on ? */
end_comment

begin_decl_stmt
DECL|variable|fits_ieee32_intel
specifier|static
name|gint
name|fits_ieee32_intel
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fits_ieee32_motorola
specifier|static
name|gint
name|fits_ieee32_motorola
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fits_ieee64_intel
specifier|static
name|gint
name|fits_ieee64_intel
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fits_ieee64_motorola
specifier|static
name|gint
name|fits_ieee64_motorola
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Macros */
end_comment

begin_define
DECL|macro|FITS_RETURN (msg,val)
define|#
directive|define
name|FITS_RETURN
parameter_list|(
name|msg
parameter_list|,
name|val
parameter_list|)
value|{ fits_set_error (msg); return (val); }
end_define

begin_define
DECL|macro|FITS_VRETURN (msg)
define|#
directive|define
name|FITS_VRETURN
parameter_list|(
name|msg
parameter_list|)
value|{ fits_set_error (msg); return; }
end_define

begin_comment
comment|/* Get pixel values from memory. p must be an (guchar *) */
end_comment

begin_define
DECL|macro|FITS_GETBITPIX16 (p,val)
define|#
directive|define
name|FITS_GETBITPIX16
parameter_list|(
name|p
parameter_list|,
name|val
parameter_list|)
value|val = ((p[0]<< 8) | (p[1]))
end_define

begin_define
DECL|macro|FITS_GETBITPIX32 (p,val)
define|#
directive|define
name|FITS_GETBITPIX32
parameter_list|(
name|p
parameter_list|,
name|val
parameter_list|)
value|val = \           ((p[0]<< 24) | (p[1]<< 16) | (p[2]<< 8) | p[3])
end_define

begin_comment
comment|/* Get floating point values from memory. p must be an (guchar *). */
end_comment

begin_comment
comment|/* The floating point values must directly correspond */
end_comment

begin_comment
comment|/* to machine representation. Otherwise it does not work. */
end_comment

begin_define
DECL|macro|FITS_GETBITPIXM32 (p,val)
define|#
directive|define
name|FITS_GETBITPIXM32
parameter_list|(
name|p
parameter_list|,
name|val
parameter_list|)
define|\
value|{ if (fits_ieee32_intel) {guchar uc[4]; \    uc[0] = p[3]; uc[1] = p[2]; uc[2] = p[1]; uc[3] = p[0]; \    val = *(FitsBitpixM32 *)uc; } \    else if (fits_ieee32_motorola) { val = *(FitsBitpixM32 *)p; } \    else if (fits_ieee64_motorola) {FitsBitpixM64 m64; \    guchar *uc= (guchar *)&m64; \    uc[0]=p[0]; uc[1]=p[1]; uc[2]=p[2]; uc[3]=p[3]; uc[4]=uc[5]=uc[6]=uc[7]=0; \    val = (FitsBitpixM32)m64; } \    else if (fits_ieee64_intel) {FitsBitpixM64 i64; \    guchar *uc= (guchar *)&i64; \    uc[0]=uc[1]=uc[2]=uc[3]=0; uc[7]=p[0]; uc[6]=p[1]; uc[5]=p[2]; uc[4]=p[3]; \    val = (FitsBitpixM32)i64;} }
end_define

begin_define
DECL|macro|FITS_GETBITPIXM64 (p,val)
define|#
directive|define
name|FITS_GETBITPIXM64
parameter_list|(
name|p
parameter_list|,
name|val
parameter_list|)
define|\
value|{ if (fits_ieee64_intel) {guchar uc[8]; \    uc[0] = p[7]; uc[1] = p[6]; uc[2] = p[5]; uc[3] = p[4]; \    uc[4] = p[3]; uc[5] = p[2]; uc[6] = p[1]; uc[7] = p[0]; \    val = *(FitsBitpixM64 *)uc; } else val = *(FitsBitpixM64 *)p; }
end_define

begin_define
DECL|macro|FITS_WRITE_BOOLCARD (fp,key,value)
define|#
directive|define
name|FITS_WRITE_BOOLCARD
parameter_list|(
name|fp
parameter_list|,
name|key
parameter_list|,
name|value
parameter_list|)
define|\
value|{ gchar card[81]; \   g_snprintf (card, sizeof (card), \               "%-8.8s= %20s%50s", key, value ? "T" : "F", " "); \   fwrite (card, 1, 80, fp); }
end_define

begin_define
DECL|macro|FITS_WRITE_LONGCARD (fp,key,value)
define|#
directive|define
name|FITS_WRITE_LONGCARD
parameter_list|(
name|fp
parameter_list|,
name|key
parameter_list|,
name|value
parameter_list|)
define|\
value|{ gchar card[81]; \   g_snprintf (card, sizeof (card), \               "%-8.8s= %20ld%50s", key, (long)value, " "); \   fwrite (card, 1, 80, fp); }
end_define

begin_define
DECL|macro|FITS_WRITE_DOUBLECARD (fp,key,value)
define|#
directive|define
name|FITS_WRITE_DOUBLECARD
parameter_list|(
name|fp
parameter_list|,
name|key
parameter_list|,
name|value
parameter_list|)
define|\
value|{ gchar card[81], dbl[21], *istr; \   g_ascii_formatd (dbl, sizeof(dbl), "%f", (gdouble)value); \   istr = strstr (dbl, "e"); \   if (istr) *istr = 'E'; \   g_snprintf (card, sizeof (card), \               "%-8.8s= %20.20s%50s", key, dbl, " "); \   fwrite (card, 1, 80, fp); }
end_define

begin_define
DECL|macro|FITS_WRITE_STRINGCARD (fp,key,value)
define|#
directive|define
name|FITS_WRITE_STRINGCARD
parameter_list|(
name|fp
parameter_list|,
name|key
parameter_list|,
name|value
parameter_list|)
define|\
value|{ gchar card[81]; int k;\   g_snprintf (card, sizeof (card), \               "%-8.8s= \'%s", key, value); \   for (k = strlen (card); k< 81; k++) card[k] = ' '; \   k = strlen (key); if (k< 8) card[19] = '\''; else card[11+k] = '\''; \   fwrite (card, 1, 80, fp); }
end_define

begin_define
DECL|macro|FITS_WRITE_CARD (fp,value)
define|#
directive|define
name|FITS_WRITE_CARD
parameter_list|(
name|fp
parameter_list|,
name|value
parameter_list|)
define|\
value|{ gchar card[81]; \   g_snprintf (card, sizeof (card), \               "%-80.80s", value); \   fwrite (card, 1, 80, fp); }
end_define

begin_comment
comment|/* Macro to convert a double value to a string using '.' as decimal point */
end_comment

begin_define
DECL|macro|FDTOSTR (buf,val)
define|#
directive|define
name|FDTOSTR
parameter_list|(
name|buf
parameter_list|,
name|val
parameter_list|)
value|g_ascii_dtostr (buf, sizeof(buf), (gdouble)(val))
end_define

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_scanfdouble - (local) scan a string for a double value   */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* const char *buf  [I] : the string to scan                                 */
end_comment

begin_comment
comment|/* double *value    [O] : where to write the double value to                 */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Scan a string for a double value represented in "C" locale.               */
end_comment

begin_comment
comment|/* On success 1 is returned. On failure 0 is returned.                       */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|fits_scanfdouble (const gchar * buf,gdouble * value)
name|fits_scanfdouble
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buf
parameter_list|,
name|gdouble
modifier|*
name|value
parameter_list|)
block|{
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|bufcopy
init|=
name|g_strdup
argument_list|(
name|buf
argument_list|)
decl_stmt|;
comment|/* We should use g_ascii_strtod. This also allows scanning of hexadecimal */
comment|/* values like 0x02. But we want the behaviour of sscanf ("0x02","%lf",...*/
comment|/* that gives 0.0 in this case. So check the string if we have a hex-value*/
if|if
condition|(
name|bufcopy
condition|)
block|{
name|gchar
modifier|*
name|bufptr
init|=
name|bufcopy
decl_stmt|;
comment|/* Remove leading white space */
name|g_strchug
argument_list|(
name|bufcopy
argument_list|)
expr_stmt|;
comment|/* Skip leading sign character */
if|if
condition|(
operator|(
operator|*
name|bufptr
operator|==
literal|'-'
operator|)
operator|||
operator|(
operator|*
name|bufptr
operator|==
literal|'+'
operator|)
condition|)
name|bufptr
operator|++
expr_stmt|;
comment|/* Start of hex value ? Take this as 0.0 */
if|if
condition|(
operator|(
name|bufptr
index|[
literal|0
index|]
operator|==
literal|'0'
operator|)
operator|&&
operator|(
name|g_ascii_toupper
argument_list|(
name|bufptr
index|[
literal|1
index|]
argument_list|)
operator|==
literal|'X'
operator|)
condition|)
block|{
operator|*
name|value
operator|=
literal|0.0
expr_stmt|;
name|retval
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|*
name|bufptr
operator|==
literal|'.'
condition|)
comment|/* leading decimal point ? Skip it */
name|bufptr
operator|++
expr_stmt|;
if|if
condition|(
name|g_ascii_isdigit
argument_list|(
operator|*
name|bufptr
argument_list|)
condition|)
comment|/* Expect the complete string is decimal */
block|{
name|gchar
modifier|*
name|endptr
decl_stmt|;
name|gdouble
name|gvalue
init|=
name|g_ascii_strtod
argument_list|(
name|bufcopy
argument_list|,
operator|&
name|endptr
argument_list|)
decl_stmt|;
if|if
condition|(
name|errno
operator|==
literal|0
condition|)
block|{
operator|*
name|value
operator|=
name|gvalue
expr_stmt|;
name|retval
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|bufcopy
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_new_filestruct - (local) initialize file structure       */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* -none-                                                                    */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Returns a pointer to an initialized fits file structure.                  */
end_comment

begin_comment
comment|/* On failure, a NULL-pointer is returned.                                   */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|FitsFile
modifier|*
DECL|function|fits_new_filestruct (void)
name|fits_new_filestruct
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_new0
argument_list|(
name|FitsFile
argument_list|,
literal|1
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_new_hdulist    - (local) initialize hdulist structure    */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* -none-                                                                    */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Returns a pointer to an initialized hdulist structure.                    */
end_comment

begin_comment
comment|/* On failure, a NULL-pointer is returned.                                   */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|FitsHduList
modifier|*
DECL|function|fits_new_hdulist (void)
name|fits_new_hdulist
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_new0
argument_list|(
name|FitsHduList
argument_list|,
literal|1
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_delete_filestruct - (local) delete file structure        */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsFile *ff   [I] : pointer to fits file structure                      */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Frees all memory allocated by the file structure.                         */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|fits_delete_filestruct (FitsFile * ff)
name|fits_delete_filestruct
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|)
block|{
if|if
condition|(
name|ff
operator|==
name|NULL
condition|)
return|return;
name|fits_delete_hdulist
argument_list|(
name|ff
operator|->
name|hdu_list
argument_list|)
expr_stmt|;
name|ff
operator|->
name|hdu_list
operator|=
name|NULL
expr_stmt|;
name|g_free
argument_list|(
name|ff
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_delete_recordlist - (local) delete record list           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsRecordList *rl  [I] : record list to delete                         */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|fits_delete_recordlist (FitsRecordList * rl)
name|fits_delete_recordlist
parameter_list|(
name|FitsRecordList
modifier|*
name|rl
parameter_list|)
block|{
while|while
condition|(
name|rl
operator|!=
name|NULL
condition|)
block|{
name|FitsRecordList
modifier|*
name|next
decl_stmt|;
name|next
operator|=
name|rl
operator|->
name|next_record
expr_stmt|;
name|rl
operator|->
name|next_record
operator|=
name|NULL
expr_stmt|;
name|g_free
argument_list|(
name|rl
argument_list|)
expr_stmt|;
name|rl
operator|=
name|next
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_delete_hdulist - (local) delete hdu list                 */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsHduList *hl  [I] : hdu list to delete                               */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|fits_delete_hdulist (FitsHduList * hl)
name|fits_delete_hdulist
parameter_list|(
name|FitsHduList
modifier|*
name|hl
parameter_list|)
block|{
while|while
condition|(
name|hl
operator|!=
name|NULL
condition|)
block|{
name|FitsHduList
modifier|*
name|next
decl_stmt|;
name|fits_delete_recordlist
argument_list|(
name|hl
operator|->
name|header_record_list
argument_list|)
expr_stmt|;
name|next
operator|=
name|hl
operator|->
name|next_hdu
expr_stmt|;
name|hl
operator|->
name|next_hdu
operator|=
name|NULL
expr_stmt|;
name|g_free
argument_list|(
name|hl
argument_list|)
expr_stmt|;
name|hl
operator|=
name|next
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_nan_32 - (local) check for IEEE NaN values (32 bit)      */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* unsigned char *v     [I] : value to check                                 */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function returns 1 if the value is a NaN. Otherwise 0 is returned.    */
end_comment

begin_comment
comment|/* The byte sequence at v must start with the sign/eponent byte.             */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|int
DECL|function|fits_nan_32 (guchar * v)
name|fits_nan_32
parameter_list|(
name|guchar
modifier|*
name|v
parameter_list|)
block|{
specifier|register
name|gulong
name|k
decl_stmt|;
name|k
operator|=
operator|(
name|v
index|[
literal|0
index|]
operator|<<
literal|24
operator|)
operator||
operator|(
name|v
index|[
literal|1
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|v
index|[
literal|2
index|]
operator|<<
literal|8
operator|)
operator||
name|v
index|[
literal|3
index|]
expr_stmt|;
name|k
operator|&=
literal|0x7fffffff
expr_stmt|;
comment|/* Dont care about the sign bit */
comment|/* See NOST Definition of the Flexible Image Transport System (FITS), */
comment|/* Appendix F, IEEE special formats. */
return|return
operator|(
operator|(
operator|(
name|k
operator|>=
literal|0x7f7fffff
operator|)
operator|&&
operator|(
name|k
operator|<=
literal|0x7fffffff
operator|)
operator|)
operator|||
operator|(
operator|(
name|k
operator|>=
literal|0x00000001
operator|)
operator|&&
operator|(
name|k
operator|<=
literal|0x00800000
operator|)
operator|)
operator|)
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_nan_64 - (local) check for IEEE NaN values (64 bit)      */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* unsigned char *v     [I] : value to check                                 */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function returns 1 if the value is a NaN. Otherwise 0 is returned.    */
end_comment

begin_comment
comment|/* The byte sequence at v must start with the sign/eponent byte.             */
end_comment

begin_comment
comment|/* (currently we ignore the low order 4 bytes of the mantissa. Therefore     */
end_comment

begin_comment
comment|/* this function is the same as for 32 bits).                                */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|int
DECL|function|fits_nan_64 (guchar * v)
name|fits_nan_64
parameter_list|(
name|guchar
modifier|*
name|v
parameter_list|)
block|{
specifier|register
name|gulong
name|k
decl_stmt|;
name|k
operator|=
operator|(
name|v
index|[
literal|0
index|]
operator|<<
literal|24
operator|)
operator||
operator|(
name|v
index|[
literal|1
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|v
index|[
literal|2
index|]
operator|<<
literal|8
operator|)
operator||
name|v
index|[
literal|3
index|]
expr_stmt|;
name|k
operator|&=
literal|0x7fffffff
expr_stmt|;
comment|/* Dont care about the sign bit */
comment|/* See NOST Definition of the Flexible Image Transport System (FITS), */
comment|/* Appendix F, IEEE special formats. */
return|return
operator|(
operator|(
operator|(
name|k
operator|>=
literal|0x7f7fffff
operator|)
operator|&&
operator|(
name|k
operator|<=
literal|0x7fffffff
operator|)
operator|)
operator|||
operator|(
operator|(
name|k
operator|>=
literal|0x00000001
operator|)
operator|&&
operator|(
name|k
operator|<=
literal|0x00800000
operator|)
operator|)
operator|)
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_get_error - get an error message                         */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* -none-                                                                    */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* If an error message has been set, a pointer to the message is returned.   */
end_comment

begin_comment
comment|/* Otherwise a NULL pointer is returned.                                     */
end_comment

begin_comment
comment|/* An inquired error message is removed from the error FIFO.                 */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|fits_get_error (void)
name|fits_get_error
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
name|errmsg
index|[
name|FITS_ERROR_LENGTH
index|]
decl_stmt|;
name|gint
name|k
decl_stmt|;
if|if
condition|(
name|fits_n_error
operator|<=
literal|0
condition|)
return|return
name|NULL
return|;
name|strcpy
argument_list|(
name|errmsg
argument_list|,
name|fits_error
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|1
init|;
name|k
operator|<
name|fits_n_error
condition|;
name|k
operator|++
control|)
name|strcpy
argument_list|(
name|fits_error
index|[
name|k
operator|-
literal|1
index|]
argument_list|,
name|fits_error
index|[
name|k
index|]
argument_list|)
expr_stmt|;
name|fits_n_error
operator|--
expr_stmt|;
return|return
name|errmsg
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_set_error - (local) set an error message                 */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* char *errmsg   [I] : Error message to set                                 */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Places the error message in the FIFO. If the FIFO is full,                */
end_comment

begin_comment
comment|/* the message is discarded.                                                 */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|fits_set_error (const gchar * errmsg)
name|fits_set_error
parameter_list|(
specifier|const
name|gchar
modifier|*
name|errmsg
parameter_list|)
block|{
if|if
condition|(
name|fits_n_error
operator|<
name|FITS_MAX_ERROR
condition|)
block|{
name|strncpy
argument_list|(
name|fits_error
index|[
name|fits_n_error
index|]
argument_list|,
name|errmsg
argument_list|,
name|FITS_ERROR_LENGTH
argument_list|)
expr_stmt|;
name|fits_error
index|[
name|fits_n_error
operator|++
index|]
index|[
name|FITS_ERROR_LENGTH
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_drop_error - (local) remove an error message             */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* -none-                                                                    */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Removes the last error message from the error message FIFO                */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|fits_drop_error (void)
name|fits_drop_error
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|fits_n_error
operator|>
literal|0
condition|)
name|fits_n_error
operator|--
expr_stmt|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_open - open a FITS file                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* char *filename   [I] : name of file to open                               */
end_comment

begin_comment
comment|/* char *openmode   [I] : mode to open the file ("r", "w")                   */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* On success, a FitsFile-pointer is returned. On failure, a NULL-          */
end_comment

begin_comment
comment|/* pointer is returned.                                                      */
end_comment

begin_comment
comment|/* The functions scans through the file loading each header and analyzing    */
end_comment

begin_comment
comment|/* them.                                                                     */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|FitsFile
modifier|*
DECL|function|fits_open (const gchar * filename,const gchar * openmode)
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
block|{
name|gint
name|reading
decl_stmt|,
name|writing
decl_stmt|,
name|n_rec
decl_stmt|,
name|n_hdr
decl_stmt|;
name|glong
name|fpos_header
decl_stmt|,
name|fpos_data
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|FitsFile
modifier|*
name|ff
decl_stmt|;
name|FitsRecordList
modifier|*
name|hdrlist
decl_stmt|;
name|FitsHduList
modifier|*
name|hdulist
init|=
name|NULL
decl_stmt|;
name|FitsHduList
modifier|*
name|last_hdulist
init|=
name|NULL
decl_stmt|;
comment|/* Check the IEEE-format we are running on */
block|{
name|gfloat
name|one32
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|one64
init|=
literal|1.0
decl_stmt|;
name|guchar
modifier|*
name|op32
init|=
operator|(
name|guchar
operator|*
operator|)
operator|&
name|one32
decl_stmt|;
name|guchar
modifier|*
name|op64
init|=
operator|(
name|guchar
operator|*
operator|)
operator|&
name|one64
decl_stmt|;
if|if
condition|(
sizeof|sizeof
argument_list|(
name|float
argument_list|)
operator|==
literal|4
condition|)
block|{
name|fits_ieee32_intel
operator|=
operator|(
name|op32
index|[
literal|3
index|]
operator|==
literal|0x3f
operator|)
expr_stmt|;
name|fits_ieee32_motorola
operator|=
operator|(
name|op32
index|[
literal|0
index|]
operator|==
literal|0x3f
operator|)
expr_stmt|;
block|}
if|if
condition|(
sizeof|sizeof
argument_list|(
name|double
argument_list|)
operator|==
literal|8
condition|)
block|{
name|fits_ieee64_intel
operator|=
operator|(
name|op64
index|[
literal|7
index|]
operator|==
literal|0x3f
operator|)
expr_stmt|;
name|fits_ieee64_motorola
operator|=
operator|(
name|op64
index|[
literal|0
index|]
operator|==
literal|0x3f
operator|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|filename
operator|==
name|NULL
operator|)
operator|||
operator|(
operator|*
name|filename
operator|==
literal|'\0'
operator|)
operator|||
operator|(
name|openmode
operator|==
name|NULL
operator|)
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_open: Invalid parameters"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|reading
operator|=
operator|(
name|strcmp
argument_list|(
name|openmode
argument_list|,
literal|"r"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
name|writing
operator|=
operator|(
name|strcmp
argument_list|(
name|openmode
argument_list|,
literal|"w"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
operator|(
operator|!
name|reading
operator|)
operator|&&
operator|(
operator|!
name|writing
operator|)
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_open: Invalid openmode"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fp
operator|=
name|g_fopen
argument_list|(
name|filename
argument_list|,
name|reading
condition|?
literal|"rb"
else|:
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
name|fp
operator|==
name|NULL
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_open: fopen() failed"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ff
operator|=
name|fits_new_filestruct
argument_list|()
expr_stmt|;
if|if
condition|(
name|ff
operator|==
name|NULL
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|FITS_RETURN
argument_list|(
literal|"fits_open: No more memory"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|ff
operator|->
name|fp
operator|=
name|fp
expr_stmt|;
name|ff
operator|->
name|openmode
operator|=
operator|*
name|openmode
expr_stmt|;
if|if
condition|(
name|writing
condition|)
return|return
name|ff
return|;
for|for
control|(
name|n_hdr
operator|=
literal|0
init|;
condition|;
name|n_hdr
operator|++
control|)
comment|/* Read through all HDUs */
block|{
name|fpos_header
operator|=
name|ftell
argument_list|(
name|fp
argument_list|)
expr_stmt|;
comment|/* Save file position of header */
name|hdrlist
operator|=
name|fits_read_header
argument_list|(
name|fp
argument_list|,
operator|&
name|n_rec
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdrlist
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|n_hdr
operator|>
literal|0
condition|)
comment|/* At least one header must be present. */
name|fits_drop_error
argument_list|()
expr_stmt|;
comment|/* If we got a header already, drop the error */
break|break;
block|}
name|fpos_data
operator|=
name|ftell
argument_list|(
name|fp
argument_list|)
expr_stmt|;
comment|/* Save file position of data */
comment|/* Decode the header */
name|hdulist
operator|=
name|fits_decode_header
argument_list|(
name|hdrlist
argument_list|,
name|fpos_header
argument_list|,
name|fpos_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdulist
operator|==
name|NULL
condition|)
block|{
name|fits_delete_recordlist
argument_list|(
name|hdrlist
argument_list|)
expr_stmt|;
break|break;
block|}
name|ff
operator|->
name|n_hdu
operator|++
expr_stmt|;
name|ff
operator|->
name|n_pic
operator|+=
name|hdulist
operator|->
name|numpic
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|blank_value
condition|)
name|ff
operator|->
name|blank_used
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|nan_value
condition|)
name|ff
operator|->
name|nan_used
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|n_hdr
operator|==
literal|0
condition|)
name|ff
operator|->
name|hdu_list
operator|=
name|hdulist
expr_stmt|;
else|else
name|last_hdulist
operator|->
name|next_hdu
operator|=
name|hdulist
expr_stmt|;
name|last_hdulist
operator|=
name|hdulist
expr_stmt|;
comment|/* Evaluate the range of pixel data */
name|fits_eval_pixrange
argument_list|(
name|fp
argument_list|,
name|hdulist
argument_list|)
expr_stmt|;
comment|/* Reposition to start of next header */
if|if
condition|(
name|fseek
argument_list|(
name|fp
argument_list|,
name|hdulist
operator|->
name|data_offset
operator|+
name|hdulist
operator|->
name|data_size
argument_list|,
name|SEEK_SET
argument_list|)
operator|<
literal|0
condition|)
break|break;
block|}
return|return
name|ff
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_close - close a FITS file                                */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsFile *ff  [I] : FITS file pointer                                    */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|void
DECL|function|fits_close (FitsFile * ff)
name|fits_close
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|)
block|{
if|if
condition|(
name|ff
operator|==
name|NULL
condition|)
name|FITS_VRETURN
argument_list|(
literal|"fits_close: Invalid parameter"
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|ff
operator|->
name|fp
argument_list|)
expr_stmt|;
name|fits_delete_filestruct
argument_list|(
name|ff
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_add_hdu - add a HDU to the file                          */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsFile *ff  [I] : FITS file pointer                                    */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Adds a new HDU to the list kept in ff. A pointer to the new HDU is        */
end_comment

begin_comment
comment|/* returned. On failure, a NULL-pointer is returned.                         */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|FitsHduList
modifier|*
DECL|function|fits_add_hdu (FitsFile * ff)
name|fits_add_hdu
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|)
block|{
name|FitsHduList
modifier|*
name|newhdu
decl_stmt|,
modifier|*
name|hdu
decl_stmt|;
if|if
condition|(
name|ff
operator|->
name|openmode
operator|!=
literal|'w'
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_add_hdu: file not open for writing"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|newhdu
operator|=
name|fits_new_hdulist
argument_list|()
expr_stmt|;
if|if
condition|(
name|newhdu
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|ff
operator|->
name|hdu_list
operator|==
name|NULL
condition|)
block|{
name|ff
operator|->
name|hdu_list
operator|=
name|newhdu
expr_stmt|;
block|}
else|else
block|{
name|hdu
operator|=
name|ff
operator|->
name|hdu_list
expr_stmt|;
while|while
condition|(
name|hdu
operator|->
name|next_hdu
operator|!=
name|NULL
condition|)
name|hdu
operator|=
name|hdu
operator|->
name|next_hdu
expr_stmt|;
name|hdu
operator|->
name|next_hdu
operator|=
name|newhdu
expr_stmt|;
block|}
return|return
name|newhdu
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_add_card - add a card to the HDU                         */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsHduList *hdulist [I] : HDU listr                                    */
end_comment

begin_comment
comment|/* char *card             [I] : card to add                                  */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The card must follow the standards of FITS. The card must not use a       */
end_comment

begin_comment
comment|/* keyword that is written using *hdulist itself. On success 0 is returned.  */
end_comment

begin_comment
comment|/* On failure -1 is returned.                                                */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|gint
DECL|function|fits_add_card (FitsHduList * hdulist,const gchar * card)
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
block|{
name|gint
name|k
decl_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|naddcards
operator|>=
name|FITS_NADD_CARDS
condition|)
return|return
operator|-
literal|1
return|;
name|k
operator|=
name|strlen
argument_list|(
name|card
argument_list|)
expr_stmt|;
if|if
condition|(
name|k
operator|<
name|FITS_CARD_SIZE
condition|)
block|{
name|memset
argument_list|(
operator|&
operator|(
name|hdulist
operator|->
name|addcards
index|[
name|hdulist
operator|->
name|naddcards
index|]
index|[
name|k
index|]
operator|)
argument_list|,
literal|' '
argument_list|,
name|FITS_CARD_SIZE
operator|-
name|k
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|hdulist
operator|->
name|addcards
index|[
operator|(
name|hdulist
operator|->
name|naddcards
operator|)
operator|++
index|]
argument_list|,
name|card
argument_list|,
name|k
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|memcpy
argument_list|(
name|hdulist
operator|->
name|addcards
index|[
operator|(
name|hdulist
operator|->
name|naddcards
operator|)
operator|++
index|]
argument_list|,
name|card
argument_list|,
name|FITS_CARD_SIZE
argument_list|)
expr_stmt|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_print_header - print the internal representation         */
end_comment

begin_comment
comment|/*                                 of a single header                        */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsHduList *hdr  [I] : pointer to the header                           */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|void
DECL|function|fits_print_header (FitsHduList * hdr)
name|fits_print_header
parameter_list|(
name|FitsHduList
modifier|*
name|hdr
parameter_list|)
block|{
name|gint
name|k
decl_stmt|;
name|gchar
name|buf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|simple
condition|)
name|printf
argument_list|(
literal|"Content of SIMPLE-header:\n"
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"Content of XTENSION-header %s:\n"
argument_list|,
name|hdr
operator|->
name|xtension
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"header_offset : %ld\n"
argument_list|,
name|hdr
operator|->
name|header_offset
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"data_offset   : %ld\n"
argument_list|,
name|hdr
operator|->
name|data_offset
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"data_size     : %ld\n"
argument_list|,
name|hdr
operator|->
name|data_size
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"used data_size: %ld\n"
argument_list|,
name|hdr
operator|->
name|udata_size
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"bytes p.pixel : %d\n"
argument_list|,
name|hdr
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"pixmin        : %s\n"
argument_list|,
name|FDTOSTR
argument_list|(
name|buf
argument_list|,
name|hdr
operator|->
name|pixmin
argument_list|)
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"pixmax        : %s\n"
argument_list|,
name|FDTOSTR
argument_list|(
name|buf
argument_list|,
name|hdr
operator|->
name|pixmax
argument_list|)
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"naxis         : %d\n"
argument_list|,
name|hdr
operator|->
name|naxis
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|1
init|;
name|k
operator|<=
name|hdr
operator|->
name|naxis
condition|;
name|k
operator|++
control|)
name|printf
argument_list|(
literal|"naxis%-3d      : %d\n"
argument_list|,
name|k
argument_list|,
name|hdr
operator|->
name|naxisn
index|[
name|k
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"bitpix        : %d\n"
argument_list|,
name|hdr
operator|->
name|bitpix
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|blank
condition|)
name|printf
argument_list|(
literal|"blank         : %ld\n"
argument_list|,
name|hdr
operator|->
name|blank
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"blank         : not used\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|datamin
condition|)
name|printf
argument_list|(
literal|"datamin       : %s\n"
argument_list|,
name|FDTOSTR
argument_list|(
name|buf
argument_list|,
name|hdr
operator|->
name|datamin
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"datamin       : not used\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|datamax
condition|)
name|printf
argument_list|(
literal|"datamax       : %s\n"
argument_list|,
name|FDTOSTR
argument_list|(
name|buf
argument_list|,
name|hdr
operator|->
name|datamax
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"datamax       : not used\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|gcount
condition|)
name|printf
argument_list|(
literal|"gcount        : %ld\n"
argument_list|,
name|hdr
operator|->
name|gcount
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"gcount        : not used\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|pcount
condition|)
name|printf
argument_list|(
literal|"pcount        : %ld\n"
argument_list|,
name|hdr
operator|->
name|pcount
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"pcount        : not used\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|bscale
condition|)
name|printf
argument_list|(
literal|"bscale        : %s\n"
argument_list|,
name|FDTOSTR
argument_list|(
name|buf
argument_list|,
name|hdr
operator|->
name|bscale
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"bscale        : not used\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdr
operator|->
name|used
operator|.
name|bzero
condition|)
name|printf
argument_list|(
literal|"bzero         : %s\n"
argument_list|,
name|FDTOSTR
argument_list|(
name|buf
argument_list|,
name|hdr
operator|->
name|bzero
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"bzero         : not used\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_read_header - (local) read FITS header                   */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FILE *fp   [I] : file pointer                                             */
end_comment

begin_comment
comment|/* int  *nrec [O] : number of records read                                   */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Reads in all header records up to the record that keeps the END-card.     */
end_comment

begin_comment
comment|/* A pointer to the record list is returned on success.                      */
end_comment

begin_comment
comment|/* On failure, a NULL-pointer is returned.                                   */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|FitsRecordList
modifier|*
DECL|function|fits_read_header (FILE * fp,gint * nrec)
name|fits_read_header
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|,
name|gint
modifier|*
name|nrec
parameter_list|)
block|{
name|gchar
name|record
index|[
name|FITS_RECORD_SIZE
index|]
decl_stmt|;
name|FitsRecordList
modifier|*
name|start_list
init|=
name|NULL
decl_stmt|;
name|FitsRecordList
modifier|*
name|cu_record
init|=
name|NULL
decl_stmt|;
name|FitsRecordList
modifier|*
name|new_record
decl_stmt|;
name|FitsData
modifier|*
name|fdat
decl_stmt|;
name|gint
name|k
decl_stmt|,
name|simple
decl_stmt|,
name|xtension
decl_stmt|;
operator|*
name|nrec
operator|=
literal|0
expr_stmt|;
name|k
operator|=
name|fread
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
name|FITS_RECORD_SIZE
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|k
operator|!=
name|FITS_RECORD_SIZE
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_read_header: Error in read of first record"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|simple
operator|=
operator|(
name|strncmp
argument_list|(
name|record
argument_list|,
literal|"SIMPLE  "
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
name|xtension
operator|=
operator|(
name|strncmp
argument_list|(
name|record
argument_list|,
literal|"XTENSION"
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
operator|(
operator|!
name|simple
operator|)
operator|&&
operator|(
operator|!
name|xtension
operator|)
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_read_header: Missing keyword SIMPLE or XTENSION"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|simple
condition|)
block|{
name|fdat
operator|=
name|fits_decode_card
argument_list|(
name|record
argument_list|,
name|FITS_DATA_TYPE_FBOOL
argument_list|)
expr_stmt|;
if|if
condition|(
name|fdat
operator|&&
operator|!
name|fdat
operator|->
name|fbool
condition|)
name|fits_set_error
argument_list|(
literal|"fits_read_header (warning): keyword SIMPLE does not "
literal|"have value T"
argument_list|)
expr_stmt|;
block|}
for|for
control|(
init|;
condition|;
control|)
comment|/* Process all header records */
block|{
name|new_record
operator|=
name|g_new0
argument_list|(
name|FitsRecordList
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|new_record
operator|->
name|data
argument_list|,
name|record
argument_list|,
name|FITS_RECORD_SIZE
argument_list|)
expr_stmt|;
name|new_record
operator|->
name|next_record
operator|=
name|NULL
expr_stmt|;
operator|(
operator|*
name|nrec
operator|)
operator|++
expr_stmt|;
if|if
condition|(
name|start_list
operator|==
name|NULL
condition|)
comment|/* Add new record to the list */
name|start_list
operator|=
name|new_record
expr_stmt|;
else|else
name|cu_record
operator|->
name|next_record
operator|=
name|new_record
expr_stmt|;
name|cu_record
operator|=
name|new_record
expr_stmt|;
comment|/* Was this the last record ? */
if|if
condition|(
name|fits_search_card
argument_list|(
name|cu_record
argument_list|,
literal|"END"
argument_list|)
operator|!=
name|NULL
condition|)
break|break;
name|k
operator|=
name|fread
argument_list|(
name|record
argument_list|,
literal|1
argument_list|,
name|FITS_RECORD_SIZE
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|k
operator|!=
name|FITS_RECORD_SIZE
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_read_header: Error in read of record"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|start_list
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_write_header - write a FITS header                       */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsFile *ff [I] : FITS-file pointer                                     */
end_comment

begin_comment
comment|/* FitsHduList [I] : pointer to header                                     */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Writes a header to the file. On success, 0 is returned. On failure,       */
end_comment

begin_comment
comment|/* -1 is returned.                                                           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|gint
DECL|function|fits_write_header (FitsFile * ff,FitsHduList * hdulist)
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
block|{
name|gint
name|numcards
decl_stmt|;
name|gint
name|k
decl_stmt|;
if|if
condition|(
name|ff
operator|->
name|openmode
operator|!=
literal|'w'
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_write_header: file not open for writing"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|numcards
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|simple
condition|)
block|{
name|FITS_WRITE_BOOLCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"SIMPLE"
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|xtension
condition|)
block|{
name|FITS_WRITE_STRINGCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"XTENSION"
argument_list|,
name|hdulist
operator|->
name|xtension
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
name|FITS_WRITE_LONGCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"BITPIX"
argument_list|,
name|hdulist
operator|->
name|bitpix
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
name|FITS_WRITE_LONGCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"NAXIS"
argument_list|,
name|hdulist
operator|->
name|naxis
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|hdulist
operator|->
name|naxis
condition|;
name|k
operator|++
control|)
block|{
name|gchar
name|naxisn
index|[
literal|16
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|naxisn
argument_list|,
sizeof|sizeof
argument_list|(
name|naxisn
argument_list|)
argument_list|,
literal|"NAXIS%d"
argument_list|,
name|k
operator|+
literal|1
argument_list|)
expr_stmt|;
name|FITS_WRITE_LONGCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
name|naxisn
argument_list|,
name|hdulist
operator|->
name|naxisn
index|[
name|k
index|]
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|extend
condition|)
block|{
name|FITS_WRITE_BOOLCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"EXTEND"
argument_list|,
name|hdulist
operator|->
name|extend
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|groups
condition|)
block|{
name|FITS_WRITE_BOOLCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"GROUPS"
argument_list|,
name|hdulist
operator|->
name|groups
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|pcount
condition|)
block|{
name|FITS_WRITE_LONGCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"PCOUNT"
argument_list|,
name|hdulist
operator|->
name|pcount
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|gcount
condition|)
block|{
name|FITS_WRITE_LONGCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"GCOUNT"
argument_list|,
name|hdulist
operator|->
name|gcount
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|bzero
condition|)
block|{
name|FITS_WRITE_DOUBLECARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"BZERO"
argument_list|,
name|hdulist
operator|->
name|bzero
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|bscale
condition|)
block|{
name|FITS_WRITE_DOUBLECARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"BSCALE"
argument_list|,
name|hdulist
operator|->
name|bscale
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|datamin
condition|)
block|{
name|FITS_WRITE_DOUBLECARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"DATAMIN"
argument_list|,
name|hdulist
operator|->
name|datamin
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|datamax
condition|)
block|{
name|FITS_WRITE_DOUBLECARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"DATAMAX"
argument_list|,
name|hdulist
operator|->
name|datamax
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|blank
condition|)
block|{
name|FITS_WRITE_LONGCARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"BLANK"
argument_list|,
name|hdulist
operator|->
name|blank
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
block|}
comment|/* Write additional cards */
if|if
condition|(
name|hdulist
operator|->
name|naddcards
operator|>
literal|0
condition|)
block|{
name|fwrite
argument_list|(
name|hdulist
operator|->
name|addcards
argument_list|,
name|FITS_CARD_SIZE
argument_list|,
name|hdulist
operator|->
name|naddcards
argument_list|,
name|ff
operator|->
name|fp
argument_list|)
expr_stmt|;
name|numcards
operator|+=
name|hdulist
operator|->
name|naddcards
expr_stmt|;
block|}
name|FITS_WRITE_CARD
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
literal|"END"
argument_list|)
expr_stmt|;
name|numcards
operator|++
expr_stmt|;
name|k
operator|=
operator|(
name|numcards
operator|*
name|FITS_CARD_SIZE
operator|)
operator|%
name|FITS_RECORD_SIZE
expr_stmt|;
if|if
condition|(
name|k
condition|)
comment|/* Must the record be filled up ? */
block|{
while|while
condition|(
name|k
operator|++
operator|<
name|FITS_RECORD_SIZE
condition|)
name|putc
argument_list|(
literal|' '
argument_list|,
name|ff
operator|->
name|fp
argument_list|)
expr_stmt|;
block|}
return|return
name|ferror
argument_list|(
name|ff
operator|->
name|fp
argument_list|)
condition|?
operator|-
literal|1
else|:
literal|0
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_decode_header - (local) decode a header                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsRecordList *hdr  [I] : the header record list                       */
end_comment

begin_comment
comment|/* long hdr_offset        [I] : fileposition of header                       */
end_comment

begin_comment
comment|/* long dat_offset        [I] : fileposition of data (end of header)         */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function decodes the mostly used data within the header and generates */
end_comment

begin_comment
comment|/* a FitsHduList-entry. On failure, a NULL-pointer is returned.            */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|FitsHduList
modifier|*
DECL|function|fits_decode_header (FitsRecordList * hdr,glong hdr_offset,glong dat_offset)
name|fits_decode_header
parameter_list|(
name|FitsRecordList
modifier|*
name|hdr
parameter_list|,
name|glong
name|hdr_offset
parameter_list|,
name|glong
name|dat_offset
parameter_list|)
block|{
name|FitsHduList
modifier|*
name|hdulist
decl_stmt|;
name|FitsData
modifier|*
name|fdat
decl_stmt|;
name|gchar
name|errmsg
index|[
literal|80
index|]
decl_stmt|,
name|key
index|[
literal|9
index|]
decl_stmt|;
name|gint
name|k
decl_stmt|,
name|bpp
decl_stmt|,
name|random_groups
decl_stmt|;
name|glong
name|mul_axis
decl_stmt|,
name|data_size
decl_stmt|,
name|bitpix_supported
decl_stmt|;
DECL|macro|FITS_DECODE_CARD (mhdr,mkey,mfdat,mtyp)
define|#
directive|define
name|FITS_DECODE_CARD
parameter_list|(
name|mhdr
parameter_list|,
name|mkey
parameter_list|,
name|mfdat
parameter_list|,
name|mtyp
parameter_list|)
define|\
value|{ strcpy (key, mkey);                                            \     mfdat = fits_decode_card (fits_search_card (mhdr, mkey), mtyp);     \     if (mfdat == NULL) goto err_missing; }
DECL|macro|FITS_TRY_CARD (mhdr,mhdu,mkey,mvar,mtyp,unionvar)
define|#
directive|define
name|FITS_TRY_CARD
parameter_list|(
name|mhdr
parameter_list|,
name|mhdu
parameter_list|,
name|mkey
parameter_list|,
name|mvar
parameter_list|,
name|mtyp
parameter_list|,
name|unionvar
parameter_list|)
define|\
value|{ FitsData *mfdat = fits_decode_card (fits_search_card (mhdr,mkey), mtyp); \     mhdu->used.mvar = (mfdat != NULL);                                  \     if (mhdu->used.mvar) mhdu->mvar = mfdat->unionvar; }
name|hdulist
operator|=
name|fits_new_hdulist
argument_list|()
expr_stmt|;
if|if
condition|(
name|hdulist
operator|==
name|NULL
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_decode_header: Not enough memory"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Initialize the header data */
name|hdulist
operator|->
name|header_offset
operator|=
name|hdr_offset
expr_stmt|;
name|hdulist
operator|->
name|data_offset
operator|=
name|dat_offset
expr_stmt|;
name|hdulist
operator|->
name|used
operator|.
name|simple
operator|=
operator|(
name|strncmp
argument_list|(
name|hdr
operator|->
name|data
argument_list|,
literal|"SIMPLE  "
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
name|hdulist
operator|->
name|used
operator|.
name|xtension
operator|=
operator|(
name|strncmp
argument_list|(
name|hdr
operator|->
name|data
argument_list|,
literal|"XTENSION"
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|xtension
condition|)
block|{
name|fdat
operator|=
name|fits_decode_card
argument_list|(
name|fits_search_card
argument_list|(
name|hdr
argument_list|,
literal|"XTENSION"
argument_list|)
argument_list|,
name|FITS_DATA_TYPE_FSTRING
argument_list|)
expr_stmt|;
if|if
condition|(
name|fdat
operator|!=
name|NULL
condition|)
block|{
name|strcpy
argument_list|(
name|hdulist
operator|->
name|xtension
argument_list|,
name|fdat
operator|->
name|fstring
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|strcpy
argument_list|(
name|errmsg
argument_list|,
literal|"No valid XTENSION header found."
argument_list|)
expr_stmt|;
goto|goto
name|err_return
goto|;
block|}
block|}
name|FITS_DECODE_CARD
argument_list|(
name|hdr
argument_list|,
literal|"NAXIS"
argument_list|,
name|fdat
argument_list|,
name|FITS_DATA_TYPE_FLONG
argument_list|)
expr_stmt|;
name|hdulist
operator|->
name|naxis
operator|=
name|fdat
operator|->
name|flong
expr_stmt|;
name|FITS_DECODE_CARD
argument_list|(
name|hdr
argument_list|,
literal|"BITPIX"
argument_list|,
name|fdat
argument_list|,
name|FITS_DATA_TYPE_FLONG
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|hdulist
operator|->
name|bitpix
operator|=
operator|(
name|gint
operator|)
name|fdat
operator|->
name|flong
expr_stmt|;
if|if
condition|(
operator|(
name|bpp
operator|!=
literal|8
operator|)
operator|&&
operator|(
name|bpp
operator|!=
literal|16
operator|)
operator|&&
operator|(
name|bpp
operator|!=
literal|32
operator|)
operator|&&
operator|(
name|bpp
operator|!=
operator|-
literal|32
operator|)
operator|&&
operator|(
name|bpp
operator|!=
operator|-
literal|64
operator|)
condition|)
block|{
name|strcpy
argument_list|(
name|errmsg
argument_list|,
literal|"fits_decode_header: Invalid BITPIX-value"
argument_list|)
expr_stmt|;
goto|goto
name|err_return
goto|;
block|}
if|if
condition|(
name|bpp
operator|<
literal|0
condition|)
name|bpp
operator|=
operator|-
name|bpp
expr_stmt|;
name|bpp
operator|/=
literal|8
expr_stmt|;
name|hdulist
operator|->
name|bpp
operator|=
name|bpp
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"GCOUNT"
argument_list|,
name|gcount
argument_list|,
name|FITS_DATA_TYPE_FLONG
argument_list|,
name|flong
argument_list|)
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"PCOUNT"
argument_list|,
name|pcount
argument_list|,
name|FITS_DATA_TYPE_FLONG
argument_list|,
name|flong
argument_list|)
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"GROUPS"
argument_list|,
name|groups
argument_list|,
name|FITS_DATA_TYPE_FLONG
argument_list|,
name|fbool
argument_list|)
expr_stmt|;
name|random_groups
operator|=
name|hdulist
operator|->
name|used
operator|.
name|groups
operator|&&
name|hdulist
operator|->
name|groups
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"EXTEND"
argument_list|,
name|extend
argument_list|,
name|FITS_DATA_TYPE_FBOOL
argument_list|,
name|fbool
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|xtension
condition|)
comment|/* Extension requires GCOUNT and PCOUNT */
block|{
if|if
condition|(
operator|!
name|hdulist
operator|->
name|used
operator|.
name|gcount
operator|||
operator|!
name|hdulist
operator|->
name|used
operator|.
name|pcount
condition|)
block|{
name|strcpy
argument_list|(
name|errmsg
argument_list|,
literal|"fits_decode_header: Missing GCOUNT/PCOUNT for XTENSION"
argument_list|)
expr_stmt|;
goto|goto
name|err_return
goto|;
block|}
block|}
name|mul_axis
operator|=
literal|1
expr_stmt|;
comment|/* Find all NAXISx-cards */
for|for
control|(
name|k
operator|=
literal|1
init|;
name|k
operator|<=
name|FITS_MAX_AXIS
condition|;
name|k
operator|++
control|)
block|{
name|gchar
name|naxisn
index|[
literal|16
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|naxisn
argument_list|,
sizeof|sizeof
argument_list|(
name|naxisn
argument_list|)
argument_list|,
literal|"NAXIS%-3d"
argument_list|,
name|k
argument_list|)
expr_stmt|;
name|fdat
operator|=
name|fits_decode_card
argument_list|(
name|fits_search_card
argument_list|(
name|hdr
argument_list|,
name|naxisn
argument_list|)
argument_list|,
name|FITS_DATA_TYPE_FLONG
argument_list|)
expr_stmt|;
if|if
condition|(
name|fdat
operator|==
name|NULL
condition|)
block|{
name|k
operator|--
expr_stmt|;
comment|/* Save the last NAXISk read */
break|break;
block|}
name|hdulist
operator|->
name|naxisn
index|[
name|k
operator|-
literal|1
index|]
operator|=
operator|(
name|int
operator|)
name|fdat
operator|->
name|flong
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|naxisn
index|[
name|k
operator|-
literal|1
index|]
operator|<
literal|0
condition|)
block|{
name|strcpy
argument_list|(
name|errmsg
argument_list|,
literal|"fits_decode_header: Negative value in NAXISn"
argument_list|)
expr_stmt|;
goto|goto
name|err_return
goto|;
block|}
if|if
condition|(
operator|(
name|k
operator|==
literal|1
operator|)
operator|&&
name|random_groups
condition|)
block|{
if|if
condition|(
name|hdulist
operator|->
name|naxisn
index|[
literal|0
index|]
operator|!=
literal|0
condition|)
block|{
name|strcpy
argument_list|(
name|errmsg
argument_list|,
literal|"fits_decode_header: Random groups with NAXIS1 != 0"
argument_list|)
expr_stmt|;
goto|goto
name|err_return
goto|;
block|}
block|}
else|else
block|{
name|mul_axis
operator|*=
name|hdulist
operator|->
name|naxisn
index|[
name|k
operator|-
literal|1
index|]
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|hdulist
operator|->
name|naxis
operator|>
literal|0
operator|)
operator|&&
operator|(
name|k
operator|<
name|hdulist
operator|->
name|naxis
operator|)
condition|)
block|{
name|strcpy
argument_list|(
name|errmsg
argument_list|,
literal|"fits_decode_card: Not enough NAXISn-cards"
argument_list|)
expr_stmt|;
goto|goto
name|err_return
goto|;
block|}
comment|/* If we have only one dimension, just set the second to size one. */
comment|/* So we dont have to check for naxis< 2 in some places. */
if|if
condition|(
name|hdulist
operator|->
name|naxis
operator|<
literal|2
condition|)
name|hdulist
operator|->
name|naxisn
index|[
literal|1
index|]
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|naxis
operator|<
literal|1
condition|)
block|{
name|mul_axis
operator|=
literal|0
expr_stmt|;
name|hdulist
operator|->
name|naxisn
index|[
literal|0
index|]
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|xtension
condition|)
name|data_size
operator|=
name|bpp
operator|*
name|hdulist
operator|->
name|gcount
operator|*
operator|(
name|hdulist
operator|->
name|pcount
operator|+
name|mul_axis
operator|)
expr_stmt|;
else|else
name|data_size
operator|=
name|bpp
operator|*
name|mul_axis
expr_stmt|;
name|hdulist
operator|->
name|udata_size
operator|=
name|data_size
expr_stmt|;
comment|/* Used data size without padding */
comment|/* Datasize must be a multiple of the FITS logical record size */
name|data_size
operator|=
operator|(
name|data_size
operator|+
name|FITS_RECORD_SIZE
operator|-
literal|1
operator|)
operator|/
name|FITS_RECORD_SIZE
expr_stmt|;
name|data_size
operator|*=
name|FITS_RECORD_SIZE
expr_stmt|;
name|hdulist
operator|->
name|data_size
operator|=
name|data_size
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"BLANK"
argument_list|,
name|blank
argument_list|,
name|FITS_DATA_TYPE_FLONG
argument_list|,
name|flong
argument_list|)
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"DATAMIN"
argument_list|,
name|datamin
argument_list|,
name|FITS_DATA_TYPE_FDOUBLE
argument_list|,
name|fdouble
argument_list|)
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"DATAMAX"
argument_list|,
name|datamax
argument_list|,
name|FITS_DATA_TYPE_FDOUBLE
argument_list|,
name|fdouble
argument_list|)
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"BZERO"
argument_list|,
name|bzero
argument_list|,
name|FITS_DATA_TYPE_FDOUBLE
argument_list|,
name|fdouble
argument_list|)
expr_stmt|;
name|FITS_TRY_CARD
argument_list|(
name|hdr
argument_list|,
name|hdulist
argument_list|,
literal|"BSCALE"
argument_list|,
name|bscale
argument_list|,
name|FITS_DATA_TYPE_FDOUBLE
argument_list|,
name|fdouble
argument_list|)
expr_stmt|;
comment|/* Evaluate number of interpretable images for this HDU */
name|hdulist
operator|->
name|numpic
operator|=
literal|0
expr_stmt|;
comment|/* We must support this format */
name|bitpix_supported
operator|=
operator|(
name|hdulist
operator|->
name|bitpix
operator|>
literal|0
operator|)
operator|||
operator|(
operator|(
name|hdulist
operator|->
name|bitpix
operator|==
operator|-
literal|64
operator|)
operator|&&
operator|(
name|fits_ieee64_intel
operator|||
name|fits_ieee64_motorola
operator|)
operator|)
operator|||
operator|(
operator|(
name|hdulist
operator|->
name|bitpix
operator|==
operator|-
literal|32
operator|)
operator|&&
operator|(
name|fits_ieee32_intel
operator|||
name|fits_ieee32_motorola
operator|||
name|fits_ieee64_intel
operator|||
name|fits_ieee64_motorola
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|bitpix_supported
condition|)
block|{
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|simple
condition|)
block|{
if|if
condition|(
name|hdulist
operator|->
name|naxis
operator|>
literal|0
condition|)
block|{
name|hdulist
operator|->
name|numpic
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|3
init|;
name|k
operator|<=
name|hdulist
operator|->
name|naxis
condition|;
name|k
operator|++
control|)
name|hdulist
operator|->
name|numpic
operator|*=
name|hdulist
operator|->
name|naxisn
index|[
name|k
operator|-
literal|1
index|]
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|xtension
operator|&&
operator|(
name|strncmp
argument_list|(
name|hdulist
operator|->
name|xtension
argument_list|,
literal|"IMAGE"
argument_list|,
literal|5
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
if|if
condition|(
name|hdulist
operator|->
name|naxis
operator|>
literal|0
condition|)
block|{
name|hdulist
operator|->
name|numpic
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|3
init|;
name|k
operator|<=
name|hdulist
operator|->
name|naxis
condition|;
name|k
operator|++
control|)
name|hdulist
operator|->
name|numpic
operator|*=
name|hdulist
operator|->
name|naxisn
index|[
name|k
operator|-
literal|1
index|]
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|gchar
name|msg
index|[
literal|160
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|msg
argument_list|,
sizeof|sizeof
argument_list|(
name|msg
argument_list|)
argument_list|,
literal|"fits_decode_header: IEEE floating point format required for "
literal|"BITPIX=%d\nis not supported on this machine"
argument_list|,
name|hdulist
operator|->
name|bitpix
argument_list|)
expr_stmt|;
name|fits_set_error
argument_list|(
name|msg
argument_list|)
expr_stmt|;
block|}
name|hdulist
operator|->
name|header_record_list
operator|=
name|hdr
expr_stmt|;
comment|/* Add header records to the list */
return|return
name|hdulist
return|;
name|err_missing
label|:
name|g_snprintf
argument_list|(
name|errmsg
argument_list|,
sizeof|sizeof
argument_list|(
name|errmsg
argument_list|)
argument_list|,
literal|"fits_decode_header: missing/invalid %s card"
argument_list|,
name|key
argument_list|)
expr_stmt|;
name|err_return
label|:
name|fits_delete_hdulist
argument_list|(
name|hdulist
argument_list|)
expr_stmt|;
name|fits_set_error
argument_list|(
name|errmsg
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
undef|#
directive|undef
name|FITS_DECODE_CARD
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_eval_pixrange - (local) evaluate range of pixel data     */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FILE *fp               [I] : file pointer                                 */
end_comment

begin_comment
comment|/* FitsHduList *hdu     [I] : pointer to header                            */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The Function sets the values hdu->pixmin and hdu->pixmax. On success 0    */
end_comment

begin_comment
comment|/* is returned. On failure, -1 is returned.                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
specifier|static
name|gint
DECL|function|fits_eval_pixrange (FILE * fp,FitsHduList * hdu)
name|fits_eval_pixrange
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|,
name|FitsHduList
modifier|*
name|hdu
parameter_list|)
block|{
specifier|register
name|gint
name|maxelem
decl_stmt|;
DECL|macro|FITSNPIX
define|#
directive|define
name|FITSNPIX
value|4096
name|guchar
name|pixdat
index|[
name|FITSNPIX
index|]
decl_stmt|;
name|gint
name|nelem
decl_stmt|,
name|bpp
decl_stmt|;
name|gboolean
name|blank_found
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|nan_found
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|fseek
argument_list|(
name|fp
argument_list|,
name|hdu
operator|->
name|data_offset
argument_list|,
name|SEEK_SET
argument_list|)
operator|<
literal|0
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_eval_pixrange: can't position file"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|hdu
operator|->
name|bpp
expr_stmt|;
comment|/* Number of bytes per pixel */
name|nelem
operator|=
name|hdu
operator|->
name|udata_size
operator|/
name|bpp
expr_stmt|;
comment|/* Number of data elements */
switch|switch
condition|(
name|hdu
operator|->
name|bitpix
condition|)
block|{
case|case
literal|8
case|:
block|{
specifier|register
name|FitsBitpix8
name|pixval
decl_stmt|;
specifier|register
name|guchar
modifier|*
name|ptr
decl_stmt|;
name|FitsBitpix8
name|minval
init|=
literal|255
decl_stmt|;
name|FitsBitpix8
name|maxval
init|=
literal|0
decl_stmt|;
while|while
condition|(
name|nelem
operator|>
literal|0
condition|)
block|{
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixdat
argument_list|)
operator|/
name|bpp
expr_stmt|;
if|if
condition|(
name|nelem
operator|<
name|maxelem
condition|)
name|maxelem
operator|=
name|nelem
expr_stmt|;
name|nelem
operator|-=
name|maxelem
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixdat
argument_list|,
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_eval_pixrange: error on read bitpix 8 data"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|pixdat
expr_stmt|;
if|if
condition|(
name|hdu
operator|->
name|used
operator|.
name|blank
condition|)
block|{
name|FitsBitpix8
name|blankval
init|=
operator|(
name|FitsBitpix8
operator|)
name|hdu
operator|->
name|blank
decl_stmt|;
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
name|pixval
operator|=
operator|(
name|FitsBitpix8
operator|)
operator|*
operator|(
name|ptr
operator|++
operator|)
expr_stmt|;
if|if
condition|(
name|pixval
operator|!=
name|blankval
condition|)
block|{
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
name|minval
operator|=
name|pixval
expr_stmt|;
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
else|else
block|{
name|blank_found
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
name|pixval
operator|=
operator|(
name|FitsBitpix8
operator|)
operator|*
operator|(
name|ptr
operator|++
operator|)
expr_stmt|;
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
name|minval
operator|=
name|pixval
expr_stmt|;
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
block|}
block|}
name|hdu
operator|->
name|pixmin
operator|=
name|minval
expr_stmt|;
name|hdu
operator|->
name|pixmax
operator|=
name|maxval
expr_stmt|;
break|break;
block|}
case|case
literal|16
case|:
block|{
specifier|register
name|FitsBitpix16
name|pixval
decl_stmt|;
specifier|register
name|guchar
modifier|*
name|ptr
decl_stmt|;
name|FitsBitpix16
name|minval
init|=
literal|0x7fff
decl_stmt|;
name|FitsBitpix16
name|maxval
init|=
operator|~
literal|0x7fff
decl_stmt|;
while|while
condition|(
name|nelem
operator|>
literal|0
condition|)
block|{
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixdat
argument_list|)
operator|/
name|bpp
expr_stmt|;
if|if
condition|(
name|nelem
operator|<
name|maxelem
condition|)
name|maxelem
operator|=
name|nelem
expr_stmt|;
name|nelem
operator|-=
name|maxelem
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixdat
argument_list|,
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_eval_pixrange: error on read bitpix 16 data"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|pixdat
expr_stmt|;
if|if
condition|(
name|hdu
operator|->
name|used
operator|.
name|blank
condition|)
block|{
name|FitsBitpix16
name|blankval
init|=
operator|(
name|FitsBitpix16
operator|)
name|hdu
operator|->
name|blank
decl_stmt|;
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
name|FITS_GETBITPIX16
argument_list|(
name|ptr
argument_list|,
name|pixval
argument_list|)
expr_stmt|;
name|ptr
operator|+=
literal|2
expr_stmt|;
if|if
condition|(
name|pixval
operator|!=
name|blankval
condition|)
block|{
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
name|minval
operator|=
name|pixval
expr_stmt|;
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
else|else
block|{
name|blank_found
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
name|FITS_GETBITPIX16
argument_list|(
name|ptr
argument_list|,
name|pixval
argument_list|)
expr_stmt|;
name|ptr
operator|+=
literal|2
expr_stmt|;
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
name|minval
operator|=
name|pixval
expr_stmt|;
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
block|}
block|}
name|hdu
operator|->
name|pixmin
operator|=
name|minval
expr_stmt|;
name|hdu
operator|->
name|pixmax
operator|=
name|maxval
expr_stmt|;
break|break;
block|}
case|case
literal|32
case|:
block|{
specifier|register
name|FitsBitpix32
name|pixval
decl_stmt|;
specifier|register
name|guchar
modifier|*
name|ptr
decl_stmt|;
name|FitsBitpix32
name|minval
init|=
literal|0x7fffffff
decl_stmt|;
name|FitsBitpix32
name|maxval
init|=
operator|~
literal|0x7fffffff
decl_stmt|;
while|while
condition|(
name|nelem
operator|>
literal|0
condition|)
block|{
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixdat
argument_list|)
operator|/
name|bpp
expr_stmt|;
if|if
condition|(
name|nelem
operator|<
name|maxelem
condition|)
name|maxelem
operator|=
name|nelem
expr_stmt|;
name|nelem
operator|-=
name|maxelem
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixdat
argument_list|,
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_eval_pixrange: error on read bitpix 32 data"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|pixdat
expr_stmt|;
if|if
condition|(
name|hdu
operator|->
name|used
operator|.
name|blank
condition|)
block|{
name|FitsBitpix32
name|blankval
init|=
operator|(
name|FitsBitpix32
operator|)
name|hdu
operator|->
name|blank
decl_stmt|;
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
name|FITS_GETBITPIX32
argument_list|(
name|ptr
argument_list|,
name|pixval
argument_list|)
expr_stmt|;
name|ptr
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|pixval
operator|!=
name|blankval
condition|)
block|{
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
name|minval
operator|=
name|pixval
expr_stmt|;
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
else|else
block|{
name|blank_found
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
name|FITS_GETBITPIX32
argument_list|(
name|ptr
argument_list|,
name|pixval
argument_list|)
expr_stmt|;
name|ptr
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
name|minval
operator|=
name|pixval
expr_stmt|;
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
block|}
block|}
name|hdu
operator|->
name|pixmin
operator|=
name|minval
expr_stmt|;
name|hdu
operator|->
name|pixmax
operator|=
name|maxval
expr_stmt|;
break|break;
block|}
case|case
operator|-
literal|32
case|:
block|{
specifier|register
name|FitsBitpixM32
name|pixval
init|=
literal|0
decl_stmt|;
specifier|register
name|guchar
modifier|*
name|ptr
decl_stmt|;
name|FitsBitpixM32
name|minval
init|=
literal|0
decl_stmt|;
name|FitsBitpixM32
name|maxval
init|=
literal|0
decl_stmt|;
name|gboolean
name|first
init|=
name|TRUE
decl_stmt|;
while|while
condition|(
name|nelem
operator|>
literal|0
condition|)
block|{
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixdat
argument_list|)
operator|/
name|bpp
expr_stmt|;
if|if
condition|(
name|nelem
operator|<
name|maxelem
condition|)
name|maxelem
operator|=
name|nelem
expr_stmt|;
name|nelem
operator|-=
name|maxelem
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixdat
argument_list|,
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_eval_pixrange: error on read bitpix -32 data"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|pixdat
expr_stmt|;
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|fits_nan_32
argument_list|(
name|ptr
argument_list|)
condition|)
block|{
name|FITS_GETBITPIXM32
argument_list|(
name|ptr
argument_list|,
name|pixval
argument_list|)
expr_stmt|;
name|ptr
operator|+=
literal|4
expr_stmt|;
if|if
condition|(
name|first
condition|)
block|{
name|first
operator|=
name|FALSE
expr_stmt|;
name|minval
operator|=
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
block|{
name|minval
operator|=
name|pixval
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
block|{
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
block|}
else|else
block|{
name|nan_found
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
name|hdu
operator|->
name|pixmin
operator|=
name|minval
expr_stmt|;
name|hdu
operator|->
name|pixmax
operator|=
name|maxval
expr_stmt|;
break|break;
block|}
case|case
operator|-
literal|64
case|:
block|{
specifier|register
name|FitsBitpixM64
name|pixval
decl_stmt|;
specifier|register
name|guchar
modifier|*
name|ptr
decl_stmt|;
name|FitsBitpixM64
name|minval
init|=
literal|0
decl_stmt|;
name|FitsBitpixM64
name|maxval
init|=
literal|0
decl_stmt|;
name|gboolean
name|first
init|=
name|TRUE
decl_stmt|;
while|while
condition|(
name|nelem
operator|>
literal|0
condition|)
block|{
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixdat
argument_list|)
operator|/
name|bpp
expr_stmt|;
if|if
condition|(
name|nelem
operator|<
name|maxelem
condition|)
name|maxelem
operator|=
name|nelem
expr_stmt|;
name|nelem
operator|-=
name|maxelem
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixdat
argument_list|,
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_eval_pixrange: error on read bitpix -64 data"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|pixdat
expr_stmt|;
while|while
condition|(
name|maxelem
operator|--
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|fits_nan_64
argument_list|(
name|ptr
argument_list|)
condition|)
block|{
name|FITS_GETBITPIXM64
argument_list|(
name|ptr
argument_list|,
name|pixval
argument_list|)
expr_stmt|;
name|ptr
operator|+=
literal|8
expr_stmt|;
if|if
condition|(
name|first
condition|)
block|{
name|first
operator|=
name|FALSE
expr_stmt|;
name|minval
operator|=
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pixval
operator|<
name|minval
condition|)
block|{
name|minval
operator|=
name|pixval
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pixval
operator|>
name|maxval
condition|)
block|{
name|maxval
operator|=
name|pixval
expr_stmt|;
block|}
block|}
else|else
block|{
name|nan_found
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
name|hdu
operator|->
name|pixmin
operator|=
name|minval
expr_stmt|;
name|hdu
operator|->
name|pixmax
operator|=
name|maxval
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|nan_found
condition|)
name|hdu
operator|->
name|used
operator|.
name|nan_value
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|blank_found
condition|)
name|hdu
operator|->
name|used
operator|.
name|blank_value
operator|=
name|TRUE
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_decode_card - decode a card                              */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* const char *card   [I] : pointer to card image                            */
end_comment

begin_comment
comment|/* FitsDataType data_type [I] : datatype to decode                           */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Decodes a card and returns a pointer to the union, keeping the data.      */
end_comment

begin_comment
comment|/* If card is NULL or on failure, a NULL-pointer is returned.                */
end_comment

begin_comment
comment|/* If the card does not have the value indicator, an error is generated,     */
end_comment

begin_comment
comment|/* but its tried to decode the card. The data is only valid up to the next   */
end_comment

begin_comment
comment|/* call of the function.                                                     */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|FitsData
modifier|*
DECL|function|fits_decode_card (const gchar * card,FitsDataType data_type)
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
block|{
specifier|static
name|FitsData
name|data
decl_stmt|;
name|glong
name|l_long
decl_stmt|;
name|gdouble
name|l_double
decl_stmt|;
name|gchar
name|l_card
index|[
name|FITS_CARD_SIZE
operator|+
literal|1
index|]
decl_stmt|;
name|gchar
name|msg
index|[
literal|256
index|]
decl_stmt|;
name|gchar
modifier|*
name|cp
decl_stmt|,
modifier|*
name|dst
decl_stmt|,
modifier|*
name|end
decl_stmt|;
name|gint
name|ErrCount
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|card
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
name|memcpy
argument_list|(
name|l_card
argument_list|,
name|card
argument_list|,
name|FITS_CARD_SIZE
argument_list|)
expr_stmt|;
name|l_card
index|[
name|FITS_CARD_SIZE
index|]
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
name|card
operator|+
literal|8
argument_list|,
literal|"= "
argument_list|,
literal|2
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_snprintf
argument_list|(
name|msg
argument_list|,
sizeof|sizeof
argument_list|(
name|msg
argument_list|)
argument_list|,
literal|"fits_decode_card (warning): Missing value indicator "
literal|"'= ' for %8.8s"
argument_list|,
name|l_card
argument_list|)
expr_stmt|;
name|fits_set_error
argument_list|(
name|msg
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
block|}
switch|switch
condition|(
name|data_type
condition|)
block|{
case|case
name|FITS_DATA_TYPE_BITPIX_8
case|:
name|data
operator|.
name|bitpix8
operator|=
call|(
name|FitsBitpix8
call|)
argument_list|(
name|l_card
index|[
literal|10
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|FITS_DATA_TYPE_BITPIX_16
case|:
if|if
condition|(
name|sscanf
argument_list|(
name|l_card
operator|+
literal|10
argument_list|,
literal|"%ld"
argument_list|,
operator|&
name|l_long
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: error decoding FITS_DATA_TYPE_BITPIX_16"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
name|data
operator|.
name|bitpix16
operator|=
operator|(
name|FitsBitpix16
operator|)
name|l_long
expr_stmt|;
break|break;
case|case
name|FITS_DATA_TYPE_BITPIX_32
case|:
if|if
condition|(
name|sscanf
argument_list|(
name|l_card
operator|+
literal|10
argument_list|,
literal|"%ld"
argument_list|,
operator|&
name|l_long
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: error decoding FITS_DATA_TYPE_BITPIX_32"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
name|data
operator|.
name|bitpix32
operator|=
operator|(
name|FitsBitpix32
operator|)
name|l_long
expr_stmt|;
break|break;
case|case
name|FITS_DATA_TYPE_BITPIX_M32
case|:
if|if
condition|(
name|fits_scanfdouble
argument_list|(
name|l_card
operator|+
literal|10
argument_list|,
operator|&
name|l_double
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: error decoding FITS_DATA_TYPE_BITPIX_M32"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
name|data
operator|.
name|bitpixm32
operator|=
operator|(
name|FitsBitpixM32
operator|)
name|l_double
expr_stmt|;
break|break;
case|case
name|FITS_DATA_TYPE_BITPIX_M64
case|:
if|if
condition|(
name|fits_scanfdouble
argument_list|(
name|l_card
operator|+
literal|10
argument_list|,
operator|&
name|l_double
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: error decoding FITS_DATA_TYPE_BITPIX_M64"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
name|data
operator|.
name|bitpixm64
operator|=
operator|(
name|FitsBitpixM64
operator|)
name|l_double
expr_stmt|;
break|break;
case|case
name|FITS_DATA_TYPE_FBOOL
case|:
name|cp
operator|=
name|l_card
operator|+
literal|10
expr_stmt|;
while|while
condition|(
operator|*
name|cp
operator|==
literal|' '
condition|)
name|cp
operator|++
expr_stmt|;
if|if
condition|(
operator|*
name|cp
operator|==
literal|'T'
condition|)
block|{
name|data
operator|.
name|fbool
operator|=
literal|1
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|*
name|cp
operator|==
literal|'F'
condition|)
block|{
name|data
operator|.
name|fbool
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: error decoding FITS_DATA_TYPE_FBOOL"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|FITS_DATA_TYPE_FLONG
case|:
if|if
condition|(
name|sscanf
argument_list|(
name|l_card
operator|+
literal|10
argument_list|,
literal|"%ld"
argument_list|,
operator|&
name|l_long
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: error decoding FITS_DATA_TYPE_FLONG"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
name|data
operator|.
name|flong
operator|=
operator|(
name|FitsBitpix32
operator|)
name|l_long
expr_stmt|;
break|break;
case|case
name|FITS_DATA_TYPE_FDOUBLE
case|:
if|if
condition|(
name|fits_scanfdouble
argument_list|(
name|l_card
operator|+
literal|10
argument_list|,
operator|&
name|l_double
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: error decoding FITS_DATA_TYPE_FDOUBLE"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
name|data
operator|.
name|fdouble
operator|=
operator|(
name|FitsBitpixM32
operator|)
name|l_double
expr_stmt|;
break|break;
case|case
name|FITS_DATA_TYPE_FSTRING
case|:
name|cp
operator|=
name|l_card
operator|+
literal|10
expr_stmt|;
if|if
condition|(
operator|*
name|cp
operator|!=
literal|'\''
condition|)
block|{
name|fits_set_error
argument_list|(
literal|"fits_decode_card: missing \' decoding FITS_DATA_TYPE_FSTRING"
argument_list|)
expr_stmt|;
name|ErrCount
operator|++
expr_stmt|;
break|break;
block|}
name|dst
operator|=
name|data
operator|.
name|fstring
expr_stmt|;
name|cp
operator|++
expr_stmt|;
name|end
operator|=
name|l_card
operator|+
name|FITS_CARD_SIZE
operator|-
literal|1
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
comment|/* Search for trailing quote */
block|{
if|if
condition|(
operator|*
name|cp
operator|!=
literal|'\''
condition|)
comment|/* All characters but quote are used. */
block|{
operator|*
operator|(
name|dst
operator|++
operator|)
operator|=
operator|*
name|cp
expr_stmt|;
block|}
else|else
comment|/* Maybe there is a quote in the string */
block|{
if|if
condition|(
name|cp
operator|>=
name|end
condition|)
break|break;
comment|/* End of card ? finished */
if|if
condition|(
operator|*
operator|(
name|cp
operator|+
literal|1
operator|)
operator|!=
literal|'\''
condition|)
break|break;
operator|*
operator|(
name|dst
operator|++
operator|)
operator|=
operator|*
operator|(
name|cp
operator|++
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|cp
operator|>=
name|end
condition|)
break|break;
name|cp
operator|++
expr_stmt|;
block|}
operator|*
name|dst
operator|=
literal|'\0'
expr_stmt|;
break|break;
block|}
return|return
operator|(
name|ErrCount
operator|==
literal|0
operator|)
condition|?
operator|&
name|data
else|:
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_search_card - search a card in the record list           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsRecordList *rl  [I] : record list to search                           */
end_comment

begin_comment
comment|/* char *keyword         [I] : keyword identifying the card                  */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* A card is searched in the record list. Only the first eight characters of */
end_comment

begin_comment
comment|/* keyword are significant. If keyword is less than 8 characters, its filled */
end_comment

begin_comment
comment|/* with blanks.                                                              */
end_comment

begin_comment
comment|/* If the card is found, a pointer to the card is returned.                  */
end_comment

begin_comment
comment|/* The pointer does not point to a null-terminated string. Only the next     */
end_comment

begin_comment
comment|/* 80 bytes are allowed to be read.                                          */
end_comment

begin_comment
comment|/* On failure a NULL-pointer is returned.                                    */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|fits_search_card (FitsRecordList * rl,gchar * keyword)
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
block|{
name|gint
name|key_len
decl_stmt|,
name|k
decl_stmt|;
name|gchar
name|key
index|[
literal|9
index|]
decl_stmt|;
name|key_len
operator|=
name|strlen
argument_list|(
name|keyword
argument_list|)
expr_stmt|;
if|if
condition|(
name|key_len
operator|>
literal|8
condition|)
name|key_len
operator|=
literal|8
expr_stmt|;
if|if
condition|(
name|key_len
operator|==
literal|0
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_search_card: Invalid parameter"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|key
argument_list|,
literal|"        "
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|key
argument_list|,
name|keyword
argument_list|,
name|key_len
argument_list|)
expr_stmt|;
while|while
condition|(
name|rl
operator|!=
name|NULL
condition|)
block|{
name|gchar
modifier|*
name|card
init|=
operator|(
name|gchar
operator|*
operator|)
name|rl
operator|->
name|data
decl_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|FITS_RECORD_SIZE
operator|/
name|FITS_CARD_SIZE
condition|;
name|k
operator|++
control|)
block|{
if|if
condition|(
name|strncmp
argument_list|(
name|card
argument_list|,
name|key
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
condition|)
return|return
operator|(
name|card
operator|)
return|;
name|card
operator|+=
name|FITS_CARD_SIZE
expr_stmt|;
block|}
name|rl
operator|=
name|rl
operator|->
name|next_record
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_image_info - get information about an image              */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsFile *ff         [I] : FITS file structure                            */
end_comment

begin_comment
comment|/* int picind            [I] : Index of picture in file (1,2,...)            */
end_comment

begin_comment
comment|/* int *hdupicind        [O] : Index of picture in HDU (1,2,...)             */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function returns on success a pointer to a FitsHduList. hdupicind     */
end_comment

begin_comment
comment|/* then gives the index of the image within the HDU.                         */
end_comment

begin_comment
comment|/* On failure, NULL is returned.                                             */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|FitsHduList
modifier|*
DECL|function|fits_image_info (FitsFile * ff,gint picind,gint * hdupicind)
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
block|{
name|FitsHduList
modifier|*
name|hdulist
decl_stmt|;
name|gint
name|firstpic
decl_stmt|,
name|lastpic
decl_stmt|;
if|if
condition|(
name|ff
operator|==
name|NULL
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_image_info: ff is NULL"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|ff
operator|->
name|openmode
operator|!=
literal|'r'
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_image_info: file not open for reading"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|picind
operator|<
literal|1
operator|)
operator|||
operator|(
name|picind
operator|>
name|ff
operator|->
name|n_pic
operator|)
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_image_info: picind out of range"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|firstpic
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|hdulist
operator|=
name|ff
operator|->
name|hdu_list
init|;
name|hdulist
operator|!=
name|NULL
condition|;
name|hdulist
operator|=
name|hdulist
operator|->
name|next_hdu
control|)
block|{
if|if
condition|(
name|hdulist
operator|->
name|numpic
operator|<=
literal|0
condition|)
continue|continue;
name|lastpic
operator|=
name|firstpic
operator|+
name|hdulist
operator|->
name|numpic
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|picind
operator|<=
name|lastpic
condition|)
comment|/* Found image in current HDU ? */
break|break;
name|firstpic
operator|=
name|lastpic
operator|+
literal|1
expr_stmt|;
block|}
operator|*
name|hdupicind
operator|=
name|picind
operator|-
name|firstpic
operator|+
literal|1
expr_stmt|;
return|return
name|hdulist
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_seek_image - position to a specific image                */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsFile *ff         [I] : FITS file structure                            */
end_comment

begin_comment
comment|/* int picind            [I] : Index of picture to seek (1,2,...)            */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function positions the file pointer to a specified image.             */
end_comment

begin_comment
comment|/* The function returns on success a pointer to a FitsHduList. This pointer  */
end_comment

begin_comment
comment|/* must also be used when reading data from the image.                       */
end_comment

begin_comment
comment|/* On failure, NULL is returned.                                             */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|FitsHduList
modifier|*
DECL|function|fits_seek_image (FitsFile * ff,gint picind)
name|fits_seek_image
parameter_list|(
name|FitsFile
modifier|*
name|ff
parameter_list|,
name|gint
name|picind
parameter_list|)
block|{
name|FitsHduList
modifier|*
name|hdulist
decl_stmt|;
name|gint
name|hdupicind
decl_stmt|;
name|glong
name|offset
decl_stmt|,
name|pic_size
decl_stmt|;
name|hdulist
operator|=
name|fits_image_info
argument_list|(
name|ff
argument_list|,
name|picind
argument_list|,
operator|&
name|hdupicind
argument_list|)
expr_stmt|;
if|if
condition|(
name|hdulist
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
name|pic_size
operator|=
name|hdulist
operator|->
name|bpp
operator|*
name|hdulist
operator|->
name|naxisn
index|[
literal|0
index|]
operator|*
name|hdulist
operator|->
name|naxisn
index|[
literal|1
index|]
expr_stmt|;
name|offset
operator|=
name|hdulist
operator|->
name|data_offset
operator|+
operator|(
name|hdupicind
operator|-
literal|1
operator|)
operator|*
name|pic_size
expr_stmt|;
if|if
condition|(
name|fseek
argument_list|(
name|ff
operator|->
name|fp
argument_list|,
name|offset
argument_list|,
name|SEEK_SET
argument_list|)
operator|<
literal|0
condition|)
name|FITS_RETURN
argument_list|(
literal|"fits_seek_image: Unable to position to image"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|hdulist
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_read_pixel - read pixel values from a file               */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* FitsFile *ff           [I] : FITS file structure                          */
end_comment

begin_comment
comment|/* FitsHduList *hdulist  [I] : pointer to hdulist that describes image       */
end_comment

begin_comment
comment|/* int npix                [I] : number of pixel values to read              */
end_comment

begin_comment
comment|/* FitsPixTransform *trans [I]: pixel transformation                         */
end_comment

begin_comment
comment|/* void *buf               [O] : buffer where to place transformed pixels    */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function reads npix pixel values from the file, transforms them       */
end_comment

begin_comment
comment|/* checking for blank/NaN pixels and stores the transformed values in buf.   */
end_comment

begin_comment
comment|/* The number of transformed pixels is returned. If the returned value is    */
end_comment

begin_comment
comment|/* less than npix (or even -1), an error has occurred.                       */
end_comment

begin_comment
comment|/* hdulist must be a pointer returned by fits_seek_image(). Before starting  */
end_comment

begin_comment
comment|/* to read an image, fits_seek_image() must be called. Even for successive   */
end_comment

begin_comment
comment|/* images.                                                                   */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|gint
DECL|function|fits_read_pixel (FitsFile * ff,FitsHduList * hdulist,gint npix,FitsPixTransform * trans,void * buf)
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
block|{
name|gdouble
name|offs
decl_stmt|,
name|scale
decl_stmt|;
name|gdouble
name|datadiff
decl_stmt|,
name|pixdiff
decl_stmt|;
name|guchar
name|pixbuffer
index|[
literal|4096
index|]
decl_stmt|;
name|guchar
modifier|*
name|pix
decl_stmt|;
name|glong
name|creplace
decl_stmt|;
name|gint
name|transcount
init|=
literal|0
decl_stmt|;
name|glong
name|tdata
decl_stmt|,
name|tmin
decl_stmt|,
name|tmax
decl_stmt|;
name|gint
name|maxelem
decl_stmt|;
if|if
condition|(
name|ff
operator|->
name|openmode
operator|!=
literal|'r'
condition|)
return|return
operator|-
literal|1
return|;
comment|/* Not open for reading */
if|if
condition|(
name|trans
operator|->
name|dsttyp
operator|!=
literal|'k'
condition|)
return|return
operator|-
literal|1
return|;
comment|/* Currently we only return types equivalent to the image format */
if|if
condition|(
name|npix
operator|<=
literal|0
condition|)
return|return
name|npix
return|;
name|datadiff
operator|=
name|trans
operator|->
name|datamax
operator|-
name|trans
operator|->
name|datamin
expr_stmt|;
name|pixdiff
operator|=
name|trans
operator|->
name|pixmax
operator|-
name|trans
operator|->
name|pixmin
expr_stmt|;
name|offs
operator|=
name|trans
operator|->
name|datamin
operator|-
name|trans
operator|->
name|pixmin
operator|*
name|datadiff
operator|/
name|pixdiff
expr_stmt|;
name|scale
operator|=
name|datadiff
operator|/
name|pixdiff
expr_stmt|;
name|tmin
operator|=
operator|(
name|glong
operator|)
name|trans
operator|->
name|datamin
expr_stmt|;
name|tmax
operator|=
operator|(
name|glong
operator|)
name|trans
operator|->
name|datamax
expr_stmt|;
name|creplace
operator|=
operator|(
name|glong
operator|)
name|trans
operator|->
name|replacement
expr_stmt|;
switch|switch
condition|(
name|hdulist
operator|->
name|bitpix
condition|)
block|{
case|case
literal|8
case|:
block|{
name|guchar
modifier|*
name|cdata
init|=
operator|(
name|guchar
operator|*
operator|)
name|buf
decl_stmt|;
while|while
condition|(
name|npix
operator|>
literal|0
condition|)
comment|/* For all pixels to read */
block|{
name|FitsBitpix8
name|bp8
decl_stmt|,
name|bp8blank
decl_stmt|;
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixbuffer
argument_list|)
operator|/
name|hdulist
operator|->
name|bpp
expr_stmt|;
if|if
condition|(
name|maxelem
operator|>
name|npix
condition|)
name|maxelem
operator|=
name|npix
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixbuffer
argument_list|,
name|hdulist
operator|->
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|ff
operator|->
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
return|return
operator|-
literal|1
return|;
name|npix
operator|-=
name|maxelem
expr_stmt|;
name|pix
operator|=
name|pixbuffer
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|blank
condition|)
block|{
name|bp8blank
operator|=
operator|(
name|FitsBitpix8
operator|)
name|hdulist
operator|->
name|blank
expr_stmt|;
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
name|bp8
operator|=
operator|(
name|FitsBitpix8
operator|)
operator|*
operator|(
name|pix
operator|++
operator|)
expr_stmt|;
if|if
condition|(
name|bp8
operator|==
name|bp8blank
condition|)
comment|/* Is it a blank pixel ? */
block|{
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|guchar
operator|)
name|creplace
expr_stmt|;
block|}
else|else
comment|/* Do transform */
block|{
name|tdata
operator|=
call|(
name|glong
call|)
argument_list|(
name|bp8
operator|*
name|scale
operator|+
name|offs
argument_list|)
expr_stmt|;
name|tdata
operator|=
name|CLAMP
argument_list|(
name|tdata
argument_list|,
name|tmin
argument_list|,
name|tmax
argument_list|)
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|guchar
operator|)
name|tdata
expr_stmt|;
block|}
name|transcount
operator|++
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
name|bp8
operator|=
operator|(
name|FitsBitpix8
operator|)
operator|*
operator|(
name|pix
operator|++
operator|)
expr_stmt|;
name|tdata
operator|=
call|(
name|glong
call|)
argument_list|(
name|bp8
operator|*
name|scale
operator|+
name|offs
argument_list|)
expr_stmt|;
name|tdata
operator|=
name|CLAMP
argument_list|(
name|tdata
argument_list|,
name|tmin
argument_list|,
name|tmax
argument_list|)
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|guchar
operator|)
name|tdata
expr_stmt|;
name|transcount
operator|++
expr_stmt|;
block|}
block|}
block|}
block|}
break|break;
case|case
literal|16
case|:
block|{
name|FitsBitpix16
modifier|*
name|cdata
init|=
operator|(
name|FitsBitpix16
operator|*
operator|)
name|buf
decl_stmt|;
while|while
condition|(
name|npix
operator|>
literal|0
condition|)
comment|/* For all pixels to read */
block|{
name|FitsBitpix16
name|bp16
decl_stmt|,
name|bp16blank
decl_stmt|;
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixbuffer
argument_list|)
operator|/
name|hdulist
operator|->
name|bpp
expr_stmt|;
if|if
condition|(
name|maxelem
operator|>
name|npix
condition|)
name|maxelem
operator|=
name|npix
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixbuffer
argument_list|,
name|hdulist
operator|->
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|ff
operator|->
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
return|return
operator|-
literal|1
return|;
name|npix
operator|-=
name|maxelem
expr_stmt|;
name|pix
operator|=
name|pixbuffer
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|blank
condition|)
block|{
name|bp16blank
operator|=
operator|(
name|FitsBitpix16
operator|)
name|hdulist
operator|->
name|blank
expr_stmt|;
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
name|FITS_GETBITPIX16
argument_list|(
name|pix
argument_list|,
name|bp16
argument_list|)
expr_stmt|;
if|if
condition|(
name|bp16
operator|==
name|bp16blank
condition|)
block|{
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|FitsBitpix16
operator|)
name|creplace
expr_stmt|;
block|}
else|else
block|{
name|tdata
operator|=
call|(
name|glong
call|)
argument_list|(
name|bp16
operator|*
name|scale
operator|+
name|offs
argument_list|)
expr_stmt|;
if|if
condition|(
name|tdata
operator|<
name|tmin
condition|)
name|tdata
operator|=
name|tmin
expr_stmt|;
elseif|else
if|if
condition|(
name|tdata
operator|>
name|tmax
condition|)
name|tdata
operator|=
name|tmax
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|FitsBitpix16
operator|)
name|tdata
expr_stmt|;
block|}
name|transcount
operator|++
expr_stmt|;
name|pix
operator|+=
literal|2
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
name|FITS_GETBITPIX16
argument_list|(
name|pix
argument_list|,
name|bp16
argument_list|)
expr_stmt|;
name|tdata
operator|=
call|(
name|glong
call|)
argument_list|(
name|bp16
operator|*
name|scale
operator|+
name|offs
argument_list|)
expr_stmt|;
if|if
condition|(
name|tdata
operator|<
name|tmin
condition|)
name|tdata
operator|=
name|tmin
expr_stmt|;
elseif|else
if|if
condition|(
name|tdata
operator|>
name|tmax
condition|)
name|tdata
operator|=
name|tmax
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|FitsBitpix16
operator|)
name|tdata
expr_stmt|;
name|transcount
operator|++
expr_stmt|;
name|pix
operator|+=
literal|2
expr_stmt|;
block|}
block|}
block|}
block|}
break|break;
case|case
literal|32
case|:
block|{
name|FitsBitpix32
modifier|*
name|cdata
init|=
operator|(
name|FitsBitpix32
operator|*
operator|)
name|buf
decl_stmt|;
while|while
condition|(
name|npix
operator|>
literal|0
condition|)
comment|/* For all pixels to read */
block|{
name|FitsBitpix32
name|bp32
decl_stmt|,
name|bp32blank
decl_stmt|;
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixbuffer
argument_list|)
operator|/
name|hdulist
operator|->
name|bpp
expr_stmt|;
if|if
condition|(
name|maxelem
operator|>
name|npix
condition|)
name|maxelem
operator|=
name|npix
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixbuffer
argument_list|,
name|hdulist
operator|->
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|ff
operator|->
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
return|return
operator|-
literal|1
return|;
name|npix
operator|-=
name|maxelem
expr_stmt|;
name|pix
operator|=
name|pixbuffer
expr_stmt|;
if|if
condition|(
name|hdulist
operator|->
name|used
operator|.
name|blank
condition|)
block|{
name|bp32blank
operator|=
operator|(
name|FitsBitpix32
operator|)
name|hdulist
operator|->
name|blank
expr_stmt|;
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
name|FITS_GETBITPIX32
argument_list|(
name|pix
argument_list|,
name|bp32
argument_list|)
expr_stmt|;
if|if
condition|(
name|bp32
operator|==
name|bp32blank
condition|)
block|{
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|FitsBitpix32
operator|)
name|creplace
expr_stmt|;
block|}
else|else
block|{
name|tdata
operator|=
call|(
name|glong
call|)
argument_list|(
name|bp32
operator|*
name|scale
operator|+
name|offs
argument_list|)
expr_stmt|;
if|if
condition|(
name|tdata
operator|<
name|tmin
condition|)
name|tdata
operator|=
name|tmin
expr_stmt|;
elseif|else
if|if
condition|(
name|tdata
operator|>
name|tmax
condition|)
name|tdata
operator|=
name|tmax
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|FitsBitpix32
operator|)
name|tdata
expr_stmt|;
block|}
name|transcount
operator|++
expr_stmt|;
name|pix
operator|+=
literal|4
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
name|FITS_GETBITPIX32
argument_list|(
name|pix
argument_list|,
name|bp32
argument_list|)
expr_stmt|;
name|tdata
operator|=
call|(
name|glong
call|)
argument_list|(
name|bp32
operator|*
name|scale
operator|+
name|offs
argument_list|)
expr_stmt|;
name|tdata
operator|=
name|CLAMP
argument_list|(
name|tdata
argument_list|,
name|tmin
argument_list|,
name|tmax
argument_list|)
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
operator|(
name|FitsBitpix32
operator|)
name|tdata
expr_stmt|;
name|transcount
operator|++
expr_stmt|;
name|pix
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
block|}
break|break;
case|case
operator|-
literal|32
case|:
block|{
name|FitsBitpixM32
modifier|*
name|cdata
init|=
operator|(
name|FitsBitpixM32
operator|*
operator|)
name|buf
decl_stmt|;
while|while
condition|(
name|npix
operator|>
literal|0
condition|)
comment|/* For all pixels to read */
block|{
name|FitsBitpixM32
name|bpm32
init|=
literal|0
decl_stmt|;
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixbuffer
argument_list|)
operator|/
name|hdulist
operator|->
name|bpp
expr_stmt|;
if|if
condition|(
name|maxelem
operator|>
name|npix
condition|)
name|maxelem
operator|=
name|npix
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixbuffer
argument_list|,
name|hdulist
operator|->
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|ff
operator|->
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
return|return
operator|-
literal|1
return|;
name|npix
operator|-=
name|maxelem
expr_stmt|;
name|pix
operator|=
name|pixbuffer
expr_stmt|;
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
if|if
condition|(
name|fits_nan_32
argument_list|(
name|pix
argument_list|)
condition|)
comment|/* An IEEE special value ? */
block|{
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
name|trans
operator|->
name|replacement
expr_stmt|;
block|}
else|else
comment|/* Do transform */
block|{
name|FITS_GETBITPIXM32
argument_list|(
name|pix
argument_list|,
name|bpm32
argument_list|)
expr_stmt|;
name|bpm32
operator|=
name|bpm32
operator|*
name|scale
operator|+
name|offs
expr_stmt|;
name|bpm32
operator|=
name|CLAMP
argument_list|(
name|bpm32
argument_list|,
name|trans
operator|->
name|datamin
argument_list|,
name|trans
operator|->
name|datamax
argument_list|)
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
name|bpm32
expr_stmt|;
block|}
name|transcount
operator|++
expr_stmt|;
name|pix
operator|+=
literal|4
expr_stmt|;
block|}
block|}
block|}
break|break;
case|case
operator|-
literal|64
case|:
block|{
name|FitsBitpixM64
modifier|*
name|cdata
init|=
operator|(
name|FitsBitpixM64
operator|*
operator|)
name|buf
decl_stmt|;
while|while
condition|(
name|npix
operator|>
literal|0
condition|)
comment|/* For all pixels to read */
block|{
name|FitsBitpixM64
name|bpm64
decl_stmt|;
name|maxelem
operator|=
sizeof|sizeof
argument_list|(
name|pixbuffer
argument_list|)
operator|/
name|hdulist
operator|->
name|bpp
expr_stmt|;
if|if
condition|(
name|maxelem
operator|>
name|npix
condition|)
name|maxelem
operator|=
name|npix
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|pixbuffer
argument_list|,
name|hdulist
operator|->
name|bpp
argument_list|,
name|maxelem
argument_list|,
name|ff
operator|->
name|fp
argument_list|)
operator|!=
name|maxelem
condition|)
return|return
operator|-
literal|1
return|;
name|npix
operator|-=
name|maxelem
expr_stmt|;
name|pix
operator|=
name|pixbuffer
expr_stmt|;
while|while
condition|(
name|maxelem
operator|--
condition|)
block|{
if|if
condition|(
name|fits_nan_64
argument_list|(
name|pix
argument_list|)
condition|)
block|{
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
name|trans
operator|->
name|replacement
expr_stmt|;
block|}
else|else
block|{
name|FITS_GETBITPIXM64
argument_list|(
name|pix
argument_list|,
name|bpm64
argument_list|)
expr_stmt|;
name|bpm64
operator|=
name|bpm64
operator|*
name|scale
operator|+
name|offs
expr_stmt|;
name|bpm64
operator|=
name|CLAMP
argument_list|(
name|bpm64
argument_list|,
name|trans
operator|->
name|datamin
argument_list|,
name|trans
operator|->
name|datamax
argument_list|)
expr_stmt|;
operator|*
operator|(
name|cdata
operator|++
operator|)
operator|=
name|bpm64
expr_stmt|;
block|}
name|transcount
operator|++
expr_stmt|;
name|pix
operator|+=
literal|8
expr_stmt|;
block|}
block|}
block|}
break|break;
block|}
return|return
name|transcount
return|;
block|}
end_function

begin_ifndef
ifndef|#
directive|ifndef
name|FITS_NO_DEMO
end_ifndef

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : fits_to_pgmraw - convert FITS-file to raw PGM-file            */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* char *fitsfile          [I] : name of fitsfile                            */
end_comment

begin_comment
comment|/* char *pgmfile           [I] : name of pgmfile                             */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function converts a FITS-file to a raw PGM-file. The PGM-file will    */
end_comment

begin_comment
comment|/* be upside down, because the orientation for storing the image is          */
end_comment

begin_comment
comment|/* different. On success, 0 is returned. On failure, -1 is returned.         */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|gint
DECL|function|fits_to_pgmraw (gchar * fitsfile,gchar * pgmfile)
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
block|{
name|FitsFile
modifier|*
name|fitsin
init|=
name|NULL
decl_stmt|;
name|FILE
modifier|*
name|pgmout
init|=
name|NULL
decl_stmt|;
name|FitsHduList
modifier|*
name|hdu
decl_stmt|;
name|FitsPixTransform
name|trans
decl_stmt|;
name|gint
name|retval
init|=
operator|-
literal|1
decl_stmt|,
name|nbytes
decl_stmt|,
name|maxbytes
decl_stmt|;
name|gchar
name|buffer
index|[
literal|1024
index|]
decl_stmt|;
name|fitsin
operator|=
name|fits_open
argument_list|(
name|fitsfile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
comment|/* Open FITS-file for reading */
if|if
condition|(
name|fitsin
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
if|if
condition|(
name|fitsin
operator|->
name|n_pic
operator|<
literal|1
condition|)
goto|goto
name|err_return
goto|;
comment|/* Any picture in it ? */
name|hdu
operator|=
name|fits_seek_image
argument_list|(
name|fitsin
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/* Position to the first image */
if|if
condition|(
name|hdu
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
if|if
condition|(
name|hdu
operator|->
name|naxis
operator|<
literal|2
condition|)
goto|goto
name|err_return
goto|;
comment|/* Enough dimensions ? */
name|pgmout
operator|=
name|g_fopen
argument_list|(
name|pgmfile
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pgmout
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
comment|/* Write PGM header with width/height */
name|fprintf
argument_list|(
name|pgmout
argument_list|,
literal|"P5\n%d %d\n255\n"
argument_list|,
name|hdu
operator|->
name|naxisn
index|[
literal|0
index|]
argument_list|,
name|hdu
operator|->
name|naxisn
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
comment|/* Set up transformation for FITS pixel values to 0...255 */
comment|/* It maps trans.pixmin to trans.datamin and trans.pixmax to trans.datamax. */
comment|/* Values out of range [datamin, datamax] are clamped */
name|trans
operator|.
name|pixmin
operator|=
name|hdu
operator|->
name|pixmin
expr_stmt|;
name|trans
operator|.
name|pixmax
operator|=
name|hdu
operator|->
name|pixmax
expr_stmt|;
name|trans
operator|.
name|datamin
operator|=
literal|0.0
expr_stmt|;
name|trans
operator|.
name|datamax
operator|=
literal|255.0
expr_stmt|;
name|trans
operator|.
name|replacement
operator|=
literal|0.0
expr_stmt|;
comment|/* Blank/NaN replacement value */
name|trans
operator|.
name|dsttyp
operator|=
literal|'c'
expr_stmt|;
comment|/* Output type is character */
name|nbytes
operator|=
name|hdu
operator|->
name|naxisn
index|[
literal|0
index|]
operator|*
name|hdu
operator|->
name|naxisn
index|[
literal|1
index|]
expr_stmt|;
while|while
condition|(
name|nbytes
operator|>
literal|0
condition|)
block|{
name|maxbytes
operator|=
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|maxbytes
operator|>
name|nbytes
condition|)
name|maxbytes
operator|=
name|nbytes
expr_stmt|;
comment|/* Read pixels and transform them */
if|if
condition|(
name|fits_read_pixel
argument_list|(
name|fitsin
argument_list|,
name|hdu
argument_list|,
name|maxbytes
argument_list|,
operator|&
name|trans
argument_list|,
name|buffer
argument_list|)
operator|!=
name|maxbytes
condition|)
goto|goto
name|err_return
goto|;
if|if
condition|(
name|fwrite
argument_list|(
name|buffer
argument_list|,
literal|1
argument_list|,
name|maxbytes
argument_list|,
name|pgmout
argument_list|)
operator|!=
name|maxbytes
condition|)
goto|goto
name|err_return
goto|;
name|nbytes
operator|-=
name|maxbytes
expr_stmt|;
block|}
name|retval
operator|=
literal|0
expr_stmt|;
name|err_return
label|:
if|if
condition|(
name|fitsin
condition|)
name|fits_close
argument_list|(
name|fitsin
argument_list|)
expr_stmt|;
if|if
condition|(
name|pgmout
condition|)
name|fclose
argument_list|(
name|pgmout
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/*****************************************************************************/
end_comment

begin_comment
comment|/* #BEG-PAR                                                                  */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Function  : pgmraw to fits - convert raw PGM-file to FITS-file            */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* Parameters:                                                               */
end_comment

begin_comment
comment|/* char *pgmfile           [I] : name of pgmfile                             */
end_comment

begin_comment
comment|/* char *fitsfile          [I] : name of fitsfile                            */
end_comment

begin_comment
comment|/*                  ( mode : I=input, O=output, I/O=input/output )           */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* The function converts a raw PGM-file to a FITS-file. The FITS-file will   */
end_comment

begin_comment
comment|/* be upside down, because the orientation for storing the image is          */
end_comment

begin_comment
comment|/* different. On success, 0 is returned. On failure, -1 is returned.         */
end_comment

begin_comment
comment|/*                                                                           */
end_comment

begin_comment
comment|/* #END-PAR                                                                  */
end_comment

begin_comment
comment|/*****************************************************************************/
end_comment

begin_function
name|gint
DECL|function|pgmraw_to_fits (gchar * pgmfile,gchar * fitsfile)
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
block|{
name|FitsFile
modifier|*
name|fitsout
init|=
name|NULL
decl_stmt|;
name|FILE
modifier|*
name|pgmin
init|=
name|NULL
decl_stmt|;
name|FitsHduList
modifier|*
name|hdu
decl_stmt|;
name|gchar
name|buffer
index|[
literal|1024
index|]
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|,
name|numbytes
decl_stmt|,
name|maxbytes
decl_stmt|;
name|gint
name|retval
init|=
operator|-
literal|1
decl_stmt|;
name|fitsout
operator|=
name|fits_open
argument_list|(
name|fitsfile
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
if|if
condition|(
name|fitsout
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
name|pgmin
operator|=
name|g_fopen
argument_list|(
name|pgmfile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pgmin
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
comment|/* Read signature of PGM file */
if|if
condition|(
name|fgets
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|pgmin
argument_list|)
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
if|if
condition|(
operator|(
name|buffer
index|[
literal|0
index|]
operator|!=
literal|'P'
operator|)
operator|||
operator|(
name|buffer
index|[
literal|1
index|]
operator|!=
literal|'5'
operator|)
condition|)
goto|goto
name|err_return
goto|;
comment|/* Skip comments up to width/height */
do|do
block|{
if|if
condition|(
name|fgets
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|pgmin
argument_list|)
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
block|}
do|while
condition|(
name|buffer
index|[
literal|0
index|]
operator|==
literal|'#'
condition|)
do|;
if|if
condition|(
name|sscanf
argument_list|(
name|buffer
argument_list|,
literal|"%d%d"
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
operator|!=
literal|2
condition|)
goto|goto
name|err_return
goto|;
if|if
condition|(
operator|(
name|width
operator|<
literal|1
operator|)
operator|||
operator|(
name|height
operator|<
literal|1
operator|)
condition|)
goto|goto
name|err_return
goto|;
comment|/* Skip comments up to maxval */
do|do
block|{
if|if
condition|(
name|fgets
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|pgmin
argument_list|)
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
block|}
do|while
condition|(
name|buffer
index|[
literal|0
index|]
operator|==
literal|'#'
condition|)
do|;
comment|/* Ignore maxval */
name|hdu
operator|=
name|fits_add_hdu
argument_list|(
name|fitsout
argument_list|)
expr_stmt|;
comment|/* Create a HDU for the FITS file */
if|if
condition|(
name|hdu
operator|==
name|NULL
condition|)
goto|goto
name|err_return
goto|;
name|hdu
operator|->
name|used
operator|.
name|simple
operator|=
literal|1
expr_stmt|;
comment|/* Set proper values */
name|hdu
operator|->
name|bitpix
operator|=
literal|8
expr_stmt|;
name|hdu
operator|->
name|naxis
operator|=
literal|2
expr_stmt|;
name|hdu
operator|->
name|naxisn
index|[
literal|0
index|]
operator|=
name|width
expr_stmt|;
name|hdu
operator|->
name|naxisn
index|[
literal|1
index|]
operator|=
name|height
expr_stmt|;
name|hdu
operator|->
name|used
operator|.
name|datamin
operator|=
literal|1
expr_stmt|;
name|hdu
operator|->
name|datamin
operator|=
literal|0.0
expr_stmt|;
name|hdu
operator|->
name|used
operator|.
name|datamax
operator|=
literal|1
expr_stmt|;
name|hdu
operator|->
name|datamax
operator|=
literal|255.0
expr_stmt|;
name|hdu
operator|->
name|used
operator|.
name|bzero
operator|=
literal|1
expr_stmt|;
name|hdu
operator|->
name|bzero
operator|=
literal|0.0
expr_stmt|;
name|hdu
operator|->
name|used
operator|.
name|bscale
operator|=
literal|1
expr_stmt|;
name|hdu
operator|->
name|bscale
operator|=
literal|1.0
expr_stmt|;
name|fits_add_card
argument_list|(
name|hdu
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|fits_add_card
argument_list|(
name|hdu
argument_list|,
literal|"HISTORY THIS FITS FILE WAS GENERATED BY FITSRW "
literal|"USING PGMRAW_TO_FITS"
argument_list|)
expr_stmt|;
comment|/* Write the header. Blocking is done automatically */
if|if
condition|(
name|fits_write_header
argument_list|(
name|fitsout
argument_list|,
name|hdu
argument_list|)
operator|<
literal|0
condition|)
goto|goto
name|err_return
goto|;
comment|/* The primary array plus blocking must be written manually */
name|numbytes
operator|=
name|width
operator|*
name|height
expr_stmt|;
while|while
condition|(
name|numbytes
operator|>
literal|0
condition|)
block|{
name|maxbytes
operator|=
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|maxbytes
operator|>
name|numbytes
condition|)
name|maxbytes
operator|=
name|numbytes
expr_stmt|;
if|if
condition|(
name|fread
argument_list|(
name|buffer
argument_list|,
literal|1
argument_list|,
name|maxbytes
argument_list|,
name|pgmin
argument_list|)
operator|!=
name|maxbytes
condition|)
goto|goto
name|err_return
goto|;
if|if
condition|(
name|fwrite
argument_list|(
name|buffer
argument_list|,
literal|1
argument_list|,
name|maxbytes
argument_list|,
name|fitsout
operator|->
name|fp
argument_list|)
operator|!=
name|maxbytes
condition|)
goto|goto
name|err_return
goto|;
name|numbytes
operator|-=
name|maxbytes
expr_stmt|;
block|}
comment|/* Do blocking */
name|numbytes
operator|=
operator|(
name|width
operator|*
name|height
operator|)
operator|%
name|FITS_RECORD_SIZE
expr_stmt|;
if|if
condition|(
name|numbytes
condition|)
block|{
while|while
condition|(
name|numbytes
operator|++
operator|<
name|FITS_RECORD_SIZE
condition|)
if|if
condition|(
name|putc
argument_list|(
literal|0
argument_list|,
name|fitsout
operator|->
name|fp
argument_list|)
operator|==
name|EOF
condition|)
goto|goto
name|err_return
goto|;
block|}
name|retval
operator|=
literal|0
expr_stmt|;
name|err_return
label|:
if|if
condition|(
name|fitsout
condition|)
name|fits_close
argument_list|(
name|fitsout
argument_list|)
expr_stmt|;
if|if
condition|(
name|pgmin
condition|)
name|fclose
argument_list|(
name|pgmin
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! FITS_NO_DEMO */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* $Id$ */
end_comment

begin_comment
comment|/* :PREAMBLE: Glace.h  *  * Main header file for GLACE programs:  *    NOTE: This is designed to load your program-specific headers for you  *  *     For PBMPLUS and Tk/Tcl-based and GIMP versions  * #define GLACE_PNM or GLACE_TK or GLACE_GIMP before inclusion  * Automatically includes pgm.h or tk.h, or gimp headers as appropriate.  */
end_comment

begin_comment
comment|/*  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  See the file COPYING for details.  *  */
end_comment

begin_comment
comment|/* :DEFS AND SUCH:  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|_PGM_H_
end_ifdef

begin_error
error|#
directive|error
error|DO NOT LOAD PBMPLUS (OR DERIVATIVE) FIRST
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|_GLACE_H_
end_ifndef

begin_define
DECL|macro|_GLACE_H_
define|#
directive|define
name|_GLACE_H_
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|BUFSIZ
end_ifndef

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GLACE_PNM
end_ifdef

begin_comment
comment|/* pbmpluss.h deals with WATCOMC */
end_comment

begin_include
include|#
directive|include
file|"pbmpluss.h"
end_include

begin_include
include|#
directive|include
file|"pnm.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__WATCOMC__
end_ifdef

begin_define
DECL|macro|__WIN32__
define|#
directive|define
name|__WIN32__
end_define

begin_comment
comment|/*#  define  DllEntryPoint LibMain*/
end_comment

begin_include
include|#
directive|include
file|"glace.wcp"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GLACE_TK
end_ifdef

begin_include
include|#
directive|include
file|"tk.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GLACE_GIMP
end_ifdef

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* This isn't really the right place for this, but... */
end_comment

begin_define
DECL|macro|BYTE_SPLIT (x,hb,lb)
define|#
directive|define
name|BYTE_SPLIT
parameter_list|(
name|x
parameter_list|,
name|hb
parameter_list|,
name|lb
parameter_list|)
define|\
value|lb = (Glace_Gray) (((unsigned int) (x+0.5))& 0377);\ hb = (Glace_Gray) ((((unsigned int) (x+0.5))>>8))
end_define

begin_comment
comment|/*lb = ((Glace_Gray) x);*/
end_comment

begin_comment
comment|/*lb = ((unsigned int) x) - (hb<<8);*/
end_comment

begin_comment
comment|/*  * There is also an internal header file glaceInt.h  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|_OVAR_
end_ifdef

begin_define
DECL|macro|GLACE_OVAR (A)
define|#
directive|define
name|GLACE_OVAR
parameter_list|(
name|A
parameter_list|)
value|A __attribute__ ((unused))
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|GLACE_OVAR (A)
define|#
directive|define
name|GLACE_OVAR
parameter_list|(
name|A
parameter_list|)
value|A
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/**********************************************************************/
end_comment

begin_comment
comment|/* :*** Simple Things ***:  *  * :+++++++: #defines  */
end_comment

begin_define
DECL|macro|GLACE_PI
define|#
directive|define
name|GLACE_PI
value|((double) 3.141592653589793)
end_define

begin_define
DECL|macro|GLACE_TRUE
define|#
directive|define
name|GLACE_TRUE
value|1
end_define

begin_define
DECL|macro|GLACE_FALSE
define|#
directive|define
name|GLACE_FALSE
value|0
end_define

begin_define
DECL|macro|GLACE_BOOL
define|#
directive|define
name|GLACE_BOOL
value|int
end_define

begin_comment
comment|/* avoiding 0, 1, etc. */
end_comment

begin_define
DECL|macro|GLACE_ERROR
define|#
directive|define
name|GLACE_ERROR
value|99
end_define

begin_define
DECL|macro|GLACE_OK
define|#
directive|define
name|GLACE_OK
value|0
end_define

begin_define
DECL|macro|GLACE_STRMAX
define|#
directive|define
name|GLACE_STRMAX
value|100
end_define

begin_define
DECL|macro|GLACE_MIDGRAY
define|#
directive|define
name|GLACE_MIDGRAY
value|((float) 127.5)
end_define

begin_define
DECL|macro|GLACE_MAXMAXGRAY
define|#
directive|define
name|GLACE_MAXMAXGRAY
value|255
end_define

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Grays and colours typedefs  */
end_comment

begin_typedef
DECL|typedef|Glace_BigGray
typedef|typedef
name|signed
name|long
name|Glace_BigGray
typedef|;
end_typedef

begin_typedef
DECL|typedef|Glace_MidGray
typedef|typedef
name|signed
name|short
name|Glace_MidGray
typedef|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|_PGM_H_
end_ifndef

begin_typedef
DECL|typedef|Glace_Gray
typedef|typedef
name|unsigned
name|char
name|Glace_Gray
typedef|;
end_typedef

begin_undef
undef|#
directive|undef
name|max
end_undef

begin_define
DECL|macro|max (a,b)
define|#
directive|define
name|max
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)> (b) ? (a) : (b))
end_define

begin_undef
undef|#
directive|undef
name|min
end_undef

begin_define
DECL|macro|min (a,b)
define|#
directive|define
name|min
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)< (b) ? (a) : (b))
end_define

begin_undef
undef|#
directive|undef
name|abs
end_undef

begin_define
DECL|macro|abs (a)
define|#
directive|define
name|abs
parameter_list|(
name|a
parameter_list|)
value|((a)>= 0 ? (a) : -(a))
end_define

begin_undef
undef|#
directive|undef
name|odd
end_undef

begin_define
DECL|macro|odd (n)
define|#
directive|define
name|odd
parameter_list|(
name|n
parameter_list|)
value|((n)& 1)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|Glace_Gray
define|#
directive|define
name|Glace_Gray
value|gray
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b3e5f710108
block|{
DECL|member|r
DECL|member|g
DECL|member|b
name|Glace_Gray
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
DECL|typedef|Glace_Pixel
block|}
name|Glace_Pixel
typedef|;
end_typedef

begin_define
DECL|macro|GLACE_GETR (p)
define|#
directive|define
name|GLACE_GETR
parameter_list|(
name|p
parameter_list|)
value|((p).r)
end_define

begin_define
DECL|macro|GLACE_GETG (p)
define|#
directive|define
name|GLACE_GETG
parameter_list|(
name|p
parameter_list|)
value|((p).g)
end_define

begin_define
DECL|macro|GLACE_GETB (p)
define|#
directive|define
name|GLACE_GETB
parameter_list|(
name|p
parameter_list|)
value|((p).b)
end_define

begin_comment
comment|/************* added definitions *****************/
end_comment

begin_define
DECL|macro|GLACE_PUTR (p,red)
define|#
directive|define
name|GLACE_PUTR
parameter_list|(
name|p
parameter_list|,
name|red
parameter_list|)
value|((p).r = (red))
end_define

begin_define
DECL|macro|GLACE_PUTG (p,grn)
define|#
directive|define
name|GLACE_PUTG
parameter_list|(
name|p
parameter_list|,
name|grn
parameter_list|)
value|((p).g = (grn))
end_define

begin_define
DECL|macro|GLACE_PUTB (p,blu)
define|#
directive|define
name|GLACE_PUTB
parameter_list|(
name|p
parameter_list|,
name|blu
parameter_list|)
value|((p).b = (blu))
end_define

begin_comment
comment|/**************************************************/
end_comment

begin_define
DECL|macro|GLACE_ASSIGN (p,red,grn,blu)
define|#
directive|define
name|GLACE_ASSIGN
parameter_list|(
name|p
parameter_list|,
name|red
parameter_list|,
name|grn
parameter_list|,
name|blu
parameter_list|)
value|do { (p).r = (red); (p).g = (grn); (p).b = (blu); } while ( 0 )
end_define

begin_comment
comment|/**********************************************************************/
end_comment

begin_comment
comment|/* :*** Structures ***:  *  * :+++++++: Glace_WData.       Wrapper data structure (dummy typedef)  */
end_comment

begin_typedef
DECL|typedef|Glace_WData
typedef|typedef
name|char
modifier|*
name|Glace_WData
typedef|;
end_typedef

begin_comment
comment|/*typedef char Glace_WErrorInfo;*/
end_comment

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Glace_ImgArrays.   Image arrays structure  *  * This is a structure that holds the pointers and defining parameters of  * the image arrays: input, reference, filtering, accumulation, and  * temporary.  The output is done row-by-row.  */
end_comment

begin_comment
comment|/* typedef enum {   GLACE_TMP_IMG_BIG,  GLACE_TMP_IMG_MID } Glace_TmpImgGraySize; */
end_comment

begin_typedef
DECL|typedef|Glace_ImageHandle
typedef|typedef
name|char
modifier|*
name|Glace_ImageHandle
typedef|;
end_typedef

begin_comment
comment|/*  * Structure definition  */
end_comment

begin_typedef
DECL|struct|Glace_ImgArrays
typedef|typedef
struct|struct
name|Glace_ImgArrays
block|{
DECL|member|inputImageHandle
DECL|member|refImageHandle
name|Glace_ImageHandle
name|inputImageHandle
decl_stmt|,
name|refImageHandle
decl_stmt|,
DECL|member|ddHImageHandle
DECL|member|ddVImageHandle
DECL|member|outputImageHandle
name|ddHImageHandle
decl_stmt|,
name|ddVImageHandle
decl_stmt|,
name|outputImageHandle
decl_stmt|;
DECL|member|ddHImgPtr
name|Glace_Gray
modifier|*
name|ddHImgPtr
decl_stmt|,
DECL|member|ddVImgPtr
modifier|*
name|ddVImgPtr
decl_stmt|;
DECL|member|inImgSize
name|long
name|inImgSize
decl_stmt|;
comment|/* Allocated size for input image, 		   taking into account * pixel planes passed on (1 to 5) */
DECL|member|inImgPtr
name|Glace_Gray
modifier|*
name|inImgPtr
decl_stmt|;
comment|/*long inImgBSize;*/
comment|/*  for input gray bytes. 0: not alloc or use inImgPtr 		    *   0: not alloc or use inImgPtr 		    *  *2 if LB+HB (ie doublep) 		    */
DECL|member|inImgHBPtr
name|Glace_Gray
modifier|*
name|inImgHBPtr
decl_stmt|;
DECL|member|inImgLBPtr
name|Glace_Gray
modifier|*
name|inImgLBPtr
decl_stmt|;
comment|/* Some color methods take RGB, others take Yxy. */
comment|/* (The C is to remind you that x,y are coordinates in color space,      and not cartesian pixel coordinates.) */
DECL|member|inImgCxPtr
name|Glace_Gray
modifier|*
name|inImgCxPtr
decl_stmt|;
DECL|member|inImgCyPtr
name|Glace_Gray
modifier|*
name|inImgCyPtr
decl_stmt|;
DECL|member|inImgCYMaxPtr
name|Glace_Gray
modifier|*
name|inImgCYMaxPtr
decl_stmt|;
DECL|member|inImgRPtr
name|Glace_Gray
modifier|*
name|inImgRPtr
decl_stmt|;
DECL|member|inImgGPtr
name|Glace_Gray
modifier|*
name|inImgGPtr
decl_stmt|;
DECL|member|inImgBPtr
name|Glace_Gray
modifier|*
name|inImgBPtr
decl_stmt|;
DECL|member|pixelSize
name|int
name|pixelSize
decl_stmt|;
DECL|member|pixelBytePad
name|int
name|pixelBytePad
decl_stmt|;
comment|/* Set by Glace_WPutImgRowStart or before */
DECL|member|refImgSize
name|long
name|refImgSize
decl_stmt|;
DECL|member|refImgPtr
name|Glace_Gray
modifier|*
name|refImgPtr
decl_stmt|;
comment|/*  long refImgBSize;*/
DECL|member|refImgHBPtr
name|Glace_Gray
modifier|*
name|refImgHBPtr
decl_stmt|;
DECL|member|refImgLBPtr
name|Glace_Gray
modifier|*
name|refImgLBPtr
decl_stmt|;
DECL|member|accImgSize
name|long
name|accImgSize
decl_stmt|;
DECL|member|accImgPtr
name|Glace_MidGray
modifier|*
name|accImgPtr
decl_stmt|;
DECL|member|outAccImgPtr
name|Glace_MidGray
modifier|*
name|outAccImgPtr
decl_stmt|;
comment|/* a dummy pointer that refers to the  				   accumulator array to be output.  This 				   can be other than the true accumulator 				   if a diagnostic image is being 				   generated. */
DECL|member|cols
name|int
name|cols
decl_stmt|;
DECL|member|rows
name|int
name|rows
decl_stmt|;
DECL|member|putImgSize
name|long
name|putImgSize
decl_stmt|;
comment|/* The wrapper can use this how it likes, eg size 		    of a single row or of a whole output image. */
DECL|member|putImgRowPtr
name|Glace_Gray
modifier|*
name|putImgRowPtr
decl_stmt|;
DECL|member|tmpImgSize
name|long
name|tmpImgSize
decl_stmt|;
comment|/* basically internal; in size_t. If zero, then tmp is unallocated. */
DECL|member|tmpImgRPad
DECL|member|tmpImgCPad
name|int
name|tmpImgRPad
decl_stmt|,
name|tmpImgCPad
decl_stmt|;
comment|/*added to rows and cols*/
comment|/*Glace_TmpImgGraySize tmpImgGraySize;*/
DECL|member|tmpImgGraySize
name|size_t
name|tmpImgGraySize
decl_stmt|;
DECL|member|tmpImgPtr
name|char
modifier|*
name|tmpImgPtr
decl_stmt|;
comment|/* Glace_BigGray *bgTmpImgPtr;   Glace_MidGray *mgTmpImgPtr;*/
DECL|member|wData
name|Glace_WData
name|wData
decl_stmt|;
DECL|typedef|Glace_ImgArrays
block|}
name|Glace_ImgArrays
typedef|;
end_typedef

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Glace_CfgInfo.     Configuration information  */
end_comment

begin_define
DECL|macro|GLACE_CFG_DEFAULT_NUM_TERMS
define|#
directive|define
name|GLACE_CFG_DEFAULT_NUM_TERMS
value|240
end_define

begin_define
DECL|macro|GLACE_CFG_DEFAULT_A_WITH_F
define|#
directive|define
name|GLACE_CFG_DEFAULT_A_WITH_F
value|GLACE_NONE
end_define

begin_comment
comment|/*#define GLACE_CFG_DEFAULT_A_WITH_F GLACE_LOCALMEAN*/
end_comment

begin_define
DECL|macro|GLACE_TOL_DOUBLEP
define|#
directive|define
name|GLACE_TOL_DOUBLEP
value|0.00001
end_define

begin_define
DECL|macro|GLACE_TOL_SINGLEP
define|#
directive|define
name|GLACE_TOL_SINGLEP
value|0.0025
end_define

begin_comment
comment|/* Default value is indicated by zero throughout */
end_comment

begin_typedef
DECL|enum|__anon2b3e5f710203
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_AUTO
DECL|enumerator|GLACE_MANUAL
name|GLACE_AUTO
init|=
literal|0
block|,
name|GLACE_MANUAL
DECL|typedef|Glace_Modes
block|}
name|Glace_Modes
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710303
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_MISSING
DECL|enumerator|GLACE_LISTFILE
DECL|enumerator|GLACE_COMMANDLINE
name|GLACE_MISSING
init|=
literal|0
block|,
name|GLACE_LISTFILE
block|,
name|GLACE_COMMANDLINE
DECL|typedef|Glace_DimSrcs
block|}
name|Glace_DimSrcs
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710403
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_NORMAL
DECL|enumerator|GLACE_COSRAW
DECL|enumerator|GLACE_COSFILT
DECL|enumerator|GLACE_SINRAW
DECL|enumerator|GLACE_SINFILT
name|GLACE_NORMAL
init|=
literal|0
block|,
name|GLACE_COSRAW
block|,
name|GLACE_COSFILT
block|,
name|GLACE_SINRAW
block|,
name|GLACE_SINFILT
DECL|typedef|Glace_OutputMethods
block|}
name|Glace_OutputMethods
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710503
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_STANDARD
DECL|enumerator|GLACE_SERIES
DECL|enumerator|GLACE_FACTOR
name|GLACE_STANDARD
init|=
literal|0
block|,
name|GLACE_SERIES
block|,
name|GLACE_FACTOR
DECL|typedef|Glace_HeTypes
block|}
name|Glace_HeTypes
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710603
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_CC
DECL|enumerator|GLACE_CG
DECL|enumerator|GLACE_GG
name|GLACE_CC
init|=
literal|0
block|,
name|GLACE_CG
block|,
name|GLACE_GG
DECL|typedef|Glace_ChromeTypes
block|}
name|Glace_ChromeTypes
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710703
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_WINDOW
DECL|enumerator|GLACE_DIRDIFF
name|GLACE_WINDOW
init|=
literal|0
block|,
name|GLACE_DIRDIFF
DECL|typedef|Glace_FiltMethods
block|}
name|Glace_FiltMethods
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710803
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_INPUT
DECL|enumerator|GLACE_SEPARATE
name|GLACE_INPUT
init|=
literal|0
block|,
name|GLACE_SEPARATE
DECL|typedef|Glace_RefImageModes
block|}
name|Glace_RefImageModes
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710903
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_NONE
DECL|enumerator|GLACE_ZEROINPUT
DECL|enumerator|GLACE_LOCALMEAN
name|GLACE_NONE
init|=
literal|0
block|,
name|GLACE_ZEROINPUT
block|,
name|GLACE_LOCALMEAN
DECL|typedef|Glace_AddbackTypes
block|}
name|Glace_AddbackTypes
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2b3e5f710a03
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_PNM_VER
DECL|enumerator|GLACE_TK_VER
DECL|enumerator|GLACE_GIMP_VER
name|GLACE_PNM_VER
init|=
literal|0
block|,
name|GLACE_TK_VER
block|,
name|GLACE_GIMP_VER
DECL|typedef|Glace_WrapTypes
block|}
name|Glace_WrapTypes
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b3e5f710b03
block|{
DECL|enumerator|GLACE_COLOR_Yxy
DECL|enumerator|GLACE_COLOR_LUMIN
name|GLACE_COLOR_Yxy
init|=
literal|0
block|,
name|GLACE_COLOR_LUMIN
DECL|typedef|Glace_ColorMethods
block|}
name|Glace_ColorMethods
typedef|;
end_typedef

begin_typedef
DECL|struct|Glace_CfgInfo
typedef|typedef
struct|struct
name|Glace_CfgInfo
block|{
DECL|member|wListfile
DECL|member|dListfile
DECL|member|sListfile
name|FILE
modifier|*
name|wListfile
decl_stmt|,
modifier|*
name|dListfile
decl_stmt|,
modifier|*
name|sListfile
decl_stmt|;
DECL|member|outputMethod
name|Glace_OutputMethods
name|outputMethod
decl_stmt|;
DECL|member|numTerms
DECL|member|firstTerm
DECL|member|termsSerialised
name|int
name|numTerms
decl_stmt|,
name|firstTerm
decl_stmt|,
name|termsSerialised
decl_stmt|;
DECL|member|activeTerms
name|unsigned
name|int
name|activeTerms
decl_stmt|;
DECL|member|verbose
name|GLACE_BOOL
name|verbose
decl_stmt|;
DECL|member|hammingCwind
name|GLACE_BOOL
name|hammingCwind
decl_stmt|;
DECL|member|gaussCwind
name|GLACE_BOOL
name|gaussCwind
decl_stmt|;
DECL|member|addbackCwind
name|GLACE_BOOL
name|addbackCwind
decl_stmt|;
DECL|member|doClip
name|GLACE_BOOL
name|doClip
decl_stmt|;
DECL|member|doublep
name|GLACE_BOOL
name|doublep
decl_stmt|;
DECL|member|doubleout
name|GLACE_BOOL
name|doubleout
decl_stmt|;
DECL|member|chrome
name|Glace_ChromeTypes
name|chrome
decl_stmt|;
DECL|member|heType
name|Glace_HeTypes
name|heType
decl_stmt|;
DECL|member|currentSeriesAllocation
name|long
name|currentSeriesAllocation
decl_stmt|;
DECL|member|heseriesSeries
DECL|member|cwindSeries
name|double
modifier|*
name|heseriesSeries
decl_stmt|,
modifier|*
name|cwindSeries
decl_stmt|;
DECL|member|addbackSeries
name|double
modifier|*
name|addbackSeries
decl_stmt|;
DECL|member|windCWSeries
DECL|member|windCHSeries
DECL|member|windSWSeries
DECL|member|windSHSeries
name|int
modifier|*
name|windCWSeries
decl_stmt|,
modifier|*
name|windCHSeries
decl_stmt|,
modifier|*
name|windSWSeries
decl_stmt|,
modifier|*
name|windSHSeries
decl_stmt|;
DECL|member|filtMethod
name|Glace_FiltMethods
name|filtMethod
decl_stmt|;
DECL|member|windBaseW
DECL|member|windBaseH
name|int
name|windBaseW
decl_stmt|,
name|windBaseH
decl_stmt|;
DECL|member|addbackFactor
name|float
name|addbackFactor
decl_stmt|;
comment|/* if dd filtering is used, then we remap arrays */
DECL|macro|GLACE_CFG_COSDIM
define|#
directive|define
name|GLACE_CFG_COSDIM
value|windCWSeries
DECL|macro|GLACE_CFG_COSBV
define|#
directive|define
name|GLACE_CFG_COSBV
value|windCHSeries
DECL|macro|GLACE_CFG_SINDIM
define|#
directive|define
name|GLACE_CFG_SINDIM
value|windSWSeries
DECL|macro|GLACE_CFG_SINBV
define|#
directive|define
name|GLACE_CFG_SINBV
value|windSHSeries
DECL|member|dimensionSrc
name|Glace_DimSrcs
name|dimensionSrc
decl_stmt|;
DECL|member|prescaleMode
name|Glace_Modes
name|prescaleMode
decl_stmt|;
DECL|member|inoffsetMode
name|Glace_Modes
name|inoffsetMode
decl_stmt|;
DECL|member|addbackMode
name|Glace_Modes
name|addbackMode
decl_stmt|;
DECL|member|addbackType
name|Glace_AddbackTypes
name|addbackType
decl_stmt|;
DECL|member|passthruFactor
name|float
name|passthruFactor
decl_stmt|;
DECL|member|prescaleVal
name|float
name|prescaleVal
decl_stmt|;
DECL|member|heFactor
name|float
name|heFactor
decl_stmt|;
DECL|member|inoffsetVal
name|float
name|inoffsetVal
decl_stmt|;
DECL|member|gaussCwindWidth
name|float
name|gaussCwindWidth
decl_stmt|;
DECL|member|coeffTol
name|float
name|coeffTol
decl_stmt|;
DECL|member|colorMethod
name|Glace_ColorMethods
name|colorMethod
decl_stmt|;
DECL|member|refimageMode
name|Glace_RefImageModes
name|refimageMode
decl_stmt|;
DECL|member|genCFunc
name|GLACE_BOOL
name|genCFunc
decl_stmt|;
DECL|member|cFuncMin
DECL|member|cFuncMax
name|float
name|cFuncMin
decl_stmt|,
name|cFuncMax
decl_stmt|;
DECL|member|cFuncPoints
name|int
name|cFuncPoints
decl_stmt|;
DECL|member|wData
name|Glace_WData
name|wData
decl_stmt|;
DECL|member|wrapType
name|Glace_WrapTypes
name|wrapType
decl_stmt|;
DECL|member|plainGlace
name|GLACE_BOOL
name|plainGlace
decl_stmt|;
DECL|typedef|Glace_CfgInfo
block|}
name|Glace_CfgInfo
typedef|;
end_typedef

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Glace_TableInfo.   Term-wise and table information  */
end_comment

begin_typedef
DECL|enum|__anon2b3e5f710c03
typedef|typedef
enum|enum
block|{
DECL|enumerator|GLACE_SIN
DECL|enumerator|GLACE_COS
name|GLACE_SIN
block|,
name|GLACE_COS
DECL|typedef|Glace_TermTypes
block|}
name|Glace_TermTypes
typedef|;
end_typedef

begin_typedef
DECL|typedef|Glace_FpSeries
typedef|typedef
name|double
name|Glace_FpSeries
typedef|;
end_typedef

begin_typedef
DECL|struct|Glace_TableInfo
typedef|typedef
struct|struct
name|Glace_TableInfo
block|{
DECL|member|filtShifts
DECL|member|notFiltShifts
name|int
name|filtShifts
decl_stmt|,
name|notFiltShifts
decl_stmt|;
DECL|member|filtFactor
DECL|member|notFiltFactor
name|float
name|filtFactor
decl_stmt|,
name|notFiltFactor
decl_stmt|;
DECL|member|termType
name|Glace_TermTypes
name|termType
decl_stmt|;
comment|/* which one is being filtered */
DECL|member|termNum
name|unsigned
name|int
name|termNum
decl_stmt|;
comment|/*  long *notFiltTable, *filtTable;*/
DECL|member|seriesTable
name|long
modifier|*
name|seriesTable
decl_stmt|;
DECL|member|accShift
name|int
name|accShift
decl_stmt|;
DECL|member|seriesAH
DECL|member|seriesAL
DECL|member|seriesBH
DECL|member|seriesBL
name|Glace_FpSeries
modifier|*
name|seriesAH
decl_stmt|,
modifier|*
name|seriesAL
decl_stmt|,
modifier|*
name|seriesBH
decl_stmt|,
modifier|*
name|seriesBL
decl_stmt|;
DECL|member|abFactor
DECL|member|abShifts
name|float
name|abFactor
decl_stmt|,
name|abShifts
decl_stmt|;
DECL|member|waveFactor
name|double
name|waveFactor
decl_stmt|;
DECL|member|wData
name|Glace_WData
name|wData
decl_stmt|;
DECL|typedef|Glace_TableInfo
block|}
name|Glace_TableInfo
typedef|;
end_typedef

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Glace_ClientData.  Umbrella clientdata  */
end_comment

begin_typedef
DECL|struct|Glace_ClientData
typedef|typedef
struct|struct
name|Glace_ClientData
block|{
DECL|member|wData
name|Glace_WData
name|wData
decl_stmt|;
DECL|member|cfgInfoPtr
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
decl_stmt|;
DECL|member|tableInfoPtr
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
decl_stmt|;
DECL|member|imgArraysPtr
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
decl_stmt|;
DECL|typedef|Glace_ClientData
block|}
name|Glace_ClientData
typedef|;
end_typedef

begin_if
if|#
directive|if
name|defined
argument_list|(
name|GLACE_IMG
argument_list|)
end_if

begin_undef
undef|#
directive|undef
name|GLACE_IMG
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|GLACE_IMG (A)
define|#
directive|define
name|GLACE_IMG
parameter_list|(
name|A
parameter_list|)
value|(imgArraysPtr->A)
end_define

begin_if
if|#
directive|if
name|defined
argument_list|(
name|GLACE_TRM
argument_list|)
end_if

begin_undef
undef|#
directive|undef
name|GLACE_TRM
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|GLACE_TRM (A)
define|#
directive|define
name|GLACE_TRM
parameter_list|(
name|A
parameter_list|)
value|(tableInfoPtr->A)
end_define

begin_if
if|#
directive|if
name|defined
argument_list|(
name|GLACE_CFG
argument_list|)
end_if

begin_undef
undef|#
directive|undef
name|GLACE_CFG
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|GLACE_CFG (A)
define|#
directive|define
name|GLACE_CFG
parameter_list|(
name|A
parameter_list|)
value|(cfgInfoPtr->A)
end_define

begin_if
if|#
directive|if
name|defined
argument_list|(
name|GLACE_CDATA
argument_list|)
end_if

begin_undef
undef|#
directive|undef
name|GLACE_CDATA
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|GLACE_CDATA (A)
define|#
directive|define
name|GLACE_CDATA
parameter_list|(
name|A
parameter_list|)
value|(((Glace_ClientData *) clientData)->A)
end_define

begin_comment
comment|/**********************************************************************/
end_comment

begin_comment
comment|/* :*** Procedures ***:  *  * :+++++++: Dummy tests  *  * These were originally used as dummy operations (a kind of NOP)  * that used a variable or structure pointer such that the error  * should never occur.  This keeps the compiler happy.  Pointers  * to structures are often unused in some versions, or if they are  * included for future expansion.  *  * Note that these tests could be used in anger, but that the message  * would be non-specific.  */
end_comment

begin_comment
comment|/*  #define GLACE_NULL_TEST(wData,ptr) if (ptr==NULL) \                Glace_WError( wData,"Pointer " \ 	       "null test failed"); #define GLACE_TEST(wData,T) if (T) Glace_WError( wData,\ 						      "Test failure"); */
end_comment

begin_define
DECL|macro|GLACE_ERROR_EXIT (wData)
define|#
directive|define
name|GLACE_ERROR_EXIT
parameter_list|(
name|wData
parameter_list|)
value|if (Glace_WIsError(wData)) \                                        exit(1);
end_define

begin_define
DECL|macro|GLACE_ERROR_CHECK (wData)
define|#
directive|define
name|GLACE_ERROR_CHECK
parameter_list|(
name|wData
parameter_list|)
value|if (Glace_WIsError(wData)) \                                        return;
end_define

begin_define
DECL|macro|GLACE_ERROR_VALUE (wData)
define|#
directive|define
name|GLACE_ERROR_VALUE
parameter_list|(
name|wData
parameter_list|)
value|if (Glace_WIsError(wData)) \                                        return Glace_WErrorValue( wData );
end_define

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Cfg.       Configuration information  */
end_comment

begin_comment
comment|/*  * CONFIG  *  */
end_comment

begin_function_decl
name|void
name|Glace_CfgInit
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_CfgAllocSeriesVectors
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_CfgBeginToHeseries
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_CfgHeseriesToAddback
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_CfgAddbackToEnd
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_CfgFreeSeriesVectors
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: W.         Wrapper-specifics  *  * The following are implemented differently for each wrapper.  * PGM   system:  glaceP.c and   * TK/TCL system: glaceT.c  */
end_comment

begin_comment
comment|/**********************************************************************/
end_comment

begin_comment
comment|/*  * WRAPPER:  *  */
end_comment

begin_function_decl
name|Glace_WData
name|Glace_WDataAlloc
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WInit
parameter_list|(
name|Glace_WData
name|wData
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Glace_WrapTypes
name|Glace_WWrapTell
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WMessage
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|char
modifier|*
name|messageStr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
comment|/* Sets error and returns error flag (but may exit) */
name|Glace_WError
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|char
modifier|*
name|argErrStr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
comment|/* Returns error flag */
name|Glace_WErrorValue
parameter_list|(
name|Glace_WData
name|wData
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
comment|/* Returns boolean */
name|Glace_WIsError
parameter_list|(
name|Glace_WData
name|wData
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*----------*/
end_comment

begin_function_decl
name|void
name|Glace_WPutImgStart
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WPutImgRowStart
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|,
name|int
name|row
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WPutImgRowFinish
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|,
name|int
name|row
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WPutImgFinish
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|Glace_WKeyMatch
parameter_list|(
name|char
modifier|*
name|str
parameter_list|,
name|char
modifier|*
name|keyWord
parameter_list|,
name|int
name|minChars
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WUsage
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|char
modifier|*
name|usage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WOpenImage
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|char
modifier|*
name|name
parameter_list|,
name|Glace_ImageHandle
modifier|*
name|handlePtr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Term-wise and table info  */
end_comment

begin_comment
comment|/* TABLE INFO  *  * This supplies the lookup tables and other related information that is  * specific to the current term being processed.  */
end_comment

begin_function_decl
name|void
name|Glace_SetForTerm
parameter_list|(
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|int
name|k
parameter_list|,
name|Glace_TermTypes
name|type
comment|/* which one is being filtered */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_TermlyReport
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_AllocTables
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_FreeTables
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_SetTables
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_FillTableForFilt
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|float
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_FillTableForNotFilt
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: CFunc.     Cumulation function  */
end_comment

begin_function_decl
name|int
name|Glace_CFuncGen
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|Glace_CFuncPoint
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|float
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|float
name|Glace_CFuncIdealPoint
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|float
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Allocation and reallocation  */
end_comment

begin_comment
comment|/*  * Etc.  */
end_comment

begin_comment
comment|/**************************************************************/
end_comment

begin_function_decl
name|char
modifier|*
name|Glace_CallocReallocFree
parameter_list|(
name|void
modifier|*
name|p
parameter_list|,
name|long
modifier|*
name|nObjPtr
parameter_list|,
name|long
name|newNObj
parameter_list|,
name|size_t
name|size
parameter_list|,
name|float
name|minBound
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_FreeImgArrays
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_SetTmpImg
parameter_list|(
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|,
name|size_t
name|graySize
parameter_list|,
name|int
name|rowPad
parameter_list|,
name|int
name|colPad
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_DefaultTmpImg
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_AllocImgArrays
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_AllocInputImgArrays
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_FreeInputImgArrays
parameter_list|(
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Glace_ClientData
modifier|*
name|Glace_AllocClientData
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_FreeClientData
parameter_list|(
name|Glace_ClientData
modifier|*
name|clientData
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Process procedures  */
end_comment

begin_function_decl
name|void
name|Glace_Process
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* void GlaceArgError (    const char *message,    char *argv[],    int numArgs,    int problemArg    );    */
end_comment

begin_function_decl
name|int
name|Glace_ParseArgs
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|,
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_WindChk
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|int
name|rows
parameter_list|,
name|int
name|cols
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|Glace_Output
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_InitAccIm
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_GenGen
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_DiagGen
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_DiagOutput
parameter_list|(
name|Glace_WData
name|wData
parameter_list|,
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_CallFilt
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|Glace_ImgArrays
modifier|*
name|imgArraysPtr
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Filt.      Filtering  */
end_comment

begin_comment
comment|/**********************************************************************/
end_comment

begin_comment
comment|/*  * FILT  *  * Image array filtering  * Implemented in glaceFilt.c  */
end_comment

begin_function_decl
name|void
name|Glace_FiltWind
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_Gray
modifier|*
name|inImgHBPtr
parameter_list|,
name|Glace_Gray
modifier|*
name|inImgLBPtr
parameter_list|,
name|Glace_BigGray
modifier|*
name|outImgPtr
parameter_list|,
comment|/*signed long *lTable,*/
name|int
name|cols
parameter_list|,
name|int
name|rows
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|Glace_FiltDD
parameter_list|(
name|Glace_CfgInfo
modifier|*
name|cfgInfoPtr
parameter_list|,
name|Glace_Gray
modifier|*
name|inImgPtr
parameter_list|,
name|Glace_MidGray
modifier|*
name|outImgPtr
parameter_list|,
comment|/*signed long *lTable,*/
name|int
name|cols
parameter_list|,
name|int
name|rows
parameter_list|,
name|Glace_TableInfo
modifier|*
name|tableInfoPtr
parameter_list|,
name|Glace_Gray
modifier|*
name|hBiasArray
parameter_list|,
name|Glace_Gray
modifier|*
name|vBiasArray
parameter_list|,
name|int
name|numPasses
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: Heseries.  Generating signed power-law series  */
end_comment

begin_comment
comment|/**********************************************************************/
end_comment

begin_comment
comment|/*  * HESERIES  *  * HE Fourier series generation  * Implemented in glaceHeseries.c  */
end_comment

begin_comment
comment|/* Internal structure.  *  * A dummy definition is used for this structure.  * The caller must preallocate it.  */
end_comment

begin_comment
comment|/* An unreasonable value for the series, used to flag errors */
end_comment

begin_define
DECL|macro|GLACE_HESERIES_ERRORFLAG
define|#
directive|define
name|GLACE_HESERIES_ERRORFLAG
value|(-1000000.0)
end_define

begin_define
DECL|macro|GLACE_HESERIES_RESERVE
define|#
directive|define
name|GLACE_HESERIES_RESERVE
value|100
end_define

begin_typedef
DECL|struct|Glace_HeseriesInfo
typedef|typedef
struct|struct
name|Glace_HeseriesInfo
block|{
DECL|member|dummy
name|char
name|dummy
index|[
name|GLACE_HESERIES_RESERVE
index|]
decl_stmt|;
DECL|typedef|Glace_HeseriesInfo
block|}
name|Glace_HeseriesInfo
typedef|;
end_typedef

begin_function_decl
name|void
name|Glace_HeseriesInit
parameter_list|(
name|Glace_HeseriesInfo
modifier|*
name|heseriesPtr
parameter_list|,
name|float
name|heFactor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|double
name|Glace_HeseriesVal
parameter_list|(
name|Glace_HeseriesInfo
modifier|*
name|heseriesPtr
parameter_list|,
name|int
name|k
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**********************************************************************/
end_comment

begin_comment
comment|/* :*** Wrapper specific data ***:  */
end_comment

begin_if
if|#
directive|if
name|defined
argument_list|(
name|WRAPPER
argument_list|)
end_if

begin_undef
undef|#
directive|undef
name|WRAPPER
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: GLACE_PNM  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|GLACE_PNM
end_ifdef

begin_empty
empty|#
end_empty

begin_typedef
DECL|struct|GlacePnmData
typedef|typedef
struct|struct
name|GlacePnmData
block|{
DECL|member|ddHImgPtrPtr
DECL|member|ddVImgPtrPtr
name|Glace_Gray
modifier|*
modifier|*
name|ddHImgPtrPtr
decl_stmt|,
modifier|*
modifier|*
name|ddVImgPtrPtr
decl_stmt|;
DECL|member|inImgPtrPtr
name|Glace_Gray
modifier|*
modifier|*
name|inImgPtrPtr
decl_stmt|;
DECL|member|refImgPtrPtr
name|Glace_Gray
modifier|*
modifier|*
name|refImgPtrPtr
decl_stmt|;
DECL|member|errorValue
name|int
name|errorValue
decl_stmt|;
DECL|typedef|GlacePnmData
block|}
name|GlacePnmData
typedef|;
end_typedef

begin_empty
empty|#
end_empty

begin_empty
empty|#
end_empty

begin_define
DECL|macro|WRAPPER (A)
define|#
directive|define
name|WRAPPER
parameter_list|(
name|A
parameter_list|)
value|(((GlacePnmData *) wData)->A)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: GLACE_GIMP  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|GLACE_GIMP
end_ifdef

begin_empty
empty|#
end_empty

begin_typedef
DECL|struct|GlaceGimpData
typedef|typedef
struct|struct
name|GlaceGimpData
block|{
comment|/*   Glace_Gray **ddHImgPtrPtr, **ddVImgPtrPtr; */
comment|/*  Glace_Gray **inImgPtrPtr;   / No, I don't have a clue as to how     */
comment|/*  Glace_Gray **refImgPtrPtr;  / much of this is used, or where. [kmt] */
comment|/* [jas]: These are used in PNM to remember pointers to arrays */
DECL|member|dest_row
name|Glace_Gray
modifier|*
name|dest_row
decl_stmt|;
comment|/* Is this a good place to store these things? */
comment|/* [jas]: yes, this is exactly the place! */
DECL|member|dest_rgn_ptr
name|GPixelRgn
name|dest_rgn_ptr
decl_stmt|;
DECL|member|drawable_ptr
name|GDrawable
modifier|*
name|drawable_ptr
decl_stmt|;
DECL|member|gimp_x0
DECL|member|gimp_y0
name|gint32
name|gimp_x0
decl_stmt|,
name|gimp_y0
decl_stmt|;
DECL|member|gimpImgPtr
name|guchar
modifier|*
name|gimpImgPtr
decl_stmt|;
DECL|member|errorValue
name|int
name|errorValue
decl_stmt|;
DECL|typedef|GlaceGimpData
block|}
name|GlaceGimpData
typedef|;
end_typedef

begin_empty
empty|#
end_empty

begin_empty
empty|#
end_empty

begin_define
DECL|macro|WRAPPER (A)
define|#
directive|define
name|WRAPPER
parameter_list|(
name|A
parameter_list|)
value|(((GlaceGimpData *) wData)->A)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*--------------------------------------------------------------------*/
end_comment

begin_comment
comment|/*  * :+++++++: GLACE_TK  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|GLACE_TK
end_ifdef

begin_empty
empty|#
end_empty

begin_typedef
DECL|struct|GlaceTkData
typedef|typedef
struct|struct
name|GlaceTkData
block|{
DECL|member|outputImageBlock
name|Tk_PhotoImageBlock
name|outputImageBlock
decl_stmt|;
DECL|member|outImgPtr
name|Glace_Gray
modifier|*
name|outImgPtr
decl_stmt|;
DECL|member|interp
name|Tcl_Interp
modifier|*
name|interp
decl_stmt|;
DECL|member|errorValue
name|int
name|errorValue
decl_stmt|;
DECL|typedef|GlaceTkData
block|}
name|GlaceTkData
typedef|;
end_typedef

begin_empty
empty|#
end_empty

begin_empty
empty|#
end_empty

begin_define
DECL|macro|WRAPPER (A)
define|#
directive|define
name|WRAPPER
parameter_list|(
name|A
parameter_list|)
value|(((GlaceTkData *) wData)->A)
end_define

begin_define
DECL|macro|INTERP (A)
define|#
directive|define
name|INTERP
parameter_list|(
name|A
parameter_list|)
value|((GlaceTkData *) A)->interp
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* ======================================================================== *\    Copyright (C) 1991, 1992 TWAIN Working Group: Aldus, Caere, Eastman-Kodak,   Hewlett-Packard and Logitech Corporations.  All rights reserved.    Copyright (C) 1997 TWAIN Working Group: Bell+Howell, Canon, DocuMagix,    Fujitsu, Genoa Technology, Hewlett-Packard, Kofax Imaging Products, and   Ricoh Corporation.  All rights reserved.     Copyright © 1998 TWAIN Working Group: Adobe Systems Incorporated,  	Canon Information Systems, Eastman Kodak Company,  	Fujitsu Computer Products of America, Genoa Technology,  	Hewlett-Packard Company, Intel Corporation, Kofax Image Products,  	JFL Peripheral Solutions Inc., Ricoh Corporation, and Xerox Corporation.   	All rights reserved.    TWAIN.h -  This is the definitive include file for applications and           data sources written to the TWAIN specification.           It defines constants, data structures, messages etc.           for the public interface to TWAIN.     Revision History:     version 1.0, March 6, 1992.  TWAIN 1.0.     version 1.1, January 1993.   Tech Notes 1.1     version 1.5, June 1993.      Specification Update 1.5                                  Change DC to TW                                   Change filename from DC.H to TWAIN.H     version 1.5, July 1993.      Remove spaces from country identifiers       version 1.7, July 1997       Added Capabilities and data structure for                                   document imaging and digital cameras.                                  KHL.     version 1.7, July 1997       Inserted Borland compatibile structure packing                                  directives provided by Mentor.  JMH     version 1.7, Aug 1997        Expanded file tabs to spaces.                                    NOTE: future authors should be sure to have                                   their editors set to automatically expand tabs                                   to spaces (original tab setting was 4 spaces).     version 1.7, Sept 1997       Added job control values                                  Added return codes     version 1.7, Sept 1997       changed definition of pRGBRESPONSE to                                   pTW_RGBRESPONSE     version 1.7  Aug 1998        Added missing TWEI_BARCODEROTATION values                                  TWBCOR_ types JMH     version 1.8  August 1998     Added new types and definitions required                                  for 1.8 Specification JMH \* ======================================================================== */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|TWAIN
end_ifndef

begin_define
DECL|macro|TWAIN
define|#
directive|define
name|TWAIN
end_define

begin_comment
comment|/*  SDH - 02/08/95 - TWUNK */
end_comment

begin_comment
comment|/*  Force 32-bit twain to use same packing of twain structures as existing */
end_comment

begin_comment
comment|/*  16-bit twain.  This allows 16/32-bit thunking.                         */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|WIN32
end_ifdef

begin_ifdef
ifdef|#
directive|ifdef
name|__BORLANDC__
end_ifdef

begin_comment
comment|//(Mentor June 13, 1996) if using a Borland compiler
end_comment

begin_pragma
pragma|#
directive|pragma
name|option
name|-
name|a2
end_pragma

begin_comment
comment|//(Mentor June 13, 1996) switch to word alignment
end_comment

begin_else
else|#
directive|else
end_else

begin_comment
comment|//(Mentor June 13, 1996) if we're using some other compiler
end_comment

begin_pragma
pragma|#
directive|pragma
name|pack
name|(
name|push
name|,
name|before_twain
name|)
end_pragma

begin_pragma
pragma|#
directive|pragma
name|pack
name|(
name|2
name|)
end_pragma

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|//(Mentor June 13, 1996)
end_comment

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* WIN32 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* WIN32 */
end_comment

begin_comment
comment|/****************************************************************************  * TWAIN Version                                                            *  ****************************************************************************/
end_comment

begin_define
DECL|macro|TWON_PROTOCOLMINOR
define|#
directive|define
name|TWON_PROTOCOLMINOR
value|8
end_define

begin_comment
DECL|macro|TWON_PROTOCOLMINOR
comment|/* Changed for Version 1.8            */
end_comment

begin_define
DECL|macro|TWON_PROTOCOLMAJOR
define|#
directive|define
name|TWON_PROTOCOLMAJOR
value|1
end_define

begin_comment
comment|/****************************************************************************  * Platform Dependent Definitions and Typedefs                              *  ****************************************************************************/
end_comment

begin_comment
comment|/* Define one of the following, depending on the platform */
end_comment

begin_comment
comment|/* #define _MAC_   */
end_comment

begin_comment
comment|/* #define _UNIX_  */
end_comment

begin_define
DECL|macro|_MSWIN_
define|#
directive|define
name|_MSWIN_
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|_MSWIN_
end_ifdef

begin_typedef
DECL|typedef|TW_HANDLE
typedef|typedef
name|HANDLE
name|TW_HANDLE
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_MEMREF
typedef|typedef
name|LPVOID
name|TW_MEMREF
typedef|;
end_typedef

begin_comment
comment|/*  SDH - 05/05/95 - TWUNK */
end_comment

begin_comment
comment|/*  For common code between 16 and 32 bits.  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|WIN32
end_ifdef

begin_define
DECL|macro|TW_HUGE
define|#
directive|define
name|TW_HUGE
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* WIN32 */
end_comment

begin_define
DECL|macro|TW_HUGE
define|#
directive|define
name|TW_HUGE
value|huge
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* WIN32 */
end_comment

begin_typedef
DECL|typedef|HPBYTE
typedef|typedef
name|BYTE
name|TW_HUGE
modifier|*
name|HPBYTE
typedef|;
end_typedef

begin_typedef
DECL|typedef|HPVOID
typedef|typedef
name|void
name|TW_HUGE
modifier|*
name|HPVOID
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _MSWIN_ */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|_MAC_
end_ifdef

begin_define
DECL|macro|PASCAL
define|#
directive|define
name|PASCAL
value|pascal
end_define

begin_define
DECL|macro|FAR
define|#
directive|define
name|FAR
end_define

begin_typedef
DECL|typedef|TW_HANDLE
typedef|typedef
name|Handle
name|TW_HANDLE
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_MEMREF
typedef|typedef
name|char
modifier|*
name|TW_MEMREF
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _MAC_ */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|_UNIX_
end_ifdef

begin_define
DECL|macro|PASCAL
define|#
directive|define
name|PASCAL
value|pascal
end_define

begin_typedef
DECL|typedef|TW_HANDLE
typedef|typedef
name|unsigned
name|char
modifier|*
name|TW_HANDLE
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_MEMREF
typedef|typedef
name|unsigned
name|char
modifier|*
name|TW_MEMREF
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _UNIX_ */
end_comment

begin_comment
comment|/****************************************************************************  * Type Definitions                                                         *  ****************************************************************************/
end_comment

begin_comment
comment|/* String types. These include room for the strings and a NULL char,     *  * or, on the Mac, a length byte followed by the string.                 *  * TW_STR255 must hold less than 256 chars so length fits in first byte. */
end_comment

begin_typedef
DECL|typedef|TW_STR32
DECL|typedef|pTW_STR32
typedef|typedef
name|char
name|TW_STR32
index|[
literal|34
index|]
typedef|,
name|FAR
modifier|*
name|pTW_STR32
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_STR64
DECL|typedef|pTW_STR64
typedef|typedef
name|char
name|TW_STR64
index|[
literal|66
index|]
typedef|,
name|FAR
modifier|*
name|pTW_STR64
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_STR128
DECL|typedef|pTW_STR128
typedef|typedef
name|char
name|TW_STR128
index|[
literal|130
index|]
typedef|,
name|FAR
modifier|*
name|pTW_STR128
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_STR255
DECL|typedef|pTW_STR255
typedef|typedef
name|char
name|TW_STR255
index|[
literal|256
index|]
typedef|,
name|FAR
modifier|*
name|pTW_STR255
typedef|;
end_typedef

begin_comment
comment|/* Numeric types. */
end_comment

begin_typedef
DECL|typedef|TW_INT8
DECL|typedef|pTW_INT8
typedef|typedef
name|char
name|TW_INT8
typedef|,
name|FAR
modifier|*
name|pTW_INT8
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_INT16
DECL|typedef|pTW_INT16
typedef|typedef
name|short
name|TW_INT16
typedef|,
name|FAR
modifier|*
name|pTW_INT16
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_INT32
DECL|typedef|pTW_INT32
typedef|typedef
name|long
name|TW_INT32
typedef|,
name|FAR
modifier|*
name|pTW_INT32
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_UINT8
DECL|typedef|pTW_UINT8
typedef|typedef
name|unsigned
name|char
name|TW_UINT8
typedef|,
name|FAR
modifier|*
name|pTW_UINT8
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_UINT16
DECL|typedef|pTW_UINT16
typedef|typedef
name|unsigned
name|short
name|TW_UINT16
typedef|,
name|FAR
modifier|*
name|pTW_UINT16
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_UINT32
DECL|typedef|pTW_UINT32
typedef|typedef
name|unsigned
name|long
name|TW_UINT32
typedef|,
name|FAR
modifier|*
name|pTW_UINT32
typedef|;
end_typedef

begin_typedef
DECL|typedef|TW_BOOL
DECL|typedef|pTW_BOOL
typedef|typedef
name|unsigned
name|short
name|TW_BOOL
typedef|,
name|FAR
modifier|*
name|pTW_BOOL
typedef|;
end_typedef

begin_comment
comment|/* Fixed point structure type. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280108
typedef|typedef
struct|struct
block|{
DECL|member|Whole
name|TW_INT16
name|Whole
decl_stmt|;
comment|/* maintains the sign */
DECL|member|Frac
name|TW_UINT16
name|Frac
decl_stmt|;
DECL|typedef|TW_FIX32
DECL|typedef|pTW_FIX32
block|}
name|TW_FIX32
operator|,
name|FAR
modifier|*
name|pTW_FIX32
typedef|;
end_typedef

begin_comment
comment|/****************************************************************************  * Structure Definitions                                                    *  ****************************************************************************/
end_comment

begin_comment
comment|/* No DAT needed. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280208
typedef|typedef
struct|struct
block|{
DECL|member|X
name|TW_FIX32
name|X
decl_stmt|;
DECL|member|Y
name|TW_FIX32
name|Y
decl_stmt|;
DECL|member|Z
name|TW_FIX32
name|Z
decl_stmt|;
DECL|typedef|TW_CIEPOINT
DECL|typedef|pTW_CIEPOINT
block|}
name|TW_CIEPOINT
operator|,
name|FAR
modifier|*
name|pTW_CIEPOINT
typedef|;
end_typedef

begin_comment
comment|/* No DAT needed. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280308
typedef|typedef
struct|struct
block|{
DECL|member|StartIn
name|TW_FIX32
name|StartIn
decl_stmt|;
DECL|member|BreakIn
name|TW_FIX32
name|BreakIn
decl_stmt|;
DECL|member|EndIn
name|TW_FIX32
name|EndIn
decl_stmt|;
DECL|member|StartOut
name|TW_FIX32
name|StartOut
decl_stmt|;
DECL|member|BreakOut
name|TW_FIX32
name|BreakOut
decl_stmt|;
DECL|member|EndOut
name|TW_FIX32
name|EndOut
decl_stmt|;
DECL|member|Gamma
name|TW_FIX32
name|Gamma
decl_stmt|;
DECL|member|SampleCount
name|TW_FIX32
name|SampleCount
decl_stmt|;
comment|/* if =0 use the gamma */
DECL|typedef|TW_DECODEFUNCTION
DECL|typedef|pTW_DECODEFUNCTION
block|}
name|TW_DECODEFUNCTION
operator|,
name|FAR
modifier|*
name|pTW_DECODEFUNCTION
typedef|;
end_typedef

begin_comment
comment|/* No DAT needed. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280408
typedef|typedef
struct|struct
block|{
DECL|member|Index
name|TW_UINT8
name|Index
decl_stmt|;
comment|/* Value used to index into the color table. */
DECL|member|Channel1
name|TW_UINT8
name|Channel1
decl_stmt|;
comment|/* First  tri-stimulus value (e.g Red)       */
DECL|member|Channel2
name|TW_UINT8
name|Channel2
decl_stmt|;
comment|/* Second tri-stimulus value (e.g Green)     */
DECL|member|Channel3
name|TW_UINT8
name|Channel3
decl_stmt|;
comment|/* Third  tri-stimulus value (e.g Blue)      */
DECL|typedef|TW_ELEMENT8
DECL|typedef|pTW_ELEMENT8
block|}
name|TW_ELEMENT8
operator|,
name|FAR
modifier|*
name|pTW_ELEMENT8
typedef|;
end_typedef

begin_comment
comment|/* No DAT.  Defines a frame rectangle in ICAP_UNITS coordinates. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280508
typedef|typedef
struct|struct
block|{
DECL|member|Left
name|TW_FIX32
name|Left
decl_stmt|;
DECL|member|Top
name|TW_FIX32
name|Top
decl_stmt|;
DECL|member|Right
name|TW_FIX32
name|Right
decl_stmt|;
DECL|member|Bottom
name|TW_FIX32
name|Bottom
decl_stmt|;
DECL|typedef|TW_FRAME
DECL|typedef|pTW_FRAME
block|}
name|TW_FRAME
operator|,
name|FAR
modifier|*
name|pTW_FRAME
typedef|;
end_typedef

begin_comment
comment|/* No DAT needed.  Used to manage memory buffers. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280608
typedef|typedef
struct|struct
block|{
DECL|member|Flags
name|TW_UINT32
name|Flags
decl_stmt|;
comment|/* Any combination of the TWMF_ constants.           */
DECL|member|Length
name|TW_UINT32
name|Length
decl_stmt|;
comment|/* Number of bytes stored in buffer TheMem.          */
DECL|member|TheMem
name|TW_MEMREF
name|TheMem
decl_stmt|;
comment|/* Pointer or handle to the allocated memory buffer. */
DECL|typedef|TW_MEMORY
DECL|typedef|pTW_MEMORY
block|}
name|TW_MEMORY
operator|,
name|FAR
modifier|*
name|pTW_MEMORY
typedef|;
end_typedef

begin_comment
comment|/* No DAT needed. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280708
typedef|typedef
struct|struct
block|{
DECL|member|Decode
name|TW_DECODEFUNCTION
name|Decode
index|[
literal|3
index|]
decl_stmt|;
DECL|member|Mix
name|TW_FIX32
name|Mix
index|[
literal|3
index|]
index|[
literal|3
index|]
decl_stmt|;
DECL|typedef|TW_TRANSFORMSTAGE
DECL|typedef|pTW_TRANSFORMSTAGE
block|}
name|TW_TRANSFORMSTAGE
operator|,
name|FAR
modifier|*
name|pTW_TRANSFORMSTAGE
typedef|;
end_typedef

begin_comment
comment|/* No DAT needed.  Describes version of software currently running. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280808
typedef|typedef
struct|struct
block|{
DECL|member|MajorNum
name|TW_UINT16
name|MajorNum
decl_stmt|;
comment|/* Major revision number of the software. */
DECL|member|MinorNum
name|TW_UINT16
name|MinorNum
decl_stmt|;
comment|/* Incremental revision number of the software. */
DECL|member|Language
name|TW_UINT16
name|Language
decl_stmt|;
comment|/* e.g. TWLG_SWISSFRENCH */
DECL|member|Country
name|TW_UINT16
name|Country
decl_stmt|;
comment|/* e.g. TWCY_SWITZERLAND */
DECL|member|Info
name|TW_STR32
name|Info
decl_stmt|;
comment|/* e.g. "1.0b3 Beta release" */
DECL|typedef|TW_VERSION
DECL|typedef|pTW_VERSION
block|}
name|TW_VERSION
operator|,
name|FAR
modifier|*
name|pTW_VERSION
typedef|;
end_typedef

begin_comment
comment|/* TWON_ARRAY. Container for array of values (a simplified TW_ENUMERATION) */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280908
typedef|typedef
struct|struct
block|{
DECL|member|ItemType
name|TW_UINT16
name|ItemType
decl_stmt|;
DECL|member|NumItems
name|TW_UINT32
name|NumItems
decl_stmt|;
comment|/* How many items in ItemList           */
DECL|member|ItemList
name|TW_UINT8
name|ItemList
index|[
literal|1
index|]
decl_stmt|;
comment|/* Array of ItemType values starts here */
DECL|typedef|TW_ARRAY
DECL|typedef|pTW_ARRAY
block|}
name|TW_ARRAY
operator|,
name|FAR
modifier|*
name|pTW_ARRAY
typedef|;
end_typedef

begin_comment
comment|/* TWON_ENUMERATION. Container for a collection of values. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280a08
typedef|typedef
struct|struct
block|{
DECL|member|ItemType
name|TW_UINT16
name|ItemType
decl_stmt|;
DECL|member|NumItems
name|TW_UINT32
name|NumItems
decl_stmt|;
comment|/* How many items in ItemList                 */
DECL|member|CurrentIndex
name|TW_UINT32
name|CurrentIndex
decl_stmt|;
comment|/* Current value is in ItemList[CurrentIndex] */
DECL|member|DefaultIndex
name|TW_UINT32
name|DefaultIndex
decl_stmt|;
comment|/* Powerup value is in ItemList[DefaultIndex] */
DECL|member|ItemList
name|TW_UINT8
name|ItemList
index|[
literal|1
index|]
decl_stmt|;
comment|/* Array of ItemType values starts here       */
DECL|typedef|TW_ENUMERATION
DECL|typedef|pTW_ENUMERATION
block|}
name|TW_ENUMERATION
operator|,
name|FAR
modifier|*
name|pTW_ENUMERATION
typedef|;
end_typedef

begin_comment
comment|/* TWON_ONEVALUE. Container for one value. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280b08
typedef|typedef
struct|struct
block|{
DECL|member|ItemType
name|TW_UINT16
name|ItemType
decl_stmt|;
DECL|member|Item
name|TW_UINT32
name|Item
decl_stmt|;
DECL|typedef|TW_ONEVALUE
DECL|typedef|pTW_ONEVALUE
block|}
name|TW_ONEVALUE
operator|,
name|FAR
modifier|*
name|pTW_ONEVALUE
typedef|;
end_typedef

begin_comment
comment|/* TWON_RANGE. Container for a range of values. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280c08
typedef|typedef
struct|struct
block|{
DECL|member|ItemType
name|TW_UINT16
name|ItemType
decl_stmt|;
DECL|member|MinValue
name|TW_UINT32
name|MinValue
decl_stmt|;
comment|/* Starting value in the range.           */
DECL|member|MaxValue
name|TW_UINT32
name|MaxValue
decl_stmt|;
comment|/* Final value in the range.              */
DECL|member|StepSize
name|TW_UINT32
name|StepSize
decl_stmt|;
comment|/* Increment from MinValue to MaxValue.   */
DECL|member|DefaultValue
name|TW_UINT32
name|DefaultValue
decl_stmt|;
comment|/* Power-up value.                        */
DECL|member|CurrentValue
name|TW_UINT32
name|CurrentValue
decl_stmt|;
comment|/* The value that is currently in effect. */
DECL|typedef|TW_RANGE
DECL|typedef|pTW_RANGE
block|}
name|TW_RANGE
operator|,
name|FAR
modifier|*
name|pTW_RANGE
typedef|;
end_typedef

begin_comment
comment|/* DAT_CAPABILITY. Used by application to get/set capability from/in a data source. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280d08
typedef|typedef
struct|struct
block|{
DECL|member|Cap
name|TW_UINT16
name|Cap
decl_stmt|;
comment|/* id of capability to set or get, e.g. CAP_BRIGHTNESS */
DECL|member|ConType
name|TW_UINT16
name|ConType
decl_stmt|;
comment|/* TWON_ONEVALUE, _RANGE, _ENUMERATION or _ARRAY   */
DECL|member|hContainer
name|TW_HANDLE
name|hContainer
decl_stmt|;
comment|/* Handle to container of type Dat              */
DECL|typedef|TW_CAPABILITY
DECL|typedef|pTW_CAPABILITY
block|}
name|TW_CAPABILITY
operator|,
name|FAR
modifier|*
name|pTW_CAPABILITY
typedef|;
end_typedef

begin_comment
comment|/* DAT_CIECOLOR. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280e08
typedef|typedef
struct|struct
block|{
DECL|member|ColorSpace
name|TW_UINT16
name|ColorSpace
decl_stmt|;
DECL|member|LowEndian
name|TW_INT16
name|LowEndian
decl_stmt|;
DECL|member|DeviceDependent
name|TW_INT16
name|DeviceDependent
decl_stmt|;
DECL|member|VersionNumber
name|TW_INT32
name|VersionNumber
decl_stmt|;
DECL|member|StageABC
name|TW_TRANSFORMSTAGE
name|StageABC
decl_stmt|;
DECL|member|StageLMN
name|TW_TRANSFORMSTAGE
name|StageLMN
decl_stmt|;
DECL|member|WhitePoint
name|TW_CIEPOINT
name|WhitePoint
decl_stmt|;
DECL|member|BlackPoint
name|TW_CIEPOINT
name|BlackPoint
decl_stmt|;
DECL|member|WhitePaper
name|TW_CIEPOINT
name|WhitePaper
decl_stmt|;
DECL|member|BlackInk
name|TW_CIEPOINT
name|BlackInk
decl_stmt|;
DECL|member|Samples
name|TW_FIX32
name|Samples
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|TW_CIECOLOR
DECL|typedef|pTW_CIECOLOR
block|}
name|TW_CIECOLOR
operator|,
name|FAR
modifier|*
name|pTW_CIECOLOR
typedef|;
end_typedef

begin_comment
comment|/* DAT_EVENT. For passing events down from the application to the DS. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22280f08
typedef|typedef
struct|struct
block|{
DECL|member|pEvent
name|TW_MEMREF
name|pEvent
decl_stmt|;
comment|/* Windows pMSG or Mac pEvent.                 */
DECL|member|TWMessage
name|TW_UINT16
name|TWMessage
decl_stmt|;
comment|/* TW msg from data source, e.g. MSG_XFERREADY */
DECL|typedef|TW_EVENT
DECL|typedef|pTW_EVENT
block|}
name|TW_EVENT
operator|,
name|FAR
modifier|*
name|pTW_EVENT
typedef|;
end_typedef

begin_comment
comment|/* DAT_GRAYRESPONSE */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281008
typedef|typedef
struct|struct
block|{
DECL|member|Response
name|TW_ELEMENT8
name|Response
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|TW_GRAYRESPONSE
DECL|typedef|pTW_GRAYRESPONSE
block|}
name|TW_GRAYRESPONSE
operator|,
name|FAR
modifier|*
name|pTW_GRAYRESPONSE
typedef|;
end_typedef

begin_comment
comment|/* DAT_IDENTITY. Identifies the program/library/code resource. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281108
typedef|typedef
struct|struct
block|{
DECL|member|Id
name|TW_UINT32
name|Id
decl_stmt|;
comment|/* Unique number.  In Windows, application hWnd      */
DECL|member|Version
name|TW_VERSION
name|Version
decl_stmt|;
comment|/* Identifies the piece of code              */
DECL|member|ProtocolMajor
name|TW_UINT16
name|ProtocolMajor
decl_stmt|;
comment|/* Application and DS must set to TWON_PROTOCOLMAJOR */
DECL|member|ProtocolMinor
name|TW_UINT16
name|ProtocolMinor
decl_stmt|;
comment|/* Application and DS must set to TWON_PROTOCOLMINOR */
DECL|member|SupportedGroups
name|TW_UINT32
name|SupportedGroups
decl_stmt|;
comment|/* Bit field OR combination of DG_ constants */
DECL|member|Manufacturer
name|TW_STR32
name|Manufacturer
decl_stmt|;
comment|/* Manufacturer name, e.g. "Hewlett-Packard" */
DECL|member|ProductFamily
name|TW_STR32
name|ProductFamily
decl_stmt|;
comment|/* Product family name, e.g. "ScanJet"       */
DECL|member|ProductName
name|TW_STR32
name|ProductName
decl_stmt|;
comment|/* Product name, e.g. "ScanJet Plus"         */
DECL|typedef|TW_IDENTITY
DECL|typedef|pTW_IDENTITY
block|}
name|TW_IDENTITY
operator|,
name|FAR
modifier|*
name|pTW_IDENTITY
typedef|;
end_typedef

begin_comment
comment|/* DAT_IMAGEINFO. Application gets detailed image info from DS with this. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281208
typedef|typedef
struct|struct
block|{
DECL|member|XResolution
name|TW_FIX32
name|XResolution
decl_stmt|;
comment|/* Resolution in the horizontal             */
DECL|member|YResolution
name|TW_FIX32
name|YResolution
decl_stmt|;
comment|/* Resolution in the vertical               */
DECL|member|ImageWidth
name|TW_INT32
name|ImageWidth
decl_stmt|;
comment|/* Columns in the image, -1 if unknown by DS*/
DECL|member|ImageLength
name|TW_INT32
name|ImageLength
decl_stmt|;
comment|/* Rows in the image, -1 if unknown by DS   */
DECL|member|SamplesPerPixel
name|TW_INT16
name|SamplesPerPixel
decl_stmt|;
comment|/* Number of samples per pixel, 3 for RGB   */
DECL|member|BitsPerSample
name|TW_INT16
name|BitsPerSample
index|[
literal|8
index|]
decl_stmt|;
comment|/* Number of bits for each sample           */
DECL|member|BitsPerPixel
name|TW_INT16
name|BitsPerPixel
decl_stmt|;
comment|/* Number of bits for each padded pixel     */
DECL|member|Planar
name|TW_BOOL
name|Planar
decl_stmt|;
comment|/* True if Planar, False if chunky          */
DECL|member|PixelType
name|TW_INT16
name|PixelType
decl_stmt|;
comment|/* How to interp data; photo interp (TWPT_) */
DECL|member|Compression
name|TW_UINT16
name|Compression
decl_stmt|;
comment|/* How the data is compressed (TWCP_xxxx)   */
DECL|typedef|TW_IMAGEINFO
DECL|typedef|pTW_IMAGEINFO
block|}
name|TW_IMAGEINFO
operator|,
name|FAR
modifier|*
name|pTW_IMAGEINFO
typedef|;
end_typedef

begin_comment
comment|/* DAT_IMAGELAYOUT. Provides image layout information in current units. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281308
typedef|typedef
struct|struct
block|{
DECL|member|Frame
name|TW_FRAME
name|Frame
decl_stmt|;
comment|/* Frame coords within larger document */
DECL|member|DocumentNumber
name|TW_UINT32
name|DocumentNumber
decl_stmt|;
DECL|member|PageNumber
name|TW_UINT32
name|PageNumber
decl_stmt|;
comment|/* Reset when you go to next document  */
DECL|member|FrameNumber
name|TW_UINT32
name|FrameNumber
decl_stmt|;
comment|/* Reset when you go to next page      */
DECL|typedef|TW_IMAGELAYOUT
DECL|typedef|pTW_IMAGELAYOUT
block|}
name|TW_IMAGELAYOUT
operator|,
name|FAR
modifier|*
name|pTW_IMAGELAYOUT
typedef|;
end_typedef

begin_comment
comment|/* DAT_IMAGEMEMXFER. Used to pass image data (e.g. in strips) from DS to application.*/
end_comment

begin_typedef
DECL|struct|__anon2b4c22281408
typedef|typedef
struct|struct
block|{
DECL|member|Compression
name|TW_UINT16
name|Compression
decl_stmt|;
comment|/* How the data is compressed                */
DECL|member|BytesPerRow
name|TW_UINT32
name|BytesPerRow
decl_stmt|;
comment|/* Number of bytes in a row of data          */
DECL|member|Columns
name|TW_UINT32
name|Columns
decl_stmt|;
comment|/* How many columns                          */
DECL|member|Rows
name|TW_UINT32
name|Rows
decl_stmt|;
comment|/* How many rows                             */
DECL|member|XOffset
name|TW_UINT32
name|XOffset
decl_stmt|;
comment|/* How far from the side of the image        */
DECL|member|YOffset
name|TW_UINT32
name|YOffset
decl_stmt|;
comment|/* How far from the top of the image         */
DECL|member|BytesWritten
name|TW_UINT32
name|BytesWritten
decl_stmt|;
comment|/* How many bytes written in Memory          */
DECL|member|Memory
name|TW_MEMORY
name|Memory
decl_stmt|;
comment|/* Mem struct used to pass actual image data */
DECL|typedef|TW_IMAGEMEMXFER
DECL|typedef|pTW_IMAGEMEMXFER
block|}
name|TW_IMAGEMEMXFER
operator|,
name|FAR
modifier|*
name|pTW_IMAGEMEMXFER
typedef|;
end_typedef

begin_comment
comment|/* Changed in 1.1: QuantTable, HuffmanDC, HuffmanAC TW_MEMREF -> TW_MEMORY  */
end_comment

begin_comment
comment|/* DAT_JPEGCOMPRESSION. Based on JPEG Draft International Std, ver 10918-1. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281508
typedef|typedef
struct|struct
block|{
DECL|member|ColorSpace
name|TW_UINT16
name|ColorSpace
decl_stmt|;
comment|/* One of the TWPT_xxxx values                */
DECL|member|SubSampling
name|TW_UINT32
name|SubSampling
decl_stmt|;
comment|/* Two word "array" for subsampling values    */
DECL|member|NumComponents
name|TW_UINT16
name|NumComponents
decl_stmt|;
comment|/* Number of color components in image        */
DECL|member|RestartFrequency
name|TW_UINT16
name|RestartFrequency
decl_stmt|;
comment|/* Frequency of restart marker codes in MDU's */
DECL|member|QuantMap
name|TW_UINT16
name|QuantMap
index|[
literal|4
index|]
decl_stmt|;
comment|/* Mapping of components to QuantTables       */
DECL|member|QuantTable
name|TW_MEMORY
name|QuantTable
index|[
literal|4
index|]
decl_stmt|;
comment|/* Quantization tables                        */
DECL|member|HuffmanMap
name|TW_UINT16
name|HuffmanMap
index|[
literal|4
index|]
decl_stmt|;
comment|/* Mapping of components to Huffman tables    */
DECL|member|HuffmanDC
name|TW_MEMORY
name|HuffmanDC
index|[
literal|2
index|]
decl_stmt|;
comment|/* DC Huffman tables                          */
DECL|member|HuffmanAC
name|TW_MEMORY
name|HuffmanAC
index|[
literal|2
index|]
decl_stmt|;
comment|/* AC Huffman tables                          */
DECL|typedef|TW_JPEGCOMPRESSION
DECL|typedef|pTW_JPEGCOMPRESSION
block|}
name|TW_JPEGCOMPRESSION
operator|,
name|FAR
modifier|*
name|pTW_JPEGCOMPRESSION
typedef|;
end_typedef

begin_comment
comment|/* DAT_PALETTE8. Color palette when TWPT_PALETTE pixels xfer'd in mem buf. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281608
typedef|typedef
struct|struct
block|{
DECL|member|NumColors
name|TW_UINT16
name|NumColors
decl_stmt|;
comment|/* Number of colors in the color table.  */
DECL|member|PaletteType
name|TW_UINT16
name|PaletteType
decl_stmt|;
comment|/* TWPA_xxxx, specifies type of palette. */
DECL|member|Colors
name|TW_ELEMENT8
name|Colors
index|[
literal|256
index|]
decl_stmt|;
comment|/* Array of palette values starts here.  */
DECL|typedef|TW_PALETTE8
DECL|typedef|pTW_PALETTE8
block|}
name|TW_PALETTE8
operator|,
name|FAR
modifier|*
name|pTW_PALETTE8
typedef|;
end_typedef

begin_comment
comment|/* DAT_PENDINGXFERS. Used with MSG_ENDXFER to indicate additional data. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281708
typedef|typedef
struct|struct
block|{
DECL|member|Count
name|TW_UINT16
name|Count
decl_stmt|;
DECL|union|__anon2b4c2228180a
union|union
block|{
DECL|member|EOJ
name|TW_UINT32
name|EOJ
decl_stmt|;
DECL|member|Reserved
name|TW_UINT32
name|Reserved
decl_stmt|;
block|}
union|;
DECL|typedef|TW_PENDINGXFERS
DECL|typedef|pTW_PENDINGXFERS
block|}
name|TW_PENDINGXFERS
operator|,
name|FAR
modifier|*
name|pTW_PENDINGXFERS
typedef|;
end_typedef

begin_comment
comment|/* DAT_RGBRESPONSE */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281908
typedef|typedef
struct|struct
block|{
DECL|member|Response
name|TW_ELEMENT8
name|Response
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|TW_RGBRESPONSE
DECL|typedef|pTW_RGBRESPONSE
block|}
name|TW_RGBRESPONSE
operator|,
name|FAR
modifier|*
name|pTW_RGBRESPONSE
typedef|;
end_typedef

begin_comment
comment|/* DAT_SETUPFILEXFER. Sets up DS to application data transfer via a file. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281a08
typedef|typedef
struct|struct
block|{
DECL|member|FileName
name|TW_STR255
name|FileName
decl_stmt|;
DECL|member|Format
name|TW_UINT16
name|Format
decl_stmt|;
comment|/* Any TWFF_ constant */
DECL|member|VRefNum
name|TW_INT16
name|VRefNum
decl_stmt|;
comment|/* Used for Mac only  */
DECL|typedef|TW_SETUPFILEXFER
DECL|typedef|pTW_SETUPFILEXFER
block|}
name|TW_SETUPFILEXFER
operator|,
name|FAR
modifier|*
name|pTW_SETUPFILEXFER
typedef|;
end_typedef

begin_comment
comment|/* DAT_SETUPMEMXFER. Sets up DS to application data transfer via a memory buffer. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281b08
typedef|typedef
struct|struct
block|{
DECL|member|MinBufSize
name|TW_UINT32
name|MinBufSize
decl_stmt|;
DECL|member|MaxBufSize
name|TW_UINT32
name|MaxBufSize
decl_stmt|;
DECL|member|Preferred
name|TW_UINT32
name|Preferred
decl_stmt|;
DECL|typedef|TW_SETUPMEMXFER
DECL|typedef|pTW_SETUPMEMXFER
block|}
name|TW_SETUPMEMXFER
operator|,
name|FAR
modifier|*
name|pTW_SETUPMEMXFER
typedef|;
end_typedef

begin_comment
comment|/* DAT_STATUS. Application gets detailed status info from a data source with this. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281c08
typedef|typedef
struct|struct
block|{
DECL|member|ConditionCode
name|TW_UINT16
name|ConditionCode
decl_stmt|;
comment|/* Any TWCC_ constant     */
DECL|member|Reserved
name|TW_UINT16
name|Reserved
decl_stmt|;
comment|/* Future expansion space */
DECL|typedef|TW_STATUS
DECL|typedef|pTW_STATUS
block|}
name|TW_STATUS
operator|,
name|FAR
modifier|*
name|pTW_STATUS
typedef|;
end_typedef

begin_comment
comment|/* DAT_USERINTERFACE. Coordinates UI between application and data source. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281d08
typedef|typedef
struct|struct
block|{
DECL|member|ShowUI
name|TW_BOOL
name|ShowUI
decl_stmt|;
comment|/* TRUE if DS should bring up its UI           */
DECL|member|ModalUI
name|TW_BOOL
name|ModalUI
decl_stmt|;
comment|/* For Mac only - true if the DS's UI is modal */
DECL|member|hParent
name|TW_HANDLE
name|hParent
decl_stmt|;
comment|/* For windows only - Application window handle        */
DECL|typedef|TW_USERINTERFACE
DECL|typedef|pTW_USERINTERFACE
block|}
name|TW_USERINTERFACE
operator|,
name|FAR
modifier|*
name|pTW_USERINTERFACE
typedef|;
end_typedef

begin_comment
comment|/* SDH - 03/21/95 - TWUNK */
end_comment

begin_comment
comment|/* DAT_TWUNKIDENTITY. Provides DS identity and 'other' information necessary */
end_comment

begin_comment
comment|/*                    across thunk link. */
end_comment

begin_typedef
DECL|struct|__anon2b4c22281e08
typedef|typedef
struct|struct
block|{
DECL|member|identity
name|TW_IDENTITY
name|identity
decl_stmt|;
comment|/* Identity of data source.                 */
DECL|member|dsPath
name|TW_STR255
name|dsPath
decl_stmt|;
comment|/* Full path and file name of data source.  */
DECL|typedef|TW_TWUNKIDENTITY
DECL|typedef|pTW_TWUNKIDENTITY
block|}
name|TW_TWUNKIDENTITY
operator|,
name|FAR
modifier|*
name|pTW_TWUNKIDENTITY
typedef|;
end_typedef

begin_comment
comment|/* SDH - 03/21/95 - TWUNK */
end_comment

begin_comment
comment|/* Provides DS_Entry parameters over thunk link. */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b4c22281f08
block|{
DECL|member|destFlag
name|TW_INT8
name|destFlag
decl_stmt|;
comment|/* TRUE if dest is not NULL                 */
DECL|member|dest
name|TW_IDENTITY
name|dest
decl_stmt|;
comment|/* Identity of data source (if used)        */
DECL|member|dataGroup
name|TW_INT32
name|dataGroup
decl_stmt|;
comment|/* DSM_Entry dataGroup parameter            */
DECL|member|dataArgType
name|TW_INT16
name|dataArgType
decl_stmt|;
comment|/* DSM_Entry dataArgType parameter          */
DECL|member|message
name|TW_INT16
name|message
decl_stmt|;
comment|/* DSM_Entry message parameter              */
DECL|member|pDataSize
name|TW_INT32
name|pDataSize
decl_stmt|;
comment|/* Size of pData (0 if NULL)                */
comment|//  TW_MEMREF   pData;      /* Based on implementation specifics, a     */
comment|/* pData parameter makes no sense in this   */
comment|/* structure, but data (if provided) will be*/
comment|/* appended in the data block.              */
DECL|typedef|TW_TWUNKDSENTRYPARAMS
DECL|typedef|pTW_TWUNKDSENTRYPARAMS
block|}
name|TW_TWUNKDSENTRYPARAMS
operator|,
name|FAR
modifier|*
name|pTW_TWUNKDSENTRYPARAMS
typedef|;
end_typedef

begin_comment
comment|/* SDH - 03/21/95 - TWUNK */
end_comment

begin_comment
comment|/* Provides DS_Entry results over thunk link. */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b4c22282008
block|{
DECL|member|returnCode
name|TW_UINT16
name|returnCode
decl_stmt|;
comment|/* Thunker DsEntry return code.             */
DECL|member|conditionCode
name|TW_UINT16
name|conditionCode
decl_stmt|;
comment|/* Thunker DsEntry condition code.          */
DECL|member|pDataSize
name|TW_INT32
name|pDataSize
decl_stmt|;
comment|/* Size of pData (0 if NULL)                */
comment|//  TW_MEMREF   pData;      /* Based on implementation specifics, a     */
comment|/* pData parameter makes no sense in this   */
comment|/* structure, but data (if provided) will be*/
comment|/* appended in the data block.              */
DECL|typedef|TW_TWUNKDSENTRYRETURN
DECL|typedef|pTW_TWUNKDSENTRYRETURN
block|}
name|TW_TWUNKDSENTRYRETURN
operator|,
name|FAR
modifier|*
name|pTW_TWUNKDSENTRYRETURN
typedef|;
end_typedef

begin_comment
comment|/* WJD - 950818 */
end_comment

begin_comment
comment|/* Added for 1.6 Specification */
end_comment

begin_comment
comment|/* TWAIN 1.6 CAP_SUPPORTEDCAPSEXT structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b4c22282108
block|{
DECL|member|Cap
name|TW_UINT16
name|Cap
decl_stmt|;
comment|/* Which CAP/ICAP info is relevant to */
DECL|member|Properties
name|TW_UINT16
name|Properties
decl_stmt|;
comment|/* Messages this CAP/ICAP supports */
DECL|typedef|TW_CAPEXT
DECL|typedef|pTW_CAPEXT
block|}
name|TW_CAPEXT
operator|,
name|FAR
modifier|*
name|pTW_CAPEXT
typedef|;
end_typedef

begin_comment
comment|/* ----------------------------------------------------------------------- *\    Version 1.7:      Added Following data structure for Document Imaging    July 1997         Enhancement.   KHL               TW_CUSTOMDSDATA --  For Saving and Restoring Source's                                          state.                     TW_INFO         --  Each attribute for extended image                                         information.                     TW_EXTIMAGEINFO --  Extended image information structure.  \* ----------------------------------------------------------------------- */
end_comment

begin_typedef
DECL|struct|__anon2b4c22282208
typedef|typedef
struct|struct
block|{
DECL|member|InfoLength
name|TW_UINT32
name|InfoLength
decl_stmt|;
comment|/* Length of Information in bytes.  */
DECL|member|hData
name|TW_HANDLE
name|hData
decl_stmt|;
comment|/* Place holder for data, DS Allocates */
DECL|typedef|TW_CUSTOMDSDATA
DECL|typedef|pTW_CUSTOMDSDATA
block|}
name|TW_CUSTOMDSDATA
operator|,
name|FAR
modifier|*
name|pTW_CUSTOMDSDATA
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b4c22282308
typedef|typedef
struct|struct
block|{
DECL|member|InfoID
name|TW_UINT16
name|InfoID
decl_stmt|;
DECL|member|ItemType
name|TW_UINT16
name|ItemType
decl_stmt|;
DECL|member|NumItems
name|TW_UINT16
name|NumItems
decl_stmt|;
DECL|member|CondCode
name|TW_UINT16
name|CondCode
decl_stmt|;
DECL|member|Item
name|TW_UINT32
name|Item
decl_stmt|;
DECL|typedef|TW_INFO
DECL|typedef|pTW_INFO
block|}
name|TW_INFO
operator|,
name|FAR
modifier|*
name|pTW_INFO
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b4c22282408
typedef|typedef
struct|struct
block|{
DECL|member|NumInfos
name|TW_UINT32
name|NumInfos
decl_stmt|;
DECL|member|Info
name|TW_INFO
name|Info
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|TW_EXTIMAGEINFO
DECL|typedef|pTW_EXTIMAGEINFO
block|}
name|TW_EXTIMAGEINFO
operator|,
name|FAR
modifier|*
name|pTW_EXTIMAGEINFO
typedef|;
end_typedef

begin_comment
comment|/* Added 1.8 */
end_comment

begin_comment
comment|/* DAT_AUDIOINFO, information about audio data */
end_comment

begin_typedef
DECL|struct|__anon2b4c22282508
typedef|typedef
struct|struct
block|{
DECL|member|Name
name|TW_STR255
name|Name
decl_stmt|;
comment|/* name of audio data */
DECL|member|Reserved
name|TW_UINT32
name|Reserved
decl_stmt|;
comment|/* reserved space */
DECL|typedef|TW_AUDIOINFO
DECL|typedef|pTW_AUDIOINFO
block|}
name|TW_AUDIOINFO
operator|,
name|FAR
modifier|*
name|pTW_AUDIOINFO
typedef|;
end_typedef

begin_comment
comment|/* DAT_DEVICEEVENT, information about events */
end_comment

begin_typedef
DECL|struct|__anon2b4c22282608
typedef|typedef
struct|struct
block|{
DECL|member|Event
name|TW_UINT32
name|Event
decl_stmt|;
comment|/* One of the TWDE_xxxx values. */
DECL|member|DeviceName
name|TW_STR255
name|DeviceName
decl_stmt|;
comment|/* The name of the device that generated the event */
DECL|member|BatteryMinutes
name|TW_UINT32
name|BatteryMinutes
decl_stmt|;
comment|/* Battery Minutes Remaining    */
DECL|member|BatteryPercentage
name|TW_INT16
name|BatteryPercentage
decl_stmt|;
comment|/* Battery Percentage Remaining */
DECL|member|PowerSupply
name|TW_INT32
name|PowerSupply
decl_stmt|;
comment|/* Power Supply                 */
DECL|member|XResolution
name|TW_FIX32
name|XResolution
decl_stmt|;
comment|/* Resolution                   */
DECL|member|YResolution
name|TW_FIX32
name|YResolution
decl_stmt|;
comment|/* Resolution                   */
DECL|member|FlashUsed2
name|TW_UINT32
name|FlashUsed2
decl_stmt|;
comment|/* Flash Used2                  */
DECL|member|AutomaticCapture
name|TW_UINT32
name|AutomaticCapture
decl_stmt|;
comment|/* Automatic Capture            */
DECL|member|TimeBeforeFirstCapture
name|TW_UINT32
name|TimeBeforeFirstCapture
decl_stmt|;
comment|/* Automatic Capture            */
DECL|member|TimeBetweenCaptures
name|TW_UINT32
name|TimeBetweenCaptures
decl_stmt|;
comment|/* Automatic Capture            */
DECL|typedef|TW_DEVICEEVENT
DECL|typedef|pTW_DEVICEEVENT
block|}
name|TW_DEVICEEVENT
operator|,
name|FAR
modifier|*
name|pTW_DEVICEEVENT
typedef|;
end_typedef

begin_comment
comment|/* DAT_FILESYSTEM, information about TWAIN file system */
end_comment

begin_typedef
DECL|struct|__anon2b4c22282708
typedef|typedef
struct|struct
block|{
comment|/* DG_CONTROL / DAT_FILESYSTEM / MSG_xxxx fields     */
DECL|member|InputName
name|TW_STR255
name|InputName
decl_stmt|;
comment|/* The name of the input or source file */
DECL|member|OutputName
name|TW_STR255
name|OutputName
decl_stmt|;
comment|/* The result of an operation or the name of a destination file */
DECL|member|Context
name|TW_MEMREF
name|Context
decl_stmt|;
comment|/* Source specific data used to remember state information */
comment|/* DG_CONTROL / DAT_FILESYSTEM / MSG_DELETE field    */
DECL|member|Recursive
name|int
name|Recursive
decl_stmt|;
comment|/* recursively delete all sub-directories */
comment|/* DG_CONTROL / DAT_FILESYSTEM / MSG_GETINFO fields  */
DECL|member|FileType
name|TW_INT32
name|FileType
decl_stmt|;
comment|/* One of the TWFT_xxxx values */
DECL|member|Size
name|TW_UINT32
name|Size
decl_stmt|;
comment|/* Size of current FileType */
DECL|member|CreateTimeDate
name|TW_STR32
name|CreateTimeDate
decl_stmt|;
comment|/* creation date of the file */
DECL|member|ModifiedTimeDate
name|TW_STR32
name|ModifiedTimeDate
decl_stmt|;
comment|/* last date the file was modified */
DECL|member|FreeSpace
name|TW_UINT32
name|FreeSpace
decl_stmt|;
comment|/* bytes of free space on the current device */
DECL|member|NewImageSize
name|TW_INT32
name|NewImageSize
decl_stmt|;
comment|/* estimate of the amount of space a new image would take up */
DECL|member|NumberOfFiles
name|TW_UINT32
name|NumberOfFiles
decl_stmt|;
comment|/* number of files, depends on FileType */
DECL|member|NumberOfSnippets
name|TW_UINT32
name|NumberOfSnippets
decl_stmt|;
comment|/**/
DECL|member|Reserved
name|char
name|Reserved
index|[
literal|512
index|]
decl_stmt|;
comment|/**/
DECL|typedef|TW_FILESYSTEM
DECL|typedef|pTW_FILESYSTEM
block|}
name|TW_FILESYSTEM
operator|,
name|FAR
modifier|*
name|pTW_FILESYSTEM
typedef|;
end_typedef

begin_comment
comment|/* DAT_PASSTHRU, device dependant data to pass through Data Source */
end_comment

begin_typedef
DECL|struct|__anon2b4c22282808
typedef|typedef
struct|struct
block|{
DECL|member|pCommand
name|TW_MEMREF
name|pCommand
decl_stmt|;
comment|/* Pointer to Command buffer */
DECL|member|CommandBytes
name|TW_UINT32
name|CommandBytes
decl_stmt|;
comment|/* Number of bytes in Command buffer */
DECL|member|Direction
name|TW_INT32
name|Direction
decl_stmt|;
comment|/* One of the TWDR_xxxx values.  Defines the direction of data flow */
DECL|member|pData
name|TW_MEMREF
name|pData
decl_stmt|;
comment|/* Pointer to Data buffer */
DECL|member|DataBytes
name|TW_UINT32
name|DataBytes
decl_stmt|;
comment|/* Number of bytes in Data buffer */
DECL|member|DataBytesXfered
name|TW_UINT32
name|DataBytesXfered
decl_stmt|;
comment|/* Number of bytes successfully transferred */
DECL|typedef|TW_PASSTHRU
DECL|typedef|pTW_PASSTHRU
block|}
name|TW_PASSTHRU
operator|,
name|FAR
modifier|*
name|pTW_PASSTHRU
typedef|;
end_typedef

begin_comment
comment|/* DAT_SETUPAUDIOFILEXFER, information required to setup an audio file transfer */
end_comment

begin_typedef
DECL|struct|__anon2b4c22282908
typedef|typedef
struct|struct
block|{
DECL|member|FileName
name|TW_STR255
name|FileName
decl_stmt|;
comment|/* full path target file */
DECL|member|Format
name|TW_UINT16
name|Format
decl_stmt|;
comment|/* one of TWAF_xxxx */
DECL|member|VRefNum
name|TW_INT16
name|VRefNum
decl_stmt|;
DECL|typedef|TW_SETUPAUDIOFILEXFER
DECL|typedef|pTW_SETUPAUDIOFILEXFER
block|}
name|TW_SETUPAUDIOFILEXFER
operator|,
name|FAR
modifier|*
name|pTW_SETUPAUDIOFILEXFER
typedef|;
end_typedef

begin_comment
comment|/****************************************************************************  * Generic Constants                                                        *  ****************************************************************************/
end_comment

begin_define
DECL|macro|TWON_ARRAY
define|#
directive|define
name|TWON_ARRAY
value|3
end_define

begin_comment
DECL|macro|TWON_ARRAY
comment|/* indicates TW_ARRAY container       */
end_comment

begin_define
DECL|macro|TWON_ENUMERATION
define|#
directive|define
name|TWON_ENUMERATION
value|4
end_define

begin_comment
DECL|macro|TWON_ENUMERATION
comment|/* indicates TW_ENUMERATION container */
end_comment

begin_define
DECL|macro|TWON_ONEVALUE
define|#
directive|define
name|TWON_ONEVALUE
value|5
end_define

begin_comment
DECL|macro|TWON_ONEVALUE
comment|/* indicates TW_ONEVALUE container    */
end_comment

begin_define
DECL|macro|TWON_RANGE
define|#
directive|define
name|TWON_RANGE
value|6
end_define

begin_comment
DECL|macro|TWON_RANGE
comment|/* indicates TW_RANGE container       */
end_comment

begin_define
DECL|macro|TWON_ICONID
define|#
directive|define
name|TWON_ICONID
value|962
end_define

begin_comment
DECL|macro|TWON_ICONID
comment|/* res Id of icon used in USERSELECT lbox */
end_comment

begin_define
DECL|macro|TWON_DSMID
define|#
directive|define
name|TWON_DSMID
value|461
end_define

begin_comment
DECL|macro|TWON_DSMID
comment|/* res Id of the DSM version num resource */
end_comment

begin_define
DECL|macro|TWON_DSMCODEID
define|#
directive|define
name|TWON_DSMCODEID
value|63
end_define

begin_comment
DECL|macro|TWON_DSMCODEID
comment|/* res Id of the Mac SM Code resource     */
end_comment

begin_define
DECL|macro|TWON_DONTCARE8
define|#
directive|define
name|TWON_DONTCARE8
value|0xff
end_define

begin_define
DECL|macro|TWON_DONTCARE16
define|#
directive|define
name|TWON_DONTCARE16
value|0xffff
end_define

begin_define
DECL|macro|TWON_DONTCARE32
define|#
directive|define
name|TWON_DONTCARE32
value|0xffffffff
end_define

begin_comment
comment|/* Flags used in TW_MEMORY structure. */
end_comment

begin_define
DECL|macro|TWMF_APPOWNS
define|#
directive|define
name|TWMF_APPOWNS
value|0x1
end_define

begin_define
DECL|macro|TWMF_DSMOWNS
define|#
directive|define
name|TWMF_DSMOWNS
value|0x2
end_define

begin_define
DECL|macro|TWMF_DSOWNS
define|#
directive|define
name|TWMF_DSOWNS
value|0x4
end_define

begin_define
DECL|macro|TWMF_POINTER
define|#
directive|define
name|TWMF_POINTER
value|0x8
end_define

begin_define
DECL|macro|TWMF_HANDLE
define|#
directive|define
name|TWMF_HANDLE
value|0x10
end_define

begin_comment
comment|/* Palette types for TW_PALETTE8 */
end_comment

begin_define
DECL|macro|TWPA_RGB
define|#
directive|define
name|TWPA_RGB
value|0
end_define

begin_define
DECL|macro|TWPA_GRAY
define|#
directive|define
name|TWPA_GRAY
value|1
end_define

begin_define
DECL|macro|TWPA_CMY
define|#
directive|define
name|TWPA_CMY
value|2
end_define

begin_comment
comment|/* There are four containers used for capabilities negotiation:  *    TWON_ONEVALUE, TWON_RANGE, TWON_ENUMERATION, TWON_ARRAY  * In each container structure ItemType can be TWTY_INT8, TWTY_INT16, etc.  * The kind of data stored in the container can be determined by doing  * DCItemSize[ItemType] where the following is defined in TWAIN glue code:  *          DCItemSize[]= { sizeof(TW_INT8),  *                          sizeof(TW_INT16),  *                          etc.  *                          sizeof(TW_UINT32) };  *  */
end_comment

begin_define
DECL|macro|TWTY_INT8
define|#
directive|define
name|TWTY_INT8
value|0x0000
end_define

begin_comment
DECL|macro|TWTY_INT8
comment|/* Means Item is a TW_INT8   */
end_comment

begin_define
DECL|macro|TWTY_INT16
define|#
directive|define
name|TWTY_INT16
value|0x0001
end_define

begin_comment
DECL|macro|TWTY_INT16
comment|/* Means Item is a TW_INT16  */
end_comment

begin_define
DECL|macro|TWTY_INT32
define|#
directive|define
name|TWTY_INT32
value|0x0002
end_define

begin_comment
DECL|macro|TWTY_INT32
comment|/* Means Item is a TW_INT32  */
end_comment

begin_define
DECL|macro|TWTY_UINT8
define|#
directive|define
name|TWTY_UINT8
value|0x0003
end_define

begin_comment
DECL|macro|TWTY_UINT8
comment|/* Means Item is a TW_UINT8  */
end_comment

begin_define
DECL|macro|TWTY_UINT16
define|#
directive|define
name|TWTY_UINT16
value|0x0004
end_define

begin_comment
DECL|macro|TWTY_UINT16
comment|/* Means Item is a TW_UINT16 */
end_comment

begin_define
DECL|macro|TWTY_UINT32
define|#
directive|define
name|TWTY_UINT32
value|0x0005
end_define

begin_comment
DECL|macro|TWTY_UINT32
comment|/* Means Item is a TW_UINT32 */
end_comment

begin_define
DECL|macro|TWTY_BOOL
define|#
directive|define
name|TWTY_BOOL
value|0x0006
end_define

begin_comment
DECL|macro|TWTY_BOOL
comment|/* Means Item is a TW_BOOL   */
end_comment

begin_define
DECL|macro|TWTY_FIX32
define|#
directive|define
name|TWTY_FIX32
value|0x0007
end_define

begin_comment
DECL|macro|TWTY_FIX32
comment|/* Means Item is a TW_FIX32  */
end_comment

begin_define
DECL|macro|TWTY_FRAME
define|#
directive|define
name|TWTY_FRAME
value|0x0008
end_define

begin_comment
DECL|macro|TWTY_FRAME
comment|/* Means Item is a TW_FRAME  */
end_comment

begin_define
DECL|macro|TWTY_STR32
define|#
directive|define
name|TWTY_STR32
value|0x0009
end_define

begin_comment
DECL|macro|TWTY_STR32
comment|/* Means Item is a TW_STR32  */
end_comment

begin_define
DECL|macro|TWTY_STR64
define|#
directive|define
name|TWTY_STR64
value|0x000a
end_define

begin_comment
DECL|macro|TWTY_STR64
comment|/* Means Item is a TW_STR64  */
end_comment

begin_define
DECL|macro|TWTY_STR128
define|#
directive|define
name|TWTY_STR128
value|0x000b
end_define

begin_comment
DECL|macro|TWTY_STR128
comment|/* Means Item is a TW_STR128 */
end_comment

begin_define
DECL|macro|TWTY_STR255
define|#
directive|define
name|TWTY_STR255
value|0x000c
end_define

begin_comment
DECL|macro|TWTY_STR255
comment|/* Means Item is a TW_STR255 */
end_comment

begin_comment
comment|/****************************************************************************  * Capability Constants                                                     *  ****************************************************************************/
end_comment

begin_comment
comment|/* ICAP_BITORDER values (BO_ means Bit Order) */
end_comment

begin_define
DECL|macro|TWBO_LSBFIRST
define|#
directive|define
name|TWBO_LSBFIRST
value|0
end_define

begin_define
DECL|macro|TWBO_MSBFIRST
define|#
directive|define
name|TWBO_MSBFIRST
value|1
end_define

begin_comment
comment|/* ICAP_COMPRESSION values (CP_ means ComPression ) */
end_comment

begin_define
DECL|macro|TWCP_NONE
define|#
directive|define
name|TWCP_NONE
value|0
end_define

begin_define
DECL|macro|TWCP_PACKBITS
define|#
directive|define
name|TWCP_PACKBITS
value|1
end_define

begin_define
DECL|macro|TWCP_GROUP31D
define|#
directive|define
name|TWCP_GROUP31D
value|2
end_define

begin_comment
DECL|macro|TWCP_GROUP31D
comment|/* Follows CCITT spec (no End Of Line)          */
end_comment

begin_define
DECL|macro|TWCP_GROUP31DEOL
define|#
directive|define
name|TWCP_GROUP31DEOL
value|3
end_define

begin_comment
DECL|macro|TWCP_GROUP31DEOL
comment|/* Follows CCITT spec (has End Of Line)         */
end_comment

begin_define
DECL|macro|TWCP_GROUP32D
define|#
directive|define
name|TWCP_GROUP32D
value|4
end_define

begin_comment
DECL|macro|TWCP_GROUP32D
comment|/* Follows CCITT spec (use cap for K Factor)    */
end_comment

begin_define
DECL|macro|TWCP_GROUP4
define|#
directive|define
name|TWCP_GROUP4
value|5
end_define

begin_comment
DECL|macro|TWCP_GROUP4
comment|/* Follows CCITT spec                           */
end_comment

begin_define
DECL|macro|TWCP_JPEG
define|#
directive|define
name|TWCP_JPEG
value|6
end_define

begin_comment
DECL|macro|TWCP_JPEG
comment|/* Use capability for more info                 */
end_comment

begin_define
DECL|macro|TWCP_LZW
define|#
directive|define
name|TWCP_LZW
value|7
end_define

begin_comment
DECL|macro|TWCP_LZW
comment|/* Must license from Unisys and IBM to use      */
end_comment

begin_define
DECL|macro|TWCP_JBIG
define|#
directive|define
name|TWCP_JBIG
value|8
end_define

begin_comment
DECL|macro|TWCP_JBIG
comment|/* For Bitonal images  -- Added 1.7 KHL         */
end_comment

begin_comment
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|TWCP_PNG
define|#
directive|define
name|TWCP_PNG
value|9
end_define

begin_define
DECL|macro|TWCP_RLE4
define|#
directive|define
name|TWCP_RLE4
value|10
end_define

begin_define
DECL|macro|TWCP_RLE8
define|#
directive|define
name|TWCP_RLE8
value|11
end_define

begin_define
DECL|macro|TWCP_BITFIELDS
define|#
directive|define
name|TWCP_BITFIELDS
value|12
end_define

begin_comment
comment|/* ICAP_IMAGEFILEFORMAT values (FF_means File Format)   */
end_comment

begin_define
DECL|macro|TWFF_TIFF
define|#
directive|define
name|TWFF_TIFF
value|0
end_define

begin_comment
DECL|macro|TWFF_TIFF
comment|/* Tagged Image File Format     */
end_comment

begin_define
DECL|macro|TWFF_PICT
define|#
directive|define
name|TWFF_PICT
value|1
end_define

begin_comment
DECL|macro|TWFF_PICT
comment|/* Macintosh PICT               */
end_comment

begin_define
DECL|macro|TWFF_BMP
define|#
directive|define
name|TWFF_BMP
value|2
end_define

begin_comment
DECL|macro|TWFF_BMP
comment|/* Windows Bitmap               */
end_comment

begin_define
DECL|macro|TWFF_XBM
define|#
directive|define
name|TWFF_XBM
value|3
end_define

begin_comment
DECL|macro|TWFF_XBM
comment|/* X-Windows Bitmap             */
end_comment

begin_define
DECL|macro|TWFF_JFIF
define|#
directive|define
name|TWFF_JFIF
value|4
end_define

begin_comment
DECL|macro|TWFF_JFIF
comment|/* JPEG File Interchange Format */
end_comment

begin_define
DECL|macro|TWFF_FPX
define|#
directive|define
name|TWFF_FPX
value|5
end_define

begin_comment
DECL|macro|TWFF_FPX
comment|/* Flash Pix                    */
end_comment

begin_define
DECL|macro|TWFF_TIFFMULTI
define|#
directive|define
name|TWFF_TIFFMULTI
value|6
end_define

begin_comment
DECL|macro|TWFF_TIFFMULTI
comment|/* Multi-page tiff file         */
end_comment

begin_define
DECL|macro|TWFF_PNG
define|#
directive|define
name|TWFF_PNG
value|7
end_define

begin_define
DECL|macro|TWFF_SPIFF
define|#
directive|define
name|TWFF_SPIFF
value|8
end_define

begin_define
DECL|macro|TWFF_EXIF
define|#
directive|define
name|TWFF_EXIF
value|9
end_define

begin_comment
comment|/* ICAP_FILTER values (FT_ means Filter Type) */
end_comment

begin_define
DECL|macro|TWFT_RED
define|#
directive|define
name|TWFT_RED
value|0
end_define

begin_define
DECL|macro|TWFT_GREEN
define|#
directive|define
name|TWFT_GREEN
value|1
end_define

begin_define
DECL|macro|TWFT_BLUE
define|#
directive|define
name|TWFT_BLUE
value|2
end_define

begin_define
DECL|macro|TWFT_NONE
define|#
directive|define
name|TWFT_NONE
value|3
end_define

begin_define
DECL|macro|TWFT_WHITE
define|#
directive|define
name|TWFT_WHITE
value|4
end_define

begin_define
DECL|macro|TWFT_CYAN
define|#
directive|define
name|TWFT_CYAN
value|5
end_define

begin_define
DECL|macro|TWFT_MAGENTA
define|#
directive|define
name|TWFT_MAGENTA
value|6
end_define

begin_define
DECL|macro|TWFT_YELLOW
define|#
directive|define
name|TWFT_YELLOW
value|7
end_define

begin_define
DECL|macro|TWFT_BLACK
define|#
directive|define
name|TWFT_BLACK
value|8
end_define

begin_comment
comment|/* ICAP_LIGHTPATH values (LP_ means Light Path) */
end_comment

begin_define
DECL|macro|TWLP_REFLECTIVE
define|#
directive|define
name|TWLP_REFLECTIVE
value|0
end_define

begin_define
DECL|macro|TWLP_TRANSMISSIVE
define|#
directive|define
name|TWLP_TRANSMISSIVE
value|1
end_define

begin_comment
comment|/* ICAP_LIGHTSOURCE values (LS_ means Light Source) */
end_comment

begin_define
DECL|macro|TWLS_RED
define|#
directive|define
name|TWLS_RED
value|0
end_define

begin_define
DECL|macro|TWLS_GREEN
define|#
directive|define
name|TWLS_GREEN
value|1
end_define

begin_define
DECL|macro|TWLS_BLUE
define|#
directive|define
name|TWLS_BLUE
value|2
end_define

begin_define
DECL|macro|TWLS_NONE
define|#
directive|define
name|TWLS_NONE
value|3
end_define

begin_define
DECL|macro|TWLS_WHITE
define|#
directive|define
name|TWLS_WHITE
value|4
end_define

begin_define
DECL|macro|TWLS_UV
define|#
directive|define
name|TWLS_UV
value|5
end_define

begin_define
DECL|macro|TWLS_IR
define|#
directive|define
name|TWLS_IR
value|6
end_define

begin_comment
comment|/* ICAP_ORIENTATION values (OR_ means ORientation) */
end_comment

begin_define
DECL|macro|TWOR_ROT0
define|#
directive|define
name|TWOR_ROT0
value|0
end_define

begin_define
DECL|macro|TWOR_ROT90
define|#
directive|define
name|TWOR_ROT90
value|1
end_define

begin_define
DECL|macro|TWOR_ROT180
define|#
directive|define
name|TWOR_ROT180
value|2
end_define

begin_define
DECL|macro|TWOR_ROT270
define|#
directive|define
name|TWOR_ROT270
value|3
end_define

begin_define
DECL|macro|TWOR_PORTRAIT
define|#
directive|define
name|TWOR_PORTRAIT
value|TWOR_ROT0
end_define

begin_define
DECL|macro|TWOR_LANDSCAPE
define|#
directive|define
name|TWOR_LANDSCAPE
value|TWOR_ROT270
end_define

begin_comment
comment|/* ICAP_PLANARCHUNKY values (PC_ means Planar/Chunky ) */
end_comment

begin_define
DECL|macro|TWPC_CHUNKY
define|#
directive|define
name|TWPC_CHUNKY
value|0
end_define

begin_define
DECL|macro|TWPC_PLANAR
define|#
directive|define
name|TWPC_PLANAR
value|1
end_define

begin_comment
comment|/* ICAP_PIXELFLAVOR values (PF_ means Pixel Flavor) */
end_comment

begin_define
DECL|macro|TWPF_CHOCOLATE
define|#
directive|define
name|TWPF_CHOCOLATE
value|0
end_define

begin_comment
DECL|macro|TWPF_CHOCOLATE
comment|/* zero pixel represents darkest shade  */
end_comment

begin_define
DECL|macro|TWPF_VANILLA
define|#
directive|define
name|TWPF_VANILLA
value|1
end_define

begin_comment
DECL|macro|TWPF_VANILLA
comment|/* zero pixel represents lightest shade */
end_comment

begin_comment
comment|/* ICAP_PIXELTYPE values (PT_ means Pixel Type) */
end_comment

begin_define
DECL|macro|TWPT_BW
define|#
directive|define
name|TWPT_BW
value|0
end_define

begin_comment
DECL|macro|TWPT_BW
comment|/* Black and White */
end_comment

begin_define
DECL|macro|TWPT_GRAY
define|#
directive|define
name|TWPT_GRAY
value|1
end_define

begin_define
DECL|macro|TWPT_RGB
define|#
directive|define
name|TWPT_RGB
value|2
end_define

begin_define
DECL|macro|TWPT_PALETTE
define|#
directive|define
name|TWPT_PALETTE
value|3
end_define

begin_define
DECL|macro|TWPT_CMY
define|#
directive|define
name|TWPT_CMY
value|4
end_define

begin_define
DECL|macro|TWPT_CMYK
define|#
directive|define
name|TWPT_CMYK
value|5
end_define

begin_define
DECL|macro|TWPT_YUV
define|#
directive|define
name|TWPT_YUV
value|6
end_define

begin_define
DECL|macro|TWPT_YUVK
define|#
directive|define
name|TWPT_YUVK
value|7
end_define

begin_define
DECL|macro|TWPT_CIEXYZ
define|#
directive|define
name|TWPT_CIEXYZ
value|8
end_define

begin_comment
comment|/* ICAP_SUPPORTEDSIZES values (SS_ means Supported Sizes) */
end_comment

begin_define
DECL|macro|TWSS_NONE
define|#
directive|define
name|TWSS_NONE
value|0
end_define

begin_define
DECL|macro|TWSS_A4LETTER
define|#
directive|define
name|TWSS_A4LETTER
value|1
end_define

begin_define
DECL|macro|TWSS_B5LETTER
define|#
directive|define
name|TWSS_B5LETTER
value|2
end_define

begin_define
DECL|macro|TWSS_USLETTER
define|#
directive|define
name|TWSS_USLETTER
value|3
end_define

begin_define
DECL|macro|TWSS_USLEGAL
define|#
directive|define
name|TWSS_USLEGAL
value|4
end_define

begin_comment
comment|/* Added 1.5 */
end_comment

begin_define
DECL|macro|TWSS_A5
define|#
directive|define
name|TWSS_A5
value|5
end_define

begin_define
DECL|macro|TWSS_B4
define|#
directive|define
name|TWSS_B4
value|6
end_define

begin_define
DECL|macro|TWSS_B6
define|#
directive|define
name|TWSS_B6
value|7
end_define

begin_comment
comment|//#define TWSS_B          8
end_comment

begin_comment
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|TWSS_USLEDGER
define|#
directive|define
name|TWSS_USLEDGER
value|9
end_define

begin_define
DECL|macro|TWSS_USEXECUTIVE
define|#
directive|define
name|TWSS_USEXECUTIVE
value|10
end_define

begin_define
DECL|macro|TWSS_A3
define|#
directive|define
name|TWSS_A3
value|11
end_define

begin_define
DECL|macro|TWSS_B3
define|#
directive|define
name|TWSS_B3
value|12
end_define

begin_define
DECL|macro|TWSS_A6
define|#
directive|define
name|TWSS_A6
value|13
end_define

begin_define
DECL|macro|TWSS_C4
define|#
directive|define
name|TWSS_C4
value|14
end_define

begin_define
DECL|macro|TWSS_C5
define|#
directive|define
name|TWSS_C5
value|15
end_define

begin_define
DECL|macro|TWSS_C6
define|#
directive|define
name|TWSS_C6
value|16
end_define

begin_comment
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|TWSS_4A0
define|#
directive|define
name|TWSS_4A0
value|17
end_define

begin_define
DECL|macro|TWSS_2A0
define|#
directive|define
name|TWSS_2A0
value|18
end_define

begin_define
DECL|macro|TWSS_A0
define|#
directive|define
name|TWSS_A0
value|19
end_define

begin_define
DECL|macro|TWSS_A1
define|#
directive|define
name|TWSS_A1
value|20
end_define

begin_define
DECL|macro|TWSS_A2
define|#
directive|define
name|TWSS_A2
value|21
end_define

begin_define
DECL|macro|TWSS_A4
define|#
directive|define
name|TWSS_A4
value|TWSS_A4LETTER
end_define

begin_define
DECL|macro|TWSS_A7
define|#
directive|define
name|TWSS_A7
value|22
end_define

begin_define
DECL|macro|TWSS_A8
define|#
directive|define
name|TWSS_A8
value|23
end_define

begin_define
DECL|macro|TWSS_A9
define|#
directive|define
name|TWSS_A9
value|24
end_define

begin_define
DECL|macro|TWSS_A10
define|#
directive|define
name|TWSS_A10
value|25
end_define

begin_define
DECL|macro|TWSS_ISOB0
define|#
directive|define
name|TWSS_ISOB0
value|26
end_define

begin_define
DECL|macro|TWSS_ISOB1
define|#
directive|define
name|TWSS_ISOB1
value|27
end_define

begin_define
DECL|macro|TWSS_ISOB2
define|#
directive|define
name|TWSS_ISOB2
value|28
end_define

begin_define
DECL|macro|TWSS_ISOB3
define|#
directive|define
name|TWSS_ISOB3
value|TWSS_B3
end_define

begin_define
DECL|macro|TWSS_ISOB4
define|#
directive|define
name|TWSS_ISOB4
value|TWSS_B4
end_define

begin_define
DECL|macro|TWSS_ISOB5
define|#
directive|define
name|TWSS_ISOB5
value|29
end_define

begin_define
DECL|macro|TWSS_ISOB6
define|#
directive|define
name|TWSS_ISOB6
value|TWSS_B6
end_define

begin_define
DECL|macro|TWSS_ISOB7
define|#
directive|define
name|TWSS_ISOB7
value|30
end_define

begin_define
DECL|macro|TWSS_ISOB8
define|#
directive|define
name|TWSS_ISOB8
value|31
end_define

begin_define
DECL|macro|TWSS_ISOB9
define|#
directive|define
name|TWSS_ISOB9
value|32
end_define

begin_define
DECL|macro|TWSS_ISOB10
define|#
directive|define
name|TWSS_ISOB10
value|33
end_define

begin_define
DECL|macro|TWSS_JISB0
define|#
directive|define
name|TWSS_JISB0
value|34
end_define

begin_define
DECL|macro|TWSS_JISB1
define|#
directive|define
name|TWSS_JISB1
value|35
end_define

begin_define
DECL|macro|TWSS_JISB2
define|#
directive|define
name|TWSS_JISB2
value|36
end_define

begin_define
DECL|macro|TWSS_JISB3
define|#
directive|define
name|TWSS_JISB3
value|37
end_define

begin_define
DECL|macro|TWSS_JISB4
define|#
directive|define
name|TWSS_JISB4
value|38
end_define

begin_define
DECL|macro|TWSS_JISB5
define|#
directive|define
name|TWSS_JISB5
value|TWSS_B5LETTER
end_define

begin_define
DECL|macro|TWSS_JISB6
define|#
directive|define
name|TWSS_JISB6
value|39
end_define

begin_define
DECL|macro|TWSS_JISB7
define|#
directive|define
name|TWSS_JISB7
value|40
end_define

begin_define
DECL|macro|TWSS_JISB8
define|#
directive|define
name|TWSS_JISB8
value|41
end_define

begin_define
DECL|macro|TWSS_JISB9
define|#
directive|define
name|TWSS_JISB9
value|42
end_define

begin_define
DECL|macro|TWSS_JISB10
define|#
directive|define
name|TWSS_JISB10
value|43
end_define

begin_define
DECL|macro|TWSS_C0
define|#
directive|define
name|TWSS_C0
value|44
end_define

begin_define
DECL|macro|TWSS_C1
define|#
directive|define
name|TWSS_C1
value|45
end_define

begin_define
DECL|macro|TWSS_C2
define|#
directive|define
name|TWSS_C2
value|46
end_define

begin_define
DECL|macro|TWSS_C3
define|#
directive|define
name|TWSS_C3
value|47
end_define

begin_define
DECL|macro|TWSS_C7
define|#
directive|define
name|TWSS_C7
value|48
end_define

begin_define
DECL|macro|TWSS_C8
define|#
directive|define
name|TWSS_C8
value|49
end_define

begin_define
DECL|macro|TWSS_C9
define|#
directive|define
name|TWSS_C9
value|50
end_define

begin_define
DECL|macro|TWSS_C10
define|#
directive|define
name|TWSS_C10
value|51
end_define

begin_define
DECL|macro|TWSS_USSTATEMENT
define|#
directive|define
name|TWSS_USSTATEMENT
value|52
end_define

begin_define
DECL|macro|TWSS_BUSINESSCARD
define|#
directive|define
name|TWSS_BUSINESSCARD
value|53
end_define

begin_comment
comment|/* ICAP_XFERMECH values (SX_ means Setup XFer) */
end_comment

begin_define
DECL|macro|TWSX_NATIVE
define|#
directive|define
name|TWSX_NATIVE
value|0
end_define

begin_define
DECL|macro|TWSX_FILE
define|#
directive|define
name|TWSX_FILE
value|1
end_define

begin_define
DECL|macro|TWSX_MEMORY
define|#
directive|define
name|TWSX_MEMORY
value|2
end_define

begin_comment
comment|/* ICAP_UNITS values (UN_ means UNits) */
end_comment

begin_define
DECL|macro|TWUN_INCHES
define|#
directive|define
name|TWUN_INCHES
value|0
end_define

begin_define
DECL|macro|TWUN_CENTIMETERS
define|#
directive|define
name|TWUN_CENTIMETERS
value|1
end_define

begin_define
DECL|macro|TWUN_PICAS
define|#
directive|define
name|TWUN_PICAS
value|2
end_define

begin_define
DECL|macro|TWUN_POINTS
define|#
directive|define
name|TWUN_POINTS
value|3
end_define

begin_define
DECL|macro|TWUN_TWIPS
define|#
directive|define
name|TWUN_TWIPS
value|4
end_define

begin_define
DECL|macro|TWUN_PIXELS
define|#
directive|define
name|TWUN_PIXELS
value|5
end_define

begin_comment
comment|/* Added 1.5 */
end_comment

begin_comment
comment|/* ICAP_BITDEPTHREDUCTION values (BR_ means Bitdepth Reduction) */
end_comment

begin_define
DECL|macro|TWBR_THRESHOLD
define|#
directive|define
name|TWBR_THRESHOLD
value|0
end_define

begin_define
DECL|macro|TWBR_HALFTONE
define|#
directive|define
name|TWBR_HALFTONE
value|1
end_define

begin_define
DECL|macro|TWBR_CUSTHALFTONE
define|#
directive|define
name|TWBR_CUSTHALFTONE
value|2
end_define

begin_define
DECL|macro|TWBR_DIFFUSION
define|#
directive|define
name|TWBR_DIFFUSION
value|3
end_define

begin_comment
comment|/* Added 1.7 */
end_comment

begin_comment
comment|/* ICAP_DUPLEX values */
end_comment

begin_define
DECL|macro|TWDX_NONE
define|#
directive|define
name|TWDX_NONE
value|0
end_define

begin_define
DECL|macro|TWDX_1PASSDUPLEX
define|#
directive|define
name|TWDX_1PASSDUPLEX
value|1
end_define

begin_define
DECL|macro|TWDX_2PASSDUPLEX
define|#
directive|define
name|TWDX_2PASSDUPLEX
value|2
end_define

begin_comment
comment|/* Added 1.7 */
end_comment

begin_comment
comment|/* TWEI_BARCODETYPE values */
end_comment

begin_define
DECL|macro|TWBT_3OF9
define|#
directive|define
name|TWBT_3OF9
value|0
end_define

begin_define
DECL|macro|TWBT_2OF5INTERLEAVED
define|#
directive|define
name|TWBT_2OF5INTERLEAVED
value|1
end_define

begin_define
DECL|macro|TWBT_2OF5NONINTERLEAVED
define|#
directive|define
name|TWBT_2OF5NONINTERLEAVED
value|2
end_define

begin_define
DECL|macro|TWBT_CODE93
define|#
directive|define
name|TWBT_CODE93
value|3
end_define

begin_define
DECL|macro|TWBT_CODE128
define|#
directive|define
name|TWBT_CODE128
value|4
end_define

begin_define
DECL|macro|TWBT_UCC128
define|#
directive|define
name|TWBT_UCC128
value|5
end_define

begin_define
DECL|macro|TWBT_CODABAR
define|#
directive|define
name|TWBT_CODABAR
value|6
end_define

begin_define
DECL|macro|TWBT_UPCA
define|#
directive|define
name|TWBT_UPCA
value|7
end_define

begin_define
DECL|macro|TWBT_UPCE
define|#
directive|define
name|TWBT_UPCE
value|8
end_define

begin_define
DECL|macro|TWBT_EAN8
define|#
directive|define
name|TWBT_EAN8
value|9
end_define

begin_define
DECL|macro|TWBT_EAN13
define|#
directive|define
name|TWBT_EAN13
value|10
end_define

begin_define
DECL|macro|TWBT_POSTNET
define|#
directive|define
name|TWBT_POSTNET
value|11
end_define

begin_define
DECL|macro|TWBT_PDF417
define|#
directive|define
name|TWBT_PDF417
value|12
end_define

begin_comment
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|TWBT_2OF5INDUSTRIAL
define|#
directive|define
name|TWBT_2OF5INDUSTRIAL
value|13
end_define

begin_define
DECL|macro|TWBT_2OF5MATRIX
define|#
directive|define
name|TWBT_2OF5MATRIX
value|14
end_define

begin_define
DECL|macro|TWBT_2OF5DATALOGIC
define|#
directive|define
name|TWBT_2OF5DATALOGIC
value|15
end_define

begin_define
DECL|macro|TWBT_2OF5IATA
define|#
directive|define
name|TWBT_2OF5IATA
value|16
end_define

begin_define
DECL|macro|TWBT_3OF9FULLASCII
define|#
directive|define
name|TWBT_3OF9FULLASCII
value|17
end_define

begin_define
DECL|macro|TWBT_CODABARWITHSTARTSTOP
define|#
directive|define
name|TWBT_CODABARWITHSTARTSTOP
value|18
end_define

begin_comment
comment|/* Added 1.7 */
end_comment

begin_comment
comment|/* TWEI_DESKEWSTATUS values */
end_comment

begin_define
DECL|macro|TWDSK_SUCCESS
define|#
directive|define
name|TWDSK_SUCCESS
value|0
end_define

begin_define
DECL|macro|TWDSK_REPORTONLY
define|#
directive|define
name|TWDSK_REPORTONLY
value|1
end_define

begin_define
DECL|macro|TWDSK_FAIL
define|#
directive|define
name|TWDSK_FAIL
value|2
end_define

begin_define
DECL|macro|TWDSK_DISABLED
define|#
directive|define
name|TWDSK_DISABLED
value|3
end_define

begin_comment
comment|/* Added 1.7 */
end_comment

begin_comment
comment|/* TWEI_PATCHCODE values */
end_comment

begin_define
DECL|macro|TWPCH_PATCH1
define|#
directive|define
name|TWPCH_PATCH1
value|0
end_define

begin_define
DECL|macro|TWPCH_PATCH2
define|#
directive|define
name|TWPCH_PATCH2
value|1
end_define

begin_define
DECL|macro|TWPCH_PATCH3
define|#
directive|define
name|TWPCH_PATCH3
value|2
end_define

begin_define
DECL|macro|TWPCH_PATCH4
define|#
directive|define
name|TWPCH_PATCH4
value|3
end_define

begin_define
DECL|macro|TWPCH_PATCH6
define|#
directive|define
name|TWPCH_PATCH6
value|4
end_define

begin_define
DECL|macro|TWPCH_PATCHT
define|#
directive|define
name|TWPCH_PATCHT
value|5
end_define

begin_comment
comment|/* Added 1.7 */
end_comment

begin_comment
comment|/* CAP_JOBCONTROL values */
end_comment

begin_define
DECL|macro|TWJC_NONE
define|#
directive|define
name|TWJC_NONE
value|0
end_define

begin_define
DECL|macro|TWJC_JSIC
define|#
directive|define
name|TWJC_JSIC
value|1
end_define

begin_define
DECL|macro|TWJC_JSIS
define|#
directive|define
name|TWJC_JSIS
value|2
end_define

begin_define
DECL|macro|TWJC_JSXC
define|#
directive|define
name|TWJC_JSXC
value|3
end_define

begin_define
DECL|macro|TWJC_JSXS
define|#
directive|define
name|TWJC_JSXS
value|4
end_define

begin_comment
comment|/* Added 1.7 */
end_comment

begin_comment
comment|/* TWEI_BARCODEROTATION values (BCOR_ means barcode rotation) */
end_comment

begin_define
DECL|macro|TWBCOR_ROT0
define|#
directive|define
name|TWBCOR_ROT0
value|0
end_define

begin_define
DECL|macro|TWBCOR_ROT90
define|#
directive|define
name|TWBCOR_ROT90
value|1
end_define

begin_define
DECL|macro|TWBCOR_ROT180
define|#
directive|define
name|TWBCOR_ROT180
value|2
end_define

begin_define
DECL|macro|TWBCOR_ROT270
define|#
directive|define
name|TWBCOR_ROT270
value|3
end_define

begin_define
DECL|macro|TWBCOR_ROTX
define|#
directive|define
name|TWBCOR_ROTX
value|4
end_define

begin_comment
comment|/* Added 1.8 */
end_comment

begin_comment
comment|/* ACAP_AUDIOFILEFORMAT values (AF_ means audio format) */
end_comment

begin_define
DECL|macro|TWAF_WAV
define|#
directive|define
name|TWAF_WAV
value|0
end_define

begin_define
DECL|macro|TWAF_AIFF
define|#
directive|define
name|TWAF_AIFF
value|1
end_define

begin_define
DECL|macro|TWAF_AU
define|#
directive|define
name|TWAF_AU
value|3
end_define

begin_define
DECL|macro|TWAF_SND
define|#
directive|define
name|TWAF_SND
value|4
end_define

begin_comment
comment|/* CAP_ALARMS values (AL_ means alarms) */
end_comment

begin_define
DECL|macro|TWAL_ALARM
define|#
directive|define
name|TWAL_ALARM
value|0
end_define

begin_define
DECL|macro|TWAL_FEEDERERROR
define|#
directive|define
name|TWAL_FEEDERERROR
value|1
end_define

begin_define
DECL|macro|TWAL_FEEDERWARNING
define|#
directive|define
name|TWAL_FEEDERWARNING
value|2
end_define

begin_define
DECL|macro|TWAL_BARCODE
define|#
directive|define
name|TWAL_BARCODE
value|3
end_define

begin_define
DECL|macro|TWAL_DOUBLEFEED
define|#
directive|define
name|TWAL_DOUBLEFEED
value|4
end_define

begin_define
DECL|macro|TWAL_JAM
define|#
directive|define
name|TWAL_JAM
value|5
end_define

begin_define
DECL|macro|TWAL_PATCHCODE
define|#
directive|define
name|TWAL_PATCHCODE
value|6
end_define

begin_define
DECL|macro|TWAL_POWER
define|#
directive|define
name|TWAL_POWER
value|7
end_define

begin_define
DECL|macro|TWAL_SKEW
define|#
directive|define
name|TWAL_SKEW
value|8
end_define

begin_comment
comment|/* CAP_CLEARBUFFERS values (CB_ means clear buffers) */
end_comment

begin_define
DECL|macro|TWCB_AUTO
define|#
directive|define
name|TWCB_AUTO
value|0
end_define

begin_define
DECL|macro|TWCB_CLEAR
define|#
directive|define
name|TWCB_CLEAR
value|1
end_define

begin_define
DECL|macro|TWCB_NOCLEAR
define|#
directive|define
name|TWCB_NOCLEAR
value|2
end_define

begin_comment
comment|/* CAP_DEVICEEVENT values (DE_ means device event) */
end_comment

begin_define
DECL|macro|TWDE_CUSTOMEVENTS
define|#
directive|define
name|TWDE_CUSTOMEVENTS
value|0x8000
end_define

begin_define
DECL|macro|TWDE_CHECKAUTOMATICCAPTURE
define|#
directive|define
name|TWDE_CHECKAUTOMATICCAPTURE
value|0
end_define

begin_define
DECL|macro|TWDE_CHECKBATTERY
define|#
directive|define
name|TWDE_CHECKBATTERY
value|1
end_define

begin_define
DECL|macro|TWDE_CHECKDEVICEONLINE
define|#
directive|define
name|TWDE_CHECKDEVICEONLINE
value|2
end_define

begin_define
DECL|macro|TWDE_CHECKFLASH
define|#
directive|define
name|TWDE_CHECKFLASH
value|3
end_define

begin_define
DECL|macro|TWDE_CHECKPOWERSUPPLY
define|#
directive|define
name|TWDE_CHECKPOWERSUPPLY
value|4
end_define

begin_define
DECL|macro|TWDE_CHECKRESOLUTION
define|#
directive|define
name|TWDE_CHECKRESOLUTION
value|5
end_define

begin_define
DECL|macro|TWDE_DEVICEADDED
define|#
directive|define
name|TWDE_DEVICEADDED
value|6
end_define

begin_define
DECL|macro|TWDE_DEVICEOFFLINE
define|#
directive|define
name|TWDE_DEVICEOFFLINE
value|7
end_define

begin_define
DECL|macro|TWDE_DEVICEREADY
define|#
directive|define
name|TWDE_DEVICEREADY
value|8
end_define

begin_define
DECL|macro|TWDE_DEVICEREMOVED
define|#
directive|define
name|TWDE_DEVICEREMOVED
value|9
end_define

begin_define
DECL|macro|TWDE_IMAGECAPTURED
define|#
directive|define
name|TWDE_IMAGECAPTURED
value|10
end_define

begin_define
DECL|macro|TWDE_IMAGEDELETED
define|#
directive|define
name|TWDE_IMAGEDELETED
value|11
end_define

begin_define
DECL|macro|TWDE_PAPERDOUBLEFEED
define|#
directive|define
name|TWDE_PAPERDOUBLEFEED
value|12
end_define

begin_define
DECL|macro|TWDE_PAPERJAM
define|#
directive|define
name|TWDE_PAPERJAM
value|13
end_define

begin_define
DECL|macro|TWDE_LAMPFAILURE
define|#
directive|define
name|TWDE_LAMPFAILURE
value|14
end_define

begin_define
DECL|macro|TWDE_POWERSAVE
define|#
directive|define
name|TWDE_POWERSAVE
value|15
end_define

begin_define
DECL|macro|TWDE_POWERSAVENOTIFY
define|#
directive|define
name|TWDE_POWERSAVENOTIFY
value|16
end_define

begin_comment
comment|/* CAP_FEEDERALIGNMENT values (FA_ means feeder alignment) */
end_comment

begin_define
DECL|macro|TWFA_NONE
define|#
directive|define
name|TWFA_NONE
value|0
end_define

begin_define
DECL|macro|TWFA_LEFT
define|#
directive|define
name|TWFA_LEFT
value|1
end_define

begin_define
DECL|macro|TWFA_CENTER
define|#
directive|define
name|TWFA_CENTER
value|2
end_define

begin_define
DECL|macro|TWFA_RIGHT
define|#
directive|define
name|TWFA_RIGHT
value|3
end_define

begin_comment
comment|/* CAP_FEEDERORDER values (FO_ means feeder order) */
end_comment

begin_define
DECL|macro|TWFO_FIRSTPAGEFIRST
define|#
directive|define
name|TWFO_FIRSTPAGEFIRST
value|0
end_define

begin_define
DECL|macro|TWFO_LASTPAGEFIRST
define|#
directive|define
name|TWFO_LASTPAGEFIRST
value|1
end_define

begin_comment
comment|/* CAP_FILESYSTEM values (FS_ means file system) */
end_comment

begin_define
DECL|macro|TWFS_FILESYSTEM
define|#
directive|define
name|TWFS_FILESYSTEM
value|0
end_define

begin_define
DECL|macro|TWFS_RECURSIVEDELETE
define|#
directive|define
name|TWFS_RECURSIVEDELETE
value|1
end_define

begin_comment
comment|/* CAP_POWERSUPPLY values (PS_ means power supply) */
end_comment

begin_define
DECL|macro|TWPS_EXTERNAL
define|#
directive|define
name|TWPS_EXTERNAL
value|0
end_define

begin_define
DECL|macro|TWPS_BATTERY
define|#
directive|define
name|TWPS_BATTERY
value|1
end_define

begin_comment
comment|/* CAP_PRINTER values (PR_ means printer) */
end_comment

begin_define
DECL|macro|TWPR_IMPRINTERTOPBEFORE
define|#
directive|define
name|TWPR_IMPRINTERTOPBEFORE
value|0
end_define

begin_define
DECL|macro|TWPR_IMPRINTERTOPAFTER
define|#
directive|define
name|TWPR_IMPRINTERTOPAFTER
value|1
end_define

begin_define
DECL|macro|TWPR_IMPRINTERBOTTOMBEFORE
define|#
directive|define
name|TWPR_IMPRINTERBOTTOMBEFORE
value|2
end_define

begin_define
DECL|macro|TWPR_IMPRINTERBOTTOMAFTER
define|#
directive|define
name|TWPR_IMPRINTERBOTTOMAFTER
value|3
end_define

begin_define
DECL|macro|TWPR_ENDORSERTOPBEFORE
define|#
directive|define
name|TWPR_ENDORSERTOPBEFORE
value|4
end_define

begin_define
DECL|macro|TWPR_ENDORSERTOPAFTER
define|#
directive|define
name|TWPR_ENDORSERTOPAFTER
value|5
end_define

begin_define
DECL|macro|TWPR_ENDORSERBOTTOMBEFORE
define|#
directive|define
name|TWPR_ENDORSERBOTTOMBEFORE
value|6
end_define

begin_define
DECL|macro|TWPR_ENDORSERBOTTOMAFTER
define|#
directive|define
name|TWPR_ENDORSERBOTTOMAFTER
value|7
end_define

begin_comment
comment|/* CAP_PRINTERMODE values (PM_ means printer mode) */
end_comment

begin_define
DECL|macro|TWPM_SINGLESTRING
define|#
directive|define
name|TWPM_SINGLESTRING
value|0
end_define

begin_define
DECL|macro|TWPM_MULTISTRING
define|#
directive|define
name|TWPM_MULTISTRING
value|1
end_define

begin_define
DECL|macro|TWPM_COMPOUNDSTRING
define|#
directive|define
name|TWPM_COMPOUNDSTRING
value|2
end_define

begin_comment
comment|/* ICAP_BARCODESEARCHMODE values (SRCH_ means search) */
end_comment

begin_define
DECL|macro|SRCH_HORZ
define|#
directive|define
name|SRCH_HORZ
value|0
end_define

begin_define
DECL|macro|SRCH_VERT
define|#
directive|define
name|SRCH_VERT
value|1
end_define

begin_define
DECL|macro|SRCH_HORZVERT
define|#
directive|define
name|SRCH_HORZVERT
value|2
end_define

begin_define
DECL|macro|SRCH_VERTHORZ
define|#
directive|define
name|SRCH_VERTHORZ
value|3
end_define

begin_comment
comment|/* ICAP_FLASHUSED2 values (FL_ means flash) */
end_comment

begin_define
DECL|macro|TWFL_NONE
define|#
directive|define
name|TWFL_NONE
value|0
end_define

begin_define
DECL|macro|TWFL_OFF
define|#
directive|define
name|TWFL_OFF
value|1
end_define

begin_define
DECL|macro|TWFL_ON
define|#
directive|define
name|TWFL_ON
value|2
end_define

begin_define
DECL|macro|TWFL_AUTO
define|#
directive|define
name|TWFL_AUTO
value|3
end_define

begin_define
DECL|macro|TWFL_REDEYE
define|#
directive|define
name|TWFL_REDEYE
value|4
end_define

begin_comment
comment|/* ICAP_FLIPROTATION values (FR_ means flip rotation) */
end_comment

begin_define
DECL|macro|TWFR_BOOK
define|#
directive|define
name|TWFR_BOOK
value|0
end_define

begin_define
DECL|macro|TWFR_FANFOLD
define|#
directive|define
name|TWFR_FANFOLD
value|1
end_define

begin_comment
comment|/* ICAP_IMAGEFILTER values (IF_ means image filter) */
end_comment

begin_define
DECL|macro|TWIF_NONE
define|#
directive|define
name|TWIF_NONE
value|0
end_define

begin_define
DECL|macro|TWIF_AUTO
define|#
directive|define
name|TWIF_AUTO
value|1
end_define

begin_define
DECL|macro|TWIF_LOWPASS
define|#
directive|define
name|TWIF_LOWPASS
value|2
end_define

begin_define
DECL|macro|TWIF_BANDPASS
define|#
directive|define
name|TWIF_BANDPASS
value|3
end_define

begin_define
DECL|macro|TWIF_HIGHPASS
define|#
directive|define
name|TWIF_HIGHPASS
value|4
end_define

begin_define
DECL|macro|TWIF_TEXT
define|#
directive|define
name|TWIF_TEXT
value|TWIF_BANDPASS
end_define

begin_define
DECL|macro|TWIF_FINELINE
define|#
directive|define
name|TWIF_FINELINE
value|TWIF_HIGHPASS
end_define

begin_comment
comment|/* ICAP_NOISEFILTER values (NF_ means noise filter) */
end_comment

begin_define
DECL|macro|TWNF_NONE
define|#
directive|define
name|TWNF_NONE
value|0
end_define

begin_define
DECL|macro|TWNF_AUTO
define|#
directive|define
name|TWNF_AUTO
value|1
end_define

begin_define
DECL|macro|TWNF_LONEPIXEL
define|#
directive|define
name|TWNF_LONEPIXEL
value|2
end_define

begin_define
DECL|macro|TWNF_MAJORITYRULE
define|#
directive|define
name|TWNF_MAJORITYRULE
value|3
end_define

begin_comment
comment|/* ICAP_OVERSCAN values (OV_ means overscan) */
end_comment

begin_define
DECL|macro|TWOV_NONE
define|#
directive|define
name|TWOV_NONE
value|0
end_define

begin_define
DECL|macro|TWOV_AUTO
define|#
directive|define
name|TWOV_AUTO
value|1
end_define

begin_define
DECL|macro|TWOV_TOPBOTTOM
define|#
directive|define
name|TWOV_TOPBOTTOM
value|2
end_define

begin_define
DECL|macro|TWOV_LEFTRIGHT
define|#
directive|define
name|TWOV_LEFTRIGHT
value|3
end_define

begin_define
DECL|macro|TWOV_ALL
define|#
directive|define
name|TWOV_ALL
value|4
end_define

begin_comment
comment|/* TW_FILESYSTEM.FileType values (FT_ means file type) */
end_comment

begin_define
DECL|macro|TWFY_CAMERA
define|#
directive|define
name|TWFY_CAMERA
value|0
end_define

begin_define
DECL|macro|TWFY_CAMERATOP
define|#
directive|define
name|TWFY_CAMERATOP
value|1
end_define

begin_define
DECL|macro|TWFY_CAMERABOTTOM
define|#
directive|define
name|TWFY_CAMERABOTTOM
value|2
end_define

begin_define
DECL|macro|TWFY_CAMERAPREVIEW
define|#
directive|define
name|TWFY_CAMERAPREVIEW
value|3
end_define

begin_define
DECL|macro|TWFY_DOMAIN
define|#
directive|define
name|TWFY_DOMAIN
value|4
end_define

begin_define
DECL|macro|TWFY_HOST
define|#
directive|define
name|TWFY_HOST
value|5
end_define

begin_define
DECL|macro|TWFY_DIRECTORY
define|#
directive|define
name|TWFY_DIRECTORY
value|6
end_define

begin_define
DECL|macro|TWFY_IMAGE
define|#
directive|define
name|TWFY_IMAGE
value|7
end_define

begin_define
DECL|macro|TWFY_UNKNOWN
define|#
directive|define
name|TWFY_UNKNOWN
value|8
end_define

begin_comment
comment|/****************************************************************************  * Country Constants                                                        *  ****************************************************************************/
end_comment

begin_define
DECL|macro|TWCY_AFGHANISTAN
define|#
directive|define
name|TWCY_AFGHANISTAN
value|1001
end_define

begin_define
DECL|macro|TWCY_ALGERIA
define|#
directive|define
name|TWCY_ALGERIA
value|213
end_define

begin_define
DECL|macro|TWCY_AMERICANSAMOA
define|#
directive|define
name|TWCY_AMERICANSAMOA
value|684
end_define

begin_define
DECL|macro|TWCY_ANDORRA
define|#
directive|define
name|TWCY_ANDORRA
value|033
end_define

begin_define
DECL|macro|TWCY_ANGOLA
define|#
directive|define
name|TWCY_ANGOLA
value|1002
end_define

begin_define
DECL|macro|TWCY_ANGUILLA
define|#
directive|define
name|TWCY_ANGUILLA
value|8090
end_define

begin_define
DECL|macro|TWCY_ANTIGUA
define|#
directive|define
name|TWCY_ANTIGUA
value|8091
end_define

begin_define
DECL|macro|TWCY_ARGENTINA
define|#
directive|define
name|TWCY_ARGENTINA
value|54
end_define

begin_define
DECL|macro|TWCY_ARUBA
define|#
directive|define
name|TWCY_ARUBA
value|297
end_define

begin_define
DECL|macro|TWCY_ASCENSIONI
define|#
directive|define
name|TWCY_ASCENSIONI
value|247
end_define

begin_define
DECL|macro|TWCY_AUSTRALIA
define|#
directive|define
name|TWCY_AUSTRALIA
value|61
end_define

begin_define
DECL|macro|TWCY_AUSTRIA
define|#
directive|define
name|TWCY_AUSTRIA
value|43
end_define

begin_define
DECL|macro|TWCY_BAHAMAS
define|#
directive|define
name|TWCY_BAHAMAS
value|8092
end_define

begin_define
DECL|macro|TWCY_BAHRAIN
define|#
directive|define
name|TWCY_BAHRAIN
value|973
end_define

begin_define
DECL|macro|TWCY_BANGLADESH
define|#
directive|define
name|TWCY_BANGLADESH
value|880
end_define

begin_define
DECL|macro|TWCY_BARBADOS
define|#
directive|define
name|TWCY_BARBADOS
value|8093
end_define

begin_define
DECL|macro|TWCY_BELGIUM
define|#
directive|define
name|TWCY_BELGIUM
value|32
end_define

begin_define
DECL|macro|TWCY_BELIZE
define|#
directive|define
name|TWCY_BELIZE
value|501
end_define

begin_define
DECL|macro|TWCY_BENIN
define|#
directive|define
name|TWCY_BENIN
value|229
end_define

begin_define
DECL|macro|TWCY_BERMUDA
define|#
directive|define
name|TWCY_BERMUDA
value|8094
end_define

begin_define
DECL|macro|TWCY_BHUTAN
define|#
directive|define
name|TWCY_BHUTAN
value|1003
end_define

begin_define
DECL|macro|TWCY_BOLIVIA
define|#
directive|define
name|TWCY_BOLIVIA
value|591
end_define

begin_define
DECL|macro|TWCY_BOTSWANA
define|#
directive|define
name|TWCY_BOTSWANA
value|267
end_define

begin_define
DECL|macro|TWCY_BRITAIN
define|#
directive|define
name|TWCY_BRITAIN
value|6
end_define

begin_define
DECL|macro|TWCY_BRITVIRGINIS
define|#
directive|define
name|TWCY_BRITVIRGINIS
value|8095
end_define

begin_define
DECL|macro|TWCY_BRAZIL
define|#
directive|define
name|TWCY_BRAZIL
value|55
end_define

begin_define
DECL|macro|TWCY_BRUNEI
define|#
directive|define
name|TWCY_BRUNEI
value|673
end_define

begin_define
DECL|macro|TWCY_BULGARIA
define|#
directive|define
name|TWCY_BULGARIA
value|359
end_define

begin_define
DECL|macro|TWCY_BURKINAFASO
define|#
directive|define
name|TWCY_BURKINAFASO
value|1004
end_define

begin_define
DECL|macro|TWCY_BURMA
define|#
directive|define
name|TWCY_BURMA
value|1005
end_define

begin_define
DECL|macro|TWCY_BURUNDI
define|#
directive|define
name|TWCY_BURUNDI
value|1006
end_define

begin_define
DECL|macro|TWCY_CAMAROON
define|#
directive|define
name|TWCY_CAMAROON
value|237
end_define

begin_define
DECL|macro|TWCY_CANADA
define|#
directive|define
name|TWCY_CANADA
value|2
end_define

begin_define
DECL|macro|TWCY_CAPEVERDEIS
define|#
directive|define
name|TWCY_CAPEVERDEIS
value|238
end_define

begin_define
DECL|macro|TWCY_CAYMANIS
define|#
directive|define
name|TWCY_CAYMANIS
value|8096
end_define

begin_define
DECL|macro|TWCY_CENTRALAFREP
define|#
directive|define
name|TWCY_CENTRALAFREP
value|1007
end_define

begin_define
DECL|macro|TWCY_CHAD
define|#
directive|define
name|TWCY_CHAD
value|1008
end_define

begin_define
DECL|macro|TWCY_CHILE
define|#
directive|define
name|TWCY_CHILE
value|56
end_define

begin_define
DECL|macro|TWCY_CHINA
define|#
directive|define
name|TWCY_CHINA
value|86
end_define

begin_define
DECL|macro|TWCY_CHRISTMASIS
define|#
directive|define
name|TWCY_CHRISTMASIS
value|1009
end_define

begin_define
DECL|macro|TWCY_COCOSIS
define|#
directive|define
name|TWCY_COCOSIS
value|1009
end_define

begin_define
DECL|macro|TWCY_COLOMBIA
define|#
directive|define
name|TWCY_COLOMBIA
value|57
end_define

begin_define
DECL|macro|TWCY_COMOROS
define|#
directive|define
name|TWCY_COMOROS
value|1010
end_define

begin_define
DECL|macro|TWCY_CONGO
define|#
directive|define
name|TWCY_CONGO
value|1011
end_define

begin_define
DECL|macro|TWCY_COOKIS
define|#
directive|define
name|TWCY_COOKIS
value|1012
end_define

begin_define
DECL|macro|TWCY_COSTARICA
define|#
directive|define
name|TWCY_COSTARICA
value|506
end_define

begin_define
DECL|macro|TWCY_CUBA
define|#
directive|define
name|TWCY_CUBA
value|005
end_define

begin_define
DECL|macro|TWCY_CYPRUS
define|#
directive|define
name|TWCY_CYPRUS
value|357
end_define

begin_define
DECL|macro|TWCY_CZECHOSLOVAKIA
define|#
directive|define
name|TWCY_CZECHOSLOVAKIA
value|42
end_define

begin_define
DECL|macro|TWCY_DENMARK
define|#
directive|define
name|TWCY_DENMARK
value|45
end_define

begin_define
DECL|macro|TWCY_DJIBOUTI
define|#
directive|define
name|TWCY_DJIBOUTI
value|1013
end_define

begin_define
DECL|macro|TWCY_DOMINICA
define|#
directive|define
name|TWCY_DOMINICA
value|8097
end_define

begin_define
DECL|macro|TWCY_DOMINCANREP
define|#
directive|define
name|TWCY_DOMINCANREP
value|8098
end_define

begin_define
DECL|macro|TWCY_EASTERIS
define|#
directive|define
name|TWCY_EASTERIS
value|1014
end_define

begin_define
DECL|macro|TWCY_ECUADOR
define|#
directive|define
name|TWCY_ECUADOR
value|593
end_define

begin_define
DECL|macro|TWCY_EGYPT
define|#
directive|define
name|TWCY_EGYPT
value|20
end_define

begin_define
DECL|macro|TWCY_ELSALVADOR
define|#
directive|define
name|TWCY_ELSALVADOR
value|503
end_define

begin_define
DECL|macro|TWCY_EQGUINEA
define|#
directive|define
name|TWCY_EQGUINEA
value|1015
end_define

begin_define
DECL|macro|TWCY_ETHIOPIA
define|#
directive|define
name|TWCY_ETHIOPIA
value|251
end_define

begin_define
DECL|macro|TWCY_FALKLANDIS
define|#
directive|define
name|TWCY_FALKLANDIS
value|1016
end_define

begin_define
DECL|macro|TWCY_FAEROEIS
define|#
directive|define
name|TWCY_FAEROEIS
value|298
end_define

begin_define
DECL|macro|TWCY_FIJIISLANDS
define|#
directive|define
name|TWCY_FIJIISLANDS
value|679
end_define

begin_define
DECL|macro|TWCY_FINLAND
define|#
directive|define
name|TWCY_FINLAND
value|358
end_define

begin_define
DECL|macro|TWCY_FRANCE
define|#
directive|define
name|TWCY_FRANCE
value|33
end_define

begin_define
DECL|macro|TWCY_FRANTILLES
define|#
directive|define
name|TWCY_FRANTILLES
value|596
end_define

begin_define
DECL|macro|TWCY_FRGUIANA
define|#
directive|define
name|TWCY_FRGUIANA
value|594
end_define

begin_define
DECL|macro|TWCY_FRPOLYNEISA
define|#
directive|define
name|TWCY_FRPOLYNEISA
value|689
end_define

begin_define
DECL|macro|TWCY_FUTANAIS
define|#
directive|define
name|TWCY_FUTANAIS
value|1043
end_define

begin_define
DECL|macro|TWCY_GABON
define|#
directive|define
name|TWCY_GABON
value|241
end_define

begin_define
DECL|macro|TWCY_GAMBIA
define|#
directive|define
name|TWCY_GAMBIA
value|220
end_define

begin_define
DECL|macro|TWCY_GERMANY
define|#
directive|define
name|TWCY_GERMANY
value|49
end_define

begin_define
DECL|macro|TWCY_GHANA
define|#
directive|define
name|TWCY_GHANA
value|233
end_define

begin_define
DECL|macro|TWCY_GIBRALTER
define|#
directive|define
name|TWCY_GIBRALTER
value|350
end_define

begin_define
DECL|macro|TWCY_GREECE
define|#
directive|define
name|TWCY_GREECE
value|30
end_define

begin_define
DECL|macro|TWCY_GREENLAND
define|#
directive|define
name|TWCY_GREENLAND
value|299
end_define

begin_define
DECL|macro|TWCY_GRENADA
define|#
directive|define
name|TWCY_GRENADA
value|8099
end_define

begin_define
DECL|macro|TWCY_GRENEDINES
define|#
directive|define
name|TWCY_GRENEDINES
value|8015
end_define

begin_define
DECL|macro|TWCY_GUADELOUPE
define|#
directive|define
name|TWCY_GUADELOUPE
value|590
end_define

begin_define
DECL|macro|TWCY_GUAM
define|#
directive|define
name|TWCY_GUAM
value|671
end_define

begin_define
DECL|macro|TWCY_GUANTANAMOBAY
define|#
directive|define
name|TWCY_GUANTANAMOBAY
value|5399
end_define

begin_define
DECL|macro|TWCY_GUATEMALA
define|#
directive|define
name|TWCY_GUATEMALA
value|502
end_define

begin_define
DECL|macro|TWCY_GUINEA
define|#
directive|define
name|TWCY_GUINEA
value|224
end_define

begin_define
DECL|macro|TWCY_GUINEABISSAU
define|#
directive|define
name|TWCY_GUINEABISSAU
value|1017
end_define

begin_define
DECL|macro|TWCY_GUYANA
define|#
directive|define
name|TWCY_GUYANA
value|592
end_define

begin_define
DECL|macro|TWCY_HAITI
define|#
directive|define
name|TWCY_HAITI
value|509
end_define

begin_define
DECL|macro|TWCY_HONDURAS
define|#
directive|define
name|TWCY_HONDURAS
value|504
end_define

begin_define
DECL|macro|TWCY_HONGKONG
define|#
directive|define
name|TWCY_HONGKONG
value|852
end_define

begin_define
DECL|macro|TWCY_HUNGARY
define|#
directive|define
name|TWCY_HUNGARY
value|36
end_define

begin_define
DECL|macro|TWCY_ICELAND
define|#
directive|define
name|TWCY_ICELAND
value|354
end_define

begin_define
DECL|macro|TWCY_INDIA
define|#
directive|define
name|TWCY_INDIA
value|91
end_define

begin_define
DECL|macro|TWCY_INDONESIA
define|#
directive|define
name|TWCY_INDONESIA
value|62
end_define

begin_define
DECL|macro|TWCY_IRAN
define|#
directive|define
name|TWCY_IRAN
value|98
end_define

begin_define
DECL|macro|TWCY_IRAQ
define|#
directive|define
name|TWCY_IRAQ
value|964
end_define

begin_define
DECL|macro|TWCY_IRELAND
define|#
directive|define
name|TWCY_IRELAND
value|353
end_define

begin_define
DECL|macro|TWCY_ISRAEL
define|#
directive|define
name|TWCY_ISRAEL
value|972
end_define

begin_define
DECL|macro|TWCY_ITALY
define|#
directive|define
name|TWCY_ITALY
value|39
end_define

begin_define
DECL|macro|TWCY_IVORYCOAST
define|#
directive|define
name|TWCY_IVORYCOAST
value|225
end_define

begin_define
DECL|macro|TWCY_JAMAICA
define|#
directive|define
name|TWCY_JAMAICA
value|8010
end_define

begin_define
DECL|macro|TWCY_JAPAN
define|#
directive|define
name|TWCY_JAPAN
value|81
end_define

begin_define
DECL|macro|TWCY_JORDAN
define|#
directive|define
name|TWCY_JORDAN
value|962
end_define

begin_define
DECL|macro|TWCY_KENYA
define|#
directive|define
name|TWCY_KENYA
value|254
end_define

begin_define
DECL|macro|TWCY_KIRIBATI
define|#
directive|define
name|TWCY_KIRIBATI
value|1018
end_define

begin_define
DECL|macro|TWCY_KOREA
define|#
directive|define
name|TWCY_KOREA
value|82
end_define

begin_define
DECL|macro|TWCY_KUWAIT
define|#
directive|define
name|TWCY_KUWAIT
value|965
end_define

begin_define
DECL|macro|TWCY_LAOS
define|#
directive|define
name|TWCY_LAOS
value|1019
end_define

begin_define
DECL|macro|TWCY_LEBANON
define|#
directive|define
name|TWCY_LEBANON
value|1020
end_define

begin_define
DECL|macro|TWCY_LIBERIA
define|#
directive|define
name|TWCY_LIBERIA
value|231
end_define

begin_define
DECL|macro|TWCY_LIBYA
define|#
directive|define
name|TWCY_LIBYA
value|218
end_define

begin_define
DECL|macro|TWCY_LIECHTENSTEIN
define|#
directive|define
name|TWCY_LIECHTENSTEIN
value|41
end_define

begin_define
DECL|macro|TWCY_LUXENBOURG
define|#
directive|define
name|TWCY_LUXENBOURG
value|352
end_define

begin_define
DECL|macro|TWCY_MACAO
define|#
directive|define
name|TWCY_MACAO
value|853
end_define

begin_define
DECL|macro|TWCY_MADAGASCAR
define|#
directive|define
name|TWCY_MADAGASCAR
value|1021
end_define

begin_define
DECL|macro|TWCY_MALAWI
define|#
directive|define
name|TWCY_MALAWI
value|265
end_define

begin_define
DECL|macro|TWCY_MALAYSIA
define|#
directive|define
name|TWCY_MALAYSIA
value|60
end_define

begin_define
DECL|macro|TWCY_MALDIVES
define|#
directive|define
name|TWCY_MALDIVES
value|960
end_define

begin_define
DECL|macro|TWCY_MALI
define|#
directive|define
name|TWCY_MALI
value|1022
end_define

begin_define
DECL|macro|TWCY_MALTA
define|#
directive|define
name|TWCY_MALTA
value|356
end_define

begin_define
DECL|macro|TWCY_MARSHALLIS
define|#
directive|define
name|TWCY_MARSHALLIS
value|692
end_define

begin_define
DECL|macro|TWCY_MAURITANIA
define|#
directive|define
name|TWCY_MAURITANIA
value|1023
end_define

begin_define
DECL|macro|TWCY_MAURITIUS
define|#
directive|define
name|TWCY_MAURITIUS
value|230
end_define

begin_define
DECL|macro|TWCY_MEXICO
define|#
directive|define
name|TWCY_MEXICO
value|3
end_define

begin_define
DECL|macro|TWCY_MICRONESIA
define|#
directive|define
name|TWCY_MICRONESIA
value|691
end_define

begin_define
DECL|macro|TWCY_MIQUELON
define|#
directive|define
name|TWCY_MIQUELON
value|508
end_define

begin_define
DECL|macro|TWCY_MONACO
define|#
directive|define
name|TWCY_MONACO
value|33
end_define

begin_define
DECL|macro|TWCY_MONGOLIA
define|#
directive|define
name|TWCY_MONGOLIA
value|1024
end_define

begin_define
DECL|macro|TWCY_MONTSERRAT
define|#
directive|define
name|TWCY_MONTSERRAT
value|8011
end_define

begin_define
DECL|macro|TWCY_MOROCCO
define|#
directive|define
name|TWCY_MOROCCO
value|212
end_define

begin_define
DECL|macro|TWCY_MOZAMBIQUE
define|#
directive|define
name|TWCY_MOZAMBIQUE
value|1025
end_define

begin_define
DECL|macro|TWCY_NAMIBIA
define|#
directive|define
name|TWCY_NAMIBIA
value|264
end_define

begin_define
DECL|macro|TWCY_NAURU
define|#
directive|define
name|TWCY_NAURU
value|1026
end_define

begin_define
DECL|macro|TWCY_NEPAL
define|#
directive|define
name|TWCY_NEPAL
value|977
end_define

begin_define
DECL|macro|TWCY_NETHERLANDS
define|#
directive|define
name|TWCY_NETHERLANDS
value|31
end_define

begin_define
DECL|macro|TWCY_NETHANTILLES
define|#
directive|define
name|TWCY_NETHANTILLES
value|599
end_define

begin_define
DECL|macro|TWCY_NEVIS
define|#
directive|define
name|TWCY_NEVIS
value|8012
end_define

begin_define
DECL|macro|TWCY_NEWCALEDONIA
define|#
directive|define
name|TWCY_NEWCALEDONIA
value|687
end_define

begin_define
DECL|macro|TWCY_NEWZEALAND
define|#
directive|define
name|TWCY_NEWZEALAND
value|64
end_define

begin_define
DECL|macro|TWCY_NICARAGUA
define|#
directive|define
name|TWCY_NICARAGUA
value|505
end_define

begin_define
DECL|macro|TWCY_NIGER
define|#
directive|define
name|TWCY_NIGER
value|227
end_define

begin_define
DECL|macro|TWCY_NIGERIA
define|#
directive|define
name|TWCY_NIGERIA
value|234
end_define

begin_define
DECL|macro|TWCY_NIUE
define|#
directive|define
name|TWCY_NIUE
value|1027
end_define

begin_define
DECL|macro|TWCY_NORFOLKI
define|#
directive|define
name|TWCY_NORFOLKI
value|1028
end_define

begin_define
DECL|macro|TWCY_NORWAY
define|#
directive|define
name|TWCY_NORWAY
value|47
end_define

begin_define
DECL|macro|TWCY_OMAN
define|#
directive|define
name|TWCY_OMAN
value|968
end_define

begin_define
DECL|macro|TWCY_PAKISTAN
define|#
directive|define
name|TWCY_PAKISTAN
value|92
end_define

begin_define
DECL|macro|TWCY_PALAU
define|#
directive|define
name|TWCY_PALAU
value|1029
end_define

begin_define
DECL|macro|TWCY_PANAMA
define|#
directive|define
name|TWCY_PANAMA
value|507
end_define

begin_define
DECL|macro|TWCY_PARAGUAY
define|#
directive|define
name|TWCY_PARAGUAY
value|595
end_define

begin_define
DECL|macro|TWCY_PERU
define|#
directive|define
name|TWCY_PERU
value|51
end_define

begin_define
DECL|macro|TWCY_PHILLIPPINES
define|#
directive|define
name|TWCY_PHILLIPPINES
value|63
end_define

begin_define
DECL|macro|TWCY_PITCAIRNIS
define|#
directive|define
name|TWCY_PITCAIRNIS
value|1030
end_define

begin_define
DECL|macro|TWCY_PNEWGUINEA
define|#
directive|define
name|TWCY_PNEWGUINEA
value|675
end_define

begin_define
DECL|macro|TWCY_POLAND
define|#
directive|define
name|TWCY_POLAND
value|48
end_define

begin_define
DECL|macro|TWCY_PORTUGAL
define|#
directive|define
name|TWCY_PORTUGAL
value|351
end_define

begin_define
DECL|macro|TWCY_QATAR
define|#
directive|define
name|TWCY_QATAR
value|974
end_define

begin_define
DECL|macro|TWCY_REUNIONI
define|#
directive|define
name|TWCY_REUNIONI
value|1031
end_define

begin_define
DECL|macro|TWCY_ROMANIA
define|#
directive|define
name|TWCY_ROMANIA
value|40
end_define

begin_define
DECL|macro|TWCY_RWANDA
define|#
directive|define
name|TWCY_RWANDA
value|250
end_define

begin_define
DECL|macro|TWCY_SAIPAN
define|#
directive|define
name|TWCY_SAIPAN
value|670
end_define

begin_define
DECL|macro|TWCY_SANMARINO
define|#
directive|define
name|TWCY_SANMARINO
value|39
end_define

begin_define
DECL|macro|TWCY_SAOTOME
define|#
directive|define
name|TWCY_SAOTOME
value|1033
end_define

begin_define
DECL|macro|TWCY_SAUDIARABIA
define|#
directive|define
name|TWCY_SAUDIARABIA
value|966
end_define

begin_define
DECL|macro|TWCY_SENEGAL
define|#
directive|define
name|TWCY_SENEGAL
value|221
end_define

begin_define
DECL|macro|TWCY_SEYCHELLESIS
define|#
directive|define
name|TWCY_SEYCHELLESIS
value|1034
end_define

begin_define
DECL|macro|TWCY_SIERRALEONE
define|#
directive|define
name|TWCY_SIERRALEONE
value|1035
end_define

begin_define
DECL|macro|TWCY_SINGAPORE
define|#
directive|define
name|TWCY_SINGAPORE
value|65
end_define

begin_define
DECL|macro|TWCY_SOLOMONIS
define|#
directive|define
name|TWCY_SOLOMONIS
value|1036
end_define

begin_define
DECL|macro|TWCY_SOMALI
define|#
directive|define
name|TWCY_SOMALI
value|1037
end_define

begin_define
DECL|macro|TWCY_SOUTHAFRICA
define|#
directive|define
name|TWCY_SOUTHAFRICA
value|27
end_define

begin_define
DECL|macro|TWCY_SPAIN
define|#
directive|define
name|TWCY_SPAIN
value|34
end_define

begin_define
DECL|macro|TWCY_SRILANKA
define|#
directive|define
name|TWCY_SRILANKA
value|94
end_define

begin_define
DECL|macro|TWCY_STHELENA
define|#
directive|define
name|TWCY_STHELENA
value|1032
end_define

begin_define
DECL|macro|TWCY_STKITTS
define|#
directive|define
name|TWCY_STKITTS
value|8013
end_define

begin_define
DECL|macro|TWCY_STLUCIA
define|#
directive|define
name|TWCY_STLUCIA
value|8014
end_define

begin_define
DECL|macro|TWCY_STPIERRE
define|#
directive|define
name|TWCY_STPIERRE
value|508
end_define

begin_define
DECL|macro|TWCY_STVINCENT
define|#
directive|define
name|TWCY_STVINCENT
value|8015
end_define

begin_define
DECL|macro|TWCY_SUDAN
define|#
directive|define
name|TWCY_SUDAN
value|1038
end_define

begin_define
DECL|macro|TWCY_SURINAME
define|#
directive|define
name|TWCY_SURINAME
value|597
end_define

begin_define
DECL|macro|TWCY_SWAZILAND
define|#
directive|define
name|TWCY_SWAZILAND
value|268
end_define

begin_define
DECL|macro|TWCY_SWEDEN
define|#
directive|define
name|TWCY_SWEDEN
value|46
end_define

begin_define
DECL|macro|TWCY_SWITZERLAND
define|#
directive|define
name|TWCY_SWITZERLAND
value|41
end_define

begin_define
DECL|macro|TWCY_SYRIA
define|#
directive|define
name|TWCY_SYRIA
value|1039
end_define

begin_define
DECL|macro|TWCY_TAIWAN
define|#
directive|define
name|TWCY_TAIWAN
value|886
end_define

begin_define
DECL|macro|TWCY_TANZANIA
define|#
directive|define
name|TWCY_TANZANIA
value|255
end_define

begin_define
DECL|macro|TWCY_THAILAND
define|#
directive|define
name|TWCY_THAILAND
value|66
end_define

begin_define
DECL|macro|TWCY_TOBAGO
define|#
directive|define
name|TWCY_TOBAGO
value|8016
end_define

begin_define
DECL|macro|TWCY_TOGO
define|#
directive|define
name|TWCY_TOGO
value|228
end_define

begin_define
DECL|macro|TWCY_TONGAIS
define|#
directive|define
name|TWCY_TONGAIS
value|676
end_define

begin_define
DECL|macro|TWCY_TRINIDAD
define|#
directive|define
name|TWCY_TRINIDAD
value|8016
end_define

begin_define
DECL|macro|TWCY_TUNISIA
define|#
directive|define
name|TWCY_TUNISIA
value|216
end_define

begin_define
DECL|macro|TWCY_TURKEY
define|#
directive|define
name|TWCY_TURKEY
value|90
end_define

begin_define
DECL|macro|TWCY_TURKSCAICOS
define|#
directive|define
name|TWCY_TURKSCAICOS
value|8017
end_define

begin_define
DECL|macro|TWCY_TUVALU
define|#
directive|define
name|TWCY_TUVALU
value|1040
end_define

begin_define
DECL|macro|TWCY_UGANDA
define|#
directive|define
name|TWCY_UGANDA
value|256
end_define

begin_define
DECL|macro|TWCY_USSR
define|#
directive|define
name|TWCY_USSR
value|7
end_define

begin_define
DECL|macro|TWCY_UAEMIRATES
define|#
directive|define
name|TWCY_UAEMIRATES
value|971
end_define

begin_define
DECL|macro|TWCY_UNITEDKINGDOM
define|#
directive|define
name|TWCY_UNITEDKINGDOM
value|44
end_define

begin_define
DECL|macro|TWCY_USA
define|#
directive|define
name|TWCY_USA
value|1
end_define

begin_define
DECL|macro|TWCY_URUGUAY
define|#
directive|define
name|TWCY_URUGUAY
value|598
end_define

begin_define
DECL|macro|TWCY_VANUATU
define|#
directive|define
name|TWCY_VANUATU
value|1041
end_define

begin_define
DECL|macro|TWCY_VATICANCITY
define|#
directive|define
name|TWCY_VATICANCITY
value|39
end_define

begin_define
DECL|macro|TWCY_VENEZUELA
define|#
directive|define
name|TWCY_VENEZUELA
value|58
end_define

begin_define
DECL|macro|TWCY_WAKE
define|#
directive|define
name|TWCY_WAKE
value|1042
end_define

begin_define
DECL|macro|TWCY_WALLISIS
define|#
directive|define
name|TWCY_WALLISIS
value|1043
end_define

begin_define
DECL|macro|TWCY_WESTERNSAHARA
define|#
directive|define
name|TWCY_WESTERNSAHARA
value|1044
end_define

begin_define
DECL|macro|TWCY_WESTERNSAMOA
define|#
directive|define
name|TWCY_WESTERNSAMOA
value|1045
end_define

begin_define
DECL|macro|TWCY_YEMEN
define|#
directive|define
name|TWCY_YEMEN
value|1046
end_define

begin_define
DECL|macro|TWCY_YUGOSLAVIA
define|#
directive|define
name|TWCY_YUGOSLAVIA
value|38
end_define

begin_define
DECL|macro|TWCY_ZAIRE
define|#
directive|define
name|TWCY_ZAIRE
value|243
end_define

begin_define
DECL|macro|TWCY_ZAMBIA
define|#
directive|define
name|TWCY_ZAMBIA
value|260
end_define

begin_define
DECL|macro|TWCY_ZIMBABWE
define|#
directive|define
name|TWCY_ZIMBABWE
value|263
end_define

begin_comment
comment|/****************************************************************************  * Language Constants                                                       *  ****************************************************************************/
end_comment

begin_define
DECL|macro|TWLG_DAN
define|#
directive|define
name|TWLG_DAN
value|0
end_define

begin_comment
DECL|macro|TWLG_DAN
comment|/* Danish                 */
end_comment

begin_define
DECL|macro|TWLG_DUT
define|#
directive|define
name|TWLG_DUT
value|1
end_define

begin_comment
DECL|macro|TWLG_DUT
comment|/* Dutch                  */
end_comment

begin_define
DECL|macro|TWLG_ENG
define|#
directive|define
name|TWLG_ENG
value|2
end_define

begin_comment
DECL|macro|TWLG_ENG
comment|/* International English  */
end_comment

begin_define
DECL|macro|TWLG_FCF
define|#
directive|define
name|TWLG_FCF
value|3
end_define

begin_comment
DECL|macro|TWLG_FCF
comment|/* French Canadian        */
end_comment

begin_define
DECL|macro|TWLG_FIN
define|#
directive|define
name|TWLG_FIN
value|4
end_define

begin_comment
DECL|macro|TWLG_FIN
comment|/* Finnish                */
end_comment

begin_define
DECL|macro|TWLG_FRN
define|#
directive|define
name|TWLG_FRN
value|5
end_define

begin_comment
DECL|macro|TWLG_FRN
comment|/* French                 */
end_comment

begin_define
DECL|macro|TWLG_GER
define|#
directive|define
name|TWLG_GER
value|6
end_define

begin_comment
DECL|macro|TWLG_GER
comment|/* German                 */
end_comment

begin_define
DECL|macro|TWLG_ICE
define|#
directive|define
name|TWLG_ICE
value|7
end_define

begin_comment
DECL|macro|TWLG_ICE
comment|/* Icelandic              */
end_comment

begin_define
DECL|macro|TWLG_ITN
define|#
directive|define
name|TWLG_ITN
value|8
end_define

begin_comment
DECL|macro|TWLG_ITN
comment|/* Italian                */
end_comment

begin_define
DECL|macro|TWLG_NOR
define|#
directive|define
name|TWLG_NOR
value|9
end_define

begin_comment
DECL|macro|TWLG_NOR
comment|/* Norwegian              */
end_comment

begin_define
DECL|macro|TWLG_POR
define|#
directive|define
name|TWLG_POR
value|10
end_define

begin_comment
DECL|macro|TWLG_POR
comment|/* Portuguese             */
end_comment

begin_define
DECL|macro|TWLG_SPA
define|#
directive|define
name|TWLG_SPA
value|11
end_define

begin_comment
DECL|macro|TWLG_SPA
comment|/* Spanish                */
end_comment

begin_define
DECL|macro|TWLG_SWE
define|#
directive|define
name|TWLG_SWE
value|12
end_define

begin_comment
DECL|macro|TWLG_SWE
comment|/* Swedish                */
end_comment

begin_define
DECL|macro|TWLG_USA
define|#
directive|define
name|TWLG_USA
value|13
end_define

begin_comment
DECL|macro|TWLG_USA
comment|/* U.S. English           */
end_comment

begin_comment
comment|/* Added for 1.8 */
end_comment

begin_define
DECL|macro|TWLG_USERLOCALE
define|#
directive|define
name|TWLG_USERLOCALE
value|-1
end_define

begin_define
DECL|macro|TWLG_AFRIKAANS
define|#
directive|define
name|TWLG_AFRIKAANS
value|14
end_define

begin_define
DECL|macro|TWLG_ALBANIA
define|#
directive|define
name|TWLG_ALBANIA
value|15
end_define

begin_define
DECL|macro|TWLG_ARABIC
define|#
directive|define
name|TWLG_ARABIC
value|16
end_define

begin_define
DECL|macro|TWLG_ARABIC_ALGERIA
define|#
directive|define
name|TWLG_ARABIC_ALGERIA
value|17
end_define

begin_define
DECL|macro|TWLG_ARABIC_BAHRAIN
define|#
directive|define
name|TWLG_ARABIC_BAHRAIN
value|18
end_define

begin_define
DECL|macro|TWLG_ARABIC_EGYPT
define|#
directive|define
name|TWLG_ARABIC_EGYPT
value|19
end_define

begin_define
DECL|macro|TWLG_ARABIC_IRAQ
define|#
directive|define
name|TWLG_ARABIC_IRAQ
value|20
end_define

begin_define
DECL|macro|TWLG_ARABIC_JORDAN
define|#
directive|define
name|TWLG_ARABIC_JORDAN
value|21
end_define

begin_define
DECL|macro|TWLG_ARABIC_KUWAIT
define|#
directive|define
name|TWLG_ARABIC_KUWAIT
value|22
end_define

begin_define
DECL|macro|TWLG_ARABIC_LEBANON
define|#
directive|define
name|TWLG_ARABIC_LEBANON
value|23
end_define

begin_define
DECL|macro|TWLG_ARABIC_LIBYA
define|#
directive|define
name|TWLG_ARABIC_LIBYA
value|24
end_define

begin_define
DECL|macro|TWLG_ARABIC_MOROCCO
define|#
directive|define
name|TWLG_ARABIC_MOROCCO
value|25
end_define

begin_define
DECL|macro|TWLG_ARABIC_OMAN
define|#
directive|define
name|TWLG_ARABIC_OMAN
value|26
end_define

begin_define
DECL|macro|TWLG_ARABIC_QATAR
define|#
directive|define
name|TWLG_ARABIC_QATAR
value|27
end_define

begin_define
DECL|macro|TWLG_ARABIC_SAUDIARABIA
define|#
directive|define
name|TWLG_ARABIC_SAUDIARABIA
value|28
end_define

begin_define
DECL|macro|TWLG_ARABIC_SYRIA
define|#
directive|define
name|TWLG_ARABIC_SYRIA
value|29
end_define

begin_define
DECL|macro|TWLG_ARABIC_TUNISIA
define|#
directive|define
name|TWLG_ARABIC_TUNISIA
value|30
end_define

begin_define
DECL|macro|TWLG_ARABIC_UAE
define|#
directive|define
name|TWLG_ARABIC_UAE
value|31
end_define

begin_comment
DECL|macro|TWLG_ARABIC_UAE
comment|/* United Arabic Emirates */
end_comment

begin_define
DECL|macro|TWLG_ARABIC_YEMEN
define|#
directive|define
name|TWLG_ARABIC_YEMEN
value|32
end_define

begin_define
DECL|macro|TWLG_BASQUE
define|#
directive|define
name|TWLG_BASQUE
value|33
end_define

begin_define
DECL|macro|TWLG_BYELORUSSIAN
define|#
directive|define
name|TWLG_BYELORUSSIAN
value|34
end_define

begin_define
DECL|macro|TWLG_BULGARIAN
define|#
directive|define
name|TWLG_BULGARIAN
value|35
end_define

begin_define
DECL|macro|TWLG_CATALAN
define|#
directive|define
name|TWLG_CATALAN
value|36
end_define

begin_define
DECL|macro|TWLG_CHINESE
define|#
directive|define
name|TWLG_CHINESE
value|37
end_define

begin_define
DECL|macro|TWLG_CHINESE_HONGKONG
define|#
directive|define
name|TWLG_CHINESE_HONGKONG
value|38
end_define

begin_define
DECL|macro|TWLG_CHINESE_PRC
define|#
directive|define
name|TWLG_CHINESE_PRC
value|39
end_define

begin_comment
DECL|macro|TWLG_CHINESE_PRC
comment|/* People's Republic of China */
end_comment

begin_define
DECL|macro|TWLG_CHINESE_SINGAPORE
define|#
directive|define
name|TWLG_CHINESE_SINGAPORE
value|40
end_define

begin_define
DECL|macro|TWLG_CHINESE_SIMPLIFIED
define|#
directive|define
name|TWLG_CHINESE_SIMPLIFIED
value|41
end_define

begin_define
DECL|macro|TWLG_CHINESE_TAIWAN
define|#
directive|define
name|TWLG_CHINESE_TAIWAN
value|42
end_define

begin_define
DECL|macro|TWLG_CHINESE_TRADITIONAL
define|#
directive|define
name|TWLG_CHINESE_TRADITIONAL
value|43
end_define

begin_define
DECL|macro|TWLG_CROATIA
define|#
directive|define
name|TWLG_CROATIA
value|44
end_define

begin_define
DECL|macro|TWLG_CZECH
define|#
directive|define
name|TWLG_CZECH
value|45
end_define

begin_define
DECL|macro|TWLG_DANISH
define|#
directive|define
name|TWLG_DANISH
value|TWLG_DAN
end_define

begin_define
DECL|macro|TWLG_DUTCH
define|#
directive|define
name|TWLG_DUTCH
value|TWLG_DUT
end_define

begin_define
DECL|macro|TWLG_DUTCH_BELGIAN
define|#
directive|define
name|TWLG_DUTCH_BELGIAN
value|46
end_define

begin_define
DECL|macro|TWLG_ENGLISH
define|#
directive|define
name|TWLG_ENGLISH
value|TWLG_ENG
end_define

begin_define
DECL|macro|TWLG_ENGLISH_AUSTRALIAN
define|#
directive|define
name|TWLG_ENGLISH_AUSTRALIAN
value|47
end_define

begin_define
DECL|macro|TWLG_ENGLISH_CANADIAN
define|#
directive|define
name|TWLG_ENGLISH_CANADIAN
value|48
end_define

begin_define
DECL|macro|TWLG_ENGLISH_IRELAND
define|#
directive|define
name|TWLG_ENGLISH_IRELAND
value|49
end_define

begin_define
DECL|macro|TWLG_ENGLISH_NEWZEALAND
define|#
directive|define
name|TWLG_ENGLISH_NEWZEALAND
value|50
end_define

begin_define
DECL|macro|TWLG_ENGLISH_SOUTHAFRICA
define|#
directive|define
name|TWLG_ENGLISH_SOUTHAFRICA
value|51
end_define

begin_define
DECL|macro|TWLG_ENGLISH_UK
define|#
directive|define
name|TWLG_ENGLISH_UK
value|52
end_define

begin_define
DECL|macro|TWLG_ENGLISH_USA
define|#
directive|define
name|TWLG_ENGLISH_USA
value|TWLG_USA
end_define

begin_define
DECL|macro|TWLG_ESTONIAN
define|#
directive|define
name|TWLG_ESTONIAN
value|53
end_define

begin_define
DECL|macro|TWLG_FAEROESE
define|#
directive|define
name|TWLG_FAEROESE
value|54
end_define

begin_define
DECL|macro|TWLG_FARSI
define|#
directive|define
name|TWLG_FARSI
value|55
end_define

begin_define
DECL|macro|TWLG_FINNISH
define|#
directive|define
name|TWLG_FINNISH
value|TWLG_FIN
end_define

begin_define
DECL|macro|TWLG_FRENCH
define|#
directive|define
name|TWLG_FRENCH
value|TWLG_FRN
end_define

begin_define
DECL|macro|TWLG_FRENCH_BELGIAN
define|#
directive|define
name|TWLG_FRENCH_BELGIAN
value|56
end_define

begin_define
DECL|macro|TWLG_FRENCH_CANADIAN
define|#
directive|define
name|TWLG_FRENCH_CANADIAN
value|TWLG_FCF
end_define

begin_define
DECL|macro|TWLG_FRENCH_LUXEMBOURG
define|#
directive|define
name|TWLG_FRENCH_LUXEMBOURG
value|57
end_define

begin_define
DECL|macro|TWLG_FRENCH_SWISS
define|#
directive|define
name|TWLG_FRENCH_SWISS
value|58
end_define

begin_define
DECL|macro|TWLG_GERMAN
define|#
directive|define
name|TWLG_GERMAN
value|TWLG_GER
end_define

begin_define
DECL|macro|TWLG_GERMAN_AUSTRIAN
define|#
directive|define
name|TWLG_GERMAN_AUSTRIAN
value|59
end_define

begin_define
DECL|macro|TWLG_GERMAN_LUXEMBOURG
define|#
directive|define
name|TWLG_GERMAN_LUXEMBOURG
value|60
end_define

begin_define
DECL|macro|TWLG_GERMAN_LIECHTENSTEIN
define|#
directive|define
name|TWLG_GERMAN_LIECHTENSTEIN
value|61
end_define

begin_define
DECL|macro|TWLG_GERMAN_SWISS
define|#
directive|define
name|TWLG_GERMAN_SWISS
value|62
end_define

begin_define
DECL|macro|TWLG_GREEK
define|#
directive|define
name|TWLG_GREEK
value|63
end_define

begin_define
DECL|macro|TWLG_HEBREW
define|#
directive|define
name|TWLG_HEBREW
value|64
end_define

begin_define
DECL|macro|TWLG_HUNGARIAN
define|#
directive|define
name|TWLG_HUNGARIAN
value|65
end_define

begin_define
DECL|macro|TWLG_ICELANDIC
define|#
directive|define
name|TWLG_ICELANDIC
value|TWLG_ICE
end_define

begin_define
DECL|macro|TWLG_INDONESIAN
define|#
directive|define
name|TWLG_INDONESIAN
value|66
end_define

begin_define
DECL|macro|TWLG_ITALIAN
define|#
directive|define
name|TWLG_ITALIAN
value|TWLG_ITN
end_define

begin_define
DECL|macro|TWLG_ITALIAN_SWISS
define|#
directive|define
name|TWLG_ITALIAN_SWISS
value|67
end_define

begin_define
DECL|macro|TWLG_JAPANESE
define|#
directive|define
name|TWLG_JAPANESE
value|68
end_define

begin_define
DECL|macro|TWLG_KOREAN
define|#
directive|define
name|TWLG_KOREAN
value|69
end_define

begin_define
DECL|macro|TWLG_KOREAN_JOHAB
define|#
directive|define
name|TWLG_KOREAN_JOHAB
value|70
end_define

begin_define
DECL|macro|TWLG_LATVIAN
define|#
directive|define
name|TWLG_LATVIAN
value|71
end_define

begin_define
DECL|macro|TWLG_LITHUANIAN
define|#
directive|define
name|TWLG_LITHUANIAN
value|72
end_define

begin_define
DECL|macro|TWLG_NORWEGIAN
define|#
directive|define
name|TWLG_NORWEGIAN
value|TWLG_NOR
end_define

begin_define
DECL|macro|TWLG_NORWEGIAN_BOKMAL
define|#
directive|define
name|TWLG_NORWEGIAN_BOKMAL
value|73
end_define

begin_define
DECL|macro|TWLG_NORWEGIAN_NYNORSK
define|#
directive|define
name|TWLG_NORWEGIAN_NYNORSK
value|74
end_define

begin_define
DECL|macro|TWLG_POLISH
define|#
directive|define
name|TWLG_POLISH
value|75
end_define

begin_define
DECL|macro|TWLG_PORTUGUESE
define|#
directive|define
name|TWLG_PORTUGUESE
value|TWLG_POR
end_define

begin_define
DECL|macro|TWLG_PORTUGUESE_BRAZIL
define|#
directive|define
name|TWLG_PORTUGUESE_BRAZIL
value|76
end_define

begin_define
DECL|macro|TWLG_ROMANIAN
define|#
directive|define
name|TWLG_ROMANIAN
value|77
end_define

begin_define
DECL|macro|TWLG_RUSSIAN
define|#
directive|define
name|TWLG_RUSSIAN
value|78
end_define

begin_define
DECL|macro|TWLG_SERBIAN_LATIN
define|#
directive|define
name|TWLG_SERBIAN_LATIN
value|79
end_define

begin_define
DECL|macro|TWLG_SLOVAK
define|#
directive|define
name|TWLG_SLOVAK
value|80
end_define

begin_define
DECL|macro|TWLG_SLOVENIAN
define|#
directive|define
name|TWLG_SLOVENIAN
value|81
end_define

begin_define
DECL|macro|TWLG_SPANISH
define|#
directive|define
name|TWLG_SPANISH
value|TWLG_SPA
end_define

begin_define
DECL|macro|TWLG_SPANISH_MEXICAN
define|#
directive|define
name|TWLG_SPANISH_MEXICAN
value|82
end_define

begin_define
DECL|macro|TWLG_SPANISH_MODERN
define|#
directive|define
name|TWLG_SPANISH_MODERN
value|83
end_define

begin_define
DECL|macro|TWLG_SWEDISH
define|#
directive|define
name|TWLG_SWEDISH
value|TWLG_SWE
end_define

begin_define
DECL|macro|TWLG_THAI
define|#
directive|define
name|TWLG_THAI
value|84
end_define

begin_define
DECL|macro|TWLG_TURKISH
define|#
directive|define
name|TWLG_TURKISH
value|85
end_define

begin_define
DECL|macro|TWLG_UKRANIAN
define|#
directive|define
name|TWLG_UKRANIAN
value|86
end_define

begin_comment
comment|/****************************************************************************  * Data Groups                                                              *  ****************************************************************************/
end_comment

begin_comment
comment|/* More Data Groups may be added in the future.  * Possible candidates include text, vector graphics, sound, etc.  * NOTE: Data Group constants must be powers of 2 as they are used  *       as bitflags when Application asks DSM to present a list of DSs.  */
end_comment

begin_define
DECL|macro|DG_CONTROL
define|#
directive|define
name|DG_CONTROL
value|0x0001L
end_define

begin_comment
DECL|macro|DG_CONTROL
comment|/* data pertaining to control       */
end_comment

begin_define
DECL|macro|DG_IMAGE
define|#
directive|define
name|DG_IMAGE
value|0x0002L
end_define

begin_comment
DECL|macro|DG_IMAGE
comment|/* data pertaining to raster images */
end_comment

begin_comment
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|DG_AUDIO
define|#
directive|define
name|DG_AUDIO
value|0x0004L
end_define

begin_comment
DECL|macro|DG_AUDIO
comment|/* data pertaining to audio */
end_comment

begin_comment
comment|/****************************************************************************  * Data Argument Types                                                      *  ****************************************************************************/
end_comment

begin_comment
comment|/*  SDH - 03/23/95 - WATCH                                                  */
end_comment

begin_comment
comment|/*  The thunker requires knowledge about size of data being passed in the   */
end_comment

begin_comment
comment|/*  lpData parameter to DS_Entry (which is not readily available due to     */
end_comment

begin_comment
comment|/*  type LPVOID.  Thus, we key off the DAT_ argument to determine the size. */
end_comment

begin_comment
comment|/*  This has a couple implications:                                         */
end_comment

begin_comment
comment|/*  1) Any additional DAT_ features require modifications to the thunk code */
end_comment

begin_comment
comment|/*     for thunker support.                                                 */
end_comment

begin_comment
comment|/*  2) Any applications which use the custom capabailites are not supported */
end_comment

begin_comment
comment|/*     under thunking since we have no way of knowing what size data (if    */
end_comment

begin_comment
comment|/*     any) is being passed.                                                */
end_comment

begin_define
DECL|macro|DAT_NULL
define|#
directive|define
name|DAT_NULL
value|0x0000
end_define

begin_comment
DECL|macro|DAT_NULL
comment|/* No data or structure. */
end_comment

begin_define
DECL|macro|DAT_CUSTOMBASE
define|#
directive|define
name|DAT_CUSTOMBASE
value|0x8000
end_define

begin_comment
DECL|macro|DAT_CUSTOMBASE
comment|/* Base of custom DATs.  */
end_comment

begin_comment
comment|/* Data Argument Types for the DG_CONTROL Data Group. */
end_comment

begin_define
DECL|macro|DAT_CAPABILITY
define|#
directive|define
name|DAT_CAPABILITY
value|0x0001
end_define

begin_comment
DECL|macro|DAT_CAPABILITY
comment|/* TW_CAPABILITY                        */
end_comment

begin_define
DECL|macro|DAT_EVENT
define|#
directive|define
name|DAT_EVENT
value|0x0002
end_define

begin_comment
DECL|macro|DAT_EVENT
comment|/* TW_EVENT                             */
end_comment

begin_define
DECL|macro|DAT_IDENTITY
define|#
directive|define
name|DAT_IDENTITY
value|0x0003
end_define

begin_comment
DECL|macro|DAT_IDENTITY
comment|/* TW_IDENTITY                          */
end_comment

begin_define
DECL|macro|DAT_PARENT
define|#
directive|define
name|DAT_PARENT
value|0x0004
end_define

begin_comment
DECL|macro|DAT_PARENT
comment|/* TW_HANDLE, application win handle in Windows */
end_comment

begin_define
DECL|macro|DAT_PENDINGXFERS
define|#
directive|define
name|DAT_PENDINGXFERS
value|0x0005
end_define

begin_comment
DECL|macro|DAT_PENDINGXFERS
comment|/* TW_PENDINGXFERS                      */
end_comment

begin_define
DECL|macro|DAT_SETUPMEMXFER
define|#
directive|define
name|DAT_SETUPMEMXFER
value|0x0006
end_define

begin_comment
DECL|macro|DAT_SETUPMEMXFER
comment|/* TW_SETUPMEMXFER                      */
end_comment

begin_define
DECL|macro|DAT_SETUPFILEXFER
define|#
directive|define
name|DAT_SETUPFILEXFER
value|0x0007
end_define

begin_comment
DECL|macro|DAT_SETUPFILEXFER
comment|/* TW_SETUPFILEXFER                     */
end_comment

begin_define
DECL|macro|DAT_STATUS
define|#
directive|define
name|DAT_STATUS
value|0x0008
end_define

begin_comment
DECL|macro|DAT_STATUS
comment|/* TW_STATUS                            */
end_comment

begin_define
DECL|macro|DAT_USERINTERFACE
define|#
directive|define
name|DAT_USERINTERFACE
value|0x0009
end_define

begin_comment
DECL|macro|DAT_USERINTERFACE
comment|/* TW_USERINTERFACE                     */
end_comment

begin_define
DECL|macro|DAT_XFERGROUP
define|#
directive|define
name|DAT_XFERGROUP
value|0x000a
end_define

begin_comment
DECL|macro|DAT_XFERGROUP
comment|/* TW_UINT32                            */
end_comment

begin_comment
comment|/*  SDH - 03/21/95 - TWUNK                                         */
end_comment

begin_comment
comment|/*  Additional message required for thunker to request the special */
end_comment

begin_comment
comment|/*  identity information.                                          */
end_comment

begin_define
DECL|macro|DAT_TWUNKIDENTITY
define|#
directive|define
name|DAT_TWUNKIDENTITY
value|0x000b
end_define

begin_comment
DECL|macro|DAT_TWUNKIDENTITY
comment|/* TW_TWUNKIDENTITY                     */
end_comment

begin_define
DECL|macro|DAT_CUSTOMDSDATA
define|#
directive|define
name|DAT_CUSTOMDSDATA
value|0x000c
end_define

begin_comment
DECL|macro|DAT_CUSTOMDSDATA
comment|/* TW_CUSTOMDSDATA.                     */
end_comment

begin_comment
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|DAT_DEVICEEVENT
define|#
directive|define
name|DAT_DEVICEEVENT
value|0x000d
end_define

begin_comment
DECL|macro|DAT_DEVICEEVENT
comment|/* TW_DEVICEEVENT                       */
end_comment

begin_define
DECL|macro|DAT_FILESYSTEM
define|#
directive|define
name|DAT_FILESYSTEM
value|0x000e
end_define

begin_comment
DECL|macro|DAT_FILESYSTEM
comment|/* TW_FILESYSTEM                        */
end_comment

begin_define
DECL|macro|DAT_PASSTHRU
define|#
directive|define
name|DAT_PASSTHRU
value|0x000f
end_define

begin_comment
DECL|macro|DAT_PASSTHRU
comment|/* TW_PASSTHRU                          */
end_comment

begin_comment
comment|/* Data Argument Types for the DG_IMAGE Data Group. */
end_comment

begin_define
DECL|macro|DAT_IMAGEINFO
define|#
directive|define
name|DAT_IMAGEINFO
value|0x0101
end_define

begin_comment
DECL|macro|DAT_IMAGEINFO
comment|/* TW_IMAGEINFO                         */
end_comment

begin_define
DECL|macro|DAT_IMAGELAYOUT
define|#
directive|define
name|DAT_IMAGELAYOUT
value|0x0102
end_define

begin_comment
DECL|macro|DAT_IMAGELAYOUT
comment|/* TW_IMAGELAYOUT                       */
end_comment

begin_define
DECL|macro|DAT_IMAGEMEMXFER
define|#
directive|define
name|DAT_IMAGEMEMXFER
value|0x0103
end_define

begin_comment
DECL|macro|DAT_IMAGEMEMXFER
comment|/* TW_IMAGEMEMXFER                      */
end_comment

begin_define
DECL|macro|DAT_IMAGENATIVEXFER
define|#
directive|define
name|DAT_IMAGENATIVEXFER
value|0x0104
end_define

begin_comment
DECL|macro|DAT_IMAGENATIVEXFER
comment|/* TW_UINT32 loword is hDIB, PICHandle  */
end_comment

begin_define
DECL|macro|DAT_IMAGEFILEXFER
define|#
directive|define
name|DAT_IMAGEFILEXFER
value|0x0105
end_define

begin_comment
DECL|macro|DAT_IMAGEFILEXFER
comment|/* Null data                            */
end_comment

begin_define
DECL|macro|DAT_CIECOLOR
define|#
directive|define
name|DAT_CIECOLOR
value|0x0106
end_define

begin_comment
DECL|macro|DAT_CIECOLOR
comment|/* TW_CIECOLOR                          */
end_comment

begin_define
DECL|macro|DAT_GRAYRESPONSE
define|#
directive|define
name|DAT_GRAYRESPONSE
value|0x0107
end_define

begin_comment
DECL|macro|DAT_GRAYRESPONSE
comment|/* TW_GRAYRESPONSE                      */
end_comment

begin_define
DECL|macro|DAT_RGBRESPONSE
define|#
directive|define
name|DAT_RGBRESPONSE
value|0x0108
end_define

begin_comment
DECL|macro|DAT_RGBRESPONSE
comment|/* TW_RGBRESPONSE                       */
end_comment

begin_define
DECL|macro|DAT_JPEGCOMPRESSION
define|#
directive|define
name|DAT_JPEGCOMPRESSION
value|0x0109
end_define

begin_comment
DECL|macro|DAT_JPEGCOMPRESSION
comment|/* TW_JPEGCOMPRESSION                   */
end_comment

begin_define
DECL|macro|DAT_PALETTE8
define|#
directive|define
name|DAT_PALETTE8
value|0x010a
end_define

begin_comment
DECL|macro|DAT_PALETTE8
comment|/* TW_PALETTE8                          */
end_comment

begin_define
DECL|macro|DAT_EXTIMAGEINFO
define|#
directive|define
name|DAT_EXTIMAGEINFO
value|0x010b
end_define

begin_comment
DECL|macro|DAT_EXTIMAGEINFO
comment|/* TW_EXTIMAGEINFO -- for 1.7 Spec.     */
end_comment

begin_comment
comment|/* Added 1.8 */
end_comment

begin_comment
comment|/* Data Argument Types for the DG_AUDIO Data Group. */
end_comment

begin_define
DECL|macro|DAT_AUDIOFILEXFER
define|#
directive|define
name|DAT_AUDIOFILEXFER
value|0x0201
end_define

begin_comment
DECL|macro|DAT_AUDIOFILEXFER
comment|/* Null data                            */
end_comment

begin_define
DECL|macro|DAT_AUDIOINFO
define|#
directive|define
name|DAT_AUDIOINFO
value|0x0202
end_define

begin_comment
DECL|macro|DAT_AUDIOINFO
comment|/* TW_AUDIOINFO                         */
end_comment

begin_define
DECL|macro|DAT_AUDIONATIVEXFER
define|#
directive|define
name|DAT_AUDIONATIVEXFER
value|0x0203
end_define

begin_comment
DECL|macro|DAT_AUDIONATIVEXFER
comment|/* TW_UINT32 handle to WAV, (AIFF Mac)  */
end_comment

begin_comment
comment|/****************************************************************************  * Messages                                                                 *  ****************************************************************************/
end_comment

begin_comment
comment|/* All message constants are unique.  * Messages are grouped according to which DATs they are used with.*/
end_comment

begin_define
DECL|macro|MSG_NULL
define|#
directive|define
name|MSG_NULL
value|0x0000
end_define

begin_comment
DECL|macro|MSG_NULL
comment|/* Used in TW_EVENT structure               */
end_comment

begin_define
DECL|macro|MSG_CUSTOMBASE
define|#
directive|define
name|MSG_CUSTOMBASE
value|0x8000
end_define

begin_comment
DECL|macro|MSG_CUSTOMBASE
comment|/* Base of custom messages                  */
end_comment

begin_comment
comment|/* Generic messages may be used with any of several DATs.                   */
end_comment

begin_define
DECL|macro|MSG_GET
define|#
directive|define
name|MSG_GET
value|0x0001
end_define

begin_comment
DECL|macro|MSG_GET
comment|/* Get one or more values                   */
end_comment

begin_define
DECL|macro|MSG_GETCURRENT
define|#
directive|define
name|MSG_GETCURRENT
value|0x0002
end_define

begin_comment
DECL|macro|MSG_GETCURRENT
comment|/* Get current value                        */
end_comment

begin_define
DECL|macro|MSG_GETDEFAULT
define|#
directive|define
name|MSG_GETDEFAULT
value|0x0003
end_define

begin_comment
DECL|macro|MSG_GETDEFAULT
comment|/* Get default (e.g. power up) value        */
end_comment

begin_define
DECL|macro|MSG_GETFIRST
define|#
directive|define
name|MSG_GETFIRST
value|0x0004
end_define

begin_comment
DECL|macro|MSG_GETFIRST
comment|/* Get first of a series of items, e.g. DSs */
end_comment

begin_define
DECL|macro|MSG_GETNEXT
define|#
directive|define
name|MSG_GETNEXT
value|0x0005
end_define

begin_comment
DECL|macro|MSG_GETNEXT
comment|/* Iterate through a series of items.       */
end_comment

begin_define
DECL|macro|MSG_SET
define|#
directive|define
name|MSG_SET
value|0x0006
end_define

begin_comment
DECL|macro|MSG_SET
comment|/* Set one or more values                   */
end_comment

begin_define
DECL|macro|MSG_RESET
define|#
directive|define
name|MSG_RESET
value|0x0007
end_define

begin_comment
DECL|macro|MSG_RESET
comment|/* Set current value to default value       */
end_comment

begin_define
DECL|macro|MSG_QUERYSUPPORT
define|#
directive|define
name|MSG_QUERYSUPPORT
value|0x0008
end_define

begin_comment
DECL|macro|MSG_QUERYSUPPORT
comment|/* Get supported operations on the cap.     */
end_comment

begin_comment
comment|/* Messages used with DAT_NULL                                              */
end_comment

begin_define
DECL|macro|MSG_XFERREADY
define|#
directive|define
name|MSG_XFERREADY
value|0x0101
end_define

begin_comment
DECL|macro|MSG_XFERREADY
comment|/* The data source has data ready           */
end_comment

begin_define
DECL|macro|MSG_CLOSEDSREQ
define|#
directive|define
name|MSG_CLOSEDSREQ
value|0x0102
end_define

begin_comment
DECL|macro|MSG_CLOSEDSREQ
comment|/* Request for Application. to close DS             */
end_comment

begin_define
DECL|macro|MSG_CLOSEDSOK
define|#
directive|define
name|MSG_CLOSEDSOK
value|0x0103
end_define

begin_comment
DECL|macro|MSG_CLOSEDSOK
comment|/* Tell the Application. to save the state.         */
end_comment

begin_comment
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|MSG_DEVICEEVENT
define|#
directive|define
name|MSG_DEVICEEVENT
value|0X0104
end_define

begin_comment
DECL|macro|MSG_DEVICEEVENT
comment|/* Some event has taken place               */
end_comment

begin_comment
comment|/* Messages used with a pointer to a DAT_STATUS structure                   */
end_comment

begin_define
DECL|macro|MSG_CHECKSTATUS
define|#
directive|define
name|MSG_CHECKSTATUS
value|0x0201
end_define

begin_comment
DECL|macro|MSG_CHECKSTATUS
comment|/* Get status information                   */
end_comment

begin_comment
comment|/* Messages used with a pointer to DAT_PARENT data                          */
end_comment

begin_define
DECL|macro|MSG_OPENDSM
define|#
directive|define
name|MSG_OPENDSM
value|0x0301
end_define

begin_comment
DECL|macro|MSG_OPENDSM
comment|/* Open the DSM                             */
end_comment

begin_define
DECL|macro|MSG_CLOSEDSM
define|#
directive|define
name|MSG_CLOSEDSM
value|0x0302
end_define

begin_comment
DECL|macro|MSG_CLOSEDSM
comment|/* Close the DSM                            */
end_comment

begin_comment
comment|/* Messages used with a pointer to a DAT_IDENTITY structure                 */
end_comment

begin_define
DECL|macro|MSG_OPENDS
define|#
directive|define
name|MSG_OPENDS
value|0x0401
end_define

begin_comment
DECL|macro|MSG_OPENDS
comment|/* Open a data source                       */
end_comment

begin_define
DECL|macro|MSG_CLOSEDS
define|#
directive|define
name|MSG_CLOSEDS
value|0x0402
end_define

begin_comment
DECL|macro|MSG_CLOSEDS
comment|/* Close a data source                      */
end_comment

begin_define
DECL|macro|MSG_USERSELECT
define|#
directive|define
name|MSG_USERSELECT
value|0x0403
end_define

begin_comment
DECL|macro|MSG_USERSELECT
comment|/* Put up a dialog of all DS                */
end_comment

begin_comment
comment|/* Messages used with a pointer to a DAT_USERINTERFACE structure            */
end_comment

begin_define
DECL|macro|MSG_DISABLEDS
define|#
directive|define
name|MSG_DISABLEDS
value|0x0501
end_define

begin_comment
DECL|macro|MSG_DISABLEDS
comment|/* Disable data transfer in the DS          */
end_comment

begin_define
DECL|macro|MSG_ENABLEDS
define|#
directive|define
name|MSG_ENABLEDS
value|0x0502
end_define

begin_comment
DECL|macro|MSG_ENABLEDS
comment|/* Enable data transfer in the DS           */
end_comment

begin_define
DECL|macro|MSG_ENABLEDSUIONLY
define|#
directive|define
name|MSG_ENABLEDSUIONLY
value|0x0503
end_define

begin_comment
DECL|macro|MSG_ENABLEDSUIONLY
comment|/* Enable for saving DS state only.     */
end_comment

begin_comment
comment|/* Messages used with a pointer to a DAT_EVENT structure                    */
end_comment

begin_define
DECL|macro|MSG_PROCESSEVENT
define|#
directive|define
name|MSG_PROCESSEVENT
value|0x0601
end_define

begin_comment
comment|/* Messages used with a pointer to a DAT_PENDINGXFERS structure             */
end_comment

begin_define
DECL|macro|MSG_ENDXFER
define|#
directive|define
name|MSG_ENDXFER
value|0x0701
end_define

begin_comment
comment|/* Added 1.8 */
end_comment

begin_comment
comment|/* Messages used with a pointer to a DAT_FILESYSTEM structure               */
end_comment

begin_define
DECL|macro|MSG_CHANGEDIRECTORY
define|#
directive|define
name|MSG_CHANGEDIRECTORY
value|0x0801
end_define

begin_define
DECL|macro|MSG_CREATEDIRECTORY
define|#
directive|define
name|MSG_CREATEDIRECTORY
value|0x0802
end_define

begin_define
DECL|macro|MSG_DELETE
define|#
directive|define
name|MSG_DELETE
value|0x0803
end_define

begin_define
DECL|macro|MSG_FORMATMEDIA
define|#
directive|define
name|MSG_FORMATMEDIA
value|0x0804
end_define

begin_define
DECL|macro|MSG_GETCLOSE
define|#
directive|define
name|MSG_GETCLOSE
value|0x0805
end_define

begin_define
DECL|macro|MSG_GETFIRSTFILE
define|#
directive|define
name|MSG_GETFIRSTFILE
value|0x0806
end_define

begin_define
DECL|macro|MSG_GETINFO
define|#
directive|define
name|MSG_GETINFO
value|0x0807
end_define

begin_define
DECL|macro|MSG_GETNEXTFILE
define|#
directive|define
name|MSG_GETNEXTFILE
value|0x0808
end_define

begin_define
DECL|macro|MSG_RENAME
define|#
directive|define
name|MSG_RENAME
value|0x0809
end_define

begin_comment
comment|/* Messages used with a pointer to a DAT_PASSTHRU structure                 */
end_comment

begin_define
DECL|macro|MSG_PASSTHRU
define|#
directive|define
name|MSG_PASSTHRU
value|0x0901
end_define

begin_comment
comment|/****************************************************************************  * Capabilities                                                             *  ****************************************************************************/
end_comment

begin_define
DECL|macro|CAP_CUSTOMBASE
define|#
directive|define
name|CAP_CUSTOMBASE
value|0x8000
end_define

begin_comment
DECL|macro|CAP_CUSTOMBASE
comment|/* Base of custom capabilities */
end_comment

begin_comment
comment|/* all data sources are REQUIRED to support these caps */
end_comment

begin_define
DECL|macro|CAP_XFERCOUNT
define|#
directive|define
name|CAP_XFERCOUNT
value|0x0001
end_define

begin_comment
comment|/* image data sources are REQUIRED to support these caps */
end_comment

begin_define
DECL|macro|ICAP_COMPRESSION
define|#
directive|define
name|ICAP_COMPRESSION
value|0x0100
end_define

begin_define
DECL|macro|ICAP_PIXELTYPE
define|#
directive|define
name|ICAP_PIXELTYPE
value|0x0101
end_define

begin_define
DECL|macro|ICAP_UNITS
define|#
directive|define
name|ICAP_UNITS
value|0x0102
end_define

begin_comment
DECL|macro|ICAP_UNITS
comment|/* default is TWUN_INCHES */
end_comment

begin_define
DECL|macro|ICAP_XFERMECH
define|#
directive|define
name|ICAP_XFERMECH
value|0x0103
end_define

begin_comment
comment|/* all data sources MAY support these caps */
end_comment

begin_define
DECL|macro|CAP_AUTHOR
define|#
directive|define
name|CAP_AUTHOR
value|0x1000
end_define

begin_define
DECL|macro|CAP_CAPTION
define|#
directive|define
name|CAP_CAPTION
value|0x1001
end_define

begin_define
DECL|macro|CAP_FEEDERENABLED
define|#
directive|define
name|CAP_FEEDERENABLED
value|0x1002
end_define

begin_define
DECL|macro|CAP_FEEDERLOADED
define|#
directive|define
name|CAP_FEEDERLOADED
value|0x1003
end_define

begin_define
DECL|macro|CAP_TIMEDATE
define|#
directive|define
name|CAP_TIMEDATE
value|0x1004
end_define

begin_define
DECL|macro|CAP_SUPPORTEDCAPS
define|#
directive|define
name|CAP_SUPPORTEDCAPS
value|0x1005
end_define

begin_define
DECL|macro|CAP_EXTENDEDCAPS
define|#
directive|define
name|CAP_EXTENDEDCAPS
value|0x1006
end_define

begin_define
DECL|macro|CAP_AUTOFEED
define|#
directive|define
name|CAP_AUTOFEED
value|0x1007
end_define

begin_define
DECL|macro|CAP_CLEARPAGE
define|#
directive|define
name|CAP_CLEARPAGE
value|0x1008
end_define

begin_define
DECL|macro|CAP_FEEDPAGE
define|#
directive|define
name|CAP_FEEDPAGE
value|0x1009
end_define

begin_define
DECL|macro|CAP_REWINDPAGE
define|#
directive|define
name|CAP_REWINDPAGE
value|0x100a
end_define

begin_define
DECL|macro|CAP_INDICATORS
define|#
directive|define
name|CAP_INDICATORS
value|0x100b
end_define

begin_comment
DECL|macro|CAP_INDICATORS
comment|/* Added 1.1 */
end_comment

begin_define
DECL|macro|CAP_SUPPORTEDCAPSEXT
define|#
directive|define
name|CAP_SUPPORTEDCAPSEXT
value|0x100c
end_define

begin_comment
DECL|macro|CAP_SUPPORTEDCAPSEXT
comment|/* Added 1.6 */
end_comment

begin_define
DECL|macro|CAP_PAPERDETECTABLE
define|#
directive|define
name|CAP_PAPERDETECTABLE
value|0x100d
end_define

begin_comment
DECL|macro|CAP_PAPERDETECTABLE
comment|/* Added 1.6 */
end_comment

begin_define
DECL|macro|CAP_UICONTROLLABLE
define|#
directive|define
name|CAP_UICONTROLLABLE
value|0x100e
end_define

begin_comment
DECL|macro|CAP_UICONTROLLABLE
comment|/* Added 1.6 */
end_comment

begin_define
DECL|macro|CAP_DEVICEONLINE
define|#
directive|define
name|CAP_DEVICEONLINE
value|0x100f
end_define

begin_comment
DECL|macro|CAP_DEVICEONLINE
comment|/* Added 1.6 */
end_comment

begin_define
DECL|macro|CAP_AUTOSCAN
define|#
directive|define
name|CAP_AUTOSCAN
value|0x1010
end_define

begin_comment
DECL|macro|CAP_AUTOSCAN
comment|/* Added 1.6 */
end_comment

begin_define
DECL|macro|CAP_THUMBNAILSENABLED
define|#
directive|define
name|CAP_THUMBNAILSENABLED
value|0x1011
end_define

begin_comment
DECL|macro|CAP_THUMBNAILSENABLED
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|CAP_DUPLEX
define|#
directive|define
name|CAP_DUPLEX
value|0x1012
end_define

begin_comment
DECL|macro|CAP_DUPLEX
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|CAP_DUPLEXENABLED
define|#
directive|define
name|CAP_DUPLEXENABLED
value|0x1013
end_define

begin_comment
DECL|macro|CAP_DUPLEXENABLED
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|CAP_ENABLEDSUIONLY
define|#
directive|define
name|CAP_ENABLEDSUIONLY
value|0x1014
end_define

begin_comment
DECL|macro|CAP_ENABLEDSUIONLY
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|CAP_CUSTOMDSDATA
define|#
directive|define
name|CAP_CUSTOMDSDATA
value|0x1015
end_define

begin_comment
DECL|macro|CAP_CUSTOMDSDATA
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|CAP_ENDORSER
define|#
directive|define
name|CAP_ENDORSER
value|0x1016
end_define

begin_comment
DECL|macro|CAP_ENDORSER
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|CAP_JOBCONTROL
define|#
directive|define
name|CAP_JOBCONTROL
value|0x1017
end_define

begin_comment
DECL|macro|CAP_JOBCONTROL
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|CAP_ALARMS
define|#
directive|define
name|CAP_ALARMS
value|0x1018
end_define

begin_comment
DECL|macro|CAP_ALARMS
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_ALARMVOLUME
define|#
directive|define
name|CAP_ALARMVOLUME
value|0x1019
end_define

begin_comment
DECL|macro|CAP_ALARMVOLUME
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_AUTOMATICCAPTURE
define|#
directive|define
name|CAP_AUTOMATICCAPTURE
value|0x101a
end_define

begin_comment
DECL|macro|CAP_AUTOMATICCAPTURE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_TIMEBEFOREFIRSTCAPTURE
define|#
directive|define
name|CAP_TIMEBEFOREFIRSTCAPTURE
value|0x101b
end_define

begin_comment
DECL|macro|CAP_TIMEBEFOREFIRSTCAPTURE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_TIMEBETWEENCAPTURES
define|#
directive|define
name|CAP_TIMEBETWEENCAPTURES
value|0x101c
end_define

begin_comment
DECL|macro|CAP_TIMEBETWEENCAPTURES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_CLEARBUFFERS
define|#
directive|define
name|CAP_CLEARBUFFERS
value|0x101d
end_define

begin_comment
DECL|macro|CAP_CLEARBUFFERS
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_MAXBATCHBUFFERS
define|#
directive|define
name|CAP_MAXBATCHBUFFERS
value|0x101e
end_define

begin_comment
DECL|macro|CAP_MAXBATCHBUFFERS
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_DEVICETIMEDATE
define|#
directive|define
name|CAP_DEVICETIMEDATE
value|0x101f
end_define

begin_comment
DECL|macro|CAP_DEVICETIMEDATE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_POWERSUPPLY
define|#
directive|define
name|CAP_POWERSUPPLY
value|0x1020
end_define

begin_comment
DECL|macro|CAP_POWERSUPPLY
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_CAMERAPREVIEWUI
define|#
directive|define
name|CAP_CAMERAPREVIEWUI
value|0x1021
end_define

begin_comment
DECL|macro|CAP_CAMERAPREVIEWUI
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_DEVICEEVENT
define|#
directive|define
name|CAP_DEVICEEVENT
value|0x1022
end_define

begin_comment
DECL|macro|CAP_DEVICEEVENT
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PAGEMULTIPLEACQUIRE
define|#
directive|define
name|CAP_PAGEMULTIPLEACQUIRE
value|0x1023
end_define

begin_comment
DECL|macro|CAP_PAGEMULTIPLEACQUIRE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_SERIALNUMBER
define|#
directive|define
name|CAP_SERIALNUMBER
value|0x1024
end_define

begin_comment
DECL|macro|CAP_SERIALNUMBER
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_FILESYSTEM
define|#
directive|define
name|CAP_FILESYSTEM
value|0x1025
end_define

begin_comment
DECL|macro|CAP_FILESYSTEM
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PRINTER
define|#
directive|define
name|CAP_PRINTER
value|0x1026
end_define

begin_comment
DECL|macro|CAP_PRINTER
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PRINTERENABLED
define|#
directive|define
name|CAP_PRINTERENABLED
value|0x1027
end_define

begin_comment
DECL|macro|CAP_PRINTERENABLED
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PRINTERINDEX
define|#
directive|define
name|CAP_PRINTERINDEX
value|0x1028
end_define

begin_comment
DECL|macro|CAP_PRINTERINDEX
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PRINTERMODE
define|#
directive|define
name|CAP_PRINTERMODE
value|0x1029
end_define

begin_comment
DECL|macro|CAP_PRINTERMODE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PRINTERSTRING
define|#
directive|define
name|CAP_PRINTERSTRING
value|0x102a
end_define

begin_comment
DECL|macro|CAP_PRINTERSTRING
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PRINTERSUFFIX
define|#
directive|define
name|CAP_PRINTERSUFFIX
value|0x102b
end_define

begin_comment
DECL|macro|CAP_PRINTERSUFFIX
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_LANGUAGE
define|#
directive|define
name|CAP_LANGUAGE
value|0x102c
end_define

begin_comment
DECL|macro|CAP_LANGUAGE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_FEEDERALIGNMENT
define|#
directive|define
name|CAP_FEEDERALIGNMENT
value|0x102d
end_define

begin_comment
DECL|macro|CAP_FEEDERALIGNMENT
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_FEEDERORDER
define|#
directive|define
name|CAP_FEEDERORDER
value|0x102e
end_define

begin_comment
DECL|macro|CAP_FEEDERORDER
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PAPERBINDING
define|#
directive|define
name|CAP_PAPERBINDING
value|0x102f
end_define

begin_comment
DECL|macro|CAP_PAPERBINDING
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_REACQUIREALLOWED
define|#
directive|define
name|CAP_REACQUIREALLOWED
value|0x1030
end_define

begin_comment
DECL|macro|CAP_REACQUIREALLOWED
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_PASSTHRU
define|#
directive|define
name|CAP_PASSTHRU
value|0x1031
end_define

begin_comment
DECL|macro|CAP_PASSTHRU
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_BATTERYMINUTES
define|#
directive|define
name|CAP_BATTERYMINUTES
value|0x1032
end_define

begin_comment
DECL|macro|CAP_BATTERYMINUTES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_BATTERYPERCENTAGE
define|#
directive|define
name|CAP_BATTERYPERCENTAGE
value|0x1033
end_define

begin_comment
DECL|macro|CAP_BATTERYPERCENTAGE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|CAP_POWERDOWNTIME
define|#
directive|define
name|CAP_POWERDOWNTIME
value|0x1034
end_define

begin_comment
DECL|macro|CAP_POWERDOWNTIME
comment|/* Added 1.8 */
end_comment

begin_comment
comment|/* image data sources MAY support these caps */
end_comment

begin_define
DECL|macro|ICAP_AUTOBRIGHT
define|#
directive|define
name|ICAP_AUTOBRIGHT
value|0x1100
end_define

begin_define
DECL|macro|ICAP_BRIGHTNESS
define|#
directive|define
name|ICAP_BRIGHTNESS
value|0x1101
end_define

begin_define
DECL|macro|ICAP_CONTRAST
define|#
directive|define
name|ICAP_CONTRAST
value|0x1103
end_define

begin_define
DECL|macro|ICAP_CUSTHALFTONE
define|#
directive|define
name|ICAP_CUSTHALFTONE
value|0x1104
end_define

begin_define
DECL|macro|ICAP_EXPOSURETIME
define|#
directive|define
name|ICAP_EXPOSURETIME
value|0x1105
end_define

begin_define
DECL|macro|ICAP_FILTER
define|#
directive|define
name|ICAP_FILTER
value|0x1106
end_define

begin_define
DECL|macro|ICAP_FLASHUSED
define|#
directive|define
name|ICAP_FLASHUSED
value|0x1107
end_define

begin_define
DECL|macro|ICAP_GAMMA
define|#
directive|define
name|ICAP_GAMMA
value|0x1108
end_define

begin_define
DECL|macro|ICAP_HALFTONES
define|#
directive|define
name|ICAP_HALFTONES
value|0x1109
end_define

begin_define
DECL|macro|ICAP_HIGHLIGHT
define|#
directive|define
name|ICAP_HIGHLIGHT
value|0x110a
end_define

begin_define
DECL|macro|ICAP_IMAGEFILEFORMAT
define|#
directive|define
name|ICAP_IMAGEFILEFORMAT
value|0x110c
end_define

begin_define
DECL|macro|ICAP_LAMPSTATE
define|#
directive|define
name|ICAP_LAMPSTATE
value|0x110d
end_define

begin_define
DECL|macro|ICAP_LIGHTSOURCE
define|#
directive|define
name|ICAP_LIGHTSOURCE
value|0x110e
end_define

begin_define
DECL|macro|ICAP_ORIENTATION
define|#
directive|define
name|ICAP_ORIENTATION
value|0x1110
end_define

begin_define
DECL|macro|ICAP_PHYSICALWIDTH
define|#
directive|define
name|ICAP_PHYSICALWIDTH
value|0x1111
end_define

begin_define
DECL|macro|ICAP_PHYSICALHEIGHT
define|#
directive|define
name|ICAP_PHYSICALHEIGHT
value|0x1112
end_define

begin_define
DECL|macro|ICAP_SHADOW
define|#
directive|define
name|ICAP_SHADOW
value|0x1113
end_define

begin_define
DECL|macro|ICAP_FRAMES
define|#
directive|define
name|ICAP_FRAMES
value|0x1114
end_define

begin_define
DECL|macro|ICAP_XNATIVERESOLUTION
define|#
directive|define
name|ICAP_XNATIVERESOLUTION
value|0x1116
end_define

begin_define
DECL|macro|ICAP_YNATIVERESOLUTION
define|#
directive|define
name|ICAP_YNATIVERESOLUTION
value|0x1117
end_define

begin_define
DECL|macro|ICAP_XRESOLUTION
define|#
directive|define
name|ICAP_XRESOLUTION
value|0x1118
end_define

begin_define
DECL|macro|ICAP_YRESOLUTION
define|#
directive|define
name|ICAP_YRESOLUTION
value|0x1119
end_define

begin_define
DECL|macro|ICAP_MAXFRAMES
define|#
directive|define
name|ICAP_MAXFRAMES
value|0x111a
end_define

begin_define
DECL|macro|ICAP_TILES
define|#
directive|define
name|ICAP_TILES
value|0x111b
end_define

begin_define
DECL|macro|ICAP_BITORDER
define|#
directive|define
name|ICAP_BITORDER
value|0x111c
end_define

begin_define
DECL|macro|ICAP_CCITTKFACTOR
define|#
directive|define
name|ICAP_CCITTKFACTOR
value|0x111d
end_define

begin_define
DECL|macro|ICAP_LIGHTPATH
define|#
directive|define
name|ICAP_LIGHTPATH
value|0x111e
end_define

begin_define
DECL|macro|ICAP_PIXELFLAVOR
define|#
directive|define
name|ICAP_PIXELFLAVOR
value|0x111f
end_define

begin_define
DECL|macro|ICAP_PLANARCHUNKY
define|#
directive|define
name|ICAP_PLANARCHUNKY
value|0x1120
end_define

begin_define
DECL|macro|ICAP_ROTATION
define|#
directive|define
name|ICAP_ROTATION
value|0x1121
end_define

begin_define
DECL|macro|ICAP_SUPPORTEDSIZES
define|#
directive|define
name|ICAP_SUPPORTEDSIZES
value|0x1122
end_define

begin_define
DECL|macro|ICAP_THRESHOLD
define|#
directive|define
name|ICAP_THRESHOLD
value|0x1123
end_define

begin_define
DECL|macro|ICAP_XSCALING
define|#
directive|define
name|ICAP_XSCALING
value|0x1124
end_define

begin_define
DECL|macro|ICAP_YSCALING
define|#
directive|define
name|ICAP_YSCALING
value|0x1125
end_define

begin_define
DECL|macro|ICAP_BITORDERCODES
define|#
directive|define
name|ICAP_BITORDERCODES
value|0x1126
end_define

begin_define
DECL|macro|ICAP_PIXELFLAVORCODES
define|#
directive|define
name|ICAP_PIXELFLAVORCODES
value|0x1127
end_define

begin_define
DECL|macro|ICAP_JPEGPIXELTYPE
define|#
directive|define
name|ICAP_JPEGPIXELTYPE
value|0x1128
end_define

begin_define
DECL|macro|ICAP_TIMEFILL
define|#
directive|define
name|ICAP_TIMEFILL
value|0x112a
end_define

begin_define
DECL|macro|ICAP_BITDEPTH
define|#
directive|define
name|ICAP_BITDEPTH
value|0x112b
end_define

begin_define
DECL|macro|ICAP_BITDEPTHREDUCTION
define|#
directive|define
name|ICAP_BITDEPTHREDUCTION
value|0x112c
end_define

begin_comment
DECL|macro|ICAP_BITDEPTHREDUCTION
comment|/* Added 1.5 */
end_comment

begin_define
DECL|macro|ICAP_UNDEFINEDIMAGESIZE
define|#
directive|define
name|ICAP_UNDEFINEDIMAGESIZE
value|0x112d
end_define

begin_comment
DECL|macro|ICAP_UNDEFINEDIMAGESIZE
comment|/* Added 1.6 */
end_comment

begin_define
DECL|macro|ICAP_IMAGEDATASET
define|#
directive|define
name|ICAP_IMAGEDATASET
value|0x112e
end_define

begin_comment
DECL|macro|ICAP_IMAGEDATASET
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|ICAP_EXTIMAGEINFO
define|#
directive|define
name|ICAP_EXTIMAGEINFO
value|0x112f
end_define

begin_comment
DECL|macro|ICAP_EXTIMAGEINFO
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|ICAP_MINIMUMHEIGHT
define|#
directive|define
name|ICAP_MINIMUMHEIGHT
value|0x1130
end_define

begin_comment
DECL|macro|ICAP_MINIMUMHEIGHT
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|ICAP_MINIMUMWIDTH
define|#
directive|define
name|ICAP_MINIMUMWIDTH
value|0x1131
end_define

begin_comment
DECL|macro|ICAP_MINIMUMWIDTH
comment|/* Added 1.7 */
end_comment

begin_define
DECL|macro|ICAP_AUTOBORDERDETECTION
define|#
directive|define
name|ICAP_AUTOBORDERDETECTION
value|0x1132
end_define

begin_comment
DECL|macro|ICAP_AUTOBORDERDETECTION
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_AUTODESKEW
define|#
directive|define
name|ICAP_AUTODESKEW
value|0x1133
end_define

begin_comment
DECL|macro|ICAP_AUTODESKEW
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_AUTODISCARDBLANKPAGES
define|#
directive|define
name|ICAP_AUTODISCARDBLANKPAGES
value|0x1134
end_define

begin_comment
DECL|macro|ICAP_AUTODISCARDBLANKPAGES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_AUTOROTATE
define|#
directive|define
name|ICAP_AUTOROTATE
value|0x1135
end_define

begin_comment
DECL|macro|ICAP_AUTOROTATE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_FLIPROTATION
define|#
directive|define
name|ICAP_FLIPROTATION
value|0x1136
end_define

begin_comment
DECL|macro|ICAP_FLIPROTATION
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_BARCODEDETECTIONENABLED
define|#
directive|define
name|ICAP_BARCODEDETECTIONENABLED
value|0x1137
end_define

begin_comment
DECL|macro|ICAP_BARCODEDETECTIONENABLED
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_SUPPORTEDBARCODETYPES
define|#
directive|define
name|ICAP_SUPPORTEDBARCODETYPES
value|0x1138
end_define

begin_comment
DECL|macro|ICAP_SUPPORTEDBARCODETYPES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_BARCODEMAXSEARCHPRIORITIES
define|#
directive|define
name|ICAP_BARCODEMAXSEARCHPRIORITIES
value|0x1139
end_define

begin_comment
DECL|macro|ICAP_BARCODEMAXSEARCHPRIORITIES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_BARCODESEARCHPRIORITIES
define|#
directive|define
name|ICAP_BARCODESEARCHPRIORITIES
value|0x113a
end_define

begin_comment
DECL|macro|ICAP_BARCODESEARCHPRIORITIES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_BARCODESEARCHMODE
define|#
directive|define
name|ICAP_BARCODESEARCHMODE
value|0x113b
end_define

begin_comment
DECL|macro|ICAP_BARCODESEARCHMODE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_BARCODEMAXRETRIES
define|#
directive|define
name|ICAP_BARCODEMAXRETRIES
value|0x113c
end_define

begin_comment
DECL|macro|ICAP_BARCODEMAXRETRIES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_BARCODETIMEOUT
define|#
directive|define
name|ICAP_BARCODETIMEOUT
value|0x113d
end_define

begin_comment
DECL|macro|ICAP_BARCODETIMEOUT
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_ZOOMFACTOR
define|#
directive|define
name|ICAP_ZOOMFACTOR
value|0x113e
end_define

begin_comment
DECL|macro|ICAP_ZOOMFACTOR
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_PATCHCODEDETECTIONENABLED
define|#
directive|define
name|ICAP_PATCHCODEDETECTIONENABLED
value|0x113f
end_define

begin_comment
DECL|macro|ICAP_PATCHCODEDETECTIONENABLED
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_SUPPORTEDPATCHCODETYPES
define|#
directive|define
name|ICAP_SUPPORTEDPATCHCODETYPES
value|0x1140
end_define

begin_comment
DECL|macro|ICAP_SUPPORTEDPATCHCODETYPES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_PATCHCODEMAXSEARCHPRIORITIES
define|#
directive|define
name|ICAP_PATCHCODEMAXSEARCHPRIORITIES
value|0x1141
end_define

begin_comment
DECL|macro|ICAP_PATCHCODEMAXSEARCHPRIORITIES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_PATCHCODESEARCHPRIORITIES
define|#
directive|define
name|ICAP_PATCHCODESEARCHPRIORITIES
value|0x1142
end_define

begin_comment
DECL|macro|ICAP_PATCHCODESEARCHPRIORITIES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_PATCHCODESEARCHMODE
define|#
directive|define
name|ICAP_PATCHCODESEARCHMODE
value|0x1143
end_define

begin_comment
DECL|macro|ICAP_PATCHCODESEARCHMODE
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_PATCHCODEMAXRETRIES
define|#
directive|define
name|ICAP_PATCHCODEMAXRETRIES
value|0x1144
end_define

begin_comment
DECL|macro|ICAP_PATCHCODEMAXRETRIES
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_PATCHCODETIMEOUT
define|#
directive|define
name|ICAP_PATCHCODETIMEOUT
value|0x1145
end_define

begin_comment
DECL|macro|ICAP_PATCHCODETIMEOUT
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_FLASHUSED2
define|#
directive|define
name|ICAP_FLASHUSED2
value|0x1146
end_define

begin_comment
DECL|macro|ICAP_FLASHUSED2
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_IMAGEFILTER
define|#
directive|define
name|ICAP_IMAGEFILTER
value|0x1147
end_define

begin_comment
DECL|macro|ICAP_IMAGEFILTER
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_NOISEFILTER
define|#
directive|define
name|ICAP_NOISEFILTER
value|0x1148
end_define

begin_comment
DECL|macro|ICAP_NOISEFILTER
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_OVERSCAN
define|#
directive|define
name|ICAP_OVERSCAN
value|0x1149
end_define

begin_comment
DECL|macro|ICAP_OVERSCAN
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_AUTOMATICBORDERDETECTION
define|#
directive|define
name|ICAP_AUTOMATICBORDERDETECTION
value|0x1150
end_define

begin_comment
DECL|macro|ICAP_AUTOMATICBORDERDETECTION
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_AUTOMATICDESKEW
define|#
directive|define
name|ICAP_AUTOMATICDESKEW
value|0x1151
end_define

begin_comment
DECL|macro|ICAP_AUTOMATICDESKEW
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ICAP_AUTOMATICROTATE
define|#
directive|define
name|ICAP_AUTOMATICROTATE
value|0x1152
end_define

begin_comment
DECL|macro|ICAP_AUTOMATICROTATE
comment|/* Added 1.8 */
end_comment

begin_comment
comment|/* image data sources MAY support these audio caps */
end_comment

begin_define
DECL|macro|ACAP_AUDIOFILEFORMAT
define|#
directive|define
name|ACAP_AUDIOFILEFORMAT
value|0x1201
end_define

begin_comment
DECL|macro|ACAP_AUDIOFILEFORMAT
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|ACAP_XFERMECH
define|#
directive|define
name|ACAP_XFERMECH
value|0x1202
end_define

begin_comment
DECL|macro|ACAP_XFERMECH
comment|/* Added 1.8 */
end_comment

begin_comment
comment|/* ----------------------------------------------------------------------- *\    Version 1.7:      Following is Extended Image Info Attributes.   July 1997            KHL                 \* ----------------------------------------------------------------------- */
end_comment

begin_define
DECL|macro|TWEI_BARCODEX
define|#
directive|define
name|TWEI_BARCODEX
value|0x1200
end_define

begin_define
DECL|macro|TWEI_BARCODEY
define|#
directive|define
name|TWEI_BARCODEY
value|0x1201
end_define

begin_define
DECL|macro|TWEI_BARCODETEXT
define|#
directive|define
name|TWEI_BARCODETEXT
value|0x1202
end_define

begin_define
DECL|macro|TWEI_BARCODETYPE
define|#
directive|define
name|TWEI_BARCODETYPE
value|0x1203
end_define

begin_define
DECL|macro|TWEI_DESHADETOP
define|#
directive|define
name|TWEI_DESHADETOP
value|0x1204
end_define

begin_define
DECL|macro|TWEI_DESHADELEFT
define|#
directive|define
name|TWEI_DESHADELEFT
value|0x1205
end_define

begin_define
DECL|macro|TWEI_DESHADEHEIGHT
define|#
directive|define
name|TWEI_DESHADEHEIGHT
value|0x1206
end_define

begin_define
DECL|macro|TWEI_DESHADEWIDTH
define|#
directive|define
name|TWEI_DESHADEWIDTH
value|0x1207
end_define

begin_define
DECL|macro|TWEI_DESHADESIZE
define|#
directive|define
name|TWEI_DESHADESIZE
value|0x1208
end_define

begin_define
DECL|macro|TWEI_SPECKLESREMOVED
define|#
directive|define
name|TWEI_SPECKLESREMOVED
value|0x1209
end_define

begin_define
DECL|macro|TWEI_HORZLINEXCOORD
define|#
directive|define
name|TWEI_HORZLINEXCOORD
value|0x120A
end_define

begin_define
DECL|macro|TWEI_HORZLINEYCOORD
define|#
directive|define
name|TWEI_HORZLINEYCOORD
value|0x120B
end_define

begin_define
DECL|macro|TWEI_HORZLINELENGTH
define|#
directive|define
name|TWEI_HORZLINELENGTH
value|0x120C
end_define

begin_define
DECL|macro|TWEI_HORZLINETHICKNESS
define|#
directive|define
name|TWEI_HORZLINETHICKNESS
value|0x120D
end_define

begin_define
DECL|macro|TWEI_VERTLINEXCOORD
define|#
directive|define
name|TWEI_VERTLINEXCOORD
value|0x120E
end_define

begin_define
DECL|macro|TWEI_VERTLINEYCOORD
define|#
directive|define
name|TWEI_VERTLINEYCOORD
value|0x120F
end_define

begin_define
DECL|macro|TWEI_VERTLINELENGTH
define|#
directive|define
name|TWEI_VERTLINELENGTH
value|0x1210
end_define

begin_define
DECL|macro|TWEI_VERTLINETHICKNESS
define|#
directive|define
name|TWEI_VERTLINETHICKNESS
value|0x1211
end_define

begin_define
DECL|macro|TWEI_PATCHCODE
define|#
directive|define
name|TWEI_PATCHCODE
value|0x1212
end_define

begin_define
DECL|macro|TWEI_ENDORSEDTEXT
define|#
directive|define
name|TWEI_ENDORSEDTEXT
value|0x1213
end_define

begin_define
DECL|macro|TWEI_FORMCONFIDENCE
define|#
directive|define
name|TWEI_FORMCONFIDENCE
value|0x1214
end_define

begin_define
DECL|macro|TWEI_FORMTEMPLATEMATCH
define|#
directive|define
name|TWEI_FORMTEMPLATEMATCH
value|0x1215
end_define

begin_define
DECL|macro|TWEI_FORMTEMPLATEPAGEMATCH
define|#
directive|define
name|TWEI_FORMTEMPLATEPAGEMATCH
value|0x1216
end_define

begin_define
DECL|macro|TWEI_FORMHORZDOCOFFSET
define|#
directive|define
name|TWEI_FORMHORZDOCOFFSET
value|0x1217
end_define

begin_define
DECL|macro|TWEI_FORMVERTDOCOFFSET
define|#
directive|define
name|TWEI_FORMVERTDOCOFFSET
value|0x1218
end_define

begin_define
DECL|macro|TWEI_BARCODECOUNT
define|#
directive|define
name|TWEI_BARCODECOUNT
value|0x1219
end_define

begin_define
DECL|macro|TWEI_BARCODECONFIDENCE
define|#
directive|define
name|TWEI_BARCODECONFIDENCE
value|0x121A
end_define

begin_define
DECL|macro|TWEI_BARCODEROTATION
define|#
directive|define
name|TWEI_BARCODEROTATION
value|0x121B
end_define

begin_define
DECL|macro|TWEI_BARCODETEXTLENGTH
define|#
directive|define
name|TWEI_BARCODETEXTLENGTH
value|0x121C
end_define

begin_define
DECL|macro|TWEI_DESHADECOUNT
define|#
directive|define
name|TWEI_DESHADECOUNT
value|0x121D
end_define

begin_define
DECL|macro|TWEI_DESHADEBLACKCOUNTOLD
define|#
directive|define
name|TWEI_DESHADEBLACKCOUNTOLD
value|0x121E
end_define

begin_define
DECL|macro|TWEI_DESHADEBLACKCOUNTNEW
define|#
directive|define
name|TWEI_DESHADEBLACKCOUNTNEW
value|0x121F
end_define

begin_define
DECL|macro|TWEI_DESHADEBLACKRLMIN
define|#
directive|define
name|TWEI_DESHADEBLACKRLMIN
value|0x1220
end_define

begin_define
DECL|macro|TWEI_DESHADEBLACKRLMAX
define|#
directive|define
name|TWEI_DESHADEBLACKRLMAX
value|0x1221
end_define

begin_define
DECL|macro|TWEI_DESHADEWHITECOUNTOLD
define|#
directive|define
name|TWEI_DESHADEWHITECOUNTOLD
value|0x1222
end_define

begin_define
DECL|macro|TWEI_DESHADEWHITECOUNTNEW
define|#
directive|define
name|TWEI_DESHADEWHITECOUNTNEW
value|0x1223
end_define

begin_define
DECL|macro|TWEI_DESHADEWHITERLMIN
define|#
directive|define
name|TWEI_DESHADEWHITERLMIN
value|0x1224
end_define

begin_define
DECL|macro|TWEI_DESHADEWHITERLAVE
define|#
directive|define
name|TWEI_DESHADEWHITERLAVE
value|0x1225
end_define

begin_define
DECL|macro|TWEI_DESHADEWHITERLMAX
define|#
directive|define
name|TWEI_DESHADEWHITERLMAX
value|0x1226
end_define

begin_define
DECL|macro|TWEI_BLACKSPECKLESREMOVED
define|#
directive|define
name|TWEI_BLACKSPECKLESREMOVED
value|0x1227
end_define

begin_define
DECL|macro|TWEI_WHITESPECKLESREMOVED
define|#
directive|define
name|TWEI_WHITESPECKLESREMOVED
value|0x1228
end_define

begin_define
DECL|macro|TWEI_HORZLINECOUNT
define|#
directive|define
name|TWEI_HORZLINECOUNT
value|0x1229
end_define

begin_define
DECL|macro|TWEI_VERTLINECOUNT
define|#
directive|define
name|TWEI_VERTLINECOUNT
value|0x122A
end_define

begin_define
DECL|macro|TWEI_DESKEWSTATUS
define|#
directive|define
name|TWEI_DESKEWSTATUS
value|0x122B
end_define

begin_define
DECL|macro|TWEI_SKEWORIGINALANGLE
define|#
directive|define
name|TWEI_SKEWORIGINALANGLE
value|0x122C
end_define

begin_define
DECL|macro|TWEI_SKEWFINALANGLE
define|#
directive|define
name|TWEI_SKEWFINALANGLE
value|0x122D
end_define

begin_define
DECL|macro|TWEI_SKEWCONFIDENCE
define|#
directive|define
name|TWEI_SKEWCONFIDENCE
value|0x122E
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWX1
define|#
directive|define
name|TWEI_SKEWWINDOWX1
value|0x122F
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWY1
define|#
directive|define
name|TWEI_SKEWWINDOWY1
value|0x1230
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWX2
define|#
directive|define
name|TWEI_SKEWWINDOWX2
value|0x1231
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWY2
define|#
directive|define
name|TWEI_SKEWWINDOWY2
value|0x1232
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWX3
define|#
directive|define
name|TWEI_SKEWWINDOWX3
value|0x1233
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWY3
define|#
directive|define
name|TWEI_SKEWWINDOWY3
value|0x1234
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWX4
define|#
directive|define
name|TWEI_SKEWWINDOWX4
value|0x1235
end_define

begin_define
DECL|macro|TWEI_SKEWWINDOWY4
define|#
directive|define
name|TWEI_SKEWWINDOWY4
value|0x1236
end_define

begin_define
DECL|macro|TWEJ_NONE
define|#
directive|define
name|TWEJ_NONE
value|0x0000
end_define

begin_define
DECL|macro|TWEJ_MIDSEPARATOR
define|#
directive|define
name|TWEJ_MIDSEPARATOR
value|0x0001
end_define

begin_define
DECL|macro|TWEJ_PATCH1
define|#
directive|define
name|TWEJ_PATCH1
value|0x0002
end_define

begin_define
DECL|macro|TWEJ_PATCH2
define|#
directive|define
name|TWEJ_PATCH2
value|0x0003
end_define

begin_define
DECL|macro|TWEJ_PATCH3
define|#
directive|define
name|TWEJ_PATCH3
value|0x0004
end_define

begin_define
DECL|macro|TWEJ_PATCH4
define|#
directive|define
name|TWEJ_PATCH4
value|0x0005
end_define

begin_define
DECL|macro|TWEJ_PATCH6
define|#
directive|define
name|TWEJ_PATCH6
value|0x0006
end_define

begin_define
DECL|macro|TWEJ_PATCHT
define|#
directive|define
name|TWEJ_PATCHT
value|0x0007
end_define

begin_comment
comment|/***************************************************************************  *            Return Codes and Condition Codes section                     *  ***************************************************************************/
end_comment

begin_comment
comment|/* Return Codes: DSM_Entry and DS_Entry may return any one of these values. */
end_comment

begin_define
DECL|macro|TWRC_CUSTOMBASE
define|#
directive|define
name|TWRC_CUSTOMBASE
value|0x8000
end_define

begin_define
DECL|macro|TWRC_SUCCESS
define|#
directive|define
name|TWRC_SUCCESS
value|0
end_define

begin_define
DECL|macro|TWRC_FAILURE
define|#
directive|define
name|TWRC_FAILURE
value|1
end_define

begin_comment
DECL|macro|TWRC_FAILURE
comment|/* Application may get TW_STATUS for info on failure */
end_comment

begin_define
DECL|macro|TWRC_CHECKSTATUS
define|#
directive|define
name|TWRC_CHECKSTATUS
value|2
end_define

begin_comment
DECL|macro|TWRC_CHECKSTATUS
comment|/* "tried hard"; get status                  */
end_comment

begin_define
DECL|macro|TWRC_CANCEL
define|#
directive|define
name|TWRC_CANCEL
value|3
end_define

begin_define
DECL|macro|TWRC_DSEVENT
define|#
directive|define
name|TWRC_DSEVENT
value|4
end_define

begin_define
DECL|macro|TWRC_NOTDSEVENT
define|#
directive|define
name|TWRC_NOTDSEVENT
value|5
end_define

begin_define
DECL|macro|TWRC_XFERDONE
define|#
directive|define
name|TWRC_XFERDONE
value|6
end_define

begin_define
DECL|macro|TWRC_ENDOFLIST
define|#
directive|define
name|TWRC_ENDOFLIST
value|7
end_define

begin_comment
DECL|macro|TWRC_ENDOFLIST
comment|/* After MSG_GETNEXT if nothing left         */
end_comment

begin_define
DECL|macro|TWRC_INFONOTSUPPORTED
define|#
directive|define
name|TWRC_INFONOTSUPPORTED
value|8
end_define

begin_define
DECL|macro|TWRC_DATANOTAVAILABLE
define|#
directive|define
name|TWRC_DATANOTAVAILABLE
value|9
end_define

begin_comment
comment|/* Condition Codes: Application gets these by doing DG_CONTROL DAT_STATUS MSG_GET.  */
end_comment

begin_define
DECL|macro|TWCC_CUSTOMBASE
define|#
directive|define
name|TWCC_CUSTOMBASE
value|0x8000
end_define

begin_define
DECL|macro|TWCC_SUCCESS
define|#
directive|define
name|TWCC_SUCCESS
value|0
end_define

begin_comment
DECL|macro|TWCC_SUCCESS
comment|/* It worked!                                */
end_comment

begin_define
DECL|macro|TWCC_BUMMER
define|#
directive|define
name|TWCC_BUMMER
value|1
end_define

begin_comment
DECL|macro|TWCC_BUMMER
comment|/* Failure due to unknown causes             */
end_comment

begin_define
DECL|macro|TWCC_LOWMEMORY
define|#
directive|define
name|TWCC_LOWMEMORY
value|2
end_define

begin_comment
DECL|macro|TWCC_LOWMEMORY
comment|/* Not enough memory to perform operation    */
end_comment

begin_define
DECL|macro|TWCC_NODS
define|#
directive|define
name|TWCC_NODS
value|3
end_define

begin_comment
DECL|macro|TWCC_NODS
comment|/* No Data Source                            */
end_comment

begin_define
DECL|macro|TWCC_MAXCONNECTIONS
define|#
directive|define
name|TWCC_MAXCONNECTIONS
value|4
end_define

begin_comment
DECL|macro|TWCC_MAXCONNECTIONS
comment|/* DS is connected to max possible applications      */
end_comment

begin_define
DECL|macro|TWCC_OPERATIONERROR
define|#
directive|define
name|TWCC_OPERATIONERROR
value|5
end_define

begin_comment
DECL|macro|TWCC_OPERATIONERROR
comment|/* DS or DSM reported error, application shouldn't   */
end_comment

begin_define
DECL|macro|TWCC_BADCAP
define|#
directive|define
name|TWCC_BADCAP
value|6
end_define

begin_comment
DECL|macro|TWCC_BADCAP
comment|/* Unknown capability                        */
end_comment

begin_define
DECL|macro|TWCC_BADPROTOCOL
define|#
directive|define
name|TWCC_BADPROTOCOL
value|9
end_define

begin_comment
DECL|macro|TWCC_BADPROTOCOL
comment|/* Unrecognized MSG DG DAT combination       */
end_comment

begin_define
DECL|macro|TWCC_BADVALUE
define|#
directive|define
name|TWCC_BADVALUE
value|10
end_define

begin_comment
DECL|macro|TWCC_BADVALUE
comment|/* Data parameter out of range              */
end_comment

begin_define
DECL|macro|TWCC_SEQERROR
define|#
directive|define
name|TWCC_SEQERROR
value|11
end_define

begin_comment
DECL|macro|TWCC_SEQERROR
comment|/* DG DAT MSG out of expected sequence      */
end_comment

begin_define
DECL|macro|TWCC_BADDEST
define|#
directive|define
name|TWCC_BADDEST
value|12
end_define

begin_comment
DECL|macro|TWCC_BADDEST
comment|/* Unknown destination Application/Source in DSM_Entry */
end_comment

begin_define
DECL|macro|TWCC_CAPUNSUPPORTED
define|#
directive|define
name|TWCC_CAPUNSUPPORTED
value|13
end_define

begin_comment
DECL|macro|TWCC_CAPUNSUPPORTED
comment|/* Capability not supported by source            */
end_comment

begin_define
DECL|macro|TWCC_CAPBADOPERATION
define|#
directive|define
name|TWCC_CAPBADOPERATION
value|14
end_define

begin_comment
DECL|macro|TWCC_CAPBADOPERATION
comment|/* Operation not supported by capability         */
end_comment

begin_define
DECL|macro|TWCC_CAPSEQERROR
define|#
directive|define
name|TWCC_CAPSEQERROR
value|15
end_define

begin_comment
DECL|macro|TWCC_CAPSEQERROR
comment|/* Capability has dependancy on other capability */
end_comment

begin_comment
comment|/* Added 1.8 */
end_comment

begin_define
DECL|macro|TWCC_DENIED
define|#
directive|define
name|TWCC_DENIED
value|16
end_define

begin_comment
DECL|macro|TWCC_DENIED
comment|/* File System operation is denied (file is protected) */
end_comment

begin_define
DECL|macro|TWCC_FILEEXISTS
define|#
directive|define
name|TWCC_FILEEXISTS
value|17
end_define

begin_comment
DECL|macro|TWCC_FILEEXISTS
comment|/* Operation failed because file already exists. */
end_comment

begin_define
DECL|macro|TWCC_FILENOTFOUND
define|#
directive|define
name|TWCC_FILENOTFOUND
value|18
end_define

begin_comment
DECL|macro|TWCC_FILENOTFOUND
comment|/* File not found */
end_comment

begin_define
DECL|macro|TWCC_NOTEMPTY
define|#
directive|define
name|TWCC_NOTEMPTY
value|19
end_define

begin_comment
DECL|macro|TWCC_NOTEMPTY
comment|/* Operation failed because directory is not empty */
end_comment

begin_define
DECL|macro|TWCC_PAPERJAM
define|#
directive|define
name|TWCC_PAPERJAM
value|20
end_define

begin_comment
DECL|macro|TWCC_PAPERJAM
comment|/* The feeder is jammed */
end_comment

begin_define
DECL|macro|TWCC_PAPERDOUBLEFEED
define|#
directive|define
name|TWCC_PAPERDOUBLEFEED
value|21
end_define

begin_comment
DECL|macro|TWCC_PAPERDOUBLEFEED
comment|/* The feeder detected multiple pages */
end_comment

begin_define
DECL|macro|TWCC_FILEWRITEERROR
define|#
directive|define
name|TWCC_FILEWRITEERROR
value|22
end_define

begin_comment
DECL|macro|TWCC_FILEWRITEERROR
comment|/* Error writing the file (meant for things like disk full conditions) */
end_comment

begin_define
DECL|macro|TWCC_CHECKDEVICEONLINE
define|#
directive|define
name|TWCC_CHECKDEVICEONLINE
value|23
end_define

begin_comment
DECL|macro|TWCC_CHECKDEVICEONLINE
comment|/* The device went offline prior to or during this operation */
end_comment

begin_comment
comment|/* bit patterns: for query the operation that are supported by the data source on a capability */
end_comment

begin_comment
comment|/* Application gets these through DG_CONTROL/DAT_CAPABILITY/MSG_QUERYSUPPORT */
end_comment

begin_comment
comment|/* Added 1.6 */
end_comment

begin_define
DECL|macro|TWQC_GET
define|#
directive|define
name|TWQC_GET
value|0x0001
end_define

begin_define
DECL|macro|TWQC_SET
define|#
directive|define
name|TWQC_SET
value|0x0002
end_define

begin_define
DECL|macro|TWQC_GETDEFAULT
define|#
directive|define
name|TWQC_GETDEFAULT
value|0x0004
end_define

begin_define
DECL|macro|TWQC_GETCURRENT
define|#
directive|define
name|TWQC_GETCURRENT
value|0x0008
end_define

begin_define
DECL|macro|TWQC_RESET
define|#
directive|define
name|TWQC_RESET
value|0x0010
end_define

begin_comment
comment|/****************************************************************************  * Entry Points                                                             *  ****************************************************************************/
end_comment

begin_comment
comment|/**********************************************************************  * Function: DSM_Entry, the only entry point into the Data Source Manager.  *  * Parameters:  *  pOrigin Identifies the source module of the message. This could  *          identify an Application, a Source, or the Source Manager.  *  *  pDest   Identifies the destination module for the message.  *          This could identify an application or a data source.  *          If this is NULL, the message goes to the Source Manager.  *  *  DG      The Data Group.   *          Example: DG_IMAGE.  *  *  DAT     The Data Attribute Type.  *          Example: DAT_IMAGEMEMXFER.  *      *  MSG     The message.  Messages are interpreted by the destination module  *          with respect to the Data Group and the Data Attribute Type.    *          Example: MSG_GET.  *  *  pData   A pointer to the data structure or variable identified   *          by the Data Attribute Type.  *          Example: (TW_MEMREF)&ImageMemXfer  *                   where ImageMemXfer is a TW_IMAGEMEMXFER structure.  *                      * Returns:  *  ReturnCode  *         Example: TWRC_SUCCESS.  *  ********************************************************************/
end_comment

begin_comment
comment|/* Don't mangle the name "DSM_Entry" if we're compiling in C++! */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
ifdef|#
directive|ifdef
name|_MSWIN_
name|TW_UINT16
name|FAR
name|PASCAL
name|DSM_Entry
parameter_list|(
name|pTW_IDENTITY
name|pOrigin
parameter_list|,
name|pTW_IDENTITY
name|pDest
parameter_list|,
name|TW_UINT32
name|DG
parameter_list|,
name|TW_UINT16
name|DAT
parameter_list|,
name|TW_UINT16
name|MSG
parameter_list|,
name|TW_MEMREF
name|pData
parameter_list|)
function_decl|;
DECL|typedef|DSMENTRYPROC
typedef|typedef
name|TW_UINT16
function_decl|(
name|FAR
name|PASCAL
modifier|*
name|DSMENTRYPROC
function_decl|)
parameter_list|(
name|pTW_IDENTITY
parameter_list|,
name|pTW_IDENTITY
parameter_list|,
name|TW_UINT32
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_MEMREF
parameter_list|)
function_decl|;
else|#
directive|else
comment|/* _MSWIN_ */
name|FAR
name|PASCAL
name|TW_UINT16
name|DSM_Entry
parameter_list|(
name|pTW_IDENTITY
name|pOrigin
parameter_list|,
name|pTW_IDENTITY
name|pDest
parameter_list|,
name|TW_UINT32
name|DG
parameter_list|,
name|TW_UINT16
name|DAT
parameter_list|,
name|TW_UINT16
name|MSG
parameter_list|,
name|TW_MEMREF
name|pData
parameter_list|)
function_decl|;
typedef|typedef
name|TW_UINT16
function_decl|(
modifier|*
name|DSMENTRYPROC
function_decl|)
parameter_list|(
name|pTW_IDENTITY
parameter_list|,
name|pTW_IDENTITY
parameter_list|,
name|TW_UINT32
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_MEMREF
parameter_list|)
function_decl|;
endif|#
directive|endif
comment|/* _MSWIN_ */
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* cplusplus */
end_comment

begin_comment
comment|/**********************************************************************  * Function: DS_Entry, the entry point provided by a Data Source.  *  * Parameters:  *  pOrigin Identifies the source module of the message. This could  *          identify an application or the Data Source Manager.  *  *  DG      The Data Group.   *          Example: DG_IMAGE.  *             *  DAT     The Data Attribute Type.  *          Example: DAT_IMAGEMEMXFER.  *      *  MSG     The message.  Messages are interpreted by the data source  *          with respect to the Data Group and the Data Attribute Type.  *          Example: MSG_GET.  *  *  pData   A pointer to the data structure or variable identified   *          by the Data Attribute Type.  *          Example: (TW_MEMREF)&ImageMemXfer  *                   where ImageMemXfer is a TW_IMAGEMEMXFER structure.  *                      * Returns:  *  ReturnCode  *          Example: TWRC_SUCCESS.  *  * Note:  *  The DSPROC type is only used by an application when it calls  *  a Data Source directly, bypassing the Data Source Manager.  *  ********************************************************************/
end_comment

begin_comment
comment|/* Don't mangle the name "DS_Entry" if we're compiling in C++! */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
ifdef|#
directive|ifdef
name|_MSWIN_
ifdef|#
directive|ifdef
name|_WIN32
name|__declspec
argument_list|(
argument|dllexport
argument_list|)
name|TW_UINT16
name|FAR
name|PASCAL
name|DS_Entry
parameter_list|(
name|pTW_IDENTITY
name|pOrigin
parameter_list|,
name|TW_UINT32
name|DG
parameter_list|,
name|TW_UINT16
name|DAT
parameter_list|,
name|TW_UINT16
name|MSG
parameter_list|,
name|TW_MEMREF
name|pData
parameter_list|)
function_decl|;
else|#
directive|else
comment|/* _WIN32 */
name|TW_UINT16
name|FAR
name|PASCAL
name|DS_Entry
parameter_list|(
name|pTW_IDENTITY
name|pOrigin
parameter_list|,
name|TW_UINT32
name|DG
parameter_list|,
name|TW_UINT16
name|DAT
parameter_list|,
name|TW_UINT16
name|MSG
parameter_list|,
name|TW_MEMREF
name|pData
parameter_list|)
function_decl|;
endif|#
directive|endif
comment|/* _WIN32 */
DECL|typedef|DSENTRYPROC
typedef|typedef
name|TW_UINT16
function_decl|(
name|FAR
name|PASCAL
modifier|*
name|DSENTRYPROC
function_decl|)
parameter_list|(
name|pTW_IDENTITY
name|pOrigin
parameter_list|,
name|TW_UINT32
name|DG
parameter_list|,
name|TW_UINT16
name|DAT
parameter_list|,
name|TW_UINT16
name|MSG
parameter_list|,
name|TW_MEMREF
name|pData
parameter_list|)
function_decl|;
else|#
directive|else
comment|/* _MSWIN_ */
name|FAR
name|PASCAL
name|TW_UINT16
name|DS_Entry
parameter_list|(
name|pTW_IDENTITY
name|pOrigin
parameter_list|,
name|TW_UINT32
name|DG
parameter_list|,
name|TW_UINT16
name|DAT
parameter_list|,
name|TW_UINT16
name|MSG
parameter_list|,
name|TW_MEMREF
name|pData
parameter_list|)
function_decl|;
typedef|typedef
name|TW_UINT16
function_decl|(
modifier|*
name|DSENTRYPROC
function_decl|)
parameter_list|(
name|pTW_IDENTITY
parameter_list|,
name|TW_UINT32
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_UINT16
parameter_list|,
name|TW_MEMREF
parameter_list|)
function_decl|;
endif|#
directive|endif
comment|/* _MSWIN_ */
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* cplusplus */
end_comment

begin_comment
comment|/*  SDH - 02/08/95 - TWUNK */
end_comment

begin_comment
comment|/*  Force 32-bit twain to use same packing of twain structures as existing */
end_comment

begin_comment
comment|/*  16-bit twain.  This allows 16/32-bit thunking. */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|WIN32
end_ifdef

begin_ifdef
ifdef|#
directive|ifdef
name|__BORLANDC__
end_ifdef

begin_comment
comment|//(Mentor June 13, 1996) if we're using a Borland compiler
end_comment

begin_pragma
pragma|#
directive|pragma
name|option
name|-
name|a
name|.
end_pragma

begin_comment
comment|//(Mentor October 30, 1996) switch back to original alignment
end_comment

begin_else
else|#
directive|else
end_else

begin_comment
comment|//(Mentor June 13, 1996) if NOT using a Borland compiler
end_comment

begin_pragma
pragma|#
directive|pragma
name|pack
name|(
name|pop
name|,
name|before_twain
name|)
end_pragma

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|//(Mentor June 13, 1996)
end_comment

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* WIN32 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* WIN32 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* TWAIN */
end_comment

end_unit


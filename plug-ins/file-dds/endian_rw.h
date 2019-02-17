begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* 	DDS GIMP plugin  	Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,    with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  	This program is free software; you can redistribute it and/or 	modify it under the terms of the GNU General Public 	License as published by the Free Software Foundation; either 	version 2 of the License, or (at your option) any later version.  	This program is distributed in the hope that it will be useful, 	but WITHOUT ANY WARRANTY; without even the implied warranty of 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 	General Public License for more details.  	You should have received a copy of the GNU General Public License 	along with this program; see the file COPYING.  If not, write to 	the Free Software Foundation, 51 Franklin Street, Fifth Floor 	Boston, MA 02110-1301, USA. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|ENDIAN_RW_H
end_ifndef

begin_define
DECL|macro|ENDIAN_RW_H
define|#
directive|define
name|ENDIAN_RW_H
end_define

begin_define
DECL|macro|GETL64 (buf)
define|#
directive|define
name|GETL64
parameter_list|(
name|buf
parameter_list|)
define|\
value|(((unsigned long long)(buf)[0]      ) | \     ((unsigned long long)(buf)[1]<<  8) | \     ((unsigned long long)(buf)[2]<< 16) | \     ((unsigned long long)(buf)[3]<< 24) | \     ((unsigned long long)(buf)[4]<< 32) | \     ((unsigned long long)(buf)[5]<< 40) | \     ((unsigned long long)(buf)[6]<< 48) | \     ((unsigned long long)(buf)[7]<< 56))
end_define

begin_define
DECL|macro|GETL32 (buf)
define|#
directive|define
name|GETL32
parameter_list|(
name|buf
parameter_list|)
define|\
value|(((unsigned int)(buf)[0]      ) | \     ((unsigned int)(buf)[1]<<  8) | \     ((unsigned int)(buf)[2]<< 16) | \     ((unsigned int)(buf)[3]<< 24))
end_define

begin_define
DECL|macro|GETL24 (buf)
define|#
directive|define
name|GETL24
parameter_list|(
name|buf
parameter_list|)
define|\
value|(((unsigned int)(buf)[0]      ) | \     ((unsigned int)(buf)[1]<<  8) | \     ((unsigned int)(buf)[2]<< 16))
end_define

begin_define
DECL|macro|GETL16 (buf)
define|#
directive|define
name|GETL16
parameter_list|(
name|buf
parameter_list|)
define|\
value|(((unsigned short)(buf)[0]     ) | \     ((unsigned short)(buf)[1]<< 8))
end_define

begin_define
DECL|macro|PUTL16 (buf,s)
define|#
directive|define
name|PUTL16
parameter_list|(
name|buf
parameter_list|,
name|s
parameter_list|)
define|\
value|(buf)[0] = ((s)     )& 0xff; \    (buf)[1] = ((s)>> 8)& 0xff;
end_define

begin_define
DECL|macro|PUTL32 (buf,l)
define|#
directive|define
name|PUTL32
parameter_list|(
name|buf
parameter_list|,
name|l
parameter_list|)
define|\
value|(buf)[0] = ((l)      )& 0xff; \ 	(buf)[1] = ((l)>>  8)& 0xff; \ 	(buf)[2] = ((l)>> 16)& 0xff; \ 	(buf)[3] = ((l)>> 24)& 0xff;
end_define

begin_define
DECL|macro|PUTL64 (buf,ll)
define|#
directive|define
name|PUTL64
parameter_list|(
name|buf
parameter_list|,
name|ll
parameter_list|)
define|\
value|(buf)[0] = ((ll)      )& 0xff; \ 	(buf)[1] = ((ll)>>  8)& 0xff; \ 	(buf)[2] = ((ll)>> 16)& 0xff; \ 	(buf)[3] = ((ll)>> 24)& 0xff; \    (buf)[4] = ((ll)>> 32)& 0xff; \    (buf)[5] = ((ll)>> 40)& 0xff; \    (buf)[6] = ((ll)>> 48)& 0xff; \    (buf)[7] = ((ll)>> 56)& 0xff;
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit


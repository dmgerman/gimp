begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_empty
empty|#ident "@(#)g3.c	3.1 95/08/30 Copyright (c) Gert Doering"
end_empty

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|"g3.h"
end_include

begin_decl_stmt
DECL|variable|t_white
name|struct
name|g3code
name|t_white
index|[
literal|66
index|]
init|=
block|{
block|{
literal|0
block|,
literal|0
block|,
literal|0x0ac
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|1
block|,
literal|0x038
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|2
block|,
literal|0x00e
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|3
block|,
literal|0x001
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|4
block|,
literal|0x00d
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|5
block|,
literal|0x003
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|6
block|,
literal|0x007
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|7
block|,
literal|0x00f
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|8
block|,
literal|0x019
block|,
literal|5
block|}
block|,
block|{
literal|0
block|,
literal|9
block|,
literal|0x005
block|,
literal|5
block|}
block|,
block|{
literal|0
block|,
literal|10
block|,
literal|0x01c
block|,
literal|5
block|}
block|,
block|{
literal|0
block|,
literal|11
block|,
literal|0x002
block|,
literal|5
block|}
block|,
block|{
literal|0
block|,
literal|12
block|,
literal|0x004
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|13
block|,
literal|0x030
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|14
block|,
literal|0x00b
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|15
block|,
literal|0x02b
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|16
block|,
literal|0x015
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|17
block|,
literal|0x035
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|18
block|,
literal|0x072
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|19
block|,
literal|0x018
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|20
block|,
literal|0x008
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|21
block|,
literal|0x074
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|22
block|,
literal|0x060
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|23
block|,
literal|0x010
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|24
block|,
literal|0x00a
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|25
block|,
literal|0x06a
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|26
block|,
literal|0x064
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|27
block|,
literal|0x012
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|28
block|,
literal|0x00c
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|29
block|,
literal|0x040
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|30
block|,
literal|0x0c0
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|31
block|,
literal|0x058
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|32
block|,
literal|0x0d8
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|33
block|,
literal|0x048
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|34
block|,
literal|0x0c8
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|35
block|,
literal|0x028
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|36
block|,
literal|0x0a8
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|37
block|,
literal|0x068
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|38
block|,
literal|0x0e8
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|39
block|,
literal|0x014
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|40
block|,
literal|0x094
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|41
block|,
literal|0x054
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|42
block|,
literal|0x0d4
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|43
block|,
literal|0x034
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|44
block|,
literal|0x0b4
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|45
block|,
literal|0x020
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|46
block|,
literal|0x0a0
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|47
block|,
literal|0x050
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|48
block|,
literal|0x0d0
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|49
block|,
literal|0x04a
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|50
block|,
literal|0x0ca
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|51
block|,
literal|0x02a
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|52
block|,
literal|0x0aa
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|53
block|,
literal|0x024
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|54
block|,
literal|0x0a4
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|55
block|,
literal|0x01a
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|56
block|,
literal|0x09a
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|57
block|,
literal|0x05a
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|58
block|,
literal|0x0da
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|59
block|,
literal|0x052
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|60
block|,
literal|0x0d2
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|61
block|,
literal|0x04c
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|62
block|,
literal|0x0cc
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|63
block|,
literal|0x02c
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
operator|-
literal|1
block|,
literal|0
block|,
literal|11
block|}
block|,
comment|/* 11 0-bits == EOL, special handling */
block|{
literal|0
block|,
operator|-
literal|1
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* end of table */
end_comment

begin_comment
comment|/* make-up codes white */
end_comment

begin_decl_stmt
DECL|variable|m_white
name|struct
name|g3code
name|m_white
index|[
literal|28
index|]
init|=
block|{
block|{
literal|0
block|,
literal|64
block|,
literal|0x01b
block|,
literal|5
block|}
block|,
block|{
literal|0
block|,
literal|128
block|,
literal|0x009
block|,
literal|5
block|}
block|,
block|{
literal|0
block|,
literal|192
block|,
literal|0x03a
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|256
block|,
literal|0x076
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|320
block|,
literal|0x06c
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|384
block|,
literal|0x0ec
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|448
block|,
literal|0x026
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|512
block|,
literal|0x0a6
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|576
block|,
literal|0x016
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|640
block|,
literal|0x0e6
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|704
block|,
literal|0x066
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|768
block|,
literal|0x166
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|832
block|,
literal|0x096
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|896
block|,
literal|0x196
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|960
block|,
literal|0x056
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1024
block|,
literal|0x156
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1088
block|,
literal|0x0d6
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1152
block|,
literal|0x1d6
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1216
block|,
literal|0x036
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1280
block|,
literal|0x136
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1344
block|,
literal|0x0b6
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1408
block|,
literal|0x1b6
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1472
block|,
literal|0x032
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1536
block|,
literal|0x132
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1600
block|,
literal|0x0b2
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|1664
block|,
literal|0x006
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|1728
block|,
literal|0x1b2
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
operator|-
literal|1
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|t_black
name|struct
name|g3code
name|t_black
index|[
literal|66
index|]
init|=
block|{
block|{
literal|0
block|,
literal|0
block|,
literal|0x3b0
block|,
literal|10
block|}
block|,
block|{
literal|0
block|,
literal|1
block|,
literal|0x002
block|,
literal|3
block|}
block|,
block|{
literal|0
block|,
literal|2
block|,
literal|0x003
block|,
literal|2
block|}
block|,
block|{
literal|0
block|,
literal|3
block|,
literal|0x001
block|,
literal|2
block|}
block|,
block|{
literal|0
block|,
literal|4
block|,
literal|0x006
block|,
literal|3
block|}
block|,
block|{
literal|0
block|,
literal|5
block|,
literal|0x00c
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|6
block|,
literal|0x004
block|,
literal|4
block|}
block|,
block|{
literal|0
block|,
literal|7
block|,
literal|0x018
block|,
literal|5
block|}
block|,
block|{
literal|0
block|,
literal|8
block|,
literal|0x028
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|9
block|,
literal|0x008
block|,
literal|6
block|}
block|,
block|{
literal|0
block|,
literal|10
block|,
literal|0x010
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|11
block|,
literal|0x050
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|12
block|,
literal|0x070
block|,
literal|7
block|}
block|,
block|{
literal|0
block|,
literal|13
block|,
literal|0x020
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|14
block|,
literal|0x0e0
block|,
literal|8
block|}
block|,
block|{
literal|0
block|,
literal|15
block|,
literal|0x030
block|,
literal|9
block|}
block|,
block|{
literal|0
block|,
literal|16
block|,
literal|0x3a0
block|,
literal|10
block|}
block|,
block|{
literal|0
block|,
literal|17
block|,
literal|0x060
block|,
literal|10
block|}
block|,
block|{
literal|0
block|,
literal|18
block|,
literal|0x040
block|,
literal|10
block|}
block|,
block|{
literal|0
block|,
literal|19
block|,
literal|0x730
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
literal|20
block|,
literal|0x0b0
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
literal|21
block|,
literal|0x1b0
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
literal|22
block|,
literal|0x760
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
literal|23
block|,
literal|0x0a0
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
literal|24
block|,
literal|0x740
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
literal|25
block|,
literal|0x0c0
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
literal|26
block|,
literal|0x530
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|27
block|,
literal|0xd30
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|28
block|,
literal|0x330
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|29
block|,
literal|0xb30
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|30
block|,
literal|0x160
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|31
block|,
literal|0x960
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|32
block|,
literal|0x560
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|33
block|,
literal|0xd60
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|34
block|,
literal|0x4b0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|35
block|,
literal|0xcb0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|36
block|,
literal|0x2b0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|37
block|,
literal|0xab0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|38
block|,
literal|0x6b0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|39
block|,
literal|0xeb0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|40
block|,
literal|0x360
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|41
block|,
literal|0xb60
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|42
block|,
literal|0x5b0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|43
block|,
literal|0xdb0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|44
block|,
literal|0x2a0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|45
block|,
literal|0xaa0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|46
block|,
literal|0x6a0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|47
block|,
literal|0xea0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|48
block|,
literal|0x260
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|49
block|,
literal|0xa60
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|50
block|,
literal|0x4a0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|51
block|,
literal|0xca0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|52
block|,
literal|0x240
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|53
block|,
literal|0xec0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|54
block|,
literal|0x1c0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|55
block|,
literal|0xe40
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|56
block|,
literal|0x140
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|57
block|,
literal|0x1a0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|58
block|,
literal|0x9a0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|59
block|,
literal|0xd40
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|60
block|,
literal|0x340
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|61
block|,
literal|0x5a0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|62
block|,
literal|0x660
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|63
block|,
literal|0xe60
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
operator|-
literal|1
block|,
literal|0x000
block|,
literal|11
block|}
block|,
block|{
literal|0
block|,
operator|-
literal|1
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|m_black
name|struct
name|g3code
name|m_black
index|[
literal|28
index|]
init|=
block|{
block|{
literal|0
block|,
literal|64
block|,
literal|0x3c0
block|,
literal|10
block|}
block|,
block|{
literal|0
block|,
literal|128
block|,
literal|0x130
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|192
block|,
literal|0x930
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|256
block|,
literal|0xda0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|320
block|,
literal|0xcc0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|384
block|,
literal|0x2c0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|448
block|,
literal|0xac0
block|,
literal|12
block|}
block|,
block|{
literal|0
block|,
literal|512
block|,
literal|0x6c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|576
block|,
literal|0x16c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|640
block|,
literal|0xa40
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|704
block|,
literal|0x1a40
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|768
block|,
literal|0x640
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|832
block|,
literal|0x1640
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|896
block|,
literal|0x9c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|960
block|,
literal|0x19c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1024
block|,
literal|0x5c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1088
block|,
literal|0x15c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1152
block|,
literal|0xdc0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1216
block|,
literal|0x1dc0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1280
block|,
literal|0x940
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1344
block|,
literal|0x1940
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1408
block|,
literal|0x540
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1472
block|,
literal|0x1540
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1536
block|,
literal|0xb40
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1600
block|,
literal|0x1b40
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1664
block|,
literal|0x4c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
literal|1728
block|,
literal|0x14c0
block|,
literal|13
block|}
block|,
block|{
literal|0
block|,
operator|-
literal|1
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|tree_add_node (struct g3_tree * p,struct g3code * g3c,int bit_code,int bit_length)
name|void
name|tree_add_node
parameter_list|(
name|struct
name|g3_tree
modifier|*
name|p
parameter_list|,
name|struct
name|g3code
modifier|*
name|g3c
parameter_list|,
name|int
name|bit_code
parameter_list|,
name|int
name|bit_length
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
if|if
condition|(
name|bit_length
operator|<=
name|FBITS
condition|)
comment|/* leaf (multiple bits) */
block|{
name|g3c
operator|->
name|nr_bits
operator|=
name|bit_length
expr_stmt|;
comment|/* leaf tag */
if|if
condition|(
name|bit_length
operator|==
name|FBITS
condition|)
comment|/* full width */
block|{
name|p
operator|->
name|nextb
index|[
name|bit_code
index|]
operator|=
operator|(
expr|struct
name|g3_tree
operator|*
operator|)
name|g3c
expr_stmt|;
block|}
else|else
comment|/* fill bits */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
literal|1
operator|<<
operator|(
name|FBITS
operator|-
name|bit_length
operator|)
operator|)
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|->
name|nextb
index|[
name|bit_code
operator|+
operator|(
name|i
operator|<<
name|bit_length
operator|)
index|]
operator|=
operator|(
expr|struct
name|g3_tree
operator|*
operator|)
name|g3c
expr_stmt|;
block|}
block|}
else|else
comment|/* node */
block|{
name|struct
name|g3_tree
modifier|*
name|p2
decl_stmt|;
name|p2
operator|=
name|p
operator|->
name|nextb
index|[
name|bit_code
operator|&
name|BITM
index|]
expr_stmt|;
if|if
condition|(
name|p2
operator|==
literal|0
condition|)
comment|/* no sub-node exists */
block|{
name|p2
operator|=
name|p
operator|->
name|nextb
index|[
name|bit_code
operator|&
name|BITM
index|]
operator|=
operator|(
expr|struct
name|g3_tree
operator|*
operator|)
name|calloc
argument_list|(
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|g3_tree
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|p2
operator|==
name|NULL
condition|)
block|{
name|perror
argument_list|(
literal|"malloc 3"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|11
argument_list|)
expr_stmt|;
block|}
name|p2
operator|->
name|nr_bits
operator|=
literal|0
expr_stmt|;
comment|/* node tag */
block|}
if|if
condition|(
name|p2
operator|->
name|nr_bits
operator|!=
literal|0
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"internal table setup error\n"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|6
argument_list|)
expr_stmt|;
block|}
name|tree_add_node
argument_list|(
name|p2
argument_list|,
name|g3c
argument_list|,
name|bit_code
operator|>>
name|FBITS
argument_list|,
name|bit_length
operator|-
name|FBITS
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|build_tree (struct g3_tree ** p,struct g3code * c)
name|void
name|build_tree
parameter_list|(
name|struct
name|g3_tree
modifier|*
modifier|*
name|p
parameter_list|,
name|struct
name|g3code
modifier|*
name|c
parameter_list|)
block|{
if|if
condition|(
operator|*
name|p
operator|==
name|NULL
condition|)
block|{
operator|(
operator|*
name|p
operator|)
operator|=
operator|(
expr|struct
name|g3_tree
operator|*
operator|)
name|calloc
argument_list|(
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|g3_tree
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|p
operator|==
name|NULL
condition|)
block|{
name|perror
argument_list|(
literal|"malloc(1)"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|10
argument_list|)
expr_stmt|;
block|}
operator|(
operator|*
name|p
operator|)
operator|->
name|nr_bits
operator|=
literal|0
expr_stmt|;
block|}
while|while
condition|(
name|c
operator|->
name|bit_length
operator|!=
literal|0
condition|)
block|{
name|tree_add_node
argument_list|(
operator|*
name|p
argument_list|,
name|c
argument_list|,
name|c
operator|->
name|bit_code
argument_list|,
name|c
operator|->
name|bit_length
argument_list|)
expr_stmt|;
name|c
operator|++
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|init_byte_tab (int reverse,int byte_tab[])
name|void
name|init_byte_tab
parameter_list|(
name|int
name|reverse
parameter_list|,
name|int
name|byte_tab
index|[]
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
if|if
condition|(
name|reverse
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
name|byte_tab
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
else|else
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
name|byte_tab
index|[
name|i
index|]
operator|=
operator|(
operator|(
operator|(
name|i
operator|&
literal|0x01
operator|)
operator|<<
literal|7
operator|)
operator||
operator|(
operator|(
name|i
operator|&
literal|0x02
operator|)
operator|<<
literal|5
operator|)
operator||
operator|(
operator|(
name|i
operator|&
literal|0x04
operator|)
operator|<<
literal|3
operator|)
operator||
operator|(
operator|(
name|i
operator|&
literal|0x08
operator|)
operator|<<
literal|1
operator|)
operator||
operator|(
operator|(
name|i
operator|&
literal|0x10
operator|)
operator|>>
literal|1
operator|)
operator||
operator|(
operator|(
name|i
operator|&
literal|0x20
operator|)
operator|>>
literal|3
operator|)
operator||
operator|(
operator|(
name|i
operator|&
literal|0x40
operator|)
operator|>>
literal|5
operator|)
operator||
operator|(
operator|(
name|i
operator|&
literal|0x80
operator|)
operator|>>
literal|7
operator|)
operator|)
expr_stmt|;
block|}
end_function

end_unit


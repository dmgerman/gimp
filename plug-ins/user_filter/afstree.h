begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Written 1997 Jens Ch. Restemeier<jchrr@hrz.uni-bielefeld.de>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|AFSTREE_H
end_ifndef

begin_typedef
DECL|struct|_afstree
typedef|typedef
struct|struct
name|_afstree
block|{
DECL|member|op_type
name|int
name|op_type
decl_stmt|;
comment|/* symbol for operation */
DECL|member|value
name|int
name|value
decl_stmt|;
comment|/* constant for OP_CONST or number of nodes */
DECL|member|nodes
name|struct
name|_afstree
modifier|*
modifier|*
name|nodes
decl_stmt|;
comment|/* nodes, if neccessary */
DECL|typedef|s_afstree
block|}
name|s_afstree
typedef|;
end_typedef

begin_comment
comment|/* operators */
end_comment

begin_define
DECL|macro|OP_CONST
define|#
directive|define
name|OP_CONST
value|0
end_define

begin_define
DECL|macro|OP_VAR_r
define|#
directive|define
name|OP_VAR_r
value|1
end_define

begin_define
DECL|macro|OP_VAR_g
define|#
directive|define
name|OP_VAR_g
value|2
end_define

begin_define
DECL|macro|OP_VAR_b
define|#
directive|define
name|OP_VAR_b
value|3
end_define

begin_define
DECL|macro|OP_VAR_a
define|#
directive|define
name|OP_VAR_a
value|4
end_define

begin_define
DECL|macro|OP_VAR_c
define|#
directive|define
name|OP_VAR_c
value|5
end_define

begin_define
DECL|macro|OP_VAR_x
define|#
directive|define
name|OP_VAR_x
value|6
end_define

begin_define
DECL|macro|OP_VAR_y
define|#
directive|define
name|OP_VAR_y
value|7
end_define

begin_define
DECL|macro|OP_VAR_z
define|#
directive|define
name|OP_VAR_z
value|8
end_define

begin_define
DECL|macro|OP_VAR_X
define|#
directive|define
name|OP_VAR_X
value|9
end_define

begin_define
DECL|macro|OP_VAR_Y
define|#
directive|define
name|OP_VAR_Y
value|10
end_define

begin_define
DECL|macro|OP_VAR_Z
define|#
directive|define
name|OP_VAR_Z
value|11
end_define

begin_define
DECL|macro|OP_VAR_i
define|#
directive|define
name|OP_VAR_i
value|12
end_define

begin_define
DECL|macro|OP_VAR_u
define|#
directive|define
name|OP_VAR_u
value|13
end_define

begin_define
DECL|macro|OP_VAR_v
define|#
directive|define
name|OP_VAR_v
value|14
end_define

begin_define
DECL|macro|OP_VAR_d
define|#
directive|define
name|OP_VAR_d
value|15
end_define

begin_define
DECL|macro|OP_VAR_D
define|#
directive|define
name|OP_VAR_D
value|16
end_define

begin_define
DECL|macro|OP_VAR_m
define|#
directive|define
name|OP_VAR_m
value|17
end_define

begin_define
DECL|macro|OP_VAR_M
define|#
directive|define
name|OP_VAR_M
value|18
end_define

begin_define
DECL|macro|OP_VAR_dmin
define|#
directive|define
name|OP_VAR_dmin
value|19
end_define

begin_define
DECL|macro|OP_VAR_mmin
define|#
directive|define
name|OP_VAR_mmin
value|20
end_define

begin_define
DECL|macro|OP_ADD
define|#
directive|define
name|OP_ADD
value|21
end_define

begin_define
DECL|macro|OP_SUB
define|#
directive|define
name|OP_SUB
value|22
end_define

begin_define
DECL|macro|OP_MUL
define|#
directive|define
name|OP_MUL
value|23
end_define

begin_define
DECL|macro|OP_DIV
define|#
directive|define
name|OP_DIV
value|24
end_define

begin_define
DECL|macro|OP_MOD
define|#
directive|define
name|OP_MOD
value|25
end_define

begin_define
DECL|macro|OP_B_AND
define|#
directive|define
name|OP_B_AND
value|26
end_define

begin_define
DECL|macro|OP_B_OR
define|#
directive|define
name|OP_B_OR
value|27
end_define

begin_define
DECL|macro|OP_B_XOR
define|#
directive|define
name|OP_B_XOR
value|28
end_define

begin_define
DECL|macro|OP_B_NOT
define|#
directive|define
name|OP_B_NOT
value|29
end_define

begin_define
DECL|macro|OP_COND
define|#
directive|define
name|OP_COND
value|30
end_define

begin_define
DECL|macro|OP_AND
define|#
directive|define
name|OP_AND
value|31
end_define

begin_define
DECL|macro|OP_OR
define|#
directive|define
name|OP_OR
value|32
end_define

begin_define
DECL|macro|OP_NOT
define|#
directive|define
name|OP_NOT
value|33
end_define

begin_define
DECL|macro|OP_EQ
define|#
directive|define
name|OP_EQ
value|34
end_define

begin_define
DECL|macro|OP_NEQ
define|#
directive|define
name|OP_NEQ
value|35
end_define

begin_define
DECL|macro|OP_LE
define|#
directive|define
name|OP_LE
value|36
end_define

begin_define
DECL|macro|OP_BE
define|#
directive|define
name|OP_BE
value|37
end_define

begin_define
DECL|macro|OP_LT
define|#
directive|define
name|OP_LT
value|38
end_define

begin_define
DECL|macro|OP_BT
define|#
directive|define
name|OP_BT
value|39
end_define

begin_define
DECL|macro|OP_SHL
define|#
directive|define
name|OP_SHL
value|41
end_define

begin_define
DECL|macro|OP_SHR
define|#
directive|define
name|OP_SHR
value|42
end_define

begin_define
DECL|macro|F_SRC
define|#
directive|define
name|F_SRC
value|43
end_define

begin_define
DECL|macro|F_RAD
define|#
directive|define
name|F_RAD
value|44
end_define

begin_define
DECL|macro|F_CNV
define|#
directive|define
name|F_CNV
value|45
end_define

begin_define
DECL|macro|F_CTL
define|#
directive|define
name|F_CTL
value|46
end_define

begin_define
DECL|macro|F_ABS
define|#
directive|define
name|F_ABS
value|47
end_define

begin_define
DECL|macro|F_DIF
define|#
directive|define
name|F_DIF
value|48
end_define

begin_define
DECL|macro|F_SCL
define|#
directive|define
name|F_SCL
value|49
end_define

begin_define
DECL|macro|F_VAL
define|#
directive|define
name|F_VAL
value|50
end_define

begin_define
DECL|macro|F_ADD
define|#
directive|define
name|F_ADD
value|51
end_define

begin_define
DECL|macro|F_SUB
define|#
directive|define
name|F_SUB
value|52
end_define

begin_define
DECL|macro|F_MIX
define|#
directive|define
name|F_MIX
value|53
end_define

begin_define
DECL|macro|F_RND
define|#
directive|define
name|F_RND
value|54
end_define

begin_define
DECL|macro|F_C2D
define|#
directive|define
name|F_C2D
value|55
end_define

begin_define
DECL|macro|F_C2M
define|#
directive|define
name|F_C2M
value|56
end_define

begin_define
DECL|macro|F_R2X
define|#
directive|define
name|F_R2X
value|57
end_define

begin_define
DECL|macro|F_R2Y
define|#
directive|define
name|F_R2Y
value|58
end_define

begin_define
DECL|macro|F_MIN
define|#
directive|define
name|F_MIN
value|59
end_define

begin_define
DECL|macro|F_MAX
define|#
directive|define
name|F_MAX
value|60
end_define

begin_define
DECL|macro|F_PUT
define|#
directive|define
name|F_PUT
value|61
end_define

begin_define
DECL|macro|F_GET
define|#
directive|define
name|F_GET
value|62
end_define

begin_define
DECL|macro|F_SIN
define|#
directive|define
name|F_SIN
value|63
end_define

begin_define
DECL|macro|F_COS
define|#
directive|define
name|F_COS
value|64
end_define

begin_define
DECL|macro|F_TAN
define|#
directive|define
name|F_TAN
value|65
end_define

begin_define
DECL|macro|F_SQR
define|#
directive|define
name|F_SQR
value|66
end_define

begin_define
DECL|macro|OP_COMMA
define|#
directive|define
name|OP_COMMA
value|67
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit


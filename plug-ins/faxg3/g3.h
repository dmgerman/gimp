begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_empty
empty|#ident "@(#)g3.h	3.1 95/08/30 Copyright (c) Gert Doering"
end_empty

begin_ifndef
ifndef|#
directive|ifndef
name|NULL
end_ifndef

begin_define
DECL|macro|NULL
define|#
directive|define
name|NULL
value|0L
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* nr_bits is set to ( bit_length MOD FBITS ) by build_g3_tree,  * nr_pels is the number of pixels to write for that code,  * bit_code is the code itself (msb2lsb), and bit_length its length  */
end_comment

begin_struct
DECL|struct|g3code
DECL|member|nr_bits
DECL|member|nr_pels
DECL|member|bit_code
DECL|member|bit_length
struct|struct
name|g3code
block|{
name|int
name|nr_bits
decl_stmt|,
name|nr_pels
decl_stmt|,
name|bit_code
decl_stmt|,
name|bit_length
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* tables for makeup / terminal codes white / black, extended m_codes */
end_comment

begin_decl_stmt
specifier|extern
name|struct
name|g3code
name|t_white
index|[]
decl_stmt|,
name|m_white
index|[]
decl_stmt|,
name|t_black
index|[]
decl_stmt|,
name|m_black
index|[]
decl_stmt|,
name|m_ext
index|[]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* The number of bits looked up simultaneously determines the amount  * of memory used by the program - some values:  * 10 bits : 87 Kbytes, 8 bits : 20 Kbytes  *  5 bits :  6 Kbytes, 1 bit  :  4 Kbytes  * - naturally, using less bits is also slower...  */
end_comment

begin_comment
comment|/* #define FBITS 5 #define BITM 0x1f */
end_comment

begin_define
DECL|macro|FBITS
define|#
directive|define
name|FBITS
value|8
end_define

begin_define
DECL|macro|BITM
define|#
directive|define
name|BITM
value|0xff
end_define

begin_comment
comment|/* #define FBITS 12 #define BITM 0xfff */
end_comment

begin_define
DECL|macro|BITN
define|#
directive|define
name|BITN
value|1<<FBITS
end_define

begin_struct
DECL|struct|g3_tree
DECL|member|nr_bits
struct|struct
name|g3_tree
block|{
name|int
name|nr_bits
decl_stmt|;
DECL|member|nextb
name|struct
name|g3_tree
modifier|*
name|nextb
index|[
name|BITN
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|g3_leaf
define|#
directive|define
name|g3_leaf
value|g3code
end_define

begin_function_decl
specifier|extern
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
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
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
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG
end_ifdef

begin_function_decl
specifier|extern
name|void
name|print_g3_tree
parameter_list|(
name|char
modifier|*
name|t
parameter_list|,
name|struct
name|g3_tree
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|extern
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
function_decl|;
end_function_decl

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__MARCHING_ANTS_H__
end_ifndef

begin_define
DECL|macro|__MARCHING_ANTS_H__
define|#
directive|define
name|__MARCHING_ANTS_H__
end_define

begin_comment
comment|/* static variable definitions */
end_comment

begin_decl_stmt
DECL|variable|ant_data
specifier|static
name|unsigned
name|char
name|ant_data
index|[
literal|8
index|]
index|[
literal|8
index|]
init|=
block|{
block|{
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
block|}
block|,
block|{
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
literal|0xF0
block|,
comment|/*  ####----  */
block|}
block|,
block|{
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
block|}
block|,
block|{
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
block|}
block|,
block|{
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
block|}
block|,
block|{
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
block|}
block|,
block|{
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
block|}
block|,
block|{
literal|0x78
block|,
comment|/*  -####---  */
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __MARCHING_ANTS_H__  */
end_comment

end_unit


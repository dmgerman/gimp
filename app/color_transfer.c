begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

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
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"color_transfer.h"
end_include

begin_define
DECL|macro|SQR (x)
define|#
directive|define
name|SQR
parameter_list|(
name|x
parameter_list|)
value|((x) * (x))
end_define

begin_comment
comment|/*  for lightening  */
end_comment

begin_decl_stmt
DECL|variable|highlights_add
name|double
name|highlights_add
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|midtones_add
name|double
name|midtones_add
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shadows_add
name|double
name|shadows_add
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  for darkening  */
end_comment

begin_decl_stmt
DECL|variable|highlights_sub
name|double
name|highlights_sub
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|midtones_sub
name|double
name|midtones_sub
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shadows_sub
name|double
name|shadows_sub
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  color transfer functions  */
end_comment

begin_function
name|void
DECL|function|color_transfer_init ()
name|color_transfer_init
parameter_list|()
block|{
name|int
name|i
decl_stmt|;
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
block|{
name|highlights_add
index|[
name|i
index|]
operator|=
name|shadows_sub
index|[
literal|255
operator|-
name|i
index|]
operator|=
operator|(
literal|1.075
operator|-
literal|1
operator|/
operator|(
operator|(
name|double
operator|)
name|i
operator|/
literal|16.0
operator|+
literal|1
operator|)
operator|)
expr_stmt|;
name|midtones_add
index|[
name|i
index|]
operator|=
name|midtones_sub
index|[
name|i
index|]
operator|=
literal|0.667
operator|*
operator|(
literal|1
operator|-
name|SQR
argument_list|(
operator|(
operator|(
name|double
operator|)
name|i
operator|-
literal|127.0
operator|)
operator|/
literal|127.0
argument_list|)
operator|)
expr_stmt|;
name|shadows_add
index|[
name|i
index|]
operator|=
name|highlights_sub
index|[
name|i
index|]
operator|=
literal|0.667
operator|*
operator|(
literal|1
operator|-
name|SQR
argument_list|(
operator|(
operator|(
name|double
operator|)
name|i
operator|-
literal|127.0
operator|)
operator|/
literal|127.0
argument_list|)
operator|)
expr_stmt|;
block|}
block|}
end_function

end_unit


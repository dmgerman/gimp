begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_function
DECL|function|pfix (int n)
specifier|static
name|int
name|pfix
parameter_list|(
name|int
name|n
parameter_list|)
block|{
if|if
condition|(
name|n
operator|<
literal|1
condition|)
return|return
literal|1
return|;
if|if
condition|(
name|n
operator|>
literal|255
condition|)
return|return
literal|255
return|;
return|return
name|n
return|;
block|}
end_function

begin_define
DECL|macro|PIXEL (y,x,z)
define|#
directive|define
name|PIXEL
parameter_list|(
name|y
parameter_list|,
name|x
parameter_list|,
name|z
parameter_list|)
value|p->col[(y)*rowstride+(x)*3+z]
end_define

begin_function
DECL|function|mkplasma_sub (ppm_t * p,int x1,int x2,int y1,int y2,float turb)
specifier|static
name|void
name|mkplasma_sub
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|,
name|int
name|x1
parameter_list|,
name|int
name|x2
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|y2
parameter_list|,
name|float
name|turb
parameter_list|)
block|{
name|int
name|rowstride
init|=
name|p
operator|->
name|width
operator|*
literal|3
decl_stmt|;
name|int
name|r
init|=
literal|0
decl_stmt|;
name|int
name|xr
decl_stmt|,
name|yr
decl_stmt|,
name|nx
decl_stmt|,
name|ny
decl_stmt|;
name|xr
operator|=
name|abs
argument_list|(
name|x1
operator|-
name|x2
argument_list|)
expr_stmt|;
name|yr
operator|=
name|abs
argument_list|(
name|y1
operator|-
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|xr
operator|==
literal|0
operator|)
operator|&&
operator|(
name|yr
operator|==
literal|0
operator|)
condition|)
return|return;
name|nx
operator|=
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2
expr_stmt|;
name|ny
operator|=
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
operator|!
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|nx
argument_list|,
name|r
argument_list|)
condition|)
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|nx
argument_list|,
name|r
argument_list|)
operator|=
name|pfix
argument_list|(
operator|(
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
operator|+
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
operator|)
operator|/
literal|2.0
operator|+
name|turb
operator|*
name|g_rand_double_range
argument_list|(
name|gr
argument_list|,
operator|-
name|xr
operator|/
literal|2.0
argument_list|,
name|xr
operator|/
literal|2.0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|nx
argument_list|,
name|r
argument_list|)
condition|)
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|nx
argument_list|,
name|r
argument_list|)
operator|=
name|pfix
argument_list|(
operator|(
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
operator|+
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
operator|)
operator|/
literal|2.0
operator|+
name|turb
operator|*
name|g_rand_double_range
argument_list|(
name|gr
argument_list|,
operator|-
name|xr
operator|/
literal|2.0
argument_list|,
name|xr
operator|/
literal|2.0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|PIXEL
argument_list|(
name|ny
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
condition|)
name|PIXEL
argument_list|(
name|ny
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
operator|=
name|pfix
argument_list|(
operator|(
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
operator|+
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
operator|)
operator|/
literal|2.0
operator|+
name|turb
operator|*
name|g_rand_double_range
argument_list|(
name|gr
argument_list|,
operator|-
name|yr
operator|/
literal|2.0
argument_list|,
name|yr
operator|/
literal|2.0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|PIXEL
argument_list|(
name|ny
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
condition|)
name|PIXEL
argument_list|(
name|ny
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
operator|=
name|pfix
argument_list|(
operator|(
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
operator|+
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
operator|)
operator|/
literal|2.0
operator|+
name|turb
operator|*
name|g_rand_double_range
argument_list|(
name|gr
argument_list|,
operator|-
name|yr
operator|/
literal|2.0
argument_list|,
name|yr
operator|/
literal|2.0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|PIXEL
argument_list|(
name|ny
argument_list|,
name|nx
argument_list|,
name|r
argument_list|)
condition|)
name|PIXEL
argument_list|(
name|ny
argument_list|,
name|nx
argument_list|,
name|r
argument_list|)
operator|=
name|pfix
argument_list|(
operator|(
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
operator|+
name|PIXEL
argument_list|(
name|y1
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
operator|+
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|x1
argument_list|,
name|r
argument_list|)
operator|+
name|PIXEL
argument_list|(
name|y2
argument_list|,
name|x2
argument_list|,
name|r
argument_list|)
operator|)
operator|/
literal|4.0
operator|+
name|turb
operator|*
name|g_rand_double_range
argument_list|(
name|gr
argument_list|,
operator|-
operator|(
name|xr
operator|+
name|yr
operator|)
operator|/
literal|4.0
argument_list|,
operator|(
name|xr
operator|+
name|yr
operator|)
operator|/
literal|4.0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|xr
operator|>
literal|1
condition|)
block|{
name|mkplasma_sub
argument_list|(
name|p
argument_list|,
name|x1
argument_list|,
name|nx
argument_list|,
name|y1
argument_list|,
name|ny
argument_list|,
name|turb
argument_list|)
expr_stmt|;
name|mkplasma_sub
argument_list|(
name|p
argument_list|,
name|nx
argument_list|,
name|x2
argument_list|,
name|y1
argument_list|,
name|ny
argument_list|,
name|turb
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|yr
operator|>
literal|1
condition|)
block|{
name|mkplasma_sub
argument_list|(
name|p
argument_list|,
name|x1
argument_list|,
name|nx
argument_list|,
name|ny
argument_list|,
name|y2
argument_list|,
name|turb
argument_list|)
expr_stmt|;
name|mkplasma_sub
argument_list|(
name|p
argument_list|,
name|nx
argument_list|,
name|x2
argument_list|,
name|ny
argument_list|,
name|y2
argument_list|,
name|turb
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|mkplasma_red (ppm_t * p,float turb)
specifier|static
name|void
name|mkplasma_red
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|,
name|float
name|turb
parameter_list|)
block|{
name|int
name|x
init|=
literal|0
decl_stmt|,
name|y
init|=
literal|0
decl_stmt|;
name|int
name|rowstride
init|=
name|p
operator|->
name|width
operator|*
literal|3
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|p
operator|->
name|width
condition|;
name|x
operator|++
control|)
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|p
operator|->
name|height
condition|;
name|y
operator|++
control|)
name|PIXEL
argument_list|(
name|y
argument_list|,
name|x
argument_list|,
literal|0
argument_list|)
operator|=
literal|0
expr_stmt|;
name|x
operator|--
expr_stmt|;
name|y
operator|--
expr_stmt|;
name|PIXEL
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
operator|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|1
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|PIXEL
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
operator|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|1
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|PIXEL
argument_list|(
literal|0
argument_list|,
name|x
argument_list|,
literal|0
argument_list|)
operator|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|1
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|PIXEL
argument_list|(
name|y
argument_list|,
name|x
argument_list|,
literal|0
argument_list|)
operator|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
literal|1
argument_list|,
literal|256
argument_list|)
expr_stmt|;
name|mkplasma_sub
argument_list|(
name|p
argument_list|,
literal|0
argument_list|,
name|x
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|turb
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|mkgrayplasma (ppm_t * p,float turb)
name|void
name|mkgrayplasma
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|,
name|float
name|turb
parameter_list|)
block|{
name|int
name|y
decl_stmt|,
name|l
decl_stmt|;
name|mkplasma_red
argument_list|(
name|p
argument_list|,
name|turb
argument_list|)
expr_stmt|;
name|l
operator|=
name|p
operator|->
name|width
operator|*
literal|3
operator|*
name|p
operator|->
name|height
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|l
condition|;
name|y
operator|+=
literal|3
control|)
name|p
operator|->
name|col
index|[
name|y
operator|+
literal|1
index|]
operator|=
name|p
operator|->
name|col
index|[
name|y
operator|+
literal|2
index|]
operator|=
name|p
operator|->
name|col
index|[
name|y
index|]
expr_stmt|;
block|}
end_function

end_unit


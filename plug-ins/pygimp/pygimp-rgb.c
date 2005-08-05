begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_define
DECL|macro|NO_IMPORT_PYGOBJECT
define|#
directive|define
name|NO_IMPORT_PYGOBJECT
end_define

begin_include
include|#
directive|include
file|"pygimpcolor.h"
end_include

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_set (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_set
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|PyObject
modifier|*
name|r
init|=
name|NULL
decl_stmt|,
modifier|*
name|g
init|=
name|NULL
decl_stmt|,
modifier|*
name|b
init|=
name|NULL
decl_stmt|,
modifier|*
name|a
init|=
name|NULL
decl_stmt|;
name|GimpRGB
name|tmprgb
decl_stmt|,
modifier|*
name|rgb
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"r"
block|,
literal|"g"
block|,
literal|"b"
block|,
literal|"a"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"|OOOO:set"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
operator|!
name|r
operator|&&
operator|!
name|g
operator|&&
operator|!
name|b
operator|&&
operator|!
name|a
condition|)
block|{
name|PyErr_SetString
argument_list|(
name|PyExc_TypeError
argument_list|,
literal|"must provide r,g,b or a arguments"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
operator|(
name|r
operator|&&
operator|(
operator|!
name|g
operator|||
operator|!
name|b
operator|)
operator|)
operator|||
operator|(
name|g
operator|&&
operator|(
operator|!
name|r
operator|||
operator|!
name|b
operator|)
operator|)
operator|||
operator|(
name|b
operator|&&
operator|(
operator|!
name|r
operator|||
operator|!
name|g
operator|)
operator|)
condition|)
block|{
name|PyErr_SetString
argument_list|(
name|PyExc_TypeError
argument_list|,
literal|"must provide all 3 r,g,b arguments"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|rgb
operator|=
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
expr_stmt|;
name|tmprgb
operator|=
operator|*
name|rgb
expr_stmt|;
DECL|macro|SET_MEMBER (m)
define|#
directive|define
name|SET_MEMBER
parameter_list|(
name|m
parameter_list|)
value|G_STMT_START {				\     if (PyInt_Check(m))						\ 	tmprgb.m = (double) PyInt_AS_LONG(m) / 255.0;		\     else if (PyFloat_Check(m))					\         tmprgb.m = PyFloat_AS_DOUBLE(m);			\     else {							\ 	PyErr_SetString(PyExc_TypeError,			\ 			#m " must be an int or a float");	\ 	return NULL;						\     }								\ } G_STMT_END
if|if
condition|(
name|r
condition|)
block|{
name|SET_MEMBER
argument_list|(
name|r
argument_list|)
expr_stmt|;
name|SET_MEMBER
argument_list|(
name|g
argument_list|)
expr_stmt|;
name|SET_MEMBER
argument_list|(
name|b
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|a
condition|)
name|SET_MEMBER
argument_list|(
name|a
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_MEMBER
operator|*
name|rgb
operator|=
name|tmprgb
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_set_alpha (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_set_alpha
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|PyObject
modifier|*
name|py_a
decl_stmt|;
name|GimpRGB
modifier|*
name|rgb
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"a"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"O:set_alpha"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|py_a
argument_list|)
condition|)
return|return
name|NULL
return|;
name|rgb
operator|=
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
expr_stmt|;
if|if
condition|(
name|PyInt_Check
argument_list|(
name|py_a
argument_list|)
condition|)
name|rgb
operator|->
name|a
operator|=
operator|(
name|double
operator|)
name|PyInt_AS_LONG
argument_list|(
name|py_a
argument_list|)
operator|/
literal|255.0
expr_stmt|;
elseif|else
if|if
condition|(
name|PyFloat_Check
argument_list|(
name|py_a
argument_list|)
condition|)
name|rgb
operator|->
name|a
operator|=
name|PyFloat_AS_DOUBLE
argument_list|(
name|py_a
argument_list|)
expr_stmt|;
else|else
block|{
name|PyErr_SetString
argument_list|(
name|PyExc_TypeError
argument_list|,
literal|"a must be an int or a float"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_add (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_add
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|PyObject
modifier|*
name|color
decl_stmt|;
name|gboolean
name|with_alpha
init|=
name|FALSE
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"color"
block|,
literal|"with_alpha"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"O!|i:add"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|PyGimpRGB_Type
argument_list|,
operator|&
name|color
argument_list|,
operator|&
name|with_alpha
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|with_alpha
condition|)
name|gimp_rgba_add
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|pyg_boxed_get
argument_list|(
name|color
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_rgb_add
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|pyg_boxed_get
argument_list|(
name|color
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_subtract (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_subtract
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|PyObject
modifier|*
name|color
decl_stmt|;
name|gboolean
name|with_alpha
init|=
name|FALSE
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"color"
block|,
literal|"with_alpha"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"O!|i:subtract"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|PyGimpRGB_Type
argument_list|,
operator|&
name|color
argument_list|,
operator|&
name|with_alpha
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|with_alpha
condition|)
name|gimp_rgba_subtract
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|pyg_boxed_get
argument_list|(
name|color
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_rgb_subtract
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|pyg_boxed_get
argument_list|(
name|color
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_multiply (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_multiply
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|double
name|factor
decl_stmt|;
name|gboolean
name|with_alpha
init|=
name|FALSE
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"factor"
block|,
literal|"with_alpha"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"d|i:multiply"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|factor
argument_list|,
operator|&
name|with_alpha
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|with_alpha
condition|)
name|gimp_rgba_multiply
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|factor
argument_list|)
expr_stmt|;
else|else
name|gimp_rgb_multiply
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|factor
argument_list|)
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_distance (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_distance
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|PyObject
modifier|*
name|color
decl_stmt|;
name|gboolean
name|alpha
init|=
name|FALSE
decl_stmt|;
name|double
name|ret
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"color"
block|,
literal|"alpha"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"O!|i:distance"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|PyGimpRGB_Type
argument_list|,
operator|&
name|color
argument_list|,
operator|&
name|alpha
argument_list|)
condition|)
return|return
name|NULL
return|;
name|ret
operator|=
name|gimp_rgb_distance
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|pyg_boxed_get
argument_list|(
name|color
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|PyFloat_FromDouble
argument_list|(
name|ret
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_max (PyObject * self)
name|rgb_max
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|)
block|{
return|return
name|PyFloat_FromDouble
argument_list|(
name|gimp_rgb_max
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_min (PyObject * self)
name|rgb_min
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|)
block|{
return|return
name|PyFloat_FromDouble
argument_list|(
name|gimp_rgb_min
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_clamp (PyObject * self)
name|rgb_clamp
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|)
block|{
name|gimp_rgb_clamp
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_gamma (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_gamma
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|double
name|gamma
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"gamma"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"d:gamma"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|gamma
argument_list|)
condition|)
return|return
name|NULL
return|;
name|gimp_rgb_gamma
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|gamma
argument_list|)
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_luminance (PyObject * self)
name|rgb_luminance
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|)
block|{
return|return
name|PyFloat_FromDouble
argument_list|(
name|gimp_rgb_luminance
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_composite (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_composite
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|PyObject
modifier|*
name|color
decl_stmt|;
name|int
name|mode
init|=
name|GIMP_RGB_COMPOSITE_NORMAL
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"color"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"O!|i:composite"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|PyGimpRGB_Type
argument_list|,
operator|&
name|color
argument_list|,
operator|&
name|mode
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|mode
operator|<
name|GIMP_RGB_COMPOSITE_NONE
operator|||
name|mode
operator|>
name|GIMP_RGB_COMPOSITE_BEHIND
condition|)
block|{
name|PyErr_SetString
argument_list|(
name|PyExc_TypeError
argument_list|,
literal|"composite type is not valid"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gimp_rgb_composite
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|pyg_boxed_get
argument_list|(
name|color
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_parse_name (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_parse_name
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|char
modifier|*
name|name
decl_stmt|;
name|int
name|len
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"name"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"s#:parse_name"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|name
argument_list|,
operator|&
name|len
argument_list|)
condition|)
return|return
name|NULL
return|;
name|success
operator|=
name|gimp_rgb_parse_name
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|name
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|PyMem_Free
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
block|{
name|PyErr_SetString
argument_list|(
name|PyExc_ValueError
argument_list|,
literal|"unable to parse color name"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_parse_hex (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_parse_hex
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|char
modifier|*
name|hex
decl_stmt|;
name|int
name|len
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"hex"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"s#:parse_hex"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|hex
argument_list|,
operator|&
name|len
argument_list|)
condition|)
return|return
name|NULL
return|;
name|success
operator|=
name|gimp_rgb_parse_hex
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|hex
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|PyMem_Free
argument_list|(
name|hex
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
block|{
name|PyErr_SetString
argument_list|(
name|PyExc_ValueError
argument_list|,
literal|"unable to parse hex value"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_parse_css (PyObject * self,PyObject * args,PyObject * kwargs)
name|rgb_parse_css
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|char
modifier|*
name|css
decl_stmt|;
name|int
name|len
decl_stmt|;
name|gboolean
name|success
decl_stmt|,
name|with_alpha
init|=
name|FALSE
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"css"
block|,
literal|"with_alpha"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"s#|i:parse_css"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|css
argument_list|,
operator|&
name|len
argument_list|,
operator|&
name|with_alpha
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|with_alpha
condition|)
name|success
operator|=
name|gimp_rgba_parse_css
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|css
argument_list|,
name|len
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|gimp_rgb_parse_css
argument_list|(
name|pyg_boxed_get
argument_list|(
name|self
argument_list|,
name|GimpRGB
argument_list|)
argument_list|,
name|css
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|PyMem_Free
argument_list|(
name|css
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
block|{
name|PyErr_SetString
argument_list|(
name|PyExc_ValueError
argument_list|,
literal|"unable to parse CSS color"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|rgb_methods
specifier|static
name|PyMethodDef
name|rgb_methods
index|[]
init|=
block|{
block|{
literal|"set"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_set
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"set_alpha"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_set_alpha
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"add"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_add
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"subtract"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_subtract
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"multiply"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_multiply
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"distance"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_distance
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"max"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_max
block|,
name|METH_NOARGS
block|}
block|,
block|{
literal|"min"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_min
block|,
name|METH_NOARGS
block|}
block|,
block|{
literal|"clamp"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_clamp
block|,
name|METH_NOARGS
block|}
block|,
block|{
literal|"gamma"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_gamma
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"luminance"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_luminance
block|,
name|METH_NOARGS
block|}
block|,
block|{
literal|"composite"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_composite
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"parse_name"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_parse_name
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"parse_hex"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_parse_hex
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"parse_css"
block|,
operator|(
name|PyCFunction
operator|)
name|rgb_parse_css
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|MEMBER_ACCESSOR (m)
define|#
directive|define
name|MEMBER_ACCESSOR
parameter_list|(
name|m
parameter_list|)
define|\
value|static PyObject *							\ rgb_get_ ## m(PyObject *self, void *closure)				\ {									\     return PyFloat_FromDouble(pyg_boxed_get(self, GimpRGB)->m);		\ }									\ static int								\ rgb_set_ ## m(PyObject *self, PyObject *value, void *closure)		\ {									\     GimpRGB *rgb = pyg_boxed_get(self, GimpRGB);			\     if (value == NULL) {						\ 	PyErr_SetString(PyExc_TypeError, "cannot delete value");	\ 	return -1;							\     }									\     else if (PyInt_Check(value))					\ 	rgb->m = (double) PyInt_AS_LONG(value) / 255.0;			\     else if (PyFloat_Check(value))					\         rgb->m = PyFloat_AS_DOUBLE(value);				\     else {								\ 	PyErr_SetString(PyExc_TypeError, "type mismatch");		\ 	return -1;							\     }									\     return 0;								\ }
end_define

begin_expr_stmt
name|MEMBER_ACCESSOR
argument_list|(
name|r
argument_list|)
expr_stmt|;
end_expr_stmt

begin_expr_stmt
name|MEMBER_ACCESSOR
argument_list|(
name|g
argument_list|)
expr_stmt|;
end_expr_stmt

begin_expr_stmt
name|MEMBER_ACCESSOR
argument_list|(
name|b
argument_list|)
expr_stmt|;
end_expr_stmt

begin_expr_stmt
name|MEMBER_ACCESSOR
argument_list|(
name|a
argument_list|)
expr_stmt|;
end_expr_stmt

begin_undef
undef|#
directive|undef
name|MEMBER_ACCESSOR
end_undef

begin_decl_stmt
DECL|variable|rgb_getsets
specifier|static
name|PyGetSetDef
name|rgb_getsets
index|[]
init|=
block|{
block|{
literal|"r"
block|,
operator|(
name|getter
operator|)
name|rgb_get_r
block|,
operator|(
name|setter
operator|)
name|rgb_set_r
block|}
block|,
block|{
literal|"g"
block|,
operator|(
name|getter
operator|)
name|rgb_get_g
block|,
operator|(
name|setter
operator|)
name|rgb_set_g
block|}
block|,
block|{
literal|"b"
block|,
operator|(
name|getter
operator|)
name|rgb_get_b
block|,
operator|(
name|setter
operator|)
name|rgb_set_b
block|}
block|,
block|{
literal|"a"
block|,
operator|(
name|getter
operator|)
name|rgb_get_a
block|,
operator|(
name|setter
operator|)
name|rgb_set_a
block|}
block|,
block|{
literal|"red"
block|,
operator|(
name|getter
operator|)
name|rgb_get_r
block|,
operator|(
name|setter
operator|)
name|rgb_set_r
block|}
block|,
block|{
literal|"green"
block|,
operator|(
name|getter
operator|)
name|rgb_get_g
block|,
operator|(
name|setter
operator|)
name|rgb_set_g
block|}
block|,
block|{
literal|"blue"
block|,
operator|(
name|getter
operator|)
name|rgb_get_b
block|,
operator|(
name|setter
operator|)
name|rgb_set_b
block|}
block|,
block|{
literal|"alpha"
block|,
operator|(
name|getter
operator|)
name|rgb_get_a
block|,
operator|(
name|setter
operator|)
name|rgb_set_a
block|}
block|,
block|{
name|NULL
block|,
operator|(
name|getter
operator|)
literal|0
block|,
operator|(
name|setter
operator|)
literal|0
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|rgb_init (PyGBoxed * self,PyObject * args,PyObject * kwargs)
name|rgb_init
parameter_list|(
name|PyGBoxed
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
name|PyObject
modifier|*
name|r
decl_stmt|,
modifier|*
name|g
decl_stmt|,
modifier|*
name|b
decl_stmt|,
modifier|*
name|a
init|=
name|NULL
decl_stmt|;
name|GimpRGB
name|rgb
decl_stmt|;
specifier|static
name|char
modifier|*
name|kwlist
index|[]
init|=
block|{
literal|"r"
block|,
literal|"g"
block|,
literal|"b"
block|,
literal|"a"
block|,
name|NULL
block|}
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTupleAndKeywords
argument_list|(
name|args
argument_list|,
name|kwargs
argument_list|,
literal|"OOO|O:set"
argument_list|,
name|kwlist
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
condition|)
return|return
name|NULL
return|;
DECL|macro|SET_MEMBER (m)
define|#
directive|define
name|SET_MEMBER
parameter_list|(
name|m
parameter_list|)
value|G_STMT_START {				\     if (PyInt_Check(m))						\ 	rgb.m = (double) PyInt_AS_LONG(m) / 255.0;		\     else if (PyFloat_Check(m))					\         rgb.m = PyFloat_AS_DOUBLE(m);				\     else {							\ 	PyErr_SetString(PyExc_TypeError,			\ 			#m " must be an int or a float");	\ 	return NULL;						\     }								\ } G_STMT_END
name|SET_MEMBER
argument_list|(
name|r
argument_list|)
expr_stmt|;
name|SET_MEMBER
argument_list|(
name|g
argument_list|)
expr_stmt|;
name|SET_MEMBER
argument_list|(
name|b
argument_list|)
expr_stmt|;
if|if
condition|(
name|a
condition|)
name|SET_MEMBER
argument_list|(
name|a
argument_list|)
expr_stmt|;
else|else
name|rgb
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
undef|#
directive|undef
name|SET_MEMBER
name|self
operator|->
name|gtype
operator|=
name|GIMP_TYPE_RGB
expr_stmt|;
name|self
operator|->
name|free_on_dealloc
operator|=
name|TRUE
expr_stmt|;
name|self
operator|->
name|boxed
operator|=
name|g_boxed_copy
argument_list|(
name|GIMP_TYPE_RGB
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|PyGimpRGB_Type
name|PyTypeObject
name|PyGimpRGB_Type
init|=
block|{
name|PyObject_HEAD_INIT
argument_list|(
name|NULL
argument_list|)
literal|0
block|,
comment|/* ob_size */
literal|"gimpcolor.RGB"
block|,
comment|/* tp_name */
sizeof|sizeof
argument_list|(
name|PyGBoxed
argument_list|)
block|,
comment|/* tp_basicsize */
literal|0
block|,
comment|/* tp_itemsize */
comment|/* methods */
operator|(
name|destructor
operator|)
literal|0
block|,
comment|/* tp_dealloc */
operator|(
name|printfunc
operator|)
literal|0
block|,
comment|/* tp_print */
operator|(
name|getattrfunc
operator|)
literal|0
block|,
comment|/* tp_getattr */
operator|(
name|setattrfunc
operator|)
literal|0
block|,
comment|/* tp_setattr */
operator|(
name|cmpfunc
operator|)
literal|0
block|,
comment|/* tp_compare */
operator|(
name|reprfunc
operator|)
literal|0
block|,
comment|/* tp_repr */
operator|(
name|PyNumberMethods
operator|*
operator|)
literal|0
block|,
comment|/* tp_as_number */
operator|(
name|PySequenceMethods
operator|*
operator|)
literal|0
block|,
comment|/* tp_as_sequence */
operator|(
name|PyMappingMethods
operator|*
operator|)
literal|0
block|,
comment|/* tp_as_mapping */
operator|(
name|hashfunc
operator|)
literal|0
block|,
comment|/* tp_hash */
operator|(
name|ternaryfunc
operator|)
literal|0
block|,
comment|/* tp_call */
operator|(
name|reprfunc
operator|)
literal|0
block|,
comment|/* tp_repr */
operator|(
name|getattrofunc
operator|)
literal|0
block|,
comment|/* tp_getattro */
operator|(
name|setattrofunc
operator|)
literal|0
block|,
comment|/* tp_setattro */
operator|(
name|PyBufferProcs
operator|*
operator|)
literal|0
block|,
comment|/* tp_as_buffer */
name|Py_TPFLAGS_DEFAULT
block|,
comment|/* tp_flags */
name|NULL
block|,
comment|/* Documentation string */
operator|(
name|traverseproc
operator|)
literal|0
block|,
comment|/* tp_traverse */
operator|(
name|inquiry
operator|)
literal|0
block|,
comment|/* tp_clear */
operator|(
name|richcmpfunc
operator|)
literal|0
block|,
comment|/* tp_richcompare */
literal|0
block|,
comment|/* tp_weaklistoffset */
operator|(
name|getiterfunc
operator|)
literal|0
block|,
comment|/* tp_iter */
operator|(
name|iternextfunc
operator|)
literal|0
block|,
comment|/* tp_iternext */
name|rgb_methods
block|,
comment|/* tp_methods */
literal|0
block|,
comment|/* tp_members */
name|rgb_getsets
block|,
comment|/* tp_getset */
name|NULL
block|,
comment|/* tp_base */
name|NULL
block|,
comment|/* tp_dict */
operator|(
name|descrgetfunc
operator|)
literal|0
block|,
comment|/* tp_descr_get */
operator|(
name|descrsetfunc
operator|)
literal|0
block|,
comment|/* tp_descr_set */
literal|0
block|,
comment|/* tp_dictoffset */
operator|(
name|initproc
operator|)
name|rgb_init
block|,
comment|/* tp_init */
operator|(
name|allocfunc
operator|)
literal|0
block|,
comment|/* tp_alloc */
operator|(
name|newfunc
operator|)
literal|0
block|,
comment|/* tp_new */
operator|(
name|freefunc
operator|)
literal|0
block|,
comment|/* tp_free */
operator|(
name|inquiry
operator|)
literal|0
comment|/* tp_is_gc */
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|PyObject
modifier|*
DECL|function|pygimp_rgb_new (GimpRGB * rgb)
name|pygimp_rgb_new
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
block|{
return|return
name|pyg_boxed_new
argument_list|(
name|GIMP_TYPE_RGB
argument_list|,
name|rgb
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

end_unit


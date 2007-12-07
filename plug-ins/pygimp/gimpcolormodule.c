begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 2005-2006  Manish Singh<yosh@gimp.org>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA     02111-1307, USA.  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|<config.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"pygimpcolor.h"
end_include

begin_define
DECL|macro|_INSIDE_PYGIMPCOLOR_
define|#
directive|define
name|_INSIDE_PYGIMPCOLOR_
end_define

begin_include
include|#
directive|include
file|"pygimpcolor-api.h"
end_include

begin_include
include|#
directive|include
file|"pygimp-util.h"
end_include

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|pygimp_rgb_parse_name (PyObject * self,PyObject * args,PyObject * kwargs)
name|pygimp_rgb_parse_name
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
name|GimpRGB
name|rgb
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
literal|"s#:rgb_parse_name"
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
name|rgb
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
name|success
operator|=
name|gimp_rgb_parse_name
argument_list|(
operator|&
name|rgb
argument_list|,
name|name
argument_list|,
name|len
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
return|return
name|pygimp_rgb_new
argument_list|(
operator|&
name|rgb
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|pygimp_rgb_parse_hex (PyObject * self,PyObject * args,PyObject * kwargs)
name|pygimp_rgb_parse_hex
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
name|GimpRGB
name|rgb
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
literal|"s#:rgb_parse_hex"
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
name|rgb
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
name|success
operator|=
name|gimp_rgb_parse_hex
argument_list|(
operator|&
name|rgb
argument_list|,
name|hex
argument_list|,
name|len
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
return|return
name|pygimp_rgb_new
argument_list|(
operator|&
name|rgb
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|pygimp_rgb_parse_css (PyObject * self,PyObject * args,PyObject * kwargs)
name|pygimp_rgb_parse_css
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
name|GimpRGB
name|rgb
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
literal|"s#|i:rgb_parse_css"
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
operator|&
name|rgb
argument_list|,
name|css
argument_list|,
name|len
argument_list|)
expr_stmt|;
else|else
block|{
name|rgb
operator|.
name|a
operator|=
literal|1.0
expr_stmt|;
name|success
operator|=
name|gimp_rgb_parse_css
argument_list|(
operator|&
name|rgb
argument_list|,
name|css
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
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
return|return
name|pygimp_rgb_new
argument_list|(
operator|&
name|rgb
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|pygimp_rgb_list_names (PyObject * self)
name|pygimp_rgb_list_names
parameter_list|(
name|PyObject
modifier|*
name|self
parameter_list|)
block|{
name|int
name|num_names
decl_stmt|,
name|i
decl_stmt|;
specifier|const
name|char
modifier|*
modifier|*
name|names
decl_stmt|;
name|GimpRGB
modifier|*
name|colors
decl_stmt|;
name|PyObject
modifier|*
name|dict
decl_stmt|,
modifier|*
name|color
decl_stmt|;
name|num_names
operator|=
name|gimp_rgb_list_names
argument_list|(
operator|&
name|names
argument_list|,
operator|&
name|colors
argument_list|)
expr_stmt|;
name|dict
operator|=
name|PyDict_New
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|dict
condition|)
goto|goto
name|cleanup
goto|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_names
condition|;
name|i
operator|++
control|)
block|{
name|color
operator|=
name|pygimp_rgb_new
argument_list|(
operator|&
name|colors
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color
condition|)
goto|goto
name|bail
goto|;
if|if
condition|(
name|PyDict_SetItemString
argument_list|(
name|dict
argument_list|,
name|names
index|[
name|i
index|]
argument_list|,
name|color
argument_list|)
operator|<
literal|0
condition|)
block|{
name|Py_DECREF
argument_list|(
name|color
argument_list|)
expr_stmt|;
goto|goto
name|bail
goto|;
block|}
name|Py_DECREF
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
goto|goto
name|cleanup
goto|;
name|bail
label|:
name|Py_DECREF
argument_list|(
name|dict
argument_list|)
expr_stmt|;
name|dict
operator|=
name|NULL
expr_stmt|;
name|cleanup
label|:
name|g_free
argument_list|(
name|names
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|colors
argument_list|)
expr_stmt|;
return|return
name|dict
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_define
unit|static PyObject * pygimp_bilinear(PyObject *self, PyObject *args, PyObject *kwargs) {     gdouble x, y;     gdouble values[4];     static char *kwlist[] = { "x", "y", "values", NULL };      if (!PyArg_ParseTupleAndKeywords(args, kwargs, 				     "dd(dddd):bilinear", kwlist,&x,&y,&values[0],&values[1],&values[2],&values[3]))   	return NULL;      return PyFloat_FromDouble(gimp_bilinear(x, y, values)); }  static PyObject * pygimp_bilinear_8(PyObject *self, PyObject *args, PyObject *kwargs) {     gdouble x, y;     char *values;     int len;     guchar r;     static char *kwlist[] = { "x", "y", "values", NULL };      if (!PyArg_ParseTupleAndKeywords(args, kwargs, 				     "dds#:bilinear_8", kwlist,&x,&y,&values,&len))   	return NULL;      if (len != 4) { 	PyErr_SetString(PyExc_ValueError, 			"string must be exactly 4 bytes long"); 	return NULL;     }      r = gimp_bilinear_8(x, y, values);      return PyString_FromStringAndSize(&r, 1); }  static PyObject * pygimp_bilinear_32(PyObject *self, PyObject *args, PyObject *kwargs) {     gdouble x, y;     guint32 values[4];     static char *kwlist[] = { "x", "y", "values", NULL };      if (!PyArg_ParseTupleAndKeywords(args, kwargs, 				     "dd(IIII):bilinear_32", 				     kwlist,&x,&y,&values[0],&values[1],&values[2],&values[3]))   	return NULL;      return PyInt_FromLong(gimp_bilinear_32(x, y, values)); }  static PyObject * pygimp_bilinear_pixels_8(PyObject *self, PyObject *args, PyObject *kwargs) {     Py_INCREF(Py_None);     return Py_None; }  typedef struct {     PyObject *func;     PyObject *data; } ProxyData;  static void proxy_render(gdouble x, gdouble y, GimpRGB *color, gpointer pdata) {     ProxyData *data = pdata;      if (data->data) 	PyObject_CallFunction(data->func, "ddO&O", x, y, pygimp_rgb_new, color, 			      data->data);     else 	PyObject_CallFunction(data->func, "ddO&", x, y, pygimp_rgb_new, color); }  static void proxy_put_pixel(gint x, gint y, GimpRGB *color, gpointer pdata) {     ProxyData *data = pdata;      if (data->data) 	PyObject_CallFunction(data->func, "iiO&O", x, y, pygimp_rgb_new, color, 			      data->data);     else 	PyObject_CallFunction(data->func, "iiO&", x, y, pygimp_rgb_new, color); }  static void proxy_progress(gint min, gint max, gint current, gpointer pdata) {     ProxyData *data = pdata;      if (data->data) 	PyObject_CallFunction(data->func, "iiiO", min, max, current, 			      data->data);     else 	PyObject_CallFunction(data->func, "iii", min, max, current); }  static PyObject * pygimp_adaptive_supersample_area(PyObject *self, PyObject *args, PyObject *kwargs) {     gulong r;      gint x1, y1, x2, y2, max_depth;     gdouble threshold;     PyObject *py_func_render = NULL, *py_data_render = NULL;     PyObject *py_func_put_pixel = NULL, *py_data_put_pixel = NULL;     PyObject *py_func_progress = NULL, *py_data_progress = NULL;      GimpRenderFunc proxy_func_render = NULL;     GimpPutPixelFunc proxy_func_put_pixel = NULL;     GimpProgressFunc proxy_func_progress = NULL;      ProxyData proxy_data_render, proxy_data_put_pixel, proxy_data_progress;      static char *kwlist[] = { 	"x1", "y1", "x2", "y2", "max_depth", "threshold", 	"render_func", "render_data",         "put_pixel_func", "put_pixel_data",         "progress_func", "progress_data",         NULL     };      if (!PyArg_ParseTupleAndKeywords(args, kwargs, 				     "iiiiid|OOOOOO" 				     ":adaptive_supersample_area", 				     kwlist,&x1,&y1,&x2,&y2,&max_depth,&threshold,&py_func_render,&py_data_render,&py_func_put_pixel,&py_data_put_pixel,&py_func_progress,&py_data_progress)) 	return NULL;
define|#
directive|define
name|PROCESS_FUNC
parameter_list|(
name|n
parameter_list|)
value|G_STMT_START {					\     if (py_func_##n != NULL) {						\         if (!PyCallable_Check(py_func_##n)) {				\ 	    PyErr_SetString(PyExc_TypeError, #n "_func "		\ 			    "must be callable");			\ 	    return NULL;						\ 	}								\ 									\ 	proxy_func_##n = proxy_##n;					\ 									\ 	proxy_data_##n.func = py_func_##n;				\ 	proxy_data_##n.data = py_data_##n;				\     }									\ } G_STMT_END
end_define

begin_undef
unit|PROCESS_FUNC(render);     PROCESS_FUNC(put_pixel);     PROCESS_FUNC(progress);
undef|#
directive|undef
name|PROCESS_FUNC
end_undef

begin_define
define|#
directive|define
name|PASS_FUNC
parameter_list|(
name|n
parameter_list|)
value|proxy_func_##n,&proxy_data_##n
end_define

begin_undef
unit|r = gimp_adaptive_supersample_area (x1, y1, x2, y2, max_depth, threshold, 					PASS_FUNC(render), 					PASS_FUNC(put_pixel), 					PASS_FUNC(progress));
undef|#
directive|undef
name|PASS_FUNC
end_undef

begin_endif
unit|return PyInt_FromLong(r); }
endif|#
directive|endif
end_endif

begin_comment
comment|/* List of methods defined in the module */
end_comment

begin_decl_stmt
DECL|variable|gimpcolor_methods
specifier|static
name|struct
name|PyMethodDef
name|gimpcolor_methods
index|[]
init|=
block|{
block|{
literal|"rgb_parse_name"
block|,
operator|(
name|PyCFunction
operator|)
name|pygimp_rgb_parse_name
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"rgb_parse_hex"
block|,
operator|(
name|PyCFunction
operator|)
name|pygimp_rgb_parse_hex
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"rgb_parse_css"
block|,
operator|(
name|PyCFunction
operator|)
name|pygimp_rgb_parse_css
block|,
name|METH_VARARGS
operator||
name|METH_KEYWORDS
block|}
block|,
block|{
literal|"rgb_names"
block|,
operator|(
name|PyCFunction
operator|)
name|pygimp_rgb_list_names
block|,
name|METH_NOARGS
block|}
block|,
if|#
directive|if
literal|0
block|{"bilinear", (PyCFunction)pygimp_bilinear, METH_VARARGS | METH_KEYWORDS},     {"bilinear_8", (PyCFunction)pygimp_bilinear_8, METH_VARARGS | METH_KEYWORDS},     {"bilinear_32", (PyCFunction)pygimp_bilinear_32, METH_VARARGS | METH_KEYWORDS},
comment|//{"bilinear_pixels_8", (PyCFunction)pygimp_bilinear_pixels_8, METH_VARARGS | METH_KEYWORDS},
block|{"adaptive_supersample_area", (PyCFunction)pygimp_adaptive_supersample_area, METH_VARARGS | METH_KEYWORDS},
endif|#
directive|endif
block|{
name|NULL
block|,
operator|(
name|PyCFunction
operator|)
name|NULL
block|,
literal|0
block|,
name|NULL
block|}
comment|/* sentinel */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pygimpcolor_api_functions
specifier|static
name|struct
name|_PyGimpColor_Functions
name|pygimpcolor_api_functions
init|=
block|{
operator|&
name|PyGimpRGB_Type
block|,
name|pygimp_rgb_new
block|,
operator|&
name|PyGimpHSV_Type
block|,
name|pygimp_hsv_new
block|,
operator|&
name|PyGimpHSL_Type
block|,
name|pygimp_hsl_new
block|,
operator|&
name|PyGimpCMYK_Type
block|,
name|pygimp_cmyk_new
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Initialization function for the module (*must* be called initgimpcolor) */
end_comment

begin_decl_stmt
DECL|variable|gimpcolor_doc
specifier|static
name|char
name|gimpcolor_doc
index|[]
init|=
literal|"This module provides interfaces to allow you to write gimp plugins"
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|initgimpcolor
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|PyMODINIT_FUNC
DECL|function|initgimpcolor (void)
name|initgimpcolor
parameter_list|(
name|void
parameter_list|)
block|{
name|PyObject
modifier|*
name|m
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|pygimp_init_pygobject
argument_list|()
expr_stmt|;
comment|/* Create the module and add the functions */
name|m
operator|=
name|Py_InitModule3
argument_list|(
literal|"gimpcolor"
argument_list|,
name|gimpcolor_methods
argument_list|,
name|gimpcolor_doc
argument_list|)
expr_stmt|;
name|d
operator|=
name|PyModule_GetDict
argument_list|(
name|m
argument_list|)
expr_stmt|;
name|pyg_register_boxed
argument_list|(
name|d
argument_list|,
literal|"RGB"
argument_list|,
name|GIMP_TYPE_RGB
argument_list|,
operator|&
name|PyGimpRGB_Type
argument_list|)
expr_stmt|;
name|pyg_register_boxed
argument_list|(
name|d
argument_list|,
literal|"HSV"
argument_list|,
name|GIMP_TYPE_HSV
argument_list|,
operator|&
name|PyGimpHSV_Type
argument_list|)
expr_stmt|;
name|pyg_register_boxed
argument_list|(
name|d
argument_list|,
literal|"HSL"
argument_list|,
name|GIMP_TYPE_HSL
argument_list|,
operator|&
name|PyGimpHSL_Type
argument_list|)
expr_stmt|;
name|pyg_register_boxed
argument_list|(
name|d
argument_list|,
literal|"CMYK"
argument_list|,
name|GIMP_TYPE_CMYK
argument_list|,
operator|&
name|PyGimpCMYK_Type
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"RGB_COMPOSITE_NONE"
argument_list|,
name|PyInt_FromLong
argument_list|(
name|GIMP_RGB_COMPOSITE_NONE
argument_list|)
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"RGB_COMPOSITE_NORMAL"
argument_list|,
name|PyInt_FromLong
argument_list|(
name|GIMP_RGB_COMPOSITE_NORMAL
argument_list|)
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"RGB_COMPOSITE_BEHIND"
argument_list|,
name|PyInt_FromLong
argument_list|(
name|GIMP_RGB_COMPOSITE_BEHIND
argument_list|)
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"RGB_LUMINANCE_RED"
argument_list|,
name|PyFloat_FromDouble
argument_list|(
name|GIMP_RGB_LUMINANCE_RED
argument_list|)
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"RGB_LUMINANCE_GREEN"
argument_list|,
name|PyFloat_FromDouble
argument_list|(
name|GIMP_RGB_LUMINANCE_GREEN
argument_list|)
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"RGB_LUMINANCE_BLUE"
argument_list|,
name|PyFloat_FromDouble
argument_list|(
name|GIMP_RGB_LUMINANCE_BLUE
argument_list|)
argument_list|)
expr_stmt|;
comment|/* for other modules */
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"_PyGimpColor_API"
argument_list|,
name|PyCObject_FromVoidPtr
argument_list|(
operator|&
name|pygimpcolor_api_functions
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Check for errors */
if|if
condition|(
name|PyErr_Occurred
argument_list|()
condition|)
name|Py_FatalError
argument_list|(
literal|"can't initialize module gimpcolor"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


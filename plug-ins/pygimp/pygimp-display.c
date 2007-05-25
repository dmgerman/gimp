begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 1997-2002  James Henstridge<james@daa.com.au>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
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
file|"pygimp.h"
end_include

begin_decl_stmt
DECL|variable|disp_methods
specifier|static
name|PyMethodDef
name|disp_methods
index|[]
init|=
block|{
block|{
name|NULL
block|,
name|NULL
block|}
comment|/* sentinel */
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|disp_get_ID (PyGimpDisplay * self,void * closure)
name|disp_get_ID
parameter_list|(
name|PyGimpDisplay
modifier|*
name|self
parameter_list|,
name|void
modifier|*
name|closure
parameter_list|)
block|{
return|return
name|PyInt_FromLong
argument_list|(
name|self
operator|->
name|ID
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|disp_getsets
specifier|static
name|PyGetSetDef
name|disp_getsets
index|[]
init|=
block|{
block|{
literal|"ID"
block|,
operator|(
name|getter
operator|)
name|disp_get_ID
block|,
operator|(
name|setter
operator|)
literal|0
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
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* ---------- */
end_comment

begin_function
name|PyObject
modifier|*
DECL|function|pygimp_display_new (gint32 ID)
name|pygimp_display_new
parameter_list|(
name|gint32
name|ID
parameter_list|)
block|{
name|PyGimpDisplay
modifier|*
name|self
decl_stmt|;
name|self
operator|=
name|PyObject_NEW
argument_list|(
name|PyGimpDisplay
argument_list|,
operator|&
name|PyGimpDisplay_Type
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
name|self
operator|->
name|ID
operator|=
name|ID
expr_stmt|;
return|return
operator|(
name|PyObject
operator|*
operator|)
name|self
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|disp_dealloc (PyGimpDisplay * self)
name|disp_dealloc
parameter_list|(
name|PyGimpDisplay
modifier|*
name|self
parameter_list|)
block|{
name|PyObject_DEL
argument_list|(
name|self
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|disp_repr (PyGimpDisplay * self)
name|disp_repr
parameter_list|(
name|PyGimpDisplay
modifier|*
name|self
parameter_list|)
block|{
name|PyObject
modifier|*
name|s
decl_stmt|;
name|s
operator|=
name|PyString_FromString
argument_list|(
literal|"<display>"
argument_list|)
expr_stmt|;
return|return
name|s
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|disp_init (PyGimpDisplay * self,PyObject * args,PyObject * kwargs)
name|disp_init
parameter_list|(
name|PyGimpDisplay
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
name|PyGimpImage
modifier|*
name|img
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTuple
argument_list|(
name|args
argument_list|,
literal|"O!:gimp.Display.__init__"
argument_list|,
operator|&
name|PyGimpImage_Type
argument_list|,
operator|&
name|img
argument_list|)
condition|)
return|return
operator|-
literal|1
return|;
name|self
operator|->
name|ID
operator|=
name|gimp_display_new
argument_list|(
name|img
operator|->
name|ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|->
name|ID
operator|<
literal|0
condition|)
block|{
name|PyErr_Format
argument_list|(
name|pygimp_error
argument_list|,
literal|"could not create display for image (ID %d)"
argument_list|,
name|img
operator|->
name|ID
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|PyGimpDisplay_Type
name|PyTypeObject
name|PyGimpDisplay_Type
init|=
block|{
name|PyObject_HEAD_INIT
argument_list|(
name|NULL
argument_list|)
literal|0
block|,
comment|/* ob_size */
literal|"gimp.Display"
block|,
comment|/* tp_name */
sizeof|sizeof
argument_list|(
name|PyGimpDisplay
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
name|disp_dealloc
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
name|disp_repr
block|,
comment|/* tp_repr */
literal|0
block|,
comment|/* tp_as_number */
literal|0
block|,
comment|/* tp_as_sequence */
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
comment|/* tp_str */
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
name|disp_methods
block|,
comment|/* tp_methods */
literal|0
block|,
comment|/* tp_members */
name|disp_getsets
block|,
comment|/* tp_getset */
operator|(
name|PyTypeObject
operator|*
operator|)
literal|0
block|,
comment|/* tp_base */
operator|(
name|PyObject
operator|*
operator|)
literal|0
block|,
comment|/* tp_dict */
literal|0
block|,
comment|/* tp_descr_get */
literal|0
block|,
comment|/* tp_descr_set */
literal|0
block|,
comment|/* tp_dictoffset */
operator|(
name|initproc
operator|)
name|disp_init
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
block|}
decl_stmt|;
end_decl_stmt

end_unit


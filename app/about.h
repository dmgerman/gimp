begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__ABOUT_H__
end_ifndef

begin_define
DECL|macro|__ABOUT_H__
define|#
directive|define
name|__ABOUT_H__
end_define

begin_define
DECL|macro|GIMP_ACRONYM
define|#
directive|define
name|GIMP_ACRONYM
value|"GIMP"
end_define

begin_define
DECL|macro|GIMP_NAME
define|#
directive|define
name|GIMP_NAME
define|\
value|_("GNU Image Manipulation Program")
end_define

begin_define
DECL|macro|GIMP_COPYRIGHT
define|#
directive|define
name|GIMP_COPYRIGHT
define|\
value|_("Copyright (C) 1995-2006\n" \     "Spencer Kimball, Peter Mattis and the GIMP Development Team")
end_define

begin_define
DECL|macro|GIMP_LICENSE
define|#
directive|define
name|GIMP_LICENSE
define|\
value|_("This program is free software; you can redistribute it and/or modify "  \     "it under the terms of the GNU General Public License as published by "  \     "the Free Software Foundation; either version 2 of the License, or "     \     "(at your option) any later version."                                    \     "\n\n"                                                                   \     "This program is distributed in the hope that it will be useful, "       \     "but WITHOUT ANY WARRANTY; without even the implied warranty of "        \     "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. "                  \     "See the GNU General Public License for more details."                   \     "\n\n"                                                                   \     "You should have received a copy of the GNU General Public License "     \     "along with this program; if not, write to the Free Software "           \     "Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, " \     "USA.")
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __ABOUT_H__ */
end_comment

end_unit


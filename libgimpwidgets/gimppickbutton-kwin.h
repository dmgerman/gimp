begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppickbutton-kwin.h  * Copyright (C) 2017 Jehan<jehan@gimp.org>  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* Private header file which is not meant to be exported. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PICK_BUTTON_KWIN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PICK_BUTTON_KWIN_H__
define|#
directive|define
name|__GIMP_PICK_BUTTON_KWIN_H__
end_define

begin_function_decl
name|gboolean
name|_gimp_pick_button_kwin_available
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_pick_button_kwin_pick
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PICK_BUTTON_KWIN_H__ */
end_comment

end_unit


begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* Win32 language lookup table:  * Copyright (C) 2007-2008 Dieter Verfaillie<dieterv@optionexplicit.be>  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<locale.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<winnls.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"language.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|language_init (const gchar * language)
name|language_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|language
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
if|if
condition|(
operator|!
name|language
condition|)
block|{
comment|/* FIXME: This is a hack. gettext doesn't pick the right language        * by default on Windows, so we enforce the right one. The        * following code is an adaptation of Python code from        * pynicotine. For reasons why this approach is needed, and why        * the GetLocaleInfo() approach in other libs falls flat, see:        * http://blogs.msdn.com/b/michkap/archive/2007/04/15/2146890.aspx        */
switch|switch
condition|(
name|GetUserDefaultUILanguage
argument_list|()
condition|)
block|{
case|case
literal|1078
case|:
name|language
operator|=
literal|"af"
expr_stmt|;
comment|/* Afrikaans - South Africa */
break|break;
case|case
literal|1052
case|:
name|language
operator|=
literal|"sq"
expr_stmt|;
comment|/* Albanian - Albania */
break|break;
case|case
literal|1118
case|:
name|language
operator|=
literal|"am"
expr_stmt|;
comment|/* Amharic - Ethiopia */
break|break;
case|case
literal|1025
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Saudi Arabia */
break|break;
case|case
literal|5121
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Algeria */
break|break;
case|case
literal|15361
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Bahrain */
break|break;
case|case
literal|3073
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Egypt */
break|break;
case|case
literal|2049
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Iraq */
break|break;
case|case
literal|11265
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Jordan */
break|break;
case|case
literal|13313
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Kuwait */
break|break;
case|case
literal|12289
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Lebanon */
break|break;
case|case
literal|4097
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Libya */
break|break;
case|case
literal|6145
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Morocco */
break|break;
case|case
literal|8193
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Oman */
break|break;
case|case
literal|16385
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Qatar */
break|break;
case|case
literal|10241
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Syria */
break|break;
case|case
literal|7169
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Tunisia */
break|break;
case|case
literal|14337
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - U.A.E. */
break|break;
case|case
literal|9217
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Yemen */
break|break;
case|case
literal|1067
case|:
name|language
operator|=
literal|"hy"
expr_stmt|;
comment|/* Armenian - Armenia */
break|break;
case|case
literal|1101
case|:
name|language
operator|=
literal|"as"
expr_stmt|;
comment|/* Assamese */
break|break;
case|case
literal|2092
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Azeri (Cyrillic) */
break|break;
case|case
literal|1068
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Azeri (Latin) */
break|break;
case|case
literal|1069
case|:
name|language
operator|=
literal|"eu"
expr_stmt|;
comment|/* Basque */
break|break;
case|case
literal|1059
case|:
name|language
operator|=
literal|"be"
expr_stmt|;
comment|/* Belarusian */
break|break;
case|case
literal|1093
case|:
name|language
operator|=
literal|"bn"
expr_stmt|;
comment|/* Bengali (India) */
break|break;
case|case
literal|2117
case|:
name|language
operator|=
literal|"bn"
expr_stmt|;
comment|/* Bengali (Bangladesh) */
break|break;
case|case
literal|5146
case|:
name|language
operator|=
literal|"bs"
expr_stmt|;
comment|/* Bosnian (Bosnia/Herzegovina) */
break|break;
case|case
literal|1026
case|:
name|language
operator|=
literal|"bg"
expr_stmt|;
comment|/* Bulgarian */
break|break;
case|case
literal|1109
case|:
name|language
operator|=
literal|"my"
expr_stmt|;
comment|/* Burmese */
break|break;
case|case
literal|1027
case|:
name|language
operator|=
literal|"ca"
expr_stmt|;
comment|/* Catalan */
break|break;
case|case
literal|1116
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Cherokee - United States */
break|break;
case|case
literal|2052
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - People"s Republic of China */
break|break;
case|case
literal|4100
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Singapore */
break|break;
case|case
literal|1028
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Taiwan */
break|break;
case|case
literal|3076
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Hong Kong SAR */
break|break;
case|case
literal|5124
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Macao SAR */
break|break;
case|case
literal|1050
case|:
name|language
operator|=
literal|"hr"
expr_stmt|;
comment|/* Croatian */
break|break;
case|case
literal|4122
case|:
name|language
operator|=
literal|"hr"
expr_stmt|;
comment|/* Croatian (Bosnia/Herzegovina) */
break|break;
case|case
literal|1029
case|:
name|language
operator|=
literal|"cs"
expr_stmt|;
comment|/* Czech */
break|break;
case|case
literal|1030
case|:
name|language
operator|=
literal|"da"
expr_stmt|;
comment|/* Danish */
break|break;
case|case
literal|1125
case|:
name|language
operator|=
literal|"dv"
expr_stmt|;
comment|/* Divehi */
break|break;
case|case
literal|1043
case|:
name|language
operator|=
literal|"nl"
expr_stmt|;
comment|/* Dutch - Netherlands */
break|break;
case|case
literal|2067
case|:
name|language
operator|=
literal|"nl"
expr_stmt|;
comment|/* Dutch - Belgium */
break|break;
case|case
literal|1126
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Edo */
break|break;
case|case
literal|1033
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - United States */
break|break;
case|case
literal|2057
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - United Kingdom */
break|break;
case|case
literal|3081
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Australia */
break|break;
case|case
literal|10249
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Belize */
break|break;
case|case
literal|4105
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Canada */
break|break;
case|case
literal|9225
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Caribbean */
break|break;
case|case
literal|15369
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Hong Kong SAR */
break|break;
case|case
literal|16393
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - India */
break|break;
case|case
literal|14345
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Indonesia */
break|break;
case|case
literal|6153
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Ireland */
break|break;
case|case
literal|8201
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Jamaica */
break|break;
case|case
literal|17417
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Malaysia */
break|break;
case|case
literal|5129
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - New Zealand */
break|break;
case|case
literal|13321
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Philippines */
break|break;
case|case
literal|18441
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Singapore */
break|break;
case|case
literal|7177
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - South Africa */
break|break;
case|case
literal|11273
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Trinidad */
break|break;
case|case
literal|12297
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Zimbabwe */
break|break;
case|case
literal|1061
case|:
name|language
operator|=
literal|"et"
expr_stmt|;
comment|/* Estonian */
break|break;
case|case
literal|1080
case|:
name|language
operator|=
literal|"fo"
expr_stmt|;
comment|/* Faroese */
break|break;
case|case
literal|1065
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Farsi */
break|break;
case|case
literal|1124
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Filipino */
break|break;
case|case
literal|1035
case|:
name|language
operator|=
literal|"fi"
expr_stmt|;
comment|/* Finnish */
break|break;
case|case
literal|1036
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - France */
break|break;
case|case
literal|2060
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Belgium */
break|break;
case|case
literal|11276
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Cameroon */
break|break;
case|case
literal|3084
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Canada */
break|break;
case|case
literal|9228
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Democratic Rep. of Congo */
break|break;
case|case
literal|12300
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Cote d"Ivoire */
break|break;
case|case
literal|15372
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Haiti */
break|break;
case|case
literal|5132
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Luxembourg */
break|break;
case|case
literal|13324
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Mali */
break|break;
case|case
literal|6156
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Monaco */
break|break;
case|case
literal|14348
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Morocco */
break|break;
case|case
literal|58380
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - North Africa */
break|break;
case|case
literal|8204
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Reunion */
break|break;
case|case
literal|10252
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Senegal */
break|break;
case|case
literal|4108
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Switzerland */
break|break;
case|case
literal|7180
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - West Indies */
break|break;
case|case
literal|1122
case|:
name|language
operator|=
literal|"fy"
expr_stmt|;
comment|/* Frisian - Netherlands */
break|break;
case|case
literal|1127
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Fulfulde - Nigeria */
break|break;
case|case
literal|1071
case|:
name|language
operator|=
literal|"mk"
expr_stmt|;
comment|/* FYRO Macedonian */
break|break;
case|case
literal|2108
case|:
name|language
operator|=
literal|"ga"
expr_stmt|;
comment|/* Gaelic (Ireland) */
break|break;
case|case
literal|1084
case|:
name|language
operator|=
literal|"gd"
expr_stmt|;
comment|/* Gaelic (Scotland) */
break|break;
case|case
literal|1110
case|:
name|language
operator|=
literal|"gl"
expr_stmt|;
comment|/* Galician */
break|break;
case|case
literal|1079
case|:
name|language
operator|=
literal|"ka"
expr_stmt|;
comment|/* Georgian */
break|break;
case|case
literal|1031
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Germany */
break|break;
case|case
literal|3079
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Austria */
break|break;
case|case
literal|5127
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Liechtenstein */
break|break;
case|case
literal|4103
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Luxembourg */
break|break;
case|case
literal|2055
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Switzerland */
break|break;
case|case
literal|1032
case|:
name|language
operator|=
literal|"el"
expr_stmt|;
comment|/* Greek */
break|break;
case|case
literal|1140
case|:
name|language
operator|=
literal|"gn"
expr_stmt|;
comment|/* Guarani - Paraguay */
break|break;
case|case
literal|1095
case|:
name|language
operator|=
literal|"gu"
expr_stmt|;
comment|/* Gujarati */
break|break;
case|case
literal|1128
case|:
name|language
operator|=
literal|"ha"
expr_stmt|;
comment|/* Hausa - Nigeria */
break|break;
case|case
literal|1141
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Hawaiian - United States */
break|break;
case|case
literal|1037
case|:
name|language
operator|=
literal|"he"
expr_stmt|;
comment|/* Hebrew */
break|break;
case|case
literal|1081
case|:
name|language
operator|=
literal|"hi"
expr_stmt|;
comment|/* Hindi */
break|break;
case|case
literal|1038
case|:
name|language
operator|=
literal|"hu"
expr_stmt|;
comment|/* Hungarian */
break|break;
case|case
literal|1129
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Ibibio - Nigeria */
break|break;
case|case
literal|1039
case|:
name|language
operator|=
literal|"is"
expr_stmt|;
comment|/* Icelandic */
break|break;
case|case
literal|1136
case|:
name|language
operator|=
literal|"ig"
expr_stmt|;
comment|/* Igbo - Nigeria */
break|break;
case|case
literal|1057
case|:
name|language
operator|=
literal|"id"
expr_stmt|;
comment|/* Indonesian */
break|break;
case|case
literal|1117
case|:
name|language
operator|=
literal|"iu"
expr_stmt|;
comment|/* Inuktitut */
break|break;
case|case
literal|1040
case|:
name|language
operator|=
literal|"it"
expr_stmt|;
comment|/* Italian - Italy */
break|break;
case|case
literal|2064
case|:
name|language
operator|=
literal|"it"
expr_stmt|;
comment|/* Italian - Switzerland */
break|break;
case|case
literal|1041
case|:
name|language
operator|=
literal|"ja"
expr_stmt|;
comment|/* Japanese */
break|break;
case|case
literal|1099
case|:
name|language
operator|=
literal|"kn"
expr_stmt|;
comment|/* Kannada */
break|break;
case|case
literal|1137
case|:
name|language
operator|=
literal|"kr"
expr_stmt|;
comment|/* Kanuri - Nigeria */
break|break;
case|case
literal|2144
case|:
name|language
operator|=
literal|"ks"
expr_stmt|;
comment|/* Kashmiri */
break|break;
case|case
literal|1120
case|:
name|language
operator|=
literal|"ks"
expr_stmt|;
comment|/* Kashmiri (Arabic) */
break|break;
case|case
literal|1087
case|:
name|language
operator|=
literal|"kk"
expr_stmt|;
comment|/* Kazakh */
break|break;
case|case
literal|1107
case|:
name|language
operator|=
literal|"km"
expr_stmt|;
comment|/* Khmer */
break|break;
case|case
literal|1111
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Konkani */
break|break;
case|case
literal|1042
case|:
name|language
operator|=
literal|"ko"
expr_stmt|;
comment|/* Korean */
break|break;
case|case
literal|1088
case|:
name|language
operator|=
literal|"ky"
expr_stmt|;
comment|/* Kyrgyz (Cyrillic) */
break|break;
case|case
literal|1108
case|:
name|language
operator|=
literal|"lo"
expr_stmt|;
comment|/* Lao */
break|break;
case|case
literal|1142
case|:
name|language
operator|=
literal|"la"
expr_stmt|;
comment|/* Latin */
break|break;
case|case
literal|1062
case|:
name|language
operator|=
literal|"lv"
expr_stmt|;
comment|/* Latvian */
break|break;
case|case
literal|1063
case|:
name|language
operator|=
literal|"lt"
expr_stmt|;
comment|/* Lithuanian */
break|break;
case|case
literal|1086
case|:
name|language
operator|=
literal|"ms"
expr_stmt|;
comment|/* Malay - Malaysia */
break|break;
case|case
literal|2110
case|:
name|language
operator|=
literal|"ms"
expr_stmt|;
comment|/* Malay - Brunei Darussalam */
break|break;
case|case
literal|1100
case|:
name|language
operator|=
literal|"ml"
expr_stmt|;
comment|/* Malayalam */
break|break;
case|case
literal|1082
case|:
name|language
operator|=
literal|"mt"
expr_stmt|;
comment|/* Maltese */
break|break;
case|case
literal|1112
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Manipuri */
break|break;
case|case
literal|1153
case|:
name|language
operator|=
literal|"mi"
expr_stmt|;
comment|/* Maori - New Zealand */
break|break;
case|case
literal|1102
case|:
name|language
operator|=
literal|"mr"
expr_stmt|;
comment|/* Marathi */
break|break;
case|case
literal|1104
case|:
name|language
operator|=
literal|"mn"
expr_stmt|;
comment|/* Mongolian (Cyrillic) */
break|break;
case|case
literal|2128
case|:
name|language
operator|=
literal|"mn"
expr_stmt|;
comment|/* Mongolian (Mongolian) */
break|break;
case|case
literal|1121
case|:
name|language
operator|=
literal|"ne"
expr_stmt|;
comment|/* Nepali */
break|break;
case|case
literal|2145
case|:
name|language
operator|=
literal|"ne"
expr_stmt|;
comment|/* Nepali - India */
break|break;
case|case
literal|1044
case|:
name|language
operator|=
literal|"no"
expr_stmt|;
comment|/* Norwegian (Bokmï¿ï¾¥l) */
break|break;
case|case
literal|2068
case|:
name|language
operator|=
literal|"no"
expr_stmt|;
comment|/* Norwegian (Nynorsk) */
break|break;
case|case
literal|1096
case|:
name|language
operator|=
literal|"or"
expr_stmt|;
comment|/* Oriya */
break|break;
case|case
literal|1138
case|:
name|language
operator|=
literal|"om"
expr_stmt|;
comment|/* Oromo */
break|break;
case|case
literal|1145
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Papiamentu */
break|break;
case|case
literal|1123
case|:
name|language
operator|=
literal|"ps"
expr_stmt|;
comment|/* Pashto */
break|break;
case|case
literal|1045
case|:
name|language
operator|=
literal|"pl"
expr_stmt|;
comment|/* Polish */
break|break;
case|case
literal|1046
case|:
name|language
operator|=
literal|"pt"
expr_stmt|;
comment|/* Portuguese - Brazil */
break|break;
case|case
literal|2070
case|:
name|language
operator|=
literal|"pt"
expr_stmt|;
comment|/* Portuguese - Portugal */
break|break;
case|case
literal|1094
case|:
name|language
operator|=
literal|"pa"
expr_stmt|;
comment|/* Punjabi */
break|break;
case|case
literal|2118
case|:
name|language
operator|=
literal|"pa"
expr_stmt|;
comment|/* Punjabi (Pakistan) */
break|break;
case|case
literal|1131
case|:
name|language
operator|=
literal|"qu"
expr_stmt|;
comment|/* Quecha - Bolivia */
break|break;
case|case
literal|2155
case|:
name|language
operator|=
literal|"qu"
expr_stmt|;
comment|/* Quecha - Ecuador */
break|break;
case|case
literal|3179
case|:
name|language
operator|=
literal|"qu"
expr_stmt|;
comment|/* Quecha - Peru */
break|break;
case|case
literal|1047
case|:
name|language
operator|=
literal|"rm"
expr_stmt|;
comment|/* Rhaeto-Romanic */
break|break;
case|case
literal|1048
case|:
name|language
operator|=
literal|"ro"
expr_stmt|;
comment|/* Romanian */
break|break;
case|case
literal|2072
case|:
name|language
operator|=
literal|"ro"
expr_stmt|;
comment|/* Romanian - Moldava */
break|break;
case|case
literal|1049
case|:
name|language
operator|=
literal|"ru"
expr_stmt|;
comment|/* Russian */
break|break;
case|case
literal|2073
case|:
name|language
operator|=
literal|"ru"
expr_stmt|;
comment|/* Russian - Moldava */
break|break;
case|case
literal|1083
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sami (Lappish) */
break|break;
case|case
literal|1103
case|:
name|language
operator|=
literal|"sa"
expr_stmt|;
comment|/* Sanskrit */
break|break;
case|case
literal|1132
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sepedi */
break|break;
case|case
literal|3098
case|:
name|language
operator|=
literal|"sr"
expr_stmt|;
comment|/* Serbian (Cyrillic) */
break|break;
case|case
literal|2074
case|:
name|language
operator|=
literal|"sr"
expr_stmt|;
comment|/* Serbian (Latin) */
break|break;
case|case
literal|1113
case|:
name|language
operator|=
literal|"sd"
expr_stmt|;
comment|/* Sindhi - India */
break|break;
case|case
literal|2137
case|:
name|language
operator|=
literal|"sd"
expr_stmt|;
comment|/* Sindhi - Pakistan */
break|break;
case|case
literal|1115
case|:
name|language
operator|=
literal|"si"
expr_stmt|;
comment|/* Sinhalese - Sri Lanka */
break|break;
case|case
literal|1051
case|:
name|language
operator|=
literal|"sk"
expr_stmt|;
comment|/* Slovak */
break|break;
case|case
literal|1060
case|:
name|language
operator|=
literal|"sl"
expr_stmt|;
comment|/* Slovenian */
break|break;
case|case
literal|1143
case|:
name|language
operator|=
literal|"so"
expr_stmt|;
comment|/* Somali */
break|break;
case|case
literal|1070
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sorbian */
break|break;
case|case
literal|3082
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Spain (Modern Sort) */
break|break;
case|case
literal|1034
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Spain (Traditional Sort) */
break|break;
case|case
literal|11274
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Argentina */
break|break;
case|case
literal|16394
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Bolivia */
break|break;
case|case
literal|13322
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Chile */
break|break;
case|case
literal|9226
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Colombia */
break|break;
case|case
literal|5130
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Costa Rica */
break|break;
case|case
literal|7178
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Dominican Republic */
break|break;
case|case
literal|12298
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Ecuador */
break|break;
case|case
literal|17418
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - El Salvador */
break|break;
case|case
literal|4106
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Guatemala */
break|break;
case|case
literal|18442
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Honduras */
break|break;
case|case
literal|58378
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Latin America */
break|break;
case|case
literal|2058
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Mexico */
break|break;
case|case
literal|19466
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Nicaragua */
break|break;
case|case
literal|6154
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Panama */
break|break;
case|case
literal|15370
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Paraguay */
break|break;
case|case
literal|10250
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Peru */
break|break;
case|case
literal|20490
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Puerto Rico */
break|break;
case|case
literal|21514
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - United States */
break|break;
case|case
literal|14346
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Uruguay */
break|break;
case|case
literal|8202
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Venezuela */
break|break;
case|case
literal|1072
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sutu */
break|break;
case|case
literal|1089
case|:
name|language
operator|=
literal|"sw"
expr_stmt|;
comment|/* Swahili */
break|break;
case|case
literal|1053
case|:
name|language
operator|=
literal|"sv"
expr_stmt|;
comment|/* Swedish */
break|break;
case|case
literal|2077
case|:
name|language
operator|=
literal|"sv"
expr_stmt|;
comment|/* Swedish - Finland */
break|break;
case|case
literal|1114
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Syriac */
break|break;
case|case
literal|1064
case|:
name|language
operator|=
literal|"tg"
expr_stmt|;
comment|/* Tajik */
break|break;
case|case
literal|1119
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Tamazight (Arabic) */
break|break;
case|case
literal|2143
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Tamazight (Latin) */
break|break;
case|case
literal|1097
case|:
name|language
operator|=
literal|"ta"
expr_stmt|;
comment|/* Tamil */
break|break;
case|case
literal|1092
case|:
name|language
operator|=
literal|"tt"
expr_stmt|;
comment|/* Tatar */
break|break;
case|case
literal|1098
case|:
name|language
operator|=
literal|"te"
expr_stmt|;
comment|/* Telugu */
break|break;
case|case
literal|1054
case|:
name|language
operator|=
literal|"th"
expr_stmt|;
comment|/* Thai */
break|break;
case|case
literal|2129
case|:
name|language
operator|=
literal|"bo"
expr_stmt|;
comment|/* Tibetan - Bhutan */
break|break;
case|case
literal|1105
case|:
name|language
operator|=
literal|"bo"
expr_stmt|;
comment|/* Tibetan - People"s Republic of China */
break|break;
case|case
literal|2163
case|:
name|language
operator|=
literal|"ti"
expr_stmt|;
comment|/* Tigrigna - Eritrea */
break|break;
case|case
literal|1139
case|:
name|language
operator|=
literal|"ti"
expr_stmt|;
comment|/* Tigrigna - Ethiopia */
break|break;
case|case
literal|1073
case|:
name|language
operator|=
literal|"ts"
expr_stmt|;
comment|/* Tsonga */
break|break;
case|case
literal|1074
case|:
name|language
operator|=
literal|"tn"
expr_stmt|;
comment|/* Tswana */
break|break;
case|case
literal|1055
case|:
name|language
operator|=
literal|"tr"
expr_stmt|;
comment|/* Turkish */
break|break;
case|case
literal|1090
case|:
name|language
operator|=
literal|"tk"
expr_stmt|;
comment|/* Turkmen */
break|break;
case|case
literal|1152
case|:
name|language
operator|=
literal|"ug"
expr_stmt|;
comment|/* Uighur - China */
break|break;
case|case
literal|1058
case|:
name|language
operator|=
literal|"uk"
expr_stmt|;
comment|/* Ukrainian */
break|break;
case|case
literal|1056
case|:
name|language
operator|=
literal|"ur"
expr_stmt|;
comment|/* Urdu */
break|break;
case|case
literal|2080
case|:
name|language
operator|=
literal|"ur"
expr_stmt|;
comment|/* Urdu - India */
break|break;
case|case
literal|2115
case|:
name|language
operator|=
literal|"uz"
expr_stmt|;
comment|/* Uzbek (Cyrillic) */
break|break;
case|case
literal|1091
case|:
name|language
operator|=
literal|"uz"
expr_stmt|;
comment|/* Uzbek (Latin) */
break|break;
case|case
literal|1075
case|:
name|language
operator|=
literal|"ve"
expr_stmt|;
comment|/* Venda */
break|break;
case|case
literal|1066
case|:
name|language
operator|=
literal|"vi"
expr_stmt|;
comment|/* Vietnamese */
break|break;
case|case
literal|1106
case|:
name|language
operator|=
literal|"cy"
expr_stmt|;
comment|/* Welsh */
break|break;
case|case
literal|1076
case|:
name|language
operator|=
literal|"xh"
expr_stmt|;
comment|/* Xhosa */
break|break;
case|case
literal|1144
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Yi */
break|break;
case|case
literal|1085
case|:
name|language
operator|=
literal|"yi"
expr_stmt|;
comment|/* Yiddish */
break|break;
case|case
literal|1130
case|:
name|language
operator|=
literal|"yo"
expr_stmt|;
comment|/* Yoruba */
break|break;
case|case
literal|1077
case|:
name|language
operator|=
literal|"zu"
expr_stmt|;
comment|/* Zulu */
break|break;
default|default:
name|language
operator|=
name|NULL
expr_stmt|;
block|}
block|}
endif|#
directive|endif
comment|/*  We already set the locale according to the environment, so just    *  return early if no language is set in gimprc.    */
if|if
condition|(
operator|!
name|language
condition|)
return|return;
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|language
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

end_unit


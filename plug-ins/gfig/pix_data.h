begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|circle_xpm
specifier|static
name|char
modifier|*
name|circle_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c black"
block|,
literal|"X	c red"
block|,
literal|"o	c white"
block|,
literal|"                        "
block|,
literal|"         ...            "
block|,
literal|"      ...   ...         "
block|,
literal|"     .         .        "
block|,
literal|"    .          XXX      "
block|,
literal|"    .          XoX      "
block|,
literal|"    .          XXX      "
block|,
literal|"   .     XXX     .      "
block|,
literal|"   .     XoX     .      "
block|,
literal|"   .     XXX     .      "
block|,
literal|"    .           .       "
block|,
literal|"    .           .       "
block|,
literal|"    .           .       "
block|,
literal|"     .         .        "
block|,
literal|"      ...   ...         "
block|,
literal|"         ...            "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|" ... ... ...  ... .  ..."
block|,
literal|"..    .  . . ..   .  .  "
block|,
literal|".     .  . . .    .  .  "
block|,
literal|".     .  ..  .    .  .. "
block|,
literal|"..    .  . . ..   .  .  "
block|,
literal|" ... ... .  . ... ......"
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|ellipse_xpm
specifier|static
name|char
modifier|*
name|ellipse_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c black"
block|,
literal|"X	c red"
block|,
literal|"o	c white"
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"      ..........        "
block|,
literal|"     .          .       "
block|,
literal|"    .            .      "
block|,
literal|"   .              .     "
block|,
literal|"   .              .     "
block|,
literal|"   .      XXX     .     "
block|,
literal|"   .      XoX     .     "
block|,
literal|"   .      XXX     .     "
block|,
literal|"   .              .     "
block|,
literal|"   .              .     "
block|,
literal|"    .            .      "
block|,
literal|"     .          .  XXX  "
block|,
literal|"      ..........   XoX  "
block|,
literal|"                   XXX  "
block|,
literal|"                        "
block|,
literal|"... .  .  ... .. ... ..."
block|,
literal|".   .  .   .  . ..   .  "
block|,
literal|"... .  .   .  . ...  ..."
block|,
literal|".   .  .   .  ..   . .  "
block|,
literal|".   .  .   .  .     ..  "
block|,
literal|"... ......... .  ... ..."
block|,
literal|"                        "
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|curve_xpm
specifier|static
name|char
modifier|*
name|curve_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c red"
block|,
literal|"X	c white"
block|,
literal|"o	c black"
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"         ...            "
block|,
literal|"         .X.ooo         "
block|,
literal|"        o...   oo       "
block|,
literal|"      oo         oo     "
block|,
literal|"     o             o    "
block|,
literal|"     o              o   "
block|,
literal|"    o               ... "
block|,
literal|"    o               .X. "
block|,
literal|"   o                ... "
block|,
literal|"  ...                   "
block|,
literal|"  .X.                   "
block|,
literal|"  ...                   "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|" ooo o  o ooo o   o ooo "
block|,
literal|"oo   o  o o o o   o o   "
block|,
literal|"o    o  o o o  o o  ooo "
block|,
literal|"o    o  o oo   o o  o   "
block|,
literal|"oo   o  o o o  o o  o   "
block|,
literal|" ooo oooo o  o  o   ooo "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|line_xpm
specifier|static
name|char
modifier|*
name|line_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c red"
block|,
literal|"X	c white"
block|,
literal|"o	c black"
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"  ...                   "
block|,
literal|"  .X.                   "
block|,
literal|"  ...                   "
block|,
literal|"     oo                 "
block|,
literal|"       oo               "
block|,
literal|"         oo             "
block|,
literal|"           oo           "
block|,
literal|"             oo         "
block|,
literal|"               oo       "
block|,
literal|"                 ...    "
block|,
literal|"                 .X.    "
block|,
literal|"                 ...    "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"   o    ooo o  o  oooo  "
block|,
literal|"   o     o  oo o  o     "
block|,
literal|"   o     o  oo o  ooo   "
block|,
literal|"   o     o  o oo  o     "
block|,
literal|"   o     o  o oo  o     "
block|,
literal|"   oooo ooo o  o  oooo  "
block|,
literal|"                        "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|move_obj_xpm
specifier|static
name|char
modifier|*
name|move_obj_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c black"
block|,
literal|"X	c red"
block|,
literal|"o	c white"
block|,
literal|"       .                "
block|,
literal|" XXX    .  XXX          "
block|,
literal|" XoX ..... XoX          "
block|,
literal|" XXX    .  XXX          "
block|,
literal|"   X   .     .          "
block|,
literal|"    X         .         "
block|,
literal|"     X     .  .         "
block|,
literal|"     X      .  .        "
block|,
literal|"      X  .....  .       "
block|,
literal|"       X    .   .       "
block|,
literal|"        X  .     .      "
block|,
literal|"        XXX      XXX    "
block|,
literal|"        XoX      XoX    "
block|,
literal|"        XXX      XXX    "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|" .   .  ...  .   . .... "
block|,
literal|" .. .. .. .. .   . .    "
block|,
literal|" .. .. .   .  . .  ...  "
block|,
literal|" .. .. .   .  . .  .    "
block|,
literal|" . . . .. ..  ...  .    "
block|,
literal|" . . .  ...    .   .... "
block|,
literal|"                        "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|copy_obj_xpm
specifier|static
name|char
modifier|*
name|copy_obj_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c black"
block|,
literal|"X	c red"
block|,
literal|"o	c white"
block|,
literal|"                        "
block|,
literal|"         .              "
block|,
literal|"  XXX     .  XXX        "
block|,
literal|"  XoX  ..... XoX        "
block|,
literal|"  XXX     .  XXX        "
block|,
literal|"    .    .     .        "
block|,
literal|"    .          .        "
block|,
literal|"     .          .       "
block|,
literal|"     .          .       "
block|,
literal|"     .     .    .       "
block|,
literal|"      .     .    .      "
block|,
literal|"      .  .....   .      "
block|,
literal|"       .    .     .     "
block|,
literal|"      XXX  .     XXX    "
block|,
literal|"      XoX        XoX    "
block|,
literal|"      XXX        XXX    "
block|,
literal|"                        "
block|,
literal|"  ....  ...  .... .   . "
block|,
literal|" ..    .. .. .  .  . .  "
block|,
literal|" .     .   . .  .  . .  "
block|,
literal|" .     .   . ...    .   "
block|,
literal|" ..  . .. .. .      .   "
block|,
literal|"  ....  ...  .      .   "
block|,
literal|"                        "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|move_point_xpm
specifier|static
name|char
modifier|*
name|move_point_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c red"
block|,
literal|"X	c white"
block|,
literal|"o	c black"
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"  ...                   "
block|,
literal|"  .X.                   "
block|,
literal|"  ...oo                 "
block|,
literal|"    .  oo               "
block|,
literal|"    .    ooo  ...       "
block|,
literal|"     .      oo.X.       "
block|,
literal|"     .        ...       "
block|,
literal|"     .                  "
block|,
literal|"     .    oooo          "
block|,
literal|"      .     oo          "
block|,
literal|"      .    o o          "
block|,
literal|"     ...  o  o          "
block|,
literal|"     .X. o              "
block|,
literal|"     ...                "
block|,
literal|"                        "
block|,
literal|"oo oo     ooo o  oooooo "
block|,
literal|"o o o     o o oo o  o   "
block|,
literal|"o o o o o o o oo o  o   "
block|,
literal|"o o o o o ooo o oo  o   "
block|,
literal|"o o o o o o   o oo  o   "
block|,
literal|"o o o  o  o   o  o  o   "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|mini_cross_xpm
specifier|static
name|char
modifier|*
name|mini_cross_xpm
index|[]
init|=
block|{
literal|"16 14 4 1"
block|,
literal|" 	c None s None"
block|,
literal|".	c red"
block|,
literal|"X	c gray50"
block|,
literal|"o	c black"
block|,
literal|"                "
block|,
literal|"           .    "
block|,
literal|"   ..X    ...   "
block|,
literal|"    ..X  .....  "
block|,
literal|"     .......oo  "
block|,
literal|"      .....o    "
block|,
literal|"      ....o     "
block|,
literal|"     ......     "
block|,
literal|"     ..o ...    "
block|,
literal|"    ..o   ...   "
block|,
literal|"    .o     ..X  "
block|,
literal|"   .o       .o  "
block|,
literal|"   o         o  "
block|,
literal|"                "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|blank_xpm
specifier|static
name|char
modifier|*
name|blank_xpm
index|[]
init|=
block|{
literal|"18 17 1 1"
block|,
literal|" 	c None"
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|,
literal|"                  "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|Floppy6_xpm
specifier|static
name|char
modifier|*
name|Floppy6_xpm
index|[]
init|=
block|{
literal|"18 18 24 1"
block|,
literal|" 	c None"
block|,
literal|".	c #861782078617"
block|,
literal|"X	c #5965596571C6"
block|,
literal|"o	c #618565955965"
block|,
literal|"O	c #596559659E79"
block|,
literal|"+	c #0000000079E7"
block|,
literal|"@	c #0820082071C6"
block|,
literal|"#	c #9E799E790000"
block|,
literal|"$	c #FFFFFFFF0000"
block|,
literal|"%	c #186118614103"
block|,
literal|"&	c #965896589E79"
block|,
literal|"*	c #9E799E795965"
block|,
literal|"=	c #000000006185"
block|,
literal|"-	c #9E799E799E79"
block|,
literal|";	c #FFFFFFFFFFFF"
block|,
literal|":	c #000000000000"
block|,
literal|">	c #71C675D69658"
block|,
literal|",	c #BEFBBEFBBEFB"
block|,
literal|"<	c #B6DAB2CABEFB"
block|,
literal|"1	c #1040145171C6"
block|,
literal|"2	c #28A228A28617"
block|,
literal|"3	c #79E77DF78E38"
block|,
literal|"4	c #A699A289A699"
block|,
literal|"5	c #38E33CF379E7"
block|,
literal|"                  "
block|,
literal|"  .XXoooooooooXO  "
block|,
literal|"  +@#$$$$$$$$$%+O "
block|,
literal|"&++*$$$$$$$$$%+O "
block|,
literal|"&+=-;;;;;;;;;%+O "
block|,
literal|"&==-;::;:;:;;%+O "
block|,
literal|"&++-;;;;;;;;;%+O "
block|,
literal|"&++-;:;:::;:;%+O "
block|,
literal|"&++-;;;;;;;;;%+O "
block|,
literal|"&+=>,,<,,,,,,1+O "
block|,
literal|"&++==========++O "
block|,
literal|"&+++22222222+++O "
block|,
literal|"&++;11>-333.+++O "
block|,
literal|"&++;++>43333+++O "
block|,
literal|"&++5++>4...3=++O "
block|,
literal|"  31+++======+++O "
block|,
literal|"&&&&&&&&&&&&   "
block|,
literal|"                  "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|poly_xpm
specifier|static
name|char
modifier|*
name|poly_xpm
index|[]
init|=
block|{
literal|"24 24 3 1"
block|,
literal|" 	c None"
block|,
literal|".	c red"
block|,
literal|"X	c black"
block|,
literal|"                        "
block|,
literal|"  ...            ...    "
block|,
literal|"  . .            . .    "
block|,
literal|"  ...            ...    "
block|,
literal|"   X X           X  X   "
block|,
literal|"   X  X         X    X  "
block|,
literal|"   X   X...  ...     ..."
block|,
literal|"   X    . .  . .     . ."
block|,
literal|"   X   X...  ...     ..."
block|,
literal|"   X  X        X     X  "
block|,
literal|"  ...X          X   X   "
block|,
literal|"  . .            ...    "
block|,
literal|"  ...            . .    "
block|,
literal|"                 ...    "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"  XXXX  XX  X   X   X   "
block|,
literal|"  X  X X  X X    X X    "
block|,
literal|"  X  X X  X X    X X    "
block|,
literal|"  XXX  X  X X     X     "
block|,
literal|"  X    X  X X     X     "
block|,
literal|"  X     XX  XXXX  X     "
block|,
literal|"                        "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|delete_xpm
specifier|static
name|char
modifier|*
name|delete_xpm
index|[]
init|=
block|{
literal|"24 24 4 1"
block|,
literal|" 	s None	c None"
block|,
literal|".	c red"
block|,
literal|"X	c white"
block|,
literal|"o	c black"
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"   ...         .        "
block|,
literal|"   .X.        .         "
block|,
literal|"   ...o      .          "
block|,
literal|"       oo  ..           "
block|,
literal|"  ..................    "
block|,
literal|"         . oo           "
block|,
literal|"        .    oo         "
block|,
literal|"       .      ...       "
block|,
literal|"     ..       .X.       "
block|,
literal|"    .         ...       "
block|,
literal|"   .                    "
block|,
literal|"  .                     "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"ooo  ooo o   ooooooooooo"
block|,
literal|"o  o o   o   o    o  o  "
block|,
literal|"o  o ooo o   ooo  o  ooo"
block|,
literal|"o  o o   o   o    o  o  "
block|,
literal|"o  o o   o   o    o  o  "
block|,
literal|"ooo  ooo ooooooo  o  ooo"
block|}
decl_stmt|;
end_decl_stmt

end_unit


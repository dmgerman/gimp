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

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|star_xpm
specifier|static
name|char
modifier|*
name|star_xpm
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
literal|"           .            "
block|,
literal|"          ...           "
block|,
literal|"          . .           "
block|,
literal|"          . .           "
block|,
literal|"          . .           "
block|,
literal|"         .. ..     XXX  "
block|,
literal|"  ........   ......XoX  "
block|,
literal|"   ..         XXX .XXX  "
block|,
literal|"    ..    XXX XoX..     "
block|,
literal|"      ..  XoX XXX       "
block|,
literal|"       .. XXX ..        "
block|,
literal|"        .     .         "
block|,
literal|"       .   .   .        "
block|,
literal|"      .. ....  .        "
block|,
literal|"      . ..  .. .        "
block|,
literal|"      ...    ...        "
block|,
literal|"     ..        ..       "
block|,
literal|"     .          .       "
block|,
literal|"  ... .....  .   ...    "
block|,
literal|"  .     .   ...  . .    "
block|,
literal|"  ..    .   . .  . .    "
block|,
literal|"   ..   .   ...  ..     "
block|,
literal|"    .   .  .   . . .    "
block|,
literal|"  ...   .  .   . .  .   "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|spiral_xpm
specifier|static
name|char
modifier|*
name|spiral_xpm
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
literal|"  ...                   "
block|,
literal|"  .X.ooooooooooooooo    "
block|,
literal|"  ...              o    "
block|,
literal|"                   o    "
block|,
literal|"     oooooooooooo  o    "
block|,
literal|"     o          o  o    "
block|,
literal|"     o     ...  o  o    "
block|,
literal|"     o  ooo.X.  o  o    "
block|,
literal|"     o  o  ...  o  o    "
block|,
literal|"     o  o       o  o    "
block|,
literal|"     o  ooooooooo  o    "
block|,
literal|"     o             o    "
block|,
literal|"     o             o    "
block|,
literal|"     ooooooooooooooo    "
block|,
literal|"                        "
block|,
literal|"                        "
block|,
literal|"ooo ooo o ooo    o   o  "
block|,
literal|"o   o o o o o   ooo  o  "
block|,
literal|"oo  o o o o o   o o  o  "
block|,
literal|" oo ooo o oo    ooo  o  "
block|,
literal|"  o o   o o o  o   o o  "
block|,
literal|"ooo o   o o  o o   o ooo"
block|,
literal|"                        "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|bezier_xpm
specifier|static
name|char
modifier|*
name|bezier_xpm
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
literal|"   ...              ... "
block|,
literal|"   .X.              .X. "
block|,
literal|"   ...             o... "
block|,
literal|"                  o     "
block|,
literal|"       ooooo      o     "
block|,
literal|"      o     oo   o      "
block|,
literal|"      o       ooo       "
block|,
literal|"     o                  "
block|,
literal|"     o          ...     "
block|,
literal|"    o           .X.     "
block|,
literal|"  ...           ...     "
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
literal|" oooXooo ooo o ooo oo   "
block|,
literal|" o oXo     o o o   o o  "
block|,
literal|" oooXooo  o  o ooo o o  "
block|,
literal|" o oXo    o  o o   oo   "
block|,
literal|" o oXo   o   o o   o o  "
block|,
literal|" oooXooo ooo o ooo o o  "
block|,
literal|"                        "
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* XPM */
end_comment

begin_decl_stmt
DECL|variable|rulers_comp_xpm
specifier|static
name|char
modifier|*
name|rulers_comp_xpm
index|[]
init|=
block|{
literal|"74 85 192 2"
block|,
literal|"  	c None"
block|,
literal|". 	c #965875D65144"
block|,
literal|"X 	c #9E797DF75965"
block|,
literal|"o 	c #861769A64103"
block|,
literal|"O 	c #69A6555530C2"
block|,
literal|"+ 	c #8E3871C64924"
block|,
literal|"@ 	c #BEFB965869A6"
block|,
literal|"# 	c #AEBA8A286185"
block|,
literal|"$ 	c #79E765954103"
block|,
literal|"% 	c #965879E75144"
block|,
literal|"& 	c #C71B9E7971C6"
block|,
literal|"* 	c #CF3CA28971C6"
block|,
literal|"= 	c #A69982075965"
block|,
literal|"- 	c #A69986175965"
block|,
literal|"; 	c #8E386DB64924"
block|,
literal|": 	c #AEBA86175965"
block|,
literal|"> 	c #D75CA69979E7"
block|,
literal|", 	c #8E3869A64103"
block|,
literal|"< 	c #9E7982075965"
block|,
literal|"1 	c #861765954103"
block|,
literal|"2 	c #9E797DF75144"
block|,
literal|"3 	c #79E75D7538E3"
block|,
literal|"4 	c #9E7979E75144"
block|,
literal|"5 	c #C71B9A6971C6"
block|,
literal|"6 	c #71C6596538E3"
block|,
literal|"7 	c #965871C64924"
block|,
literal|"8 	c #79E761854103"
block|,
literal|"9 	c #492434D32081"
block|,
literal|"0 	c #38E328A21861"
block|,
literal|"q 	c #208118610820"
block|,
literal|"w 	c #28A220811040"
block|,
literal|"e 	c #5965492428A2"
block|,
literal|"r 	c #79E7618538E3"
block|,
literal|"t 	c #28A21C711040"
block|,
literal|"y 	c #28A218610820"
block|,
literal|"u 	c #30C224921040"
block|,
literal|"i 	c #410334D32081"
block|,
literal|"p 	c #492438E32081"
block|,
literal|"a 	c #5144410328A2"
block|,
literal|"s 	c #5965451428A2"
block|,
literal|"d 	c #B6DA8E386185"
block|,
literal|"f 	c #38E32CB21861"
block|,
literal|"g 	c #082008200000"
block|,
literal|"h 	c #B6DA924869A6"
block|,
literal|"j 	c #6185492428A2"
block|,
literal|"k 	c #69A64D3430C2"
block|,
literal|"l 	c #FFFFEBADCF3C"
block|,
literal|"z 	c #49243CF32081"
block|,
literal|"x 	c #410330C21861"
block|,
literal|"c 	c #000000000000"
block|,
literal|"v 	c #BEFB9A6969A6"
block|,
literal|"b 	c #86176DB64924"
block|,
literal|"n 	c #FFFFE79DC71B"
block|,
literal|"m 	c #F7DED75C9E79"
block|,
literal|"M 	c #FFFFE38DBEFB"
block|,
literal|"N 	c #104008200000"
block|,
literal|"B 	c #FFFFC71B6185"
block|,
literal|"V 	c #FFFFAAAA0820"
block|,
literal|"C 	c #FFFFA6990000"
block|,
literal|"Z 	c #FFFFBAEA4103"
block|,
literal|"A 	c #F7DEE38DBEFB"
block|,
literal|"S 	c #28A224921040"
block|,
literal|"D 	c #6185514430C2"
block|,
literal|"F 	c #FFFFB2CA28A2"
block|,
literal|"G 	c #FFFFA2890000"
block|,
literal|"H 	c #FFFFAEBA1861"
block|,
literal|"J 	c #61854D3430C2"
block|,
literal|"K 	c #F7DED34C9658"
block|,
literal|"L 	c #FFFFCB2B71C6"
block|,
literal|"P 	c #71C6555530C2"
block|,
literal|"I 	c #FFFFC30B5144"
block|,
literal|"U 	c #FFFFBEFB4924"
block|,
literal|"Y 	c #30C228A21861"
block|,
literal|"T 	c #FFFFD75C9658"
block|,
literal|"R 	c #186114510820"
block|,
literal|"E 	c #F7DECF3C8617"
block|,
literal|"W 	c #BEFB924869A6"
block|,
literal|"Q 	c #CF3CA69971C6"
block|,
literal|"! 	c #F7DEA2890000"
block|,
literal|"~ 	c #79E76DB630C2"
block|,
literal|"^ 	c #9E7979E72081"
block|,
literal|"/ 	c #CF3C79E71040"
block|,
literal|"( 	c #C71B7DF74103"
block|,
literal|") 	c #30C220811040"
block|,
literal|"_ 	c #51443CF32081"
block|,
literal|"` 	c #69A6514430C2"
block|,
literal|"' 	c #41032CB21861"
block|,
literal|"] 	c #F7DE9E790000"
block|,
literal|"[ 	c #BEFB82074103"
block|,
literal|"{ 	c #CF3C8E381040"
block|,
literal|"} 	c #EFBE92480820"
block|,
literal|"| 	c #C71B924879E7"
block|,
literal|" .	c #20811C711040"
block|,
literal|"..	c #000004100000"
block|,
literal|"X.	c #30C251444924"
block|,
literal|"o.	c #E79D92480820"
block|,
literal|"O.	c #A699514428A2"
block|,
literal|"+.	c #FFFFFBEED75C"
block|,
literal|"@.	c #FFFFFFFFE79D"
block|,
literal|"#.	c #71C65D7538E3"
block|,
literal|"$.	c #10400C300000"
block|,
literal|"%.	c #E79D9A690820"
block|,
literal|"&.	c #C71B82074103"
block|,
literal|"*.	c #FFFFF7DEDF7D"
block|,
literal|"=.	c #DF7DD75CD75C"
block|,
literal|"-.	c #E79DE38DCF3C"
block|,
literal|";.	c #FFFF9E790000"
block|,
literal|":.	c #EFBE96580820"
block|,
literal|">.	c #BEFB75D638E3"
block|,
literal|",.	c #F7DEF7DEE79D"
block|,
literal|"<.	c #F7DEEFBECF3C"
block|,
literal|"1.	c #C71BC71BC71B"
block|,
literal|"2.	c #D75CD34CC71B"
block|,
literal|"3.	c #F7DEF3CECF3C"
block|,
literal|"4.	c #DF7D8A280820"
block|,
literal|"5.	c #A699555528A2"
block|,
literal|"6.	c #DF7DDB6CC71B"
block|,
literal|"7.	c #BEFBBEFBBEFB"
block|,
literal|"8.	c #C71BC30BBEFB"
block|,
literal|"9.	c #AEBA8E386185"
block|,
literal|"0.	c #CF3C8A284924"
block|,
literal|"q.	c #9E79A699A699"
block|,
literal|"w.	c #71C686178617"
block|,
literal|"e.	c #B6DAB6DAB6DA"
block|,
literal|"r.	c #E79DE79DC71B"
block|,
literal|"t.	c #8E3875D65144"
block|,
literal|"y.	c #EFBEEBADCF3C"
block|,
literal|"u.	c #A699AAAAAEBA"
block|,
literal|"i.	c #CF3CCB2BC71B"
block|,
literal|"p.	c #514438E32081"
block|,
literal|"a.	c #492465956185"
block|,
literal|"s.	c #8E3896589658"
block|,
literal|"d.	c #BEFBBAEABEFB"
block|,
literal|"f.	c #861786178617"
block|,
literal|"g.	c #69A669A669A6"
block|,
literal|"h.	c #69A66DB669A6"
block|,
literal|"j.	c #D75C92480820"
block|,
literal|"k.	c #30C234D330C2"
block|,
literal|"l.	c #BEFB75D61861"
block|,
literal|"z.	c #BEFB71C638E3"
block|,
literal|"x.	c #208114510820"
block|,
literal|"c.	c #E79D8A280820"
block|,
literal|"v.	c #AEBAAAAAAEBA"
block|,
literal|"b.	c #861782078617"
block|,
literal|"n.	c #596559655965"
block|,
literal|"m.	c #49244D344924"
block|,
literal|"M.	c #C71B79E730C2"
block|,
literal|"N.	c #AEBAB2CAAEBA"
block|,
literal|"B.	c #AEBAAEBAAEBA"
block|,
literal|"V.	c #A699A699A699"
block|,
literal|"C.	c #C71BA28971C6"
block|,
literal|"Z.	c #082004100000"
block|,
literal|"A.	c #CF3C861730C2"
block|,
literal|"S.	c #8E389A699E79"
block|,
literal|"D.	c #9E79A289A699"
block|,
literal|"F.	c #EFBEE79DC71B"
block|,
literal|"G.	c #9E799A699E79"
block|,
literal|"H.	c #FFFFF7DECF3C"
block|,
literal|"J.	c #79E78A288E38"
block|,
literal|"K.	c #208120812081"
block|,
literal|"L.	c #618565956185"
block|,
literal|"P.	c #F7DE9A690820"
block|,
literal|"I.	c #41035D755965"
block|,
literal|"U.	c #104014511040"
block|,
literal|"Y.	c #D75C7DF71040"
block|,
literal|"T.	c #B6DA69A630C2"
block|,
literal|"R.	c #38E338E338E3"
block|,
literal|"E.	c #965875D628A2"
block|,
literal|"W.	c #EFBE9E7928A2"
block|,
literal|"Q.	c #B6DA86171861"
block|,
literal|"!.	c #CF3C8E384924"
block|,
literal|"~.	c #C71B965879E7"
block|,
literal|"^.	c #618575D671C6"
block|,
literal|"/.	c #79E779E779E7"
block|,
literal|"(.	c #71C675D671C6"
block|,
literal|").	c #AEBA5D7528A2"
block|,
literal|"_.	c #B6DA92486185"
block|,
literal|"`.	c #8E388E388E38"
block|,
literal|"'.	c #BEFB6DB628A2"
block|,
literal|"].	c #DF7D86171040"
block|,
literal|"[.	c #CF3C92481040"
block|,
literal|"{.	c #861771C628A2"
block|,
literal|"}.	c #514451445144"
block|,
literal|"|.	c #BEFB861769A6"
block|,
literal|" X	c #8E3871C628A2"
block|,
literal|".X	c #C71B7DF730C2"
block|,
literal|"XX	c #71C671C671C6"
block|,
literal|"oX	c #B6DABAEABEFB"
block|,
literal|"OX	c #104010401040"
block|,
literal|"+X	c #69A6596538E3"
block|,
literal|"@X	c #9E799E799E79"
block|,
literal|"#X	c #79E77DF779E7"
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"          . X                                                                                                                                       "
block|,
literal|"        o O O X                                                                                                                                     "
block|,
literal|"      + + @ # $                                                                                                                                     "
block|,
literal|"      $ %& * # $ =                                                                                                                                 "
block|,
literal|"      - ; : *> : , X                                                                                                                               "
block|,
literal|"< o =& * : 1 2                                                                                                                             "
block|,
literal|"          = + #&& X 3 4                                                                                                                           "
block|,
literal|"            = . # 5 @ 3 6     # ; 3 ,                                                                                                               "
block|,
literal|"                7 % 4 7 6 8 6 9 0 q w 9 e ;                                                                                                         "
block|,
literal|"                = $ $ r 3 t y u 9 i p a u s 6 =                                                                                                     "
block|,
literal|"                  d # O f g i +     d h 3 j k 3                                   l l                                                               "
block|,
literal|"                      z g x = c -       v b q s                                 n m m M                                                             "
block|,
literal|"                    = t N p c c c X         3 t O                             M B V C Z A                                                           "
block|,
literal|"                    2 S p % c ; ; c O D     - x a                           n B F G C H B M                                                         "
block|,
literal|"                    7 w J   h c o $ c a     s q 9                         n K V C C C G C L M                                                       "
block|,
literal|"                      0 s     # c O P c .   j p f ,                     A I H C C C G C G H U M                                                     "
block|,
literal|"                      x Y =     J c c c c 6 6 c J P .                   L F G C G C C C G G H L T                                                   "
block|,
literal|"                      z R $       r = c o o c r # - + 2 -           n E G G C G C C G G C C C C C F                                                 "
block|,
literal|"                      ; 0 0 =       = c 4 W h x = Q h # 2 + X @   M I F C C d C G ! ~ ^ C C G G / (                                                 "
block|,
literal|"                        7 ) _ .     r c . d& _ ;& * * @ 2 ` `   K F G C 4 ' J C ] [ c { ] G } ( |                                                 "
block|,
literal|"                          ,  .q w  .c ; o D J _ a . : W * 5 @< $ 6 4 C 4 x ..R $ C C c X.{ o.O.          +.@.                                      "
block|,
literal|"                            7 8 0 q 0 #.4 . 3 1 . + ; . # v& * : 7 o r p $.q #.C G G %.c (&.          *.=.-.@.                                    "
block|,
literal|"                                h % J O -& @ 8 1& h . #.#.-& * * h ; O f f G C C C ;.:.>.|         ,.<.1.2.3.                                    "
block|,
literal|"                                      7 % v Q d 4 v * W . o 1 o 2 5 * 5 h 7 O 8 - C G 4.5.          +.6.7.7.7.8.<.@.                                "
block|,
literal|"                                        . # * @ ; + v& 9.. . 8 j . @ 5 *& @ : 1 7 2 0.          ,.6.q.w.e.7.7.2.r.@.                              "
block|,
literal|"                                        2 4& Q W j 2 h o #..< _ 0 ; t.@& Q * = 1 r + .       *.y.7.c c u.e.7.7.i.*.                              "
block|,
literal|"                                          o X *& 3 o = 6 o o p.g $.6 ; ; 7 9.* * @ : o $ 3 # @ =.1.7.e.c a.w.7.7.7.8.1.i.1.                        "
block|,
literal|"                                          2 6 W * # $ + ; o . ` R s c c % ; ; #& *& d # ; k ` = s.d.7.e.c s.7.7.7.7.f.g.h.                        "
block|,
literal|"                                          # ` 2&& , 1 o a ` + e 8 G j.c h< ; 7 : v * * v - . r r . 7.7.7.7.7.7.7.d.k.c c                         "
block|,
literal|"                                            4 o #& = 3 a q q e ; 3 t.G c l.z.    7 , . W Q *& - 3 6 4 7.7.7.7.7.7.7.k.c c                         "
block|,
literal|"                                            E r , * 5 4 p x.a r 6 D 3 ;.c.0.|     - 6 D 1 # h * * * d % 2 ; 7.7.7.v.b.n.m.m.                        "
block|,
literal|"                                        n E G ; J d Q @ r s = C . 6 d } O.          +.# o D O # * Q * v h 4 r . : b...                              "
block|,
literal|"                                      n I F C G . `&& 2 r C G C C / M.          *.=.i.d.. 4 ` # d 5 * * 5 4 r 6 n.                                "
block|,
literal|"                                      K H G G C #.9 @ Q 5 . o C ;.} ( |         *.y.N.B.7.7.V.= + b 2 d v *& C.: ` a ;                             "
block|,
literal|"                                  A L C C C W O Z.$.b 5 Q X 6 C c.O.          +.6.e.c c 7.7.7.7.7.# + b . d& *& P f p o                           "
block|,
literal|"                                n I F G G G 6 R c ' ` # * h + 4 A.          *.=.i.7.S.D.7.7.7.7.7.7.7.% + o o # - 6 O j O .                         "
block|,
literal|"                              n K H C C C G #.t x % . X v& d 2 #         ,.F.e.e.7.7.7.7.7.7.7.7.7.7.B.G.< ; o r p s 1 + . .                       "
block|,
literal|"                            A B V G C C G C G ; = C # ; 4 5& # -       H.=.e.c J.7.7.7.7.7.7.7.7.7.7.n.K.    = s q Y #.9.h % %                     "
block|,
literal|"                          n B F C G G C G C C G G C C 4 1 - * d . -   ,.6.i.e.w.c J.e.7.7.7.7.7.7.B.L.h.        - P O ` 7 h @ , +                   "
block|,
literal|"                        M m C C C C C C C G G C C G G P.o .&& # o : y.e.d.7.7.J.I.B.7.7.7.7.7.e.G.U.                6 3 ; % p.o 2                 "
block|,
literal|"                        H H G G C C C C C C G G C G Y.T.  1 = * h 6 X N.c S.7.7.e.B.d.7.7.7.7.d.m.R.                  5 d E.J i ' t ;               "
block|,
literal|"                        W.4.G C C C :.Q.P.G C C ;.c.!.~.  #.t.* * 2 r N.^.V.7.7.7.7.7.7.7.7.v./.L.(.                        # d - 3 r               "
block|,
literal|"                        | ).P.G G C c X.{ G G G :.5.      4 1 _.* * 3 + 7.7.7.7.7.7.7.7.7.d.`...                                                    "
block|,
literal|"                            '.].C C %.[.~ {.C />.          ; ; @& 8 , 7.7.7.7.7.7.7.7.d.}.}.                                                      "
block|,
literal|"                            |.A.} G G C  Xc }&.|         ,.. + h * @ + 7 7.7.7.7.7.7.v.`.m.h.                                                      "
block|,
literal|"                                5.:.C G C c.O.          *.-.7.. . @> W $ 1 7.7.7.d.7./...                                                          "
block|,
literal|"                                  M.Y.G /&.          +.=.q.c = o - *& + 6 7.7.7.e.}.L.                                                            "
block|,
literal|"                                  |..X:.>.~.        ,.y.8.s.a.B.; X& * d b , 7.B.G.R.XX                                                            "
block|,
literal|"                                      5.          +.6.8.7.d.e.7.7.; # * * X _ @ L.U.                                                                "
block|,
literal|"                                                *.=.c w.e.7.7.7.7.= = C.Q @ ` 4 h.                                                                  "
block|,
literal|"                                              ,.<.7.w.c u.oX7.7.7.# . # *& = 6 :                                                                   "
block|,
literal|"                                              =.8.7.e.c a.w.7.7.7.7.2 o #& h ` .                                                                   "
block|,
literal|"                                                i.XXG.e.w.s.7.7.7.7.7.6 7 * 5 4 ,                                                                   "
block|,
literal|"                                                  OXg.e.d.7.7.7.7.7.d.. , d W 7 O J                                                                 "
block|,
literal|"                                                    h.k.B.7.7.7.7.d.}.m.b +X+ s q w 7                                                               "
block|,
literal|"                                                      }./.@X7.7.B.b.n.h.. a $ $ e t 1                                                               "
block|,
literal|"                                                        K.}.d.d.f...      1 _ 9 #.r #.+                                                             "
block|,
literal|"                                                          #Xk.k.n.          #.u o h ; $ W                                                           "
block|,
literal|"                                                            c c m.            8 1 d 9.1 %                                                           "
block|,
literal|"                                                            c c m.              + + # 3 r d                                                         "
block|,
literal|"                                                                                  . 6 _ _ .                                                         "
block|,
literal|"< $ J 1                                                         "
block|,
literal|"                                                                                        4 $ #                                                       "
block|,
literal|"                                                                                        h ; d                                                       "
block|,
literal|"                                                                                          h                                                         "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|,
literal|"                                                                                                                                                    "
block|}
decl_stmt|;
end_decl_stmt

end_unit


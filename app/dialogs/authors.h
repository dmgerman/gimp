begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* NOTE: This file is autogenerated from authors.xml, do not edit it. */
end_comment

begin_decl_stmt
DECL|variable|authors
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|authors
index|[]
init|=
block|{
literal|"Spencer Kimball"
block|,
literal|"Peter Mattis"
block|,
literal|"Lauri Alanko"
block|,
literal|"Shawn Amundson"
block|,
literal|"Sven Anders"
block|,
literal|"Henrik Brix Andersen"
block|,
literal|"Karl-Johan Andersson"
block|,
literal|"John Beale"
block|,
literal|"Zach Beane"
block|,
literal|"Tom Bech"
block|,
literal|"Marc Bless"
block|,
literal|"Edward Blevins"
block|,
literal|"Reagan Blundell"
block|,
literal|"Xavier Bouchoux"
block|,
literal|"Roberto Boyd"
block|,
literal|"Stanislav Brabec"
block|,
literal|"Hans Breuer"
block|,
literal|"Simon Budig"
block|,
literal|"JoÃ£o S. O. Bueno Calligaris"
block|,
literal|"Seth Burgess"
block|,
literal|"Brent Burton"
block|,
literal|"Francisco Bustamante"
block|,
literal|"Albert Cahalan"
block|,
literal|"Lapo Calamandrei"
block|,
literal|"George J. Carrette"
block|,
literal|"Sean Cier"
block|,
literal|"Winston Chang"
block|,
literal|"Zbigniew Chyla"
block|,
literal|"Branko Collin"
block|,
literal|"Ed Connel"
block|,
literal|"Piers Cornwell"
block|,
literal|"Daniel Cotting"
block|,
literal|"Jay Cox"
block|,
literal|"Kevin Cozens"
block|,
literal|"Brian Degenhardt"
block|,
literal|"Karine Delvare"
block|,
literal|"Andreas Dilger"
block|,
literal|"Austin Donnelly"
block|,
literal|"Scott Draves"
block|,
literal|"Daniel Dunbar"
block|,
literal|"Misha Dynin"
block|,
literal|"Daniel Egger"
block|,
literal|"Morton Eriksen"
block|,
literal|"Larry Ewing"
block|,
literal|"Nick Fetchak"
block|,
literal|"Shlomi Fish"
block|,
literal|"David Forsyth"
block|,
literal|"Raphael Francois"
block|,
literal|"Jochen Friedrich"
block|,
literal|"Jordi Gay"
block|,
literal|"Jim Geuther"
block|,
literal|"Graeme Gill"
block|,
literal|"Pedro Gimeno"
block|,
literal|"Scott Goehring"
block|,
literal|"Heiko Goller"
block|,
literal|"Marcelo de Gomensoro Malheiros"
block|,
literal|"David Gowers"
block|,
literal|"Cameron Gregory"
block|,
literal|"Pavel Grinfeld"
block|,
literal|"Dov Grobgeld"
block|,
literal|"Michael Hammel"
block|,
literal|"James Henstridge"
block|,
literal|"Eric Hernes"
block|,
literal|"David Hodson"
block|,
literal|"Christoph Hoegl"
block|,
literal|"Wolfgang Hofer"
block|,
literal|"Alan Horkan"
block|,
literal|"Jan HubiÄka"
block|,
literal|"Ben Jackson"
block|,
literal|"Tim Janik"
block|,
literal|"RÃ³man Joost"
block|,
literal|"Geert Jordaens"
block|,
literal|"Andrew Kieschnick"
block|,
literal|"Peter Kirchgessner"
block|,
literal|"Philipp Klaus"
block|,
literal|"David Koblas"
block|,
literal|"Daniel Kobras"
block|,
literal|"Ãyvind KolÃ¥s"
block|,
literal|"Robert L Krawitz"
block|,
literal|"Tuomas Kuosmanen"
block|,
literal|"Olof S Kylander"
block|,
literal|"Karl La Rocca"
block|,
literal|"Philip Lafleur"
block|,
literal|"Chris Lahey"
block|,
literal|"Nick Lamb"
block|,
literal|"Marco Lamberto"
block|,
literal|"Jens Lautenbacher"
block|,
literal|"Laramie Leavitt"
block|,
literal|"Elliot Lee"
block|,
literal|"Marc Lehmann"
block|,
literal|"Ray Lehtiniemi"
block|,
literal|"Raph Levien"
block|,
literal|"Wing Tung Leung"
block|,
literal|"Adrian Likins"
block|,
literal|"Tor Lillqvist"
block|,
literal|"Ingo LÃ¼tkebohle"
block|,
literal|"Josh MacDonald"
block|,
literal|"Ed Mackey"
block|,
literal|"Vidar Madsen"
block|,
literal|"Ian Main"
block|,
literal|"Kjartan Maraas"
block|,
literal|"Kelly Martin"
block|,
literal|"Torsten Martinsen"
block|,
literal|"Gordon Matzigkeit"
block|,
literal|"Gregory McLean"
block|,
literal|"Federico Mena Quintero"
block|,
literal|"Jim Meyer"
block|,
literal|"James Mitchell"
block|,
literal|"Hirotsuna Mizuno"
block|,
literal|"David Monniaux"
block|,
literal|"Adam D Moss"
block|,
literal|"Balazs Nagy"
block|,
literal|"Yukihiro Nakai"
block|,
literal|"Shuji Narazaki"
block|,
literal|"Felix Natter"
block|,
literal|"Michael Natterer"
block|,
literal|"David Neary"
block|,
literal|"David Necas"
block|,
literal|"Sven Neumann"
block|,
literal|"Andreas Nilsson"
block|,
literal|"Stephen Robert Norris"
block|,
literal|"Tim Newsome"
block|,
literal|"Erik Nygren"
block|,
literal|"Miles O'Neal"
block|,
literal|"David Odin"
block|,
literal|"Robert Ãgren"
block|,
literal|"Thom van Os"
block|,
literal|"Garry R. Osgood"
block|,
literal|"Alan Paeth"
block|,
literal|"Jay Painter"
block|,
literal|"Ville PÃ¤tsi"
block|,
literal|"Akkana Peck"
block|,
literal|"Asbjorn Pettersen"
block|,
literal|"Mike Phillips"
block|,
literal|"Ari Pollak"
block|,
literal|"RaphaÃ«l Quinet"
block|,
literal|"Tom Rathborne"
block|,
literal|"Jens Restemeier"
block|,
literal|"Maurits Rijk"
block|,
literal|"Daniel Risacher"
block|,
literal|"James Robinson"
block|,
literal|"Guillermo S. Romero"
block|,
literal|"Tim Rowley"
block|,
literal|"Mike Schaeffer"
block|,
literal|"John Schlag"
block|,
literal|"Norbert Schmitz"
block|,
literal|"Thorsten Schnier"
block|,
literal|"Alexander Schulz"
block|,
literal|"Michael Schumacher"
block|,
literal|"Tracy Scott"
block|,
literal|"Craig Setera"
block|,
literal|"Aaron Sherman"
block|,
literal|"Manish Singh"
block|,
literal|"William Skaggs"
block|,
literal|"Daniel Skarda"
block|,
literal|"Adam Spiers"
block|,
literal|"Jakub Steiner"
block|,
literal|"Nathan Summers"
block|,
literal|"Mike Sweet"
block|,
literal|"William Szilveszter"
block|,
literal|"Eiichi Takamori"
block|,
literal|"Tristan Tarrant"
block|,
literal|"Michael Taylor"
block|,
literal|"Owen Taylor"
block|,
literal|"Ian Tester"
block|,
literal|"Andy Thomas"
block|,
literal|"Kevin Turner"
block|,
literal|"Brion Vibber"
block|,
literal|"Helvetix Victorinox"
block|,
literal|"Rebecca Walter"
block|,
literal|"Martin Weber"
block|,
literal|"James Wang"
block|,
literal|"Kris Wehner"
block|,
literal|"Nigel Wetten"
block|,
literal|"Calvin Williamson"
block|,
literal|"Matthew Wilson"
block|,
literal|"Shirasaki Yasuhiro"
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|artists
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|artists
index|[]
init|=
block|{
literal|"Lapo Calamandrei"
block|,
literal|"Tuomas Kuosmanen"
block|,
literal|"Karl La Rocca"
block|,
literal|"Andreas Nilsson"
block|,
literal|"Mike Schaeffer"
block|,
literal|"Carol Spears"
block|,
literal|"Jakub Steiner"
block|,
literal|"William Szilveszter"
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|documenters
specifier|static
specifier|const
name|gchar
modifier|*
specifier|const
name|documenters
index|[]
init|=
block|{
literal|"Carey Bunks"
block|,
literal|"Michael Hammel"
block|,
literal|"Simon Janes"
block|,
literal|"Karin Kylander"
block|,
literal|"Olof S Kylander"
block|,
literal|"Ed Mackey"
block|,
literal|"Ian Main"
block|,
literal|"James Robinson"
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

end_unit


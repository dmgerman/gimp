begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* NOTE: This file is autogenerated by authorsgen.pl. */
end_comment

begin_comment
comment|/*  * The main authors are Spencer Kimball and Peter Mattis.  */
end_comment

begin_decl_stmt
DECL|variable|authors
specifier|static
name|gchar
modifier|*
name|authors
index|[]
init|=
block|{
literal|"Lauri Alanko"
block|,
literal|"Shawn Amundson"
block|,
literal|"Sven Anders"
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
literal|"Robert Brady"
block|,
literal|"Hans Breuer"
block|,
literal|"Simon Budig"
block|,
literal|"Carey Bunks"
block|,
literal|"Seth Burgess"
block|,
literal|"Brent Burton"
block|,
literal|"Francisco Bustamante"
block|,
literal|"Albert Cahalan"
block|,
literal|"Sean Cier"
block|,
literal|"Winston Chang"
block|,
literal|"Kenneth Christiansen"
block|,
literal|"Zbigniew Chyla"
block|,
literal|"Ed Connel"
block|,
literal|"Piers Cornwell"
block|,
literal|"Daniel Cotting"
block|,
literal|"Jay Cox"
block|,
literal|"Brian Degenhardt"
block|,
literal|"Gert Dewit"
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
literal|"Valek Filippov"
block|,
literal|"David Forsyth"
block|,
literal|"Raphael Francois"
block|,
literal|"Jochen Friedrich"
block|,
literal|"Sami Gerdt"
block|,
literal|"Jim Geuther"
block|,
literal|"Graeme Gill"
block|,
literal|"Scott Goehring"
block|,
literal|"Heiko Goller"
block|,
literal|"Marcelo de Gomensoro Malheiros"
block|,
literal|"Pavel Grinfeld"
block|,
literal|"Michael Hammel"
block|,
literal|"Henrik Hansen"
block|,
literal|"Ville HautamÃ¤ki"
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
literal|"Jan Hubicka"
block|,
literal|"Andreas Hyden"
block|,
literal|"Ben Jackson"
block|,
literal|"Krzysztof Jakubowski"
block|,
literal|"Simon Janes"
block|,
literal|"Tim Janik"
block|,
literal|"Fellmann Joaquim"
block|,
literal|"Andrew Kieschnick"
block|,
literal|"Peter Kirchgessner"
block|,
literal|"Philipp Klaus"
block|,
literal|"David Koblas"
block|,
literal|"Robert L Krawitz"
block|,
literal|"Tuomas Kuosmanen"
block|,
literal|"Karin Kylander"
block|,
literal|"Olof S Kylander"
block|,
literal|"Karl La Rocca"
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
literal|"Ingo Luetkebohle"
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
literal|"Daniele Medri"
block|,
literal|"Federico Mena Quintero"
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
literal|"Sung-Hyun Nam"
block|,
literal|"Shuji Narazaki"
block|,
literal|"Felix Natter"
block|,
literal|"Michael Natterer"
block|,
literal|"David Neary"
block|,
literal|"Sven Neumann"
block|,
literal|"Stephen Robert Norris"
block|,
literal|"Tim Newsome"
block|,
literal|"Erik Nygren"
block|,
literal|"Miles O'Neal"
block|,
literal|"David Odin "
block|,
literal|"Thom van Os"
block|,
literal|"Garry R. Osgood"
block|,
literal|"Alan Paeth"
block|,
literal|"Jay Painter"
block|,
literal|"Sergey Panov"
block|,
literal|"Asbjorn Pettersen"
block|,
literal|"Mike Phillips"
block|,
literal|"Artur Polaczynski"
block|,
literal|"Raphael Quinet"
block|,
literal|"Tom Rathborne"
block|,
literal|"Vincent Renardias"
block|,
literal|"Jens Restemeier"
block|,
literal|"Maurits Rijk"
block|,
literal|"Daniel Risacher"
block|,
literal|"James Robinson"
block|,
literal|"Tim Rowley"
block|,
literal|"Pablo Saratxaga"
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
literal|"Tracy Scott"
block|,
literal|"Craig Setera"
block|,
literal|"Aaron Sherman"
block|,
literal|"Manish Singh"
block|,
literal|"Daniel Skarda"
block|,
literal|"Adam Spiers"
block|,
literal|"Nathan Summers"
block|,
literal|"Mike Sweet"
block|,
literal|"Yuri Syrota"
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
block|, }
decl_stmt|;
end_decl_stmt

end_unit


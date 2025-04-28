#ifndef __TEST_DATA__H
#define __TEST_DATA__H

// Define test data for PR1
const char* test_data_pr1_str = "PERSON;98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954\n" \
								"PERSON;33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867\n" \
								"PERSON;55565432Z;Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972\n" \
								"PERSON;12345672C;Anne;Huiller;666789789;anne.huiller@example.com;rue percebe, 125;22222;12/01/1969\n" \
								"PERSON;47051307Z;James;Bond;707070707;bond.jamesbond@example.com;Downing street, 10;07077;12/01/1952\n" \
								"SUBSCRIPTION;1;98765432J;01/01/2025;31/12/2025;Free;0;1\n" \
								"SUBSCRIPTION;2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3\n" \
								"SUBSCRIPTION;3;12345672C;15/06/2025;14/06/2026;Standard;29.95;3\n" \
								"SUBSCRIPTION;4;55565432Z;21/03/2025;20/03/2026;Free;0;1\n" \
								"SUBSCRIPTION;5;47051307Z;01/01/2023;31/12/2028;Premium;29.95;3\n" \
								"FILM;Interstellar;02:49;4;07/11/2014;4.8;0\n" \
								"FILM;Blade Runner 2049;02:44;4;06/10/2017;4.6;1\n" \
								"FILM;The Matrix;02:16;4;31/03/1999;4.9;1\n" \
								"FILM;Inception;02:28;0;16/07/2010;4.7;1\n" \
								"FILM;Mad Max: Fury Road;02:00;0;15/05/2015;4.5;0\n" \
								"FILM;Die Hard;02:12;0;15/07/1988;4.3;1\n" \
								"FILM;The Grand Budapest Hotel;01:39;1;28/02/2014;4.2;0\n" \
								"FILM;Superbad;01:53;1;17/08/2007;4.0;1\n" \
								"FILM;Monty Python and the Holy Grail;01:31;1;03/04/1975;4.8;1\n" \
								"FILM;Forrest Gump;02:22;2;06/07/1994;4.9;0\n" \
								"FILM;The Green Mile;03:09;2;10/12/1999;4.8;1\n" \
								"FILM;The Pursuit of Happyness;01:57;2;15/12/2006;4.4;1\n" \
								"FILM;The Shining;02:26;3;23/05/1980;4.5;1\n" \
								"FILM;A Nightmare on Elm Street;01:31;3;09/11/1984;4.1;1\n" \
								"FILM;Get Out;01:44;3;24/02/2017;4.3;1\n";

// Define test data for PR1
const char* test_data_pr2_str = "PERSON;98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954\n" \
								"PERSON;33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867\n" \
								"PERSON;55565432Z;Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972\n" \
								"PERSON;12345672C;Anne;Huiller;666789789;anne.huiller@example.com;rue percebe, 125;22222;12/01/1969\n" \
								"PERSON;47051307Z;James;Bond;707070707;bond.jamesbond@example.com;Downing street, 10;07077;12/01/1952\n" \
								"SUBSCRIPTION;1;98765432J;01/01/2025;31/12/2025;Free;0;1\n" \
								"SUBSCRIPTION;2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3\n" \
								"SUBSCRIPTION;3;12345672C;15/06/2025;14/06/2026;Standard;29.95;3\n" \
								"SUBSCRIPTION;4;55565432Z;21/03/2025;20/03/2026;Free;0;1\n" \
								"SUBSCRIPTION;5;47051307Z;01/01/2023;31/12/2028;Premium;29.95;3\n" \
								"FILM;Interstellar;02:49;4;07/11/2014;4.8;0\n" \
								"FILM;Blade Runner 2049;02:44;4;06/10/2017;4.6;1\n" \
								"FILM;The Matrix;02:16;4;31/03/1999;4.9;1\n" \
								"FILM;Inception;02:28;0;16/07/2010;4.7;1\n" \
								"FILM;Mad Max: Fury Road;02:00;0;15/05/2015;4.5;0\n" \
								"FILM;Die Hard;02:12;0;15/07/1988;4.3;1\n" \
								"FILM;The Grand Budapest Hotel;01:39;1;28/02/2014;4.2;0\n" \
								"FILM;Superbad;01:53;1;17/08/2007;4.0;1\n" \
								"FILM;Monty Python and the Holy Grail;01:31;1;03/04/1975;4.8;1\n" \
								"FILM;Forrest Gump;02:22;2;06/07/1994;4.9;0\n" \
								"FILM;The Green Mile;03:09;2;10/12/1999;4.8;1\n" \
								"FILM;The Pursuit of Happyness;01:57;2;15/12/2006;4.4;1\n" \
								"FILM;The Shining;02:26;3;23/05/1980;4.5;1\n" \
								"FILM;A Nightmare on Elm Street;01:31;3;09/11/1984;4.1;1\n" \
								"FILM;Get Out;01:44;3;24/02/2017;4.3;1\n"
                                "SHOW;Breaking Bad;1;20/01/2008;1;Pilot;00:58;4.9\n"
                                "SHOW;Breaking Bad;1;27/01/2008;2;Cat's in the Bag...;00:48;4.8\n"
                                "SHOW;Stranger Things;1;15/07/2016;1;The Vanishing of Will Byers;00:47;4.7\n"
                                "SHOW;Stranger Things;1;15/07/2016;2;The Weirdo on Maple Street;00:55;4.6\n"
                                "SHOW;The Office;1;24/03/2005;1;Pilot;00:23;4.0\n"
                                "SHOW;The Office;1;29/03/2005;2;Diversity Day;00:22;4.2\n";


                                
                                
                                                  
#endif // TEST_DATA__H
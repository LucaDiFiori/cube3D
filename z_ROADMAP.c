/*_______________________________LINK APERTI__________________________________*/
https://github.com/LucaDiFiori/So_long/blob/main/so_long/map_checks.c
https://cdn.intra.42.fr/pdf/pdf/116175/en.subject.pdf
https://github.com/mcombeau/cub3D/blob/main/sources/parsing/get_file_data.c
https://github.com/mcombeau/cub3D/blob/main/sources/parsing/parse_data.c#L39

gitbook minrt: https://42-cursus.gitbook.io/guide/rank-04/minirt/building-the-thing


                                  youtube
https://www.youtube.com/watch?v=xW8skO7MFYw&ab_channel=javidx9



/*____________________________________________________________________________*/




/*_______________________________GIT_HUB_REPO_________________________________*/
/*0- elengo di repo*/
https://github.com/topics/cub3d

/*1*/
https://github.com/ael-bekk/Cub3d-Advanced-Raycasting

/*2*/
https://github.com/mcombeau/cub3D/blob/main/textures/wolfenstein/purple_stone.xpm

/*3-> repo sul rey casting*/
https://github.com/Saxsori/ray-cast
/*____________________________________________________________________________*/







/*_________________________________MAPP_______________________________________*/
/*Info generali---------------------------------------------------------------*/
* "La mappa può contenere 6 caratteri:" 
  "0 1  and N,S,E or W" for the player’s start position and spawning
  orientation.
  /*NOTA: Questa funzionalità può essere impmeneta:
          1) estraendo una singola riga con gnl e controllando se c'è un carattere
		     non valito. Solo dopo creo la matrice
		  2) Dopo aver creato la matrice la scorro per vedere se ci sono parametri 
		     non validi.
			 
		  Probabilmente opterò per la prima*/

* La "mappa deve essere chiusa e circondata da muri"

* La mappa può avere forme irregolari

* La mappa dovrà essere "parsata" come da file: Gli "spazi" sono validi 
  (a nostra discrezione come gestirli).

* Nei git linkati sopra ci sono delle mappe con il "nemico" segnato con "H"
/*----------------------------------------------------------------------------*/



/*info sul file della mappa---------------------------------------------------*/
* il file della mappa termina con .cub                          (funzione fatta)

* il "file della mappa" contiene i seguenti "elementi":
  i) la mappa
  ii) percorso delle texture per i muri nord, sud, est, ovest
  iii) colore del soffitto e del pavimento
 
* All interno del file "l elemento mappa dovrà essere sempre l ultimo".
  Gli altri elementi potranno essere messi in qualsiasi ordine 

* All interno del file, fatta eccezione per la mappa, "ogni elemento può 
  essere separato da una o più linee vuote"

* All interno del file, fatta eccezione per la mappa, "ogni dato di un elemento
  può essere separato da un numero arbitrario di spazi"


* La "prima infoirmazione" di ogni elemente presente nel file della mappa
  (fatta eccezione per la mappa stessa) sarà il "type identifier" composto da 
  "1 o 2 caratteri" seguito dalle informazioni specifiche per ogni oggetto 
  
  Esempio:          NO ./path_to_the_north_texture
  - identifier:		NO
  - informazione:	./path_to_the_north_texture

  identifier ed informazione devono seguire questo specifico ordine

* Gli "ELEMENTI" saranno:
  - NO ./path_to_the_north_texture
  - SO ./path_to_the_south_texture
  - WE ./path_to_the_west_texture
  - EA ./path_to_the_east_texture
  - F 220,100,0   
    Dove: F = floar |  200, 100, 0 = colori in R,G,B nel range [0, 255]
  - C 225,30,0
	Dove: C = Ceiling 




/*Esempio---------------------------------------------------------------------*/
*"Esempio di un file.cub mappa valido:"

NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

		1111111111111111111111111
		1000000000110000000000001
		1011000001110000000000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
/*----------------------------------------------------------------------------*/
/*____________________________________________________________________________*/





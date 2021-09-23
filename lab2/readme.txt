/**********************************************************************
 *  Knäcka lösenord readme.txt
 **********************************************************************/

 Ungefärligt antal timmar spenderade på labben (valfritt): 10 timmar

/**********************************************************************
 *  Ge en högnivåbeskrivning av ditt program decrypt.c.
 **********************************************************************/
Vi utgår från lösningsiden där vi sparar en specifik del av lösenord kombinationer i en unordered_map med en hash funktion. 
För resterande kombinationer kontrollerar vi om svaret finns i vår symboltabell. 
Om vi hittar svaret i tabellen skriver vi ut den. På så sätt körs programmet betydligt snabbare än brute.cc

/**********************************************************************
 *  Beskriv symboltabellen du använt för decrypt.c.
 **********************************************************************/
Vi har använt std::unordered_map för att spara ett Key objekt som båda nyckel och värde.
 För att kunna göra det behövde vi skapa en egen hash-funktion som kunde snabbt konvertera en Key-objekt till 
 en integer och det skulle vara unik så att vi inte få några kollisioner annars 
 skulle vi riskera att programmet körs långsamt.
  Vår hash-funktion skapar en heltal som motsvarar Key-objektet i binär-form. 
  Till exempel lösenordet “b” som i binär formatet är “00001” konverteras till heltalet 1, “c” till 2 osv. 
  Den har en tidskomplexitet av O(n) där n är antal bitar i lösenordet.

/**********************************************************************
 *  Ge de dekrypterade versionerna av alla lösenord med 8 och 10
 *  bokstäver i uppgiften du lyckades knäca med DIN kod.
 **********************************************************************/


8 bokstäver         10 bokstäver
-----------         ------------
congrats            completely
ibqfehan            nbryjimvrd
mqubzd45            unbreakabl 
youfound            cryptogram  
theright            ormaybenot
aeiqrsd4
solution


/****************************************************************************
 *  Hur lång tid använder brute.c för att knäcka lösenord av en viss storlek?
 *  Ge en uppskattning (baserad på tidskomplexiteten)  markerad med en asterisk
 *  om det tar längre tid än vad du orkar vänta. Ge en kort motivering för
 *  dina uppskattningar.
 ***************************************************************************/


Char     Brute     
--------------
 4        0 sekunder
 5        3 sekunder
 6        128 sekunder (2 ^ 30) * c = 128 => c = 0,000000119
 8        * (2 ^ 40) * c är ungefär 130841 sekunder dvs 2180 dvs 90 dygn 


/******************************************************************************
 *  Hur lång tid använder decrypt.c för att knäcka lösenord av en viss storlek?
 *  Hur mycket minne använder programmet?
 *  Ge en uppskattning markerad med en asterisk om det tar längre tid än vad
 *  du orkar vänta. Ge en kort motivering för dina uppskattningar.
 ******************************************************************************/

Char    Tid (sekunder)    Minne (bytes)
----------------------------------------
Vi sparar alla kombinationer med ett lösenord som är 
hälften av den orginala lösenordet. ex xxxxx xxxxx då sparar vi xxxxx i olika kombinationer
vilket i detta fall blir 2 ^ 5 medan den originala lösenordet består av 10 bitar så:
Minnet som programmet tar är: (2 ^ (N/2)) * N

6          0 sekund       (2 ^ (30 / 2)) * 30 = 122880 bytes
8          0 sekund       (2 ^ (40 / 2)) * 40 = 5242880 bytes i praktiken visar htop ungefär 18 000 000 bytes
10         59 sekunder    (2 ^ (50 / 2)) * 50 = 209715200 bytes i praktiken visar htop ungefär 700 000 000 bytes
12         *              (2 ^ (60 / 2)) * 60 = 4026531840 bytes

/*************************************************************************
 * Hur många operationer använder brute.c för ett N-bitars lösenord?
 * Hur många operationer använder din decrypt.c för ett N-bitars lösenord?
 * Använd ordo-notation.
 *************************************************************************/
brute är av typen O(2 ^ n) där n är antal bitar i lösenordet. Eftersom brute
har en exponentiell tillväxthastighet så tar det vädligt mycket tid när antal
karaktär ökar i lösenordet.

Vår decrypt behöver iterera 2 * (2 ^ n/2) gånger vilket är 2 ^ ( (2 + n) / 2).
För ett lösenord med 4 karaktär dvs 20 bitar behöver brute 2 ^ 20 iterationer medan 
vår decrypt tar 2 ^ 11 iterationer. Även vår decrypt har enn exponentiell tillväxthastighet
O(2 ^ n) fast skillnaden är att med samma hårdvara klarar vi att knäcka längre lösenord
tack vare mindre exponent jämfört med brute. 

/*************************************************************************
 * Vilka egenskaper skulle ni leta efter i en hashfunktion för att
 * försäkra er om att den är "säker"?
 *************************************************************************/
Vi vill ha en hash-funktion som skapar så unika hashar som möjligt och det skulle 
vara så snabb som möjligt samt mindre kollisioner.
/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

 Ungef�rligt antal timmar spenderade p� labben (valfritt): 3 timmar

/**********************************************************************
 * Empirisk analys
 *
 * Fyll i tabellen nedan med riktiga k�rtider i sekunder n�r det k�nns
 * vettigt att v�nta p� hela ber�kningen.
 * Ge uppskattningar av k�rtiden (baserat p� tidskomplexiteten)
 * i �vriga fall.
 *
 **********************************************************************/
    
      N       brute (s)      sortering (s)
 ----------------------------------
    150         0.004            0.004                    // N ^ 4 * C = tidskomplexiteten                                                                        
    200         0.013            0.019                    // 150 ^ 4 * C = 4 ms
    300         0.028            0.014                    // C = 0,000000008
    400         0.072            0.029                    // uppskattning = 12800 ^ 4 * 0,000000008 = 214748364 ms = 214748 s = 3579 min = 59 dygn
    800         0.394            0.057
   1600         3.2              0.164
   3200         25.2             0.624
   6400         206.3            2.7
  12800         59 dygn          12


/**********************************************************************
 * Teoretisk analys
 *
 * Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som en funktion
 * av N. Ge en kort motivering.
 
 * Matchar brute-l�sningen sitt v�rstafall i praktiken, eller har den
 * ett medelfall som �r b�ttre?
 *
 **********************************************************************/

Brute: 
 -- Brute har tidskomplexiteten av ordo(N ^ 4). Den har fyra loopar som körs 
     ett antal gånger som är beroende på N. Om man ignorerar konstanter så
     visar det sig att den har en tidskomplexitet av ordo(N ^  4).
     Brute lösning har ett bättre medelfall när vi räknar ut ifrån tidskomplexiteten. 

Sortering: 
 -- Vi tycker att sorteringslösningen har en tidskomplexitet av ordo((N ^ 2) * log N). Detta är för att 
     vi använder std::sort som har en tidskomplexitet av ordo(N * log N) och vi i yttre while loopen
     kör sorteringen N - 2 gånger. Om vi ignorerar konstanter får vi som resultat en tidskomplexitet
     som är N ^ 2 * log N. 

/**********************************************************************
 * Energianv�ndning
 *
 * Antag att du anv�nder m�nsterigenk�nningsprogrammet f�r att analysera
 * data fr�n en kamera. Kameran sitter i en byggnad och tar en bild
 * p� stommen av byggnaden var 30:e minut. Bilden f�rbehandlas sedan
 * lite, innan punkter som representerar stommen skickas till
 * m�nsterigenk�nningsprogrammet. Hittas inte tillr�ckligt m�nga raka
 * linjer s� betyder det att n�got h�ller p� att g� s�nder, och
 * att byggnaden beh�ver noggrannare inspektion.
 *
 * Hur mycket energi sparar du p� ett �r om du anv�nder din snabbare
 * sorteringsl�sning i st�llet f�r brute-l�sningen? Du kan anta f�ljande:
 * - Systemet k�rs 24/7 under hela �ret.
 * - Inget annat k�rs p� det h�r systemet.
 * - Systemet drar 8 W n�r det inte g�r n�got (idle)  
 * - Systemet drar 36 W n�r det arbetar (med 1 k�rna) 
 * - R�kna med att ditt program k�rs var 30:e minut (= 2 g�nger/timme)
 * - F�r- och efterbehandling �r snabba, s� vi kan bortse fr�n dem
 * - Indata till programmet inneh�ller ca 6400 punkter
 * - Det �r inte skott�r (= 365 dagar)
 *
 * Att j�mf�ra med drar en kombinerad kyl/frys ca 200 kWh per �r
 * (enligt Energimyndigheten).
 *
 * Kom ih�g: energi m�ts ofta i kWh, vilket �r:
 *  energi (kWh) = effekt (kW) * tid (h)
 *
 * Tips: ett s�tt att r�kna p� �r att f�rst r�kna f�rbrukningen av
 * ett system som inte g�r n�got p� ett helt �r, sedan l�gga till
 * den extra f�rbrukningen (36 W - 8 W = 28 W) f�r tiden som systemet
 * �r aktiv.
 *
 * (Siffrorna �r l�st baserade p� en Intel i9-9900K, vi r�knar bara p�
 * CPU:n f�r enkelhets skull, besparingarna blir sannolikt st�rre om
 * vi r�knar p� st�rre delar av systemet, �ven om andra komponenter
 * ocks� drar str�m i "idle".)
 *
 **********************************************************************/
F�rbrukning av brute p� ett �r: 95 kWh

// 8 * 24 * 365 = 70080 Wh = 70 kWh  // When idle
// 6 min * 24 * 365 = 52560 min / year => 876 h / year => 24528 Wh => 25 kWh // When working 


F�rbrukning av sotering p� ett �r: 70.4 kWh
// 8 * 24 * 365 = 70080 Wh = 70 kWh  // When idle
// 6 sec * 24 * 365 =  52560 sec / year => 876 min / year => 14.6 h / year => (14.6 * 28) => 408 Wh => 0.4 kWh // When working 

Skillnad: 24.6 kWh


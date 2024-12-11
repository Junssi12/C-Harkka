Jussi Koivurinta
C++ Harjoitustyö

Harjoitustyö on tehty 2–3 pisteen tavoitteella ja kriteereillä. Harjoitustyön tarkoituksena on luoda C++ koodi, joka toimii Hotellin huonevaraus ohjelmana. Ohjelmassa käyttäjä voi tehdä uusia varauksia, tarkastella olemassa olevia varauksia ja tietysti sulkea ohjelman. Ohjelma hyödyntää rakenteita ja taulukoita tietojen tallentamiseen ja käsittelyyn.

Ensimmäiseksi koodiin määritetään rakenne, jonka avulla voidaan tallentaa kaikki tarvittavat tiedot varauksista. ”Varaukset” rakanenne sisältää ja tallentaa varaajan nimen, huoneen numeron, varattujen öiden määrän, yöpymisen kokonaishinnan, sekä varausnumeron. 
Seuravaksi määritetään vektorit, joiden mukaisesti ohjelma toimii. Näistä ensimmäinen on tarkastusfunktio, joka tarkistaa käyttäjän syötteen olevan positiivinen kokonaisluku. Jos syöte ei ole kelvollinen (esim. negatiivinen tai ei-kokonaisluku), se pyytää käyttäjää syöttämään arvon uudelleen.
Seuraavaksi määritetään funktio, joka arpoo satunnaisen huoneen numeron ohjelmassa olevasta taulukosta, joka pitää kirjaa huoneiden varaustilasta. 
Jos vapaita huoneita ei ole, ohjelma ilmoittaa siitä käyttäjälle eikä anna tehdä varausta. Varatun huoneen numero tallennetaan ja siirrytään eteenpäin.
Seuraavan funktion tarkoitus on arpoa asiakkaalle varausnumero 10000-99999 väliltä. Varausnumero ja muut annetut tiedot tallennetaan varaukset -vektoriin.
Viimeisenä määritettään vielä funktiot varaustietojen etsimistä varten. Jos käyttäjä haluaa tarkastella varausta varausnumeron tai nimen perusteella, ohjelma etsii varauksen ja tulostaa sen tiedot.

Pääohjelma aloitetaan alustamalla satunnaislukugeneraattori, jonka avulla ohjelma asettaa hotellin huoneiden määrän ja huoneen hinnan satunnaisesti. Huoneiden määrä on välillä 30–70 ja huoneen hinta on välillä 80–100 euroa per yö.
Ohjelman toimintavalikosta tai ”menusta” Käyttäjä voi tehdä neljä asiaa:
1.	Tee uusi varaus: Käyttäjä syöttää nimen ja öiden määrän. Jos vapaita huoneita on, varaus tehdään satunnaiselle huoneelle ja asiakkaalle ilmoitetaan kokonaishinta.
2.	Hae varaus varausnumerolla: Käyttäjä voi hakea varauksen varausnumeron avulla ja ohjelma näyttää kyseisen varauksen tiedot.
3.	Hae varaus varaajan nimellä: Käyttäjä voi hakea varauksen varaajan nimellä ja ohjelma näyttää kyseisen varauksen tiedot.
4.	Poistu: Ohjelma sulkeutuu.

ohjelma on yksinkertaisen esimerkki hotellihuoneiden varausjärjestelmästä, jossa käyttäjä voi tehdä varauksia, tarkastella niitä ja poistua ohjelmasta. Koodi käyttää satunnaislukuja huoneiden ja varausten valintaan, ja se huolehtii virheellisistä syötteistä ja varmistaa, onko huoneiden varaus mahdollista.

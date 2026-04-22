3D Tank Játék



1\. A projekt leírása



A beadandó feladat egy belső nézetben játszható 3D-s játék, ami egy aréna alapú környezetben játszódik. A felhasználó egy tankot irányít, amellyel különböző célpontokat kell megkeresnie és megsemmisítenie. 



2. Alkalmazott grafikai módszerek



&#x20;   Saját matematikai implementáció: A transzformációkhoz szükséges 4×4-es mátrixokat (eltolás, forgatás, perspektivikus vetítés) és a mátrixszorzást saját függvényekkel valósítom meg.



&#x20;   Modern csővezeték (Pipeline): Az adatátvitel során Vertex Buffer Object-eket (VBO) és Vertex Array Object-eket (VAO) használok a hatékony adatkezelés érdekében.



&#x20;   Hierarchikus modellezés: Az objektumok felépítése hierarchikus (különálló test és forgatható torony), ahol a torony transzformációja a test aktuális mátrixától függ.



&#x20;   Világítás (Phong-modell): A jelenet megvilágítását a Fragment shaderben számolom ki. A lövedékek és a tank fényszórója dinamikus pontfényforrásként funkcionálnak, megvilágítva a környező felületeket.



&#x20;   Textúrázás: Az objektumok felületi megjelenését textúra-atlasz segítségével alakítom ki, biztosítva a pontos UV koordináta-leképezést a geometriákon.



4\. Játéklogika és funkciók



&#x20;   Időalapú mozgás: Az objektumok elmozdulását az eltelt időhöz (Delta Time) kötöm



&#x20;   Ütközésvizsgálat: Sugaras távolságmérésen alapuló számítás a lövedékek és a környezeti elemek interakciójának kezeléséhez.



&#x20;   Irányítás: Billentyűzet- és egérkezelés az SDL2 eseménykezelő rendszerén keresztül.


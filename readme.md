V štandardnej knižnici jazyka C sú pre alokáciu a uvoľnenie pamäti k dispozícii funkcie malloc, a free. V tomto zadaní je úlohou implementovať vlastnú verziu alokácie pamäti.

Zadanie sa vypracúva v dvoch častiach:

Vlastný algoritmus prideľovania pamäti (do 9.10.2017 8:59)
Dokumentácia (do 16.10.2017 8:59)
V prvej časti (odovzdanie do 9.10.2017 8:59) je vašou úlohou implementovať nasledovné ŠTYRI funkcie využitím metódy explicitných zoznamov:

    void *memory_alloc(unsigned int size);
    int memory_free(void *valid_ptr);
    int memory_check(void *ptr);
    void memory_init(void *ptr, unsigned int size);
    
Vo vlastnej implementácii môžete definovať aj iné pomocné funkcie ako vyššie spomenuté, nesmiete však použiť existujúce funkcie malloc a free.

Funkcia memory_alloc má poskytovať služby analogické štandardnému malloc. Teda, vstupné parametre sú veľkosť požadovaného súvislého bloku pamäte a funkcia mu vráti: ukazovateľ na úspešne alokovaný kus voľnej pamäte, ktorý sa vyhradil, alebo NULL, keď nie je možné súvislú pamäť požadovanej veľkosť vyhradiť.

Funkcia memory_free slúži na uvoľnenie vyhradeného bloku pamäti, podobne ako funkcia free. Funkcia vráti 0, ak sa podarilo (funkcia zbehla úspešne) uvoľniť blok pamäti, inak vráti 1. Môžete predpokladať, že parameter bude vždy platný smerník z predchádzajúcich volaní vrátení funkciou memory_alloc, ktorý ešte nebol uvoľnený.

Funkcia memory_check slúži na skontrolovanie, či parameter (smerník) je platný smerník, ktorý bol v nejakom z predchádzajúcich volaní vrátení funkciou memory_alloc a zatiaľ nebol uvoľnený funkciou memory_free. Funkcia vráti 0, ak sa je smerník neplatný, inak vráti 1.

Funkcia memory_init slúži na inicializáciu spravovanej voľnej pamäte. Predpokladajte, že funkcia sa volá práve raz pred všetkými inými volaniami memory_alloc, memory_free a memory_check. Viď testovanie nižšie. Ako vstupný parameter funkcie príde blok pamäte, ktorú môžete použiť pre organizovanie a aj pridelenie voľnej pamäte. Vaše funkcie nemôžu používať globálne premenné okrem jednej globálnej premennej na zapamätanie smerníku na pamäť, ktorá vstupuje do funkcie memory_init. Smerníky, ktoré prideľuje vaša funkcia memory_alloc musia byť výhradne z bloku pamäte, ktorá bola pridelená funkcii memory_init.

Pred odovzdaním si vlastnú implementáciu dôkladne otestujte. Do testovača by ste mali odovzdávať už funkčnú verziu. Môžete síce do testovača odovzdať aj na viac krát, ale pokiaľ tam bude mať niekto 30 odovzdaných pokusov, niečo asi nie je v poriadku.

Ukážka testu:

    #include <string.h>
    int main()
    {
        char region[50];
        memory_init(region, 50);
        char* pointer = (char*) memory_alloc(10);
        if (pointer)
            memset(pointer, 0, 10);
        if (pointer)
            memory_free(pointer);
        return 0;
    }
    
V prvej časti odovzdávate len program. Program je napísaný v programovacom jazyku C, zachováva určité konvencie písania prehľadných programov (pri odovzdávaní povedzte cvičiacemu, aké konvencie ste pri písaní kódu dodržiavali). Snažte sa, aby to bolo na prvý pohľad pochopiteľné.

V druhej časti (odovzdanie do 9.10.2017 8:59) odovzdávate textovú dokumentáciu, ktorá obsahuje hlavičku (kto, aké zadanie odovzdáva), stručný opis použitého algoritmu, s názornými nákresmi/obrázkami, a krátkymi ukážkami zdrojového kódu, vyberajte len kód na ktorý chcete extra upozorniť. Pri opise sa snažte dbať osobitý dôraz na zdôvodnenie správnosti vášho riešenia – teda, dôvody prečo je dobré/správne. Nakoniec musí technická dokumentácia obsahovať odhad výpočtovej (časovej) a priestorovej (pamäťovej) zložitosti vášho algoritmu. Celkovo musí byť cvičiacemu jasné, že viete čo ste spravili, že viete odôvodniť, že to je správne riešenie, a vedieť aké je to efektívne.

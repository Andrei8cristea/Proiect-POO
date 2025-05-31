# PROIECT POO - LICITATII DE MASINI

## Descrierea proiectului

#### Descrierea claselor:

CCar este clasa abstracta din care derivez fiecare clasa specifica de masini(Classic, Rally si Sport)

Apoi am clasa CStrategy cu care implementez tiparul strategic al fiecarui jucator cu un enum(Agressive, Normal, Passive)

In clasa CBidder instantiez practic participantii la licitatie si prin functia decide bid le atribui o strategie in functie de masina prefereata, numarul de runde anterior pierdut sau numarul de runde castigat(de exemplu daca acum se
liciteaza o masina de tip favourite si bidderul a pierdut cel putin o runda acesta va aborda o strategie mai agresiva si va bid-ui mai mult). De asemenea am adaugat si un factor de randomness pe care l-am numit stressfactor si imi mai
adauga o mica parte la bid(presupunand ca din cauza stresului bidder vor oferi sume care nu sunt rotunde si putin mai mari decat minimul necesar)

In clasa template CRepository tin datele si am implementat ca functii adaugarea stergerea si functia findAll care ia un predicat de tip template(care este practic o functie) si imi intoarce toate valorile din colectia respectiva care respecta
conditia din predicat

In CMenu implementez efectiv functionalitatile vizibile in meniul interactiv

#### Functionalitati:

1. vinderea unei masini. Practic se supraincarca operatorul de citire al fiecarei clase derivate care foloseste operatorul din clasa de baza si ulterior adauga masina astfel creeata in CRepo ul necesar.
2. afisarea tuturor masinilor disponibile pt licitatie. Pur si simplu afisez toate elementele din vector utilizand operatorul de citire supraincarcat
3. inceperea licitiatiilor. Cea mai complexa functie din proiectul meu. Pentru fiecare masina se afiseaza datele si apoi se deschide o licitatie. Apoi bidderii pot paria in functie de bugetul lor si de strategie pe care o au in acel moment(deoarece aceasta se schimba de-a lungul licitatiilor). Apoi vine si randul userului care este tot un bidder si acesta are trei optiuni: sa parieze cu cel putin 500 mai mult decat bid ul curent, sa dea skip acestui bid, sau sa dea skip acestei masini lasand doar botii sa joace. La final castigatorului i se actualizeaza bugetul si masina i se adauga in portofoliu/
4. aici se pot vedea informatii despre fiecare bidder in parte (buget, masini castigate, runde pierdute, castigate, etc)

Exceptiile au fost tratate prin creearea unei clase genereale de exceptii derivata din std::exception (CException) din care am derivat ulterior alte clase de exceptii specifice.


## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.

## Cerințe obligatorii

Nerespectarea duce la nepunctarea proiectului

  - programul va fi scris în C++
  - programul va avea un meniu interactiv (doar pentru ilustrarea funcționalității)
  - programul nu are erori de compilare
  - fară variabile globale
  - datele membre private(sau protected)
  - GitHub Actions trecute
  - commit-uri pe Git adecvate si punctuale
  - folosirea a funcționalităților limbajului fără sens
  - folosirea a funcționlităților limbajului cu scopul de a încălca "legal" o altă regulă
      - folosirea excesivă a claselor friend
      - folosirea excesviă a elementelor statice
  - lipsa separarea implementarii de definitie

## Cerințe
- [X] definirea a minim **2-3 ieararhii de clase** care sa interactioneze in cadrul temei alese (fie prin compunere, agregare sau doar sa apeleze metodele celeilalte intr-un mod logic) (6p)
  - minim o clasa cu:
    - [X] constructori de inițializare [*](https://github.com/Ionnier/poo/tree/main/labs/L02#crearea-obiectelor)
    - [X] constructor supraîncărcat [*](https://github.com/Ionnier/poo/tree/main/labs/L02#supra%C3%AEnc%C4%83rcarea-func%C8%9Biilor)
    - [X] constructori de copiere [*](https://github.com/Ionnier/poo/tree/main/labs/L02#crearea-obiectelor)
    - [X] `operator=` de copiere [*](https://github.com/Ionnier/poo/tree/main/labs/L02#supra%C3%AEnc%C4%83rcarea-operatorilor)
    - [X] destructor [*](https://github.com/Ionnier/poo/tree/main/labs/L02#crearea-obiectelor)
    - [X] `operator<<` pentru afișare (std::ostream) [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L123)
    - [X] `operator>>` pentru citire (std::istream) [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L128)
    - [X] alt operator supraîncărcat ca funcție membră [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L32)
    - [X] alt operator supraîncărcat ca funcție non-membră [*](https://github.com/Ionnier/poo/blob/main/labs/L02/fractie.cpp#L39) - nu neaparat ca friend
  - in derivate
      - [X] implementarea funcționalităților alese prin [upcast](https://github.com/Ionnier/poo/tree/main/labs/L04#solu%C8%9Bie-func%C8%9Bii-virtuale-late-binding) și [downcast](https://github.com/Ionnier/poo/tree/main/labs/L04#smarter-downcast-dynamic-cast)
        - aceasta va fi făcută prin **2-3** metode specifice temei alese
        - funcțiile pentru citire / afișare sau destructorul nu sunt incluse deși o să trebuiască să le implementați 
      - [X] apelarea constructorului din clasa de bază din [constructori din derivate](https://github.com/Ionnier/poo/tree/main/labs/L04#comportamentul-constructorului-la-derivare)
      - [X] suprascris [cc](https://github.com/Ionnier/poo/tree/main/labs/L04#comportamentul-constructorului-de-copiere-la-derivare)/op= pentru copieri/atribuiri corecte
      - [X] destructor [virtual](https://github.com/Ionnier/poo/tree/main/labs/L04#solu%C8%9Bie-func%C8%9Bii-virtuale-late-binding)
  - pentru celelalte clase se va definii doar ce e nevoie
  - minim o ierarhie mai dezvoltata (cu 2-3 clase dintr-o clasa de baza)
  - ierarhie de clasa se considera si daca exista doar o clasa de bază însă care nu moștenește dintr-o clasă din altă ierarhie
- [X] cât mai multe `const` [(0.25p)](https://github.com/Ionnier/poo/tree/main/labs/L04#reminder-const-everywhere)
- [X] funcții și atribute `static` (în clase) [0.5p](https://github.com/Ionnier/poo/tree/main/labs/L04#static)
  - [X] 1+ atribute statice non-triviale 
  - [X] 1+ funcții statice non-triviale
- [ ] excepții [0.5p](https://github.com/Ionnier/poo/tree/main/labs/L04#exception-handling)
  - porniți de la `std::exception`
  - ilustrați propagarea excepțiilor
  - ilustrati upcasting-ul în blocurile catch
  - minim folosit într-un loc în care tratarea erorilor în modurile clasice este mai dificilă
- [X] folosirea unei clase abstracte [(0.25p)](https://github.com/Ionnier/poo/tree/main/labs/L04#clase-abstracte)
 - [X] clase template
   - [X] crearea unei clase template [(1p)](https://github.com/Ionnier/poo/tree/main/labs/L08)
   - [X] 2 instanțieri ale acestei clase (0.5p)
 - STL [(0.25p)](https://github.com/Ionnier/poo/tree/main/labs/L07#stl)
   - [ ] utilizarea a două structuri (containere) diferite (vector, list sau orice alt container care e mai mult sau mai putin un array)
   - [X] utilizarea a unui algoritm cu funcție lambda (de exemplu, sort, transform)
 - Design Patterns [(0.75p)](https://github.com/Ionnier/poo/tree/main/labs/L08)
   - [ ] utilizarea a două șabloane de proiectare

### Observații

* Pot exista depunctări până la 2p pentru diferite aspecte precum:
  - memory leak-uri
  - nefolosirea destructorului virtual la nevoie
  - abuzarea de diferite concepte (toate funcțiile declarate virtual)
  - apelarea de funcții virtual în constructori

* În general, acestea sunt prezente în [CppCoreGuideline](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md), dar nu e nevoie să parcurgeți documentul, doar să scrieți codul suficient de organizat

* folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.

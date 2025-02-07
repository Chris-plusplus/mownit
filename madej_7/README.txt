Poniżej instrukcja jak pominąć rysowanie wykresów.
Niezbędne jest posiadanie kompilatora wspierającego standard C++20, np:
- g++, w wersji >=13
- clang, w wersji >=17
- msvc, w wersji >=19.29
(na podstawie https://en.cppreference.com/w/cpp/20/,
wiersz 'Text formatting' w sekcji 'C++20 library features'),
oraz posiadanie programów:
- CMake
- conan 2.3 (menedżer pakietów, instalowany pythonowym pip'em)

Aby skompilować program należy w folderze z plikiem 'CMakeLists.txt' wykonać polecenia:

cmake . -B build
cd build
cmake --build .

(jeżeli kompilator to msvc, plik wykonywalny może znajdować się w folderze Debug lub Release)

Aby uruchomić program należy wykonać polecenie:

./lab9

następnie należy wpisać 'sr' (oblicz promienie spektralne) lub 'jcb' (oblicz układy równań metodą Jacobiego)
kolejno wpisać limit obliczeń, czyli maksymalny rozmiar układu

(dla przyspieszenia w trybie 'sr' program prowadzi obliczenia równolegle na N-1 wątkach, gdzie N to liczba wątków logicznych procesora,
 liczbę wątków można zmienić modyfikując linijkę ~206 z 'thread_pool(std::thread::hardware_concurrency() - 1)' na 'thread_pool(<liczba wątków>)')


Po zakończeniu działania programu pojawią się pliki w folderze z plikiem wykonywalnym
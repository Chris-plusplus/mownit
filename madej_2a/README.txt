Niezbędne jest posiadanie kompilatora wspierającego standard C++20, np:
- g++, w wersji >=13
- clang, w wersji >=17
- msvc, w wersji >=19.29
(na podstawie https://en.cppreference.com/w/cpp/20/,
wiersz 'Text formatting' w sekcji 'C++20 library features'),
oraz posiadanie programów:
- CMake
- conan 2.1 (menedżer pakietów, instalowany pythonowym pip'em)

Aby skompilować program należy w folderze z plikiem 'CMakeLists.txt' wykonać polecenia:

cmake . -B build
cd build
cmake --build .

conan pobierze i zainstaluje niezbędne biblioteki,
niektóre z nich mogą wymagać kompilacji na maszynie użytkownika
w moim przypadku (Windows 11, kompilator MSCV) zajęło to 3266 sekund, czyli prawie godzinę (to nie żart)

Aby uruchomić program należy wykonać polecenie:

./lab2

(jeżeli kompilator to msvc, plik wykonywalny może znajdować się w folderze Debug lub Release)

Po zakończeniu działania programu pojawią się pliki w folderach ze słowem 'interpolation' (w ścieżce pliku wykonywalnego)
Niezbędne jest posiadanie kompilatora wspierającego standard C++20, np:
- g++, w wersji >=13
- clang, w wersji >=17
- msvc, w wersji >=19.29
(na podstawie https://en.cppreference.com/w/cpp/20/,
wiersz 'Text formatting' w sekcji 'C++20 library features'),
oraz posiadanie programu CMake


Aby skompilować program należy w folderze z plikiem 'CMakeLists.txt' wykonać polecenia:

cmake . -B build
cd build
cmake --build .

Aby uruchomić program należy wykonać polecenie:

./lab1

(jeżeli kompilator to msvc, plik wykonywalny może znajdować się w folderze Debug lub Release)

Po zakończeniu działania programu pojawi się 5 plików .txt z w wynikami obliczeń (liczby są z '.', nie ',').
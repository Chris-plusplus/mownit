Poniżej instrukcja jak pominąć rysowanie wykresów.
Niezbędne jest posiadanie kompilatora wspierającego standard C++20, np:
- g++, w wersji >=13
- clang, w wersji >=17
- msvc, w wersji >=19.29
(na podstawie https://en.cppreference.com/w/cpp/20/,
wiersz 'Text formatting' w sekcji 'C++20 library features'),
oraz posiadanie programów:
- CMake
- conan 2.1 (menedżer pakietów, instalowany pythonowym pip'em)

chcąc pominąć rysowanie wykresów należy:
- w pliku conanfile.py zakomentować linijki 'self.requires' zawierające:
	- jasper
	- cvplot
	- opencv
- w pliku CMakeLists.txt zakomentować linijki 'find_package' (~110 linijka) zawierające:
	- opencv
	- cvplot
- w pliku CMakeLists.txt usunąć z linijki 'target_link_libraries' (~125 linijka)
	wartość 'CvPlot::CvPlot'
- w pliku CMakeLists.txt zmienić wartośc makra NOPLOT na 1 (~8 linijka)

Aby dodać m i n do zbioru save_whitelist trzeba zmienić linijkę:

std::set<std::pair<flt, flt>> save_whitelist{};

na:

std::set<std::pair<flt, flt>> save_whitelist {
	{m_0, n_0},
	{m_1, n_1},
	...
};

Aby skompilować program należy w folderze z plikiem 'CMakeLists.txt' wykonać polecenia:

cmake . -B build
cd build
cmake --build .

conan pobierze i zainstaluje niezbędne biblioteki,
niektóre z nich mogą wymagać kompilacji na maszynie użytkownika
w moim przypadku (Windows 11, kompilator MSCV) zajęło to 3266 sekund, czyli prawie godzinę

Aby uruchomić program należy wykonać polecenie:

./lab5

(jeżeli kompilator to msvc, plik wykonywalny może znajdować się w folderze Debug lub Release)

Po zakończeniu działania programu pojawią się pliki w folderach ze słowem 'approximation' (w ścieżce pliku wykonywalnego)

pliki *.dat zawierają macierz w formacie liniowym, z błędami aproksymacji w zależności od m i n
aby zapisać render mapy cieplnej macierzy należy pliki *.dat przenieść do folderu labs/lab5/
i uruchomić skrypty *.gp (GnuPlot) w tym folderze

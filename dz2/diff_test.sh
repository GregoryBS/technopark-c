./build/st_main.out tests a > stat.txt
./build/dyn_main.out tests a > dyn.txt
diff stat.txt dyn.txt

./build/st_main.out tests You > stat.txt
./build/dyn_main.out tests You > dyn.txt
diff stat.txt dyn.txt

./build/st_main.out tests _ancbschsd > stat.txt
./build/dyn_main.out tests _ancbschsd > dyn.txt
diff stat.txt dyn.txt
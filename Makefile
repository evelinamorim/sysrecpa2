datadir = ../../PA1/ml-100k/

index:
	g++ -O3 -c -o util.o util.cpp -ggdb
	g++ -O3 -c -o le.o le.cpp -ggdb
	g++ -O3 -c -o item.o item.cpp -ggdb
	g++ -O3 -c -o main_index.o main_index.cpp -ggdb
	g++ -O3 -o tp2-index main_index.o util.o le.o item.o -g

#recommend:

#evaluation:

run:
	#time ./tp2-index $(datadir)/u.user $(datadir)/u.item $(datadir)/ua.base
	./tp2-index toy.user toy.item toy.base

EXO : exe

ppm_lib.o : ppm_lib.c ppm_lib.h
	gcc -c $< -o $@

compression.o : compression.c ppm_lib.h
	gcc -c $< -o $@

decompression.o : decompression.c ppm_lib.h
	gcc -c $< -o $@

conversion.o : conversion.c ppm_lib.h
	gcc -c $< -o $@

Menu.o : Menu.c ppm_lib.h
	gcc -c $< -o $@

main.o : main.c ppm_lib.h
	gcc -c $< -o $@

exe : ppm_lib.o compression.o decompression.o conversion.o Menu.o main.o
	gcc  $^ -o $@

clean:
	rm -f *.o
	rm exe
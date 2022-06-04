EXO : exe

save/ppm_lib.o : src/ppm_lib.c src/ppm_lib.h
	gcc -c $< -o $@

save/compression.o : src/compression.c src/ppm_lib.h
	gcc -c $< -o $@

save/decompression.o : src/decompression.c src/ppm_lib.h
	gcc -c $< -o $@

save/conversion.o : src/conversion.c src/ppm_lib.h
	gcc -c $< -o $@

save/Menu.o : src/Menu.c src/ppm_lib.h
	gcc -c $< -o $@

save/main.o : src/main.c src/ppm_lib.h
	gcc -c $< -o $@

save/debugTool.o : src/debugTool.c src/ppm_lib.h
	gcc -c $< -o $@
	
exe : save/debugTool.o save/ppm_lib.o save/compression.o save/decompression.o save/conversion.o save/Menu.o save/main.o
	gcc  $^ -o $@

clean:
	rm -f save/*.o
	rm exe

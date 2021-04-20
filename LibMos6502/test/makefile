test.nes: test.o
	ld65 test.o --config ines.cfg -o test.nes

test.o: test.s
	ca65 test.s

clean:
	del test.o test.nes
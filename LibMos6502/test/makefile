test.nes: test.o
	ld65 test.o --config ines.cfg -o test.nes

test.o: test.ca65
	ca65 test.ca65

clean:
	del test.o test.nes
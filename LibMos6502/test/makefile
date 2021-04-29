test.nes: test.o
	ld65 test.o --config ines.cfg -o test.nes

test.o: test.asm
	ca65 test.asm

clean:
	del test.o test.nes
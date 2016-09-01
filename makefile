test:
	@echo "---------------------------------------------------------------"
	#gcc -o build/test_roman src/*.c test/*.c ../check/src/*.c -I../check/src -Isrc/ -g -fno-common -fmessage-length=0 -Wall -Wextra -MMD -MP -Wno-implicit-function-declaration -lm
	gcc -o build/test_roman src/*.c test/*.c `pkg-config --cflags --libs check` -Isrc/ -g -fno-common -fmessage-length=0 -Wall -Wextra -MMD -MP -Wno-implicit-function-declaration -lm
	./build/test_roman
    
.PHONY: test
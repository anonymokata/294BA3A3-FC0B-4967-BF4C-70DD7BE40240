ifeq (,$(wildcard build))
$(shell mkdir -p build)
endif

test:
	@echo "---------------------------------------------------------------"
	gcc -o build/test_roman src/*.c test/*.c check/src/*.c -Icheck/src -Isrc/ -Itest/ -g -fno-common -fmessage-length=0 -Wall -Wextra -MMD -MP -Wno-implicit-function-declaration -lm
	#gcc -o build/test_roman src/*.c test/*.c -Isrc/ -Itest/ -g -fno-common -fmessage-length=0 -Wall -Wextra -MMD -MP -Wno-implicit-function-declaration `pkg-config --cflags --libs check` -lm
	./build/test_roman

.PHONY: test
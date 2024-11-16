
default:
	@mkdir -p build
	@mkdir -p build/test
	@clear
	@echo "\033[1;33m|----------Compile Tests----------|\033[0m\n\033[1;33m|  \033[0m"
	@for file in $(shell ls src/tests); do \
		echo "\033[1;33m|  \033[0m$$file"; \
		echo "\033[1;33m|  \033[0mgcc -o build/test/$$file src/tests/$$file -Isrc/includes\n\033[1;33m|  \033[0m"; \
		gcc -o build/test/$${file%.*} src/tests/$$file src/modules/* -Isrc/includes; \
	done
	@echo "\033[1;33m|----------Compile Tests----------|\033[0m"
	@echo "\033[1;32m|----------Launch Tests-----------|\033[0m\n\033[1;32m|  \033[0m"
	@for file in $(shell ls src/tests); do \
		echo "\033[1;32m|  \033[0m$$file"; \
		./build/test/$${file%.*}; \
		echo "\033[1;32m|  \033[0m"; \
	done
	@echo "\033[1;32m|----------Launch Tests-----------|\033[0m"
	@echo "\033[1;36m|----------Compile Main-----------|\033[0m"
	@echo "\033[1;36m|  \033[0mmain.c"
	@echo "\033[1;36m|  \033[0mgcc -o build/main main.c src/modules/* -Isrc/includes"
	@gcc -o build/main main.c src/modules/* -Isrc/includes
	@echo "\033[1;36m|----------Main Compiled----------|\033[0m"




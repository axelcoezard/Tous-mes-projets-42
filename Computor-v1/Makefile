BUILD_FOLDER	:=	./build
SOURCE_FOLDER	:=	.

all:
	cmake -B$(BUILD_FOLDER) -S$(SOURCE_FOLDER)
	make -C $(BUILD_FOLDER)

clean:
	rm -rf $(BUILD_FOLDER)

re: clean all

.PHONY: all clean re

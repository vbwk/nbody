BGFX_HEADERS = -I bgfx/include -I bx/include -I bimg/include

LINKER_FLAGS = bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so -lglfw3 -lGL -lX11 -lstdc++ -lpthread -lXrandr -lXi -ldl -lm

main : render.cc
	./bgfx/.build/linux64_gcc/bin/shadercRelease \
	    -f vertex.sc \
	    -o vertex.bin \
	    --platform linux \
	    --type vertex \
	    --verbose \
	    -i bgfx/src
	    ./bgfx/.build/linux64_gcc/bin/shadercRelease \
	    -f fragment.sc \
	    -o fragment.bin \
	    --platform linux \
	    --type fragment \
	    --verbose \
	    -i bgfx/src
	cc render.cc $(LINKER_FLAGS) $(BGFX_HEADERS) 

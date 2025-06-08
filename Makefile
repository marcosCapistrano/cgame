build:
	cc -g -O0 main.c game/area.c game/tile.c physics/body.c -o cgame -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run:
	./cgame
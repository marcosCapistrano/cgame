build:
	cc main.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run:
	./game
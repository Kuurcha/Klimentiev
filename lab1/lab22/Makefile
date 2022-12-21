all: clean main addition substraction multiplication division squareRoot
main:
	gcc main.c sharedLib.c -o main
addition: 
	gcc addition.c  sharedLib.c -o addition
substraction: 
	gcc substraction.c sharedLib.c -o substraction
multiplication:
	gcc multiplication.c sharedLib.c -o multiplication
division:
	gcc division.c sharedLib.c -o division
squareRoot: 
	gcc squareRoot.c sharedLib.c -o squareRoot -lm
clean: 
	rm -rf main
	rm -rf addition
	rm -rf substraction
	rm -rf multiplication
	rm -rf division
	rm -rf squareRoot
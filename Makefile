Files = main.cpp mainUtils.cpp
FLAGS = -fsanitize=address -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o prog -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


all:
	g++ -O2 -mavx2 $(Files) $(FLAGS)

SSE:
	g++ -O2 -DSSE -mavx2 $(Files) $(FLAGS)



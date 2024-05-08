@echo off
echo === Compiling ParticleSystem.cpp ===
g++ -std=c++17 -c ParticleSystem.cpp -o ParticleSystem.o
if errorlevel 1 (
    echo FAILED: ParticleSystem.cpp
    goto :error
)
echo OK

echo === Compiling Game.cpp ===
g++ -std=c++17 -c Game.cpp -o Game.o
if errorlevel 1 (
    echo FAILED: Game.cpp
    goto :error
)
echo OK

echo === Linking Arkadroid.exe ===
g++ -std=c++17 -o Arkadroid.exe Ball.o BlueBrick.o BlueFood.o Brick.o FileHandler.o Food.o Game.o GreenBrick.o GreenFood.o HUD.o Level.o Level1.o Level2.o Level3.o Paddle.o ParticleSystem.o PinkBrick.o PinkFood.o RedBrick.o RedFood.o UIManager.o YellowBrick.o YellowFood.o main.o -lsfml-graphics -lsfml-window -lsfml-system
if errorlevel 1 (
    echo FAILED: Linking
    goto :error
)
echo === BUILD SUCCESS ===
goto :eof

:error
echo === BUILD FAILED ===
exit /b 1

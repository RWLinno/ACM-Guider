@echo off
echo rwl version
echo map1:
.\PreliminaryJudge.exe -m .\maps\map1.txt -l ERR .\main3.13.exe
echo map2:
.\PreliminaryJudge.exe -m .\maps\map2.txt -l ERR .\main3.13.exe
echo map3.7:
.\PreliminaryJudge.exe -m .\maps\map-3.7.txt -l ERR .\main3.13.exe
echo map3.8:
.\PreliminaryJudge.exe -m .\maps\map-3.8.txt -l ERR .\main3.13.exe
echo map3.9:
.\PreliminaryJudge.exe -m .\maps\map-3.9.txt -l ERR .\main3.13.exe
echo map3-10:
.\PreliminaryJudge.exe -m .\maps\map-3.10.txt -l ERR .\main3.13.exe
echo map3-11:
.\PreliminaryJudge.exe -m .\maps\map-3.11.txt -l ERR .\main3.13.exe
echo map3-12:
.\PreliminaryJudge.exe -m .\maps\map-3.12.txt -l ERR .\main3.13.exe
echo map3-13:
.\PreliminaryJudge.exe -m .\maps\map-3.13.txt -l ERR .\main3.13.exe
echo good bye
pause
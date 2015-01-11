Usage format:

Project.exe [fileName] [-r startX startY endX endY]

where:
[fileName] is any number of valid filenames like N50E015
[-r startX startY endX endY] is range tag which will load all
   sectors with coords:
      x >= startX && x <= endX
      y >= startY && x <= endY

X >= 0 are East coordinates
X  < 0 are West coordinates
y >= 0 are North coordinates
Y  < 0 are South coordinates

example:
Project.exe N10E010 N15W040 -r 20 20 21 22

will load files:
N10E010.hgt
N15W040.hgt
and range files:
N20E020.hgt
N20E021.hgt
N21E020.hgt
N21E021.hgt
N22E020.hgt
N22E021.hgt
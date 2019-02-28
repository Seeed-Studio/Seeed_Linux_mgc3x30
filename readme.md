# Seeed_mgc3130
Microchip’s MGC3X30 are 3D gesture recognition and motion tracking controller chips based on Microchip’s patented GestIC technology.They enable user command input with natural hand and finger movements.

*** 
## Usage
### Install ncurses
download from [here](https://invisible-mirror.net/archives/ncurses/)  
Recommended  ncurses-6.1.tar.gz

### Install instructions

	tar -xvf ncurses-x.x.tar.gz
	cd ncurses-x.x/
	./configure
	make
	sudo make install
*** NOTICE: the x.x in instructions is the version of ncurses that you download. 6.1 if ncurses-6.1.tar.gz***

Check whether the ncurse installation finished:

	ncursesx-config --version

*** NOTICE: the x in instructions is the version of ncurses that you download.6 if ncurses-6.1.tar.gz ***

***

### install wiringPi
	git clone git://git.drogon.net/wiringPi
	cd wiringPi
	git pull origin
	cd wiringPi
	./build


### Library Usage
clone this library

	cd Seeed_mgc3x30
	make clean && make
	./mgc3130
And then, you can see a terminal graph and test the 3D touch board.

### Function Support
The library support functions blow:
* x,y,z axis position detection.
* gesture: four types,left,right,up,down
* airwheel
* Touch,tap,double tap. 


***
This software is written by downey  for seeed studio<br>
Email:dao.huang@seeed.cc
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>















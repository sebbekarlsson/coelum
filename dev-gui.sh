cd parsing
echo "PARSING"
sudo make clean; sudo make install &&
cd ..
cd coelum
echo "COELUM"
sudo make clean; sudo make install &&
cd ..
cd apollon
echo "APOLLON"
sudo make clean; sudo make && ./coelumg.out

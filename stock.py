import time;
import serial;
from urllib import urlopen
import xml.etree.ElementTree as ET

ser = serial.Serial('COM3',9600);     #replace COM3 to whatever port the arduino listens in your case, mine is com3
while True:
	u = urlopen('http://localhost:8167/?format=xml');     #From httpspeedfan
	doc = ET.parse(u);
	root = doc.getroot();
	
	GPUtemp = root[1][12].text;			#Second number is found in configure/Temperatures in speedfan, count to where GPU is, subtract one and replace the second number
	GPUfanspeed = root[2][6].text;      #Same thing but in configure/fans
	
	print (GPUtemp)
	print (GPUfanspeed)
	
	ser.write(GPUtemp+'*'+GPUfanspeed);
	time.sleep(7.5);

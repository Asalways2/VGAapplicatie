\mainpage VGA_API Demo software
# VGA_API Demo Software

This software is written by:
@author Erwin Blankestein
@author Remy van der Pol

This software has been written as an educational assignment at the Hogeschool Utrecht.
The software consist of the VGA_API, with a demo code for using this library.

The demo has been buildt for the STM32F407VG microcontroller board from ST. 




Links:

Demo application      |Library                         
---------- | ---------------------------------
[Waffle link Demo application](https://waffle.io/Asalways2/VGAlibraries/join) | [Waffle link Library](https://waffle.io/Asalways2/VGAapplicatie/join)  
[Github link Demo application](https://github.com/Asalways2/VGAapplicatie/tree/Test) | [Github link Library](https://github.com/Asalways2/VGAlibraries/tree/develop2) 



# Functions
The demo software has the following functionalitys:

<UL>
<LI>Reading commands from the computer;</LI>
<LI>Translating the commands to functions;</LI>
<LI>Give feedback to the user about the received command;</LI>
<LI>Draw the requested figures on the screen.</LI>
</UL>

The demo software has been written using a 3-layer model: the Front-layer, Logic-layer and the IO-layer.

Layer      |Function                         
---------- | ---------------------------------
Front-layer|Receive and process commands
Logic-layer|Execute the command
IO-layer   |Initialize and drive the hardware 

As mentioned before, the demo software makes use of the VGA_API file. This file consists of two library's: The IO_API and the DRAW_API.
API        |Function                                                           
---------- | ------------------------------------------------------------------
IO_API     |Handles the IO functions for the VGA screen                        
DRAW_API   |Draws the figures, bitmaps and text on the screen using the IO_API

# Script
To use the demo application, the user needs to connect the board to the computer using an USB cable. To be able to talk to the board, you will need to connect to the board using a serial terminal (like putty: https://www.putty.org/ for example).
After the board has been connected, you can use any of the following supported commands to put something on the screen:

Command                                          |Parameters                                                                                     
-------------------------------------------------| --------------------------------------------------------------------------------------------- 
lijn, x, y, x’, y’, width, color                 |x, y: starting coördinates; x', y': end coördinates; width: line width; color: line color      
ellips, x-mp, y-mp, radius-x, radius-y, color    |x-mp, y-mp: Ellips position; radius-x, radius-y: Ellips height and width; color: Ellips color  
rechthoek, x-lo, y-lo, x-rb, y-rb, color         |x-lo, y-lo: Left bottom coördinates; x-rb, y-rb: right top coördinates; color: rectangle color    
driehoek, x, y, x’, y’,x”, y”, color             |x, y: coördinates 1; x’, y’: coördinates 2; x”, y”: coördinates 3; color: triangle color       
tekst, x, y, text, color, style                  |x, y: coördinates; text: text; color: text color; style: text style(normaal, vet, cursief)     
bitmap, nr, x-lo, y-lo                           |nr: selected bitmap(0, 1 or 2); x-lo, y-lo: position                                           
clearscherm, color                               |color: screencolor                                                                             
wacht, msecs                                     |msecs: amount of miliseconds to wait before next command                                       
execute											 |no parameters. Script will only run after receiving this command!                              
verbose                                          |no parameters. Turns errors and warnings on or off                                             

Available colors are:
script      |color        
----------  | ----------- 
zwart       |Black        
blauw       |Blue         
lichtblauw  |Lightblue    
groen       |Green        
lichtgroen  |Lightgreen   
cyaan       |Cyan         
lichtcyaan  |Lightcyan    
rood        |Red          
lichtrood   |Lightred     
magenta     |Magenta      
lichtmagenta|Lightmagenta 
bruin       |Brown        
geel        |Yellow       
grijs       |Grey         
wit         |White        




# Software diagram
\image html 3lagenmodel.jpg



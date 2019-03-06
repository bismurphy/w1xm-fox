# w1xm-fox
Arduino sketch which runs a Fox for W1XM.

This was originally developed to have an Arduino act as a stand-in for a PIC microcontroller that was used on the Fox long ago. We lost any software that was on the PIC (as well as any tools to program it) so I retrofitted the Arduino. Inside the Fox is a 44X MHz transmitter board which is about an inch square. We have also used this script on new Foxes, which instead simply use a Baofeng radio, with the Arduino patched into the Baofeng's microphone port. Note that this configuration makes receiving impossible. But receiving never really worked with this script anyway. Luckily, the script works just fine without receive.

The morse lookup system is pretty janky in that it's a sequence of letters and Morse symbols, and it's all just a long string. If this was Python I'd use a dictionary where keys are letters and they map to Morse symbols, but that's not possible on Arduino. If someone wants to punch together a better solution that would be awesome. Note that this method does prevent any possibility of having "." or "-" be transmitted as the symbols they are since the getMorse function is assuming that any dot or dash is part of a transmission sequence (so if you were to put a period and its encoding (.-.-.-) after the letter Z, the code would think that Z in morse code is "--....-.-.-"). So yeah, a better solution for this would be good.

Any other improvements would be cool to hear as well. I'm happy to take suggestions as I enjoyed this project. 

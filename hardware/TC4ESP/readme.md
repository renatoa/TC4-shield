Before proceeding, a quick warning: this is a builders project, there is no shield available, or a complete ready to buy version, atm, as is TC4C ! At least, not yet...

However, to approach this build, only simple pins/wires soldering knowledge is required, nothing smd is involved, the whole project uses ready soldered breadboard modules.

And now, explanation of TC4ESP schematic... components description:

- buttons pad - done using the resistor ladder principle - https://en.wikipedia.org/wiki/Resistor_ladder - and the unique ADC input of ESP8266.
    
    The buttons pad can be DIY, or you can buy ready to use boards for this purpose from eBay, search for "Analog button for Arduino".
    
    To handle this new button pad option, a new library adcButtons has been created, forking the initial cButton library. 
    A new feature of this library is the long press handling.
    
    This library, along with the resistor ladder concept, can be used also with the original TC4 shield, changing the ADC GPIO pin accordingly.
    
- heater SSR - any random fire SSR, only slow PWM (and ICC) support so far, PAC is work in progress.
    Update: starting with V1.1, ICC was been implemented, using a ZCD-SSR device called RobotDyn dimmer.
    For fan you have a PWM output, equivalent of TC4 IO3, you must fit yourself the fan driver.

- LCD - any cheap 20x4 I2C LCD. Library used for this display: https://github.com/marcoschwartz/LiquidCrystal_I2C

- thermocouples interface
    TC4ESP use the same MCP3424 capable ADC, but raise the performance bar at other level, adding for each thermocouple a dedicated amplifier with cold junction compensation, from the AD849x line, manufactured by Analog Devices.
    
    With this setup the resolution and sample rate is in the same ballpark as the phidgets device, at 1/4 cost, or less. 
    
    ADC and amplifiers used were bought as ready soldered breadboards from eBay, total cost of an ADC and two amplifier boards, about $15.
    
    The performance of this solution is now 0.012 C degree resolution (LSB), and 60 ms sample time - per channel - so 16 samples per second for single TC, or 8 samples per second for two measurements. 
    The sample time is smaller because ADC works in 16 bit mode, instead 18 bit, faster and more stable.
    
    Amplifiers are available for K and J types only. Not sure how popular is the T type thermocouple, though...
    
    Ambient sensor is not used anymore, because CJC is a feature of TC amp itself.
    
    Software changes to handle this configuration are very small... actually it could operate with the original library unchanged, using the linear model class, just specifying a slope of 5mV per C degree. However, for more code optimization, some sections related to ambient sensor were disabled, and also the code for K/J/T thermocouples has been conditionally disabled based on several defines. 
    The resulting library should be of greater interest for Arduino users than for ESP platform, because a serious memory amount has been freed this way.
    
- potentiometers
     Because one of the most important drawbacks of the ESP platform is the lack of multiple ADC, this issue has been addressed in two ways:
     - Additional operating modes, based on buttons instead of pots, have been added in a separate user interface;
     - in a later iteration, for those not happy to operate clicking buttons, the pots based functionality has been reinstated, using the unused channels 3 and 4 of MCP3424, assuming they aren't used for additional thermocouples !
     
     So, anyone interested to approach this new platform should be aware about this possible scenario limitation: if all the 4 TC channels are desired to be used for temperatures, AND not interested to explore a new user interface where heater is operated using buttons, then the available operating modes are either standalone profile based roasting, with no manual heater control, either computer controlled via Artisan or similar software.
     
     Another approach, that is now in the evaluation queue, is to use a rotary encoder instead potentiometer.
     
The code branch for this platform can be found here:
    
https://github.com/renatoa/TC4-shield/tree/master/applications/Artisan/aArtisanESP

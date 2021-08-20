# Automatic_Medicine_Remainder-

**INTRODUCTION**

A huge number of patients failed to comply their prescribed medication schedules this can cause disease complications, lower quality of life in even mortality .
To overcome these issues automatic medicine remainder is used.
This system is very simple to operate and update. Therefore any person of age group can use it.
This system can also be useful in hospital where number of patients to overcome the following problems:
 1. Maintaining the regularity of prescribed dosage is difficult to be remembered in busy schedule.
 2. Remembering the name of the medicine to be taken is really very difficult.
 3. Due to above two reasons the patient’s life can get more complicated.

Therefore, there is a growing need and urgency for in –home health care devices and technologies in order to provide patients with the electronic tools to support medication self-management.

**COMPONENTS REQUIRED**
1. Arduino Uno                                                   
2. Bread Board                                             
3. RTC DS3231 module                                             
4. Push Buttons
5. 16x2 LCD display                                              
6. 10K Potentiometer
7. Buzzer                                                       
8. 10K, 1K Resistors
9. LED (any colour)                                            
10. Jumper Wires

**WORKING OF AUTOMATIC MEDICINE REMAINDER SYSTEM**
1. The Medicine Reminder Alarm is powered using 5V supply. When it first boots up, it shows a welcome massage as “Welcome to Circuit Digest”. 
2. The LCD screen is set to cycle in three screens. The 1st screen shows message as “Stay Healthy, Get Well Soon”. The second screen is a help screen which tells to press select push button to select any one time-slot to remind (once/twice/thrice in a day). 
3. The time slot is changeable in program and can be configured accordingly. Right now we have fixed this into three durations i.e. 8am, 2pm, and 8pm. 
4. We have divided time slots into three modes. Mode 1 selects to take medicine once/day at 8am when user presses 1st push button. Mode 2 selects to take medicine twice/day at 8am and 8pm when user presses 2nd push button. Mode 3 selects to take medicine thrice/day at 8am, 2pm and 8pm if user presses 3rd push button.
5. We can also add a feature to snooze the buzzer for 10 minutes (not included in this project).When user selects desired slots by pressing push buttons, the user input is recorded and the time is taken from RTC. When time is matched with selected time slot then the buzzer starts buzzing.
6. User can stop the buzzer by pressing STOP button. 
7. The same process continues for the next slot reminder


**ARCHITECTURAL DESIGN**

![image](https://user-images.githubusercontent.com/66819169/130248492-c4809532-c0ff-4626-9d25-1fc6affc3fe7.png)


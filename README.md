# Arduino-AutoReward

Code for Infrared triggered dual reward system

Hey there!

Thank you for showing interest on the project. At the lab, we lack an automatized way for delivery rewards. What we wanted was a device that:

-	Detect when the animal reaches the end of any of the two arms.
-	Delivers a certain amount of fluid through the corresponding licking port, or the opposite one if wanted.
-	Give visual cues (for experimenters or animals) that indicates which arm has been reached (or needs to be reached).
-	Allows easy mode selection through some interface, to switch between protocols.
-	Therefore, allows different working protocols: Habituation, Training, Experimental, as well as a filling and cleaning mode.

To achieve it, I decided for very simple system. A couple of cheap Infrared emitters are read continuously by a basic Elegoo UNO R3 board. Breaking any of the beams trigger the signal to open one of the two solenoid valves, connected to the fluid tank (modified regular laboratory sample tubes), letting the reward fall by gravity for around 75 milliseconds and resulting in a single drop at the tip of the licking port. I added a delay after each response, stopping the loop, to avoid repetitive delivery when animals don’t leave the area (useful basically during habituation and training phases). In addition, a couple LEDs mounted in the bare-board, light up when the IRs are crossed. I use them as indicators for the ‘Waiting for selection’ mode, turned on continuously meanwhile no option is choose.

The selection is made through a membrane keypad. Right now only have the numbers 1 to 6 working, more than enough for the few programs I have coded so far. When any section is made, the in-built LED blinks the same amount of times and the system is ready to work. At any moment, pressing any key makes the system reset to the waiting mode. The predefined modes are:

-	Waiting mode: root level. You get here when plugging the board or by pressing any key if the system is in other mode.
-	[1] Habituation: every time a beam is broken, the same lick port gives the reward.
-	[2] Training: Since we want to perform alternate choices, this mode only gives a reward, in the same side port, when the beams are broken in alternating sequence.
-	[3], [5] and [6] are empty to implement any further protocols. Would be for giving rewards with a certain probabilities, different alternations depending on additional clues…
-	[4] Fill and Clean: Opens the valves for 5 seconds and close them for 2 seconds, to either fill the tubing or empty it.

Everything is powered by a regular 9V wall adapter, giving 3.3V to the LEDs and IRs circuit and 9V to the solenoids (the circuit is protected by a couple of diodes at this level).

And that’s all, is really simple and I think is the very basic someone can ask for. The most important thing, it works. I have it already mounted and mice are easily detected and single drops of water are delivered. Second more important thing, is really cheap. All the components can be found for less than 80€. Here is the list (links could not be the exact items, but equivalent):

-	Elegoo UNO R3 (I found them for 9,99€, with USB cable)
-	BreadBoard + Acrylic base (7€)
-	9V 1A Wall power supply (9€)
-	2x InfraRed beams (5mm) (15€ both)
-	2x Mini-Solenoid valves (10€ both)
-	2x regular LEDs
-	4x 1 KΩ resistors
-	2x TIP120 Transistors
-	2x 1N4001 diodes
-	Wiring
-	‘Velcro’ to attach the acrylic base where the boards are mounted.
-	Additional plastic tubing and laboratory sample tubes.
-	Four soft magnets for fixing the deposits to the walls.

Coding is not my main strength, even it is improving so perhaps someone will be scandalized by it. And, of course, I have in mind many possible upgrades such as a screen, a SD card port, perhaps to change the Keypad for a wireless interface (tactile? Someone said smartphone + Bluetooth?), a barcode reader or related to easily introduce subjects data (to blind experimenter?)… And here is where I relay in the community, I offer it and hopefully someone wants to implement any of the ideas.

Again, thanks for your interest. If only one people find it helpful, I would be more than happy.

Cheers!

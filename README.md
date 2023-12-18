# Happy Kid

So, this was an exercise to see how fast and easy it would be to write a game in C using ChatGPT. I used ChatGPT for the
generation of most of the code, and for the generation of the graphical assets.

To be honest, I am amazed at how easy this was, using ChatGPT 4 and DALL-E. The quality of the graphics were amazing.
When I prompted DALL-E with "Hi DALL-E! Can you generate an image sprite for me, of let's say 64x64 pixels, of a happy
kid with a cap." and one more refinement prompt of "Oh that's really good, but I would need the whole body and not just
only the head/shoulders. Coul you create another one? Make sure the resolution of the image is actually 64 x 64 pixels.
Also make sure the background is transparent.", the result was exactly what I could imagine I'd want it to be. The same
goes for the fire creatures it came up with, they were perfect. The problem was more with animation and consistency. It
had a hard time getting the details of a prompt right. I also gave up trying to generate animation frames of a kid, at
this moment it just doesn't seem to be able to be consistent enough. That might soon change though.

In a way the same goes for the code. What is so great about it is that it will give you consistent quality of the files.
The problem is more very strange mistakes that you'd have to hunt down. But that's pretty easy to do. I love how it not
only tells me about libraries I didn't know about like SDL, but also how to install them and calling APIs in the code
examples it generates already. That is quite stunning and allows you to move very very fast.

A word on the code itself: I made the game very very simple. It's hardly a game, but it qualifies because there is an
objective, an agent and a challenge, which is pretty much all you need for basic game mechanics, I'd argue. I use some
game states to keep track of where in the game we are. There's four states really the game can be in really: either you
are not playing yet, playing, dead or victorious. The main.c file keeps track of what state you're in and act
accordingly. The main loop of things is in the game.c file, which really just has initiation, the main loop that main.c
keeps calling and a cleanup part. The configuration of baddies, diamonds and the world are all in text files that we can
read when we load them in the ./assets folder. The corresponding .c files take care of loading, rendering and cleaning
up these parts.

The whole thing sort of feels like putting singleton instances of classes in files, with the functions being public
methods and the static variables being private members, some not static and with getters so other files can use them. I
still wonder if this is the right way to structure C programs, but coming from OOP, this works well.

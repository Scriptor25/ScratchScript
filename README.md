## ScratchScript - Scratch but cool

This will be a kind of game engine I guess, using concepts stolen from Scratch (https://scratch.mit.edu) combined with a scriptable language.

# The Goal

The core goal of this is to make it easy for beginners in the broad field of programming, but especially in games programming, to create what they have in mind. Like Scratch it will use a simple block-like syntax, but packed into a custom scripting language instead of using blocks.

# Features

 - Project Creation
 - Assets Management (Sounds, Scripts, Sprites, etc.)
 - Scratch to ScratchScript converter
 - and some more if I have the time to work on it

# Language syntax (WIP)

...

# Dependencies

All the project dependencies are shipped via git submodules and built with the project. ScratchScript hopefully will work platform agnostic, so without you having to worry about anything when building the project yourself.

ScratchScript uses [GLEW](https://github.com/Perlmint/glew-cmake)/OpenGL as the rendering backend, [GLFW](https://github.com/glfw/glfw) for window management, [GLM](https://github.com/icaven/glm) for math, [Dear ImGui](https://github.com/ocornut/imgui) for, as the name already implies, GUI, and last but not least, [nlohmann](https://github.com/nlohmann)'s [Json](https://github.com/nlohmann/json) for, again, JSON.

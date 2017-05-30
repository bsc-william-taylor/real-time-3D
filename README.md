
<img src='preview.gif' />

<img src='icon.png' align='right' width='150' height='150' />

# Real Time 3D

The real time 3D module taught basic 3D graphics using an industry standard graphics library and programming language. Students learn the theoretical underpinnings of 3D graphics - from elementary viewing to scene graphs, gain a basic understanding of contemporary graphics hardware. It is assessed with a practical coursework where students develop a 3D demo and show it both to fellow students and module lectures. 

## Assignment

Using C++ and OpenGL students were to produce a 3D tech demo in which a player can control an animated character around a 3D,lit, environment. The demo should then be presented to students and module lectures and a 3D recording made available should our project fail to build on university machines. Students could investigate advanced graphics topics and if implemented students would receive extra marks although a basic level would still yield a pass. Along with the practical aspect the following elements were mandatory for a basic pass (C Grade). 

* Software design document
* Software project report
* User instructions
* Reasonable  coding standard.
* Use object oriented code

For the best marks students were expected to implement the following.

* Terrain
* Collision detection
* Animation
* 2D/3D Sound
* Minimap
* Dynamic lighting

## Submission

I submitted a 3D city demo written in C++ using OpenGL that had the following features. The .gif showed at the top of this README displays the demo off although as it's a gif it doesn't show an accurate rendering of the demo. As I am quite keen on C++ graphics I decided to implement a lot of additional features. The key feature was that for accurate collisions I decided to auto generate bounding boxes from geometry read in from models. This allowed me to apply collision boxes to the entire city model when it was loaded in from file. The other features are mentioned below.

* Animated models
* Full city model
* Post processing
* UI
* Skybox
* Terrain
* Minimap

## License

Apache 2.0

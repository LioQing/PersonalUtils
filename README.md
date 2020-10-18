# PersonalUtils

All my personal utilities, majority of the code is written myself, feel free to use.  

[Algorithms](https://github.com/LioQing/PersonalUtils/tree/master/algorithms)
[Code Architectures](https://github.com/LioQing/PersonalUtils/tree/master/code%20architectures)  
[Data Structures](https://github.com/LioQing/PersonalUtils/tree/master/data%20structures)  
[Tools](https://github.com/LioQing/PersonalUtils/tree/master/tools)  

### Algorithms

File | Name | Description | C++ Standard | Dependcies | Namespace
--- | --- | --- | --- | --- | ---
[AStarPathfinder.hpp](https://github.com/LioQing/PersonalUtils/blob/master/algorithms/AStarPathfinder.hpp) | A Star Pathfinder | An A* path finder class can be used on a 2D std::vector | C++14 | [Vec2.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Vec2.hpp) | lio

### Code Architectures

File | Name | Description | C++ Standard | Dependcies | Namespace
--- | --- | --- | --- | --- | ---
[lecs.hpp](https://github.com/LioQing/PersonalUtils/blob/master/code%20architectures/lecs.hpp) | Lio's ECS | Single header ECS library, managers for components, entities, and systems, with an event system, also managed by an event Manager | C++14 | N/A | lecs
[lev.hpp](https://github.com/LioQing/PersonalUtils/blob/master/code%20architectures/lev.hpp) | Lio's Event System | Single header simple event system library | C++20 | N/A | lev
[LIC](https://github.com/LioQing/PersonalUtils/blob/master/code%20architectures/LIC) | Lio's IC | Single header data oriented and data driven library, centralized and managed Entity(ID)-Component relataionship (Can be used for ECS) | C++20 | N/A | lic
### Data Structures

File | Name | Description | C++ Standard | Dependcies | Namespace
--- | --- | --- | --- | --- | ---
[Matrix.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Matrix.hpp) | Matrix | A half-finished matrix class | C++14 | N/A | lio
[Vec2.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Vec2.hpp) | Vector2 | 2D Vector class with many graphical functions | C++14 | N/A | lio
[LineSeg.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/LineSeg.hpp) | Line Segment | 2D line segment class | C++14 | [Vec2.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Vec2.hpp) | lio
[Circle.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Circle.hpp) | Circle | 2D circle class | C++14 | [Vec2.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Vec2.hpp), [Transformable.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Transformable.hpp) | lio
[Rect.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Rect.hpp) | Rectangle | 2D rectangle class | C++14 | [Vec2.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Vec2.hpp), [Transformable.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Transformable.hpp) | lio
[Triangle.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Triangle.hpp) | Triangle | 2D triangle class | C++14 | [Vec2.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Vec2.hpp) | lio
[Transformable.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Transformable.hpp) | Transformable | Transformable for other 2D shape classes to inherit from | C++14 | [Vec2.hpp](https://github.com/LioQing/PersonalUtils/blob/master/data%20structures/Graphics/Vec2.hpp) | lio

### Tools

File | Name | Description | C++ Standard | Dependcies | Namespace
--- | --- | --- | --- | --- | ---
[CSVReader](https://github.com/LioQing/PersonalUtils/blob/master/tools/CSVReader) | CSV Reader | CSV (Comma Separated Values) file reader and parser | C++11 | N/A | lio
[LConsoleScreen](https://github.com/LioQing/PersonalUtils/tree/master/tools/LConsoleScreen) | Lio's Console Screen | Display Ascii characters as 2D screen in cmd (Windows only) | C++11 / C99 | [windows.h](https://en.wikipedia.org/wiki/Windows.h) | lio


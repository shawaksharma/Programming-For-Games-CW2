#include "Square.h"
#include "Circle.h"
#include "Surface.h"
#include <time.h>
#include <tgmath.h>


// Creates random shapes and adds them to a surface
void createRandomShapes(int numberOfShapes, Surface &surface) {

    while (surface.shapes.size() < numberOfShapes) {    // While loop executes until the number of shapes is met
        
        // Setting variables
        int a = rand() % 2; // Sets a random integer between 0 and 1 to randomly pick a Square or a Circle
        double range = min(surface.getHeight(), surface.getWidth());    // Finds the maximum value the radius/length can be
        double radiusOrLength = (floor((double)rand()/((double)RAND_MAX/(range/2))) + 1);   // Sets radius/length to a random value between 0 and half of the maximum value
        double x = floor((double)rand()/((double)RAND_MAX/surface.getWidth())); // Sets x value between 0 and the width of the surface, rounds down so it isn't on the boundary
        double y = floor((double)rand()/((double)RAND_MAX/surface.getHeight()));    // Sets y value between 0 and the height of the surface, rounds down so it isn't on the boundary 

        // Creating a square when the random integer is equal to 0
        if (a == 0) {
            cout << "Creating a Square with length " << radiusOrLength << " at (" << x << ", " << y << "), ";   // Prints selected length and origin
            Square* squarePointer = new Square(radiusOrLength,x,y); // Creates shape
            surface.addShape(squarePointer);    // Calls method that checks if shape is in bounds, and adds to surface if it is and removes if not
        }

        // Creating a circle when the random integer is equal to 1
        if (a == 1) {
            cout << "Creating a Circle with radius " << radiusOrLength << " at (" << x << ", " << y << "), ";   // Prints selected radius and origin
            Circle* circlePointer = new Circle(radiusOrLength,x,y); // Creates shape
            surface.addShape(circlePointer);    // Calls method that checks if shape is in bounds, and adds to surface if it is and removes if not
        }
    }

    surface.printShapes();  // Prints set of shapes on the surface
}

int main() {

    // Sets seed for random function
    srand((unsigned int) time(NULL));
    cout << endl;

    // CREATING SURFACE
    double height;
    double width;
    
    // Sets height of the surface
    cout << "Height of the surface: ";
    cin >> height;
    while (cin.fail() || height <= 0) {  // Makes sure the entry is a number and above 0
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid entry, please enter a NUMBER above 0 (height): ";
        cin >> height;
    }

    // Sets width of the surface
    cout << "Width of the surface: ";
    cin >> width;
    while (cin.fail() || width <= 0) {  // Makes sure the entry is a number and above 0
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid entry, please enter a NUMBER above 0 (width): ";
        cin >> width;
    }

    Surface surface(height,width);  // Creates surface
    cout << "Created surface with height of " << surface.getHeight() << " and width of " << surface.getWidth() << "\n\n";   // Outputs surface dimensions to confirm
    

    // CREATING SHAPES
    int numShapes;

    // Creates number of shapes picked by the user with random dimensions and positions
    cout << "Number of Shapes: ";
    cin >> numShapes;
    while (cin.fail() || numShapes <= 0) {  // Makes sure the entry is a number and above 0
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid entry, please enter a NUMBER above 0 (number of shapes): ";
        cin >> numShapes;
    }
    cout << endl;
    createRandomShapes(numShapes, surface); // Generates shapes

    // Starts the game on the surface
    surface.playGame();

    // Makes sure all shapes are deleted from the heap (Only apparent when createRandomShapes() runs but the game is not played)
    if (surface.shapes.size() > 0) {
        for (Shape* shape :  surface.shapes) {
            delete shape;
        }
    }

    return 0;
}

/* 3D EXTENSION

Sphere and Sphere collision:
    Check the distance between the both the centres of the spheres by squaring the difference in x, y and z coordinates, adding them and square rooting the answer.
    Then checking if the sum of the radii of the spheres is greater than or equal to the distance, if so they must be touching or colliding.

Sphere and Cube collision:
    Check the distance between one of the cube's points to the centre of the sphere by squaring the difference in x, y and z coordinates, adding them and square rooting the answer.
    Then checking if the distance between the centre of the sphere and the cube's point is equal to or less than the radius of the circle, if so they must be touching or colliding.
    If not, there's still a possibility the sphere is overlapping with the cube on one of the cube's faces (or inside it). To check this:
        Find the sphere's maximum and minimum points
        maximum X (centre + radius, centre, centre)
        maximum Y (centre, centre + radius, centre)
        maximum Z (centre, centre, centre + radius)
        minimum X (centre - radius, centre, centre)
        minimum Y (centre, centre - radius, centre)
        minimum Z (centre, centre, centre - radius)
        And check if any of these points are inside the cube or touching it by seeing if they are below the cube's maximum x, y, z and above the cube's minimum x, y, z (or equal to).

Cube and Cube collision:
    Check to see if one of the cube's points is inside the other cube or touching it.
    Check to see if the point's x value is between the other cube's minimum x value and maximum x value (or equal to).
    If it is, then check to see if the point's y value is above the cube's minimum and below the cube's maximum y values (or equal to).
    If this is true too, then check the point's z value is between the cube's minimum z value and maximum z value (or equal to).
    If all of these are true, that must mean that point is touching or inside the cube and therefore overlapping.
*/
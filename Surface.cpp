#include "Surface.h"
#include <iostream>
#include <math.h>


// Surface Constructor
Surface::Surface(double height, double width) {
    this->height = height;  // Sets height of surface
    this->width = width;    // Sets width of surface
}


// Getter for width
double Surface::getWidth() { return width; }


// Getter for height
double Surface::getHeight() { return height; }


// Adds the shape to the surface
void Surface::addShape(Shape* shape) {
    
    // Checks if shape is in bounds and if it fits, its added to the surface
    if (shapeInBounds(shape)) {
        cout << "Shape added" << endl;  // Prints shape is added
        shapes.push_back(shape);    // Adds to surface
        shape->setShapeNumber(shapes.size());   // Sets the shape number
    }
    else {
        delete shape;   // If not in bounds, deletes shape
    }
}


// Removes the shape from the surface and deletes it
void Surface::removeShape(Shape* shape) {

    // For loop to iterate through the list and erase matching shape
    for (int i = 0;i<shapes.size();i++) {
        if (shapes[i] == shape) {
            shapes.erase(shapes.begin() + i);
            cout << "Shape " << shape->getShapeNumber() <<  " removed" << endl; // Prints shape is removed
            delete shape;   // Delete shape on heap
            return; // Exits loop once the shape is found
        }
    }
}


// Checks if the shape is on the surface
bool Surface::shapeInBounds(Shape* shape) {

    // SQUARE
    if (shape->shapeType == ShapeType::SQUARE) {
        for (Point* point: shape->points) { // Checks if any of the points lie outside the surface
            if (point->getY() > height || point->getY() < 0 || point->getX() > width || point->getX() < 0) {
                cout << "Shape out of bounds" << endl;  // Prints shape is out of bounds
                return false;   // Returns false since shape is out of bounds
            }
        }
    }

    // CIRCLE
    else if (shape->shapeType == ShapeType::CIRCLE) {
        // If the centre of the circle is closer to the edge of the surface than its radius, then part of the shape is outside the surface
        if (shape->getRadiusOrLength() > shape->points[0]->getX() || shape->getRadiusOrLength() > shape->points[0]->getY() || 
        shape->getRadiusOrLength() > height - shape->points[0]->getY() || shape->getRadiusOrLength() > width - shape->points[0]->getX()) {
            cout << "Shape out of bounds" << endl; // Prints shape is out of bounds
            return false;   // Returns false since shape is out of bounds
        }
    }
    
    return true;    // Return true since shape is in bounds if none of the out of bounds if statments were hit
}


// Prints the total number of shapes and all the shapes with their points on the surface
void Surface::printShapes() {
    cout << endl << "Number of shapes: " << shapes.size() << endl;  // Prints number of shapes on the surface
    // For each shape on the surface, print its shape number and call the shape's print method
    for (Shape* shape : shapes) {
        cout << "Shape " << shape->getShapeNumber(); cout << ": ";
        shape->printShape();
        cout << endl;
    }
    cout << endl;
}


// Plays the game
void Surface::playGame() {
    int round = 0;  // Sets round to 0
    cout << "\n-------------------------------------------\n\nGAME STARTING\n\n";
    printShapes();  // Prints all the shapes on the surface the game starts with
    while (shapes.size() > 1) { // The game will continue until there is no shapes or one shape remaining
        round++;    //Begins the new round
        cout << "-------------------------------------------\n\n" << "ROUND " << round << endl << endl; //  Prints round
        moveShapesRandomly();   //  Moves shapes around randomly
        printShapes();  // Prints new positions of the shapes
        checkOverlap(); // Checks for any shapes that are overlapping and removes them
        cout << endl << "END OF ROUND " << round << " RESULTS" << endl;
        printShapes();  // Prints the remaining shapes
    }
    // If no shapes are left
    if (shapes.size() == 0) {
        cout << "-------------------------------------------\n\nNo shape wins!";
    }
    // If one shape remains
    else {
        cout << "-------------------------------------------\n\nShape " << shapes[0]->getShapeNumber() << " wins!\n\n";
        removeShape(shapes[0]); // Calls remove shape method that deletes the final shape from heap memory
    }
    cout << endl << "Number of rounds: "<< round << endl << endl;   // Prints the number of rounds it took for the game to finish
}


//  Moves the shapes randomly, and if the shape is moved off the surface at a certain boundary, moves it so it touches that boundary instead
void Surface::moveShapesRandomly() {
    for (Shape* shape : shapes) {
        // Chooses random x and y values from -1/3 to 1/3 of the surface width and height
        double x = rand() % (2*(width/3)) - (width/3);  // Random x value to move
        double y = rand() % (2*(height/3)) - (height/3);    // Random y value to move
        cout << "Moving Shape " << shape->getShapeNumber(); cout << " by: (" << x << ", " << y << ")" << endl;  // Prints the x and y values the shape is being moved by
        shape->move(x, y);  // Move shape by random x and y value set above
        
        if (!shapeInBounds(shape)) {    // If shape is moved out of bounds, find which edge it has crossed and return it to the boundary

            // SQUARE
            if (shape->shapeType == ShapeType::SQUARE) {    // Checks which point is out of bounds, and moves it according to that x/y value in the opposite direction
                
                // Checks if the bottom left point has crossed the LEFT (X = 0) side of the surface, move it back by the difference
                if (shape->points[0]->getX() < 0) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (" << -shape->points[0]->getX() << ", 0)" << endl;
                    shape->move(-shape->points[0]->getX(),0);
                }

                // Checks if the bottom left point has crossed the BOTTOM (Y = 0) side of the surface, move it back by the difference
                if (shape->points[0]->getY() < 0) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (0, " << -shape->points[0]->getY() << ")" << endl;
                    shape->move(0,-shape->points[0]->getY());
                }

                // Checks if the top right point has crossed the RIGHT (WIDTH) of the surface, move it back by the difference
                if (shape->points[2]->getX() > width) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (" << width-shape->points[2]->getX() << ", 0)" << endl;
                    shape->move((width-shape->points[2]->getX()),0);
                }

                // Checks if the top right point has crossed the TOP (HEIGHT) of the surface, move it back by the difference
                if (shape->points[2]->getY() > height) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (0, " << height-shape->points[2]->getY() << ")" << endl;
                    shape->move(0,(height-shape->points[2]->getY()));
                }
            }

            // CIRCLE
            else if (shape->shapeType == ShapeType::CIRCLE) {   // Checks if the radius is larger than the distance of the centre of the circle to the edge, it is out of bounds and moved back to touch the boundary
                
                //  If the radius is bigger than the distance to LEFT SIDE (X = 0) of the surface, move back into the surface by the difference
                if (shape->getRadiusOrLength() > shape->points[0]->getX()) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (" << shape->getRadiusOrLength() - shape->points[0]->getX() << ", 0)" << endl;
                    shape->move(shape->getRadiusOrLength() - shape->points[0]->getX(), 0);
                }

                // If the radius is bigger than the distance to the BOTTOM (Y = 0) of the surface, move back into the surface by the difference
                if (shape->getRadiusOrLength() > shape->points[0]->getY()) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (0, " << shape->getRadiusOrLength() - shape->points[0]->getY() << ")" << endl;
                    shape->move(0, shape->getRadiusOrLength() - shape->points[0]->getY());
                }

                // If the radius is bigger than the distance to RIGHT (WIDTH) side of the surface, move back into the surface by the difference
                if (shape->getRadiusOrLength() > height - shape->points[0]->getY()) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (0, " << (height - shape->points[0]->getY()) - shape->getRadiusOrLength() << ")" << endl;
                    shape->move(0, (height - shape->points[0]->getY()) - shape->getRadiusOrLength());
                }

                // If the radius is bigger than the distance to TOP (HEIGHT) of the surface, move back into the surface by the difference
                if (shape->getRadiusOrLength() > width - shape->points[0]->getX()) {
                    cout << "Moving Shape " << shape->getShapeNumber() << " by: (" << (width - shape->points[0]->getX()) - shape->getRadiusOrLength() << ", 0)" << endl;
                    shape->move((width - shape->points[0]->getX()) - shape->getRadiusOrLength(), 0);
                }
            }
        }
        cout << endl;
    }
}



//  Checks if two shapes are overlapping
void Surface::checkOverlap() {
    vector<Shape*> removeShapes;    // Creates a vector list to store shapes to delete after all the comparisons are done
    int index = 1;  // Sets starting index for 2nd iteration (to not repeat comparisons)
    for (Shape* currentShape : shapes) {    // Compares this shape with the rest of the shapes to check for overlaps
        for (int i = index; i<shapes.size(); i++) { // For loop to compare with shapes not yet compared with (starts at the shape after currentShape)

            // SQUARE AND SQUARE
            if (currentShape->shapeType == ShapeType::SQUARE && shapes[i]->shapeType == ShapeType::SQUARE) {
                for (Point* point : currentShape->points) { // Checks if any of the points are inside or touching the other square
                    if (point->getX() >= shapes[i]->points[0]->getX() &&    // Checks if the currentShape's x value is in front or equal to of the bottom left point
                    point->getX() <= shapes[i]->points[3]->getX() &&    // Checks if the currentShape's x value is behind or equal to the top right point
                    point->getY() >= shapes[i]->points[0]->getY() &&    // Checks if the currentShape's y value is above or equal to the bottom left point
                    point->getY() <= shapes[i]->points[1]->getY())  // Checks if the currentShape's y value is below or equal to the top left point
                    {
                        cout << "Shape " << currentShape->getShapeNumber() << " and " << shapes[i]->getShapeNumber() << " are overlapping (Square and Square)" << endl; // Prints overlap
                        removeShapes.push_back(currentShape);   // Add currentShape into removeShapes to remove after comparisons finish
                        removeShapes.push_back(shapes[i]);  // Add shape comparing with into removeShapes to remove after comparisons finish
                        break;  // Break for loop as we don't need to compare the rest of the points
                    }
                }
            }

            // CIRCLE AND CIRCLE
            if (currentShape->shapeType == ShapeType::CIRCLE && shapes[i]->shapeType == ShapeType::CIRCLE) {
                //  Checks if the distance between the two centres is less than adding the radius of both circles together, if so, the circles must be overlapping or touching
                double distance = sqrt((pow((currentShape->points[0]->getX() - shapes[i]->points[0]->getX()), 2) + pow((currentShape->points[0]->getY() - shapes[i]->points[0]->getY()), 2)));
                if (currentShape->getRadiusOrLength() + shapes[i]->getRadiusOrLength() >= distance) {
                    cout << "Shape " << currentShape->getShapeNumber() << " and " << shapes[i]->getShapeNumber() << " are overlapping (Circle and Circle)" << endl; // Prints overlap
                    removeShapes.push_back(currentShape);   // Add currentShape into removeShapes to remove after comparisons finish
                    removeShapes.push_back(shapes[i]);  // Add shape comparing with into removeShapes to remove after comparisons finish
                }
            }

            // SQUARE AND CIRCLE
            if (currentShape->shapeType == ShapeType::SQUARE && shapes[i]->shapeType == ShapeType::CIRCLE) {
                bool overlap = false;
                //  Checks to see if any of the points of the square are closer or equal to the centre of the circle than its radius, if so, the square must be inside or touching the circle
                for (Point* point : currentShape->points) { // Checks all points of the square
                    double distance = sqrt((pow((point->getX() - shapes[i]->points[0]->getX()), 2) + pow((point->getY() - shapes[i]->points[0]->getY()), 2)));
                    if (shapes[i]->getRadiusOrLength() >= distance) {
                        cout << "Shape " << currentShape->getShapeNumber() << " and " << shapes[i]->getShapeNumber() << " are overlapping (Square and Circle)" << endl; // Prints overlap
                        removeShapes.push_back(currentShape);   // Add currentShape into removeShapes to remove after comparisons finish
                        removeShapes.push_back(shapes[i]);  // Add shape comparing with into removeShapes to remove after comparisons finish
                        overlap = true;
                        break;  // Break for loop as we don't need to compare the rest of the points
                    }
                }

                if (overlap == false) { // Only need to execute this code if the previous if no square point was inside the circle

                    // Creating minimum and maximum points of the circle
                    Point maxX(shapes[i]->points[0]->getX() + shapes[i]->getRadiusOrLength(), shapes[i]->points[0]->getY());
                    Point maxY(shapes[i]->points[0]->getX(), shapes[i]->points[0]->getY() + shapes[i]->getRadiusOrLength());
                    Point minX(shapes[i]->points[0]->getX() - shapes[i]->getRadiusOrLength(), shapes[i]->points[0]->getY());
                    Point minY(shapes[i]->points[0]->getX(), shapes[i]->points[0]->getY() - shapes[i]->getRadiusOrLength());

                    vector<Point> circleRange;
                    circleRange = {maxX, maxY, minX, minY};

                    for (Point p : circleRange) {
                        if (p.getX() >= currentShape->points[0]->getX() &&    // Checks if the circle's max/min point is in front or equal to of the bottom left point
                        p.getX() <= currentShape->points[3]->getX() &&    // Checks if the circle's max/min point is behind or equal to the top right point
                        p.getY() >= currentShape->points[0]->getY() &&    // Checks if the circle's max/min point is above or equal to the bottom left point
                        p.getY() <= currentShape->points[1]->getY())  // Checks if the circle's max/min point is below or equal to the top left point
                        {
                            cout << "Shape " << currentShape->getShapeNumber() << " and " << shapes[i]->getShapeNumber() << " are overlapping (Square and Circle)" << endl; // Prints overlap
                            removeShapes.push_back(currentShape);   // Add currentShape into removeShapes to remove after comparisons finish
                            removeShapes.push_back(shapes[i]);  // Add shape comparing with into removeShapes to remove after comparisons finish
                            break;  // Break for loop as we don't need to compare the rest of the points
                        }
                    }
                }
            }

            // CIRCLE AND SQUARE
            if (currentShape->shapeType == ShapeType::CIRCLE && shapes[i]->shapeType == ShapeType::SQUARE) {
                bool overlap = false;
                //  Checks to see if the radius of the circle is larger or equal to than its distance from the centre to a point of the square, if so, they must be overlapping or touching
                for (Point* point : shapes[i]->points) {    // Checks all points of the square
                    double distance = sqrt((pow((point->getX() - currentShape->points[0]->getX()), 2) + pow((point->getY() - currentShape->points[0]->getY()), 2)));
                    if (currentShape->getRadiusOrLength() >= distance) {
                        cout << "Shape " << shapes[i]->getShapeNumber() << " and " << currentShape->getShapeNumber() << " are overlapping (Circle and Square)" << endl;
                        removeShapes.push_back(shapes[i]);  // Add currentShape into removeShapes to remove after comparisons finish
                        removeShapes.push_back(currentShape);   // Add shape comparing with into removeShapes to remove after comparisons finish
                        overlap = true;
                        break;  // Break for loop as we don't need to compare the rest of the points
                    }
                }

                if (overlap == false) { // Only need to execute this code if the previous if no square point was inside the circle
                    
                    // Creating minimum and maximum points of the circle
                    Point maxX(currentShape->points[0]->getX() + currentShape->getRadiusOrLength(), currentShape->points[0]->getY());
                    Point maxY(currentShape->points[0]->getX(), currentShape->points[0]->getY() + currentShape->getRadiusOrLength());
                    Point minX(currentShape->points[0]->getX() - currentShape->getRadiusOrLength(), currentShape->points[0]->getY());
                    Point minY(currentShape->points[0]->getX(), currentShape->points[0]->getY() - currentShape->getRadiusOrLength());

                    vector<Point> circleRange;
                    circleRange = {maxX, maxY, minX, minY};

                    for (Point p : circleRange) {
                        if (p.getX() >= shapes[i]->points[0]->getX() &&    // Checks if the circle's max/min point is in front or equal to of the bottom left point
                        p.getX() <= shapes[i]->points[3]->getX() &&    // Checks if the circle's max/min point is behind or equal to the top right point
                        p.getY() >= shapes[i]->points[0]->getY() &&    // Checks if the circle's max/min point is above or equal to the bottom left point
                        p.getY() <= shapes[i]->points[1]->getY())  // Checks if the circle's max/min point is below or equal to the top left point
                        {
                            cout << "Shape " << currentShape->getShapeNumber() << " and " << shapes[i]->getShapeNumber() << " are overlapping (Circle and Square)" << endl; // Prints overlap
                            removeShapes.push_back(shapes[i]);   // Add currentShape into removeShapes to remove after comparisons finish
                            removeShapes.push_back(currentShape);  // Add shape comparing with into removeShapes to remove after comparisons finish
                            break;  // Break for loop as we don't need to compare the rest of the points
                        }
                    }
                }  
            }
        }

        index++;    // Increment index
    }
    //  Remove all shapes found overlapping
    for (Shape* shape: removeShapes) {
        removeShape(shape);
    }
}
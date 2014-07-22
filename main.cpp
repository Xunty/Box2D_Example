#include <erincatto/box2d/box2d/box2d.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);

    //**************************************************//
    //                 Creating a World                        //
    //**************************************************//

    // Define the gravity vector.
    b2Vec2 gravity(0.0f,-10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);


    //**************************************************//
    //                 Creating a Ground Box               //
    //**************************************************//

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f,-10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    //**************************************************//
    //            Creating a Circle Shape                   //
    //**************************************************//

    b2BodyDef BodyDef;
    BodyDef.type = b2_dynamicBody;
    BodyDef.position = b2Vec2(0.0f, 4.0f);
    BodyDef.userData = (void *) "Circle";
    b2Body* body = world.CreateBody(&BodyDef);

    b2CircleShape circle;
    circle.m_radius = 1.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 2.0f;
    fixtureDef.restitution = 0.5f;

    fixtureDef.shape = &circle;

    body->CreateFixture(&fixtureDef);

    //**************************************************//
    //            Simulating the World (of Box2D)     //
    //**************************************************//

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // This is our little game loop.
    for (int32 i = 0; i < 100; ++i)
    {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world.Step(timeStep, velocityIterations, positionIterations);

        // Now print the position and angle of the body.
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        if (position.y - 1.00 <= 0.001)
            cout<< "Ball hits the ground!!" << endl;
        else
            cout<<"X = " << position.x << " Y = " << position.y << endl;
    }
}
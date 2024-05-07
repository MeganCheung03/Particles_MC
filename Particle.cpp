#include "Particle.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
    //initialize variables
    m_ttl = TTL;
    m_numPoints = numPoints;
    m_radiansPerSec = ((float)rand() / (RAND_MAX)) * M_PI;
    //map between monitor pixel coords to Cartesian coordinates to allow Matrix algebra to work
    m_cartesianPlane.setCenter(0, 0);
    //initialize width and height to size of RenderWindow and invert the y-axis
    m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
    //store location of center on Cartesian plane
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    //assign random horizontal velocties 
    m_vx = rand() % 401 + 100; 
    //make m_vx randomly positive or negative
    int posOrNeg = rand() % 2;
    if (posOrNeg != 0)
    {
        m_vx *= (-1);
    }
    //assign random vertical velocities
    m_vy = rand() % 401 + 100; 

    //colors
    m_color1.r = 255;
    m_color1.g = 255;
    m_color1.b = 255;

    m_color2.r = 0;
    m_color2.g = 128;
    m_color2.b = 0;

    float theta = ((float)rand() / (RAND_MAX)) * (M_PI / 2);
    //amount to rotate per vertex
    float dTheta = 2 * M_PI / (numPoints - 1);

    //generate numPoint vertices with randomizsed radii
    for (int i = 0; i < numPoints; i++)
    {
        float r, dx, dy;
        r = rand() % 61 + 20;
        dx = r * cos(theta);
        dy = r * sin(theta);
        m_A(0, i) = m_centerCoordinate.x + dx;
        m_A(1, i) = m_centerCoordinate.y + dy;
        theta += dTheta;
    }
}

void Particle::draw(RenderTarget& target, RenderStates states) const 
{
    //overrides the virtual function from Drawable to allow this one to polymorph
    //convert Cartesian matrix coords from m_a to pixel coords in VertexArray
    sf::VertexArray lines(TriangleFan, m_numPoints + 1);
    //store location on monitor of center of particle
    sf::Vector2i screenCenter = target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane);
    sf::Vector2f center(screenCenter);
    //give center of the particle and a colour
    lines[0].position = center;
    lines[0].color = m_color1;

    for (int i = 1; i <= m_numPoints; i++)
    {
        //map from Cartesian to pixel coords       
        sf::Vector2f coords(m_A(0, i - 1), m_A(1, i - 1));
        sf::Vector2i pixelCoords = target.mapCoordsToPixel(coords, m_cartesianPlane);
        sf::Vector2f pixel(pixelCoords);

        lines[i].position = pixel;
        lines[i].color = m_color2;
    }
    //draw VertexArray
    target.draw(lines, states);
}

void Particle::update(float dt)
{
    //decreasing time to live, rotating the particle, and changing it's size
    m_ttl -= dt;
    rotate(dt * m_radiansPerSec);
    scale(SCALE);
    float dx, dy;
    //how far to shift/translate particle
    dx = m_vx * dt;
    //travel up and then fall down
    m_vy -= G * dt; 
    dy = m_vy * dt;
    translate(dx, dy);
}

bool Particle::almostEqual(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = M_PI / 4.0;
    RotationMatrix r(M_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }


    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(M_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0, j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
}

void Particle::rotate(double theta)
{
    Vector2f temp = m_centerCoordinate;
    // shift particles center back to origin
    translate(-temp.x, -temp.y);
    RotationMatrix R(theta);
    m_A = R * m_A;
    //shift particle back to origin center
    translate(temp.x, temp.y);
}

void Particle::scale(double c)
{
    Vector2f temp = m_centerCoordinate;
    //shift  particle center back to the origin
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    ScalingMatrix S(c);
    m_A = S * m_A;
    //shift particle back to original center
    translate(temp.x, temp.y);
}


void Particle::translate(double xShift, double yShift)
{
    Matrices::TranslationMatrix T(xShift, yShift, m_A.getCols());
    m_A = T + m_A;
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}